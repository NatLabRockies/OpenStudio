/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling_Impl.hpp"
#include "StraightComponent/Node.hpp"

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
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>());

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

    CurveBiquadratic normalizedCapacityFunctionofTemperatureCurve(model);
    ok &= static_cast<bool>(normalizedCapacityFunctionofTemperatureCurve.setName("GAHP Heating CapFT"));
    ok &= normalizedCapacityFunctionofTemperatureCurve.setCoefficient1Constant(1.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setCoefficient2x(0.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setCoefficient3xPOW2(0.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setCoefficient4y(0.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setCoefficient5yPOW2(0.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setCoefficient6xTIMESY(0.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setMinimumValueofx(5.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setMaximumValueofx(10.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setMinimumValueofy(24.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setMaximumValueofy(35.0);
    ok &= normalizedCapacityFunctionofTemperatureCurve.setInputUnitTypeforX("Temperature");
    ok &= normalizedCapacityFunctionofTemperatureCurve.setInputUnitTypeforY("Temperature");
    ok &= setNormalizedCapacityFunctionofTemperatureCurve(normalizedCapacityFunctionofTemperatureCurve);

    CurveBiquadratic fuelEnergyInputRatioFunctionofTemperatureCurve(model);
    ok &= static_cast<bool>(fuelEnergyInputRatioFunctionofTemperatureCurve.setName("GAHP Heating EIRFT"));
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setCoefficient1Constant(1.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setCoefficient2x(0.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setCoefficient3xPOW2(0.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setCoefficient4y(0.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setCoefficient5yPOW2(0.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setCoefficient6xTIMESY(0.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setMinimumValueofx(5.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setMaximumValueofx(10.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setMinimumValueofy(24.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setMaximumValueofy(35.0);
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setInputUnitTypeforX("Temperature");
    ok &= fuelEnergyInputRatioFunctionofTemperatureCurve.setInputUnitTypeforY("Temperature");
    ok &= setFuelEnergyInputRatioFunctionofTemperatureCurve(fuelEnergyInputRatioFunctionofTemperatureCurve);

    CurveQuadratic fuelEnergyInputRatioFunctionofPLRCurve(model);
    ok &= static_cast<bool>(fuelEnergyInputRatioFunctionofPLRCurve.setName("GAHP Heating EIRFPLR"));
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setCoefficient1Constant(1.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setCoefficient2x(0.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setCoefficient3xPOW2(0.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setMinimumValueofx(0.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setMaximumValueofx(1.0);
    ok &= setFuelEnergyInputRatioFunctionofPLRCurve(fuelEnergyInputRatioFunctionofPLRCurve);

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

  HeatPumpAirToWaterFuelFiredHeating::HeatPumpAirToWaterFuelFiredHeating(const Model& model,
                                                                         const Curve& normalizedCapacityFunctionofTemperatureCurve,
                                                                         const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve,
                                                                         const Curve& fuelEnergyInputRatioFunctionofPLRCurve)
    : StraightComponent(HeatPumpAirToWaterFuelFiredHeating::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>());

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
    OS_ASSERT(ok);

    ok = setNormalizedCapacityFunctionofTemperatureCurve(normalizedCapacityFunctionofTemperatureCurve);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.HeatPumpAirToWaterFuelFiredHeating",
                         "Unable to set " << briefDescription() << "'s normalized capacity modifier function of temperature curve to "
                                          << normalizedCapacityFunctionofTemperatureCurve.briefDescription() << ".");
    }

    ok = setFuelEnergyInputRatioFunctionofTemperatureCurve(fuelEnergyInputRatioFunctionofTemperatureCurve);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.HeatPumpAirToWaterFuelFiredHeating",
                         "Unable to set " << briefDescription() << "'s fuel energy input ratio function of temperature curve to "
                                          << fuelEnergyInputRatioFunctionofTemperatureCurve.briefDescription() << ".");
    }

    ok = setFuelEnergyInputRatioFunctionofPLRCurve(fuelEnergyInputRatioFunctionofPLRCurve);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.HeatPumpAirToWaterFuelFiredHeating",
                         "Unable to set " << briefDescription() << "'s fuel energy input ratio function of PLR curve to "
                                          << fuelEnergyInputRatioFunctionofPLRCurve.briefDescription() << ".");
    }

    ok = setMinimumPartLoadRatio(0.1);
    OS_ASSERT(ok);
    ok = setMaximumPartLoadRatio(1.0);
    OS_ASSERT(ok);
    ok = setDefrostControlType("Timed");
    OS_ASSERT(ok);
    ok = setDefrostOperationTimeFraction(0.0);
    OS_ASSERT(ok);
    ok = setResistiveDefrostHeaterCapacity(0.0);
    OS_ASSERT(ok);
    ok = setMaximumOutdoorDrybulbTemperatureforDefrostOperation(5.0);
    OS_ASSERT(ok);
    ok = setNominalAuxiliaryElectricPower(0.0);
    OS_ASSERT(ok);
    ok = setStandbyElectricPower(0.0);
    OS_ASSERT(ok);
    ok = setMinimumUnloadingRatio(0.25);
    OS_ASSERT(ok);
  }

  HeatPumpAirToWaterFuelFiredHeating::HeatPumpAirToWaterFuelFiredHeating(std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredHeating_Impl> impl)
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

  boost::optional<HeatPumpAirToWaterFuelFiredCooling> HeatPumpAirToWaterFuelFiredHeating::companionCoolingHeatPump() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->companionCoolingHeatPump();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setCompanionCoolingHeatPump(const HeatPumpAirToWaterFuelFiredCooling& heatPumpAirToWaterFuelFiredCooling) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setCompanionCoolingHeatPump(heatPumpAirToWaterFuelFiredCooling);
  }

  void HeatPumpAirToWaterFuelFiredHeating::resetCompanionCoolingHeatPump() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetCompanionCoolingHeatPump();
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

  Curve HeatPumpAirToWaterFuelFiredHeating::normalizedCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->normalizedCapacityFunctionofTemperatureCurve();
  }

  bool
    HeatPumpAirToWaterFuelFiredHeating::setNormalizedCapacityFunctionofTemperatureCurve(const Curve& normalizedCapacityFunctionofTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setNormalizedCapacityFunctionofTemperatureCurve(
      normalizedCapacityFunctionofTemperatureCurve);
  }

  Curve HeatPumpAirToWaterFuelFiredHeating::fuelEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->fuelEnergyInputRatioFunctionofTemperatureCurve();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setFuelEnergyInputRatioFunctionofTemperatureCurve(
    const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setFuelEnergyInputRatioFunctionofTemperatureCurve(
      fuelEnergyInputRatioFunctionofTemperatureCurve);
  }

  Curve HeatPumpAirToWaterFuelFiredHeating::fuelEnergyInputRatioFunctionofPLRCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->fuelEnergyInputRatioFunctionofPLRCurve();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setFuelEnergyInputRatioFunctionofPLRCurve(const Curve& fuelEnergyInputRatioFunctionofPLRCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setFuelEnergyInputRatioFunctionofPLRCurve(
      fuelEnergyInputRatioFunctionofPLRCurve);
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

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating::fuelEnergyInputRatioDefrostAdjustmentCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->fuelEnergyInputRatioDefrostAdjustmentCurve();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setFuelEnergyInputRatioDefrostAdjustmentCurve(const Curve& fuelEnergyInputRatioDefrostAdjustmentCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setFuelEnergyInputRatioDefrostAdjustmentCurve(
      fuelEnergyInputRatioDefrostAdjustmentCurve);
  }

  void HeatPumpAirToWaterFuelFiredHeating::resetFuelEnergyInputRatioDefrostAdjustmentCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetFuelEnergyInputRatioDefrostAdjustmentCurve();
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

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating::cyclingRatioFactorCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->cyclingRatioFactorCurve();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setCyclingRatioFactorCurve(const Curve& cyclingRatioFactorCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setCyclingRatioFactorCurve(cyclingRatioFactorCurve);
  }

  void HeatPumpAirToWaterFuelFiredHeating::resetCyclingRatioFactorCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetCyclingRatioFactorCurve();
  }

  double HeatPumpAirToWaterFuelFiredHeating::nominalAuxiliaryElectricPower() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->nominalAuxiliaryElectricPower();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setNominalAuxiliaryElectricPower(nominalAuxiliaryElectricPower);
  }

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating::auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(
    const Curve& auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(
      auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve);
  }

  void HeatPumpAirToWaterFuelFiredHeating::resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();
  }

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating::auxiliaryElectricEnergyInputRatioFunctionofPLRCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->auxiliaryElectricEnergyInputRatioFunctionofPLRCurve();
  }

  bool HeatPumpAirToWaterFuelFiredHeating::setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(
    const Curve& auxiliaryElectricEnergyInputRatioFunctionofPLRCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(
      auxiliaryElectricEnergyInputRatioFunctionofPLRCurve);
  }

  void HeatPumpAirToWaterFuelFiredHeating::resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredHeating_Impl>()->resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve();
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

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }
      return false;
    }

    boost::optional<HeatPumpAirToWaterFuelFiredCooling> HeatPumpAirToWaterFuelFiredHeating_Impl::companionCoolingHeatPump() const {
      return getObject<ModelObject>().getModelObjectTarget<HeatPumpAirToWaterFuelFiredCooling>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::CompanionCoolingHeatPumpName);
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setCompanionCoolingHeatPump(
      const HeatPumpAirToWaterFuelFiredCooling& heatPumpAirToWaterFuelFiredCooling) {
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::CompanionCoolingHeatPumpName,
                        heatPumpAirToWaterFuelFiredCooling.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredHeating_Impl::resetCompanionCoolingHeatPump() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::CompanionCoolingHeatPumpName, Handle(), false));
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

    Curve HeatPumpAirToWaterFuelFiredHeating_Impl::normalizedCapacityFunctionofTemperatureCurve() const {
      auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NormalizedCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(result);
      return *result;
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setNormalizedCapacityFunctionofTemperatureCurve(
      const Curve& normalizedCapacityFunctionofTemperatureCurve) {
      if (normalizedCapacityFunctionofTemperatureCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NormalizedCapacityFunctionofTemperatureCurveName,
                        normalizedCapacityFunctionofTemperatureCurve.handle(), false);
    }

    Curve HeatPumpAirToWaterFuelFiredHeating_Impl::fuelEnergyInputRatioFunctionofTemperatureCurve() const {
      auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioFunctionofTemperatureCurveName);
      OS_ASSERT(result);
      return *result;
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setFuelEnergyInputRatioFunctionofTemperatureCurve(
      const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve) {
      if (fuelEnergyInputRatioFunctionofTemperatureCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioFunctionofTemperatureCurveName,
                        fuelEnergyInputRatioFunctionofTemperatureCurve.handle(), false);
    }

    Curve HeatPumpAirToWaterFuelFiredHeating_Impl::fuelEnergyInputRatioFunctionofPLRCurve() const {
      auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioFunctionofPLRCurveName);
      OS_ASSERT(result);
      return *result;
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setFuelEnergyInputRatioFunctionofPLRCurve(const Curve& fuelEnergyInputRatioFunctionofPLRCurve) {
      if (fuelEnergyInputRatioFunctionofPLRCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioFunctionofPLRCurveName,
                        fuelEnergyInputRatioFunctionofPLRCurve.handle(), false);
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

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating_Impl::fuelEnergyInputRatioDefrostAdjustmentCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioDefrostAdjustmentCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setFuelEnergyInputRatioDefrostAdjustmentCurve(
      const Curve& fuelEnergyInputRatioDefrostAdjustmentCurve) {
      if (fuelEnergyInputRatioDefrostAdjustmentCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioDefrostAdjustmentCurveName,
                        fuelEnergyInputRatioDefrostAdjustmentCurve.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredHeating_Impl::resetFuelEnergyInputRatioDefrostAdjustmentCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::FuelEnergyInputRatioDefrostAdjustmentCurveName, Handle(), false));
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

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating_Impl::cyclingRatioFactorCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::CyclingRatioFactorCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setCyclingRatioFactorCurve(const Curve& cyclingRatioFactorCurve) {
      if (cyclingRatioFactorCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::CyclingRatioFactorCurveName, cyclingRatioFactorCurve.handle(),
                        false);
    }

    void HeatPumpAirToWaterFuelFiredHeating_Impl::resetCyclingRatioFactorCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::CyclingRatioFactorCurveName, Handle(), false));
    }

    double HeatPumpAirToWaterFuelFiredHeating_Impl::nominalAuxiliaryElectricPower() const {
      const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalAuxiliaryElectricPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
      return setDouble(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::NominalAuxiliaryElectricPower, nominalAuxiliaryElectricPower);
    }

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating_Impl::auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(
      const Curve& auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve) {
      if (auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName,
                        auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredHeating_Impl::resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName,
                           Handle(), false));
    }

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredHeating_Impl::auxiliaryElectricEnergyInputRatioFunctionofPLRCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredHeating_Impl::setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(
      const Curve& auxiliaryElectricEnergyInputRatioFunctionofPLRCurve) {
      if (auxiliaryElectricEnergyInputRatioFunctionofPLRCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName,
                        auxiliaryElectricEnergyInputRatioFunctionofPLRCurve.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredHeating_Impl::resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_HeatingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName, Handle(),
                           false));
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
