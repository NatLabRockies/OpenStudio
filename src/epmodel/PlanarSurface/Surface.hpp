/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACE_HPP
#define EPMODEL_SURFACE_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurface.hpp"

#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Space;
  class SubSurface;
  class SurfaceIntersection;

  namespace detail {
    class Surface_Impl;
  }

  class EPMODEL_API Surface : public PlanarSurface
  {
   public:
    explicit Surface(const std::vector<Point3d>& vertices, const Model& model);

    virtual ~Surface() override = default;
    Surface(const Surface& other) = default;
    Surface(Surface&& other) = default;
    Surface& operator=(const Surface&) = default;
    Surface& operator=(Surface&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validSurfaceTypeValues();

    /** Returns true if surfaceType is "Roof" or "Ceiling". */
    static bool isCeilingLike(const std::string& surfaceType);
    static std::vector<std::string> validOutsideBoundaryConditionValues();
    static std::vector<std::string> validSunExposureValues();
    static std::vector<std::string> validWindExposureValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model Surface scalar accessor names/signatures.
    // - Field Mapping: These APIs map to BuildingSurface:Detailed fields in the EnergyPlus schema.
    // - Field Mapping: Construction Name, Zone Name, Space Name, Outside Boundary Condition Object,
    //   and extensible vertex coordinates are relationship/non-scalar fields and are intentionally excluded.
    // - ForwardTranslator evidence: ForwardTranslateSurface.cpp maps surfaceType, outsideBoundaryCondition,
    //   sunExposure, windExposure, and viewFactortoGround directly to BuildingSurface:Detailed.
    // - TODO(parity): Add non-scalar geometry and relationship APIs in later parity milestones.
    std::string surfaceType() const;
    bool setSurfaceType(const std::string& surfaceType);

    std::string outsideBoundaryCondition() const;
    bool setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition);

    std::string sunExposure() const;
    bool isSunExposureDefaulted() const;
    bool setSunExposure(const std::string& sunExposure);
    void resetSunExposure();

    std::string windExposure() const;
    bool isWindExposureDefaulted() const;
    bool setWindExposure(const std::string& windExposure);
    void resetWindExposure();

    boost::optional<double> viewFactortoGround() const;
    bool isViewFactortoGroundDefaulted() const;
    bool isViewFactortoGroundAutocalculated() const;
    bool setViewFactortoGround(double viewFactortoGround);
    void resetViewFactortoGround();
    void autocalculateViewFactortoGround();

    unsigned int numberofVertices() const;
    bool isNumberofVerticesDefaulted() const;
    bool isNumberofVerticesAutocalculated() const;
    bool setNumberofVertices(unsigned int numberofVertices);
    void resetNumberofVertices();
    void autocalculateNumberofVertices();

    /// Returns all child \link SubSurface SubSurfaces \endlink.
    std::vector<SubSurface> subSurfaces() const;

    /// Sets the parent Space.
    bool setSpace(const Space& space);

    /** Sets the window-to-wall ratio. Replaces existing windows on this Wall surface.
     *  Returns the new SubSurface if successful. */
    boost::optional<SubSurface> setWindowToWallRatio(double wwr, double desiredHeightOffset = 0.762, bool heightOffsetFromFloor = true);

    /** Returns the adjacent Surface, if it exists. */
    boost::optional<Surface> adjacentSurface() const;
    /** Sets the adjacent Surface, will clear adjacent surface on other surface. */
    bool setAdjacentSurface(Surface& surface);
    /** Resets the adjacent Surface. */
    void resetAdjacentSurface();

    /** Intersect with other Surface in other Space.
   *  Returns false if either surface has child windows.
   *  Returns false if either surface has an adjacent surface.
   *  Returns false if surfaces are not on the same plane with opposing outward normals.
   *  If the surfaces are the same, returns true but no new geometry is created.
   *  Returns true if an intersection occurred. Does not set surface adjacency. */
    bool intersect(Surface& otherSurface);
    boost::optional<SurfaceIntersection> computeIntersection(Surface& otherSurface);

    /** Creates an adjacent Surface in another Space, also create adjacent SubSurface objects if needed.
      Returns the new Surface if created. */
    boost::optional<Surface> createAdjacentSurface(const Space& otherSpace);

    /** Returns true if the surface has outsideBoundaryCondition of Ground, GroundFCfactorMethod
   *  GroundSlabPreprocessorAverage, GroundSlabPreprocessorCore, GroundSlabPreprocessorPerimeter,
   *  GroundBasementPreprocessorAverageWall, GroundBasementPreprocessorAverageFloor,
   *  GroundBasementPreprocessorUpperWall, GroundBasementPreprocessorLowerWall, or
   *  Foundation */
    bool isGroundSurface() const;

    /** Returns true if the Surface is part of the building envelope. */
    bool isPartOfEnvelope() const;

    /** Assign default surface type based on vertices. */
    void assignDefaultSurfaceType();

    /** Assign default boundary condition. */
    void assignDefaultBoundaryCondition();

    /** Assign default sun exposure. */
    void assignDefaultSunExposure();

    /** Assign default wind exposure. */
    void assignDefaultWindExposure();

   protected:
    using ImplType = detail::Surface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class openstudio::epmodel::detail::Surface_Impl;

    explicit Surface(std::shared_ptr<detail::Surface_Impl> impl);
  };

  /** SurfaceIntersection contains detailed information about a surface intersection. */
  class EPMODEL_API SurfaceIntersection
  {
   public:
    SurfaceIntersection(Surface surface1, Surface surface2, std::vector<Surface> newSurfaces1, std::vector<Surface> newSurfaces2);

    // first surface post intersection
    Surface surface1() const;

    // second surface post intersection
    Surface surface2() const;

    // new surfaces generated in the first surface's space
    std::vector<Surface> newSurfaces1() const;

    // new surfaces generated in the second surface's space
    std::vector<Surface> newSurfaces2() const;

   private:
    Surface m_surface1;
    Surface m_surface2;
    std::vector<Surface> m_newSurfaces1;
    std::vector<Surface> m_newSurfaces2;
  };

  /** \relates SurfaceIntersection */
  EPMODEL_API std::ostream& operator<<(std::ostream& os, const SurfaceIntersection& surfaceIntersection);

}  // namespace epmodel
}  // namespace openstudio

#endif
