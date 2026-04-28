/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingOverhang.hpp"
#include "ShadingOverhang_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Overhang_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadingOverhang::ShadingOverhang(const Model& model) : ModelObject(ShadingOverhang::iddObjectType(), model) {}

ShadingOverhang::ShadingOverhang(std::shared_ptr<detail::ShadingOverhang_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ShadingOverhang::iddObjectType() {
  return IddObjectType::Shading_Overhang;
}

boost::optional<double> ShadingOverhang::heightaboveWindoworDoor() const {
  return getImpl<detail::ShadingOverhang_Impl>()->heightaboveWindoworDoor();
}

bool ShadingOverhang::setHeightaboveWindoworDoor(double heightaboveWindoworDoor) {
  return getImpl<detail::ShadingOverhang_Impl>()->setHeightaboveWindoworDoor(heightaboveWindoworDoor);
}

void ShadingOverhang::resetHeightaboveWindoworDoor() {
  getImpl<detail::ShadingOverhang_Impl>()->resetHeightaboveWindoworDoor();
}

double ShadingOverhang::tiltAnglefromWindowDoor() const {
  return getImpl<detail::ShadingOverhang_Impl>()->tiltAnglefromWindowDoor();
}

bool ShadingOverhang::isTiltAnglefromWindowDoorDefaulted() const {
  return getImpl<detail::ShadingOverhang_Impl>()->isTiltAnglefromWindowDoorDefaulted();
}

bool ShadingOverhang::setTiltAnglefromWindowDoor(double tiltAnglefromWindowDoor) {
  return getImpl<detail::ShadingOverhang_Impl>()->setTiltAnglefromWindowDoor(tiltAnglefromWindowDoor);
}

void ShadingOverhang::resetTiltAnglefromWindowDoor() {
  getImpl<detail::ShadingOverhang_Impl>()->resetTiltAnglefromWindowDoor();
}

boost::optional<double> ShadingOverhang::leftextensionfromWindowDoorWidth() const {
  return getImpl<detail::ShadingOverhang_Impl>()->leftextensionfromWindowDoorWidth();
}

bool ShadingOverhang::setLeftextensionfromWindowDoorWidth(double leftextensionfromWindowDoorWidth) {
  return getImpl<detail::ShadingOverhang_Impl>()->setLeftextensionfromWindowDoorWidth(leftextensionfromWindowDoorWidth);
}

void ShadingOverhang::resetLeftextensionfromWindowDoorWidth() {
  getImpl<detail::ShadingOverhang_Impl>()->resetLeftextensionfromWindowDoorWidth();
}

boost::optional<double> ShadingOverhang::rightextensionfromWindowDoorWidth() const {
  return getImpl<detail::ShadingOverhang_Impl>()->rightextensionfromWindowDoorWidth();
}

bool ShadingOverhang::setRightextensionfromWindowDoorWidth(double rightextensionfromWindowDoorWidth) {
  return getImpl<detail::ShadingOverhang_Impl>()->setRightextensionfromWindowDoorWidth(rightextensionfromWindowDoorWidth);
}

void ShadingOverhang::resetRightextensionfromWindowDoorWidth() {
  getImpl<detail::ShadingOverhang_Impl>()->resetRightextensionfromWindowDoorWidth();
}

boost::optional<double> ShadingOverhang::depth() const {
  return getImpl<detail::ShadingOverhang_Impl>()->depth();
}

bool ShadingOverhang::setDepth(double depth) {
  return getImpl<detail::ShadingOverhang_Impl>()->setDepth(depth);
}

void ShadingOverhang::resetDepth() {
  getImpl<detail::ShadingOverhang_Impl>()->resetDepth();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> ShadingOverhang_Impl::heightaboveWindoworDoor() const {
  return getDouble(openstudio::Shading_OverhangFields::HeightaboveWindoworDoor, true);
}

bool ShadingOverhang_Impl::setHeightaboveWindoworDoor(double heightaboveWindoworDoor) {
  const bool result = setDouble(openstudio::Shading_OverhangFields::HeightaboveWindoworDoor, heightaboveWindoworDoor);
  OS_ASSERT(result);
  return result;
}

void ShadingOverhang_Impl::resetHeightaboveWindoworDoor() {
  OS_ASSERT(setString(openstudio::Shading_OverhangFields::HeightaboveWindoworDoor, ""));
}

double ShadingOverhang_Impl::tiltAnglefromWindowDoor() const {
  const auto value = getDouble(openstudio::Shading_OverhangFields::TiltAnglefromWindow_Door, true);
  OS_ASSERT(value);
  return *value;
}

bool ShadingOverhang_Impl::isTiltAnglefromWindowDoorDefaulted() const {
  return !getDouble(openstudio::Shading_OverhangFields::TiltAnglefromWindow_Door, false);
}

bool ShadingOverhang_Impl::setTiltAnglefromWindowDoor(double tiltAnglefromWindowDoor) {
  return setDouble(openstudio::Shading_OverhangFields::TiltAnglefromWindow_Door, tiltAnglefromWindowDoor);
}

void ShadingOverhang_Impl::resetTiltAnglefromWindowDoor() {
  OS_ASSERT(setString(openstudio::Shading_OverhangFields::TiltAnglefromWindow_Door, ""));
}

boost::optional<double> ShadingOverhang_Impl::leftextensionfromWindowDoorWidth() const {
  return getDouble(openstudio::Shading_OverhangFields::LeftextensionfromWindow_DoorWidth, true);
}

bool ShadingOverhang_Impl::setLeftextensionfromWindowDoorWidth(double leftextensionfromWindowDoorWidth) {
  const bool result = setDouble(openstudio::Shading_OverhangFields::LeftextensionfromWindow_DoorWidth, leftextensionfromWindowDoorWidth);
  OS_ASSERT(result);
  return result;
}

void ShadingOverhang_Impl::resetLeftextensionfromWindowDoorWidth() {
  OS_ASSERT(setString(openstudio::Shading_OverhangFields::LeftextensionfromWindow_DoorWidth, ""));
}

boost::optional<double> ShadingOverhang_Impl::rightextensionfromWindowDoorWidth() const {
  return getDouble(openstudio::Shading_OverhangFields::RightextensionfromWindow_DoorWidth, true);
}

bool ShadingOverhang_Impl::setRightextensionfromWindowDoorWidth(double rightextensionfromWindowDoorWidth) {
  const bool result = setDouble(openstudio::Shading_OverhangFields::RightextensionfromWindow_DoorWidth, rightextensionfromWindowDoorWidth);
  OS_ASSERT(result);
  return result;
}

void ShadingOverhang_Impl::resetRightextensionfromWindowDoorWidth() {
  OS_ASSERT(setString(openstudio::Shading_OverhangFields::RightextensionfromWindow_DoorWidth, ""));
}

boost::optional<double> ShadingOverhang_Impl::depth() const {
  return getDouble(openstudio::Shading_OverhangFields::Depth, true);
}

bool ShadingOverhang_Impl::setDepth(double depth) {
  return setDouble(openstudio::Shading_OverhangFields::Depth, depth);
}

void ShadingOverhang_Impl::resetDepth() {
  OS_ASSERT(setString(openstudio::Shading_OverhangFields::Depth, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
