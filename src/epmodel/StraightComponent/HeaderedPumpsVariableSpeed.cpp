/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HeaderedPumpsVariableSpeed.hpp"
#include "StraightComponent/HeaderedPumpsVariableSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeaderedPumps_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HeaderedPumpsVariableSpeed::HeaderedPumpsVariableSpeed(const Model& model)
  : StraightComponent(HeaderedPumpsVariableSpeed::iddObjectType(), model) {
  autosizeTotalRatedFlowRate();
  OS_ASSERT(setNumberofPumpsinBank(2));
  OS_ASSERT(setFlowSequencingControlScheme("Sequential"));
  OS_ASSERT(setRatedPumpHead(179352.0));
  autosizeRatedPowerConsumption();
  OS_ASSERT(setMotorEfficiency(0.9));
  OS_ASSERT(setFractionofMotorInefficienciestoFluidStream(0.0));
  OS_ASSERT(setCoefficient1ofthePartLoadPerformanceCurve(0.0));
  OS_ASSERT(setCoefficient2ofthePartLoadPerformanceCurve(1.0));
  OS_ASSERT(setCoefficient3ofthePartLoadPerformanceCurve(0.0));
  OS_ASSERT(setCoefficient4ofthePartLoadPerformanceCurve(0.0));
  OS_ASSERT(setMinimumFlowRateFraction(0.0));
  OS_ASSERT(setPumpControlType("Continuous"));
  OS_ASSERT(setSkinLossRadiativeFraction(0.1));
  OS_ASSERT(setDesignPowerSizingMethod("PowerPerFlowPerPressure"));
  OS_ASSERT(setDesignElectricPowerPerUnitFlowRate(348701.1));
  OS_ASSERT(setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.282051282));
  OS_ASSERT(setEndUseSubcategory("General"));
}

HeaderedPumpsVariableSpeed::HeaderedPumpsVariableSpeed(std::shared_ptr<detail::HeaderedPumpsVariableSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType HeaderedPumpsVariableSpeed::iddObjectType() {
  return IddObjectType::HeaderedPumps_VariableSpeed;
}

std::vector<std::string> HeaderedPumpsVariableSpeed::flowSequencingControlSchemeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeaderedPumps_VariableSpeedFields::FlowSequencingControlScheme);
}

std::vector<std::string> HeaderedPumpsVariableSpeed::pumpControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeaderedPumps_VariableSpeedFields::PumpControlType);
}

std::vector<std::string> HeaderedPumpsVariableSpeed::designPowerSizingMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerSizingMethod);
}

boost::optional<double> HeaderedPumpsVariableSpeed::totalRatedFlowRate() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->totalRatedFlowRate();
}

bool HeaderedPumpsVariableSpeed::isTotalRatedFlowRateAutosized() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->isTotalRatedFlowRateAutosized();
}

int HeaderedPumpsVariableSpeed::numberofPumpsinBank() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->numberofPumpsinBank();
}

std::string HeaderedPumpsVariableSpeed::flowSequencingControlScheme() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->flowSequencingControlScheme();
}

double HeaderedPumpsVariableSpeed::ratedPumpHead() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->ratedPumpHead();
}

boost::optional<double> HeaderedPumpsVariableSpeed::ratedPowerConsumption() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->ratedPowerConsumption();
}

bool HeaderedPumpsVariableSpeed::isRatedPowerConsumptionAutosized() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->isRatedPowerConsumptionAutosized();
}

double HeaderedPumpsVariableSpeed::motorEfficiency() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->motorEfficiency();
}

double HeaderedPumpsVariableSpeed::fractionofMotorInefficienciestoFluidStream() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->fractionofMotorInefficienciestoFluidStream();
}

double HeaderedPumpsVariableSpeed::coefficient1ofthePartLoadPerformanceCurve() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->coefficient1ofthePartLoadPerformanceCurve();
}

double HeaderedPumpsVariableSpeed::coefficient2ofthePartLoadPerformanceCurve() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->coefficient2ofthePartLoadPerformanceCurve();
}

double HeaderedPumpsVariableSpeed::coefficient3ofthePartLoadPerformanceCurve() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->coefficient3ofthePartLoadPerformanceCurve();
}

double HeaderedPumpsVariableSpeed::coefficient4ofthePartLoadPerformanceCurve() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->coefficient4ofthePartLoadPerformanceCurve();
}

double HeaderedPumpsVariableSpeed::minimumFlowRateFraction() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->minimumFlowRateFraction();
}

std::string HeaderedPumpsVariableSpeed::pumpControlType() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->pumpControlType();
}

double HeaderedPumpsVariableSpeed::skinLossRadiativeFraction() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->skinLossRadiativeFraction();
}

std::string HeaderedPumpsVariableSpeed::designPowerSizingMethod() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->designPowerSizingMethod();
}

double HeaderedPumpsVariableSpeed::designElectricPowerPerUnitFlowRate() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->designElectricPowerPerUnitFlowRate();
}

double HeaderedPumpsVariableSpeed::designShaftPowerPerUnitFlowRatePerUnitHead() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->designShaftPowerPerUnitFlowRatePerUnitHead();
}

std::string HeaderedPumpsVariableSpeed::endUseSubcategory() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->endUseSubcategory();
}

bool HeaderedPumpsVariableSpeed::setTotalRatedFlowRate(double totalRatedFlowRate) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setTotalRatedFlowRate(totalRatedFlowRate);
}

void HeaderedPumpsVariableSpeed::autosizeTotalRatedFlowRate() {
  getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->autosizeTotalRatedFlowRate();
}

bool HeaderedPumpsVariableSpeed::setNumberofPumpsinBank(int numberofPumpsinBank) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setNumberofPumpsinBank(numberofPumpsinBank);
}

bool HeaderedPumpsVariableSpeed::setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setFlowSequencingControlScheme(flowSequencingControlScheme);
}

bool HeaderedPumpsVariableSpeed::setRatedPumpHead(double ratedPumpHead) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setRatedPumpHead(ratedPumpHead);
}

bool HeaderedPumpsVariableSpeed::setRatedPowerConsumption(double ratedPowerConsumption) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
}

void HeaderedPumpsVariableSpeed::autosizeRatedPowerConsumption() {
  getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->autosizeRatedPowerConsumption();
}

bool HeaderedPumpsVariableSpeed::setMotorEfficiency(double motorEfficiency) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setMotorEfficiency(motorEfficiency);
}

bool HeaderedPumpsVariableSpeed::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setFractionofMotorInefficienciestoFluidStream(
    fractionofMotorInefficienciestoFluidStream);
}

bool HeaderedPumpsVariableSpeed::setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setCoefficient1ofthePartLoadPerformanceCurve(
    coefficient1ofthePartLoadPerformanceCurve);
}

bool HeaderedPumpsVariableSpeed::setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setCoefficient2ofthePartLoadPerformanceCurve(
    coefficient2ofthePartLoadPerformanceCurve);
}

bool HeaderedPumpsVariableSpeed::setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setCoefficient3ofthePartLoadPerformanceCurve(
    coefficient3ofthePartLoadPerformanceCurve);
}

bool HeaderedPumpsVariableSpeed::setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setCoefficient4ofthePartLoadPerformanceCurve(
    coefficient4ofthePartLoadPerformanceCurve);
}

bool HeaderedPumpsVariableSpeed::setMinimumFlowRateFraction(double minimumFlowRateFraction) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setMinimumFlowRateFraction(minimumFlowRateFraction);
}

bool HeaderedPumpsVariableSpeed::setPumpControlType(const std::string& pumpControlType) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setPumpControlType(pumpControlType);
}

bool HeaderedPumpsVariableSpeed::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setSkinLossRadiativeFraction(skinLossRadiativeFraction);
}

bool HeaderedPumpsVariableSpeed::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setDesignPowerSizingMethod(designPowerSizingMethod);
}

bool HeaderedPumpsVariableSpeed::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setDesignElectricPowerPerUnitFlowRate(designElectricPowerPerUnitFlowRate);
}

bool HeaderedPumpsVariableSpeed::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setDesignShaftPowerPerUnitFlowRatePerUnitHead(
    designShaftPowerPerUnitFlowRatePerUnitHead);
}

bool HeaderedPumpsVariableSpeed::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

boost::optional<double> HeaderedPumpsVariableSpeed::autosizedTotalRatedFlowRate() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->autosizedTotalRatedFlowRate();
}

boost::optional<double> HeaderedPumpsVariableSpeed::autosizedRatedPowerConsumption() const {
  return getImpl<detail::HeaderedPumpsVariableSpeed_Impl>()->autosizedRatedPowerConsumption();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned HeaderedPumpsVariableSpeed_Impl::inletPort() const {
  return openstudio::HeaderedPumps_VariableSpeedFields::InletNodeName;
}

unsigned HeaderedPumpsVariableSpeed_Impl::outletPort() const {
  return openstudio::HeaderedPumps_VariableSpeedFields::OutletNodeName;
}

boost::optional<double> HeaderedPumpsVariableSpeed_Impl::totalRatedFlowRate() const {
  return getDouble(openstudio::HeaderedPumps_VariableSpeedFields::TotalDesignFlowRate, true);
}

bool HeaderedPumpsVariableSpeed_Impl::isTotalRatedFlowRateAutosized() const {
  if (const auto value = getString(openstudio::HeaderedPumps_VariableSpeedFields::TotalDesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

int HeaderedPumpsVariableSpeed_Impl::numberofPumpsinBank() const {
  const auto value = getInt(openstudio::HeaderedPumps_VariableSpeedFields::NumberofPumpsinBank, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeaderedPumpsVariableSpeed_Impl::flowSequencingControlScheme() const {
  const auto value = getString(openstudio::HeaderedPumps_VariableSpeedFields::FlowSequencingControlScheme, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::ratedPumpHead() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignPumpHead, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> HeaderedPumpsVariableSpeed_Impl::ratedPowerConsumption() const {
  return getDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerConsumption, true);
}

bool HeaderedPumpsVariableSpeed_Impl::isRatedPowerConsumptionAutosized() const {
  if (const auto value = getString(openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerConsumption, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double HeaderedPumpsVariableSpeed_Impl::motorEfficiency() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::MotorEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::fractionofMotorInefficienciestoFluidStream() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::coefficient1ofthePartLoadPerformanceCurve() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::coefficient2ofthePartLoadPerformanceCurve() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::coefficient3ofthePartLoadPerformanceCurve() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::coefficient4ofthePartLoadPerformanceCurve() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::minimumFlowRateFraction() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::MinimumFlowRateFraction, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeaderedPumpsVariableSpeed_Impl::pumpControlType() const {
  const auto value = getString(openstudio::HeaderedPumps_VariableSpeedFields::PumpControlType, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::skinLossRadiativeFraction() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::SkinLossRadiativeFraction, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeaderedPumpsVariableSpeed_Impl::designPowerSizingMethod() const {
  const auto value = getString(openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerSizingMethod, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::designElectricPowerPerUnitFlowRate() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignElectricPowerperUnitFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

double HeaderedPumpsVariableSpeed_Impl::designShaftPowerPerUnitFlowRatePerUnitHead() const {
  const auto value = getDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, true);
  OS_ASSERT(value);
  return *value;
}

std::string HeaderedPumpsVariableSpeed_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::HeaderedPumps_VariableSpeedFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool HeaderedPumpsVariableSpeed_Impl::setTotalRatedFlowRate(double totalRatedFlowRate) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::TotalDesignFlowRate, totalRatedFlowRate);
}

void HeaderedPumpsVariableSpeed_Impl::autosizeTotalRatedFlowRate() {
  const bool result = setString(openstudio::HeaderedPumps_VariableSpeedFields::TotalDesignFlowRate, "Autosize");
  OS_ASSERT(result);
}

bool HeaderedPumpsVariableSpeed_Impl::setNumberofPumpsinBank(int numberofPumpsinBank) {
  const bool result = setInt(openstudio::HeaderedPumps_VariableSpeedFields::NumberofPumpsinBank, numberofPumpsinBank);
  OS_ASSERT(result);
  return result;
}

bool HeaderedPumpsVariableSpeed_Impl::setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme) {
  return setString(openstudio::HeaderedPumps_VariableSpeedFields::FlowSequencingControlScheme, flowSequencingControlScheme);
}

bool HeaderedPumpsVariableSpeed_Impl::setRatedPumpHead(double ratedPumpHead) {
  const bool result = setDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignPumpHead, ratedPumpHead);
  OS_ASSERT(result);
  return result;
}

bool HeaderedPumpsVariableSpeed_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
  const bool result = setDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerConsumption, ratedPowerConsumption);
  OS_ASSERT(result);
  return result;
}

void HeaderedPumpsVariableSpeed_Impl::autosizeRatedPowerConsumption() {
  const bool result = setString(openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerConsumption, "Autosize");
  OS_ASSERT(result);
}

bool HeaderedPumpsVariableSpeed_Impl::setMotorEfficiency(double motorEfficiency) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::MotorEfficiency, motorEfficiency);
}

bool HeaderedPumpsVariableSpeed_Impl::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream,
                   fractionofMotorInefficienciestoFluidStream);
}

bool HeaderedPumpsVariableSpeed_Impl::setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve) {
  const bool result = setDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve,
                                coefficient1ofthePartLoadPerformanceCurve);
  OS_ASSERT(result);
  return result;
}

bool HeaderedPumpsVariableSpeed_Impl::setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve) {
  const bool result = setDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve,
                                coefficient2ofthePartLoadPerformanceCurve);
  OS_ASSERT(result);
  return result;
}

bool HeaderedPumpsVariableSpeed_Impl::setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve) {
  const bool result = setDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve,
                                coefficient3ofthePartLoadPerformanceCurve);
  OS_ASSERT(result);
  return result;
}

bool HeaderedPumpsVariableSpeed_Impl::setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve) {
  const bool result = setDouble(openstudio::HeaderedPumps_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve,
                                coefficient4ofthePartLoadPerformanceCurve);
  OS_ASSERT(result);
  return result;
}

bool HeaderedPumpsVariableSpeed_Impl::setMinimumFlowRateFraction(double minimumFlowRateFraction) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::MinimumFlowRateFraction, minimumFlowRateFraction);
}

bool HeaderedPumpsVariableSpeed_Impl::setPumpControlType(const std::string& pumpControlType) {
  return setString(openstudio::HeaderedPumps_VariableSpeedFields::PumpControlType, pumpControlType);
}

bool HeaderedPumpsVariableSpeed_Impl::setSkinLossRadiativeFraction(double skinLossRadiativeFraction) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::SkinLossRadiativeFraction, skinLossRadiativeFraction);
}

bool HeaderedPumpsVariableSpeed_Impl::setDesignPowerSizingMethod(const std::string& designPowerSizingMethod) {
  return setString(openstudio::HeaderedPumps_VariableSpeedFields::DesignPowerSizingMethod, designPowerSizingMethod);
}

bool HeaderedPumpsVariableSpeed_Impl::setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignElectricPowerperUnitFlowRate, designElectricPowerPerUnitFlowRate);
}

bool HeaderedPumpsVariableSpeed_Impl::setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead) {
  return setDouble(openstudio::HeaderedPumps_VariableSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead,
                   designShaftPowerPerUnitFlowRatePerUnitHead);
}

bool HeaderedPumpsVariableSpeed_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return setString(openstudio::HeaderedPumps_VariableSpeedFields::EndUseSubcategory, endUseSubcategory);
}

boost::optional<double> HeaderedPumpsVariableSpeed_Impl::autosizedTotalRatedFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

boost::optional<double> HeaderedPumpsVariableSpeed_Impl::autosizedRatedPowerConsumption() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
