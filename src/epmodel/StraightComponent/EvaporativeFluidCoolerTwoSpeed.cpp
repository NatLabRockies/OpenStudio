/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/EvaporativeFluidCoolerTwoSpeed.hpp"
#include "StraightComponent/EvaporativeFluidCoolerTwoSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/EvaporativeFluidCooler_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

EvaporativeFluidCoolerTwoSpeed::EvaporativeFluidCoolerTwoSpeed(const Model& model)
  : StraightComponent(EvaporativeFluidCoolerTwoSpeed::iddObjectType(), model) {
  bool ok = true;
  autosizeHighFanSpeedAirFlowRate();
  autosizeHighFanSpeedFanPower();
  autosizeLowFanSpeedAirFlowRate();
  ok = setLowFanSpeedAirFlowRateSizingFactor(0.5);
  OS_ASSERT(ok);
  autosizeLowFanSpeedFanPower();
  ok = setLowFanSpeedFanPowerSizingFactor(0.5);
  OS_ASSERT(ok);
  ok = setDesignSprayWaterFlowRate(0.002208);
  OS_ASSERT(ok);
  ok = setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate");
  OS_ASSERT(ok);
  ok = setHeatRejectionCapacityandNominalCapacitySizingRatio(1.25);
  OS_ASSERT(ok);
  autosizeLowSpeedUserSpecifiedDesignCapacity();
  autosizeLowSpeedStandardDesignCapacity();
  ok = setLowSpeedStandardCapacitySizingFactor(0.5);
  OS_ASSERT(ok);
  autosizeHighFanSpeedUfactorTimesAreaValue();
  autosizeLowFanSpeedUfactorTimesAreaValue();
  ok = setLowFanSpeedUFactorTimesAreaSizingFactor(0.6);
  OS_ASSERT(ok);
  ok = setLowSpeedUserSpecifiedDesignCapacitySizingFactor(0.5);
  OS_ASSERT(ok);
  autosizeDesignEnteringWaterTemperature();
  ok = setDesignEnteringAirTemperature(35.0);
  OS_ASSERT(ok);
  ok = setDesignEnteringAirWetbulbTemperature(25.6);
  OS_ASSERT(ok);
  ok = setHighSpeedSizingFactor(1.0);
  OS_ASSERT(ok);
  ok = setEvaporationLossMode("SaturatedExit");
  OS_ASSERT(ok);
  ok = setDriftLossPercent(0.008);
  OS_ASSERT(ok);
  ok = setBlowdownCalculationMode("ConcentrationRatio");
  OS_ASSERT(ok);
  ok = setBlowdownConcentrationRatio(3.0);
  OS_ASSERT(ok);
  autosizeDesignWaterFlowRate();
}

EvaporativeFluidCoolerTwoSpeed::EvaporativeFluidCoolerTwoSpeed(std::shared_ptr<detail::EvaporativeFluidCoolerTwoSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType EvaporativeFluidCoolerTwoSpeed::iddObjectType() {
  return IddObjectType::EvaporativeFluidCooler_TwoSpeed;
}

std::vector<std::string> EvaporativeFluidCoolerTwoSpeed::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_TwoSpeedFields::PerformanceInputMethod);
}

std::vector<std::string> EvaporativeFluidCoolerTwoSpeed::evaporationLossModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossMode);
}

std::vector<std::string> EvaporativeFluidCoolerTwoSpeed::blowdownCalculationModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::EvaporativeFluidCooler_TwoSpeedFields::BlowdownCalculationMode);
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::highFanSpeedAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->highFanSpeedAirFlowRate();
}

bool EvaporativeFluidCoolerTwoSpeed::isHighFanSpeedAirFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isHighFanSpeedAirFlowRateAutosized();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::highFanSpeedFanPower() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->highFanSpeedFanPower();
}

bool EvaporativeFluidCoolerTwoSpeed::isHighFanSpeedFanPowerAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isHighFanSpeedFanPowerAutosized();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::lowFanSpeedAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowFanSpeedAirFlowRate();
}

bool EvaporativeFluidCoolerTwoSpeed::isLowFanSpeedAirFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isLowFanSpeedAirFlowRateAutosized();
}

double EvaporativeFluidCoolerTwoSpeed::lowFanSpeedAirFlowRateSizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowFanSpeedAirFlowRateSizingFactor();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::lowFanSpeedFanPower() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowFanSpeedFanPower();
}

bool EvaporativeFluidCoolerTwoSpeed::isLowFanSpeedFanPowerAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isLowFanSpeedFanPowerAutosized();
}

double EvaporativeFluidCoolerTwoSpeed::lowFanSpeedFanPowerSizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowFanSpeedFanPowerSizingFactor();
}

double EvaporativeFluidCoolerTwoSpeed::designSprayWaterFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->designSprayWaterFlowRate();
}

std::string EvaporativeFluidCoolerTwoSpeed::performanceInputMethod() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->performanceInputMethod();
}

double EvaporativeFluidCoolerTwoSpeed::heatRejectionCapacityandNominalCapacitySizingRatio() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->heatRejectionCapacityandNominalCapacitySizingRatio();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::highSpeedStandardDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->highSpeedStandardDesignCapacity();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::lowSpeedStandardDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowSpeedStandardDesignCapacity();
}

bool EvaporativeFluidCoolerTwoSpeed::isLowSpeedStandardDesignCapacityAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isLowSpeedStandardDesignCapacityAutosized();
}

double EvaporativeFluidCoolerTwoSpeed::lowSpeedStandardCapacitySizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowSpeedStandardCapacitySizingFactor();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::highFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->highFanSpeedUfactorTimesAreaValue();
}

bool EvaporativeFluidCoolerTwoSpeed::isHighFanSpeedUfactorTimesAreaValueAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isHighFanSpeedUfactorTimesAreaValueAutosized();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::lowFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowFanSpeedUfactorTimesAreaValue();
}

bool EvaporativeFluidCoolerTwoSpeed::isLowFanSpeedUfactorTimesAreaValueAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isLowFanSpeedUfactorTimesAreaValueAutosized();
}

double EvaporativeFluidCoolerTwoSpeed::lowFanSpeedUFactorTimesAreaSizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowFanSpeedUFactorTimesAreaSizingFactor();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::designWaterFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->designWaterFlowRate();
}

bool EvaporativeFluidCoolerTwoSpeed::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isDesignWaterFlowRateAutosized();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::highSpeedUserSpecifiedDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->highSpeedUserSpecifiedDesignCapacity();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::lowSpeedUserSpecifiedDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowSpeedUserSpecifiedDesignCapacity();
}

bool EvaporativeFluidCoolerTwoSpeed::isLowSpeedUserSpecifiedDesignCapacityAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isLowSpeedUserSpecifiedDesignCapacityAutosized();
}

double EvaporativeFluidCoolerTwoSpeed::lowSpeedUserSpecifiedDesignCapacitySizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->lowSpeedUserSpecifiedDesignCapacitySizingFactor();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::designEnteringWaterTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->designEnteringWaterTemperature();
}

bool EvaporativeFluidCoolerTwoSpeed::isDesignEnteringWaterTemperatureAutosized() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->isDesignEnteringWaterTemperatureAutosized();
}

double EvaporativeFluidCoolerTwoSpeed::designEnteringAirTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->designEnteringAirTemperature();
}

double EvaporativeFluidCoolerTwoSpeed::designEnteringAirWetbulbTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->designEnteringAirWetbulbTemperature();
}

double EvaporativeFluidCoolerTwoSpeed::highSpeedSizingFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->highSpeedSizingFactor();
}

std::string EvaporativeFluidCoolerTwoSpeed::evaporationLossMode() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->evaporationLossMode();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::evaporationLossFactor() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->evaporationLossFactor();
}

double EvaporativeFluidCoolerTwoSpeed::driftLossPercent() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->driftLossPercent();
}

std::string EvaporativeFluidCoolerTwoSpeed::blowdownCalculationMode() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->blowdownCalculationMode();
}

double EvaporativeFluidCoolerTwoSpeed::blowdownConcentrationRatio() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->blowdownConcentrationRatio();
}

bool EvaporativeFluidCoolerTwoSpeed::setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHighFanSpeedAirFlowRate(highFanSpeedAirFlowRate);
}

void EvaporativeFluidCoolerTwoSpeed::autosizeHighFanSpeedAirFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedAirFlowRate();
}

bool EvaporativeFluidCoolerTwoSpeed::setHighFanSpeedFanPower(double highFanSpeedFanPower) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHighFanSpeedFanPower(highFanSpeedFanPower);
}

void EvaporativeFluidCoolerTwoSpeed::autosizeHighFanSpeedFanPower() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedFanPower();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRate(lowFanSpeedAirFlowRate);
}

void EvaporativeFluidCoolerTwoSpeed::autosizeLowFanSpeedAirFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedAirFlowRate();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRateSizingFactor(lowFanSpeedAirFlowRateSizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed::setLowFanSpeedFanPower(double lowFanSpeedFanPower) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowFanSpeedFanPower(lowFanSpeedFanPower);
}

void EvaporativeFluidCoolerTwoSpeed::autosizeLowFanSpeedFanPower() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedFanPower();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowFanSpeedFanPowerSizingFactor(lowFanSpeedFanPowerSizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed::setDesignSprayWaterFlowRate(double designSprayWaterFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setDesignSprayWaterFlowRate(designSprayWaterFlowRate);
}

bool EvaporativeFluidCoolerTwoSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
}

bool EvaporativeFluidCoolerTwoSpeed::setHeatRejectionCapacityandNominalCapacitySizingRatio(
  double heatRejectionCapacityandNominalCapacitySizingRatio) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHeatRejectionCapacityandNominalCapacitySizingRatio(
    heatRejectionCapacityandNominalCapacitySizingRatio);
}

bool EvaporativeFluidCoolerTwoSpeed::setHighSpeedStandardDesignCapacity(double highSpeedStandardDesignCapacity) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHighSpeedStandardDesignCapacity(highSpeedStandardDesignCapacity);
}

void EvaporativeFluidCoolerTwoSpeed::resetHighSpeedStandardDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetHighSpeedStandardDesignCapacity();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowSpeedStandardDesignCapacity(double lowSpeedStandardDesignCapacity) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowSpeedStandardDesignCapacity(lowSpeedStandardDesignCapacity);
}

void EvaporativeFluidCoolerTwoSpeed::resetLowSpeedStandardDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetLowSpeedStandardDesignCapacity();
}

void EvaporativeFluidCoolerTwoSpeed::autosizeLowSpeedStandardDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeLowSpeedStandardDesignCapacity();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowSpeedStandardCapacitySizingFactor(double lowSpeedStandardCapacitySizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowSpeedStandardCapacitySizingFactor(lowSpeedStandardCapacitySizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed::setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHighFanSpeedUfactorTimesAreaValue(highFanSpeedUfactorTimesAreaValue);
}

void EvaporativeFluidCoolerTwoSpeed::resetHighFanSpeedUfactorTimesAreaValue() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetHighFanSpeedUfactorTimesAreaValue();
}

void EvaporativeFluidCoolerTwoSpeed::autosizeHighFanSpeedUfactorTimesAreaValue() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedUfactorTimesAreaValue();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowFanSpeedUfactorTimesAreaValue(lowFanSpeedUfactorTimesAreaValue);
}

void EvaporativeFluidCoolerTwoSpeed::resetLowFanSpeedUfactorTimesAreaValue() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetLowFanSpeedUfactorTimesAreaValue();
}

void EvaporativeFluidCoolerTwoSpeed::autosizeLowFanSpeedUfactorTimesAreaValue() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedUfactorTimesAreaValue();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowFanSpeedUFactorTimesAreaSizingFactor(lowFanSpeedUFactorTimesAreaSizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
}

void EvaporativeFluidCoolerTwoSpeed::resetDesignWaterFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetDesignWaterFlowRate();
}

void EvaporativeFluidCoolerTwoSpeed::autosizeDesignWaterFlowRate() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeDesignWaterFlowRate();
}

bool EvaporativeFluidCoolerTwoSpeed::setHighSpeedUserSpecifiedDesignCapacity(double highSpeedUserSpecifiedDesignCapacity) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHighSpeedUserSpecifiedDesignCapacity(highSpeedUserSpecifiedDesignCapacity);
}

void EvaporativeFluidCoolerTwoSpeed::resetHighSpeedUserSpecifiedDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetHighSpeedUserSpecifiedDesignCapacity();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowSpeedUserSpecifiedDesignCapacity(double lowSpeedUserSpecifiedDesignCapacity) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowSpeedUserSpecifiedDesignCapacity(lowSpeedUserSpecifiedDesignCapacity);
}

void EvaporativeFluidCoolerTwoSpeed::resetLowSpeedUserSpecifiedDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetLowSpeedUserSpecifiedDesignCapacity();
}

void EvaporativeFluidCoolerTwoSpeed::autosizeLowSpeedUserSpecifiedDesignCapacity() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeLowSpeedUserSpecifiedDesignCapacity();
}

bool EvaporativeFluidCoolerTwoSpeed::setLowSpeedUserSpecifiedDesignCapacitySizingFactor(
  double lowSpeedUserSpecifiedDesignCapacitySizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setLowSpeedUserSpecifiedDesignCapacitySizingFactor(
    lowSpeedUserSpecifiedDesignCapacitySizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setDesignEnteringWaterTemperature(designEnteringWaterTemperature);
}

void EvaporativeFluidCoolerTwoSpeed::autosizeDesignEnteringWaterTemperature() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizeDesignEnteringWaterTemperature();
}

bool EvaporativeFluidCoolerTwoSpeed::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setDesignEnteringAirTemperature(designEnteringAirTemperature);
}

bool EvaporativeFluidCoolerTwoSpeed::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setDesignEnteringAirWetbulbTemperature(designEnteringAirWetbulbTemperature);
}

bool EvaporativeFluidCoolerTwoSpeed::setHighSpeedSizingFactor(double highSpeedSizingFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setHighSpeedSizingFactor(highSpeedSizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setEvaporationLossMode(evaporationLossMode);
}

bool EvaporativeFluidCoolerTwoSpeed::setEvaporationLossFactor(double evaporationLossFactor) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setEvaporationLossFactor(evaporationLossFactor);
}

void EvaporativeFluidCoolerTwoSpeed::resetEvaporationLossFactor() {
  getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->resetEvaporationLossFactor();
}

bool EvaporativeFluidCoolerTwoSpeed::setDriftLossPercent(double driftLossPercent) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setDriftLossPercent(driftLossPercent);
}

bool EvaporativeFluidCoolerTwoSpeed::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setBlowdownCalculationMode(blowdownCalculationMode);
}

bool EvaporativeFluidCoolerTwoSpeed::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->setBlowdownConcentrationRatio(blowdownConcentrationRatio);
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedHighFanSpeedAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedAirFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedHighFanSpeedFanPower() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedFanPower();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedLowFanSpeedAirFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedAirFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedLowFanSpeedFanPower() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedFanPower();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedLowSpeedStandardDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedLowSpeedStandardDesignCapacity();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedHighFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedUfactorTimesAreaValue();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedLowFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedUfactorTimesAreaValue();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedDesignWaterFlowRate() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedDesignWaterFlowRate();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedLowSpeedUserSpecifiedDesignCapacity() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedLowSpeedUserSpecifiedDesignCapacity();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed::autosizedDesignEnteringWaterTemperature() const {
  return getImpl<detail::EvaporativeFluidCoolerTwoSpeed_Impl>()->autosizedDesignEnteringWaterTemperature();
}

namespace detail {

unsigned EvaporativeFluidCoolerTwoSpeed_Impl::inletPort() const {
  return openstudio::EvaporativeFluidCooler_TwoSpeedFields::WaterInletNodeName;
}

unsigned EvaporativeFluidCoolerTwoSpeed_Impl::outletPort() const {
  return openstudio::EvaporativeFluidCooler_TwoSpeedFields::WaterOutletNodeName;
}

std::vector<std::string> EvaporativeFluidCoolerTwoSpeed_Impl::performanceInputMethodValues() const {
  return EvaporativeFluidCoolerTwoSpeed::performanceInputMethodValues();
}

std::vector<std::string> EvaporativeFluidCoolerTwoSpeed_Impl::evaporationLossModeValues() const {
  return EvaporativeFluidCoolerTwoSpeed::evaporationLossModeValues();
}

std::vector<std::string> EvaporativeFluidCoolerTwoSpeed_Impl::blowdownCalculationModeValues() const {
  return EvaporativeFluidCoolerTwoSpeed::blowdownCalculationModeValues();
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::highFanSpeedAirFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isHighFanSpeedAirFlowRateAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::highFanSpeedFanPower() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedFanPower, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isHighFanSpeedFanPowerAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedFanPower, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::lowFanSpeedAirFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isLowFanSpeedAirFlowRateAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::lowFanSpeedAirFlowRateSizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::lowFanSpeedFanPower() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPower, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isLowFanSpeedFanPowerAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPower, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::lowFanSpeedFanPowerSizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::designSprayWaterFlowRate() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignSprayWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

std::string EvaporativeFluidCoolerTwoSpeed_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::heatRejectionCapacityandNominalCapacitySizingRatio() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::highSpeedStandardDesignCapacity() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedStandardDesignCapacity, true);
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::lowSpeedStandardDesignCapacity() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isLowSpeedStandardDesignCapacityAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::lowSpeedStandardCapacitySizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardCapacitySizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::highFanSpeedUfactorTimesAreaValue() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isHighFanSpeedUfactorTimesAreaValueAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::lowFanSpeedUfactorTimesAreaValue() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isLowFanSpeedUfactorTimesAreaValueAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::lowFanSpeedUFactorTimesAreaSizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isDesignWaterFlowRateAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::highSpeedUserSpecifiedDesignCapacity() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedUserSpecifiedDesignCapacity, true);
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::lowSpeedUserSpecifiedDesignCapacity() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isLowSpeedUserSpecifiedDesignCapacityAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::lowSpeedUserSpecifiedDesignCapacitySizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacitySizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::designEnteringWaterTemperature() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, true);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::isDesignEnteringWaterTemperatureAutosized() const {
  bool result = false;
  if (const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, true)) {
    result = openstudio::istringEqual(*value, "autosize");
  }
  return result;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::designEnteringAirTemperature() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::designEnteringAirWetbulbTemperature() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::highSpeedSizingFactor() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

std::string EvaporativeFluidCoolerTwoSpeed_Impl::evaporationLossMode() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossMode, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::evaporationLossFactor() const {
  return getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossFactor, true);
}

double EvaporativeFluidCoolerTwoSpeed_Impl::driftLossPercent() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DriftLossPercent, true);
  OS_ASSERT(value);
  return *value;
}

std::string EvaporativeFluidCoolerTwoSpeed_Impl::blowdownCalculationMode() const {
  const auto value = getString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::BlowdownCalculationMode, true);
  OS_ASSERT(value);
  return *value;
}

double EvaporativeFluidCoolerTwoSpeed_Impl::blowdownConcentrationRatio() const {
  const auto value = getDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::BlowdownConcentrationRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHighFanSpeedAirFlowRate(boost::optional<double> highFanSpeedAirFlowRate) {
  bool result = false;
  if (highFanSpeedAirFlowRate) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, *highFanSpeedAirFlowRate);
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedAirFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHighFanSpeedFanPower(boost::optional<double> highFanSpeedFanPower) {
  bool result = false;
  if (highFanSpeedFanPower) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedFanPower, *highFanSpeedFanPower);
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedFanPower() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedFanPower, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowFanSpeedAirFlowRate(boost::optional<double> lowFanSpeedAirFlowRate) {
  bool result = false;
  if (lowFanSpeedAirFlowRate) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, *lowFanSpeedAirFlowRate);
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedAirFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
  const bool result =
    setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, lowFanSpeedAirFlowRateSizingFactor);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowFanSpeedFanPower(boost::optional<double> lowFanSpeedFanPower) {
  bool result = false;
  if (lowFanSpeedFanPower) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPower, *lowFanSpeedFanPower);
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedFanPower() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPower, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
  const bool result =
    setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, lowFanSpeedFanPowerSizingFactor);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setDesignSprayWaterFlowRate(double designSprayWaterFlowRate) {
  return setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignSprayWaterFlowRate, designSprayWaterFlowRate);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::PerformanceInputMethod, performanceInputMethod);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHeatRejectionCapacityandNominalCapacitySizingRatio(
  double heatRejectionCapacityandNominalCapacitySizingRatio) {
  const bool result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio,
                                heatRejectionCapacityandNominalCapacitySizingRatio);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHighSpeedStandardDesignCapacity(boost::optional<double> highSpeedStandardDesignCapacity) {
  bool result = false;
  if (highSpeedStandardDesignCapacity) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedStandardDesignCapacity, *highSpeedStandardDesignCapacity);
  } else {
    resetHighSpeedStandardDesignCapacity();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetHighSpeedStandardDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedStandardDesignCapacity, ""));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowSpeedStandardDesignCapacity(boost::optional<double> lowSpeedStandardDesignCapacity) {
  bool result = false;
  if (lowSpeedStandardDesignCapacity) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity, *lowSpeedStandardDesignCapacity);
  } else {
    resetLowSpeedStandardDesignCapacity();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetLowSpeedStandardDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity, ""));
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeLowSpeedStandardDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowSpeedStandardCapacitySizingFactor(double lowSpeedStandardCapacitySizingFactor) {
  const bool result =
    setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardCapacitySizingFactor, lowSpeedStandardCapacitySizingFactor);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue) {
  bool result = false;
  if (highFanSpeedUfactorTimesAreaValue) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, *highFanSpeedUfactorTimesAreaValue);
  } else {
    resetHighFanSpeedUfactorTimesAreaValue();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetHighFanSpeedUfactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, ""));
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedUfactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue) {
  bool result = false;
  if (lowFanSpeedUfactorTimesAreaValue) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, *lowFanSpeedUfactorTimesAreaValue);
  } else {
    resetLowFanSpeedUfactorTimesAreaValue();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetLowFanSpeedUfactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, ""));
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedUfactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
  const bool result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor,
                                lowFanSpeedUFactorTimesAreaSizingFactor);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate) {
  bool result = false;
  if (designWaterFlowRate) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate, *designWaterFlowRate);
  } else {
    resetDesignWaterFlowRate();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate, ""));
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHighSpeedUserSpecifiedDesignCapacity(boost::optional<double> highSpeedUserSpecifiedDesignCapacity) {
  bool result = false;
  if (highSpeedUserSpecifiedDesignCapacity) {
    result =
      setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedUserSpecifiedDesignCapacity, *highSpeedUserSpecifiedDesignCapacity);
  } else {
    resetHighSpeedUserSpecifiedDesignCapacity();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetHighSpeedUserSpecifiedDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedUserSpecifiedDesignCapacity, ""));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowSpeedUserSpecifiedDesignCapacity(boost::optional<double> lowSpeedUserSpecifiedDesignCapacity) {
  bool result = false;
  if (lowSpeedUserSpecifiedDesignCapacity) {
    result =
      setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity, *lowSpeedUserSpecifiedDesignCapacity);
  } else {
    resetLowSpeedUserSpecifiedDesignCapacity();
    result = true;
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetLowSpeedUserSpecifiedDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity, ""));
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeLowSpeedUserSpecifiedDesignCapacity() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setLowSpeedUserSpecifiedDesignCapacitySizingFactor(
  double lowSpeedUserSpecifiedDesignCapacitySizingFactor) {
  const bool result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacitySizingFactor,
                                lowSpeedUserSpecifiedDesignCapacitySizingFactor);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature) {
  bool result = false;
  if (designEnteringWaterTemperature) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, *designEnteringWaterTemperature);
  }
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::autosizeDesignEnteringWaterTemperature() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, "Autosize"));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature) {
  bool result = false;
  if (designEnteringAirTemperature) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, *designEnteringAirTemperature);
  }
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setDesignEnteringAirWetbulbTemperature(
  boost::optional<double> designEnteringAirWetbulbTemperature) {
  bool result = false;
  if (designEnteringAirWetbulbTemperature) {
    result =
      setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, *designEnteringAirWetbulbTemperature);
  }
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setHighSpeedSizingFactor(double highSpeedSizingFactor) {
  return setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::HighSpeedSizingFactor, highSpeedSizingFactor);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setEvaporationLossMode(const std::string& evaporationLossMode) {
  return setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossMode, evaporationLossMode);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setEvaporationLossFactor(boost::optional<double> evaporationLossFactor) {
  bool result = false;
  if (evaporationLossFactor) {
    result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossFactor, *evaporationLossFactor);
  } else {
    resetEvaporationLossFactor();
    result = true;
  }
  OS_ASSERT(result);
  return result;
}

void EvaporativeFluidCoolerTwoSpeed_Impl::resetEvaporationLossFactor() {
  OS_ASSERT(setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossFactor, ""));
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setDriftLossPercent(double driftLossPercent) {
  const bool result = setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::DriftLossPercent, driftLossPercent);
  OS_ASSERT(result);
  return result;
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setBlowdownCalculationMode(const std::string& blowdownCalculationMode) {
  return setString(openstudio::EvaporativeFluidCooler_TwoSpeedFields::BlowdownCalculationMode, blowdownCalculationMode);
}

bool EvaporativeFluidCoolerTwoSpeed_Impl::setBlowdownConcentrationRatio(double blowdownConcentrationRatio) {
  return setDouble(openstudio::EvaporativeFluidCooler_TwoSpeedFields::BlowdownConcentrationRatio, blowdownConcentrationRatio);
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedAirFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedFanPower() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedAirFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedFanPower() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedLowSpeedStandardDesignCapacity() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedUfactorTimesAreaValue() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedUfactorTimesAreaValue() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedDesignWaterFlowRate() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedLowSpeedUserSpecifiedDesignCapacity() const {
  return boost::none;
}

boost::optional<double> EvaporativeFluidCoolerTwoSpeed_Impl::autosizedDesignEnteringWaterTemperature() const {
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
