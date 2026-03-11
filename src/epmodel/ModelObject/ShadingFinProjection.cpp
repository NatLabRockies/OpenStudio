/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingFinProjection.hpp"
#include "ShadingFinProjection_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Fin_Projection_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadingFinProjection::ShadingFinProjection(const Model& model) : ModelObject(ShadingFinProjection::iddObjectType(), model) {}

ShadingFinProjection::ShadingFinProjection(std::shared_ptr<detail::ShadingFinProjection_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ShadingFinProjection::iddObjectType() {
  return IddObjectType::Shading_Fin_Projection;
}

boost::optional<double> ShadingFinProjection::leftExtensionfromWindowDoor() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->leftExtensionfromWindowDoor();
}

bool ShadingFinProjection::setLeftExtensionfromWindowDoor(double leftExtensionfromWindowDoor) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setLeftExtensionfromWindowDoor(leftExtensionfromWindowDoor);
}

void ShadingFinProjection::resetLeftExtensionfromWindowDoor() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetLeftExtensionfromWindowDoor();
}

boost::optional<double> ShadingFinProjection::leftDistanceAboveTopofWindow() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->leftDistanceAboveTopofWindow();
}

bool ShadingFinProjection::setLeftDistanceAboveTopofWindow(double leftDistanceAboveTopofWindow) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setLeftDistanceAboveTopofWindow(leftDistanceAboveTopofWindow);
}

void ShadingFinProjection::resetLeftDistanceAboveTopofWindow() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetLeftDistanceAboveTopofWindow();
}

boost::optional<double> ShadingFinProjection::leftDistanceBelowBottomofWindow() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->leftDistanceBelowBottomofWindow();
}

bool ShadingFinProjection::setLeftDistanceBelowBottomofWindow(double leftDistanceBelowBottomofWindow) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setLeftDistanceBelowBottomofWindow(leftDistanceBelowBottomofWindow);
}

void ShadingFinProjection::resetLeftDistanceBelowBottomofWindow() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetLeftDistanceBelowBottomofWindow();
}

double ShadingFinProjection::leftTiltAnglefromWindowDoor() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->leftTiltAnglefromWindowDoor();
}

bool ShadingFinProjection::isLeftTiltAnglefromWindowDoorDefaulted() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->isLeftTiltAnglefromWindowDoorDefaulted();
}

bool ShadingFinProjection::setLeftTiltAnglefromWindowDoor(double leftTiltAnglefromWindowDoor) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setLeftTiltAnglefromWindowDoor(leftTiltAnglefromWindowDoor);
}

void ShadingFinProjection::resetLeftTiltAnglefromWindowDoor() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetLeftTiltAnglefromWindowDoor();
}

boost::optional<double> ShadingFinProjection::leftDepthasFractionofWindowDoorWidth() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->leftDepthasFractionofWindowDoorWidth();
}

bool ShadingFinProjection::setLeftDepthasFractionofWindowDoorWidth(double leftDepthasFractionofWindowDoorWidth) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setLeftDepthasFractionofWindowDoorWidth(leftDepthasFractionofWindowDoorWidth);
}

void ShadingFinProjection::resetLeftDepthasFractionofWindowDoorWidth() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetLeftDepthasFractionofWindowDoorWidth();
}

boost::optional<double> ShadingFinProjection::rightExtensionfromWindowDoor() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->rightExtensionfromWindowDoor();
}

bool ShadingFinProjection::setRightExtensionfromWindowDoor(double rightExtensionfromWindowDoor) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setRightExtensionfromWindowDoor(rightExtensionfromWindowDoor);
}

void ShadingFinProjection::resetRightExtensionfromWindowDoor() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetRightExtensionfromWindowDoor();
}

boost::optional<double> ShadingFinProjection::rightDistanceAboveTopofWindow() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->rightDistanceAboveTopofWindow();
}

bool ShadingFinProjection::setRightDistanceAboveTopofWindow(double rightDistanceAboveTopofWindow) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setRightDistanceAboveTopofWindow(rightDistanceAboveTopofWindow);
}

void ShadingFinProjection::resetRightDistanceAboveTopofWindow() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetRightDistanceAboveTopofWindow();
}

boost::optional<double> ShadingFinProjection::rightDistanceBelowBottomofWindow() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->rightDistanceBelowBottomofWindow();
}

bool ShadingFinProjection::setRightDistanceBelowBottomofWindow(double rightDistanceBelowBottomofWindow) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setRightDistanceBelowBottomofWindow(rightDistanceBelowBottomofWindow);
}

void ShadingFinProjection::resetRightDistanceBelowBottomofWindow() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetRightDistanceBelowBottomofWindow();
}

double ShadingFinProjection::rightTiltAnglefromWindowDoor() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->rightTiltAnglefromWindowDoor();
}

bool ShadingFinProjection::isRightTiltAnglefromWindowDoorDefaulted() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->isRightTiltAnglefromWindowDoorDefaulted();
}

bool ShadingFinProjection::setRightTiltAnglefromWindowDoor(double rightTiltAnglefromWindowDoor) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setRightTiltAnglefromWindowDoor(rightTiltAnglefromWindowDoor);
}

void ShadingFinProjection::resetRightTiltAnglefromWindowDoor() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetRightTiltAnglefromWindowDoor();
}

boost::optional<double> ShadingFinProjection::rightDepthasFractionofWindowDoorWidth() const {
  return getImpl<detail::ShadingFinProjection_Impl>()->rightDepthasFractionofWindowDoorWidth();
}

bool ShadingFinProjection::setRightDepthasFractionofWindowDoorWidth(double rightDepthasFractionofWindowDoorWidth) {
  return getImpl<detail::ShadingFinProjection_Impl>()->setRightDepthasFractionofWindowDoorWidth(rightDepthasFractionofWindowDoorWidth);
}

void ShadingFinProjection::resetRightDepthasFractionofWindowDoorWidth() {
  getImpl<detail::ShadingFinProjection_Impl>()->resetRightDepthasFractionofWindowDoorWidth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ShadingFinProjection_Impl::leftExtensionfromWindowDoor() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::LeftExtensionfromWindow_Door, true);
}

bool ShadingFinProjection_Impl::setLeftExtensionfromWindowDoor(double leftExtensionfromWindowDoor) {
  const bool result = setDouble(openstudio::Shading_Fin_ProjectionFields::LeftExtensionfromWindow_Door, leftExtensionfromWindowDoor);
  OS_ASSERT(result);
  return result;
}

void ShadingFinProjection_Impl::resetLeftExtensionfromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::LeftExtensionfromWindow_Door, ""));
}

boost::optional<double> ShadingFinProjection_Impl::leftDistanceAboveTopofWindow() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::LeftDistanceAboveTopofWindow, true);
}

bool ShadingFinProjection_Impl::setLeftDistanceAboveTopofWindow(double leftDistanceAboveTopofWindow) {
  const bool result = setDouble(openstudio::Shading_Fin_ProjectionFields::LeftDistanceAboveTopofWindow, leftDistanceAboveTopofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFinProjection_Impl::resetLeftDistanceAboveTopofWindow() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::LeftDistanceAboveTopofWindow, ""));
}

boost::optional<double> ShadingFinProjection_Impl::leftDistanceBelowBottomofWindow() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::LeftDistanceBelowBottomofWindow, true);
}

bool ShadingFinProjection_Impl::setLeftDistanceBelowBottomofWindow(double leftDistanceBelowBottomofWindow) {
  const bool result = setDouble(openstudio::Shading_Fin_ProjectionFields::LeftDistanceBelowBottomofWindow, leftDistanceBelowBottomofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFinProjection_Impl::resetLeftDistanceBelowBottomofWindow() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::LeftDistanceBelowBottomofWindow, ""));
}

double ShadingFinProjection_Impl::leftTiltAnglefromWindowDoor() const {
  const auto value = getDouble(openstudio::Shading_Fin_ProjectionFields::LeftTiltAnglefromWindow_Door, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingFinProjection_Impl::isLeftTiltAnglefromWindowDoorDefaulted() const {
  return !getDouble(openstudio::Shading_Fin_ProjectionFields::LeftTiltAnglefromWindow_Door, false);
}

bool ShadingFinProjection_Impl::setLeftTiltAnglefromWindowDoor(double leftTiltAnglefromWindowDoor) {
  return setDouble(openstudio::Shading_Fin_ProjectionFields::LeftTiltAnglefromWindow_Door, leftTiltAnglefromWindowDoor);
}

void ShadingFinProjection_Impl::resetLeftTiltAnglefromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::LeftTiltAnglefromWindow_Door, ""));
}

boost::optional<double> ShadingFinProjection_Impl::leftDepthasFractionofWindowDoorWidth() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::LeftDepthasFractionofWindow_DoorWidth, true);
}

bool ShadingFinProjection_Impl::setLeftDepthasFractionofWindowDoorWidth(double leftDepthasFractionofWindowDoorWidth) {
  return setDouble(openstudio::Shading_Fin_ProjectionFields::LeftDepthasFractionofWindow_DoorWidth, leftDepthasFractionofWindowDoorWidth);
}

void ShadingFinProjection_Impl::resetLeftDepthasFractionofWindowDoorWidth() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::LeftDepthasFractionofWindow_DoorWidth, ""));
}

boost::optional<double> ShadingFinProjection_Impl::rightExtensionfromWindowDoor() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::RightExtensionfromWindow_Door, true);
}

bool ShadingFinProjection_Impl::setRightExtensionfromWindowDoor(double rightExtensionfromWindowDoor) {
  const bool result = setDouble(openstudio::Shading_Fin_ProjectionFields::RightExtensionfromWindow_Door, rightExtensionfromWindowDoor);
  OS_ASSERT(result);
  return result;
}

void ShadingFinProjection_Impl::resetRightExtensionfromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::RightExtensionfromWindow_Door, ""));
}

boost::optional<double> ShadingFinProjection_Impl::rightDistanceAboveTopofWindow() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::RightDistanceAboveTopofWindow, true);
}

bool ShadingFinProjection_Impl::setRightDistanceAboveTopofWindow(double rightDistanceAboveTopofWindow) {
  const bool result = setDouble(openstudio::Shading_Fin_ProjectionFields::RightDistanceAboveTopofWindow, rightDistanceAboveTopofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFinProjection_Impl::resetRightDistanceAboveTopofWindow() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::RightDistanceAboveTopofWindow, ""));
}

boost::optional<double> ShadingFinProjection_Impl::rightDistanceBelowBottomofWindow() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::RightDistanceBelowBottomofWindow, true);
}

bool ShadingFinProjection_Impl::setRightDistanceBelowBottomofWindow(double rightDistanceBelowBottomofWindow) {
  const bool result = setDouble(openstudio::Shading_Fin_ProjectionFields::RightDistanceBelowBottomofWindow, rightDistanceBelowBottomofWindow);
  OS_ASSERT(result);
  return result;
}

void ShadingFinProjection_Impl::resetRightDistanceBelowBottomofWindow() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::RightDistanceBelowBottomofWindow, ""));
}

double ShadingFinProjection_Impl::rightTiltAnglefromWindowDoor() const {
  const auto value = getDouble(openstudio::Shading_Fin_ProjectionFields::RightTiltAnglefromWindow_Door, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingFinProjection_Impl::isRightTiltAnglefromWindowDoorDefaulted() const {
  return !getDouble(openstudio::Shading_Fin_ProjectionFields::RightTiltAnglefromWindow_Door, false);
}

bool ShadingFinProjection_Impl::setRightTiltAnglefromWindowDoor(double rightTiltAnglefromWindowDoor) {
  return setDouble(openstudio::Shading_Fin_ProjectionFields::RightTiltAnglefromWindow_Door, rightTiltAnglefromWindowDoor);
}

void ShadingFinProjection_Impl::resetRightTiltAnglefromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::RightTiltAnglefromWindow_Door, ""));
}

boost::optional<double> ShadingFinProjection_Impl::rightDepthasFractionofWindowDoorWidth() const {
  return getDouble(openstudio::Shading_Fin_ProjectionFields::RightDepthasFractionofWindow_DoorWidth, true);
}

bool ShadingFinProjection_Impl::setRightDepthasFractionofWindowDoorWidth(double rightDepthasFractionofWindowDoorWidth) {
  return setDouble(openstudio::Shading_Fin_ProjectionFields::RightDepthasFractionofWindow_DoorWidth, rightDepthasFractionofWindowDoorWidth);
}

void ShadingFinProjection_Impl::resetRightDepthasFractionofWindowDoorWidth() {
  OS_ASSERT(setString(openstudio::Shading_Fin_ProjectionFields::RightDepthasFractionofWindow_DoorWidth, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
