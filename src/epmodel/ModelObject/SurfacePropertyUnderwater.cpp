/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyUnderwater.hpp"
#include "SurfacePropertyUnderwater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SurfaceProperty_Underwater_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyUnderwater::SurfacePropertyUnderwater(const Model& model) : ModelObject(SurfacePropertyUnderwater::iddObjectType(), model) {
    OS_ASSERT(setDistanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer(0.5));
  }

  SurfacePropertyUnderwater::SurfacePropertyUnderwater(std::shared_ptr<detail::SurfacePropertyUnderwater_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyUnderwater::iddObjectType() {
    return IddObjectType::SurfaceProperty_Underwater;
  }

  double SurfacePropertyUnderwater::distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer() const {
    return getImpl<detail::SurfacePropertyUnderwater_Impl>()->distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer();
  }

  bool SurfacePropertyUnderwater::setDistanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer(
    double distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer) {
    return getImpl<detail::SurfacePropertyUnderwater_Impl>()->setDistanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer(
      distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SurfacePropertyUnderwater_Impl::distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer() const {
      const auto value = getDouble(openstudio::SurfaceProperty_UnderwaterFields::DistancefromSurfaceCentroidtoLeadingEdgeofBoundaryLayer, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyUnderwater_Impl::setDistanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer(
      double distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer) {
      return setDouble(openstudio::SurfaceProperty_UnderwaterFields::DistancefromSurfaceCentroidtoLeadingEdgeofBoundaryLayer,
                       distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
