/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirTerminalSingleDuctVAVReheatVariableSpeedFan.hpp"
#include "AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "HVACComponent.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan_FieldEnums.hxx>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/Fan_OnOff_FieldEnums.hxx>
#include <utilities/idd/Fan_VariableVolume_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

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
          m_thermalZone(std::move(thermalZone)),
          m_previousADUOutletNode(m_adu ? m_adu->outletNode() : boost::optional<Node>{}) {
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

      bool apply() {
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
          (void)unregisterTerminalFromThermalZone(m_terminal, *m_thermalZone);
        }
        if (m_adu && m_aduUpdated) {
          if (m_previousADUOutletNode) {
            (void)m_adu->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(*m_previousADUOutletNode);
          } else {
            (void)m_adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle());
          }
        }
        if (m_outletAssigned) {
          (void)setTerminalPointer(m_outletPort, openstudio::Handle());
        }
        if (m_inletAssigned) {
          (void)setTerminalPointer(m_inletPort, openstudio::Handle());
        }
        if (m_splitterRewired) {
          (void)m_splitter.setOutletModelObject(m_branchIndex, m_outletNode.cast<ModelObject>());
        }
        if (m_createdInletNode && m_inletNode && m_terminal.model().getObject(m_inletNode->handle())) {
          m_inletNode->remove();
        }
      }

      bool setTerminalPointer(unsigned fieldIndex, const openstudio::Handle& targetHandle) {
        auto terminalImpl = m_terminal.getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>();
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
      boost::optional<Node> m_previousADUOutletNode;
      boost::optional<Node> m_inletNode;
      bool m_createdInletNode = false;
      bool m_splitterRewired = false;
      bool m_inletAssigned = false;
      bool m_outletAssigned = false;
      bool m_aduUpdated = false;
      bool m_zoneRegistered = false;
      bool m_committed = false;
    };

    bool isValidFanType(const IddObjectType type) {
      return (type == IddObjectType::Fan_ConstantVolume) || (type == IddObjectType::Fan_SystemModel) || (type == IddObjectType::Fan_OnOff)
             || (type == IddObjectType::Fan_VariableVolume) || (type == IddObjectType::OS_Fan_ConstantVolume)
             || (type == IddObjectType::OS_Fan_SystemModel) || (type == IddObjectType::OS_Fan_OnOff)
             || (type == IddObjectType::OS_Fan_VariableVolume);
    }

    bool isValidHeatingCoilType(const IddObjectType type) {
      return (type == IddObjectType::OS_Coil_Heating_Gas) || (type == IddObjectType::OS_Coil_Heating_Electric)
             || (type == IddObjectType::OS_Coil_Heating_Water) || (type == IddObjectType::Coil_Heating_Fuel)
             || (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Water);
    }

    bool setFanAvailabilitySchedule(HVACComponent& fan, Schedule& schedule) {
      const auto type = fan.iddObject().type();
      if (type == IddObjectType::Fan_ConstantVolume || type == IddObjectType::OS_Fan_ConstantVolume) {
        return fan.setPointer(openstudio::Fan_ConstantVolumeFields::AvailabilityScheduleName, schedule.handle());
      }
      if (type == IddObjectType::Fan_OnOff || type == IddObjectType::OS_Fan_OnOff) {
        return fan.setPointer(openstudio::Fan_OnOffFields::AvailabilityScheduleName, schedule.handle());
      }
      if (type == IddObjectType::Fan_VariableVolume || type == IddObjectType::OS_Fan_VariableVolume) {
        return fan.setPointer(openstudio::Fan_VariableVolumeFields::AvailabilityScheduleName, schedule.handle());
      }
      if (type == IddObjectType::Fan_SystemModel || type == IddObjectType::OS_Fan_SystemModel) {
        return fan.setPointer(openstudio::Fan_SystemModelFields::AvailabilityScheduleName, schedule.handle());
      }
      return false;
    }

  }  // namespace

  AirTerminalSingleDuctVAVReheatVariableSpeedFan::AirTerminalSingleDuctVAVReheatVariableSpeedFan(const Model& model)
    : StraightComponent(AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumCoolingAirFlowRate();
    autosizeMaximumHeatingAirFlowRate();
    OS_ASSERT(setZoneMinimumAirFlowFraction(0.3));
    autosizeMaximumHotWaterorSteamFlowRate();
    OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
    OS_ASSERT(setHeatingConvergenceTolerance(0.001));
  }

  AirTerminalSingleDuctVAVReheatVariableSpeedFan::AirTerminalSingleDuctVAVReheatVariableSpeedFan(
    std::shared_ptr<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan;
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> AirTerminalSingleDuctVAVReheatVariableSpeedFan::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent AirTerminalSingleDuctVAVReheatVariableSpeedFan::fan() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->fan();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setFan(HVACComponent& fan) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setFan(fan);
  }

  HVACComponent AirTerminalSingleDuctVAVReheatVariableSpeedFan::heatingCoil() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->heatingCoil();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setHeatingCoil(HVACComponent& coil) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setHeatingCoil(coil);
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan::maximumCoolingAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->maximumCoolingAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMaximumCoolingAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMaximumCoolingAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMaximumCoolingAirFlowRate(maximumCoolingAirFlowRate);
  }

  void AirTerminalSingleDuctVAVReheatVariableSpeedFan::autosizeMaximumCoolingAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->autosizeMaximumCoolingAirFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan::maximumHeatingAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->maximumHeatingAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMaximumHeatingAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMaximumHeatingAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMaximumHeatingAirFlowRate(maximumHeatingAirFlowRate);
  }

  void AirTerminalSingleDuctVAVReheatVariableSpeedFan::autosizeMaximumHeatingAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->autosizeMaximumHeatingAirFlowRate();
  }

  double AirTerminalSingleDuctVAVReheatVariableSpeedFan::zoneMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->zoneMinimumAirFlowFraction();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
  }

  boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan::maximumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->maximumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMaximumHotWaterorSteamFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctVAVReheatVariableSpeedFan::autosizeMaximumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctVAVReheatVariableSpeedFan::minimumHotWaterorSteamFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->minimumHotWaterorSteamFlowRate();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMinimumHotWaterorSteamFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
  }

  void AirTerminalSingleDuctVAVReheatVariableSpeedFan::resetMinimumHotWaterorSteamFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->resetMinimumHotWaterorSteamFlowRate();
  }

  double AirTerminalSingleDuctVAVReheatVariableSpeedFan::heatingConvergenceTolerance() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->heatingConvergenceTolerance();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void AirTerminalSingleDuctVAVReheatVariableSpeedFan::resetHeatingConvergenceTolerance() {
    getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->resetHeatingConvergenceTolerance();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AirInletNodeName;
    }

    unsigned AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AirOutletNodeName;
    }

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::children() const {
      std::vector<ModelObject> result;
      auto thisObject = getObject<ModelObject>();
      if (auto fanComponent =
            thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName)) {
        result.push_back(*fanComponent);
      }
      if (auto coil =
            thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName)) {
        result.push_back(*coil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::remove() {
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

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      if (!thermalZone && outletNode) {
        if (auto outletZoneNode = outletNode->optionalCast<Node>()) {
          thermalZone = owningThermalZoneForBranchNode(model(), *outletZoneNode);
        }
      }
      auto coil = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName);
      auto plantLoop = coil ? coil->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};

      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode = splitter.outletModelObject(splitterBranchIndex) == *inletNode;
          }
        }
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

      if (!setPointer(inletPort(), openstudio::Handle(), false)) {
        return false;
      }
      if (!setPointer(outletPort(), openstudio::Handle(), false)) {
        return false;
      }

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      if (plantLoop && coil) {
        if (!plantLoop->removeDemandBranchWithComponent(*coil)) {
          return false;
        }
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || cleanedADU || static_cast<bool>(plantLoop);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "addToNode requires a node in the same model as the terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "Refusing to add an already-connected terminal to node '" << node.nameString() << "'.");
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      const auto fan = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName);
      const auto coil =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName);
      if (!fan || !coil) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "Refusing to connect a terminal without its required fan and heating coil.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
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
      return plan.apply();
    }

    boost::optional<Schedule> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AvailabilityScheduleName);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setAvailabilitySchedule(Schedule& schedule) {
      if (!ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::AvailabilityScheduleName,
                                         "AirTerminalSingleDuctVAVReheatVariableSpeedFan", "Availability", schedule)) {
        return false;
      }

      if (auto fanComponent = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName)) {
        if (!setFanAvailabilitySchedule(*fanComponent, schedule)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                   "Failed to synchronize the fan availability schedule for " << briefDescription() << ".");
          return false;
        }
      }

      return true;
    }

    HVACComponent AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::fan() const {
      auto fanComponent =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName);
      OS_ASSERT(fanComponent);
      return *fanComponent;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setFan(HVACComponent& fanComponent) {
      if (fanComponent.model() != model()) {
        return false;
      }
      if (!isValidFanType(fanComponent.iddObject().type())) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "Unsupported fan type '" << fanComponent.iddObject().name() << "' for AirTerminalSingleDuctVAVReheatVariableSpeedFan.");
        return false;
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanName, fanComponent.handle(), false)) {
        return false;
      }
      if (!setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::FanObjectType, fanComponent.iddObject().name())) {
        return false;
      }
      if (auto schedule = availabilitySchedule()) {
        if (!setFanAvailabilitySchedule(fanComponent, *schedule)) {
          return false;
        }
      }
      return true;
    }

    HVACComponent AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::heatingCoil() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setHeatingCoil(HVACComponent& coil) {
      if (coil.model() != model()) {
        return false;
      }
      if (!isValidHeatingCoilType(coil.iddObject().type())) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctVAVReheatVariableSpeedFan",
                 "Unsupported heating coil type '" << coil.iddObject().name() << "' for AirTerminalSingleDuctVAVReheatVariableSpeedFan.");
        return false;
      }
      if (!setPointer(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilName, coil.handle(), false)) {
        return false;
      }
      return setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingCoilObjectType, coil.iddObject().name());
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::maximumCoolingAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMaximumCoolingAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, maximumCoolingAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::autosizeMaximumCoolingAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::maximumHeatingAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMaximumHeatingAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, maximumHeatingAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::autosizeMaximumHeatingAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::zoneMinimumAirFlowFraction() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::ZoneMinimumAirFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::maximumHotWaterorSteamFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate,
                                    maximumHotWaterorSteamFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::minimumHotWaterorSteamFlowRate() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate,
                                    minimumHotWaterorSteamFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::resetMinimumHotWaterorSteamFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate, "");
      OS_ASSERT(result);
    }

    double AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::heatingConvergenceTolerance() const {
      const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance);
    }

    bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::resetHeatingConvergenceTolerance() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
