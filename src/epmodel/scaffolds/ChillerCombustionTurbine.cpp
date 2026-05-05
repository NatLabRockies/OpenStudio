/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ChillerCombustionTurbine.hpp"
#include "ChillerCombustionTurbine_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_CombustionTurbine_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ChillerCombustionTurbine::ChillerCombustionTurbine(const Model& model) : ModelObject(ChillerCombustionTurbine::iddObjectType(), model) {}

  ChillerCombustionTurbine::ChillerCombustionTurbine(std::shared_ptr<detail::ChillerCombustionTurbine_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ChillerCombustionTurbine::iddObjectType() {
    return IddObjectType::Chiller_CombustionTurbine;
  }

  std::vector<std::string> ChillerCombustionTurbine::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_CombustionTurbineFields::CondenserType);
  }

  std::vector<std::string> ChillerCombustionTurbine::chillerFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_CombustionTurbineFields::ChillerFlowMode);
  }

  std::vector<std::string> ChillerCombustionTurbine::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_CombustionTurbineFields::FuelType);
  }

  std::string ChillerCombustionTurbine::condenserType() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->condenserType();
  }

  bool ChillerCombustionTurbine::isCondenserTypeDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isCondenserTypeDefaulted();
  }

  bool ChillerCombustionTurbine::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCondenserType(condenserType);
  }

  void ChillerCombustionTurbine::resetCondenserType() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCondenserType();
  }

  boost::optional<double> ChillerCombustionTurbine::nominalCapacity() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->nominalCapacity();
  }

  bool ChillerCombustionTurbine::isNominalCapacityAutosized() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isNominalCapacityAutosized();
  }

  bool ChillerCombustionTurbine::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void ChillerCombustionTurbine::autosizeNominalCapacity() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->autosizeNominalCapacity();
  }

  double ChillerCombustionTurbine::nominalCOP() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->nominalCOP();
  }

  bool ChillerCombustionTurbine::setNominalCOP(double nominalCOP) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setNominalCOP(nominalCOP);
  }

  boost::optional<double> ChillerCombustionTurbine::minimumPartLoadRatio() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->minimumPartLoadRatio();
  }

  bool ChillerCombustionTurbine::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  void ChillerCombustionTurbine::resetMinimumPartLoadRatio() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetMinimumPartLoadRatio();
  }

  boost::optional<double> ChillerCombustionTurbine::maximumPartLoadRatio() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->maximumPartLoadRatio();
  }

  bool ChillerCombustionTurbine::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  void ChillerCombustionTurbine::resetMaximumPartLoadRatio() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetMaximumPartLoadRatio();
  }

  boost::optional<double> ChillerCombustionTurbine::optimumPartLoadRatio() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->optimumPartLoadRatio();
  }

  bool ChillerCombustionTurbine::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  void ChillerCombustionTurbine::resetOptimumPartLoadRatio() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetOptimumPartLoadRatio();
  }

  boost::optional<double> ChillerCombustionTurbine::designCondenserInletTemperature() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->designCondenserInletTemperature();
  }

  bool ChillerCombustionTurbine::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setDesignCondenserInletTemperature(designCondenserInletTemperature);
  }

  void ChillerCombustionTurbine::resetDesignCondenserInletTemperature() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetDesignCondenserInletTemperature();
  }

  double ChillerCombustionTurbine::temperatureRiseCoefficient() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->temperatureRiseCoefficient();
  }

  bool ChillerCombustionTurbine::setTemperatureRiseCoefficient(double temperatureRiseCoefficient) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setTemperatureRiseCoefficient(temperatureRiseCoefficient);
  }

  boost::optional<double> ChillerCombustionTurbine::designChilledWaterOutletTemperature() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->designChilledWaterOutletTemperature();
  }

  bool ChillerCombustionTurbine::setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setDesignChilledWaterOutletTemperature(designChilledWaterOutletTemperature);
  }

  void ChillerCombustionTurbine::resetDesignChilledWaterOutletTemperature() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetDesignChilledWaterOutletTemperature();
  }

  boost::optional<double> ChillerCombustionTurbine::designChilledWaterFlowRate() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->designChilledWaterFlowRate();
  }

  bool ChillerCombustionTurbine::isDesignChilledWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isDesignChilledWaterFlowRateAutosized();
  }

  bool ChillerCombustionTurbine::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
  }

  void ChillerCombustionTurbine::resetDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetDesignChilledWaterFlowRate();
  }

  void ChillerCombustionTurbine::autosizeDesignChilledWaterFlowRate() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->autosizeDesignChilledWaterFlowRate();
  }

  boost::optional<double> ChillerCombustionTurbine::designCondenserWaterFlowRate() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->designCondenserWaterFlowRate();
  }

  bool ChillerCombustionTurbine::isDesignCondenserWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isDesignCondenserWaterFlowRateAutosized();
  }

  bool ChillerCombustionTurbine::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
  }

  void ChillerCombustionTurbine::resetDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetDesignCondenserWaterFlowRate();
  }

  void ChillerCombustionTurbine::autosizeDesignCondenserWaterFlowRate() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->autosizeDesignCondenserWaterFlowRate();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofCapacityRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofCapacityRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofCapacityRatioCurve(coefficient1ofCapacityRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofCapacityRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofCapacityRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofCapacityRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofCapacityRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofCapacityRatioCurve(coefficient2ofCapacityRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofCapacityRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofCapacityRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofCapacityRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofCapacityRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofCapacityRatioCurve(coefficient3ofCapacityRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofCapacityRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofCapacityRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofPowerRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofPowerRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofPowerRatioCurve(coefficient1ofPowerRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofPowerRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofPowerRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofPowerRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofPowerRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofPowerRatioCurve(coefficient2ofPowerRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofPowerRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofPowerRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofPowerRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofPowerRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofPowerRatioCurve(coefficient3ofPowerRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofPowerRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofPowerRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofFullLoadRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofFullLoadRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofFullLoadRatioCurve(coefficient1ofFullLoadRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofFullLoadRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofFullLoadRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofFullLoadRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofFullLoadRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofFullLoadRatioCurve(coefficient2ofFullLoadRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofFullLoadRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofFullLoadRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofFullLoadRatioCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofFullLoadRatioCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofFullLoadRatioCurve(coefficient3ofFullLoadRatioCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofFullLoadRatioCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofFullLoadRatioCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::chilledWaterOutletTemperatureLowerLimit() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->chilledWaterOutletTemperatureLowerLimit();
  }

  bool ChillerCombustionTurbine::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setChilledWaterOutletTemperatureLowerLimit(chilledWaterOutletTemperatureLowerLimit);
  }

  void ChillerCombustionTurbine::resetChilledWaterOutletTemperatureLowerLimit() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetChilledWaterOutletTemperatureLowerLimit();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofFuelInputCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofFuelInputCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofFuelInputCurve(double coefficient1ofFuelInputCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofFuelInputCurve(coefficient1ofFuelInputCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofFuelInputCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofFuelInputCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofFuelInputCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofFuelInputCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofFuelInputCurve(double coefficient2ofFuelInputCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofFuelInputCurve(coefficient2ofFuelInputCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofFuelInputCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofFuelInputCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofFuelInputCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofFuelInputCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofFuelInputCurve(double coefficient3ofFuelInputCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofFuelInputCurve(coefficient3ofFuelInputCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofFuelInputCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofFuelInputCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofTemperatureBasedFuelInputCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofTemperatureBasedFuelInputCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofTemperatureBasedFuelInputCurve(double coefficient1ofTemperatureBasedFuelInputCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofTemperatureBasedFuelInputCurve(
      coefficient1ofTemperatureBasedFuelInputCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofTemperatureBasedFuelInputCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofTemperatureBasedFuelInputCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofTemperatureBasedFuelInputCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofTemperatureBasedFuelInputCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofTemperatureBasedFuelInputCurve(double coefficient2ofTemperatureBasedFuelInputCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofTemperatureBasedFuelInputCurve(
      coefficient2ofTemperatureBasedFuelInputCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofTemperatureBasedFuelInputCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofTemperatureBasedFuelInputCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofTemperatureBasedFuelInputCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofTemperatureBasedFuelInputCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofTemperatureBasedFuelInputCurve(double coefficient3ofTemperatureBasedFuelInputCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofTemperatureBasedFuelInputCurve(
      coefficient3ofTemperatureBasedFuelInputCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofTemperatureBasedFuelInputCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofTemperatureBasedFuelInputCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofExhaustFlowCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofExhaustFlowCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofExhaustFlowCurve(double coefficient1ofExhaustFlowCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofExhaustFlowCurve(coefficient1ofExhaustFlowCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofExhaustFlowCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofExhaustFlowCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofExhaustFlowCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofExhaustFlowCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofExhaustFlowCurve(double coefficient2ofExhaustFlowCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofExhaustFlowCurve(coefficient2ofExhaustFlowCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofExhaustFlowCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofExhaustFlowCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofExhaustFlowCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofExhaustFlowCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofExhaustFlowCurve(double coefficient3ofExhaustFlowCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofExhaustFlowCurve(coefficient3ofExhaustFlowCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofExhaustFlowCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofExhaustFlowCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofExhaustGasTemperatureCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofExhaustGasTemperatureCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofExhaustGasTemperatureCurve(double coefficient1ofExhaustGasTemperatureCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofExhaustGasTemperatureCurve(coefficient1ofExhaustGasTemperatureCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofExhaustGasTemperatureCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofExhaustGasTemperatureCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofExhaustGasTemperatureCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofExhaustGasTemperatureCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofExhaustGasTemperatureCurve(double coefficient2ofExhaustGasTemperatureCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofExhaustGasTemperatureCurve(coefficient2ofExhaustGasTemperatureCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofExhaustGasTemperatureCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofExhaustGasTemperatureCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofExhaustGasTemperatureCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofExhaustGasTemperatureCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofExhaustGasTemperatureCurve(double coefficient3ofExhaustGasTemperatureCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofExhaustGasTemperatureCurve(coefficient3ofExhaustGasTemperatureCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofExhaustGasTemperatureCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofExhaustGasTemperatureCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofTemperatureBasedExhaustGasTemperatureCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofTemperatureBasedExhaustGasTemperatureCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve(
    double coefficient1ofTemperatureBasedExhaustGasTemperatureCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve(
      coefficient1ofTemperatureBasedExhaustGasTemperatureCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofTemperatureBasedExhaustGasTemperatureCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofTemperatureBasedExhaustGasTemperatureCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve(
    double coefficient2ofTemperatureBasedExhaustGasTemperatureCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve(
      coefficient2ofTemperatureBasedExhaustGasTemperatureCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofTemperatureBasedExhaustGasTemperatureCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofTemperatureBasedExhaustGasTemperatureCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve(
    double coefficient3ofTemperatureBasedExhaustGasTemperatureCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve(
      coefficient3ofTemperatureBasedExhaustGasTemperatureCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofRecoveryLubeHeatCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofRecoveryLubeHeatCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofRecoveryLubeHeatCurve(double coefficient1ofRecoveryLubeHeatCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofRecoveryLubeHeatCurve(coefficient1ofRecoveryLubeHeatCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofRecoveryLubeHeatCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofRecoveryLubeHeatCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofRecoveryLubeHeatCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofRecoveryLubeHeatCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofRecoveryLubeHeatCurve(double coefficient2ofRecoveryLubeHeatCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofRecoveryLubeHeatCurve(coefficient2ofRecoveryLubeHeatCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofRecoveryLubeHeatCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofRecoveryLubeHeatCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient3ofRecoveryLubeHeatCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient3ofRecoveryLubeHeatCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient3ofRecoveryLubeHeatCurve(double coefficient3ofRecoveryLubeHeatCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient3ofRecoveryLubeHeatCurve(coefficient3ofRecoveryLubeHeatCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient3ofRecoveryLubeHeatCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient3ofRecoveryLubeHeatCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient1ofUFactorTimesAreaCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient1ofUFactorTimesAreaCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient1ofUFactorTimesAreaCurve(coefficient1ofUFactorTimesAreaCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient1ofUFactorTimesAreaCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient1ofUFactorTimesAreaCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::coefficient2ofUFactorTimesAreaCurve() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->coefficient2ofUFactorTimesAreaCurve();
  }

  bool ChillerCombustionTurbine::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCoefficient2ofUFactorTimesAreaCurve(coefficient2ofUFactorTimesAreaCurve);
  }

  void ChillerCombustionTurbine::resetCoefficient2ofUFactorTimesAreaCurve() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCoefficient2ofUFactorTimesAreaCurve();
  }

  boost::optional<double> ChillerCombustionTurbine::gasTurbineEngineCapacity() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->gasTurbineEngineCapacity();
  }

  bool ChillerCombustionTurbine::isGasTurbineEngineCapacityAutosized() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isGasTurbineEngineCapacityAutosized();
  }

  bool ChillerCombustionTurbine::setGasTurbineEngineCapacity(double gasTurbineEngineCapacity) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setGasTurbineEngineCapacity(gasTurbineEngineCapacity);
  }

  void ChillerCombustionTurbine::resetGasTurbineEngineCapacity() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetGasTurbineEngineCapacity();
  }

  void ChillerCombustionTurbine::autosizeGasTurbineEngineCapacity() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->autosizeGasTurbineEngineCapacity();
  }

  boost::optional<double> ChillerCombustionTurbine::maximumExhaustFlowperUnitofPowerOutput() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->maximumExhaustFlowperUnitofPowerOutput();
  }

  bool ChillerCombustionTurbine::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setMaximumExhaustFlowperUnitofPowerOutput(maximumExhaustFlowperUnitofPowerOutput);
  }

  void ChillerCombustionTurbine::resetMaximumExhaustFlowperUnitofPowerOutput() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetMaximumExhaustFlowperUnitofPowerOutput();
  }

  boost::optional<double> ChillerCombustionTurbine::designSteamSaturationTemperature() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->designSteamSaturationTemperature();
  }

  bool ChillerCombustionTurbine::setDesignSteamSaturationTemperature(double designSteamSaturationTemperature) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setDesignSteamSaturationTemperature(designSteamSaturationTemperature);
  }

  void ChillerCombustionTurbine::resetDesignSteamSaturationTemperature() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetDesignSteamSaturationTemperature();
  }

  boost::optional<double> ChillerCombustionTurbine::fuelHigherHeatingValue() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->fuelHigherHeatingValue();
  }

  bool ChillerCombustionTurbine::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setFuelHigherHeatingValue(fuelHigherHeatingValue);
  }

  void ChillerCombustionTurbine::resetFuelHigherHeatingValue() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetFuelHigherHeatingValue();
  }

  boost::optional<double> ChillerCombustionTurbine::designHeatRecoveryWaterFlowRate() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->designHeatRecoveryWaterFlowRate();
  }

  bool ChillerCombustionTurbine::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isDesignHeatRecoveryWaterFlowRateDefaulted();
  }

  bool ChillerCombustionTurbine::isDesignHeatRecoveryWaterFlowRateAutosized() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isDesignHeatRecoveryWaterFlowRateAutosized();
  }

  bool ChillerCombustionTurbine::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
  }

  void ChillerCombustionTurbine::resetDesignHeatRecoveryWaterFlowRate() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetDesignHeatRecoveryWaterFlowRate();
  }

  void ChillerCombustionTurbine::autosizeDesignHeatRecoveryWaterFlowRate() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->autosizeDesignHeatRecoveryWaterFlowRate();
  }

  std::string ChillerCombustionTurbine::chillerFlowMode() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->chillerFlowMode();
  }

  bool ChillerCombustionTurbine::isChillerFlowModeDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isChillerFlowModeDefaulted();
  }

  bool ChillerCombustionTurbine::setChillerFlowMode(const std::string& chillerFlowMode) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setChillerFlowMode(chillerFlowMode);
  }

  void ChillerCombustionTurbine::resetChillerFlowMode() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetChillerFlowMode();
  }

  std::string ChillerCombustionTurbine::fuelType() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->fuelType();
  }

  bool ChillerCombustionTurbine::isFuelTypeDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isFuelTypeDefaulted();
  }

  bool ChillerCombustionTurbine::setFuelType(const std::string& fuelType) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setFuelType(fuelType);
  }

  void ChillerCombustionTurbine::resetFuelType() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetFuelType();
  }

  double ChillerCombustionTurbine::heatRecoveryMaximumTemperature() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->heatRecoveryMaximumTemperature();
  }

  bool ChillerCombustionTurbine::isHeatRecoveryMaximumTemperatureDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isHeatRecoveryMaximumTemperatureDefaulted();
  }

  bool ChillerCombustionTurbine::setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setHeatRecoveryMaximumTemperature(heatRecoveryMaximumTemperature);
  }

  void ChillerCombustionTurbine::resetHeatRecoveryMaximumTemperature() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetHeatRecoveryMaximumTemperature();
  }

  double ChillerCombustionTurbine::sizingFactor() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->sizingFactor();
  }

  bool ChillerCombustionTurbine::isSizingFactorDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isSizingFactorDefaulted();
  }

  bool ChillerCombustionTurbine::setSizingFactor(double sizingFactor) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setSizingFactor(sizingFactor);
  }

  void ChillerCombustionTurbine::resetSizingFactor() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetSizingFactor();
  }

  double ChillerCombustionTurbine::basinHeaterCapacity() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->basinHeaterCapacity();
  }

  bool ChillerCombustionTurbine::isBasinHeaterCapacityDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isBasinHeaterCapacityDefaulted();
  }

  bool ChillerCombustionTurbine::setBasinHeaterCapacity(double basinHeaterCapacity) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setBasinHeaterCapacity(basinHeaterCapacity);
  }

  void ChillerCombustionTurbine::resetBasinHeaterCapacity() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetBasinHeaterCapacity();
  }

  double ChillerCombustionTurbine::basinHeaterSetpointTemperature() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->basinHeaterSetpointTemperature();
  }

  bool ChillerCombustionTurbine::isBasinHeaterSetpointTemperatureDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isBasinHeaterSetpointTemperatureDefaulted();
  }

  bool ChillerCombustionTurbine::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setBasinHeaterSetpointTemperature(basinHeaterSetpointTemperature);
  }

  void ChillerCombustionTurbine::resetBasinHeaterSetpointTemperature() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetBasinHeaterSetpointTemperature();
  }

  boost::optional<double> ChillerCombustionTurbine::condenserHeatRecoveryRelativeCapacityFraction() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->condenserHeatRecoveryRelativeCapacityFraction();
  }

  bool ChillerCombustionTurbine::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setCondenserHeatRecoveryRelativeCapacityFraction(
      condenserHeatRecoveryRelativeCapacityFraction);
  }

  void ChillerCombustionTurbine::resetCondenserHeatRecoveryRelativeCapacityFraction() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetCondenserHeatRecoveryRelativeCapacityFraction();
  }

  double ChillerCombustionTurbine::turbineEngineEfficiency() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->turbineEngineEfficiency();
  }

  bool ChillerCombustionTurbine::isTurbineEngineEfficiencyDefaulted() const {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->isTurbineEngineEfficiencyDefaulted();
  }

  bool ChillerCombustionTurbine::setTurbineEngineEfficiency(double turbineEngineEfficiency) {
    return getImpl<detail::ChillerCombustionTurbine_Impl>()->setTurbineEngineEfficiency(turbineEngineEfficiency);
  }

  void ChillerCombustionTurbine::resetTurbineEngineEfficiency() {
    getImpl<detail::ChillerCombustionTurbine_Impl>()->resetTurbineEngineEfficiency();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ChillerCombustionTurbine_Impl::condenserType() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::CondenserType, false)) {
        return *value;
      }
      return "AirCooled";
    }

    bool ChillerCombustionTurbine_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::CondenserType);
    }

    bool ChillerCombustionTurbine_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::Chiller_CombustionTurbineFields::CondenserType, condenserType);
    }

    void ChillerCombustionTurbine_Impl::resetCondenserType() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::CondenserType, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::nominalCapacity() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::NominalCapacity, true);
    }

    bool ChillerCombustionTurbine_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerCombustionTurbine_Impl::setNominalCapacity(double nominalCapacity) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::NominalCapacity, nominalCapacity);
      return result;
    }

    void ChillerCombustionTurbine_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::NominalCapacity, "autosize"));
    }

    double ChillerCombustionTurbine_Impl::nominalCOP() const {
      const auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::NominalCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerCombustionTurbine_Impl::setNominalCOP(double nominalCOP) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::NominalCOP, nominalCOP);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::minimumPartLoadRatio() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::MinimumPartLoadRatio, true);
    }

    bool ChillerCombustionTurbine_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::MinimumPartLoadRatio, minimumPartLoadRatio);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetMinimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::MinimumPartLoadRatio, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::maximumPartLoadRatio() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::MaximumPartLoadRatio, true);
    }

    bool ChillerCombustionTurbine_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::MaximumPartLoadRatio, maximumPartLoadRatio);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetMaximumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::MaximumPartLoadRatio, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::optimumPartLoadRatio() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::OptimumPartLoadRatio, true);
    }

    bool ChillerCombustionTurbine_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::OptimumPartLoadRatio, optimumPartLoadRatio);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetOptimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::OptimumPartLoadRatio, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::designCondenserInletTemperature() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::DesignCondenserInletTemperature, true);
    }

    bool ChillerCombustionTurbine_Impl::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::DesignCondenserInletTemperature, designCondenserInletTemperature);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetDesignCondenserInletTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignCondenserInletTemperature, ""));
    }

    double ChillerCombustionTurbine_Impl::temperatureRiseCoefficient() const {
      const auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::TemperatureRiseCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerCombustionTurbine_Impl::setTemperatureRiseCoefficient(double temperatureRiseCoefficient) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::TemperatureRiseCoefficient, temperatureRiseCoefficient);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::designChilledWaterOutletTemperature() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterOutletTemperature, true);
    }

    bool ChillerCombustionTurbine_Impl::setDesignChilledWaterOutletTemperature(double designChilledWaterOutletTemperature) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterOutletTemperature, designChilledWaterOutletTemperature);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetDesignChilledWaterOutletTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterOutletTemperature, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::designChilledWaterFlowRate() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterFlowRate, true);
    }

    bool ChillerCombustionTurbine_Impl::isDesignChilledWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerCombustionTurbine_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetDesignChilledWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterFlowRate, ""));
    }

    void ChillerCombustionTurbine_Impl::autosizeDesignChilledWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignChilledWaterFlowRate, "autosize"));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::designCondenserWaterFlowRate() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::DesignCondenserWaterFlowRate, true);
    }

    bool ChillerCombustionTurbine_Impl::isDesignCondenserWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::DesignCondenserWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerCombustionTurbine_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetDesignCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignCondenserWaterFlowRate, ""));
    }

    void ChillerCombustionTurbine_Impl::autosizeDesignCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignCondenserWaterFlowRate, "autosize"));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofCapacityRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofCapacityRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofCapacityRatioCurve(double coefficient1ofCapacityRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofCapacityRatioCurve, coefficient1ofCapacityRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofCapacityRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofCapacityRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofCapacityRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofCapacityRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofCapacityRatioCurve(double coefficient2ofCapacityRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofCapacityRatioCurve, coefficient2ofCapacityRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofCapacityRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofCapacityRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofCapacityRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofCapacityRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofCapacityRatioCurve(double coefficient3ofCapacityRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofCapacityRatioCurve, coefficient3ofCapacityRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofCapacityRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofCapacityRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofPowerRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofPowerRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofPowerRatioCurve(double coefficient1ofPowerRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofPowerRatioCurve, coefficient1ofPowerRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofPowerRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofPowerRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofPowerRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofPowerRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofPowerRatioCurve(double coefficient2ofPowerRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofPowerRatioCurve, coefficient2ofPowerRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofPowerRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofPowerRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofPowerRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofPowerRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofPowerRatioCurve(double coefficient3ofPowerRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofPowerRatioCurve, coefficient3ofPowerRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofPowerRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofPowerRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofFullLoadRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofFullLoadRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofFullLoadRatioCurve(double coefficient1ofFullLoadRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofFullLoadRatioCurve, coefficient1ofFullLoadRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofFullLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofFullLoadRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofFullLoadRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofFullLoadRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofFullLoadRatioCurve(double coefficient2ofFullLoadRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofFullLoadRatioCurve, coefficient2ofFullLoadRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofFullLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofFullLoadRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofFullLoadRatioCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofFullLoadRatioCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofFullLoadRatioCurve(double coefficient3ofFullLoadRatioCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofFullLoadRatioCurve, coefficient3ofFullLoadRatioCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofFullLoadRatioCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofFullLoadRatioCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::chilledWaterOutletTemperatureLowerLimit() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::ChilledWaterOutletTemperatureLowerLimit, true);
    }

    bool ChillerCombustionTurbine_Impl::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::ChilledWaterOutletTemperatureLowerLimit, chilledWaterOutletTemperatureLowerLimit);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetChilledWaterOutletTemperatureLowerLimit() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::ChilledWaterOutletTemperatureLowerLimit, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofFuelInputCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofFuelInputCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofFuelInputCurve(double coefficient1ofFuelInputCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofFuelInputCurve, coefficient1ofFuelInputCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofFuelInputCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofFuelInputCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofFuelInputCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofFuelInputCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofFuelInputCurve(double coefficient2ofFuelInputCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofFuelInputCurve, coefficient2ofFuelInputCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofFuelInputCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofFuelInputCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofFuelInputCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofFuelInputCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofFuelInputCurve(double coefficient3ofFuelInputCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofFuelInputCurve, coefficient3ofFuelInputCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofFuelInputCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofFuelInputCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofTemperatureBasedFuelInputCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedFuelInputCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofTemperatureBasedFuelInputCurve(double coefficient1ofTemperatureBasedFuelInputCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedFuelInputCurve,
                                    coefficient1ofTemperatureBasedFuelInputCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofTemperatureBasedFuelInputCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedFuelInputCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofTemperatureBasedFuelInputCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedFuelInputCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofTemperatureBasedFuelInputCurve(double coefficient2ofTemperatureBasedFuelInputCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedFuelInputCurve,
                                    coefficient2ofTemperatureBasedFuelInputCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofTemperatureBasedFuelInputCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedFuelInputCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofTemperatureBasedFuelInputCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedFuelInputCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofTemperatureBasedFuelInputCurve(double coefficient3ofTemperatureBasedFuelInputCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedFuelInputCurve,
                                    coefficient3ofTemperatureBasedFuelInputCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofTemperatureBasedFuelInputCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedFuelInputCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofExhaustFlowCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofExhaustFlowCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofExhaustFlowCurve(double coefficient1ofExhaustFlowCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofExhaustFlowCurve, coefficient1ofExhaustFlowCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofExhaustFlowCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofExhaustFlowCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofExhaustFlowCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofExhaustFlowCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofExhaustFlowCurve(double coefficient2ofExhaustFlowCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofExhaustFlowCurve, coefficient2ofExhaustFlowCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofExhaustFlowCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofExhaustFlowCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofExhaustFlowCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofExhaustFlowCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofExhaustFlowCurve(double coefficient3ofExhaustFlowCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofExhaustFlowCurve, coefficient3ofExhaustFlowCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofExhaustFlowCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofExhaustFlowCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofExhaustGasTemperatureCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofExhaustGasTemperatureCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofExhaustGasTemperatureCurve(double coefficient1ofExhaustGasTemperatureCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofExhaustGasTemperatureCurve, coefficient1ofExhaustGasTemperatureCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofExhaustGasTemperatureCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofExhaustGasTemperatureCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofExhaustGasTemperatureCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofExhaustGasTemperatureCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofExhaustGasTemperatureCurve(double coefficient2ofExhaustGasTemperatureCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofExhaustGasTemperatureCurve, coefficient2ofExhaustGasTemperatureCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofExhaustGasTemperatureCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofExhaustGasTemperatureCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofExhaustGasTemperatureCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofExhaustGasTemperatureCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofExhaustGasTemperatureCurve(double coefficient3ofExhaustGasTemperatureCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofExhaustGasTemperatureCurve, coefficient3ofExhaustGasTemperatureCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofExhaustGasTemperatureCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofExhaustGasTemperatureCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofTemperatureBasedExhaustGasTemperatureCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedExhaustGasTemperatureCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve(
      double coefficient1ofTemperatureBasedExhaustGasTemperatureCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedExhaustGasTemperatureCurve,
                                    coefficient1ofTemperatureBasedExhaustGasTemperatureCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofTemperatureBasedExhaustGasTemperatureCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedExhaustGasTemperatureCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofTemperatureBasedExhaustGasTemperatureCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedExhaustGasTemperatureCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve(
      double coefficient2ofTemperatureBasedExhaustGasTemperatureCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedExhaustGasTemperatureCurve,
                                    coefficient2ofTemperatureBasedExhaustGasTemperatureCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofTemperatureBasedExhaustGasTemperatureCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedExhaustGasTemperatureCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofTemperatureBasedExhaustGasTemperatureCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedExhaustGasTemperatureCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve(
      double coefficient3ofTemperatureBasedExhaustGasTemperatureCurve) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedExhaustGasTemperatureCurve,
                                    coefficient3ofTemperatureBasedExhaustGasTemperatureCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofTemperatureBasedExhaustGasTemperatureCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedExhaustGasTemperatureCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofRecoveryLubeHeatCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofRecoveryLubeHeatCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofRecoveryLubeHeatCurve(double coefficient1ofRecoveryLubeHeatCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofRecoveryLubeHeatCurve, coefficient1ofRecoveryLubeHeatCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofRecoveryLubeHeatCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofRecoveryLubeHeatCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofRecoveryLubeHeatCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofRecoveryLubeHeatCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofRecoveryLubeHeatCurve(double coefficient2ofRecoveryLubeHeatCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofRecoveryLubeHeatCurve, coefficient2ofRecoveryLubeHeatCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofRecoveryLubeHeatCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofRecoveryLubeHeatCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient3ofRecoveryLubeHeatCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofRecoveryLubeHeatCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient3ofRecoveryLubeHeatCurve(double coefficient3ofRecoveryLubeHeatCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofRecoveryLubeHeatCurve, coefficient3ofRecoveryLubeHeatCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient3ofRecoveryLubeHeatCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient3ofRecoveryLubeHeatCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient1ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient1ofUFactorTimesAreaCurve(double coefficient1ofUFactorTimesAreaCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, coefficient1ofUFactorTimesAreaCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient1ofUFactorTimesAreaCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::coefficient2ofUFactorTimesAreaCurve() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, true);
    }

    bool ChillerCombustionTurbine_Impl::setCoefficient2ofUFactorTimesAreaCurve(double coefficient2ofUFactorTimesAreaCurve) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, coefficient2ofUFactorTimesAreaCurve);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCoefficient2ofUFactorTimesAreaCurve() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::gasTurbineEngineCapacity() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::GasTurbineEngineCapacity, true);
    }

    bool ChillerCombustionTurbine_Impl::isGasTurbineEngineCapacityAutosized() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::GasTurbineEngineCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerCombustionTurbine_Impl::setGasTurbineEngineCapacity(double gasTurbineEngineCapacity) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::GasTurbineEngineCapacity, gasTurbineEngineCapacity);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetGasTurbineEngineCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::GasTurbineEngineCapacity, ""));
    }

    void ChillerCombustionTurbine_Impl::autosizeGasTurbineEngineCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::GasTurbineEngineCapacity, "autosize"));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::maximumExhaustFlowperUnitofPowerOutput() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, true);
    }

    bool ChillerCombustionTurbine_Impl::setMaximumExhaustFlowperUnitofPowerOutput(double maximumExhaustFlowperUnitofPowerOutput) {
      const bool result =
        setDouble(openstudio::Chiller_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, maximumExhaustFlowperUnitofPowerOutput);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetMaximumExhaustFlowperUnitofPowerOutput() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::designSteamSaturationTemperature() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::DesignSteamSaturationTemperature, true);
    }

    bool ChillerCombustionTurbine_Impl::setDesignSteamSaturationTemperature(double designSteamSaturationTemperature) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::DesignSteamSaturationTemperature, designSteamSaturationTemperature);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetDesignSteamSaturationTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignSteamSaturationTemperature, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::fuelHigherHeatingValue() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::FuelHigherHeatingValue, true);
    }

    bool ChillerCombustionTurbine_Impl::setFuelHigherHeatingValue(double fuelHigherHeatingValue) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::FuelHigherHeatingValue, fuelHigherHeatingValue);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetFuelHigherHeatingValue() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::FuelHigherHeatingValue, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::designHeatRecoveryWaterFlowRate() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, true);
    }

    bool ChillerCombustionTurbine_Impl::isDesignHeatRecoveryWaterFlowRateDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate);
    }

    bool ChillerCombustionTurbine_Impl::isDesignHeatRecoveryWaterFlowRateAutosized() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ChillerCombustionTurbine_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, designHeatRecoveryWaterFlowRate);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetDesignHeatRecoveryWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, ""));
    }

    void ChillerCombustionTurbine_Impl::autosizeDesignHeatRecoveryWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, "autosize"));
    }

    std::string ChillerCombustionTurbine_Impl::chillerFlowMode() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::ChillerFlowMode, false)) {
        return *value;
      }
      return "NotModulated";
    }

    bool ChillerCombustionTurbine_Impl::isChillerFlowModeDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::ChillerFlowMode);
    }

    bool ChillerCombustionTurbine_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
      return setString(openstudio::Chiller_CombustionTurbineFields::ChillerFlowMode, chillerFlowMode);
    }

    void ChillerCombustionTurbine_Impl::resetChillerFlowMode() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::ChillerFlowMode, ""));
    }

    std::string ChillerCombustionTurbine_Impl::fuelType() const {
      if (auto value = getString(openstudio::Chiller_CombustionTurbineFields::FuelType, false)) {
        return *value;
      }
      return "NaturalGas";
    }

    bool ChillerCombustionTurbine_Impl::isFuelTypeDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::FuelType);
    }

    bool ChillerCombustionTurbine_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Chiller_CombustionTurbineFields::FuelType, fuelType);
    }

    void ChillerCombustionTurbine_Impl::resetFuelType() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::FuelType, ""));
    }

    double ChillerCombustionTurbine_Impl::heatRecoveryMaximumTemperature() const {
      if (auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::HeatRecoveryMaximumTemperature, false)) {
        return *value;
      }
      return 80.0;
    }

    bool ChillerCombustionTurbine_Impl::isHeatRecoveryMaximumTemperatureDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::HeatRecoveryMaximumTemperature);
    }

    bool ChillerCombustionTurbine_Impl::setHeatRecoveryMaximumTemperature(double heatRecoveryMaximumTemperature) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::HeatRecoveryMaximumTemperature, heatRecoveryMaximumTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetHeatRecoveryMaximumTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::HeatRecoveryMaximumTemperature, ""));
    }

    double ChillerCombustionTurbine_Impl::sizingFactor() const {
      if (auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::SizingFactor, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ChillerCombustionTurbine_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::SizingFactor);
    }

    bool ChillerCombustionTurbine_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::SizingFactor, sizingFactor);
      OS_ASSERT(result);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::SizingFactor, ""));
    }

    double ChillerCombustionTurbine_Impl::basinHeaterCapacity() const {
      if (auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::BasinHeaterCapacity, false)) {
        return *value;
      }
      return 0.0;
    }

    bool ChillerCombustionTurbine_Impl::isBasinHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::BasinHeaterCapacity);
    }

    bool ChillerCombustionTurbine_Impl::setBasinHeaterCapacity(double basinHeaterCapacity) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::BasinHeaterCapacity, basinHeaterCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetBasinHeaterCapacity() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::BasinHeaterCapacity, ""));
    }

    double ChillerCombustionTurbine_Impl::basinHeaterSetpointTemperature() const {
      if (auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::BasinHeaterSetpointTemperature, false)) {
        return *value;
      }
      return 2.0;
    }

    bool ChillerCombustionTurbine_Impl::isBasinHeaterSetpointTemperatureDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::BasinHeaterSetpointTemperature);
    }

    bool ChillerCombustionTurbine_Impl::setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::BasinHeaterSetpointTemperature, basinHeaterSetpointTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetBasinHeaterSetpointTemperature() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::BasinHeaterSetpointTemperature, ""));
    }

    boost::optional<double> ChillerCombustionTurbine_Impl::condenserHeatRecoveryRelativeCapacityFraction() const {
      return getDouble(openstudio::Chiller_CombustionTurbineFields::CondenserHeatRecoveryRelativeCapacityFraction, true);
    }

    bool ChillerCombustionTurbine_Impl::setCondenserHeatRecoveryRelativeCapacityFraction(double condenserHeatRecoveryRelativeCapacityFraction) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::CondenserHeatRecoveryRelativeCapacityFraction,
                                    condenserHeatRecoveryRelativeCapacityFraction);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetCondenserHeatRecoveryRelativeCapacityFraction() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::CondenserHeatRecoveryRelativeCapacityFraction, ""));
    }

    double ChillerCombustionTurbine_Impl::turbineEngineEfficiency() const {
      if (auto value = getDouble(openstudio::Chiller_CombustionTurbineFields::TurbineEngineEfficiency, false)) {
        return *value;
      }
      return 0.35;
    }

    bool ChillerCombustionTurbine_Impl::isTurbineEngineEfficiencyDefaulted() const {
      return isEmpty(openstudio::Chiller_CombustionTurbineFields::TurbineEngineEfficiency);
    }

    bool ChillerCombustionTurbine_Impl::setTurbineEngineEfficiency(double turbineEngineEfficiency) {
      const bool result = setDouble(openstudio::Chiller_CombustionTurbineFields::TurbineEngineEfficiency, turbineEngineEfficiency);
      OS_ASSERT(result);
      return result;
    }

    void ChillerCombustionTurbine_Impl::resetTurbineEngineEfficiency() {
      OS_ASSERT(setString(openstudio::Chiller_CombustionTurbineFields::TurbineEngineEfficiency, ""));
    }

    std::vector<std::string> ChillerCombustionTurbine_Impl::condenserTypeValues() const {
      return openstudio::epmodel::ChillerCombustionTurbine::condenserTypeValues();
    }

    std::vector<std::string> ChillerCombustionTurbine_Impl::chillerFlowModeValues() const {
      return openstudio::epmodel::ChillerCombustionTurbine::chillerFlowModeValues();
    }

    std::vector<std::string> ChillerCombustionTurbine_Impl::fuelTypeValues() const {
      return openstudio::epmodel::ChillerCombustionTurbine::fuelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
