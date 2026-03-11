/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/FanZoneExhaust.hpp"
#include "ZoneHVACComponent/FanZoneExhaust_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Fan_ZoneExhaust_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FanZoneExhaust::FanZoneExhaust(const Model& model) : ModelObject(FanZoneExhaust::iddObjectType(), model) {
  // Mirror openstudio::model constructor defaults for required scalar fields.
  OS_ASSERT(setFanTotalEfficiency(0.60));
  OS_ASSERT(setPressureRise(0.0));
  OS_ASSERT(setEndUseSubcategory("General"));
  OS_ASSERT(setSystemAvailabilityManagerCouplingMode("Decoupled"));
}

FanZoneExhaust::FanZoneExhaust(std::shared_ptr<detail::FanZoneExhaust_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType FanZoneExhaust::iddObjectType() {
  return IddObjectType::Fan_ZoneExhaust;
}

std::vector<std::string> FanZoneExhaust::systemAvailabilityManagerCouplingModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Fan_ZoneExhaustFields::SystemAvailabilityManagerCouplingMode);
}

double FanZoneExhaust::fanTotalEfficiency() const {
  return getImpl<detail::FanZoneExhaust_Impl>()->fanTotalEfficiency();
}

double FanZoneExhaust::fanEfficiency() const {
  return getImpl<detail::FanZoneExhaust_Impl>()->fanTotalEfficiency();
}

bool FanZoneExhaust::setFanTotalEfficiency(double fanTotalEfficiency) {
  return getImpl<detail::FanZoneExhaust_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
}

bool FanZoneExhaust::setFanEfficiency(double fanTotalEfficiency) {
  return getImpl<detail::FanZoneExhaust_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
}

double FanZoneExhaust::pressureRise() const {
  return getImpl<detail::FanZoneExhaust_Impl>()->pressureRise();
}

bool FanZoneExhaust::setPressureRise(double pressureRise) {
  return getImpl<detail::FanZoneExhaust_Impl>()->setPressureRise(pressureRise);
}

boost::optional<double> FanZoneExhaust::maximumFlowRate() const {
  return getImpl<detail::FanZoneExhaust_Impl>()->maximumFlowRate();
}

bool FanZoneExhaust::setMaximumFlowRate(double maximumFlowRate) {
  return getImpl<detail::FanZoneExhaust_Impl>()->setMaximumFlowRate(maximumFlowRate);
}

void FanZoneExhaust::resetMaximumFlowRate() {
  getImpl<detail::FanZoneExhaust_Impl>()->resetMaximumFlowRate();
}

std::string FanZoneExhaust::endUseSubcategory() const {
  return getImpl<detail::FanZoneExhaust_Impl>()->endUseSubcategory();
}

bool FanZoneExhaust::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::FanZoneExhaust_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

std::string FanZoneExhaust::systemAvailabilityManagerCouplingMode() const {
  return getImpl<detail::FanZoneExhaust_Impl>()->systemAvailabilityManagerCouplingMode();
}

bool FanZoneExhaust::setSystemAvailabilityManagerCouplingMode(const std::string& systemAvailabilityManagerCouplingMode) {
  return getImpl<detail::FanZoneExhaust_Impl>()->setSystemAvailabilityManagerCouplingMode(systemAvailabilityManagerCouplingMode);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FanZoneExhaust_Impl::fanTotalEfficiency() const {
  const auto value = getDouble(openstudio::Fan_ZoneExhaustFields::FanTotalEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool FanZoneExhaust_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
  return setDouble(openstudio::Fan_ZoneExhaustFields::FanTotalEfficiency, fanTotalEfficiency);
}

double FanZoneExhaust_Impl::pressureRise() const {
  const auto value = getDouble(openstudio::Fan_ZoneExhaustFields::PressureRise, true);
  OS_ASSERT(value);
  return *value;
}

bool FanZoneExhaust_Impl::setPressureRise(double pressureRise) {
  const bool result = setDouble(openstudio::Fan_ZoneExhaustFields::PressureRise, pressureRise);
  OS_ASSERT(result);
  return result;
}

boost::optional<double> FanZoneExhaust_Impl::maximumFlowRate() const {
  return getDouble(openstudio::Fan_ZoneExhaustFields::MaximumFlowRate, true);
}

bool FanZoneExhaust_Impl::setMaximumFlowRate(double maximumFlowRate) {
  return setDouble(openstudio::Fan_ZoneExhaustFields::MaximumFlowRate, maximumFlowRate);
}

void FanZoneExhaust_Impl::resetMaximumFlowRate() {
  const bool result = setString(openstudio::Fan_ZoneExhaustFields::MaximumFlowRate, "");
  OS_ASSERT(result);
}

std::string FanZoneExhaust_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Fan_ZoneExhaustFields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool FanZoneExhaust_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Fan_ZoneExhaustFields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

std::string FanZoneExhaust_Impl::systemAvailabilityManagerCouplingMode() const {
  const auto value = getString(openstudio::Fan_ZoneExhaustFields::SystemAvailabilityManagerCouplingMode, true);
  OS_ASSERT(value);
  return *value;
}

bool FanZoneExhaust_Impl::setSystemAvailabilityManagerCouplingMode(const std::string& systemAvailabilityManagerCouplingMode) {
  return setString(openstudio::Fan_ZoneExhaustFields::SystemAvailabilityManagerCouplingMode, systemAvailabilityManagerCouplingMode);
}

std::vector<std::string> FanZoneExhaust_Impl::systemAvailabilityManagerCouplingModeValues() const {
  return openstudio::epmodel::FanZoneExhaust::systemAvailabilityManagerCouplingModeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
