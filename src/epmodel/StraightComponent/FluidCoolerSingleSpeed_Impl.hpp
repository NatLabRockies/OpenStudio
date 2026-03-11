/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERSINGLESPEED_IMPL_HPP
#define EPMODEL_FLUIDCOOLERSINGLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FluidCoolerSingleSpeed_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~FluidCoolerSingleSpeed_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::vector<std::string> performanceInputMethodValues() const;

  std::string performanceInputMethod() const;

  boost::optional<double> designAirFlowRateUfactorTimesAreaValue() const;
  bool isDesignAirFlowRateUfactorTimesAreaValueAutosized() const;

  double nominalCapacity() const;

  double designEnteringWaterTemperature() const;

  double designEnteringAirTemperature() const;

  double designEnteringAirWetbulbTemperature() const;

  boost::optional<double> designWaterFlowRate() const;
  bool isDesignWaterFlowRateAutosized() const;

  boost::optional<double> designAirFlowRate() const;
  bool isDesignAirFlowRateAutosized() const;

  boost::optional<double> designAirFlowRateFanPower() const;
  bool isDesignAirFlowRateFanPowerAutosized() const;

  bool setPerformanceInputMethod(const std::string& performanceInputMethod);

  bool setDesignAirFlowRateUfactorTimesAreaValue(boost::optional<double> designAirFlowRateUfactorTimesAreaValue);
  void autosizeDesignAirFlowRateUfactorTimesAreaValue();

  bool setNominalCapacity(double nominalCapacity);

  bool setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature);

  bool setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature);

  bool setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature);

  bool setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate);
  void autosizeDesignWaterFlowRate();

  bool setDesignAirFlowRate(boost::optional<double> designAirFlowRate);
  void autosizeDesignAirFlowRate();

  bool setDesignAirFlowRateFanPower(boost::optional<double> designAirFlowRateFanPower);
  void autosizeDesignAirFlowRateFanPower();

  boost::optional<double> autosizedDesignAirFlowRateUfactorTimesAreaValue() const;
  boost::optional<double> autosizedDesignWaterFlowRate() const;
  boost::optional<double> autosizedDesignAirFlowRate() const;
  boost::optional<double> autosizedDesignAirFlowRateFanPower() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
