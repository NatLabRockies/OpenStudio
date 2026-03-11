/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingFin.hpp"
#include "ShadingFin_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Fin_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadingFin::ShadingFin(const Model& model) : ModelObject(ShadingFin::iddObjectType(), model) {}

ShadingFin::ShadingFin(std::shared_ptr<detail::ShadingFin_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ShadingFin::iddObjectType() {
  return IddObjectType::Shading_Fin;
}

boost::optional<double> ShadingFin::leftExtensionfromWindowDoor() const {
  return getImpl<detail::ShadingFin_Impl>()->leftExtensionfromWindowDoor();
}

bool ShadingFin::setLeftExtensionfromWindowDoor(double leftExtensionfromWindowDoor) {
  return getImpl<detail::ShadingFin_Impl>()->setLeftExtensionfromWindowDoor(leftExtensionfromWindowDoor);
}

void ShadingFin::resetLeftExtensionfromWindowDoor() {
  getImpl<detail::ShadingFin_Impl>()->resetLeftExtensionfromWindowDoor();
}

boost::optional<double> ShadingFin::leftDistanceAboveTopofWindow() const {
  return getImpl<detail::ShadingFin_Impl>()->leftDistanceAboveTopofWindow();
}

bool ShadingFin::setLeftDistanceAboveTopofWindow(double leftDistanceAboveTopofWindow) {
  return getImpl<detail::ShadingFin_Impl>()->setLeftDistanceAboveTopofWindow(leftDistanceAboveTopofWindow);
}

void ShadingFin::resetLeftDistanceAboveTopofWindow() {
  getImpl<detail::ShadingFin_Impl>()->resetLeftDistanceAboveTopofWindow();
}

boost::optional<double> ShadingFin::leftDistanceBelowBottomofWindow() const {
  return getImpl<detail::ShadingFin_Impl>()->leftDistanceBelowBottomofWindow();
}

bool ShadingFin::setLeftDistanceBelowBottomofWindow(double leftDistanceBelowBottomofWindow) {
  return getImpl<detail::ShadingFin_Impl>()->setLeftDistanceBelowBottomofWindow(leftDistanceBelowBottomofWindow);
}

void ShadingFin::resetLeftDistanceBelowBottomofWindow() {
  getImpl<detail::ShadingFin_Impl>()->resetLeftDistanceBelowBottomofWindow();
}

double ShadingFin::leftTiltAnglefromWindowDoor() const {
  return getImpl<detail::ShadingFin_Impl>()->leftTiltAnglefromWindowDoor();
}

bool ShadingFin::isLeftTiltAnglefromWindowDoorDefaulted() const {
  return getImpl<detail::ShadingFin_Impl>()->isLeftTiltAnglefromWindowDoorDefaulted();
}

bool ShadingFin::setLeftTiltAnglefromWindowDoor(double leftTiltAnglefromWindowDoor) {
  return getImpl<detail::ShadingFin_Impl>()->setLeftTiltAnglefromWindowDoor(leftTiltAnglefromWindowDoor);
}

void ShadingFin::resetLeftTiltAnglefromWindowDoor() {
  getImpl<detail::ShadingFin_Impl>()->resetLeftTiltAnglefromWindowDoor();
}

boost::optional<double> ShadingFin::leftDepth() const {
  return getImpl<detail::ShadingFin_Impl>()->leftDepth();
}

bool ShadingFin::setLeftDepth(double leftDepth) {
  return getImpl<detail::ShadingFin_Impl>()->setLeftDepth(leftDepth);
}

void ShadingFin::resetLeftDepth() {
  getImpl<detail::ShadingFin_Impl>()->resetLeftDepth();
}

boost::optional<double> ShadingFin::rightExtensionfromWindowDoor() const {
  return getImpl<detail::ShadingFin_Impl>()->rightExtensionfromWindowDoor();
}

bool ShadingFin::setRightExtensionfromWindowDoor(double rightExtensionfromWindowDoor) {
  return getImpl<detail::ShadingFin_Impl>()->setRightExtensionfromWindowDoor(rightExtensionfromWindowDoor);
}

void ShadingFin::resetRightExtensionfromWindowDoor() {
  getImpl<detail::ShadingFin_Impl>()->resetRightExtensionfromWindowDoor();
}

boost::optional<double> ShadingFin::rightDistanceAboveTopofWindow() const {
  return getImpl<detail::ShadingFin_Impl>()->rightDistanceAboveTopofWindow();
}

bool ShadingFin::setRightDistanceAboveTopofWindow(double rightDistanceAboveTopofWindow) {
  return getImpl<detail::ShadingFin_Impl>()->setRightDistanceAboveTopofWindow(rightDistanceAboveTopofWindow);
}

void ShadingFin::resetRightDistanceAboveTopofWindow() {
  getImpl<detail::ShadingFin_Impl>()->resetRightDistanceAboveTopofWindow();
}

boost::optional<double> ShadingFin::rightDistanceBelowBottomofWindow() const {
  return getImpl<detail::ShadingFin_Impl>()->rightDistanceBelowBottomofWindow();
}

bool ShadingFin::setRightDistanceBelowBottomofWindow(double rightDistanceBelowBottomofWindow) {
  return getImpl<detail::ShadingFin_Impl>()->setRightDistanceBelowBottomofWindow(rightDistanceBelowBottomofWindow);
}

void ShadingFin::resetRightDistanceBelowBottomofWindow() {
  getImpl<detail::ShadingFin_Impl>()->resetRightDistanceBelowBottomofWindow();
}

double ShadingFin::rightTiltAnglefromWindowDoor() const {
  return getImpl<detail::ShadingFin_Impl>()->rightTiltAnglefromWindowDoor();
}

bool ShadingFin::isRightTiltAnglefromWindowDoorDefaulted() const {
  return getImpl<detail::ShadingFin_Impl>()->isRightTiltAnglefromWindowDoorDefaulted();
}

bool ShadingFin::setRightTiltAnglefromWindowDoor(double rightTiltAnglefromWindowDoor) {
  return getImpl<detail::ShadingFin_Impl>()->setRightTiltAnglefromWindowDoor(rightTiltAnglefromWindowDoor);
}

void ShadingFin::resetRightTiltAnglefromWindowDoor() {
  getImpl<detail::ShadingFin_Impl>()->resetRightTiltAnglefromWindowDoor();
}

boost::optional<double> ShadingFin::rightDepth() const {
  return getImpl<detail::ShadingFin_Impl>()->rightDepth();
}

bool ShadingFin::setRightDepth(double rightDepth) {
  return getImpl<detail::ShadingFin_Impl>()->setRightDepth(rightDepth);
}

void ShadingFin::resetRightDepth() {
  getImpl<detail::ShadingFin_Impl>()->resetRightDepth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ShadingFin_Impl::leftExtensionfromWindowDoor() const {
  return getDouble(openstudio::Shading_FinFields::LeftExtensionfromWindow_Door, true);
}

bool ShadingFin_Impl::setLeftExtensionfromWindowDoor(double leftExtensionfromWindowDoor) {
  const bool result = setDouble(openstudio::Shading_FinFields::LeftExtensionfromWindow_Door, leftExtensionfromWindowDoor);
  OS_ASSERT(result);
  return result;
}

void ShadingFin_Impl::resetLeftExtensionfromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::LeftExtensionfromWindow_Door, ""));
}

boost::optional<double> ShadingFin_Impl::leftDistanceAboveTopofWindow() const {
  return getDouble(openstudio::Shading_FinFields::LeftDistanceAboveTopofWindow, true);
}

bool ShadingFin_Impl::setLeftDistanceAboveTopofWindow(double leftDistanceAboveTopofWindow) {
  const bool result = setDouble(openstudio::Shading_FinFields::LeftDistanceAboveTopofWindow, leftDistanceAboveTopofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFin_Impl::resetLeftDistanceAboveTopofWindow() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::LeftDistanceAboveTopofWindow, ""));
}

boost::optional<double> ShadingFin_Impl::leftDistanceBelowBottomofWindow() const {
  return getDouble(openstudio::Shading_FinFields::LeftDistanceBelowBottomofWindow, true);
}

bool ShadingFin_Impl::setLeftDistanceBelowBottomofWindow(double leftDistanceBelowBottomofWindow) {
  const bool result = setDouble(openstudio::Shading_FinFields::LeftDistanceBelowBottomofWindow, leftDistanceBelowBottomofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFin_Impl::resetLeftDistanceBelowBottomofWindow() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::LeftDistanceBelowBottomofWindow, ""));
}

double ShadingFin_Impl::leftTiltAnglefromWindowDoor() const {
  const auto value = getDouble(openstudio::Shading_FinFields::LeftTiltAnglefromWindow_Door, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingFin_Impl::isLeftTiltAnglefromWindowDoorDefaulted() const {
  return !getDouble(openstudio::Shading_FinFields::LeftTiltAnglefromWindow_Door, false);
}

bool ShadingFin_Impl::setLeftTiltAnglefromWindowDoor(double leftTiltAnglefromWindowDoor) {
  return setDouble(openstudio::Shading_FinFields::LeftTiltAnglefromWindow_Door, leftTiltAnglefromWindowDoor);
}

void ShadingFin_Impl::resetLeftTiltAnglefromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::LeftTiltAnglefromWindow_Door, ""));
}

boost::optional<double> ShadingFin_Impl::leftDepth() const {
  return getDouble(openstudio::Shading_FinFields::LeftDepth, true);
}

bool ShadingFin_Impl::setLeftDepth(double leftDepth) {
  return setDouble(openstudio::Shading_FinFields::LeftDepth, leftDepth);
}

void ShadingFin_Impl::resetLeftDepth() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::LeftDepth, ""));
}

boost::optional<double> ShadingFin_Impl::rightExtensionfromWindowDoor() const {
  return getDouble(openstudio::Shading_FinFields::RightExtensionfromWindow_Door, true);
}

bool ShadingFin_Impl::setRightExtensionfromWindowDoor(double rightExtensionfromWindowDoor) {
  const bool result = setDouble(openstudio::Shading_FinFields::RightExtensionfromWindow_Door, rightExtensionfromWindowDoor);
  OS_ASSERT(result);
  return result;
}

void ShadingFin_Impl::resetRightExtensionfromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::RightExtensionfromWindow_Door, ""));
}

boost::optional<double> ShadingFin_Impl::rightDistanceAboveTopofWindow() const {
  return getDouble(openstudio::Shading_FinFields::RightDistanceAboveTopofWindow, true);
}

bool ShadingFin_Impl::setRightDistanceAboveTopofWindow(double rightDistanceAboveTopofWindow) {
  const bool result = setDouble(openstudio::Shading_FinFields::RightDistanceAboveTopofWindow, rightDistanceAboveTopofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFin_Impl::resetRightDistanceAboveTopofWindow() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::RightDistanceAboveTopofWindow, ""));
}

boost::optional<double> ShadingFin_Impl::rightDistanceBelowBottomofWindow() const {
  return getDouble(openstudio::Shading_FinFields::RightDistanceBelowBottomofWindow, true);
}

bool ShadingFin_Impl::setRightDistanceBelowBottomofWindow(double rightDistanceBelowBottomofWindow) {
  const bool result = setDouble(openstudio::Shading_FinFields::RightDistanceBelowBottomofWindow, rightDistanceBelowBottomofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFin_Impl::resetRightDistanceBelowBottomofWindow() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::RightDistanceBelowBottomofWindow, ""));
}

double ShadingFin_Impl::rightTiltAnglefromWindowDoor() const {
  const auto value = getDouble(openstudio::Shading_FinFields::RightTiltAnglefromWindow_Door, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingFin_Impl::isRightTiltAnglefromWindowDoorDefaulted() const {
  return !getDouble(openstudio::Shading_FinFields::RightTiltAnglefromWindow_Door, false);
}

bool ShadingFin_Impl::setRightTiltAnglefromWindowDoor(double rightTiltAnglefromWindowDoor) {
  return setDouble(openstudio::Shading_FinFields::RightTiltAnglefromWindow_Door, rightTiltAnglefromWindowDoor);
}

void ShadingFin_Impl::resetRightTiltAnglefromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::RightTiltAnglefromWindow_Door, ""));
}

boost::optional<double> ShadingFin_Impl::rightDepth() const {
  return getDouble(openstudio::Shading_FinFields::RightDepth, true);
}

bool ShadingFin_Impl::setRightDepth(double rightDepth) {
  return setDouble(openstudio::Shading_FinFields::RightDepth, rightDepth);
}

void ShadingFin_Impl::resetRightDepth() {
  OS_ASSERT(setString(openstudio::Shading_FinFields::RightDepth, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
