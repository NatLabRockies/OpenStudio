/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DemandManagerVentilation.hpp"
#include "DemandManagerVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DemandManager_Ventilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

DemandManagerVentilation::DemandManagerVentilation(const Model& model) : ModelObject(DemandManagerVentilation::iddObjectType(), model) {}

DemandManagerVentilation::DemandManagerVentilation(std::shared_ptr<detail::DemandManagerVentilation_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DemandManagerVentilation::iddObjectType() {
  return IddObjectType::DemandManager_Ventilation;
}

std::vector<std::string> DemandManagerVentilation::limitControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_VentilationFields::LimitControl);
}

std::vector<std::string> DemandManagerVentilation::selectionControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::DemandManager_VentilationFields::SelectionControl);
}

std::string DemandManagerVentilation::limitControl() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->limitControl();
}

bool DemandManagerVentilation::setLimitControl(const std::string& limitControl) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setLimitControl(limitControl);
}

boost::optional<int> DemandManagerVentilation::minimumLimitDuration() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->minimumLimitDuration();
}

bool DemandManagerVentilation::setMinimumLimitDuration(int minimumLimitDuration) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setMinimumLimitDuration(minimumLimitDuration);
}

void DemandManagerVentilation::resetMinimumLimitDuration() {
  getImpl<detail::DemandManagerVentilation_Impl>()->resetMinimumLimitDuration();
}

boost::optional<double> DemandManagerVentilation::fixedRate() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->fixedRate();
}

bool DemandManagerVentilation::setFixedRate(double fixedRate) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setFixedRate(fixedRate);
}

void DemandManagerVentilation::resetFixedRate() {
  getImpl<detail::DemandManagerVentilation_Impl>()->resetFixedRate();
}

boost::optional<double> DemandManagerVentilation::reductionRatio() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->reductionRatio();
}

bool DemandManagerVentilation::setReductionRatio(double reductionRatio) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setReductionRatio(reductionRatio);
}

void DemandManagerVentilation::resetReductionRatio() {
  getImpl<detail::DemandManagerVentilation_Impl>()->resetReductionRatio();
}

boost::optional<double> DemandManagerVentilation::limitStepChange() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->limitStepChange();
}

bool DemandManagerVentilation::setLimitStepChange(double limitStepChange) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setLimitStepChange(limitStepChange);
}

void DemandManagerVentilation::resetLimitStepChange() {
  getImpl<detail::DemandManagerVentilation_Impl>()->resetLimitStepChange();
}

std::string DemandManagerVentilation::selectionControl() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->selectionControl();
}

bool DemandManagerVentilation::isSelectionControlDefaulted() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->isSelectionControlDefaulted();
}

bool DemandManagerVentilation::setSelectionControl(const std::string& selectionControl) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setSelectionControl(selectionControl);
}

void DemandManagerVentilation::resetSelectionControl() {
  getImpl<detail::DemandManagerVentilation_Impl>()->resetSelectionControl();
}

boost::optional<int> DemandManagerVentilation::rotationDuration() const {
  return getImpl<detail::DemandManagerVentilation_Impl>()->rotationDuration();
}

bool DemandManagerVentilation::setRotationDuration(int rotationDuration) {
  return getImpl<detail::DemandManagerVentilation_Impl>()->setRotationDuration(rotationDuration);
}

void DemandManagerVentilation::resetRotationDuration() {
  getImpl<detail::DemandManagerVentilation_Impl>()->resetRotationDuration();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string DemandManagerVentilation_Impl::limitControl() const {
  const auto value = getString(openstudio::DemandManager_VentilationFields::LimitControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerVentilation_Impl::setLimitControl(const std::string& limitControl) {
  return setString(openstudio::DemandManager_VentilationFields::LimitControl, limitControl);
}

boost::optional<int> DemandManagerVentilation_Impl::minimumLimitDuration() const {
  return getInt(openstudio::DemandManager_VentilationFields::MinimumLimitDuration, true);
}

bool DemandManagerVentilation_Impl::setMinimumLimitDuration(int minimumLimitDuration) {
  return setInt(openstudio::DemandManager_VentilationFields::MinimumLimitDuration, minimumLimitDuration);
}

void DemandManagerVentilation_Impl::resetMinimumLimitDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_VentilationFields::MinimumLimitDuration, ""));
}

boost::optional<double> DemandManagerVentilation_Impl::fixedRate() const {
  return getDouble(openstudio::DemandManager_VentilationFields::FixedRate, true);
}

bool DemandManagerVentilation_Impl::setFixedRate(double fixedRate) {
  return setDouble(openstudio::DemandManager_VentilationFields::FixedRate, fixedRate);
}

void DemandManagerVentilation_Impl::resetFixedRate() {
  OS_ASSERT(setString(openstudio::DemandManager_VentilationFields::FixedRate, ""));
}

boost::optional<double> DemandManagerVentilation_Impl::reductionRatio() const {
  return getDouble(openstudio::DemandManager_VentilationFields::ReductionRatio, true);
}

bool DemandManagerVentilation_Impl::setReductionRatio(double reductionRatio) {
  return setDouble(openstudio::DemandManager_VentilationFields::ReductionRatio, reductionRatio);
}

void DemandManagerVentilation_Impl::resetReductionRatio() {
  OS_ASSERT(setString(openstudio::DemandManager_VentilationFields::ReductionRatio, ""));
}

boost::optional<double> DemandManagerVentilation_Impl::limitStepChange() const {
  return getDouble(openstudio::DemandManager_VentilationFields::LimitStepChange, true);
}

bool DemandManagerVentilation_Impl::setLimitStepChange(double limitStepChange) {
  const bool result = setDouble(openstudio::DemandManager_VentilationFields::LimitStepChange, limitStepChange);
  OS_ASSERT(result);
  return result;
}

void DemandManagerVentilation_Impl::resetLimitStepChange() {
  OS_ASSERT(setString(openstudio::DemandManager_VentilationFields::LimitStepChange, ""));
}

std::string DemandManagerVentilation_Impl::selectionControl() const {
  const auto value = getString(openstudio::DemandManager_VentilationFields::SelectionControl, true);
  OS_ASSERT(value);
  return *value;
}

bool DemandManagerVentilation_Impl::isSelectionControlDefaulted() const {
  return isEmpty(openstudio::DemandManager_VentilationFields::SelectionControl);
}

bool DemandManagerVentilation_Impl::setSelectionControl(const std::string& selectionControl) {
  return setString(openstudio::DemandManager_VentilationFields::SelectionControl, selectionControl);
}

void DemandManagerVentilation_Impl::resetSelectionControl() {
  OS_ASSERT(setString(openstudio::DemandManager_VentilationFields::SelectionControl, ""));
}

boost::optional<int> DemandManagerVentilation_Impl::rotationDuration() const {
  return getInt(openstudio::DemandManager_VentilationFields::RotationDuration, true);
}

bool DemandManagerVentilation_Impl::setRotationDuration(int rotationDuration) {
  return setInt(openstudio::DemandManager_VentilationFields::RotationDuration, rotationDuration);
}

void DemandManagerVentilation_Impl::resetRotationDuration() {
  OS_ASSERT(setString(openstudio::DemandManager_VentilationFields::RotationDuration, ""));
}

std::vector<std::string> DemandManagerVentilation_Impl::limitControlValues() const {
  return openstudio::epmodel::DemandManagerVentilation::limitControlValues();
}

std::vector<std::string> DemandManagerVentilation_Impl::selectionControlValues() const {
  return openstudio::epmodel::DemandManagerVentilation::selectionControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
