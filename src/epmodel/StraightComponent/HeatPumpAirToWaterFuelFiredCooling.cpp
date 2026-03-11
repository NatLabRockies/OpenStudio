/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_AirToWater_FuelFired_Cooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HeatPumpAirToWaterFuelFiredCooling::HeatPumpAirToWaterFuelFiredCooling(const Model& model)
  : StraightComponent(HeatPumpAirToWaterFuelFiredCooling::iddObjectType(), model) {
  // Mirror model default scalar behavior while excluding relationship/object fields.
  bool ok = true;
  ok &= setFuelType("NaturalGas");
  autosizeNominalCoolingCapacity();
  ok &= setNominalCOP(1.0);
  autosizeDesignFlowRate();
  ok &= setDesignSupplyTemperature(7.0);
  ok &= setDesignTemperatureLift(11.1);
  ok &= setSizingFactor(1.0);
  ok &= setFlowMode("NotModulated");
  ok &= setOutdoorAirTemperatureCurveInputVariable("DryBulb");
  ok &= setWaterTemperatureCurveInputVariable("EnteringEvaporator");
  ok &= setMinimumPartLoadRatio(0.1);
  ok &= setMaximumPartLoadRatio(1.0);
  ok &= setNominalAuxiliaryElectricPower(0.0);
  ok &= setStandbyElectricPower(0.0);
  ok &= setMinimumUnloadingRatio(0.25);
  OS_ASSERT(ok);
}

HeatPumpAirToWaterFuelFiredCooling::HeatPumpAirToWaterFuelFiredCooling(
  std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredCooling_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType HeatPumpAirToWaterFuelFiredCooling::iddObjectType() {
  return IddObjectType::HeatPump_AirToWater_FuelFired_Cooling;
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling::fuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelType);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling::flowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FlowMode);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling::outdoorAirTemperatureCurveInputVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::OutdoorAirTemperatureCurveInputVariable);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling::waterTemperatureCurveInputVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterTemperatureCurveInputVariable);
}

std::string HeatPumpAirToWaterFuelFiredCooling::fuelType() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->fuelType();
}

bool HeatPumpAirToWaterFuelFiredCooling::setFuelType(const std::string& fuelType) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setFuelType(fuelType);
}

std::string HeatPumpAirToWaterFuelFiredCooling::endUseSubcategory() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->endUseSubcategory();
}

bool HeatPumpAirToWaterFuelFiredCooling::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->isEndUseSubcategoryDefaulted();
}

bool HeatPumpAirToWaterFuelFiredCooling::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void HeatPumpAirToWaterFuelFiredCooling::resetEndUseSubcategory() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetEndUseSubcategory();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling::nominalCoolingCapacity() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->nominalCoolingCapacity();
}

bool HeatPumpAirToWaterFuelFiredCooling::isNominalCoolingCapacityAutosized() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->isNominalCoolingCapacityAutosized();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling::autosizedNominalCoolingCapacity() {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->autosizedNominalCoolingCapacity();
}

bool HeatPumpAirToWaterFuelFiredCooling::setNominalCoolingCapacity(double nominalCoolingCapacity) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setNominalCoolingCapacity(nominalCoolingCapacity);
}

void HeatPumpAirToWaterFuelFiredCooling::resetNominalCoolingCapacity() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetNominalCoolingCapacity();
}

void HeatPumpAirToWaterFuelFiredCooling::autosizeNominalCoolingCapacity() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->autosizeNominalCoolingCapacity();
}

double HeatPumpAirToWaterFuelFiredCooling::nominalCOP() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->nominalCOP();
}

bool HeatPumpAirToWaterFuelFiredCooling::setNominalCOP(double nominalCOP) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setNominalCOP(nominalCOP);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling::designFlowRate() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->designFlowRate();
}

bool HeatPumpAirToWaterFuelFiredCooling::isDesignFlowRateAutosized() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->isDesignFlowRateAutosized();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling::autosizedDesignFlowRate() {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->autosizedDesignFlowRate();
}

bool HeatPumpAirToWaterFuelFiredCooling::setDesignFlowRate(double designFlowRate) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setDesignFlowRate(designFlowRate);
}

void HeatPumpAirToWaterFuelFiredCooling::resetDesignFlowRate() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetDesignFlowRate();
}

void HeatPumpAirToWaterFuelFiredCooling::autosizeDesignFlowRate() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->autosizeDesignFlowRate();
}

double HeatPumpAirToWaterFuelFiredCooling::designSupplyTemperature() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->designSupplyTemperature();
}

bool HeatPumpAirToWaterFuelFiredCooling::setDesignSupplyTemperature(double designSupplyTemperature) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setDesignSupplyTemperature(designSupplyTemperature);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling::designTemperatureLift() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->designTemperatureLift();
}

bool HeatPumpAirToWaterFuelFiredCooling::isDesignTemperatureLiftAutosized() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->isDesignTemperatureLiftAutosized();
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling::autosizedDesignTemperatureLift() {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->autosizedDesignTemperatureLift();
}

bool HeatPumpAirToWaterFuelFiredCooling::setDesignTemperatureLift(double designTemperatureLift) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setDesignTemperatureLift(designTemperatureLift);
}

void HeatPumpAirToWaterFuelFiredCooling::autosizeDesignTemperatureLift() {
  getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->autosizeDesignTemperatureLift();
}

double HeatPumpAirToWaterFuelFiredCooling::sizingFactor() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->sizingFactor();
}

bool HeatPumpAirToWaterFuelFiredCooling::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setSizingFactor(sizingFactor);
}

std::string HeatPumpAirToWaterFuelFiredCooling::flowMode() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->flowMode();
}

bool HeatPumpAirToWaterFuelFiredCooling::setFlowMode(const std::string& flowMode) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setFlowMode(flowMode);
}

std::string HeatPumpAirToWaterFuelFiredCooling::outdoorAirTemperatureCurveInputVariable() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->outdoorAirTemperatureCurveInputVariable();
}

bool HeatPumpAirToWaterFuelFiredCooling::setOutdoorAirTemperatureCurveInputVariable(const std::string& outdoorAirTemperatureCurveInputVariable) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setOutdoorAirTemperatureCurveInputVariable(
    outdoorAirTemperatureCurveInputVariable);
}

std::string HeatPumpAirToWaterFuelFiredCooling::waterTemperatureCurveInputVariable() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->waterTemperatureCurveInputVariable();
}

bool HeatPumpAirToWaterFuelFiredCooling::setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setWaterTemperatureCurveInputVariable(waterTemperatureCurveInputVariable);
}

double HeatPumpAirToWaterFuelFiredCooling::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->minimumPartLoadRatio();
}

bool HeatPumpAirToWaterFuelFiredCooling::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double HeatPumpAirToWaterFuelFiredCooling::maximumPartLoadRatio() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->maximumPartLoadRatio();
}

bool HeatPumpAirToWaterFuelFiredCooling::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

double HeatPumpAirToWaterFuelFiredCooling::nominalAuxiliaryElectricPower() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->nominalAuxiliaryElectricPower();
}

bool HeatPumpAirToWaterFuelFiredCooling::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setNominalAuxiliaryElectricPower(nominalAuxiliaryElectricPower);
}

double HeatPumpAirToWaterFuelFiredCooling::standbyElectricPower() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->standbyElectricPower();
}

bool HeatPumpAirToWaterFuelFiredCooling::setStandbyElectricPower(double standbyElectricPower) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setStandbyElectricPower(standbyElectricPower);
}

double HeatPumpAirToWaterFuelFiredCooling::minimumUnloadingRatio() const {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->minimumUnloadingRatio();
}

bool HeatPumpAirToWaterFuelFiredCooling::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setMinimumUnloadingRatio(minimumUnloadingRatio);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned HeatPumpAirToWaterFuelFiredCooling_Impl::inletPort() const {
  // OutdoorAir:Node inventory selection maps here to the owning HeatPump object's required water node field.
  return openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterInletNodeName;
}

unsigned HeatPumpAirToWaterFuelFiredCooling_Impl::outletPort() const {
  // OutdoorAir:Node inventory selection maps here to the owning HeatPump object's required water node field.
  return openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterOutletNodeName;
}

std::string HeatPumpAirToWaterFuelFiredCooling_Impl::fuelType() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelType, fuelType);
}

std::string HeatPumpAirToWaterFuelFiredCooling_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::EndUseSubcategory);
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWaterFuelFiredCooling_Impl::resetEndUseSubcategory() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::EndUseSubcategory, "");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling_Impl::nominalCoolingCapacity() const {
  return getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCoolingCapacity, true);
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::isNominalCoolingCapacityAutosized() const {
  if (auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling_Impl::autosizedNominalCoolingCapacity() {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setNominalCoolingCapacity(double nominalCoolingCapacity) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCoolingCapacity, nominalCoolingCapacity);
}

void HeatPumpAirToWaterFuelFiredCooling_Impl::resetNominalCoolingCapacity() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCoolingCapacity, "");
  OS_ASSERT(result);
}

void HeatPumpAirToWaterFuelFiredCooling_Impl::autosizeNominalCoolingCapacity() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCoolingCapacity, "autosize");
  OS_ASSERT(result);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::nominalCOP() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setNominalCOP(double nominalCOP) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalCOP, nominalCOP);
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling_Impl::designFlowRate() const {
  return getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignFlowRate, true);
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::isDesignFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling_Impl::autosizedDesignFlowRate() {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setDesignFlowRate(double designFlowRate) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignFlowRate, designFlowRate);
}

void HeatPumpAirToWaterFuelFiredCooling_Impl::resetDesignFlowRate() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignFlowRate, "");
  OS_ASSERT(result);
}

void HeatPumpAirToWaterFuelFiredCooling_Impl::autosizeDesignFlowRate() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignFlowRate, "autosize");
  OS_ASSERT(result);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::designSupplyTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignSupplyTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setDesignSupplyTemperature(double designSupplyTemperature) {
  const bool result = setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignSupplyTemperature, designSupplyTemperature);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling_Impl::designTemperatureLift() const {
  return getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignTemperatureLift, true);
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::isDesignTemperatureLiftAutosized() const {
  if (auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignTemperatureLift, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> HeatPumpAirToWaterFuelFiredCooling_Impl::autosizedDesignTemperatureLift() {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setDesignTemperatureLift(double designTemperatureLift) {
  const bool result = setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignTemperatureLift, designTemperatureLift);
  OS_ASSERT(result);
  return result;
}

void HeatPumpAirToWaterFuelFiredCooling_Impl::autosizeDesignTemperatureLift() {
  const bool result = setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::DesignTemperatureLift, "autosize");
  OS_ASSERT(result);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::SizingFactor, sizingFactor);
}

std::string HeatPumpAirToWaterFuelFiredCooling_Impl::flowMode() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setFlowMode(const std::string& flowMode) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FlowMode, flowMode);
}

std::string HeatPumpAirToWaterFuelFiredCooling_Impl::outdoorAirTemperatureCurveInputVariable() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::OutdoorAirTemperatureCurveInputVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setOutdoorAirTemperatureCurveInputVariable(
  const std::string& outdoorAirTemperatureCurveInputVariable) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::OutdoorAirTemperatureCurveInputVariable,
                   outdoorAirTemperatureCurveInputVariable);
}

std::string HeatPumpAirToWaterFuelFiredCooling_Impl::waterTemperatureCurveInputVariable() const {
  const auto value = getString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterTemperatureCurveInputVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable) {
  return setString(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterTemperatureCurveInputVariable,
                   waterTemperatureCurveInputVariable);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::nominalAuxiliaryElectricPower() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalAuxiliaryElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalAuxiliaryElectricPower, nominalAuxiliaryElectricPower);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::standbyElectricPower() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::StandbyElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setStandbyElectricPower(double standbyElectricPower) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::StandbyElectricPower, standbyElectricPower);
}

double HeatPumpAirToWaterFuelFiredCooling_Impl::minimumUnloadingRatio() const {
  const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::MinimumUnloadingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpAirToWaterFuelFiredCooling_Impl::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::MinimumUnloadingRatio, minimumUnloadingRatio);
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling_Impl::fuelTypeValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredCooling::fuelTypeValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling_Impl::flowModeValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredCooling::flowModeValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling_Impl::outdoorAirTemperatureCurveInputVariableValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredCooling::outdoorAirTemperatureCurveInputVariableValues();
}

std::vector<std::string> HeatPumpAirToWaterFuelFiredCooling_Impl::waterTemperatureCurveInputVariableValues() const {
  return openstudio::epmodel::HeatPumpAirToWaterFuelFiredCooling::waterTemperatureCurveInputVariableValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
