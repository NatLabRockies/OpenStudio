/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredCooling_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating.hpp"
#include "StraightComponent/HeatPumpAirToWaterFuelFiredHeating_Impl.hpp"
#include "StraightComponent/Node.hpp"

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
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>());

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

    CurveBiquadratic normalizedCapacityFunctionofTemperatureCurve(model);
    ok &= static_cast<bool>(normalizedCapacityFunctionofTemperatureCurve.setName("GAHP Cooling CapFT"));
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
    ok &= static_cast<bool>(fuelEnergyInputRatioFunctionofTemperatureCurve.setName("GAHP Cooling EIRFT"));
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
    ok &= static_cast<bool>(fuelEnergyInputRatioFunctionofPLRCurve.setName("GAHP Cooling EIRFPLR"));
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setCoefficient1Constant(1.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setCoefficient2x(0.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setCoefficient3xPOW2(0.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setMinimumValueofx(0.0);
    ok &= fuelEnergyInputRatioFunctionofPLRCurve.setMaximumValueofx(1.0);
    ok &= setFuelEnergyInputRatioFunctionofPLRCurve(fuelEnergyInputRatioFunctionofPLRCurve);

    ok &= setMinimumPartLoadRatio(0.1);
    ok &= setMaximumPartLoadRatio(1.0);
    ok &= setNominalAuxiliaryElectricPower(0.0);
    ok &= setStandbyElectricPower(0.0);
    ok &= setMinimumUnloadingRatio(0.25);
    OS_ASSERT(ok);
  }

  HeatPumpAirToWaterFuelFiredCooling::HeatPumpAirToWaterFuelFiredCooling(const Model& model,
                                                                         const Curve& normalizedCapacityFunctionofTemperatureCurve,
                                                                         const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve,
                                                                         const Curve& fuelEnergyInputRatioFunctionofPLRCurve)
    : StraightComponent(HeatPumpAirToWaterFuelFiredCooling::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>());

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
    OS_ASSERT(ok);

    ok = setNormalizedCapacityFunctionofTemperatureCurve(normalizedCapacityFunctionofTemperatureCurve);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.HeatPumpAirToWaterFuelFiredCooling",
                         "Unable to set " << briefDescription() << "'s normalized capacity modifier function of temperature curve to "
                                          << normalizedCapacityFunctionofTemperatureCurve.briefDescription() << ".");
    }

    ok = setFuelEnergyInputRatioFunctionofTemperatureCurve(fuelEnergyInputRatioFunctionofTemperatureCurve);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.HeatPumpAirToWaterFuelFiredCooling",
                         "Unable to set " << briefDescription() << "'s fuel energy input ratio function of temperature curve to "
                                          << fuelEnergyInputRatioFunctionofTemperatureCurve.briefDescription() << ".");
    }

    ok = setFuelEnergyInputRatioFunctionofPLRCurve(fuelEnergyInputRatioFunctionofPLRCurve);
    if (!ok) {
      remove();
      LOG_FREE_AND_THROW("openstudio.epmodel.HeatPumpAirToWaterFuelFiredCooling",
                         "Unable to set " << briefDescription() << "'s fuel energy input ratio function of PLR curve to "
                                          << fuelEnergyInputRatioFunctionofPLRCurve.briefDescription() << ".");
    }

    ok = setMinimumPartLoadRatio(0.1);
    OS_ASSERT(ok);
    ok = setMaximumPartLoadRatio(1.0);
    OS_ASSERT(ok);
    ok = setNominalAuxiliaryElectricPower(0.0);
    OS_ASSERT(ok);
    ok = setStandbyElectricPower(0.0);
    OS_ASSERT(ok);
    ok = setMinimumUnloadingRatio(0.25);
    OS_ASSERT(ok);
  }

  HeatPumpAirToWaterFuelFiredCooling::HeatPumpAirToWaterFuelFiredCooling(std::shared_ptr<detail::HeatPumpAirToWaterFuelFiredCooling_Impl> impl)
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

  boost::optional<HeatPumpAirToWaterFuelFiredHeating> HeatPumpAirToWaterFuelFiredCooling::companionHeatingHeatPump() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->companionHeatingHeatPump();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setCompanionHeatingHeatPump(const HeatPumpAirToWaterFuelFiredHeating& heatPumpAirToWaterFuelFiredHeating) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setCompanionHeatingHeatPump(heatPumpAirToWaterFuelFiredHeating);
  }

  void HeatPumpAirToWaterFuelFiredCooling::resetCompanionHeatingHeatPump() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetCompanionHeatingHeatPump();
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

  Curve HeatPumpAirToWaterFuelFiredCooling::normalizedCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->normalizedCapacityFunctionofTemperatureCurve();
  }

  bool
    HeatPumpAirToWaterFuelFiredCooling::setNormalizedCapacityFunctionofTemperatureCurve(const Curve& normalizedCapacityFunctionofTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setNormalizedCapacityFunctionofTemperatureCurve(
      normalizedCapacityFunctionofTemperatureCurve);
  }

  Curve HeatPumpAirToWaterFuelFiredCooling::fuelEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->fuelEnergyInputRatioFunctionofTemperatureCurve();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setFuelEnergyInputRatioFunctionofTemperatureCurve(
    const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setFuelEnergyInputRatioFunctionofTemperatureCurve(
      fuelEnergyInputRatioFunctionofTemperatureCurve);
  }

  Curve HeatPumpAirToWaterFuelFiredCooling::fuelEnergyInputRatioFunctionofPLRCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->fuelEnergyInputRatioFunctionofPLRCurve();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setFuelEnergyInputRatioFunctionofPLRCurve(const Curve& fuelEnergyInputRatioFunctionofPLRCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setFuelEnergyInputRatioFunctionofPLRCurve(
      fuelEnergyInputRatioFunctionofPLRCurve);
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

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredCooling::cyclingRatioFactorCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->cyclingRatioFactorCurve();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setCyclingRatioFactorCurve(const Curve& cyclingRatioFactorCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setCyclingRatioFactorCurve(cyclingRatioFactorCurve);
  }

  void HeatPumpAirToWaterFuelFiredCooling::resetCyclingRatioFactorCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetCyclingRatioFactorCurve();
  }

  double HeatPumpAirToWaterFuelFiredCooling::nominalAuxiliaryElectricPower() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->nominalAuxiliaryElectricPower();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setNominalAuxiliaryElectricPower(nominalAuxiliaryElectricPower);
  }

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredCooling::auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(
    const Curve& auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(
      auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve);
  }

  void HeatPumpAirToWaterFuelFiredCooling::resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve();
  }

  boost::optional<Curve> HeatPumpAirToWaterFuelFiredCooling::auxiliaryElectricEnergyInputRatioFunctionofPLRCurve() const {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->auxiliaryElectricEnergyInputRatioFunctionofPLRCurve();
  }

  bool HeatPumpAirToWaterFuelFiredCooling::setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(
    const Curve& auxiliaryElectricEnergyInputRatioFunctionofPLRCurve) {
    return getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(
      auxiliaryElectricEnergyInputRatioFunctionofPLRCurve);
  }

  void HeatPumpAirToWaterFuelFiredCooling::resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve() {
    getImpl<detail::HeatPumpAirToWaterFuelFiredCooling_Impl>()->resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve();
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
      return openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterInletNodeName;
    }

    unsigned HeatPumpAirToWaterFuelFiredCooling_Impl::outletPort() const {
      return openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::WaterOutletNodeName;
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }
      return false;
    }

    boost::optional<HeatPumpAirToWaterFuelFiredHeating> HeatPumpAirToWaterFuelFiredCooling_Impl::companionHeatingHeatPump() const {
      return getObject<ModelObject>().getModelObjectTarget<HeatPumpAirToWaterFuelFiredHeating>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::CompanionHeatingHeatPumpName);
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setCompanionHeatingHeatPump(
      const HeatPumpAirToWaterFuelFiredHeating& heatPumpAirToWaterFuelFiredHeating) {
      if (heatPumpAirToWaterFuelFiredHeating.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::CompanionHeatingHeatPumpName,
                        heatPumpAirToWaterFuelFiredHeating.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredCooling_Impl::resetCompanionHeatingHeatPump() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::CompanionHeatingHeatPumpName, Handle(), false));
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

    Curve HeatPumpAirToWaterFuelFiredCooling_Impl::normalizedCapacityFunctionofTemperatureCurve() const {
      auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NormalizedCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(result);
      return *result;
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setNormalizedCapacityFunctionofTemperatureCurve(
      const Curve& normalizedCapacityFunctionofTemperatureCurve) {
      if (normalizedCapacityFunctionofTemperatureCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NormalizedCapacityFunctionofTemperatureCurveName,
                        normalizedCapacityFunctionofTemperatureCurve.handle(), false);
    }

    Curve HeatPumpAirToWaterFuelFiredCooling_Impl::fuelEnergyInputRatioFunctionofTemperatureCurve() const {
      auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelEnergyInputRatioFunctionofTemperatureCurveName);
      OS_ASSERT(result);
      return *result;
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setFuelEnergyInputRatioFunctionofTemperatureCurve(
      const Curve& fuelEnergyInputRatioFunctionofTemperatureCurve) {
      if (fuelEnergyInputRatioFunctionofTemperatureCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelEnergyInputRatioFunctionofTemperatureCurveName,
                        fuelEnergyInputRatioFunctionofTemperatureCurve.handle(), false);
    }

    Curve HeatPumpAirToWaterFuelFiredCooling_Impl::fuelEnergyInputRatioFunctionofPLRCurve() const {
      auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelEnergyInputRatioFunctionofPLRCurveName);
      OS_ASSERT(result);
      return *result;
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setFuelEnergyInputRatioFunctionofPLRCurve(const Curve& fuelEnergyInputRatioFunctionofPLRCurve) {
      if (fuelEnergyInputRatioFunctionofPLRCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::FuelEnergyInputRatioFunctionofPLRCurveName,
                        fuelEnergyInputRatioFunctionofPLRCurve.handle(), false);
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

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredCooling_Impl::cyclingRatioFactorCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::CyclingRatioFactorCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setCyclingRatioFactorCurve(const Curve& cyclingRatioFactorCurve) {
      if (cyclingRatioFactorCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::CyclingRatioFactorCurveName, cyclingRatioFactorCurve.handle(),
                        false);
    }

    void HeatPumpAirToWaterFuelFiredCooling_Impl::resetCyclingRatioFactorCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::CyclingRatioFactorCurveName, Handle(), false));
    }

    double HeatPumpAirToWaterFuelFiredCooling_Impl::nominalAuxiliaryElectricPower() const {
      const auto value = getDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalAuxiliaryElectricPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower) {
      return setDouble(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::NominalAuxiliaryElectricPower, nominalAuxiliaryElectricPower);
    }

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredCooling_Impl::auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve(
      const Curve& auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve) {
      if (auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName,
                        auxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredCooling_Impl::resetAuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName,
                           Handle(), false));
    }

    boost::optional<Curve> HeatPumpAirToWaterFuelFiredCooling_Impl::auxiliaryElectricEnergyInputRatioFunctionofPLRCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName);
    }

    bool HeatPumpAirToWaterFuelFiredCooling_Impl::setAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve(
      const Curve& auxiliaryElectricEnergyInputRatioFunctionofPLRCurve) {
      if (auxiliaryElectricEnergyInputRatioFunctionofPLRCurve.model() != model()) {
        return false;
      }
      return setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName,
                        auxiliaryElectricEnergyInputRatioFunctionofPLRCurve.handle(), false);
    }

    void HeatPumpAirToWaterFuelFiredCooling_Impl::resetAuxiliaryElectricEnergyInputRatioFunctionofPLRCurve() {
      OS_ASSERT(setPointer(openstudio::HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName, Handle(),
                           false));
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
