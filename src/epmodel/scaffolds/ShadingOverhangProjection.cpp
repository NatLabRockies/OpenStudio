/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingOverhangProjection.hpp"
#include "ShadingOverhangProjection_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Overhang_Projection_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadingOverhangProjection::ShadingOverhangProjection(const Model& model) : ModelObject(ShadingOverhangProjection::iddObjectType(), model) {}

ShadingOverhangProjection::ShadingOverhangProjection(std::shared_ptr<detail::ShadingOverhangProjection_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ShadingOverhangProjection::iddObjectType() {
  return IddObjectType::Shading_Overhang_Projection;
}

boost::optional<double> ShadingOverhangProjection::heightaboveWindoworDoor() const {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->heightaboveWindoworDoor();
}

bool ShadingOverhangProjection::setHeightaboveWindoworDoor(double heightaboveWindoworDoor) {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->setHeightaboveWindoworDoor(heightaboveWindoworDoor);
}

void ShadingOverhangProjection::resetHeightaboveWindoworDoor() {
  getImpl<detail::ShadingOverhangProjection_Impl>()->resetHeightaboveWindoworDoor();
}

double ShadingOverhangProjection::tiltAnglefromWindowDoor() const {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->tiltAnglefromWindowDoor();
}

bool ShadingOverhangProjection::isTiltAnglefromWindowDoorDefaulted() const {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->isTiltAnglefromWindowDoorDefaulted();
}

bool ShadingOverhangProjection::setTiltAnglefromWindowDoor(double tiltAnglefromWindowDoor) {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->setTiltAnglefromWindowDoor(tiltAnglefromWindowDoor);
}

void ShadingOverhangProjection::resetTiltAnglefromWindowDoor() {
  getImpl<detail::ShadingOverhangProjection_Impl>()->resetTiltAnglefromWindowDoor();
}

boost::optional<double> ShadingOverhangProjection::leftextensionfromWindowDoorWidth() const {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->leftextensionfromWindowDoorWidth();
}

bool ShadingOverhangProjection::setLeftextensionfromWindowDoorWidth(double leftextensionfromWindowDoorWidth) {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->setLeftextensionfromWindowDoorWidth(leftextensionfromWindowDoorWidth);
}

void ShadingOverhangProjection::resetLeftextensionfromWindowDoorWidth() {
  getImpl<detail::ShadingOverhangProjection_Impl>()->resetLeftextensionfromWindowDoorWidth();
}

boost::optional<double> ShadingOverhangProjection::rightextensionfromWindowDoorWidth() const {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->rightextensionfromWindowDoorWidth();
}

bool ShadingOverhangProjection::setRightextensionfromWindowDoorWidth(double rightextensionfromWindowDoorWidth) {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->setRightextensionfromWindowDoorWidth(rightextensionfromWindowDoorWidth);
}

void ShadingOverhangProjection::resetRightextensionfromWindowDoorWidth() {
  getImpl<detail::ShadingOverhangProjection_Impl>()->resetRightextensionfromWindowDoorWidth();
}

boost::optional<double> ShadingOverhangProjection::depthasFractionofWindowDoorHeight() const {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->depthasFractionofWindowDoorHeight();
}

bool ShadingOverhangProjection::setDepthasFractionofWindowDoorHeight(double depthasFractionofWindowDoorHeight) {
  return getImpl<detail::ShadingOverhangProjection_Impl>()->setDepthasFractionofWindowDoorHeight(depthasFractionofWindowDoorHeight);
}

void ShadingOverhangProjection::resetDepthasFractionofWindowDoorHeight() {
  getImpl<detail::ShadingOverhangProjection_Impl>()->resetDepthasFractionofWindowDoorHeight();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ShadingOverhangProjection_Impl::heightaboveWindoworDoor() const {
  return getDouble(openstudio::Shading_Overhang_ProjectionFields::HeightaboveWindoworDoor, true);
}

bool ShadingOverhangProjection_Impl::setHeightaboveWindoworDoor(double heightaboveWindoworDoor) {
  const bool result = setDouble(openstudio::Shading_Overhang_ProjectionFields::HeightaboveWindoworDoor, heightaboveWindoworDoor);
  OS_ASSERT(result);
  return result;
}

void ShadingOverhangProjection_Impl::resetHeightaboveWindoworDoor() {
  OS_ASSERT(setString(openstudio::Shading_Overhang_ProjectionFields::HeightaboveWindoworDoor, ""));
}

double ShadingOverhangProjection_Impl::tiltAnglefromWindowDoor() const {
  const auto value = getDouble(openstudio::Shading_Overhang_ProjectionFields::TiltAnglefromWindow_Door, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingOverhangProjection_Impl::isTiltAnglefromWindowDoorDefaulted() const {
  return !getDouble(openstudio::Shading_Overhang_ProjectionFields::TiltAnglefromWindow_Door, false);
}

bool ShadingOverhangProjection_Impl::setTiltAnglefromWindowDoor(double tiltAnglefromWindowDoor) {
  return setDouble(openstudio::Shading_Overhang_ProjectionFields::TiltAnglefromWindow_Door, tiltAnglefromWindowDoor);
}

void ShadingOverhangProjection_Impl::resetTiltAnglefromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_Overhang_ProjectionFields::TiltAnglefromWindow_Door, ""));
}

boost::optional<double> ShadingOverhangProjection_Impl::leftextensionfromWindowDoorWidth() const {
  return getDouble(openstudio::Shading_Overhang_ProjectionFields::LeftextensionfromWindow_DoorWidth, true);
}

bool ShadingOverhangProjection_Impl::setLeftextensionfromWindowDoorWidth(double leftextensionfromWindowDoorWidth) {
  const bool result = setDouble(openstudio::Shading_Overhang_ProjectionFields::LeftextensionfromWindow_DoorWidth, leftextensionfromWindowDoorWidth);
  OS_ASSERT(result);
  return result;
}

void ShadingOverhangProjection_Impl::resetLeftextensionfromWindowDoorWidth() {
  OS_ASSERT(setString(openstudio::Shading_Overhang_ProjectionFields::LeftextensionfromWindow_DoorWidth, ""));
}

boost::optional<double> ShadingOverhangProjection_Impl::rightextensionfromWindowDoorWidth() const {
  return getDouble(openstudio::Shading_Overhang_ProjectionFields::RightextensionfromWindow_DoorWidth, true);
}

bool ShadingOverhangProjection_Impl::setRightextensionfromWindowDoorWidth(double rightextensionfromWindowDoorWidth) {
  const bool result = setDouble(openstudio::Shading_Overhang_ProjectionFields::RightextensionfromWindow_DoorWidth, rightextensionfromWindowDoorWidth);
  OS_ASSERT(result);
  return result;
}

void ShadingOverhangProjection_Impl::resetRightextensionfromWindowDoorWidth() {
  OS_ASSERT(setString(openstudio::Shading_Overhang_ProjectionFields::RightextensionfromWindow_DoorWidth, ""));
}

boost::optional<double> ShadingOverhangProjection_Impl::depthasFractionofWindowDoorHeight() const {
  return getDouble(openstudio::Shading_Overhang_ProjectionFields::DepthasFractionofWindow_DoorHeight, true);
}

bool ShadingOverhangProjection_Impl::setDepthasFractionofWindowDoorHeight(double depthasFractionofWindowDoorHeight) {
  return setDouble(openstudio::Shading_Overhang_ProjectionFields::DepthasFractionofWindow_DoorHeight, depthasFractionofWindowDoorHeight);
}

void ShadingOverhangProjection_Impl::resetDepthasFractionofWindowDoorHeight() {
  OS_ASSERT(setString(openstudio::Shading_Overhang_ProjectionFields::DepthasFractionofWindow_DoorHeight, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
