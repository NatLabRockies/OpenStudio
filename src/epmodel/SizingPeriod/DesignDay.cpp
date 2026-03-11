/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DesignDay.hpp"
#include "DesignDay_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SizingPeriod_DesignDay_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

DesignDay::DesignDay(const Model& model) : ModelObject(DesignDay::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::DesignDay_Impl>());
  OS_ASSERT(setWetBulbOrDewPointAtMaximumDryBulb(23.0));
}

DesignDay::DesignDay(std::shared_ptr<detail::DesignDay_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DesignDay::iddObjectType() {
  return IddObjectType::SizingPeriod_DesignDay;
}

std::vector<std::string> DesignDay::validDayTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SizingPeriod_DesignDayFields::DayType);
}

std::vector<std::string> DesignDay::validHumidityIndicatingTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SizingPeriod_DesignDayFields::HumidityConditionType);
}

std::vector<std::string> DesignDay::validHumidityConditionTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SizingPeriod_DesignDayFields::HumidityConditionType);
}

std::vector<std::string> DesignDay::validDryBulbTemperatureRangeModifierTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType);
}

std::vector<std::string> DesignDay::validSolarModelIndicatorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SizingPeriod_DesignDayFields::SolarModelIndicator);
}

std::vector<std::string> DesignDay::validBeginEnvironmentResetModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SizingPeriod_DesignDayFields::BeginEnvironmentResetMode);
}

double DesignDay::maximumDryBulbTemperature() const {
  return getImpl<detail::DesignDay_Impl>()->maximumDryBulbTemperature();
}

bool DesignDay::isMaximumDryBulbTemperatureDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isMaximumDryBulbTemperatureDefaulted();
}

double DesignDay::dailyDryBulbTemperatureRange() const {
  return getImpl<detail::DesignDay_Impl>()->dailyDryBulbTemperatureRange();
}

bool DesignDay::isDailyDryBulbTemperatureRangeDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isDailyDryBulbTemperatureRangeDefaulted();
}

double DesignDay::humidityIndicatingConditionsAtMaximumDryBulb() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::HumidityConditionType, true);
  OS_ASSERT(value);

  const std::string humidityConditionType = *value;
  if (openstudio::istringEqual(humidityConditionType, "WetBulb") || openstudio::istringEqual(humidityConditionType, "DewPoint")
      || openstudio::istringEqual(humidityConditionType, "WetBulbProfileMultiplierSchedule")
      || openstudio::istringEqual(humidityConditionType, "WetBulbProfileDifferenceSchedule")
      || openstudio::istringEqual(humidityConditionType, "WetBulbProfileDefaultMultipliers")) {
    auto v = getImpl<detail::DesignDay_Impl>()->wetBulbOrDewPointAtMaximumDryBulb();
    OS_ASSERT(v);
    return *v;
  }

  if (openstudio::istringEqual(humidityConditionType, "HumidityRatio")) {
    auto v = getImpl<detail::DesignDay_Impl>()->humidityRatioAtMaximumDryBulb();
    OS_ASSERT(v);
    return *v;
  }

  if (openstudio::istringEqual(humidityConditionType, "Enthalpy")) {
    auto v = getImpl<detail::DesignDay_Impl>()->enthalpyAtMaximumDryBulb();
    OS_ASSERT(v);
    return *v;
  }

  return 0.0;
}

bool DesignDay::isHumidityIndicatingConditionsAtMaximumDryBulbDefaulted() const {
  const bool wetBulbOrDewPointAtMaximumDryBulb = isEmpty(openstudio::SizingPeriod_DesignDayFields::WetbulborDewPointatMaximumDryBulb);
  const bool humidityRatioAtMaximumDryBulb = isEmpty(openstudio::SizingPeriod_DesignDayFields::HumidityRatioatMaximumDryBulb);
  const bool enthalpyAtMaximumDryBulb = isEmpty(openstudio::SizingPeriod_DesignDayFields::EnthalpyatMaximumDryBulb);
  return wetBulbOrDewPointAtMaximumDryBulb && humidityRatioAtMaximumDryBulb && enthalpyAtMaximumDryBulb;
}

double DesignDay::barometricPressure() const {
  return getImpl<detail::DesignDay_Impl>()->barometricPressure();
}

bool DesignDay::isBarometricPressureDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isBarometricPressureDefaulted();
}

double DesignDay::windSpeed() const {
  return getImpl<detail::DesignDay_Impl>()->windSpeed();
}

bool DesignDay::isWindSpeedDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isWindSpeedDefaulted();
}

double DesignDay::windDirection() const {
  return getImpl<detail::DesignDay_Impl>()->windDirection();
}

bool DesignDay::isWindDirectionDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isWindDirectionDefaulted();
}

double DesignDay::skyClearness() const {
  return getImpl<detail::DesignDay_Impl>()->skyClearness();
}

bool DesignDay::isSkyClearnessDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isSkyClearnessDefaulted();
}

bool DesignDay::rainIndicator() const {
  return getImpl<detail::DesignDay_Impl>()->rainIndicator();
}

bool DesignDay::isRainIndicatorDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isRainIndicatorDefaulted();
}

bool DesignDay::snowIndicator() const {
  return getImpl<detail::DesignDay_Impl>()->snowIndicator();
}

bool DesignDay::isSnowIndicatorDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isSnowIndicatorDefaulted();
}

int DesignDay::dayOfMonth() const {
  return getImpl<detail::DesignDay_Impl>()->dayOfMonth();
}

bool DesignDay::isDayOfMonthDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isDayOfMonthDefaulted();
}

int DesignDay::month() const {
  return getImpl<detail::DesignDay_Impl>()->month();
}

bool DesignDay::isMonthDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isMonthDefaulted();
}

std::string DesignDay::dayType() const {
  return getImpl<detail::DesignDay_Impl>()->dayType();
}

bool DesignDay::isDayTypeDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isDayTypeDefaulted();
}

bool DesignDay::daylightSavingTimeIndicator() const {
  return getImpl<detail::DesignDay_Impl>()->daylightSavingTimeIndicator();
}

bool DesignDay::isDaylightSavingTimeIndicatorDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isDaylightSavingTimeIndicatorDefaulted();
}

std::string DesignDay::humidityIndicatingType() const {
  return getImpl<detail::DesignDay_Impl>()->humidityConditionType();
}

std::string DesignDay::humidityConditionType() const {
  return getImpl<detail::DesignDay_Impl>()->humidityConditionType();
}

bool DesignDay::isHumidityIndicatingTypeDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isHumidityConditionTypeDefaulted();
}

bool DesignDay::isHumidityConditionTypeDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isHumidityConditionTypeDefaulted();
}

boost::optional<double> DesignDay::wetBulbOrDewPointAtMaximumDryBulb() const {
  return getImpl<detail::DesignDay_Impl>()->wetBulbOrDewPointAtMaximumDryBulb();
}

boost::optional<double> DesignDay::humidityRatioAtMaximumDryBulb() const {
  return getImpl<detail::DesignDay_Impl>()->humidityRatioAtMaximumDryBulb();
}

boost::optional<double> DesignDay::enthalpyAtMaximumDryBulb() const {
  return getImpl<detail::DesignDay_Impl>()->enthalpyAtMaximumDryBulb();
}

std::string DesignDay::dryBulbTemperatureRangeModifierType() const {
  return getImpl<detail::DesignDay_Impl>()->dryBulbTemperatureRangeModifierType();
}

bool DesignDay::isDryBulbTemperatureRangeModifierTypeDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isDryBulbTemperatureRangeModifierTypeDefaulted();
}

std::string DesignDay::solarModelIndicator() const {
  return getImpl<detail::DesignDay_Impl>()->solarModelIndicator();
}

bool DesignDay::isSolarModelIndicatorDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isSolarModelIndicatorDefaulted();
}

double DesignDay::ashraeTaub() const {
  return getImpl<detail::DesignDay_Impl>()->ashraeClearSkyOpticalDepthForBeamIrradiance();
}

double DesignDay::ashraeClearSkyOpticalDepthForBeamIrradiance() const {
  return getImpl<detail::DesignDay_Impl>()->ashraeClearSkyOpticalDepthForBeamIrradiance();
}

bool DesignDay::isAshraeTaubDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted();
}

bool DesignDay::isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted();
}

double DesignDay::ashraeTaud() const {
  return getImpl<detail::DesignDay_Impl>()->ashraeClearSkyOpticalDepthForDiffuseIrradiance();
}

double DesignDay::ashraeClearSkyOpticalDepthForDiffuseIrradiance() const {
  return getImpl<detail::DesignDay_Impl>()->ashraeClearSkyOpticalDepthForDiffuseIrradiance();
}

bool DesignDay::isAshraeTaudDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted();
}

bool DesignDay::isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted();
}

boost::optional<double> DesignDay::dailyWetBulbTemperatureRange() const {
  return getImpl<detail::DesignDay_Impl>()->dailyWetBulbTemperatureRange();
}

boost::optional<int> DesignDay::maximumNumberWarmupDays() const {
  return getImpl<detail::DesignDay_Impl>()->maximumNumberWarmupDays();
}

std::string DesignDay::beginEnvironmentResetMode() const {
  return getImpl<detail::DesignDay_Impl>()->beginEnvironmentResetMode();
}

bool DesignDay::isBeginEnvironmentResetModeDefaulted() const {
  return getImpl<detail::DesignDay_Impl>()->isBeginEnvironmentResetModeDefaulted();
}

bool DesignDay::setMaximumDryBulbTemperature(double maximumDryBulbTemperature) {
  return getImpl<detail::DesignDay_Impl>()->setMaximumDryBulbTemperature(maximumDryBulbTemperature);
}

void DesignDay::resetMaximumDryBulbTemperature() {
  getImpl<detail::DesignDay_Impl>()->resetMaximumDryBulbTemperature();
}

bool DesignDay::setDailyDryBulbTemperatureRange(double dailyDryBulbTemperatureRange) {
  return getImpl<detail::DesignDay_Impl>()->setDailyDryBulbTemperatureRange(dailyDryBulbTemperatureRange);
}

void DesignDay::resetDailyDryBulbTemperatureRange() {
  getImpl<detail::DesignDay_Impl>()->resetDailyDryBulbTemperatureRange();
}

bool DesignDay::setHumidityIndicatingConditionsAtMaximumDryBulb(double humidityIndicatingConditionsAtMaximumDryBulb) {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::HumidityConditionType, true);
  OS_ASSERT(value);

  const std::string humidityConditionType = *value;
  if (openstudio::istringEqual(humidityConditionType, "WetBulb") || openstudio::istringEqual(humidityConditionType, "DewPoint")
      || openstudio::istringEqual(humidityConditionType, "WetBulbProfileMultiplierSchedule")
      || openstudio::istringEqual(humidityConditionType, "WetBulbProfileDifferenceSchedule")
      || openstudio::istringEqual(humidityConditionType, "WetBulbProfileDefaultMultipliers")) {
    return getImpl<detail::DesignDay_Impl>()->setWetBulbOrDewPointAtMaximumDryBulb(humidityIndicatingConditionsAtMaximumDryBulb);
  }

  if (openstudio::istringEqual(humidityConditionType, "HumidityRatio")) {
    return getImpl<detail::DesignDay_Impl>()->setHumidityRatioAtMaximumDryBulb(humidityIndicatingConditionsAtMaximumDryBulb);
  }

  if (openstudio::istringEqual(humidityConditionType, "Enthalpy")) {
    return getImpl<detail::DesignDay_Impl>()->setEnthalpyAtMaximumDryBulb(humidityIndicatingConditionsAtMaximumDryBulb);
  }

  return false;
}

void DesignDay::resetHumidityIndicatingConditionsAtMaximumDryBulb() {
  getImpl<detail::DesignDay_Impl>()->resetWetBulbOrDewPointAtMaximumDryBulb();
  getImpl<detail::DesignDay_Impl>()->resetHumidityRatioAtMaximumDryBulb();
  getImpl<detail::DesignDay_Impl>()->resetEnthalpyAtMaximumDryBulb();
}

bool DesignDay::setBarometricPressure(double barometricPressure) {
  return getImpl<detail::DesignDay_Impl>()->setBarometricPressure(barometricPressure);
}

void DesignDay::resetBarometricPressure() {
  getImpl<detail::DesignDay_Impl>()->resetBarometricPressure();
}

bool DesignDay::setWindSpeed(double windSpeed) {
  return getImpl<detail::DesignDay_Impl>()->setWindSpeed(windSpeed);
}

void DesignDay::resetWindSpeed() {
  getImpl<detail::DesignDay_Impl>()->resetWindSpeed();
}

bool DesignDay::setWindDirection(double windDirection) {
  return getImpl<detail::DesignDay_Impl>()->setWindDirection(windDirection);
}

void DesignDay::resetWindDirection() {
  getImpl<detail::DesignDay_Impl>()->resetWindDirection();
}

bool DesignDay::setSkyClearness(double skyClearness) {
  return getImpl<detail::DesignDay_Impl>()->setSkyClearness(skyClearness);
}

void DesignDay::resetSkyClearness() {
  getImpl<detail::DesignDay_Impl>()->resetSkyClearness();
}

bool DesignDay::setRainIndicator(bool rainIndicator) {
  return getImpl<detail::DesignDay_Impl>()->setRainIndicator(rainIndicator);
}

void DesignDay::resetRainIndicator() {
  getImpl<detail::DesignDay_Impl>()->resetRainIndicator();
}

bool DesignDay::setSnowIndicator(bool snowIndicator) {
  return getImpl<detail::DesignDay_Impl>()->setSnowIndicator(snowIndicator);
}

void DesignDay::resetSnowIndicator() {
  getImpl<detail::DesignDay_Impl>()->resetSnowIndicator();
}

bool DesignDay::setDayOfMonth(int dayOfMonth) {
  return getImpl<detail::DesignDay_Impl>()->setDayOfMonth(dayOfMonth);
}

void DesignDay::resetDayOfMonth() {
  getImpl<detail::DesignDay_Impl>()->resetDayOfMonth();
}

bool DesignDay::setMonth(int month) {
  return getImpl<detail::DesignDay_Impl>()->setMonth(month);
}

void DesignDay::resetMonth() {
  getImpl<detail::DesignDay_Impl>()->resetMonth();
}

bool DesignDay::setDayType(const std::string& dayType) {
  return getImpl<detail::DesignDay_Impl>()->setDayType(dayType);
}

void DesignDay::resetDayType() {
  getImpl<detail::DesignDay_Impl>()->resetDayType();
}

bool DesignDay::setDaylightSavingTimeIndicator(bool daylightSavingTimeIndicator) {
  return getImpl<detail::DesignDay_Impl>()->setDaylightSavingTimeIndicator(daylightSavingTimeIndicator);
}

void DesignDay::resetDaylightSavingTimeIndicator() {
  getImpl<detail::DesignDay_Impl>()->resetDaylightSavingTimeIndicator();
}

bool DesignDay::setHumidityIndicatingType(const std::string& humidityIndicatingType) {
  return getImpl<detail::DesignDay_Impl>()->setHumidityConditionType(humidityIndicatingType);
}

bool DesignDay::setHumidityConditionType(const std::string& humidityConditionType) {
  return getImpl<detail::DesignDay_Impl>()->setHumidityConditionType(humidityConditionType);
}

void DesignDay::resetHumidityIndicatingType() {
  getImpl<detail::DesignDay_Impl>()->resetHumidityConditionType();
}

void DesignDay::resetHumidityConditionType() {
  getImpl<detail::DesignDay_Impl>()->resetHumidityConditionType();
}

bool DesignDay::setWetBulbOrDewPointAtMaximumDryBulb(double wetBulbOrDewPointAtMaximumDryBulb) {
  return getImpl<detail::DesignDay_Impl>()->setWetBulbOrDewPointAtMaximumDryBulb(wetBulbOrDewPointAtMaximumDryBulb);
}

void DesignDay::resetWetBulbOrDewPointAtMaximumDryBulb() {
  getImpl<detail::DesignDay_Impl>()->resetWetBulbOrDewPointAtMaximumDryBulb();
}

bool DesignDay::setHumidityRatioAtMaximumDryBulb(double humidityRatioAtMaximumDryBulb) {
  return getImpl<detail::DesignDay_Impl>()->setHumidityRatioAtMaximumDryBulb(humidityRatioAtMaximumDryBulb);
}

void DesignDay::resetHumidityRatioAtMaximumDryBulb() {
  getImpl<detail::DesignDay_Impl>()->resetHumidityRatioAtMaximumDryBulb();
}

bool DesignDay::setEnthalpyAtMaximumDryBulb(double enthalpyAtMaximumDryBulb) {
  return getImpl<detail::DesignDay_Impl>()->setEnthalpyAtMaximumDryBulb(enthalpyAtMaximumDryBulb);
}

void DesignDay::resetEnthalpyAtMaximumDryBulb() {
  getImpl<detail::DesignDay_Impl>()->resetEnthalpyAtMaximumDryBulb();
}

bool DesignDay::setDryBulbTemperatureRangeModifierType(const std::string& dryBulbTemperatureRangeModifierType) {
  return getImpl<detail::DesignDay_Impl>()->setDryBulbTemperatureRangeModifierType(dryBulbTemperatureRangeModifierType);
}

void DesignDay::resetDryBulbTemperatureRangeModifierType() {
  getImpl<detail::DesignDay_Impl>()->resetDryBulbTemperatureRangeModifierType();
}

bool DesignDay::setSolarModelIndicator(const std::string& solarModelIndicator) {
  return getImpl<detail::DesignDay_Impl>()->setSolarModelIndicator(solarModelIndicator);
}

void DesignDay::resetSolarModelIndicator() {
  getImpl<detail::DesignDay_Impl>()->resetSolarModelIndicator();
}

bool DesignDay::setAshraeTaub(double ashraeTaub) {
  return getImpl<detail::DesignDay_Impl>()->setAshraeClearSkyOpticalDepthForBeamIrradiance(ashraeTaub);
}

bool DesignDay::setAshraeClearSkyOpticalDepthForBeamIrradiance(double ashraeClearSkyOpticalDepthForBeamIrradiance) {
  return getImpl<detail::DesignDay_Impl>()->setAshraeClearSkyOpticalDepthForBeamIrradiance(ashraeClearSkyOpticalDepthForBeamIrradiance);
}

void DesignDay::resetAshraeTaub() {
  getImpl<detail::DesignDay_Impl>()->resetAshraeClearSkyOpticalDepthForBeamIrradiance();
}

void DesignDay::resetAshraeClearSkyOpticalDepthForBeamIrradiance() {
  getImpl<detail::DesignDay_Impl>()->resetAshraeClearSkyOpticalDepthForBeamIrradiance();
}

bool DesignDay::setAshraeTaud(double ashraeTaud) {
  return getImpl<detail::DesignDay_Impl>()->setAshraeClearSkyOpticalDepthForDiffuseIrradiance(ashraeTaud);
}

bool DesignDay::setAshraeClearSkyOpticalDepthForDiffuseIrradiance(double ashraeClearSkyOpticalDepthForDiffuseIrradiance) {
  return getImpl<detail::DesignDay_Impl>()->setAshraeClearSkyOpticalDepthForDiffuseIrradiance(ashraeClearSkyOpticalDepthForDiffuseIrradiance);
}

void DesignDay::resetAshraeTaud() {
  getImpl<detail::DesignDay_Impl>()->resetAshraeClearSkyOpticalDepthForDiffuseIrradiance();
}

void DesignDay::resetAshraeClearSkyOpticalDepthForDiffuseIrradiance() {
  getImpl<detail::DesignDay_Impl>()->resetAshraeClearSkyOpticalDepthForDiffuseIrradiance();
}

bool DesignDay::setDailyWetBulbTemperatureRange(double dailyWetBulbTemperatureRange) {
  return getImpl<detail::DesignDay_Impl>()->setDailyWetBulbTemperatureRange(dailyWetBulbTemperatureRange);
}

void DesignDay::resetDailyWetBulbTemperatureRange() {
  getImpl<detail::DesignDay_Impl>()->resetDailyWetBulbTemperatureRange();
}

bool DesignDay::setMaximumNumberWarmupDays(int maximumNumberWarmupDays) {
  return getImpl<detail::DesignDay_Impl>()->setMaximumNumberWarmupDays(maximumNumberWarmupDays);
}

void DesignDay::resetMaximumNumberWarmupDays() {
  getImpl<detail::DesignDay_Impl>()->resetMaximumNumberWarmupDays();
}

bool DesignDay::setBeginEnvironmentResetMode(const std::string& beginEnvironmentResetMode) {
  return getImpl<detail::DesignDay_Impl>()->setBeginEnvironmentResetMode(beginEnvironmentResetMode);
}

void DesignDay::resetBeginEnvironmentResetMode() {
  getImpl<detail::DesignDay_Impl>()->resetBeginEnvironmentResetMode();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double DesignDay_Impl::maximumDryBulbTemperature() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::MaximumDryBulbTemperature, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isMaximumDryBulbTemperatureDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::MaximumDryBulbTemperature);
}

double DesignDay_Impl::dailyDryBulbTemperatureRange() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::DailyDryBulbTemperatureRange, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isDailyDryBulbTemperatureRangeDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::DailyDryBulbTemperatureRange);
}

double DesignDay_Impl::barometricPressure() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::BarometricPressure, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isBarometricPressureDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::BarometricPressure);
}

double DesignDay_Impl::windSpeed() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::WindSpeed, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isWindSpeedDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::WindSpeed);
}

double DesignDay_Impl::windDirection() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::WindDirection, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isWindDirectionDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::WindDirection);
}

double DesignDay_Impl::skyClearness() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::SkyClearness, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isSkyClearnessDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::SkyClearness);
}

bool DesignDay_Impl::rainIndicator() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::RainIndicator, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool DesignDay_Impl::isRainIndicatorDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::RainIndicator);
}

bool DesignDay_Impl::snowIndicator() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::SnowIndicator, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool DesignDay_Impl::isSnowIndicatorDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::SnowIndicator);
}

int DesignDay_Impl::dayOfMonth() const {
  auto value = getInt(openstudio::SizingPeriod_DesignDayFields::DayofMonth, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isDayOfMonthDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::DayofMonth);
}

int DesignDay_Impl::month() const {
  auto value = getInt(openstudio::SizingPeriod_DesignDayFields::Month, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isMonthDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::Month);
}

std::string DesignDay_Impl::dayType() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::DayType, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isDayTypeDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::DayType);
}

bool DesignDay_Impl::daylightSavingTimeIndicator() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::DaylightSavingTimeIndicator, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes");
}

bool DesignDay_Impl::isDaylightSavingTimeIndicatorDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::DaylightSavingTimeIndicator);
}

std::string DesignDay_Impl::humidityConditionType() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::HumidityConditionType, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isHumidityConditionTypeDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::HumidityConditionType);
}

boost::optional<double> DesignDay_Impl::wetBulbOrDewPointAtMaximumDryBulb() const {
  return getDouble(openstudio::SizingPeriod_DesignDayFields::WetbulborDewPointatMaximumDryBulb, true);
}

boost::optional<double> DesignDay_Impl::humidityRatioAtMaximumDryBulb() const {
  return getDouble(openstudio::SizingPeriod_DesignDayFields::HumidityRatioatMaximumDryBulb, true);
}

boost::optional<double> DesignDay_Impl::enthalpyAtMaximumDryBulb() const {
  return getDouble(openstudio::SizingPeriod_DesignDayFields::EnthalpyatMaximumDryBulb, true);
}

std::string DesignDay_Impl::dryBulbTemperatureRangeModifierType() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isDryBulbTemperatureRangeModifierTypeDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType);
}

std::string DesignDay_Impl::solarModelIndicator() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::SolarModelIndicator, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isSolarModelIndicatorDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::SolarModelIndicator);
}

double DesignDay_Impl::ashraeClearSkyOpticalDepthForBeamIrradiance() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_);
}

double DesignDay_Impl::ashraeClearSkyOpticalDepthForDiffuseIrradiance() const {
  auto value = getDouble(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_);
}

boost::optional<double> DesignDay_Impl::dailyWetBulbTemperatureRange() const {
  return getDouble(openstudio::SizingPeriod_DesignDayFields::DailyWetBulbTemperatureRange, true);
}

boost::optional<int> DesignDay_Impl::maximumNumberWarmupDays() const {
  return getInt(openstudio::SizingPeriod_DesignDayFields::MaximumNumberWarmupDays, true);
}

std::string DesignDay_Impl::beginEnvironmentResetMode() const {
  auto value = getString(openstudio::SizingPeriod_DesignDayFields::BeginEnvironmentResetMode, true);
  OS_ASSERT(value);
  return *value;
}

bool DesignDay_Impl::isBeginEnvironmentResetModeDefaulted() const {
  return isEmpty(openstudio::SizingPeriod_DesignDayFields::BeginEnvironmentResetMode);
}

bool DesignDay_Impl::setMaximumDryBulbTemperature(double maximumDryBulbTemperature) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::MaximumDryBulbTemperature, maximumDryBulbTemperature);
}

void DesignDay_Impl::resetMaximumDryBulbTemperature() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::MaximumDryBulbTemperature, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setDailyDryBulbTemperatureRange(double dailyDryBulbTemperatureRange) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::DailyDryBulbTemperatureRange, dailyDryBulbTemperatureRange);
}

void DesignDay_Impl::resetDailyDryBulbTemperatureRange() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::DailyDryBulbTemperatureRange, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setBarometricPressure(double barometricPressure) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::BarometricPressure, barometricPressure);
}

void DesignDay_Impl::resetBarometricPressure() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::BarometricPressure, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setWindSpeed(double windSpeed) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::WindSpeed, windSpeed);
}

void DesignDay_Impl::resetWindSpeed() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::WindSpeed, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setWindDirection(double windDirection) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::WindDirection, windDirection);
}

void DesignDay_Impl::resetWindDirection() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::WindDirection, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setSkyClearness(double skyClearness) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::SkyClearness, skyClearness);
}

void DesignDay_Impl::resetSkyClearness() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::SkyClearness, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setRainIndicator(bool rainIndicator) {
  const bool result = setString(openstudio::SizingPeriod_DesignDayFields::RainIndicator, rainIndicator ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetRainIndicator() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::RainIndicator, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setSnowIndicator(bool snowIndicator) {
  const bool result = setString(openstudio::SizingPeriod_DesignDayFields::SnowIndicator, snowIndicator ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetSnowIndicator() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::SnowIndicator, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setDayOfMonth(int dayOfMonth) {
  return setInt(openstudio::SizingPeriod_DesignDayFields::DayofMonth, dayOfMonth);
}

void DesignDay_Impl::resetDayOfMonth() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::DayofMonth, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setMonth(int month) {
  return setInt(openstudio::SizingPeriod_DesignDayFields::Month, month);
}

void DesignDay_Impl::resetMonth() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::Month, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setDayType(const std::string& dayType) {
  return setString(openstudio::SizingPeriod_DesignDayFields::DayType, dayType);
}

void DesignDay_Impl::resetDayType() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::DayType, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setDaylightSavingTimeIndicator(bool daylightSavingTimeIndicator) {
  const bool result = setString(openstudio::SizingPeriod_DesignDayFields::DaylightSavingTimeIndicator,
                                daylightSavingTimeIndicator ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetDaylightSavingTimeIndicator() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::DaylightSavingTimeIndicator, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setHumidityConditionType(const std::string& humidityConditionType) {
  return setString(openstudio::SizingPeriod_DesignDayFields::HumidityConditionType, humidityConditionType);
}

void DesignDay_Impl::resetHumidityConditionType() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::HumidityConditionType, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setWetBulbOrDewPointAtMaximumDryBulb(boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb) {
  bool result = false;
  if (wetBulbOrDewPointAtMaximumDryBulb) {
    result = setDouble(openstudio::SizingPeriod_DesignDayFields::WetbulborDewPointatMaximumDryBulb, *wetBulbOrDewPointAtMaximumDryBulb);
  } else {
    result = setString(openstudio::SizingPeriod_DesignDayFields::WetbulborDewPointatMaximumDryBulb, "");
  }
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetWetBulbOrDewPointAtMaximumDryBulb() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::WetbulborDewPointatMaximumDryBulb, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setHumidityRatioAtMaximumDryBulb(boost::optional<double> humidityRatioAtMaximumDryBulb) {
  bool result = false;
  if (humidityRatioAtMaximumDryBulb) {
    result = setDouble(openstudio::SizingPeriod_DesignDayFields::HumidityRatioatMaximumDryBulb, *humidityRatioAtMaximumDryBulb);
  } else {
    result = setString(openstudio::SizingPeriod_DesignDayFields::HumidityRatioatMaximumDryBulb, "");
  }
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetHumidityRatioAtMaximumDryBulb() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::HumidityRatioatMaximumDryBulb, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setEnthalpyAtMaximumDryBulb(boost::optional<double> enthalpyAtMaximumDryBulb) {
  bool result = false;
  if (enthalpyAtMaximumDryBulb) {
    result = setDouble(openstudio::SizingPeriod_DesignDayFields::EnthalpyatMaximumDryBulb, *enthalpyAtMaximumDryBulb);
  } else {
    result = setString(openstudio::SizingPeriod_DesignDayFields::EnthalpyatMaximumDryBulb, "");
  }
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetEnthalpyAtMaximumDryBulb() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::EnthalpyatMaximumDryBulb, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setDryBulbTemperatureRangeModifierType(const std::string& dryBulbTemperatureRangeModifierType) {
  return setString(openstudio::SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType, dryBulbTemperatureRangeModifierType);
}

void DesignDay_Impl::resetDryBulbTemperatureRangeModifierType() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setSolarModelIndicator(const std::string& solarModelIndicator) {
  return setString(openstudio::SizingPeriod_DesignDayFields::SolarModelIndicator, solarModelIndicator);
}

void DesignDay_Impl::resetSolarModelIndicator() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::SolarModelIndicator, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setAshraeClearSkyOpticalDepthForBeamIrradiance(double ashraeClearSkyOpticalDepthForBeamIrradiance) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_,
                   ashraeClearSkyOpticalDepthForBeamIrradiance);
}

void DesignDay_Impl::resetAshraeClearSkyOpticalDepthForBeamIrradiance() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setAshraeClearSkyOpticalDepthForDiffuseIrradiance(double ashraeClearSkyOpticalDepthForDiffuseIrradiance) {
  return setDouble(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_,
                   ashraeClearSkyOpticalDepthForDiffuseIrradiance);
}

void DesignDay_Impl::resetAshraeClearSkyOpticalDepthForDiffuseIrradiance() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setDailyWetBulbTemperatureRange(boost::optional<double> dailyWetBulbTemperatureRange) {
  bool result = false;
  if (dailyWetBulbTemperatureRange) {
    result = setDouble(openstudio::SizingPeriod_DesignDayFields::DailyWetBulbTemperatureRange, *dailyWetBulbTemperatureRange);
  } else {
    result = setString(openstudio::SizingPeriod_DesignDayFields::DailyWetBulbTemperatureRange, "");
  }
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetDailyWetBulbTemperatureRange() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::DailyWetBulbTemperatureRange, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setMaximumNumberWarmupDays(boost::optional<int> maximumNumberWarmupDays) {
  bool result = false;
  if (maximumNumberWarmupDays) {
    result = setInt(openstudio::SizingPeriod_DesignDayFields::MaximumNumberWarmupDays, *maximumNumberWarmupDays);
  } else {
    result = setString(openstudio::SizingPeriod_DesignDayFields::MaximumNumberWarmupDays, "");
  }
  OS_ASSERT(result);
  return result;
}

void DesignDay_Impl::resetMaximumNumberWarmupDays() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::MaximumNumberWarmupDays, "");
  OS_ASSERT(result);
}

bool DesignDay_Impl::setBeginEnvironmentResetMode(const std::string& beginEnvironmentResetMode) {
  return setString(openstudio::SizingPeriod_DesignDayFields::BeginEnvironmentResetMode, beginEnvironmentResetMode);
}

void DesignDay_Impl::resetBeginEnvironmentResetMode() {
  bool result = setString(openstudio::SizingPeriod_DesignDayFields::BeginEnvironmentResetMode, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
