/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNSURFACEMAPPING_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNSURFACEMAPPING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RoomAirTemperaturePatternSurfaceMapping_Impl;
}

class EPMODEL_API RoomAirTemperaturePatternSurfaceMapping : public ModelObject
{
 public:
  explicit RoomAirTemperaturePatternSurfaceMapping(const Model& model);

  virtual ~RoomAirTemperaturePatternSurfaceMapping() override = default;
  RoomAirTemperaturePatternSurfaceMapping(const RoomAirTemperaturePatternSurfaceMapping& other) = default;
  RoomAirTemperaturePatternSurfaceMapping(RoomAirTemperaturePatternSurfaceMapping&& other) = default;
  RoomAirTemperaturePatternSurfaceMapping& operator=(const RoomAirTemperaturePatternSurfaceMapping&) = default;
  RoomAirTemperaturePatternSurfaceMapping& operator=(RoomAirTemperaturePatternSurfaceMapping&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class and accessor naming.
  // - Field Mapping: controlIntegerforPatternControlScheduleName, thermostatOffset, returnAirOffset, and exhaustAirOffset
  //   map directly to EnergyPlus RoomAir:TemperaturePattern:SurfaceMapping non-extensible scalar fields.
  // - Field Mapping: Name is intentionally omitted here and remains provided by ModelObject base name APIs.
  // - TODO(parity): Add extensible APIs for Surface Name Pair / Delta Adjacent Air Temperature Pair when non-scalar/extensible support is added.
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

 protected:
  using ImplType = detail::RoomAirTemperaturePatternSurfaceMapping_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RoomAirTemperaturePatternSurfaceMapping(std::shared_ptr<detail::RoomAirTemperaturePatternSurfaceMapping_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
