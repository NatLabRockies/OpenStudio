/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/Site.hpp"
#include "ParentObject/Site_Impl.hpp"

#include "Model.hpp"
#include "ParentObject/Building.hpp"
#include "ParentObject/Building_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Building_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Site_Location_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

Site::Site(const Model& model) : ParentObject(Site::iddObjectType(), model) {}

Site::Site(std::shared_ptr<detail::Site_Impl> impl) : ParentObject(std::move(impl)) {}

IddObjectType Site::iddObjectType() {
  return IddObjectType::Site_Location;
}

std::vector<std::string> Site::validTerrainValues() {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::Building).get(), openstudio::BuildingFields::Terrain);
}

double Site::latitude() const {
  return getImpl<detail::Site_Impl>()->latitude();
}

bool Site::isLatitudeDefaulted() const {
  return getImpl<detail::Site_Impl>()->isLatitudeDefaulted();
}

bool Site::setLatitude(double latitude) {
  return getImpl<detail::Site_Impl>()->setLatitude(latitude);
}

void Site::resetLatitude() {
  getImpl<detail::Site_Impl>()->resetLatitude();
}

double Site::longitude() const {
  return getImpl<detail::Site_Impl>()->longitude();
}

bool Site::isLongitudeDefaulted() const {
  return getImpl<detail::Site_Impl>()->isLongitudeDefaulted();
}

bool Site::setLongitude(double longitude) {
  return getImpl<detail::Site_Impl>()->setLongitude(longitude);
}

void Site::resetLongitude() {
  getImpl<detail::Site_Impl>()->resetLongitude();
}

double Site::timeZone() const {
  return getImpl<detail::Site_Impl>()->timeZone();
}

bool Site::isTimeZoneDefaulted() const {
  return getImpl<detail::Site_Impl>()->isTimeZoneDefaulted();
}

bool Site::setTimeZone(double timeZone) {
  return getImpl<detail::Site_Impl>()->setTimeZone(timeZone);
}

void Site::resetTimeZone() {
  getImpl<detail::Site_Impl>()->resetTimeZone();
}

double Site::elevation() const {
  return getImpl<detail::Site_Impl>()->elevation();
}

bool Site::isElevationDefaulted() const {
  return getImpl<detail::Site_Impl>()->isElevationDefaulted();
}

bool Site::setElevation(double elevation) {
  return getImpl<detail::Site_Impl>()->setElevation(elevation);
}

void Site::resetElevation() {
  getImpl<detail::Site_Impl>()->resetElevation();
}

std::string Site::terrain() const {
  return getImpl<detail::Site_Impl>()->terrain();
}

bool Site::isTerrainDefaulted() const {
  return getImpl<detail::Site_Impl>()->isTerrainDefaulted();
}

bool Site::setTerrain(const std::string& terrain) {
  return getImpl<detail::Site_Impl>()->setTerrain(terrain);
}

void Site::resetTerrain() {
  getImpl<detail::Site_Impl>()->resetTerrain();
}

bool Site::keepSiteLocationInformation() const {
  return getImpl<detail::Site_Impl>()->keepSiteLocationInformation();
}

bool Site::isKeepSiteLocationInformationDefaulted() const {
  return getImpl<detail::Site_Impl>()->isKeepSiteLocationInformationDefaulted();
}

bool Site::setKeepSiteLocationInformation(bool keepSiteLocationInformation) {
  return getImpl<detail::Site_Impl>()->setKeepSiteLocationInformation(keepSiteLocationInformation);
}

void Site::resetKeepSiteLocationInformation() {
  getImpl<detail::Site_Impl>()->resetKeepSiteLocationInformation();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

boost::optional<openstudio::epmodel::Building> optionalBuildingForSite(const openstudio::epmodel::Model& model) {
  auto buildings = model.getConcreteModelObjects<openstudio::epmodel::Building>();
  if (!buildings.empty()) {
    return buildings.front();
  }
  return boost::none;
}

openstudio::epmodel::Building ensureBuildingForSite(openstudio::epmodel::Model model) {
  if (auto existing = optionalBuildingForSite(model)) {
    return *existing;
  }
  return model.getUniqueModelObject<Building>();
}

std::string defaultBuildingTerrain() {
  const auto iddObject = IddFactory::instance().getObject(IddObjectType::Building);
  OS_ASSERT(iddObject);
  const auto iddField = iddObject->getField(static_cast<unsigned>(openstudio::BuildingFields::Terrain));
  OS_ASSERT(iddField);
  const auto defaultValue = iddField->properties().stringDefault;
  OS_ASSERT(defaultValue);
  return *defaultValue;
}

}  // namespace

double Site_Impl::latitude() const {
  const auto value = getDouble(openstudio::Site_LocationFields::Latitude, true);
  OS_ASSERT(value);
  return *value;
}

bool Site_Impl::isLatitudeDefaulted() const {
  return isEmpty(openstudio::Site_LocationFields::Latitude);
}

bool Site_Impl::setLatitude(double latitude) {
  return setDouble(openstudio::Site_LocationFields::Latitude, latitude);
}

void Site_Impl::resetLatitude() {
  OS_ASSERT(setString(openstudio::Site_LocationFields::Latitude, ""));
}

double Site_Impl::longitude() const {
  const auto value = getDouble(openstudio::Site_LocationFields::Longitude, true);
  OS_ASSERT(value);
  return *value;
}

bool Site_Impl::isLongitudeDefaulted() const {
  return isEmpty(openstudio::Site_LocationFields::Longitude);
}

bool Site_Impl::setLongitude(double longitude) {
  return setDouble(openstudio::Site_LocationFields::Longitude, longitude);
}

void Site_Impl::resetLongitude() {
  OS_ASSERT(setString(openstudio::Site_LocationFields::Longitude, ""));
}

double Site_Impl::timeZone() const {
  const auto value = getDouble(openstudio::Site_LocationFields::TimeZone, true);
  OS_ASSERT(value);
  return *value;
}

bool Site_Impl::isTimeZoneDefaulted() const {
  return isEmpty(openstudio::Site_LocationFields::TimeZone);
}

bool Site_Impl::setTimeZone(double timeZone) {
  return setDouble(openstudio::Site_LocationFields::TimeZone, timeZone);
}

void Site_Impl::resetTimeZone() {
  OS_ASSERT(setString(openstudio::Site_LocationFields::TimeZone, ""));
}

double Site_Impl::elevation() const {
  const auto value = getDouble(openstudio::Site_LocationFields::Elevation, true);
  OS_ASSERT(value);
  return *value;
}

bool Site_Impl::isElevationDefaulted() const {
  return isEmpty(openstudio::Site_LocationFields::Elevation);
}

bool Site_Impl::setElevation(double elevation) {
  return setDouble(openstudio::Site_LocationFields::Elevation, elevation);
}

void Site_Impl::resetElevation() {
  OS_ASSERT(setString(openstudio::Site_LocationFields::Elevation, ""));
}

std::string Site_Impl::terrain() const {
  if (auto building = optionalBuildingForSite(model())) {
    if (auto value = building->getString(openstudio::BuildingFields::Terrain, true)) {
      return *value;
    }
  }

  return defaultBuildingTerrain();
}

bool Site_Impl::isTerrainDefaulted() const {
  if (auto building = optionalBuildingForSite(model())) {
    return building->isEmpty(openstudio::BuildingFields::Terrain);
  }
  return true;
}

bool Site_Impl::setTerrain(const std::string& terrain) {
  auto building = ensureBuildingForSite(model());
  return building.setString(openstudio::BuildingFields::Terrain, terrain);
}

void Site_Impl::resetTerrain() {
  auto building = ensureBuildingForSite(model());
  OS_ASSERT(building.setString(openstudio::BuildingFields::Terrain, ""));
}

bool Site_Impl::keepSiteLocationInformation() const {
  const auto value = getString(openstudio::Site_LocationFields::KeepSiteLocationInformation, true);
  OS_ASSERT(value);
  return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
}

bool Site_Impl::isKeepSiteLocationInformationDefaulted() const {
  return isEmpty(openstudio::Site_LocationFields::KeepSiteLocationInformation);
}

bool Site_Impl::setKeepSiteLocationInformation(bool keepSiteLocationInformation) {
  const bool result =
    setString(openstudio::Site_LocationFields::KeepSiteLocationInformation, keepSiteLocationInformation ? "Yes" : "No");
  OS_ASSERT(result);
  return result;
}

void Site_Impl::resetKeepSiteLocationInformation() {
  OS_ASSERT(setString(openstudio::Site_LocationFields::KeepSiteLocationInformation, ""));
}

std::vector<std::string> Site_Impl::validTerrainValues() const {
  return openstudio::epmodel::Site::validTerrainValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
