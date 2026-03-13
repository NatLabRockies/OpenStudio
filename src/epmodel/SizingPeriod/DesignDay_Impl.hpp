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
      bool setMaximumDryBulbTemperature(double maximumDryBulbTemperature);
      void resetMaximumDryBulbTemperature();

      double dailyDryBulbTemperatureRange() const;
      bool isDailyDryBulbTemperatureRangeDefaulted() const;
      bool setDailyDryBulbTemperatureRange(double dailyDryBulbTemperatureRange);
      void resetDailyDryBulbTemperatureRange();

      double barometricPressure() const;
      bool isBarometricPressureDefaulted() const;
      bool setBarometricPressure(double barometricPressure);
      void resetBarometricPressure();

      double windSpeed() const;
      bool isWindSpeedDefaulted() const;
      bool setWindSpeed(double windSpeed);
      void resetWindSpeed();

      double windDirection() const;
      bool isWindDirectionDefaulted() const;
      bool setWindDirection(double windDirection);
      void resetWindDirection();

      double skyClearness() const;
      bool isSkyClearnessDefaulted() const;
      bool setSkyClearness(double skyClearness);
      void resetSkyClearness();

      bool rainIndicator() const;
      bool isRainIndicatorDefaulted() const;
      bool setRainIndicator(bool rainIndicator);
      void resetRainIndicator();

      bool snowIndicator() const;
      bool isSnowIndicatorDefaulted() const;
      bool setSnowIndicator(bool snowIndicator);
      void resetSnowIndicator();

      int dayOfMonth() const;
      bool isDayOfMonthDefaulted() const;
      bool setDayOfMonth(int dayOfMonth);
      void resetDayOfMonth();

      int month() const;
      bool isMonthDefaulted() const;
      bool setMonth(int month);
      void resetMonth();

      std::string dayType() const;
      bool isDayTypeDefaulted() const;
      bool setDayType(const std::string& dayType);
      void resetDayType();

      bool daylightSavingTimeIndicator() const;
      bool isDaylightSavingTimeIndicatorDefaulted() const;
      bool setDaylightSavingTimeIndicator(bool daylightSavingTimeIndicator);
      void resetDaylightSavingTimeIndicator();

      std::string humidityConditionType() const;
      bool isHumidityConditionTypeDefaulted() const;
      bool setHumidityConditionType(const std::string& humidityConditionType);
      void resetHumidityConditionType();

      boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb() const;
      bool setWetBulbOrDewPointAtMaximumDryBulb(boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb);
      void resetWetBulbOrDewPointAtMaximumDryBulb();

      boost::optional<double> humidityRatioAtMaximumDryBulb() const;
      bool setHumidityRatioAtMaximumDryBulb(boost::optional<double> humidityRatioAtMaximumDryBulb);
      void resetHumidityRatioAtMaximumDryBulb();

      boost::optional<double> enthalpyAtMaximumDryBulb() const;
      bool setEnthalpyAtMaximumDryBulb(boost::optional<double> enthalpyAtMaximumDryBulb);
      void resetEnthalpyAtMaximumDryBulb();

      std::string dryBulbTemperatureRangeModifierType() const;
      bool isDryBulbTemperatureRangeModifierTypeDefaulted() const;
      bool setDryBulbTemperatureRangeModifierType(const std::string& dryBulbTemperatureRangeModifierType);
      void resetDryBulbTemperatureRangeModifierType();

      std::string solarModelIndicator() const;
      bool isSolarModelIndicatorDefaulted() const;
      bool setSolarModelIndicator(const std::string& solarModelIndicator);
      void resetSolarModelIndicator();

      double ashraeClearSkyOpticalDepthForBeamIrradiance() const;
      bool isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted() const;
      bool setAshraeClearSkyOpticalDepthForBeamIrradiance(double ashraeClearSkyOpticalDepthForBeamIrradiance);
      void resetAshraeClearSkyOpticalDepthForBeamIrradiance();

      double ashraeClearSkyOpticalDepthForDiffuseIrradiance() const;
      bool isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted() const;
      bool setAshraeClearSkyOpticalDepthForDiffuseIrradiance(double ashraeClearSkyOpticalDepthForDiffuseIrradiance);
      void resetAshraeClearSkyOpticalDepthForDiffuseIrradiance();

      boost::optional<double> dailyWetBulbTemperatureRange() const;
      bool setDailyWetBulbTemperatureRange(boost::optional<double> dailyWetBulbTemperatureRange);
      void resetDailyWetBulbTemperatureRange();

      boost::optional<int> maximumNumberWarmupDays() const;
      bool setMaximumNumberWarmupDays(boost::optional<int> maximumNumberWarmupDays);
      void resetMaximumNumberWarmupDays();

      std::string beginEnvironmentResetMode() const;
      bool isBeginEnvironmentResetModeDefaulted() const;
      bool setBeginEnvironmentResetMode(const std::string& beginEnvironmentResetMode);
      void resetBeginEnvironmentResetMode();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
