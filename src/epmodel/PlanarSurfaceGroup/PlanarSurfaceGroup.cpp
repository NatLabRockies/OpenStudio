/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurfaceGroup/PlanarSurfaceGroup.hpp"
#include "PlanarSurfaceGroup/PlanarSurfaceGroup_Impl.hpp"

#include "Model.hpp"
#include "ParentObject/Building.hpp"
#include "ParentObject/Building_Impl.hpp"

#include <utilities/geometry/BoundingBox.hpp>
#include <utilities/geometry/Transformation.hpp>

namespace openstudio {
namespace epmodel {

  openstudio::Transformation PlanarSurfaceGroup::transformation() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->transformation();
  }

  openstudio::Transformation PlanarSurfaceGroup::buildingTransformation() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->buildingTransformation();
  }

  openstudio::Transformation PlanarSurfaceGroup::siteTransformation() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->siteTransformation();
  }

  bool PlanarSurfaceGroup::setTransformation(const openstudio::Transformation& transformation) {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->setTransformation(transformation);
  }

  bool PlanarSurfaceGroup::changeTransformation(const openstudio::Transformation& transformation) {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->changeTransformation(transformation);
  }

  openstudio::BoundingBox PlanarSurfaceGroup::boundingBox() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->boundingBox();
  }

  openstudio::BoundingBox PlanarSurfaceGroup::boundingBoxParentCoordinates() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->boundingBoxParentCoordinates();
  }

  openstudio::BoundingBox PlanarSurfaceGroup::boundingBoxBuildingCoordinates() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->boundingBoxBuildingCoordinates();
  }

  openstudio::BoundingBox PlanarSurfaceGroup::boundingBoxSiteCoordinates() const {
    return getImpl<detail::PlanarSurfaceGroup_Impl>()->boundingBoxSiteCoordinates();
  }

  PlanarSurfaceGroup::PlanarSurfaceGroup(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : ModelObject(type, model, fastName, isTransient) {}

  PlanarSurfaceGroup::PlanarSurfaceGroup(std::shared_ptr<detail::PlanarSurfaceGroup_Impl> impl) : ModelObject(std::move(impl)) {}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    openstudio::Transformation PlanarSurfaceGroup_Impl::siteTransformation() const {
      Transformation transformation;

      boost::optional<Building> building = this->model().getOptionalUniqueModelObject<Building>();
      if (building) {
        transformation = building->transformation() * this->buildingTransformation();
      } else {
        transformation = this->buildingTransformation();
      }
      return transformation;
    }
    openstudio::BoundingBox PlanarSurfaceGroup_Impl::boundingBoxParentCoordinates() const {
      return transformation() * boundingBox();
    }

    openstudio::BoundingBox PlanarSurfaceGroup_Impl::boundingBoxBuildingCoordinates() const {
      return buildingTransformation() * boundingBox();
    }

    openstudio::BoundingBox PlanarSurfaceGroup_Impl::boundingBoxSiteCoordinates() const {
      return siteTransformation() * boundingBox();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
