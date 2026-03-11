/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNDAY_IMPL_HPP
#define EPMODEL_DESIGNDAY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DesignDay_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DesignDay_Impl() override = default;

  double maximumDryBulbTemperature() const;
  bool isMaximumDryBulbTemperatureDefaulted() const;

  double dailyDryBulbTemperatureRange() const;
  bool isDailyDryBulbTemperatureRangeDefaulted() const;

  double barometricPressure() const;
  bool isBarometricPressureDefaulted() const;

  double windSpeed() const;
  bool isWindSpeedDefaulted() const;

  double windDirection() const;
  bool isWindDirectionDefaulted() const;

  double skyClearness() const;
  bool isSkyClearnessDefaulted() const;

  bool rainIndicator() const;
  bool isRainIndicatorDefaulted() const;

  bool snowIndicator() const;
  bool isSnowIndicatorDefaulted() const;

  int dayOfMonth() const;
  bool isDayOfMonthDefaulted() const;

  int month() const;
  bool isMonthDefaulted() const;

  std::string dayType() const;
  bool isDayTypeDefaulted() const;

  bool daylightSavingTimeIndicator() const;
  bool isDaylightSavingTimeIndicatorDefaulted() const;

  std::string humidityConditionType() const;
  bool isHumidityConditionTypeDefaulted() const;

  boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb() const;
  boost::optional<double> humidityRatioAtMaximumDryBulb() const;
  boost::optional<double> enthalpyAtMaximumDryBulb() const;

  std::string dryBulbTemperatureRangeModifierType() const;
  bool isDryBulbTemperatureRangeModifierTypeDefaulted() const;

  std::string solarModelIndicator() const;
  bool isSolarModelIndicatorDefaulted() const;

  double ashraeClearSkyOpticalDepthForBeamIrradiance() const;
  bool isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted() const;

  double ashraeClearSkyOpticalDepthForDiffuseIrradiance() const;
  bool isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted() const;

  boost::optional<double> dailyWetBulbTemperatureRange() const;
  boost::optional<int> maximumNumberWarmupDays() const;

  std::string beginEnvironmentResetMode() const;
  bool isBeginEnvironmentResetModeDefaulted() const;

  bool setMaximumDryBulbTemperature(double maximumDryBulbTemperature);
  void resetMaximumDryBulbTemperature();

  bool setDailyDryBulbTemperatureRange(double dailyDryBulbTemperatureRange);
  void resetDailyDryBulbTemperatureRange();

  bool setBarometricPressure(double barometricPressure);
  void resetBarometricPressure();

  bool setWindSpeed(double windSpeed);
  void resetWindSpeed();

  bool setWindDirection(double windDirection);
  void resetWindDirection();

  bool setSkyClearness(double skyClearness);
  void resetSkyClearness();

  bool setRainIndicator(bool rainIndicator);
  void resetRainIndicator();

  bool setSnowIndicator(bool snowIndicator);
  void resetSnowIndicator();

  bool setDayOfMonth(int dayOfMonth);
  void resetDayOfMonth();

  bool setMonth(int month);
  void resetMonth();

  bool setDayType(const std::string& dayType);
  void resetDayType();

  bool setDaylightSavingTimeIndicator(bool daylightSavingTimeIndicator);
  void resetDaylightSavingTimeIndicator();

  bool setHumidityConditionType(const std::string& humidityConditionType);
  void resetHumidityConditionType();

  bool setWetBulbOrDewPointAtMaximumDryBulb(boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb);
  void resetWetBulbOrDewPointAtMaximumDryBulb();

  bool setHumidityRatioAtMaximumDryBulb(boost::optional<double> humidityRatioAtMaximumDryBulb);
  void resetHumidityRatioAtMaximumDryBulb();

  bool setEnthalpyAtMaximumDryBulb(boost::optional<double> enthalpyAtMaximumDryBulb);
  void resetEnthalpyAtMaximumDryBulb();

  bool setDryBulbTemperatureRangeModifierType(const std::string& dryBulbTemperatureRangeModifierType);
  void resetDryBulbTemperatureRangeModifierType();

  bool setSolarModelIndicator(const std::string& solarModelIndicator);
  void resetSolarModelIndicator();

  bool setAshraeClearSkyOpticalDepthForBeamIrradiance(double ashraeClearSkyOpticalDepthForBeamIrradiance);
  void resetAshraeClearSkyOpticalDepthForBeamIrradiance();

  bool setAshraeClearSkyOpticalDepthForDiffuseIrradiance(double ashraeClearSkyOpticalDepthForDiffuseIrradiance);
  void resetAshraeClearSkyOpticalDepthForDiffuseIrradiance();

  bool setDailyWetBulbTemperatureRange(boost::optional<double> dailyWetBulbTemperatureRange);
  void resetDailyWetBulbTemperatureRange();

  bool setMaximumNumberWarmupDays(boost::optional<int> maximumNumberWarmupDays);
  void resetMaximumNumberWarmupDays();

  bool setBeginEnvironmentResetMode(const std::string& beginEnvironmentResetMode);
  void resetBeginEnvironmentResetMode();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
