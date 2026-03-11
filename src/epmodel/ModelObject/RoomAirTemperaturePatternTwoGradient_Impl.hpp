/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNTWOGRADIENT_IMPL_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNTWOGRADIENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API RoomAirTemperaturePatternTwoGradient_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~RoomAirTemperaturePatternTwoGradient_Impl() override = default;

  int controlIntegerforPatternControlScheduleName() const;
  boost::optional<double> thermostatHeight() const;
  boost::optional<double> returnAirHeight() const;
  boost::optional<double> exhaustAirHeight() const;
  boost::optional<double> temperatureGradientLowerBound() const;
  boost::optional<double> temperatureGradientUpperBound() const;
  boost::optional<std::string> gradientInterpolationMode() const;
  boost::optional<double> upperTemperatureBound() const;
  boost::optional<double> lowerTemperatureBound() const;
  boost::optional<double> upperHeatRateBound() const;
  boost::optional<double> lowerHeatRateBound() const;

  bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);
  bool setThermostatHeight(double thermostatHeight);
  void resetThermostatHeight();
  bool setReturnAirHeight(double returnAirHeight);
  void resetReturnAirHeight();
  bool setExhaustAirHeight(double exhaustAirHeight);
  void resetExhaustAirHeight();
  bool setTemperatureGradientLowerBound(double temperatureGradientLowerBound);
  void resetTemperatureGradientLowerBound();
  bool setTemperatureGradientUpperBound(double temperatureGradientUpperBound);
  void resetTemperatureGradientUpperBound();
  bool setGradientInterpolationMode(const std::string& gradientInterpolationMode);
  void resetGradientInterpolationMode();
  bool setUpperTemperatureBound(double upperTemperatureBound);
  void resetUpperTemperatureBound();
  bool setLowerTemperatureBound(double lowerTemperatureBound);
  void resetLowerTemperatureBound();
  bool setUpperHeatRateBound(double upperHeatRateBound);
  void resetUpperHeatRateBound();
  bool setLowerHeatRateBound(double lowerHeatRateBound);
  void resetLowerHeatRateBound();

  std::vector<std::string> gradientInterpolationModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
