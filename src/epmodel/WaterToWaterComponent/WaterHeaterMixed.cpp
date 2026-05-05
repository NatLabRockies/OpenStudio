/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/WaterHeaterMixed.hpp"
#include "WaterToWaterComponent/WaterHeaterMixed_Impl.hpp"

#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject/WaterHeaterSizing.hpp"
#include "ModelObject/WaterHeaterSizing_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_Mixed_FieldEnums.hxx>

#include <algorithm>
#include <set>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  WaterHeaterMixed::WaterHeaterMixed(const Model& model) : WaterToWaterComponent(WaterHeaterMixed::iddObjectType(), model) {
    setTankVolume(0.3785);
    setDeadbandTemperatureDifference(2.0);
    setMaximumTemperatureLimit(82.22);
    setHeaterControlType("Cycle");
    setHeaterMaximumCapacity(845000.0);
    setHeaterFuelType(FuelType::Gas);
    setHeaterThermalEfficiency(0.8);
    setOffCycleParasiticFuelConsumptionRate(20.0);
    setOffCycleParasiticFuelType(FuelType::Gas);
    setOffCycleParasiticHeatFractiontoTank(0.8);
    setOnCycleParasiticFuelType(FuelType::Gas);
    setOffCycleLossCoefficienttoAmbientTemperature(6.0);
    setOnCycleLossCoefficienttoAmbientTemperature(6.0);
    setUseSideEffectiveness(1.0);
    setSourceSideEffectiveness(1.0);
    autosizeUseSideDesignFlowRate();
    autosizeSourceSideDesignFlowRate();
    setIndirectWaterHeatingRecoveryTime(1.5);
    setAmbientTemperatureIndicator("Schedule");

    ScheduleConstant ambientSchedule(model);
    OS_ASSERT(ambientSchedule.setValue(22.0));
    OS_ASSERT(setAmbientTemperatureSchedule(ambientSchedule));

    ScheduleConstant setpointSchedule(model);
    OS_ASSERT(setpointSchedule.setValue(60.0));
    OS_ASSERT(setSetpointTemperatureSchedule(setpointSchedule));

    setSourceSideFlowControlMode("IndirectHeatPrimarySetpoint");
    setEndUseSubcategory("General");

    WaterHeaterSizing waterHeaterSizing(*this);
  }

  WaterHeaterMixed::WaterHeaterMixed(std::shared_ptr<detail::WaterHeaterMixed_Impl> impl) : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType WaterHeaterMixed::iddObjectType() {
    return IddObjectType::WaterHeater_Mixed;
  }

  std::vector<std::string> WaterHeaterMixed::heaterControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_MixedFields::HeaterControlType);
  }

  std::vector<std::string> WaterHeaterMixed::heaterFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_MixedFields::HeaterFuelType);
  }

  std::vector<std::string> WaterHeaterMixed::offCycleParasiticFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_MixedFields::OffCycleParasiticFuelType);
  }

  std::vector<std::string> WaterHeaterMixed::onCycleParasiticFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_MixedFields::OnCycleParasiticFuelType);
  }

  std::vector<std::string> WaterHeaterMixed::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_MixedFields::AmbientTemperatureIndicator);
  }

  std::vector<std::string> WaterHeaterMixed::sourceSideFlowControlModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_MixedFields::SourceSideFlowControlMode);
  }

  boost::optional<double> WaterHeaterMixed::tankVolume() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->tankVolume();
  }

  bool WaterHeaterMixed::isTankVolumeDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isTankVolumeDefaulted();
  }

  bool WaterHeaterMixed::isTankVolumeAutosized() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isTankVolumeAutosized();
  }

  bool WaterHeaterMixed::setTankVolume(double tankVolume) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setTankVolume(tankVolume);
  }

  void WaterHeaterMixed::resetTankVolume() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetTankVolume();
  }

  void WaterHeaterMixed::autosizeTankVolume() {
    getImpl<detail::WaterHeaterMixed_Impl>()->autosizeTankVolume();
  }

  boost::optional<double> WaterHeaterMixed::autosizedTankVolume() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->autosizedTankVolume();
  }

  boost::optional<Schedule> WaterHeaterMixed::setpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setpointTemperatureSchedule();
  }

  bool WaterHeaterMixed::setSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setSetpointTemperatureSchedule(schedule);
  }

  void WaterHeaterMixed::resetSetpointTemperatureSchedule() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetSetpointTemperatureSchedule();
  }

  double WaterHeaterMixed::deadbandTemperatureDifference() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->deadbandTemperatureDifference();
  }

  bool WaterHeaterMixed::isDeadbandTemperatureDifferenceDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isDeadbandTemperatureDifferenceDefaulted();
  }

  bool WaterHeaterMixed::setDeadbandTemperatureDifference(double deadbandTemperatureDifference) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setDeadbandTemperatureDifference(deadbandTemperatureDifference);
  }

  void WaterHeaterMixed::resetDeadbandTemperatureDifference() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetDeadbandTemperatureDifference();
  }

  boost::optional<double> WaterHeaterMixed::maximumTemperatureLimit() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->maximumTemperatureLimit();
  }

  bool WaterHeaterMixed::setMaximumTemperatureLimit(double maximumTemperatureLimit) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setMaximumTemperatureLimit(maximumTemperatureLimit);
  }

  void WaterHeaterMixed::resetMaximumTemperatureLimit() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetMaximumTemperatureLimit();
  }

  std::string WaterHeaterMixed::heaterControlType() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterControlType();
  }

  bool WaterHeaterMixed::isHeaterControlTypeDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isHeaterControlTypeDefaulted();
  }

  bool WaterHeaterMixed::setHeaterControlType(const std::string& heaterControlType) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterControlType(heaterControlType);
  }

  void WaterHeaterMixed::resetHeaterControlType() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetHeaterControlType();
  }

  boost::optional<double> WaterHeaterMixed::heaterMaximumCapacity() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterMaximumCapacity();
  }

  bool WaterHeaterMixed::isHeaterMaximumCapacityAutosized() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isHeaterMaximumCapacityAutosized();
  }

  bool WaterHeaterMixed::setHeaterMaximumCapacity(double heaterMaximumCapacity) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterMaximumCapacity(heaterMaximumCapacity);
  }

  void WaterHeaterMixed::resetHeaterMaximumCapacity() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetHeaterMaximumCapacity();
  }

  void WaterHeaterMixed::autosizeHeaterMaximumCapacity() {
    getImpl<detail::WaterHeaterMixed_Impl>()->autosizeHeaterMaximumCapacity();
  }

  boost::optional<double> WaterHeaterMixed::autosizedHeaterMaximumCapacity() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->autosizedHeaterMaximumCapacity();
  }

  boost::optional<double> WaterHeaterMixed::heaterMinimumCapacity() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterMinimumCapacity();
  }

  bool WaterHeaterMixed::setHeaterMinimumCapacity(double heaterMinimumCapacity) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterMinimumCapacity(heaterMinimumCapacity);
  }

  void WaterHeaterMixed::resetHeaterMinimumCapacity() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetHeaterMinimumCapacity();
  }

  double WaterHeaterMixed::heaterIgnitionMinimumFlowRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterIgnitionMinimumFlowRate();
  }

  bool WaterHeaterMixed::isHeaterIgnitionMinimumFlowRateDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isHeaterIgnitionMinimumFlowRateDefaulted();
  }

  bool WaterHeaterMixed::setHeaterIgnitionMinimumFlowRate(double heaterIgnitionMinimumFlowRate) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterIgnitionMinimumFlowRate(heaterIgnitionMinimumFlowRate);
  }

  void WaterHeaterMixed::resetHeaterIgnitionMinimumFlowRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetHeaterIgnitionMinimumFlowRate();
  }

  double WaterHeaterMixed::heaterIgnitionDelay() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterIgnitionDelay();
  }

  bool WaterHeaterMixed::isHeaterIgnitionDelayDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isHeaterIgnitionDelayDefaulted();
  }

  bool WaterHeaterMixed::setHeaterIgnitionDelay(double heaterIgnitionDelay) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterIgnitionDelay(heaterIgnitionDelay);
  }

  void WaterHeaterMixed::resetHeaterIgnitionDelay() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetHeaterIgnitionDelay();
  }

  std::string WaterHeaterMixed::heaterFuelType() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterFuelType();
  }

  bool WaterHeaterMixed::setHeaterFuelType(const FuelType& heaterFuelType) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterFuelType(heaterFuelType.valueDescription());
  }

  bool WaterHeaterMixed::setHeaterFuelType(const std::string& heaterFuelType) {
    try {
      return setHeaterFuelType(FuelType{heaterFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  boost::optional<double> WaterHeaterMixed::heaterThermalEfficiency() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->heaterThermalEfficiency();
  }

  bool WaterHeaterMixed::setHeaterThermalEfficiency(double heaterThermalEfficiency) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setHeaterThermalEfficiency(heaterThermalEfficiency);
  }

  void WaterHeaterMixed::resetHeaterThermalEfficiency() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetHeaterThermalEfficiency();
  }

  boost::optional<CurveCubic> WaterHeaterMixed::partLoadFactorCurve() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->partLoadFactorCurve();
  }

  bool WaterHeaterMixed::setPartLoadFactorCurve(const CurveCubic& partLoadFactorCurve) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setPartLoadFactorCurve(partLoadFactorCurve);
  }

  void WaterHeaterMixed::resetPartLoadFactorCurve() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetPartLoadFactorCurve();
  }

  double WaterHeaterMixed::offCycleParasiticFuelConsumptionRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->offCycleParasiticFuelConsumptionRate();
  }

  bool WaterHeaterMixed::isOffCycleParasiticFuelConsumptionRateDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isOffCycleParasiticFuelConsumptionRateDefaulted();
  }

  bool WaterHeaterMixed::setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOffCycleParasiticFuelConsumptionRate(offCycleParasiticFuelConsumptionRate);
  }

  void WaterHeaterMixed::resetOffCycleParasiticFuelConsumptionRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOffCycleParasiticFuelConsumptionRate();
  }

  boost::optional<std::string> WaterHeaterMixed::offCycleParasiticFuelType() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->offCycleParasiticFuelType();
  }

  bool WaterHeaterMixed::setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOffCycleParasiticFuelType(offCycleParasiticFuelType.valueDescription());
  }

  bool WaterHeaterMixed::setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType) {
    try {
      return setOffCycleParasiticFuelType(FuelType{offCycleParasiticFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  void WaterHeaterMixed::resetOffCycleParasiticFuelType() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOffCycleParasiticFuelType();
  }

  double WaterHeaterMixed::offCycleParasiticHeatFractiontoTank() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->offCycleParasiticHeatFractiontoTank();
  }

  bool WaterHeaterMixed::isOffCycleParasiticHeatFractiontoTankDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isOffCycleParasiticHeatFractiontoTankDefaulted();
  }

  bool WaterHeaterMixed::setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOffCycleParasiticHeatFractiontoTank(offCycleParasiticHeatFractiontoTank);
  }

  void WaterHeaterMixed::resetOffCycleParasiticHeatFractiontoTank() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOffCycleParasiticHeatFractiontoTank();
  }

  double WaterHeaterMixed::onCycleParasiticFuelConsumptionRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->onCycleParasiticFuelConsumptionRate();
  }

  bool WaterHeaterMixed::isOnCycleParasiticFuelConsumptionRateDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isOnCycleParasiticFuelConsumptionRateDefaulted();
  }

  bool WaterHeaterMixed::setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOnCycleParasiticFuelConsumptionRate(onCycleParasiticFuelConsumptionRate);
  }

  void WaterHeaterMixed::resetOnCycleParasiticFuelConsumptionRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOnCycleParasiticFuelConsumptionRate();
  }

  boost::optional<std::string> WaterHeaterMixed::onCycleParasiticFuelType() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->onCycleParasiticFuelType();
  }

  bool WaterHeaterMixed::setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOnCycleParasiticFuelType(onCycleParasiticFuelType.valueDescription());
  }

  bool WaterHeaterMixed::setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType) {
    try {
      return setOnCycleParasiticFuelType(FuelType{onCycleParasiticFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  void WaterHeaterMixed::resetOnCycleParasiticFuelType() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOnCycleParasiticFuelType();
  }

  double WaterHeaterMixed::onCycleParasiticHeatFractiontoTank() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->onCycleParasiticHeatFractiontoTank();
  }

  bool WaterHeaterMixed::isOnCycleParasiticHeatFractiontoTankDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isOnCycleParasiticHeatFractiontoTankDefaulted();
  }

  bool WaterHeaterMixed::setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOnCycleParasiticHeatFractiontoTank(onCycleParasiticHeatFractiontoTank);
  }

  void WaterHeaterMixed::resetOnCycleParasiticHeatFractiontoTank() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOnCycleParasiticHeatFractiontoTank();
  }

  std::string WaterHeaterMixed::ambientTemperatureIndicator() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->ambientTemperatureIndicator();
  }

  bool WaterHeaterMixed::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setAmbientTemperatureIndicator(ambientTemperatureIndicator);
  }

  boost::optional<Schedule> WaterHeaterMixed::ambientTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->ambientTemperatureSchedule();
  }

  bool WaterHeaterMixed::setAmbientTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setAmbientTemperatureSchedule(schedule);
  }

  void WaterHeaterMixed::resetAmbientTemperatureSchedule() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetAmbientTemperatureSchedule();
  }

  boost::optional<ThermalZone> WaterHeaterMixed::ambientTemperatureThermalZone() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->ambientTemperatureThermalZone();
  }

  bool WaterHeaterMixed::setAmbientTemperatureThermalZone(const ThermalZone& ambientTemperatureThermalZone) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setAmbientTemperatureThermalZone(ambientTemperatureThermalZone);
  }

  void WaterHeaterMixed::resetAmbientTemperatureThermalZone() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetAmbientTemperatureThermalZone();
  }

  boost::optional<std::string> WaterHeaterMixed::ambientTemperatureOutdoorAirNodeName() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->ambientTemperatureOutdoorAirNodeName();
  }

  bool WaterHeaterMixed::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setAmbientTemperatureOutdoorAirNodeName(ambientTemperatureOutdoorAirNodeName);
  }

  void WaterHeaterMixed::resetAmbientTemperatureOutdoorAirNodeName() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetAmbientTemperatureOutdoorAirNodeName();
  }

  boost::optional<double> WaterHeaterMixed::offCycleLossCoefficienttoAmbientTemperature() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->offCycleLossCoefficienttoAmbientTemperature();
  }

  bool WaterHeaterMixed::setOffCycleLossCoefficienttoAmbientTemperature(double offCycleLossCoefficienttoAmbientTemperature) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOffCycleLossCoefficienttoAmbientTemperature(offCycleLossCoefficienttoAmbientTemperature);
  }

  void WaterHeaterMixed::resetOffCycleLossCoefficienttoAmbientTemperature() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOffCycleLossCoefficienttoAmbientTemperature();
  }

  double WaterHeaterMixed::offCycleLossFractiontoThermalZone() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->offCycleLossFractiontoThermalZone();
  }

  bool WaterHeaterMixed::isOffCycleLossFractiontoThermalZoneDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isOffCycleLossFractiontoThermalZoneDefaulted();
  }

  bool WaterHeaterMixed::setOffCycleLossFractiontoThermalZone(double offCycleLossFractiontoThermalZone) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOffCycleLossFractiontoThermalZone(offCycleLossFractiontoThermalZone);
  }

  void WaterHeaterMixed::resetOffCycleLossFractiontoThermalZone() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOffCycleLossFractiontoThermalZone();
  }

  boost::optional<double> WaterHeaterMixed::onCycleLossCoefficienttoAmbientTemperature() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->onCycleLossCoefficienttoAmbientTemperature();
  }

  bool WaterHeaterMixed::setOnCycleLossCoefficienttoAmbientTemperature(double onCycleLossCoefficienttoAmbientTemperature) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOnCycleLossCoefficienttoAmbientTemperature(onCycleLossCoefficienttoAmbientTemperature);
  }

  void WaterHeaterMixed::resetOnCycleLossCoefficienttoAmbientTemperature() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOnCycleLossCoefficienttoAmbientTemperature();
  }

  double WaterHeaterMixed::onCycleLossFractiontoThermalZone() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->onCycleLossFractiontoThermalZone();
  }

  bool WaterHeaterMixed::isOnCycleLossFractiontoThermalZoneDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isOnCycleLossFractiontoThermalZoneDefaulted();
  }

  bool WaterHeaterMixed::setOnCycleLossFractiontoThermalZone(double onCycleLossFractiontoThermalZone) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setOnCycleLossFractiontoThermalZone(onCycleLossFractiontoThermalZone);
  }

  void WaterHeaterMixed::resetOnCycleLossFractiontoThermalZone() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetOnCycleLossFractiontoThermalZone();
  }

  boost::optional<double> WaterHeaterMixed::peakUseFlowRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->peakUseFlowRate();
  }

  bool WaterHeaterMixed::setPeakUseFlowRate(double peakUseFlowRate) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setPeakUseFlowRate(peakUseFlowRate);
  }

  void WaterHeaterMixed::resetPeakUseFlowRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetPeakUseFlowRate();
  }

  boost::optional<Schedule> WaterHeaterMixed::useFlowRateFractionSchedule() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->useFlowRateFractionSchedule();
  }

  bool WaterHeaterMixed::setUseFlowRateFractionSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setUseFlowRateFractionSchedule(schedule);
  }

  void WaterHeaterMixed::resetUseFlowRateFractionSchedule() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetUseFlowRateFractionSchedule();
  }

  boost::optional<Schedule> WaterHeaterMixed::coldWaterSupplyTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->coldWaterSupplyTemperatureSchedule();
  }

  bool WaterHeaterMixed::setColdWaterSupplyTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setColdWaterSupplyTemperatureSchedule(schedule);
  }

  void WaterHeaterMixed::resetColdWaterSupplyTemperatureSchedule() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetColdWaterSupplyTemperatureSchedule();
  }

  double WaterHeaterMixed::useSideEffectiveness() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->useSideEffectiveness();
  }

  bool WaterHeaterMixed::isUseSideEffectivenessDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isUseSideEffectivenessDefaulted();
  }

  bool WaterHeaterMixed::setUseSideEffectiveness(double useSideEffectiveness) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setUseSideEffectiveness(useSideEffectiveness);
  }

  void WaterHeaterMixed::resetUseSideEffectiveness() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetUseSideEffectiveness();
  }

  double WaterHeaterMixed::sourceSideEffectiveness() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->sourceSideEffectiveness();
  }

  bool WaterHeaterMixed::isSourceSideEffectivenessDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isSourceSideEffectivenessDefaulted();
  }

  bool WaterHeaterMixed::setSourceSideEffectiveness(double sourceSideEffectiveness) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setSourceSideEffectiveness(sourceSideEffectiveness);
  }

  void WaterHeaterMixed::resetSourceSideEffectiveness() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetSourceSideEffectiveness();
  }

  boost::optional<double> WaterHeaterMixed::useSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->useSideDesignFlowRate();
  }

  bool WaterHeaterMixed::isUseSideDesignFlowRateDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isUseSideDesignFlowRateDefaulted();
  }

  bool WaterHeaterMixed::isUseSideDesignFlowRateAutosized() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isUseSideDesignFlowRateAutosized();
  }

  bool WaterHeaterMixed::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setUseSideDesignFlowRate(useSideDesignFlowRate);
  }

  void WaterHeaterMixed::resetUseSideDesignFlowRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetUseSideDesignFlowRate();
  }

  void WaterHeaterMixed::autosizeUseSideDesignFlowRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->autosizeUseSideDesignFlowRate();
  }

  boost::optional<double> WaterHeaterMixed::autosizedUseSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->autosizedUseSideDesignFlowRate();
  }

  boost::optional<double> WaterHeaterMixed::sourceSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->sourceSideDesignFlowRate();
  }

  bool WaterHeaterMixed::isSourceSideDesignFlowRateDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isSourceSideDesignFlowRateDefaulted();
  }

  bool WaterHeaterMixed::isSourceSideDesignFlowRateAutosized() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isSourceSideDesignFlowRateAutosized();
  }

  bool WaterHeaterMixed::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setSourceSideDesignFlowRate(sourceSideDesignFlowRate);
  }

  void WaterHeaterMixed::resetSourceSideDesignFlowRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetSourceSideDesignFlowRate();
  }

  void WaterHeaterMixed::autosizeSourceSideDesignFlowRate() {
    getImpl<detail::WaterHeaterMixed_Impl>()->autosizeSourceSideDesignFlowRate();
  }

  boost::optional<double> WaterHeaterMixed::autosizedSourceSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->autosizedSourceSideDesignFlowRate();
  }

  double WaterHeaterMixed::indirectWaterHeatingRecoveryTime() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->indirectWaterHeatingRecoveryTime();
  }

  bool WaterHeaterMixed::isIndirectWaterHeatingRecoveryTimeDefaulted() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->isIndirectWaterHeatingRecoveryTimeDefaulted();
  }

  bool WaterHeaterMixed::setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setIndirectWaterHeatingRecoveryTime(indirectWaterHeatingRecoveryTime);
  }

  void WaterHeaterMixed::resetIndirectWaterHeatingRecoveryTime() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetIndirectWaterHeatingRecoveryTime();
  }

  std::string WaterHeaterMixed::sourceSideFlowControlMode() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->sourceSideFlowControlMode();
  }

  bool WaterHeaterMixed::setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setSourceSideFlowControlMode(sourceSideFlowControlMode);
  }

  boost::optional<Schedule> WaterHeaterMixed::indirectAlternateSetpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->indirectAlternateSetpointTemperatureSchedule();
  }

  bool WaterHeaterMixed::setIndirectAlternateSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setIndirectAlternateSetpointTemperatureSchedule(schedule);
  }

  void WaterHeaterMixed::resetIndirectAlternateSetpointTemperatureSchedule() {
    getImpl<detail::WaterHeaterMixed_Impl>()->resetIndirectAlternateSetpointTemperatureSchedule();
  }

  std::string WaterHeaterMixed::endUseSubcategory() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->endUseSubcategory();
  }

  bool WaterHeaterMixed::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  WaterHeaterSizing WaterHeaterMixed::waterHeaterSizing() const {
    return getImpl<detail::WaterHeaterMixed_Impl>()->waterHeaterSizing();
  }

  bool WaterHeaterMixed::addToSourceSideNode(Node& node) {
    return getImpl<detail::WaterHeaterMixed_Impl>()->addToSourceSideNode(node);
  }

  boost::optional<PlantLoop> WaterHeaterMixed::useSidePlantLoop() const {
    return plantLoop();
  }

  boost::optional<PlantLoop> WaterHeaterMixed::sourceSidePlantLoop() const {
    return secondaryPlantLoop();
  }

  bool WaterHeaterMixed::removeFromSourceSidePlantLoop() {
    return removeFromSecondaryPlantLoop();
  }

  boost::optional<ModelObject> WaterHeaterMixed::useSideInletModelObject() const {
    return supplyInletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterMixed::useSideOutletModelObject() const {
    return supplyOutletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterMixed::sourceSideInletModelObject() const {
    return demandInletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterMixed::sourceSideOutletModelObject() const {
    return demandOutletModelObject();
  }

  namespace detail {

    namespace {

      bool isAutosize(const ModelObject_Impl& impl, int fieldIndex) {
        if (auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

    }  // namespace

    void WaterHeaterMixed_Impl::doCanonicalize(LoadContext& context) {
      WaterToWaterComponent_Impl::doCanonicalize(context);

      try {
        waterHeaterSizing();
        return;
      } catch (const std::exception&) {
      }

      const auto waterHeater = getObject<WaterHeaterMixed>();
      WaterHeaterSizing sizing(waterHeater);
      detail::addLoadInfo(context, "Created default WaterHeater:Sizing object for WaterHeater:Mixed '" + waterHeater.nameString() + "'.");
    }

    std::vector<ModelObject> WaterHeaterMixed_Impl::children() const {
      return {waterHeaterSizing()};
    }

    unsigned WaterHeaterMixed_Impl::supplyInletPort() const {
      return openstudio::WaterHeater_MixedFields::UseSideInletNodeName;
    }

    unsigned WaterHeaterMixed_Impl::supplyOutletPort() const {
      return openstudio::WaterHeater_MixedFields::UseSideOutletNodeName;
    }

    unsigned WaterHeaterMixed_Impl::demandInletPort() const {
      return openstudio::WaterHeater_MixedFields::SourceSideInletNodeName;
    }

    unsigned WaterHeaterMixed_Impl::demandOutletPort() const {
      return openstudio::WaterHeater_MixedFields::SourceSideOutletNodeName;
    }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                          \
  boost::optional<double> WaterHeaterMixed_Impl::method() const {       \
    return getDouble(openstudio::WaterHeater_MixedFields::field, true); \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                      \
  double WaterHeaterMixed_Impl::method() const {                                    \
    const auto value = getDouble(openstudio::WaterHeater_MixedFields::field, true); \
    OS_ASSERT(value);                                                               \
    return *value;                                                                  \
  }

#define OS_IMPL_OPTIONAL_STRING(method, field)                          \
  boost::optional<std::string> WaterHeaterMixed_Impl::method() const {  \
    return getString(openstudio::WaterHeater_MixedFields::field, true); \
  }

#define OS_IMPL_REQUIRED_STRING(method, field)                                      \
  std::string WaterHeaterMixed_Impl::method() const {                               \
    const auto value = getString(openstudio::WaterHeater_MixedFields::field, true); \
    OS_ASSERT(value);                                                               \
    return *value;                                                                  \
  }

    // Tank volume getter is implemented manually below to keep EnergyPlus defaults hidden.
    OS_IMPL_REQUIRED_DOUBLE(deadbandTemperatureDifference, DeadbandTemperatureDifference)
    OS_IMPL_OPTIONAL_DOUBLE(maximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_REQUIRED_STRING(heaterControlType, HeaterControlType)
    OS_IMPL_OPTIONAL_DOUBLE(heaterMaximumCapacity, HeaterMaximumCapacity)
    OS_IMPL_OPTIONAL_DOUBLE(heaterMinimumCapacity, HeaterMinimumCapacity)
    OS_IMPL_REQUIRED_DOUBLE(heaterIgnitionMinimumFlowRate, HeaterIgnitionMinimumFlowRate)
    OS_IMPL_REQUIRED_DOUBLE(heaterIgnitionDelay, HeaterIgnitionDelay)
    OS_IMPL_REQUIRED_STRING(heaterFuelType, HeaterFuelType)
    OS_IMPL_OPTIONAL_DOUBLE(heaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_OPTIONAL_STRING(offCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_OPTIONAL_STRING(onCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    // Ambient temperature indicator requires a custom getter/setter to translate the "ThermalZone" token.
    OS_IMPL_OPTIONAL_DOUBLE(offCycleLossCoefficienttoAmbientTemperature, OffCycleLossCoefficienttoAmbientTemperature)
    OS_IMPL_REQUIRED_DOUBLE(offCycleLossFractiontoThermalZone, OffCycleLossFractiontoZone)
    OS_IMPL_OPTIONAL_DOUBLE(onCycleLossCoefficienttoAmbientTemperature, OnCycleLossCoefficienttoAmbientTemperature)
    OS_IMPL_REQUIRED_DOUBLE(onCycleLossFractiontoThermalZone, OnCycleLossFractiontoZone)
    OS_IMPL_OPTIONAL_DOUBLE(peakUseFlowRate, PeakUseFlowRate)
    OS_IMPL_REQUIRED_DOUBLE(useSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_REQUIRED_DOUBLE(sourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_OPTIONAL_DOUBLE(useSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_OPTIONAL_DOUBLE(sourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_REQUIRED_DOUBLE(indirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
    OS_IMPL_REQUIRED_STRING(sourceSideFlowControlMode, SourceSideFlowControlMode)
    OS_IMPL_REQUIRED_STRING(endUseSubcategory, EndUseSubcategory)

#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_STRING
#undef OS_IMPL_OPTIONAL_STRING

    boost::optional<double> WaterHeaterMixed_Impl::tankVolume() const {
      if (isTankVolumeDefaulted()) {
        return boost::none;
      }
      return getDouble(openstudio::WaterHeater_MixedFields::TankVolume);
    }

    boost::optional<Schedule> WaterHeaterMixed_Impl::setpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_MixedFields::SetpointTemperatureScheduleName);
    }

    bool WaterHeaterMixed_Impl::setSetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_MixedFields::SetpointTemperatureScheduleName, "WaterHeaterMixed", "Setpoint Temperature", schedule);
    }

    void WaterHeaterMixed_Impl::resetSetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::SetpointTemperatureScheduleName, ""));
    }

    std::string WaterHeaterMixed_Impl::ambientTemperatureIndicator() const {
      const auto value = getString(openstudio::WaterHeater_MixedFields::AmbientTemperatureIndicator, true);
      OS_ASSERT(value);
      if (openstudio::istringEqual(*value, "Zone")) {
        return "ThermalZone";
      }
      return *value;
    }

    boost::optional<CurveCubic> WaterHeaterMixed_Impl::partLoadFactorCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<CurveCubic>(openstudio::WaterHeater_MixedFields::PartLoadFactorCurveName);
    }

    bool WaterHeaterMixed_Impl::setPartLoadFactorCurve(const CurveCubic& partLoadFactorCurve) {
      return setPointer(openstudio::WaterHeater_MixedFields::PartLoadFactorCurveName, partLoadFactorCurve.handle());
    }

    void WaterHeaterMixed_Impl::resetPartLoadFactorCurve() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::PartLoadFactorCurveName, ""));
    }

    boost::optional<Schedule> WaterHeaterMixed_Impl::ambientTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_MixedFields::AmbientTemperatureScheduleName);
    }

    bool WaterHeaterMixed_Impl::setAmbientTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_MixedFields::AmbientTemperatureScheduleName, "WaterHeaterMixed", "Ambient Temperature", schedule);
    }

    void WaterHeaterMixed_Impl::resetAmbientTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::AmbientTemperatureScheduleName, ""));
    }

    boost::optional<ThermalZone> WaterHeaterMixed_Impl::ambientTemperatureThermalZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::WaterHeater_MixedFields::AmbientTemperatureZoneName);
    }

    bool WaterHeaterMixed_Impl::setAmbientTemperatureThermalZone(const ThermalZone& ambientTemperatureThermalZone) {
      return setPointer(openstudio::WaterHeater_MixedFields::AmbientTemperatureZoneName, ambientTemperatureThermalZone.handle());
    }

    void WaterHeaterMixed_Impl::resetAmbientTemperatureThermalZone() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::AmbientTemperatureZoneName, ""));
    }

    boost::optional<std::string> WaterHeaterMixed_Impl::ambientTemperatureOutdoorAirNodeName() const {
      auto value = getString(openstudio::WaterHeater_MixedFields::AmbientTemperatureOutdoorAirNodeName, true);
      if (value && value->empty()) {
        return boost::none;
      }
      return value;
    }

    bool WaterHeaterMixed_Impl::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
      return setString(openstudio::WaterHeater_MixedFields::AmbientTemperatureOutdoorAirNodeName, ambientTemperatureOutdoorAirNodeName);
    }

    void WaterHeaterMixed_Impl::resetAmbientTemperatureOutdoorAirNodeName() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::AmbientTemperatureOutdoorAirNodeName, ""));
    }

    boost::optional<Schedule> WaterHeaterMixed_Impl::useFlowRateFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_MixedFields::UseFlowRateFractionScheduleName);
    }

    bool WaterHeaterMixed_Impl::setUseFlowRateFractionSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_MixedFields::UseFlowRateFractionScheduleName, "WaterHeaterMixed", "Use Flow Rate Fraction", schedule);
    }

    void WaterHeaterMixed_Impl::resetUseFlowRateFractionSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::UseFlowRateFractionScheduleName, ""));
    }

    boost::optional<Schedule> WaterHeaterMixed_Impl::coldWaterSupplyTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_MixedFields::ColdWaterSupplyTemperatureScheduleName);
    }

    bool WaterHeaterMixed_Impl::setColdWaterSupplyTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_MixedFields::ColdWaterSupplyTemperatureScheduleName, "WaterHeaterMixed",
                         "Cold Water Supply Temperature", schedule);
    }

    void WaterHeaterMixed_Impl::resetColdWaterSupplyTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::ColdWaterSupplyTemperatureScheduleName, ""));
    }

#define OS_IMPL_DEFAULTED(method, field)                        \
  bool WaterHeaterMixed_Impl::method() const {                  \
    return isEmpty(openstudio::WaterHeater_MixedFields::field); \
  }

    OS_IMPL_DEFAULTED(isTankVolumeDefaulted, TankVolume)
    OS_IMPL_DEFAULTED(isDeadbandTemperatureDifferenceDefaulted, DeadbandTemperatureDifference)
    OS_IMPL_DEFAULTED(isHeaterControlTypeDefaulted, HeaterControlType)
    OS_IMPL_DEFAULTED(isHeaterIgnitionMinimumFlowRateDefaulted, HeaterIgnitionMinimumFlowRate)
    OS_IMPL_DEFAULTED(isHeaterIgnitionDelayDefaulted, HeaterIgnitionDelay)
    OS_IMPL_DEFAULTED(isOffCycleParasiticFuelConsumptionRateDefaulted, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_DEFAULTED(isOffCycleParasiticHeatFractiontoTankDefaulted, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_DEFAULTED(isOnCycleParasiticFuelConsumptionRateDefaulted, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_DEFAULTED(isOnCycleParasiticHeatFractiontoTankDefaulted, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_DEFAULTED(isOffCycleLossFractiontoThermalZoneDefaulted, OffCycleLossFractiontoZone)
    OS_IMPL_DEFAULTED(isOnCycleLossFractiontoThermalZoneDefaulted, OnCycleLossFractiontoZone)
    OS_IMPL_DEFAULTED(isUseSideEffectivenessDefaulted, UseSideEffectiveness)
    OS_IMPL_DEFAULTED(isSourceSideEffectivenessDefaulted, SourceSideEffectiveness)
    OS_IMPL_DEFAULTED(isUseSideDesignFlowRateDefaulted, UseSideDesignFlowRate)
    OS_IMPL_DEFAULTED(isSourceSideDesignFlowRateDefaulted, SourceSideDesignFlowRate)
    OS_IMPL_DEFAULTED(isIndirectWaterHeatingRecoveryTimeDefaulted, IndirectWaterHeatingRecoveryTime)
#undef OS_IMPL_DEFAULTED

#define OS_IMPL_AUTOSIZED(method, field)                                  \
  bool WaterHeaterMixed_Impl::method() const {                            \
    return isAutosize(*this, openstudio::WaterHeater_MixedFields::field); \
  }

    OS_IMPL_AUTOSIZED(isTankVolumeAutosized, TankVolume)
    OS_IMPL_AUTOSIZED(isHeaterMaximumCapacityAutosized, HeaterMaximumCapacity)
    OS_IMPL_AUTOSIZED(isUseSideDesignFlowRateAutosized, UseSideDesignFlowRate)
    OS_IMPL_AUTOSIZED(isSourceSideDesignFlowRateAutosized, SourceSideDesignFlowRate)
#undef OS_IMPL_AUTOSIZED

#define OS_IMPL_SET_DOUBLE(method, field)                                \
  bool WaterHeaterMixed_Impl::method(double value) {                     \
    return setDouble(openstudio::WaterHeater_MixedFields::field, value); \
  }

#define OS_IMPL_SET_STRING(method, field)                                \
  bool WaterHeaterMixed_Impl::method(const std::string& value) {         \
    return setString(openstudio::WaterHeater_MixedFields::field, value); \
  }

    OS_IMPL_SET_DOUBLE(setTankVolume, TankVolume)
    OS_IMPL_SET_DOUBLE(setDeadbandTemperatureDifference, DeadbandTemperatureDifference)
    OS_IMPL_SET_DOUBLE(setMaximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_SET_STRING(setHeaterControlType, HeaterControlType)
    OS_IMPL_SET_DOUBLE(setHeaterMaximumCapacity, HeaterMaximumCapacity)
    OS_IMPL_SET_DOUBLE(setHeaterMinimumCapacity, HeaterMinimumCapacity)
    OS_IMPL_SET_DOUBLE(setHeaterIgnitionMinimumFlowRate, HeaterIgnitionMinimumFlowRate)
    OS_IMPL_SET_DOUBLE(setHeaterIgnitionDelay, HeaterIgnitionDelay)
    OS_IMPL_SET_STRING(setHeaterFuelType, HeaterFuelType)
    OS_IMPL_SET_DOUBLE(setHeaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_SET_STRING(setOffCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_SET_STRING(setOnCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_SET_DOUBLE(setOffCycleLossCoefficienttoAmbientTemperature, OffCycleLossCoefficienttoAmbientTemperature)
    OS_IMPL_SET_DOUBLE(setOffCycleLossFractiontoThermalZone, OffCycleLossFractiontoZone)
    OS_IMPL_SET_DOUBLE(setOnCycleLossCoefficienttoAmbientTemperature, OnCycleLossCoefficienttoAmbientTemperature)
    OS_IMPL_SET_DOUBLE(setOnCycleLossFractiontoThermalZone, OnCycleLossFractiontoZone)
    OS_IMPL_SET_DOUBLE(setPeakUseFlowRate, PeakUseFlowRate)
    OS_IMPL_SET_DOUBLE(setUseSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_SET_DOUBLE(setSourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_SET_DOUBLE(setUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_SET_DOUBLE(setSourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_SET_DOUBLE(setIndirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
    OS_IMPL_SET_STRING(setEndUseSubcategory, EndUseSubcategory)
#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

    bool WaterHeaterMixed_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      auto normalized = ambientTemperatureIndicator;
      if (openstudio::istringEqual(ambientTemperatureIndicator, "ThermalZone")) {
        normalized = "Zone";
      }
      return setString(openstudio::WaterHeater_MixedFields::AmbientTemperatureIndicator, normalized);
    }

#define OS_IMPL_RESET(method, field)                                               \
  void WaterHeaterMixed_Impl::method() {                                           \
    const bool result = setString(openstudio::WaterHeater_MixedFields::field, ""); \
    OS_ASSERT(result);                                                             \
  }

    OS_IMPL_RESET(resetTankVolume, TankVolume)
    OS_IMPL_RESET(resetDeadbandTemperatureDifference, DeadbandTemperatureDifference)
    OS_IMPL_RESET(resetMaximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_RESET(resetHeaterControlType, HeaterControlType)
    OS_IMPL_RESET(resetHeaterMaximumCapacity, HeaterMaximumCapacity)
    OS_IMPL_RESET(resetHeaterMinimumCapacity, HeaterMinimumCapacity)
    OS_IMPL_RESET(resetHeaterIgnitionMinimumFlowRate, HeaterIgnitionMinimumFlowRate)
    OS_IMPL_RESET(resetHeaterIgnitionDelay, HeaterIgnitionDelay)
    OS_IMPL_RESET(resetHeaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_RESET(resetOffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_RESET(resetOffCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_RESET(resetOffCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_RESET(resetOnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_RESET(resetOnCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_RESET(resetOnCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_RESET(resetOffCycleLossCoefficienttoAmbientTemperature, OffCycleLossCoefficienttoAmbientTemperature)
    OS_IMPL_RESET(resetOffCycleLossFractiontoThermalZone, OffCycleLossFractiontoZone)
    OS_IMPL_RESET(resetOnCycleLossCoefficienttoAmbientTemperature, OnCycleLossCoefficienttoAmbientTemperature)
    OS_IMPL_RESET(resetOnCycleLossFractiontoThermalZone, OnCycleLossFractiontoZone)
    OS_IMPL_RESET(resetPeakUseFlowRate, PeakUseFlowRate)
    OS_IMPL_RESET(resetUseSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_RESET(resetSourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_RESET(resetUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_RESET(resetSourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_RESET(resetIndirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
#undef OS_IMPL_RESET
#undef OS_IMPL_RESET

#define OS_IMPL_AUTOSIZE(method, field)                                           \
  void WaterHeaterMixed_Impl::method() {                                          \
    OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::field, "autosize")); \
  }

    OS_IMPL_AUTOSIZE(autosizeTankVolume, TankVolume)
    OS_IMPL_AUTOSIZE(autosizeHeaterMaximumCapacity, HeaterMaximumCapacity)
    OS_IMPL_AUTOSIZE(autosizeUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_AUTOSIZE(autosizeSourceSideDesignFlowRate, SourceSideDesignFlowRate)
#undef OS_IMPL_AUTOSIZE

    boost::optional<double> WaterHeaterMixed_Impl::autosizedTankVolume() const {
      return getAutosizedValue("Design Size Tank Volume", "m3");
    }

    boost::optional<double> WaterHeaterMixed_Impl::autosizedHeaterMaximumCapacity() const {
      return getAutosizedValue("Design Size Heater Maximum Capacity", "W");
    }

    boost::optional<double> WaterHeaterMixed_Impl::autosizedUseSideDesignFlowRate() const {
      return getAutosizedValue("Design Size Use Side Design Flow Rate", "m3/s");
    }

    boost::optional<double> WaterHeaterMixed_Impl::autosizedSourceSideDesignFlowRate() const {
      return getAutosizedValue("Design Size Source Side Design Flow Rate", "m3/s");
    }

    bool WaterHeaterMixed_Impl::setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode) {
      if (openstudio::istringEqual("IndirectHeatAlternateSetpoint", sourceSideFlowControlMode)) {
        if (!indirectAlternateSetpointTemperatureSchedule()) {
          return false;
        }
        return setString(openstudio::WaterHeater_MixedFields::SourceSideFlowControlMode, sourceSideFlowControlMode);
      }

      const bool result = setString(openstudio::WaterHeater_MixedFields::SourceSideFlowControlMode, sourceSideFlowControlMode);
      if (result && indirectAlternateSetpointTemperatureSchedule()) {
        OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::IndirectAlternateSetpointTemperatureScheduleName, ""));
      }
      return result;
    }

    boost::optional<Schedule> WaterHeaterMixed_Impl::indirectAlternateSetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_MixedFields::IndirectAlternateSetpointTemperatureScheduleName);
    }

    bool WaterHeaterMixed_Impl::setIndirectAlternateSetpointTemperatureSchedule(Schedule& indirectAlternateSetpointTemperatureSchedule) {
      bool result = setSchedule(openstudio::WaterHeater_MixedFields::IndirectAlternateSetpointTemperatureScheduleName, "WaterHeaterMixed",
                                "Indirect Alternate Setpoint Temperature", indirectAlternateSetpointTemperatureSchedule);
      if (result && !openstudio::istringEqual("IndirectHeatAlternateSetpoint", sourceSideFlowControlMode())) {
        result = setString(openstudio::WaterHeater_MixedFields::SourceSideFlowControlMode, "IndirectHeatAlternateSetpoint");
      }
      return result;
    }

    void WaterHeaterMixed_Impl::resetIndirectAlternateSetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::IndirectAlternateSetpointTemperatureScheduleName, ""));
      if (openstudio::istringEqual("IndirectHeatAlternateSetpoint", sourceSideFlowControlMode())) {
        OS_ASSERT(setString(openstudio::WaterHeater_MixedFields::SourceSideFlowControlMode, "IndirectHeatPrimarySetpoint"));
      }
    }

    WaterHeaterSizing WaterHeaterMixed_Impl::waterHeaterSizing() const {
      for (const auto& source : getObject<ModelObject>().getSources(WaterHeaterSizing::iddObjectType())) {
        if (auto sizing = source.optionalCast<WaterHeaterSizing>()) {
          try {
            if (sizing->waterHeater().handle() == handle()) {
              return *sizing;
            }
          } catch (const std::exception&) {
          }
        }
      }
      throw std::runtime_error("WaterHeaterMixed missing WaterHeater:Sizing object.");
    }

    boost::optional<PlantLoop> WaterHeaterMixed_Impl::plantLoop() const {
      if (auto sourceSidePlantLoop = secondaryPlantLoop()) {
        for (const auto& plantLoop : model().getConcreteModelObjects<PlantLoop>()) {
          const auto supplyComponents = plantLoop.supplyComponents(openstudio::IddObjectType::Catchall);
          const auto matchesSourceLoop = std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const auto& component) {
            return component.handle() == handle();
          });
          if (matchesSourceLoop != supplyComponents.end() && plantLoop.handle() != sourceSidePlantLoop->handle()) {
            return plantLoop;
          }
        }
      }

      return WaterToWaterComponent_Impl::plantLoop();
    }

    boost::optional<PlantLoop> WaterHeaterMixed_Impl::secondaryPlantLoop() const {
      if (auto secondaryLoop = WaterToWaterComponent_Impl::secondaryPlantLoop()) {
        return secondaryLoop;
      }

      auto sourceSideOutletModelObject_ = demandOutletModelObject();
      if (!sourceSideOutletModelObject_) {
        return boost::none;
      }

      auto sourceSideOutletNode_ = sourceSideOutletModelObject_->optionalCast<Node>();
      if (!sourceSideOutletNode_) {
        return boost::none;
      }

      if (auto sourceSidePlantLoop = sourceSideOutletNode_->plantLoop()) {
        const auto supplyComponents = sourceSidePlantLoop->supplyComponents(openstudio::IddObjectType::Catchall);
        const auto matchesSourceLoop = std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const auto& component) {
          return component.handle() == handle();
        });
        if (matchesSourceLoop != supplyComponents.end()) {
          return sourceSidePlantLoop;
        }
      }

      return boost::none;
    }

    bool WaterHeaterMixed_Impl::removeFromSecondaryPlantLoop() {
      return removeFromBranch(demandInletPort(), demandOutletPort(), secondaryPlantLoop());
    }

    bool WaterHeaterMixed_Impl::addToNode(Node& node) {
      auto t_plantLoop = node.plantLoop();
      if (t_plantLoop && t_plantLoop->supplyComponent(node.handle())) {
        if (auto useSidePlant = plantLoop()) {
          if (t_plantLoop->handle() != useSidePlant->handle()) {
            return addToSourceSideNode(node);
          }
        }
      }

      return WaterToWaterComponent_Impl::addToNode(node);
    }

    bool WaterHeaterMixed_Impl::addToSourceSideNode(Node& node) {
      auto t_plantLoop = node.plantLoop();
      if (!t_plantLoop) {
        return false;
      }

      auto branch = t_plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
      if (!branch) {
        return false;
      }

      if (t_plantLoop->supplyComponent(node.handle()) || t_plantLoop->demandComponent(node.handle())) {
        removeFromSecondaryPlantLoop();
        return insertOnBranch(node, *branch, demandInletPort(), demandOutletPort());
      }

      return false;
    }

    openstudio::ComponentType WaterHeaterMixed_Impl::componentType() const {
      if (auto heaterMaximumCapacity_ = heaterMaximumCapacity()) {
        if (*heaterMaximumCapacity_ == 0.0) {
          if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
            return sourceSidePlantLoop_->componentType();
          }
          if (containingZoneHVACComponent()) {
            return openstudio::ComponentType::Heating;
          }
          return openstudio::ComponentType::None;
        }

        return openstudio::ComponentType::Heating;
      }

      return openstudio::ComponentType::Heating;
    }

    std::vector<openstudio::FuelType> WaterHeaterMixed_Impl::coolingFuelTypes() const {
      std::set<openstudio::FuelType> result;
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->coolingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      return {result.begin(), result.end()};
    }

    std::vector<openstudio::FuelType> WaterHeaterMixed_Impl::heatingFuelTypes() const {
      std::set<openstudio::FuelType> result;
      if (auto heaterMaximumCapacity_ = heaterMaximumCapacity(); heaterMaximumCapacity_ && (*heaterMaximumCapacity_ > 0.0)) {
        result.insert(openstudio::FuelType(heaterFuelType()));
      }
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->heatingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      if (containingZoneHVACComponent()) {
        result.insert(openstudio::FuelType::Electricity);
      }
      return {result.begin(), result.end()};
    }

    std::vector<openstudio::AppGFuelType> WaterHeaterMixed_Impl::appGHeatingFuelTypes() const {
      std::set<openstudio::AppGFuelType> result;
      if (auto heaterMaximumCapacity_ = heaterMaximumCapacity(); heaterMaximumCapacity_ && (*heaterMaximumCapacity_ > 0.0)) {
        result.insert(convertFuelTypeToAppG(openstudio::FuelType(heaterFuelType())));
      }
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->appGHeatingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      if (containingZoneHVACComponent()) {
        result.insert(openstudio::AppGFuelType::HeatPump);
      }
      return {result.begin(), result.end()};
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
