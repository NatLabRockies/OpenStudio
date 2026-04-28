/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNCONSTANTGRADIENT_IMPL_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNCONSTANTGRADIENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RoomAirTemperaturePatternConstantGradient_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirTemperaturePatternConstantGradient_Impl() override = default;

      int controlIntegerforPatternControlScheduleName() const;
      bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);

      boost::optional<double> thermostatOffset() const;
      bool setThermostatOffset(double thermostatOffset);
      void resetThermostatOffset();

      boost::optional<double> returnAirOffset() const;
      bool setReturnAirOffset(double returnAirOffset);
      void resetReturnAirOffset();

      boost::optional<double> exhaustAirOffset() const;
      bool setExhaustAirOffset(double exhaustAirOffset);
      void resetExhaustAirOffset();

      boost::optional<double> temperatureGradient() const;
      bool setTemperatureGradient(double temperatureGradient);
      void resetTemperatureGradient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
