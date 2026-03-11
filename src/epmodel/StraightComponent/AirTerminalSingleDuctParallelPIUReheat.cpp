/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctParallelPIUReheat::AirTerminalSingleDuctParallelPIUReheat(const Model& model)
  : ModelObject(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), model) {
  autosizeMaximumPrimaryAirFlowRate();
  autosizeMaximumSecondaryAirFlowRate();
  autosizeMinimumPrimaryAirFlowFraction();
  autosizeFanOnFlowFraction();
  autosizeMaximumHotWaterorSteamFlowRate();
  OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
  OS_ASSERT(setConvergenceTolerance(0.001));
  OS_ASSERT(setFanControlType("ConstantSpeed"));
  OS_ASSERT(setMinimumFanTurnDownRatio(0.3));
  OS_ASSERT(setHeatingControlType("Staged"));
  OS_ASSERT(setDesignHeatingDischargeAirTemperature(32.1));
  OS_ASSERT(setHighLimitHeatingDischargeAirTemperature(37.7));
}

AirTerminalSingleDuctParallelPIUReheat::AirTerminalSingleDuctParallelPIUReheat(
  std::shared_ptr<detail::AirTerminalSingleDuctParallelPIUReheat_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctParallelPIUReheat::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_ParallelPIU_Reheat;
}

std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat::fanControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType);
}

std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat::heatingControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HeatingControlType);
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::maximumPrimaryAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->maximumPrimaryAirFlowRate();
}

bool AirTerminalSingleDuctParallelPIUReheat::isMaximumPrimaryAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMaximumPrimaryAirFlowRateAutosized();
}

bool AirTerminalSingleDuctParallelPIUReheat::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMaximumPrimaryAirFlowRate(maximumPrimaryAirFlowRate);
}

void AirTerminalSingleDuctParallelPIUReheat::autosizeMaximumPrimaryAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMaximumPrimaryAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::maximumSecondaryAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->maximumSecondaryAirFlowRate();
}

bool AirTerminalSingleDuctParallelPIUReheat::isMaximumSecondaryAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMaximumSecondaryAirFlowRateAutosized();
}

bool AirTerminalSingleDuctParallelPIUReheat::setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMaximumSecondaryAirFlowRate(maximumSecondaryAirFlowRate);
}

void AirTerminalSingleDuctParallelPIUReheat::autosizeMaximumSecondaryAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMaximumSecondaryAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::minimumPrimaryAirFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->minimumPrimaryAirFlowFraction();
}

bool AirTerminalSingleDuctParallelPIUReheat::isMinimumPrimaryAirFlowFractionAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMinimumPrimaryAirFlowFractionAutosized();
}

bool AirTerminalSingleDuctParallelPIUReheat::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMinimumPrimaryAirFlowFraction(minimumPrimaryAirFlowFraction);
}

void AirTerminalSingleDuctParallelPIUReheat::autosizeMinimumPrimaryAirFlowFraction() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMinimumPrimaryAirFlowFraction();
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::fanOnFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->fanOnFlowFraction();
}

bool AirTerminalSingleDuctParallelPIUReheat::isFanOnFlowFractionAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isFanOnFlowFractionAutosized();
}

bool AirTerminalSingleDuctParallelPIUReheat::setFanOnFlowFraction(double fanOnFlowFraction) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setFanOnFlowFraction(fanOnFlowFraction);
}

void AirTerminalSingleDuctParallelPIUReheat::autosizeFanOnFlowFraction() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeFanOnFlowFraction();
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat::maximumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->maximumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctParallelPIUReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
}

bool AirTerminalSingleDuctParallelPIUReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctParallelPIUReheat::resetMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
}

void AirTerminalSingleDuctParallelPIUReheat::autosizeMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctParallelPIUReheat::minimumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->minimumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctParallelPIUReheat::isMinimumHotWaterorSteamFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
}

bool AirTerminalSingleDuctParallelPIUReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctParallelPIUReheat::resetMinimumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->resetMinimumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctParallelPIUReheat::convergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->convergenceTolerance();
}

bool AirTerminalSingleDuctParallelPIUReheat::isConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->isConvergenceToleranceDefaulted();
}

bool AirTerminalSingleDuctParallelPIUReheat::setConvergenceTolerance(double convergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
}

void AirTerminalSingleDuctParallelPIUReheat::resetConvergenceTolerance() {
  getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->resetConvergenceTolerance();
}

std::string AirTerminalSingleDuctParallelPIUReheat::fanControlType() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->fanControlType();
}

bool AirTerminalSingleDuctParallelPIUReheat::setFanControlType(const std::string& fanControlType) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setFanControlType(fanControlType);
}

double AirTerminalSingleDuctParallelPIUReheat::minimumFanTurnDownRatio() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->minimumFanTurnDownRatio();
}

bool AirTerminalSingleDuctParallelPIUReheat::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setMinimumFanTurnDownRatio(minimumFanTurnDownRatio);
}

std::string AirTerminalSingleDuctParallelPIUReheat::heatingControlType() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->heatingControlType();
}

bool AirTerminalSingleDuctParallelPIUReheat::setHeatingControlType(const std::string& heatingControlType) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setHeatingControlType(heatingControlType);
}

double AirTerminalSingleDuctParallelPIUReheat::designHeatingDischargeAirTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->designHeatingDischargeAirTemperature();
}

bool AirTerminalSingleDuctParallelPIUReheat::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setDesignHeatingDischargeAirTemperature(designHeatingDischargeAirTemperature);
}

double AirTerminalSingleDuctParallelPIUReheat::highLimitHeatingDischargeAirTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->highLimitHeatingDischargeAirTemperature();
}

bool AirTerminalSingleDuctParallelPIUReheat::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
  return getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>()->setHighLimitHeatingDischargeAirTemperature(
    highLimitHeatingDischargeAirTemperature);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::maximumPrimaryAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, true);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMaximumPrimaryAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
  const bool result = setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, maximumPrimaryAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMaximumPrimaryAirFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumPrimaryAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::maximumSecondaryAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, true);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMaximumSecondaryAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMaximumSecondaryAirFlowRate(double maximumSecondaryAirFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, maximumSecondaryAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMaximumSecondaryAirFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumSecondaryAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::minimumPrimaryAirFlowFraction() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMinimumPrimaryAirFlowFractionAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, minimumPrimaryAirFlowFraction);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMinimumPrimaryAirFlowFraction() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumPrimaryAirFlowFraction, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::fanOnFlowFraction() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, true);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isFanOnFlowFractionAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setFanOnFlowFraction(double fanOnFlowFraction) {
  const bool result = setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, fanOnFlowFraction);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeFanOnFlowFraction() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanOnFlowFraction, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctParallelPIUReheat_Impl::maximumHotWaterorSteamFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, maximumHotWaterorSteamFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
}

double AirTerminalSingleDuctParallelPIUReheat_Impl::minimumHotWaterorSteamFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::resetMinimumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, ""));
}

double AirTerminalSingleDuctParallelPIUReheat_Impl::convergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::isConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance);
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, convergenceTolerance);
}

void AirTerminalSingleDuctParallelPIUReheat_Impl::resetConvergenceTolerance() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::ConvergenceTolerance, ""));
}

std::string AirTerminalSingleDuctParallelPIUReheat_Impl::fanControlType() const {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setFanControlType(const std::string& fanControlType) {
  return setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::FanControlType, fanControlType);
}

double AirTerminalSingleDuctParallelPIUReheat_Impl::minimumFanTurnDownRatio() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumFanTurnDownRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::MinimumFanTurnDownRatio, minimumFanTurnDownRatio);
}

std::string AirTerminalSingleDuctParallelPIUReheat_Impl::heatingControlType() const {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HeatingControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setHeatingControlType(const std::string& heatingControlType) {
  return setString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HeatingControlType, heatingControlType);
}

double AirTerminalSingleDuctParallelPIUReheat_Impl::designHeatingDischargeAirTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::DesignHeatingDischargeAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::DesignHeatingDischargeAirTemperature,
                   designHeatingDischargeAirTemperature);
}

double AirTerminalSingleDuctParallelPIUReheat_Impl::highLimitHeatingDischargeAirTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctParallelPIUReheat_Impl::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature,
                   highLimitHeatingDischargeAirTemperature);
}

std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat_Impl::fanControlTypeValues() const {
  return openstudio::epmodel::AirTerminalSingleDuctParallelPIUReheat::fanControlTypeValues();
}

std::vector<std::string> AirTerminalSingleDuctParallelPIUReheat_Impl::heatingControlTypeValues() const {
  return openstudio::epmodel::AirTerminalSingleDuctParallelPIUReheat::heatingControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
