/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CeilingAdiabatic.hpp"
#include "CeilingAdiabatic_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Ceiling_Adiabatic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CeilingAdiabatic::CeilingAdiabatic(const Model& model) : ModelObject(CeilingAdiabatic::iddObjectType(), model) {}

CeilingAdiabatic::CeilingAdiabatic(std::shared_ptr<detail::CeilingAdiabatic_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType CeilingAdiabatic::iddObjectType() {
  return IddObjectType::Ceiling_Adiabatic;
}

boost::optional<double> CeilingAdiabatic::azimuthAngle() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->azimuthAngle();
}

bool CeilingAdiabatic::setAzimuthAngle(double azimuthAngle) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setAzimuthAngle(azimuthAngle);
}

void CeilingAdiabatic::resetAzimuthAngle() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetAzimuthAngle();
}

double CeilingAdiabatic::tiltAngle() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->tiltAngle();
}

bool CeilingAdiabatic::isTiltAngleDefaulted() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->isTiltAngleDefaulted();
}

bool CeilingAdiabatic::setTiltAngle(double tiltAngle) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setTiltAngle(tiltAngle);
}

void CeilingAdiabatic::resetTiltAngle() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetTiltAngle();
}

boost::optional<double> CeilingAdiabatic::startingXCoordinate() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->startingXCoordinate();
}

bool CeilingAdiabatic::setStartingXCoordinate(double startingXCoordinate) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setStartingXCoordinate(startingXCoordinate);
}

void CeilingAdiabatic::resetStartingXCoordinate() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetStartingXCoordinate();
}

boost::optional<double> CeilingAdiabatic::startingYCoordinate() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->startingYCoordinate();
}

bool CeilingAdiabatic::setStartingYCoordinate(double startingYCoordinate) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setStartingYCoordinate(startingYCoordinate);
}

void CeilingAdiabatic::resetStartingYCoordinate() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetStartingYCoordinate();
}

boost::optional<double> CeilingAdiabatic::startingZCoordinate() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->startingZCoordinate();
}

bool CeilingAdiabatic::setStartingZCoordinate(double startingZCoordinate) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setStartingZCoordinate(startingZCoordinate);
}

void CeilingAdiabatic::resetStartingZCoordinate() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetStartingZCoordinate();
}

boost::optional<double> CeilingAdiabatic::length() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->length();
}

bool CeilingAdiabatic::setLength(double length) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setLength(length);
}

void CeilingAdiabatic::resetLength() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetLength();
}

boost::optional<double> CeilingAdiabatic::width() const {
  return getImpl<detail::CeilingAdiabatic_Impl>()->width();
}

bool CeilingAdiabatic::setWidth(double width) {
  return getImpl<detail::CeilingAdiabatic_Impl>()->setWidth(width);
}

void CeilingAdiabatic::resetWidth() {
  getImpl<detail::CeilingAdiabatic_Impl>()->resetWidth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> CeilingAdiabatic_Impl::azimuthAngle() const {
  return getDouble(openstudio::Ceiling_AdiabaticFields::AzimuthAngle, true);
}

bool CeilingAdiabatic_Impl::setAzimuthAngle(double azimuthAngle) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::AzimuthAngle, azimuthAngle);
}

void CeilingAdiabatic_Impl::resetAzimuthAngle() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::AzimuthAngle, ""));
}

double CeilingAdiabatic_Impl::tiltAngle() const {
  const auto value = getDouble(openstudio::Ceiling_AdiabaticFields::TiltAngle, true);
  OS_ASSERT(value);
  return *value;
}

bool CeilingAdiabatic_Impl::isTiltAngleDefaulted() const {
  return isEmpty(openstudio::Ceiling_AdiabaticFields::TiltAngle);
}

bool CeilingAdiabatic_Impl::setTiltAngle(double tiltAngle) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::TiltAngle, tiltAngle);
}

void CeilingAdiabatic_Impl::resetTiltAngle() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::TiltAngle, ""));
}

boost::optional<double> CeilingAdiabatic_Impl::startingXCoordinate() const {
  return getDouble(openstudio::Ceiling_AdiabaticFields::StartingXCoordinate, true);
}

bool CeilingAdiabatic_Impl::setStartingXCoordinate(double startingXCoordinate) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::StartingXCoordinate, startingXCoordinate);
}

void CeilingAdiabatic_Impl::resetStartingXCoordinate() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::StartingXCoordinate, ""));
}

boost::optional<double> CeilingAdiabatic_Impl::startingYCoordinate() const {
  return getDouble(openstudio::Ceiling_AdiabaticFields::StartingYCoordinate, true);
}

bool CeilingAdiabatic_Impl::setStartingYCoordinate(double startingYCoordinate) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::StartingYCoordinate, startingYCoordinate);
}

void CeilingAdiabatic_Impl::resetStartingYCoordinate() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::StartingYCoordinate, ""));
}

boost::optional<double> CeilingAdiabatic_Impl::startingZCoordinate() const {
  return getDouble(openstudio::Ceiling_AdiabaticFields::StartingZCoordinate, true);
}

bool CeilingAdiabatic_Impl::setStartingZCoordinate(double startingZCoordinate) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::StartingZCoordinate, startingZCoordinate);
}

void CeilingAdiabatic_Impl::resetStartingZCoordinate() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::StartingZCoordinate, ""));
}

boost::optional<double> CeilingAdiabatic_Impl::length() const {
  return getDouble(openstudio::Ceiling_AdiabaticFields::Length, true);
}

bool CeilingAdiabatic_Impl::setLength(double length) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::Length, length);
}

void CeilingAdiabatic_Impl::resetLength() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::Length, ""));
}

boost::optional<double> CeilingAdiabatic_Impl::width() const {
  return getDouble(openstudio::Ceiling_AdiabaticFields::Width, true);
}

bool CeilingAdiabatic_Impl::setWidth(double width) {
  return setDouble(openstudio::Ceiling_AdiabaticFields::Width, width);
}

void CeilingAdiabatic_Impl::resetWidth() {
  OS_ASSERT(setString(openstudio::Ceiling_AdiabaticFields::Width, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
