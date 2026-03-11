/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingSite.hpp"
#include "ShadingSite_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Site_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadingSite::ShadingSite(const Model& model) : ModelObject(ShadingSite::iddObjectType(), model) {}

ShadingSite::ShadingSite(std::shared_ptr<detail::ShadingSite_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ShadingSite::iddObjectType() {
  return IddObjectType::Shading_Site;
}

boost::optional<double> ShadingSite::azimuthAngle() const {
  return getImpl<detail::ShadingSite_Impl>()->azimuthAngle();
}

bool ShadingSite::setAzimuthAngle(double azimuthAngle) {
  return getImpl<detail::ShadingSite_Impl>()->setAzimuthAngle(azimuthAngle);
}

void ShadingSite::resetAzimuthAngle() {
  getImpl<detail::ShadingSite_Impl>()->resetAzimuthAngle();
}

double ShadingSite::tiltAngle() const {
  return getImpl<detail::ShadingSite_Impl>()->tiltAngle();
}

bool ShadingSite::isTiltAngleDefaulted() const {
  return getImpl<detail::ShadingSite_Impl>()->isTiltAngleDefaulted();
}

bool ShadingSite::setTiltAngle(double tiltAngle) {
  return getImpl<detail::ShadingSite_Impl>()->setTiltAngle(tiltAngle);
}

void ShadingSite::resetTiltAngle() {
  getImpl<detail::ShadingSite_Impl>()->resetTiltAngle();
}

boost::optional<double> ShadingSite::startingXCoordinate() const {
  return getImpl<detail::ShadingSite_Impl>()->startingXCoordinate();
}

bool ShadingSite::setStartingXCoordinate(double startingXCoordinate) {
  return getImpl<detail::ShadingSite_Impl>()->setStartingXCoordinate(startingXCoordinate);
}

void ShadingSite::resetStartingXCoordinate() {
  getImpl<detail::ShadingSite_Impl>()->resetStartingXCoordinate();
}

boost::optional<double> ShadingSite::startingYCoordinate() const {
  return getImpl<detail::ShadingSite_Impl>()->startingYCoordinate();
}

bool ShadingSite::setStartingYCoordinate(double startingYCoordinate) {
  return getImpl<detail::ShadingSite_Impl>()->setStartingYCoordinate(startingYCoordinate);
}

void ShadingSite::resetStartingYCoordinate() {
  getImpl<detail::ShadingSite_Impl>()->resetStartingYCoordinate();
}

boost::optional<double> ShadingSite::startingZCoordinate() const {
  return getImpl<detail::ShadingSite_Impl>()->startingZCoordinate();
}

bool ShadingSite::setStartingZCoordinate(double startingZCoordinate) {
  return getImpl<detail::ShadingSite_Impl>()->setStartingZCoordinate(startingZCoordinate);
}

void ShadingSite::resetStartingZCoordinate() {
  getImpl<detail::ShadingSite_Impl>()->resetStartingZCoordinate();
}

boost::optional<double> ShadingSite::length() const {
  return getImpl<detail::ShadingSite_Impl>()->length();
}

bool ShadingSite::setLength(double length) {
  return getImpl<detail::ShadingSite_Impl>()->setLength(length);
}

void ShadingSite::resetLength() {
  getImpl<detail::ShadingSite_Impl>()->resetLength();
}

boost::optional<double> ShadingSite::height() const {
  return getImpl<detail::ShadingSite_Impl>()->height();
}

bool ShadingSite::setHeight(double height) {
  return getImpl<detail::ShadingSite_Impl>()->setHeight(height);
}

void ShadingSite::resetHeight() {
  getImpl<detail::ShadingSite_Impl>()->resetHeight();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ShadingSite_Impl::azimuthAngle() const {
  return getDouble(openstudio::Shading_SiteFields::AzimuthAngle, true);
}

bool ShadingSite_Impl::setAzimuthAngle(double azimuthAngle) {
  return setDouble(openstudio::Shading_SiteFields::AzimuthAngle, azimuthAngle);
}

void ShadingSite_Impl::resetAzimuthAngle() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::AzimuthAngle, ""));
}

double ShadingSite_Impl::tiltAngle() const {
  const auto value = getDouble(openstudio::Shading_SiteFields::TiltAngle, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingSite_Impl::isTiltAngleDefaulted() const {
  return !getDouble(openstudio::Shading_SiteFields::TiltAngle, false);
}

bool ShadingSite_Impl::setTiltAngle(double tiltAngle) {
  return setDouble(openstudio::Shading_SiteFields::TiltAngle, tiltAngle);
}

void ShadingSite_Impl::resetTiltAngle() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::TiltAngle, ""));
}

boost::optional<double> ShadingSite_Impl::startingXCoordinate() const {
  return getDouble(openstudio::Shading_SiteFields::StartingXCoordinate, true);
}

bool ShadingSite_Impl::setStartingXCoordinate(double startingXCoordinate) {
  const bool result = setDouble(openstudio::Shading_SiteFields::StartingXCoordinate, startingXCoordinate);
  OS_ASSERT(result);
  return result;
}

void ShadingSite_Impl::resetStartingXCoordinate() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::StartingXCoordinate, ""));
}

boost::optional<double> ShadingSite_Impl::startingYCoordinate() const {
  return getDouble(openstudio::Shading_SiteFields::StartingYCoordinate, true);
}

bool ShadingSite_Impl::setStartingYCoordinate(double startingYCoordinate) {
  const bool result = setDouble(openstudio::Shading_SiteFields::StartingYCoordinate, startingYCoordinate);
  OS_ASSERT(result);
  return result;
}

void ShadingSite_Impl::resetStartingYCoordinate() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::StartingYCoordinate, ""));
}

boost::optional<double> ShadingSite_Impl::startingZCoordinate() const {
  return getDouble(openstudio::Shading_SiteFields::StartingZCoordinate, true);
}

bool ShadingSite_Impl::setStartingZCoordinate(double startingZCoordinate) {
  const bool result = setDouble(openstudio::Shading_SiteFields::StartingZCoordinate, startingZCoordinate);
  OS_ASSERT(result);
  return result;
}

void ShadingSite_Impl::resetStartingZCoordinate() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::StartingZCoordinate, ""));
}

boost::optional<double> ShadingSite_Impl::length() const {
  return getDouble(openstudio::Shading_SiteFields::Length, true);
}

bool ShadingSite_Impl::setLength(double length) {
  const bool result = setDouble(openstudio::Shading_SiteFields::Length, length);
  OS_ASSERT(result);
  return result;
}

void ShadingSite_Impl::resetLength() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::Length, ""));
}

boost::optional<double> ShadingSite_Impl::height() const {
  return getDouble(openstudio::Shading_SiteFields::Height, true);
}

bool ShadingSite_Impl::setHeight(double height) {
  const bool result = setDouble(openstudio::Shading_SiteFields::Height, height);
  OS_ASSERT(result);
  return result;
}

void ShadingSite_Impl::resetHeight() {
  OS_ASSERT(setString(openstudio::Shading_SiteFields::Height, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
