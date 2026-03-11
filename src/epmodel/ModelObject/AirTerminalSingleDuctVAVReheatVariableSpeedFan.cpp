/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirTerminalSingleDuctVAVReheatVariableSpeedFan.hpp"
#include "AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctVAVReheatVariableSpeedFan::AirTerminalSingleDuctVAVReheatVariableSpeedFan(const Model& model)
  : ModelObject(AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType(), model) {
  autosizeMaximumCoolingAirFlowRate();
  autosizeMaximumHeatingAirFlowRate();
  OS_ASSERT(setZoneMinimumAirFlowFraction(0.3));
  autosizeMaximumHotWaterorSteamFlowRate();
  OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
  OS_ASSERT(setHeatingConvergenceTolerance(0.001));
}

AirTerminalSingleDuctVAVReheatVariableSpeedFan::AirTerminalSingleDuctVAVReheatVariableSpeedFan(
  std::shared_ptr<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctVAVReheatVariableSpeedFan::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFan;
}

boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan::maximumCoolingAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->maximumCoolingAirFlowRate();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMaximumCoolingAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMaximumCoolingAirFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMaximumCoolingAirFlowRate(maximumCoolingAirFlowRate);
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan::autosizeMaximumCoolingAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->autosizeMaximumCoolingAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan::maximumHeatingAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->maximumHeatingAirFlowRate();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMaximumHeatingAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMaximumHeatingAirFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMaximumHeatingAirFlowRate(maximumHeatingAirFlowRate);
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan::autosizeMaximumHeatingAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->autosizeMaximumHeatingAirFlowRate();
}

double AirTerminalSingleDuctVAVReheatVariableSpeedFan::zoneMinimumAirFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->zoneMinimumAirFlowFraction();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
}

boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan::maximumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->maximumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMaximumHotWaterorSteamFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan::autosizeMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctVAVReheatVariableSpeedFan::minimumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->minimumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isMinimumHotWaterorSteamFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan::resetMinimumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->resetMinimumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctVAVReheatVariableSpeedFan::heatingConvergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->heatingConvergenceTolerance();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::isHeatingConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->isHeatingConvergenceToleranceDefaulted();
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan::resetHeatingConvergenceTolerance() {
  getImpl<detail::AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl>()->resetHeatingConvergenceTolerance();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::maximumCoolingAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, true);
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMaximumCoolingAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMaximumCoolingAirFlowRate(double maximumCoolingAirFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, maximumCoolingAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::autosizeMaximumCoolingAirFlowRate() {
  const bool result =
    setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumCoolingAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::maximumHeatingAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, true);
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMaximumHeatingAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMaximumHeatingAirFlowRate(double maximumHeatingAirFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, maximumHeatingAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::autosizeMaximumHeatingAirFlowRate() {
  const bool result =
    setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHeatingAirFlowRate, "autosize");
  OS_ASSERT(result);
}

double AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::zoneMinimumAirFlowFraction() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::ZoneMinimumAirFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::ZoneMinimumAirFlowFraction,
                                zoneMinimumAirFlowFraction);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::maximumHotWaterorSteamFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, true);
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate,
                                maximumHotWaterorSteamFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
  const bool result =
    setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MaximumHotWaterorSteamFlowRate, "autosize");
  OS_ASSERT(result);
}

double AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::minimumHotWaterorSteamFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate);
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate,
                                minimumHotWaterorSteamFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::resetMinimumHotWaterorSteamFlowRate() {
  const bool result =
    setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::MinimumHotWaterorSteamFlowRate, "");
  OS_ASSERT(result);
}

double AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::heatingConvergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::isHeatingConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance);
}

bool AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctVAVReheatVariableSpeedFan_Impl::resetHeatingConvergenceTolerance() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_Reheat_VariableSpeedFanFields::HeatingConvergenceTolerance, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
