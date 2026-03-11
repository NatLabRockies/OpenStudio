/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DemandManagerExteriorLights.hpp"
#include "DemandManagerExteriorLights_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DemandManager_ExteriorLights_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

DemandManagerExteriorLights::DemandManagerExteriorLights(const Model& model)
  : ModelObject(DemandManagerExteriorLights::iddObjectType(), model) {}

DemandManagerExteriorLights::DemandManagerExteriorLights(std::shared_ptr<detail::DemandManagerExteriorLights_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType DemandManagerExteriorLights::iddObjectType() {
  return IddObjectType::DemandManager_ExteriorLights;
}

std::vector<std::string> DemandManagerExteriorLights::limitControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_ExteriorLightsFields::LimitControl);
}

std::vector<std::string> DemandManagerExteriorLights::selectionControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_ExteriorLightsFields::SelectionControl);
}

std::string DemandManagerExteriorLights::limitControl() const {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->limitControl();
}

bool DemandManagerExteriorLights::setLimitControl(const std::string& limitControl) {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->setLimitControl(limitControl);
}

boost::optional<int> DemandManagerExteriorLights::minimumLimitDuration() const {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->minimumLimitDuration();
}

bool DemandManagerExteriorLights::setMinimumLimitDuration(int minimumLimitDuration) {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->setMinimumLimitDuration(minimumLimitDuration);
}

void DemandManagerExteriorLights::resetMinimumLimitDuration() {
  getImpl<detail::DemandManagerExteriorLights_Impl>()->resetMinimumLimitDuration();
}

boost::optional<double> DemandManagerExteriorLights::maximumLimitFraction() const {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->maximumLimitFraction();
}

bool DemandManagerExteriorLights::setMaximumLimitFraction(double maximumLimitFraction) {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->setMaximumLimitFraction(maximumLimitFraction);
}

void DemandManagerExteriorLights::resetMaximumLimitFraction() {
  getImpl<detail::DemandManagerExteriorLights_Impl>()->resetMaximumLimitFraction();
}

boost::optional<double> DemandManagerExteriorLights::limitStepChange() const {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->limitStepChange();
}

bool DemandManagerExteriorLights::setLimitStepChange(double limitStepChange) {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->setLimitStepChange(limitStepChange);
}

void DemandManagerExteriorLights::resetLimitStepChange() {
  getImpl<detail::DemandManagerExteriorLights_Impl>()->resetLimitStepChange();
}

std::string DemandManagerExteriorLights::selectionControl() const {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->selectionControl();
}

bool DemandManagerExteriorLights::setSelectionControl(const std::string& selectionControl) {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->setSelectionControl(selectionControl);
}

boost::optional<int> DemandManagerExteriorLights::rotationDuration() const {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->rotationDuration();
}

bool DemandManagerExteriorLights::setRotationDuration(int rotationDuration) {
  return getImpl<detail::DemandManagerExteriorLights_Impl>()->setRotationDuration(rotationDuration);
}

void DemandManagerExteriorLights::resetRotationDuration() {
  getImpl<detail::DemandManagerExteriorLights_Impl>()->resetRotationDuration();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DemandManagerExteriorLights_Impl::limitControl() const {
  const auto value = getString(openstudio::DemandManager_ExteriorLightsFields::LimitControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerExteriorLights_Impl::setLimitControl(const std::string& limitControl) {
  return setString(openstudio::DemandManager_ExteriorLightsFields::LimitControl, limitControl);
}

boost::optional<int> DemandManagerExteriorLights_Impl::minimumLimitDuration() const {
  return getInt(openstudio::DemandManager_ExteriorLightsFields::MinimumLimitDuration, true);
}

bool DemandManagerExteriorLights_Impl::setMinimumLimitDuration(int minimumLimitDuration) {
  return setInt(openstudio::DemandManager_ExteriorLightsFields::MinimumLimitDuration, minimumLimitDuration);
}

void DemandManagerExteriorLights_Impl::resetMinimumLimitDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_ExteriorLightsFields::MinimumLimitDuration, ""));
}

boost::optional<double> DemandManagerExteriorLights_Impl::maximumLimitFraction() const {
  return getDouble(openstudio::DemandManager_ExteriorLightsFields::MaximumLimitFraction, true);
}

bool DemandManagerExteriorLights_Impl::setMaximumLimitFraction(double maximumLimitFraction) {
  return setDouble(openstudio::DemandManager_ExteriorLightsFields::MaximumLimitFraction, maximumLimitFraction);
}

void DemandManagerExteriorLights_Impl::resetMaximumLimitFraction() {
  OS_ASSERT(setString(openstudio::DemandManager_ExteriorLightsFields::MaximumLimitFraction, ""));
}

boost::optional<double> DemandManagerExteriorLights_Impl::limitStepChange() const {
  return getDouble(openstudio::DemandManager_ExteriorLightsFields::LimitStepChange, true);
}

bool DemandManagerExteriorLights_Impl::setLimitStepChange(double limitStepChange) {
  const bool result = setDouble(openstudio::DemandManager_ExteriorLightsFields::LimitStepChange, limitStepChange);
  OS_ASSERT(result);
  return result;
}

void DemandManagerExteriorLights_Impl::resetLimitStepChange() {
  OS_ASSERT(setString(openstudio::DemandManager_ExteriorLightsFields::LimitStepChange, ""));
}

std::string DemandManagerExteriorLights_Impl::selectionControl() const {
  const auto value = getString(openstudio::DemandManager_ExteriorLightsFields::SelectionControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerExteriorLights_Impl::setSelectionControl(const std::string& selectionControl) {
  return setString(openstudio::DemandManager_ExteriorLightsFields::SelectionControl, selectionControl);
}

boost::optional<int> DemandManagerExteriorLights_Impl::rotationDuration() const {
  return getInt(openstudio::DemandManager_ExteriorLightsFields::RotationDuration, true);
}

bool DemandManagerExteriorLights_Impl::setRotationDuration(int rotationDuration) {
  return setInt(openstudio::DemandManager_ExteriorLightsFields::RotationDuration, rotationDuration);
}

void DemandManagerExteriorLights_Impl::resetRotationDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_ExteriorLightsFields::RotationDuration, ""));
}

std::vector<std::string> DemandManagerExteriorLights_Impl::limitControlValues() const {
  return openstudio::epmodel::DemandManagerExteriorLights::limitControlValues();
}

std::vector<std::string> DemandManagerExteriorLights_Impl::selectionControlValues() const {
  return openstudio::epmodel::DemandManagerExteriorLights::selectionControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
