/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"
#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil_Impl.hpp"

#include "HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_FourPipeFanCoil_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACFourPipeFanCoil::ZoneHVACFourPipeFanCoil(const Model& model) : ZoneHVACComponent(ZoneHVACFourPipeFanCoil::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>());

    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));

    auto capacityMethods = ZoneHVACFourPipeFanCoil::capacityControlMethodValues();
    OS_ASSERT(!capacityMethods.empty());
    OS_ASSERT(setCapacityControlMethod(capacityMethods.front()));

    auto mixerTypes = ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues();
    OS_ASSERT(!mixerTypes.empty());
    OS_ASSERT(setOutdoorAirMixerObjectType(mixerTypes.front()));

    autosizeMaximumSupplyAirFlowRate();
    autosizeMaximumOutdoorAirFlowRate();
    autosizeMaximumColdWaterFlowRate();
    autosizeMaximumHotWaterFlowRate();
    autosizeMinimumSupplyAirTemperatureInCoolingMode();
    autosizeMaximumSupplyAirTemperatureInHeatingMode();
  }

  ZoneHVACFourPipeFanCoil::ZoneHVACFourPipeFanCoil(std::shared_ptr<detail::ZoneHVACFourPipeFanCoil_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACFourPipeFanCoil::iddObjectType() {
    return IddObjectType::ZoneHVAC_FourPipeFanCoil;
  }

  std::vector<std::string> ZoneHVACFourPipeFanCoil::capacityControlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_FourPipeFanCoilFields::CapacityControlMethod);
  }

  std::vector<std::string> ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerObjectType);
  }

  Schedule ZoneHVACFourPipeFanCoil::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACFourPipeFanCoil::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent ZoneHVACFourPipeFanCoil::supplyAirFan() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->supplyAirFan();
  }

  HVACComponent ZoneHVACFourPipeFanCoil::coolingCoil() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->coolingCoil();
  }

  HVACComponent ZoneHVACFourPipeFanCoil::heatingCoil() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->heatingCoil();
  }

  std::string ZoneHVACFourPipeFanCoil::capacityControlMethod() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->capacityControlMethod();
  }

  bool ZoneHVACFourPipeFanCoil::setCapacityControlMethod(const std::string& capacityControlMethod) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setCapacityControlMethod(capacityControlMethod);
  }

  boost::optional<double> ZoneHVACFourPipeFanCoil::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACFourPipeFanCoil::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  bool ZoneHVACFourPipeFanCoil::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACFourPipeFanCoil::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  double ZoneHVACFourPipeFanCoil::lowSpeedSupplyAirFlowRatio() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->lowSpeedSupplyAirFlowRatio();
  }

  bool ZoneHVACFourPipeFanCoil::isLowSpeedSupplyAirFlowRatioDefaulted() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isLowSpeedSupplyAirFlowRatioDefaulted();
  }

  bool ZoneHVACFourPipeFanCoil::setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setLowSpeedSupplyAirFlowRatio(lowSpeedSupplyAirFlowRatio);
  }

  void ZoneHVACFourPipeFanCoil::resetLowSpeedSupplyAirFlowRatio() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetLowSpeedSupplyAirFlowRatio();
  }

  double ZoneHVACFourPipeFanCoil::mediumSpeedSupplyAirFlowRatio() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->mediumSpeedSupplyAirFlowRatio();
  }

  bool ZoneHVACFourPipeFanCoil::isMediumSpeedSupplyAirFlowRatioDefaulted() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMediumSpeedSupplyAirFlowRatioDefaulted();
  }

  bool ZoneHVACFourPipeFanCoil::setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMediumSpeedSupplyAirFlowRatio(mediumSpeedSupplyAirFlowRatio);
  }

  void ZoneHVACFourPipeFanCoil::resetMediumSpeedSupplyAirFlowRatio() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetMediumSpeedSupplyAirFlowRatio();
  }

  boost::optional<double> ZoneHVACFourPipeFanCoil::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ZoneHVACFourPipeFanCoil::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACFourPipeFanCoil::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  void ZoneHVACFourPipeFanCoil::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  std::string ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectType() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->outdoorAirMixerObjectType();
  }

  bool ZoneHVACFourPipeFanCoil::setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setOutdoorAirMixerObjectType(outdoorAirMixerObjectType);
  }

  boost::optional<Schedule> ZoneHVACFourPipeFanCoil::outdoorAirSchedule() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->outdoorAirSchedule();
  }

  bool ZoneHVACFourPipeFanCoil::setOutdoorAirSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setOutdoorAirSchedule(schedule);
  }

  void ZoneHVACFourPipeFanCoil::resetOutdoorAirSchedule() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetOutdoorAirSchedule();
  }

  bool ZoneHVACFourPipeFanCoil::setSupplyAirFan(HVACComponent& fan) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setSupplyAirFan(fan);
  }

  bool ZoneHVACFourPipeFanCoil::setCoolingCoil(HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setCoolingCoil(coolingCoil);
  }

  bool ZoneHVACFourPipeFanCoil::setHeatingCoil(HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setHeatingCoil(heatingCoil);
  }

  boost::optional<Schedule> ZoneHVACFourPipeFanCoil::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACFourPipeFanCoil::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void ZoneHVACFourPipeFanCoil::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  boost::optional<double> ZoneHVACFourPipeFanCoil::maximumColdWaterFlowRate() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->maximumColdWaterFlowRate();
  }

  bool ZoneHVACFourPipeFanCoil::isMaximumColdWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMaximumColdWaterFlowRateAutosized();
  }

  bool ZoneHVACFourPipeFanCoil::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMaximumColdWaterFlowRate(maximumColdWaterFlowRate);
  }

  void ZoneHVACFourPipeFanCoil::autosizeMaximumColdWaterFlowRate() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->autosizeMaximumColdWaterFlowRate();
  }

  double ZoneHVACFourPipeFanCoil::minimumColdWaterFlowRate() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->minimumColdWaterFlowRate();
  }

  bool ZoneHVACFourPipeFanCoil::isMinimumColdWaterFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMinimumColdWaterFlowRateDefaulted();
  }

  bool ZoneHVACFourPipeFanCoil::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMinimumColdWaterFlowRate(minimumColdWaterFlowRate);
  }

  void ZoneHVACFourPipeFanCoil::resetMinimumColdWaterFlowRate() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetMinimumColdWaterFlowRate();
  }

  double ZoneHVACFourPipeFanCoil::coolingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->coolingConvergenceTolerance();
  }

  bool ZoneHVACFourPipeFanCoil::isCoolingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isCoolingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACFourPipeFanCoil::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  void ZoneHVACFourPipeFanCoil::resetCoolingConvergenceTolerance() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetCoolingConvergenceTolerance();
  }

  boost::optional<double> ZoneHVACFourPipeFanCoil::maximumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->maximumHotWaterFlowRate();
  }

  bool ZoneHVACFourPipeFanCoil::isMaximumHotWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMaximumHotWaterFlowRateAutosized();
  }

  bool ZoneHVACFourPipeFanCoil::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMaximumHotWaterFlowRate(maximumHotWaterFlowRate);
  }

  void ZoneHVACFourPipeFanCoil::autosizeMaximumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->autosizeMaximumHotWaterFlowRate();
  }

  double ZoneHVACFourPipeFanCoil::minimumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->minimumHotWaterFlowRate();
  }

  bool ZoneHVACFourPipeFanCoil::isMinimumHotWaterFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMinimumHotWaterFlowRateDefaulted();
  }

  bool ZoneHVACFourPipeFanCoil::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMinimumHotWaterFlowRate(minimumHotWaterFlowRate);
  }

  void ZoneHVACFourPipeFanCoil::resetMinimumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetMinimumHotWaterFlowRate();
  }

  double ZoneHVACFourPipeFanCoil::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACFourPipeFanCoil::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACFourPipeFanCoil::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void ZoneHVACFourPipeFanCoil::resetHeatingConvergenceTolerance() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->resetHeatingConvergenceTolerance();
  }

  bool ZoneHVACFourPipeFanCoil::isMinimumSupplyAirTemperatureInCoolingModeAutosized() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMinimumSupplyAirTemperatureInCoolingModeAutosized();
  }

  boost::optional<double> ZoneHVACFourPipeFanCoil::minimumSupplyAirTemperatureInCoolingMode() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->minimumSupplyAirTemperatureInCoolingMode();
  }

  bool ZoneHVACFourPipeFanCoil::setMinimumSupplyAirTemperatureInCoolingMode(double minimumSupplyAirTemperatureInCoolingMode) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMinimumSupplyAirTemperatureInCoolingMode(minimumSupplyAirTemperatureInCoolingMode);
  }

  void ZoneHVACFourPipeFanCoil::autosizeMinimumSupplyAirTemperatureInCoolingMode() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->autosizeMinimumSupplyAirTemperatureInCoolingMode();
  }

  bool ZoneHVACFourPipeFanCoil::isMaximumSupplyAirTemperatureInHeatingModeAutosized() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->isMaximumSupplyAirTemperatureInHeatingModeAutosized();
  }

  boost::optional<double> ZoneHVACFourPipeFanCoil::maximumSupplyAirTemperatureInHeatingMode() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->maximumSupplyAirTemperatureInHeatingMode();
  }

  bool ZoneHVACFourPipeFanCoil::setMaximumSupplyAirTemperatureInHeatingMode(double maximumSupplyAirTemperatureInHeatingMode) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setMaximumSupplyAirTemperatureInHeatingMode(maximumSupplyAirTemperatureInHeatingMode);
  }

  void ZoneHVACFourPipeFanCoil::autosizeMaximumSupplyAirTemperatureInHeatingMode() {
    getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->autosizeMaximumSupplyAirTemperatureInHeatingMode();
  }

  namespace detail {

    std::vector<ModelObject> ZoneHVACFourPipeFanCoil_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName)) {
        result.push_back(*fan);
      }
      if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName)) {
        result.push_back(*coolingCoil);
      }
      if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName)) {
        result.push_back(*heatingCoil);
      }
      return result;
    }

    unsigned ZoneHVACFourPipeFanCoil_Impl::inletPort() const {
      return ZoneHVAC_FourPipeFanCoilFields::AirInletNodeName;
    }

    unsigned ZoneHVACFourPipeFanCoil_Impl::outletPort() const {
      return ZoneHVAC_FourPipeFanCoilFields::AirOutletNodeName;
    }

    Schedule ZoneHVACFourPipeFanCoil_Impl::availabilitySchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_FourPipeFanCoilFields::AvailabilityScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_FourPipeFanCoilFields::AvailabilityScheduleName, "ZoneHVACFourPipeFanCoil",
                                           "Availability", schedule);
    }

    std::string ZoneHVACFourPipeFanCoil_Impl::capacityControlMethod() const {
      auto value = getString(ZoneHVAC_FourPipeFanCoilFields::CapacityControlMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setCapacityControlMethod(const std::string& capacityControlMethod) {
      return setString(ZoneHVAC_FourPipeFanCoilFields::CapacityControlMethod, capacityControlMethod);
    }

    std::vector<std::string> ZoneHVACFourPipeFanCoil_Impl::capacityControlMethodValues() const {
      return ZoneHVACFourPipeFanCoil::capacityControlMethodValues();
    }

    boost::optional<double> ZoneHVACFourPipeFanCoil_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::autosizeMaximumSupplyAirFlowRate() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double ZoneHVACFourPipeFanCoil_Impl::lowSpeedSupplyAirFlowRatio() const {
      const auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isLowSpeedSupplyAirFlowRatioDefaulted() const {
      return isEmpty(ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setLowSpeedSupplyAirFlowRatio(double lowSpeedSupplyAirFlowRatio) {
      return setDouble(ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio, lowSpeedSupplyAirFlowRatio);
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetLowSpeedSupplyAirFlowRatio() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio, "");
      OS_ASSERT(result);
    }

    double ZoneHVACFourPipeFanCoil_Impl::mediumSpeedSupplyAirFlowRatio() const {
      const auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMediumSpeedSupplyAirFlowRatioDefaulted() const {
      return isEmpty(ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMediumSpeedSupplyAirFlowRatio(double mediumSpeedSupplyAirFlowRatio) {
      return setDouble(ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio, mediumSpeedSupplyAirFlowRatio);
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetMediumSpeedSupplyAirFlowRatio() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACFourPipeFanCoil_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_FourPipeFanCoilFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::autosizeMaximumOutdoorAirFlowRate() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MaximumOutdoorAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    std::string ZoneHVACFourPipeFanCoil_Impl::outdoorAirMixerObjectType() const {
      auto value = getString(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerObjectType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType) {
      return setString(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerObjectType, outdoorAirMixerObjectType);
    }

    boost::optional<Schedule> ZoneHVACFourPipeFanCoil_Impl::outdoorAirSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirScheduleName);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setOutdoorAirSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirScheduleName, "ZoneHVACFourPipeFanCoil", "Outdoor Air",
                                           schedule);
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetOutdoorAirSchedule() {
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirScheduleName, ""));
    }

    std::vector<std::string> ZoneHVACFourPipeFanCoil_Impl::outdoorAirMixerObjectTypeValues() const {
      return ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues();
    }

    HVACComponent ZoneHVACFourPipeFanCoil_Impl::supplyAirFan() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName);
      OS_ASSERT(fan);
      return *fan;
    }

    HVACComponent ZoneHVACFourPipeFanCoil_Impl::coolingCoil() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    HVACComponent ZoneHVACFourPipeFanCoil_Impl::heatingCoil() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setSupplyAirFan(HVACComponent& fan) {
      bool isAllowedType = false;
      const auto fanType = fan.iddObject().type();

      if (fanType == IddObjectType::OS_Fan_SystemModel || fanType == IddObjectType::Fan_SystemModel) {
        isAllowedType = true;
      } else {
        if (istringEqual(capacityControlMethod(), "ConstantFanVariableFlow")) {
          if (fanType == IddObjectType::OS_Fan_ConstantVolume || fanType == IddObjectType::OS_Fan_OnOff
              || fanType == IddObjectType::Fan_ConstantVolume || fanType == IddObjectType::Fan_OnOff) {
            isAllowedType = true;
          }
        } else if (istringEqual(capacityControlMethod(), "CyclingFan")) {
          if (fanType == IddObjectType::OS_Fan_OnOff || fanType == IddObjectType::Fan_OnOff) {
            isAllowedType = true;
          }
        } else if (istringEqual(capacityControlMethod(), "VariableFanVariableFlow")
                   || istringEqual(capacityControlMethod(), "VariableFanConstantFlow")) {
          if (fanType == IddObjectType::OS_Fan_VariableVolume || fanType == IddObjectType::Fan_VariableVolume) {
            isAllowedType = true;
          }
        }
      }

      if (isAllowedType) {
        return setPointer(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, fan.handle());
      }

      return false;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setCoolingCoil(HVACComponent& coolingCoil) {
      bool isAllowedType = false;
      const auto coolingCoilType = coolingCoil.iddObject().type();
      if ((coolingCoilType == IddObjectType::OS_Coil_Cooling_Water)
          || (coolingCoilType == IddObjectType::OS_CoilSystem_Cooling_Water_HeatExchangerAssisted)
          || (coolingCoilType == IddObjectType::Coil_Cooling_Water)
          || (coolingCoilType == IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted)) {
        isAllowedType = true;
      }

      if (isAllowedType) {
        return setPointer(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, coolingCoil.handle());
      }

      return false;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setHeatingCoil(HVACComponent& heatingCoil) {
      bool isAllowedType = false;
      const auto heatingCoilType = heatingCoil.iddObject().type();
      if ((heatingCoilType == IddObjectType::OS_Coil_Heating_Water) || (heatingCoilType == IddObjectType::OS_Coil_Heating_Electric)
          || (heatingCoilType == IddObjectType::Coil_Heating_Water) || (heatingCoilType == IddObjectType::Coil_Heating_Electric)) {
        isAllowedType = true;
      }

      if (isAllowedType) {
        return setPointer(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, heatingCoil.handle());
      }

      return false;
    }

    boost::optional<Schedule> ZoneHVACFourPipeFanCoil_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanOperatingModeScheduleName, "ZoneHVACFourPipeFanCoil",
                                           "Supply Air Fan Operating Mode", schedule);
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetSupplyAirFanOperatingModeSchedule() {
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanOperatingModeScheduleName, ""));
    }

    boost::optional<double> ZoneHVACFourPipeFanCoil_Impl::maximumColdWaterFlowRate() const {
      return getDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumColdWaterFlowRate, true);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMaximumColdWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_FourPipeFanCoilFields::MaximumColdWaterFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumColdWaterFlowRate, maximumColdWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::autosizeMaximumColdWaterFlowRate() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MaximumColdWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double ZoneHVACFourPipeFanCoil_Impl::minimumColdWaterFlowRate() const {
      const auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMinimumColdWaterFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate, minimumColdWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetMinimumColdWaterFlowRate() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate, "");
      OS_ASSERT(result);
    }

    double ZoneHVACFourPipeFanCoil_Impl::coolingConvergenceTolerance() const {
      const auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isCoolingConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      return setDouble(ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance, coolingConvergenceTolerance);
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetCoolingConvergenceTolerance() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACFourPipeFanCoil_Impl::maximumHotWaterFlowRate() const {
      return getDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumHotWaterFlowRate, true);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMaximumHotWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_FourPipeFanCoilFields::MaximumHotWaterFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumHotWaterFlowRate, maximumHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::autosizeMaximumHotWaterFlowRate() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MaximumHotWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double ZoneHVACFourPipeFanCoil_Impl::minimumHotWaterFlowRate() const {
      const auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMinimumHotWaterFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate, minimumHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetMinimumHotWaterFlowRate() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate, "");
      OS_ASSERT(result);
    }

    double ZoneHVACFourPipeFanCoil_Impl::heatingConvergenceTolerance() const {
      const auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      return setDouble(ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
    }

    void ZoneHVACFourPipeFanCoil_Impl::resetHeatingConvergenceTolerance() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance, "");
      OS_ASSERT(result);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMinimumSupplyAirTemperatureInCoolingModeAutosized() const {
      if (auto value = getString(ZoneHVAC_FourPipeFanCoilFields::MinimumSupplyAirTemperatureinCoolingMode, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    boost::optional<double> ZoneHVACFourPipeFanCoil_Impl::minimumSupplyAirTemperatureInCoolingMode() const {
      return getDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumSupplyAirTemperatureinCoolingMode, true);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMinimumSupplyAirTemperatureInCoolingMode(double minimumSupplyAirTemperatureInCoolingMode) {
      const bool result =
        setDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumSupplyAirTemperatureinCoolingMode, minimumSupplyAirTemperatureInCoolingMode);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::autosizeMinimumSupplyAirTemperatureInCoolingMode() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MinimumSupplyAirTemperatureinCoolingMode, "autosize");
      OS_ASSERT(result);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::isMaximumSupplyAirTemperatureInHeatingModeAutosized() const {
      if (auto value = getString(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirTemperatureinHeatingMode, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    boost::optional<double> ZoneHVACFourPipeFanCoil_Impl::maximumSupplyAirTemperatureInHeatingMode() const {
      return getDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirTemperatureinHeatingMode, true);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setMaximumSupplyAirTemperatureInHeatingMode(double maximumSupplyAirTemperatureInHeatingMode) {
      const bool result =
        setDouble(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirTemperatureinHeatingMode, maximumSupplyAirTemperatureInHeatingMode);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACFourPipeFanCoil_Impl::autosizeMaximumSupplyAirTemperatureInHeatingMode() {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirTemperatureinHeatingMode, "autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
