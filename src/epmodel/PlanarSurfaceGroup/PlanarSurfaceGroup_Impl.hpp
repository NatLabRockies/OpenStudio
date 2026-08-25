/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANARSURFACEGROUP_IMPL_HPP
#define EPMODEL_PLANARSURFACEGROUP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <utilities/geometry/Transformation.hpp>

namespace openstudio {

class BoundingBox;

namespace epmodel {

  namespace detail {

    class EPMODEL_API PlanarSurfaceGroup_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PlanarSurfaceGroup_Impl() override = default;

      /** Returns the transformation from local coordinates to parent coordinates. */
      virtual openstudio::Transformation transformation() const = 0;

      /** Returns the transformation from local coordinates to building coordinates. */
      virtual openstudio::Transformation buildingTransformation() const = 0;

      /** Returns the transformation from local coordinates to site coordinates. */
      openstudio::Transformation siteTransformation() const;

      /** Sets the transformation from local coordinates to parent coordinates. */
      virtual bool setTransformation(const openstudio::Transformation& transformation) = 0;

      /** Changes the transformation, altering child geometry so surfaces remain in place. */
      virtual bool changeTransformation(const openstudio::Transformation& transformation) = 0;

      /** Get the BoundingBox in local coordinates. */
      virtual openstudio::BoundingBox boundingBox() const = 0;

      /** Get the BoundingBox in parent coordinates. */
      openstudio::BoundingBox boundingBoxParentCoordinates() const;

      /** Get the BoundingBox in building coordinates. */
      openstudio::BoundingBox boundingBoxBuildingCoordinates() const;

      /** Get the BoundingBox in site coordinates. */
      openstudio::BoundingBox boundingBoxSiteCoordinates() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
