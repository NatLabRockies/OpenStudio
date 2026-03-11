/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERTWOSPEED_IMPL_HPP
#define EPMODEL_FLUIDCOOLERTWOSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FluidCoolerTwoSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~FluidCoolerTwoSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::vector<std::string> performanceInputMethodValues() const;

  std::string performanceInputMethod() const;

  boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
  bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;

  boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
  bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;

  double lowFanSpeedUFactorTimesAreaSizingFactor() const;

  double highSpeedNominalCapacity() const;

  boost::optional<double> lowSpeedNominalCapacity() const;
  bool isLowSpeedNominalCapacityAutosized() const;

  double lowSpeedNominalCapacitySizingFactor() const;

  double designEnteringWaterTemperature() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

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

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue);
  void autosizeHighFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue);
  void autosizeLowFanSpeedUfactorTimesAreaValue();

  bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

  bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);

  bool setLowSpeedNominalCapacity(boost::optional<double> lowSpeedNominalCapacity);
  void autosizeLowSpeedNominalCapacity();

  bool setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor);

  bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);

  bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

  bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
  void autosizeDesignWaterFlowRate();

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

  boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;
  boost::optional<double> autosizedLowSpeedNominalCapacity() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedHighFanSpeedFanPower() const;
  boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;
  boost::optional<double> autosizedLowFanSpeedFanPower() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
