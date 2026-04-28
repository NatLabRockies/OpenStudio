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
      bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);

      boost::optional<double> thermostatHeight() const;
      bool setThermostatHeight(double thermostatHeight);
      void resetThermostatHeight();

      boost::optional<double> returnAirHeight() const;
      bool setReturnAirHeight(double returnAirHeight);
      void resetReturnAirHeight();

      boost::optional<double> exhaustAirHeight() const;
      bool setExhaustAirHeight(double exhaustAirHeight);
      void resetExhaustAirHeight();

      boost::optional<double> temperatureGradientLowerBound() const;
      bool setTemperatureGradientLowerBound(double temperatureGradientLowerBound);
      void resetTemperatureGradientLowerBound();

      boost::optional<double> temperatureGradientUpperBound() const;
      bool setTemperatureGradientUpperBound(double temperatureGradientUpperBound);
      void resetTemperatureGradientUpperBound();

      boost::optional<std::string> gradientInterpolationMode() const;
      bool setGradientInterpolationMode(const std::string& gradientInterpolationMode);
      void resetGradientInterpolationMode();

      boost::optional<double> upperTemperatureBound() const;
      bool setUpperTemperatureBound(double upperTemperatureBound);
      void resetUpperTemperatureBound();

      boost::optional<double> lowerTemperatureBound() const;
      bool setLowerTemperatureBound(double lowerTemperatureBound);
      void resetLowerTemperatureBound();

      boost::optional<double> upperHeatRateBound() const;
      bool setUpperHeatRateBound(double upperHeatRateBound);
      void resetUpperHeatRateBound();

      boost::optional<double> lowerHeatRateBound() const;
      bool setLowerHeatRateBound(double lowerHeatRateBound);
      void resetLowerHeatRateBound();

      std::vector<std::string> gradientInterpolationModeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
