/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteWeatherStation.hpp"
#include "SiteWeatherStation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Site_WeatherStation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SiteWeatherStation::SiteWeatherStation(const Model& model) : ModelObject(SiteWeatherStation::iddObjectType(), model) {}

SiteWeatherStation::SiteWeatherStation(std::shared_ptr<detail::SiteWeatherStation_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType SiteWeatherStation::iddObjectType() {
  return IddObjectType::Site_WeatherStation;
}

double SiteWeatherStation::windSensorHeightAboveGround() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->windSensorHeightAboveGround();
}

bool SiteWeatherStation::isWindSensorHeightAboveGroundDefaulted() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->isWindSensorHeightAboveGroundDefaulted();
}

bool SiteWeatherStation::setWindSensorHeightAboveGround(double windSensorHeightAboveGround) {
  return getImpl<detail::SiteWeatherStation_Impl>()->setWindSensorHeightAboveGround(windSensorHeightAboveGround);
}

void SiteWeatherStation::resetWindSensorHeightAboveGround() {
  getImpl<detail::SiteWeatherStation_Impl>()->resetWindSensorHeightAboveGround();
}

double SiteWeatherStation::windSpeedProfileExponent() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->windSpeedProfileExponent();
}

bool SiteWeatherStation::isWindSpeedProfileExponentDefaulted() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->isWindSpeedProfileExponentDefaulted();
}

bool SiteWeatherStation::setWindSpeedProfileExponent(double windSpeedProfileExponent) {
  return getImpl<detail::SiteWeatherStation_Impl>()->setWindSpeedProfileExponent(windSpeedProfileExponent);
}

void SiteWeatherStation::resetWindSpeedProfileExponent() {
  getImpl<detail::SiteWeatherStation_Impl>()->resetWindSpeedProfileExponent();
}

double SiteWeatherStation::windSpeedProfileBoundaryLayerThickness() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->windSpeedProfileBoundaryLayerThickness();
}

bool SiteWeatherStation::isWindSpeedProfileBoundaryLayerThicknessDefaulted() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->isWindSpeedProfileBoundaryLayerThicknessDefaulted();
}

bool SiteWeatherStation::setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness) {
  return getImpl<detail::SiteWeatherStation_Impl>()->setWindSpeedProfileBoundaryLayerThickness(windSpeedProfileBoundaryLayerThickness);
}

void SiteWeatherStation::resetWindSpeedProfileBoundaryLayerThickness() {
  getImpl<detail::SiteWeatherStation_Impl>()->resetWindSpeedProfileBoundaryLayerThickness();
}

double SiteWeatherStation::airTemperatureSensorHeightAboveGround() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->airTemperatureSensorHeightAboveGround();
}

bool SiteWeatherStation::isAirTemperatureSensorHeightAboveGroundDefaulted() const {
  return getImpl<detail::SiteWeatherStation_Impl>()->isAirTemperatureSensorHeightAboveGroundDefaulted();
}

bool SiteWeatherStation::setAirTemperatureSensorHeightAboveGround(double airTemperatureSensorHeightAboveGround) {
  return getImpl<detail::SiteWeatherStation_Impl>()->setAirTemperatureSensorHeightAboveGround(airTemperatureSensorHeightAboveGround);
}

void SiteWeatherStation::resetAirTemperatureSensorHeightAboveGround() {
  getImpl<detail::SiteWeatherStation_Impl>()->resetAirTemperatureSensorHeightAboveGround();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SiteWeatherStation_Impl::windSensorHeightAboveGround() const {
  const auto value = getDouble(openstudio::Site_WeatherStationFields::WindSensorHeightAboveGround, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteWeatherStation_Impl::isWindSensorHeightAboveGroundDefaulted() const {
  return isEmpty(openstudio::Site_WeatherStationFields::WindSensorHeightAboveGround);
}

bool SiteWeatherStation_Impl::setWindSensorHeightAboveGround(double windSensorHeightAboveGround) {
  return setDouble(openstudio::Site_WeatherStationFields::WindSensorHeightAboveGround, windSensorHeightAboveGround);
}

void SiteWeatherStation_Impl::resetWindSensorHeightAboveGround() {
  OS_ASSERT(setString(openstudio::Site_WeatherStationFields::WindSensorHeightAboveGround, ""));
}

double SiteWeatherStation_Impl::windSpeedProfileExponent() const {
  const auto value = getDouble(openstudio::Site_WeatherStationFields::WindSpeedProfileExponent, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteWeatherStation_Impl::isWindSpeedProfileExponentDefaulted() const {
  return isEmpty(openstudio::Site_WeatherStationFields::WindSpeedProfileExponent);
}

bool SiteWeatherStation_Impl::setWindSpeedProfileExponent(double windSpeedProfileExponent) {
  return setDouble(openstudio::Site_WeatherStationFields::WindSpeedProfileExponent, windSpeedProfileExponent);
}

void SiteWeatherStation_Impl::resetWindSpeedProfileExponent() {
  OS_ASSERT(setString(openstudio::Site_WeatherStationFields::WindSpeedProfileExponent, ""));
}

double SiteWeatherStation_Impl::windSpeedProfileBoundaryLayerThickness() const {
  const auto value = getDouble(openstudio::Site_WeatherStationFields::WindSpeedProfileBoundaryLayerThickness, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteWeatherStation_Impl::isWindSpeedProfileBoundaryLayerThicknessDefaulted() const {
  return isEmpty(openstudio::Site_WeatherStationFields::WindSpeedProfileBoundaryLayerThickness);
}

bool SiteWeatherStation_Impl::setWindSpeedProfileBoundaryLayerThickness(double windSpeedProfileBoundaryLayerThickness) {
  return setDouble(openstudio::Site_WeatherStationFields::WindSpeedProfileBoundaryLayerThickness, windSpeedProfileBoundaryLayerThickness);
}

void SiteWeatherStation_Impl::resetWindSpeedProfileBoundaryLayerThickness() {
  OS_ASSERT(setString(openstudio::Site_WeatherStationFields::WindSpeedProfileBoundaryLayerThickness, ""));
}

double SiteWeatherStation_Impl::airTemperatureSensorHeightAboveGround() const {
  const auto value = getDouble(openstudio::Site_WeatherStationFields::AirTemperatureSensorHeightAboveGround, true);
  OS_ASSERT(value);
  return *value;
}

bool SiteWeatherStation_Impl::isAirTemperatureSensorHeightAboveGroundDefaulted() const {
  return isEmpty(openstudio::Site_WeatherStationFields::AirTemperatureSensorHeightAboveGround);
}

bool SiteWeatherStation_Impl::setAirTemperatureSensorHeightAboveGround(double airTemperatureSensorHeightAboveGround) {
  return setDouble(openstudio::Site_WeatherStationFields::AirTemperatureSensorHeightAboveGround, airTemperatureSensorHeightAboveGround);
}

void SiteWeatherStation_Impl::resetAirTemperatureSensorHeightAboveGround() {
  OS_ASSERT(setString(openstudio::Site_WeatherStationFields::AirTemperatureSensorHeightAboveGround, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
