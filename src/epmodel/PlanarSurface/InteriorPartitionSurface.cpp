/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurface/InteriorPartitionSurface.hpp"
#include "PlanarSurface/InteriorPartitionSurface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/InternalMass_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

InteriorPartitionSurface::InteriorPartitionSurface(const Model& model) : ModelObject(InteriorPartitionSurface::iddObjectType(), model) {}

InteriorPartitionSurface::InteriorPartitionSurface(std::shared_ptr<detail::InteriorPartitionSurface_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType InteriorPartitionSurface::iddObjectType() {
  return IddObjectType::InternalMass;
}

bool InteriorPartitionSurface::converttoInternalMass() const {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->converttoInternalMass();
}

bool InteriorPartitionSurface::isConverttoInternalMassDefaulted() const {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->isConverttoInternalMassDefaulted();
}

boost::optional<double> InteriorPartitionSurface::surfaceArea() const {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->surfaceArea();
}

boost::optional<double> InteriorPartitionSurface::numberofVertices() const {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->numberofVertices();
}

bool InteriorPartitionSurface::isNumberofVerticesDefaulted() const {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->isNumberofVerticesDefaulted();
}

bool InteriorPartitionSurface::isNumberofVerticesAutocalculated() const {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->isNumberofVerticesAutocalculated();
}

bool InteriorPartitionSurface::setConverttoInternalMass(bool converttoInternalMass) {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->setConverttoInternalMass(converttoInternalMass);
}

void InteriorPartitionSurface::resetConverttoInternalMass() {
  getImpl<detail::InteriorPartitionSurface_Impl>()->resetConverttoInternalMass();
}

bool InteriorPartitionSurface::setSurfaceArea(boost::optional<double> surfaceArea) {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->setSurfaceArea(surfaceArea);
}

bool InteriorPartitionSurface::setSurfaceArea(double surfaceArea) {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->setSurfaceArea(surfaceArea);
}

void InteriorPartitionSurface::resetSurfaceArea() {
  getImpl<detail::InteriorPartitionSurface_Impl>()->resetSurfaceArea();
}

bool InteriorPartitionSurface::setNumberofVertices(boost::optional<double> numberofVertices) {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->setNumberofVertices(numberofVertices);
}

bool InteriorPartitionSurface::setNumberofVertices(double numberofVertices) {
  return getImpl<detail::InteriorPartitionSurface_Impl>()->setNumberofVertices(numberofVertices);
}

void InteriorPartitionSurface::resetNumberofVertices() {
  getImpl<detail::InteriorPartitionSurface_Impl>()->resetNumberofVertices();
}

void InteriorPartitionSurface::autocalculateNumberofVertices() {
  getImpl<detail::InteriorPartitionSurface_Impl>()->autocalculateNumberofVertices();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool InteriorPartitionSurface_Impl::converttoInternalMass() const {
  // InternalMass is already the translated EP object for this class.
  return true;
}

bool InteriorPartitionSurface_Impl::isConverttoInternalMassDefaulted() const {
  // Compatibility shim: no dedicated EP field exists for this OS-only flag.
  return true;
}

boost::optional<double> InteriorPartitionSurface_Impl::surfaceArea() const {
  return getDouble(openstudio::InternalMassFields::SurfaceArea, true);
}

boost::optional<double> InteriorPartitionSurface_Impl::numberofVertices() const {
  // Compatibility shim: InternalMass has no vertex-count scalar.
  return boost::none;
}

bool InteriorPartitionSurface_Impl::isNumberofVerticesDefaulted() const {
  return true;
}

bool InteriorPartitionSurface_Impl::isNumberofVerticesAutocalculated() const {
  return false;
}

bool InteriorPartitionSurface_Impl::setConverttoInternalMass(bool converttoInternalMass) {
  // Compatibility shim: this epmodel class always maps to InternalMass.
  return converttoInternalMass;
}

void InteriorPartitionSurface_Impl::resetConverttoInternalMass() {}

bool InteriorPartitionSurface_Impl::setSurfaceArea(boost::optional<double> surfaceArea) {
  bool result = false;
  if (surfaceArea) {
    result = setDouble(openstudio::InternalMassFields::SurfaceArea, surfaceArea.get());
  } else {
    result = setString(openstudio::InternalMassFields::SurfaceArea, "");
  }
  return result;
}

bool InteriorPartitionSurface_Impl::setSurfaceArea(double surfaceArea) {
  return setDouble(openstudio::InternalMassFields::SurfaceArea, surfaceArea);
}

void InteriorPartitionSurface_Impl::resetSurfaceArea() {
  OS_ASSERT(setString(openstudio::InternalMassFields::SurfaceArea, ""));
}

bool InteriorPartitionSurface_Impl::setNumberofVertices(boost::optional<double> numberofVertices) {
  if (!numberofVertices) {
    return true;
  }
  return false;
}

bool InteriorPartitionSurface_Impl::setNumberofVertices(double numberofVertices) {
  static_cast<void>(numberofVertices);
  return false;
}

void InteriorPartitionSurface_Impl::resetNumberofVertices() {}

void InteriorPartitionSurface_Impl::autocalculateNumberofVertices() {}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
