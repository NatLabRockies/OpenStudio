/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"
#include "TestFailurePoint.hpp"
#include "StraightComponent/CompoundTerminalTopologyInspection.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/NodeList.hpp"
#include "ModelObject/NodeList_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "StraightComponent/SingleDuctTerminalRemovalPlan.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    using detail::ExistingNodeField;
    using detail::ExistingNodeRows;
    using detail::existingNodeCollectionField;
    using detail::existingNodeField;
    using detail::existingNodeRows;
    using detail::existingObjectField;
    using detail::hasExactSources;
    using detail::isSoleOwnedChild;

    bool isSupportedParallelPIUFan(const HVACComponent& hvacComponent) {
      const auto type = hvacComponent.iddObject().type();
      return (type == IddObjectType::Fan_ConstantVolume) || (type == IddObjectType::Fan_SystemModel);
    }

    bool isSupportedParallelPIUReheatCoil(const HVACComponent& hvacComponent) {
      const auto type = hvacComponent.iddObject().type();
      return (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel)
             || (type == IddObjectType::Coil_Heating_Water);
    }

    boost::optional<ThermalZone> owningThermalZoneForZoneNode(const Model& model, const Node& node) {
      for (const auto& connections : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        const auto inletNodes = connections.zoneAirInletNodes();
        if (std::ranges::find(inletNodes, node) != inletNodes.end()) {
          return connections.thermalZone();
        }
      }
      return boost::none;
    }

    bool isServedZoneReturnNode(const boost::optional<ThermalZone>& thermalZone, const ModelObject& nodeObject) {
      auto node = nodeObject.optionalCast<Node>();
      if (!thermalZone || !node) {
        return false;
      }

      auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto connections = zoneImpl->zoneHVACEquipmentConnections();
      if (!connections) {
        return false;
      }

      const auto returnNodes = connections->zoneReturnAirNodes();
      return std::ranges::find(returnNodes, *node) != returnNodes.end();
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& thermalZone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = thermalZone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return thermalZone;
        }
      }
      return boost::none;
    }

    bool registerTerminalWithZone(ThermalZone& thermalZone, const ModelObject& terminal) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);

      if (!zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "Failed to register " << terminal.briefDescription() << " with thermal zone " << thermalZone.briefDescription() << ".");
        return false;
      }

      return true;
    }

    bool unregisterTerminalFromZone(ThermalZone& thermalZone, const ModelObject& terminal) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
    }

    struct AirFields
    {
      unsigned inlet;
      unsigned outlet;
    };

    boost::optional<AirFields> parallelPIUFanAirFields(const HVACComponent& fan) {
      switch (fan.iddObject().type().value()) {
        case IddObjectType::Fan_ConstantVolume:
          return AirFields{openstudio::Fan_ConstantVolumeFields::AirInletNodeName, openstudio::Fan_ConstantVolumeFields::AirOutletNodeName};
        case IddObjectType::Fan_SystemModel:
          return AirFields{openstudio::Fan_SystemModelFields::AirInletNodeName, openstudio::Fan_SystemModelFields::AirOutletNodeName};
        default:
          return boost::none;
      }
    }

    boost::optional<AirFields> parallelPIUCoilAirFields(const HVACComponent& coil) {
      switch (coil.iddObject().type().value()) {
        case IddObjectType::Coil_Heating_Electric:
          return AirFields{openstudio::Coil_Heating_ElectricFields::AirInletNodeName, openstudio::Coil_Heating_ElectricFields::AirOutletNodeName};
        case IddObjectType::Coil_Heating_Fuel:
          return AirFields{openstudio::Coil_Heating_FuelFields::AirInletNodeName, openstudio::Coil_Heating_FuelFields::AirOutletNodeName};
        case IddObjectType::Coil_Heating_Water:
          return AirFields{openstudio::Coil_Heating_WaterFields::AirInletNodeName, openstudio::Coil_Heating_WaterFields::AirOutletNodeName};
        default:
          return boost::none;
      }
    }

    bool parallelPIUHasContainedTopology(const ModelObject& terminal) {
      if (existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName).set
          || existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName).set) {
        return true;
      }
      for (const auto& [relationshipField, airFieldResolver] :
           {std::pair<unsigned, boost::optional<AirFields> (*)(const HVACComponent&)>(
              openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, parallelPIUFanAirFields),
            std::pair<unsigned, boost::optional<AirFields> (*)(const HVACComponent&)>(
              openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, parallelPIUCoilAirFields)}) {
        const auto relationship = existingObjectField(terminal, relationshipField);
        const auto component = relationship.object ? relationship.object->optionalCast<HVACComponent>() : boost::none;
        const auto airFields = component ? airFieldResolver(*component) : boost::none;
        if (component && airFields
            && (existingObjectField(component->cast<ModelObject>(), airFields->inlet).set
                || existingObjectField(component->cast<ModelObject>(), airFields->outlet).set)) {
          return true;
        }
      }
      return false;
    }

    // A Parallel PIU owns an induced-air fan lane that joins the primary lane
    // before the reheat coil. Prove that exact graph before any external or
    // plant topology is changed.
    class ParallelPIUContainedAirPathRemovalPlan
    {
     public:
      static std::unique_ptr<ParallelPIUContainedAirPathRemovalPlan> prepare(const ModelObject& terminal) {
        const auto fanRelationship = existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName);
        const auto coilRelationship = existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
        const auto fan = fanRelationship.object ? fanRelationship.object->optionalCast<HVACComponent>() : boost::none;
        const auto coil = coilRelationship.object ? coilRelationship.object->optionalCast<HVACComponent>() : boost::none;
        if (!fanRelationship.set || !coilRelationship.set || !fan || !coil || !isSupportedParallelPIUFan(*fan)
            || !isSupportedParallelPIUReheatCoil(*coil) || !isSoleOwnedChild(terminal, *fan) || !isSoleOwnedChild(terminal, *coil)) {
          return nullptr;
        }

        const auto fanFields = parallelPIUFanAirFields(*fan);
        const auto coilFields = parallelPIUCoilAirFields(*coil);
        const auto storedCoilType =
          terminal.getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilObjectType, false, true);
        if (!fanFields || !coilFields || !storedCoilType || !openstudio::istringEqual(*storedCoilType, coil->iddObject().name())) {
          return nullptr;
        }

        const auto primary = existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName);
        const auto secondary = existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName);
        const auto terminalOutlet = existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName);
        const auto mixerRelationship = existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName);
        const auto fanInlet = existingNodeField(fan->cast<ModelObject>(), fanFields->inlet);
        const auto fanOutlet = existingNodeField(fan->cast<ModelObject>(), fanFields->outlet);
        const auto coilInlet = existingNodeField(coil->cast<ModelObject>(), coilFields->inlet);
        const auto coilOutlet = existingNodeField(coil->cast<ModelObject>(), coilFields->outlet);

        const bool hasPrimary = primary.set;
        const bool hasSecondary = secondary.set;
        if (!hasPrimary && !hasSecondary) {
          if (terminalOutlet.set || mixerRelationship.set || fanInlet.set || fanOutlet.set || coilInlet.set || coilOutlet.set) {
            return nullptr;
          }
          return std::unique_ptr<ParallelPIUContainedAirPathRemovalPlan>(
            new ParallelPIUContainedAirPathRemovalPlan(terminal, fan->cast<ModelObject>(), *fanFields, coil->cast<ModelObject>(), *coilFields));
        }

        if (hasPrimary && !hasSecondary) {
          if (!primary.node || !terminalOutlet.set || !terminalOutlet.node || mixerRelationship.set || fanInlet.set || fanOutlet.set || coilInlet.set
              || coilOutlet.set) {
            return nullptr;
          }
          return std::unique_ptr<ParallelPIUContainedAirPathRemovalPlan>(
            new ParallelPIUContainedAirPathRemovalPlan(terminal, fan->cast<ModelObject>(), *fanFields, coil->cast<ModelObject>(), *coilFields));
        }

        if (!hasPrimary || !primary.node || !secondary.node || !fanInlet.node || !fanOutlet.node || !coilInlet.node || !coilOutlet.node
            || !mixerRelationship.set || !mixerRelationship.object) {
          return nullptr;
        }
        const auto mixer = mixerRelationship.object->optionalCast<AirLoopHVACZoneMixer>();
        if (!mixer || !hasExactSources(mixer->cast<ModelObject>(), {terminal.handle()})) {
          return nullptr;
        }
        const auto mixerOutlet = existingNodeField(mixer->cast<ModelObject>(), openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName);
        const auto mixerInlets = existingNodeRows(mixer->cast<ModelObject>(), openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName);
        if (!mixerOutlet.node || !mixerInlets.valid || mixer->extensibleGroups().size() != 2u || mixerInlets.rows.size() != 2u
            || mixerInlets.rows[0].first != 0u || mixerInlets.rows[0].second.handle() != fanOutlet.node->handle() || mixerInlets.rows[1].first != 1u
            || mixerInlets.rows[1].second.handle() != primary.node->handle() || fanInlet.node->handle() != secondary.node->handle()
            || coilInlet.node->handle() != mixerOutlet.node->handle()) {
          return nullptr;
        }
        const auto authoritativeOutlet = *coilOutlet.node;
        const std::vector<Handle> graphNodeHandles{primary.node->handle(), secondary.node->handle(), authoritativeOutlet.handle(),
                                                   fanOutlet.node->handle(), mixerOutlet.node->handle()};
        std::vector<Handle> uniqueGraphNodeHandles = graphNodeHandles;
        std::ranges::sort(uniqueGraphNodeHandles);
        if (std::ranges::unique(uniqueGraphNodeHandles).begin() != uniqueGraphNodeHandles.end()
            || !hasExactSources(fanOutlet.node->cast<ModelObject>(), {fan->handle(), mixer->handle()})
            || !hasExactSources(mixerOutlet.node->cast<ModelObject>(), {mixer->handle(), coil->handle()})) {
          return nullptr;
        }

        struct ExhaustMatch
        {
          ZoneHVACEquipmentConnections connections;
          ModelObject target;
        };
        std::vector<ExhaustMatch> exhaustMatches;
        for (const auto& connections : terminal.model().getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
          const auto exhaustField = existingNodeCollectionField(connections.cast<ModelObject>(),
                                                                openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
          if (!exhaustField.valid || !exhaustField.target) {
            continue;
          }
          if (std::ranges::count(exhaustField.nodes, *secondary.node) == 1) {
            exhaustMatches.push_back(ExhaustMatch{connections, *exhaustField.target});
          }
        }
        if (exhaustMatches.size() != 1u) {
          return nullptr;
        }

        const auto zoneRelationship =
          existingObjectField(exhaustMatches.front().connections.cast<ModelObject>(), openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
        const auto servedZone = zoneRelationship.object ? zoneRelationship.object->optionalCast<ThermalZone>() : boost::none;
        const auto inletField = existingNodeCollectionField(exhaustMatches.front().connections.cast<ModelObject>(),
                                                            openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
        if (!servedZone || !inletField.valid || std::ranges::count(inletField.nodes, authoritativeOutlet) != 1) {
          return nullptr;
        }

        std::vector<ThermalZone> registeredZones;
        for (const auto& zone : terminal.model().getConcreteModelObjects<ThermalZone>()) {
          const auto equipment = zone.equipment();
          const auto count = std::ranges::count(equipment, terminal);
          if (count > 1) {
            return nullptr;
          }
          if (count == 1) {
            registeredZones.push_back(zone);
          }
        }
        if (registeredZones.size() > 1u || (!registeredZones.empty() && registeredZones.front() != *servedZone)) {
          return nullptr;
        }

        const auto exhaustTarget = exhaustMatches.front().target;
        const auto exhaustSourceHandle =
          exhaustTarget.optionalCast<NodeList>() ? exhaustTarget.handle() : exhaustMatches.front().connections.handle();
        if (!hasExactSources(secondary.node->cast<ModelObject>(), {terminal.handle(), fan->handle(), exhaustSourceHandle})) {
          return nullptr;
        }
        if (auto exhaustList = exhaustTarget.optionalCast<NodeList>()) {
          if (!hasExactSources(exhaustList->cast<ModelObject>(), {exhaustMatches.front().connections.handle()})) {
            return nullptr;
          }
        }

        std::vector<ZoneHVACAirDistributionUnit> airDistributionUnits;
        for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
          if (auto airDistributionUnit = source.optionalCast<ZoneHVACAirDistributionUnit>()) {
            airDistributionUnits.push_back(*airDistributionUnit);
          }
        }
        if (airDistributionUnits.size() > 1u) {
          return nullptr;
        }
        if (!airDistributionUnits.empty()) {
          const auto aduObject = airDistributionUnits.front().cast<ModelObject>();
          const auto linkedTerminal = existingObjectField(aduObject, openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName);
          const auto aduOutlet = existingNodeField(aduObject, openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName);
          const auto terminalType = aduObject.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, false, true);
          if (!linkedTerminal.object || linkedTerminal.object->handle() != terminal.handle() || !aduOutlet.node
              || aduOutlet.node->handle() != authoritativeOutlet.handle() || !terminalType
              || !openstudio::istringEqual(*terminalType, terminal.iddObject().name())) {
            return nullptr;
          }
        }

        auto result = std::unique_ptr<ParallelPIUContainedAirPathRemovalPlan>(
          new ParallelPIUContainedAirPathRemovalPlan(terminal, fan->cast<ModelObject>(), *fanFields, coil->cast<ModelObject>(), *coilFields));
        result->m_mixer = mixer->cast<ModelObject>();
        result->m_fanOutlet = fanOutlet.node->cast<ModelObject>();
        result->m_mixerOutlet = mixerOutlet.node->cast<ModelObject>();
        result->m_secondary = secondary.node->cast<ModelObject>();
        result->m_zoneConnections = exhaustMatches.front().connections.cast<ModelObject>();
        result->m_exhaustTarget = exhaustTarget;
        result->m_authoritativeOutlet = authoritativeOutlet;
        result->m_allowMissingZoneRegistration = registeredZones.empty();
        return result;
      }

      bool hasContainedAirPath() const {
        return static_cast<bool>(m_mixer);
      }

      boost::optional<Node> authoritativeOutlet() const {
        return m_authoritativeOutlet;
      }

      bool allowMissingZoneRegistration() const {
        return m_allowMissingZoneRegistration;
      }

      void commit() {
        if (!m_mixer) {
          return;
        }

        auto fanImpl = m_fan.getImpl<detail::ModelObject_Impl>();
        auto coilImpl = m_coil.getImpl<detail::ModelObject_Impl>();
        auto terminalImpl = m_terminal.getImpl<detail::ModelObject_Impl>();
        OS_ASSERT(fanImpl && coilImpl && terminalImpl);
        assertSuccessfulMutation(coilImpl->setPointer(m_coilFields.inlet, Handle(), false));
        assertSuccessfulMutation(coilImpl->setPointer(m_coilFields.outlet, Handle(), false));
        assertSuccessfulMutation(fanImpl->setPointer(m_fanFields.inlet, Handle(), false));
        assertSuccessfulMutation(fanImpl->setPointer(m_fanFields.outlet, Handle(), false));
        assertSuccessfulMutation(
          terminalImpl->setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName, Handle(), false));

        const auto mixerHandle = m_mixer->handle();
        auto mixer = m_mixer->optionalCast<AirLoopHVACZoneMixer>();
        OS_ASSERT(mixer);
        mixer->remove();
        OS_ASSERT(!m_terminal.model().getObject(mixerHandle));

        for (const auto& internalNodeObject : {m_fanOutlet, m_mixerOutlet}) {
          OS_ASSERT(internalNodeObject);
          auto internalNode = internalNodeObject->optionalCast<Node>();
          OS_ASSERT(internalNode && internalNode->sources().empty());
          const auto nodeHandle = internalNode->handle();
          internalNode->remove();
          OS_ASSERT(!m_terminal.model().getObject(nodeHandle));
        }

        assertSuccessfulMutation(
          terminalImpl->setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, Handle(), false));
        OS_ASSERT(m_zoneConnections && m_exhaustTarget && m_secondary);
        auto zoneConnections = m_zoneConnections->optionalCast<ZoneHVACEquipmentConnections>();
        auto secondary = m_secondary->optionalCast<Node>();
        OS_ASSERT(zoneConnections && secondary);
        if (auto exhaustList = m_exhaustTarget->optionalCast<NodeList>()) {
          const bool removeList = exhaustList->nodes().size() == 1u;
          assertSuccessfulMutation(exhaustList->getImpl<detail::NodeList_Impl>()->removeNode(*secondary));
          if (removeList) {
            assertSuccessfulMutation(zoneConnections->getImpl<detail::ModelObject_Impl>()->setPointer(
              openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, Handle(), false));
            const auto listHandle = exhaustList->handle();
            exhaustList->remove();
            OS_ASSERT(!m_terminal.model().getObject(listHandle));
          }
        } else {
          OS_ASSERT(m_exhaustTarget->optionalCast<Node>());
          assertSuccessfulMutation(zoneConnections->getImpl<detail::ModelObject_Impl>()->setPointer(
            openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, Handle(), false));
        }

        OS_ASSERT(secondary->sources().empty());
        const auto secondaryHandle = secondary->handle();
        secondary->remove();
        OS_ASSERT(!m_terminal.model().getObject(secondaryHandle));
      }

     private:
      ParallelPIUContainedAirPathRemovalPlan(ModelObject terminal, ModelObject fan, AirFields fanFields, ModelObject coil, AirFields coilFields)
        : m_terminal(std::move(terminal)), m_fan(std::move(fan)), m_fanFields(fanFields), m_coil(std::move(coil)), m_coilFields(coilFields) {}

      ModelObject m_terminal;
      ModelObject m_fan;
      AirFields m_fanFields;
      ModelObject m_coil;
      AirFields m_coilFields;
      bool m_allowMissingZoneRegistration = false;
      boost::optional<ModelObject> m_mixer;
      boost::optional<ModelObject> m_fanOutlet;
      boost::optional<ModelObject> m_mixerOutlet;
      boost::optional<ModelObject> m_secondary;
      boost::optional<ModelObject> m_zoneConnections;
      boost::optional<ModelObject> m_exhaustTarget;
      boost::optional<Node> m_authoritativeOutlet;
    };

    struct ParallelPIUTopologyRemovalPlans
    {
      std::unique_ptr<ParallelPIUContainedAirPathRemovalPlan> containedAirPath;
      std::unique_ptr<detail::SingleDuctTerminalRemovalPlan> externalTopology;
    };

    std::unique_ptr<ParallelPIUTopologyRemovalPlans> prepareParallelPIUTopologyRemoval(const ModelObject& terminalObject) {
      auto result = std::make_unique<ParallelPIUTopologyRemovalPlans>();
      result->containedAirPath = ParallelPIUContainedAirPathRemovalPlan::prepare(terminalObject);
      if (!result->containedAirPath) {
        return nullptr;
      }

      auto terminal = terminalObject.cast<StraightComponent>();
      if (detail::SingleDuctTerminalRemovalPlan::hasTopology(terminal)) {
        std::vector<ModelObject> containedInletSources;
        if (result->containedAirPath->hasContainedAirPath()) {
          const auto mixerRelationship =
            existingObjectField(terminalObject, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName);
          OS_ASSERT(mixerRelationship.object);
          containedInletSources.push_back(*mixerRelationship.object);
        }
        result->externalTopology = detail::SingleDuctTerminalRemovalPlan::prepare(
          terminal, containedInletSources, result->containedAirPath->authoritativeOutlet(), result->containedAirPath->allowMissingZoneRegistration());
        if (!result->externalTopology) {
          return nullptr;
        }
      }
      return result;
    }

    // A missing persisted child name can still leave one uniquely identifiable
    // Parallel PIU graph. Temporarily restore only that relationship to prepare
    // the normal air teardown, then put the unresolved text back. A surviving
    // water coil keeps its independent plant branch during load repair.
    bool detachIncompleteParallelPIUAirTopologyForRepair(ModelObject terminal, const boost::optional<HVACComponent>& knownFan,
                                                         const boost::optional<HVACComponent>& knownCoil) {
      const auto mixerRelationship = existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName);
      const auto mixer = mixerRelationship.object ? mixerRelationship.object->optionalCast<AirLoopHVACZoneMixer>() : boost::none;
      const auto terminalOutlet = existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName);
      const auto mixerOutlet =
        mixer ? existingNodeField(mixer->cast<ModelObject>(), openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName) : ExistingNodeField{};
      const auto mixerInlets =
        mixer ? existingNodeRows(mixer->cast<ModelObject>(), openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName) : ExistingNodeRows{};
      if (!mixer || !terminalOutlet.node || !mixerOutlet.node || !mixerInlets.valid || mixerInlets.rows.size() != 2u
          || mixerInlets.rows[0].first != 0u) {
        return false;
      }

      std::vector<HVACComponent> fanCandidates;
      std::vector<HVACComponent> coilCandidates;
      for (const auto& component : terminal.model().getModelObjects<HVACComponent>()) {
        if (!knownFan || component.handle() == knownFan->handle()) {
          if (const auto fields = parallelPIUFanAirFields(component)) {
            const auto outlet = existingNodeField(component.cast<ModelObject>(), fields->outlet);
            if (outlet.node && outlet.node->handle() == mixerInlets.rows[0].second.handle()) {
              fanCandidates.push_back(component);
            }
          }
        }

        if (!knownCoil || component.handle() == knownCoil->handle()) {
          if (const auto fields = parallelPIUCoilAirFields(component)) {
            const auto inlet = existingNodeField(component.cast<ModelObject>(), fields->inlet);
            const auto outlet = existingNodeField(component.cast<ModelObject>(), fields->outlet);
            if (inlet.node && outlet.node && inlet.node->handle() == mixerOutlet.node->handle()
                && outlet.node->handle() == terminalOutlet.node->handle()) {
              coilCandidates.push_back(component);
            }
          }
        }
      }
      if (fanCandidates.size() != 1u || coilCandidates.size() != 1u) {
        return false;
      }

      struct TemporarilyRepairedField
      {
        unsigned field;
        std::string rawValue;
      };
      std::vector<TemporarilyRepairedField> repairedFields;
      auto terminalWorkspaceImpl = terminal.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(terminalWorkspaceImpl);
      const auto temporarilySetRelationship = [&](unsigned field, const HVACComponent& component) {
        const auto rawValue = terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("");
        if (!terminalWorkspaceImpl->setPointer(field, component.handle(), false)) {
          return false;
        }
        repairedFields.push_back(TemporarilyRepairedField{field, rawValue});
        return true;
      };

      bool relationshipsSet = true;
      if (!knownFan) {
        relationshipsSet = temporarilySetRelationship(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, fanCandidates.front());
      }
      if (relationshipsSet && !knownCoil) {
        relationshipsSet =
          temporarilySetRelationship(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, coilCandidates.front());
      }

      auto plans = relationshipsSet ? prepareParallelPIUTopologyRemoval(terminal) : nullptr;
      for (auto repaired = repairedFields.rbegin(); repaired != repairedFields.rend(); ++repaired) {
        assertSuccessfulMutation(terminalWorkspaceImpl->setPointer(repaired->field, Handle(), false));
        assertSuccessfulMutation(terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(repaired->field, repaired->rawValue, false));
      }
      if (!plans || !plans->externalTopology) {
        return false;
      }

      plans->containedAirPath->commit();
      plans->externalTopology->commit();
      return true;
    }

    boost::optional<unsigned> fanAvailabilityScheduleField(const HVACComponent& fan) {
      if (fan.iddObject().type() == IddObjectType::Fan_ConstantVolume) {
        return openstudio::Fan_ConstantVolumeFields::AvailabilityScheduleName;
      }
      if (fan.iddObject().type() == IddObjectType::Fan_SystemModel) {
        return openstudio::Fan_SystemModelFields::AvailabilityScheduleName;
      }
      return boost::none;
    }

    bool syncFanAvailabilityWithLoop(HVACComponent& fan, Schedule& schedule) {
      const auto field = fanAvailabilityScheduleField(fan);
      return field && fan.setPointer(*field, schedule.handle());
    }

    void applyConstructorDefaults(AirTerminalSingleDuctParallelPIUReheat& terminal) {
      terminal.autosizeMaximumPrimaryAirFlowRate();
      terminal.autosizeMaximumSecondaryAirFlowRate();
      terminal.autosizeMinimumPrimaryAirFlowFraction();
      terminal.autosizeFanOnFlowFraction();
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      const bool minimumFlowSet = terminal.setMinimumHotWaterorSteamFlowRate(0.0);
      const bool convergenceSet = terminal.setConvergenceTolerance(0.001);
      const bool fanControlSet = terminal.setFanControlType("ConstantSpeed");
      const bool fanTurnDownSet = terminal.setMinimumFanTurnDownRatio(0.3);
      const bool heatingControlSet = terminal.setHeatingControlType("Staged");
      const bool designTemperatureSet = terminal.setDesignHeatingDischargeAirTemperature(32.1);
      const bool highLimitTemperatureSet = terminal.setHighLimitHeatingDischargeAirTemperature(37.7);
      OS_ASSERT(minimumFlowSet && convergenceSet && fanControlSet && fanTurnDownSet && heatingControlSet && designTemperatureSet
                && highLimitTemperatureSet);
    }

  }  // namespace

  AirTerminalSingleDuctParallelPIUReheat::AirTerminalSingleDuctParallelPIUReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    const bool valueSet = alwaysOn.setValue(1.0);
    const bool availabilitySet = setAvailabilitySchedule(alwaysOn);
    OS_ASSERT(valueSet && availabilitySet);
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctParallelPIUReheat::AirTerminalSingleDuctParallelPIUReheat(const Model& model, Schedule& schedule, HVACComponent& fan,
                                                                                 HVACComponent& reheatCoil)
    : StraightComponent(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>());

    if (!setAvailabilitySchedule(schedule)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                         "Could not construct " << briefDescription() << ", because the availability schedule could not be assigned.");
    }

    if (!setFan(fan)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                         "Could not construct " << briefDescription() << ", because the fan type was invalid or from another model.");
    }

    if (!setReheatCoil(reheatCoil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                         "Could not construct " << briefDescription() << ", because the reheat coil type was invalid or from another model.");
    }

    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctParallelPIUReheat::AirTerminalSingleDuctParallelPIUReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctParallelPIUReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctParallelPIUReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat;
  }

  std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat::fanControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType);
  }

  std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat::heatingControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HeatingControlType);
  }

  Schedule AirTerminalSingleDuctParallelPIUReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  bool AirTerminalSingleDuctParallelPIUReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->addToNode(node);
  }

  HVACComponent AirTerminalSingleDuctParallelPIUReheat::fan() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->fan();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setFan(HVACComponent& hvacComponent) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setFan(hvacComponent);
  }

  HVACComponent AirTerminalSingleDuctParallelPIUReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setReheatCoil(HVACComponent& hvacComponent) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setReheatCoil(hvacComponent);
  }

  boost::optional<Node> AirTerminalSingleDuctParallelPIUReheat::secondaryAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->secondaryAirInletNode();
  }

  unsigned AirTerminalSingleDuctParallelPIUReheat::secondaryAirInletPort() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->secondaryAirInletPort();
  }

  boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::maximumPrimaryAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->maximumPrimaryAirFlowRate();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isMaximumPrimaryAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMaximumPrimaryAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMaximumPrimaryAirFlowRate(maximumPrimaryAirFlowRate);
  }

  void AirTerminalSingleDuctParallelPIUReheat::autosizeMaximumPrimaryAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMaximumPrimaryAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::maximumSecondaryAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->maximumSecondaryAirFlowRate();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isMaximumSecondaryAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMaximumSecondaryAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMaximumSecondaryAirFlowRate(maximumSecondaryAirFlowRate);
  }

  void AirTerminalSingleDuctParallelPIUReheat::autosizeMaximumSecondaryAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMaximumSecondaryAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::minimumPrimaryAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->minimumPrimaryAirFlowFraction();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isMinimumPrimaryAirFlowFractionAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMinimumPrimaryAirFlowFractionAutosized();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMinimumPrimaryAirFlowFraction(minimumPrimaryAirFlowFraction);
  }

  void AirTerminalSingleDuctParallelPIUReheat::autosizeMinimumPrimaryAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMinimumPrimaryAirFlowFraction();
  }

  boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::fanOnFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->fanOnFlowFraction();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isFanOnFlowFractionAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isFanOnFlowFractionAutosized();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setFanOnFlowFraction(double fanOnFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setFanOnFlowFraction(fanOnFlowFraction);
  }

  void AirTerminalSingleDuctParallelPIUReheat::autosizeFanOnFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeFanOnFlowFraction();
  }

  boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctParallelPIUReheat::resetMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
  }

  void AirTerminalSingleDuctParallelPIUReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctParallelPIUReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isMinimumHotWaterorSteamFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctParallelPIUReheat::resetMinimumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->resetMinimumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctParallelPIUReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void AirTerminalSingleDuctParallelPIUReheat::resetConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->resetConvergenceTolerance();
  }

  std::string AirTerminalSingleDuctParallelPIUReheat::fanControlType() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->fanControlType();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setFanControlType(const std::string& fanControlType) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setFanControlType(fanControlType);
  }

  double AirTerminalSingleDuctParallelPIUReheat::minimumFanTurnDownRatio() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->minimumFanTurnDownRatio();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMinimumFanTurnDownRatio(minimumFanTurnDownRatio);
  }

  std::string AirTerminalSingleDuctParallelPIUReheat::heatingControlType() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->heatingControlType();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setHeatingControlType(const std::string& heatingControlType) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setHeatingControlType(heatingControlType);
  }

  double AirTerminalSingleDuctParallelPIUReheat::designHeatingDischargeAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->designHeatingDischargeAirTemperature();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setDesignHeatingDischargeAirTemperature(
      designHeatingDischargeAirTemperature);
  }

  double AirTerminalSingleDuctParallelPIUReheat::highLimitHeatingDischargeAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->highLimitHeatingDischargeAirTemperature();
  }

  bool AirTerminalSingleDuctParallelPIUReheat::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setHighLimitHeatingDischargeAirTemperature(
      highLimitHeatingDischargeAirTemperature);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Owns every provisional mutation made while inserting a parallel PIU.
    // Zone-specific secondary-air and equipment projections are enrolled only
    // when the demand branch already serves a zone; a terminal-only branch has
    // primary air topology but deliberately has no invented zone state.
    class AirTerminalSingleDuctParallelPIUReheat_Impl::InsertionPlan
    {
     public:
      static std::unique_ptr<InsertionPlan> prepare(AirTerminalSingleDuctParallelPIUReheat_Impl& terminalImpl, AirLoopHVAC airLoop,
                                                    AirLoopHVACZoneSplitter splitter, unsigned branchIndex, Node outletNode,
                                                    boost::optional<ThermalZone> thermalZone, bool terminalNameAssigned) {
        auto terminal = terminalImpl.getObject<ModelObject>();
        const std::string inletNodeName = outletNode.nameString() + " - " + terminal.nameString() + " Inlet Node";
        const bool inletNodeExisted = static_cast<bool>(terminalImpl.model().getConcreteModelObjectByName<Node>(inletNodeName));
        auto inletNode = terminalImpl.model().getOrCreateTransientByName<Node>(inletNodeName);

        boost::optional<Node> secondaryNode;
        bool secondaryNodeExisted = false;
        if (thermalZone) {
          const std::string secondaryNodeName = outletNode.nameString() + " - " + terminal.nameString() + " Secondary Air Inlet Node";
          secondaryNodeExisted = static_cast<bool>(terminalImpl.model().getConcreteModelObjectByName<Node>(secondaryNodeName));
          secondaryNode = terminalImpl.model().getOrCreateTransientByName<Node>(secondaryNodeName);
        }

        auto plan = std::unique_ptr<InsertionPlan>(
          new InsertionPlan(terminalImpl, std::move(airLoop), std::move(splitter), branchIndex, std::move(outletNode), std::move(inletNode),
                            !inletNodeExisted, std::move(thermalZone), std::move(secondaryNode), !secondaryNodeExisted, terminalNameAssigned));
        if (!plan->prepareTopology()) {
          return nullptr;
        }
        return plan;
      }

      InsertionPlan(const InsertionPlan&) = delete;
      InsertionPlan& operator=(const InsertionPlan&) = delete;
      InsertionPlan(InsertionPlan&& other) noexcept
        : m_state(other.m_state),
          m_terminalImpl(other.m_terminalImpl),
          m_airLoop(std::move(other.m_airLoop)),
          m_splitter(std::move(other.m_splitter)),
          m_branchIndex(other.m_branchIndex),
          m_outletNode(std::move(other.m_outletNode)),
          m_inletNode(std::move(other.m_inletNode)),
          m_inletNodeCreated(other.m_inletNodeCreated),
          m_thermalZone(std::move(other.m_thermalZone)),
          m_secondaryNode(std::move(other.m_secondaryNode)),
          m_secondaryNodeCreated(other.m_secondaryNodeCreated),
          m_zoneConnections(std::move(other.m_zoneConnections)),
          m_airDistributionUnit(std::move(other.m_airDistributionUnit)),
          m_previousADUOutletTarget(std::move(other.m_previousADUOutletTarget)),
          m_previousADUOutletNodeName(std::move(other.m_previousADUOutletNodeName)),
          m_previousFanAvailabilityTarget(std::move(other.m_previousFanAvailabilityTarget)),
          m_previousFanAvailabilityRaw(std::move(other.m_previousFanAvailabilityRaw)),
          m_fanAvailabilityField(other.m_fanAvailabilityField),
          m_terminalNameAssigned(other.m_terminalNameAssigned),
          m_fanAvailabilityUpdateAttempted(other.m_fanAvailabilityUpdateAttempted),
          m_splitterRewired(other.m_splitterRewired),
          m_inletAssigned(other.m_inletAssigned),
          m_outletAssigned(other.m_outletAssigned),
          m_secondaryAssigned(other.m_secondaryAssigned),
          m_exhaustRegistered(other.m_exhaustRegistered),
          m_aduUpdated(other.m_aduUpdated),
          m_zoneRegistered(other.m_zoneRegistered) {
        other.m_state = State::MovedFrom;
      }
      InsertionPlan& operator=(InsertionPlan&&) = delete;

      ~InsertionPlan() {
        if (m_state == State::Prepared) {
          cleanupPreparedState();
        }
      }

      void commit() {
        OS_ASSERT(m_state == State::Prepared);
        m_state = State::Committed;
      }

     private:
      enum class State
      {
        Prepared,
        Committed,
        MovedFrom,
      };

      InsertionPlan(AirTerminalSingleDuctParallelPIUReheat_Impl& terminalImpl, AirLoopHVAC airLoop, AirLoopHVACZoneSplitter splitter,
                    unsigned branchIndex, Node outletNode, Node inletNode, bool inletNodeCreated, boost::optional<ThermalZone> thermalZone,
                    boost::optional<Node> secondaryNode, bool secondaryNodeCreated, bool terminalNameAssigned)
        : m_terminalImpl(&terminalImpl),
          m_airLoop(std::move(airLoop)),
          m_splitter(std::move(splitter)),
          m_branchIndex(branchIndex),
          m_outletNode(std::move(outletNode)),
          m_inletNode(std::move(inletNode)),
          m_inletNodeCreated(inletNodeCreated),
          m_thermalZone(std::move(thermalZone)),
          m_secondaryNode(std::move(secondaryNode)),
          m_secondaryNodeCreated(secondaryNodeCreated),
          m_terminalNameAssigned(terminalNameAssigned) {}

      bool prepareTopology() {
        auto terminal = m_terminalImpl->getObject<ModelObject>();
        if (m_thermalZone) {
          auto zoneImpl = m_thermalZone->getImpl<detail::ThermalZone_Impl>();
          OS_ASSERT(zoneImpl);
          m_zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
          m_airDistributionUnit = m_terminalImpl->zoneHVACAirDistributionUnit();
          if (m_airDistributionUnit) {
            m_previousADUOutletNodeName =
              m_airDistributionUnit->getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
            if (auto target = m_airDistributionUnit->getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName)) {
              m_previousADUOutletTarget = target->optionalCast<ModelObject>();
            }
          }
        }

        m_splitterRewired = true;
        if (!m_splitter.setOutletModelObject(m_branchIndex, m_inletNode.cast<ModelObject>())) {
          return false;
        }

        m_inletAssigned = true;
        if (!m_terminalImpl->setPointer(m_terminalImpl->inletPort(), m_inletNode.handle(), false)) {
          return false;
        }
        m_outletAssigned = true;
        if (!m_terminalImpl->setPointer(m_terminalImpl->outletPort(), m_outletNode.handle(), false)) {
          return false;
        }

        auto fanObject = m_terminalImpl->fan();
        m_fanAvailabilityField = fanAvailabilityScheduleField(fanObject);
        if (!m_fanAvailabilityField) {
          return false;
        }
        if (const auto originalField = fanObject.getField(*m_fanAvailabilityField, false)) {
          const auto targetHandle = toUUID(*originalField);
          if (!targetHandle.isNull()) {
            if (auto target = fanObject.model().getObject(targetHandle)) {
              m_previousFanAvailabilityTarget = target->optionalCast<ModelObject>();
            }
          }
        }
        if (!m_previousFanAvailabilityTarget) {
          auto workspaceImpl = fanObject.getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(workspaceImpl);
          m_previousFanAvailabilityRaw = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(*m_fanAvailabilityField, false, true);
        }
        m_fanAvailabilityUpdateAttempted = true;
        auto loopAvailability = m_airLoop.availabilitySchedule();
        if (!syncFanAvailabilityWithLoop(fanObject, loopAvailability)) {
          return false;
        }

        if (!m_thermalZone) {
          return true;
        }

        OS_ASSERT(m_secondaryNode && m_zoneConnections);
        m_secondaryAssigned = true;
        if (!m_terminalImpl->setPointer(m_terminalImpl->secondaryAirInletPort(), m_secondaryNode->handle(), false)) {
          return false;
        }

        const auto originalExhaustNodes = m_zoneConnections->zoneAirExhaustNodes();
        const bool wasExhaustRegistered = std::ranges::find(originalExhaustNodes, *m_secondaryNode) != originalExhaustNodes.end();
        const bool exhaustResult = m_zoneConnections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->addZoneAirExhaustNode(*m_secondaryNode);
        const auto currentExhaustNodes = m_zoneConnections->zoneAirExhaustNodes();
        m_exhaustRegistered = !wasExhaustRegistered && (std::ranges::find(currentExhaustNodes, *m_secondaryNode) != currentExhaustNodes.end());
        if (!exhaustResult) {
          return false;
        }

        if (m_airDistributionUnit) {
          m_aduUpdated = true;
          if (!m_airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(m_outletNode)) {
            return false;
          }
        }

        const auto originalEquipment = m_thermalZone->equipment();
        const bool wasZoneRegistered = std::ranges::find(originalEquipment, terminal) != originalEquipment.end();
        const bool zoneResult = registerTerminalWithZone(*m_thermalZone, terminal);
        const auto currentEquipment = m_thermalZone->equipment();
        m_zoneRegistered = !wasZoneRegistered && (std::ranges::find(currentEquipment, terminal) != currentEquipment.end());
        return zoneResult;
      }

      void cleanupPreparedState() {
        auto terminal = m_terminalImpl->getObject<ModelObject>();
        if (m_zoneRegistered && m_thermalZone) {
          const bool removed = unregisterTerminalFromZone(*m_thermalZone, terminal);
          OS_ASSERT(removed);
          (void)removed;
        }
        if (m_aduUpdated && m_airDistributionUnit) {
          auto aduImpl = m_airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
          OS_ASSERT(aduImpl);
          const bool restored =
            m_previousADUOutletTarget ? aduImpl->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName,
                                                            m_previousADUOutletTarget->handle(), false)
            : m_previousADUOutletNodeName
              ? aduImpl->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, *m_previousADUOutletNodeName,
                                   false)
              : aduImpl->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, Handle(), false);
          OS_ASSERT(restored);
          (void)restored;
        }
        if (m_exhaustRegistered && m_zoneConnections && m_secondaryNode) {
          const bool removed = m_zoneConnections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeZoneAirExhaustNode(*m_secondaryNode);
          OS_ASSERT(removed);
          (void)removed;
        }
        if (m_secondaryAssigned) {
          const bool cleared = m_terminalImpl->setPointer(m_terminalImpl->secondaryAirInletPort(), openstudio::Handle(), false);
          OS_ASSERT(cleared);
          (void)cleared;
        }
        if (m_outletAssigned) {
          const bool cleared = m_terminalImpl->setPointer(m_terminalImpl->outletPort(), openstudio::Handle(), false);
          OS_ASSERT(cleared);
          (void)cleared;
        }
        if (m_inletAssigned) {
          const bool cleared = m_terminalImpl->setPointer(m_terminalImpl->inletPort(), openstudio::Handle(), false);
          OS_ASSERT(cleared);
          (void)cleared;
        }
        if (m_splitterRewired) {
          const bool restored = m_splitter.setOutletModelObject(m_branchIndex, m_outletNode.cast<ModelObject>());
          OS_ASSERT(restored);
          (void)restored;
        }
        if (m_secondaryNodeCreated && m_secondaryNode && m_terminalImpl->model().getObject(m_secondaryNode->handle())) {
          m_secondaryNode->remove();
        }
        if (m_inletNodeCreated && m_terminalImpl->model().getObject(m_inletNode.handle())) {
          m_inletNode.remove();
        }
        if (m_fanAvailabilityUpdateAttempted && m_fanAvailabilityField) {
          auto fanObject = m_terminalImpl->fan();
          auto fanImpl = fanObject.getImpl<detail::ModelObject_Impl>();
          OS_ASSERT(fanImpl);
          bool restored = false;
          if (m_previousFanAvailabilityTarget) {
            restored = fanImpl->setPointer(*m_fanAvailabilityField, m_previousFanAvailabilityTarget->handle(), false);
          } else if (m_previousFanAvailabilityRaw) {
            const bool cleared = fanImpl->setPointer(*m_fanAvailabilityField, Handle(), false);
            const bool rawRestored =
              fanImpl->openstudio::detail::IdfObject_Impl::setString(*m_fanAvailabilityField, *m_previousFanAvailabilityRaw, false);
            restored = cleared && rawRestored;
          } else {
            restored = fanImpl->setPointer(*m_fanAvailabilityField, Handle(), false);
          }
          OS_ASSERT(restored);
          (void)restored;
        }
        if (m_terminalNameAssigned) {
          auto workspaceImpl = terminal.getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(workspaceImpl);
          const bool restored = static_cast<bool>(workspaceImpl->setName("", false));
          OS_ASSERT(restored);
          (void)restored;
        }
      }

      State m_state = State::Prepared;
      AirTerminalSingleDuctParallelPIUReheat_Impl* m_terminalImpl;
      AirLoopHVAC m_airLoop;
      AirLoopHVACZoneSplitter m_splitter;
      unsigned m_branchIndex;
      Node m_outletNode;
      Node m_inletNode;
      bool m_inletNodeCreated;
      boost::optional<ThermalZone> m_thermalZone;
      boost::optional<Node> m_secondaryNode;
      bool m_secondaryNodeCreated;
      boost::optional<ZoneHVACEquipmentConnections> m_zoneConnections;
      boost::optional<ZoneHVACAirDistributionUnit> m_airDistributionUnit;
      boost::optional<ModelObject> m_previousADUOutletTarget;
      boost::optional<std::string> m_previousADUOutletNodeName;
      boost::optional<ModelObject> m_previousFanAvailabilityTarget;
      boost::optional<std::string> m_previousFanAvailabilityRaw;
      boost::optional<unsigned> m_fanAvailabilityField;
      bool m_terminalNameAssigned = false;
      bool m_fanAvailabilityUpdateAttempted = false;
      bool m_splitterRewired = false;
      bool m_inletAssigned = false;
      bool m_outletAssigned = false;
      bool m_secondaryAssigned = false;
      bool m_exhaustRegistered = false;
      bool m_aduUpdated = false;
      bool m_zoneRegistered = false;
    };

    Schedule AirTerminalSingleDuctParallelPIUReheat_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctParallelPIUReheat", "Availability", schedule);
    }

    HVACComponent AirTerminalSingleDuctParallelPIUReheat_Impl::fan() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName);
      OS_ASSERT(fan);
      return *fan;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setFan(HVACComponent& hvacComponent) {
      if ((hvacComponent.model() != model()) || !isSupportedParallelPIUFan(hvacComponent)) {
        return false;
      }
      auto terminal = getObject<ModelObject>();
      auto previousFan = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName);
      if (previousFan && previousFan->handle() == hvacComponent.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = hvacComponent.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      const auto newFanType = hvacComponent.iddObject().type();
      const auto previousFanControlType = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType, false, true);
      auto rollbackFanAssignment = [&]() {
        if (newFanType == IddObjectType::Fan_ConstantVolume) {
          OS_ASSERT(hvacComponent.setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(hvacComponent.setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
        } else if (newFanType == IddObjectType::Fan_SystemModel) {
          OS_ASSERT(hvacComponent.setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
          OS_ASSERT(hvacComponent.setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
        }
        OS_ASSERT(
          setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, previousFan ? previousFan->handle() : Handle(), false));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType, previousFanControlType.value_or("")));
        OS_ASSERT(maintainContainedAirPath());
      };
      if (newFanType == IddObjectType::Fan_ConstantVolume) {
        if (hvacComponent.getTarget(openstudio::Fan_ConstantVolumeFields::AirInletNodeName)
            || hvacComponent.getTarget(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)) {
          return false;
        }
      } else if (newFanType == IddObjectType::Fan_SystemModel) {
        if (hvacComponent.getTarget(openstudio::Fan_SystemModelFields::AirInletNodeName)
            || hvacComponent.getTarget(openstudio::Fan_SystemModelFields::AirOutletNodeName)) {
          return false;
        }
      }
      if (previousFan) {
        const auto previousType = previousFan->iddObject().type();
        if (previousType == IddObjectType::Fan_ConstantVolume) {
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Fan_SystemModel) {
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousFan->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
        }
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, hvacComponent.handle(), false)) {
        rollbackFanAssignment();
        return false;
      }

      if (newFanType == IddObjectType::Fan_ConstantVolume || newFanType == IddObjectType::OS_Fan_ConstantVolume) {
        if (!setFanControlType("ConstantSpeed")) {
          rollbackFanAssignment();
          return false;
        }
      }
      if (!maintainContainedAirPath()) {
        rollbackFanAssignment();
        return false;
      }
      return true;
    }

    HVACComponent AirTerminalSingleDuctParallelPIUReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setReheatCoil(HVACComponent& hvacComponent) {
      if ((hvacComponent.model() != model()) || !isSupportedParallelPIUReheatCoil(hvacComponent)) {
        return false;
      }
      auto terminal = getObject<ModelObject>();
      auto previousCoil = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      if (previousCoil && previousCoil->handle() == hvacComponent.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = hvacComponent.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      const auto newCoilType = hvacComponent.iddObject().type();
      if ((newCoilType == IddObjectType::Coil_Heating_Electric
           && (hvacComponent.getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)
               || hvacComponent.getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName)))
          || (newCoilType == IddObjectType::Coil_Heating_Fuel
              && (hvacComponent.getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName)
                  || hvacComponent.getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName)))
          || (newCoilType == IddObjectType::Coil_Heating_Water
              && (hvacComponent.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName)
                  || hvacComponent.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)))) {
        return false;
      }
      if (previousCoil) {
        const auto previousType = previousCoil->iddObject().type();
        if (previousType == IddObjectType::Coil_Heating_Electric) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Coil_Heating_Fuel) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (previousType == IddObjectType::Coil_Heating_Water) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, hvacComponent.handle(), false)) {
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        if (previousCoil) {
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      if (!maintainContainedAirPath()) {
        if (newCoilType == IddObjectType::Coil_Heating_Electric) {
          OS_ASSERT(hvacComponent.setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(hvacComponent.setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (newCoilType == IddObjectType::Coil_Heating_Fuel) {
          OS_ASSERT(hvacComponent.setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(hvacComponent.setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (newCoilType == IddObjectType::Coil_Heating_Water) {
          OS_ASSERT(hvacComponent.setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(hvacComponent.setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      return true;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::doCanonicalize(LoadContext& context) {
      if (!repairContainedAirPath(context)) {
        detail::addLoadError(context, "Failed to repair contained air path for AirTerminal:SingleDuct:ParallelPIU:Reheat '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto terminal = getObject<ModelObject>();
      auto fanComponent = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName);
      auto reheatComponent =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      if (fanComponent && context) {
        const auto type = fanComponent->iddObject().type();
        const bool supported = (type == IddObjectType::Fan_ConstantVolume) || (type == IddObjectType::Fan_SystemModel);
        const auto owner = fanComponent->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " fan reference from AirTerminal:SingleDuct:ParallelPIU:Reheat '" + terminal.nameString() + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, Handle(), false));
          fanComponent = boost::none;
        }
      }
      if (reheatComponent && context) {
        const auto type = reheatComponent->iddObject().type();
        const bool supported =
          (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel) || (type == IddObjectType::Coil_Heating_Water);
        const auto owner = reheatComponent->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " reheat-coil reference from AirTerminal:SingleDuct:ParallelPIU:Reheat '" + terminal.nameString()
                                             + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, Handle(), false));
          reheatComponent = boost::none;
        }
      }
      if (!fanComponent || !reheatComponent) {
        if ((fanComponent && !isSupportedParallelPIUFan(*fanComponent)) || (reheatComponent && !isSupportedParallelPIUReheatCoil(*reheatComponent))) {
          return false;
        }
        const bool hadExternalTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                                         || static_cast<bool>(resolvedNodeTarget(secondaryAirInletPort()))
                                         || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal))
                                         || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology) {
          // An incomplete air terminal may still own a valid plant-connected
          // reheat coil. Remove only its air/zone projection here.
          const bool detached = detachIncompleteParallelPIUAirTopologyForRepair(terminal, fanComponent, reheatComponent);
          if (!detached) {
            detail::addLoadError(*context, "Could not detach incomplete AirTerminal:SingleDuct:ParallelPIU:Reheat '" + terminal.nameString()
                                             + "' from its external topology.");
            return false;
          }
        }
        bool changed = false;
        std::vector<Node> orphanCandidates;
        if (fanComponent) {
          const auto type = fanComponent->iddObject().type();
          if (type == IddObjectType::Fan_ConstantVolume) {
            if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)) {
              orphanCandidates.push_back(*node);
            }
            changed = changed || static_cast<bool>(fanComponent->getTarget(openstudio::Fan_ConstantVolumeFields::AirInletNodeName))
                      || !orphanCandidates.empty();
            OS_ASSERT(fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
            OS_ASSERT(fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
          } else if (type == IddObjectType::Fan_SystemModel) {
            if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName)) {
              orphanCandidates.push_back(*node);
            }
            changed =
              changed || static_cast<bool>(fanComponent->getTarget(openstudio::Fan_SystemModelFields::AirInletNodeName)) || !orphanCandidates.empty();
            OS_ASSERT(fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
            OS_ASSERT(fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
          } else {
            return false;
          }
        }
        if (reheatComponent) {
          const auto type = reheatComponent->iddObject().type();
          if (type == IddObjectType::Coil_Heating_Electric) {
            if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)) {
              orphanCandidates.push_back(*node);
            }
            changed = changed || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));
            OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
            OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
          } else if (type == IddObjectType::Coil_Heating_Fuel) {
            if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName)) {
              orphanCandidates.push_back(*node);
            }
            changed = changed || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName));
            OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
            OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
          } else if (type == IddObjectType::Coil_Heating_Water) {
            if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)) {
              orphanCandidates.push_back(*node);
            }
            changed = changed || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
            OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
            OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
          } else {
            return false;
          }
          OS_ASSERT(
            setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilObjectType, reheatComponent->iddObject().name()));
        } else {
          changed =
            changed || !getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilObjectType, true).value_or("").empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilObjectType, ""));
        }
        if (!fanComponent) {
          const auto previousFanName = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, false, true).value_or("");
          changed = changed || !previousFanName.empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, ""));
        }
        if (!reheatComponent) {
          const auto previousCoilName =
            getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, false, true).value_or("");
          changed = changed || !previousCoilName.empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, ""));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName)) {
          changed = true;
          auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>();
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName, Handle(), false));
          if (oldMixer) {
            const bool exclusivelyOwned =
              std::ranges::all_of(oldMixer->sources(), [&terminal](const auto& source) { return source.handle() == terminal.handle(); });
            if (exclusivelyOwned) {
              oldMixer->remove();
            }
          }
        }
        for (auto& node : orphanCandidates) {
          if (node.sources().empty() && model().getObject(node.handle())) {
            node.remove();
          }
        }
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(secondaryAirInletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if ((changed || hadExternalTopology) && context) {
          detail::addLoadWarning(*context, "Detached incomplete AirTerminal:SingleDuct:ParallelPIU:Reheat '" + terminal.nameString()
                                             + "' and cleared its unresolved child references.");
        }
        return true;
      }
      const auto fanType = fanComponent->iddObject().type();
      const auto coilType = reheatComponent->iddObject().type();
      if (((fanType != IddObjectType::Fan_ConstantVolume) && (fanType != IddObjectType::Fan_SystemModel))
          || ((coilType != IddObjectType::Coil_Heating_Electric) && (coilType != IddObjectType::Coil_Heating_Fuel)
              && (coilType != IddObjectType::Coil_Heating_Water))) {
        return false;
      }
      bool changed = false;
      const auto storedCoilType = terminal.getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilObjectType);
      changed = !storedCoilType || !openstudio::istringEqual(*storedCoilType, reheatComponent->iddObject().name());
      if (!setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilObjectType, reheatComponent->iddObject().name())) {
        return false;
      }

      auto supplyNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName);
      auto secondaryNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName);
      auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName);
      if (!supplyNode || !secondaryNode || !outletNode) {
        boost::optional<Node> fanOutletNode;
        boost::optional<Node> mixerOutletNode;
        if (fanType == IddObjectType::Fan_ConstantVolume) {
          fanOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName);
          changed = changed || static_cast<bool>(fanComponent->getTarget(openstudio::Fan_ConstantVolumeFields::AirInletNodeName))
                    || static_cast<bool>(fanOutletNode);
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, Handle()));
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, Handle()));
        } else {
          fanOutletNode = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName);
          changed = changed || static_cast<bool>(fanComponent->getTarget(openstudio::Fan_SystemModelFields::AirInletNodeName))
                    || static_cast<bool>(fanOutletNode);
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, Handle()));
          OS_ASSERT(fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, Handle()));
        }
        if (coilType == IddObjectType::Coil_Heating_Electric) {
          mixerOutletNode = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName);
          changed = changed || static_cast<bool>(mixerOutletNode)
                    || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
          mixerOutletNode = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName);
          changed = changed || static_cast<bool>(mixerOutletNode)
                    || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else {
          mixerOutletNode = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
          changed = changed || static_cast<bool>(mixerOutletNode)
                    || static_cast<bool>(reheatComponent->getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName)) {
          changed = true;
          if (auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>()) {
            bool exclusivelyOwned = true;
            for (const auto& source : oldMixer->sources()) {
              if (source.handle() != terminal.handle()) {
                exclusivelyOwned = false;
                break;
              }
            }
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName, Handle(), false));
            if (exclusivelyOwned) {
              oldMixer->remove();
            }
          } else {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName, Handle(), false));
          }
        }
        if (fanOutletNode && fanOutletNode->sources().empty()) {
          fanOutletNode->remove();
        }
        if (mixerOutletNode && mixerOutletNode->sources().empty()) {
          mixerOutletNode->remove();
        }
        if (changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ParallelPIU:Reheat '" + terminal.nameString() + "'.");
        }
        return true;
      }
      if (!terminal.name() && !terminal.createName()) {
        return false;
      }
      const auto baseName = terminal.nameString();

      boost::optional<AirLoopHVACZoneMixer> mixer;
      if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName)) {
        mixer = target->optionalCast<AirLoopHVACZoneMixer>();
      }
      if (mixer) {
        for (const auto& source : mixer->sources()) {
          if (source.handle() != terminal.handle()) {
            mixer = boost::none;
            changed = true;
            break;
          }
        }
      }

      std::vector<Node> displacedNodeCandidates;
      if (fanType == IddObjectType::Fan_ConstantVolume) {
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else if (fanType == IddObjectType::Fan_SystemModel) {
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      }
      if (coilType == IddObjectType::Coil_Heating_Electric) {
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      } else {
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
      }
      if (mixer) {
        if (auto node = mixer->getModelObjectTarget<Node>(mixer->outletPort())) {
          displacedNodeCandidates.push_back(*node);
        }
        for (const auto& inlet : mixer->inletModelObjects()) {
          if (auto node = inlet.optionalCast<Node>()) {
            displacedNodeCandidates.push_back(*node);
          }
        }
      }

      boost::optional<Node> fanOutletNode;
      boost::optional<Node> mixerOutletNode;
      if (allowChildNodeRecovery && mixer) {
        const auto mixerInlets = mixer->inletModelObjects();
        const auto currentFanOutlet = fanType == IddObjectType::Fan_ConstantVolume
                                        ? fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName)
                                        : fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName);
        if (!mixerInlets.empty() && currentFanOutlet && mixerInlets[0] == currentFanOutlet->cast<ModelObject>() && *currentFanOutlet != *supplyNode
            && *currentFanOutlet != *secondaryNode && *currentFanOutlet != *outletNode) {
          fanOutletNode = currentFanOutlet;
        }
        const auto currentMixerOutlet = mixer->getModelObjectTarget<Node>(mixer->outletPort());
        const auto currentCoilInlet = coilType == IddObjectType::Coil_Heating_Electric
                                        ? reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)
                                      : coilType == IddObjectType::Coil_Heating_Fuel
                                        ? reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName)
                                        : reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
        if (currentMixerOutlet && currentCoilInlet && *currentMixerOutlet == *currentCoilInlet && *currentMixerOutlet != *supplyNode
            && *currentMixerOutlet != *secondaryNode && *currentMixerOutlet != *outletNode) {
          mixerOutletNode = currentMixerOutlet;
        }
      }
      if (!fanOutletNode) {
        fanOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Fan Outlet");
      }
      if (!mixerOutletNode) {
        mixerOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Mixer Outlet");
      }
      if (!mixer) {
        mixer = AirLoopHVACZoneMixer(model());
        changed = true;
        if (!mixer->setName(baseName + " Mixer")
            || !setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ZoneMixerName, mixer->handle(), false)) {
          return false;
        }
      }
      auto mixerImpl = mixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
      OS_ASSERT(mixerImpl);
      const auto previousMixerInlets = mixer->inletModelObjects();
      const auto previousMixerOutlet = mixer->getModelObjectTarget<Node>(mixer->outletPort());
      changed = changed || !previousMixerOutlet || *previousMixerOutlet != *mixerOutletNode || previousMixerInlets.size() != 2u
                || previousMixerInlets[0] != fanOutletNode->cast<ModelObject>() || previousMixerInlets[1] != supplyNode->cast<ModelObject>();
      if (!mixerImpl->setOutletNode(*mixerOutletNode) || !mixer->setInletModelObject(0u, fanOutletNode->cast<ModelObject>())
          || !mixer->setInletModelObject(1u, supplyNode->cast<ModelObject>())) {
        return false;
      }
      while (mixer->inletModelObjects().size() > 2u) {
        auto displacedNode = mixer->inletModelObjects().back().optionalCast<Node>();
        mixer->removePortForBranch(static_cast<unsigned>(mixer->inletModelObjects().size() - 1u));
        if (displacedNode && displacedNode->sources().empty() && model().getObject(displacedNode->handle())) {
          displacedNode->remove();
        }
      }

      if (fanType == IddObjectType::Fan_ConstantVolume) {
        changed = changed || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName) != secondaryNode
                  || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName) != fanOutletNode;
        if (!fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirInletNodeName, secondaryNode->handle())
            || !fanComponent->setPointer(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName, fanOutletNode->handle())) {
          return false;
        }
      } else if (fanType == IddObjectType::Fan_SystemModel) {
        changed = changed || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName) != secondaryNode
                  || fanComponent->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName) != fanOutletNode;
        if (!fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, secondaryNode->handle())
            || !fanComponent->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, fanOutletNode->handle())) {
          return false;
        }
      }

      bool result = false;
      if (coilType == IddObjectType::Coil_Heating_Electric) {
        changed = changed || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName) != mixerOutletNode
                  || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName) != outletNode;
        result = reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, mixerOutletNode->handle())
                 && reheatComponent->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, outletNode->handle());
      } else if (coilType == IddObjectType::Coil_Heating_Fuel) {
        changed = changed || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName) != mixerOutletNode
                  || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName) != outletNode;
        result = reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, mixerOutletNode->handle())
                 && reheatComponent->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, outletNode->handle());
      } else {
        changed = changed || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName) != mixerOutletNode
                  || reheatComponent->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName) != outletNode;
        result = reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, mixerOutletNode->handle())
                 && reheatComponent->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, outletNode->handle());
      }
      if (result) {
        for (auto& displacedNode : displacedNodeCandidates) {
          if (displacedNode == *supplyNode || displacedNode == *secondaryNode || displacedNode == *outletNode || displacedNode == *fanOutletNode
              || displacedNode == *mixerOutletNode) {
            continue;
          }
          if (model().getObject(displacedNode.handle()) && displacedNode.sources().empty()) {
            displacedNode.remove();
          }
        }
      }
      if (result && changed && context) {
        detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:ParallelPIU:Reheat '" + terminal.nameString() + "'.");
      }
      return result;
    }

    boost::optional<Node> AirTerminalSingleDuctParallelPIUReheat_Impl::secondaryAirInletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(
        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName);
    }

    boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::maximumPrimaryAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, true);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMaximumPrimaryAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, maximumPrimaryAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMaximumPrimaryAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::maximumSecondaryAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, true);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMaximumSecondaryAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, maximumSecondaryAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMaximumSecondaryAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::minimumPrimaryAirFlowFraction() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMinimumPrimaryAirFlowFractionAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, minimumPrimaryAirFlowFraction);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMinimumPrimaryAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::fanOnFlowFraction() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, true);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isFanOnFlowFractionAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setFanOnFlowFraction(double fanOnFlowFraction) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, fanOnFlowFraction);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeFanOnFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, maximumHotWaterorSteamFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctParallelPIUReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::resetMinimumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, ""));
    }

    double AirTerminalSingleDuctParallelPIUReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    void AirTerminalSingleDuctParallelPIUReheat_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, ""));
    }

    std::string AirTerminalSingleDuctParallelPIUReheat_Impl::fanControlType() const {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setFanControlType(const std::string& fanControlType) {
      auto fanComponent =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName);
      if (fanComponent
          && ((fanComponent->iddObject().type() == IddObjectType::Fan_ConstantVolume)
              || (fanComponent->iddObject().type() == IddObjectType::OS_Fan_ConstantVolume))
          && istringEqual(fanControlType, "VariableSpeed")) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "Rejecting VariableSpeed fan control for a constant-volume fan on " << briefDescription() << ".");
        return false;
      }

      return setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType, fanControlType);
    }

    double AirTerminalSingleDuctParallelPIUReheat_Impl::minimumFanTurnDownRatio() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumFanTurnDownRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumFanTurnDownRatio, minimumFanTurnDownRatio);
    }

    std::string AirTerminalSingleDuctParallelPIUReheat_Impl::heatingControlType() const {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HeatingControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setHeatingControlType(const std::string& heatingControlType) {
      return setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HeatingControlType, heatingControlType);
    }

    double AirTerminalSingleDuctParallelPIUReheat_Impl::designHeatingDischargeAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::DesignHeatingDischargeAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::DesignHeatingDischargeAirTemperature,
                       designHeatingDischargeAirTemperature);
    }

    double AirTerminalSingleDuctParallelPIUReheat_Impl::highLimitHeatingDischargeAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature,
                       highLimitHeatingDischargeAirTemperature);
    }

    std::vector<ModelObject> AirTerminalSingleDuctParallelPIUReheat_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto reheat = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName)) {
        result.push_back(*reheat);
      }
      if (auto fanComponent =
            getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName)) {
        result.push_back(*fanComponent);
      }
      return result;
    }

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctParallelPIUReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::isRemovable() const {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }

      auto terminalObject = getObject<ModelObject>();
      auto terminal = terminalObject.cast<StraightComponent>();
      const auto reheat =
        terminalObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      const bool hasAirTopology = SingleDuctTerminalRemovalPlan::hasTopology(terminal) || parallelPIUHasContainedTopology(terminalObject);
      const bool hasPlantTopology = reheat && reheat->plantLoop();
      if (!hasAirTopology && !hasPlantTopology) {
        return true;
      }

      if (!prepareParallelPIUTopologyRemoval(terminalObject)) {
        return false;
      }
      if (reheat) {
        if (auto waterCoil = reheat->optionalCast<CoilHeatingWater>()) {
          if (auto plantLoop = waterCoil->plantLoop()) {
            auto plantLoopImpl = plantLoop->getImpl<PlantLoop_Impl>();
            OS_ASSERT(plantLoopImpl);
            return static_cast<bool>(plantLoopImpl->prepareCoilHeatingWaterDemandBranchRemoval(*waterCoil));
          }
        } else if (reheat->plantLoop()) {
          return false;
        }
      }
      return true;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctParallelPIUReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thisModel = model();
      const auto thisHandle = thisObject.handle();
      const auto ownedChildren = children();

      if (!removeFromLoop()) {
        const auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
          openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
        if (SingleDuctTerminalRemovalPlan::hasTopology(thisObject.cast<StraightComponent>()) || parallelPIUHasContainedTopology(thisObject)
            || (reheat && reheat->plantLoop())) {
          return {};
        }
      }
      if (!maintainContainedAirPath()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty() || thisModel.getObject(thisHandle)) {
        return {};
      }

      for (auto child : ownedChildren) {
        if (thisModel.getObject(child.handle())) {
          auto removedChild = child.remove();
          result.insert(result.end(), removedChild.begin(), removedChild.end());
        }
      }
      return result;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto terminal = thisObject.cast<StraightComponent>();
      auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      const bool hasAirTopology = SingleDuctTerminalRemovalPlan::hasTopology(terminal) || parallelPIUHasContainedTopology(thisObject);
      const bool hasPlantTopology = reheat && reheat->plantLoop();
      if (!hasAirTopology && !hasPlantTopology) {
        return false;
      }

      auto topologyRemovalPlans = prepareParallelPIUTopologyRemoval(thisObject);
      if (!topologyRemovalPlans) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "Refusing to remove a Parallel PIU whose contained or external topology is not exact.");
        return false;
      }

      std::unique_ptr<PlantLoop_Impl::CoilHeatingWaterDemandBranchRemovalPlan> plantRemovalPlan;
      if (reheat) {
        if (auto waterCoil = reheat->optionalCast<CoilHeatingWater>()) {
          if (auto plantLoop = waterCoil->plantLoop()) {
            auto plantLoopImpl = plantLoop->getImpl<PlantLoop_Impl>();
            OS_ASSERT(plantLoopImpl);
            plantRemovalPlan = plantLoopImpl->prepareCoilHeatingWaterDemandBranchRemoval(*waterCoil);
            if (!plantRemovalPlan) {
              return false;
            }
          }
        } else if (reheat->plantLoop()) {
          return false;
        }
      }

      if (plantRemovalPlan) {
        plantRemovalPlan->commit();
      }
      topologyRemovalPlans->containedAirPath->commit();
      if (topologyRemovalPlans->externalTopology) {
        topologyRemovalPlans->externalTopology->commit();
      }
      return true;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires a node in the same model as the parallel PIU terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop() || inletModelObject() || outletModelObject() || secondaryAirInletNode()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "Refusing to add an already-connected parallel PIU terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto resolvedOutletNode = AirLoopHVAC_Impl::resolveSingleDuctTerminalAttachmentNode(node);
      if (!resolvedOutletNode) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires a unique terminal-free single-duct branch for the requested outlet node.");
        return false;
      }
      auto& insertionOutletNode = *resolvedOutletNode;

      auto airLoop = insertionOutletNode.airLoopHVAC();
      OS_ASSERT(airLoop);

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = insertionOutletNode.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(insertionOutletNode);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForZoneNode(model(), insertionOutletNode);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      const auto fanComponent = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName);
      const auto reheatComponent =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      if (!fanComponent || !reheatComponent) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires both the fan and reheat coil relationships to be established before insertion.");
        return false;
      }
      const auto originalName = thisObject.name();
      const bool terminalNameAssigned = !originalName || originalName->empty();
      if (terminalNameAssigned) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto insertion =
        InsertionPlan::prepare(*this, *airLoop, zoneSplitter, splitterBranchIndex, insertionOutletNode, thermalZone, terminalNameAssigned);
      if (!insertion) {
        return false;
      }
      if (testFailurePointReached(model(), TestFailurePoint::ParallelPIUAfterTopologyPrepared)) {
        return false;
      }
      if (!maintainContainedAirPath()) {
        insertion.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      insertion->commit();
      return true;
    }

    unsigned AirTerminalSingleDuctParallelPIUReheat_Impl::secondaryAirInletPort() const {
      return openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName;
    }

    std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat_Impl::fanControlTypeValues() const {
      return openstudio::epmodel::AirTerminalSingleDuctParallelPIUReheat::fanControlTypeValues();
    }

    std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat_Impl::heatingControlTypeValues() const {
      return openstudio::epmodel::AirTerminalSingleDuctParallelPIUReheat::heatingControlTypeValues();
    }

    unsigned AirTerminalSingleDuctParallelPIUReheat_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctParallelPIUReheat_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
