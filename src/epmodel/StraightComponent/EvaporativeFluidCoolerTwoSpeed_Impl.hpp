/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_IMPL_HPP
#define EPMODEL_EVAPORATIVEFLUIDCOOLERTWOSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API EvaporativeFluidCoolerTwoSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~EvaporativeFluidCoolerTwoSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::vector<std::string> performanceInputMethodValues() const;
  std::vector<std::string> evaporationLossModeValues() const;
  std::vector<std::string> blowdownCalculationModeValues() const;

  boost::optional<double> highFanSpeedAirFlowRate() const;
  bool isHighFanSpeedAirFlowRateAutosized() const;

  boost::optional<double> highFanSpeedFanPower() const;
  bool isHighFanSpeedFanPowerAutosized() const;

  boost::optional<double> lowFanSpeedAirFlowRate() const;
  bool isLowFanSpeedAirFlowRateAutosized() const;

  double lowFanSpeedAirFlowRateSizingFactor() const;

  boost::optional<double> lowFanSpeedFanPower() const;
  bool isLowFanSpeedFanPowerAutosized() const;

  double lowFanSpeedFanPowerSizingFactor() const;

  double designSprayWaterFlowRate() const;

  std::string performanceInputMethod() const;

  double heatRejectionCapacityandNominalCapacitySizingRatio() const;

  boost::optional<double> highSpeedStandardDesignCapacity() const;

  boost::optional<double> lowSpeedStandardDesignCapacity() const;
  bool isLowSpeedStandardDesignCapacityAutosized() const;

  double lowSpeedStandardCapacitySizingFactor() const;

  boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
  bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;

  boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
  bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;

  double lowFanSpeedUFactorTimesAreaSizingFactor() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

  boost::optional<double> highSpeedUserSpecifiedDesignCapacity() const;

  boost::optional<double> lowSpeedUserSpecifiedDesignCapacity() const;
  bool isLowSpeedUserSpecifiedDesignCapacityAutosized() const;

  double lowSpeedUserSpecifiedDesignCapacitySizingFactor() const;

  boost::optional<double> designEnteringWaterTemperature() const;
  bool isDesignEnteringWaterTemperatureAutosized() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  double highSpeedSizingFactor() const;

  std::string evaporationLossMode() const;

  boost::optional<double> evaporationLossFactor() const;

  double driftLossPercent() const;

  std::string blowdownCalculationMode() const;

  double blowdownConcentrationRatio() const;

  bool setHighFanSpeedAirFlowRate(boost::optional<double> highFanSpeedAirFlowRate);
  void autosizeHighFanSpeedAirFlowRate();

  bool setHighFanSpeedFanPower(boost::optional<double> highFanSpeedFanPower);
  void autosizeHighFanSpeedFanPower();

  bool setLowFanSpeedAirFlowRate(boost::optional<double> lowFanSpeedAirFlowRate);
  void autosizeLowFanSpeedAirFlowRate();

  bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);

  bool setLowFanSpeedFanPower(boost::optional<double> lowFanSpeedFanPower);
  void autosizeLowFanSpeedFanPower();

  bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);

  bool setDesignSprayWaterFlowRate(double designSprayWaterFlowRate);

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setHeatRejectionCapacityandNominalCapacitySizingRatio(double heatRejectionCapacityandNominalCapacitySizingRatio);

  bool setHighSpeedStandardDesignCapacity(boost::optional<double> highSpeedStandardDesignCapacity);
  void resetHighSpeedStandardDesignCapacity();

  bool setLowSpeedStandardDesignCapacity(boost::optional<double> lowSpeedStandardDesignCapacity);
  void resetLowSpeedStandardDesignCapacity();
  void autosizeLowSpeedStandardDesignCapacity();

  bool setLowSpeedStandardCapacitySizingFactor(double lowSpeedStandardCapacitySizingFactor);

  bool setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue);
  void resetHighFanSpeedUfactorTimesAreaValue();
  void autosizeHighFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue);
  void resetLowFanSpeedUfactorTimesAreaValue();
  void autosizeLowFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

  bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
  void resetDesignWaterFlowRate();
  void autosizeDesignWaterFlowRate();

  bool setHighSpeedUserSpecifiedDesignCapacity(boost::optional<double> highSpeedUserSpecifiedDesignCapacity);
  void resetHighSpeedUserSpecifiedDesignCapacity();

  bool setLowSpeedUserSpecifiedDesignCapacity(boost::optional<double> lowSpeedUserSpecifiedDesignCapacity);
  void resetLowSpeedUserSpecifiedDesignCapacity();
  void autosizeLowSpeedUserSpecifiedDesignCapacity();

  bool setLowSpeedUserSpecifiedDesignCapacitySizingFactor(double lowSpeedUserSpecifiedDesignCapacitySizingFactor);

  bool setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature);
  void autosizeDesignEnteringWaterTemperature();

  bool setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature);

  bool setHighSpeedSizingFactor(double highSpeedSizingFactor);

  bool setEvaporationLossMode(const std::string& evaporationLossMode);

  bool setEvaporationLossFactor(boost::optional<double> evaporationLossFactor);
  void resetEvaporationLossFactor();

  bool setDriftLossPercent(double driftLossPercent);

  bool setBlowdownCalculationMode(const std::string& blowdownCalculationMode);

  bool setBlowdownConcentrationRatio(double blowdownConcentrationRatio);

  boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedHighFanSpeedFanPower() const;
  boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedLowFanSpeedFanPower() const;
  boost::optional<double> autosizedLowSpeedStandardDesignCapacity() const;
  boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedLowSpeedUserSpecifiedDesignCapacity() const;
  boost::optional<double> autosizedDesignEnteringWaterTemperature() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
