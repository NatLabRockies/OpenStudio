/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"
#include "StraightComponent/CompoundTerminalTopologyInspection.hpp"
#include "StraightComponent/SingleDuctTerminalRemovalPlan.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "HVACComponent/HVACComponent_Impl.hpp"
#include "HVACComponent/ControllerWaterCoil.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/Branch.hpp"
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
#include "Node_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <iterator>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace {

    using detail::existingNodeCollectionField;
    using detail::existingNodeField;
    using detail::existingNodeRows;
    using detail::existingObjectField;
    using detail::hasExactSources;
    using detail::isSoleOwnedChild;

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
    }

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeFourPipeInduction& terminal) {
      terminal.autosizeMaximumTotalAirFlowRate();
      terminal.autosizeMaximumHotWaterFlowRate();
      terminal.autosizeMaximumColdWaterFlowRate();
      OS_ASSERT(terminal.setMinimumColdWaterFlowRate(0.0));
      OS_ASSERT(terminal.setCoolingConvergenceTolerance(0.001));
      OS_ASSERT(terminal.setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, ""));
    }

    boost::optional<ThermalZone> owningThermalZoneForBranchNode(const Model& model, const Node& node) {
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

    bool registerTerminalWithThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal);
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::find(equipment.begin(), equipment.end(), terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    bool unregisterTerminalFromThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

    boost::optional<Node> zoneExhaustNodeForThermalZone(ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);

      auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
      if (auto exhaustNode =
            zoneConnections.getModelObjectTarget<Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName)) {
        return exhaustNode;
      }

      auto exhaustNode = thermalZone.model().getOrCreateTransientByName<Node>(thermalZone.nameString() + " Exhaust Node");
      if (!zoneConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, exhaustNode.handle())) {
        return boost::none;
      }
      return exhaustNode;
    }

    bool inductionHasContainedTopology(const ModelObject& terminal) {
      if (existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName).set
          || existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName).set) {
        return true;
      }
      for (const auto& relationshipAndFields :
           {std::pair<unsigned, std::pair<unsigned, unsigned>>{
              openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName,
              {openstudio::Coil_Heating_WaterFields::AirInletNodeName, openstudio::Coil_Heating_WaterFields::AirOutletNodeName}},
            std::pair<unsigned, std::pair<unsigned, unsigned>>{
              openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName,
              {openstudio::Coil_Cooling_WaterFields::AirInletNodeName, openstudio::Coil_Cooling_WaterFields::AirOutletNodeName}}}) {
        const auto relationship = existingObjectField(terminal, relationshipAndFields.first);
        if (relationship.object
            && (existingObjectField(*relationship.object, relationshipAndFields.second.first).set
                || existingObjectField(*relationship.object, relationshipAndFields.second.second).set)) {
          return true;
        }
      }
      return false;
    }

    class InductionContainedAirPathRemovalPlan
    {
     public:
      static std::unique_ptr<InductionContainedAirPathRemovalPlan> prepare(const ModelObject& terminal) {
        const auto heatingRelationship =
          existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
        const auto coolingRelationship =
          existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
        const auto heating = heatingRelationship.object ? heatingRelationship.object->optionalCast<CoilHeatingWater>() : boost::none;
        const auto cooling = coolingRelationship.object ? coolingRelationship.object->optionalCast<CoilCoolingWater>() : boost::none;
        if (!heatingRelationship.set || !heating || (coolingRelationship.set && !cooling) || !isSoleOwnedChild(terminal, *heating)
            || (cooling && !isSoleOwnedChild(terminal, *cooling))) {
          return nullptr;
        }

        const auto heatingType =
          terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType, false, true);
        const auto coolingType =
          terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, false, true);
        if (!heatingType || !openstudio::istringEqual(*heatingType, heating->iddObject().name())
            || (cooling && (!coolingType || !openstudio::istringEqual(*coolingType, cooling->iddObject().name())))
            || (!cooling && coolingType && !coolingType->empty())) {
          return nullptr;
        }

        const auto primary =
          existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName);
        const auto induced =
          existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName);
        const auto outlet = existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName);
        const auto mixerRelationship =
          existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName);
        const auto heatingInlet = existingNodeField(*heating, openstudio::Coil_Heating_WaterFields::AirInletNodeName);
        const auto heatingOutlet = existingNodeField(*heating, openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        const auto coolingInlet =
          cooling ? existingNodeField(*cooling, openstudio::Coil_Cooling_WaterFields::AirInletNodeName) : detail::ExistingNodeField{};
        const auto coolingOutlet =
          cooling ? existingNodeField(*cooling, openstudio::Coil_Cooling_WaterFields::AirOutletNodeName) : detail::ExistingNodeField{};

        if (!primary.set && !induced.set) {
          if (outlet.set || mixerRelationship.set || heatingInlet.set || heatingOutlet.set || coolingInlet.set || coolingOutlet.set) {
            return nullptr;
          }
          return std::unique_ptr<InductionContainedAirPathRemovalPlan>(new InductionContainedAirPathRemovalPlan(terminal, *heating, cooling));
        }
        if (primary.set && !induced.set) {
          if (!primary.node || !outlet.set || !outlet.node || mixerRelationship.set || heatingInlet.set || heatingOutlet.set || coolingInlet.set
              || coolingOutlet.set) {
            return nullptr;
          }
          return std::unique_ptr<InductionContainedAirPathRemovalPlan>(new InductionContainedAirPathRemovalPlan(terminal, *heating, cooling));
        }

        const bool projectedOnly = primary.node && induced.node && outlet.node && !mixerRelationship.set && !heatingInlet.set && !heatingOutlet.set
                                   && !coolingInlet.set && !coolingOutlet.set;
        if (!projectedOnly
            && (!primary.node || !induced.node || !outlet.node || !mixerRelationship.object || !heatingInlet.node || !heatingOutlet.node
                || (cooling && (!coolingInlet.node || !coolingOutlet.node)))) {
          return nullptr;
        }

        boost::optional<AirLoopHVACZoneMixer> mixer;
        if (!projectedOnly) {
          mixer = mixerRelationship.object->optionalCast<AirLoopHVACZoneMixer>();
          if (!mixer || !hasExactSources(*mixer, {terminal.handle()})) {
            return nullptr;
          }
          const auto mixerOutlet = existingNodeField(*mixer, openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName);
          const auto mixerInlets = existingNodeRows(*mixer, openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName);
          const auto finalInducedNode = cooling ? coolingOutlet.node : heatingOutlet.node;
          if (!mixerOutlet.node || mixerOutlet.node->handle() != outlet.node->handle() || !mixerInlets.valid || mixerInlets.rows.size() != 2u
              || mixerInlets.rows[0].first != 0u || mixerInlets.rows[0].second.handle() != primary.node->handle() || mixerInlets.rows[1].first != 1u
              || !finalInducedNode || mixerInlets.rows[1].second.handle() != finalInducedNode->handle()
              || heatingInlet.node->handle() != induced.node->handle() || (cooling && coolingInlet.node->handle() != heatingOutlet.node->handle())) {
            return nullptr;
          }

          std::vector<Handle> graphNodes{primary.node->handle(), induced.node->handle(), outlet.node->handle(), heatingOutlet.node->handle()};
          if (cooling) {
            graphNodes.push_back(coolingOutlet.node->handle());
          }
          auto uniqueGraphNodes = graphNodes;
          std::ranges::sort(uniqueGraphNodes);
          std::vector<Handle> expectedHeatingOutletSources =
            cooling ? std::vector<Handle>{heating->handle(), cooling->handle()} : std::vector<Handle>{heating->handle(), mixer->handle()};
          if (heating->plantLoop()) {
            if (const auto controller = heating->controllerWaterCoil()) {
              expectedHeatingOutletSources.push_back(controller->handle());
            }
          }
          std::vector<Handle> expectedCoolingOutletSources;
          if (cooling) {
            expectedCoolingOutletSources = {cooling->handle(), mixer->handle()};
            if (cooling->plantLoop()) {
              if (const auto controller = cooling->controllerWaterCoil()) {
                expectedCoolingOutletSources.push_back(controller->handle());
              }
            }
          }
          if (std::ranges::unique(uniqueGraphNodes).begin() != uniqueGraphNodes.end()
              || !hasExactSources(*heatingOutlet.node, expectedHeatingOutletSources)
              || (cooling && !hasExactSources(*coolingOutlet.node, expectedCoolingOutletSources))) {
            return nullptr;
          }
        }

        struct ExhaustMatch
        {
          ZoneHVACEquipmentConnections connections;
          ModelObject target;
        };
        std::vector<ExhaustMatch> exhaustMatches;
        for (const auto& connections : terminal.model().getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
          const auto exhaustField =
            existingNodeCollectionField(connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
          if (exhaustField.valid && exhaustField.target && std::ranges::count(exhaustField.nodes, *induced.node) == 1) {
            exhaustMatches.push_back(ExhaustMatch{connections, *exhaustField.target});
          }
        }
        if (exhaustMatches.size() != 1u) {
          return nullptr;
        }
        const auto zoneRelationship =
          existingObjectField(exhaustMatches.front().connections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
        const auto servedZone = zoneRelationship.object ? zoneRelationship.object->optionalCast<ThermalZone>() : boost::none;
        const auto zoneInlets = existingNodeCollectionField(exhaustMatches.front().connections,
                                                            openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
        if (!servedZone || !zoneInlets.valid || std::ranges::count(zoneInlets.nodes, *outlet.node) != 1) {
          return nullptr;
        }

        std::vector<ThermalZone> registeredZones;
        for (const auto& zone : terminal.model().getConcreteModelObjects<ThermalZone>()) {
          const auto count = std::ranges::count(zone.equipment(), terminal);
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
        const auto exhaustSource = exhaustTarget.optionalCast<NodeList>() ? exhaustTarget.handle() : exhaustMatches.front().connections.handle();
        const std::vector<Handle> expectedInducedSources = projectedOnly ? std::vector<Handle>{terminal.handle(), exhaustSource}
                                                                         : std::vector<Handle>{terminal.handle(), heating->handle(), exhaustSource};
        if (!hasExactSources(*induced.node, expectedInducedSources)) {
          return nullptr;
        }
        if (auto exhaustList = exhaustTarget.optionalCast<NodeList>();
            exhaustList && !hasExactSources(*exhaustList, {exhaustMatches.front().connections.handle()})) {
          return nullptr;
        }

        auto result = std::unique_ptr<InductionContainedAirPathRemovalPlan>(new InductionContainedAirPathRemovalPlan(terminal, *heating, cooling));
        if (mixer) {
          result->m_mixer = *mixer;
          result->m_internalNodes.push_back(*heatingOutlet.node);
          if (cooling) {
            result->m_internalNodes.push_back(*coolingOutlet.node);
          }
        }
        result->m_induced = *induced.node;
        result->m_zoneConnections = exhaustMatches.front().connections;
        result->m_exhaustTarget = exhaustTarget;
        result->m_authoritativeOutlet = *outlet.node;
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
        if (!m_induced) {
          return;
        }

        auto terminalImpl = m_terminal.getImpl<detail::ModelObject_Impl>();
        OS_ASSERT(terminalImpl);
        if (m_mixer) {
          auto heatingImpl = m_heating.getImpl<detail::ModelObject_Impl>();
          OS_ASSERT(heatingImpl);
          assertSuccessfulMutation(heatingImpl->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle(), false));
          assertSuccessfulMutation(heatingImpl->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle(), false));
          if (m_cooling) {
            auto coolingImpl = m_cooling->getImpl<detail::ModelObject_Impl>();
            OS_ASSERT(coolingImpl);
            assertSuccessfulMutation(coolingImpl->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle(), false));
            assertSuccessfulMutation(coolingImpl->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle(), false));
          }
          assertSuccessfulMutation(
            terminalImpl->setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));

          const auto mixerHandle = m_mixer->handle();
          m_mixer->remove();
          OS_ASSERT(!m_terminal.model().getObject(mixerHandle));
          for (auto& node : m_internalNodes) {
            OS_ASSERT(node.sources().empty());
            const auto nodeHandle = node.handle();
            node.remove();
            OS_ASSERT(!m_terminal.model().getObject(nodeHandle));
          }
        }

        assertSuccessfulMutation(terminalImpl->setPointer(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName, Handle(), false));
        OS_ASSERT(m_zoneConnections && m_exhaustTarget && m_induced);
        if (auto exhaustList = m_exhaustTarget->optionalCast<NodeList>()) {
          const bool removeList = exhaustList->nodes().size() == 1u;
          assertSuccessfulMutation(exhaustList->getImpl<detail::NodeList_Impl>()->removeNode(*m_induced));
          if (removeList) {
            assertSuccessfulMutation(m_zoneConnections->getImpl<detail::ModelObject_Impl>()->setPointer(
              openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, Handle(), false));
            const auto listHandle = exhaustList->handle();
            exhaustList->remove();
            OS_ASSERT(!m_terminal.model().getObject(listHandle));
          }
        } else {
          assertSuccessfulMutation(m_zoneConnections->getImpl<detail::ModelObject_Impl>()->setPointer(
            openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, Handle(), false));
        }
        OS_ASSERT(m_induced->sources().empty());
        const auto inducedHandle = m_induced->handle();
        m_induced->remove();
        OS_ASSERT(!m_terminal.model().getObject(inducedHandle));
      }

     private:
      InductionContainedAirPathRemovalPlan(ModelObject terminal, CoilHeatingWater heating, boost::optional<CoilCoolingWater> cooling)
        : m_terminal(std::move(terminal)), m_heating(std::move(heating)), m_cooling(std::move(cooling)) {}

      ModelObject m_terminal;
      CoilHeatingWater m_heating;
      boost::optional<CoilCoolingWater> m_cooling;
      boost::optional<AirLoopHVACZoneMixer> m_mixer;
      std::vector<Node> m_internalNodes;
      boost::optional<Node> m_induced;
      boost::optional<ZoneHVACEquipmentConnections> m_zoneConnections;
      boost::optional<ModelObject> m_exhaustTarget;
      boost::optional<Node> m_authoritativeOutlet;
      bool m_allowMissingZoneRegistration = false;
    };

    struct InductionTopologyRemovalPlans
    {
      std::unique_ptr<InductionContainedAirPathRemovalPlan> containedAirPath;
      std::unique_ptr<detail::SingleDuctTerminalRemovalPlan> externalTopology;
    };

    std::unique_ptr<InductionTopologyRemovalPlans> prepareInductionTopologyRemoval(const ModelObject& terminalObject) {
      auto result = std::make_unique<InductionTopologyRemovalPlans>();
      result->containedAirPath = InductionContainedAirPathRemovalPlan::prepare(terminalObject);
      if (!result->containedAirPath) {
        return nullptr;
      }
      auto terminal = terminalObject.cast<StraightComponent>();
      if (detail::SingleDuctTerminalRemovalPlan::hasTopology(terminal)) {
        std::vector<ModelObject> containedInletSources;
        if (result->containedAirPath->hasContainedAirPath()) {
          const auto mixer =
            existingObjectField(terminalObject, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName);
          OS_ASSERT(mixer.object);
          containedInletSources.push_back(*mixer.object);
        }
        result->externalTopology = detail::SingleDuctTerminalRemovalPlan::prepare(
          terminal, containedInletSources, result->containedAirPath->authoritativeOutlet(), result->containedAirPath->allowMissingZoneRegistration());
        if (!result->externalTopology) {
          return nullptr;
        }
      }
      return result;
    }

    // A missing persisted heating-coil name can leave an otherwise exact
    // induction graph. Temporarily restore the one heating coil identified by
    // that graph so the normal air teardown can be prepared. Plant branches
    // are deliberately left alone during load repair.
    bool detachIncompleteInductionAirTopologyForRepair(ModelObject terminal, const boost::optional<CoilCoolingWater>& knownCoolingCoil) {
      const auto mixerRelationship =
        existingObjectField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName);
      const auto mixer = mixerRelationship.object ? mixerRelationship.object->optionalCast<AirLoopHVACZoneMixer>() : boost::none;
      const auto terminalOutlet =
        existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName);
      const auto induced =
        existingNodeField(terminal, openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName);
      const auto mixerOutlet =
        mixer ? existingNodeField(mixer->cast<ModelObject>(), openstudio::AirLoopHVAC_ZoneMixerFields::OutletNodeName) : detail::ExistingNodeField{};
      const auto mixerInlets = mixer ? existingNodeRows(mixer->cast<ModelObject>(), openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName)
                                     : detail::ExistingNodeRows{};
      if (!mixer || !terminalOutlet.node || !induced.node || !mixerOutlet.node || mixerOutlet.node->handle() != terminalOutlet.node->handle()
          || !mixerInlets.valid || mixerInlets.rows.size() != 2u || mixerInlets.rows[1].first != 1u) {
        return false;
      }

      boost::optional<Node> coolingInlet;
      if (knownCoolingCoil) {
        coolingInlet = existingNodeField(*knownCoolingCoil, openstudio::Coil_Cooling_WaterFields::AirInletNodeName).node;
        const auto coolingOutlet = existingNodeField(*knownCoolingCoil, openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
        if (!coolingInlet || !coolingOutlet.node || coolingOutlet.node->handle() != mixerInlets.rows[1].second.handle()) {
          return false;
        }
      }

      std::vector<CoilHeatingWater> heatingCandidates;
      for (const auto& candidate : terminal.model().getConcreteModelObjects<CoilHeatingWater>()) {
        const auto inlet = existingNodeField(candidate, openstudio::Coil_Heating_WaterFields::AirInletNodeName);
        const auto outlet = existingNodeField(candidate, openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        const auto expectedOutlet = knownCoolingCoil ? coolingInlet : boost::optional<Node>(mixerInlets.rows[1].second);
        if (inlet.node && outlet.node && expectedOutlet && inlet.node->handle() == induced.node->handle()
            && outlet.node->handle() == expectedOutlet->handle()) {
          heatingCandidates.push_back(candidate);
        }
      }
      if (heatingCandidates.size() != 1u) {
        return false;
      }

      const auto heatingField = openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName;
      auto terminalWorkspaceImpl = terminal.getImpl<openstudio::detail::WorkspaceObject_Impl>();
      OS_ASSERT(terminalWorkspaceImpl);
      const auto rawHeatingName = terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(heatingField, false, true).value_or("");
      if (!terminalWorkspaceImpl->setPointer(heatingField, heatingCandidates.front().handle(), false)) {
        return false;
      }

      auto plans = prepareInductionTopologyRemoval(terminal);
      assertSuccessfulMutation(terminalWorkspaceImpl->setPointer(heatingField, Handle(), false));
      assertSuccessfulMutation(terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(heatingField, rawHeatingName, false));
      if (!plans || !plans->externalTopology) {
        return false;
      }

      plans->containedAirPath->commit();
      plans->externalTopology->commit();
      return true;
    }

  }  // namespace

  AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model,
                                                                                                             HVACComponent& heatingCoil)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    applyConstructorDefaults(*this);
    OS_ASSERT(setHeatingCoil(heatingCoil));
  }

  AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction;
  }

  boost::optional<Schedule> AirTerminalSingleDuctConstantVolumeFourPipeInduction::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetAvailabilitySchedule() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumTotalAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumTotalAirFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumTotalAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumTotalAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumTotalAirFlowRate(maximumTotalAirFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumTotalAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumTotalAirFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::inductionRatio() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inductionRatio();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isInductionRatioDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isInductionRatioDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setInductionRatio(double inductionRatio) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setInductionRatio(inductionRatio);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetInductionRatio() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetInductionRatio();
  }

  HVACComponent AirTerminalSingleDuctConstantVolumeFourPipeInduction::heatingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->heatingCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setHeatingCoil(heatingCoil);
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumHotWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumHotWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumHotWaterFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumHotWaterFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumHotWaterFlowRate(maximumHotWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMaximumHotWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMaximumHotWaterFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumHotWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumHotWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::minimumHotWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->minimumHotWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMinimumHotWaterFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMinimumHotWaterFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMinimumHotWaterFlowRate(minimumHotWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMinimumHotWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMinimumHotWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::heatingConvergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->heatingConvergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetHeatingConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetHeatingConvergenceTolerance();
  }

  boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeInduction::coolingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->coolingCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setCoolingCoil(coolingCoil);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetCoolingCoil() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetCoolingCoil();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumColdWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumColdWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumColdWaterFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumColdWaterFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumColdWaterFlowRate(maximumColdWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMaximumColdWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMaximumColdWaterFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumColdWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumColdWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::minimumColdWaterFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->minimumColdWaterFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMinimumColdWaterFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMinimumColdWaterFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMinimumColdWaterFlowRate(minimumColdWaterFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMinimumColdWaterFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMinimumColdWaterFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeFourPipeInduction::coolingConvergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->coolingConvergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isCoolingConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isCoolingConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetCoolingConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetCoolingConvergenceTolerance();
  }

  boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeInduction::inducedAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inducedAirInletNode();
  }

  unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction::inducedAirInletPort() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inducedAirInletPort();
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto coolingCoil = this->coolingCoil()) {
        result.push_back(*coolingCoil);
      }
      auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      if (heatingCoil) {
        result.push_back(*heatingCoil);
      }
      return result;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isRemovable() const {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }
      auto terminalObject = getObject<ModelObject>();
      auto terminal = terminalObject.cast<StraightComponent>();
      const auto heating = terminalObject.getModelObjectTarget<CoilHeatingWater>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      const auto cooling = terminalObject.getModelObjectTarget<CoilCoolingWater>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
      const bool hasAirTopology = SingleDuctTerminalRemovalPlan::hasTopology(terminal) || inductionHasContainedTopology(terminalObject);
      const auto heatingLoop = heating ? heating->plantLoop() : boost::none;
      const auto coolingLoop = cooling ? cooling->plantLoop() : boost::none;
      if (!hasAirTopology && !heatingLoop && !coolingLoop) {
        return true;
      }
      if (!prepareInductionTopologyRemoval(terminalObject) || (heatingLoop && coolingLoop && *heatingLoop == *coolingLoop)) {
        return false;
      }
      for (const auto& coil : {boost::optional<WaterToAirComponent>(heating), boost::optional<WaterToAirComponent>(cooling)}) {
        if (coil) {
          if (auto plantLoop = coil->plantLoop()) {
            auto plantLoopImpl = plantLoop->getImpl<PlantLoop_Impl>();
            OS_ASSERT(plantLoopImpl);
            if (!plantLoopImpl->prepareWaterCoilDemandBranchRemoval(*coil)) {
              return false;
            }
          }
        }
      }
      return true;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::remove() {
      auto thisObject = getObject<ModelObject>();
      auto thisModel = model();
      const auto thisHandle = thisObject.handle();
      const auto ownedChildren = children();
      if (!removeFromLoop()) {
        const auto heating = thisObject.getModelObjectTarget<CoilHeatingWater>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
        const auto cooling = thisObject.getModelObjectTarget<CoilCoolingWater>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
        if (SingleDuctTerminalRemovalPlan::hasTopology(thisObject.cast<StraightComponent>()) || inductionHasContainedTopology(thisObject)
            || (heating && heating->plantLoop()) || (cooling && cooling->plantLoop())) {
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

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::removeFromLoop() {
      auto terminalObject = getObject<ModelObject>();
      auto terminal = terminalObject.cast<StraightComponent>();
      const auto heating = terminalObject.getModelObjectTarget<CoilHeatingWater>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      const auto cooling = terminalObject.getModelObjectTarget<CoilCoolingWater>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
      const bool hasAirTopology = SingleDuctTerminalRemovalPlan::hasTopology(terminal) || inductionHasContainedTopology(terminalObject);
      const auto heatingLoop = heating ? heating->plantLoop() : boost::none;
      const auto coolingLoop = cooling ? cooling->plantLoop() : boost::none;
      if (!hasAirTopology && !heatingLoop && !coolingLoop) {
        return false;
      }

      auto topologyPlans = prepareInductionTopologyRemoval(terminalObject);
      if (!topologyPlans || (heatingLoop && coolingLoop && *heatingLoop == *coolingLoop)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "Refusing to remove a four-pipe induction terminal whose contained, external, or same-loop plant topology is not exact.");
        return false;
      }

      std::unique_ptr<PlantLoop_Impl::WaterCoilDemandBranchRemovalPlan> heatingPlantPlan;
      std::unique_ptr<PlantLoop_Impl::WaterCoilDemandBranchRemovalPlan> coolingPlantPlan;
      if (heatingLoop) {
        auto plantLoopImpl = heatingLoop->getImpl<PlantLoop_Impl>();
        OS_ASSERT(plantLoopImpl && heating);
        heatingPlantPlan = plantLoopImpl->prepareWaterCoilDemandBranchRemoval(*heating);
        if (!heatingPlantPlan) {
          return false;
        }
      }
      if (coolingLoop) {
        auto plantLoopImpl = coolingLoop->getImpl<PlantLoop_Impl>();
        OS_ASSERT(plantLoopImpl && cooling);
        coolingPlantPlan = plantLoopImpl->prepareWaterCoilDemandBranchRemoval(*cooling);
        if (!coolingPlantPlan) {
          return false;
        }
      }

      if (coolingPlantPlan) {
        coolingPlantPlan->commit();
      }
      if (heatingPlantPlan) {
        heatingPlantPlan->commit();
      }
      topologyPlans->containedAirPath->commit();
      if (topologyPlans->externalTopology) {
        topologyPlans->externalTopology->commit();
      }
      return true;
    }

    boost::optional<Schedule> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName);
    }

    unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeFourPipeInduction", "Availability", schedule);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AvailabilityScheduleName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumTotalAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumTotalAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, maximumTotalAirFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumTotalAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inductionRatio() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isInductionRatioDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setInductionRatio(double inductionRatio) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, inductionRatio);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetInductionRatio() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, ""));
    }

    HVACComponent AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::heatingCoil() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if ((heatingCoil.model() != model()) || (heatingCoil.iddObject().type() != IddObjectType::Coil_Heating_Water)) {
        return false;
      }
      auto mutableHeatingCoil = heatingCoil;
      auto terminal = getObject<ModelObject>();
      auto previousCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      if (previousCoil && previousCoil->handle() == heatingCoil.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = heatingCoil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      if (heatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName)
          || heatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
        return false;
      }
      if (previousCoil) {
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, heatingCoil.handle(), false)) {
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        if (previousCoil) {
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      if (!maintainContainedAirPath()) {
        OS_ASSERT(mutableHeatingCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(mutableHeatingCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName,
                             previousCoil ? previousCoil->handle() : Handle(), false));
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      return true;
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumHotWaterFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumHotWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, maximumHotWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::minimumHotWaterFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMinimumHotWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, minimumHotWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMinimumHotWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::heatingConvergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance,
                       heatingConvergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetHeatingConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, ""));
    }

    boost::optional<HVACComponent> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setCoolingCoil(const boost::optional<HVACComponent>& coolingCoil) {
      if (coolingCoil) {
        if ((coolingCoil->model() != model()) || (coolingCoil->iddObject().type() != IddObjectType::Coil_Cooling_Water)) {
          return false;
        }
        auto mutableCoolingCoil = *coolingCoil;
        auto terminal = getObject<ModelObject>();
        auto previousCoil =
          terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
        if (previousCoil && previousCoil->handle() == coolingCoil->handle()) {
          return maintainContainedAirPath();
        }
        if (auto owner = coolingCoil->containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
          return false;
        }
        if (coolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName)
            || coolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName)) {
          return false;
        }
        if (previousCoil) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
        }
        if (!setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, coolingCoil->handle(), false)) {
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName,
                               previousCoil ? previousCoil->handle() : Handle(), false));
          if (previousCoil) {
            OS_ASSERT(maintainContainedAirPath());
          }
          return false;
        }
        if (!maintainContainedAirPath()) {
          OS_ASSERT(mutableCoolingCoil.setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(mutableCoolingCoil.setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName,
                               previousCoil ? previousCoil->handle() : Handle(), false));
          OS_ASSERT(maintainContainedAirPath());
          return false;
        }
        return true;
      }
      resetCoolingCoil();
      return true;
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetCoolingCoil() {
      if (auto previousCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName)) {
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
      }
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, ""));
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
      OS_ASSERT(maintainContainedAirPath());
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::doCanonicalize(LoadContext& context) {
      if (!repairContainedAirPath(context)) {
        detail::addLoadError(context, "Failed to repair contained air path for AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto terminal = getObject<ModelObject>();
      auto heatingCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      auto coolingCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
      if (heatingCoil && context) {
        const bool supported = heatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Water;
        const auto owner = heatingCoil->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " heating-coil reference from AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                             + terminal.nameString() + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, Handle(), false));
          heatingCoil = boost::none;
        }
      }
      if (coolingCoil && context) {
        const bool supported = coolingCoil->iddObject().type() == IddObjectType::Coil_Cooling_Water;
        const auto owner = coolingCoil->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " cooling-coil reference from AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                             + terminal.nameString() + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, Handle(), false));
          coolingCoil = boost::none;
        }
      }
      if (!heatingCoil) {
        if (coolingCoil && coolingCoil->iddObject().type() != IddObjectType::Coil_Cooling_Water) {
          return false;
        }
        const bool hadExternalTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                                         || static_cast<bool>(resolvedNodeTarget(inducedAirInletPort()))
                                         || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal))
                                         || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology) {
          const auto coolingWaterCoil = coolingCoil ? coolingCoil->optionalCast<CoilCoolingWater>() : boost::none;
          const bool detached = detachIncompleteInductionAirTopologyForRepair(terminal, coolingWaterCoil);
          if (!detached) {
            detail::addLoadError(*context, "Could not detach incomplete AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                             + terminal.nameString() + "' from its external topology.");
            return false;
          }
        }
        bool changed = false;
        std::vector<Node> orphanCandidates;
        if (coolingCoil) {
          for (const auto field : {openstudio::Coil_Cooling_WaterFields::AirInletNodeName, openstudio::Coil_Cooling_WaterFields::AirOutletNodeName}) {
            if (auto node = coolingCoil->getModelObjectTarget<Node>(field)) {
              orphanCandidates.push_back(*node);
            }
            changed = changed || static_cast<bool>(coolingCoil->getTarget(field));
            OS_ASSERT(coolingCoil->setPointer(field, Handle()));
          }
        }
        const auto previousHeatingType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType, false, true).value_or("");
        const auto previousCoolingType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, false, true).value_or("");
        const auto expectedCoolingType = coolingCoil ? coolingCoil->iddObject().name() : "";
        changed = changed || !previousHeatingType.empty() || !openstudio::istringEqual(previousCoolingType, expectedCoolingType);
        const auto previousHeatingName =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, false, true).value_or("");
        changed = changed || !previousHeatingName.empty();
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, expectedCoolingType));
        if (!coolingCoil) {
          const auto previousCoolingName =
            getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, false, true).value_or("");
          changed = changed || !previousCoolingName.empty();
          OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName)) {
          changed = true;
          auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>();
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));
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
        OS_ASSERT(setPointer(inducedAirInletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if ((changed || hadExternalTopology) && context) {
          detail::addLoadWarning(*context, "Detached incomplete AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '" + terminal.nameString()
                                             + "' and cleared its unresolved heating-coil reference.");
        }
        return true;
      }
      if ((heatingCoil->iddObject().type() != IddObjectType::Coil_Heating_Water)
          || (coolingCoil && coolingCoil->iddObject().type() != IddObjectType::Coil_Cooling_Water)) {
        return false;
      }
      bool changed = false;
      const auto storedHeatingType =
        terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType);
      changed = !storedHeatingType || !openstudio::istringEqual(*storedHeatingType, heatingCoil->iddObject().name());
      if (!setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType,
                     heatingCoil->iddObject().name())) {
        return false;
      }
      if (coolingCoil) {
        const auto storedCoolingType =
          terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType);
        changed = changed || !storedCoolingType || !openstudio::istringEqual(*storedCoolingType, coolingCoil->iddObject().name());
        if (!setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType,
                       coolingCoil->iddObject().name())) {
          return false;
        }
      } else {
        const auto previousCoolingName =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, false, true).value_or("");
        const auto previousCoolingType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, false, true).value_or("");
        changed = changed || !previousCoolingName.empty() || !previousCoolingType.empty();
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType, ""));
      }

      auto supplyNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName);
      auto inducedNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName);
      auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName);
      if (!supplyNode || !inducedNode || !outletNode) {
        auto heatingOutletNode = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        changed = changed || static_cast<bool>(heatingCoil->getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName))
                  || static_cast<bool>(heatingOutletNode);
        OS_ASSERT(heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
        OS_ASSERT(heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        boost::optional<Node> coolingOutletNode;
        if (coolingCoil) {
          coolingOutletNode = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
          changed = changed || static_cast<bool>(coolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName))
                    || static_cast<bool>(coolingOutletNode);
          OS_ASSERT(coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, Handle()));
        }
        if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName)) {
          changed = true;
          if (auto oldMixer = target->optionalCast<AirLoopHVACZoneMixer>()) {
            bool exclusivelyOwned = true;
            for (const auto& source : oldMixer->sources()) {
              if (source.handle() != terminal.handle()) {
                exclusivelyOwned = false;
                break;
              }
            }
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));
            if (exclusivelyOwned) {
              oldMixer->remove();
            }
          } else {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, Handle(), false));
          }
        }
        if (heatingOutletNode && heatingOutletNode->sources().empty()) {
          heatingOutletNode->remove();
        }
        if (coolingOutletNode && coolingOutletNode->sources().empty()) {
          coolingOutletNode->remove();
        }
        if (changed && context) {
          detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                          + terminal.nameString() + "'.");
        }
        return true;
      }
      if (!terminal.name() && !terminal.createName()) {
        return false;
      }
      const auto baseName = terminal.nameString();

      boost::optional<AirLoopHVACZoneMixer> mixer;
      if (auto target = terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName)) {
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
      if (auto node = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)) {
        displacedNodeCandidates.push_back(*node);
      }
      if (auto node = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
        displacedNodeCandidates.push_back(*node);
      }
      if (coolingCoil) {
        if (auto node = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName)) {
          displacedNodeCandidates.push_back(*node);
        }
        if (auto node = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName)) {
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

      boost::optional<Node> heatingOutletNode;
      boost::optional<Node> coolingOutletNode;
      if (allowChildNodeRecovery && mixer) {
        const auto currentHeatingOutlet = heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        const auto currentInducedMixerInlet =
          mixer->inletModelObjects().size() > 1u ? mixer->inletModelObjects()[1].optionalCast<Node>() : boost::optional<Node>{};
        if (coolingCoil) {
          const auto currentCoolingInlet = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName);
          if (currentHeatingOutlet && currentCoolingInlet && *currentHeatingOutlet == *currentCoolingInlet && *currentHeatingOutlet != *supplyNode
              && *currentHeatingOutlet != *inducedNode && *currentHeatingOutlet != *outletNode) {
            heatingOutletNode = currentHeatingOutlet;
          }
          const auto currentCoolingOutlet = coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
          if (currentCoolingOutlet && currentInducedMixerInlet && *currentCoolingOutlet == *currentInducedMixerInlet
              && *currentCoolingOutlet != *supplyNode && *currentCoolingOutlet != *inducedNode && *currentCoolingOutlet != *outletNode) {
            coolingOutletNode = currentCoolingOutlet;
          }
        } else if (currentHeatingOutlet && currentInducedMixerInlet && *currentHeatingOutlet == *currentInducedMixerInlet
                   && *currentHeatingOutlet != *supplyNode && *currentHeatingOutlet != *inducedNode && *currentHeatingOutlet != *outletNode) {
          heatingOutletNode = currentHeatingOutlet;
        }
      }
      if (!heatingOutletNode) {
        heatingOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Heating Coil Outlet");
      }
      if (coolingCoil && !coolingOutletNode) {
        coolingOutletNode = model().getOrCreateTransientByName<Node>(baseName + " Cooling Coil Outlet");
      }

      changed = changed || heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName) != inducedNode
                || heatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName) != heatingOutletNode;
      if (!heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, inducedNode->handle())
          || !heatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, heatingOutletNode->handle())) {
        return false;
      }

      Node inducedMixerInlet = *heatingOutletNode;
      if (coolingCoil) {
        OS_ASSERT(coolingOutletNode);
        changed = changed || coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName) != heatingOutletNode
                  || coolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName) != coolingOutletNode;
        if (!coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, heatingOutletNode->handle())
            || !coolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, coolingOutletNode->handle())) {
          return false;
        }
        inducedMixerInlet = *coolingOutletNode;
      }
      if (!mixer) {
        mixer = AirLoopHVACZoneMixer(model());
        changed = true;
        if (!mixer->setName(baseName + " Mixer")
            || !setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName, mixer->handle(), false)) {
          return false;
        }
      }
      auto mixerImpl = mixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
      OS_ASSERT(mixerImpl);
      const auto previousMixerInlets = mixer->inletModelObjects();
      const auto previousMixerOutlet = mixer->getModelObjectTarget<Node>(mixer->outletPort());
      changed = changed || !previousMixerOutlet || *previousMixerOutlet != *outletNode || previousMixerInlets.size() != 2u
                || previousMixerInlets[0] != supplyNode->cast<ModelObject>() || previousMixerInlets[1] != inducedMixerInlet.cast<ModelObject>();
      if (!mixerImpl->setOutletNode(*outletNode) || !mixer->setInletModelObject(0u, supplyNode->cast<ModelObject>())
          || !mixer->setInletModelObject(1u, inducedMixerInlet.cast<ModelObject>())) {
        return false;
      }
      while (mixer->inletModelObjects().size() > 2u) {
        auto displacedNode = mixer->inletModelObjects().back().optionalCast<Node>();
        mixer->removePortForBranch(static_cast<unsigned>(mixer->inletModelObjects().size() - 1u));
        if (displacedNode && displacedNode->sources().empty() && model().getObject(displacedNode->handle())) {
          displacedNode->remove();
        }
      }
      for (auto& displacedNode : displacedNodeCandidates) {
        if (displacedNode == *supplyNode || displacedNode == *inducedNode || displacedNode == *outletNode || displacedNode == *heatingOutletNode
            || (coolingOutletNode && displacedNode == *coolingOutletNode)) {
          continue;
        }
        if (model().getObject(displacedNode.handle()) && displacedNode.sources().empty()) {
          displacedNode.remove();
        }
      }
      if (changed && context) {
        detail::addLoadInfo(*context, "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:FourPipeInduction '"
                                        + terminal.nameString() + "'.");
      }
      return true;
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumColdWaterFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumColdWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, maximumColdWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMaximumColdWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumColdWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::minimumColdWaterFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMinimumColdWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, minimumColdWaterFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMinimumColdWaterFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::coolingConvergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isCoolingConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance,
                       coolingConvergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetCoolingConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, ""));
    }

    boost::optional<Node> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inducedAirInletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName);
    }

    unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inducedAirInletPort() const {
      return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InducedAirInletNodeName;
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires a node in the same model as the four-pipe induction terminal.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      auto heatingChild =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName);
      auto coolingChild =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilName);
      if (!heatingChild || heatingChild->iddObject().type() != IddObjectType::Coil_Heating_Water
          || (coolingChild && coolingChild->iddObject().type() != IddObjectType::Coil_Cooling_Water)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires supported water-coil children before topology is changed.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      if (inletModelObject() || outletModelObject()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                 "addToNode refuses to insert an already-connected four-pipe induction terminal.");
        return false;
      }

      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      const bool inletNodeExisted = static_cast<bool>(model().getConcreteModelObjectByName<Node>(inletNodeName));
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      auto adu = zoneHVACAirDistributionUnit();
      const auto aduOutletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
      const auto originalADUOutlet = adu ? adu->getString(aduOutletField, false, true) : boost::optional<std::string>{};

      boost::optional<ZoneHVACEquipmentConnections> zoneConnections;
      boost::optional<std::string> originalExhaustTarget;
      boost::optional<Node> exhaustNode;
      bool exhaustNodeExisted = true;
      bool terminalRegistered = false;
      bool terminalWasRegistered = false;
      if (thermalZone) {
        const auto zoneEquipment = thermalZone->equipment();
        terminalWasRegistered = std::ranges::find(zoneEquipment, thisObject) != zoneEquipment.end();
        auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);
        zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
        originalExhaustTarget =
          zoneConnections->getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, false, true);
        const auto exhaustNodeName = thermalZone->nameString() + " Exhaust Node";
        exhaustNodeExisted = static_cast<bool>(model().getConcreteModelObjectByName<Node>(exhaustNodeName));
      }

      auto rollback = [&]() {
        if (terminalRegistered && thermalZone) {
          OS_ASSERT(unregisterTerminalFromThermalZone(thisObject, *thermalZone));
        }
        OS_ASSERT(setPointer(inducedAirInletPort(), Handle(), false));
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if (adu) {
          auto aduWorkspaceImpl = adu->getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(aduWorkspaceImpl);
          OS_ASSERT(aduWorkspaceImpl->setPointer(aduOutletField, Handle(), false));
          OS_ASSERT(aduWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(aduOutletField, originalADUOutlet.value_or(""), false));
        }
        OS_ASSERT(zoneSplitter.setOutletModelObject(splitterBranchIndex, node.cast<ModelObject>()));
        if (zoneConnections) {
          const auto exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
          auto connectionsWorkspaceImpl = zoneConnections->getImpl<openstudio::detail::WorkspaceObject_Impl>();
          OS_ASSERT(connectionsWorkspaceImpl);
          OS_ASSERT(connectionsWorkspaceImpl->setPointer(exhaustField, Handle(), false));
          OS_ASSERT(connectionsWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(exhaustField, originalExhaustTarget.value_or(""), false));
        }
        OS_ASSERT(maintainContainedAirPath());
        if (!inletNodeExisted && inletNode.sources().empty()) {
          inletNode.remove();
        }
        if (exhaustNode && !exhaustNodeExisted && exhaustNode->sources().empty()) {
          exhaustNode->remove();
        }
        return false;
      };

      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return rollback();
      }

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        return rollback();
      }

      if (!setPointer(outletPort(), node.handle(), false)) {
        return rollback();
      }

      if (adu) {
        adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
      }

      if (thermalZone) {
        exhaustNode = zoneExhaustNodeForThermalZone(*thermalZone);
        if (!exhaustNode) {
          return rollback();
        }

        if (!setPointer(inducedAirInletPort(), exhaustNode->handle())) {
          return rollback();
        }

        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeInduction",
                   "addToNode failed to register the four-pipe induction terminal with the owning thermal zone.");
          return rollback();
        }
        terminalRegistered = !terminalWasRegistered;
      }

      if (failureStage == AddToNodeFailureStage::AfterTopologyPrepared) {
        return rollback();
      }
      if (!maintainContainedAirPath()) {
        return rollback();
      }
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
