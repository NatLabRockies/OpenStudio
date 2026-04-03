/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"

#include "HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_SeriesPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctSeriesPIUReheat::AirTerminalSingleDuctSeriesPIUReheat(const Model& model)
  : StraightComponent(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), model) {
  autosizeMaximumAirFlowRate();
  autosizeMaximumPrimaryAirFlowRate();
  autosizeMinimumPrimaryAirFlowFraction();
  autosizeMaximumHotWaterorSteamFlowRate();
  OS_ASSERT(setMinimumHotWaterorSteamFlowRate(0.0));
  OS_ASSERT(setConvergenceTolerance(0.001));
  OS_ASSERT(setFanControlType("ConstantSpeed"));
  OS_ASSERT(setMinimumFanTurnDownRatio(0.3));
  OS_ASSERT(setHeatingControlType("Staged"));
  OS_ASSERT(setDesignHeatingDischargeAirTemperature(32.1));
  OS_ASSERT(setHighLimitHeatingDischargeAirTemperature(37.7));
}

AirTerminalSingleDuctSeriesPIUReheat::AirTerminalSingleDuctSeriesPIUReheat(
  std::shared_ptr<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctSeriesPIUReheat::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_SeriesPIU_Reheat;
}

std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType);
}

std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HeatingControlType);
}

boost::optional<Schedule> AirTerminalSingleDuctSeriesPIUReheat::availabilitySchedule() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->availabilitySchedule();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setAvailabilitySchedule(schedule);
}

void AirTerminalSingleDuctSeriesPIUReheat::resetAvailabilitySchedule() {
  getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->resetAvailabilitySchedule();
}

HVACComponent AirTerminalSingleDuctSeriesPIUReheat::fan() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->fan();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setFan(const HVACComponent& fan) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setFan(fan);
}

HVACComponent AirTerminalSingleDuctSeriesPIUReheat::reheatCoil() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->reheatCoil();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setReheatCoil(const HVACComponent& coil) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setReheatCoil(coil);
}

boost::optional<Node> AirTerminalSingleDuctSeriesPIUReheat::secondaryAirInletNode() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->secondaryAirInletNode();
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::maximumAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->maximumAirFlowRate();
}

bool AirTerminalSingleDuctSeriesPIUReheat::isMaximumAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMaximumAirFlowRateAutosized();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
}

void AirTerminalSingleDuctSeriesPIUReheat::autosizeMaximumAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMaximumAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::maximumPrimaryAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->maximumPrimaryAirFlowRate();
}

bool AirTerminalSingleDuctSeriesPIUReheat::isMaximumPrimaryAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMaximumPrimaryAirFlowRateAutosized();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMaximumPrimaryAirFlowRate(maximumPrimaryAirFlowRate);
}

void AirTerminalSingleDuctSeriesPIUReheat::autosizeMaximumPrimaryAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMaximumPrimaryAirFlowRate();
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::minimumPrimaryAirFlowFraction() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->minimumPrimaryAirFlowFraction();
}

bool AirTerminalSingleDuctSeriesPIUReheat::isMinimumPrimaryAirFlowFractionAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMinimumPrimaryAirFlowFractionAutosized();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMinimumPrimaryAirFlowFraction(minimumPrimaryAirFlowFraction);
}

void AirTerminalSingleDuctSeriesPIUReheat::autosizeMinimumPrimaryAirFlowFraction() {
  getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMinimumPrimaryAirFlowFraction();
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat::maximumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->maximumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctSeriesPIUReheat::isMaximumHotWaterorSteamFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->isMaximumHotWaterorSteamFlowRateAutosized();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMaximumHotWaterorSteamFlowRate(maximumHotWaterorSteamFlowRate);
}

void AirTerminalSingleDuctSeriesPIUReheat::resetMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->resetMaximumHotWaterorSteamFlowRate();
}

void AirTerminalSingleDuctSeriesPIUReheat::autosizeMaximumHotWaterorSteamFlowRate() {
  getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->autosizeMaximumHotWaterorSteamFlowRate();
}

double AirTerminalSingleDuctSeriesPIUReheat::minimumHotWaterorSteamFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->minimumHotWaterorSteamFlowRate();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMinimumHotWaterorSteamFlowRate(minimumHotWaterorSteamFlowRate);
}

double AirTerminalSingleDuctSeriesPIUReheat::convergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->convergenceTolerance();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setConvergenceTolerance(double convergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setConvergenceTolerance(convergenceTolerance);
}

std::string AirTerminalSingleDuctSeriesPIUReheat::fanControlType() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->fanControlType();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setFanControlType(const std::string& fanControlType) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setFanControlType(fanControlType);
}

double AirTerminalSingleDuctSeriesPIUReheat::minimumFanTurnDownRatio() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->minimumFanTurnDownRatio();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setMinimumFanTurnDownRatio(minimumFanTurnDownRatio);
}

std::string AirTerminalSingleDuctSeriesPIUReheat::heatingControlType() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->heatingControlType();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setHeatingControlType(const std::string& heatingControlType) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setHeatingControlType(heatingControlType);
}

double AirTerminalSingleDuctSeriesPIUReheat::designHeatingDischargeAirTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->designHeatingDischargeAirTemperature();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setDesignHeatingDischargeAirTemperature(designHeatingDischargeAirTemperature);
}

double AirTerminalSingleDuctSeriesPIUReheat::highLimitHeatingDischargeAirTemperature() const {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->highLimitHeatingDischargeAirTemperature();
}

bool AirTerminalSingleDuctSeriesPIUReheat::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
  return getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>()->setHighLimitHeatingDischargeAirTemperature(highLimitHeatingDischargeAirTemperature);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<Schedule> AirTerminalSingleDuctSeriesPIUReheat_Impl::availabilitySchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName);
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName,
                                       "AirTerminalSingleDuctSeriesPIUReheat", "Availability", schedule);
}

void AirTerminalSingleDuctSeriesPIUReheat_Impl::resetAvailabilitySchedule() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::AvailabilityScheduleName, ""));
}

HVACComponent AirTerminalSingleDuctSeriesPIUReheat_Impl::fan() const {
  auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName);
  OS_ASSERT(fan);
  return *fan;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setFan(const HVACComponent& fan) {
  if (fan.model() != model()) {
    return false;
  }
  return setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, fan.handle(), false);
}

HVACComponent AirTerminalSingleDuctSeriesPIUReheat_Impl::reheatCoil() const {
  auto coil =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName);
  OS_ASSERT(coil);
  return *coil;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setReheatCoil(const HVACComponent& coil) {
  if (coil.model() != model()) {
    return false;
  }
  return setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilName, coil.handle(), false);
}

boost::optional<Node> AirTerminalSingleDuctSeriesPIUReheat_Impl::secondaryAirInletNode() const {
  return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName);
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::maximumAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, true);
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMaximumAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
  const bool result = setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMaximumAirFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::maximumPrimaryAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, true);
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMaximumPrimaryAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMaximumPrimaryAirFlowRate(double maximumPrimaryAirFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, maximumPrimaryAirFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMaximumPrimaryAirFlowRate() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumPrimaryAirFlowRate, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::minimumPrimaryAirFlowFraction() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true);
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMinimumPrimaryAirFlowFractionAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMinimumPrimaryAirFlowFraction(double minimumPrimaryAirFlowFraction) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, minimumPrimaryAirFlowFraction);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMinimumPrimaryAirFlowFraction() {
  const bool result = setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumPrimaryAirFlowFraction, "autosize");
  OS_ASSERT(result);
}

boost::optional<double> AirTerminalSingleDuctSeriesPIUReheat_Impl::maximumHotWaterorSteamFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true);
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::isMaximumHotWaterorSteamFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMaximumHotWaterorSteamFlowRate(double maximumHotWaterorSteamFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, maximumHotWaterorSteamFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctSeriesPIUReheat_Impl::resetMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, ""));
}

void AirTerminalSingleDuctSeriesPIUReheat_Impl::autosizeMaximumHotWaterorSteamFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MaximumHotWaterorSteamFlowRate, "autosize"));
}

double AirTerminalSingleDuctSeriesPIUReheat_Impl::minimumHotWaterorSteamFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMinimumHotWaterorSteamFlowRate(double minimumHotWaterorSteamFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumHotWaterorSteamFlowRate, minimumHotWaterorSteamFlowRate);
}

double AirTerminalSingleDuctSeriesPIUReheat_Impl::convergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setConvergenceTolerance(double convergenceTolerance) {
  return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ConvergenceTolerance, convergenceTolerance);
}

std::string AirTerminalSingleDuctSeriesPIUReheat_Impl::fanControlType() const {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setFanControlType(const std::string& fanControlType) {
  return setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanControlType, fanControlType);
}

double AirTerminalSingleDuctSeriesPIUReheat_Impl::minimumFanTurnDownRatio() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumFanTurnDownRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setMinimumFanTurnDownRatio(double minimumFanTurnDownRatio) {
  return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::MinimumFanTurnDownRatio, minimumFanTurnDownRatio);
}

std::string AirTerminalSingleDuctSeriesPIUReheat_Impl::heatingControlType() const {
  const auto value = getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HeatingControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setHeatingControlType(const std::string& heatingControlType) {
  return setString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HeatingControlType, heatingControlType);
}

double AirTerminalSingleDuctSeriesPIUReheat_Impl::designHeatingDischargeAirTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::DesignHeatingDischargeAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setDesignHeatingDischargeAirTemperature(double designHeatingDischargeAirTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::DesignHeatingDischargeAirTemperature,
                   designHeatingDischargeAirTemperature);
}

double AirTerminalSingleDuctSeriesPIUReheat_Impl::highLimitHeatingDischargeAirTemperature() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctSeriesPIUReheat_Impl::setHighLimitHeatingDischargeAirTemperature(double highLimitHeatingDischargeAirTemperature) {
  return setDouble(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::HighLimitHeatingDischargeAirTemperature,
                   highLimitHeatingDischargeAirTemperature);
}

std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat_Impl::fanControlTypeValues() const {
  return openstudio::epmodel::AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues();
}

std::vector<std::string> AirTerminalSingleDuctSeriesPIUReheat_Impl::heatingControlTypeValues() const {
  return openstudio::epmodel::AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues();
}

unsigned AirTerminalSingleDuctSeriesPIUReheat_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SupplyAirInletNodeName;
}

unsigned AirTerminalSingleDuctSeriesPIUReheat_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
