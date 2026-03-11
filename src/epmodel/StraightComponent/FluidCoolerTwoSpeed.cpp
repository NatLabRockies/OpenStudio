/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FluidCoolerTwoSpeed.hpp"
#include "StraightComponent/FluidCoolerTwoSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/FluidCooler_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

FluidCoolerTwoSpeed::FluidCoolerTwoSpeed(const Model& model) : StraightComponent(FluidCoolerTwoSpeed::iddObjectType(), model) {
  bool ok = true;
  ok = setPerformanceInputMethod("NominalCapacity");
  OS_ASSERT(ok);
  autosizeHighFanSpeedUfactorTimesAreaValue();
  autosizeLowFanSpeedUfactorTimesAreaValue();
  ok = setLowFanSpeedUFactorTimesAreaSizingFactor(0.6);
  OS_ASSERT(ok);
  ok = setHighSpeedNominalCapacity(58601.0);
  OS_ASSERT(ok);
  ok = setLowSpeedNominalCapacity(28601.0);
  OS_ASSERT(ok);
  ok = setLowSpeedNominalCapacitySizingFactor(0.5);
  OS_ASSERT(ok);
  ok = setDesignEnteringWaterTemperature(51.67);
  OS_ASSERT(ok);
  ok = setDesignEnteringAirTemperature(35.0);
  OS_ASSERT(ok);
  ok = setDesignEnteringAirWetbulbTemperature(25.6);
  OS_ASSERT(ok);
  ok = setDesignWaterFlowRate(0.001388);
  OS_ASSERT(ok);
  ok = setHighFanSpeedAirFlowRate(9.911);
  OS_ASSERT(ok);
  autosizeHighFanSpeedFanPower();
  ok = setLowFanSpeedAirFlowRate(4.955);
  OS_ASSERT(ok);
  ok = setLowFanSpeedAirFlowRateSizingFactor(0.5);
  OS_ASSERT(ok);
  autosizeLowFanSpeedFanPower();
  ok = setLowFanSpeedFanPowerSizingFactor(0.16);
  OS_ASSERT(ok);
}

FluidCoolerTwoSpeed::FluidCoolerTwoSpeed(std::shared_ptr<detail::FluidCoolerTwoSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType FluidCoolerTwoSpeed::iddObjectType() {
  return IddObjectType::FluidCooler_TwoSpeed;
}

std::vector<std::string> FluidCoolerTwoSpeed::performanceInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FluidCooler_TwoSpeedFields::PerformanceInputMethod);
}

std::string FluidCoolerTwoSpeed::performanceInputMethod() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->performanceInputMethod();
}

boost::optional<double> FluidCoolerTwoSpeed::highFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highFanSpeedUfactorTimesAreaValue();
}

bool FluidCoolerTwoSpeed::isHighFanSpeedUfactorTimesAreaValueAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isHighFanSpeedUfactorTimesAreaValueAutosized();
}

boost::optional<double> FluidCoolerTwoSpeed::lowFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedUfactorTimesAreaValue();
}

bool FluidCoolerTwoSpeed::isLowFanSpeedUfactorTimesAreaValueAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowFanSpeedUfactorTimesAreaValueAutosized();
}

double FluidCoolerTwoSpeed::lowFanSpeedUFactorTimesAreaSizingFactor() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedUFactorTimesAreaSizingFactor();
}

double FluidCoolerTwoSpeed::highSpeedNominalCapacity() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highSpeedNominalCapacity();
}

boost::optional<double> FluidCoolerTwoSpeed::lowSpeedNominalCapacity() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowSpeedNominalCapacity();
}

bool FluidCoolerTwoSpeed::isLowSpeedNominalCapacityAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowSpeedNominalCapacityAutosized();
}

double FluidCoolerTwoSpeed::lowSpeedNominalCapacitySizingFactor() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowSpeedNominalCapacitySizingFactor();
}

double FluidCoolerTwoSpeed::designEnteringWaterTemperature() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designEnteringWaterTemperature();
}

double FluidCoolerTwoSpeed::designEnteringAirTemperature() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designEnteringAirTemperature();
}

double FluidCoolerTwoSpeed::designEnteringAirWetbulbTemperature() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designEnteringAirWetbulbTemperature();
}

boost::optional<double> FluidCoolerTwoSpeed::designWaterFlowRate() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designWaterFlowRate();
}

bool FluidCoolerTwoSpeed::isDesignWaterFlowRateAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isDesignWaterFlowRateAutosized();
}

boost::optional<double> FluidCoolerTwoSpeed::highFanSpeedAirFlowRate() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highFanSpeedAirFlowRate();
}

bool FluidCoolerTwoSpeed::isHighFanSpeedAirFlowRateAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isHighFanSpeedAirFlowRateAutosized();
}

boost::optional<double> FluidCoolerTwoSpeed::highFanSpeedFanPower() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highFanSpeedFanPower();
}

bool FluidCoolerTwoSpeed::isHighFanSpeedFanPowerAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isHighFanSpeedFanPowerAutosized();
}

boost::optional<double> FluidCoolerTwoSpeed::lowFanSpeedAirFlowRate() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedAirFlowRate();
}

bool FluidCoolerTwoSpeed::isLowFanSpeedAirFlowRateAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowFanSpeedAirFlowRateAutosized();
}

double FluidCoolerTwoSpeed::lowFanSpeedAirFlowRateSizingFactor() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedAirFlowRateSizingFactor();
}

boost::optional<double> FluidCoolerTwoSpeed::lowFanSpeedFanPower() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedFanPower();
}

bool FluidCoolerTwoSpeed::isLowFanSpeedFanPowerAutosized() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowFanSpeedFanPowerAutosized();
}

double FluidCoolerTwoSpeed::lowFanSpeedFanPowerSizingFactor() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedFanPowerSizingFactor();
}

bool FluidCoolerTwoSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
}

bool FluidCoolerTwoSpeed::setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighFanSpeedUfactorTimesAreaValue(highFanSpeedUfactorTimesAreaValue);
}

void FluidCoolerTwoSpeed::autosizeHighFanSpeedUfactorTimesAreaValue() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedUfactorTimesAreaValue();
}

bool FluidCoolerTwoSpeed::setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedUfactorTimesAreaValue(lowFanSpeedUfactorTimesAreaValue);
}

void FluidCoolerTwoSpeed::autosizeLowFanSpeedUfactorTimesAreaValue() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedUfactorTimesAreaValue();
}

bool FluidCoolerTwoSpeed::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedUFactorTimesAreaSizingFactor(lowFanSpeedUFactorTimesAreaSizingFactor);
}

bool FluidCoolerTwoSpeed::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighSpeedNominalCapacity(highSpeedNominalCapacity);
}

bool FluidCoolerTwoSpeed::setLowSpeedNominalCapacity(double lowSpeedNominalCapacity) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowSpeedNominalCapacity(lowSpeedNominalCapacity);
}

void FluidCoolerTwoSpeed::autosizeLowSpeedNominalCapacity() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowSpeedNominalCapacity();
}

bool FluidCoolerTwoSpeed::setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowSpeedNominalCapacitySizingFactor(lowSpeedNominalCapacitySizingFactor);
}

bool FluidCoolerTwoSpeed::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignEnteringWaterTemperature(designEnteringWaterTemperature);
}

bool FluidCoolerTwoSpeed::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignEnteringAirTemperature(designEnteringAirTemperature);
}

bool FluidCoolerTwoSpeed::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignEnteringAirWetbulbTemperature(designEnteringAirWetbulbTemperature);
}

bool FluidCoolerTwoSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
}

void FluidCoolerTwoSpeed::autosizeDesignWaterFlowRate() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeDesignWaterFlowRate();
}

bool FluidCoolerTwoSpeed::setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighFanSpeedAirFlowRate(highFanSpeedAirFlowRate);
}

void FluidCoolerTwoSpeed::autosizeHighFanSpeedAirFlowRate() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedAirFlowRate();
}

bool FluidCoolerTwoSpeed::setHighFanSpeedFanPower(double highFanSpeedFanPower) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighFanSpeedFanPower(highFanSpeedFanPower);
}

void FluidCoolerTwoSpeed::autosizeHighFanSpeedFanPower() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedFanPower();
}

bool FluidCoolerTwoSpeed::setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRate(lowFanSpeedAirFlowRate);
}

void FluidCoolerTwoSpeed::autosizeLowFanSpeedAirFlowRate() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedAirFlowRate();
}

bool FluidCoolerTwoSpeed::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRateSizingFactor(lowFanSpeedAirFlowRateSizingFactor);
}

bool FluidCoolerTwoSpeed::setLowFanSpeedFanPower(double lowFanSpeedFanPower) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedFanPower(lowFanSpeedFanPower);
}

void FluidCoolerTwoSpeed::autosizeLowFanSpeedFanPower() {
  getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedFanPower();
}

bool FluidCoolerTwoSpeed::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedFanPowerSizingFactor(lowFanSpeedFanPowerSizingFactor);
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedHighFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedUfactorTimesAreaValue();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedLowFanSpeedUfactorTimesAreaValue() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedUfactorTimesAreaValue();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedLowSpeedNominalCapacity() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowSpeedNominalCapacity();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedDesignWaterFlowRate() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedDesignWaterFlowRate();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedHighFanSpeedAirFlowRate() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedAirFlowRate();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedHighFanSpeedFanPower() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedFanPower();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedLowFanSpeedAirFlowRate() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedAirFlowRate();
}

boost::optional<double> FluidCoolerTwoSpeed::autosizedLowFanSpeedFanPower() const {
  return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedFanPower();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned FluidCoolerTwoSpeed_Impl::inletPort() const {
  return openstudio::FluidCooler_TwoSpeedFields::WaterInletNodeName;
}

unsigned FluidCoolerTwoSpeed_Impl::outletPort() const {
  return openstudio::FluidCooler_TwoSpeedFields::WaterOutletNodeName;
}

std::vector<std::string> FluidCoolerTwoSpeed_Impl::performanceInputMethodValues() const {
  return FluidCoolerTwoSpeed::performanceInputMethodValues();
}

std::string FluidCoolerTwoSpeed_Impl::performanceInputMethod() const {
  const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::PerformanceInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::highFanSpeedUfactorTimesAreaValue() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, true);
}

bool FluidCoolerTwoSpeed_Impl::isHighFanSpeedUfactorTimesAreaValueAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::lowFanSpeedUfactorTimesAreaValue() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, true);
}

bool FluidCoolerTwoSpeed_Impl::isLowFanSpeedUfactorTimesAreaValueAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double FluidCoolerTwoSpeed_Impl::lowFanSpeedUFactorTimesAreaSizingFactor() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FluidCoolerTwoSpeed_Impl::highSpeedNominalCapacity() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::HighSpeedNominalCapacity, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::lowSpeedNominalCapacity() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, true);
}

bool FluidCoolerTwoSpeed_Impl::isLowSpeedNominalCapacityAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double FluidCoolerTwoSpeed_Impl::lowSpeedNominalCapacitySizingFactor() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FluidCoolerTwoSpeed_Impl::designEnteringWaterTemperature() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double FluidCoolerTwoSpeed_Impl::designEnteringAirTemperature() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

double FluidCoolerTwoSpeed_Impl::designEnteringAirWetbulbTemperature() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::designWaterFlowRate() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, true);
}

bool FluidCoolerTwoSpeed_Impl::isDesignWaterFlowRateAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::highFanSpeedAirFlowRate() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, true);
}

bool FluidCoolerTwoSpeed_Impl::isHighFanSpeedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::highFanSpeedFanPower() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, true);
}

bool FluidCoolerTwoSpeed_Impl::isHighFanSpeedFanPowerAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::lowFanSpeedAirFlowRate() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, true);
}

bool FluidCoolerTwoSpeed_Impl::isLowFanSpeedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double FluidCoolerTwoSpeed_Impl::lowFanSpeedAirFlowRateSizingFactor() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::lowFanSpeedFanPower() const {
  return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, true);
}

bool FluidCoolerTwoSpeed_Impl::isLowFanSpeedFanPowerAutosized() const {
  if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

double FluidCoolerTwoSpeed_Impl::lowFanSpeedFanPowerSizingFactor() const {
  const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool FluidCoolerTwoSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
  return setString(openstudio::FluidCooler_TwoSpeedFields::PerformanceInputMethod, performanceInputMethod);
}

bool FluidCoolerTwoSpeed_Impl::setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue) {
  bool result = false;
  if (highFanSpeedUfactorTimesAreaValue) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, *highFanSpeedUfactorTimesAreaValue);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedUfactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue) {
  bool result = false;
  if (lowFanSpeedUfactorTimesAreaValue) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, *lowFanSpeedUfactorTimesAreaValue);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedUfactorTimesAreaValue() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
  const bool result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor,
                                lowFanSpeedUFactorTimesAreaSizingFactor);
  OS_ASSERT(result);
  return result;
}

bool FluidCoolerTwoSpeed_Impl::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
  return setDouble(openstudio::FluidCooler_TwoSpeedFields::HighSpeedNominalCapacity, highSpeedNominalCapacity);
}

bool FluidCoolerTwoSpeed_Impl::setLowSpeedNominalCapacity(boost::optional<double> lowSpeedNominalCapacity) {
  bool result = false;
  if (lowSpeedNominalCapacity) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, *lowSpeedNominalCapacity);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeLowSpeedNominalCapacity() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor) {
  const bool result =
    setDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, lowSpeedNominalCapacitySizingFactor);
  OS_ASSERT(result);
  return result;
}

bool FluidCoolerTwoSpeed_Impl::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
  return setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, designEnteringWaterTemperature);
}

bool FluidCoolerTwoSpeed_Impl::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
  return setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, designEnteringAirTemperature);
}

bool FluidCoolerTwoSpeed_Impl::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
  return setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, designEnteringAirWetbulbTemperature);
}

bool FluidCoolerTwoSpeed_Impl::setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate) {
  bool result = false;
  if (designWaterFlowRate) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, *designWaterFlowRate);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeDesignWaterFlowRate() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setHighFanSpeedAirFlowRate(boost::optional<double> highFanSpeedAirFlowRate) {
  bool result = false;
  if (highFanSpeedAirFlowRate) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, *highFanSpeedAirFlowRate);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedAirFlowRate() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setHighFanSpeedFanPower(boost::optional<double> highFanSpeedFanPower) {
  bool result = false;
  if (highFanSpeedFanPower) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, *highFanSpeedFanPower);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedFanPower() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedAirFlowRate(boost::optional<double> lowFanSpeedAirFlowRate) {
  bool result = false;
  if (lowFanSpeedAirFlowRate) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, *lowFanSpeedAirFlowRate);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedAirFlowRate() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
  const bool result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, lowFanSpeedAirFlowRateSizingFactor);
  OS_ASSERT(result);
  return result;
}

bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedFanPower(boost::optional<double> lowFanSpeedFanPower) {
  bool result = false;
  if (lowFanSpeedFanPower) {
    result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, *lowFanSpeedFanPower);
  }
  return result;
}

void FluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedFanPower() {
  OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, "Autosize"));
}

bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
  const bool result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, lowFanSpeedFanPowerSizingFactor);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedUfactorTimesAreaValue() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedUfactorTimesAreaValue() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowSpeedNominalCapacity() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedDesignWaterFlowRate() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedAirFlowRate() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedFanPower() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedAirFlowRate() const {
  return boost::none;
}

boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedFanPower() const {
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
