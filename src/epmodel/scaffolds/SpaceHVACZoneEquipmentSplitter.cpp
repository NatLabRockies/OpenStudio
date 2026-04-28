/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceHVACZoneEquipmentSplitter.hpp"
#include "SpaceHVACZoneEquipmentSplitter_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddKey.hpp>
#include <utilities/idd/SpaceHVAC_ZoneEquipmentSplitter_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SpaceHVACZoneEquipmentSplitter::SpaceHVACZoneEquipmentSplitter(const Model& model)
  : ModelObject(SpaceHVACZoneEquipmentSplitter::iddObjectType(), model) {}

SpaceHVACZoneEquipmentSplitter::SpaceHVACZoneEquipmentSplitter(std::shared_ptr<detail::SpaceHVACZoneEquipmentSplitter_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SpaceHVACZoneEquipmentSplitter::iddObjectType() {
  return IddObjectType::SpaceHVAC_ZoneEquipmentSplitter;
}

std::vector<std::string> SpaceHVACZoneEquipmentSplitter::zoneEquipmentObjectTypeValues() {
  const auto iddObject = IddFactory::instance().getObject(iddObjectType());
  OS_ASSERT(iddObject);
  const auto iddField = iddObject->getField(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ZoneEquipmentObjectType);
  OS_ASSERT(iddField);
  std::vector<std::string> result;
  for (const auto& key : iddField->keys()) {
    result.emplace_back(key.name());
  }
  return result;
}

std::vector<std::string> SpaceHVACZoneEquipmentSplitter::thermostatControlMethodValues() {
  return {"SingleSpace", "Maximum", "Ideal"};
}

std::vector<std::string> SpaceHVACZoneEquipmentSplitter::spaceFractionMethodValues() {
  return {"DesignCoolingLoad", "DesignHeatingLoad", "FloorArea", "Volume", "PerimeterLength"};
}

std::string SpaceHVACZoneEquipmentSplitter::zoneEquipmentObjectType() const {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->zoneEquipmentObjectType();
}

bool SpaceHVACZoneEquipmentSplitter::setZoneEquipmentObjectType(const std::string& zoneEquipmentObjectType) {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->setZoneEquipmentObjectType(zoneEquipmentObjectType);
}

std::string SpaceHVACZoneEquipmentSplitter::thermostatControlMethod() const {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->thermostatControlMethod();
}

bool SpaceHVACZoneEquipmentSplitter::isThermostatControlMethodDefaulted() const {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->isThermostatControlMethodDefaulted();
}

bool SpaceHVACZoneEquipmentSplitter::setThermostatControlMethod(const std::string& thermostatControlMethod) {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->setThermostatControlMethod(thermostatControlMethod);
}

void SpaceHVACZoneEquipmentSplitter::resetThermostatControlMethod() {
  getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->resetThermostatControlMethod();
}

std::string SpaceHVACZoneEquipmentSplitter::spaceFractionMethod() const {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->spaceFractionMethod();
}

bool SpaceHVACZoneEquipmentSplitter::isSpaceFractionMethodDefaulted() const {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->isSpaceFractionMethodDefaulted();
}

bool SpaceHVACZoneEquipmentSplitter::setSpaceFractionMethod(const std::string& spaceFractionMethod) {
  return getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->setSpaceFractionMethod(spaceFractionMethod);
}

void SpaceHVACZoneEquipmentSplitter::resetSpaceFractionMethod() {
  getImpl<detail::SpaceHVACZoneEquipmentSplitter_Impl>()->resetSpaceFractionMethod();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string SpaceHVACZoneEquipmentSplitter_Impl::zoneEquipmentObjectType() const {
  const auto value = getString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ZoneEquipmentObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool SpaceHVACZoneEquipmentSplitter_Impl::setZoneEquipmentObjectType(const std::string& zoneEquipmentObjectType) {
  return setString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ZoneEquipmentObjectType, zoneEquipmentObjectType);
}

std::string SpaceHVACZoneEquipmentSplitter_Impl::thermostatControlMethod() const {
  const auto value = getString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ThermostatControlMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SpaceHVACZoneEquipmentSplitter_Impl::isThermostatControlMethodDefaulted() const {
  return isEmpty(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ThermostatControlMethod);
}

bool SpaceHVACZoneEquipmentSplitter_Impl::setThermostatControlMethod(const std::string& thermostatControlMethod) {
  return setString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ThermostatControlMethod, thermostatControlMethod);
}

void SpaceHVACZoneEquipmentSplitter_Impl::resetThermostatControlMethod() {
  OS_ASSERT(setString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::ThermostatControlMethod, ""));
}

std::string SpaceHVACZoneEquipmentSplitter_Impl::spaceFractionMethod() const {
  const auto value = getString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::SpaceFractionMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool SpaceHVACZoneEquipmentSplitter_Impl::isSpaceFractionMethodDefaulted() const {
  return isEmpty(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::SpaceFractionMethod);
}

bool SpaceHVACZoneEquipmentSplitter_Impl::setSpaceFractionMethod(const std::string& spaceFractionMethod) {
  return setString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::SpaceFractionMethod, spaceFractionMethod);
}

void SpaceHVACZoneEquipmentSplitter_Impl::resetSpaceFractionMethod() {
  OS_ASSERT(setString(openstudio::SpaceHVAC_ZoneEquipmentSplitterFields::SpaceFractionMethod, ""));
}

std::vector<std::string> SpaceHVACZoneEquipmentSplitter_Impl::zoneEquipmentObjectTypeValues() const {
  return openstudio::epmodel::SpaceHVACZoneEquipmentSplitter::zoneEquipmentObjectTypeValues();
}

std::vector<std::string> SpaceHVACZoneEquipmentSplitter_Impl::thermostatControlMethodValues() const {
  return openstudio::epmodel::SpaceHVACZoneEquipmentSplitter::thermostatControlMethodValues();
}

std::vector<std::string> SpaceHVACZoneEquipmentSplitter_Impl::spaceFractionMethodValues() const {
  return openstudio::epmodel::SpaceHVACZoneEquipmentSplitter::spaceFractionMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
