/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ChillerElectric.hpp"
#include "ChillerElectric_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Electric_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerElectric::ChillerElectric(const Model& model) : ModelObject(ChillerElectric::iddObjectType(), model) {}

ChillerElectric::ChillerElectric(std::shared_ptr<detail::ChillerElectric_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ChillerElectric::iddObjectType() {
  return IddObjectType::Chiller_Electric;
}

std::vector<std::string> ChillerElectric::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_ElectricFields::CondenserType);
}

std::vector<std::string> ChillerElectric::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_ElectricFields::ChillerFlowMode);
}

std::string ChillerElectric::condenserType() const {
  return getImpl<detail::ChillerElectric_Impl>()->condenserType();
}

bool ChillerElectric::isCondenserTypeDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isCondenserTypeDefaulted();
}

bool ChillerElectric::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::ChillerElectric_Impl>()->setCondenserType(condenserType);
}

void ChillerElectric::resetCondenserType() {
  getImpl<detail::ChillerElectric_Impl>()->resetCondenserType();
}

boost::optional<double> ChillerElectric::nominalCapacity() const {
  return getImpl<detail::ChillerElectric_Impl>()->nominalCapacity();
}

bool ChillerElectric::isNominalCapacityAutosized() const {
  return getImpl<detail::ChillerElectric_Impl>()->isNominalCapacityAutosized();
}

bool ChillerElectric::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::ChillerElectric_Impl>()->setNominalCapacity(nominalCapacity);
}

void ChillerElectric::autosizeNominalCapacity() {
  getImpl<detail::ChillerElectric_Impl>()->autosizeNominalCapacity();
}

double ChillerElectric::nominalCOP() const {
  return getImpl<detail::ChillerElectric_Impl>()->nominalCOP();
}

bool ChillerElectric::setNominalCOP(double nominalCOP) {
  return getImpl<detail::ChillerElectric_Impl>()->setNominalCOP(nominalCOP);
}

boost::optional<double> ChillerElectric::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerElectric_Impl>()->minimumPartLoadRatio();
}

bool ChillerElectric::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerElectric_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

void ChillerElectric::resetMinimumPartLoadRatio() {
  getImpl<detail::ChillerElectric_Impl>()->resetMinimumPartLoadRatio();
}

boost::optional<double> ChillerElectric::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerElectric_Impl>()->maximumPartLoadRatio();
}

bool ChillerElectric::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerElectric_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

void ChillerElectric::resetMaximumPartLoadRatio() {
  getImpl<detail::ChillerElectric_Impl>()->resetMaximumPartLoadRatio();
}

boost::optional<double> ChillerElectric::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerElectric_Impl>()->optimumPartLoadRatio();
}

bool ChillerElectric::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerElectric_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

void ChillerElectric::resetOptimumPartLoadRatio() {
  getImpl<detail::ChillerElectric_Impl>()->resetOptimumPartLoadRatio();
}

boost::optional<double> ChillerElectric::designCondenserInletTemperature() const {
  return getImpl<detail::ChillerElectric_Impl>()->designCondenserInletTemperature();
}

bool ChillerElectric::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  return getImpl<detail::ChillerElectric_Impl>()->setDesignCondenserInletTemperature(designCondenserInletTemperature);
}

void ChillerElectric::resetDesignCondenserInletTemperature() {
  getImpl<detail::ChillerElectric_Impl>()->resetDesignCondenserInletTemperature();
}

double ChillerElectric::temperatureRiseCoefficient() const {
  return getImpl<detail::ChillerElectric_Impl>()->temperatureRiseCoefficient();
}

bool ChillerElectric::setTemperatureRiseCoefficient(double temperatureRiseCoefficient) {
  return getImpl<detail::ChillerElectric_Impl>()->setTemperatureRiseCoefficient(temperatureRiseCoefficient);
}

boost::optional<double> ChillerElectric::designChilledWaterOutletTemperature() const {
  return getImpl<detail::ChillerElectric_Impl>()->designChilledWaterOutletTemperature();
}

bool ChillerElectric::setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature) {
  return getImpl<detail::ChillerElectric_Impl>()->setDesignChilledWaterOutletTemperature(designChilledWaterOutletTemperature);
}

void ChillerElectric::resetDesignChilledWaterOutletTemperature() {
  getImpl<detail::ChillerElectric_Impl>()->resetDesignChilledWaterOutletTemperature();
}

boost::optional<double> ChillerElectric::designChilledWaterFlowRate() const {
  return getImpl<detail::ChillerElectric_Impl>()->designChilledWaterFlowRate();
}

bool ChillerElectric::isDesignChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectric_Impl>()->isDesignChilledWaterFlowRateAutosized();
}

bool ChillerElectric::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return getImpl<detail::ChillerElectric_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
}

void ChillerElectric::resetDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerElectric_Impl>()->resetDesignChilledWaterFlowRate();
}

void ChillerElectric::autosizeDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerElectric_Impl>()->autosizeDesignChilledWaterFlowRate();
}

boost::optional<double> ChillerElectric::designCondenserFluidFlowRate() const {
  return getImpl<detail::ChillerElectric_Impl>()->designCondenserFluidFlowRate();
}

bool ChillerElectric::isDesignCondenserFluidFlowRateAutosized() const {
  return getImpl<detail::ChillerElectric_Impl>()->isDesignCondenserFluidFlowRateAutosized();
}

bool ChillerElectric::setDesignCondenserFluidFlowRate(double designCondenserFluidFlowRate) {
  return getImpl<detail::ChillerElectric_Impl>()->setDesignCondenserFluidFlowRate(designCondenserFluidFlowRate);
}

void ChillerElectric::resetDesignCondenserFluidFlowRate() {
  getImpl<detail::ChillerElectric_Impl>()->resetDesignCondenserFluidFlowRate();
}

void ChillerElectric::autosizeDesignCondenserFluidFlowRate() {
  getImpl<detail::ChillerElectric_Impl>()->autosizeDesignCondenserFluidFlowRate();
}

boost::optional<double> ChillerElectric::coefficient1ofCapacityRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient1ofCapacityRatioCurve();
}

bool ChillerElectric::setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient1ofCapacityRatioCurve(coefficient1ofCapacityRatioCurve);
}

void ChillerElectric::resetCoefficient1ofCapacityRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient1ofCapacityRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient2ofCapacityRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient2ofCapacityRatioCurve();
}

bool ChillerElectric::setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient2ofCapacityRatioCurve(coefficient2ofCapacityRatioCurve);
}

void ChillerElectric::resetCoefficient2ofCapacityRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient2ofCapacityRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient3ofCapacityRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient3ofCapacityRatioCurve();
}

bool ChillerElectric::setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient3ofCapacityRatioCurve(coefficient3ofCapacityRatioCurve);
}

void ChillerElectric::resetCoefficient3ofCapacityRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient3ofCapacityRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient1ofPowerRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient1ofPowerRatioCurve();
}

bool ChillerElectric::setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient1ofPowerRatioCurve(coefficient1ofPowerRatioCurve);
}

void ChillerElectric::resetCoefficient1ofPowerRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient1ofPowerRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient2ofPowerRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient2ofPowerRatioCurve();
}

bool ChillerElectric::setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient2ofPowerRatioCurve(coefficient2ofPowerRatioCurve);
}

void ChillerElectric::resetCoefficient2ofPowerRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient2ofPowerRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient3ofPowerRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient3ofPowerRatioCurve();
}

bool ChillerElectric::setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient3ofPowerRatioCurve(coefficient3ofPowerRatioCurve);
}

void ChillerElectric::resetCoefficient3ofPowerRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient3ofPowerRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient1ofFullLoadRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient1ofFullLoadRatioCurve();
}

bool ChillerElectric::setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient1ofFullLoadRatioCurve(coefficient1ofFullLoadRatioCurve);
}

void ChillerElectric::resetCoefficient1ofFullLoadRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient1ofFullLoadRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient2ofFullLoadRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient2ofFullLoadRatioCurve();
}

bool ChillerElectric::setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient2ofFullLoadRatioCurve(coefficient2ofFullLoadRatioCurve);
}

void ChillerElectric::resetCoefficient2ofFullLoadRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient2ofFullLoadRatioCurve();
}

boost::optional<double> ChillerElectric::coefficient3ofFullLoadRatioCurve() const {
  return getImpl<detail::ChillerElectric_Impl>()->coefficient3ofFullLoadRatioCurve();
}

bool ChillerElectric::setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve) {
  return getImpl<detail::ChillerElectric_Impl>()->setCoefficient3ofFullLoadRatioCurve(coefficient3ofFullLoadRatioCurve);
}

void ChillerElectric::resetCoefficient3ofFullLoadRatioCurve() {
  getImpl<detail::ChillerElectric_Impl>()->resetCoefficient3ofFullLoadRatioCurve();
}

boost::optional<double> ChillerElectric::chilledWaterOutletTemperatureLowerLimit() const {
  return getImpl<detail::ChillerElectric_Impl>()->chilledWaterOutletTemperatureLowerLimit();
}

bool ChillerElectric::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  return getImpl<detail::ChillerElectric_Impl>()->setChilledWaterOutletTemperatureLowerLimit(chilledWaterOutletTemperatureLowerLimit);
}

void ChillerElectric::resetChilledWaterOutletTemperatureLowerLimit() {
  getImpl<detail::ChillerElectric_Impl>()->resetChilledWaterOutletTemperatureLowerLimit();
}

std::string ChillerElectric::chillerFlowMode() const {
  return getImpl<detail::ChillerElectric_Impl>()->chillerFlowMode();
}

bool ChillerElectric::isChillerFlowModeDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isChillerFlowModeDefaulted();
}

bool ChillerElectric::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerElectric_Impl>()->setChillerFlowMode(chillerFlowMode);
}

void ChillerElectric::resetChillerFlowMode() {
  getImpl<detail::ChillerElectric_Impl>()->resetChillerFlowMode();
}

boost::optional<double> ChillerElectric::designHeatRecoveryWaterFlowRate() const {
  return getImpl<detail::ChillerElectric_Impl>()->designHeatRecoveryWaterFlowRate();
}

bool ChillerElectric::isDesignHeatRecoveryWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerElectric_Impl>()->isDesignHeatRecoveryWaterFlowRateAutosized();
}

bool ChillerElectric::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return getImpl<detail::ChillerElectric_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
}

void ChillerElectric::resetDesignHeatRecoveryWaterFlowRate() {
  getImpl<detail::ChillerElectric_Impl>()->resetDesignHeatRecoveryWaterFlowRate();
}

void ChillerElectric::autosizeDesignHeatRecoveryWaterFlowRate() {
  getImpl<detail::ChillerElectric_Impl>()->autosizeDesignHeatRecoveryWaterFlowRate();
}

double ChillerElectric::sizingFactor() const {
  return getImpl<detail::ChillerElectric_Impl>()->sizingFactor();
}

bool ChillerElectric::isSizingFactorDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isSizingFactorDefaulted();
}

bool ChillerElectric::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerElectric_Impl>()->setSizingFactor(sizingFactor);
}

void ChillerElectric::resetSizingFactor() {
  getImpl<detail::ChillerElectric_Impl>()->resetSizingFactor();
}

double ChillerElectric::basinHeaterCapacity() const {
  return getImpl<detail::ChillerElectric_Impl>()->basinHeaterCapacity();
}

bool ChillerElectric::isBasinHeaterCapacityDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isBasinHeaterCapacityDefaulted();
}

bool ChillerElectric::setBasinHeaterCapacity(double basinHeaterCapacity) {
  return getImpl<detail::ChillerElectric_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
}

void ChillerElectric::resetBasinHeaterCapacity() {
  getImpl<detail::ChillerElectric_Impl>()->resetBasinHeaterCapacity();
}

double ChillerElectric::basinHeaterSetpointTemperature() const {
  return getImpl<detail::ChillerElectric_Impl>()->basinHeaterSetpointTemperature();
}

bool ChillerElectric::isBasinHeaterSetpointTemperatureDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
}

bool ChillerElectric::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  return getImpl<detail::ChillerElectric_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
}

void ChillerElectric::resetBasinHeaterSetpointTemperature() {
  getImpl<detail::ChillerElectric_Impl>()->resetBasinHeaterSetpointTemperature();
}

boost::optional<double> ChillerElectric::condenserHeatRecoveryRelativeCapacityFraction() const {
  return getImpl<detail::ChillerElectric_Impl>()->condenserHeatRecoveryRelativeCapacityFraction();
}

bool ChillerElectric::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
  return getImpl<detail::ChillerElectric_Impl>()->setCondenserHeatRecoveryRelativeCapacityFraction(condenserHeatRecoveryRelativeCapacityFraction);
}

void ChillerElectric::resetCondenserHeatRecoveryRelativeCapacityFraction() {
  getImpl<detail::ChillerElectric_Impl>()->resetCondenserHeatRecoveryRelativeCapacityFraction();
}

std::string ChillerElectric::endUseSubcategory() const {
  return getImpl<detail::ChillerElectric_Impl>()->endUseSubcategory();
}

bool ChillerElectric::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isEndUseSubcategoryDefaulted();
}

bool ChillerElectric::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::ChillerElectric_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void ChillerElectric::resetEndUseSubcategory() {
  getImpl<detail::ChillerElectric_Impl>()->resetEndUseSubcategory();
}

double ChillerElectric::thermosiphonMinimumTemperatureDifference() const {
  return getImpl<detail::ChillerElectric_Impl>()->thermosiphonMinimumTemperatureDifference();
}

bool ChillerElectric::isThermosiphonMinimumTemperatureDifferenceDefaulted() const {
  return getImpl<detail::ChillerElectric_Impl>()->isThermosiphonMinimumTemperatureDifferenceDefaulted();
}

bool ChillerElectric::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return getImpl<detail::ChillerElectric_Impl>()->setThermosiphonMinimumTemperatureDifference(thermosiphonMinimumTemperatureDifference);
}

void ChillerElectric::resetThermosiphonMinimumTemperatureDifference() {
  getImpl<detail::ChillerElectric_Impl>()->resetThermosiphonMinimumTemperatureDifference();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ChillerElectric_Impl::condenserType() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::CondenserType, false)) {
    return *value;
  }
  return "AirCooled";
}

bool ChillerElectric_Impl::isCondenserTypeDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::CondenserType);
}

bool ChillerElectric_Impl::setCondenserType(const std::string& condenserType) {
  return setString(openstudio::Chiller_ElectricFields::CondenserType, condenserType);
}

void ChillerElectric_Impl::resetCondenserType() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::CondenserType, ""));
}

boost::optional<double> ChillerElectric_Impl::nominalCapacity() const {
  return getDouble(openstudio::Chiller_ElectricFields::NominalCapacity, true);
}

bool ChillerElectric_Impl::isNominalCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::NominalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerElectric_Impl::setNominalCapacity(double nominalCapacity) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::NominalCapacity, nominalCapacity);
  return result;
}

void ChillerElectric_Impl::autosizeNominalCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::NominalCapacity, "autosize"));
}

double ChillerElectric_Impl::nominalCOP() const {
  const auto value = getDouble(openstudio::Chiller_ElectricFields::NominalCOP, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectric_Impl::setNominalCOP(double nominalCOP) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::NominalCOP, nominalCOP);
  return result;
}

boost::optional<double> ChillerElectric_Impl::minimumPartLoadRatio() const {
  return getDouble(openstudio::Chiller_ElectricFields::MinimumPartLoadRatio, true);
}

bool ChillerElectric_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::MinimumPartLoadRatio, minimumPartLoadRatio);
  return result;
}

void ChillerElectric_Impl::resetMinimumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::MinimumPartLoadRatio, ""));
}

boost::optional<double> ChillerElectric_Impl::maximumPartLoadRatio() const {
  return getDouble(openstudio::Chiller_ElectricFields::MaximumPartLoadRatio, true);
}

bool ChillerElectric_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::MaximumPartLoadRatio, maximumPartLoadRatio);
  return result;
}

void ChillerElectric_Impl::resetMaximumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::MaximumPartLoadRatio, ""));
}

boost::optional<double> ChillerElectric_Impl::optimumPartLoadRatio() const {
  return getDouble(openstudio::Chiller_ElectricFields::OptimumPartLoadRatio, true);
}

bool ChillerElectric_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::OptimumPartLoadRatio, optimumPartLoadRatio);
  return result;
}

void ChillerElectric_Impl::resetOptimumPartLoadRatio() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::OptimumPartLoadRatio, ""));
}

boost::optional<double> ChillerElectric_Impl::designCondenserInletTemperature() const {
  return getDouble(openstudio::Chiller_ElectricFields::DesignCondenserInletTemperature, true);
}

bool ChillerElectric_Impl::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::DesignCondenserInletTemperature, designCondenserInletTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetDesignCondenserInletTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignCondenserInletTemperature, ""));
}

double ChillerElectric_Impl::temperatureRiseCoefficient() const {
  const auto value = getDouble(openstudio::Chiller_ElectricFields::TemperatureRiseCoefficient, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectric_Impl::setTemperatureRiseCoefficient(double temperatureRiseCoefficient) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::TemperatureRiseCoefficient, temperatureRiseCoefficient);
  return result;
}

boost::optional<double> ChillerElectric_Impl::designChilledWaterOutletTemperature() const {
  return getDouble(openstudio::Chiller_ElectricFields::DesignChilledWaterOutletTemperature, true);
}

bool ChillerElectric_Impl::setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::DesignChilledWaterOutletTemperature, designChilledWaterOutletTemperature);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetDesignChilledWaterOutletTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignChilledWaterOutletTemperature, ""));
}

boost::optional<double> ChillerElectric_Impl::designChilledWaterFlowRate() const {
  return getDouble(openstudio::Chiller_ElectricFields::DesignChilledWaterFlowRate, true);
}

bool ChillerElectric_Impl::isDesignChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::DesignChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerElectric_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
  return result;
}

void ChillerElectric_Impl::resetDesignChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignChilledWaterFlowRate, ""));
}

void ChillerElectric_Impl::autosizeDesignChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignChilledWaterFlowRate, "autosize"));
}

boost::optional<double> ChillerElectric_Impl::designCondenserFluidFlowRate() const {
  return getDouble(openstudio::Chiller_ElectricFields::DesignCondenserFluidFlowRate, true);
}

bool ChillerElectric_Impl::isDesignCondenserFluidFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::DesignCondenserFluidFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerElectric_Impl::setDesignCondenserFluidFlowRate(double designCondenserFluidFlowRate) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::DesignCondenserFluidFlowRate, designCondenserFluidFlowRate);
  return result;
}

void ChillerElectric_Impl::resetDesignCondenserFluidFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignCondenserFluidFlowRate, ""));
}

void ChillerElectric_Impl::autosizeDesignCondenserFluidFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignCondenserFluidFlowRate, "autosize"));
}

boost::optional<double> ChillerElectric_Impl::coefficient1ofCapacityRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient1ofCapacityRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient1ofCapacityRatioCurve, coefficient1ofCapacityRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient1ofCapacityRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient1ofCapacityRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient2ofCapacityRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient2ofCapacityRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient2ofCapacityRatioCurve, coefficient2ofCapacityRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient2ofCapacityRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient2ofCapacityRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient3ofCapacityRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient3ofCapacityRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient3ofCapacityRatioCurve, coefficient3ofCapacityRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient3ofCapacityRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient3ofCapacityRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient1ofPowerRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient1ofPowerRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient1ofPowerRatioCurve, coefficient1ofPowerRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient1ofPowerRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient1ofPowerRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient2ofPowerRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient2ofPowerRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient2ofPowerRatioCurve, coefficient2ofPowerRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient2ofPowerRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient2ofPowerRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient3ofPowerRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient3ofPowerRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient3ofPowerRatioCurve, coefficient3ofPowerRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient3ofPowerRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient3ofPowerRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient1ofFullLoadRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient1ofFullLoadRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient1ofFullLoadRatioCurve, coefficient1ofFullLoadRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient1ofFullLoadRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient1ofFullLoadRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient2ofFullLoadRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient2ofFullLoadRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient2ofFullLoadRatioCurve, coefficient2ofFullLoadRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient2ofFullLoadRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient2ofFullLoadRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::coefficient3ofFullLoadRatioCurve() const {
  return getDouble(openstudio::Chiller_ElectricFields::Coefficient3ofFullLoadRatioCurve, true);
}

bool ChillerElectric_Impl::setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::Coefficient3ofFullLoadRatioCurve, coefficient3ofFullLoadRatioCurve);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetCoefficient3ofFullLoadRatioCurve() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::Coefficient3ofFullLoadRatioCurve, ""));
}

boost::optional<double> ChillerElectric_Impl::chilledWaterOutletTemperatureLowerLimit() const {
  return getDouble(openstudio::Chiller_ElectricFields::ChilledWaterOutletTemperatureLowerLimit, true);
}

bool ChillerElectric_Impl::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::ChilledWaterOutletTemperatureLowerLimit, chilledWaterOutletTemperatureLowerLimit);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetChilledWaterOutletTemperatureLowerLimit() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::ChilledWaterOutletTemperatureLowerLimit, ""));
}

std::string ChillerElectric_Impl::chillerFlowMode() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::ChillerFlowMode, false)) {
    return *value;
  }
  return "NotModulated";
}

bool ChillerElectric_Impl::isChillerFlowModeDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::ChillerFlowMode);
}

bool ChillerElectric_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  return setString(openstudio::Chiller_ElectricFields::ChillerFlowMode, chillerFlowMode);
}

void ChillerElectric_Impl::resetChillerFlowMode() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::ChillerFlowMode, ""));
}

boost::optional<double> ChillerElectric_Impl::designHeatRecoveryWaterFlowRate() const {
  return getDouble(openstudio::Chiller_ElectricFields::DesignHeatRecoveryWaterFlowRate, true);
}

bool ChillerElectric_Impl::isDesignHeatRecoveryWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::DesignHeatRecoveryWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerElectric_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
  return result;
}

void ChillerElectric_Impl::resetDesignHeatRecoveryWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignHeatRecoveryWaterFlowRate, ""));
}

void ChillerElectric_Impl::autosizeDesignHeatRecoveryWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::DesignHeatRecoveryWaterFlowRate, "autosize"));
}

double ChillerElectric_Impl::sizingFactor() const {
  if (auto value = getDouble(openstudio::Chiller_ElectricFields::SizingFactor, false)) {
    return *value;
  }
  return 1.0;
}

bool ChillerElectric_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::SizingFactor);
}

bool ChillerElectric_Impl::setSizingFactor(double sizingFactor) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::SizingFactor, sizingFactor);
  return result;
}

void ChillerElectric_Impl::resetSizingFactor() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::SizingFactor, ""));
}

double ChillerElectric_Impl::basinHeaterCapacity() const {
  if (auto value = getDouble(openstudio::Chiller_ElectricFields::BasinHeaterCapacity, false)) {
    return *value;
  }
  return 0.0;
}

bool ChillerElectric_Impl::isBasinHeaterCapacityDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::BasinHeaterCapacity);
}

bool ChillerElectric_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::BasinHeaterCapacity, basinHeaterCapacity);
  return result;
}

void ChillerElectric_Impl::resetBasinHeaterCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::BasinHeaterCapacity, ""));
}

double ChillerElectric_Impl::basinHeaterSetpointTemperature() const {
  if (auto value = getDouble(openstudio::Chiller_ElectricFields::BasinHeaterSetpointTemperature, false)) {
    return *value;
  }
  return 2.0;
}

bool ChillerElectric_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::BasinHeaterSetpointTemperature);
}

bool ChillerElectric_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
  const bool result = setDouble(openstudio::Chiller_ElectricFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
  return result;
}

void ChillerElectric_Impl::resetBasinHeaterSetpointTemperature() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::BasinHeaterSetpointTemperature, ""));
}

boost::optional<double> ChillerElectric_Impl::condenserHeatRecoveryRelativeCapacityFraction() const {
  return getDouble(openstudio::Chiller_ElectricFields::CondenserHeatRecoveryRelativeCapacityFraction, true);
}

bool ChillerElectric_Impl::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
  const bool result =
    setDouble(openstudio::Chiller_ElectricFields::CondenserHeatRecoveryRelativeCapacityFraction, condenserHeatRecoveryRelativeCapacityFraction);
  return result;
}

void ChillerElectric_Impl::resetCondenserHeatRecoveryRelativeCapacityFraction() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::CondenserHeatRecoveryRelativeCapacityFraction, ""));
}

std::string ChillerElectric_Impl::endUseSubcategory() const {
  if (auto value = getString(openstudio::Chiller_ElectricFields::EndUseSubcategory, false)) {
    return *value;
  }
  return "General";
}

bool ChillerElectric_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::EndUseSubcategory);
}

bool ChillerElectric_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Chiller_ElectricFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ChillerElectric_Impl::resetEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::EndUseSubcategory, ""));
}

double ChillerElectric_Impl::thermosiphonMinimumTemperatureDifference() const {
  if (auto value = getDouble(openstudio::Chiller_ElectricFields::ThermosiphonMinimumTemperatureDifference, false)) {
    return *value;
  }
  return 0.0;
}

bool ChillerElectric_Impl::isThermosiphonMinimumTemperatureDifferenceDefaulted() const {
  return isEmpty(openstudio::Chiller_ElectricFields::ThermosiphonMinimumTemperatureDifference);
}

bool ChillerElectric_Impl::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  const bool result =
    setDouble(openstudio::Chiller_ElectricFields::ThermosiphonMinimumTemperatureDifference, thermosiphonMinimumTemperatureDifference);
  return result;
}

void ChillerElectric_Impl::resetThermosiphonMinimumTemperatureDifference() {
  OS_ASSERT(setString(openstudio::Chiller_ElectricFields::ThermosiphonMinimumTemperatureDifference, ""));
}

std::vector<std::string> ChillerElectric_Impl::condenserTypeValues() const {
  return ChillerElectric::condenserTypeValues();
}

std::vector<std::string> ChillerElectric_Impl::chillerFlowModeValues() const {
  return ChillerElectric::chillerFlowModeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
