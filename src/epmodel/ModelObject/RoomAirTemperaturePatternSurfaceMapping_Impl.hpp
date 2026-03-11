/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNSURFACEMAPPING_IMPL_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNSURFACEMAPPING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API RoomAirTemperaturePatternSurfaceMapping_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~RoomAirTemperaturePatternSurfaceMapping_Impl() override = default;

  int controlIntegerforPatternControlScheduleName() const;
  boost::optional<double> thermostatOffset() const;
  boost::optional<double> returnAirOffset() const;
  boost::optional<double> exhaustAirOffset() const;

  bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);
  bool setThermostatOffset(double thermostatOffset);
  void resetThermostatOffset();
  bool setReturnAirOffset(double returnAirOffset);
  void resetReturnAirOffset();
  bool setExhaustAirOffset(double exhaustAirOffset);
  void resetExhaustAirOffset();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
