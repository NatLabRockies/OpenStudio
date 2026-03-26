/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(const Model& model)
  : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), model) {
  autosizeMaximumTotalAirFlowRate();
  autosizeMaximumHotWaterFlowRate();
  autosizeMaximumColdWaterFlowRate();
  OS_ASSERT(setMinimumColdWaterFlowRate(0.0));
  OS_ASSERT(setCoolingConvergenceTolerance(0.001));
}

AirTerminalSingleDuctConstantVolumeFourPipeInduction::AirTerminalSingleDuctConstantVolumeFourPipeInduction(
  std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction;
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumTotalAirFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumTotalAirFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumTotalAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumTotalAirFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumTotalAirFlowRate(maximumTotalAirFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumTotalAirFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumTotalAirFlowRate();
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction::inductionRatio() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->inductionRatio();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isInductionRatioDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isInductionRatioDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setInductionRatio(double inductionRatio) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setInductionRatio(inductionRatio);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetInductionRatio() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetInductionRatio();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumHotWaterFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumHotWaterFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumHotWaterFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumHotWaterFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumHotWaterFlowRate(maximumHotWaterFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMaximumHotWaterFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMaximumHotWaterFlowRate();
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumHotWaterFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumHotWaterFlowRate();
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction::minimumHotWaterFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->minimumHotWaterFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMinimumHotWaterFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMinimumHotWaterFlowRateDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMinimumHotWaterFlowRate(minimumHotWaterFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMinimumHotWaterFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMinimumHotWaterFlowRate();
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction::heatingConvergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->heatingConvergenceTolerance();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isHeatingConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isHeatingConvergenceToleranceDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetHeatingConvergenceTolerance() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetHeatingConvergenceTolerance();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction::maximumColdWaterFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->maximumColdWaterFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMaximumColdWaterFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMaximumColdWaterFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMaximumColdWaterFlowRate(maximumColdWaterFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMaximumColdWaterFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMaximumColdWaterFlowRate();
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::autosizeMaximumColdWaterFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->autosizeMaximumColdWaterFlowRate();
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction::minimumColdWaterFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->minimumColdWaterFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isMinimumColdWaterFlowRateDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isMinimumColdWaterFlowRateDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setMinimumColdWaterFlowRate(minimumColdWaterFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetMinimumColdWaterFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetMinimumColdWaterFlowRate();
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction::coolingConvergenceTolerance() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->coolingConvergenceTolerance();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::isCoolingConvergenceToleranceDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->isCoolingConvergenceToleranceDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction::resetCoolingConvergenceTolerance() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>()->resetCoolingConvergenceTolerance();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumTotalAirFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumTotalAirFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumTotalAirFlowRate(double maximumTotalAirFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, maximumTotalAirFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumTotalAirFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumTotalAirFlowRate, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inductionRatio() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isInductionRatioDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setInductionRatio(double inductionRatio) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, inductionRatio);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetInductionRatio() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::InductionRatio, ""));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumHotWaterFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumHotWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, maximumHotWaterFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMaximumHotWaterFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, ""));
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumHotWaterFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumHotWaterFlowRate, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::minimumHotWaterFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMinimumHotWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, minimumHotWaterFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMinimumHotWaterFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumHotWaterFlowRate, ""));
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::heatingConvergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isHeatingConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance,
                   heatingConvergenceTolerance);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetHeatingConvergenceTolerance() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingConvergenceTolerance, ""));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::maximumColdWaterFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMaximumColdWaterFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMaximumColdWaterFlowRate(double maximumColdWaterFlowRate) {
  const bool result =
    setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, maximumColdWaterFlowRate);
  OS_ASSERT(result);
  return result;
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMaximumColdWaterFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, ""));
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::autosizeMaximumColdWaterFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MaximumColdWaterFlowRate, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::minimumColdWaterFlowRate() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isMinimumColdWaterFlowRateDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setMinimumColdWaterFlowRate(double minimumColdWaterFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, minimumColdWaterFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetMinimumColdWaterFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::MinimumColdWaterFlowRate, ""));
}

double AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::coolingConvergenceTolerance() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::isCoolingConvergenceToleranceDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance,
                   coolingConvergenceTolerance);
}

void AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::resetCoolingConvergenceTolerance() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingConvergenceTolerance, ""));
}

unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::SupplyAirInletNodeName;
}

unsigned AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::AirOutletNodeName;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
