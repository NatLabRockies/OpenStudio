/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FloorInterzone.hpp"
#include "FloorInterzone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Floor_Interzone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FloorInterzone::FloorInterzone(const Model& model) : ModelObject(FloorInterzone::iddObjectType(), model) {}

FloorInterzone::FloorInterzone(std::shared_ptr<detail::FloorInterzone_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType FloorInterzone::iddObjectType() {
  return IddObjectType::Floor_Interzone;
}

boost::optional<double> FloorInterzone::azimuthAngle() const {
  return getImpl<detail::FloorInterzone_Impl>()->azimuthAngle();
}

bool FloorInterzone::setAzimuthAngle(double azimuthAngle) {
  return getImpl<detail::FloorInterzone_Impl>()->setAzimuthAngle(azimuthAngle);
}

void FloorInterzone::resetAzimuthAngle() {
  getImpl<detail::FloorInterzone_Impl>()->resetAzimuthAngle();
}

double FloorInterzone::tiltAngle() const {
  return getImpl<detail::FloorInterzone_Impl>()->tiltAngle();
}

bool FloorInterzone::isTiltAngleDefaulted() const {
  return getImpl<detail::FloorInterzone_Impl>()->isTiltAngleDefaulted();
}

bool FloorInterzone::setTiltAngle(double tiltAngle) {
  return getImpl<detail::FloorInterzone_Impl>()->setTiltAngle(tiltAngle);
}

void FloorInterzone::resetTiltAngle() {
  getImpl<detail::FloorInterzone_Impl>()->resetTiltAngle();
}

boost::optional<double> FloorInterzone::startingXCoordinate() const {
  return getImpl<detail::FloorInterzone_Impl>()->startingXCoordinate();
}

bool FloorInterzone::setStartingXCoordinate(double startingXCoordinate) {
  return getImpl<detail::FloorInterzone_Impl>()->setStartingXCoordinate(startingXCoordinate);
}

void FloorInterzone::resetStartingXCoordinate() {
  getImpl<detail::FloorInterzone_Impl>()->resetStartingXCoordinate();
}

boost::optional<double> FloorInterzone::startingYCoordinate() const {
  return getImpl<detail::FloorInterzone_Impl>()->startingYCoordinate();
}

bool FloorInterzone::setStartingYCoordinate(double startingYCoordinate) {
  return getImpl<detail::FloorInterzone_Impl>()->setStartingYCoordinate(startingYCoordinate);
}

void FloorInterzone::resetStartingYCoordinate() {
  getImpl<detail::FloorInterzone_Impl>()->resetStartingYCoordinate();
}

boost::optional<double> FloorInterzone::startingZCoordinate() const {
  return getImpl<detail::FloorInterzone_Impl>()->startingZCoordinate();
}

bool FloorInterzone::setStartingZCoordinate(double startingZCoordinate) {
  return getImpl<detail::FloorInterzone_Impl>()->setStartingZCoordinate(startingZCoordinate);
}

void FloorInterzone::resetStartingZCoordinate() {
  getImpl<detail::FloorInterzone_Impl>()->resetStartingZCoordinate();
}

boost::optional<double> FloorInterzone::length() const {
  return getImpl<detail::FloorInterzone_Impl>()->length();
}

bool FloorInterzone::setLength(double length) {
  return getImpl<detail::FloorInterzone_Impl>()->setLength(length);
}

void FloorInterzone::resetLength() {
  getImpl<detail::FloorInterzone_Impl>()->resetLength();
}

boost::optional<double> FloorInterzone::width() const {
  return getImpl<detail::FloorInterzone_Impl>()->width();
}

bool FloorInterzone::setWidth(double width) {
  return getImpl<detail::FloorInterzone_Impl>()->setWidth(width);
}

void FloorInterzone::resetWidth() {
  getImpl<detail::FloorInterzone_Impl>()->resetWidth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> FloorInterzone_Impl::azimuthAngle() const {
  return getDouble(openstudio::Floor_InterzoneFields::AzimuthAngle, true);
}

bool FloorInterzone_Impl::setAzimuthAngle(double azimuthAngle) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::AzimuthAngle, azimuthAngle);
  return result;
}

void FloorInterzone_Impl::resetAzimuthAngle() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::AzimuthAngle, ""));
}

double FloorInterzone_Impl::tiltAngle() const {
  const auto value = getDouble(openstudio::Floor_InterzoneFields::TiltAngle, true);
  OS_ASSERT(value);
  return *value;
}

bool FloorInterzone_Impl::isTiltAngleDefaulted() const {
  return isEmpty(openstudio::Floor_InterzoneFields::TiltAngle);
}

bool FloorInterzone_Impl::setTiltAngle(double tiltAngle) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::TiltAngle, tiltAngle);
  return result;
}

void FloorInterzone_Impl::resetTiltAngle() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::TiltAngle, ""));
}

boost::optional<double> FloorInterzone_Impl::startingXCoordinate() const {
  return getDouble(openstudio::Floor_InterzoneFields::StartingXCoordinate, true);
}

bool FloorInterzone_Impl::setStartingXCoordinate(double startingXCoordinate) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::StartingXCoordinate, startingXCoordinate);
  OS_ASSERT(result);
  return result;
}

void FloorInterzone_Impl::resetStartingXCoordinate() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::StartingXCoordinate, ""));
}

boost::optional<double> FloorInterzone_Impl::startingYCoordinate() const {
  return getDouble(openstudio::Floor_InterzoneFields::StartingYCoordinate, true);
}

bool FloorInterzone_Impl::setStartingYCoordinate(double startingYCoordinate) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::StartingYCoordinate, startingYCoordinate);
  OS_ASSERT(result);
  return result;
}

void FloorInterzone_Impl::resetStartingYCoordinate() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::StartingYCoordinate, ""));
}

boost::optional<double> FloorInterzone_Impl::startingZCoordinate() const {
  return getDouble(openstudio::Floor_InterzoneFields::StartingZCoordinate, true);
}

bool FloorInterzone_Impl::setStartingZCoordinate(double startingZCoordinate) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::StartingZCoordinate, startingZCoordinate);
  OS_ASSERT(result);
  return result;
}

void FloorInterzone_Impl::resetStartingZCoordinate() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::StartingZCoordinate, ""));
}

boost::optional<double> FloorInterzone_Impl::length() const {
  return getDouble(openstudio::Floor_InterzoneFields::Length, true);
}

bool FloorInterzone_Impl::setLength(double length) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::Length, length);
  OS_ASSERT(result);
  return result;
}

void FloorInterzone_Impl::resetLength() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::Length, ""));
}

boost::optional<double> FloorInterzone_Impl::width() const {
  return getDouble(openstudio::Floor_InterzoneFields::Width, true);
}

bool FloorInterzone_Impl::setWidth(double width) {
  const bool result = setDouble(openstudio::Floor_InterzoneFields::Width, width);
  OS_ASSERT(result);
  return result;
}

void FloorInterzone_Impl::resetWidth() {
  OS_ASSERT(setString(openstudio::Floor_InterzoneFields::Width, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
