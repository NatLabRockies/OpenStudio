/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
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
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    void assertSuccessfulMutation(bool result) {
      OS_ASSERT(result);
      (void)result;
    }

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeReheat& terminal) {
      terminal.autosizeMaximumAirFlowRate();
      terminal.autosizeMaximumHotWaterorSteamFlowRate();
      assertSuccessfulMutation(terminal.setMinimumHotWaterorSteamFlowRate(0.0));
      assertSuccessfulMutation(terminal.setConvergenceTolerance(0.001));
      assertSuccessfulMutation(terminal.setMaximumReheatAirTemperature(35.0));
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

        return true;
      }

      void commit() {
        m_committed = true;
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

      bool setTerminalPointer(unsigned fieldIndex, const Handle& targetHandle) {
        auto terminalImpl = m_terminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
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

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    assertSuccessfulMutation(setAvailabilitySchedule(alwaysOn));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model, Schedule& availabilitySchedule,
                                                                                       HVACComponent& reheatCoil)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    assertSuccessfulMutation(setAvailabilitySchedule(availabilitySchedule));
    assertSuccessfulMutation(setReheatCoil(reheatCoil));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat;
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->addToNode(node);
  }

  Schedule AirTerminalSingleDuctConstantVolumeReheat::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent AirTerminalSingleDuctConstantVolumeReheat::reheatCoil() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->reheatCoil();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setReheatCoil(const HVACComponent& coil) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setReheatCoil(coil);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetReheatCoil() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetReheatCoil();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumAirFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMinimumHotWaterorSteamFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMinimumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMinimumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::convergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->convergenceTolerance();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetConvergenceTolerance();
  }

  double AirTerminalSingleDuctConstantVolumeReheat::maximumReheatAirTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumReheatAirTemperature();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumReheatAirTemperatureDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumReheatAirTemperatureDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
  }

  void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumReheatAirTemperature() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumReheatAirTemperature();
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::inletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName;
  }

  unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::outletPort() const {
    return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeReheat_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeReheat_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeReheat_Impl::remove() {
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

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      auto plantRemovalPlan = demandBranchRemovalPlan(coil);
      if (!plantRemovalPlan.valid) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
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
        const auto branchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));
        const auto mixerInlet = airLoop->zoneMixer().inletModelObject(branchIndex);
        if (!mixerInlet || ((*mixerInlet != *outletNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet))) {
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

      if (!maintainContainedAirPath()) {
        return false;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU || removedFromPlantLoop;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
      if (node.model() != model()) {
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Refusing to add an already-connected terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Refusing to connect a terminal without its required reheat coil.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
        return false;
      }

      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto plan = std::make_unique<TerminalInsertionPlan>(thisObject, zoneSplitter, splitterBranchIndex, node, inletPort(), outletPort(),
                                                          zoneHVACAirDistributionUnit(), thermalZone);
      if (!plan->apply(failureStage == AddToNodeFailureStage::AfterADUUpdateBeforeZoneRegistration)) {
        return false;
      }
      if (!maintainContainedAirPath()) {
        plan.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      plan->commit();
      return true;
    }

    Schedule AirTerminalSingleDuctConstantVolumeReheat_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeReheat_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeReheat", "Availability", schedule);
    }

    HVACComponent AirTerminalSingleDuctConstantVolumeReheat_Impl::reheatCoil() const {
      auto coil =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setReheatCoil(const HVACComponent& coil) {
      if (coil.model() != model()) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::Coil_Heating_Fuel) && (iddObjectType != IddObjectType::Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeReheat",
                 "Unsupported reheat coil type '" << coil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeReheat.");
        return false;
      }

      auto terminal = getObject<ModelObject>();
      auto previousCoil =
        terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (previousCoil && previousCoil->handle() == coil.handle()) {
        return maintainContainedAirPath();
      }
      if (auto owner = coil.containingHVACComponent(); owner && owner->handle() != terminal.handle()) {
        return false;
      }
      if (iddObjectType == IddObjectType::Coil_Heating_Electric) {
        if (coil.getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName)
            || coil.getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName)) {
          return false;
        }
      } else if (iddObjectType == IddObjectType::Coil_Heating_Fuel) {
        if (coil.getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName)
            || coil.getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName)) {
          return false;
        }
      } else if (iddObjectType == IddObjectType::Coil_Heating_Water) {
        if (coil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName)
            || coil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)) {
          return false;
        }
      }

      resetReheatCoil();
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, coil.handle(), false)) {
        if (previousCoil) {
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, previousCoil->handle(), false));
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      if (!maintainContainedAirPath()) {
        resetReheatCoil();
        if (previousCoil) {
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, previousCoil->handle(), false));
          OS_ASSERT(maintainContainedAirPath());
        }
        return false;
      }
      return true;
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetReheatCoil() {
      if (auto previousCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName)) {
        const auto type = previousCoil->iddObject().type();
        if (type == IddObjectType::Coil_Heating_Electric) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Fuel) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Water) {
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(previousCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
      }
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, ""));
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::doCanonicalize(LoadContext& context) {
      if (!repairContainedAirPath(context)) {
        detail::addLoadError(context, "Failed to repair contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '"
                                        + getObject<ModelObject>().nameString() + "'.");
      }
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(nullptr);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(&context);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::reconcileContainedAirPath(LoadContext* context) {
      auto terminal = getObject<ModelObject>();
      auto coil = terminal.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
      if (coil && context) {
        const auto type = coil->iddObject().type();
        const bool supported =
          (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel) || (type == IddObjectType::Coil_Heating_Water);
        const auto owner = coil->containingHVACComponent();
        if (!supported || (owner && owner->handle() != terminal.handle())) {
          detail::addLoadWarning(*context, "Dropped " + std::string(supported ? "shared" : "unsupported")
                                             + " reheat-coil reference from AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString()
                                             + "'.");
          OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, Handle(), false));
          coil = boost::none;
        }
      }
      if (!coil) {
        const auto previousName = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, false, true).value_or("");
        const auto previousType =
          getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, false, true).value_or("");
        const bool hadExternalTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                                         || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal))
                                         || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology && !removeFromLoop()) {
          detail::addLoadError(*context, "Could not detach incomplete AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString()
                                           + "' from its external topology.");
          return false;
        }
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, ""));
        OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, ""));
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        if ((!previousName.empty() || !previousType.empty() || hadExternalTopology) && context) {
          detail::addLoadWarning(*context, "Detached incomplete AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString()
                                             + "' and cleared its unresolved reheat-coil reference.");
        }
        return true;
      }
      const auto coilType = coil->iddObject().type();
      if ((coilType != IddObjectType::Coil_Heating_Electric) && (coilType != IddObjectType::Coil_Heating_Fuel)
          && (coilType != IddObjectType::Coil_Heating_Water)) {
        return false;
      }
      bool changed =
        !terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType)
        || !openstudio::istringEqual(terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType).get(),
                                     coil->iddObject().name());
      if (!setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType, coil->iddObject().name())) {
        return false;
      }

      auto inletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName);
      auto outletNode = resolvedNodeTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName);
      if (!inletNode || !outletNode) {
        const auto type = coil->iddObject().type();
        if (type == IddObjectType::Coil_Heating_Electric) {
          changed = changed || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName))
                    || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, Handle()));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Fuel) {
          changed = changed || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName))
                    || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, Handle()));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, Handle()));
        } else if (type == IddObjectType::Coil_Heating_Water) {
          changed = changed || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName))
                    || static_cast<bool>(coil->getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, Handle()));
          OS_ASSERT(coil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, Handle()));
        }
        if (changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return true;
      }

      const auto type = coil->iddObject().type();
      if (type == IddObjectType::Coil_Heating_Electric) {
        const auto previousInlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName);
        const auto previousOutlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName);
        changed = changed || previousInlet != inletNode || previousOutlet != outletNode;
        const bool result = coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirInletNodeName, inletNode->handle())
                            && coil->setPointer(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName, outletNode->handle());
        for (auto displacedNode : {previousInlet, previousOutlet}) {
          if (result && displacedNode && *displacedNode != *inletNode && *displacedNode != *outletNode && displacedNode->sources().empty()
              && model().getObject(displacedNode->handle())) {
            displacedNode->remove();
          }
        }
        if (result && changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return result;
      }
      if (type == IddObjectType::Coil_Heating_Fuel) {
        const auto previousInlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName);
        const auto previousOutlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName);
        changed = changed || previousInlet != inletNode || previousOutlet != outletNode;
        const bool result = coil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, inletNode->handle())
                            && coil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, outletNode->handle());
        for (auto displacedNode : {previousInlet, previousOutlet}) {
          if (result && displacedNode && *displacedNode != *inletNode && *displacedNode != *outletNode && displacedNode->sources().empty()
              && model().getObject(displacedNode->handle())) {
            displacedNode->remove();
          }
        }
        if (result && changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return result;
      }
      if (type == IddObjectType::Coil_Heating_Water) {
        const auto previousInlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
        const auto previousOutlet = coil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
        changed = changed || previousInlet != inletNode || previousOutlet != outletNode;
        const bool result = coil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, inletNode->handle())
                            && coil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, outletNode->handle());
        for (auto displacedNode : {previousInlet, previousOutlet}) {
          if (result && displacedNode && *displacedNode != *inletNode && *displacedNode != *outletNode && displacedNode->sources().empty()
              && model().getObject(displacedNode->handle())) {
            displacedNode->remove();
          }
        }
        if (result && changed && context) {
          detail::addLoadInfo(*context,
                              "Reconciled contained air path for AirTerminal:SingleDuct:ConstantVolume:Reheat '" + terminal.nameString() + "'.");
        }
        return result;
      }
      return false;
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
      (void)result;
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate,
                       maximumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize");
      OS_ASSERT(result);
      (void)result;
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate,
                       minimumHotWaterorSteamFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMinimumHotWaterorSteamFlowRate() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, ""));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::convergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, convergenceTolerance);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, ""));
    }

    double AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumReheatAirTemperature() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumReheatAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature);
    }

    bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
      return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
    }

    void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumReheatAirTemperature() {
      OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
