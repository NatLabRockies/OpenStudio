/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRCooling_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"
#include "WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Cooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

HeatPumpPlantLoopEIRCooling::HeatPumpPlantLoopEIRCooling(const Model& model, const Curve& capacityModifierFunctionofTemperatureCurve,
                                                         const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve,
                                                         const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve)
  : WaterToWaterComponent(HeatPumpPlantLoopEIRCooling::iddObjectType(), model) {
  autosizeLoadSideReferenceFlowRate();
  autosizeSourceSideReferenceFlowRate();
  autosizeHeatRecoveryReferenceFlowRate();
  autosizeReferenceCapacity();
  OS_ASSERT(setCapacityModifierFunctionofTemperatureCurve(capacityModifierFunctionofTemperatureCurve));
  OS_ASSERT(setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(electricInputtoOutputRatioModifierFunctionofTemperatureCurve));
  OS_ASSERT(setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve));
  OS_ASSERT(setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, "AirSource"));
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setFlowMode("ConstantFlow"));
  OS_ASSERT(setMinimumPartLoadRatio(0.0));
  OS_ASSERT(setMinimumSourceInletTemperature(-100.0));
  OS_ASSERT(setMaximumSourceInletTemperature(100.0));
  OS_ASSERT(setMaximumHeatRecoveryOutletTemperature(60.0));
  OS_ASSERT(setThermosiphonMinimumTemperatureDifference(0.0));
}

HeatPumpPlantLoopEIRCooling::HeatPumpPlantLoopEIRCooling(const Model& model)
  : WaterToWaterComponent(HeatPumpPlantLoopEIRCooling::iddObjectType(), model) {
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

  OS_ASSERT(setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, "AirSource"));
  OS_ASSERT(setReferenceCoefficientofPerformance(7.5));
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setControlType("Load"));
  OS_ASSERT(setFlowMode("ConstantFlow"));
  OS_ASSERT(setMinimumPartLoadRatio(0.0));
  OS_ASSERT(setMinimumSourceInletTemperature(-100.0));
  OS_ASSERT(setMaximumSourceInletTemperature(100.0));
  OS_ASSERT(setMaximumHeatRecoveryOutletTemperature(60.0));
  OS_ASSERT(setThermosiphonMinimumTemperatureDifference(0.0));
}

HeatPumpPlantLoopEIRCooling::HeatPumpPlantLoopEIRCooling(std::shared_ptr<detail::HeatPumpPlantLoopEIRCooling_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType HeatPumpPlantLoopEIRCooling::iddObjectType() {
  return IddObjectType::HeatPump_PlantLoop_EIR_Cooling;
}

std::vector<std::string> HeatPumpPlantLoopEIRCooling::validCondenserTypeValues() {
  return HeatPumpPlantLoopEIRCooling::condenserTypeValues();
}

std::vector<std::string> HeatPumpPlantLoopEIRCooling::condenserTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType);
}

std::string HeatPumpPlantLoopEIRCooling::condenserType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->condenserType();
}

bool HeatPumpPlantLoopEIRCooling::setCondenserType(const std::string& condenserType) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setCondenserType(condenserType);
}

boost::optional<HeatPumpPlantLoopEIRHeating> HeatPumpPlantLoopEIRCooling::companionHeatingHeatPump() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->companionHeatingHeatPump();
}

bool HeatPumpPlantLoopEIRCooling::setCompanionHeatingHeatPump(const HeatPumpPlantLoopEIRHeating& companionHeatingHeatPump) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setCompanionHeatingHeatPump(companionHeatingHeatPump);
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::loadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->loadSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRCooling::isLoadSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isLoadSideReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setLoadSideReferenceFlowRate(loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling::autosizeLoadSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedLoadSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedLoadSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::sourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sourceSideReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRCooling::isSourceSideReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isSourceSideReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setSourceSideReferenceFlowRate(sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling::autosizeSourceSideReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedSourceSideReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedSourceSideReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::heatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryReferenceFlowRate();
}

bool HeatPumpPlantLoopEIRCooling::isHeatRecoveryReferenceFlowRateAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isHeatRecoveryReferenceFlowRateAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setHeatRecoveryReferenceFlowRate(heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling::autosizeHeatRecoveryReferenceFlowRate() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedHeatRecoveryReferenceFlowRate() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedHeatRecoveryReferenceFlowRate();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::referenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->referenceCapacity();
}

bool HeatPumpPlantLoopEIRCooling::isReferenceCapacityAutosized() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->isReferenceCapacityAutosized();
}

bool HeatPumpPlantLoopEIRCooling::setReferenceCapacity(double referenceCapacity) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setReferenceCapacity(referenceCapacity);
}

void HeatPumpPlantLoopEIRCooling::autosizeReferenceCapacity() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizeReferenceCapacity();
}

boost::optional<double> HeatPumpPlantLoopEIRCooling::autosizedReferenceCapacity() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->autosizedReferenceCapacity();
}

double HeatPumpPlantLoopEIRCooling::referenceCoefficientofPerformance() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->referenceCoefficientofPerformance();
}

bool HeatPumpPlantLoopEIRCooling::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setReferenceCoefficientofPerformance(referenceCoefficientofPerformance);
}

double HeatPumpPlantLoopEIRCooling::sizingFactor() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sizingFactor();
}

bool HeatPumpPlantLoopEIRCooling::setSizingFactor(double sizingFactor) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setSizingFactor(sizingFactor);
}

Curve HeatPumpPlantLoopEIRCooling::capacityModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->capacityModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRCooling::setCapacityModifierFunctionofTemperatureCurve(const Curve& capacityModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setCapacityModifierFunctionofTemperatureCurve(
    capacityModifierFunctionofTemperatureCurve);
}

Curve HeatPumpPlantLoopEIRCooling::electricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->electricInputtoOutputRatioModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRCooling::setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
    electricInputtoOutputRatioModifierFunctionofTemperatureCurve);
}

Curve HeatPumpPlantLoopEIRCooling::electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve();
}

bool HeatPumpPlantLoopEIRCooling::setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(
    electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve);
}

std::string HeatPumpPlantLoopEIRCooling::controlType() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->controlType();
}

bool HeatPumpPlantLoopEIRCooling::setControlType(const std::string& controlType) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setControlType(controlType);
}

std::string HeatPumpPlantLoopEIRCooling::flowMode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->flowMode();
}

bool HeatPumpPlantLoopEIRCooling::setFlowMode(const std::string& flowMode) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setFlowMode(flowMode);
}

double HeatPumpPlantLoopEIRCooling::minimumPartLoadRatio() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->minimumPartLoadRatio();
}

bool HeatPumpPlantLoopEIRCooling::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double HeatPumpPlantLoopEIRCooling::minimumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->minimumSourceInletTemperature();
}

bool HeatPumpPlantLoopEIRCooling::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMinimumSourceInletTemperature(minimumSourceInletTemperature);
}

double HeatPumpPlantLoopEIRCooling::maximumSourceInletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->maximumSourceInletTemperature();
}

bool HeatPumpPlantLoopEIRCooling::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMaximumSourceInletTemperature(maximumSourceInletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling::minimumSupplyWaterTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->minimumSupplyWaterTemperatureCurve();
}

bool HeatPumpPlantLoopEIRCooling::setMinimumSupplyWaterTemperatureCurve(const Curve& minimumSupplyWaterTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMinimumSupplyWaterTemperatureCurve(minimumSupplyWaterTemperatureCurve);
}

void HeatPumpPlantLoopEIRCooling::resetMinimumSupplyWaterTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->resetMinimumSupplyWaterTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling::maximumSupplyWaterTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->maximumSupplyWaterTemperatureCurve();
}

bool HeatPumpPlantLoopEIRCooling::setMaximumSupplyWaterTemperatureCurve(const Curve& maximumSupplyWaterTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMaximumSupplyWaterTemperatureCurve(maximumSupplyWaterTemperatureCurve);
}

void HeatPumpPlantLoopEIRCooling::resetMaximumSupplyWaterTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->resetMaximumSupplyWaterTemperatureCurve();
}

double HeatPumpPlantLoopEIRCooling::maximumHeatRecoveryOutletTemperature() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->maximumHeatRecoveryOutletTemperature();
}

bool HeatPumpPlantLoopEIRCooling::setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setMaximumHeatRecoveryOutletTemperature(maximumHeatRecoveryOutletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling::heatRecoveryCapacityModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryCapacityModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRCooling::setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryCapacityModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(
    heatRecoveryCapacityModifierFunctionofTemperatureCurve);
}

void HeatPumpPlantLoopEIRCooling::resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling::heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();
}

bool HeatPumpPlantLoopEIRCooling::setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
    heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve);
}

void HeatPumpPlantLoopEIRCooling::resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling::thermosiphonCapacityFractionCurve() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->thermosiphonCapacityFractionCurve();
}

bool HeatPumpPlantLoopEIRCooling::setThermosiphonCapacityFractionCurve(const Curve& thermosiphonCapacityFractionCurve) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setThermosiphonCapacityFractionCurve(thermosiphonCapacityFractionCurve);
}

void HeatPumpPlantLoopEIRCooling::resetThermosiphonCapacityFractionCurve() {
  getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->resetThermosiphonCapacityFractionCurve();
}

double HeatPumpPlantLoopEIRCooling::thermosiphonMinimumTemperatureDifference() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->thermosiphonMinimumTemperatureDifference();
}

bool HeatPumpPlantLoopEIRCooling::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->setThermosiphonMinimumTemperatureDifference(thermosiphonMinimumTemperatureDifference);
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRCooling::loadSideWaterLoop() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->loadSideWaterLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRCooling::sourceSideWaterLoop() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sourceSideWaterLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRCooling::heatRecoveryLoop() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryLoop();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling::sourceSideWaterInletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sourceSideWaterInletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling::sourceSideWaterOutletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->sourceSideWaterOutletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling::loadSideWaterInletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->loadSideWaterInletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling::loadSideWaterOutletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->loadSideWaterOutletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling::heatRecoveryInletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryInletNode();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling::heatRecoveryOutletNode() const {
  return getImpl<detail::HeatPumpPlantLoopEIRCooling_Impl>()->heatRecoveryOutletNode();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string HeatPumpPlantLoopEIRCooling_Impl::condenserType() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setCondenserType(const std::string& condenserType) {
  if (openstudio::istringEqual("AirSource", condenserType) && secondaryPlantLoop()) {
    return false;
  }
  if (openstudio::istringEqual("WaterSource", condenserType) && !secondaryPlantLoop()) {
    return false;
  }
  return setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CondenserType, condenserType);
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRCooling_Impl::loadSideWaterLoop() const {
  return WaterToWaterComponent_Impl::plantLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRCooling_Impl::sourceSideWaterLoop() const {
  return WaterToWaterComponent_Impl::secondaryPlantLoop();
}

boost::optional<PlantLoop> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryLoop() const {
  return WaterToWaterComponent_Impl::tertiaryPlantLoop();
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling_Impl::sourceSideWaterInletNode() const {
  if (auto mo = demandInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling_Impl::sourceSideWaterOutletNode() const {
  if (auto mo = demandOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling_Impl::loadSideWaterInletNode() const {
  if (auto mo = supplyInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling_Impl::loadSideWaterOutletNode() const {
  if (auto mo = supplyOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryInletNode() const {
  if (auto mo = tertiaryInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryOutletNode() const {
  if (auto mo = tertiaryOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

bool HeatPumpPlantLoopEIRCooling_Impl::addToNode(Node& node) {
  if (shouldRouteDemandSideNodeToTertiary(node)) {
    return addToTertiaryNode(node);
  }

  const bool ok = WaterToWaterComponent_Impl::addToNode(node);
  if (sourceSideWaterLoop()) {
    setCondenserType("WaterSource");
  }
  return ok;
}

bool HeatPumpPlantLoopEIRCooling_Impl::addToTertiaryNode(Node& node) {
  return addToDemandSideTertiaryNode(node);
}

bool HeatPumpPlantLoopEIRCooling_Impl::removeFromSecondaryPlantLoop() {
  const bool ok = WaterToWaterComponent_Impl::removeFromSecondaryPlantLoop();
  setCondenserType("AirSource");
  return ok;
}

boost::optional<HeatPumpPlantLoopEIRHeating> HeatPumpPlantLoopEIRCooling_Impl::companionHeatingHeatPump() const {
  return getObject<ModelObject>().getModelObjectTarget<HeatPumpPlantLoopEIRHeating>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CompanionHeatPumpName);
}

bool HeatPumpPlantLoopEIRCooling_Impl::setCompanionHeatingHeatPump(const HeatPumpPlantLoopEIRHeating& companionHeatingHeatPump) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CompanionHeatPumpName, companionHeatingHeatPump.handle());
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::loadSideReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRCooling_Impl::isLoadSideReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setLoadSideReferenceFlowRate(double loadSideReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, loadSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling_Impl::autosizeLoadSideReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedLoadSideReferenceFlowRate() const {
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::sourceSideReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRCooling_Impl::isSourceSideReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setSourceSideReferenceFlowRate(double sourceSideReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, sourceSideReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling_Impl::autosizeSourceSideReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedSourceSideReferenceFlowRate() const {
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryReferenceFlowRate() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, true);
}

bool HeatPumpPlantLoopEIRCooling_Impl::isHeatRecoveryReferenceFlowRateAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setHeatRecoveryReferenceFlowRate(double heatRecoveryReferenceFlowRate) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, heatRecoveryReferenceFlowRate);
}

void HeatPumpPlantLoopEIRCooling_Impl::autosizeHeatRecoveryReferenceFlowRate() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryReferenceFlowRate, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedHeatRecoveryReferenceFlowRate() const {
  return boost::none;
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::referenceCapacity() const {
  return getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, true);
}

bool HeatPumpPlantLoopEIRCooling_Impl::isReferenceCapacityAutosized() const {
  if (auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setReferenceCapacity(double referenceCapacity) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, referenceCapacity);
}

void HeatPumpPlantLoopEIRCooling_Impl::autosizeReferenceCapacity() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCapacity, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> HeatPumpPlantLoopEIRCooling_Impl::autosizedReferenceCapacity() const {
  return boost::none;
}

double HeatPumpPlantLoopEIRCooling_Impl::referenceCoefficientofPerformance() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCoefficientofPerformance, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setReferenceCoefficientofPerformance(double referenceCoefficientofPerformance) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ReferenceCoefficientofPerformance, referenceCoefficientofPerformance);
}

double HeatPumpPlantLoopEIRCooling_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SizingFactor, sizingFactor);
}

Curve HeatPumpPlantLoopEIRCooling_Impl::capacityModifierFunctionofTemperatureCurve() const {
  auto result =
    getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CapacityModifierFunctionofTemperatureCurveName);
  OS_ASSERT(result);
  return *result;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setCapacityModifierFunctionofTemperatureCurve(const Curve& capacityModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::CapacityModifierFunctionofTemperatureCurveName,
                    capacityModifierFunctionofTemperatureCurve.handle());
}

Curve HeatPumpPlantLoopEIRCooling_Impl::electricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName);
  OS_ASSERT(result);
  return *result;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName,
                    electricInputtoOutputRatioModifierFunctionofTemperatureCurve.handle());
}

Curve HeatPumpPlantLoopEIRCooling_Impl::electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve() const {
  auto result = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName);
  OS_ASSERT(result);
  return *result;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(
  const Curve& electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName,
                    electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve.handle());
}

std::string HeatPumpPlantLoopEIRCooling_Impl::controlType() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ControlType, controlType);
}

std::string HeatPumpPlantLoopEIRCooling_Impl::flowMode() const {
  const auto value = getString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::FlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setFlowMode(const std::string& flowMode) {
  return setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::FlowMode, flowMode);
}

double HeatPumpPlantLoopEIRCooling_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

double HeatPumpPlantLoopEIRCooling_Impl::minimumSourceInletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSourceInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setMinimumSourceInletTemperature(double minimumSourceInletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSourceInletTemperature, minimumSourceInletTemperature);
}

double HeatPumpPlantLoopEIRCooling_Impl::maximumSourceInletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSourceInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setMaximumSourceInletTemperature(double maximumSourceInletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSourceInletTemperature, maximumSourceInletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling_Impl::minimumSupplyWaterTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSupplyWaterTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRCooling_Impl::setMinimumSupplyWaterTemperatureCurve(const Curve& minimumSupplyWaterTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSupplyWaterTemperatureCurveName,
                    minimumSupplyWaterTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRCooling_Impl::resetMinimumSupplyWaterTemperatureCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MinimumSupplyWaterTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling_Impl::maximumSupplyWaterTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSupplyWaterTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRCooling_Impl::setMaximumSupplyWaterTemperatureCurve(const Curve& maximumSupplyWaterTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSupplyWaterTemperatureCurveName,
                    maximumSupplyWaterTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRCooling_Impl::resetMaximumSupplyWaterTemperatureCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumSupplyWaterTemperatureCurveName, "");
  OS_ASSERT(result);
}

double HeatPumpPlantLoopEIRCooling_Impl::maximumHeatRecoveryOutletTemperature() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumHeatRecoveryOutletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setMaximumHeatRecoveryOutletTemperature(double maximumHeatRecoveryOutletTemperature) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::MaximumHeatRecoveryOutletTemperature, maximumHeatRecoveryOutletTemperature);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryCapacityModifierFunctionofTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRCooling_Impl::setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryCapacityModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName,
                    heatRecoveryCapacityModifierFunctionofTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRCooling_Impl::resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryCapacityModifierFunctionofTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling_Impl::heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName);
}

bool HeatPumpPlantLoopEIRCooling_Impl::setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(
  const Curve& heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName,
                    heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve.handle());
}

void HeatPumpPlantLoopEIRCooling_Impl::resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve() {
  const bool result =
    setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "");
  OS_ASSERT(result);
}

boost::optional<Curve> HeatPumpPlantLoopEIRCooling_Impl::thermosiphonCapacityFractionCurve() const {
  return getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonCapacityFractionCurveName);
}

bool HeatPumpPlantLoopEIRCooling_Impl::setThermosiphonCapacityFractionCurve(const Curve& thermosiphonCapacityFractionCurve) {
  return setPointer(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonCapacityFractionCurveName,
                    thermosiphonCapacityFractionCurve.handle());
}

void HeatPumpPlantLoopEIRCooling_Impl::resetThermosiphonCapacityFractionCurve() {
  const bool result = setString(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonCapacityFractionCurveName, "");
  OS_ASSERT(result);
}

double HeatPumpPlantLoopEIRCooling_Impl::thermosiphonMinimumTemperatureDifference() const {
  const auto value = getDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonMinimumTemperatureDifference, true);
  OS_ASSERT(value);
  return *value;
}

bool HeatPumpPlantLoopEIRCooling_Impl::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
  return setDouble(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::ThermosiphonMinimumTemperatureDifference,
                   thermosiphonMinimumTemperatureDifference);
}

std::vector<std::string> HeatPumpPlantLoopEIRCooling_Impl::condenserTypeValues() const {
  return openstudio::epmodel::HeatPumpPlantLoopEIRCooling::condenserTypeValues();
}

unsigned HeatPumpPlantLoopEIRCooling_Impl::supplyInletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideInletNodeName;
}

unsigned HeatPumpPlantLoopEIRCooling_Impl::supplyOutletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideOutletNodeName;
}

unsigned HeatPumpPlantLoopEIRCooling_Impl::demandInletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName;
}

unsigned HeatPumpPlantLoopEIRCooling_Impl::demandOutletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName;
}

unsigned HeatPumpPlantLoopEIRCooling_Impl::tertiaryInletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName;
}

unsigned HeatPumpPlantLoopEIRCooling_Impl::tertiaryOutletPort() const {
  return openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
