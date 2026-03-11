/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_AirToWater_FuelFired_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HeatPumpAirToWaterFuelFiredHeating::HeatPumpAirToWaterFuelFiredHeating(const Model& model)
  : StraightComponent(HeatPumpAirToWaterFuelFiredHeating::iddObjectType(), model) {
  // Mirror model default scalar behavior while excluding relationship/object fields.
  bool ok = true;
  ok &= setFuelType("NaturalGas");
  autosizeNominalHeatingCapacity();
  ok &= setNominalCOP(1.0);
  autosizeDesignFlowRate();
  ok &= setDesignSupplyTemperature(60.0);
  ok &= setDesignTemperatureLift(11.1);
  ok &= setSizingFactor(1.0);
  ok &= setFlowMode("NotModulated");
  ok &= setOutdoorAirTemperatureCurveInputVariable("DryBulb");
  ok &= setWaterTemperatureCurveInputVariable("EnteringCondenser");
  ok &= setMinimumPartLoadRatio(0.1);
  ok &= setMaximumPartLoadRatio(1.0);
  ok &= setDefrostControlType("Timed");
  ok &= setDefrostOperationTimeFraction(0.0);
  ok &= setResistiveDefrostHeaterCapacity(0.0);
  ok &= setMaximumOutdoorDrybulbTemperatureforDefrostOperation(5.0);
  ok &= setNominalAuxiliaryElectricPower(0.0);
  ok &= setStandbyElectricPower(0.0);
  ok &= setMinimumUnloadingRatio(0.25);
  OS_ASSERT(ok);
}

HeatPumpAirToWaterFuelFiredHeating::HeatPumpAirToWaterFuelFiredHeating(
  std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredHeating_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType HeatPumpAirToWaterFuelFiredHeating::iddObjectType() {
  return IddObjectType::HeatPump_AirToWater_FuelFired_Heating;
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating::fuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelType);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating::flowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FlowMode);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating::outdoorAirTemperatureCurveInputVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::OutdoorAirTemperatureCurveInputVariable);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating::waterTemperatureCurveInputVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::WaterTemperatureCurveInputVariable);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating::defrostControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DefrostControlType);
}

std::string HeatPumpAirToWaterFuelFiredHeating::fuelType() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->fuelType();
}

bool HeatPumpAirToWaterFuelFiredHeating::setFuelType(const std::string& fuelType) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setFuelType(fuelType);
}

std::string HeatPumpAirToWaterFuelFiredHeating::endUseSubcategory() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->endUseSubcategory();
}

bool HeatPumpAirToWaterFuelFiredHeating::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->isEndUseSubcategoryDefaulted();
}

bool HeatPumpAirToWaterFuelFiredHeating::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void HeatPumpAirToWaterFuelFiredHeating::resetEndUseSubcategory() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetEndUseSubcategory();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating::nominalHeatingCapacity() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->nominalHeatingCapacity();
}

bool HeatPumpAirToWaterFuelFiredHeating::isNominalHeatingCapacityAutosized() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->isNominalHeatingCapacityAutosized();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating::autosizedNominalHeatingCapacity() {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->autosizedNominalHeatingCapacity();
}

bool HeatPumpAirToWaterFuelFiredHeating::setNominalHeatingCapacity(double nominalHeatingCapacity) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setNominalHeatingCapacity(nominalHeatingCapacity);
}

void HeatPumpAirToWaterFuelFiredHeating::resetNominalHeatingCapacity() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetNominalHeatingCapacity();
}

void HeatPumpAirToWaterFuelFiredHeating::autosizeNominalHeatingCapacity() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->autosizeNominalHeatingCapacity();
}

double HeatPumpAirToWaterFuelFiredHeating::nominalCOP() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->nominalCOP();
}

bool HeatPumpAirToWaterFuelFiredHeating::setNominalCOP(double nominalCOP) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setNominalCOP(nominalCOP);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating::designFlowRate() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->designFlowRate();
}

bool HeatPumpAirToWaterFuelFiredHeating::isDesignFlowRateAutosized() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->isDesignFlowRateAutosized();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating::autosizedDesignFlowRate() {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->autosizedDesignFlowRate();
}

bool HeatPumpAirToWaterFuelFiredHeating::setDesignFlowRate(double designFlowRate) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setDesignFlowRate(designFlowRate);
}

void HeatPumpAirToWaterFuelFiredHeating::resetDesignFlowRate() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetDesignFlowRate();
}

void HeatPumpAirToWaterFuelFiredHeating::autosizeDesignFlowRate() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->autosizeDesignFlowRate();
}

double HeatPumpAirToWaterFuelFiredHeating::designSupplyTemperature() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->designSupplyTemperature();
}

bool HeatPumpAirToWaterFuelFiredHeating::setDesignSupplyTemperature(double designSupplyTemperature) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setDesignSupplyTemperature(designSupplyTemperature);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating::designTemperatureLift() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->designTemperatureLift();
}

bool HeatPumpAirToWaterFuelFiredHeating::isDesignTemperatureLiftAutosized() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->isDesignTemperatureLiftAutosized();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating::autosizedDesignTemperatureLift() {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->autosizedDesignTemperatureLift();
}

bool HeatPumpAirToWaterFuelFiredHeating::setDesignTemperatureLift(double designTemperatureLift) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setDesignTemperatureLift(designTemperatureLift);
}

void HeatPumpAirToWaterFuelFiredHeating::autosizeDesignTemperatureLift() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->autosizeDesignTemperatureLift();
}

double HeatPumpAirToWaterFuelFiredHeating::sizingFactor() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->sizingFactor();
}

bool HeatPumpAirToWaterFuelFiredHeating::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setSizingFactor(sizingFactor);
}

std::string HeatPumpAirToWaterFuelFiredHeating::flowMode() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->flowMode();
}

bool HeatPumpAirToWaterFuelFiredHeating::setFlowMode(const std::string& flowMode) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setFlowMode(flowMode);
}

std::string HeatPumpAirToWaterFuelFiredHeating::outdoorAirTemperatureCurveInputVariable() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->outdoorAirTemperatureCurveInputVariable();
}

bool HeatPumpAirToWaterFuelFiredHeating::setOutdoorAirTemperatureCurveInputVariable(const std::string& outdoorAirTemperatureCurveInputVariable) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setOutdoorAirTemperatureCurveInputVariable(
    outdoorAirTemperatureCurveInputVariable);
}

std::string HeatPumpAirToWaterFuelFiredHeating::waterTemperatureCurveInputVariable() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->waterTemperatureCurveInputVariable();
}

bool HeatPumpAirToWaterFuelFiredHeating::setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setWaterTemperatureCurveInputVariable(waterTemperatureCurveInputVariable);
}

double HeatPumpAirToWaterFuelFiredHeating::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->minimumPartLoadRatio();
}

bool HeatPumpAirToWaterFuelFiredHeating::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double HeatPumpAirToWaterFuelFiredHeating::maximumPartLoadRatio() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->maximumPartLoadRatio();
}

bool HeatPumpAirToWaterFuelFiredHeating::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

std::string HeatPumpAirToWaterFuelFiredHeating::defrostControlType() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->defrostControlType();
}

bool HeatPumpAirToWaterFuelFiredHeating::setDefrostControlType(const std::string& defrostControlType) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setDefrostControlType(defrostControlType);
}

double HeatPumpAirToWaterFuelFiredHeating::defrostOperationTimeFraction() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->defrostOperationTimeFraction();
}

bool HeatPumpAirToWaterFuelFiredHeating::setDefrostOperationTimeFraction(double defrostOperationTimeFraction) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setDefrostOperationTimeFraction(defrostOperationTimeFraction);
}

double HeatPumpAirToWaterFuelFiredHeating::resistiveDefrostHeaterCapacity() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resistiveDefrostHeaterCapacity();
}

bool HeatPumpAirToWaterFuelFiredHeating::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity);
}

double HeatPumpAirToWaterFuelFiredHeating::maximumOutdoorDrybulbTemperatureforDefrostOperation() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->maximumOutdoorDrybulbTemperatureforDefrostOperation();
}

bool HeatPumpAirToWaterFuelFiredHeating::setMaximumOutdoorDrybulbTemperatureforDefrostOperation(
  double maximumOutdoorDrybulbTemperatureforDefrostOperation) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setMaximumOutdoorDrybulbTemperatureforDefrostOperation(
    maximumOutdoorDrybulbTemperatureforDefrostOperation);
}

double HeatPumpAirToWaterFuelFiredHeating::nominalAuxiliaryElectricPower() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->nominalAuxiliaryElectricPower();
}

bool HeatPumpAirToWaterFuelFiredHeating::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setNominalAuxiliaryElectricPower(nominalAuxiliaryElectricPower);
}

double HeatPumpAirToWaterFuelFiredHeating::standbyElectricPower() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->standbyElectricPower();
}

bool HeatPumpAirToWaterFuelFiredHeating::setStandbyElectricPower(double standbyElectricPower) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setStandbyElectricPower(standbyElectricPower);
}

double HeatPumpAirToWaterFuelFiredHeating::minimumUnloadingRatio() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->minimumUnloadingRatio();
}

bool HeatPumpAirToWaterFuelFiredHeating::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setMinimumUnloadingRatio(minimumUnloadingRatio);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned HeatPumpAirToWaterFuelFiredHeating_Impl::inletPort() const {
  return openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::WaterInletNodeName;
}

unsigned HeatPumpAirToWaterFuelFiredHeating_Impl::outletPort() const {
  return openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::WaterOutletNodeName;
}

std::string HeatPumpAirToWaterFuelFiredHeating_Impl::fuelType() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelType, fuelType);
}

std::string HeatPumpAirToWaterFuelFiredHeating_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::EndUseSubcategory);
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWaterFuelFiredHeating_Impl::resetEndUseSubcategory() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::EndUseSubcategory, "");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating_Impl::nominalHeatingCapacity() const {
  return getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalHeatingCapacity, true);
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::isNominalHeatingCapacityAutosized() const {
  if (auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalHeatingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating_Impl::autosizedNominalHeatingCapacity() {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setNominalHeatingCapacity(double nominalHeatingCapacity) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalHeatingCapacity, nominalHeatingCapacity);
}

void HeatPumpAirToWaterFuelFiredHeating_Impl::resetNominalHeatingCapacity() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalHeatingCapacity, "");
  OS_ASSERT(result);
}

void HeatPumpAirToWaterFuelFiredHeating_Impl::autosizeNominalHeatingCapacity() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalHeatingCapacity, "autosize");
  OS_ASSERT(result);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::nominalCOP() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setNominalCOP(double nominalCOP) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalCOP, nominalCOP);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating_Impl::designFlowRate() const {
  return getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignFlowRate, true);
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::isDesignFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating_Impl::autosizedDesignFlowRate() {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setDesignFlowRate(double designFlowRate) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignFlowRate, designFlowRate);
}

void HeatPumpAirToWaterFuelFiredHeating_Impl::resetDesignFlowRate() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignFlowRate, "");
  OS_ASSERT(result);
}

void HeatPumpAirToWaterFuelFiredHeating_Impl::autosizeDesignFlowRate() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignFlowRate, "autosize");
  OS_ASSERT(result);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::designSupplyTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignSupplyTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setDesignSupplyTemperature(double designSupplyTemperature) {
  const bool result = setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignSupplyTemperature, designSupplyTemperature);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating_Impl::designTemperatureLift() const {
  return getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignTemperatureLift, true);
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::isDesignTemperatureLiftAutosized() const {
  if (auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignTemperatureLift, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredHeating_Impl::autosizedDesignTemperatureLift() {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setDesignTemperatureLift(double designTemperatureLift) {
  const bool result = setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignTemperatureLift, designTemperatureLift);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWaterFuelFiredHeating_Impl::autosizeDesignTemperatureLift() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DesignTemperatureLift, "autosize");
  OS_ASSERT(result);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::SizingFactor, sizingFactor);
}

std::string HeatPumpAirToWaterFuelFiredHeating_Impl::flowMode() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setFlowMode(const std::string& flowMode) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FlowMode, flowMode);
}

std::string HeatPumpAirToWaterFuelFiredHeating_Impl::outdoorAirTemperatureCurveInputVariable() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::OutdoorAirTemperatureCurveInputVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setOutdoorAirTemperatureCurveInputVariable(
  const std::string& outdoorAirTemperatureCurveInputVariable) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::OutdoorAirTemperatureCurveInputVariable,
                   outdoorAirTemperatureCurveInputVariable);
}

std::string HeatPumpAirToWaterFuelFiredHeating_Impl::waterTemperatureCurveInputVariable() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::WaterTemperatureCurveInputVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::WaterTemperatureCurveInputVariable,
                   waterTemperatureCurveInputVariable);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

std::string HeatPumpAirToWaterFuelFiredHeating_Impl::defrostControlType() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DefrostControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setDefrostControlType(const std::string& defrostControlType) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DefrostControlType, defrostControlType);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::defrostOperationTimeFraction() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DefrostOperationTimeFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setDefrostOperationTimeFraction(double defrostOperationTimeFraction) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::DefrostOperationTimeFraction, defrostOperationTimeFraction);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::resistiveDefrostHeaterCapacity() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::ResistiveDefrostHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::maximumOutdoorDrybulbTemperatureforDefrostOperation() const {
  const auto value =
    getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setMaximumOutdoorDrybulbTemperatureforDefrostOperation(
  double maximumOutdoorDrybulbTemperatureforDefrostOperation) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation,
                   maximumOutdoorDrybulbTemperatureforDefrostOperation);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::nominalAuxiliaryElectricPower() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalAuxiliaryElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalAuxiliaryElectricPower, nominalAuxiliaryElectricPower);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::standbyElectricPower() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::StandbyElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setStandbyElectricPower(double standbyElectricPower) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::StandbyElectricPower, standbyElectricPower);
}

double HeatPumpAirToWaterFuelFiredHeating_Impl::minimumUnloadingRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MinimumUnloadingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredHeating_Impl::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::MinimumUnloadingRatio, minimumUnloadingRatio);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating_Impl::fuelTypeValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredHeating::fuelTypeValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating_Impl::flowModeValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredHeating::flowModeValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating_Impl::outdoorAirTemperatureCurveInputVariableValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredHeating::outdoorAirTemperatureCurveInputVariableValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating_Impl::waterTemperatureCurveInputVariableValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredHeating::waterTemperatureCurveInputVariableValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredHeating_Impl::defrostControlTypeValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredHeating::defrostControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
