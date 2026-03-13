/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "AvailabilityManager/AvailabilityManagerNightCycle_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/Loop.hpp"
#include "Loop/Loop_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AvailabilityManager_NightCycle_FieldEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AvailabilityManagerNightCycle::AvailabilityManagerNightCycle(const Model& model)
  : AvailabilityManager(AvailabilityManagerNightCycle::iddObjectType(), model) {
  auto impl = getImpl<detail::AvailabilityManagerNightCycle_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
  setThermostatTolerance(1.0);
  setCyclingRunTime(3600.0);
}

AvailabilityManagerNightCycle::AvailabilityManagerNightCycle(std::shared_ptr<detail::AvailabilityManagerNightCycle_Impl> impl)
  : AvailabilityManager(std::move(impl)) {}

IddObjectType AvailabilityManagerNightCycle::iddObjectType() {
  return IddObjectType::AvailabilityManager_NightCycle;
}

std::vector<std::string> AvailabilityManagerNightCycle::controlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AvailabilityManager_NightCycleFields::ControlType);
}

std::vector<std::string> AvailabilityManagerNightCycle::cyclingRunTimeControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AvailabilityManager_NightCycleFields::CyclingRunTimeControlType);
}

boost::optional<AirLoopHVAC> AvailabilityManagerNightCycle::airLoopHVAC() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->airLoopHVAC();
}

std::string AvailabilityManagerNightCycle::controlType() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->controlType();
}

bool AvailabilityManagerNightCycle::setControlType(const std::string& controlType) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setControlType(controlType);
}

bool AvailabilityManagerNightCycle::isControlTypeDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isControlTypeDefaulted();
}

void AvailabilityManagerNightCycle::resetControlType() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetControlType();
}

double AvailabilityManagerNightCycle::thermostatTolerance() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->thermostatTolerance();
}

bool AvailabilityManagerNightCycle::setThermostatTolerance(double thermostatTolerance) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setThermostatTolerance(thermostatTolerance);
}

bool AvailabilityManagerNightCycle::isThermostatToleranceDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isThermostatToleranceDefaulted();
}

void AvailabilityManagerNightCycle::resetThermostatTolerance() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetThermostatTolerance();
}

double AvailabilityManagerNightCycle::cyclingRunTime() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->cyclingRunTime();
}

bool AvailabilityManagerNightCycle::setCyclingRunTime(double cyclingRunTime) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setCyclingRunTime(cyclingRunTime);
}

bool AvailabilityManagerNightCycle::isCyclingRunTimeDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isCyclingRunTimeDefaulted();
}

void AvailabilityManagerNightCycle::resetCyclingRunTime() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetCyclingRunTime();
}

std::string AvailabilityManagerNightCycle::cyclingRunTimeControlType() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->cyclingRunTimeControlType();
}

bool AvailabilityManagerNightCycle::setCyclingRunTimeControlType(const std::string& cyclingRunTimeControlType) {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->setCyclingRunTimeControlType(cyclingRunTimeControlType);
}

bool AvailabilityManagerNightCycle::isCyclingRunTimeControlTypeDefaulted() const {
  return getImpl<detail::AvailabilityManagerNightCycle_Impl>()->isCyclingRunTimeControlTypeDefaulted();
}

void AvailabilityManagerNightCycle::resetCyclingRunTimeControlType() {
  getImpl<detail::AvailabilityManagerNightCycle_Impl>()->resetCyclingRunTimeControlType();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<openstudio::epmodel::AirLoopHVAC> AvailabilityManagerNightCycle_Impl::airLoopHVAC() const {
  auto owner = loop();
  if (!owner) {
    return boost::none;
  }
  return owner->optionalCast<openstudio::epmodel::AirLoopHVAC>();
}

std::string AvailabilityManagerNightCycle_Impl::controlType() const {
  const auto value = getString(openstudio::AvailabilityManager_NightCycleFields::ControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightCycle_Impl::setControlType(const std::string& controlType) {
  return setString(openstudio::AvailabilityManager_NightCycleFields::ControlType, controlType);
}

bool AvailabilityManagerNightCycle_Impl::isControlTypeDefaulted() const {
  return isEmpty(openstudio::AvailabilityManager_NightCycleFields::ControlType);
}

void AvailabilityManagerNightCycle_Impl::resetControlType() {
  OS_ASSERT(setString(openstudio::AvailabilityManager_NightCycleFields::ControlType, ""));
}

double AvailabilityManagerNightCycle_Impl::thermostatTolerance() const {
  const auto value = getDouble(openstudio::AvailabilityManager_NightCycleFields::ThermostatTolerance, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightCycle_Impl::setThermostatTolerance(double thermostatTolerance) {
  return setDouble(openstudio::AvailabilityManager_NightCycleFields::ThermostatTolerance, thermostatTolerance);
}

bool AvailabilityManagerNightCycle_Impl::isThermostatToleranceDefaulted() const {
  return isEmpty(openstudio::AvailabilityManager_NightCycleFields::ThermostatTolerance);
}

void AvailabilityManagerNightCycle_Impl::resetThermostatTolerance() {
  const bool result = setString(openstudio::AvailabilityManager_NightCycleFields::ThermostatTolerance, "");
  OS_ASSERT(result);
}

double AvailabilityManagerNightCycle_Impl::cyclingRunTime() const {
  const auto value = getDouble(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTime, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightCycle_Impl::setCyclingRunTime(double cyclingRunTime) {
  return setDouble(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTime, cyclingRunTime);
}

bool AvailabilityManagerNightCycle_Impl::isCyclingRunTimeDefaulted() const {
  return isEmpty(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTime);
}

void AvailabilityManagerNightCycle_Impl::resetCyclingRunTime() {
  const bool result = setString(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTime, "");
  OS_ASSERT(result);
}

std::string AvailabilityManagerNightCycle_Impl::cyclingRunTimeControlType() const {
  const auto value = getString(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTimeControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AvailabilityManagerNightCycle_Impl::setCyclingRunTimeControlType(const std::string& cyclingRunTimeControlType) {
  return setString(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTimeControlType, cyclingRunTimeControlType);
}

bool AvailabilityManagerNightCycle_Impl::isCyclingRunTimeControlTypeDefaulted() const {
  return isEmpty(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTimeControlType);
}

void AvailabilityManagerNightCycle_Impl::resetCyclingRunTimeControlType() {
  const bool result = setString(openstudio::AvailabilityManager_NightCycleFields::CyclingRunTimeControlType, "");
  OS_ASSERT(result);
}

std::vector<std::string> AvailabilityManagerNightCycle_Impl::controlTypeValues() const {
  return openstudio::epmodel::AvailabilityManagerNightCycle::controlTypeValues();
}

std::vector<std::string> AvailabilityManagerNightCycle_Impl::cyclingRunTimeControlTypeValues() const {
  return openstudio::epmodel::AvailabilityManagerNightCycle::cyclingRunTimeControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
