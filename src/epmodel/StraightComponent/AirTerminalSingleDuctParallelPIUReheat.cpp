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
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
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
      return (type == IddObjectType::Fan_ConstantVolume) || (type == IddObjectType::Fan_SystemModel) || (type == IddObjectType::OS_Fan_ConstantVolume)
             || (type == IddObjectType::OS_Fan_SystemModel);
    }

    bool isSupportedParallelPIUReheatCoil(const HVACComponent& hvacComponent) {
      const auto type = hvacComponent.iddObject().type();
      return (type == IddObjectType::Coil_Heating_Electric) || (type == IddObjectType::Coil_Heating_Fuel)
             || (type == IddObjectType::Coil_Heating_Water) || (type == IddObjectType::OS_Coil_Heating_Electric)
             || (type == IddObjectType::OS_Coil_Heating_Gas) || (type == IddObjectType::OS_Coil_Heating_Water);
    }

    boost::optional<ThermalZone> owningThermalZoneForZoneNode(const Model& model, const Node& node) {
      for (const auto& thermalZone : model.getConcreteModelObjects<ThermalZone>()) {
        if (thermalZone.zoneAirNode() == node) {
          return thermalZone;
        }
      }
      return boost::none;
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

  }  // namespace

  AirTerminalSingleDuctParallelPIUReheat::AirTerminalSingleDuctParallelPIUReheat(const Model& model)
    : StraightComponent(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumPrimaryAirFlowRate();
    autosizeMaximumSecondaryAirFlowRate();
    autosizeMinimumPrimaryAirFlowFraction();
    autosizeFanOnFlowFraction();
    autosizeMaximumHotWaterorSteamFlowRate();
    OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
    OS_ASSERT(setConvergenceTolerance(0.001));
    OS_ASSERT(setFanControlType("ConstantSpeed"));
    OS_ASSERT(setMinimumFanTurnDownRatio(0.3));
    OS_ASSERT(setHeatingControlType("Staged"));
    OS_ASSERT(setDesignHeatingDischargeAirTemperature(32.1));
    OS_ASSERT(setHighLimitHeatingDischargeAirTemperature(37.7));
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

    autosizeMaximumPrimaryAirFlowRate();
    autosizeMaximumSecondaryAirFlowRate();
    autosizeMinimumPrimaryAirFlowFraction();
    autosizeFanOnFlowFraction();
    autosizeMaximumHotWaterorSteamFlowRate();
    OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
    OS_ASSERT(setConvergenceTolerance(0.001));
    OS_ASSERT(setFanControlType("ConstantSpeed"));
    OS_ASSERT(setMinimumFanTurnDownRatio(0.3));
    OS_ASSERT(setHeatingControlType("Staged"));
    OS_ASSERT(setDesignHeatingDischargeAirTemperature(32.1));
    OS_ASSERT(setHighLimitHeatingDischargeAirTemperature(37.7));
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
      if (!setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanName, hvacComponent.handle(), false)) {
        return false;
      }

      if (hvacComponent.iddObject().type() == IddObjectType::Fan_ConstantVolume
          || hvacComponent.iddObject().type() == IddObjectType::OS_Fan_ConstantVolume) {
        return setFanControlType("ConstantSpeed");
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
      return setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName, hvacComponent.handle(), false);
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
      auto reheat = thisObject.getModelObjectTarget<openstudio::epmodel::HVACComponent>(
        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ReheatCoilName);

      removeFromLoop();

      if (reheat) {
        if (auto plantLoop = reheat->plantLoop()) {
          plantLoop->removeDemandBranchWithComponent(*reheat);
        }
      }

      return HVACComponent_Impl::remove();
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
            const auto mixer = airLoop->zoneMixer();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode =
              (splitter.outletModelObject(splitterBranchIndex) == *inletNode) && (mixer.inletModelObject(splitterBranchIndex) == *outletNode);
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

        if (secondaryNode->sources().empty()) {
          secondaryNode->remove();
          removedSecondaryNode = true;
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

      return removedFromAirLoop || static_cast<bool>(thermalZone) || removedSecondaryNode || cleanedADU || removedFromPlantLoop;
    }

    bool AirTerminalSingleDuctParallelPIUReheat_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires a node in the same model as the parallel PIU terminal.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
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
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      if (*mixerInlet != thisNode) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires the ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << " to match the drop node.");
        return false;
      }

      auto thermalZone = owningThermalZoneForZoneNode(model(), node);
      if (!thermalZone) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode requires the drop node to be the current zone-branch node for an attached thermal zone.");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        return false;
      }

      if (!setPointer(outletPort(), node.handle(), false)) {
        return false;
      }

      const std::string secondaryNodeName = node.nameString() + " - " + thisObject.nameString() + " Secondary Air Inlet Node";
      auto secondaryNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(secondaryNodeName);
      if (!setPointer(secondaryAirInletPort(), secondaryNode.handle(), false)) {
        return false;
      }

      auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
      if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->addZoneAirExhaustNode(secondaryNode)) {
        return false;
      }

      if (auto adu = zoneHVACAirDistributionUnit()) {
        if (!adu->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node)) {
          return false;
        }
      }

      auto fanObject = fan();
      auto loopAvailability = airLoop->availabilitySchedule();
      if (!syncFanAvailabilityWithLoop(fanObject, loopAvailability)) {
        return false;
      }

      if (!registerTerminalWithZone(*thermalZone, thisObject)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctParallelPIUReheat",
                 "addToNode failed to register the parallel PIU terminal with the owning thermal zone.");
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
