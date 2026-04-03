/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(const Model& model)
  : StraightComponent(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), model) {
  ScheduleConstant alwaysOn(model);
  OS_ASSERT(alwaysOn.setValue(1.0));
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  autosizeMaximumAirFlowRate();
  autosizeMaximumHotWaterorSteamFlowRate();
  OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
  OS_ASSERT(setConvergenceTolerance(0.001));
  OS_ASSERT(setMaximumReheatAirTemperature(35.0));
}

AirTerminalSingleDuctConstantVolumeReheat::AirTerminalSingleDuctConstantVolumeReheat(
  std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctConstantVolumeReheat::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat;
}

Schedule AirTerminalSingleDuctConstantVolumeReheat::availabilitySchedule() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->availabilitySchedule();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setAvailabilitySchedule(schedule);
}

HVACComponent AirTerminalSingleDuctConstantVolumeReheat::reheatCoil() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->reheatCoil();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setReheatCoil(const HVACComponent& coil) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setReheatCoil(coil);
}

void AirTerminalSingleDuctConstantVolumeReheat::resetReheatCoil() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetReheatCoil();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumAirFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumAirFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
}

void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumAirFlowRate();
}

void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat::maximumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
}

void AirTerminalSingleDuctConstantVolumeReheat::autosizeMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctConstantVolumeReheat::minimumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->minimumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeReheat::isMinimumHotWaterorSteamFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMinimumHotWaterorSteamFlowRateDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctConstantVolumeReheat::resetMinimumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMinimumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctConstantVolumeReheat::convergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->convergenceTolerance();
}

bool AirTerminalSingleDuctConstantVolumeReheat::isConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isConvergenceToleranceDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setConvergenceTolerance(double convergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
}

void AirTerminalSingleDuctConstantVolumeReheat::resetConvergenceTolerance() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetConvergenceTolerance();
}

double AirTerminalSingleDuctConstantVolumeReheat::maximumReheatAirTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->maximumReheatAirTemperature();
}

bool AirTerminalSingleDuctConstantVolumeReheat::isMaximumReheatAirTemperatureDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->isMaximumReheatAirTemperatureDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeReheat::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->setMaximumReheatAirTemperature(maximumReheatAirTemperature);
}

void AirTerminalSingleDuctConstantVolumeReheat::resetMaximumReheatAirTemperature() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeReheat_Impl>()->resetMaximumReheatAirTemperature();
}

unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName;
}

unsigned detail::AirTerminalSingleDuctConstantVolumeReheat_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

Schedule AirTerminalSingleDuctConstantVolumeReheat_Impl::availabilitySchedule() const {
  auto schedule =
    getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
  OS_ASSERT(schedule);
  return *schedule;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName,
                                       "AirTerminalSingleDuctConstantVolumeReheat", "Availability", schedule);
}

HVACComponent AirTerminalSingleDuctConstantVolumeReheat_Impl::reheatCoil() const {
  auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
  OS_ASSERT(coil);
  return *coil;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setReheatCoil(const HVACComponent& coil) {
  if (coil.model() != model()) {
    return false;
  }
  return setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, coil.handle(), false);
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetReheatCoil() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName, ""));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, ""));
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumHotWaterorSteamFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate,
                   maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeReheat_Impl::minimumHotWaterorSteamFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMinimumHotWaterorSteamFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate);
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate,
                   minimumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMinimumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate, ""));
}

double AirTerminalSingleDuctConstantVolumeReheat_Impl::convergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance);
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, convergenceTolerance);
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetConvergenceTolerance() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance, ""));
}

double AirTerminalSingleDuctConstantVolumeReheat_Impl::maximumReheatAirTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::isMaximumReheatAirTemperatureDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature);
}

bool AirTerminalSingleDuctConstantVolumeReheat_Impl::setMaximumReheatAirTemperature(double maximumReheatAirTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, maximumReheatAirTemperature);
}

void AirTerminalSingleDuctConstantVolumeReheat_Impl::resetMaximumReheatAirTemperature() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
