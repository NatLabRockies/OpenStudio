/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingPeriodWeatherFileDays.hpp"
#include "SizingPeriodWeatherFileDays_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SizingPeriod_WeatherFileDays_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SizingPeriodWeatherFileDays::SizingPeriodWeatherFileDays(const Model& model) : ModelObject(SizingPeriodWeatherFileDays::iddObjectType(), model) {}

SizingPeriodWeatherFileDays::SizingPeriodWeatherFileDays(std::shared_ptr<detail::SizingPeriodWeatherFileDays_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType SizingPeriodWeatherFileDays::iddObjectType() {
  return IddObjectType::SizingPeriod_WeatherFileDays;
}

std::vector<std::string> SizingPeriodWeatherFileDays::dayofWeekforStartDayValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SizingPeriod_WeatherFileDaysFields::DayofWeekforStartDay);
}

int SizingPeriodWeatherFileDays::beginMonth() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->beginMonth();
}

bool SizingPeriodWeatherFileDays::setBeginMonth(int beginMonth) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setBeginMonth(beginMonth);
}

int SizingPeriodWeatherFileDays::beginDayofMonth() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->beginDayofMonth();
}

bool SizingPeriodWeatherFileDays::setBeginDayofMonth(int beginDayofMonth) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setBeginDayofMonth(beginDayofMonth);
}

int SizingPeriodWeatherFileDays::endMonth() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->endMonth();
}

bool SizingPeriodWeatherFileDays::setEndMonth(int endMonth) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setEndMonth(endMonth);
}

int SizingPeriodWeatherFileDays::endDayofMonth() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->endDayofMonth();
}

bool SizingPeriodWeatherFileDays::setEndDayofMonth(int endDayofMonth) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setEndDayofMonth(endDayofMonth);
}

std::string SizingPeriodWeatherFileDays::dayofWeekforStartDay() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->dayofWeekforStartDay();
}

bool SizingPeriodWeatherFileDays::setDayofWeekforStartDay(const std::string& dayofWeekforStartDay) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setDayofWeekforStartDay(dayofWeekforStartDay);
}

bool SizingPeriodWeatherFileDays::isDayofWeekforStartDayDefaulted() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->isDayofWeekforStartDayDefaulted();
}

void SizingPeriodWeatherFileDays::resetDayofWeekforStartDay() {
  getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->resetDayofWeekforStartDay();
}

bool SizingPeriodWeatherFileDays::useWeatherFileDaylightSavingPeriod() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->useWeatherFileDaylightSavingPeriod();
}

bool SizingPeriodWeatherFileDays::setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setUseWeatherFileDaylightSavingPeriod(useWeatherFileDaylightSavingPeriod);
}

bool SizingPeriodWeatherFileDays::isUseWeatherFileDaylightSavingPeriodDefaulted() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->isUseWeatherFileDaylightSavingPeriodDefaulted();
}

void SizingPeriodWeatherFileDays::resetUseWeatherFileDaylightSavingPeriod() {
  getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->resetUseWeatherFileDaylightSavingPeriod();
}

bool SizingPeriodWeatherFileDays::useWeatherFileRainandSnowIndicators() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->useWeatherFileRainandSnowIndicators();
}

bool SizingPeriodWeatherFileDays::setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators) {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->setUseWeatherFileRainandSnowIndicators(useWeatherFileRainandSnowIndicators);
}

bool SizingPeriodWeatherFileDays::isUseWeatherFileRainandSnowIndicatorsDefaulted() const {
  return getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->isUseWeatherFileRainandSnowIndicatorsDefaulted();
}

void SizingPeriodWeatherFileDays::resetUseWeatherFileRainandSnowIndicators() {
  getImpl<detail::SizingPeriodWeatherFileDays_Impl>()->resetUseWeatherFileRainandSnowIndicators();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int SizingPeriodWeatherFileDays_Impl::beginMonth() const {
  const auto value = getInt(openstudio::SizingPeriod_WeatherFileDaysFields::BeginMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileDays_Impl::setBeginMonth(int beginMonth) {
  const bool result = setInt(openstudio::SizingPeriod_WeatherFileDaysFields::BeginMonth, beginMonth);
  OS_ASSERT(result);
  return result;
}

int SizingPeriodWeatherFileDays_Impl::beginDayofMonth() const {
  const auto value = getInt(openstudio::SizingPeriod_WeatherFileDaysFields::BeginDayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileDays_Impl::setBeginDayofMonth(int beginDayofMonth) {
  const bool result = setInt(openstudio::SizingPeriod_WeatherFileDaysFields::BeginDayofMonth, beginDayofMonth);
  OS_ASSERT(result);
  return result;
}

int SizingPeriodWeatherFileDays_Impl::endMonth() const {
  const auto value = getInt(openstudio::SizingPeriod_WeatherFileDaysFields::EndMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileDays_Impl::setEndMonth(int endMonth) {
  const bool result = setInt(openstudio::SizingPeriod_WeatherFileDaysFields::EndMonth, endMonth);
  OS_ASSERT(result);
  return result;
}

int SizingPeriodWeatherFileDays_Impl::endDayofMonth() const {
  const auto value = getInt(openstudio::SizingPeriod_WeatherFileDaysFields::EndDayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileDays_Impl::setEndDayofMonth(int endDayofMonth) {
  const bool result = setInt(openstudio::SizingPeriod_WeatherFileDaysFields::EndDayofMonth, endDayofMonth);
  OS_ASSERT(result);
  return result;
}

std::string SizingPeriodWeatherFileDays_Impl::dayofWeekforStartDay() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileDaysFields::DayofWeekforStartDay, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileDays_Impl::setDayofWeekforStartDay(const std::string& dayofWeekforStartDay) {
  return setString(openstudio::SizingPeriod_WeatherFileDaysFields::DayofWeekforStartDay, dayofWeekforStartDay);
}

bool SizingPeriodWeatherFileDays_Impl::isDayofWeekforStartDayDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_WeatherFileDaysFields::DayofWeekforStartDay);
}

void SizingPeriodWeatherFileDays_Impl::resetDayofWeekforStartDay() {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileDaysFields::DayofWeekforStartDay, "");
  OS_ASSERT(result);
}

bool SizingPeriodWeatherFileDays_Impl::useWeatherFileDaylightSavingPeriod() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileDaylightSavingPeriod, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SizingPeriodWeatherFileDays_Impl::setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod) {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileDaylightSavingPeriod,
                                useWeatherFileDaylightSavingPeriod ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool SizingPeriodWeatherFileDays_Impl::isUseWeatherFileDaylightSavingPeriodDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileDaylightSavingPeriod);
}

void SizingPeriodWeatherFileDays_Impl::resetUseWeatherFileDaylightSavingPeriod() {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileDaylightSavingPeriod, "");
  OS_ASSERT(result);
}

bool SizingPeriodWeatherFileDays_Impl::useWeatherFileRainandSnowIndicators() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileRainandSnowIndicators, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SizingPeriodWeatherFileDays_Impl::setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators) {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileRainandSnowIndicators,
                                useWeatherFileRainandSnowIndicators ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool SizingPeriodWeatherFileDays_Impl::isUseWeatherFileRainandSnowIndicatorsDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileRainandSnowIndicators);
}

void SizingPeriodWeatherFileDays_Impl::resetUseWeatherFileRainandSnowIndicators() {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileDaysFields::UseWeatherFileRainandSnowIndicators, "");
  OS_ASSERT(result);
}

std::vector<std::string> SizingPeriodWeatherFileDays_Impl::dayofWeekforStartDayValues() const {
  return openstudio::epmodel::SizingPeriodWeatherFileDays::dayofWeekforStartDayValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
