/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DemandManagerLights.hpp"
#include "DemandManagerLights_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DemandManager_Lights_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

DemandManagerLights::DemandManagerLights(const Model& model) : ModelObject(DemandManagerLights::iddObjectType(), model) {}

DemandManagerLights::DemandManagerLights(std::shared_ptr<detail::DemandManagerLights_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DemandManagerLights::iddObjectType() {
  return IddObjectType::DemandManager_Lights;
}

std::vector<std::string> DemandManagerLights::limitControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_LightsFields::LimitControl);
}

std::vector<std::string> DemandManagerLights::selectionControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_LightsFields::SelectionControl);
}

std::string DemandManagerLights::limitControl() const {
  return getImpl<detail::DemandManagerLights_Impl>()->limitControl();
}

bool DemandManagerLights::setLimitControl(const std::string& limitControl) {
  return getImpl<detail::DemandManagerLights_Impl>()->setLimitControl(limitControl);
}

boost::optional<int> DemandManagerLights::minimumLimitDuration() const {
  return getImpl<detail::DemandManagerLights_Impl>()->minimumLimitDuration();
}

bool DemandManagerLights::setMinimumLimitDuration(int minimumLimitDuration) {
  return getImpl<detail::DemandManagerLights_Impl>()->setMinimumLimitDuration(minimumLimitDuration);
}

void DemandManagerLights::resetMinimumLimitDuration() {
  getImpl<detail::DemandManagerLights_Impl>()->resetMinimumLimitDuration();
}

boost::optional<double> DemandManagerLights::maximumLimitFraction() const {
  return getImpl<detail::DemandManagerLights_Impl>()->maximumLimitFraction();
}

bool DemandManagerLights::setMaximumLimitFraction(double maximumLimitFraction) {
  return getImpl<detail::DemandManagerLights_Impl>()->setMaximumLimitFraction(maximumLimitFraction);
}

void DemandManagerLights::resetMaximumLimitFraction() {
  getImpl<detail::DemandManagerLights_Impl>()->resetMaximumLimitFraction();
}

boost::optional<double> DemandManagerLights::limitStepChange() const {
  return getImpl<detail::DemandManagerLights_Impl>()->limitStepChange();
}

bool DemandManagerLights::setLimitStepChange(double limitStepChange) {
  return getImpl<detail::DemandManagerLights_Impl>()->setLimitStepChange(limitStepChange);
}

void DemandManagerLights::resetLimitStepChange() {
  getImpl<detail::DemandManagerLights_Impl>()->resetLimitStepChange();
}

std::string DemandManagerLights::selectionControl() const {
  return getImpl<detail::DemandManagerLights_Impl>()->selectionControl();
}

bool DemandManagerLights::setSelectionControl(const std::string& selectionControl) {
  return getImpl<detail::DemandManagerLights_Impl>()->setSelectionControl(selectionControl);
}

boost::optional<int> DemandManagerLights::rotationDuration() const {
  return getImpl<detail::DemandManagerLights_Impl>()->rotationDuration();
}

bool DemandManagerLights::setRotationDuration(int rotationDuration) {
  return getImpl<detail::DemandManagerLights_Impl>()->setRotationDuration(rotationDuration);
}

void DemandManagerLights::resetRotationDuration() {
  getImpl<detail::DemandManagerLights_Impl>()->resetRotationDuration();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DemandManagerLights_Impl::limitControl() const {
  const auto value = getString(openstudio::DemandManager_LightsFields::LimitControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerLights_Impl::setLimitControl(const std::string& limitControl) {
  return setString(openstudio::DemandManager_LightsFields::LimitControl, limitControl);
}

boost::optional<int> DemandManagerLights_Impl::minimumLimitDuration() const {
  return getInt(openstudio::DemandManager_LightsFields::MinimumLimitDuration, true);
}

bool DemandManagerLights_Impl::setMinimumLimitDuration(int minimumLimitDuration) {
  return setInt(openstudio::DemandManager_LightsFields::MinimumLimitDuration, minimumLimitDuration);
}

void DemandManagerLights_Impl::resetMinimumLimitDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_LightsFields::MinimumLimitDuration, ""));
}

boost::optional<double> DemandManagerLights_Impl::maximumLimitFraction() const {
  return getDouble(openstudio::DemandManager_LightsFields::MaximumLimitFraction, true);
}

bool DemandManagerLights_Impl::setMaximumLimitFraction(double maximumLimitFraction) {
  return setDouble(openstudio::DemandManager_LightsFields::MaximumLimitFraction, maximumLimitFraction);
}

void DemandManagerLights_Impl::resetMaximumLimitFraction() {
  OS_ASSERT(setString(openstudio::DemandManager_LightsFields::MaximumLimitFraction, ""));
}

boost::optional<double> DemandManagerLights_Impl::limitStepChange() const {
  return getDouble(openstudio::DemandManager_LightsFields::LimitStepChange, true);
}

bool DemandManagerLights_Impl::setLimitStepChange(double limitStepChange) {
  const bool result = setDouble(openstudio::DemandManager_LightsFields::LimitStepChange, limitStepChange);
  OS_ASSERT(result);
  return result;
}

void DemandManagerLights_Impl::resetLimitStepChange() {
  OS_ASSERT(setString(openstudio::DemandManager_LightsFields::LimitStepChange, ""));
}

std::string DemandManagerLights_Impl::selectionControl() const {
  const auto value = getString(openstudio::DemandManager_LightsFields::SelectionControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerLights_Impl::setSelectionControl(const std::string& selectionControl) {
  return setString(openstudio::DemandManager_LightsFields::SelectionControl, selectionControl);
}

boost::optional<int> DemandManagerLights_Impl::rotationDuration() const {
  return getInt(openstudio::DemandManager_LightsFields::RotationDuration, true);
}

bool DemandManagerLights_Impl::setRotationDuration(int rotationDuration) {
  return setInt(openstudio::DemandManager_LightsFields::RotationDuration, rotationDuration);
}

void DemandManagerLights_Impl::resetRotationDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_LightsFields::RotationDuration, ""));
}

std::vector<std::string> DemandManagerLights_Impl::limitControlValues() const {
  return openstudio::epmodel::DemandManagerLights::limitControlValues();
}

std::vector<std::string> DemandManagerLights_Impl::selectionControlValues() const {
  return openstudio::epmodel::DemandManagerLights::selectionControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
