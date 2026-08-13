/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
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
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

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

    bool syncFanAvailabilityWithLoop(HVACComponent& fan, Schedule& schedule) {
      if (fan.iddObject().type() == IddObjectType::Fan_ConstantVolume) {
        return fan.setPointer(openstudio::Fan_ConstantVolumeFields::AvailabilityScheduleName, schedule.handle());
      }
      if (fan.iddObject().type() == IddObjectType::Fan_SystemModel) {
        return fan.setPointer(openstudio::Fan_SystemModelFields::AvailabilityScheduleName, schedule.handle());
      }
      return false;
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
                                                    boost::optional<ThermalZone> thermalZone) {
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

        auto plan = std::unique_ptr<InsertionPlan>(new InsertionPlan(terminalImpl, std::move(airLoop), std::move(splitter), branchIndex,
                                                                     std::move(outletNode), std::move(inletNode), !inletNodeExisted,
                                                                     std::move(thermalZone), std::move(secondaryNode), !secondaryNodeExisted));
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

      bool commit() {
        OS_ASSERT(m_state == State::Prepared);
        auto fanObject = m_terminalImpl->fan();
        auto loopAvailability = m_airLoop.availabilitySchedule();
        if (!syncFanAvailabilityWithLoop(fanObject, loopAvailability)) {
          return false;
        }
        m_state = State::Committed;
        return true;
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
                    boost::optional<Node> secondaryNode, bool secondaryNodeCreated)
        : m_terminalImpl(&terminalImpl),
          m_airLoop(std::move(airLoop)),
          m_splitter(std::move(splitter)),
          m_branchIndex(branchIndex),
          m_outletNode(std::move(outletNode)),
          m_inletNode(std::move(inletNode)),
          m_inletNodeCreated(inletNodeCreated),
          m_thermalZone(std::move(thermalZone)),
          m_secondaryNode(std::move(secondaryNode)),
          m_secondaryNodeCreated(secondaryNodeCreated) {}

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

        if (!m_splitter.setOutletModelObject(m_branchIndex, m_inletNode.cast<ModelObject>())) {
          return false;
        }
        m_splitterRewired = true;

        if (!m_terminalImpl->setPointer(m_terminalImpl->inletPort(), m_inletNode.handle(), false)) {
          return false;
        }
        m_inletAssigned = true;
        if (!m_terminalImpl->setPointer(m_terminalImpl->outletPort(), m_outletNode.handle(), false)) {
          return false;
        }
        m_outletAssigned = true;

        if (!m_thermalZone) {
          return true;
        }

        OS_ASSERT(m_secondaryNode && m_zoneConnections);
        if (!m_terminalImpl->setPointer(m_terminalImpl->secondaryAirInletPort(), m_secondaryNode->handle(), false)) {
          return false;
        }
        m_secondaryAssigned = true;

        const auto originalExhaustNodes = m_zoneConnections->zoneAirExhaustNodes();
        const bool wasExhaustRegistered = std::ranges::find(originalExhaustNodes, *m_secondaryNode) != originalExhaustNodes.end();
        const bool exhaustResult = m_zoneConnections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->addZoneAirExhaustNode(*m_secondaryNode);
        const auto currentExhaustNodes = m_zoneConnections->zoneAirExhaustNodes();
        m_exhaustRegistered = !wasExhaustRegistered && (std::ranges::find(currentExhaustNodes, *m_secondaryNode) != currentExhaustNodes.end());
        if (!exhaustResult) {
          return false;
        }

        if (m_airDistributionUnit) {
          if (!m_airDistributionUnit->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(m_outletNode)) {
            return false;
          }
          m_aduUpdated = true;
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
        const bool hadExternalTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                                         || static_cast<bool>(resolvedNodeTarget(secondaryAirInletPort()))
                                         || static_cast<bool>(thermalZoneContainingTerminal(model(), terminal))
                                         || static_cast<bool>(zoneHVACAirDistributionUnit());
        if (context && hadExternalTopology) {
          // An incomplete air terminal may still own a valid plant-connected
          // reheat coil. Detach only the invalid air/zone projection here.
          if (reheatComponent) {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, Handle(), false));
          }
          const bool detached = removeFromLoop();
          if (reheatComponent) {
            OS_ASSERT(setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, reheatComponent->handle(), false));
          }
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

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctParallelPIUReheat_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto ownedChildren = children();
      const bool hadTopology = static_cast<bool>(inletModelObject()) || static_cast<bool>(outletModelObject())
                               || static_cast<bool>(secondaryAirInletNode()) || static_cast<bool>(thermalZoneContainingTerminal(model(), thisObject))
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
      if (!maintainContainedAirPath()) {
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

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      if (!thermalZone && outletNode) {
        if (auto outletZoneNode = outletNode->optionalCast<Node>()) {
          thermalZone = owningThermalZoneForZoneNode(model(), *outletZoneNode);
        }
      }
      auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);
      auto plantLoop = reheat ? reheat->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};
      auto secondaryNode = secondaryAirInletNode();

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

      if (thermalZone) {
        unregisterTerminalFromZone(*thermalZone, thisObject);
      }

      bool removedSecondaryNode = false;
      if (secondaryNode) {
        auto zoneImpl = thermalZone ? thermalZone->getImpl<detail::ThermalZone_Impl>() : nullptr;
        if (zoneImpl) {
          auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
          if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeZoneAirExhaustNode(*secondaryNode)) {
            return false;
          }
        }

        if (!setPointer(secondaryAirInletPort(), openstudio::Handle(), false)) {
          return false;
        }

        const auto secondaryNodeHandle = secondaryNode->handle();
        secondaryNode->remove();
        removedSecondaryNode = !model().getObject(secondaryNodeHandle);
        if (!removedSecondaryNode) {
          return false;
        }
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

      bool removedFromPlantLoop = false;
      if (plantLoop && reheat) {
        if (!plantLoop->removeDemandBranchWithComponent(*reheat)) {
          return false;
        }
        removedFromPlantLoop = true;
      }

      if (!maintainContainedAirPath()) {
        return false;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || removedSecondaryNode || cleanedADU || removedFromPlantLoop;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::addToNode(Node& node) {
      return addToNode(node, AddToNodeFailureStage::None);
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::addToNode(Node& node, AddToNodeFailureStage failureStage) {
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

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      const auto thisNode = node.cast<ModelObject>();
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
      auto mixerInlet = airLoopImpl->effectiveDemandReturnNodeForBranchStart(node);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires one effective ZoneMixer return for the selected ZoneSplitter branch.");
        return false;
      }
      auto thermalZone = owningThermalZoneForZoneNode(model(), node);
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
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto insertion = InsertionPlan::prepare(*this, *airLoop, zoneSplitter, splitterBranchIndex, node, thermalZone);
      if (!insertion) {
        return false;
      }
      if (failureStage == AddToNodeFailureStage::AfterTopologyPrepared) {
        return false;
      }
      if (!maintainContainedAirPath()) {
        insertion.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
      if (!insertion->commit()) {
        insertion.reset();
        OS_ASSERT(maintainContainedAirPath());
        return false;
      }
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
