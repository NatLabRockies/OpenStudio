/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANARSURFACE_HPP
#define EPMODEL_PLANARSURFACE_HPP

#include "ParentObject/ParentObject.hpp"

#include "../utilities/idf/IdfObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {

class Plane;
class Point3d;
class Vector3d;

namespace epmodel {

  class Space;

  namespace detail {
    class PlanarSurface_Impl;
  }

  class EPMODEL_API PlanarSurface : public ParentObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{
    virtual ~PlanarSurface() override = default;
    PlanarSurface(const PlanarSurface& other) = default;
    PlanarSurface(PlanarSurface&& other) = default;
    PlanarSurface& operator=(const PlanarSurface&) = default;
    PlanarSurface& operator=(PlanarSurface&&) = default;

    //@}
    /** @name Getters */
    //@{

    /// Returns the containing Space if available.
    boost::optional<Space> space() const;

    /// Returns the vertices.
    std::vector<Point3d> vertices() const;

    //@}
    /** @name Setters */
    //@{

    /// Sets the vertices.
    bool setVertices(const std::vector<Point3d>& vertices);

    //@}
    /** @name Queries */
    //@{

    /// Computes the surface's gross area (m^2).
    double grossArea() const;

    /// Reports if user should subtract this surface's net area from parent's gross area
    /// to compute parent's net area (e.g. true for a window).
    bool subtractFromGrossArea() const;

    /// Computes the surface's net area (m^2).
    double netArea() const;

    /// Returns the outward normal vector in local coordinates.
    /// Throws openstudio::Exception if cannot compute outward normal for this surface.
    Vector3d outwardNormal() const;

    /// Returns the surface's tilt measured as angle between outward normal and local up (radians).
    /// Throws openstudio::Exception if cannot compute outward normal for this surface.
    double tilt() const;

    /// Returns the surface's azimuth measured clockwise as angle between outward normal and local North (radians).
    /// Throws openstudio::Exception if cannot compute outward normal for this surface.
    double azimuth() const;

    /// Get the plane, throws openstudio::Exception if cannot compute plane for this surface.
    Plane plane() const;

    /// Return the centroid of this planar surface's vertices
    Point3d centroid() const;

    bool isConvex() const;

    /// Get a triangulation of this surface, subsurfaces will be replaced by holes in the triangulation
    std::vector<std::vector<Point3d>> triangulation() const;

    /// Check if this planar surface's vertices are equal to the other's in the building coordinate system
    bool equalVertices(const PlanarSurface& other) const;

    /// Check if this planar surface's vertices are reverse equal to the other's in the building coordinate system
    bool reverseEqualVertices(const PlanarSurface& other) const;

    //@}
   protected:
    /** @name Constructors and Destructors */
    //@{

    PlanarSurface(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    //@}

    /// @cond

    using ImplType = detail::PlanarSurface_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit PlanarSurface(std::shared_ptr<detail::PlanarSurface_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.PlanarSurface");

    /// @endcond
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
