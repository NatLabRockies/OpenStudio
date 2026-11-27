/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANARSURFACE_HPP
#define EPMODEL_PLANARSURFACE_HPP

#include "ParentObject/ParentObject.hpp"
#include "ConstructionBase/ConstructionBase.hpp"

#include "../utilities/core/Enum.hpp"

#include "../utilities/idf/IdfObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {

class Plane;
class Point3d;
class Vector3d;

namespace epmodel {

  class ConstructionBase;
  class Space;

  namespace detail {
    class PlanarSurface_Impl;
  }

  // clang-format off

  /** \class SearchDistanceType
   *  \brief Where a PlanarSurface's construction comes from, as in EnergyPlus' ConstructionAssignments: Explicit if named on the
   *  surface, Space if assigned by its Space's ConstructionAssignmentSet, Building if assigned by the Building's. A lower value takes
   *  precedence when resolving a surface against its adjacent surface. Unlike Model, which also searches the SpaceType, BuildingStory and
   *  Building SpaceType, EnergyPlus only has Space and Building sets.
   *  \relates PlanarSurface */
  OPENSTUDIO_ENUM(SearchDistanceType,
    ((Explicit))
    ((Space))
    ((Building))
  );

  // clang-format on

  /** \brief A construction along with where it was found.
   *
   * \par EnergyPlus object
   * This has no EnergyPlus object. It mirrors EnergyPlus' <code>ConstructionWithSearchDistance</code>, used to resolve the
   * construction of a surface from its ConstructionAssignmentSets.
   *
   * \par OpenStudio Model API
   * There is no corresponding <code>openstudio::model</code> class: Model returns a
   * <code>std::pair&lt;ConstructionBase, int&gt;</code> instead.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  struct EPMODEL_API ConstructionWithSearchDistance
  {
    ConstructionWithSearchDistance(SearchDistanceType searchDistance, ConstructionBase construction);

    SearchDistanceType searchDistance;
    ConstructionBase construction;
  };

  /** \brief Abstract base for planar geometry belonging to a surface group.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object; concrete `Surface` and `SubSurface` provide persisted vertices,
   * while the \epobject{group-thermal-zone-description-geometry.html#internalmass,InternalMass}-backed `InteriorPartitionSurface` projects its area without EnergyPlus vertices.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model base is `openstudio::model::PlanarSurface`; concrete subclasses provide
   * geometry, parent-space, and boundary-condition behavior.
   * <b>Changed:</b> a defaulted construction is resolved the way EnergyPlus does it: from the Space's ConstructionAssignmentSet, then
   * the Building's (Model also searches the SpaceType, BuildingStory, and Building SpaceType). <code>constructionWithSearchDistance()</code>
   * therefore returns a ConstructionWithSearchDistance whose SearchDistanceType is Explicit, Space or Building, where Model returns
   * a <code>std::pair&lt;ConstructionBase, int&gt;</code> with a search distance from 0 to 5. When resolving against an adjacent surface,
   * two different constructions with reversed layers are each kept regardless of search distance, where Model only checks this when
   * the search distances are equal.
   *
   * \par Known limitations
   * EnergyPlus stores geometry differently for building, fenestration, and internal-mass objects, so concrete wrappers
   * determine which geometry and adjacency operations can round-trip.
   */
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

    /** Returns the construction EnergyPlus uses for this surface. That is the construction named on this surface if any, else the one
     *  assigned by the ConstructionAssignmentSet of its Space, else by the Building's. For a Surface or SubSurface with an adjacent
     *  surface, both sides are resolved together, as EnergyPlus does: see \ref constructionWithSearchDistance. */
    boost::optional<ConstructionBase> construction() const;

    /** Returns this surface's own construction along with where it was found: Explicit if named on this surface, Space if assigned by
     *  its Space's ConstructionAssignmentSet, Building if assigned by the Building's. The adjacent surface, if any, is not considered. */
    boost::optional<ConstructionWithSearchDistance> constructionWithSearchDistance() const;

    /// Returns true if this surface does not name a construction, i.e. it is assigned by a ConstructionAssignmentSet, if any.
    bool isConstructionDefaulted() const;

    bool setConstruction(const ConstructionBase& construction);
    void resetConstruction();

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
