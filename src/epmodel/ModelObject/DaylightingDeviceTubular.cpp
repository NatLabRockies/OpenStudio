/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DaylightingDeviceTubular.hpp"
#include "DaylightingDeviceTubular_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DaylightingDevice_Tubular_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DaylightingDeviceTubular::DaylightingDeviceTubular(const Model& model) : ModelObject(DaylightingDeviceTubular::iddObjectType(), model) {
  // Keep required scalar fields populated for strict non-optional getters.
  OS_ASSERT(setDiameter(0.3556));
  OS_ASSERT(setTotalLength(1.4));
}

DaylightingDeviceTubular::DaylightingDeviceTubular(std::shared_ptr<detail::DaylightingDeviceTubular_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DaylightingDeviceTubular::iddObjectType() {
  return IddObjectType::DaylightingDevice_Tubular;
}

double DaylightingDeviceTubular::diameter() const {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->diameter();
}

bool DaylightingDeviceTubular::setDiameter(double diameter) {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->setDiameter(diameter);
}

double DaylightingDeviceTubular::totalLength() const {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->totalLength();
}

bool DaylightingDeviceTubular::setTotalLength(double totalLength) {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->setTotalLength(totalLength);
}

double DaylightingDeviceTubular::effectiveThermalResistance() const {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->effectiveThermalResistance();
}

bool DaylightingDeviceTubular::isEffectiveThermalResistanceDefaulted() const {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->isEffectiveThermalResistanceDefaulted();
}

bool DaylightingDeviceTubular::setEffectiveThermalResistance(double effectiveThermalResistance) {
  return getImpl<detail::DaylightingDeviceTubular_Impl>()->setEffectiveThermalResistance(effectiveThermalResistance);
}

void DaylightingDeviceTubular::resetEffectiveThermalResistance() {
  getImpl<detail::DaylightingDeviceTubular_Impl>()->resetEffectiveThermalResistance();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double DaylightingDeviceTubular_Impl::diameter() const {
  const auto value = getDouble(openstudio::DaylightingDevice_TubularFields::Diameter, true);
  OS_ASSERT(value);
  return *value;
}

bool DaylightingDeviceTubular_Impl::setDiameter(double diameter) {
  return setDouble(openstudio::DaylightingDevice_TubularFields::Diameter, diameter);
}

double DaylightingDeviceTubular_Impl::totalLength() const {
  const auto value = getDouble(openstudio::DaylightingDevice_TubularFields::TotalLength, true);
  OS_ASSERT(value);
  return *value;
}

bool DaylightingDeviceTubular_Impl::setTotalLength(double totalLength) {
  return setDouble(openstudio::DaylightingDevice_TubularFields::TotalLength, totalLength);
}

double DaylightingDeviceTubular_Impl::effectiveThermalResistance() const {
  const auto value = getDouble(openstudio::DaylightingDevice_TubularFields::EffectiveThermalResistance, true);
  OS_ASSERT(value);
  return *value;
}

bool DaylightingDeviceTubular_Impl::isEffectiveThermalResistanceDefaulted() const {
  return isEmpty(openstudio::DaylightingDevice_TubularFields::EffectiveThermalResistance);
}

bool DaylightingDeviceTubular_Impl::setEffectiveThermalResistance(double effectiveThermalResistance) {
  return setDouble(openstudio::DaylightingDevice_TubularFields::EffectiveThermalResistance, effectiveThermalResistance);
}

void DaylightingDeviceTubular_Impl::resetEffectiveThermalResistance() {
  OS_ASSERT(setString(openstudio::DaylightingDevice_TubularFields::EffectiveThermalResistance, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
