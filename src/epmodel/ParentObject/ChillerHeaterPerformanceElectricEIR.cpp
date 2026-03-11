/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/ChillerHeaterPerformanceElectricEIR.hpp"
#include "ParentObject/ChillerHeaterPerformanceElectricEIR_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ChillerHeaterPerformance_Electric_EIR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerHeaterPerformanceElectricEIR::ChillerHeaterPerformanceElectricEIR(const Model& model)
  : ParentObject(ChillerHeaterPerformanceElectricEIR::iddObjectType(), model) {}

ChillerHeaterPerformanceElectricEIR::ChillerHeaterPerformanceElectricEIR(
  std::shared_ptr<detail::ChillerHeaterPerformanceElectricEIR_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType ChillerHeaterPerformanceElectricEIR::iddObjectType() {
  return IddObjectType::ChillerHeaterPerformance_Electric_EIR;
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR::chilledWaterFlowModeTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ChillerHeaterPerformance_Electric_EIRFields::ChilledWaterFlowModeType);
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ChillerHeaterPerformance_Electric_EIRFields::CondenserType);
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR::coolingModeTemperatureCurveCondenserWaterIndependentVariableValues() {
  return getIddKeyNames(
    IddFactory::instance().getObject(iddObjectType()).get(),
    openstudio::ChillerHeaterPerformance_Electric_EIRFields::CoolingModeTemperatureCurveCondenserWaterIndependentVariable);
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR::heatingModeTemperatureCurveCondenserWaterIndependentVariableValues() {
  return getIddKeyNames(
    IddFactory::instance().getObject(iddObjectType()).get(),
    openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeTemperatureCurveCondenserWaterIndependentVariable);
}

boost::optional<double> ChillerHeaterPerformanceElectricEIR::referenceCoolingModeEvaporatorCapacity() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceCoolingModeEvaporatorCapacity();
}

bool ChillerHeaterPerformanceElectricEIR::isReferenceCoolingModeEvaporatorCapacityAutosized() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->isReferenceCoolingModeEvaporatorCapacityAutosized();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceCoolingModeEvaporatorCapacity(double referenceCoolingModeEvaporatorCapacity) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceCoolingModeEvaporatorCapacity(
    referenceCoolingModeEvaporatorCapacity);
}

void ChillerHeaterPerformanceElectricEIR::autosizeReferenceCoolingModeEvaporatorCapacity() {
  getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->autosizeReferenceCoolingModeEvaporatorCapacity();
}

double ChillerHeaterPerformanceElectricEIR::referenceCoolingModeCOP() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceCoolingModeCOP();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceCoolingModeCOP(double referenceCoolingModeCOP) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceCoolingModeCOP(referenceCoolingModeCOP);
}

double ChillerHeaterPerformanceElectricEIR::referenceCoolingModeLeavingChilledWaterTemperature() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceCoolingModeLeavingChilledWaterTemperature();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceCoolingModeLeavingChilledWaterTemperature(
  double referenceCoolingModeLeavingChilledWaterTemperature) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceCoolingModeLeavingChilledWaterTemperature(
    referenceCoolingModeLeavingChilledWaterTemperature);
}

double ChillerHeaterPerformanceElectricEIR::referenceCoolingModeEnteringCondenserFluidTemperature() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceCoolingModeEnteringCondenserFluidTemperature();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceCoolingModeEnteringCondenserFluidTemperature(
  double referenceCoolingModeEnteringCondenserFluidTemperature) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceCoolingModeEnteringCondenserFluidTemperature(
    referenceCoolingModeEnteringCondenserFluidTemperature);
}

double ChillerHeaterPerformanceElectricEIR::referenceCoolingModeLeavingCondenserWaterTemperature() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceCoolingModeLeavingCondenserWaterTemperature();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceCoolingModeLeavingCondenserWaterTemperature(
  double referenceCoolingModeLeavingCondenserWaterTemperature) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceCoolingModeLeavingCondenserWaterTemperature(
    referenceCoolingModeLeavingCondenserWaterTemperature);
}

double ChillerHeaterPerformanceElectricEIR::referenceHeatingModeCoolingCapacityRatio() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceHeatingModeCoolingCapacityRatio();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceHeatingModeCoolingCapacityRatio(double referenceHeatingModeCoolingCapacityRatio) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceHeatingModeCoolingCapacityRatio(
    referenceHeatingModeCoolingCapacityRatio);
}

double ChillerHeaterPerformanceElectricEIR::referenceHeatingModeCoolingPowerInputRatio() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceHeatingModeCoolingPowerInputRatio();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceHeatingModeCoolingPowerInputRatio(double referenceHeatingModeCoolingPowerInputRatio) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceHeatingModeCoolingPowerInputRatio(
    referenceHeatingModeCoolingPowerInputRatio);
}

double ChillerHeaterPerformanceElectricEIR::referenceHeatingModeLeavingChilledWaterTemperature() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceHeatingModeLeavingChilledWaterTemperature();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceHeatingModeLeavingChilledWaterTemperature(
  double referenceHeatingModeLeavingChilledWaterTemperature) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceHeatingModeLeavingChilledWaterTemperature(
    referenceHeatingModeLeavingChilledWaterTemperature);
}

double ChillerHeaterPerformanceElectricEIR::referenceHeatingModeLeavingCondenserWaterTemperature() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceHeatingModeLeavingCondenserWaterTemperature();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceHeatingModeLeavingCondenserWaterTemperature(
  double referenceHeatingModeLeavingCondenserWaterTemperature) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceHeatingModeLeavingCondenserWaterTemperature(
    referenceHeatingModeLeavingCondenserWaterTemperature);
}

double ChillerHeaterPerformanceElectricEIR::referenceHeatingModeEnteringCondenserFluidTemperature() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->referenceHeatingModeEnteringCondenserFluidTemperature();
}

bool ChillerHeaterPerformanceElectricEIR::setReferenceHeatingModeEnteringCondenserFluidTemperature(
  double referenceHeatingModeEnteringCondenserFluidTemperature) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setReferenceHeatingModeEnteringCondenserFluidTemperature(
    referenceHeatingModeEnteringCondenserFluidTemperature);
}

double ChillerHeaterPerformanceElectricEIR::heatingModeEnteringChilledWaterTemperatureLowLimit() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->heatingModeEnteringChilledWaterTemperatureLowLimit();
}

bool ChillerHeaterPerformanceElectricEIR::setHeatingModeEnteringChilledWaterTemperatureLowLimit(
  double heatingModeEnteringChilledWaterTemperatureLowLimit) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setHeatingModeEnteringChilledWaterTemperatureLowLimit(
    heatingModeEnteringChilledWaterTemperatureLowLimit);
}

std::string ChillerHeaterPerformanceElectricEIR::chilledWaterFlowModeType() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->chilledWaterFlowModeType();
}

bool ChillerHeaterPerformanceElectricEIR::setChilledWaterFlowModeType(const std::string& chilledWaterFlowModeType) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setChilledWaterFlowModeType(chilledWaterFlowModeType);
}

boost::optional<double> ChillerHeaterPerformanceElectricEIR::designChilledWaterFlowRate() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->designChilledWaterFlowRate();
}

bool ChillerHeaterPerformanceElectricEIR::isDesignChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->isDesignChilledWaterFlowRateAutosized();
}

bool ChillerHeaterPerformanceElectricEIR::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
}

void ChillerHeaterPerformanceElectricEIR::resetDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->resetDesignChilledWaterFlowRate();
}

void ChillerHeaterPerformanceElectricEIR::autosizeDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->autosizeDesignChilledWaterFlowRate();
}

boost::optional<double> ChillerHeaterPerformanceElectricEIR::designCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->designCondenserWaterFlowRate();
}

bool ChillerHeaterPerformanceElectricEIR::isDesignCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->isDesignCondenserWaterFlowRateAutosized();
}

bool ChillerHeaterPerformanceElectricEIR::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
}

void ChillerHeaterPerformanceElectricEIR::resetDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->resetDesignCondenserWaterFlowRate();
}

void ChillerHeaterPerformanceElectricEIR::autosizeDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->autosizeDesignCondenserWaterFlowRate();
}

double ChillerHeaterPerformanceElectricEIR::designHotWaterFlowRate() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->designHotWaterFlowRate();
}

bool ChillerHeaterPerformanceElectricEIR::setDesignHotWaterFlowRate(double designHotWaterFlowRate) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setDesignHotWaterFlowRate(designHotWaterFlowRate);
}

double ChillerHeaterPerformanceElectricEIR::compressorMotorEfficiency() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->compressorMotorEfficiency();
}

bool ChillerHeaterPerformanceElectricEIR::setCompressorMotorEfficiency(double compressorMotorEfficiency) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setCompressorMotorEfficiency(compressorMotorEfficiency);
}

std::string ChillerHeaterPerformanceElectricEIR::condenserType() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->condenserType();
}

bool ChillerHeaterPerformanceElectricEIR::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setCondenserType(condenserType);
}

std::string ChillerHeaterPerformanceElectricEIR::coolingModeTemperatureCurveCondenserWaterIndependentVariable() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->coolingModeTemperatureCurveCondenserWaterIndependentVariable();
}

bool ChillerHeaterPerformanceElectricEIR::setCoolingModeTemperatureCurveCondenserWaterIndependentVariable(
  const std::string& coolingModeTemperatureCurveCondenserWaterIndependentVariable) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setCoolingModeTemperatureCurveCondenserWaterIndependentVariable(
    coolingModeTemperatureCurveCondenserWaterIndependentVariable);
}

double ChillerHeaterPerformanceElectricEIR::coolingModeCoolingCapacityOptimumPartLoadRatio() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->coolingModeCoolingCapacityOptimumPartLoadRatio();
}

bool ChillerHeaterPerformanceElectricEIR::setCoolingModeCoolingCapacityOptimumPartLoadRatio(double coolingModeCoolingCapacityOptimumPartLoadRatio) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setCoolingModeCoolingCapacityOptimumPartLoadRatio(
    coolingModeCoolingCapacityOptimumPartLoadRatio);
}

std::string ChillerHeaterPerformanceElectricEIR::heatingModeTemperatureCurveCondenserWaterIndependentVariable() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->heatingModeTemperatureCurveCondenserWaterIndependentVariable();
}

bool ChillerHeaterPerformanceElectricEIR::setHeatingModeTemperatureCurveCondenserWaterIndependentVariable(
  const std::string& heatingModeTemperatureCurveCondenserWaterIndependentVariable) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setHeatingModeTemperatureCurveCondenserWaterIndependentVariable(
    heatingModeTemperatureCurveCondenserWaterIndependentVariable);
}

double ChillerHeaterPerformanceElectricEIR::heatingModeCoolingCapacityOptimumPartLoadRatio() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->heatingModeCoolingCapacityOptimumPartLoadRatio();
}

bool ChillerHeaterPerformanceElectricEIR::setHeatingModeCoolingCapacityOptimumPartLoadRatio(double heatingModeCoolingCapacityOptimumPartLoadRatio) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setHeatingModeCoolingCapacityOptimumPartLoadRatio(
    heatingModeCoolingCapacityOptimumPartLoadRatio);
}

double ChillerHeaterPerformanceElectricEIR::sizingFactor() const {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->sizingFactor();
}

bool ChillerHeaterPerformanceElectricEIR::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerHeaterPerformanceElectricEIR_Impl>()->setSizingFactor(sizingFactor);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ChillerHeaterPerformanceElectricEIR_Impl::referenceCoolingModeEvaporatorCapacity() const {
  return getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEvaporatorCapacity, true);
}

bool ChillerHeaterPerformanceElectricEIR_Impl::isReferenceCoolingModeEvaporatorCapacityAutosized() const {
  if (auto value = getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEvaporatorCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceCoolingModeEvaporatorCapacity(double referenceCoolingModeEvaporatorCapacity) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEvaporatorCapacity,
                   referenceCoolingModeEvaporatorCapacity);
}

void ChillerHeaterPerformanceElectricEIR_Impl::autosizeReferenceCoolingModeEvaporatorCapacity() {
  OS_ASSERT(setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEvaporatorCapacity, "Autosize"));
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceCoolingModeCOP() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceCoolingModeCOP(double referenceCoolingModeCOP) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeCOP, referenceCoolingModeCOP);
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceCoolingModeLeavingChilledWaterTemperature() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingChilledWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceCoolingModeLeavingChilledWaterTemperature(
  double referenceCoolingModeLeavingChilledWaterTemperature) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingChilledWaterTemperature,
                                referenceCoolingModeLeavingChilledWaterTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceCoolingModeEnteringCondenserFluidTemperature() const {
  const auto value =
    getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEnteringCondenserFluidTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceCoolingModeEnteringCondenserFluidTemperature(
  double referenceCoolingModeEnteringCondenserFluidTemperature) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEnteringCondenserFluidTemperature,
                                referenceCoolingModeEnteringCondenserFluidTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceCoolingModeLeavingCondenserWaterTemperature() const {
  const auto value =
    getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingCondenserWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceCoolingModeLeavingCondenserWaterTemperature(
  double referenceCoolingModeLeavingCondenserWaterTemperature) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingCondenserWaterTemperature,
                                referenceCoolingModeLeavingCondenserWaterTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceHeatingModeCoolingCapacityRatio() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingCapacityRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceHeatingModeCoolingCapacityRatio(double referenceHeatingModeCoolingCapacityRatio) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingCapacityRatio,
                                referenceHeatingModeCoolingCapacityRatio);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceHeatingModeCoolingPowerInputRatio() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingPowerInputRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceHeatingModeCoolingPowerInputRatio(double referenceHeatingModeCoolingPowerInputRatio) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingPowerInputRatio,
                   referenceHeatingModeCoolingPowerInputRatio);
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceHeatingModeLeavingChilledWaterTemperature() const {
  const auto value =
    getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingChilledWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceHeatingModeLeavingChilledWaterTemperature(
  double referenceHeatingModeLeavingChilledWaterTemperature) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingChilledWaterTemperature,
                                referenceHeatingModeLeavingChilledWaterTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceHeatingModeLeavingCondenserWaterTemperature() const {
  const auto value =
    getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingCondenserWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceHeatingModeLeavingCondenserWaterTemperature(
  double referenceHeatingModeLeavingCondenserWaterTemperature) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingCondenserWaterTemperature,
                                referenceHeatingModeLeavingCondenserWaterTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::referenceHeatingModeEnteringCondenserFluidTemperature() const {
  const auto value =
    getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeEnteringCondenserFluidTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setReferenceHeatingModeEnteringCondenserFluidTemperature(
  double referenceHeatingModeEnteringCondenserFluidTemperature) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeEnteringCondenserFluidTemperature,
                                referenceHeatingModeEnteringCondenserFluidTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerHeaterPerformanceElectricEIR_Impl::heatingModeEnteringChilledWaterTemperatureLowLimit() const {
  const auto value =
    getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeEnteringChilledWaterTemperatureLowLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setHeatingModeEnteringChilledWaterTemperatureLowLimit(
  double heatingModeEnteringChilledWaterTemperatureLowLimit) {
  const bool result = setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeEnteringChilledWaterTemperatureLowLimit,
                                heatingModeEnteringChilledWaterTemperatureLowLimit);
  OS_ASSERT(result);
  return result;
}

std::string ChillerHeaterPerformanceElectricEIR_Impl::chilledWaterFlowModeType() const {
  const auto value = getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ChilledWaterFlowModeType, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setChilledWaterFlowModeType(const std::string& chilledWaterFlowModeType) {
  return setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::ChilledWaterFlowModeType, chilledWaterFlowModeType);
}

boost::optional<double> ChillerHeaterPerformanceElectricEIR_Impl::designChilledWaterFlowRate() const {
  return getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, true);
}

bool ChillerHeaterPerformanceElectricEIR_Impl::isDesignChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
}

void ChillerHeaterPerformanceElectricEIR_Impl::resetDesignChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, ""));
}

void ChillerHeaterPerformanceElectricEIR_Impl::autosizeDesignChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, "Autosize"));
}

boost::optional<double> ChillerHeaterPerformanceElectricEIR_Impl::designCondenserWaterFlowRate() const {
  return getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, true);
}

bool ChillerHeaterPerformanceElectricEIR_Impl::isDesignCondenserWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
}

void ChillerHeaterPerformanceElectricEIR_Impl::resetDesignCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, ""));
}

void ChillerHeaterPerformanceElectricEIR_Impl::autosizeDesignCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, "Autosize"));
}

double ChillerHeaterPerformanceElectricEIR_Impl::designHotWaterFlowRate() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignHotWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setDesignHotWaterFlowRate(double designHotWaterFlowRate) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::DesignHotWaterFlowRate, designHotWaterFlowRate);
}

double ChillerHeaterPerformanceElectricEIR_Impl::compressorMotorEfficiency() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CompressorMotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setCompressorMotorEfficiency(double compressorMotorEfficiency) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CompressorMotorEfficiency, compressorMotorEfficiency);
}

std::string ChillerHeaterPerformanceElectricEIR_Impl::condenserType() const {
  const auto value = getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CondenserType, condenserType);
}

std::string ChillerHeaterPerformanceElectricEIR_Impl::coolingModeTemperatureCurveCondenserWaterIndependentVariable() const {
  const auto value =
    getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CoolingModeTemperatureCurveCondenserWaterIndependentVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setCoolingModeTemperatureCurveCondenserWaterIndependentVariable(
  const std::string& coolingModeTemperatureCurveCondenserWaterIndependentVariable) {
  return setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CoolingModeTemperatureCurveCondenserWaterIndependentVariable,
                   coolingModeTemperatureCurveCondenserWaterIndependentVariable);
}

double ChillerHeaterPerformanceElectricEIR_Impl::coolingModeCoolingCapacityOptimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CoolingModeCoolingCapacityOptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setCoolingModeCoolingCapacityOptimumPartLoadRatio(
  double coolingModeCoolingCapacityOptimumPartLoadRatio) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::CoolingModeCoolingCapacityOptimumPartLoadRatio,
                   coolingModeCoolingCapacityOptimumPartLoadRatio);
}

std::string ChillerHeaterPerformanceElectricEIR_Impl::heatingModeTemperatureCurveCondenserWaterIndependentVariable() const {
  const auto value =
    getString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeTemperatureCurveCondenserWaterIndependentVariable, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setHeatingModeTemperatureCurveCondenserWaterIndependentVariable(
  const std::string& heatingModeTemperatureCurveCondenserWaterIndependentVariable) {
  return setString(openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeTemperatureCurveCondenserWaterIndependentVariable,
                   heatingModeTemperatureCurveCondenserWaterIndependentVariable);
}

double ChillerHeaterPerformanceElectricEIR_Impl::heatingModeCoolingCapacityOptimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeCoolingCapacityOptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setHeatingModeCoolingCapacityOptimumPartLoadRatio(
  double heatingModeCoolingCapacityOptimumPartLoadRatio) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::HeatingModeCoolingCapacityOptimumPartLoadRatio,
                   heatingModeCoolingCapacityOptimumPartLoadRatio);
}

double ChillerHeaterPerformanceElectricEIR_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerHeaterPerformanceElectricEIR_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::ChillerHeaterPerformance_Electric_EIRFields::SizingFactor, sizingFactor);
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR_Impl::chilledWaterFlowModeTypeValues() const {
  return openstudio::epmodel::ChillerHeaterPerformanceElectricEIR::chilledWaterFlowModeTypeValues();
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR_Impl::condenserTypeValues() const {
  return openstudio::epmodel::ChillerHeaterPerformanceElectricEIR::condenserTypeValues();
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR_Impl::coolingModeTemperatureCurveCondenserWaterIndependentVariableValues() const {
  return openstudio::epmodel::ChillerHeaterPerformanceElectricEIR::coolingModeTemperatureCurveCondenserWaterIndependentVariableValues();
}

std::vector<std::string> ChillerHeaterPerformanceElectricEIR_Impl::heatingModeTemperatureCurveCondenserWaterIndependentVariableValues() const {
  return openstudio::epmodel::ChillerHeaterPerformanceElectricEIR::heatingModeTemperatureCurveCondenserWaterIndependentVariableValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
