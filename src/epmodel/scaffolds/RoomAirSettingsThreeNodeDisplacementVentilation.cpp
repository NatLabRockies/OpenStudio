/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirSettingsThreeNodeDisplacementVentilation.hpp"
#include "RoomAirSettingsThreeNodeDisplacementVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RoomAirSettings_ThreeNodeDisplacementVentilation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

RoomAirSettingsThreeNodeDisplacementVentilation::RoomAirSettingsThreeNodeDisplacementVentilation(const Model& model)
  : ModelObject(RoomAirSettingsThreeNodeDisplacementVentilation::iddObjectType(), model) {}

RoomAirSettingsThreeNodeDisplacementVentilation::RoomAirSettingsThreeNodeDisplacementVentilation(
  std::shared_ptr<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RoomAirSettingsThreeNodeDisplacementVentilation::iddObjectType() {
  return IddObjectType::RoomAirSettings_ThreeNodeDisplacementVentilation;
}

double RoomAirSettingsThreeNodeDisplacementVentilation::numberofPlumesperOccupant() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->numberofPlumesperOccupant();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::isNumberofPlumesperOccupantDefaulted() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->isNumberofPlumesperOccupantDefaulted();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::setNumberofPlumesperOccupant(double numberofPlumesperOccupant) {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->setNumberofPlumesperOccupant(numberofPlumesperOccupant);
}

void RoomAirSettingsThreeNodeDisplacementVentilation::resetNumberofPlumesperOccupant() {
  getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->resetNumberofPlumesperOccupant();
}

double RoomAirSettingsThreeNodeDisplacementVentilation::thermostatHeight() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->thermostatHeight();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::isThermostatHeightDefaulted() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->isThermostatHeightDefaulted();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::setThermostatHeight(double thermostatHeight) {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->setThermostatHeight(thermostatHeight);
}

void RoomAirSettingsThreeNodeDisplacementVentilation::resetThermostatHeight() {
  getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->resetThermostatHeight();
}

double RoomAirSettingsThreeNodeDisplacementVentilation::comfortHeight() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->comfortHeight();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::isComfortHeightDefaulted() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->isComfortHeightDefaulted();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::setComfortHeight(double comfortHeight) {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->setComfortHeight(comfortHeight);
}

void RoomAirSettingsThreeNodeDisplacementVentilation::resetComfortHeight() {
  getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->resetComfortHeight();
}

double RoomAirSettingsThreeNodeDisplacementVentilation::temperatureDifferenceThresholdforReporting() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->temperatureDifferenceThresholdforReporting();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::isTemperatureDifferenceThresholdforReportingDefaulted() const {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()
    ->isTemperatureDifferenceThresholdforReportingDefaulted();
}

bool RoomAirSettingsThreeNodeDisplacementVentilation::setTemperatureDifferenceThresholdforReporting(
  double temperatureDifferenceThresholdforReporting) {
  return getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->setTemperatureDifferenceThresholdforReporting(
    temperatureDifferenceThresholdforReporting);
}

void RoomAirSettingsThreeNodeDisplacementVentilation::resetTemperatureDifferenceThresholdforReporting() {
  getImpl<detail::RoomAirSettingsThreeNodeDisplacementVentilation_Impl>()->resetTemperatureDifferenceThresholdforReporting();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double RoomAirSettingsThreeNodeDisplacementVentilation_Impl::numberofPlumesperOccupant() const {
  const auto value = getDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::NumberofPlumesperOccupant, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::isNumberofPlumesperOccupantDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::NumberofPlumesperOccupant);
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::setNumberofPlumesperOccupant(double numberofPlumesperOccupant) {
  return setDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::NumberofPlumesperOccupant, numberofPlumesperOccupant);
}

void RoomAirSettingsThreeNodeDisplacementVentilation_Impl::resetNumberofPlumesperOccupant() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::NumberofPlumesperOccupant, ""));
}

double RoomAirSettingsThreeNodeDisplacementVentilation_Impl::thermostatHeight() const {
  const auto value = getDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ThermostatHeight, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::isThermostatHeightDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ThermostatHeight);
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::setThermostatHeight(double thermostatHeight) {
  return setDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ThermostatHeight, thermostatHeight);
}

void RoomAirSettingsThreeNodeDisplacementVentilation_Impl::resetThermostatHeight() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ThermostatHeight, ""));
}

double RoomAirSettingsThreeNodeDisplacementVentilation_Impl::comfortHeight() const {
  const auto value = getDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ComfortHeight, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::isComfortHeightDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ComfortHeight);
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::setComfortHeight(double comfortHeight) {
  return setDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ComfortHeight, comfortHeight);
}

void RoomAirSettingsThreeNodeDisplacementVentilation_Impl::resetComfortHeight() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::ComfortHeight, ""));
}

double RoomAirSettingsThreeNodeDisplacementVentilation_Impl::temperatureDifferenceThresholdforReporting() const {
  const auto value =
    getDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::TemperatureDifferenceThresholdforReporting, true);
  OS_ASSERT(value);
  return *value;
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::isTemperatureDifferenceThresholdforReportingDefaulted() const {
  return isEmpty(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::TemperatureDifferenceThresholdforReporting);
}

bool RoomAirSettingsThreeNodeDisplacementVentilation_Impl::setTemperatureDifferenceThresholdforReporting(
  double temperatureDifferenceThresholdforReporting) {
  return setDouble(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::TemperatureDifferenceThresholdforReporting,
                   temperatureDifferenceThresholdforReporting);
}

void RoomAirSettingsThreeNodeDisplacementVentilation_Impl::resetTemperatureDifferenceThresholdforReporting() {
  OS_ASSERT(setString(openstudio::RoomAirSettings_ThreeNodeDisplacementVentilationFields::TemperatureDifferenceThresholdforReporting, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
