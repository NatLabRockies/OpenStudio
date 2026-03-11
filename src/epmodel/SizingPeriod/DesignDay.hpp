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

  double dailyDryBulbTemperatureRange() const;
  bool isDailyDryBulbTemperatureRangeDefaulted() const;

  double humidityIndicatingConditionsAtMaximumDryBulb() const;
  bool isHumidityIndicatingConditionsAtMaximumDryBulbDefaulted() const;

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

  std::string humidityIndicatingType() const;
  std::string humidityConditionType() const;
  bool isHumidityIndicatingTypeDefaulted() const;
  bool isHumidityConditionTypeDefaulted() const;

  boost::optional<double> wetBulbOrDewPointAtMaximumDryBulb() const;
  boost::optional<double> humidityRatioAtMaximumDryBulb() const;
  boost::optional<double> enthalpyAtMaximumDryBulb() const;

  std::string dryBulbTemperatureRangeModifierType() const;
  bool isDryBulbTemperatureRangeModifierTypeDefaulted() const;

  std::string solarModelIndicator() const;
  bool isSolarModelIndicatorDefaulted() const;

  double ashraeTaub() const;
  double ashraeClearSkyOpticalDepthForBeamIrradiance() const;
  bool isAshraeTaubDefaulted() const;
  bool isAshraeClearSkyOpticalDepthForBeamIrradianceDefaulted() const;

  double ashraeTaud() const;
  double ashraeClearSkyOpticalDepthForDiffuseIrradiance() const;
  bool isAshraeTaudDefaulted() const;
  bool isAshraeClearSkyOpticalDepthForDiffuseIrradianceDefaulted() const;

  boost::optional<double> dailyWetBulbTemperatureRange() const;
  boost::optional<int> maximumNumberWarmupDays() const;

  std::string beginEnvironmentResetMode() const;
  bool isBeginEnvironmentResetModeDefaulted() const;

  bool setMaximumDryBulbTemperature(double maximumDryBulbTemperature);
  void resetMaximumDryBulbTemperature();

  bool setDailyDryBulbTemperatureRange(double dailyDryBulbTemperatureRange);
  void resetDailyDryBulbTemperatureRange();

  bool setHumidityIndicatingConditionsAtMaximumDryBulb(double humidityIndicatingConditionsAtMaximumDryBulb);
  void resetHumidityIndicatingConditionsAtMaximumDryBulb();

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

  bool setHumidityIndicatingType(const std::string& humidityIndicatingType);
  bool setHumidityConditionType(const std::string& humidityConditionType);
  void resetHumidityIndicatingType();
  void resetHumidityConditionType();

  bool setWetBulbOrDewPointAtMaximumDryBulb(double wetBulbOrDewPointAtMaximumDryBulb);
  void resetWetBulbOrDewPointAtMaximumDryBulb();

  bool setHumidityRatioAtMaximumDryBulb(double humidityRatioAtMaximumDryBulb);
  void resetHumidityRatioAtMaximumDryBulb();

  bool setEnthalpyAtMaximumDryBulb(double enthalpyAtMaximumDryBulb);
  void resetEnthalpyAtMaximumDryBulb();

  bool setDryBulbTemperatureRangeModifierType(const std::string& dryBulbTemperatureRangeModifierType);
  void resetDryBulbTemperatureRangeModifierType();

  bool setSolarModelIndicator(const std::string& solarModelIndicator);
  void resetSolarModelIndicator();

  bool setAshraeTaub(double ashraeTaub);
  bool setAshraeClearSkyOpticalDepthForBeamIrradiance(double ashraeClearSkyOpticalDepthForBeamIrradiance);
  void resetAshraeTaub();
  void resetAshraeClearSkyOpticalDepthForBeamIrradiance();

  bool setAshraeTaud(double ashraeTaud);
  bool setAshraeClearSkyOpticalDepthForDiffuseIrradiance(double ashraeClearSkyOpticalDepthForDiffuseIrradiance);
  void resetAshraeTaud();
  void resetAshraeClearSkyOpticalDepthForDiffuseIrradiance();

  bool setDailyWetBulbTemperatureRange(double dailyWetBulbTemperatureRange);
  void resetDailyWetBulbTemperatureRange();

  bool setMaximumNumberWarmupDays(int maximumNumberWarmupDays);
  void resetMaximumNumberWarmupDays();

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
