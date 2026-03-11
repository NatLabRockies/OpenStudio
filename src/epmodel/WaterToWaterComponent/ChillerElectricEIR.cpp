/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerElectricEIR.hpp"
#include "WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Electric_EIR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerElectricEIR::ChillerElectricEIR(const Model& model) : ModelObject(ChillerElectricEIR::iddObjectType(), model) {}

ChillerElectricEIR::ChillerElectricEIR(std::shared_ptr<detail::ChillerElectricEIR_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ChillerElectricEIR::iddObjectType() {
  return IddObjectType::Chiller_Electric_EIR;
}

std::vector<std::string> ChillerElectricEIR::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_Electric_EIRFields::CondenserType);
}

std::vector<std::string> ChillerElectricEIR::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_Electric_EIRFields::ChillerFlowMode);
}

std::vector<std::string> ChillerElectricEIR::condenserFlowControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_Electric_EIRFields::CondenserFlowControl);
}

boost::optional<double> ChillerElectricEIR::referenceCapacity() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->referenceCapacity();
}

bool ChillerElectricEIR::isReferenceCapacityAutosized() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isReferenceCapacityAutosized();
}

bool ChillerElectricEIR::setReferenceCapacity(boost::optional<double> referenceCapacity) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceCapacity(referenceCapacity);
}

bool ChillerElectricEIR::setReferenceCapacity(double referenceCapacity) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceCapacity(referenceCapacity);
}

void ChillerElectricEIR::autosizeReferenceCapacity() {
  getImpl<detail::ChillerElectricEIR_Impl>()->autosizeReferenceCapacity();
}

double ChillerElectricEIR::referenceCOP() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->referenceCOP();
}

bool ChillerElectricEIR::setReferenceCOP(double referenceCOP) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceCOP(referenceCOP);
}

double ChillerElectricEIR::referenceLeavingChilledWaterTemperature() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->referenceLeavingChilledWaterTemperature();
}

bool ChillerElectricEIR::isReferenceLeavingChilledWaterTemperatureDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isReferenceLeavingChilledWaterTemperatureDefaulted();
}

bool ChillerElectricEIR::setReferenceLeavingChilledWaterTemperature(double referenceLeavingChilledWaterTemperature) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceLeavingChilledWaterTemperature(referenceLeavingChilledWaterTemperature);
}

void ChillerElectricEIR::resetReferenceLeavingChilledWaterTemperature() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetReferenceLeavingChilledWaterTemperature();
}

double ChillerElectricEIR::referenceEnteringCondenserFluidTemperature() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->referenceEnteringCondenserFluidTemperature();
}

bool ChillerElectricEIR::isReferenceEnteringCondenserFluidTemperatureDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isReferenceEnteringCondenserFluidTemperatureDefaulted();
}

bool ChillerElectricEIR::setReferenceEnteringCondenserFluidTemperature(double referenceEnteringCondenserFluidTemperature) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceEnteringCondenserFluidTemperature(referenceEnteringCondenserFluidTemperature);
}

void ChillerElectricEIR::resetReferenceEnteringCondenserFluidTemperature() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetReferenceEnteringCondenserFluidTemperature();
}

boost::optional<double> ChillerElectricEIR::referenceChilledWaterFlowRate() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->referenceChilledWaterFlowRate();
}

bool ChillerElectricEIR::isReferenceChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isReferenceChilledWaterFlowRateAutosized();
}

bool ChillerElectricEIR::setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceChilledWaterFlowRate(referenceChilledWaterFlowRate);
}

bool ChillerElectricEIR::setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceChilledWaterFlowRate(referenceChilledWaterFlowRate);
}

void ChillerElectricEIR::resetReferenceChilledWaterFlowRate() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetReferenceChilledWaterFlowRate();
}

void ChillerElectricEIR::autosizeReferenceChilledWaterFlowRate() {
  getImpl<detail::ChillerElectricEIR_Impl>()->autosizeReferenceChilledWaterFlowRate();
}

boost::optional<double> ChillerElectricEIR::referenceCondenserFluidFlowRate() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->referenceCondenserFluidFlowRate();
}

bool ChillerElectricEIR::isReferenceCondenserFluidFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isReferenceCondenserFluidFlowRateAutosized();
}

bool ChillerElectricEIR::setReferenceCondenserFluidFlowRate(boost::optional<double> referenceCondenserFluidFlowRate) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceCondenserFluidFlowRate(referenceCondenserFluidFlowRate);
}

bool ChillerElectricEIR::setReferenceCondenserFluidFlowRate(double referenceCondenserFluidFlowRate) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setReferenceCondenserFluidFlowRate(referenceCondenserFluidFlowRate);
}

void ChillerElectricEIR::resetReferenceCondenserFluidFlowRate() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetReferenceCondenserFluidFlowRate();
}

void ChillerElectricEIR::autosizeReferenceCondenserFluidFlowRate() {
  getImpl<detail::ChillerElectricEIR_Impl>()->autosizeReferenceCondenserFluidFlowRate();
}

double ChillerElectricEIR::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->minimumPartLoadRatio();
}

bool ChillerElectricEIR::isMinimumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isMinimumPartLoadRatioDefaulted();
}

bool ChillerElectricEIR::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

void ChillerElectricEIR::resetMinimumPartLoadRatio() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetMinimumPartLoadRatio();
}

double ChillerElectricEIR::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->maximumPartLoadRatio();
}

bool ChillerElectricEIR::isMaximumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isMaximumPartLoadRatioDefaulted();
}

bool ChillerElectricEIR::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

void ChillerElectricEIR::resetMaximumPartLoadRatio() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetMaximumPartLoadRatio();
}

double ChillerElectricEIR::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->optimumPartLoadRatio();
}

bool ChillerElectricEIR::isOptimumPartLoadRatioDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isOptimumPartLoadRatioDefaulted();
}

bool ChillerElectricEIR::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

void ChillerElectricEIR::resetOptimumPartLoadRatio() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetOptimumPartLoadRatio();
}

double ChillerElectricEIR::minimumUnloadingRatio() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->minimumUnloadingRatio();
}

bool ChillerElectricEIR::isMinimumUnloadingRatioDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isMinimumUnloadingRatioDefaulted();
}

bool ChillerElectricEIR::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setMinimumUnloadingRatio(minimumUnloadingRatio);
}

void ChillerElectricEIR::resetMinimumUnloadingRatio() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetMinimumUnloadingRatio();
}

std::string ChillerElectricEIR::condenserType() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->condenserType();
}

bool ChillerElectricEIR::isCondenserTypeDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isCondenserTypeDefaulted();
}

bool ChillerElectricEIR::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setCondenserType(condenserType);
}

void ChillerElectricEIR::resetCondenserType() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetCondenserType();
}

double ChillerElectricEIR::condenserFanPowerRatio() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->condenserFanPowerRatio();
}

bool ChillerElectricEIR::isCondenserFanPowerRatioDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isCondenserFanPowerRatioDefaulted();
}

bool ChillerElectricEIR::setCondenserFanPowerRatio(double condenserFanPowerRatio) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setCondenserFanPowerRatio(condenserFanPowerRatio);
}

void ChillerElectricEIR::resetCondenserFanPowerRatio() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetCondenserFanPowerRatio();
}

double ChillerElectricEIR::fractionofCompressorElectricConsumptionRejectedbyCondenser() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->fractionofCompressorElectricConsumptionRejectedbyCondenser();
}

bool ChillerElectricEIR::isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted();
}

bool ChillerElectricEIR::setFractionofCompressorElectricConsumptionRejectedbyCondenser(
  double fractionofCompressorElectricConsumptionRejectedbyCondenser) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setFractionofCompressorElectricConsumptionRejectedbyCondenser(
    fractionofCompressorElectricConsumptionRejectedbyCondenser);
}

void ChillerElectricEIR::resetFractionofCompressorElectricConsumptionRejectedbyCondenser() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetFractionofCompressorElectricConsumptionRejectedbyCondenser();
}

double ChillerElectricEIR::leavingChilledWaterLowerTemperatureLimit() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->leavingChilledWaterLowerTemperatureLimit();
}

bool ChillerElectricEIR::isLeavingChilledWaterLowerTemperatureLimitDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isLeavingChilledWaterLowerTemperatureLimitDefaulted();
}

bool ChillerElectricEIR::setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setLeavingChilledWaterLowerTemperatureLimit(leavingChilledWaterLowerTemperatureLimit);
}

void ChillerElectricEIR::resetLeavingChilledWaterLowerTemperatureLimit() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetLeavingChilledWaterLowerTemperatureLimit();
}

std::string ChillerElectricEIR::chillerFlowMode() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->chillerFlowMode();
}

bool ChillerElectricEIR::isChillerFlowModeDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isChillerFlowModeDefaulted();
}

bool ChillerElectricEIR::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setChillerFlowMode(chillerFlowMode);
}

void ChillerElectricEIR::resetChillerFlowMode() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetChillerFlowMode();
}

boost::optional<double> ChillerElectricEIR::designHeatRecoveryWaterFlowRate() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->designHeatRecoveryWaterFlowRate();
}

bool ChillerElectricEIR::isDesignHeatRecoveryWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isDesignHeatRecoveryWaterFlowRateAutosized();
}

bool ChillerElectricEIR::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
}

void ChillerElectricEIR::autosizeDesignHeatRecoveryWaterFlowRate() {
  getImpl<detail::ChillerElectricEIR_Impl>()->autosizeDesignHeatRecoveryWaterFlowRate();
}

double ChillerElectricEIR::sizingFactor() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->sizingFactor();
}

bool ChillerElectricEIR::isSizingFactorDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isSizingFactorDefaulted();
}

bool ChillerElectricEIR::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setSizingFactor(sizingFactor);
}

void ChillerElectricEIR::resetSizingFactor() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetSizingFactor();
}

double ChillerElectricEIR::basinHeaterCapacity() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->basinHeaterCapacity();
}

bool ChillerElectricEIR::isBasinHeaterCapacityDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isBasinHeaterCapacityDefaulted();
}

bool ChillerElectricEIR::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

void ChillerElectricEIR::resetBasinHeaterCapacity() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetBasinHeaterCapacity();
}

double ChillerElectricEIR::basinHeaterSetpointTemperature() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->basinHeaterSetpointTemperature();
}

bool ChillerElectricEIR::isBasinHeaterSetpointTemperatureDefaulted() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
}

bool ChillerElectricEIR::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

void ChillerElectricEIR::resetBasinHeaterSetpointTemperature() {
  getImpl<detail::ChillerElectricEIR_Impl>()->resetBasinHeaterSetpointTemperature();
}

double ChillerElectricEIR::condenserHeatRecoveryRelativeCapacityFraction() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->condenserHeatRecoveryRelativeCapacityFraction();
}

bool ChillerElectricEIR::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setCondenserHeatRecoveryRelativeCapacityFraction(
    condenserHeatRecoveryRelativeCapacityFraction);
}

std::string ChillerElectricEIR::endUseSubcategory() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->endUseSubcategory();
}

bool ChillerElectricEIR::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

std::string ChillerElectricEIR::condenserFlowControl() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->condenserFlowControl();
}

bool ChillerElectricEIR::setCondenserFlowControl(const std::string& condenserFlowControl) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setCondenserFlowControl(condenserFlowControl);
}

double ChillerElectricEIR::condenserMinimumFlowFraction() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->condenserMinimumFlowFraction();
}

bool ChillerElectricEIR::setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setCondenserMinimumFlowFraction(condenserMinimumFlowFraction);
}

double ChillerElectricEIR::thermosiphonMinimumTemperatureDifference() const {
  return getImpl<detail::ChillerElectricEIR_Impl>()->thermosiphonMinimumTemperatureDifference();
}

bool ChillerElectricEIR::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return getImpl<detail::ChillerElectricEIR_Impl>()->setThermosiphonMinimumTemperatureDifference(thermosiphonMinimumTemperatureDifference);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ChillerElectricEIR_Impl::referenceCapacity() const {
  return getDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCapacity, true);
}

bool ChillerElectricEIR_Impl::isReferenceCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_EIRFields::ReferenceCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricEIR_Impl::setReferenceCapacity(boost::optional<double> referenceCapacity) {
  bool result = false;
  if (referenceCapacity) {
    result = setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCapacity, *referenceCapacity);
  }
  return result;
}

bool ChillerElectricEIR_Impl::setReferenceCapacity(double referenceCapacity) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCapacity, referenceCapacity);
}

void ChillerElectricEIR_Impl::autosizeReferenceCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceCapacity, "Autosize"));
}

double ChillerElectricEIR_Impl::referenceCOP() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::setReferenceCOP(double referenceCOP) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCOP, referenceCOP);
}

double ChillerElectricEIR_Impl::referenceLeavingChilledWaterTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::ReferenceLeavingChilledWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isReferenceLeavingChilledWaterTemperatureDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::ReferenceLeavingChilledWaterTemperature);
}

bool ChillerElectricEIR_Impl::setReferenceLeavingChilledWaterTemperature(double referenceLeavingChilledWaterTemperature) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceLeavingChilledWaterTemperature, referenceLeavingChilledWaterTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricEIR_Impl::resetReferenceLeavingChilledWaterTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceLeavingChilledWaterTemperature, ""));
}

double ChillerElectricEIR_Impl::referenceEnteringCondenserFluidTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::ReferenceEnteringCondenserFluidTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isReferenceEnteringCondenserFluidTemperatureDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::ReferenceEnteringCondenserFluidTemperature);
}

bool ChillerElectricEIR_Impl::setReferenceEnteringCondenserFluidTemperature(double referenceEnteringCondenserFluidTemperature) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceEnteringCondenserFluidTemperature, referenceEnteringCondenserFluidTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricEIR_Impl::resetReferenceEnteringCondenserFluidTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceEnteringCondenserFluidTemperature, ""));
}

boost::optional<double> ChillerElectricEIR_Impl::referenceChilledWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, true);
}

bool ChillerElectricEIR_Impl::isReferenceChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricEIR_Impl::setReferenceChilledWaterFlowRate(boost::optional<double> referenceChilledWaterFlowRate) {
  bool result = false;
  if (referenceChilledWaterFlowRate) {
    result = setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, *referenceChilledWaterFlowRate);
  }
  return result;
}

bool ChillerElectricEIR_Impl::setReferenceChilledWaterFlowRate(double referenceChilledWaterFlowRate) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, referenceChilledWaterFlowRate);
}

void ChillerElectricEIR_Impl::resetReferenceChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, ""));
}

void ChillerElectricEIR_Impl::autosizeReferenceChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, "Autosize"));
}

boost::optional<double> ChillerElectricEIR_Impl::referenceCondenserFluidFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, true);
}

bool ChillerElectricEIR_Impl::isReferenceCondenserFluidFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricEIR_Impl::setReferenceCondenserFluidFlowRate(boost::optional<double> referenceCondenserFluidFlowRate) {
  bool result = false;
  if (referenceCondenserFluidFlowRate) {
    result = setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, *referenceCondenserFluidFlowRate);
  }
  return result;
}

bool ChillerElectricEIR_Impl::setReferenceCondenserFluidFlowRate(double referenceCondenserFluidFlowRate) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, referenceCondenserFluidFlowRate);
}

void ChillerElectricEIR_Impl::resetReferenceCondenserFluidFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, ""));
}

void ChillerElectricEIR_Impl::autosizeReferenceCondenserFluidFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, "Autosize"));
}

double ChillerElectricEIR_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isMinimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::MinimumPartLoadRatio);
}

bool ChillerElectricEIR_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

void ChillerElectricEIR_Impl::resetMinimumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::MinimumPartLoadRatio, ""));
}

double ChillerElectricEIR_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isMaximumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::MaximumPartLoadRatio);
}

bool ChillerElectricEIR_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

void ChillerElectricEIR_Impl::resetMaximumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::MaximumPartLoadRatio, ""));
}

double ChillerElectricEIR_Impl::optimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::OptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isOptimumPartLoadRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::OptimumPartLoadRatio);
}

bool ChillerElectricEIR_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::OptimumPartLoadRatio, optimumPartLoadRatio);
}

void ChillerElectricEIR_Impl::resetOptimumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::OptimumPartLoadRatio, ""));
}

double ChillerElectricEIR_Impl::minimumUnloadingRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::MinimumUnloadingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isMinimumUnloadingRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::MinimumUnloadingRatio);
}

bool ChillerElectricEIR_Impl::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::MinimumUnloadingRatio, minimumUnloadingRatio);
}

void ChillerElectricEIR_Impl::resetMinimumUnloadingRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::MinimumUnloadingRatio, ""));
}

std::string ChillerElectricEIR_Impl::condenserType() const {
  const auto value = getString(openstudio::Chiller_Electric_EIRFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isCondenserTypeDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::CondenserType);
}

bool ChillerElectricEIR_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Chiller_Electric_EIRFields::CondenserType, condenserType);
}

void ChillerElectricEIR_Impl::resetCondenserType() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::CondenserType, ""));
}

double ChillerElectricEIR_Impl::condenserFanPowerRatio() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::CondenserFanPowerRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isCondenserFanPowerRatioDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::CondenserFanPowerRatio);
}

bool ChillerElectricEIR_Impl::setCondenserFanPowerRatio(double condenserFanPowerRatio) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::CondenserFanPowerRatio, condenserFanPowerRatio);
}

void ChillerElectricEIR_Impl::resetCondenserFanPowerRatio() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::CondenserFanPowerRatio, ""));
}

double ChillerElectricEIR_Impl::fractionofCompressorElectricConsumptionRejectedbyCondenser() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser);
}

bool ChillerElectricEIR_Impl::setFractionofCompressorElectricConsumptionRejectedbyCondenser(
  double fractionofCompressorElectricConsumptionRejectedbyCondenser) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser,
                   fractionofCompressorElectricConsumptionRejectedbyCondenser);
}

void ChillerElectricEIR_Impl::resetFractionofCompressorElectricConsumptionRejectedbyCondenser() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, ""));
}

double ChillerElectricEIR_Impl::leavingChilledWaterLowerTemperatureLimit() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::LeavingChilledWaterLowerTemperatureLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isLeavingChilledWaterLowerTemperatureLimitDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::LeavingChilledWaterLowerTemperatureLimit);
}

bool ChillerElectricEIR_Impl::setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit) {
  const bool result = setDouble(openstudio::Chiller_Electric_EIRFields::LeavingChilledWaterLowerTemperatureLimit,
                                leavingChilledWaterLowerTemperatureLimit);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricEIR_Impl::resetLeavingChilledWaterLowerTemperatureLimit() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::LeavingChilledWaterLowerTemperatureLimit, ""));
}

std::string ChillerElectricEIR_Impl::chillerFlowMode() const {
  const auto value = getString(openstudio::Chiller_Electric_EIRFields::ChillerFlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isChillerFlowModeDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::ChillerFlowMode);
}

bool ChillerElectricEIR_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  if (openstudio::istringEqual(chillerFlowMode, "VariableFlow")) {
    return setString(openstudio::Chiller_Electric_EIRFields::ChillerFlowMode, "LeavingSetpointModulated");
  }
  return setString(openstudio::Chiller_Electric_EIRFields::ChillerFlowMode, chillerFlowMode);
}

void ChillerElectricEIR_Impl::resetChillerFlowMode() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::ChillerFlowMode, ""));
}

boost::optional<double> ChillerElectricEIR_Impl::designHeatRecoveryWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate, true);
}

bool ChillerElectricEIR_Impl::isDesignHeatRecoveryWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricEIR_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
}

void ChillerElectricEIR_Impl::autosizeDesignHeatRecoveryWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate, "Autosize"));
}

double ChillerElectricEIR_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::SizingFactor);
}

bool ChillerElectricEIR_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::SizingFactor, sizingFactor);
}

void ChillerElectricEIR_Impl::resetSizingFactor() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::SizingFactor, ""));
}

double ChillerElectricEIR_Impl::basinHeaterCapacity() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::BasinHeaterCapacity, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isBasinHeaterCapacityDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::BasinHeaterCapacity);
}

bool ChillerElectricEIR_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::BasinHeaterCapacity, basinHeaterCapacity);
}

void ChillerElectricEIR_Impl::resetBasinHeaterCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::BasinHeaterCapacity, ""));
}

double ChillerElectricEIR_Impl::basinHeaterSetpointTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::BasinHeaterSetpointTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_EIRFields::BasinHeaterSetpointTemperature);
}

bool ChillerElectricEIR_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
}

void ChillerElectricEIR_Impl::resetBasinHeaterSetpointTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_EIRFields::BasinHeaterSetpointTemperature, ""));
}

double ChillerElectricEIR_Impl::condenserHeatRecoveryRelativeCapacityFraction() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::CondenserHeatRecoveryRelativeCapacityFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::CondenserHeatRecoveryRelativeCapacityFraction,
                   condenserHeatRecoveryRelativeCapacityFraction);
}

std::string ChillerElectricEIR_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Chiller_Electric_EIRFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return setString(openstudio::Chiller_Electric_EIRFields::EndUseSubcategory, endUseSubcategory);
}

std::string ChillerElectricEIR_Impl::condenserFlowControl() const {
  const auto value = getString(openstudio::Chiller_Electric_EIRFields::CondenserFlowControl, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::setCondenserFlowControl(const std::string& condenserFlowControl) {
  return setString(openstudio::Chiller_Electric_EIRFields::CondenserFlowControl, condenserFlowControl);
}

double ChillerElectricEIR_Impl::condenserMinimumFlowFraction() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::CondenserMinimumFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::CondenserMinimumFlowFraction, condenserMinimumFlowFraction);
}

double ChillerElectricEIR_Impl::thermosiphonMinimumTemperatureDifference() const {
  const auto value = getDouble(openstudio::Chiller_Electric_EIRFields::ThermosiphonMinimumTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricEIR_Impl::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return setDouble(openstudio::Chiller_Electric_EIRFields::ThermosiphonMinimumTemperatureDifference, thermosiphonMinimumTemperatureDifference);
}

std::vector<std::string> ChillerElectricEIR_Impl::condenserTypeValues() const {
  return ChillerElectricEIR::condenserTypeValues();
}

std::vector<std::string> ChillerElectricEIR_Impl::chillerFlowModeValues() const {
  return ChillerElectricEIR::chillerFlowModeValues();
}

std::vector<std::string> ChillerElectricEIR_Impl::condenserFlowControlValues() const {
  return ChillerElectricEIR::condenserFlowControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
