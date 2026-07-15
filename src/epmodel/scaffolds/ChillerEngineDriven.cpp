/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ChillerEngineDriven.hpp"
#include "ChillerEngineDriven_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_EngineDriven_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ChillerEngineDriven::ChillerEngineDriven(const Model& model) : ModelObject(ChillerEngineDriven::iddObjectType(), model) {}

  ChillerEngineDriven::ChillerEngineDriven(std::shared_ptr<detail::ChillerEngineDriven_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ChillerEngineDriven::iddObjectType() {
    return IddObjectType::Chiller_EngineDriven;
  }

  std::vector<std::string> ChillerEngineDriven::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_EngineDrivenFields::CondenserType);
  }

  std::vector<std::string> ChillerEngineDriven::chillerFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_EngineDrivenFields::ChillerFlowMode);
  }

  std::vector<std::string> ChillerEngineDriven::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_EngineDrivenFields::FuelType);
  }

  std::string ChillerEngineDriven::condenserType() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->condenserType();
  }

  bool ChillerEngineDriven::isCondenserTypeDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isCondenserTypeDefaulted();
  }

  bool ChillerEngineDriven::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCondenserType(condenserType);
  }

  void ChillerEngineDriven::resetCondenserType() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCondenserType();
  }

  boost::optional<double> ChillerEngineDriven::nominalCapacity() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->nominalCapacity();
  }

  bool ChillerEngineDriven::isNominalCapacityAutosized() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isNominalCapacityAutosized();
  }

  bool ChillerEngineDriven::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void ChillerEngineDriven::autosizeNominalCapacity() {
    getImpl<detail::ChillerEngineDriven_Impl>()->autosizeNominalCapacity();
  }

  double ChillerEngineDriven::nominalCOP() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->nominalCOP();
  }

  bool ChillerEngineDriven::setNominalCOP(double nominalCOP) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setNominalCOP(nominalCOP);
  }

  boost::optional<double> ChillerEngineDriven::minimumPartLoadRatio() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->minimumPartLoadRatio();
  }

  bool ChillerEngineDriven::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  void ChillerEngineDriven::resetMinimumPartLoadRatio() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetMinimumPartLoadRatio();
  }

  boost::optional<double> ChillerEngineDriven::maximumPartLoadRatio() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->maximumPartLoadRatio();
  }

  bool ChillerEngineDriven::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  void ChillerEngineDriven::resetMaximumPartLoadRatio() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetMaximumPartLoadRatio();
  }

  boost::optional<double> ChillerEngineDriven::optimumPartLoadRatio() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->optimumPartLoadRatio();
  }

  bool ChillerEngineDriven::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  void ChillerEngineDriven::resetOptimumPartLoadRatio() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetOptimumPartLoadRatio();
  }

  boost::optional<double> ChillerEngineDriven::designCondenserInletTemperature() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->designCondenserInletTemperature();
  }

  bool ChillerEngineDriven::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setDesignCondenserInletTemperature(designCondenserInletTemperature);
  }

  void ChillerEngineDriven::resetDesignCondenserInletTemperature() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetDesignCondenserInletTemperature();
  }

  double ChillerEngineDriven::temperatureRiseCoefficient() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->temperatureRiseCoefficient();
  }

  bool ChillerEngineDriven::setTemperatureRiseCoefficient(double temperatureRiseCoefficient) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setTemperatureRiseCoefficient(temperatureRiseCoefficient);
  }

  boost::optional<double> ChillerEngineDriven::designChilledWaterOutletTemperature() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->designChilledWaterOutletTemperature();
  }

  bool ChillerEngineDriven::setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setDesignChilledWaterOutletTemperature(designChilledWaterOutletTemperature);
  }

  void ChillerEngineDriven::resetDesignChilledWaterOutletTemperature() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetDesignChilledWaterOutletTemperature();
  }

  boost::optional<double> ChillerEngineDriven::designChilledWaterFlowRate() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->designChilledWaterFlowRate();
  }

  bool ChillerEngineDriven::isDesignChilledWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isDesignChilledWaterFlowRateAutosized();
  }

  bool ChillerEngineDriven::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
  }

  void ChillerEngineDriven::resetDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetDesignChilledWaterFlowRate();
  }

  void ChillerEngineDriven::autosizeDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerEngineDriven_Impl>()->autosizeDesignChilledWaterFlowRate();
  }

  boost::optional<double> ChillerEngineDriven::designCondenserWaterFlowRate() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->designCondenserWaterFlowRate();
  }

  bool ChillerEngineDriven::isDesignCondenserWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isDesignCondenserWaterFlowRateAutosized();
  }

  bool ChillerEngineDriven::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
  }

  void ChillerEngineDriven::resetDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetDesignCondenserWaterFlowRate();
  }

  void ChillerEngineDriven::autosizeDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerEngineDriven_Impl>()->autosizeDesignCondenserWaterFlowRate();
  }

  boost::optional<double> ChillerEngineDriven::coefficient1ofCapacityRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient1ofCapacityRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient1ofCapacityRatioCurve(coefficient1ofCapacityRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient1ofCapacityRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient1ofCapacityRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient2ofCapacityRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient2ofCapacityRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient2ofCapacityRatioCurve(coefficient2ofCapacityRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient2ofCapacityRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient2ofCapacityRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient3ofCapacityRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient3ofCapacityRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient3ofCapacityRatioCurve(coefficient3ofCapacityRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient3ofCapacityRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient3ofCapacityRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient1ofPowerRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient1ofPowerRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient1ofPowerRatioCurve(coefficient1ofPowerRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient1ofPowerRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient1ofPowerRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient2ofPowerRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient2ofPowerRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient2ofPowerRatioCurve(coefficient2ofPowerRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient2ofPowerRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient2ofPowerRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient3ofPowerRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient3ofPowerRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient3ofPowerRatioCurve(coefficient3ofPowerRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient3ofPowerRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient3ofPowerRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient1ofFullLoadRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient1ofFullLoadRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient1ofFullLoadRatioCurve(coefficient1ofFullLoadRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient1ofFullLoadRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient1ofFullLoadRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient2ofFullLoadRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient2ofFullLoadRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient2ofFullLoadRatioCurve(coefficient2ofFullLoadRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient2ofFullLoadRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient2ofFullLoadRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient3ofFullLoadRatioCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient3ofFullLoadRatioCurve();
  }

  bool ChillerEngineDriven::setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient3ofFullLoadRatioCurve(coefficient3ofFullLoadRatioCurve);
  }

  void ChillerEngineDriven::resetCoefficient3ofFullLoadRatioCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient3ofFullLoadRatioCurve();
  }

  boost::optional<double> ChillerEngineDriven::chilledWaterOutletTemperatureLowerLimit() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->chilledWaterOutletTemperatureLowerLimit();
  }

  bool ChillerEngineDriven::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setChilledWaterOutletTemperatureLowerLimit(chilledWaterOutletTemperatureLowerLimit);
  }

  void ChillerEngineDriven::resetChilledWaterOutletTemperatureLowerLimit() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetChilledWaterOutletTemperatureLowerLimit();
  }

  boost::optional<double> ChillerEngineDriven::coefficient1ofUFactorTimesAreaCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient1ofUFactorTimesAreaCurve();
  }

  bool ChillerEngineDriven::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient1ofUFactorTimesAreaCurve(coefficient1ofUFactorTimesAreaCurve);
  }

  void ChillerEngineDriven::resetCoefficient1ofUFactorTimesAreaCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient1ofUFactorTimesAreaCurve();
  }

  boost::optional<double> ChillerEngineDriven::coefficient2ofUFactorTimesAreaCurve() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->coefficient2ofUFactorTimesAreaCurve();
  }

  bool ChillerEngineDriven::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCoefficient2ofUFactorTimesAreaCurve(coefficient2ofUFactorTimesAreaCurve);
  }

  void ChillerEngineDriven::resetCoefficient2ofUFactorTimesAreaCurve() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCoefficient2ofUFactorTimesAreaCurve();
  }

  boost::optional<double> ChillerEngineDriven::maximumExhaustFlowperUnitofPowerOutput() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->maximumExhaustFlowperUnitofPowerOutput();
  }

  bool ChillerEngineDriven::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setMaximumExhaustFlowperUnitofPowerOutput(maximumExhaustFlowperUnitofPowerOutput);
  }

  void ChillerEngineDriven::resetMaximumExhaustFlowperUnitofPowerOutput() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetMaximumExhaustFlowperUnitofPowerOutput();
  }

  boost::optional<double> ChillerEngineDriven::designMinimumExhaustTemperature() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->designMinimumExhaustTemperature();
  }

  bool ChillerEngineDriven::setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setDesignMinimumExhaustTemperature(designMinimumExhaustTemperature);
  }

  void ChillerEngineDriven::resetDesignMinimumExhaustTemperature() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetDesignMinimumExhaustTemperature();
  }

  boost::optional<double> ChillerEngineDriven::fuelHigherHeatingValue() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->fuelHigherHeatingValue();
  }

  bool ChillerEngineDriven::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setFuelHigherHeatingValue(fuelHigherHeatingValue);
  }

  void ChillerEngineDriven::resetFuelHigherHeatingValue() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetFuelHigherHeatingValue();
  }

  boost::optional<double> ChillerEngineDriven::designHeatRecoveryWaterFlowRate() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->designHeatRecoveryWaterFlowRate();
  }

  bool ChillerEngineDriven::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isDesignHeatRecoveryWaterFlowRateDefaulted();
  }

  bool ChillerEngineDriven::isDesignHeatRecoveryWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isDesignHeatRecoveryWaterFlowRateAutosized();
  }

  bool ChillerEngineDriven::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
  }

  void ChillerEngineDriven::resetDesignHeatRecoveryWaterFlowRate() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetDesignHeatRecoveryWaterFlowRate();
  }

  void ChillerEngineDriven::autosizeDesignHeatRecoveryWaterFlowRate() {
    getImpl<detail::ChillerEngineDriven_Impl>()->autosizeDesignHeatRecoveryWaterFlowRate();
  }

  std::string ChillerEngineDriven::chillerFlowMode() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->chillerFlowMode();
  }

  bool ChillerEngineDriven::isChillerFlowModeDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isChillerFlowModeDefaulted();
  }

  bool ChillerEngineDriven::setChillerFlowMode(const std::string& chillerFlowMode) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setChillerFlowMode(chillerFlowMode);
  }

  void ChillerEngineDriven::resetChillerFlowMode() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetChillerFlowMode();
  }

  std::string ChillerEngineDriven::fuelType() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->fuelType();
  }

  bool ChillerEngineDriven::setFuelType(const std::string& fuelType) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setFuelType(fuelType);
  }

  double ChillerEngineDriven::maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode();
  }

  bool ChillerEngineDriven::isMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNodeDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNodeDefaulted();
  }

  bool ChillerEngineDriven::setMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode(
    double maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode(
      maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode);
  }

  void ChillerEngineDriven::resetMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode();
  }

  double ChillerEngineDriven::sizingFactor() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->sizingFactor();
  }

  bool ChillerEngineDriven::isSizingFactorDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isSizingFactorDefaulted();
  }

  bool ChillerEngineDriven::setSizingFactor(double sizingFactor) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setSizingFactor(sizingFactor);
  }

  void ChillerEngineDriven::resetSizingFactor() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetSizingFactor();
  }

  double ChillerEngineDriven::basinHeaterCapacity() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->basinHeaterCapacity();
  }

  bool ChillerEngineDriven::isBasinHeaterCapacityDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isBasinHeaterCapacityDefaulted();
  }

  bool ChillerEngineDriven::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  void ChillerEngineDriven::resetBasinHeaterCapacity() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetBasinHeaterCapacity();
  }

  double ChillerEngineDriven::basinHeaterSetpointTemperature() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->basinHeaterSetpointTemperature();
  }

  bool ChillerEngineDriven::isBasinHeaterSetpointTemperatureDefaulted() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
  }

  bool ChillerEngineDriven::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  void ChillerEngineDriven::resetBasinHeaterSetpointTemperature() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetBasinHeaterSetpointTemperature();
  }

  boost::optional<double> ChillerEngineDriven::condenserHeatRecoveryRelativeCapacityFraction() const {
    return getImpl<detail::ChillerEngineDriven_Impl>()->condenserHeatRecoveryRelativeCapacityFraction();
  }

  bool ChillerEngineDriven::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
    return getImpl<detail::ChillerEngineDriven_Impl>()->setCondenserHeatRecoveryRelativeCapacityFraction(
      condenserHeatRecoveryRelativeCapacityFraction);
  }

  void ChillerEngineDriven::resetCondenserHeatRecoveryRelativeCapacityFraction() {
    getImpl<detail::ChillerEngineDriven_Impl>()->resetCondenserHeatRecoveryRelativeCapacityFraction();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ChillerEngineDriven_Impl::condenserType() const {
      if (auto value = getString(openstudio::Chiller_EngineDrivenFields::CondenserType, false)) {
        return *value;
      }
      return "AirCooled";
    }

    bool ChillerEngineDriven_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::CondenserType);
    }

    bool ChillerEngineDriven_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::Chiller_EngineDrivenFields::CondenserType, condenserType);
    }

    void ChillerEngineDriven_Impl::resetCondenserType() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::CondenserType, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::nominalCapacity() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::NominalCapacity, true);
    }

    bool ChillerEngineDriven_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::Chiller_EngineDrivenFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerEngineDriven_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::NominalCapacity, nominalCapacity);
    }

    void ChillerEngineDriven_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::NominalCapacity, "autosize"));
    }

    double ChillerEngineDriven_Impl::nominalCOP() const {
      const auto value = getDouble(openstudio::Chiller_EngineDrivenFields::NominalCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerEngineDriven_Impl::setNominalCOP(double nominalCOP) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::NominalCOP, nominalCOP);
    }

    boost::optional<double> ChillerEngineDriven_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::MinimumPartLoadRatio, true);
    }

    bool ChillerEngineDriven_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    void ChillerEngineDriven_Impl::resetMinimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::MinimumPartLoadRatio, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::MaximumPartLoadRatio, true);
    }

    bool ChillerEngineDriven_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    void ChillerEngineDriven_Impl::resetMaximumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::MaximumPartLoadRatio, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::OptimumPartLoadRatio, true);
    }

    bool ChillerEngineDriven_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    void ChillerEngineDriven_Impl::resetOptimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::OptimumPartLoadRatio, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::designCondenserInletTemperature() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::DesignCondenserInletTemperature, true);
    }

    bool ChillerEngineDriven_Impl::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::DesignCondenserInletTemperature, designCondenserInletTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetDesignCondenserInletTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignCondenserInletTemperature, ""));
    }

    double ChillerEngineDriven_Impl::temperatureRiseCoefficient() const {
      const auto value = getDouble(openstudio::Chiller_EngineDrivenFields::TemperatureRiseCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerEngineDriven_Impl::setTemperatureRiseCoefficient(double temperatureRiseCoefficient) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::TemperatureRiseCoefficient, temperatureRiseCoefficient);
    }

    boost::optional<double> ChillerEngineDriven_Impl::designChilledWaterOutletTemperature() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterOutletTemperature, true);
    }

    bool ChillerEngineDriven_Impl::setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterOutletTemperature, designChilledWaterOutletTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetDesignChilledWaterOutletTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterOutletTemperature, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::designChilledWaterFlowRate() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterFlowRate, true);
    }

    bool ChillerEngineDriven_Impl::isDesignChilledWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerEngineDriven_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
    }

    void ChillerEngineDriven_Impl::resetDesignChilledWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterFlowRate, ""));
    }

    void ChillerEngineDriven_Impl::autosizeDesignChilledWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignChilledWaterFlowRate, "autosize"));
    }

    boost::optional<double> ChillerEngineDriven_Impl::designCondenserWaterFlowRate() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::DesignCondenserWaterFlowRate, true);
    }

    bool ChillerEngineDriven_Impl::isDesignCondenserWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_EngineDrivenFields::DesignCondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerEngineDriven_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
    }

    void ChillerEngineDriven_Impl::resetDesignCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignCondenserWaterFlowRate, ""));
    }

    void ChillerEngineDriven_Impl::autosizeDesignCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignCondenserWaterFlowRate, "autosize"));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient1ofCapacityRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofCapacityRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofCapacityRatioCurve, coefficient1ofCapacityRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient1ofCapacityRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient1ofCapacityRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient2ofCapacityRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofCapacityRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofCapacityRatioCurve, coefficient2ofCapacityRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient2ofCapacityRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient2ofCapacityRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient3ofCapacityRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient3ofCapacityRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient3ofCapacityRatioCurve, coefficient3ofCapacityRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient3ofCapacityRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient3ofCapacityRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient1ofPowerRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofPowerRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofPowerRatioCurve, coefficient1ofPowerRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient1ofPowerRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient1ofPowerRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient2ofPowerRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofPowerRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofPowerRatioCurve, coefficient2ofPowerRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient2ofPowerRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient2ofPowerRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient3ofPowerRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient3ofPowerRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient3ofPowerRatioCurve, coefficient3ofPowerRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient3ofPowerRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient3ofPowerRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient1ofFullLoadRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofFullLoadRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofFullLoadRatioCurve, coefficient1ofFullLoadRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient1ofFullLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient1ofFullLoadRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient2ofFullLoadRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofFullLoadRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofFullLoadRatioCurve, coefficient2ofFullLoadRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient2ofFullLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient2ofFullLoadRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient3ofFullLoadRatioCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient3ofFullLoadRatioCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient3ofFullLoadRatioCurve, coefficient3ofFullLoadRatioCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient3ofFullLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient3ofFullLoadRatioCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::chilledWaterOutletTemperatureLowerLimit() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::ChilledWaterOutletTemperatureLowerLimit, true);
    }

    bool ChillerEngineDriven_Impl::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
      const bool result =
        setDouble(openstudio::Chiller_EngineDrivenFields::ChilledWaterOutletTemperatureLowerLimit, chilledWaterOutletTemperatureLowerLimit);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetChilledWaterOutletTemperatureLowerLimit() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::ChilledWaterOutletTemperatureLowerLimit, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient1ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofUFactorTimesAreaCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient1ofUFactorTimesAreaCurve, coefficient1ofUFactorTimesAreaCurve);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetCoefficient1ofUFactorTimesAreaCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient1ofUFactorTimesAreaCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::coefficient2ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofUFactorTimesAreaCurve, true);
    }

    bool ChillerEngineDriven_Impl::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::Coefficient2ofUFactorTimesAreaCurve, coefficient2ofUFactorTimesAreaCurve);
    }

    void ChillerEngineDriven_Impl::resetCoefficient2ofUFactorTimesAreaCurve() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::Coefficient2ofUFactorTimesAreaCurve, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::maximumExhaustFlowperUnitofPowerOutput() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::MaximumExhaustFlowperUnitofPowerOutput, true);
    }

    bool ChillerEngineDriven_Impl::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::MaximumExhaustFlowperUnitofPowerOutput, maximumExhaustFlowperUnitofPowerOutput);
    }

    void ChillerEngineDriven_Impl::resetMaximumExhaustFlowperUnitofPowerOutput() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::MaximumExhaustFlowperUnitofPowerOutput, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::designMinimumExhaustTemperature() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::DesignMinimumExhaustTemperature, true);
    }

    bool ChillerEngineDriven_Impl::setDesignMinimumExhaustTemperature(double designMinimumExhaustTemperature) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::DesignMinimumExhaustTemperature, designMinimumExhaustTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetDesignMinimumExhaustTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignMinimumExhaustTemperature, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::fuelHigherHeatingValue() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::FuelHigherHeatingValue, true);
    }

    bool ChillerEngineDriven_Impl::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
      const bool result = setDouble(openstudio::Chiller_EngineDrivenFields::FuelHigherHeatingValue, fuelHigherHeatingValue);
      OS_ASSERT(result);
      return result;
    }

    void ChillerEngineDriven_Impl::resetFuelHigherHeatingValue() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::FuelHigherHeatingValue, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::designHeatRecoveryWaterFlowRate() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate, true);
    }

    bool ChillerEngineDriven_Impl::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate);
    }

    bool ChillerEngineDriven_Impl::isDesignHeatRecoveryWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerEngineDriven_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
    }

    void ChillerEngineDriven_Impl::resetDesignHeatRecoveryWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate, ""));
    }

    void ChillerEngineDriven_Impl::autosizeDesignHeatRecoveryWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::DesignHeatRecoveryWaterFlowRate, "autosize"));
    }

    std::string ChillerEngineDriven_Impl::chillerFlowMode() const {
      if (auto value = getString(openstudio::Chiller_EngineDrivenFields::ChillerFlowMode, false)) {
        return *value;
      }
      return "NotModulated";
    }

    bool ChillerEngineDriven_Impl::isChillerFlowModeDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::ChillerFlowMode);
    }

    bool ChillerEngineDriven_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
      return setString(openstudio::Chiller_EngineDrivenFields::ChillerFlowMode, chillerFlowMode);
    }

    void ChillerEngineDriven_Impl::resetChillerFlowMode() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::ChillerFlowMode, ""));
    }

    std::string ChillerEngineDriven_Impl::fuelType() const {
      const auto value = getString(openstudio::Chiller_EngineDrivenFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerEngineDriven_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Chiller_EngineDrivenFields::FuelType, fuelType);
    }

    double ChillerEngineDriven_Impl::maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode() const {
      if (auto value = getDouble(openstudio::Chiller_EngineDrivenFields::MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode, false)) {
        return *value;
      }
      return 60.0;
    }

    bool ChillerEngineDriven_Impl::isMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNodeDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode);
    }

    bool ChillerEngineDriven_Impl::setMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode(
      double maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode,
                       maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode);
    }

    void ChillerEngineDriven_Impl::resetMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::MaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode, ""));
    }

    double ChillerEngineDriven_Impl::sizingFactor() const {
      if (auto value = getDouble(openstudio::Chiller_EngineDrivenFields::SizingFactor, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ChillerEngineDriven_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::SizingFactor);
    }

    bool ChillerEngineDriven_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::SizingFactor, sizingFactor);
    }

    void ChillerEngineDriven_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::SizingFactor, ""));
    }

    double ChillerEngineDriven_Impl::basinHeaterCapacity() const {
      if (auto value = getDouble(openstudio::Chiller_EngineDrivenFields::BasinHeaterCapacity, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ChillerEngineDriven_Impl::isBasinHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::BasinHeaterCapacity);
    }

    bool ChillerEngineDriven_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::BasinHeaterCapacity, basinHeaterCapacity);
    }

    void ChillerEngineDriven_Impl::resetBasinHeaterCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::BasinHeaterCapacity, ""));
    }

    double ChillerEngineDriven_Impl::basinHeaterSetpointTemperature() const {
      if (auto value = getDouble(openstudio::Chiller_EngineDrivenFields::BasinHeaterSetpointTemperature, false)) {
        return *value;
      }
      return 2.0;
    }

    bool ChillerEngineDriven_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::Chiller_EngineDrivenFields::BasinHeaterSetpointTemperature);
    }

    bool ChillerEngineDriven_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
    }

    void ChillerEngineDriven_Impl::resetBasinHeaterSetpointTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::BasinHeaterSetpointTemperature, ""));
    }

    boost::optional<double> ChillerEngineDriven_Impl::condenserHeatRecoveryRelativeCapacityFraction() const {
      return getDouble(openstudio::Chiller_EngineDrivenFields::CondenserHeatRecoveryRelativeCapacityFraction, true);
    }

    bool ChillerEngineDriven_Impl::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
      return setDouble(openstudio::Chiller_EngineDrivenFields::CondenserHeatRecoveryRelativeCapacityFraction,
                       condenserHeatRecoveryRelativeCapacityFraction);
    }

    void ChillerEngineDriven_Impl::resetCondenserHeatRecoveryRelativeCapacityFraction() {
      OS_ASSERT(setString(openstudio::Chiller_EngineDrivenFields::CondenserHeatRecoveryRelativeCapacityFraction, ""));
    }

    std::vector<std::string> ChillerEngineDriven_Impl::condenserTypeValues() const {
      return openstudio::epmodel::ChillerEngineDriven::condenserTypeValues();
    }

    std::vector<std::string> ChillerEngineDriven_Impl::chillerFlowModeValues() const {
      return openstudio::epmodel::ChillerEngineDriven::chillerFlowModeValues();
    }

    std::vector<std::string> ChillerEngineDriven_Impl::fuelTypeValues() const {
      return openstudio::epmodel::ChillerEngineDriven::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
