/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/RunPeriod.hpp"
#include "ParentObject/RunPeriod_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RunPeriod_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

RunPeriod::RunPeriod(const Model& model) : ParentObject(RunPeriod::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::RunPeriod_Impl>());
  OS_ASSERT(setBeginMonth(1));
  OS_ASSERT(setBeginDayOfMonth(1));
  OS_ASSERT(setEndMonth(12));
  OS_ASSERT(setEndDayOfMonth(31));
}

RunPeriod::RunPeriod(std::shared_ptr<detail::RunPeriod_Impl> impl) : ParentObject(std::move(impl)) {}

IddObjectType RunPeriod::iddObjectType() {
  return IddObjectType::RunPeriod;
}

int RunPeriod::getBeginMonth() const {
  return getImpl<detail::RunPeriod_Impl>()->getBeginMonth();
}

int RunPeriod::getBeginDayOfMonth() const {
  return getImpl<detail::RunPeriod_Impl>()->getBeginDayOfMonth();
}

int RunPeriod::getEndMonth() const {
  return getImpl<detail::RunPeriod_Impl>()->getEndMonth();
}

int RunPeriod::getEndDayOfMonth() const {
  return getImpl<detail::RunPeriod_Impl>()->getEndDayOfMonth();
}

bool RunPeriod::getUseWeatherFileHolidays() const {
  return getImpl<detail::RunPeriod_Impl>()->getUseWeatherFileHolidays();
}

bool RunPeriod::getUseWeatherFileDaylightSavings() const {
  return getImpl<detail::RunPeriod_Impl>()->getUseWeatherFileDaylightSavings();
}

bool RunPeriod::getApplyWeekendHolidayRule() const {
  return getImpl<detail::RunPeriod_Impl>()->getApplyWeekendHolidayRule();
}

bool RunPeriod::getUseWeatherFileRainInd() const {
  return getImpl<detail::RunPeriod_Impl>()->getUseWeatherFileRainInd();
}

bool RunPeriod::getUseWeatherFileSnowInd() const {
  return getImpl<detail::RunPeriod_Impl>()->getUseWeatherFileSnowInd();
}

int RunPeriod::getNumTimePeriodRepeats() const {
  return getImpl<detail::RunPeriod_Impl>()->getNumTimePeriodRepeats();
}

bool RunPeriod::setBeginMonth(int month) {
  return getImpl<detail::RunPeriod_Impl>()->setBeginMonth(month);
}

bool RunPeriod::setBeginDayOfMonth(int day) {
  return getImpl<detail::RunPeriod_Impl>()->setBeginDayOfMonth(day);
}

bool RunPeriod::setEndMonth(int month) {
  return getImpl<detail::RunPeriod_Impl>()->setEndMonth(month);
}

bool RunPeriod::setEndDayOfMonth(int day) {
  return getImpl<detail::RunPeriod_Impl>()->setEndDayOfMonth(day);
}

bool RunPeriod::setUseWeatherFileHolidays(bool use) {
  return getImpl<detail::RunPeriod_Impl>()->setUseWeatherFileHolidays(use);
}

bool RunPeriod::setUseWeatherFileDaylightSavings(bool use) {
  return getImpl<detail::RunPeriod_Impl>()->setUseWeatherFileDaylightSavings(use);
}

bool RunPeriod::setApplyWeekendHolidayRule(bool apply) {
  return getImpl<detail::RunPeriod_Impl>()->setApplyWeekendHolidayRule(apply);
}

bool RunPeriod::setUseWeatherFileRainInd(bool rainInd) {
  return getImpl<detail::RunPeriod_Impl>()->setUseWeatherFileRainInd(rainInd);
}

bool RunPeriod::setUseWeatherFileSnowInd(bool snowInd) {
  return getImpl<detail::RunPeriod_Impl>()->setUseWeatherFileSnowInd(snowInd);
}

bool RunPeriod::setNumTimePeriodRepeats(int numRepeats) {
  return getImpl<detail::RunPeriod_Impl>()->setNumTimePeriodRepeats(numRepeats);
}

void RunPeriod::ensureNoLeapDays() {
  getImpl<detail::RunPeriod_Impl>()->ensureNoLeapDays();
}

bool RunPeriod::isAnnual() const {
  return getImpl<detail::RunPeriod_Impl>()->isAnnual();
}

bool RunPeriod::isPartialYear() const {
  return getImpl<detail::RunPeriod_Impl>()->isPartialYear();
}

bool RunPeriod::isRepeated() const {
  return getImpl<detail::RunPeriod_Impl>()->isRepeated();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int RunPeriod_Impl::getBeginMonth() const {
  const auto value = getInt(openstudio::RunPeriodFields::BeginMonth, true);
  OS_ASSERT(value);
  return *value;
}

int RunPeriod_Impl::getBeginDayOfMonth() const {
  const auto value = getInt(openstudio::RunPeriodFields::BeginDayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

int RunPeriod_Impl::getEndMonth() const {
  const auto value = getInt(openstudio::RunPeriodFields::EndMonth, true);
  OS_ASSERT(value);
  return *value;
}

int RunPeriod_Impl::getEndDayOfMonth() const {
  const auto value = getInt(openstudio::RunPeriodFields::EndDayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool RunPeriod_Impl::getUseWeatherFileHolidays() const {
  const auto value = getString(openstudio::RunPeriodFields::UseWeatherFileHolidaysandSpecialDays, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool RunPeriod_Impl::getUseWeatherFileDaylightSavings() const {
  const auto value = getString(openstudio::RunPeriodFields::UseWeatherFileDaylightSavingPeriod, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool RunPeriod_Impl::getApplyWeekendHolidayRule() const {
  const auto value = getString(openstudio::RunPeriodFields::ApplyWeekendHolidayRule, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool RunPeriod_Impl::getUseWeatherFileRainInd() const {
  const auto value = getString(openstudio::RunPeriodFields::UseWeatherFileRainIndicators, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool RunPeriod_Impl::getUseWeatherFileSnowInd() const {
  const auto value = getString(openstudio::RunPeriodFields::UseWeatherFileSnowIndicators, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

int RunPeriod_Impl::getNumTimePeriodRepeats() const {
  const auto beginYear = getInt(openstudio::RunPeriodFields::BeginYear, false);
  const auto endYear = getInt(openstudio::RunPeriodFields::EndYear, false);
  if (!beginYear || !endYear) {
    return 1;
  }

  const bool wrapsYear = (getEndMonth() < getBeginMonth()) || ((getEndMonth() == getBeginMonth()) && (getEndDayOfMonth() < getBeginDayOfMonth()));
  const int repeats = wrapsYear ? (*endYear - *beginYear) : (*endYear - *beginYear + 1);
  return repeats > 0 ? repeats : 1;
}

bool RunPeriod_Impl::setBeginMonth(int month) {
  return setInt(openstudio::RunPeriodFields::BeginMonth, month);
}

bool RunPeriod_Impl::setBeginDayOfMonth(int day) {
  return setInt(openstudio::RunPeriodFields::BeginDayofMonth, day);
}

bool RunPeriod_Impl::setEndMonth(int month) {
  return setInt(openstudio::RunPeriodFields::EndMonth, month);
}

bool RunPeriod_Impl::setEndDayOfMonth(int day) {
  return setInt(openstudio::RunPeriodFields::EndDayofMonth, day);
}

bool RunPeriod_Impl::setUseWeatherFileHolidays(bool use) {
  const bool result = setString(openstudio::RunPeriodFields::UseWeatherFileHolidaysandSpecialDays, use ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool RunPeriod_Impl::setUseWeatherFileDaylightSavings(bool use) {
  const bool result = setString(openstudio::RunPeriodFields::UseWeatherFileDaylightSavingPeriod, use ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool RunPeriod_Impl::setApplyWeekendHolidayRule(bool apply) {
  const bool result = setString(openstudio::RunPeriodFields::ApplyWeekendHolidayRule, apply ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool RunPeriod_Impl::setUseWeatherFileRainInd(bool rainInd) {
  const bool result = setString(openstudio::RunPeriodFields::UseWeatherFileRainIndicators, rainInd ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool RunPeriod_Impl::setUseWeatherFileSnowInd(bool snowInd) {
  const bool result = setString(openstudio::RunPeriodFields::UseWeatherFileSnowIndicators, snowInd ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool RunPeriod_Impl::setNumTimePeriodRepeats(int numRepeats) {
  if (numRepeats < 1) {
    return false;
  }

  const bool wrapsYear = (getEndMonth() < getBeginMonth()) || ((getEndMonth() == getBeginMonth()) && (getEndDayOfMonth() < getBeginDayOfMonth()));
  const int beginYear = getInt(openstudio::RunPeriodFields::BeginYear, false).get_value_or(2009);
  const int endYear = wrapsYear ? (beginYear + numRepeats) : (beginYear + numRepeats - 1);

  bool result = setInt(openstudio::RunPeriodFields::BeginYear, beginYear);
  result = setInt(openstudio::RunPeriodFields::EndYear, endYear) && result;
  return result;
}

void RunPeriod_Impl::ensureNoLeapDays() {
  if ((getBeginMonth() == 2) && (getBeginDayOfMonth() == 29)) {
    OS_ASSERT(setBeginDayOfMonth(28));
  }

  if ((getEndMonth() == 2) && (getEndDayOfMonth() == 29)) {
    OS_ASSERT(setEndDayOfMonth(28));
  }
}

bool RunPeriod_Impl::isAnnual() const {
  return (getBeginMonth() == 1) && (getBeginDayOfMonth() == 1) && (getEndMonth() == 12) && (getEndDayOfMonth() == 31);
}

bool RunPeriod_Impl::isPartialYear() const {
  return !isAnnual();
}

bool RunPeriod_Impl::isRepeated() const {
  return (getNumTimePeriodRepeats() > 1);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
