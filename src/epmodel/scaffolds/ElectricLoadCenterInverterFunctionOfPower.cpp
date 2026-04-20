/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricLoadCenterInverterFunctionOfPower.hpp"
#include "ElectricLoadCenterInverterFunctionOfPower_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Inverter_FunctionOfPower_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterInverterFunctionOfPower::ElectricLoadCenterInverterFunctionOfPower(const Model& model)
  : ModelObject(ElectricLoadCenterInverterFunctionOfPower::iddObjectType(), model) {}

ElectricLoadCenterInverterFunctionOfPower::ElectricLoadCenterInverterFunctionOfPower(
  std::shared_ptr<detail::ElectricLoadCenterInverterFunctionOfPower_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterInverterFunctionOfPower::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Inverter_FunctionOfPower;
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::radiativeFraction() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->radiativeFraction();
}

bool ElectricLoadCenterInverterFunctionOfPower::setRadiativeFraction(double radiativeFraction) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setRadiativeFraction(radiativeFraction);
}

void ElectricLoadCenterInverterFunctionOfPower::resetRadiativeFraction() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetRadiativeFraction();
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::ratedMaximumContinuousInputPower() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->ratedMaximumContinuousInputPower();
}

bool ElectricLoadCenterInverterFunctionOfPower::setRatedMaximumContinuousInputPower(double ratedMaximumContinuousInputPower) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setRatedMaximumContinuousInputPower(
    ratedMaximumContinuousInputPower);
}

void ElectricLoadCenterInverterFunctionOfPower::resetRatedMaximumContinuousInputPower() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetRatedMaximumContinuousInputPower();
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::minimumEfficiency() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->minimumEfficiency();
}

bool ElectricLoadCenterInverterFunctionOfPower::setMinimumEfficiency(double minimumEfficiency) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setMinimumEfficiency(minimumEfficiency);
}

void ElectricLoadCenterInverterFunctionOfPower::resetMinimumEfficiency() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetMinimumEfficiency();
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::maximumEfficiency() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->maximumEfficiency();
}

bool ElectricLoadCenterInverterFunctionOfPower::setMaximumEfficiency(double maximumEfficiency) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setMaximumEfficiency(maximumEfficiency);
}

void ElectricLoadCenterInverterFunctionOfPower::resetMaximumEfficiency() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetMaximumEfficiency();
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::minimumPowerOutput() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->minimumPowerOutput();
}

bool ElectricLoadCenterInverterFunctionOfPower::setMinimumPowerOutput(double minimumPowerOutput) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setMinimumPowerOutput(minimumPowerOutput);
}

void ElectricLoadCenterInverterFunctionOfPower::resetMinimumPowerOutput() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetMinimumPowerOutput();
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::maximumPowerOutput() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->maximumPowerOutput();
}

bool ElectricLoadCenterInverterFunctionOfPower::setMaximumPowerOutput(double maximumPowerOutput) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setMaximumPowerOutput(maximumPowerOutput);
}

void ElectricLoadCenterInverterFunctionOfPower::resetMaximumPowerOutput() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetMaximumPowerOutput();
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower::ancillaryPowerConsumedInStandby() const {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->ancillaryPowerConsumedInStandby();
}

bool ElectricLoadCenterInverterFunctionOfPower::setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby) {
  return getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->setAncillaryPowerConsumedInStandby(
    ancillaryPowerConsumedInStandby);
}

void ElectricLoadCenterInverterFunctionOfPower::resetAncillaryPowerConsumedInStandby() {
  getImpl<detail::ElectricLoadCenterInverterFunctionOfPower_Impl>()->resetAncillaryPowerConsumedInStandby();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::radiativeFraction() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::RadiativeFraction, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setRadiativeFraction(double radiativeFraction) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::RadiativeFraction, radiativeFraction);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetRadiativeFraction() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::RadiativeFraction, ""));
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::ratedMaximumContinuousInputPower() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::RatedMaximumContinuousInputPower, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setRatedMaximumContinuousInputPower(double ratedMaximumContinuousInputPower) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::RatedMaximumContinuousInputPower, ratedMaximumContinuousInputPower);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetRatedMaximumContinuousInputPower() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::RatedMaximumContinuousInputPower, ""));
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::minimumEfficiency() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumEfficiency, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setMinimumEfficiency(double minimumEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumEfficiency, minimumEfficiency);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetMinimumEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumEfficiency, ""));
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::maximumEfficiency() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumEfficiency, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setMaximumEfficiency(double maximumEfficiency) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumEfficiency, maximumEfficiency);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetMaximumEfficiency() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumEfficiency, ""));
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::minimumPowerOutput() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumPowerOutput, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setMinimumPowerOutput(double minimumPowerOutput) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumPowerOutput, minimumPowerOutput);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetMinimumPowerOutput() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MinimumPowerOutput, ""));
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::maximumPowerOutput() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumPowerOutput, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setMaximumPowerOutput(double maximumPowerOutput) {
  const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumPowerOutput, maximumPowerOutput);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetMaximumPowerOutput() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::MaximumPowerOutput, ""));
}

boost::optional<double> ElectricLoadCenterInverterFunctionOfPower_Impl::ancillaryPowerConsumedInStandby() const {
  return getDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::AncillaryPowerConsumedInStandby, true);
}

bool ElectricLoadCenterInverterFunctionOfPower_Impl::setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby) {
  const bool result =
    setDouble(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::AncillaryPowerConsumedInStandby, ancillaryPowerConsumedInStandby);
  OS_ASSERT(result);
  return result;
}

void ElectricLoadCenterInverterFunctionOfPower_Impl::resetAncillaryPowerConsumedInStandby() {
  OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_FunctionOfPowerFields::AncillaryPowerConsumedInStandby, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
