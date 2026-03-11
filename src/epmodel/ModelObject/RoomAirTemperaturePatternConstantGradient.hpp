/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNCONSTANTGRADIENT_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNCONSTANTGRADIENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RoomAirTemperaturePatternConstantGradient_Impl;
}

class EPMODEL_API RoomAirTemperaturePatternConstantGradient : public ModelObject
{
 public:
  explicit RoomAirTemperaturePatternConstantGradient(const Model& model);

  virtual ~RoomAirTemperaturePatternConstantGradient() override = default;
  RoomAirTemperaturePatternConstantGradient(const RoomAirTemperaturePatternConstantGradient& other) = default;
  RoomAirTemperaturePatternConstantGradient(RoomAirTemperaturePatternConstantGradient&& other) = default;
  RoomAirTemperaturePatternConstantGradient& operator=(const RoomAirTemperaturePatternConstantGradient&) = default;
  RoomAirTemperaturePatternConstantGradient& operator=(RoomAirTemperaturePatternConstantGradient&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class and accessor naming.
  // - Field Mapping: controlIntegerforPatternControlScheduleName, thermostatOffset, returnAirOffset, exhaustAirOffset,
  //   and temperatureGradient map directly to EnergyPlus RoomAir:TemperaturePattern:ConstantGradient scalar fields.
  // - Field Mapping: Name is intentionally omitted here and remains provided by ModelObject base name APIs.
  // - TODO(parity): Add relationship APIs if future schema introduces non-scalar links for this object.
  int controlIntegerforPatternControlScheduleName() const;
  boost::optional<double> thermostatOffset() const;
  boost::optional<double> returnAirOffset() const;
  boost::optional<double> exhaustAirOffset() const;
  boost::optional<double> temperatureGradient() const;

  bool setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName);
  bool setThermostatOffset(double thermostatOffset);
  void resetThermostatOffset();
  bool setReturnAirOffset(double returnAirOffset);
  void resetReturnAirOffset();
  bool setExhaustAirOffset(double exhaustAirOffset);
  void resetExhaustAirOffset();
  bool setTemperatureGradient(double temperatureGradient);
  void resetTemperatureGradient();

 protected:
  using ImplType = detail::RoomAirTemperaturePatternConstantGradient_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RoomAirTemperaturePatternConstantGradient(std::shared_ptr<detail::RoomAirTemperaturePatternConstantGradient_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
