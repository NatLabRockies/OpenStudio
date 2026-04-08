/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"
#include "ZoneHVACComponent/ZoneHVACFourPipeFanCoil_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <boost/none.hpp>

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

  boost::optional<Node> ZoneHVACFourPipeFanCoil::fanOutletNode() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACFourPipeFanCoil::coolingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->coolingCoilOutletNode();
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

  bool ZoneHVACFourPipeFanCoil::setSupplyAirFan(const HVACComponent& fan) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setSupplyAirFan(fan);
  }

  bool ZoneHVACFourPipeFanCoil::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACFourPipeFanCoil_Impl>()->setCoolingCoil(coolingCoil);
  }

  bool ZoneHVACFourPipeFanCoil::setHeatingCoil(const HVACComponent& heatingCoil) {
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

    bool ZoneHVACFourPipeFanCoil_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }

      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACFourPipeFanCoil_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACFourPipeFanCoil_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
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
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::CapacityControlMethod, capacityControlMethod);
      OS_ASSERT(result);
      return result;
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    double ZoneHVACFourPipeFanCoil_Impl::lowSpeedSupplyAirFlowRatio() const {
      auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio, true);
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio, ""));
    }

    double ZoneHVACFourPipeFanCoil_Impl::mediumSpeedSupplyAirFlowRatio() const {
      auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio, true);
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio, ""));
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    std::string ZoneHVACFourPipeFanCoil_Impl::outdoorAirMixerObjectType() const {
      auto value = getString(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerObjectType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType) {
      const bool result = setString(ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerObjectType, outdoorAirMixerObjectType);
      OS_ASSERT(result);
      return result;
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

    // The public wrapper still treats the supply fan as a real contained
    // relationship, but owner maintenance and canonicalization need to cope
    // with incomplete wiring while setters are swapping children or while raw
    // imported state is being repaired. In practice that means the parent may
    // temporarily have to re-thread any of these serial air-side fragments
    // back onto its owned inlet/outlet nodes:
    //
    // - inlet -> fan -> outlet
    // - inlet -> fan -> cooling coil -> outlet
    // - inlet -> fan -> heating coil -> outlet
    // - inlet -> fan -> cooling coil -> heating coil -> outlet
    // - inlet -> cooling coil -> heating coil -> outlet
    // - inlet -> cooling coil -> outlet
    // - inlet -> heating coil -> outlet
    //
    // This getter exposes the fan-outlet role on the parent. That role may
    // alias the unit outlet when there is no downstream coil, and it may not
    // exist at all when the fan is absent.
    boost::optional<Node> ZoneHVACFourPipeFanCoil_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    // This getter exposes the cooling-coil-outlet role on the parent. That
    // role exists whenever a cooling coil exists, even when its outlet node is
    // also the unit outlet because there is no downstream heating coil.
    boost::optional<Node> ZoneHVACFourPipeFanCoil_Impl::coolingCoilOutletNode() const {
      auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName);
      auto cooling =
        (coolingObject && detail::isContainedAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      if (!cooling) {
        return boost::none;
      }

      auto coolingOutlet = detail::containedAirOutletModelObject(*cooling);
      return coolingOutlet ? coolingOutlet->optionalCast<Node>() : boost::none;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setSupplyAirFan(const HVACComponent& fan) {
      if (fan.model() != model()) {
        return false;
      }

      bool isAllowedType = false;
      const auto fanType = fan.iddObject().type();
      if (fanType == IddObjectType::OS_Fan_SystemModel || fanType == IddObjectType::Fan_SystemModel) {
        isAllowedType = true;
      } else if (istringEqual(capacityControlMethod(), "ConstantFanVariableFlow")) {
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

      if (!isAllowedType) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, fan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if (coolingCoil.model() != model()) {
        return false;
      }

      const auto coolingCoilType = coolingCoil.iddObject().type();
      const bool isAllowedType = (coolingCoilType == IddObjectType::OS_Coil_Cooling_Water)
                                 || (coolingCoilType == IddObjectType::OS_CoilSystem_Cooling_Water_HeatExchangerAssisted)
                                 || (coolingCoilType == IddObjectType::Coil_Cooling_Water)
                                 || (coolingCoilType == IddObjectType::CoilSystem_Cooling_Water_HeatExchangerAssisted);
      if (!isAllowedType) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, coolingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    bool ZoneHVACFourPipeFanCoil_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if (heatingCoil.model() != model()) {
        return false;
      }

      const auto heatingCoilType = heatingCoil.iddObject().type();
      const bool isAllowedType = (heatingCoilType == IddObjectType::OS_Coil_Heating_Water)
                                 || (heatingCoilType == IddObjectType::OS_Coil_Heating_Electric)
                                 || (heatingCoilType == IddObjectType::Coil_Heating_Water)
                                 || (heatingCoilType == IddObjectType::Coil_Heating_Electric);
      if (!isAllowedType) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, heatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MaximumColdWaterFlowRate, "autosize"));
    }

    double ZoneHVACFourPipeFanCoil_Impl::minimumColdWaterFlowRate() const {
      auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate, true);
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate, ""));
    }

    double ZoneHVACFourPipeFanCoil_Impl::coolingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance, true);
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance, ""));
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MaximumHotWaterFlowRate, "autosize"));
    }

    double ZoneHVACFourPipeFanCoil_Impl::minimumHotWaterFlowRate() const {
      auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate, true);
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate, ""));
    }

    double ZoneHVACFourPipeFanCoil_Impl::heatingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance, true);
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance, ""));
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MinimumSupplyAirTemperatureinCoolingMode, "autosize"));
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
      OS_ASSERT(setString(ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirTemperatureinHeatingMode, "autosize"));
    }

    bool ZoneHVACFourPipeFanCoil_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACFourPipeFanCoil_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto cooling =
        (coolingObject && detail::isContainedAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      auto heating =
        (heatingObject && detail::isContainedAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;

      bool changed = false;

      const auto currentFanType = thisObject.getString(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, true);
      const auto expectedFanType = fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedFanType) {
        if (!currentFanType || !openstudio::istringEqual(*currentFanType, *expectedFanType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, *expectedFanType));
          changed = true;
        }
      } else if (currentFanType && !currentFanType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, ""));
        changed = true;
      }

      const auto currentCoolingType = thisObject.getString(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, true);
      const auto expectedCoolingType =
        coolingObject ? boost::optional<std::string>(coolingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedCoolingType) {
        if (!currentCoolingType || !openstudio::istringEqual(*currentCoolingType, *expectedCoolingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, *expectedCoolingType));
          changed = true;
        }
      } else if (currentCoolingType && !currentCoolingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, ""));
        changed = true;
      }

      const auto currentHeatingType = thisObject.getString(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, true);
      const auto expectedHeatingType =
        heatingObject ? boost::optional<std::string>(heatingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedHeatingType) {
        if (!currentHeatingType || !openstudio::istringEqual(*currentHeatingType, *expectedHeatingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, *expectedHeatingType));
          changed = true;
        }
      } else if (currentHeatingType && !currentHeatingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, ""));
        changed = true;
      }

      if (!fan && !cooling && !heating) {
        if (changed && context) {
          detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:FourPipeFanCoil '" + thisObject.nameString() + "'.");
        }
        return changed;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");

      changed = setPointer(inletPort(), inletNode.handle(), false) || changed;
      changed = setPointer(outletPort(), outletNode.handle(), false) || changed;

      boost::optional<Node> fanOutlet;
      if (fan && (cooling || heating)) {
        if (!allowChildNodeRecovery) {
          auto currentFanOutlet = fan->outletModelObject() ? fan->outletModelObject()->optionalCast<Node>() : boost::none;
          const auto downstream = cooling ? cooling : heating;
          auto currentDownstreamInlet = downstream && detail::containedAirInletPort(*downstream) != 0u
                                          ? downstream->getModelObjectTarget<Node>(detail::containedAirInletPort(*downstream))
                                          : boost::none;
          if (currentFanOutlet && currentDownstreamInlet && (*currentFanOutlet == *currentDownstreamInlet) && (*currentFanOutlet != inletNode)
              && (*currentFanOutlet != outletNode)) {
            fanOutlet = currentFanOutlet;
          }
        } else {
          fanOutlet = fanOutletNode();
        }
        if (!fanOutlet && allowChildNodeRecovery) {
          if (auto candidate = fan->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(fan->outletPort())) {
            if ((*candidate != inletNode) && (*candidate != outletNode)) {
              fanOutlet = *candidate;
            }
          }
        }
        if (!fanOutlet && allowChildNodeRecovery) {
          const auto downstream = cooling ? cooling : heating;
          if (downstream) {
            const auto downstreamInletPort = detail::containedAirInletPort(*downstream);
            if (downstreamInletPort != 0u) {
              if (auto candidate = downstream->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(downstreamInletPort)) {
                if ((*candidate != inletNode) && (*candidate != outletNode)) {
                  fanOutlet = *candidate;
                }
              }
            }
          }
        }
        if (!fanOutlet) {
          fanOutlet = model().getOrCreateTransientByName<Node>(baseName + " Fan Outlet Node");
        }
      }

      boost::optional<Node> coolingOutlet;
      if (cooling && heating) {
        if (!allowChildNodeRecovery) {
          auto currentCoolingOutlet = detail::containedAirOutletModelObject(*cooling)
                                        ? detail::containedAirOutletModelObject(*cooling)->optionalCast<Node>()
                                        : boost::none;
          auto currentHeatingInlet = detail::containedAirInletPort(*heating) != 0u
                                       ? heating->getModelObjectTarget<Node>(detail::containedAirInletPort(*heating))
                                       : boost::none;
          if (currentCoolingOutlet && currentHeatingInlet && (*currentCoolingOutlet == *currentHeatingInlet)
              && (*currentCoolingOutlet != inletNode) && (*currentCoolingOutlet != outletNode)
              && (!fanOutlet || (*currentCoolingOutlet != *fanOutlet))) {
            coolingOutlet = currentCoolingOutlet;
          }
        } else {
          coolingOutlet = coolingCoilOutletNode();
        }
        if (!coolingOutlet && allowChildNodeRecovery) {
          const auto coolingAirOutletPort = detail::containedAirOutletPort(*cooling);
          if (coolingAirOutletPort != 0u) {
            if (auto candidate = cooling->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(coolingAirOutletPort)) {
              if ((*candidate != inletNode) && (*candidate != outletNode) && (!fanOutlet || (*candidate != *fanOutlet))) {
                coolingOutlet = *candidate;
              }
            }
          }
        }
        if (!coolingOutlet && allowChildNodeRecovery) {
          const auto heatingAirInletPort = detail::containedAirInletPort(*heating);
          if (heatingAirInletPort != 0u) {
            if (auto candidate = heating->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(heatingAirInletPort)) {
              if ((*candidate != inletNode) && (*candidate != outletNode) && (!fanOutlet || (*candidate != *fanOutlet))) {
                coolingOutlet = *candidate;
              }
            }
          }
        }
        if (!coolingOutlet) {
          coolingOutlet = model().getOrCreateTransientByName<Node>(baseName + " Cooling Coil Outlet Node");
        }
      }

      if (fan) {
        changed = fan->getImpl<detail::ModelObject_Impl>()->setPointer(fan->inletPort(), inletNode.handle(), false) || changed;
        if (fanOutlet) {
          changed = fan->getImpl<detail::ModelObject_Impl>()->setPointer(fan->outletPort(), fanOutlet->handle(), false) || changed;
        } else {
          changed = fan->getImpl<detail::ModelObject_Impl>()->setPointer(fan->outletPort(), outletNode.handle(), false) || changed;
        }
      }

      if (cooling) {
        const auto coolingAirInletPort = detail::containedAirInletPort(*cooling);
        const auto coolingAirOutletPort = detail::containedAirOutletPort(*cooling);
        if (coolingAirInletPort != 0u) {
          if (fanOutlet) {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirInletPort, fanOutlet->handle(), false) || changed;
          } else {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirInletPort, inletNode.handle(), false) || changed;
          }
        }
        if (coolingAirOutletPort != 0u) {
          if (coolingOutlet) {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirOutletPort, coolingOutlet->handle(), false) || changed;
          } else {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirOutletPort, outletNode.handle(), false) || changed;
          }
        }
      }

      if (heating) {
        const auto heatingAirInletPort = detail::containedAirInletPort(*heating);
        const auto heatingAirOutletPort = detail::containedAirOutletPort(*heating);
        if (heatingAirInletPort != 0u) {
          if (coolingOutlet) {
            changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirInletPort, coolingOutlet->handle(), false) || changed;
          } else if (fanOutlet) {
            changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirInletPort, fanOutlet->handle(), false) || changed;
          } else {
            changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirInletPort, inletNode.handle(), false) || changed;
          }
        }
        if (heatingAirOutletPort != 0u) {
          changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirOutletPort, outletNode.handle(), false) || changed;
        }
      }

      if (changed && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:FourPipeFanCoil '" + baseName + "'.");
      }

      return changed;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
