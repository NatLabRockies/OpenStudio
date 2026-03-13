/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNDAY_HPP
#define EPMODEL_DESIGNDAY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DesignDay_Impl;
  }

  class EPMODEL_API DesignDay : public ModelObject
  {
   public:
    explicit DesignDay(const Model& model);

    virtual ~DesignDay() override = default;
    DesignDay(const DesignDay& other) = default;
    DesignDay(DesignDay&& other) = default;
    DesignDay& operator=(const DesignDay&) = default;
    DesignDay& operator=(DesignDay&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validDayTypeValues();
    static std::vector<std::string> validHumidityIndicatingTypeValues();
    static std::vector<std::string> validHumidityConditionTypeValues();
    static std::vector<std::string> validDryBulbTemperatureRangeModifierTypeValues();
    static std::vector<std::string> validSolarModelIndicatorValues();
    static std::vector<std::string> validBeginEnvironmentResetModeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model DesignDay scalar accessor names/signatures,
    //   including legacy aliases (humidityIndicating*, ashraeTau*).
    // - Field Mapping: These scalar APIs map to E+ SizingPeriod:DesignDay fields.
    // - Field Mapping: Legacy alias methods humidityIndicating* map to current
    //   HumidityConditionType and wet-bulb/humidity-ratio/enthalpy scalar fields.
    // - Field Mapping: ashraeTaub/ashraeTaud map to E+ fields
    //   ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_ and
    //   ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_.
    // - ForwardTranslator Evidence: ForwardTranslateDesignDay confirms these mappings and
    //   conditional field usage by humidity/solar indicator type.
    // - TODO(parity): Add relationship schedule-field APIs in a dedicated non-scalar pass.

    double maximumDryBulbTemperature() const;
    bool isMaximumDryBulbTemperatureDefaulted() const;
    bool setMaximumDryBulbTemperature(double maximumDryBulbTemperature);
    void resetMaximumDryBulbTemperature();

    double dailyDryBulbTemperatureRange() const;
    bool isDailyDryBulbTemperatureRangeDefaulted() const;
    bool setDailyDryBulbTemperatureRange(double dailyDryBulbTemperatureRange);
    void resetDailyDryBulbTemperatureRange();

    double humidityIndicatingConditionsAtMaximumDryBulb() const;
    bool isHumidityIndicatingConditionsAtMaximumDryBulbDefaulted() const;
    bool setHumidityIndicatingConditionsAtMaximumDryBulb(double humidityIndicatingConditionsAtMaximumDryBulb);
    void resetHumidityIndicatingConditionsAtMaximumDryBulb();

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

    std::string humidityIndicatingType() const;
    bool isHumidityIndicatingTypeDefaulted() const;
    bool setHumidityIndicatingType(const std::string& humidityIndicatingType);
    void resetHumidityIndicatingType();

    std::string humidityConditionType() const;
    bool isHumidityConditionTypeDefaulted() const;
    bool setHumidityConditionType(const std::string& humidityConditionType);
    void resetHumidityConditionType();

    boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb() const;
    bool setWetBulbOrDewPointAtMaximumDryBulb(double wetBulbOrDewPointAtMaximumDryBulb);
    void resetWetBulbOrDewPointAtMaximumDryBulb();

    boost::optional<double> humidityRatioAtMaximumDryBulb() const;
    bool setHumidityRatioAtMaximumDryBulb(double humidityRatioAtMaximumDryBulb);
    void resetHumidityRatioAtMaximumDryBulb();

    boost::optional<double> enthalpyAtMaximumDryBulb() const;
    bool setEnthalpyAtMaximumDryBulb(double enthalpyAtMaximumDryBulb);
    void resetEnthalpyAtMaximumDryBulb();

    std::string dryBulbTemperatureRangeModifierType() const;
    bool isDryBulbTemperatureRangeModifierTypeDefaulted() const;
    bool setDryBulbTemperatureRangeModifierType(const std::string& dryBulbTemperatureRangeModifierType);
    void resetDryBulbTemperatureRangeModifierType();

    std::string solarModelIndicator() const;
    bool isSolarModelIndicatorDefaulted() const;
    bool setSolarModelIndicator(const std::string& solarModelIndicator);
    void resetSolarModelIndicator();

    double ashraeTaub() const;
    bool isAshraeTaubDefaulted() const;
    bool setAshraeTaub(double ashraeTaub);
    void resetAshraeTaub();

    double ashraeClearSkyOpticalDepthForBeamIrradiance() const;
    bool isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted() const;
    bool setAshraeClearSkyOpticalDepthForBeamIrradiance(double ashraeClearSkyOpticalDepthForBeamIrradiance);
    void resetAshraeClearSkyOpticalDepthForBeamIrradiance();

    double ashraeTaud() const;
    bool isAshraeTaudDefaulted() const;
    bool setAshraeTaud(double ashraeTaud);
    void resetAshraeTaud();

    double ashraeClearSkyOpticalDepthForDiffuseIrradiance() const;
    bool isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted() const;
    bool setAshraeClearSkyOpticalDepthForDiffuseIrradiance(double ashraeClearSkyOpticalDepthForDiffuseIrradiance);
    void resetAshraeClearSkyOpticalDepthForDiffuseIrradiance();

    boost::optional<double> dailyWetBulbTemperatureRange() const;
    bool setDailyWetBulbTemperatureRange(double dailyWetBulbTemperatureRange);
    void resetDailyWetBulbTemperatureRange();

    boost::optional<int> maximumNumberWarmupDays() const;
    bool setMaximumNumberWarmupDays(int maximumNumberWarmupDays);
    void resetMaximumNumberWarmupDays();

    std::string beginEnvironmentResetMode() const;
    bool isBeginEnvironmentResetModeDefaulted() const;
    bool setBeginEnvironmentResetMode(const std::string& beginEnvironmentResetMode);
    void resetBeginEnvironmentResetMode();

   protected:
    using ImplType = detail::DesignDay_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DesignDay(std::shared_ptr<detail::DesignDay_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
