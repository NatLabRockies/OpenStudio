/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirTemperaturePatternSurfaceMapping.hpp"
#include "RoomAirTemperaturePatternSurfaceMapping_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RoomAir_TemperaturePattern_SurfaceMapping_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

RoomAirTemperaturePatternSurfaceMapping::RoomAirTemperaturePatternSurfaceMapping(const Model& model)
  : ModelObject(RoomAirTemperaturePatternSurfaceMapping::iddObjectType(), model) {}

RoomAirTemperaturePatternSurfaceMapping::RoomAirTemperaturePatternSurfaceMapping(
  std::shared_ptr<detail::RoomAirTemperaturePatternSurfaceMapping_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RoomAirTemperaturePatternSurfaceMapping::iddObjectType() {
  return IddObjectType::RoomAir_TemperaturePattern_SurfaceMapping;
}

int RoomAirTemperaturePatternSurfaceMapping::controlIntegerforPatternControlScheduleName() const {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->controlIntegerforPatternControlScheduleName();
}

boost::optional<double> RoomAirTemperaturePatternSurfaceMapping::thermostatOffset() const {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->thermostatOffset();
}

boost::optional<double> RoomAirTemperaturePatternSurfaceMapping::returnAirOffset() const {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->returnAirOffset();
}

boost::optional<double> RoomAirTemperaturePatternSurfaceMapping::exhaustAirOffset() const {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->exhaustAirOffset();
}

bool RoomAirTemperaturePatternSurfaceMapping::setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName) {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->setControlIntegerforPatternControlScheduleName(
    controlIntegerforPatternControlScheduleName);
}

bool RoomAirTemperaturePatternSurfaceMapping::setThermostatOffset(double thermostatOffset) {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->setThermostatOffset(thermostatOffset);
}

void RoomAirTemperaturePatternSurfaceMapping::resetThermostatOffset() {
  getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->resetThermostatOffset();
}

bool RoomAirTemperaturePatternSurfaceMapping::setReturnAirOffset(double returnAirOffset) {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->setReturnAirOffset(returnAirOffset);
}

void RoomAirTemperaturePatternSurfaceMapping::resetReturnAirOffset() {
  getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->resetReturnAirOffset();
}

bool RoomAirTemperaturePatternSurfaceMapping::setExhaustAirOffset(double exhaustAirOffset) {
  return getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->setExhaustAirOffset(exhaustAirOffset);
}

void RoomAirTemperaturePatternSurfaceMapping::resetExhaustAirOffset() {
  getImpl<detail::RoomAirTemperaturePatternSurfaceMapping_Impl>()->resetExhaustAirOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

int RoomAirTemperaturePatternSurfaceMapping_Impl::controlIntegerforPatternControlScheduleName() const {
  const auto value = getInt(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ControlIntegerforPatternControlScheduleName, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> RoomAirTemperaturePatternSurfaceMapping_Impl::thermostatOffset() const {
  return getDouble(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ThermostatOffset, true);
}

boost::optional<double> RoomAirTemperaturePatternSurfaceMapping_Impl::returnAirOffset() const {
  return getDouble(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ReturnAirOffset, true);
}

boost::optional<double> RoomAirTemperaturePatternSurfaceMapping_Impl::exhaustAirOffset() const {
  return getDouble(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ExhaustAirOffset, true);
}

bool RoomAirTemperaturePatternSurfaceMapping_Impl::setControlIntegerforPatternControlScheduleName(
  int controlIntegerforPatternControlScheduleName) {
  const bool result =
    setInt(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ControlIntegerforPatternControlScheduleName,
           controlIntegerforPatternControlScheduleName);
  OS_ASSERT(result);
  return result;
}

bool RoomAirTemperaturePatternSurfaceMapping_Impl::setThermostatOffset(double thermostatOffset) {
  const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ThermostatOffset, thermostatOffset);
  OS_ASSERT(result);
  return result;
}

void RoomAirTemperaturePatternSurfaceMapping_Impl::resetThermostatOffset() {
  const bool result = setString(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ThermostatOffset, "");
  OS_ASSERT(result);
}

bool RoomAirTemperaturePatternSurfaceMapping_Impl::setReturnAirOffset(double returnAirOffset) {
  const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ReturnAirOffset, returnAirOffset);
  OS_ASSERT(result);
  return result;
}

void RoomAirTemperaturePatternSurfaceMapping_Impl::resetReturnAirOffset() {
  const bool result = setString(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ReturnAirOffset, "");
  OS_ASSERT(result);
}

bool RoomAirTemperaturePatternSurfaceMapping_Impl::setExhaustAirOffset(double exhaustAirOffset) {
  const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ExhaustAirOffset, exhaustAirOffset);
  OS_ASSERT(result);
  return result;
}

void RoomAirTemperaturePatternSurfaceMapping_Impl::resetExhaustAirOffset() {
  const bool result = setString(openstudio::RoomAir_TemperaturePattern_SurfaceMappingFields::ExhaustAirOffset, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
