/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SizingPeriodWeatherFileConditionType.hpp"
#include "SizingPeriodWeatherFileConditionType_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SizingPeriod_WeatherFileConditionType_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SizingPeriodWeatherFileConditionType::SizingPeriodWeatherFileConditionType(const Model& model)
  : ModelObject(SizingPeriodWeatherFileConditionType::iddObjectType(), model) {}

SizingPeriodWeatherFileConditionType::SizingPeriodWeatherFileConditionType(
  std::shared_ptr<detail::SizingPeriodWeatherFileConditionType_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SizingPeriodWeatherFileConditionType::iddObjectType() {
  return IddObjectType::SizingPeriod_WeatherFileConditionType;
}

std::vector<std::string> SizingPeriodWeatherFileConditionType::periodSelectionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SizingPeriod_WeatherFileConditionTypeFields::PeriodSelection);
}

std::vector<std::string> SizingPeriodWeatherFileConditionType::dayofWeekforStartDayValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SizingPeriod_WeatherFileConditionTypeFields::DayofWeekforStartDay);
}

std::string SizingPeriodWeatherFileConditionType::periodSelection() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->periodSelection();
}

bool SizingPeriodWeatherFileConditionType::setPeriodSelection(const std::string& periodSelection) {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->setPeriodSelection(periodSelection);
}

std::string SizingPeriodWeatherFileConditionType::dayofWeekforStartDay() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->dayofWeekforStartDay();
}

bool SizingPeriodWeatherFileConditionType::setDayofWeekforStartDay(const std::string& dayofWeekforStartDay) {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->setDayofWeekforStartDay(dayofWeekforStartDay);
}

bool SizingPeriodWeatherFileConditionType::isDayofWeekforStartDayDefaulted() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->isDayofWeekforStartDayDefaulted();
}

void SizingPeriodWeatherFileConditionType::resetDayofWeekforStartDay() {
  getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->resetDayofWeekforStartDay();
}

bool SizingPeriodWeatherFileConditionType::useWeatherFileDaylightSavingPeriod() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->useWeatherFileDaylightSavingPeriod();
}

bool SizingPeriodWeatherFileConditionType::setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod) {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->setUseWeatherFileDaylightSavingPeriod(
    useWeatherFileDaylightSavingPeriod);
}

bool SizingPeriodWeatherFileConditionType::isUseWeatherFileDaylightSavingPeriodDefaulted() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->isUseWeatherFileDaylightSavingPeriodDefaulted();
}

void SizingPeriodWeatherFileConditionType::resetUseWeatherFileDaylightSavingPeriod() {
  getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->resetUseWeatherFileDaylightSavingPeriod();
}

bool SizingPeriodWeatherFileConditionType::useWeatherFileRainandSnowIndicators() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->useWeatherFileRainandSnowIndicators();
}

bool SizingPeriodWeatherFileConditionType::setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators) {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->setUseWeatherFileRainandSnowIndicators(
    useWeatherFileRainandSnowIndicators);
}

bool SizingPeriodWeatherFileConditionType::isUseWeatherFileRainandSnowIndicatorsDefaulted() const {
  return getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->isUseWeatherFileRainandSnowIndicatorsDefaulted();
}

void SizingPeriodWeatherFileConditionType::resetUseWeatherFileRainandSnowIndicators() {
  getImpl<detail::SizingPeriodWeatherFileConditionType_Impl>()->resetUseWeatherFileRainandSnowIndicators();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string SizingPeriodWeatherFileConditionType_Impl::periodSelection() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::PeriodSelection, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileConditionType_Impl::setPeriodSelection(const std::string& periodSelection) {
  return setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::PeriodSelection, periodSelection);
}

std::string SizingPeriodWeatherFileConditionType_Impl::dayofWeekforStartDay() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::DayofWeekforStartDay, true);
  OS_ASSERT(value);
  return *value;
}

bool SizingPeriodWeatherFileConditionType_Impl::setDayofWeekforStartDay(const std::string& dayofWeekforStartDay) {
  return setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::DayofWeekforStartDay, dayofWeekforStartDay);
}

bool SizingPeriodWeatherFileConditionType_Impl::isDayofWeekforStartDayDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_WeatherFileConditionTypeFields::DayofWeekforStartDay);
}

void SizingPeriodWeatherFileConditionType_Impl::resetDayofWeekforStartDay() {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::DayofWeekforStartDay, "");
  OS_ASSERT(result);
}

bool SizingPeriodWeatherFileConditionType_Impl::useWeatherFileDaylightSavingPeriod() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileDaylightSavingPeriod, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SizingPeriodWeatherFileConditionType_Impl::setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod) {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileDaylightSavingPeriod,
                                useWeatherFileDaylightSavingPeriod ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool SizingPeriodWeatherFileConditionType_Impl::isUseWeatherFileDaylightSavingPeriodDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileDaylightSavingPeriod);
}

void SizingPeriodWeatherFileConditionType_Impl::resetUseWeatherFileDaylightSavingPeriod() {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileDaylightSavingPeriod, "");
  OS_ASSERT(result);
}

bool SizingPeriodWeatherFileConditionType_Impl::useWeatherFileRainandSnowIndicators() const {
  const auto value = getString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileRainandSnowIndicators, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool SizingPeriodWeatherFileConditionType_Impl::setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators) {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileRainandSnowIndicators,
                                useWeatherFileRainandSnowIndicators ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

bool SizingPeriodWeatherFileConditionType_Impl::isUseWeatherFileRainandSnowIndicatorsDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileRainandSnowIndicators);
}

void SizingPeriodWeatherFileConditionType_Impl::resetUseWeatherFileRainandSnowIndicators() {
  const bool result = setString(openstudio::SizingPeriod_WeatherFileConditionTypeFields::UseWeatherFileRainandSnowIndicators, "");
  OS_ASSERT(result);
}

std::vector<std::string> SizingPeriodWeatherFileConditionType_Impl::periodSelectionValues() const {
  return openstudio::epmodel::SizingPeriodWeatherFileConditionType::periodSelectionValues();
}

std::vector<std::string> SizingPeriodWeatherFileConditionType_Impl::dayofWeekforStartDayValues() const {
  return openstudio::epmodel::SizingPeriodWeatherFileConditionType::dayofWeekforStartDayValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
