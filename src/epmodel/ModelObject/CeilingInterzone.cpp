/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CeilingInterzone.hpp"
#include "CeilingInterzone_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Ceiling_Interzone_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CeilingInterzone::CeilingInterzone(const Model& model) : ModelObject(CeilingInterzone::iddObjectType(), model) {}

CeilingInterzone::CeilingInterzone(std::shared_ptr<detail::CeilingInterzone_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CeilingInterzone::iddObjectType() {
  return IddObjectType::Ceiling_Interzone;
}

boost::optional<double> CeilingInterzone::azimuthAngle() const {
  return getImpl<detail::CeilingInterzone_Impl>()->azimuthAngle();
}

bool CeilingInterzone::setAzimuthAngle(double azimuthAngle) {
  return getImpl<detail::CeilingInterzone_Impl>()->setAzimuthAngle(azimuthAngle);
}

void CeilingInterzone::resetAzimuthAngle() {
  getImpl<detail::CeilingInterzone_Impl>()->resetAzimuthAngle();
}

double CeilingInterzone::tiltAngle() const {
  return getImpl<detail::CeilingInterzone_Impl>()->tiltAngle();
}

bool CeilingInterzone::isTiltAngleDefaulted() const {
  return getImpl<detail::CeilingInterzone_Impl>()->isTiltAngleDefaulted();
}

bool CeilingInterzone::setTiltAngle(double tiltAngle) {
  return getImpl<detail::CeilingInterzone_Impl>()->setTiltAngle(tiltAngle);
}

void CeilingInterzone::resetTiltAngle() {
  getImpl<detail::CeilingInterzone_Impl>()->resetTiltAngle();
}

boost::optional<double> CeilingInterzone::startingXCoordinate() const {
  return getImpl<detail::CeilingInterzone_Impl>()->startingXCoordinate();
}

bool CeilingInterzone::setStartingXCoordinate(double startingXCoordinate) {
  return getImpl<detail::CeilingInterzone_Impl>()->setStartingXCoordinate(startingXCoordinate);
}

void CeilingInterzone::resetStartingXCoordinate() {
  getImpl<detail::CeilingInterzone_Impl>()->resetStartingXCoordinate();
}

boost::optional<double> CeilingInterzone::startingYCoordinate() const {
  return getImpl<detail::CeilingInterzone_Impl>()->startingYCoordinate();
}

bool CeilingInterzone::setStartingYCoordinate(double startingYCoordinate) {
  return getImpl<detail::CeilingInterzone_Impl>()->setStartingYCoordinate(startingYCoordinate);
}

void CeilingInterzone::resetStartingYCoordinate() {
  getImpl<detail::CeilingInterzone_Impl>()->resetStartingYCoordinate();
}

boost::optional<double> CeilingInterzone::startingZCoordinate() const {
  return getImpl<detail::CeilingInterzone_Impl>()->startingZCoordinate();
}

bool CeilingInterzone::setStartingZCoordinate(double startingZCoordinate) {
  return getImpl<detail::CeilingInterzone_Impl>()->setStartingZCoordinate(startingZCoordinate);
}

void CeilingInterzone::resetStartingZCoordinate() {
  getImpl<detail::CeilingInterzone_Impl>()->resetStartingZCoordinate();
}

boost::optional<double> CeilingInterzone::length() const {
  return getImpl<detail::CeilingInterzone_Impl>()->length();
}

bool CeilingInterzone::setLength(double length) {
  return getImpl<detail::CeilingInterzone_Impl>()->setLength(length);
}

void CeilingInterzone::resetLength() {
  getImpl<detail::CeilingInterzone_Impl>()->resetLength();
}

boost::optional<double> CeilingInterzone::width() const {
  return getImpl<detail::CeilingInterzone_Impl>()->width();
}

bool CeilingInterzone::setWidth(double width) {
  return getImpl<detail::CeilingInterzone_Impl>()->setWidth(width);
}

void CeilingInterzone::resetWidth() {
  getImpl<detail::CeilingInterzone_Impl>()->resetWidth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CeilingInterzone_Impl::azimuthAngle() const {
  return getDouble(openstudio::Ceiling_InterzoneFields::AzimuthAngle, true);
}

bool CeilingInterzone_Impl::setAzimuthAngle(double azimuthAngle) {
  return setDouble(openstudio::Ceiling_InterzoneFields::AzimuthAngle, azimuthAngle);
}

void CeilingInterzone_Impl::resetAzimuthAngle() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::AzimuthAngle, ""));
}

double CeilingInterzone_Impl::tiltAngle() const {
  const auto value = getDouble(openstudio::Ceiling_InterzoneFields::TiltAngle, true);
  OS_ASSERT(value);
  return *value;
}

bool CeilingInterzone_Impl::isTiltAngleDefaulted() const {
  return isEmpty(openstudio::Ceiling_InterzoneFields::TiltAngle);
}

bool CeilingInterzone_Impl::setTiltAngle(double tiltAngle) {
  return setDouble(openstudio::Ceiling_InterzoneFields::TiltAngle, tiltAngle);
}

void CeilingInterzone_Impl::resetTiltAngle() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::TiltAngle, ""));
}

boost::optional<double> CeilingInterzone_Impl::startingXCoordinate() const {
  return getDouble(openstudio::Ceiling_InterzoneFields::StartingXCoordinate, true);
}

bool CeilingInterzone_Impl::setStartingXCoordinate(double startingXCoordinate) {
  return setDouble(openstudio::Ceiling_InterzoneFields::StartingXCoordinate, startingXCoordinate);
}

void CeilingInterzone_Impl::resetStartingXCoordinate() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::StartingXCoordinate, ""));
}

boost::optional<double> CeilingInterzone_Impl::startingYCoordinate() const {
  return getDouble(openstudio::Ceiling_InterzoneFields::StartingYCoordinate, true);
}

bool CeilingInterzone_Impl::setStartingYCoordinate(double startingYCoordinate) {
  return setDouble(openstudio::Ceiling_InterzoneFields::StartingYCoordinate, startingYCoordinate);
}

void CeilingInterzone_Impl::resetStartingYCoordinate() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::StartingYCoordinate, ""));
}

boost::optional<double> CeilingInterzone_Impl::startingZCoordinate() const {
  return getDouble(openstudio::Ceiling_InterzoneFields::StartingZCoordinate, true);
}

bool CeilingInterzone_Impl::setStartingZCoordinate(double startingZCoordinate) {
  return setDouble(openstudio::Ceiling_InterzoneFields::StartingZCoordinate, startingZCoordinate);
}

void CeilingInterzone_Impl::resetStartingZCoordinate() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::StartingZCoordinate, ""));
}

boost::optional<double> CeilingInterzone_Impl::length() const {
  return getDouble(openstudio::Ceiling_InterzoneFields::Length, true);
}

bool CeilingInterzone_Impl::setLength(double length) {
  return setDouble(openstudio::Ceiling_InterzoneFields::Length, length);
}

void CeilingInterzone_Impl::resetLength() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::Length, ""));
}

boost::optional<double> CeilingInterzone_Impl::width() const {
  return getDouble(openstudio::Ceiling_InterzoneFields::Width, true);
}

bool CeilingInterzone_Impl::setWidth(double width) {
  return setDouble(openstudio::Ceiling_InterzoneFields::Width, width);
}

void CeilingInterzone_Impl::resetWidth() {
  OS_ASSERT(setString(openstudio::Ceiling_InterzoneFields::Width, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
