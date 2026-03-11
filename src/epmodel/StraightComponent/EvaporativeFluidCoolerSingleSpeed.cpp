/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/EvaporativeFluidCoolerSingleSpeed.hpp"
#include "StraightComponent/EvaporativeFluidCoolerSingleSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeFluidCooler_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

EvaporativeFluidCoolerSingleSpeed::EvaporativeFluidCoolerSingleSpeed(const Model& model)
  : StraightComponent(EvaporativeFluidCoolerSingleSpeed::iddObjectType(), model) {
  bool ok = true;
  autosizeDesignAirFlowRate();
  autosizeFanPoweratDesignAirFlowRate();
  ok = setDesignSprayWaterFlowRate(0.03);
  OS_ASSERT(ok);
  ok = setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate");
  OS_ASSERT(ok);
  ok = setHeatRejectionCapacityandNominalCapacitySizingRatio(1.25);
  OS_ASSERT(ok);
  resetStandardDesignCapacity();
  autosizeUfactorTimesAreaValueatDesignAirFlowRate();
  autosizeDesignWaterFlowRate();
  resetUserSpecifiedDesignCapacity();
  autosizeDesignEnteringWaterTemperature();
  ok = setDesignEnteringAirTemperature(35.0);
  OS_ASSERT(ok);
  ok = setDesignEnteringAirWetbulbTemperature(25.6);
  OS_ASSERT(ok);
  ok = setCapacityControl("FanCycling");
  OS_ASSERT(ok);
  ok = setSizingFactor(1.0);
  OS_ASSERT(ok);
  ok = setEvaporationLossMode("SaturatedExit");
  OS_ASSERT(ok);
  ok = setDriftLossPercent(0.008);
  OS_ASSERT(ok);
  ok = setBlowdownCalculationMode("ConcentrationRatio");
  OS_ASSERT(ok);
  ok = setBlowdownConcentrationRatio(3.0);
  OS_ASSERT(ok);
}

EvaporativeFluidCoolerSingleSpeed::EvaporativeFluidCoolerSingleSpeed(
  std::shared_ptr<detail::EvaporativeFluidCoolerSingleSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType EvaporativeFluidCoolerSingleSpeed::iddObjectType() {
  return IddObjectType::EvaporativeFluidCooler_SingleSpeed;
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_SingleSpeedFields::PerformanceInputMethod);
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed::capacityControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_SingleSpeedFields::CapacityControl);
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed::evaporationLossModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode);
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed::blowdownCalculationModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode);
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::designAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->designAirFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::isDesignAirFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateAutosized();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::fanPoweratDesignAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->fanPoweratDesignAirFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::isFanPoweratDesignAirFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isFanPoweratDesignAirFlowRateAutosized();
}

double EvaporativeFluidCoolerSingleSpeed::designSprayWaterFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->designSprayWaterFlowRate();
}

std::string EvaporativeFluidCoolerSingleSpeed::performanceInputMethod() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->performanceInputMethod();
}

double EvaporativeFluidCoolerSingleSpeed::heatRejectionCapacityandNominalCapacitySizingRatio() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->heatRejectionCapacityandNominalCapacitySizingRatio();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::standardDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->standardDesignCapacity();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::ufactorTimesAreaValueatDesignAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->ufactorTimesAreaValueatDesignAirFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::isUfactorTimesAreaValueatDesignAirFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isUfactorTimesAreaValueatDesignAirFlowRateAutosized();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::designWaterFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->designWaterFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isDesignWaterFlowRateAutosized();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::userSpecifiedDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->userSpecifiedDesignCapacity();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::designEnteringWaterTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->designEnteringWaterTemperature();
}

bool EvaporativeFluidCoolerSingleSpeed::isDesignEnteringWaterTemperatureAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isDesignEnteringWaterTemperatureAutosized();
}

double EvaporativeFluidCoolerSingleSpeed::designEnteringAirTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->designEnteringAirTemperature();
}

double EvaporativeFluidCoolerSingleSpeed::designEnteringAirWetbulbTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->designEnteringAirWetbulbTemperature();
}

std::string EvaporativeFluidCoolerSingleSpeed::capacityControl() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->capacityControl();
}

bool EvaporativeFluidCoolerSingleSpeed::isCapacityControlDefaulted() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isCapacityControlDefaulted();
}

double EvaporativeFluidCoolerSingleSpeed::sizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->sizingFactor();
}

bool EvaporativeFluidCoolerSingleSpeed::isSizingFactorDefaulted() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isSizingFactorDefaulted();
}

std::string EvaporativeFluidCoolerSingleSpeed::evaporationLossMode() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->evaporationLossMode();
}

bool EvaporativeFluidCoolerSingleSpeed::isEvaporationLossModeDefaulted() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isEvaporationLossModeDefaulted();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::evaporationLossFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->evaporationLossFactor();
}

double EvaporativeFluidCoolerSingleSpeed::driftLossPercent() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->driftLossPercent();
}

bool EvaporativeFluidCoolerSingleSpeed::isDriftLossPercentDefaulted() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isDriftLossPercentDefaulted();
}

std::string EvaporativeFluidCoolerSingleSpeed::blowdownCalculationMode() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->blowdownCalculationMode();
}

bool EvaporativeFluidCoolerSingleSpeed::isBlowdownCalculationModeDefaulted() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isBlowdownCalculationModeDefaulted();
}

double EvaporativeFluidCoolerSingleSpeed::blowdownConcentrationRatio() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->blowdownConcentrationRatio();
}

bool EvaporativeFluidCoolerSingleSpeed::isBlowdownConcentrationRatioDefaulted() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->isBlowdownConcentrationRatioDefaulted();
}

bool EvaporativeFluidCoolerSingleSpeed::setDesignAirFlowRate(double designAirFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRate(designAirFlowRate);
}

void EvaporativeFluidCoolerSingleSpeed::autosizeDesignAirFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::setFanPoweratDesignAirFlowRate(double fanPoweratDesignAirFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setFanPoweratDesignAirFlowRate(fanPoweratDesignAirFlowRate);
}

void EvaporativeFluidCoolerSingleSpeed::autosizeFanPoweratDesignAirFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizeFanPoweratDesignAirFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::setDesignSprayWaterFlowRate(double designSprayWaterFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDesignSprayWaterFlowRate(designSprayWaterFlowRate);
}

bool EvaporativeFluidCoolerSingleSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
}

bool EvaporativeFluidCoolerSingleSpeed::setHeatRejectionCapacityandNominalCapacitySizingRatio(
  double heatRejectionCapacityandNominalCapacitySizingRatio) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setHeatRejectionCapacityandNominalCapacitySizingRatio(
    heatRejectionCapacityandNominalCapacitySizingRatio);
}

bool EvaporativeFluidCoolerSingleSpeed::setStandardDesignCapacity(double standardDesignCapacity) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setStandardDesignCapacity(standardDesignCapacity);
}

void EvaporativeFluidCoolerSingleSpeed::resetStandardDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetStandardDesignCapacity();
}

bool EvaporativeFluidCoolerSingleSpeed::setUfactorTimesAreaValueatDesignAirFlowRate(double ufactorTimesAreaValueatDesignAirFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setUfactorTimesAreaValueatDesignAirFlowRate(
    ufactorTimesAreaValueatDesignAirFlowRate);
}

void EvaporativeFluidCoolerSingleSpeed::resetUfactorTimesAreaValueatDesignAirFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetUfactorTimesAreaValueatDesignAirFlowRate();
}

void EvaporativeFluidCoolerSingleSpeed::autosizeUfactorTimesAreaValueatDesignAirFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizeUfactorTimesAreaValueatDesignAirFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
}

void EvaporativeFluidCoolerSingleSpeed::resetDesignWaterFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetDesignWaterFlowRate();
}

void EvaporativeFluidCoolerSingleSpeed::autosizeDesignWaterFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizeDesignWaterFlowRate();
}

bool EvaporativeFluidCoolerSingleSpeed::setUserSpecifiedDesignCapacity(double userSpecifiedDesignCapacity) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setUserSpecifiedDesignCapacity(userSpecifiedDesignCapacity);
}

void EvaporativeFluidCoolerSingleSpeed::resetUserSpecifiedDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetUserSpecifiedDesignCapacity();
}

bool EvaporativeFluidCoolerSingleSpeed::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDesignEnteringWaterTemperature(designEnteringWaterTemperature);
}

void EvaporativeFluidCoolerSingleSpeed::autosizeDesignEnteringWaterTemperature() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizeDesignEnteringWaterTemperature();
}

bool EvaporativeFluidCoolerSingleSpeed::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDesignEnteringAirTemperature(designEnteringAirTemperature);
}

bool EvaporativeFluidCoolerSingleSpeed::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDesignEnteringAirWetbulbTemperature(designEnteringAirWetbulbTemperature);
}

bool EvaporativeFluidCoolerSingleSpeed::setCapacityControl(const std::string& capacityControl) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setCapacityControl(capacityControl);
}

void EvaporativeFluidCoolerSingleSpeed::resetCapacityControl() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetCapacityControl();
}

bool EvaporativeFluidCoolerSingleSpeed::setSizingFactor(double sizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setSizingFactor(sizingFactor);
}

void EvaporativeFluidCoolerSingleSpeed::resetSizingFactor() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetSizingFactor();
}

bool EvaporativeFluidCoolerSingleSpeed::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setEvaporationLossMode(evaporationLossMode);
}

void EvaporativeFluidCoolerSingleSpeed::resetEvaporationLossMode() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetEvaporationLossMode();
}

bool EvaporativeFluidCoolerSingleSpeed::setEvaporationLossFactor(double evaporationLossFactor) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setEvaporationLossFactor(evaporationLossFactor);
}

void EvaporativeFluidCoolerSingleSpeed::resetEvaporationLossFactor() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetEvaporationLossFactor();
}

bool EvaporativeFluidCoolerSingleSpeed::setDriftLossPercent(double driftLossPercent) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setDriftLossPercent(driftLossPercent);
}

void EvaporativeFluidCoolerSingleSpeed::resetDriftLossPercent() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetDriftLossPercent();
}

bool EvaporativeFluidCoolerSingleSpeed::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setBlowdownCalculationMode(blowdownCalculationMode);
}

void EvaporativeFluidCoolerSingleSpeed::resetBlowdownCalculationMode() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetBlowdownCalculationMode();
}

bool EvaporativeFluidCoolerSingleSpeed::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
}

void EvaporativeFluidCoolerSingleSpeed::resetBlowdownConcentrationRatio() {
  getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->resetBlowdownConcentrationRatio();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::autosizedDesignAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::autosizedFanPoweratDesignAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizedFanPoweratDesignAirFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::autosizedUfactorTimesAreaValueatDesignAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizedUfactorTimesAreaValueatDesignAirFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::autosizedDesignWaterFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizedDesignWaterFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed::autosizedDesignEnteringWaterTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerSingleSpeed_Impl>()->autosizedDesignEnteringWaterTemperature();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned EvaporativeFluidCoolerSingleSpeed_Impl::inletPort() const {
  return openstudio::EvaporativeFluidCooler_SingleSpeedFields::WaterInletNodeName;
}

unsigned EvaporativeFluidCoolerSingleSpeed_Impl::outletPort() const {
  return openstudio::EvaporativeFluidCooler_SingleSpeedFields::WaterOutletNodeName;
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed_Impl::performanceInputMethodValues() const {
  return EvaporativeFluidCoolerSingleSpeed::performanceInputMethodValues();
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed_Impl::capacityControlValues() const {
  return EvaporativeFluidCoolerSingleSpeed::capacityControlValues();
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed_Impl::evaporationLossModeValues() const {
  return EvaporativeFluidCoolerSingleSpeed::evaporationLossModeValues();
}

std::vector<std::string> EvaporativeFluidCoolerSingleSpeed_Impl::blowdownCalculationModeValues() const {
  return EvaporativeFluidCoolerSingleSpeed::blowdownCalculationModeValues();
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::designAirFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRate, true);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isDesignAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::fanPoweratDesignAirFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, true);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isFanPoweratDesignAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double EvaporativeFluidCoolerSingleSpeed_Impl::designSprayWaterFlowRate() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignSprayWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

std::string EvaporativeFluidCoolerSingleSpeed_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerSingleSpeed_Impl::heatRejectionCapacityandNominalCapacitySizingRatio() const {
  const auto value =
    getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::standardDesignCapacity() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::StandardDesignCapacity, true);
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::ufactorTimesAreaValueatDesignAirFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, true);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isUfactorTimesAreaValueatDesignAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate, true);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isDesignWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::userSpecifiedDesignCapacity() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::UserSpecifiedDesignCapacity, true);
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::designEnteringWaterTemperature() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, true);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isDesignEnteringWaterTemperatureAutosized() const {
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double EvaporativeFluidCoolerSingleSpeed_Impl::designEnteringAirTemperature() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerSingleSpeed_Impl::designEnteringAirWetbulbTemperature() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

std::string EvaporativeFluidCoolerSingleSpeed_Impl::capacityControl() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::CapacityControl, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isCapacityControlDefaulted() const {
  return isEmpty(openstudio::EvaporativeFluidCooler_SingleSpeedFields::CapacityControl);
}

double EvaporativeFluidCoolerSingleSpeed_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isSizingFactorDefaulted() const {
  return isEmpty(openstudio::EvaporativeFluidCooler_SingleSpeedFields::SizingFactor);
}

std::string EvaporativeFluidCoolerSingleSpeed_Impl::evaporationLossMode() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isEvaporationLossModeDefaulted() const {
  return isEmpty(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode);
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::evaporationLossFactor() const {
  return getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossFactor, true);
}

double EvaporativeFluidCoolerSingleSpeed_Impl::driftLossPercent() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DriftLossPercent, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isDriftLossPercentDefaulted() const {
  return isEmpty(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DriftLossPercent);
}

std::string EvaporativeFluidCoolerSingleSpeed_Impl::blowdownCalculationMode() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isBlowdownCalculationModeDefaulted() const {
  return isEmpty(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode);
}

double EvaporativeFluidCoolerSingleSpeed_Impl::blowdownConcentrationRatio() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownConcentrationRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::isBlowdownConcentrationRatioDefaulted() const {
  return isEmpty(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownConcentrationRatio);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDesignAirFlowRate(boost::optional<double> designAirFlowRate) {
  bool result = false;
  if (designAirFlowRate) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRate, *designAirFlowRate);
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRate, "Autosize"));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setFanPoweratDesignAirFlowRate(boost::optional<double> fanPoweratDesignAirFlowRate) {
  bool result = false;
  if (fanPoweratDesignAirFlowRate) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, *fanPoweratDesignAirFlowRate);
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::autosizeFanPoweratDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, "Autosize"));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDesignSprayWaterFlowRate(double designSprayWaterFlowRate) {
  return setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignSprayWaterFlowRate, designSprayWaterFlowRate);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::PerformanceInputMethod, performanceInputMethod);
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setHeatRejectionCapacityandNominalCapacitySizingRatio(
  double heatRejectionCapacityandNominalCapacitySizingRatio) {
  const bool result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio,
                                heatRejectionCapacityandNominalCapacitySizingRatio);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setStandardDesignCapacity(boost::optional<double> standardDesignCapacity) {
  bool result = false;
  if (standardDesignCapacity) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::StandardDesignCapacity, *standardDesignCapacity);
  } else {
    resetStandardDesignCapacity();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetStandardDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::StandardDesignCapacity, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setUfactorTimesAreaValueatDesignAirFlowRate(
  boost::optional<double> ufactorTimesAreaValueatDesignAirFlowRate) {
  bool result = false;
  if (ufactorTimesAreaValueatDesignAirFlowRate) {
    result =
      setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, *ufactorTimesAreaValueatDesignAirFlowRate);
  } else {
    resetUfactorTimesAreaValueatDesignAirFlowRate();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetUfactorTimesAreaValueatDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, ""));
}

void EvaporativeFluidCoolerSingleSpeed_Impl::autosizeUfactorTimesAreaValueatDesignAirFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, "Autosize"));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate) {
  bool result = false;
  if (designWaterFlowRate) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate, *designWaterFlowRate);
  } else {
    resetDesignWaterFlowRate();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate, ""));
}

void EvaporativeFluidCoolerSingleSpeed_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate, "Autosize"));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setUserSpecifiedDesignCapacity(boost::optional<double> userSpecifiedDesignCapacity) {
  bool result = false;
  if (userSpecifiedDesignCapacity) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::UserSpecifiedDesignCapacity, *userSpecifiedDesignCapacity);
  } else {
    resetUserSpecifiedDesignCapacity();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetUserSpecifiedDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::UserSpecifiedDesignCapacity, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature) {
  bool result = false;
  if (designEnteringWaterTemperature) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, *designEnteringWaterTemperature);
  }
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::autosizeDesignEnteringWaterTemperature() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, "Autosize"));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature) {
  bool result = false;
  if (designEnteringAirTemperature) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, *designEnteringAirTemperature);
  }
  return result;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDesignEnteringAirWetbulbTemperature(
  boost::optional<double> designEnteringAirWetbulbTemperature) {
  bool result = false;
  if (designEnteringAirWetbulbTemperature) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature,
                       *designEnteringAirWetbulbTemperature);
  }
  return result;
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setCapacityControl(const std::string& capacityControl) {
  return setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::CapacityControl, capacityControl);
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetCapacityControl() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::CapacityControl, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setSizingFactor(double sizingFactor) {
  return setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::SizingFactor, sizingFactor);
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetSizingFactor() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::SizingFactor, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode, evaporationLossMode);
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetEvaporationLossMode() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setEvaporationLossFactor(boost::optional<double> evaporationLossFactor) {
  bool result = false;
  if (evaporationLossFactor) {
    result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossFactor, *evaporationLossFactor);
  } else {
    resetEvaporationLossFactor();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetEvaporationLossFactor() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossFactor, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setDriftLossPercent(double driftLossPercent) {
  const bool result = setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DriftLossPercent, driftLossPercent);
  OS_ASSERT(result);
  return result;
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetDriftLossPercent() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::DriftLossPercent, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode, blowdownCalculationMode);
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetBlowdownCalculationMode() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode, ""));
}

bool EvaporativeFluidCoolerSingleSpeed_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return setDouble(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
}

void EvaporativeFluidCoolerSingleSpeed_Impl::resetBlowdownConcentrationRatio() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownConcentrationRatio, ""));
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::autosizedFanPoweratDesignAirFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::autosizedUfactorTimesAreaValueatDesignAirFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::autosizedDesignWaterFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerSingleSpeed_Impl::autosizedDesignEnteringWaterTemperature() const {
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
