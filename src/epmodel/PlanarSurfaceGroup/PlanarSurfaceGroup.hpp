/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANARSURFACEGROUP_HPP
#define EPMODEL_PLANARSURFACEGROUP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {

class BoundingBox;
class Transformation;

namespace epmodel {

  namespace detail {
    class PlanarSurfaceGroup_Impl;
  }

  /** PlanarSurfaceGroup is an abstract class representing a group that holds many PlanarSurfaces. */
  class EPMODEL_API PlanarSurfaceGroup : public ModelObject
  {
   public:
    virtual ~PlanarSurfaceGroup() override = default;
    PlanarSurfaceGroup(const PlanarSurfaceGroup& other) = default;
    PlanarSurfaceGroup(PlanarSurfaceGroup&& other) = default;
    PlanarSurfaceGroup& operator=(const PlanarSurfaceGroup&) = default;
    PlanarSurfaceGroup& operator=(PlanarSurfaceGroup&&) = default;

    /** Returns the transformation from local coordinates to parent coordinates. */
    openstudio::Transformation transformation() const;

    /** Returns the transformation from local coordinates to building coordinates. */
    openstudio::Transformation buildingTransformation() const;

    /** Returns the transformation from local coordinates to site coordinates. */
    openstudio::Transformation siteTransformation() const;

    /** Sets the transformation from local coordinates to parent coordinates. */
    bool setTransformation(const openstudio::Transformation& transformation);

    /** Changes the transformation from local coordinates to parent coordinates,
     *  altering child geometry so surfaces remain in place. */
    bool changeTransformation(const openstudio::Transformation& transformation);

    /** Get the BoundingBox in local coordinates. */
    openstudio::BoundingBox boundingBox() const;

    /** Get the BoundingBox in parent coordinates. */
    openstudio::BoundingBox boundingBoxParentCoordinates() const;

    /** Get the BoundingBox in building coordinates. */
    openstudio::BoundingBox boundingBoxBuildingCoordinates() const;

    /** Get the BoundingBox in site coordinates. */
    openstudio::BoundingBox boundingBoxSiteCoordinates() const;

   protected:
    PlanarSurfaceGroup(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);

    using ImplType = detail::PlanarSurfaceGroup_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlanarSurfaceGroup(std::shared_ptr<detail::PlanarSurfaceGroup_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.PlanarSurfaceGroup");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
