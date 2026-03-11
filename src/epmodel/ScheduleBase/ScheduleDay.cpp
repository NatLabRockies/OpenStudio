/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleDay.hpp"
#include "ScheduleDay_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Schedule_Day_Interval_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ScheduleDay::ScheduleDay(const Model& model) : ModelObject(ScheduleDay::iddObjectType(), model) {}

ScheduleDay::ScheduleDay(std::shared_ptr<detail::ScheduleDay_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ScheduleDay::iddObjectType() {
  return IddObjectType::Schedule_Day_Interval;
}

std::vector<std::string> ScheduleDay::interpolatetoTimestepValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep);
}

std::string ScheduleDay::interpolatetoTimestep() const {
  return getImpl<detail::ScheduleDay_Impl>()->interpolatetoTimestep();
}

bool ScheduleDay::isInterpolatetoTimestepDefaulted() const {
  return getImpl<detail::ScheduleDay_Impl>()->isInterpolatetoTimestepDefaulted();
}

bool ScheduleDay::setInterpolatetoTimestep(const std::string& interpolatetoTimestep) {
  return getImpl<detail::ScheduleDay_Impl>()->setInterpolatetoTimestep(interpolatetoTimestep);
}

void ScheduleDay::resetInterpolatetoTimestep() {
  getImpl<detail::ScheduleDay_Impl>()->resetInterpolatetoTimestep();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ScheduleDay_Impl::interpolatetoTimestep() const {
  const auto value = getString(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep, true);
  OS_ASSERT(value);
  return *value;
}

bool ScheduleDay_Impl::isInterpolatetoTimestepDefaulted() const {
  return isEmpty(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep);
}

bool ScheduleDay_Impl::setInterpolatetoTimestep(const std::string& interpolatetoTimestep) {
  return setString(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep, interpolatetoTimestep);
}

void ScheduleDay_Impl::resetInterpolatetoTimestep() {
  const bool result = setString(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep, "");
  OS_ASSERT(result);
}

std::vector<std::string> ScheduleDay_Impl::interpolatetoTimestepValues() const {
  return openstudio::epmodel::ScheduleDay::interpolatetoTimestepValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
