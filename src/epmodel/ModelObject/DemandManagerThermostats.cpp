/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DemandManagerThermostats.hpp"
#include "DemandManagerThermostats_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DemandManager_Thermostats_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

DemandManagerThermostats::DemandManagerThermostats(const Model& model) : ModelObject(DemandManagerThermostats::iddObjectType(), model) {}

DemandManagerThermostats::DemandManagerThermostats(std::shared_ptr<detail::DemandManagerThermostats_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DemandManagerThermostats::iddObjectType() {
  return IddObjectType::DemandManager_Thermostats;
}

std::vector<std::string> DemandManagerThermostats::resetControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_ThermostatsFields::ResetControl);
}

std::vector<std::string> DemandManagerThermostats::selectionControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_ThermostatsFields::SelectionControl);
}

std::string DemandManagerThermostats::resetControl() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->resetControl();
}

bool DemandManagerThermostats::setResetControl(const std::string& resetControl) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setResetControl(resetControl);
}

boost::optional<int> DemandManagerThermostats::minimumResetDuration() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->minimumResetDuration();
}

bool DemandManagerThermostats::setMinimumResetDuration(int minimumResetDuration) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setMinimumResetDuration(minimumResetDuration);
}

void DemandManagerThermostats::resetMinimumResetDuration() {
  getImpl<detail::DemandManagerThermostats_Impl>()->resetMinimumResetDuration();
}

double DemandManagerThermostats::maximumHeatingSetpointReset() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->maximumHeatingSetpointReset();
}

bool DemandManagerThermostats::setMaximumHeatingSetpointReset(double maximumHeatingSetpointReset) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setMaximumHeatingSetpointReset(maximumHeatingSetpointReset);
}

double DemandManagerThermostats::maximumCoolingSetpointReset() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->maximumCoolingSetpointReset();
}

bool DemandManagerThermostats::setMaximumCoolingSetpointReset(double maximumCoolingSetpointReset) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setMaximumCoolingSetpointReset(maximumCoolingSetpointReset);
}

boost::optional<double> DemandManagerThermostats::resetStepChange() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->resetStepChange();
}

bool DemandManagerThermostats::setResetStepChange(double resetStepChange) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setResetStepChange(resetStepChange);
}

void DemandManagerThermostats::resetResetStepChange() {
  getImpl<detail::DemandManagerThermostats_Impl>()->resetResetStepChange();
}

std::string DemandManagerThermostats::selectionControl() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->selectionControl();
}

bool DemandManagerThermostats::setSelectionControl(const std::string& selectionControl) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setSelectionControl(selectionControl);
}

boost::optional<int> DemandManagerThermostats::rotationDuration() const {
  return getImpl<detail::DemandManagerThermostats_Impl>()->rotationDuration();
}

bool DemandManagerThermostats::setRotationDuration(int rotationDuration) {
  return getImpl<detail::DemandManagerThermostats_Impl>()->setRotationDuration(rotationDuration);
}

void DemandManagerThermostats::resetRotationDuration() {
  getImpl<detail::DemandManagerThermostats_Impl>()->resetRotationDuration();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DemandManagerThermostats_Impl::resetControl() const {
  const auto value = getString(openstudio::DemandManager_ThermostatsFields::ResetControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerThermostats_Impl::setResetControl(const std::string& resetControl) {
  return setString(openstudio::DemandManager_ThermostatsFields::ResetControl, resetControl);
}

boost::optional<int> DemandManagerThermostats_Impl::minimumResetDuration() const {
  return getInt(openstudio::DemandManager_ThermostatsFields::MinimumResetDuration, true);
}

bool DemandManagerThermostats_Impl::setMinimumResetDuration(int minimumResetDuration) {
  return setInt(openstudio::DemandManager_ThermostatsFields::MinimumResetDuration, minimumResetDuration);
}

void DemandManagerThermostats_Impl::resetMinimumResetDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_ThermostatsFields::MinimumResetDuration, ""));
}

double DemandManagerThermostats_Impl::maximumHeatingSetpointReset() const {
  const auto value = getDouble(openstudio::DemandManager_ThermostatsFields::MaximumHeatingSetpointReset, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerThermostats_Impl::setMaximumHeatingSetpointReset(double maximumHeatingSetpointReset) {
  const bool result = setDouble(openstudio::DemandManager_ThermostatsFields::MaximumHeatingSetpointReset, maximumHeatingSetpointReset);
  OS_ASSERT(result);
  return result;
}

double DemandManagerThermostats_Impl::maximumCoolingSetpointReset() const {
  const auto value = getDouble(openstudio::DemandManager_ThermostatsFields::MaximumCoolingSetpointReset, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerThermostats_Impl::setMaximumCoolingSetpointReset(double maximumCoolingSetpointReset) {
  const bool result = setDouble(openstudio::DemandManager_ThermostatsFields::MaximumCoolingSetpointReset, maximumCoolingSetpointReset);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> DemandManagerThermostats_Impl::resetStepChange() const {
  return getDouble(openstudio::DemandManager_ThermostatsFields::ResetStepChange, true);
}

bool DemandManagerThermostats_Impl::setResetStepChange(double resetStepChange) {
  const bool result = setDouble(openstudio::DemandManager_ThermostatsFields::ResetStepChange, resetStepChange);
  OS_ASSERT(result);
  return result;
}

void DemandManagerThermostats_Impl::resetResetStepChange() {
  OS_ASSERT(setString(openstudio::DemandManager_ThermostatsFields::ResetStepChange, ""));
}

std::string DemandManagerThermostats_Impl::selectionControl() const {
  const auto value = getString(openstudio::DemandManager_ThermostatsFields::SelectionControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerThermostats_Impl::setSelectionControl(const std::string& selectionControl) {
  return setString(openstudio::DemandManager_ThermostatsFields::SelectionControl, selectionControl);
}

boost::optional<int> DemandManagerThermostats_Impl::rotationDuration() const {
  return getInt(openstudio::DemandManager_ThermostatsFields::RotationDuration, true);
}

bool DemandManagerThermostats_Impl::setRotationDuration(int rotationDuration) {
  return setInt(openstudio::DemandManager_ThermostatsFields::RotationDuration, rotationDuration);
}

void DemandManagerThermostats_Impl::resetRotationDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_ThermostatsFields::RotationDuration, ""));
}

std::vector<std::string> DemandManagerThermostats_Impl::resetControlValues() const {
  return openstudio::epmodel::DemandManagerThermostats::resetControlValues();
}

std::vector<std::string> DemandManagerThermostats_Impl::selectionControlValues() const {
  return openstudio::epmodel::DemandManagerThermostats::selectionControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
