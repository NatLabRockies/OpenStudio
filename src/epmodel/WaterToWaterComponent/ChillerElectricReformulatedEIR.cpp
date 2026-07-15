/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp"
#include "WaterToWaterComponent/ChillerElectricReformulatedEIR_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBicubic.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Electric_ReformulatedEIR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  ChillerElectricReformulatedEIR::ChillerElectricReformulatedEIR(const Model& model, const Curve& CCFofT, const Curve& EItoCORFofT,
                                                                 const Curve& EItoCORFofPLR)
    : WaterToWaterComponent(ChillerElectricReformulatedEIR::iddObjectType(), model) {
    OS_ASSERT(setCoolingCapacityFunctionOfTemperature(CCFofT));
    OS_ASSERT(setElectricInputToCoolingOutputRatioFunctionOfTemperature(EItoCORFofT));
    OS_ASSERT(setElectricInputToCoolingOutputRatioFunctionOfPLR(EItoCORFofPLR));
    OS_ASSERT(setReferenceCOP(3.99));
    autosizeReferenceCapacity();
    autosizeReferenceChilledWaterFlowRate();
    autosizeReferenceCondenserWaterFlowRate();
    autosizeDesignHeatRecoveryWaterFlowRate();
    OS_ASSERT(setCondenserHeatRecoveryRelativeCapacityFraction(1.0));
    resetHeatRecoveryLeavingTemperatureSetpointNode();
    resetHeatRecoveryInletHighTemperatureLimitSchedule();
    OS_ASSERT(setEndUseSubcategory("General"));
    OS_ASSERT(setCondenserFlowControl("ConstantFlow"));
    OS_ASSERT(setCondenserMinimumFlowFraction(0.2));
    OS_ASSERT(setThermosiphonMinimumTemperatureDifference(0.0));
  }

  ChillerElectricReformulatedEIR::ChillerElectricReformulatedEIR(const Model& model)
    : WaterToWaterComponent(ChillerElectricReformulatedEIR::iddObjectType(), model) {
    CurveBiquadratic CCFofT(model);
    OS_ASSERT(CCFofT.setCoefficient1Constant(0.958546443));
    OS_ASSERT(CCFofT.setCoefficient2x(0.035168695));
    OS_ASSERT(CCFofT.setCoefficient3xPOW2(0.000124662));
    OS_ASSERT(CCFofT.setCoefficient4y(-0.00274551));
    OS_ASSERT(CCFofT.setCoefficient5yPOW2(-0.00005000));
    OS_ASSERT(CCFofT.setCoefficient6xTIMESY(-0.00017234));
    OS_ASSERT(CCFofT.setMinimumValueofx(5.0));
    OS_ASSERT(CCFofT.setMaximumValueofx(10.0));
    OS_ASSERT(CCFofT.setMinimumValueofy(20.0));
    OS_ASSERT(CCFofT.setMaximumValueofy(40.94));

    CurveBiquadratic EIRToCorfOfT(model);
    OS_ASSERT(EIRToCorfOfT.setCoefficient1Constant(0.732700123));
    OS_ASSERT(EIRToCorfOfT.setCoefficient2x(-0.00834360));
    OS_ASSERT(EIRToCorfOfT.setCoefficient3xPOW2(0.000638530));
    OS_ASSERT(EIRToCorfOfT.setCoefficient4y(-0.00303753));
    OS_ASSERT(EIRToCorfOfT.setCoefficient5yPOW2(0.000484952));
    OS_ASSERT(EIRToCorfOfT.setCoefficient6xTIMESY(-0.00083584));
    OS_ASSERT(EIRToCorfOfT.setMinimumValueofx(5.0));
    OS_ASSERT(EIRToCorfOfT.setMaximumValueofx(10.0));
    OS_ASSERT(EIRToCorfOfT.setMinimumValueofy(20.0));
    OS_ASSERT(EIRToCorfOfT.setMaximumValueofy(40.94));

    CurveBicubic EIRToCorfOfPLR(model);
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient1Constant(0.070862846));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient2x(0.002787560));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient3xPOW2(-0.00000891));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient4y(0.230973399));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient5yPOW2(1.250442176));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient6xTIMESY(-0.00216102));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient7xPOW3(0.000000));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient8yPOW3(-0.56300936));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient9xPOW2TIMESY(0.000000));
    OS_ASSERT(EIRToCorfOfPLR.setCoefficient10xTIMESYPOW2(0.000000));
    OS_ASSERT(EIRToCorfOfPLR.setMinimumValueofx(20.0));
    OS_ASSERT(EIRToCorfOfPLR.setMaximumValueofx(40.94));
    OS_ASSERT(EIRToCorfOfPLR.setMinimumValueofy(0.01));
    OS_ASSERT(EIRToCorfOfPLR.setMaximumValueofy(1.0));

    OS_ASSERT(setCoolingCapacityFunctionOfTemperature(CCFofT));
    OS_ASSERT(setElectricInputToCoolingOutputRatioFunctionOfTemperature(EIRToCorfOfT));
    OS_ASSERT(setElectricInputToCoolingOutputRatioFunctionOfPLR(EIRToCorfOfPLR));
    OS_ASSERT(setReferenceCOP(3.99));
    autosizeReferenceCapacity();
    autosizeReferenceChilledWaterFlowRate();
    autosizeReferenceCondenserWaterFlowRate();
    autosizeDesignHeatRecoveryWaterFlowRate();
    OS_ASSERT(setCondenserHeatRecoveryRelativeCapacityFraction(1.0));
    resetHeatRecoveryLeavingTemperatureSetpointNode();
    resetHeatRecoveryInletHighTemperatureLimitSchedule();
    OS_ASSERT(setEndUseSubcategory("General"));
    OS_ASSERT(setCondenserFlowControl("ConstantFlow"));
    OS_ASSERT(setCondenserMinimumFlowFraction(0.2));
    OS_ASSERT(setThermosiphonMinimumTemperatureDifference(0.0));
  }

  ChillerElectricReformulatedEIR::ChillerElectricReformulatedEIR(std::shared_ptr<detail::ChillerElectricReformulatedEIR_Impl> impl)
    : WaterToWaterComponent(std::move(impl)) {}

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
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceLeavingChilledWaterTemperature(
      referenceLeavingChilledWaterTemperature);
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
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setReferenceLeavingCondenserWaterTemperature(
      referenceLeavingCondenserWaterTemperature);
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

  Curve ChillerElectricReformulatedEIR::coolingCapacityFunctionOfTemperature() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->coolingCapacityFunctionOfTemperature();
  }

  bool ChillerElectricReformulatedEIR::setCoolingCapacityFunctionOfTemperature(const Curve& curve) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setCoolingCapacityFunctionOfTemperature(curve);
  }

  Curve ChillerElectricReformulatedEIR::electricInputToCoolingOutputRatioFunctionOfTemperature() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->electricInputToCoolingOutputRatioFunctionOfTemperature();
  }

  bool ChillerElectricReformulatedEIR::setElectricInputToCoolingOutputRatioFunctionOfTemperature(const Curve& curve) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setElectricInputToCoolingOutputRatioFunctionOfTemperature(curve);
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

  Curve ChillerElectricReformulatedEIR::electricInputToCoolingOutputRatioFunctionOfPLR() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->electricInputToCoolingOutputRatioFunctionOfPLR();
  }

  bool ChillerElectricReformulatedEIR::setElectricInputToCoolingOutputRatioFunctionOfPLR(const Curve& curve) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setElectricInputToCoolingOutputRatioFunctionOfPLR(curve);
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

  boost::optional<Schedule> ChillerElectricReformulatedEIR::heatRecoveryInletHighTemperatureLimitSchedule() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->heatRecoveryInletHighTemperatureLimitSchedule();
  }

  bool ChillerElectricReformulatedEIR::setHeatRecoveryInletHighTemperatureLimitSchedule(Schedule& schedule) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setHeatRecoveryInletHighTemperatureLimitSchedule(schedule);
  }

  void ChillerElectricReformulatedEIR::resetHeatRecoveryInletHighTemperatureLimitSchedule() {
    getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetHeatRecoveryInletHighTemperatureLimitSchedule();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::heatRecoveryLeavingTemperatureSetpointNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->heatRecoveryLeavingTemperatureSetpointNode();
  }

  bool ChillerElectricReformulatedEIR::setHeatRecoveryLeavingTemperatureSetpointNode(const Node& node) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setHeatRecoveryLeavingTemperatureSetpointNode(node);
  }

  void ChillerElectricReformulatedEIR::resetHeatRecoveryLeavingTemperatureSetpointNode() {
    getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetHeatRecoveryLeavingTemperatureSetpointNode();
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

  boost::optional<Curve> ChillerElectricReformulatedEIR::condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve();
  }

  bool ChillerElectricReformulatedEIR::setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(const Curve& curve) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(curve);
  }

  void ChillerElectricReformulatedEIR::resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve() {
    getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve();
  }

  boost::optional<Schedule> ChillerElectricReformulatedEIR::temperatureDifferenceAcrossCondenserSchedule() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->temperatureDifferenceAcrossCondenserSchedule();
  }

  bool ChillerElectricReformulatedEIR::setTemperatureDifferenceAcrossCondenserSchedule(Schedule& schedule) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setTemperatureDifferenceAcrossCondenserSchedule(schedule);
  }

  void ChillerElectricReformulatedEIR::resetTemperatureDifferenceAcrossCondenserSchedule() {
    getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetTemperatureDifferenceAcrossCondenserSchedule();
  }

  double ChillerElectricReformulatedEIR::condenserMinimumFlowFraction() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserMinimumFlowFraction();
  }

  bool ChillerElectricReformulatedEIR::setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setCondenserMinimumFlowFraction(condenserMinimumFlowFraction);
  }

  boost::optional<Curve> ChillerElectricReformulatedEIR::thermosiphonCapacityFractionCurve() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->thermosiphonCapacityFractionCurve();
  }

  bool ChillerElectricReformulatedEIR::setThermosiphonCapacityFractionCurve(const Curve& curve) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setThermosiphonCapacityFractionCurve(curve);
  }

  void ChillerElectricReformulatedEIR::resetThermosiphonCapacityFractionCurve() {
    getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->resetThermosiphonCapacityFractionCurve();
  }

  double ChillerElectricReformulatedEIR::thermosiphonMinimumTemperatureDifference() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->thermosiphonMinimumTemperatureDifference();
  }

  bool ChillerElectricReformulatedEIR::setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference) {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->setThermosiphonMinimumTemperatureDifference(
      thermosiphonMinimumTemperatureDifference);
  }

  boost::optional<double> ChillerElectricReformulatedEIR::autosizedReferenceCapacity() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizedReferenceCapacity();
  }

  boost::optional<double> ChillerElectricReformulatedEIR::autosizedReferenceChilledWaterFlowRate() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizedReferenceChilledWaterFlowRate();
  }

  boost::optional<double> ChillerElectricReformulatedEIR::autosizedReferenceCondenserWaterFlowRate() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizedReferenceCondenserWaterFlowRate();
  }

  boost::optional<double> ChillerElectricReformulatedEIR::autosizedDesignHeatRecoveryWaterFlowRate() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->autosizedDesignHeatRecoveryWaterFlowRate();
  }

  boost::optional<PlantLoop> ChillerElectricReformulatedEIR::chilledWaterLoop() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->chilledWaterLoop();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::chilledWaterInletNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->chilledWaterInletNode();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::chilledWaterOutletNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->chilledWaterOutletNode();
  }

  boost::optional<PlantLoop> ChillerElectricReformulatedEIR::condenserWaterLoop() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserWaterLoop();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::condenserInletNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserInletNode();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::condenserOutletNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->condenserOutletNode();
  }

  boost::optional<PlantLoop> ChillerElectricReformulatedEIR::heatRecoveryLoop() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->heatRecoveryLoop();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::heatRecoveryInletNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->heatRecoveryInletNode();
  }

  boost::optional<Node> ChillerElectricReformulatedEIR::heatRecoveryOutletNode() const {
    return getImpl<detail::ChillerElectricReformulatedEIR_Impl>()->heatRecoveryOutletNode();
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
      const bool result = setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature,
                                    referenceLeavingChilledWaterTemperature);
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
      autosizeReferenceCondenserWaterFlowRate();
    }

    void ChillerElectricReformulatedEIR_Impl::autosizeReferenceCondenserWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, "Autosize"));
    }

    boost::optional<double> ChillerElectricReformulatedEIR_Impl::autosizedReferenceCondenserWaterFlowRate() const {
      return boost::none;
    }

    Curve ChillerElectricReformulatedEIR_Impl::coolingCapacityFunctionOfTemperature() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::CoolingCapacityFunctionofTemperatureCurveName);
      OS_ASSERT(target);
      return *target;
    }

    bool ChillerElectricReformulatedEIR_Impl::setCoolingCapacityFunctionOfTemperature(const Curve& curve) {
      return setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::CoolingCapacityFunctionofTemperatureCurveName, curve.handle());
    }

    Curve ChillerElectricReformulatedEIR_Impl::electricInputToCoolingOutputRatioFunctionOfTemperature() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName);
      OS_ASSERT(target);
      return *target;
    }

    bool ChillerElectricReformulatedEIR_Impl::setElectricInputToCoolingOutputRatioFunctionOfTemperature(const Curve& curve) {
      return setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName,
                        curve.handle());
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
      OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, ""));
    }

    Curve ChillerElectricReformulatedEIR_Impl::electricInputToCoolingOutputRatioFunctionOfPLR() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName);
      OS_ASSERT(target);
      return *target;
    }

    bool ChillerElectricReformulatedEIR_Impl::setElectricInputToCoolingOutputRatioFunctionOfPLR(const Curve& curve) {
      return setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName,
                        curve.handle());
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
      const bool result = setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit,
                                    leavingChilledWaterLowerTemperatureLimit);
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

    boost::optional<double> ChillerElectricReformulatedEIR_Impl::autosizedDesignHeatRecoveryWaterFlowRate() const {
      return boost::none;
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

    boost::optional<Schedule> ChillerElectricReformulatedEIR_Impl::heatRecoveryInletHighTemperatureLimitSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName);
    }

    bool ChillerElectricReformulatedEIR_Impl::setHeatRecoveryInletHighTemperatureLimitSchedule(Schedule& schedule) {
      return setSchedule(openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName,
                         "ChillerElectricReformulatedEIR", "Heat Recovery Inlet High Temperature Limit", schedule);
    }

    void ChillerElectricReformulatedEIR_Impl::resetHeatRecoveryInletHighTemperatureLimitSchedule() {
      OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName, ""));
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::heatRecoveryLeavingTemperatureSetpointNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName);
    }

    bool ChillerElectricReformulatedEIR_Impl::setHeatRecoveryLeavingTemperatureSetpointNode(const Node& node) {
      return setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, node.handle());
    }

    void ChillerElectricReformulatedEIR_Impl::resetHeatRecoveryLeavingTemperatureSetpointNode() {
      setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, Handle(), false);
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

    boost::optional<Curve> ChillerElectricReformulatedEIR_Impl::condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName);
    }

    bool ChillerElectricReformulatedEIR_Impl::setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(const Curve& curve) {
      return setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName,
                        curve.handle());
    }

    void ChillerElectricReformulatedEIR_Impl::resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve() {
      setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurveName, Handle(),
                 false);
    }

    boost::optional<Schedule> ChillerElectricReformulatedEIR_Impl::temperatureDifferenceAcrossCondenserSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::TemperatureDifferenceAcrossCondenserScheduleName);
    }

    bool ChillerElectricReformulatedEIR_Impl::setTemperatureDifferenceAcrossCondenserSchedule(Schedule& schedule) {
      return setSchedule(openstudio::Chiller_Electric_ReformulatedEIRFields::TemperatureDifferenceAcrossCondenserScheduleName,
                         "ChillerElectricReformulatedEIR", "Temperature Difference Across Condenser", schedule);
    }

    void ChillerElectricReformulatedEIR_Impl::resetTemperatureDifferenceAcrossCondenserSchedule() {
      OS_ASSERT(setString(openstudio::Chiller_Electric_ReformulatedEIRFields::TemperatureDifferenceAcrossCondenserScheduleName, ""));
    }

    double ChillerElectricReformulatedEIR_Impl::condenserMinimumFlowFraction() const {
      const auto value = getDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserMinimumFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ChillerElectricReformulatedEIR_Impl::setCondenserMinimumFlowFraction(double condenserMinimumFlowFraction) {
      return setDouble(openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserMinimumFlowFraction, condenserMinimumFlowFraction);
    }

    boost::optional<Curve> ChillerElectricReformulatedEIR_Impl::thermosiphonCapacityFractionCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Chiller_Electric_ReformulatedEIRFields::ThermosiphonCapacityFractionCurveName);
    }

    bool ChillerElectricReformulatedEIR_Impl::setThermosiphonCapacityFractionCurve(const Curve& curve) {
      return setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::ThermosiphonCapacityFractionCurveName, curve.handle());
    }

    void ChillerElectricReformulatedEIR_Impl::resetThermosiphonCapacityFractionCurve() {
      setPointer(openstudio::Chiller_Electric_ReformulatedEIRFields::ThermosiphonCapacityFractionCurveName, Handle(), false);
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

    boost::optional<double> ChillerElectricReformulatedEIR_Impl::autosizedReferenceCapacity() const {
      return boost::none;
    }

    boost::optional<double> ChillerElectricReformulatedEIR_Impl::autosizedReferenceChilledWaterFlowRate() const {
      return boost::none;
    }

    boost::optional<PlantLoop> ChillerElectricReformulatedEIR_Impl::chilledWaterLoop() const {
      return WaterToWaterComponent_Impl::plantLoop();
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::chilledWaterInletNode() const {
      if (auto mo = supplyInletModelObject()) {
        return mo->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::chilledWaterOutletNode() const {
      if (auto mo = supplyOutletModelObject()) {
        return mo->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<PlantLoop> ChillerElectricReformulatedEIR_Impl::condenserWaterLoop() const {
      return WaterToWaterComponent_Impl::secondaryPlantLoop();
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::condenserInletNode() const {
      if (auto mo = demandInletModelObject()) {
        return mo->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::condenserOutletNode() const {
      if (auto mo = demandOutletModelObject()) {
        return mo->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<PlantLoop> ChillerElectricReformulatedEIR_Impl::heatRecoveryLoop() const {
      return WaterToWaterComponent_Impl::tertiaryPlantLoop();
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::heatRecoveryInletNode() const {
      if (auto mo = tertiaryInletModelObject()) {
        return mo->optionalCast<Node>();
      }
      return boost::none;
    }

    boost::optional<Node> ChillerElectricReformulatedEIR_Impl::heatRecoveryOutletNode() const {
      if (auto mo = tertiaryOutletModelObject()) {
        return mo->optionalCast<Node>();
      }
      return boost::none;
    }

    bool ChillerElectricReformulatedEIR_Impl::addToNode(Node& node) {
      if (shouldRouteDemandSideNodeToTertiary(node)) {
        return addToTertiaryNode(node);
      }
      return WaterToWaterComponent_Impl::addToNode(node);
    }

    bool ChillerElectricReformulatedEIR_Impl::addToTertiaryNode(Node& node) {
      return addToDemandSideTertiaryNode(node);
    }

    bool ChillerElectricReformulatedEIR_Impl::removeFromSecondaryPlantLoop() {
      return WaterToWaterComponent_Impl::removeFromSecondaryPlantLoop();
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

    unsigned ChillerElectricReformulatedEIR_Impl::supplyInletPort() const {
      return openstudio::Chiller_Electric_ReformulatedEIRFields::ChilledWaterInletNodeName;
    }

    unsigned ChillerElectricReformulatedEIR_Impl::supplyOutletPort() const {
      return openstudio::Chiller_Electric_ReformulatedEIRFields::ChilledWaterOutletNodeName;
    }

    unsigned ChillerElectricReformulatedEIR_Impl::demandInletPort() const {
      return openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserInletNodeName;
    }

    unsigned ChillerElectricReformulatedEIR_Impl::demandOutletPort() const {
      return openstudio::Chiller_Electric_ReformulatedEIRFields::CondenserOutletNodeName;
    }

    unsigned ChillerElectricReformulatedEIR_Impl::tertiaryInletPort() const {
      return openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletNodeName;
    }

    unsigned ChillerElectricReformulatedEIR_Impl::tertiaryOutletPort() const {
      return openstudio::Chiller_Electric_ReformulatedEIRFields::HeatRecoveryOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
