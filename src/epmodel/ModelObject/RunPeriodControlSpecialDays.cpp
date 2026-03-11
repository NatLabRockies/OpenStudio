/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RunPeriodControlSpecialDays.hpp"
#include "RunPeriodControlSpecialDays_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RunPeriodControl_SpecialDays_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

RunPeriodControlSpecialDays::RunPeriodControlSpecialDays(const Model& model)
  : ModelObject(RunPeriodControlSpecialDays::iddObjectType(), model) {
  OS_ASSERT(setStartDate("1/1"));
  OS_ASSERT(setDuration(1));

  const auto values = specialDayTypeValues();
  if (!values.empty()) {
    OS_ASSERT(setSpecialDayType(values.front()));
  }
}

RunPeriodControlSpecialDays::RunPeriodControlSpecialDays(std::shared_ptr<detail::RunPeriodControlSpecialDays_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RunPeriodControlSpecialDays::iddObjectType() {
  return IddObjectType::RunPeriodControl_SpecialDays;
}

std::vector<std::string> RunPeriodControlSpecialDays::specialDayTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RunPeriodControl_SpecialDaysFields::SpecialDayType);
}

std::vector<std::string> RunPeriodControlSpecialDays::validSpecialDayTypeValues() {
  return specialDayTypeValues();
}

std::string RunPeriodControlSpecialDays::startDate() const {
  return getImpl<detail::RunPeriodControlSpecialDays_Impl>()->startDate();
}

unsigned RunPeriodControlSpecialDays::duration() const {
  return getImpl<detail::RunPeriodControlSpecialDays_Impl>()->duration();
}

std::string RunPeriodControlSpecialDays::specialDayType() const {
  return getImpl<detail::RunPeriodControlSpecialDays_Impl>()->specialDayType();
}

bool RunPeriodControlSpecialDays::setStartDate(const std::string& startDate) {
  return getImpl<detail::RunPeriodControlSpecialDays_Impl>()->setStartDate(startDate);
}

bool RunPeriodControlSpecialDays::setDuration(unsigned duration) {
  return getImpl<detail::RunPeriodControlSpecialDays_Impl>()->setDuration(duration);
}

bool RunPeriodControlSpecialDays::setSpecialDayType(const std::string& specialDayType) {
  return getImpl<detail::RunPeriodControlSpecialDays_Impl>()->setSpecialDayType(specialDayType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string RunPeriodControlSpecialDays_Impl::startDate() const {
  const auto value = getString(openstudio::RunPeriodControl_SpecialDaysFields::StartDate, true);
  OS_ASSERT(value);
  return *value;
}

unsigned RunPeriodControlSpecialDays_Impl::duration() const {
  const auto value = getUnsigned(openstudio::RunPeriodControl_SpecialDaysFields::Duration, true);
  OS_ASSERT(value);
  return *value;
}

std::string RunPeriodControlSpecialDays_Impl::specialDayType() const {
  const auto value = getString(openstudio::RunPeriodControl_SpecialDaysFields::SpecialDayType, true);
  OS_ASSERT(value);
  return *value;
}

bool RunPeriodControlSpecialDays_Impl::setStartDate(const std::string& startDate) {
  return setString(openstudio::RunPeriodControl_SpecialDaysFields::StartDate, startDate);
}

bool RunPeriodControlSpecialDays_Impl::setDuration(unsigned duration) {
  return setUnsigned(openstudio::RunPeriodControl_SpecialDaysFields::Duration, duration);
}

bool RunPeriodControlSpecialDays_Impl::setSpecialDayType(const std::string& specialDayType) {
  return setString(openstudio::RunPeriodControl_SpecialDaysFields::SpecialDayType, specialDayType);
}

std::vector<std::string> RunPeriodControlSpecialDays_Impl::specialDayTypeValues() const {
  return openstudio::epmodel::RunPeriodControlSpecialDays::specialDayTypeValues();
}

std::vector<std::string> RunPeriodControlSpecialDays_Impl::validSpecialDayTypeValues() const {
  return openstudio::epmodel::RunPeriodControlSpecialDays::validSpecialDayTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
