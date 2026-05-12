/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACE_HPP
#define EPMODEL_SUBSURFACE_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurface.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Surface;
  class WindowPropertyFrameAndDivider;

  namespace detail {
    class SubSurface_Impl;
  }

  class EPMODEL_API SubSurface : public PlanarSurface
  {
   public:
    explicit SubSurface(const std::vector<Point3d>& vertices, const Model& model);

    virtual ~SubSurface() override = default;
    SubSurface(const SubSurface& other) = default;
    SubSurface(SubSurface&& other) = default;
    SubSurface& operator=(const SubSurface&) = default;
    SubSurface& operator=(SubSurface&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validSubSurfaceTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::SubSurface scalar accessor names/signatures.
    // - Field Mapping: These APIs map to FenestrationSurface:Detailed fields in the EnergyPlus schema.
    // - Field Mapping: Construction Name, Building Surface Name, Outside Boundary Condition Object,
    //   Frame and Divider Name, and extensible vertex coordinates are relationship/non-scalar fields and are excluded.
    // - ForwardTranslator evidence: ForwardTranslateSubSurface.cpp maps subSurfaceType, viewFactortoGround,
    //   and multiplier directly to FenestrationSurface:Detailed.
    // - TODO(parity): Add geometry and typed relationship APIs in later parity milestones.

    std::string subSurfaceType() const;
    bool isSubSurfaceTypeDefaulted() const;
    bool setSubSurfaceType(const std::string& subSurfaceType);
    void resetSubSurfaceType();

    boost::optional<double> viewFactortoGround() const;
    bool isViewFactortoGroundDefaulted() const;
    bool isViewFactortoGroundAutocalculated() const;
    bool setViewFactortoGround(double viewFactortoGround);
    void resetViewFactortoGround();
    void autocalculateViewFactortoGround();

    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    unsigned int numberofVertices() const;
    bool isNumberofVerticesDefaulted() const;
    bool isNumberofVerticesAutocalculated() const;
    bool setNumberofVertices(unsigned int numberofVertices);
    void resetNumberofVertices();
    void autocalculateNumberofVertices();

    bool allowWindowPropertyFrameAndDivider() const;
    boost::optional<WindowPropertyFrameAndDivider> windowPropertyFrameAndDivider() const;
    bool setWindowPropertyFrameAndDivider(const WindowPropertyFrameAndDivider& windowPropertyFrameAndDivider);
    void resetWindowPropertyFrameAndDivider();

    boost::optional<Surface> surface() const;
    bool setSurface(const Surface& surface);

    /// get the adjacent subsurface
    boost::optional<SubSurface> adjacentSubSurface() const;

    /// set the adjacent subsurface, will fail unless both sub surfaces are parented by surfaces
    /// which are adjacent
    bool setAdjacentSubSurface(SubSurface& subSurface);
    /// reset the adjacent subsurface, will clear references on both this and adjacent sub surface
    void resetAdjacentSubSurface();

    /** Assign default sub surface type based on vertices. */
    void assignDefaultSubSurfaceType();

    /** Return the surface()'s outsideBoundaryCondition, or an empty string. */
    std::string outsideBoundaryCondition() const;

    /* Get the total area of the sub surface rough area which includes the frame */
    double roughOpeningArea() const;

    /* Get the rough opening vertices for the sub surface including the frame */
    std::vector<Point3d> roughOpeningVertices() const;

    // Gets the total area of the frame
    double frameArea() const;

    // Gets the total area of the divider
    double dividerArea() const;

    /** Returns true if this sub-surface is a skylight (type "Window" with tilt < 60deg or > 179deg). */
    bool isSkylight() const;

   protected:
    using ImplType = detail::SubSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SubSurface(std::shared_ptr<detail::SubSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
