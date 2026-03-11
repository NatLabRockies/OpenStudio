/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Door.hpp"
#include "Door_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Door_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

Door::Door(const Model& model) : ModelObject(Door::iddObjectType(), model) {}

Door::Door(std::shared_ptr<detail::Door_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType Door::iddObjectType() {
  return IddObjectType::Door;
}

double Door::multiplier() const {
  return getImpl<detail::Door_Impl>()->multiplier();
}

bool Door::isMultiplierDefaulted() const {
  return getImpl<detail::Door_Impl>()->isMultiplierDefaulted();
}

bool Door::setMultiplier(double multiplier) {
  return getImpl<detail::Door_Impl>()->setMultiplier(multiplier);
}

void Door::resetMultiplier() {
  getImpl<detail::Door_Impl>()->resetMultiplier();
}

boost::optional<double> Door::startingXCoordinate() const {
  return getImpl<detail::Door_Impl>()->startingXCoordinate();
}

bool Door::setStartingXCoordinate(double startingXCoordinate) {
  return getImpl<detail::Door_Impl>()->setStartingXCoordinate(startingXCoordinate);
}

void Door::resetStartingXCoordinate() {
  getImpl<detail::Door_Impl>()->resetStartingXCoordinate();
}

boost::optional<double> Door::startingZCoordinate() const {
  return getImpl<detail::Door_Impl>()->startingZCoordinate();
}

bool Door::setStartingZCoordinate(double startingZCoordinate) {
  return getImpl<detail::Door_Impl>()->setStartingZCoordinate(startingZCoordinate);
}

void Door::resetStartingZCoordinate() {
  getImpl<detail::Door_Impl>()->resetStartingZCoordinate();
}

boost::optional<double> Door::length() const {
  return getImpl<detail::Door_Impl>()->length();
}

bool Door::setLength(double length) {
  return getImpl<detail::Door_Impl>()->setLength(length);
}

void Door::resetLength() {
  getImpl<detail::Door_Impl>()->resetLength();
}

boost::optional<double> Door::height() const {
  return getImpl<detail::Door_Impl>()->height();
}

bool Door::setHeight(double height) {
  return getImpl<detail::Door_Impl>()->setHeight(height);
}

void Door::resetHeight() {
  getImpl<detail::Door_Impl>()->resetHeight();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double Door_Impl::multiplier() const {
  const auto value = getDouble(openstudio::DoorFields::Multiplier, true);
  OS_ASSERT(value);
  return *value;
}

bool Door_Impl::isMultiplierDefaulted() const {
  return isEmpty(openstudio::DoorFields::Multiplier);
}

bool Door_Impl::setMultiplier(double multiplier) {
  return setDouble(openstudio::DoorFields::Multiplier, multiplier);
}

void Door_Impl::resetMultiplier() {
  OS_ASSERT(setString(openstudio::DoorFields::Multiplier, ""));
}

boost::optional<double> Door_Impl::startingXCoordinate() const {
  return getDouble(openstudio::DoorFields::StartingXCoordinate, true);
}

bool Door_Impl::setStartingXCoordinate(double startingXCoordinate) {
  return setDouble(openstudio::DoorFields::StartingXCoordinate, startingXCoordinate);
}

void Door_Impl::resetStartingXCoordinate() {
  OS_ASSERT(setString(openstudio::DoorFields::StartingXCoordinate, ""));
}

boost::optional<double> Door_Impl::startingZCoordinate() const {
  return getDouble(openstudio::DoorFields::StartingZCoordinate, true);
}

bool Door_Impl::setStartingZCoordinate(double startingZCoordinate) {
  return setDouble(openstudio::DoorFields::StartingZCoordinate, startingZCoordinate);
}

void Door_Impl::resetStartingZCoordinate() {
  OS_ASSERT(setString(openstudio::DoorFields::StartingZCoordinate, ""));
}

boost::optional<double> Door_Impl::length() const {
  return getDouble(openstudio::DoorFields::Length, true);
}

bool Door_Impl::setLength(double length) {
  return setDouble(openstudio::DoorFields::Length, length);
}

void Door_Impl::resetLength() {
  OS_ASSERT(setString(openstudio::DoorFields::Length, ""));
}

boost::optional<double> Door_Impl::height() const {
  return getDouble(openstudio::DoorFields::Height, true);
}

bool Door_Impl::setHeight(double height) {
  return setDouble(openstudio::DoorFields::Height, height);
}

void Door_Impl::resetHeight() {
  OS_ASSERT(setString(openstudio::DoorFields::Height, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
