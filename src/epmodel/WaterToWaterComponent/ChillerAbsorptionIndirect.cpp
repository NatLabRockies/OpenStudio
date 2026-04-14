/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerAbsorptionIndirect.hpp"
#include "WaterToWaterComponent/ChillerAbsorptionIndirect_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Chiller_Absorption_Indirect_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

ChillerAbsorptionIndirect::ChillerAbsorptionIndirect(const Model& model)
  : WaterToWaterComponent(ChillerAbsorptionIndirect::iddObjectType(), model) {
  autosizeNominalCapacity();
  autosizeNominalPumpingPower();
  OS_ASSERT(setMinimumPartLoadRatio(0.15));
  OS_ASSERT(setMaximumPartLoadRatio(1.0));
  OS_ASSERT(setOptimumPartLoadRatio(0.65));
  OS_ASSERT(setDesignCondenserInletTemperature(35.0));
  OS_ASSERT(setCondenserInletTemperatureLowerLimit(10.0));
  OS_ASSERT(setChilledWaterOutletTemperatureLowerLimit(5.0));
  autosizeDesignChilledWaterFlowRate();
  autosizeDesignCondenserWaterFlowRate();
  OS_ASSERT(setChillerFlowMode("NotModulated"));
  OS_ASSERT(setGeneratorHeatSourceType("Steam"));
  autosizeDesignGeneratorFluidFlowRate();
  OS_ASSERT(setTemperatureLowerLimitGeneratorInlet(30.0));
  OS_ASSERT(setDegreeofSubcoolinginSteamGenerator(2.0));
  OS_ASSERT(setDegreeofSubcoolinginSteamCondensateLoop(12.0));
  OS_ASSERT(setSizingFactor(1.0));

  CurveCubic generatorHeatInputFPLR(model);
  OS_ASSERT(generatorHeatInputFPLR.setCoefficient1Constant(0.18892));
  OS_ASSERT(generatorHeatInputFPLR.setCoefficient2x(0.968044));
  OS_ASSERT(generatorHeatInputFPLR.setCoefficient3xPOW2(1.119202));
  OS_ASSERT(generatorHeatInputFPLR.setCoefficient4xPOW3(-0.5034));
  OS_ASSERT(generatorHeatInputFPLR.setMinimumValueofx(0.15));
  OS_ASSERT(generatorHeatInputFPLR.setMaximumValueofx(1.0));
  OS_ASSERT(setGeneratorHeatInputFunctionofPartLoadRatioCurve(generatorHeatInputFPLR));

  CurveQuadratic pumpElectricFPLR(model);
  OS_ASSERT(pumpElectricFPLR.setCoefficient1Constant(1.0));
  OS_ASSERT(pumpElectricFPLR.setCoefficient2x(0.0));
  OS_ASSERT(pumpElectricFPLR.setCoefficient3xPOW2(0.0));
  OS_ASSERT(pumpElectricFPLR.setMinimumValueofx(0.15));
  OS_ASSERT(pumpElectricFPLR.setMaximumValueofx(1.0));
  OS_ASSERT(setPumpElectricInputFunctionofPartLoadRatioCurve(pumpElectricFPLR));

  CurveCubic capacityCorrectionCondTemp(model);
  OS_ASSERT(capacityCorrectionCondTemp.setCoefficient1Constant(0.245507));
  OS_ASSERT(capacityCorrectionCondTemp.setCoefficient2x(0.023614));
  OS_ASSERT(capacityCorrectionCondTemp.setCoefficient3xPOW2(0.0000278));
  OS_ASSERT(capacityCorrectionCondTemp.setCoefficient4xPOW3(0.000013));
  OS_ASSERT(capacityCorrectionCondTemp.setMinimumValueofx(7.0));
  OS_ASSERT(capacityCorrectionCondTemp.setMaximumValueofx(25.0));
  OS_ASSERT(setCapacityCorrectionFunctionofCondenserTemperatureCurve(capacityCorrectionCondTemp));

  CurveCubic capacityCorrectionGeneratorTemp(model);
  OS_ASSERT(capacityCorrectionGeneratorTemp.setCoefficient1Constant(1.0));
  OS_ASSERT(capacityCorrectionGeneratorTemp.setCoefficient2x(0.0));
  OS_ASSERT(capacityCorrectionGeneratorTemp.setCoefficient3xPOW2(0.0));
  OS_ASSERT(capacityCorrectionGeneratorTemp.setCoefficient4xPOW3(0.0));
  OS_ASSERT(capacityCorrectionGeneratorTemp.setMinimumValueofx(0.0));
  OS_ASSERT(capacityCorrectionGeneratorTemp.setMaximumValueofx(100.0));
  OS_ASSERT(setCapacityCorrectionFunctionofGeneratorTemperatureCurve(capacityCorrectionGeneratorTemp));

  CurveCubic capacityCorrectionChilledTemp(model);
  OS_ASSERT(capacityCorrectionChilledTemp.setCoefficient1Constant(0.690571));
  OS_ASSERT(capacityCorrectionChilledTemp.setCoefficient2x(0.065571));
  OS_ASSERT(capacityCorrectionChilledTemp.setCoefficient3xPOW2(-0.00289));
  OS_ASSERT(capacityCorrectionChilledTemp.setCoefficient4xPOW3(0.0));
  OS_ASSERT(capacityCorrectionChilledTemp.setMinimumValueofx(4.0));
  OS_ASSERT(capacityCorrectionChilledTemp.setMaximumValueofx(10.0));
  OS_ASSERT(setCapacityCorrectionFunctionofChilledWaterTemperatureCurve(capacityCorrectionChilledTemp));

  CurveCubic generatorHeatInputCorrectionCondTemp(model);
  OS_ASSERT(generatorHeatInputCorrectionCondTemp.setCoefficient1Constant(0.712019));
  OS_ASSERT(generatorHeatInputCorrectionCondTemp.setCoefficient2x(-0.00478));
  OS_ASSERT(generatorHeatInputCorrectionCondTemp.setCoefficient3xPOW2(0.000864));
  OS_ASSERT(generatorHeatInputCorrectionCondTemp.setCoefficient4xPOW3(-0.000013));
  OS_ASSERT(generatorHeatInputCorrectionCondTemp.setMinimumValueofx(7.0));
  OS_ASSERT(generatorHeatInputCorrectionCondTemp.setMaximumValueofx(30.0));
  OS_ASSERT(setGeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurve(generatorHeatInputCorrectionCondTemp));

  CurveCubic generatorHeatInputCorrectionChilledTemp(model);
  OS_ASSERT(generatorHeatInputCorrectionChilledTemp.setCoefficient1Constant(0.995571));
  OS_ASSERT(generatorHeatInputCorrectionChilledTemp.setCoefficient2x(0.046821));
  OS_ASSERT(generatorHeatInputCorrectionChilledTemp.setCoefficient3xPOW2(-0.01099));
  OS_ASSERT(generatorHeatInputCorrectionChilledTemp.setCoefficient4xPOW3(0.000608));
  OS_ASSERT(generatorHeatInputCorrectionChilledTemp.setMinimumValueofx(4.0));
  OS_ASSERT(generatorHeatInputCorrectionChilledTemp.setMaximumValueofx(10.0));
  OS_ASSERT(setGeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve(generatorHeatInputCorrectionChilledTemp));
}

ChillerAbsorptionIndirect::ChillerAbsorptionIndirect(std::shared_ptr<detail::ChillerAbsorptionIndirect_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType ChillerAbsorptionIndirect::iddObjectType() {
  return IddObjectType::Chiller_Absorption_Indirect;
}

std::vector<std::string> ChillerAbsorptionIndirect::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Chiller_Absorption_IndirectFields::ChillerFlowMode);
}

std::vector<std::string> ChillerAbsorptionIndirect::generatorHeatSourceTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType);
}

boost::optional<double> ChillerAbsorptionIndirect::nominalCapacity() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->nominalCapacity();
}

bool ChillerAbsorptionIndirect::isNominalCapacityAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isNominalCapacityAutosized();
}

bool ChillerAbsorptionIndirect::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setNominalCapacity(nominalCapacity);
}

void ChillerAbsorptionIndirect::autosizeNominalCapacity() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeNominalCapacity();
}

boost::optional<double> ChillerAbsorptionIndirect::nominalPumpingPower() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->nominalPumpingPower();
}

bool ChillerAbsorptionIndirect::isNominalPumpingPowerAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isNominalPumpingPowerAutosized();
}

bool ChillerAbsorptionIndirect::setNominalPumpingPower(double nominalPumpingPower) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setNominalPumpingPower(nominalPumpingPower);
}

void ChillerAbsorptionIndirect::autosizeNominalPumpingPower() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeNominalPumpingPower();
}

double ChillerAbsorptionIndirect::minimumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->minimumPartLoadRatio();
}

bool ChillerAbsorptionIndirect::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
}

double ChillerAbsorptionIndirect::maximumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->maximumPartLoadRatio();
}

bool ChillerAbsorptionIndirect::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
}

double ChillerAbsorptionIndirect::optimumPartLoadRatio() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->optimumPartLoadRatio();
}

bool ChillerAbsorptionIndirect::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
}

double ChillerAbsorptionIndirect::designCondenserInletTemperature() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designCondenserInletTemperature();
}

bool ChillerAbsorptionIndirect::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignCondenserInletTemperature(designCondenserInletTemperature);
}

double ChillerAbsorptionIndirect::condenserInletTemperatureLowerLimit() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->condenserInletTemperatureLowerLimit();
}

bool ChillerAbsorptionIndirect::setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setCondenserInletTemperatureLowerLimit(condenserInletTemperatureLowerLimit);
}

double ChillerAbsorptionIndirect::chilledWaterOutletTemperatureLowerLimit() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->chilledWaterOutletTemperatureLowerLimit();
}

bool ChillerAbsorptionIndirect::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setChilledWaterOutletTemperatureLowerLimit(chilledWaterOutletTemperatureLowerLimit);
}

boost::optional<double> ChillerAbsorptionIndirect::designChilledWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designChilledWaterFlowRate();
}

bool ChillerAbsorptionIndirect::isDesignChilledWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isDesignChilledWaterFlowRateAutosized();
}

bool ChillerAbsorptionIndirect::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignChilledWaterFlowRate(designChilledWaterFlowRate);
}

void ChillerAbsorptionIndirect::autosizeDesignChilledWaterFlowRate() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeDesignChilledWaterFlowRate();
}

boost::optional<double> ChillerAbsorptionIndirect::designCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designCondenserWaterFlowRate();
}

bool ChillerAbsorptionIndirect::isDesignCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isDesignCondenserWaterFlowRateAutosized();
}

bool ChillerAbsorptionIndirect::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignCondenserWaterFlowRate(designCondenserWaterFlowRate);
}

void ChillerAbsorptionIndirect::autosizeDesignCondenserWaterFlowRate() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeDesignCondenserWaterFlowRate();
}

std::string ChillerAbsorptionIndirect::chillerFlowMode() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->chillerFlowMode();
}

bool ChillerAbsorptionIndirect::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setChillerFlowMode(chillerFlowMode);
}

Curve ChillerAbsorptionIndirect::generatorHeatInputFunctionofPartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->generatorHeatInputFunctionofPartLoadRatioCurve();
}

bool ChillerAbsorptionIndirect::setGeneratorHeatInputFunctionofPartLoadRatioCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setGeneratorHeatInputFunctionofPartLoadRatioCurve(curve);
}

Curve ChillerAbsorptionIndirect::pumpElectricInputFunctionofPartLoadRatioCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->pumpElectricInputFunctionofPartLoadRatioCurve();
}

bool ChillerAbsorptionIndirect::setPumpElectricInputFunctionofPartLoadRatioCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setPumpElectricInputFunctionofPartLoadRatioCurve(curve);
}

Curve ChillerAbsorptionIndirect::capacityCorrectionFunctionofCondenserTemperatureCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->capacityCorrectionFunctionofCondenserTemperatureCurve();
}

bool ChillerAbsorptionIndirect::setCapacityCorrectionFunctionofCondenserTemperatureCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setCapacityCorrectionFunctionofCondenserTemperatureCurve(curve);
}

Curve ChillerAbsorptionIndirect::capacityCorrectionFunctionofChilledWaterTemperatureCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->capacityCorrectionFunctionofChilledWaterTemperatureCurve();
}

bool ChillerAbsorptionIndirect::setCapacityCorrectionFunctionofChilledWaterTemperatureCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setCapacityCorrectionFunctionofChilledWaterTemperatureCurve(curve);
}

Curve ChillerAbsorptionIndirect::capacityCorrectionFunctionofGeneratorTemperatureCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->capacityCorrectionFunctionofGeneratorTemperatureCurve();
}

bool ChillerAbsorptionIndirect::setCapacityCorrectionFunctionofGeneratorTemperatureCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setCapacityCorrectionFunctionofGeneratorTemperatureCurve(curve);
}

Curve ChillerAbsorptionIndirect::generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve();
}

bool ChillerAbsorptionIndirect::setGeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setGeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurve(curve);
}

Curve ChillerAbsorptionIndirect::generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve();
}

bool ChillerAbsorptionIndirect::setGeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve(const Curve& curve) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setGeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve(curve);
}

std::string ChillerAbsorptionIndirect::generatorHeatSourceType() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->generatorHeatSourceType();
}

bool ChillerAbsorptionIndirect::setGeneratorHeatSourceType(const std::string& generatorHeatSourceType) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setGeneratorHeatSourceType(generatorHeatSourceType);
}

boost::optional<double> ChillerAbsorptionIndirect::designGeneratorFluidFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->designGeneratorFluidFlowRate();
}

bool ChillerAbsorptionIndirect::isDesignGeneratorFluidFlowRateAutosized() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->isDesignGeneratorFluidFlowRateAutosized();
}

bool ChillerAbsorptionIndirect::setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDesignGeneratorFluidFlowRate(designGeneratorFluidFlowRate);
}

void ChillerAbsorptionIndirect::autosizeDesignGeneratorFluidFlowRate() {
  getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizeDesignGeneratorFluidFlowRate();
}

double ChillerAbsorptionIndirect::temperatureLowerLimitGeneratorInlet() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->temperatureLowerLimitGeneratorInlet();
}

bool ChillerAbsorptionIndirect::setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setTemperatureLowerLimitGeneratorInlet(temperatureLowerLimitGeneratorInlet);
}

double ChillerAbsorptionIndirect::degreeofSubcoolinginSteamGenerator() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->degreeofSubcoolinginSteamGenerator();
}

bool ChillerAbsorptionIndirect::setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDegreeofSubcoolinginSteamGenerator(degreeofSubcoolinginSteamGenerator);
}

double ChillerAbsorptionIndirect::degreeofSubcoolinginSteamCondensateLoop() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->degreeofSubcoolinginSteamCondensateLoop();
}

bool ChillerAbsorptionIndirect::setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setDegreeofSubcoolinginSteamCondensateLoop(degreeofSubcoolinginSteamCondensateLoop);
}

double ChillerAbsorptionIndirect::sizingFactor() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->sizingFactor();
}

bool ChillerAbsorptionIndirect::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->setSizingFactor(sizingFactor);
}

boost::optional<double> ChillerAbsorptionIndirect::autosizedNominalCapacity() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizedNominalCapacity();
}

boost::optional<double> ChillerAbsorptionIndirect::autosizedNominalPumpingPower() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizedNominalPumpingPower();
}

boost::optional<double> ChillerAbsorptionIndirect::autosizedDesignChilledWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizedDesignChilledWaterFlowRate();
}

boost::optional<double> ChillerAbsorptionIndirect::autosizedDesignCondenserWaterFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizedDesignCondenserWaterFlowRate();
}

boost::optional<double> ChillerAbsorptionIndirect::autosizedDesignGeneratorFluidFlowRate() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->autosizedDesignGeneratorFluidFlowRate();
}

boost::optional<PlantLoop> ChillerAbsorptionIndirect::chilledWaterLoop() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->chilledWaterLoop();
}

boost::optional<PlantLoop> ChillerAbsorptionIndirect::condenserWaterLoop() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->condenserWaterLoop();
}

boost::optional<PlantLoop> ChillerAbsorptionIndirect::generatorLoop() const {
  return getImpl<detail::ChillerAbsorptionIndirect_Impl>()->generatorLoop();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ChillerAbsorptionIndirect_Impl::nominalCapacity() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, true);
}

bool ChillerAbsorptionIndirect_Impl::isNominalCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerAbsorptionIndirect_Impl::setNominalCapacity(double nominalCapacity) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, nominalCapacity);
}

void ChillerAbsorptionIndirect_Impl::autosizeNominalCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::NominalCapacity, "autosize"));
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::autosizedNominalCapacity() const {
  return boost::none;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::nominalPumpingPower() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, true);
}

bool ChillerAbsorptionIndirect_Impl::isNominalPumpingPowerAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerAbsorptionIndirect_Impl::setNominalPumpingPower(double nominalPumpingPower) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, nominalPumpingPower);
}

void ChillerAbsorptionIndirect_Impl::autosizeNominalPumpingPower() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::NominalPumpingPower, "autosize"));
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::autosizedNominalPumpingPower() const {
  return boost::none;
}

double ChillerAbsorptionIndirect_Impl::minimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::MinimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::MinimumPartLoadRatio, minimumPartLoadRatio);
}

double ChillerAbsorptionIndirect_Impl::maximumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::MaximumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::MaximumPartLoadRatio, maximumPartLoadRatio);
}

double ChillerAbsorptionIndirect_Impl::optimumPartLoadRatio() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::OptimumPartLoadRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::OptimumPartLoadRatio, optimumPartLoadRatio);
}

double ChillerAbsorptionIndirect_Impl::designCondenserInletTemperature() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setDesignCondenserInletTemperature(double designCondenserInletTemperature) {
  const bool result = setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature, designCondenserInletTemperature);
  OS_ASSERT(result);
  return result;
}

double ChillerAbsorptionIndirect_Impl::condenserInletTemperatureLowerLimit() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit) {
  const bool result =
    setDouble(openstudio::Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit, condenserInletTemperatureLowerLimit);
  OS_ASSERT(result);
  return result;
}

double ChillerAbsorptionIndirect_Impl::chilledWaterOutletTemperatureLowerLimit() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit) {
  const bool result =
    setDouble(openstudio::Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit, chilledWaterOutletTemperatureLowerLimit);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::designChilledWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, true);
}

bool ChillerAbsorptionIndirect_Impl::isDesignChilledWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerAbsorptionIndirect_Impl::setDesignChilledWaterFlowRate(double designChilledWaterFlowRate) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, designChilledWaterFlowRate);
}

void ChillerAbsorptionIndirect_Impl::autosizeDesignChilledWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, "autosize"));
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::autosizedDesignChilledWaterFlowRate() const {
  return boost::none;
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::designCondenserWaterFlowRate() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, true);
}

bool ChillerAbsorptionIndirect_Impl::isDesignCondenserWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerAbsorptionIndirect_Impl::setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, designCondenserWaterFlowRate);
}

void ChillerAbsorptionIndirect_Impl::autosizeDesignCondenserWaterFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, "autosize"));
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::autosizedDesignCondenserWaterFlowRate() const {
  return boost::none;
}

std::string ChillerAbsorptionIndirect_Impl::chillerFlowMode() const {
  const auto value = getString(openstudio::Chiller_Absorption_IndirectFields::ChillerFlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  return setString(openstudio::Chiller_Absorption_IndirectFields::ChillerFlowMode, chillerFlowMode);
}

Curve ChillerAbsorptionIndirect_Impl::generatorHeatInputFunctionofPartLoadRatioCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatInputFunctionofPartLoadRatioCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setGeneratorHeatInputFunctionofPartLoadRatioCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatInputFunctionofPartLoadRatioCurveName, curve.handle());
}

Curve ChillerAbsorptionIndirect_Impl::pumpElectricInputFunctionofPartLoadRatioCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::PumpElectricInputFunctionofPartLoadRatioCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setPumpElectricInputFunctionofPartLoadRatioCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::PumpElectricInputFunctionofPartLoadRatioCurveName, curve.handle());
}

Curve ChillerAbsorptionIndirect_Impl::capacityCorrectionFunctionofCondenserTemperatureCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofCondenserTemperatureCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setCapacityCorrectionFunctionofCondenserTemperatureCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofCondenserTemperatureCurveName, curve.handle());
}

Curve ChillerAbsorptionIndirect_Impl::capacityCorrectionFunctionofChilledWaterTemperatureCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofChilledWaterTemperatureCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setCapacityCorrectionFunctionofChilledWaterTemperatureCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofChilledWaterTemperatureCurveName, curve.handle());
}

Curve ChillerAbsorptionIndirect_Impl::capacityCorrectionFunctionofGeneratorTemperatureCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofGeneratorTemperatureCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setCapacityCorrectionFunctionofGeneratorTemperatureCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofGeneratorTemperatureCurveName, curve.handle());
}

Curve ChillerAbsorptionIndirect_Impl::generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setGeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName,
                    curve.handle());
}

Curve ChillerAbsorptionIndirect_Impl::generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve() const {
  auto target = getTarget(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName);
  OS_ASSERT(target);
  return target->cast<Curve>();
}

bool ChillerAbsorptionIndirect_Impl::setGeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve(const Curve& curve) {
  return setPointer(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName,
                    curve.handle());
}

std::string ChillerAbsorptionIndirect_Impl::generatorHeatSourceType() const {
  const auto value = getString(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setGeneratorHeatSourceType(const std::string& generatorHeatSourceType) {
  if (istringEqual("Steam", generatorHeatSourceType) && generatorLoop()) {
    return false;
  }
  return setString(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, generatorHeatSourceType);
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::designGeneratorFluidFlowRate() const {
  return getDouble(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, true);
}

bool ChillerAbsorptionIndirect_Impl::isDesignGeneratorFluidFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool ChillerAbsorptionIndirect_Impl::setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate) {
  const bool result = setDouble(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, designGeneratorFluidFlowRate);
  OS_ASSERT(result);
  return result;
}

void ChillerAbsorptionIndirect_Impl::autosizeDesignGeneratorFluidFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, "autosize"));
}

boost::optional<double> ChillerAbsorptionIndirect_Impl::autosizedDesignGeneratorFluidFlowRate() const {
  return boost::none;
}

double ChillerAbsorptionIndirect_Impl::temperatureLowerLimitGeneratorInlet() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet) {
  const bool result =
    setDouble(openstudio::Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet, temperatureLowerLimitGeneratorInlet);
  OS_ASSERT(result);
  return result;
}

double ChillerAbsorptionIndirect_Impl::degreeofSubcoolinginSteamGenerator() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator, degreeofSubcoolinginSteamGenerator);
}

double ChillerAbsorptionIndirect_Impl::degreeofSubcoolinginSteamCondensateLoop() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop,
                   degreeofSubcoolinginSteamCondensateLoop);
}

double ChillerAbsorptionIndirect_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::Chiller_Absorption_IndirectFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerAbsorptionIndirect_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::Chiller_Absorption_IndirectFields::SizingFactor, sizingFactor);
}

std::vector<std::string> ChillerAbsorptionIndirect_Impl::chillerFlowModeValues() const {
  return openstudio::epmodel::ChillerAbsorptionIndirect::chillerFlowModeValues();
}

std::vector<std::string> ChillerAbsorptionIndirect_Impl::generatorHeatSourceTypeValues() const {
  return openstudio::epmodel::ChillerAbsorptionIndirect::generatorHeatSourceTypeValues();
}

unsigned ChillerAbsorptionIndirect_Impl::supplyInletPort() const {
  return openstudio::Chiller_Absorption_IndirectFields::ChilledWaterInletNodeName;
}

unsigned ChillerAbsorptionIndirect_Impl::supplyOutletPort() const {
  return openstudio::Chiller_Absorption_IndirectFields::ChilledWaterOutletNodeName;
}

unsigned ChillerAbsorptionIndirect_Impl::demandInletPort() const {
  return openstudio::Chiller_Absorption_IndirectFields::CondenserInletNodeName;
}

unsigned ChillerAbsorptionIndirect_Impl::demandOutletPort() const {
  return openstudio::Chiller_Absorption_IndirectFields::CondenserOutletNodeName;
}

unsigned ChillerAbsorptionIndirect_Impl::tertiaryInletPort() const {
  return openstudio::Chiller_Absorption_IndirectFields::GeneratorInletNodeName;
}

unsigned ChillerAbsorptionIndirect_Impl::tertiaryOutletPort() const {
  return openstudio::Chiller_Absorption_IndirectFields::GeneratorOutletNodeName;
}

boost::optional<PlantLoop> ChillerAbsorptionIndirect_Impl::chilledWaterLoop() const {
  return WaterToWaterComponent_Impl::plantLoop();
}

boost::optional<PlantLoop> ChillerAbsorptionIndirect_Impl::condenserWaterLoop() const {
  return WaterToWaterComponent_Impl::secondaryPlantLoop();
}

boost::optional<PlantLoop> ChillerAbsorptionIndirect_Impl::generatorLoop() const {
  return WaterToWaterComponent_Impl::tertiaryPlantLoop();
}

bool ChillerAbsorptionIndirect_Impl::addToNode(Node& node) {
  if (shouldRouteDemandSideNodeToTertiary(node)) {
    return addToTertiaryNode(node);
  }

  return WaterToWaterComponent_Impl::addToNode(node);
}

bool ChillerAbsorptionIndirect_Impl::addToTertiaryNode(Node& node) {
  const bool ok = addToDemandSideTertiaryNode(node);
  if (ok) {
    return setGeneratorHeatSourceType("HotWater");
  }
  return false;
}

bool ChillerAbsorptionIndirect_Impl::removeFromTertiaryPlantLoop() {
  const bool ok = WaterToWaterComponent_Impl::removeFromTertiaryPlantLoop();
  if (ok) {
    OS_ASSERT(setString(openstudio::Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, "Steam"));
  }
  return ok;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
