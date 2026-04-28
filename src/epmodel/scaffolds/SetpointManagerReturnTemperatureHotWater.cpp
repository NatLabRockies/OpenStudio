/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManagerReturnTemperatureHotWater.hpp"
#include "SetpointManagerReturnTemperatureHotWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_ReturnTemperature_HotWater_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerReturnTemperatureHotWater::SetpointManagerReturnTemperatureHotWater(const Model& model)
  : ModelObject(SetpointManagerReturnTemperatureHotWater::iddObjectType(), model) {}

SetpointManagerReturnTemperatureHotWater::SetpointManagerReturnTemperatureHotWater(
  std::shared_ptr<detail::SetpointManagerReturnTemperatureHotWater_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SetpointManagerReturnTemperatureHotWater::iddObjectType() {
  return IddObjectType::SetpointManager_ReturnTemperature_HotWater;
}

std::vector<std::string> SetpointManagerReturnTemperatureHotWater::returnTemperatureSetpointInputTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointInputType);
}

double SetpointManagerReturnTemperatureHotWater::minimumSupplyTemperatureSetpoint() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->minimumSupplyTemperatureSetpoint();
}

bool SetpointManagerReturnTemperatureHotWater::isMinimumSupplyTemperatureSetpointDefaulted() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->isMinimumSupplyTemperatureSetpointDefaulted();
}

bool SetpointManagerReturnTemperatureHotWater::setMinimumSupplyTemperatureSetpoint(double minimumSupplyTemperatureSetpoint) {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->setMinimumSupplyTemperatureSetpoint(minimumSupplyTemperatureSetpoint);
}

void SetpointManagerReturnTemperatureHotWater::resetMinimumSupplyTemperatureSetpoint() {
  getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->resetMinimumSupplyTemperatureSetpoint();
}

double SetpointManagerReturnTemperatureHotWater::maximumSupplyTemperatureSetpoint() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->maximumSupplyTemperatureSetpoint();
}

bool SetpointManagerReturnTemperatureHotWater::isMaximumSupplyTemperatureSetpointDefaulted() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->isMaximumSupplyTemperatureSetpointDefaulted();
}

bool SetpointManagerReturnTemperatureHotWater::setMaximumSupplyTemperatureSetpoint(double maximumSupplyTemperatureSetpoint) {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->setMaximumSupplyTemperatureSetpoint(maximumSupplyTemperatureSetpoint);
}

void SetpointManagerReturnTemperatureHotWater::resetMaximumSupplyTemperatureSetpoint() {
  getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->resetMaximumSupplyTemperatureSetpoint();
}

std::string SetpointManagerReturnTemperatureHotWater::returnTemperatureSetpointInputType() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->returnTemperatureSetpointInputType();
}

bool SetpointManagerReturnTemperatureHotWater::setReturnTemperatureSetpointInputType(const std::string& returnTemperatureSetpointInputType) {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->setReturnTemperatureSetpointInputType(returnTemperatureSetpointInputType);
}

double SetpointManagerReturnTemperatureHotWater::returnTemperatureSetpointConstantValue() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->returnTemperatureSetpointConstantValue();
}

bool SetpointManagerReturnTemperatureHotWater::isReturnTemperatureSetpointConstantValueDefaulted() const {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->isReturnTemperatureSetpointConstantValueDefaulted();
}

bool SetpointManagerReturnTemperatureHotWater::setReturnTemperatureSetpointConstantValue(double returnTemperatureSetpointConstantValue) {
  return getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->setReturnTemperatureSetpointConstantValue(returnTemperatureSetpointConstantValue);
}

void SetpointManagerReturnTemperatureHotWater::resetReturnTemperatureSetpointConstantValue() {
  getImpl<detail::SetpointManagerReturnTemperatureHotWater_Impl>()->resetReturnTemperatureSetpointConstantValue();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SetpointManagerReturnTemperatureHotWater_Impl::minimumSupplyTemperatureSetpoint() const {
  const auto value = getDouble(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MinimumSupplyTemperatureSetpoint, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerReturnTemperatureHotWater_Impl::isMinimumSupplyTemperatureSetpointDefaulted() const {
  return isEmpty(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MinimumSupplyTemperatureSetpoint);
}

bool SetpointManagerReturnTemperatureHotWater_Impl::setMinimumSupplyTemperatureSetpoint(double minimumSupplyTemperatureSetpoint) {
  const bool result = setDouble(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MinimumSupplyTemperatureSetpoint,
                                minimumSupplyTemperatureSetpoint);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerReturnTemperatureHotWater_Impl::resetMinimumSupplyTemperatureSetpoint() {
  OS_ASSERT(setString(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MinimumSupplyTemperatureSetpoint, ""));
}

double SetpointManagerReturnTemperatureHotWater_Impl::maximumSupplyTemperatureSetpoint() const {
  const auto value = getDouble(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MaximumSupplyTemperatureSetpoint, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerReturnTemperatureHotWater_Impl::isMaximumSupplyTemperatureSetpointDefaulted() const {
  return isEmpty(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MaximumSupplyTemperatureSetpoint);
}

bool SetpointManagerReturnTemperatureHotWater_Impl::setMaximumSupplyTemperatureSetpoint(double maximumSupplyTemperatureSetpoint) {
  const bool result = setDouble(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MaximumSupplyTemperatureSetpoint,
                                maximumSupplyTemperatureSetpoint);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerReturnTemperatureHotWater_Impl::resetMaximumSupplyTemperatureSetpoint() {
  OS_ASSERT(setString(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::MaximumSupplyTemperatureSetpoint, ""));
}

std::string SetpointManagerReturnTemperatureHotWater_Impl::returnTemperatureSetpointInputType() const {
  const auto value = getString(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointInputType, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerReturnTemperatureHotWater_Impl::setReturnTemperatureSetpointInputType(const std::string& returnTemperatureSetpointInputType) {
  return setString(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointInputType,
                   returnTemperatureSetpointInputType);
}

double SetpointManagerReturnTemperatureHotWater_Impl::returnTemperatureSetpointConstantValue() const {
  const auto value = getDouble(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointConstantValue, true);
  OS_ASSERT(value);
  return *value;
}

bool SetpointManagerReturnTemperatureHotWater_Impl::isReturnTemperatureSetpointConstantValueDefaulted() const {
  return isEmpty(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointConstantValue);
}

bool SetpointManagerReturnTemperatureHotWater_Impl::setReturnTemperatureSetpointConstantValue(double returnTemperatureSetpointConstantValue) {
  const bool result = setDouble(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointConstantValue,
                                returnTemperatureSetpointConstantValue);
  OS_ASSERT(result);
  return result;
}

void SetpointManagerReturnTemperatureHotWater_Impl::resetReturnTemperatureSetpointConstantValue() {
  OS_ASSERT(setString(openstudio::SetpointManager_ReturnTemperature_HotWaterFields::ReturnTemperatureSetpointConstantValue, ""));
}

std::vector<std::string> SetpointManagerReturnTemperatureHotWater_Impl::returnTemperatureSetpointInputTypeValues() const {
  return SetpointManagerReturnTemperatureHotWater::returnTemperatureSetpointInputTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
