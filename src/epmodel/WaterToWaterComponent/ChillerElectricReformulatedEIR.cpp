/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp"
#include "WaterToWaterComponent/ChillerElectricReformulatedEIR_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Electric_ReformulatedEIR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerElectricReformulatedEIR::ChillerElectricReformulatedEIR(const Model& model)
  : ModelObject(ChillerElectricReformulatedEIR::iddObjectType(), model) {}

ChillerElectricReformulatedEIR::ChillerElectricReformulatedEIR(std::shared_ptr<detail::ChillerElectricReformulatedEIR_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ChillerElectricReformulatedEIR::iddObjectType() {
  return IddObjectType::Chiller_Electric_ReformulatedEIR;
}

std::vector<std::string> ChillerElectricReformulatedEIR::validChillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType);
}

std::vector<std::string> ChillerElectricReformulatedEIR::validCondenserFlowControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserFlowControl);
}

std::vector<std::string> ChillerElectricReformulatedEIR::validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType);
}

boost::optional<double> ChillerElectricReformulatedEIR::referenceCapacity() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->referenceCapacity();
}

bool ChillerElectricReformulatedEIR::isReferenceCapacityAutosized() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isReferenceCapacityAutosized();
}

bool ChillerElectricReformulatedEIR::setReferenceCapacity(boost::optional<double> referenceCapacity) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceCapacity(referenceCapacity);
}

bool ChillerElectricReformulatedEIR::setReferenceCapacity(double referenceCapacity) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceCapacity(referenceCapacity);
}

void ChillerElectricReformulatedEIR::autosizeReferenceCapacity() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizeReferenceCapacity();
}

double ChillerElectricReformulatedEIR::referenceCOP() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->referenceCOP();
}

bool ChillerElectricReformulatedEIR::setReferenceCOP(double referenceCOP) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceCOP(referenceCOP);
}

double ChillerElectricReformulatedEIR::referenceLeavingChilledWaterTemperature() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->referenceLeavingChilledWaterTemperature();
}

bool ChillerElectricReformulatedEIR::isReferenceLeavingChilledWaterTemperatureDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isReferenceLeavingChilledWaterTemperatureDefaulted();
}

bool ChillerElectricReformulatedEIR::setReferenceLeavingChilledWaterTemperature(double referenceLeavingChilledWaterTemperature) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceLeavingChilledWaterTemperature(referenceLeavingChilledWaterTemperature);
}

void ChillerElectricReformulatedEIR::resetReferenceLeavingChilledWaterTemperature() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetReferenceLeavingChilledWaterTemperature();
}

double ChillerElectricReformulatedEIR::referenceLeavingCondenserWaterTemperature() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->referenceLeavingCondenserWaterTemperature();
}

bool ChillerElectricReformulatedEIR::isReferenceLeavingCondenserWaterTemperatureDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isReferenceLeavingCondenserWaterTemperatureDefaulted();
}

bool ChillerElectricReformulatedEIR::setReferenceLeavingCondenserWaterTemperature(double referenceLeavingCondenserWaterTemperature) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceLeavingCondenserWaterTemperature(referenceLeavingCondenserWaterTemperature);
}

void ChillerElectricReformulatedEIR::resetReferenceLeavingCondenserWaterTemperature() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetReferenceLeavingCondenserWaterTemperature();
}

boost::optional<double> ChillerElectricReformulatedEIR::referenceChilledWaterFlowRate() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->referenceChilledWaterFlowRate();
}

bool ChillerElectricReformulatedEIR::isReferenceChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isReferenceChilledWaterFlowRateAutosized();
}

bool ChillerElectricReformulatedEIR::setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceChilledWaterFlowRate(referenceChilledWaterFlowRate);
}

bool ChillerElectricReformulatedEIR::setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceChilledWaterFlowRate(referenceChilledWaterFlowRate);
}

void ChillerElectricReformulatedEIR::resetReferenceChilledWaterFlowRate() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetReferenceChilledWaterFlowRate();
}

void ChillerElectricReformulatedEIR::autosizeReferenceChilledWaterFlowRate() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizeReferenceChilledWaterFlowRate();
}

boost::optional<double> ChillerElectricReformulatedEIR::referenceCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->referenceCondenserWaterFlowRate();
}

bool ChillerElectricReformulatedEIR::isReferenceCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isReferenceCondenserWaterFlowRateAutosized();
}

bool ChillerElectricReformulatedEIR::setReferenceCondenserWaterFlowRate(boost::optional<double> referenceCondenserWaterFlowRate) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceCondenserWaterFlowRate(referenceCondenserWaterFlowRate);
}

bool ChillerElectricReformulatedEIR::setReferenceCondenserWaterFlowRate(double referenceCondenserWaterFlowRate) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceCondenserWaterFlowRate(referenceCondenserWaterFlowRate);
}

void ChillerElectricReformulatedEIR::resetReferenceCondenserWaterFlowRate() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetReferenceCondenserWaterFlowRate();
}

void ChillerElectricReformulatedEIR::autosizeReferenceCondenserWaterFlowRate() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizeReferenceCondenserWaterFlowRate();
}

std::string ChillerElectricReformulatedEIR::electricInputToCoolingOutputRatioFunctionOfPLRType() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->electricInputToCoolingOutputRatioFunctionOfPLRType();
}

bool ChillerElectricReformulatedEIR::setElectricInputToCoolingOutputRatioFunctionOfPLRType(
  const std::string& electricInputToCoolingOutputRatioFunctionOfPLRType) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setElectricInputToCoolingOutputRatioFunctionOfPLRType(
    electricInputToCoolingOutputRatioFunctionOfPLRType);
}

void ChillerElectricReformulatedEIR::resetElectricInputToCoolingOutputRatioFunctionOfPLRType() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetElectricInputToCoolingOutputRatioFunctionOfPLRType();
}

double ChillerElectricReformulatedEIR::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->minimumPartLoadRatio();
}

bool ChillerElectricReformulatedEIR::isMinimumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isMinimumPartLoadRatioDefaulted();
}

bool ChillerElectricReformulatedEIR::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

void ChillerElectricReformulatedEIR::resetMinimumPartLoadRatio() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetMinimumPartLoadRatio();
}

double ChillerElectricReformulatedEIR::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->maximumPartLoadRatio();
}

bool ChillerElectricReformulatedEIR::isMaximumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isMaximumPartLoadRatioDefaulted();
}

bool ChillerElectricReformulatedEIR::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

void ChillerElectricReformulatedEIR::resetMaximumPartLoadRatio() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetMaximumPartLoadRatio();
}

double ChillerElectricReformulatedEIR::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->optimumPartLoadRatio();
}

bool ChillerElectricReformulatedEIR::isOptimumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isOptimumPartLoadRatioDefaulted();
}

bool ChillerElectricReformulatedEIR::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

void ChillerElectricReformulatedEIR::resetOptimumPartLoadRatio() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetOptimumPartLoadRatio();
}

double ChillerElectricReformulatedEIR::minimumUnloadingRatio() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->minimumUnloadingRatio();
}

bool ChillerElectricReformulatedEIR::isMinimumUnloadingRatioDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isMinimumUnloadingRatioDefaulted();
}

bool ChillerElectricReformulatedEIR::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setMinimumUnloadingRatio(minimumUnloadingRatio);
}

void ChillerElectricReformulatedEIR::resetMinimumUnloadingRatio() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetMinimumUnloadingRatio();
}

double ChillerElectricReformulatedEIR::fractionofCompressorElectricConsumptionRejectedbyCondenser() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->fractionofCompressorElectricConsumptionRejectedbyCondenser();
}

bool ChillerElectricReformulatedEIR::isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted();
}

bool ChillerElectricReformulatedEIR::setFractionofCompressorElectricConsumptionRejectedbyCondenser(
  double fractionofCompressorElectricConsumptionRejectedbyCondenser) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setFractionofCompressorElectricConsumptionRejectedbyCondenser(
    fractionofCompressorElectricConsumptionRejectedbyCondenser);
}

void ChillerElectricReformulatedEIR::resetFractionofCompressorElectricConsumptionRejectedbyCondenser() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetFractionofCompressorElectricConsumptionRejectedbyCondenser();
}

double ChillerElectricReformulatedEIR::leavingChilledWaterLowerTemperatureLimit() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->leavingChilledWaterLowerTemperatureLimit();
}

bool ChillerElectricReformulatedEIR::isLeavingChilledWaterLowerTemperatureLimitDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isLeavingChilledWaterLowerTemperatureLimitDefaulted();
}

bool ChillerElectricReformulatedEIR::setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setLeavingChilledWaterLowerTemperatureLimit(
    leavingChilledWaterLowerTemperatureLimit);
}

void ChillerElectricReformulatedEIR::resetLeavingChilledWaterLowerTemperatureLimit() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetLeavingChilledWaterLowerTemperatureLimit();
}

std::string ChillerElectricReformulatedEIR::chillerFlowMode() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->chillerFlowMode();
}

bool ChillerElectricReformulatedEIR::isChillerFlowModeDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isChillerFlowModeDefaulted();
}

bool ChillerElectricReformulatedEIR::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setChillerFlowMode(chillerFlowMode);
}

void ChillerElectricReformulatedEIR::resetChillerFlowMode() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetChillerFlowMode();
}

boost::optional<double> ChillerElectricReformulatedEIR::designHeatRecoveryWaterFlowRate() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->designHeatRecoveryWaterFlowRate();
}

bool ChillerElectricReformulatedEIR::isDesignHeatRecoveryWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isDesignHeatRecoveryWaterFlowRateAutosized();
}

bool ChillerElectricReformulatedEIR::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
}

void ChillerElectricReformulatedEIR::autosizeDesignHeatRecoveryWaterFlowRate() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizeDesignHeatRecoveryWaterFlowRate();
}

double ChillerElectricReformulatedEIR::sizingFactor() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->sizingFactor();
}

bool ChillerElectricReformulatedEIR::isSizingFactorDefaulted() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->isSizingFactorDefaulted();
}

bool ChillerElectricReformulatedEIR::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setSizingFactor(sizingFactor);
}

void ChillerElectricReformulatedEIR::resetSizingFactor() {
  getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetSizingFactor();
}

double ChillerElectricReformulatedEIR::condenserHeatRecoveryRelativeCapacityFraction() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserHeatRecoveryRelativeCapacityFraction();
}

bool ChillerElectricReformulatedEIR::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setCondenserHeatRecoveryRelativeCapacityFraction(
    condenserHeatRecoveryRelativeCapacityFraction);
}

std::string ChillerElectricReformulatedEIR::endUseSubcategory() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->endUseSubcategory();
}

bool ChillerElectricReformulatedEIR::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

std::string ChillerElectricReformulatedEIR::condenserFlowControl() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserFlowControl();
}

bool ChillerElectricReformulatedEIR::setCondenserFlowControl(const std::string& condenserFlowControl) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setCondenserFlowControl(condenserFlowControl);
}

double ChillerElectricReformulatedEIR::condenserMinimumFlowFraction() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserMinimumFlowFraction();
}

bool ChillerElectricReformulatedEIR::setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setCondenserMinimumFlowFraction(condenserMinimumFlowFraction);
}

double ChillerElectricReformulatedEIR::thermosiphonMinimumTemperatureDifference() const {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->thermosiphonMinimumTemperatureDifference();
}

bool ChillerElectricReformulatedEIR::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setThermosiphonMinimumTemperatureDifference(
    thermosiphonMinimumTemperatureDifference);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ChillerElectricReformulatedEIR_Impl::referenceCapacity() const {
  return getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, true);
}

bool ChillerElectricReformulatedEIR_Impl::isReferenceCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceCapacity(boost::optional<double> referenceCapacity) {
  bool result = false;
  if (referenceCapacity) {
    result = setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, *referenceCapacity);
  }
  return result;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceCapacity(double referenceCapacity) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, referenceCapacity);
}

void ChillerElectricReformulatedEIR_Impl::autosizeReferenceCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, "Autosize"));
}

double ChillerElectricReformulatedEIR_Impl::referenceCOP() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceCOP(double referenceCOP) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCOP, referenceCOP);
}

double ChillerElectricReformulatedEIR_Impl::referenceLeavingChilledWaterTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isReferenceLeavingChilledWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature);
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceLeavingChilledWaterTemperature(double referenceLeavingChilledWaterTemperature) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature, referenceLeavingChilledWaterTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricReformulatedEIR_Impl::resetReferenceLeavingChilledWaterTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature, ""));
}

double ChillerElectricReformulatedEIR_Impl::referenceLeavingCondenserWaterTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingCondenserWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isReferenceLeavingCondenserWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingCondenserWaterTemperature);
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceLeavingCondenserWaterTemperature(double referenceLeavingCondenserWaterTemperature) {
  const bool result = setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingCondenserWaterTemperature,
                                referenceLeavingCondenserWaterTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricReformulatedEIR_Impl::resetReferenceLeavingCondenserWaterTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingCondenserWaterTemperature, ""));
}

boost::optional<double> ChillerElectricReformulatedEIR_Impl::referenceChilledWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, true);
}

bool ChillerElectricReformulatedEIR_Impl::isReferenceChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate) {
  bool result = false;
  if (referenceChilledWaterFlowRate) {
    result = setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, *referenceChilledWaterFlowRate);
  }
  return result;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, referenceChilledWaterFlowRate);
}

void ChillerElectricReformulatedEIR_Impl::resetReferenceChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, ""));
}

void ChillerElectricReformulatedEIR_Impl::autosizeReferenceChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, "Autosize"));
}

boost::optional<double> ChillerElectricReformulatedEIR_Impl::referenceCondenserWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, true);
}

bool ChillerElectricReformulatedEIR_Impl::isReferenceCondenserWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceCondenserWaterFlowRate(boost::optional<double> referenceCondenserWaterFlowRate) {
  bool result = false;
  if (referenceCondenserWaterFlowRate) {
    result = setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, *referenceCondenserWaterFlowRate);
  }
  return result;
}

bool ChillerElectricReformulatedEIR_Impl::setReferenceCondenserWaterFlowRate(double referenceCondenserWaterFlowRate) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, referenceCondenserWaterFlowRate);
}

void ChillerElectricReformulatedEIR_Impl::resetReferenceCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, ""));
}

void ChillerElectricReformulatedEIR_Impl::autosizeReferenceCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, "Autosize"));
}

std::string ChillerElectricReformulatedEIR_Impl::electricInputToCoolingOutputRatioFunctionOfPLRType() const {
  const auto value =
    getString(openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setElectricInputToCoolingOutputRatioFunctionOfPLRType(
  const std::string& electricInputToCoolingOutputRatioFunctionOfPLRType) {
  return setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType,
                   electricInputToCoolingOutputRatioFunctionOfPLRType);
}

void ChillerElectricReformulatedEIR_Impl::resetElectricInputToCoolingOutputRatioFunctionOfPLRType() {
  OS_ASSERT(
    setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, ""));
}

double ChillerElectricReformulatedEIR_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isMinimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio);
}

bool ChillerElectricReformulatedEIR_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

void ChillerElectricReformulatedEIR_Impl::resetMinimumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio, ""));
}

double ChillerElectricReformulatedEIR_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isMaximumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio);
}

bool ChillerElectricReformulatedEIR_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

void ChillerElectricReformulatedEIR_Impl::resetMaximumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio, ""));
}

double ChillerElectricReformulatedEIR_Impl::optimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isOptimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio);
}

bool ChillerElectricReformulatedEIR_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio, optimumPartLoadRatio);
}

void ChillerElectricReformulatedEIR_Impl::resetOptimumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio, ""));
}

double ChillerElectricReformulatedEIR_Impl::minimumUnloadingRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isMinimumUnloadingRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio);
}

bool ChillerElectricReformulatedEIR_Impl::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio, minimumUnloadingRatio);
}

void ChillerElectricReformulatedEIR_Impl::resetMinimumUnloadingRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio, ""));
}

double ChillerElectricReformulatedEIR_Impl::fractionofCompressorElectricConsumptionRejectedbyCondenser() const {
  const auto value =
    getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser);
}

bool ChillerElectricReformulatedEIR_Impl::setFractionofCompressorElectricConsumptionRejectedbyCondenser(
  double fractionofCompressorElectricConsumptionRejectedbyCondenser) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser,
                   fractionofCompressorElectricConsumptionRejectedbyCondenser);
}

void ChillerElectricReformulatedEIR_Impl::resetFractionofCompressorElectricConsumptionRejectedbyCondenser() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, ""));
}

double ChillerElectricReformulatedEIR_Impl::leavingChilledWaterLowerTemperatureLimit() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isLeavingChilledWaterLowerTemperatureLimitDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit);
}

bool ChillerElectricReformulatedEIR_Impl::setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit, leavingChilledWaterLowerTemperatureLimit);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricReformulatedEIR_Impl::resetLeavingChilledWaterLowerTemperatureLimit() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit, ""));
}

std::string ChillerElectricReformulatedEIR_Impl::chillerFlowMode() const {
  const auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isChillerFlowModeDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType);
}

bool ChillerElectricReformulatedEIR_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  if (openstudio::istringEqual(chillerFlowMode, "VariableFlow")) {
    return setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType, "LeavingSetpointModulated");
  }
  return setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType, chillerFlowMode);
}

void ChillerElectricReformulatedEIR_Impl::resetChillerFlowMode() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType, ""));
}

boost::optional<double> ChillerElectricReformulatedEIR_Impl::designHeatRecoveryWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, true);
}

bool ChillerElectricReformulatedEIR_Impl::isDesignHeatRecoveryWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricReformulatedEIR_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
}

void ChillerElectricReformulatedEIR_Impl::autosizeDesignHeatRecoveryWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, "Autosize"));
}

double ChillerElectricReformulatedEIR_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ReformulatedEIRFields::SizingFactor);
}

bool ChillerElectricReformulatedEIR_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::SizingFactor, sizingFactor);
}

void ChillerElectricReformulatedEIR_Impl::resetSizingFactor() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::SizingFactor, ""));
}

double ChillerElectricReformulatedEIR_Impl::condenserHeatRecoveryRelativeCapacityFraction() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserHeatRecoveryRelativeCapacityFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserHeatRecoveryRelativeCapacityFraction,
                   condenserHeatRecoveryRelativeCapacityFraction);
}

std::string ChillerElectricReformulatedEIR_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return setString(openstudio::Chiller_Electric_ReformulatedEIRFields::EndUseSubcategory, endUseSubcategory);
}

std::string ChillerElectricReformulatedEIR_Impl::condenserFlowControl() const {
  const auto value = getString(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserFlowControl, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setCondenserFlowControl(const std::string& condenserFlowControl) {
  return setString(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserFlowControl, condenserFlowControl);
}

double ChillerElectricReformulatedEIR_Impl::condenserMinimumFlowFraction() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserMinimumFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserMinimumFlowFraction, condenserMinimumFlowFraction);
}

double ChillerElectricReformulatedEIR_Impl::thermosiphonMinimumTemperatureDifference() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ThermosiphonMinimumTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricReformulatedEIR_Impl::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ThermosiphonMinimumTemperatureDifference,
                   thermosiphonMinimumTemperatureDifference);
}

std::vector<std::string> ChillerElectricReformulatedEIR_Impl::validChillerFlowModeValues() const {
  return ChillerElectricReformulatedEIR::validChillerFlowModeValues();
}

std::vector<std::string> ChillerElectricReformulatedEIR_Impl::validCondenserFlowControlValues() const {
  return ChillerElectricReformulatedEIR::validCondenserFlowControlValues();
}

std::vector<std::string> ChillerElectricReformulatedEIR_Impl::validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues() const {
  return ChillerElectricReformulatedEIR::validElectricInputToCoolingOutputRatioFunctionOfPLRTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
