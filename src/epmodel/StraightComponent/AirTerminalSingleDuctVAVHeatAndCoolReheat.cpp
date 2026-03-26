/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(const Model& model)
  : StraightComponent(AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType(), model) {}

AirTerminalSingleDuctVAVHeatAndCoolReheat::AirTerminalSingleDuctVAVHeatAndCoolReheat(
  std::shared_ptr<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctVAVHeatAndCoolReheat::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_VAV_HeatAndCool_Reheat;
}

boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumAirFlowRate();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::isMaximumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->isMaximumAirFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
}

void AirTerminalSingleDuctVAVHeatAndCoolReheat::autosizeMaximumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->autosizeMaximumAirFlowRate();
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat::zoneMinimumAirFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->zoneMinimumAirFlowFraction();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
}

boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctVAVHeatAndCoolReheat::autosizeMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat::minimumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->minimumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat::convergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->convergenceTolerance();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setConvergenceTolerance(double convergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat::maximumReheatAirTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->maximumReheatAirTemperature();
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return getImpl<detail::AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, true);
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isMaximumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
}

void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::autosizeMaximumAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumAirFlowRate, "autosize"));
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::zoneMinimumAirFlowFraction() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ZoneMinimumAirFlowFraction, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
}

boost::optional<double> AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumHotWaterorSteamFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate,
                   maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::minimumHotWaterorSteamFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MinimumHotWaterorSteamFlowRate,
                   minimumHotWaterorSteamFlowRate);
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::convergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::ConvergenceTolerance, convergenceTolerance);
}

double AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::maximumReheatAirTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumReheatAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
}

unsigned AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AirInletNodeName;
}

unsigned AirTerminalSingleDuctVAVHeatAndCoolReheat_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_VAV_HeatAndCool_ReheatFields::AirOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
