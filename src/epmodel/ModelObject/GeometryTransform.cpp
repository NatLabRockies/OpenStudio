/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeometryTransform.hpp"
#include "GeometryTransform_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GeometryTransform_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeometryTransform::GeometryTransform(const Model& model) : ModelObject(GeometryTransform::iddObjectType(), model) {}

GeometryTransform::GeometryTransform(std::shared_ptr<detail::GeometryTransform_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType GeometryTransform::iddObjectType() {
  return IddObjectType::GeometryTransform;
}

std::vector<std::string> GeometryTransform::planeofTransformValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::GeometryTransformFields::PlaneofTransform);
}

std::string GeometryTransform::planeofTransform() const {
  return getImpl<detail::GeometryTransform_Impl>()->planeofTransform();
}

bool GeometryTransform::isPlaneofTransformDefaulted() const {
  return getImpl<detail::GeometryTransform_Impl>()->isPlaneofTransformDefaulted();
}

bool GeometryTransform::setPlaneofTransform(const std::string& planeofTransform) {
  return getImpl<detail::GeometryTransform_Impl>()->setPlaneofTransform(planeofTransform);
}

void GeometryTransform::resetPlaneofTransform() {
  getImpl<detail::GeometryTransform_Impl>()->resetPlaneofTransform();
}

double GeometryTransform::currentAspectRatio() const {
  return getImpl<detail::GeometryTransform_Impl>()->currentAspectRatio();
}

bool GeometryTransform::setCurrentAspectRatio(double currentAspectRatio) {
  return getImpl<detail::GeometryTransform_Impl>()->setCurrentAspectRatio(currentAspectRatio);
}

double GeometryTransform::newAspectRatio() const {
  return getImpl<detail::GeometryTransform_Impl>()->newAspectRatio();
}

bool GeometryTransform::setNewAspectRatio(double newAspectRatio) {
  return getImpl<detail::GeometryTransform_Impl>()->setNewAspectRatio(newAspectRatio);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string GeometryTransform_Impl::planeofTransform() const {
  const auto value = openstudio::detail::IdfObject_Impl::getString(openstudio::GeometryTransformFields::PlaneofTransform, true);
  OS_ASSERT(value);
  return *value;
}

bool GeometryTransform_Impl::isPlaneofTransformDefaulted() const {
  return !openstudio::detail::IdfObject_Impl::getString(openstudio::GeometryTransformFields::PlaneofTransform, false);
}

bool GeometryTransform_Impl::setPlaneofTransform(const std::string& planeofTransform) {
  return openstudio::detail::IdfObject_Impl::setString(openstudio::GeometryTransformFields::PlaneofTransform, planeofTransform);
}

void GeometryTransform_Impl::resetPlaneofTransform() {
  OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(openstudio::GeometryTransformFields::PlaneofTransform, ""));
}

double GeometryTransform_Impl::currentAspectRatio() const {
  const auto value = getDouble(openstudio::GeometryTransformFields::CurrentAspectRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool GeometryTransform_Impl::setCurrentAspectRatio(double currentAspectRatio) {
  return setDouble(openstudio::GeometryTransformFields::CurrentAspectRatio, currentAspectRatio);
}

double GeometryTransform_Impl::newAspectRatio() const {
  const auto value = getDouble(openstudio::GeometryTransformFields::NewAspectRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool GeometryTransform_Impl::setNewAspectRatio(double newAspectRatio) {
  return setDouble(openstudio::GeometryTransformFields::NewAspectRatio, newAspectRatio);
}

std::vector<std::string> GeometryTransform_Impl::planeofTransformValues() const {
  return openstudio::epmodel::GeometryTransform::planeofTransformValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
