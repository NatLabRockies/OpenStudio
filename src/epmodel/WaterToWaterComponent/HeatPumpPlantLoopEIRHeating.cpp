/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Heating_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

HeatPumpPlantLoopEIRHeating::HeatPumpPlantLoopEIRHeating(const Model& model, const Curve& capacityModifierFunctionofTemperatureCurve,
                                                         const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve,
                                                         const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve)
  : WaterToWaterComponent(HeatPumpPlantLoopEIRHeating::iddObjectType(), model) {
  autosizeLoadSideReferenceFlowRate();
  autosizeSourceSideReferenceFlowRate();
  autosizeHeatRecoveryReferenceFlowRate();
  autosizeReferenceCapacity();
  OS_ASSERT(setCapacityModifierFunctionofTemperatureCurve(capacityModifierFunctionofTemperatureCurve));
  OS_ASSERT(setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(electricInputtoOutputRatioModifierFunctionofTemperatureCurve));
  OS_ASSERT(setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve));
  OS_ASSERT(setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, "AirSource"));
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setHeatingToCoolingCapacitySizingRatio(1.0));
  OS_ASSERT(setHeatPumpSizingMethod("CoolingCapacity"));
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setFlowMode("ConstantFlow"));
  OS_ASSERT(setMinimumPartLoadRatio(0.0));
  OS_ASSERT(setMinimumSourceInletTemperature(-100.0));
  OS_ASSERT(setMaximumSourceInletTemperature(100.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureForDefrostOperation(10.0));
  OS_ASSERT(setHeatPumpDefrostControl("None"));
  OS_ASSERT(setHeatPumpDefrostTimePeriodFraction(0.058333));
  OS_ASSERT(setMinimumHeatRecoveryOutletTemperature(4.5));
}

HeatPumpPlantLoopEIRHeating::HeatPumpPlantLoopEIRHeating(const Model& model)
  : WaterToWaterComponent(HeatPumpPlantLoopEIRHeating::iddObjectType(), model) {
  autosizeLoadSideReferenceFlowRate();
  autosizeSourceSideReferenceFlowRate();
  autosizeHeatRecoveryReferenceFlowRate();
  autosizeReferenceCapacity();

  CurveBiquadratic capacityModifierFunctionofTemperatureCurve(model);
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setCoefficient1Constant(1.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setCoefficient2x(0.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setCoefficient3xPOW2(0.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setCoefficient4y(0.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setCoefficient5yPOW2(0.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setCoefficient6xTIMESY(0.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setMinimumValueofx(5.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setMaximumValueofx(10.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setMinimumValueofy(24.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setMaximumValueofy(35.0));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setInputUnitTypeforX("Temperature"));
  OS_ASSERT(capacityModifierFunctionofTemperatureCurve.setInputUnitTypeforY("Temperature"));
  OS_ASSERT(setCapacityModifierFunctionofTemperatureCurve(capacityModifierFunctionofTemperatureCurve));

  CurveBiquadratic eirFT(model);
  OS_ASSERT(eirFT.setCoefficient1Constant(1.0));
  OS_ASSERT(eirFT.setCoefficient2x(0.0));
  OS_ASSERT(eirFT.setCoefficient3xPOW2(0.0));
  OS_ASSERT(eirFT.setCoefficient4y(0.0));
  OS_ASSERT(eirFT.setCoefficient5yPOW2(0.0));
  OS_ASSERT(eirFT.setCoefficient6xTIMESY(0.0));
  OS_ASSERT(eirFT.setMinimumValueofx(5.0));
  OS_ASSERT(eirFT.setMaximumValueofx(10.0));
  OS_ASSERT(eirFT.setMinimumValueofy(24.0));
  OS_ASSERT(eirFT.setMaximumValueofy(35.0));
  OS_ASSERT(eirFT.setInputUnitTypeforX("Temperature"));
  OS_ASSERT(eirFT.setInputUnitTypeforY("Temperature"));
  OS_ASSERT(setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(eirFT));

  CurveQuadratic eirFPLR(model);
  OS_ASSERT(eirFPLR.setCoefficient1Constant(1.0));
  OS_ASSERT(eirFPLR.setCoefficient2x(0.0));
  OS_ASSERT(eirFPLR.setCoefficient3xPOW2(0.0));
  OS_ASSERT(eirFPLR.setMinimumValueofx(0.0));
  OS_ASSERT(eirFPLR.setMaximumValueofx(1.0));
  OS_ASSERT(setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(eirFPLR));

  OS_ASSERT(setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, "AirSource"));
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setHeatingToCoolingCapacitySizingRatio(1.0));
  OS_ASSERT(setHeatPumpSizingMethod("CoolingCapacity"));
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setFlowMode("ConstantFlow"));
  OS_ASSERT(setMinimumPartLoadRatio(0.0));
  OS_ASSERT(setMinimumSourceInletTemperature(-100.0));
  OS_ASSERT(setMaximumSourceInletTemperature(100.0));
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureForDefrostOperation(10.0));
  OS_ASSERT(setHeatPumpDefrostControl("None"));
  OS_ASSERT(setHeatPumpDefrostTimePeriodFraction(0.058333));
  OS_ASSERT(setMinimumHeatRecoveryOutletTemperature(4.5));
}

HeatPumpPlantLoopEIRHeating::HeatPumpPlantLoopEIRHeating(std::shared_ptr<detail::HeatPumpPlantLoopEIRHeating_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType HeatPumpPlantLoopEIRHeating::iddObjectType() {
  return IddObjectType::HeatPump_PlantLoop_EIR_Heating;
}

std::vector<std::string> HeatPumpPlantLoopEIRHeating::validCondenserTypeValues() {
  return HeatPumpPlantLoopEIRHeating::condenserTypeValues();
}

std::vector<std::string> HeatPumpPlantLoopEIRHeating::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType);
}

std::string HeatPumpPlantLoopEIRHeating::condenserType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->condenserType();
}

bool HeatPumpPlantLoopEIRHeating::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setCondenserType(condenserType);
}

boost::optional<HeatPumpPlantLoopEIRCooling> HeatPumpPlantLoopEIRHeating::companionCoolingHeatPump() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->companionCoolingHeatPump();
}

bool HeatPumpPlantLoopEIRHeating::setCompanionCoolingHeatPump(const HeatPumpPlantLoopEIRCooling& companionCoolingHeatPump) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setCompanionCoolingHeatPump(companionCoolingHeatPump);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::loadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->loadSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::isLoadSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isLoadSideReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRHeating::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setLoadSideReferenceFlowRate(loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating::autosizeLoadSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedLoadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::sourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sourceSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::isSourceSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isSourceSideReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRHeating::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setSourceSideReferenceFlowRate(sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating::autosizeSourceSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedSourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::heatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRHeating::isHeatRecoveryReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isHeatRecoveryReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRHeating::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatRecoveryReferenceFlowRate(heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating::autosizeHeatRecoveryReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedHeatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::referenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->referenceCapacity();
}

bool HeatPumpPlantLoopEIRHeating::isReferenceCapacityAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->isReferenceCapacityAutosized();
}

bool HeatPumpPlantLoopEIRHeating::setReferenceCapacity(double referenceCapacity) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setReferenceCapacity(referenceCapacity);
}

void HeatPumpPlantLoopEIRHeating::autosizeReferenceCapacity() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizeReferenceCapacity();
}

boost::optional<double> HeatPumpPlantLoopEIRHeating::autosizedReferenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->autosizedReferenceCapacity();
}

double HeatPumpPlantLoopEIRHeating::referenceCoefficientofPerformance() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->referenceCoefficientofPerformance();
}

bool HeatPumpPlantLoopEIRHeating::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
}

double HeatPumpPlantLoopEIRHeating::sizingFactor() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sizingFactor();
}

bool HeatPumpPlantLoopEIRHeating::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setSizingFactor(sizingFactor);
}

Curve HeatPumpPlantLoopEIRHeating::capacityModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->capacityModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setCapacityModifierFunctionofTemperatureCurve(const Curve& capacityModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setCapacityModifierFunctionofTemperatureCurve(
    capacityModifierFunctionofTemperatureCurve);
}

Curve HeatPumpPlantLoopEIRHeating::electricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->electricInputtoOutputRatioModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
    electricInputtoOutputRatioModifierFunctionofTemperatureCurve);
}

Curve HeatPumpPlantLoopEIRHeating::electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve();
}

bool HeatPumpPlantLoopEIRHeating::setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(
    electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve);
}

double HeatPumpPlantLoopEIRHeating::heatingToCoolingCapacitySizingRatio() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatingToCoolingCapacitySizingRatio();
}

bool HeatPumpPlantLoopEIRHeating::setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatingToCoolingCapacitySizingRatio(heatingToCoolingCapacitySizingRatio);
}

std::string HeatPumpPlantLoopEIRHeating::heatPumpSizingMethod() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatPumpSizingMethod();
}

bool HeatPumpPlantLoopEIRHeating::setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatPumpSizingMethod(heatPumpSizingMethod);
}

std::string HeatPumpPlantLoopEIRHeating::controlType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->controlType();
}

bool HeatPumpPlantLoopEIRHeating::setControlType(const std::string& controlType) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setControlType(controlType);
}

std::string HeatPumpPlantLoopEIRHeating::flowMode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->flowMode();
}

bool HeatPumpPlantLoopEIRHeating::setFlowMode(const std::string& flowMode) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setFlowMode(flowMode);
}

double HeatPumpPlantLoopEIRHeating::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumPartLoadRatio();
}

bool HeatPumpPlantLoopEIRHeating::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double HeatPumpPlantLoopEIRHeating::minimumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumSourceInletTemperature();
}

bool HeatPumpPlantLoopEIRHeating::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumSourceInletTemperature(minimumSourceInletTemperature);
}

double HeatPumpPlantLoopEIRHeating::maximumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->maximumSourceInletTemperature();
}

bool HeatPumpPlantLoopEIRHeating::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMaximumSourceInletTemperature(maximumSourceInletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::minimumSupplyWaterTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumSupplyWaterTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setMinimumSupplyWaterTemperatureCurve(const Curve& minimumSupplyWaterTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumSupplyWaterTemperatureCurve(minimumSupplyWaterTemperatureCurve);
}

void HeatPumpPlantLoopEIRHeating::resetMinimumSupplyWaterTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetMinimumSupplyWaterTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::maximumSupplyWaterTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->maximumSupplyWaterTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setMaximumSupplyWaterTemperatureCurve(const Curve& maximumSupplyWaterTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMaximumSupplyWaterTemperatureCurve(maximumSupplyWaterTemperatureCurve);
}

void HeatPumpPlantLoopEIRHeating::resetMaximumSupplyWaterTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetMaximumSupplyWaterTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::dryOutdoorCorrectionFactorCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->dryOutdoorCorrectionFactorCurve();
}

bool HeatPumpPlantLoopEIRHeating::setDryOutdoorCorrectionFactorCurve(const Curve& dryOutdoorCorrectionFactorCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setDryOutdoorCorrectionFactorCurve(dryOutdoorCorrectionFactorCurve);
}

void HeatPumpPlantLoopEIRHeating::resetDryOutdoorCorrectionFactorCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetDryOutdoorCorrectionFactorCurve();
}

double HeatPumpPlantLoopEIRHeating::maximumOutdoorDryBulbTemperatureForDefrostOperation() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->maximumOutdoorDryBulbTemperatureForDefrostOperation();
}

bool HeatPumpPlantLoopEIRHeating::setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMaximumOutdoorDryBulbTemperatureForDefrostOperation(
    maximumOutdoorDryBulbTemperatureForDefrostOperation);
}

std::string HeatPumpPlantLoopEIRHeating::heatPumpDefrostControl() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatPumpDefrostControl();
}

bool HeatPumpPlantLoopEIRHeating::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatPumpDefrostControl(heatPumpDefrostControl);
}

double HeatPumpPlantLoopEIRHeating::heatPumpDefrostTimePeriodFraction() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatPumpDefrostTimePeriodFraction();
}

bool HeatPumpPlantLoopEIRHeating::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatPumpDefrostTimePeriodFraction(heatPumpDefrostTimePeriodFraction);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::defrostEnergyInputRatioFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->defrostEnergyInputRatioFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setDefrostEnergyInputRatioFunctionofTemperatureCurve(
  const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setDefrostEnergyInputRatioFunctionofTemperatureCurve(
    defrostEnergyInputRatioFunctionofTemperatureCurve);
}

void HeatPumpPlantLoopEIRHeating::resetDefrostEnergyInputRatioFunctionofTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::timedEmpiricalDefrostFrequencyCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->timedEmpiricalDefrostFrequencyCurve();
}

bool HeatPumpPlantLoopEIRHeating::setTimedEmpiricalDefrostFrequencyCurve(const Curve& timedEmpiricalDefrostFrequencyCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setTimedEmpiricalDefrostFrequencyCurve(timedEmpiricalDefrostFrequencyCurve);
}

void HeatPumpPlantLoopEIRHeating::resetTimedEmpiricalDefrostFrequencyCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetTimedEmpiricalDefrostFrequencyCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::timedEmpiricalDefrostHeatLoadPenaltyCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->timedEmpiricalDefrostHeatLoadPenaltyCurve();
}

bool HeatPumpPlantLoopEIRHeating::setTimedEmpiricalDefrostHeatLoadPenaltyCurve(const Curve& timedEmpiricalDefrostHeatLoadPenaltyCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setTimedEmpiricalDefrostHeatLoadPenaltyCurve(
    timedEmpiricalDefrostHeatLoadPenaltyCurve);
}

void HeatPumpPlantLoopEIRHeating::resetTimedEmpiricalDefrostHeatLoadPenaltyCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetTimedEmpiricalDefrostHeatLoadPenaltyCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::timedEmpiricalDefrostHeatInputEnergyFractionCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->timedEmpiricalDefrostHeatInputEnergyFractionCurve();
}

bool HeatPumpPlantLoopEIRHeating::setTimedEmpiricalDefrostHeatInputEnergyFractionCurve(
  const Curve& timedEmpiricalDefrostHeatInputEnergyFractionCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setTimedEmpiricalDefrostHeatInputEnergyFractionCurve(
    timedEmpiricalDefrostHeatInputEnergyFractionCurve);
}

void HeatPumpPlantLoopEIRHeating::resetTimedEmpiricalDefrostHeatInputEnergyFractionCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetTimedEmpiricalDefrostHeatInputEnergyFractionCurve();
}

double HeatPumpPlantLoopEIRHeating::minimumHeatRecoveryOutletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->minimumHeatRecoveryOutletTemperature();
}

bool HeatPumpPlantLoopEIRHeating::setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setMinimumHeatRecoveryOutletTemperature(minimumHeatRecoveryOutletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::heatRecoveryCapacityModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryCapacityModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryCapacityModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(
    heatRecoveryCapacityModifierFunctionofTemperatureCurve);
}

void HeatPumpPlantLoopEIRHeating::resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating::heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRHeating::setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
    heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve);
}

void HeatPumpPlantLoopEIRHeating::resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRHeating::loadSideWaterLoop() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->loadSideWaterLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRHeating::sourceSideWaterLoop() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sourceSideWaterLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRHeating::heatRecoveryLoop() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryLoop();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating::sourceSideWaterInletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sourceSideWaterInletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating::sourceSideWaterOutletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->sourceSideWaterOutletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating::loadSideWaterInletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->loadSideWaterInletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating::loadSideWaterOutletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->loadSideWaterOutletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating::heatRecoveryInletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryInletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating::heatRecoveryOutletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRHeating_Impl>()->heatRecoveryOutletNode();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HeatPumpPlantLoopEIRHeating_Impl::condenserType() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setCondenserType(const std::string& condenserType) {
  if (openstudio::istringEqual("AirSource", condenserType) && secondaryPlantLoop()) {
    return false;
  }
  if (openstudio::istringEqual("WaterSource", condenserType) && !secondaryPlantLoop()) {
    return false;
  }
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, condenserType);
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRHeating_Impl::loadSideWaterLoop() const {
  return WaterToWaterComponent_Impl::plantLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRHeating_Impl::sourceSideWaterLoop() const {
  return WaterToWaterComponent_Impl::secondaryPlantLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryLoop() const {
  return WaterToWaterComponent_Impl::tertiaryPlantLoop();
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating_Impl::sourceSideWaterInletNode() const {
  if (auto mo = demandInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating_Impl::sourceSideWaterOutletNode() const {
  if (auto mo = demandOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating_Impl::loadSideWaterInletNode() const {
  if (auto mo = supplyInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating_Impl::loadSideWaterOutletNode() const {
  if (auto mo = supplyOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryInletNode() const {
  if (auto mo = tertiaryInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryOutletNode() const {
  if (auto mo = tertiaryOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

bool HeatPumpPlantLoopEIRHeating_Impl::addToNode(Node& node) {
  if (auto loop = node.plantLoop()) {
    if (loop->demandComponent(node.handle())) {
      if (auto sourceLoop = sourceSideWaterLoop()) {
        if (loop->handle() != sourceLoop->handle()) {
          if (!heatRecoveryLoop()) {
            return addToTertiaryNode(node);
          }
        }
      }
    }
  }

  const bool ok = WaterToWaterComponent_Impl::addToNode(node);
  if (ok && sourceSideWaterLoop()) {
    setCondenserType("WaterSource");
  }
  return ok;
}

bool HeatPumpPlantLoopEIRHeating_Impl::addToTertiaryNode(Node& node) {
  if (auto loop = node.plantLoop()) {
    if (loop->demandComponent(node.handle())) {
      return WaterToWaterComponent_Impl::addToTertiaryNode(node);
    }
  }
  return false;
}

bool HeatPumpPlantLoopEIRHeating_Impl::removeFromSecondaryPlantLoop() {
  const bool ok = WaterToWaterComponent_Impl::removeFromSecondaryPlantLoop();
  setCondenserType("AirSource");
  return ok;
}

boost::optional<HeatPumpPlantLoopEIRCooling> HeatPumpPlantLoopEIRHeating_Impl::companionCoolingHeatPump() const {
  return getObject<ModelObject>().getModelObjectTarget<HeatPumpPlantLoopEIRCooling>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setCompanionCoolingHeatPump(const HeatPumpPlantLoopEIRCooling& companionCoolingHeatPump) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName, companionCoolingHeatPump.handle());
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::loadSideReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isLoadSideReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeLoadSideReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedLoadSideReferenceFlowRate() const {
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::sourceSideReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isSourceSideReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeSourceSideReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedSourceSideReferenceFlowRate() const {
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isHeatRecoveryReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeHeatRecoveryReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedHeatRecoveryReferenceFlowRate() const {
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::referenceCapacity() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, true);
}

bool HeatPumpPlantLoopEIRHeating_Impl::isReferenceCapacityAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setReferenceCapacity(double referenceCapacity) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, referenceCapacity);
}

void HeatPumpPlantLoopEIRHeating_Impl::autosizeReferenceCapacity() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRHeating_Impl::autosizedReferenceCapacity() const {
  return boost::none;
}

double HeatPumpPlantLoopEIRHeating_Impl::referenceCoefficientofPerformance() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
}

double HeatPumpPlantLoopEIRHeating_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, sizingFactor);
}

Curve HeatPumpPlantLoopEIRHeating_Impl::capacityModifierFunctionofTemperatureCurve() const {
  auto result =
    getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CapacityModifierFunctionofTemperatureCurveName);
  OS_ASSERT(result);
  return *result;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setCapacityModifierFunctionofTemperatureCurve(const Curve& capacityModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::CapacityModifierFunctionofTemperatureCurveName,
                    capacityModifierFunctionofTemperatureCurve.handle());
}

Curve HeatPumpPlantLoopEIRHeating_Impl::electricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName);
  OS_ASSERT(result);
  return *result;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName,
                    electricInputtoOutputRatioModifierFunctionofTemperatureCurve.handle());
}

Curve HeatPumpPlantLoopEIRHeating_Impl::electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve() const {
  auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName);
  OS_ASSERT(result);
  return *result;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName,
                    electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve.handle());
}

double HeatPumpPlantLoopEIRHeating_Impl::heatingToCoolingCapacitySizingRatio() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatingToCoolingCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatingToCoolingCapacitySizingRatio(double heatingToCoolingCapacitySizingRatio) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatingToCoolingCapacitySizingRatio, heatingToCoolingCapacitySizingRatio);
}

std::string HeatPumpPlantLoopEIRHeating_Impl::heatPumpSizingMethod() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpSizingMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatPumpSizingMethod(const std::string& heatPumpSizingMethod) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpSizingMethod, heatPumpSizingMethod);
}

std::string HeatPumpPlantLoopEIRHeating_Impl::controlType() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::ControlType, controlType);
}

std::string HeatPumpPlantLoopEIRHeating_Impl::flowMode() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::FlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setFlowMode(const std::string& flowMode) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::FlowMode, flowMode);
}

double HeatPumpPlantLoopEIRHeating_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

double HeatPumpPlantLoopEIRHeating_Impl::minimumSourceInletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSourceInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSourceInletTemperature, minimumSourceInletTemperature);
}

double HeatPumpPlantLoopEIRHeating_Impl::maximumSourceInletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSourceInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSourceInletTemperature, maximumSourceInletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::minimumSupplyWaterTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSupplyWaterTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumSupplyWaterTemperatureCurve(const Curve& minimumSupplyWaterTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSupplyWaterTemperatureCurveName,
                    minimumSupplyWaterTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetMinimumSupplyWaterTemperatureCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumSupplyWaterTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::maximumSupplyWaterTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSupplyWaterTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMaximumSupplyWaterTemperatureCurve(const Curve& maximumSupplyWaterTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSupplyWaterTemperatureCurveName,
                    maximumSupplyWaterTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetMaximumSupplyWaterTemperatureCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumSupplyWaterTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::dryOutdoorCorrectionFactorCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::DryOutdoorCorrectionFactorCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setDryOutdoorCorrectionFactorCurve(const Curve& dryOutdoorCorrectionFactorCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::DryOutdoorCorrectionFactorCurveName, dryOutdoorCorrectionFactorCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetDryOutdoorCorrectionFactorCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::DryOutdoorCorrectionFactorCurveName, "");
  OS_ASSERT(result);
}

double HeatPumpPlantLoopEIRHeating_Impl::maximumOutdoorDryBulbTemperatureForDefrostOperation() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMaximumOutdoorDryBulbTemperatureForDefrostOperation(
  double maximumOutdoorDryBulbTemperatureForDefrostOperation) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation,
                   maximumOutdoorDryBulbTemperatureForDefrostOperation);
}

std::string HeatPumpPlantLoopEIRHeating_Impl::heatPumpDefrostControl() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostControl, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostControl, heatPumpDefrostControl);
}

double HeatPumpPlantLoopEIRHeating_Impl::heatPumpDefrostTimePeriodFraction() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostTimePeriodFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostTimePeriodFraction, heatPumpDefrostTimePeriodFraction);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::defrostEnergyInputRatioFunctionofTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setDefrostEnergyInputRatioFunctionofTemperatureCurve(
  const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName,
                    defrostEnergyInputRatioFunctionofTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetDefrostEnergyInputRatioFunctionofTemperatureCurve() {
  const bool result =
    setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::timedEmpiricalDefrostFrequencyCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostFrequencyCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setTimedEmpiricalDefrostFrequencyCurve(const Curve& timedEmpiricalDefrostFrequencyCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostFrequencyCurveName,
                    timedEmpiricalDefrostFrequencyCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetTimedEmpiricalDefrostFrequencyCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostFrequencyCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::timedEmpiricalDefrostHeatLoadPenaltyCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatLoadPenaltyCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setTimedEmpiricalDefrostHeatLoadPenaltyCurve(const Curve& timedEmpiricalDefrostHeatLoadPenaltyCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatLoadPenaltyCurveName,
                    timedEmpiricalDefrostHeatLoadPenaltyCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetTimedEmpiricalDefrostHeatLoadPenaltyCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatLoadPenaltyCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::timedEmpiricalDefrostHeatInputEnergyFractionCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatInputEnergyFractionCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setTimedEmpiricalDefrostHeatInputEnergyFractionCurve(
  const Curve& timedEmpiricalDefrostHeatInputEnergyFractionCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatInputEnergyFractionCurveName,
                    timedEmpiricalDefrostHeatInputEnergyFractionCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetTimedEmpiricalDefrostHeatInputEnergyFractionCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatInputEnergyFractionCurveName, "");
  OS_ASSERT(result);
}

double HeatPumpPlantLoopEIRHeating_Impl::minimumHeatRecoveryOutletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumHeatRecoveryOutletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRHeating_Impl::setMinimumHeatRecoveryOutletTemperature(double minimumHeatRecoveryOutletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::MinimumHeatRecoveryOutletTemperature, minimumHeatRecoveryOutletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryCapacityModifierFunctionofTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryCapacityModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName,
                    heatRecoveryCapacityModifierFunctionofTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRHeating_Impl::heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRHeating_Impl::setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName,
                    heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRHeating_Impl::resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() {
  const bool result =
    setString(openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "");
  OS_ASSERT(result);
}

std::vector<std::string> HeatPumpPlantLoopEIRHeating_Impl::condenserTypeValues() const {
  return openstudio::epmodel::HeatPumpPlantLoopEIRHeating::condenserTypeValues();
}

unsigned HeatPumpPlantLoopEIRHeating_Impl::supplyInletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideInletNodeName;
}

unsigned HeatPumpPlantLoopEIRHeating_Impl::supplyOutletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_HeatingFields::LoadSideOutletNodeName;
}

unsigned HeatPumpPlantLoopEIRHeating_Impl::demandInletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideInletNodeName;
}

unsigned HeatPumpPlantLoopEIRHeating_Impl::demandOutletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_HeatingFields::SourceSideOutletNodeName;
}

unsigned HeatPumpPlantLoopEIRHeating_Impl::tertiaryInletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryInletNodeName;
}

unsigned HeatPumpPlantLoopEIRHeating_Impl::tertiaryOutletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_HeatingFields::HeatRecoveryOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
