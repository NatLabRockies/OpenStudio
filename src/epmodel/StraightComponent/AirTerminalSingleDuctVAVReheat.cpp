/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctVAVReheat::AirTerminalSingleDuctVAVReheat(const Model& model)
  : StraightComponent(AirTerminalSingleDuctVAVReheat::iddObjectType(), model) {
  ScheduleConstant alwaysOn(model);
  OS_ASSERT(alwaysOn.setValue(1.0));
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  autosizeMaximumAirFlowRate();
  OS_ASSERT(setZoneMinimumAirFlowInputMethod("Constant"));
  OS_ASSERT(setConstantMinimumAirFlowFraction(0.3));
  OS_ASSERT(setFixedMinimumAirFlowRate(0.0));
  OS_ASSERT(setMaximumFlowPerZoneFloorAreaDuringReheat(0.0));
  OS_ASSERT(setMinimumHotWaterOrStreamFlowRate(0.0));
  OS_ASSERT(setConvergenceTolerance(0.001));
  OS_ASSERT(setDamperHeatingAction("Normal"));
  autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
  autosizeMaximumFlowFractionDuringReheat();
  OS_ASSERT(setMaximumReheatAirTemperature(35.0));
  autosizeMaximumHotWaterOrSteamFlowRate();
}

AirTerminalSingleDuctVAVReheat::AirTerminalSingleDuctVAVReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVReheat_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctVAVReheat::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_VAV_Reheat;
}

std::vector<std::string> AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowInputMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ZoneMinimumAirFlowInputMethod);
}

std::vector<std::string> AirTerminalSingleDuctVAVReheat::damperHeatingActionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperHeatingAction);
}

HVACComponent AirTerminalSingleDuctVAVReheat::reheatCoil() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->reheatCoil();
}

bool AirTerminalSingleDuctVAVReheat::setReheatCoil(HVACComponent& coil) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setReheatCoil(coil);
}

Schedule AirTerminalSingleDuctVAVReheat::availabilitySchedule() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->availabilitySchedule();
}

bool AirTerminalSingleDuctVAVReheat::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setAvailabilitySchedule(schedule);
}

boost::optional<Schedule> AirTerminalSingleDuctVAVReheat::minimumAirFlowFractionSchedule() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->minimumAirFlowFractionSchedule();
}

bool AirTerminalSingleDuctVAVReheat::setMinimumAirFlowFractionSchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMinimumAirFlowFractionSchedule(schedule);
}

void AirTerminalSingleDuctVAVReheat::resetMinimumAirFlowFractionSchedule() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMinimumAirFlowFractionSchedule();
}

boost::optional<Schedule> AirTerminalSingleDuctVAVReheat::minimumAirFlowTurndownSchedule() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->minimumAirFlowTurndownSchedule();
}

bool AirTerminalSingleDuctVAVReheat::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMinimumAirFlowTurndownSchedule(schedule);
}

void AirTerminalSingleDuctVAVReheat::resetMinimumAirFlowTurndownSchedule() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMinimumAirFlowTurndownSchedule();
}

boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumAirFlowRate();
}

bool AirTerminalSingleDuctVAVReheat::isMaximumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumAirFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
}

void AirTerminalSingleDuctVAVReheat::autosizeMaximumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumAirFlowRate();
}

std::string AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowInputMethod() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->zoneMinimumAirFlowInputMethod();
}

std::string AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowMethod() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->zoneMinimumAirFlowInputMethod();
}

bool AirTerminalSingleDuctVAVReheat::setZoneMinimumAirFlowInputMethod(const std::string& value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setZoneMinimumAirFlowInputMethod(value);
}

bool AirTerminalSingleDuctVAVReheat::setZoneMinimumAirFlowMethod(const std::string& value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setZoneMinimumAirFlowInputMethod(value);
}

boost::optional<double> AirTerminalSingleDuctVAVReheat::constantMinimumAirFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->constantMinimumAirFlowFraction();
}

bool AirTerminalSingleDuctVAVReheat::isConstantMinimumAirFlowFractionAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isConstantMinimumAirFlowFractionAutosized();
}

bool AirTerminalSingleDuctVAVReheat::setConstantMinimumAirFlowFraction(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setConstantMinimumAirFlowFraction(value);
}

void AirTerminalSingleDuctVAVReheat::autosizeConstantMinimumAirFlowFraction() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeConstantMinimumAirFlowFraction();
}

boost::optional<double> AirTerminalSingleDuctVAVReheat::fixedMinimumAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->fixedMinimumAirFlowRate();
}

bool AirTerminalSingleDuctVAVReheat::isFixedMinimumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isFixedMinimumAirFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVReheat::setFixedMinimumAirFlowRate(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setFixedMinimumAirFlowRate(value);
}

void AirTerminalSingleDuctVAVReheat::autosizeFixedMinimumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeFixedMinimumAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumHotWaterOrSteamFlowRate() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumHotWaterOrSteamFlowRate();
}

bool AirTerminalSingleDuctVAVReheat::isMaximumHotWaterOrSteamFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumHotWaterOrSteamFlowRateAutosized();
}

bool AirTerminalSingleDuctVAVReheat::setMaximumHotWaterOrSteamFlowRate(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumHotWaterOrSteamFlowRate(value);
}

void AirTerminalSingleDuctVAVReheat::autosizeMaximumHotWaterOrSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumHotWaterOrSteamFlowRate();
}

double AirTerminalSingleDuctVAVReheat::minimumHotWaterOrSteamFlowRate() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->minimumHotWaterOrSteamFlowRate();
}

bool AirTerminalSingleDuctVAVReheat::setMinimumHotWaterOrStreamFlowRate(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMinimumHotWaterOrStreamFlowRate(value);
}

double AirTerminalSingleDuctVAVReheat::convergenceTolerance() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->convergenceTolerance();
}

bool AirTerminalSingleDuctVAVReheat::setConvergenceTolerance(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setConvergenceTolerance(value);
}

std::string AirTerminalSingleDuctVAVReheat::damperHeatingAction() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->damperHeatingAction();
}

bool AirTerminalSingleDuctVAVReheat::setDamperHeatingAction(const std::string& value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setDamperHeatingAction(value);
}

boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumFlowPerZoneFloorAreaDuringReheat() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumFlowPerZoneFloorAreaDuringReheat();
}

bool AirTerminalSingleDuctVAVReheat::isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumFlowPerZoneFloorAreaDuringReheatAutosized();
}

bool AirTerminalSingleDuctVAVReheat::setMaximumFlowPerZoneFloorAreaDuringReheat(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumFlowPerZoneFloorAreaDuringReheat(value);
}

void AirTerminalSingleDuctVAVReheat::autosizeMaximumFlowPerZoneFloorAreaDuringReheat() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
}

void AirTerminalSingleDuctVAVReheat::resetMaximumFlowPerZoneFloorAreaDuringReheat() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMaximumFlowPerZoneFloorAreaDuringReheat();
}

boost::optional<double> AirTerminalSingleDuctVAVReheat::maximumFlowFractionDuringReheat() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumFlowFractionDuringReheat();
}

bool AirTerminalSingleDuctVAVReheat::isMaximumFlowFractionDuringReheatAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->isMaximumFlowFractionDuringReheatAutosized();
}

bool AirTerminalSingleDuctVAVReheat::setMaximumFlowFractionDuringReheat(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumFlowFractionDuringReheat(value);
}

void AirTerminalSingleDuctVAVReheat::autosizeMaximumFlowFractionDuringReheat() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->autosizeMaximumFlowFractionDuringReheat();
}

void AirTerminalSingleDuctVAVReheat::resetMaximumFlowFractionDuringReheat() {
  getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->resetMaximumFlowFractionDuringReheat();
}

double AirTerminalSingleDuctVAVReheat::maximumReheatAirTemperature() {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->maximumReheatAirTemperature();
}

bool AirTerminalSingleDuctVAVReheat::setMaximumReheatAirTemperature(double value) {
  return getImpl<detail::AirTerminalSingleDuctVAVReheat_Impl>()->setMaximumReheatAirTemperature(value);
}

unsigned detail::AirTerminalSingleDuctVAVReheat_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AirInletNodeName;
}

unsigned detail::AirTerminalSingleDuctVAVReheat_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AirOutletNodeName;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

HVACComponent AirTerminalSingleDuctVAVReheat_Impl::reheatCoil() const {
  auto coil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName);
  OS_ASSERT(coil);
  return *coil;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setReheatCoil(HVACComponent& coil) {
  if (coil.model() != model()) {
    return false;
  }
  return setPointer(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilName, coil.handle(), false);
}

Schedule AirTerminalSingleDuctVAVReheat_Impl::availabilitySchedule() const {
  auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AvailabilityScheduleName);
  OS_ASSERT(schedule);
  return *schedule;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::AvailabilityScheduleName,
                                       "AirTerminalSingleDuctVAVReheat", "Availability", schedule);
}

boost::optional<Schedule> AirTerminalSingleDuctVAVReheat_Impl::minimumAirFlowFractionSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowFractionScheduleName);
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMinimumAirFlowFractionSchedule(Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowFractionScheduleName,
                                       "AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Fraction", schedule);
}

void AirTerminalSingleDuctVAVReheat_Impl::resetMinimumAirFlowFractionSchedule() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowFractionScheduleName, ""));
}

boost::optional<Schedule> AirTerminalSingleDuctVAVReheat_Impl::minimumAirFlowTurndownSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowTurndownScheduleName);
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMinimumAirFlowTurndownSchedule(Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowTurndownScheduleName,
                                       "AirTerminalSingleDuctVAVReheat", "Minimum Air Flow Turndown", schedule);
}

void AirTerminalSingleDuctVAVReheat_Impl::resetMinimumAirFlowTurndownSchedule() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumAirFlowTurndownScheduleName, ""));
}

boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, true);
}

bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
}

void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumAirFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumAirFlowRate, "autosize");
  OS_ASSERT(result);
}

std::string AirTerminalSingleDuctVAVReheat_Impl::zoneMinimumAirFlowInputMethod() {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ZoneMinimumAirFlowInputMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setZoneMinimumAirFlowInputMethod(const std::string& value) {
  return setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ZoneMinimumAirFlowInputMethod, value);
}

std::vector<std::string> AirTerminalSingleDuctVAVReheat_Impl::zoneMinimumAirFlowInputMethodValues() const {
  return AirTerminalSingleDuctVAVReheat::zoneMinimumAirFlowInputMethodValues();
}

boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::constantMinimumAirFlowFraction() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, true);
}

bool AirTerminalSingleDuctVAVReheat_Impl::isConstantMinimumAirFlowFractionAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, true)) {
    return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setConstantMinimumAirFlowFraction(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, value);
}

void AirTerminalSingleDuctVAVReheat_Impl::autosizeConstantMinimumAirFlowFraction() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConstantMinimumAirFlowFraction, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::fixedMinimumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, true);
}

bool AirTerminalSingleDuctVAVReheat_Impl::isFixedMinimumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setFixedMinimumAirFlowRate(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, value);
}

void AirTerminalSingleDuctVAVReheat_Impl::autosizeFixedMinimumAirFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::FixedMinimumAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumHotWaterOrSteamFlowRate() {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
}

bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumHotWaterOrSteamFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumHotWaterOrSteamFlowRate(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, value);
}

void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumHotWaterOrSteamFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize");
  OS_ASSERT(result);
}

double AirTerminalSingleDuctVAVReheat_Impl::minimumHotWaterOrSteamFlowRate() {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMinimumHotWaterOrStreamFlowRate(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MinimumHotWaterorSteamFlowRate, value);
}

double AirTerminalSingleDuctVAVReheat_Impl::convergenceTolerance() {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setConvergenceTolerance(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ConvergenceTolerance, value);
}

std::string AirTerminalSingleDuctVAVReheat_Impl::damperHeatingAction() {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperHeatingAction, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setDamperHeatingAction(const std::string& value) {
  return setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperHeatingAction, value);
}

std::vector<std::string> AirTerminalSingleDuctVAVReheat_Impl::damperHeatingActionValues() const {
  return AirTerminalSingleDuctVAVReheat::damperHeatingActionValues();
}

boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumFlowPerZoneFloorAreaDuringReheat() {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, true);
}

bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumFlowPerZoneFloorAreaDuringReheatAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, true)) {
    return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumFlowPerZoneFloorAreaDuringReheat(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, value);
}

void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumFlowPerZoneFloorAreaDuringReheat() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, "autocalculate");
  OS_ASSERT(result);
}

void AirTerminalSingleDuctVAVReheat_Impl::resetMaximumFlowPerZoneFloorAreaDuringReheat() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowperZoneFloorAreaDuringReheat, "");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctVAVReheat_Impl::maximumFlowFractionDuringReheat() {
  return getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, true);
}

bool AirTerminalSingleDuctVAVReheat_Impl::isMaximumFlowFractionDuringReheatAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, true)) {
    return openstudio::istringEqual(*value, "autosize") || openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumFlowFractionDuringReheat(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, value);
}

void AirTerminalSingleDuctVAVReheat_Impl::autosizeMaximumFlowFractionDuringReheat() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, "autocalculate");
  OS_ASSERT(result);
}

void AirTerminalSingleDuctVAVReheat_Impl::resetMaximumFlowFractionDuringReheat() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumFlowFractionDuringReheat, "");
  OS_ASSERT(result);
}

double AirTerminalSingleDuctVAVReheat_Impl::maximumReheatAirTemperature() {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumReheatAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctVAVReheat_Impl::setMaximumReheatAirTemperature(double value) {
  return setDouble(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::MaximumReheatAirTemperature, value);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
