/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
    }

    void applyConstructorDefaults(AirTerminalSingleDuctVAVHeatAndCoolReheat& terminal) {
      terminal.autosizeMaximumAirFlowRate();
      assertSuccessfulMutation(terminal.setZoneMinimumAirFlowFraction(0.0));
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      assertSuccessfulMutation(terminal.setMinimumHotWaterorSteamFlowRate(0.0));
      assertSuccessfulMutation(terminal.setConvergenceTolerance(0.001));
      assertSuccessfulMutation(terminal.setMaximumReheatAirTemperature(1000.0));
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

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    bool registerTerminalWithThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal);
    }

    bool unregisterTerminalFromThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

    struct DemandBranchRemovalPlan
    {
      bool valid = true;
      boost::optional<PlantLoop> plantLoop;
    };

    DemandBranchRemovalPlan demandBranchRemovalPlan(const boost::optional<HVACComponent>& coil) {
      DemandBranchRemovalPlan result;
      if (!coil) {
        return result;
      }

      auto plantLoop = coil->plantLoop();
      if (!plantLoop) {
        return result;
      }

      boost::optional<ModelObject> inletObject;
      boost::optional<ModelObject> outletObject;
      if (auto straightCoil = coil->optionalCast<StraightComponent>()) {
        inletObject = straightCoil->inletModelObject();
        outletObject = straightCoil->outletModelObject();
      } else if (auto waterCoil = coil->optionalCast<WaterToAirComponent>()) {
        inletObject = waterCoil->waterInletModelObject();
        outletObject = waterCoil->waterOutletModelObject();
      }
      const auto inletNode = inletObject ? inletObject->optionalCast<Node>() : boost::none;
      const auto outletNode = outletObject ? outletObject->optionalCast<Node>() : boost::none;
      auto plantLoopImpl = plantLoop->getImpl<detail::PlantLoop_Impl>();
      OS_ASSERT(plantLoopImpl);
      const auto inletBranch = inletNode ? plantLoopImpl->branchForNode(*inletNode) : boost::none;
      const auto outletBranch = outletNode ? plantLoopImpl->branchForNode(*outletNode) : boost::none;
      const auto equipmentBranches = plantLoopImpl->demandEquipmentBranches();

      boost::optional<Branch> targetBranch;
      for (const auto& candidate : {inletBranch, outletBranch}) {
        if (!candidate) {
          continue;
        }
        if (std::ranges::find(equipmentBranches, *candidate) == equipmentBranches.end() || (targetBranch && (*targetBranch != *candidate))) {
          result.valid = false;
          return result;
        }
        targetBranch = *candidate;
      }

      if (!targetBranch) {
        result.valid = false;
        return result;
      }

      result.plantLoop = *plantLoop;
      return result;
    }

    class TerminalInsertionPlan
    {
     public:
      TerminalInsertionPlan(ModelObject terminal, AirLoopHVACZoneSplitter splitter, unsigned branchIndex, Node outletNode, unsigned inletPort,
                            unsigned outletPort, boost::optional<ZoneHVACAirDistributionUnit> adu, boost::optional<ThermalZone> thermalZone)
        : m_terminal(std::move(terminal)),
          m_splitter(std::move(splitter)),
          m_branchIndex(branchIndex),
          m_outletNode(std::move(outletNode)),
          m_inletPort(inletPort),
          m_outletPort(outletPort),
          m_adu(std::move(adu)),
          m_thermalZone(std::move(thermalZone)) {
        if (m_adu) {
          const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
          if (auto managedField = m_adu->getField(outletField, false)) {
            const auto targetHandle = toUUID(*managedField);
            if (!targetHandle.isNull()) {
              if (auto target = m_terminal.model().getObject(targetHandle)) {
                m_previousADUOutletTarget = target->optionalCast<ModelObject>();
              }
            }
          }
          if (!m_previousADUOutletTarget) {
            auto workspaceImpl = m_adu->getImpl<openstudio::detail::WorkspaceObject_Impl>();
            OS_ASSERT(workspaceImpl);
            m_previousADUOutletNodeName = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
          }
        }
        const std::string inletNodeName = m_outletNode.nameString() + " - " + m_terminal.nameString() + " Inlet Node";
        if (auto existingNode = m_terminal.model().getConcreteModelObjectByName<Node>(inletNodeName)) {
          m_inletNode = *existingNode;
        } else {
          m_inletNode = m_terminal.model().getOrCreateTransientByName<Node>(inletNodeName);
          m_createdInletNode = true;
        }
      }

      TerminalInsertionPlan(const TerminalInsertionPlan&) = delete;
      TerminalInsertionPlan& operator=(const TerminalInsertionPlan&) = delete;
      TerminalInsertionPlan(TerminalInsertionPlan&&) = delete;
      TerminalInsertionPlan& operator=(TerminalInsertionPlan&&) = delete;

      ~TerminalInsertionPlan() {
        if (!m_committed) {
          rollback();
        }
      }

      bool apply(bool failAfterADUUpdate) {
        OS_ASSERT(m_inletNode);
        if (!m_splitter.setOutletModelObject(m_branchIndex, m_inletNode->cast<ModelObject>())) {
          return false;
        }
        m_splitterRewired = true;

        if (!setTerminalPointer(m_inletPort, m_inletNode->handle())) {
          return false;
        }
        m_inletAssigned = true;

        if (!setTerminalPointer(m_outletPort, m_outletNode.handle())) {
          return false;
        }
        m_outletAssigned = true;

        if (m_adu) {
          if (!m_adu->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(m_outletNode)) {
            return false;
          }
          m_aduUpdated = true;
        }

        if (failAfterADUUpdate) {
          return false;
        }

        if (m_thermalZone) {
          if (!registerTerminalWithThermalZone(m_terminal, *m_thermalZone)) {
            return false;
          }
          m_zoneRegistered = true;
        }

        m_committed = true;
        return true;
      }

     private:
      void rollback() {
        if (m_zoneRegistered && m_thermalZone) {
          assertSuccessfulMutation(unregisterTerminalFromThermalZone(m_terminal, *m_thermalZone));
        }
        if (m_adu && m_aduUpdated) {
          auto aduImpl = m_adu->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
          OS_ASSERT(aduImpl);
          const auto outletField = openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName;
          bool restored = false;
          if (m_previousADUOutletTarget) {
            restored = aduImpl->setPointer(outletField, m_previousADUOutletTarget->handle(), false);
          } else if (m_previousADUOutletNodeName) {
            const bool pointerCleared = aduImpl->setPointer(outletField, Handle(), false);
            const bool rawRestored = aduImpl->openstudio::detail::IdfObject_Impl::setString(outletField, *m_previousADUOutletNodeName, false);
            restored = pointerCleared && rawRestored;
          } else {
            restored = aduImpl->setPointer(outletField, Handle(), false);
          }
          assertSuccessfulMutation(restored);
        }
        if (m_outletAssigned) {
          assertSuccessfulMutation(setTerminalPointer(m_outletPort, Handle()));
        }
        if (m_inletAssigned) {
          assertSuccessfulMutation(setTerminalPointer(m_inletPort, Handle()));
        }
        if (m_splitterRewired) {
          assertSuccessfulMutation(m_splitter.setOutletModelObject(m_branchIndex, m_outletNode.cast<ModelObject>()));
        }
        if (m_createdInletNode && m_inletNode && m_terminal.model().getObject(m_inletNode->handle())) {
          m_inletNode->remove();
        }
      }

      bool setTerminalPointer(unsigned fieldIndex, const openstudio::Handle& targetHandle) {
        auto terminalImpl = m_terminal.getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>();
        OS_ASSERT(terminalImpl);
        return terminalImpl->setPointer(fieldIndex, targetHandle, false);
      }

      ModelObject m_terminal;
      AirLoopHVACZoneSplitter m_splitter;
      unsigned m_branchIndex;
      Node m_outletNode;
      unsigned m_inletPort;
      unsigned m_outletPort;
      boost::optional<ZoneHVACAirDistributionUnit> m_adu;
      boost::optional<ThermalZone> m_thermalZone;
      boost::optional<std::string> m_previousADUOutletNodeName;
      boost::optional<ModelObject> m_previousADUOutletTarget;
      boost::optional<Node> m_inletNode;
      bool m_createdInletNode = false;
      bool m_splitterRewired = false;
      bool m_inletAssigned = false;
      bool m_outletAssigned = false;
      bool m_aduUpdated = false;
      bool m_zoneRegistered = false;
      bool m_committed = false;
    };

  }  // namespace

  AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType(), model) {
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model, const HVACComponent& reheatCoil)
    : StraightComponent(AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType(), model) {
    if (!setReheatCoil(reheatCoil)) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                         "Could not construct " << briefDescription() << ", because the reheat coil was from another model.");
    }
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat;
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::resetAvailabilitySchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->resetAvailabilitySchedule();
  }

  HVACComponent AirTerminalSingleDuctVAVHeatAndCoolReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setReheatCoil(const HVACComponent& heatingCoilName) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setReheatCoil(heatingCoilName);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat::minimumAirFlowTurndownSchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->minimumAirFlowTurndownSchedule();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMinimumAirFlowTurndownSchedule(schedule);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::resetMinimumAirFlowTurndownSchedule() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->resetMinimumAirFlowTurndownSchedule();
  }

  boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::zoneMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->zoneMinimumAirFlowFraction();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
  }

  boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctVAVHeatAndCoolReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  double AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumReheatAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumReheatAirTemperature();
  }

  bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isRemovable() const {
      if (!HVACComponent_Impl::isRemovable()) {
        return false;
      }
      const auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      return demandBranchRemovalPlan(coil).valid;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto ownedChildren = children();
      const bool hadTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                               || static_cast<bool>(thermalZoneContainingTerminal(model(), thisObject))
                               || static_cast<bool>(zoneHVACAirDistributionUnit());
      bool childHadPlantTopology = false;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<openstudio::epmodel::HVACComponent>(); component && component->plantLoop()) {
          childHadPlantTopology = true;
          break;
        }
      }

      if ((hadTopology || childHadPlantTopology) && !removeFromLoop()) {
        return {};
      }

      auto result = HVACComponent_Impl::remove();
      if (result.empty()) {
        return result;
      }

      for (auto& child : ownedChildren) {
        auto removedChild = child.remove();
        result.insert(result.end(), removedChild.begin(), removedChild.end());
      }
      return result;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      auto plantRemovalPlan = demandBranchRemovalPlan(coil);
      if (!plantRemovalPlan.valid) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "Refusing to remove a terminal whose reheat coil does not belong to exactly one demand-equipment branch.");
        return false;
      }

      bool shouldRemoveTerminalInletNode = false;
      if (inletNode || outletNode) {
        if (!inletNode || !outletNode) {
          return false;
        }
        auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>();
        auto airLoop = terminal ? terminal->airLoopHVAC() : boost::optional<openstudio::epmodel::AirLoopHVAC>{};
        if (!airLoop) {
          return false;
        }
        const auto splitter = airLoop->zoneSplitter();
        const auto splitterOutlets = splitter.outletModelObjects();
        const auto splitterIt = std::ranges::find(splitterOutlets, *inletNode);
        if (splitterIt == splitterOutlets.end()) {
          return false;
        }
        const auto mixerInlets = airLoop->zoneMixer().inletModelObjects();
        const bool hasMatchingReturn = std::ranges::any_of(
          mixerInlets, [&](const auto& mixerInlet) { return (mixerInlet == *outletNode) || isServedZoneReturnNode(thermalZone, mixerInlet); });
        if (!hasMatchingReturn) {
          return false;
        }
        shouldRemoveTerminalInletNode = true;
      }

      // Refuse malformed plant topology before mutating air or zone state.
      bool removedFromPlantLoop = false;
      if (plantRemovalPlan.plantLoop && coil) {
        if (!plantRemovalPlan.plantLoop->removeDemandBranchWithComponent(*coil)) {
          return false;
        }
        removedFromPlantLoop = true;
      }

      bool removedFromAirLoop = false;
      if (inletNode && outletNode) {
        if (!StraightComponent_Impl::removeFromLoop()) {
          return false;
        }
        removedFromAirLoop = true;
      }

      if (thermalZone && !unregisterTerminalFromThermalZone(thisObject, *thermalZone)) {
        return false;
      }

      bool cleanedADU = false;
      if (auto adu = zoneHVACAirDistributionUnit()) {
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle())) {
          return false;
        }
        if (!adu->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, "")) {
          return false;
        }
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, openstudio::Handle())) {
          return false;
        }
        cleanedADU = true;
      }

      setPointer(inletPort(), openstudio::Handle(), false);
      setPointer(outletPort(), openstudio::Handle(), false);

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU || removedFromPlantLoop;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "Refusing to add an already-connected terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "Refusing to connect a terminal without its required reheat coil.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVHeatAndCoolReheat",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      TerminalInsertionPlan plan(thisObject, zoneSplitter, splitterBranchIndex, node, inletPort(), outletPort(), zoneHVACAirDistributionUnit(),
                                 thermalZone);
      return plan.apply(failureStage == AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration);
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AvailabilityScheduleName);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctVAVHeatAndCoolReheat", "Availability", schedule);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AvailabilityScheduleName, ""));
    }

    HVACComponent AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setReheatCoil(const HVACComponent& heatingCoilName) {
      if (heatingCoilName.model() != model()) {
        return false;
      }
      return setPointer(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ReheatCoilName, heatingCoilName.handle(), false);
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::minimumAirFlowTurndownSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumAirFlowTurndownScheduleName);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumAirFlowTurndownScheduleName,
                                           "AirTerminalSingleDuctVAVHeatAndCoolReheat", "Minimum Air Flow Turndown", schedule);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::resetMinimumAirFlowTurndownSchedule() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumAirFlowTurndownScheduleName, ""));
    }

    boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
      (void)result;
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::zoneMinimumAirFlowFraction() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ZoneMinimumAirFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
    }

    boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate,
                       maximumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize");
      OS_ASSERT(result);
      (void)result;
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumHotWaterorSteamFlowRate,
                       minimumHotWaterorSteamFlowRate);
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumReheatAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumReheatAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
    }

    unsigned AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AirInletNodeName;
    }

    unsigned AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AirOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
