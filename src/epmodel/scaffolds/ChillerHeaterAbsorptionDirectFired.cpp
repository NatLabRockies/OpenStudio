/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ChillerHeaterAbsorptionDirectFired.hpp"
#include "ChillerHeaterAbsorptionDirectFired_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ChillerHeater_Absorption_DirectFired_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerHeaterAbsorptionDirectFired::ChillerHeaterAbsorptionDirectFired(const Model& model) : ModelObject(ChillerHeaterAbsorptionDirectFired::iddObjectType(), model) {}

ChillerHeaterAbsorptionDirectFired::ChillerHeaterAbsorptionDirectFired(std::shared_ptr<detail::ChillerHeaterAbsorptionDirectFired_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ChillerHeaterAbsorptionDirectFired::iddObjectType() {
  return IddObjectType::ChillerHeater_Absorption_DirectFired;
}

std::vector<std::string> ChillerHeaterAbsorptionDirectFired::temperatureCurveInputVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ChillerHeater_Absorption_DirectFiredFields::TemperatureCurveInputVariable);
}

std::vector<std::string> ChillerHeaterAbsorptionDirectFired::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ChillerHeater_Absorption_DirectFiredFields::CondenserType);
}

std::vector<std::string> ChillerHeaterAbsorptionDirectFired::fuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelType);
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired::nominalCoolingCapacity() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->nominalCoolingCapacity();
}

bool ChillerHeaterAbsorptionDirectFired::isNominalCoolingCapacityDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isNominalCoolingCapacityDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::isNominalCoolingCapacityAutosized() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isNominalCoolingCapacityAutosized();
}

bool ChillerHeaterAbsorptionDirectFired::setNominalCoolingCapacity(double nominalCoolingCapacity) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setNominalCoolingCapacity(nominalCoolingCapacity);
}

void ChillerHeaterAbsorptionDirectFired::resetNominalCoolingCapacity() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetNominalCoolingCapacity();
}

void ChillerHeaterAbsorptionDirectFired::autosizeNominalCoolingCapacity() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->autosizeNominalCoolingCapacity();
}

double ChillerHeaterAbsorptionDirectFired::heatingtoCoolingCapacityRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->heatingtoCoolingCapacityRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isHeatingtoCoolingCapacityRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isHeatingtoCoolingCapacityRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setHeatingtoCoolingCapacityRatio(double heatingtoCoolingCapacityRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setHeatingtoCoolingCapacityRatio(heatingtoCoolingCapacityRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetHeatingtoCoolingCapacityRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetHeatingtoCoolingCapacityRatio();
}

double ChillerHeaterAbsorptionDirectFired::fuelInputtoCoolingOutputRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->fuelInputtoCoolingOutputRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isFuelInputtoCoolingOutputRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isFuelInputtoCoolingOutputRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setFuelInputtoCoolingOutputRatio(double fuelInputtoCoolingOutputRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setFuelInputtoCoolingOutputRatio(fuelInputtoCoolingOutputRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetFuelInputtoCoolingOutputRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetFuelInputtoCoolingOutputRatio();
}

double ChillerHeaterAbsorptionDirectFired::fuelInputtoHeatingOutputRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->fuelInputtoHeatingOutputRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isFuelInputtoHeatingOutputRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isFuelInputtoHeatingOutputRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setFuelInputtoHeatingOutputRatio(double fuelInputtoHeatingOutputRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setFuelInputtoHeatingOutputRatio(fuelInputtoHeatingOutputRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetFuelInputtoHeatingOutputRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetFuelInputtoHeatingOutputRatio();
}

double ChillerHeaterAbsorptionDirectFired::electricInputtoCoolingOutputRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->electricInputtoCoolingOutputRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isElectricInputtoCoolingOutputRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isElectricInputtoCoolingOutputRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setElectricInputtoCoolingOutputRatio(double electricInputtoCoolingOutputRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setElectricInputtoCoolingOutputRatio(electricInputtoCoolingOutputRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetElectricInputtoCoolingOutputRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetElectricInputtoCoolingOutputRatio();
}

double ChillerHeaterAbsorptionDirectFired::electricInputtoHeatingOutputRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->electricInputtoHeatingOutputRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isElectricInputtoHeatingOutputRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isElectricInputtoHeatingOutputRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setElectricInputtoHeatingOutputRatio(double electricInputtoHeatingOutputRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setElectricInputtoHeatingOutputRatio(electricInputtoHeatingOutputRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetElectricInputtoHeatingOutputRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetElectricInputtoHeatingOutputRatio();
}

double ChillerHeaterAbsorptionDirectFired::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->minimumPartLoadRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isMinimumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isMinimumPartLoadRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetMinimumPartLoadRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetMinimumPartLoadRatio();
}

double ChillerHeaterAbsorptionDirectFired::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->maximumPartLoadRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isMaximumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isMaximumPartLoadRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetMaximumPartLoadRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetMaximumPartLoadRatio();
}

double ChillerHeaterAbsorptionDirectFired::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->optimumPartLoadRatio();
}

bool ChillerHeaterAbsorptionDirectFired::isOptimumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isOptimumPartLoadRatioDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

void ChillerHeaterAbsorptionDirectFired::resetOptimumPartLoadRatio() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetOptimumPartLoadRatio();
}

double ChillerHeaterAbsorptionDirectFired::designEnteringCondenserWaterTemperature() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->designEnteringCondenserWaterTemperature();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignEnteringCondenserWaterTemperatureDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignEnteringCondenserWaterTemperatureDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setDesignEnteringCondenserWaterTemperature(double designEnteringCondenserWaterTemperature) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setDesignEnteringCondenserWaterTemperature(designEnteringCondenserWaterTemperature);
}

void ChillerHeaterAbsorptionDirectFired::resetDesignEnteringCondenserWaterTemperature() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetDesignEnteringCondenserWaterTemperature();
}

double ChillerHeaterAbsorptionDirectFired::designLeavingChilledWaterTemperature() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->designLeavingChilledWaterTemperature();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignLeavingChilledWaterTemperatureDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignLeavingChilledWaterTemperatureDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setDesignLeavingChilledWaterTemperature(double designLeavingChilledWaterTemperature) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setDesignLeavingChilledWaterTemperature(designLeavingChilledWaterTemperature);
}

void ChillerHeaterAbsorptionDirectFired::resetDesignLeavingChilledWaterTemperature() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetDesignLeavingChilledWaterTemperature();
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired::designChilledWaterFlowRate() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->designChilledWaterFlowRate();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignChilledWaterFlowRateDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignChilledWaterFlowRateDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignChilledWaterFlowRateAutosized();
}

bool ChillerHeaterAbsorptionDirectFired::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
}

void ChillerHeaterAbsorptionDirectFired::resetDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetDesignChilledWaterFlowRate();
}

void ChillerHeaterAbsorptionDirectFired::autosizeDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->autosizeDesignChilledWaterFlowRate();
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired::designCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->designCondenserWaterFlowRate();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignCondenserWaterFlowRateDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignCondenserWaterFlowRateDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignCondenserWaterFlowRateAutosized();
}

bool ChillerHeaterAbsorptionDirectFired::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
}

void ChillerHeaterAbsorptionDirectFired::resetDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetDesignCondenserWaterFlowRate();
}

void ChillerHeaterAbsorptionDirectFired::autosizeDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->autosizeDesignCondenserWaterFlowRate();
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired::designHotWaterFlowRate() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->designHotWaterFlowRate();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignHotWaterFlowRateDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignHotWaterFlowRateDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::isDesignHotWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isDesignHotWaterFlowRateAutosized();
}

bool ChillerHeaterAbsorptionDirectFired::setDesignHotWaterFlowRate(double designHotWaterFlowRate) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setDesignHotWaterFlowRate(designHotWaterFlowRate);
}

void ChillerHeaterAbsorptionDirectFired::resetDesignHotWaterFlowRate() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetDesignHotWaterFlowRate();
}

void ChillerHeaterAbsorptionDirectFired::autosizeDesignHotWaterFlowRate() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->autosizeDesignHotWaterFlowRate();
}

std::string ChillerHeaterAbsorptionDirectFired::temperatureCurveInputVariable() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->temperatureCurveInputVariable();
}

bool ChillerHeaterAbsorptionDirectFired::isTemperatureCurveInputVariableDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isTemperatureCurveInputVariableDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setTemperatureCurveInputVariable(const std::string& temperatureCurveInputVariable) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setTemperatureCurveInputVariable(temperatureCurveInputVariable);
}

void ChillerHeaterAbsorptionDirectFired::resetTemperatureCurveInputVariable() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetTemperatureCurveInputVariable();
}

std::string ChillerHeaterAbsorptionDirectFired::condenserType() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->condenserType();
}

bool ChillerHeaterAbsorptionDirectFired::isCondenserTypeDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isCondenserTypeDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setCondenserType(condenserType);
}

void ChillerHeaterAbsorptionDirectFired::resetCondenserType() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetCondenserType();
}

double ChillerHeaterAbsorptionDirectFired::chilledWaterTemperatureLowerLimit() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->chilledWaterTemperatureLowerLimit();
}

bool ChillerHeaterAbsorptionDirectFired::isChilledWaterTemperatureLowerLimitDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isChilledWaterTemperatureLowerLimitDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setChilledWaterTemperatureLowerLimit(double chilledWaterTemperatureLowerLimit) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setChilledWaterTemperatureLowerLimit(chilledWaterTemperatureLowerLimit);
}

void ChillerHeaterAbsorptionDirectFired::resetChilledWaterTemperatureLowerLimit() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetChilledWaterTemperatureLowerLimit();
}

double ChillerHeaterAbsorptionDirectFired::fuelHigherHeatingValue() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->fuelHigherHeatingValue();
}

bool ChillerHeaterAbsorptionDirectFired::isFuelHigherHeatingValueDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isFuelHigherHeatingValueDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setFuelHigherHeatingValue(fuelHigherHeatingValue);
}

void ChillerHeaterAbsorptionDirectFired::resetFuelHigherHeatingValue() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetFuelHigherHeatingValue();
}

std::string ChillerHeaterAbsorptionDirectFired::fuelType() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->fuelType();
}

bool ChillerHeaterAbsorptionDirectFired::isFuelTypeDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isFuelTypeDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setFuelType(const std::string& fuelType) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setFuelType(fuelType);
}

void ChillerHeaterAbsorptionDirectFired::resetFuelType() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetFuelType();
}

double ChillerHeaterAbsorptionDirectFired::sizingFactor() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->sizingFactor();
}

bool ChillerHeaterAbsorptionDirectFired::isSizingFactorDefaulted() const {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->isSizingFactorDefaulted();
}

bool ChillerHeaterAbsorptionDirectFired::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->setSizingFactor(sizingFactor);
}

void ChillerHeaterAbsorptionDirectFired::resetSizingFactor() {
  getImpl<detail::ChillerHeaterAbsorptionDirectFired_Impl>()->resetSizingFactor();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ChillerHeaterAbsorptionDirectFired_Impl::nominalCoolingCapacity() const {
  return getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::NominalCoolingCapacity, true);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isNominalCoolingCapacityDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::NominalCoolingCapacity);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isNominalCoolingCapacityAutosized() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::NominalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setNominalCoolingCapacity(double nominalCoolingCapacity) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::NominalCoolingCapacity, nominalCoolingCapacity);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetNominalCoolingCapacity() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::NominalCoolingCapacity, "");
  OS_ASSERT(result);
}

void ChillerHeaterAbsorptionDirectFired_Impl::autosizeNominalCoolingCapacity() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::NominalCoolingCapacity, "autosize");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::heatingtoCoolingCapacityRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::HeatingtoCoolingCapacityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isHeatingtoCoolingCapacityRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::HeatingtoCoolingCapacityRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setHeatingtoCoolingCapacityRatio(double heatingtoCoolingCapacityRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::HeatingtoCoolingCapacityRatio, heatingtoCoolingCapacityRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetHeatingtoCoolingCapacityRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::HeatingtoCoolingCapacityRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::fuelInputtoCoolingOutputRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoCoolingOutputRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isFuelInputtoCoolingOutputRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoCoolingOutputRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setFuelInputtoCoolingOutputRatio(double fuelInputtoCoolingOutputRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoCoolingOutputRatio, fuelInputtoCoolingOutputRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetFuelInputtoCoolingOutputRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoCoolingOutputRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::fuelInputtoHeatingOutputRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoHeatingOutputRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isFuelInputtoHeatingOutputRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoHeatingOutputRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setFuelInputtoHeatingOutputRatio(double fuelInputtoHeatingOutputRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoHeatingOutputRatio, fuelInputtoHeatingOutputRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetFuelInputtoHeatingOutputRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelInputtoHeatingOutputRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::electricInputtoCoolingOutputRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoCoolingOutputRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isElectricInputtoCoolingOutputRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoCoolingOutputRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setElectricInputtoCoolingOutputRatio(double electricInputtoCoolingOutputRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoCoolingOutputRatio, electricInputtoCoolingOutputRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetElectricInputtoCoolingOutputRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoCoolingOutputRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::electricInputtoHeatingOutputRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoHeatingOutputRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isElectricInputtoHeatingOutputRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoHeatingOutputRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setElectricInputtoHeatingOutputRatio(double electricInputtoHeatingOutputRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoHeatingOutputRatio, electricInputtoHeatingOutputRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetElectricInputtoHeatingOutputRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::ElectricInputtoHeatingOutputRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isMinimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::MinimumPartLoadRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::MinimumPartLoadRatio, minimumPartLoadRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetMinimumPartLoadRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::MinimumPartLoadRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isMaximumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::MaximumPartLoadRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::MaximumPartLoadRatio, maximumPartLoadRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetMaximumPartLoadRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::MaximumPartLoadRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::optimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::OptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isOptimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::OptimumPartLoadRatio);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::OptimumPartLoadRatio, optimumPartLoadRatio);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetOptimumPartLoadRatio() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::OptimumPartLoadRatio, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::designEnteringCondenserWaterTemperature() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignEnteringCondenserWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignEnteringCondenserWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignEnteringCondenserWaterTemperature);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setDesignEnteringCondenserWaterTemperature(double designEnteringCondenserWaterTemperature) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignEnteringCondenserWaterTemperature, designEnteringCondenserWaterTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetDesignEnteringCondenserWaterTemperature() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignEnteringCondenserWaterTemperature, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::designLeavingChilledWaterTemperature() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignLeavingChilledWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignLeavingChilledWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignLeavingChilledWaterTemperature);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setDesignLeavingChilledWaterTemperature(double designLeavingChilledWaterTemperature) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignLeavingChilledWaterTemperature, designLeavingChilledWaterTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetDesignLeavingChilledWaterTemperature() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignLeavingChilledWaterTemperature, "");
  OS_ASSERT(result);
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired_Impl::designChilledWaterFlowRate() const {
  return getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignChilledWaterFlowRate, true);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignChilledWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignChilledWaterFlowRate);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetDesignChilledWaterFlowRate() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignChilledWaterFlowRate, "");
  OS_ASSERT(result);
}

void ChillerHeaterAbsorptionDirectFired_Impl::autosizeDesignChilledWaterFlowRate() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignChilledWaterFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired_Impl::designCondenserWaterFlowRate() const {
  return getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignCondenserWaterFlowRate, true);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignCondenserWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignCondenserWaterFlowRate);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignCondenserWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetDesignCondenserWaterFlowRate() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignCondenserWaterFlowRate, "");
  OS_ASSERT(result);
}

void ChillerHeaterAbsorptionDirectFired_Impl::autosizeDesignCondenserWaterFlowRate() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignCondenserWaterFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> ChillerHeaterAbsorptionDirectFired_Impl::designHotWaterFlowRate() const {
  return getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignHotWaterFlowRate, true);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignHotWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignHotWaterFlowRate);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isDesignHotWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignHotWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setDesignHotWaterFlowRate(double designHotWaterFlowRate) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignHotWaterFlowRate, designHotWaterFlowRate);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetDesignHotWaterFlowRate() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignHotWaterFlowRate, "");
  OS_ASSERT(result);
}

void ChillerHeaterAbsorptionDirectFired_Impl::autosizeDesignHotWaterFlowRate() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::DesignHotWaterFlowRate, "autosize");
  OS_ASSERT(result);
}

std::string ChillerHeaterAbsorptionDirectFired_Impl::temperatureCurveInputVariable() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::TemperatureCurveInputVariable, false)) {
    return *value;
  }
  return "EnteringCondenser";
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isTemperatureCurveInputVariableDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::TemperatureCurveInputVariable);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setTemperatureCurveInputVariable(const std::string& temperatureCurveInputVariable) {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::TemperatureCurveInputVariable, temperatureCurveInputVariable);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetTemperatureCurveInputVariable() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::TemperatureCurveInputVariable, "");
  OS_ASSERT(result);
}

std::string ChillerHeaterAbsorptionDirectFired_Impl::condenserType() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::CondenserType, false)) {
    return *value;
  }
  return "WaterCooled";
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isCondenserTypeDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::CondenserType);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setCondenserType(const std::string& condenserType) {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::CondenserType, condenserType);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetCondenserType() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::CondenserType, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::chilledWaterTemperatureLowerLimit() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::ChilledWaterTemperatureLowerLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isChilledWaterTemperatureLowerLimitDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::ChilledWaterTemperatureLowerLimit);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setChilledWaterTemperatureLowerLimit(double chilledWaterTemperatureLowerLimit) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::ChilledWaterTemperatureLowerLimit, chilledWaterTemperatureLowerLimit);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetChilledWaterTemperatureLowerLimit() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::ChilledWaterTemperatureLowerLimit, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::fuelHigherHeatingValue() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelHigherHeatingValue, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isFuelHigherHeatingValueDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelHigherHeatingValue);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelHigherHeatingValue, fuelHigherHeatingValue);
  OS_ASSERT(result);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetFuelHigherHeatingValue() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelHigherHeatingValue, "");
  OS_ASSERT(result);
}

std::string ChillerHeaterAbsorptionDirectFired_Impl::fuelType() const {
  if (auto value = getString(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelType, false)) {
    return *value;
  }
  return "NaturalGas";
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isFuelTypeDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelType);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setFuelType(const std::string& fuelType) {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelType, fuelType);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetFuelType() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::FuelType, "");
  OS_ASSERT(result);
}

double ChillerHeaterAbsorptionDirectFired_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterAbsorptionDirectFired_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::ChillerHeater_Absorption_DirectFiredFields::SizingFactor);
}

bool ChillerHeaterAbsorptionDirectFired_Impl::setSizingFactor(double sizingFactor) {
  const bool result = setDouble(openstudio::ChillerHeater_Absorption_DirectFiredFields::SizingFactor, sizingFactor);
  return result;
}

void ChillerHeaterAbsorptionDirectFired_Impl::resetSizingFactor() {
  const bool result = setString(openstudio::ChillerHeater_Absorption_DirectFiredFields::SizingFactor, "");
  OS_ASSERT(result);
}

std::vector<std::string> ChillerHeaterAbsorptionDirectFired_Impl::temperatureCurveInputVariableValues() const {
  return openstudio::epmodel::ChillerHeaterAbsorptionDirectFired::temperatureCurveInputVariableValues();
}

std::vector<std::string> ChillerHeaterAbsorptionDirectFired_Impl::condenserTypeValues() const {
  return openstudio::epmodel::ChillerHeaterAbsorptionDirectFired::condenserTypeValues();
}

std::vector<std::string> ChillerHeaterAbsorptionDirectFired_Impl::fuelTypeValues() const {
  return openstudio::epmodel::ChillerHeaterAbsorptionDirectFired::fuelTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
