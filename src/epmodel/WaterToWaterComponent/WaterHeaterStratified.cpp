/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/WaterHeaterSizing.hpp"
#include "ModelObject/WaterHeaterSizing_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump_Impl.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_Stratified_FieldEnums.hxx>

#include <utility>

#include <set>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  WaterHeaterStratified::WaterHeaterStratified(const Model& model) : WaterToWaterComponent(WaterHeaterStratified::iddObjectType(), model) {
    setTankVolume(0.1893);
    setTankHeight(1.4);
    setTankShape("VerticalCylinder");
    setMaximumTemperatureLimit(82.22);
    setHeaterPriorityControl("MasterSlave");

    ScheduleConstant heater1Setpoint(model);
    ScheduleConstant heater2Setpoint(model);
    ScheduleConstant ambientSchedule(model);
    OS_ASSERT(heater1Setpoint.setValue(48.89));
    OS_ASSERT(heater2Setpoint.setValue(48.89));
    OS_ASSERT(ambientSchedule.setValue(22.0));

    OS_ASSERT(setHeater1SetpointTemperatureSchedule(heater1Setpoint));
    setHeater1DeadbandTemperatureDifference(2.0);
    setHeater1Capacity(4500.0);
    setHeater1Height(1.0);

    OS_ASSERT(setHeater2SetpointTemperatureSchedule(heater2Setpoint));
    setHeater2DeadbandTemperatureDifference(5.0);
    setHeater2Capacity(4500.0);
    setHeater2Height(0.0);

    setHeaterFuelType(FuelType::Electricity);
    setHeaterThermalEfficiency(0.98);
    setOffCycleParasiticFuelConsumptionRate(10.0);
    setOffCycleParasiticFuelType(FuelType::Electricity);
    setOffCycleParasiticHeatFractiontoTank(0.0);
    setOffCycleParasiticHeight(0.0);
    setOnCycleParasiticFuelConsumptionRate(10.0);
    setOnCycleParasiticFuelType(FuelType::Electricity);
    setOnCycleParasiticHeatFractiontoTank(0.0);
    setOnCycleParasiticHeight(0.0);
    setAmbientTemperatureIndicator("Schedule");
    OS_ASSERT(setAmbientTemperatureSchedule(ambientSchedule));
    setSkinLossFractiontoZone(1.0);
    setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(0.846);
    setOffCycleFlueLossCoefficienttoAmbientTemperature(0.0);
    setOffCycleFlueLossFractiontoZone(1.0);
    setUseSideEffectiveness(1.0);
    setUseSideInletHeight(0.0);
    autocalculateUseSideOutletHeight();
    setSourceSideEffectiveness(1.0);
    autocalculateSourceSideInletHeight();
    setSourceSideOutletHeight(0.0);
    setInletMode("Fixed");
    autosizeUseSideDesignFlowRate();
    autosizeSourceSideDesignFlowRate();
    setIndirectWaterHeatingRecoveryTime(1.5);
    setEndUseSubcategory("General");
    setNumberofNodes(6);
    setAdditionalDestratificationConductivity(0.1);
    setNode1AdditionalLossCoefficient(0.15);
    setNode2AdditionalLossCoefficient(0.0);
    setNode3AdditionalLossCoefficient(0.0);
    setNode4AdditionalLossCoefficient(0.0);
    setNode5AdditionalLossCoefficient(0.0);
    setNode6AdditionalLossCoefficient(0.1);
    setNode7AdditionalLossCoefficient(0.0);
    setNode8AdditionalLossCoefficient(0.0);
    setNode9AdditionalLossCoefficient(0.0);
    setNode10AdditionalLossCoefficient(0.0);
    setNode11AdditionalLossCoefficient(0.0);
    setNode12AdditionalLossCoefficient(0.0);
    setSourceSideFlowControlMode("IndirectHeatPrimarySetpoint");

    WaterHeaterSizing waterHeaterSizing(*this);
  }

  WaterHeaterStratified::WaterHeaterStratified(std::shared_ptr<detail::WaterHeaterStratified_Impl> impl) : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType WaterHeaterStratified::iddObjectType() {
    return IddObjectType::WaterHeater_Stratified;
  }

  std::vector<std::string> WaterHeaterStratified::tankShapeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::TankShape);
  }

  std::vector<std::string> WaterHeaterStratified::heaterPriorityControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::HeaterPriorityControl);
  }

  std::vector<std::string> WaterHeaterStratified::heaterFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::HeaterFuelType);
  }

  std::vector<std::string> WaterHeaterStratified::offCycleParasiticFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::OffCycleParasiticFuelType);
  }

  std::vector<std::string> WaterHeaterStratified::onCycleParasiticFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::OnCycleParasiticFuelType);
  }

  std::vector<std::string> WaterHeaterStratified::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::AmbientTemperatureIndicator);
  }

  std::vector<std::string> WaterHeaterStratified::inletModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::InletMode);
  }

  std::vector<std::string> WaterHeaterStratified::sourceSideFlowControlModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::SourceSideFlowControlMode);
  }

  std::string WaterHeaterStratified::endUseSubcategory() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->endUseSubcategory();
  }
  bool WaterHeaterStratified::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  boost::optional<double> WaterHeaterStratified::tankVolume() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->tankVolume();
  }
  bool WaterHeaterStratified::setTankVolume(double tankVolume) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setTankVolume(tankVolume);
  }
  void WaterHeaterStratified::autosizeTankVolume() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autosizeTankVolume();
  }
  bool WaterHeaterStratified::isTankVolumeAutosized() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isTankVolumeAutosized();
  }
  boost::optional<double> WaterHeaterStratified::autosizedTankVolume() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->autosizedTankVolume();
  }

  boost::optional<double> WaterHeaterStratified::tankHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->tankHeight();
  }
  bool WaterHeaterStratified::setTankHeight(double tankHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setTankHeight(tankHeight);
  }
  void WaterHeaterStratified::autosizeTankHeight() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autosizeTankHeight();
  }
  bool WaterHeaterStratified::isTankHeightAutosized() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isTankHeightAutosized();
  }
  boost::optional<double> WaterHeaterStratified::autosizedTankHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->autosizedTankHeight();
  }

  std::string WaterHeaterStratified::tankShape() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->tankShape();
  }
  bool WaterHeaterStratified::setTankShape(const std::string& tankShape) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setTankShape(tankShape);
  }

  boost::optional<double> WaterHeaterStratified::tankPerimeter() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->tankPerimeter();
  }
  bool WaterHeaterStratified::setTankPerimeter(double tankPerimeter) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setTankPerimeter(tankPerimeter);
  }
  void WaterHeaterStratified::resetTankPerimeter() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetTankPerimeter();
  }

  double WaterHeaterStratified::maximumTemperatureLimit() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->maximumTemperatureLimit();
  }
  bool WaterHeaterStratified::setMaximumTemperatureLimit(double maximumTemperatureLimit) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setMaximumTemperatureLimit(maximumTemperatureLimit);
  }

  std::string WaterHeaterStratified::heaterPriorityControl() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heaterPriorityControl();
  }
  bool WaterHeaterStratified::setHeaterPriorityControl(const std::string& heaterPriorityControl) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeaterPriorityControl(heaterPriorityControl);
  }

  boost::optional<Schedule> WaterHeaterStratified::heater1SetpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater1SetpointTemperatureSchedule();
  }
  bool WaterHeaterStratified::setHeater1SetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater1SetpointTemperatureSchedule(schedule);
  }
  void WaterHeaterStratified::resetHeater1SetpointTemperatureSchedule() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetHeater1SetpointTemperatureSchedule();
  }

  double WaterHeaterStratified::heater1DeadbandTemperatureDifference() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater1DeadbandTemperatureDifference();
  }
  bool WaterHeaterStratified::setHeater1DeadbandTemperatureDifference(double heater1DeadbandTemperatureDifference) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater1DeadbandTemperatureDifference(heater1DeadbandTemperatureDifference);
  }

  boost::optional<double> WaterHeaterStratified::heater1Capacity() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater1Capacity();
  }
  bool WaterHeaterStratified::setHeater1Capacity(double heater1Capacity) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater1Capacity(heater1Capacity);
  }
  void WaterHeaterStratified::autosizeHeater1Capacity() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autosizeHeater1Capacity();
  }
  bool WaterHeaterStratified::isHeater1CapacityAutosized() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isHeater1CapacityAutosized();
  }
  boost::optional<double> WaterHeaterStratified::autosizedHeater1Capacity() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->autosizedHeater1Capacity();
  }

  double WaterHeaterStratified::heater1Height() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater1Height();
  }
  bool WaterHeaterStratified::setHeater1Height(double heater1Height) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater1Height(heater1Height);
  }

  boost::optional<Schedule> WaterHeaterStratified::heater2SetpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater2SetpointTemperatureSchedule();
  }
  bool WaterHeaterStratified::setHeater2SetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater2SetpointTemperatureSchedule(schedule);
  }
  void WaterHeaterStratified::resetHeater2SetpointTemperatureSchedule() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetHeater2SetpointTemperatureSchedule();
  }

  double WaterHeaterStratified::heater2DeadbandTemperatureDifference() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater2DeadbandTemperatureDifference();
  }
  bool WaterHeaterStratified::setHeater2DeadbandTemperatureDifference(double heater2DeadbandTemperatureDifference) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater2DeadbandTemperatureDifference(heater2DeadbandTemperatureDifference);
  }

  double WaterHeaterStratified::heater2Capacity() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater2Capacity();
  }
  bool WaterHeaterStratified::setHeater2Capacity(double heater2Capacity) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater2Capacity(heater2Capacity);
  }

  double WaterHeaterStratified::heater2Height() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heater2Height();
  }
  bool WaterHeaterStratified::setHeater2Height(double heater2Height) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeater2Height(heater2Height);
  }

  std::string WaterHeaterStratified::heaterFuelType() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heaterFuelType();
  }

  double WaterHeaterStratified::heaterThermalEfficiency() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->heaterThermalEfficiency();
  }
  bool WaterHeaterStratified::setHeaterThermalEfficiency(double heaterThermalEfficiency) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeaterThermalEfficiency(heaterThermalEfficiency);
  }

  double WaterHeaterStratified::offCycleParasiticFuelConsumptionRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->offCycleParasiticFuelConsumptionRate();
  }
  bool WaterHeaterStratified::setOffCycleParasiticFuelConsumptionRate(double offCycleParasiticFuelConsumptionRate) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleParasiticFuelConsumptionRate(offCycleParasiticFuelConsumptionRate);
  }

  std::string WaterHeaterStratified::offCycleParasiticFuelType() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->offCycleParasiticFuelType();
  }

  double WaterHeaterStratified::offCycleParasiticHeatFractiontoTank() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->offCycleParasiticHeatFractiontoTank();
  }
  bool WaterHeaterStratified::setOffCycleParasiticHeatFractiontoTank(double offCycleParasiticHeatFractiontoTank) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleParasiticHeatFractiontoTank(offCycleParasiticHeatFractiontoTank);
  }

  double WaterHeaterStratified::offCycleParasiticHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->offCycleParasiticHeight();
  }
  bool WaterHeaterStratified::setOffCycleParasiticHeight(double offCycleParasiticHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleParasiticHeight(offCycleParasiticHeight);
  }

  double WaterHeaterStratified::onCycleParasiticFuelConsumptionRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->onCycleParasiticFuelConsumptionRate();
  }
  bool WaterHeaterStratified::setOnCycleParasiticFuelConsumptionRate(double onCycleParasiticFuelConsumptionRate) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOnCycleParasiticFuelConsumptionRate(onCycleParasiticFuelConsumptionRate);
  }

  std::string WaterHeaterStratified::onCycleParasiticFuelType() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->onCycleParasiticFuelType();
  }

  double WaterHeaterStratified::onCycleParasiticHeatFractiontoTank() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->onCycleParasiticHeatFractiontoTank();
  }
  bool WaterHeaterStratified::setOnCycleParasiticHeatFractiontoTank(double onCycleParasiticHeatFractiontoTank) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOnCycleParasiticHeatFractiontoTank(onCycleParasiticHeatFractiontoTank);
  }

  double WaterHeaterStratified::onCycleParasiticHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->onCycleParasiticHeight();
  }
  bool WaterHeaterStratified::setOnCycleParasiticHeight(double onCycleParasiticHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOnCycleParasiticHeight(onCycleParasiticHeight);
  }

  std::string WaterHeaterStratified::ambientTemperatureIndicator() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->ambientTemperatureIndicator();
  }
  bool WaterHeaterStratified::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setAmbientTemperatureIndicator(ambientTemperatureIndicator);
  }

  boost::optional<Schedule> WaterHeaterStratified::ambientTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->ambientTemperatureSchedule();
  }
  bool WaterHeaterStratified::setAmbientTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setAmbientTemperatureSchedule(schedule);
  }
  void WaterHeaterStratified::resetAmbientTemperatureSchedule() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetAmbientTemperatureSchedule();
  }

  boost::optional<ThermalZone> WaterHeaterStratified::ambientTemperatureThermalZone() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->ambientTemperatureThermalZone();
  }
  bool WaterHeaterStratified::setAmbientTemperatureThermalZone(const ThermalZone& thermalZone) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setAmbientTemperatureThermalZone(thermalZone);
  }
  void WaterHeaterStratified::resetAmbientTemperatureThermalZone() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetAmbientTemperatureThermalZone();
  }

  boost::optional<std::string> WaterHeaterStratified::ambientTemperatureOutdoorAirNodeName() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->ambientTemperatureOutdoorAirNodeName();
  }
  bool WaterHeaterStratified::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setAmbientTemperatureOutdoorAirNodeName(ambientTemperatureOutdoorAirNodeName);
  }
  void WaterHeaterStratified::resetAmbientTemperatureOutdoorAirNodeName() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetAmbientTemperatureOutdoorAirNodeName();
  }

  boost::optional<double> WaterHeaterStratified::uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->uniformSkinLossCoefficientperUnitAreatoAmbientTemperature();
  }
  bool WaterHeaterStratified::setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(
    double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(
      uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
  }
  void WaterHeaterStratified::resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();
  }

  double WaterHeaterStratified::skinLossFractiontoZone() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->skinLossFractiontoZone();
  }
  bool WaterHeaterStratified::setSkinLossFractiontoZone(double skinLossFractiontoZone) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setSkinLossFractiontoZone(skinLossFractiontoZone);
  }

  boost::optional<double> WaterHeaterStratified::offCycleFlueLossCoefficienttoAmbientTemperature() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->offCycleFlueLossCoefficienttoAmbientTemperature();
  }
  bool WaterHeaterStratified::setOffCycleFlueLossCoefficienttoAmbientTemperature(double offCycleFlueLossCoefficienttoAmbientTemperature) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleFlueLossCoefficienttoAmbientTemperature(
      offCycleFlueLossCoefficienttoAmbientTemperature);
  }
  void WaterHeaterStratified::resetOffCycleFlueLossCoefficienttoAmbientTemperature() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetOffCycleFlueLossCoefficienttoAmbientTemperature();
  }

  double WaterHeaterStratified::offCycleFlueLossFractiontoZone() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->offCycleFlueLossFractiontoZone();
  }
  bool WaterHeaterStratified::setOffCycleFlueLossFractiontoZone(double offCycleFlueLossFractiontoZone) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleFlueLossFractiontoZone(offCycleFlueLossFractiontoZone);
  }

  boost::optional<double> WaterHeaterStratified::peakUseFlowRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->peakUseFlowRate();
  }
  bool WaterHeaterStratified::setPeakUseFlowRate(double peakUseFlowRate) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setPeakUseFlowRate(peakUseFlowRate);
  }
  void WaterHeaterStratified::resetPeakUseFlowRate() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetPeakUseFlowRate();
  }

  boost::optional<Schedule> WaterHeaterStratified::useFlowRateFractionSchedule() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->useFlowRateFractionSchedule();
  }
  bool WaterHeaterStratified::setUseFlowRateFractionSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setUseFlowRateFractionSchedule(schedule);
  }
  void WaterHeaterStratified::resetUseFlowRateFractionSchedule() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetUseFlowRateFractionSchedule();
  }

  boost::optional<Schedule> WaterHeaterStratified::coldWaterSupplyTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->coldWaterSupplyTemperatureSchedule();
  }
  bool WaterHeaterStratified::setColdWaterSupplyTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setColdWaterSupplyTemperatureSchedule(schedule);
  }
  void WaterHeaterStratified::resetColdWaterSupplyTemperatureSchedule() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetColdWaterSupplyTemperatureSchedule();
  }

  double WaterHeaterStratified::useSideEffectiveness() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->useSideEffectiveness();
  }
  bool WaterHeaterStratified::setUseSideEffectiveness(double useSideEffectiveness) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setUseSideEffectiveness(useSideEffectiveness);
  }

  double WaterHeaterStratified::useSideInletHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->useSideInletHeight();
  }
  bool WaterHeaterStratified::setUseSideInletHeight(double useSideInletHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setUseSideInletHeight(useSideInletHeight);
  }

  boost::optional<double> WaterHeaterStratified::useSideOutletHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->useSideOutletHeight();
  }
  bool WaterHeaterStratified::setUseSideOutletHeight(double useSideOutletHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setUseSideOutletHeight(useSideOutletHeight);
  }
  void WaterHeaterStratified::autocalculateUseSideOutletHeight() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autocalculateUseSideOutletHeight();
  }
  bool WaterHeaterStratified::isUseSideOutletHeightAutocalculated() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isUseSideOutletHeightAutocalculated();
  }

  double WaterHeaterStratified::sourceSideEffectiveness() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->sourceSideEffectiveness();
  }
  bool WaterHeaterStratified::setSourceSideEffectiveness(double sourceSideEffectiveness) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setSourceSideEffectiveness(sourceSideEffectiveness);
  }

  boost::optional<double> WaterHeaterStratified::sourceSideInletHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->sourceSideInletHeight();
  }
  bool WaterHeaterStratified::setSourceSideInletHeight(double sourceSideInletHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setSourceSideInletHeight(sourceSideInletHeight);
  }
  void WaterHeaterStratified::autocalculateSourceSideInletHeight() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autocalculateSourceSideInletHeight();
  }
  bool WaterHeaterStratified::isSourceSideInletHeightAutocalculated() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isSourceSideInletHeightAutocalculated();
  }

  double WaterHeaterStratified::sourceSideOutletHeight() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->sourceSideOutletHeight();
  }
  bool WaterHeaterStratified::setSourceSideOutletHeight(double sourceSideOutletHeight) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setSourceSideOutletHeight(sourceSideOutletHeight);
  }

  std::string WaterHeaterStratified::inletMode() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->inletMode();
  }
  bool WaterHeaterStratified::setInletMode(const std::string& inletMode) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setInletMode(inletMode);
  }

  boost::optional<double> WaterHeaterStratified::useSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->useSideDesignFlowRate();
  }
  bool WaterHeaterStratified::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setUseSideDesignFlowRate(useSideDesignFlowRate);
  }
  void WaterHeaterStratified::autosizeUseSideDesignFlowRate() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autosizeUseSideDesignFlowRate();
  }
  bool WaterHeaterStratified::isUseSideDesignFlowRateAutosized() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isUseSideDesignFlowRateAutosized();
  }
  boost::optional<double> WaterHeaterStratified::autosizedUseSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->autosizedUseSideDesignFlowRate();
  }

  boost::optional<double> WaterHeaterStratified::sourceSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->sourceSideDesignFlowRate();
  }
  bool WaterHeaterStratified::setSourceSideDesignFlowRate(double sourceSideDesignFlowRate) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setSourceSideDesignFlowRate(sourceSideDesignFlowRate);
  }
  void WaterHeaterStratified::autosizeSourceSideDesignFlowRate() {
    getImpl<detail::WaterHeaterStratified_Impl>()->autosizeSourceSideDesignFlowRate();
  }
  bool WaterHeaterStratified::isSourceSideDesignFlowRateAutosized() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->isSourceSideDesignFlowRateAutosized();
  }
  boost::optional<double> WaterHeaterStratified::autosizedSourceSideDesignFlowRate() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->autosizedSourceSideDesignFlowRate();
  }

  double WaterHeaterStratified::indirectWaterHeatingRecoveryTime() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->indirectWaterHeatingRecoveryTime();
  }
  bool WaterHeaterStratified::setIndirectWaterHeatingRecoveryTime(double indirectWaterHeatingRecoveryTime) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setIndirectWaterHeatingRecoveryTime(indirectWaterHeatingRecoveryTime);
  }

  int WaterHeaterStratified::numberofNodes() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->numberofNodes();
  }
  bool WaterHeaterStratified::setNumberofNodes(int numberofNodes) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNumberofNodes(numberofNodes);
  }

  double WaterHeaterStratified::additionalDestratificationConductivity() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->additionalDestratificationConductivity();
  }
  bool WaterHeaterStratified::setAdditionalDestratificationConductivity(double additionalDestratificationConductivity) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setAdditionalDestratificationConductivity(additionalDestratificationConductivity);
  }

  double WaterHeaterStratified::node1AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node1AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode1AdditionalLossCoefficient(node1AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node2AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node2AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode2AdditionalLossCoefficient(node2AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node3AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node3AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode3AdditionalLossCoefficient(node3AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node4AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node4AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode4AdditionalLossCoefficient(node4AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node5AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node5AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode5AdditionalLossCoefficient(node5AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node6AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node6AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode6AdditionalLossCoefficient(node6AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node7AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node7AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode7AdditionalLossCoefficient(node7AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node8AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node8AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode8AdditionalLossCoefficient(node8AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node9AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node9AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode9AdditionalLossCoefficient(node9AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node10AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node10AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode10AdditionalLossCoefficient(node10AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node11AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node11AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode11AdditionalLossCoefficient(double node11AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode11AdditionalLossCoefficient(node11AdditionalLossCoefficient);
  }

  double WaterHeaterStratified::node12AdditionalLossCoefficient() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->node12AdditionalLossCoefficient();
  }
  bool WaterHeaterStratified::setNode12AdditionalLossCoefficient(double node12AdditionalLossCoefficient) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setNode12AdditionalLossCoefficient(node12AdditionalLossCoefficient);
  }

  std::string WaterHeaterStratified::sourceSideFlowControlMode() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->sourceSideFlowControlMode();
  }
  bool WaterHeaterStratified::setSourceSideFlowControlMode(const std::string& sourceSideFlowControlMode) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setSourceSideFlowControlMode(sourceSideFlowControlMode);
  }

  boost::optional<Schedule> WaterHeaterStratified::indirectAlternateSetpointTemperatureSchedule() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->indirectAlternateSetpointTemperatureSchedule();
  }
  bool WaterHeaterStratified::setIndirectAlternateSetpointTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setIndirectAlternateSetpointTemperatureSchedule(schedule);
  }
  void WaterHeaterStratified::resetIndirectAlternateSetpointTemperatureSchedule() {
    getImpl<detail::WaterHeaterStratified_Impl>()->resetIndirectAlternateSetpointTemperatureSchedule();
  }

  WaterHeaterSizing WaterHeaterStratified::waterHeaterSizing() const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->waterHeaterSizing();
  }

  ModelObject WaterHeaterStratified::clone(Model model) const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->clone(model);
  }
  bool WaterHeaterStratified::addToSourceSideNode(Node& node) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->addToSourceSideNode(node);
  }

  boost::optional<PlantLoop> WaterHeaterStratified::useSidePlantLoop() const {
    return plantLoop();
  }

  boost::optional<PlantLoop> WaterHeaterStratified::sourceSidePlantLoop() const {
    return secondaryPlantLoop();
  }

  bool WaterHeaterStratified::removeFromSourceSidePlantLoop() {
    return removeFromSecondaryPlantLoop();
  }

  boost::optional<ModelObject> WaterHeaterStratified::useSideInletModelObject() const {
    return supplyInletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterStratified::useSideOutletModelObject() const {
    return supplyOutletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterStratified::sourceSideInletModelObject() const {
    return demandInletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterStratified::sourceSideOutletModelObject() const {
    return demandOutletModelObject();
  }

  bool WaterHeaterStratified::setHeaterFuelType(const FuelType& heaterFuelType) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeaterFuelType(heaterFuelType.valueDescription());
  }

  bool WaterHeaterStratified::setHeaterFuelType(const std::string& heaterFuelType) {
    try {
      return setHeaterFuelType(FuelType{heaterFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  bool WaterHeaterStratified::setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleParasiticFuelType(offCycleParasiticFuelType.valueDescription());
  }

  bool WaterHeaterStratified::setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType) {
    try {
      return setOffCycleParasiticFuelType(FuelType{offCycleParasiticFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  bool WaterHeaterStratified::setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOnCycleParasiticFuelType(onCycleParasiticFuelType.valueDescription());
  }

  bool WaterHeaterStratified::setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType) {
    try {
      return setOnCycleParasiticFuelType(FuelType{onCycleParasiticFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  namespace detail {

    namespace {

      bool isAutosize(const ModelObject_Impl& impl, int fieldIndex) {
        if (auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

      bool isAutocalculate(const ModelObject_Impl& impl, int fieldIndex) {
        if (auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autocalculate");
        }
        return false;
      }

    }  // namespace

    void WaterHeaterStratified_Impl::doCanonicalize(LoadContext& context) {
      WaterToWaterComponent_Impl::doCanonicalize(context);

      try {
        waterHeaterSizing();
        return;
      } catch (const std::exception&) {
      }

      const auto waterHeater = getObject<WaterHeaterStratified>();
      WaterHeaterSizing sizing(waterHeater);
      detail::addLoadInfo(context, "Created default WaterHeater:Sizing object for WaterHeater:Stratified '" + waterHeater.nameString() + "'.");
    }

    std::vector<ModelObject> WaterHeaterStratified_Impl::children() const {
      return {waterHeaterSizing()};
    }

    ModelObject WaterHeaterStratified_Impl::clone(Model model) const {
      auto heaterCloneObject = model.addObject(idfObject());
      OS_ASSERT(heaterCloneObject);
      auto heaterClone = heaterCloneObject->cast<WaterHeaterStratified>();

      OS_ASSERT(heaterClone.setString(heaterClone.supplyInletPort(), ""));
      OS_ASSERT(heaterClone.setString(heaterClone.supplyOutletPort(), ""));
      OS_ASSERT(heaterClone.setString(heaterClone.demandInletPort(), ""));
      OS_ASSERT(heaterClone.setString(heaterClone.demandOutletPort(), ""));

      auto sizingCloneObject = model.addObject(waterHeaterSizing().idfObject());
      OS_ASSERT(sizingCloneObject);
      auto sizingClone = sizingCloneObject->cast<WaterHeaterSizing>();
      OS_ASSERT(sizingClone.getImpl<WaterHeaterSizing_Impl>()->setWaterHeater(heaterClone));

      return heaterClone;
    }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                               \
  boost::optional<double> WaterHeaterStratified_Impl::method() const {       \
    return getDouble(openstudio::WaterHeater_StratifiedFields::field, true); \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                           \
  double WaterHeaterStratified_Impl::method() const {                                    \
    const auto value = getDouble(openstudio::WaterHeater_StratifiedFields::field, true); \
    OS_ASSERT(value);                                                                    \
    return *value;                                                                       \
  }

#define OS_IMPL_OPTIONAL_STRING(method, field)                                     \
  boost::optional<std::string> WaterHeaterStratified_Impl::method() const {        \
    return getString(openstudio::WaterHeater_StratifiedFields::field, true, true); \
  }

#define OS_IMPL_REQUIRED_STRING(method, field)                                           \
  std::string WaterHeaterStratified_Impl::method() const {                               \
    const auto value = getString(openstudio::WaterHeater_StratifiedFields::field, true); \
    OS_ASSERT(value);                                                                    \
    return *value;                                                                       \
  }

#define OS_IMPL_IS_AUTOSIZED(method, field)                                    \
  bool WaterHeaterStratified_Impl::method() const {                            \
    return isAutosize(*this, openstudio::WaterHeater_StratifiedFields::field); \
  }

#define OS_IMPL_IS_AUTOCALCULATED(method, field)                                    \
  bool WaterHeaterStratified_Impl::method() const {                                 \
    return isAutocalculate(*this, openstudio::WaterHeater_StratifiedFields::field); \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                     \
  bool WaterHeaterStratified_Impl::method(double value) {                     \
    return setDouble(openstudio::WaterHeater_StratifiedFields::field, value); \
  }

#define OS_IMPL_SET_STRING(method, field)                                     \
  bool WaterHeaterStratified_Impl::method(const std::string& value) {         \
    return setString(openstudio::WaterHeater_StratifiedFields::field, value); \
  }

#define OS_IMPL_SET_INT(method, field)                                     \
  bool WaterHeaterStratified_Impl::method(int value) {                     \
    return setInt(openstudio::WaterHeater_StratifiedFields::field, value); \
  }

#define OS_IMPL_REQUIRED_INT(method, field)                                           \
  int WaterHeaterStratified_Impl::method() const {                                    \
    const auto value = getInt(openstudio::WaterHeater_StratifiedFields::field, true); \
    OS_ASSERT(value);                                                                 \
    return *value;                                                                    \
  }

#define OS_IMPL_RESET(method, field)                                                    \
  void WaterHeaterStratified_Impl::method() {                                           \
    const bool result = setString(openstudio::WaterHeater_StratifiedFields::field, ""); \
    OS_ASSERT(result);                                                                  \
  }

#define OS_IMPL_AUTOSIZE(method, field)                                                         \
  void WaterHeaterStratified_Impl::method() {                                                   \
    const bool result = setString(openstudio::WaterHeater_StratifiedFields::field, "autosize"); \
    OS_ASSERT(result);                                                                          \
  }

#define OS_IMPL_AUTOCALCULATE(method, field)                                                         \
  void WaterHeaterStratified_Impl::method() {                                                        \
    const bool result = setString(openstudio::WaterHeater_StratifiedFields::field, "autocalculate"); \
    OS_ASSERT(result);                                                                               \
  }

    OS_IMPL_OPTIONAL_DOUBLE(tankVolume, TankVolume)
    OS_IMPL_IS_AUTOSIZED(isTankVolumeAutosized, TankVolume)
    OS_IMPL_OPTIONAL_DOUBLE(tankHeight, TankHeight)
    OS_IMPL_IS_AUTOSIZED(isTankHeightAutosized, TankHeight)
    OS_IMPL_REQUIRED_STRING(tankShape, TankShape)
    OS_IMPL_OPTIONAL_DOUBLE(tankPerimeter, TankPerimeter)
    OS_IMPL_REQUIRED_DOUBLE(maximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_REQUIRED_STRING(heaterPriorityControl, HeaterPriorityControl)
    boost::optional<Schedule> WaterHeaterStratified_Impl::heater1SetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName);
    }
    OS_IMPL_REQUIRED_DOUBLE(heater1DeadbandTemperatureDifference, Heater1DeadbandTemperatureDifference)
    OS_IMPL_OPTIONAL_DOUBLE(heater1Capacity, Heater1Capacity)
    OS_IMPL_IS_AUTOSIZED(isHeater1CapacityAutosized, Heater1Capacity)
    OS_IMPL_REQUIRED_DOUBLE(heater1Height, Heater1Height)
    boost::optional<Schedule> WaterHeaterStratified_Impl::heater2SetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName);
    }
    OS_IMPL_REQUIRED_DOUBLE(heater2DeadbandTemperatureDifference, Heater2DeadbandTemperatureDifference)
    OS_IMPL_REQUIRED_DOUBLE(heater2Capacity, Heater2Capacity)
    OS_IMPL_REQUIRED_DOUBLE(heater2Height, Heater2Height)
    OS_IMPL_REQUIRED_STRING(heaterFuelType, HeaterFuelType)
    OS_IMPL_REQUIRED_DOUBLE(heaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_REQUIRED_STRING(offCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticHeight, OffCycleParasiticHeight)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_REQUIRED_STRING(onCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticHeight, OnCycleParasiticHeight)
    std::string WaterHeaterStratified_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::WaterHeater_StratifiedFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }
    std::string WaterHeaterStratified_Impl::ambientTemperatureIndicator() const {
      const auto value = getString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureIndicator, true);
      OS_ASSERT(value);
      if (openstudio::istringEqual(*value, "Zone")) {
        return "ThermalZone";
      }
      return *value;
    }
    boost::optional<Schedule> WaterHeaterStratified_Impl::ambientTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureScheduleName);
    }
    boost::optional<ThermalZone> WaterHeaterStratified_Impl::ambientTemperatureThermalZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureZoneName);
    }
    OS_IMPL_OPTIONAL_STRING(ambientTemperatureOutdoorAirNodeName, AmbientTemperatureOutdoorAirNodeName)
    OS_IMPL_OPTIONAL_DOUBLE(uniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
    OS_IMPL_REQUIRED_DOUBLE(skinLossFractiontoZone, SkinLossFractiontoZone)
    OS_IMPL_OPTIONAL_DOUBLE(offCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossCoefficienttoAmbientTemperature)
    OS_IMPL_REQUIRED_DOUBLE(offCycleFlueLossFractiontoZone, OffCycleFlueLossFractiontoZone)
    OS_IMPL_OPTIONAL_DOUBLE(peakUseFlowRate, PeakUseFlowRate)
    boost::optional<Schedule> WaterHeaterStratified_Impl::useFlowRateFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName);
    }
    boost::optional<Schedule> WaterHeaterStratified_Impl::coldWaterSupplyTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName);
    }
    OS_IMPL_REQUIRED_DOUBLE(useSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_REQUIRED_DOUBLE(useSideInletHeight, UseSideInletHeight)
    OS_IMPL_OPTIONAL_DOUBLE(useSideOutletHeight, UseSideOutletHeight)
    OS_IMPL_IS_AUTOCALCULATED(isUseSideOutletHeightAutocalculated, UseSideOutletHeight)
    OS_IMPL_REQUIRED_DOUBLE(sourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_OPTIONAL_DOUBLE(sourceSideInletHeight, SourceSideInletHeight)
    OS_IMPL_IS_AUTOCALCULATED(isSourceSideInletHeightAutocalculated, SourceSideInletHeight)
    OS_IMPL_REQUIRED_DOUBLE(sourceSideOutletHeight, SourceSideOutletHeight)
    OS_IMPL_REQUIRED_STRING(inletMode, InletMode)
    OS_IMPL_OPTIONAL_DOUBLE(useSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_IS_AUTOSIZED(isUseSideDesignFlowRateAutosized, UseSideDesignFlowRate)
    OS_IMPL_OPTIONAL_DOUBLE(sourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_IS_AUTOSIZED(isSourceSideDesignFlowRateAutosized, SourceSideDesignFlowRate)
    OS_IMPL_REQUIRED_DOUBLE(indirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
    OS_IMPL_REQUIRED_INT(numberofNodes, NumberofNodes)
    OS_IMPL_REQUIRED_DOUBLE(additionalDestratificationConductivity, AdditionalDestratificationConductivity)
    OS_IMPL_REQUIRED_DOUBLE(node1AdditionalLossCoefficient, Node1AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node2AdditionalLossCoefficient, Node2AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node3AdditionalLossCoefficient, Node3AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node4AdditionalLossCoefficient, Node4AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node5AdditionalLossCoefficient, Node5AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node6AdditionalLossCoefficient, Node6AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node7AdditionalLossCoefficient, Node7AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node8AdditionalLossCoefficient, Node8AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node9AdditionalLossCoefficient, Node9AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node10AdditionalLossCoefficient, Node10AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node11AdditionalLossCoefficient, Node11AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node12AdditionalLossCoefficient, Node12AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_STRING(sourceSideFlowControlMode, SourceSideFlowControlMode)
    boost::optional<Schedule> WaterHeaterStratified_Impl::indirectAlternateSetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName);
    }

    boost::optional<double> WaterHeaterStratified_Impl::autosizedTankVolume() const {
      return getAutosizedValue("Design Size Tank Volume", "m3");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedTankHeight() const {
      return getAutosizedValue("Design Size Tank Height", "m");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedHeater1Capacity() const {
      return getAutosizedValue("Design Size Heater 1 Capacity", "W");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedUseSideDesignFlowRate() const {
      return getAutosizedValue("Design Size Use Side Design Flow Rate", "m3/s");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedSourceSideDesignFlowRate() const {
      return getAutosizedValue("Design Size Source Side Design Flow Rate", "m3/s");
    }

    OS_IMPL_SET_STRING(setEndUseSubcategory, EndUseSubcategory)
    OS_IMPL_SET_DOUBLE(setTankVolume, TankVolume)
    OS_IMPL_AUTOSIZE(autosizeTankVolume, TankVolume)
    OS_IMPL_SET_DOUBLE(setTankHeight, TankHeight)
    OS_IMPL_AUTOSIZE(autosizeTankHeight, TankHeight)
    OS_IMPL_SET_STRING(setTankShape, TankShape)
    OS_IMPL_SET_DOUBLE(setTankPerimeter, TankPerimeter)
    OS_IMPL_RESET(resetTankPerimeter, TankPerimeter)
    OS_IMPL_SET_DOUBLE(setMaximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_SET_STRING(setHeaterPriorityControl, HeaterPriorityControl)
    bool WaterHeaterStratified_Impl::setHeater1SetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName, "WaterHeaterStratified",
                         "Heater 1 Setpoint Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetHeater1SetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName, ""));
    }
    OS_IMPL_SET_DOUBLE(setHeater1DeadbandTemperatureDifference, Heater1DeadbandTemperatureDifference)
    OS_IMPL_SET_DOUBLE(setHeater1Capacity, Heater1Capacity)
    OS_IMPL_AUTOSIZE(autosizeHeater1Capacity, Heater1Capacity)
    OS_IMPL_SET_DOUBLE(setHeater1Height, Heater1Height)
    bool WaterHeaterStratified_Impl::setHeater2SetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName, "WaterHeaterStratified",
                         "Heater 2 Setpoint Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetHeater2SetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName, ""));
    }
    OS_IMPL_SET_DOUBLE(setHeater2DeadbandTemperatureDifference, Heater2DeadbandTemperatureDifference)
    OS_IMPL_SET_DOUBLE(setHeater2Capacity, Heater2Capacity)
    OS_IMPL_SET_DOUBLE(setHeater2Height, Heater2Height)
    OS_IMPL_SET_STRING(setHeaterFuelType, HeaterFuelType)
    OS_IMPL_SET_DOUBLE(setHeaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_SET_STRING(setOffCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticHeight, OffCycleParasiticHeight)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_SET_STRING(setOnCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticHeight, OnCycleParasiticHeight)
    bool WaterHeaterStratified_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      auto normalized = ambientTemperatureIndicator;
      if (openstudio::istringEqual(ambientTemperatureIndicator, "ThermalZone")) {
        normalized = "Zone";
      }
      return setString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureIndicator, normalized);
    }
    bool WaterHeaterStratified_Impl::setAmbientTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureScheduleName, "WaterHeaterStratified", "Ambient Temperature",
                         schedule);
    }
    void WaterHeaterStratified_Impl::resetAmbientTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureScheduleName, ""));
    }
    bool WaterHeaterStratified_Impl::setAmbientTemperatureThermalZone(const ThermalZone& thermalZone) {
      return setPointer(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureZoneName, thermalZone.handle());
    }
    void WaterHeaterStratified_Impl::resetAmbientTemperatureThermalZone() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureZoneName, ""));
    }
    OS_IMPL_SET_STRING(setAmbientTemperatureOutdoorAirNodeName, AmbientTemperatureOutdoorAirNodeName)
    OS_IMPL_RESET(resetAmbientTemperatureOutdoorAirNodeName, AmbientTemperatureOutdoorAirNodeName)
    OS_IMPL_SET_DOUBLE(setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
    OS_IMPL_RESET(resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
    OS_IMPL_SET_DOUBLE(setSkinLossFractiontoZone, SkinLossFractiontoZone)
    OS_IMPL_SET_DOUBLE(setOffCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossCoefficienttoAmbientTemperature)
    OS_IMPL_RESET(resetOffCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossCoefficienttoAmbientTemperature)
    OS_IMPL_SET_DOUBLE(setOffCycleFlueLossFractiontoZone, OffCycleFlueLossFractiontoZone)
    OS_IMPL_SET_DOUBLE(setPeakUseFlowRate, PeakUseFlowRate)
    OS_IMPL_RESET(resetPeakUseFlowRate, PeakUseFlowRate)
    bool WaterHeaterStratified_Impl::setUseFlowRateFractionSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName, "WaterHeaterStratified", "Use Flow Rate Fraction",
                         schedule);
    }
    void WaterHeaterStratified_Impl::resetUseFlowRateFractionSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName, ""));
    }
    bool WaterHeaterStratified_Impl::setColdWaterSupplyTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName, "WaterHeaterStratified",
                         "Cold Water Supply Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetColdWaterSupplyTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName, ""));
    }
    OS_IMPL_SET_DOUBLE(setUseSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_SET_DOUBLE(setUseSideInletHeight, UseSideInletHeight)
    OS_IMPL_SET_DOUBLE(setUseSideOutletHeight, UseSideOutletHeight)
    OS_IMPL_AUTOCALCULATE(autocalculateUseSideOutletHeight, UseSideOutletHeight)
    OS_IMPL_SET_DOUBLE(setSourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_SET_DOUBLE(setSourceSideInletHeight, SourceSideInletHeight)
    OS_IMPL_AUTOCALCULATE(autocalculateSourceSideInletHeight, SourceSideInletHeight)
    OS_IMPL_SET_DOUBLE(setSourceSideOutletHeight, SourceSideOutletHeight)
    OS_IMPL_SET_STRING(setInletMode, InletMode)
    OS_IMPL_SET_DOUBLE(setUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_AUTOSIZE(autosizeUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_SET_DOUBLE(setSourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_AUTOSIZE(autosizeSourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_SET_DOUBLE(setIndirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
    OS_IMPL_SET_INT(setNumberofNodes, NumberofNodes)
    OS_IMPL_SET_DOUBLE(setAdditionalDestratificationConductivity, AdditionalDestratificationConductivity)
    OS_IMPL_SET_DOUBLE(setNode1AdditionalLossCoefficient, Node1AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode2AdditionalLossCoefficient, Node2AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode3AdditionalLossCoefficient, Node3AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode4AdditionalLossCoefficient, Node4AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode5AdditionalLossCoefficient, Node5AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode6AdditionalLossCoefficient, Node6AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode7AdditionalLossCoefficient, Node7AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode8AdditionalLossCoefficient, Node8AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode9AdditionalLossCoefficient, Node9AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode10AdditionalLossCoefficient, Node10AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode11AdditionalLossCoefficient, Node11AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode12AdditionalLossCoefficient, Node12AdditionalLossCoefficient)
    OS_IMPL_SET_STRING(setSourceSideFlowControlMode, SourceSideFlowControlMode)
    bool WaterHeaterStratified_Impl::setIndirectAlternateSetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName, "WaterHeaterStratified",
                         "Indirect Alternate Setpoint Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetIndirectAlternateSetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName, ""));
    }

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_OPTIONAL_STRING
#undef OS_IMPL_REQUIRED_STRING
#undef OS_IMPL_IS_AUTOSIZED
#undef OS_IMPL_IS_AUTOCALCULATED
#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING
#undef OS_IMPL_SET_INT
#undef OS_IMPL_REQUIRED_INT
#undef OS_IMPL_RESET
#undef OS_IMPL_AUTOSIZE
#undef OS_IMPL_AUTOCALCULATE

    unsigned WaterHeaterStratified_Impl::supplyInletPort() const {
      return openstudio::WaterHeater_StratifiedFields::UseSideInletNodeName;
    }

    unsigned WaterHeaterStratified_Impl::supplyOutletPort() const {
      return openstudio::WaterHeater_StratifiedFields::UseSideOutletNodeName;
    }

    unsigned WaterHeaterStratified_Impl::demandInletPort() const {
      return openstudio::WaterHeater_StratifiedFields::SourceSideInletNodeName;
    }

    unsigned WaterHeaterStratified_Impl::demandOutletPort() const {
      return openstudio::WaterHeater_StratifiedFields::SourceSideOutletNodeName;
    }

    WaterHeaterSizing WaterHeaterStratified_Impl::waterHeaterSizing() const {
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
      throw std::runtime_error("WaterHeaterStratified missing WaterHeater:Sizing object.");
    }

    boost::optional<PlantLoop> WaterHeaterStratified_Impl::plantLoop() const {
      if (auto sourceSidePlantLoop = secondaryPlantLoop()) {
        for (const auto& plantLoop : model().getConcreteModelObjects<PlantLoop>()) {
          const auto supplyComponents = plantLoop.supplyComponents(openstudio::IddObjectType::Catchall);
          const auto matchesSourceLoop =
            std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const auto& component) { return component.handle() == handle(); });
          if (matchesSourceLoop != supplyComponents.end() && plantLoop.handle() != sourceSidePlantLoop->handle()) {
            return plantLoop;
          }
        }
      }

      return WaterToWaterComponent_Impl::plantLoop();
    }

    boost::optional<PlantLoop> WaterHeaterStratified_Impl::secondaryPlantLoop() const {
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
        const auto matchesSourceLoop =
          std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const auto& component) { return component.handle() == handle(); });
        if (matchesSourceLoop != supplyComponents.end()) {
          return sourceSidePlantLoop;
        }
      }

      return boost::none;
    }

    bool WaterHeaterStratified_Impl::removeFromSecondaryPlantLoop() {
      return removeFromBranch(demandInletPort(), demandOutletPort(), secondaryPlantLoop());
    }

    bool WaterHeaterStratified_Impl::addToNode(Node& node) {
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

    bool WaterHeaterStratified_Impl::addToSourceSideNode(Node& node) {
      auto t_plantLoop = node.plantLoop();
      if (!t_plantLoop) {
        return false;
      }

      auto branch = t_plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
      if (!branch) {
        return false;
      }

      const auto branchComponents = branch->components();
      if (std::ranges::find_if(branchComponents, [&](const auto& component) { return component.handle() == handle(); }) != branchComponents.end()) {
        return false;
      }

      if (t_plantLoop->supplyComponent(node.handle()) || t_plantLoop->demandComponent(node.handle())) {
        removeFromSecondaryPlantLoop();
        return insertOnBranch(node, *branch, demandInletPort(), demandOutletPort());
      }

      return false;
    }

    openstudio::ComponentType WaterHeaterStratified_Impl::componentType() const {
      if (isHeater1CapacityAutosized() || ((heater1Capacity().get() + heater2Capacity()) > 0.01)) {
        return openstudio::ComponentType::Heating;
      }

      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        return sourceSidePlantLoop_->componentType();
      }

      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPump>()) {
        if (hpwh.tank().handle() == handle()) {
          return openstudio::ComponentType::Heating;
        }
      }

      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPumpWrappedCondenser>()) {
        if (hpwh.tank().handle() == handle()) {
          return openstudio::ComponentType::Heating;
        }
      }

      return openstudio::ComponentType::None;
    }

    std::vector<openstudio::FuelType> WaterHeaterStratified_Impl::coolingFuelTypes() const {
      std::set<openstudio::FuelType> result;
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->coolingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      return {result.begin(), result.end()};
    }

    std::vector<openstudio::FuelType> WaterHeaterStratified_Impl::heatingFuelTypes() const {
      std::set<openstudio::FuelType> result;
      if (isHeater1CapacityAutosized() || ((heater1Capacity().get() + heater2Capacity()) > 0.01)) {
        result.insert(openstudio::FuelType(heaterFuelType()));
      }
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->heatingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPump>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::FuelType::Electricity);
        }
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPumpWrappedCondenser>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::FuelType::Electricity);
        }
      }
      return {result.begin(), result.end()};
    }

    std::vector<openstudio::AppGFuelType> WaterHeaterStratified_Impl::appGHeatingFuelTypes() const {
      std::set<openstudio::AppGFuelType> result;
      if (isHeater1CapacityAutosized() || ((heater1Capacity().get() + heater2Capacity()) > 0.01)) {
        result.insert(openstudio::convertFuelTypeToAppG(openstudio::FuelType(heaterFuelType())));
      }
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->appGHeatingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPump>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::AppGFuelType::HeatPump);
        }
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPumpWrappedCondenser>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::AppGFuelType::HeatPump);
        }
      }
      return {result.begin(), result.end()};
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
