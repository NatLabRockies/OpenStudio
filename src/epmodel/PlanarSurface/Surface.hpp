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

    boost::optional<double> numberofVertices() const;
    bool isNumberofVerticesDefaulted() const;
    bool isNumberofVerticesAutocalculated() const;
    bool setNumberofVertices(unsigned int numberofVertices);
    void resetNumberofVertices();
    void autocalculateNumberofVertices();

    bool setSpace(const Space& space);

   protected:
    using ImplType = detail::Surface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Surface(std::shared_ptr<detail::Surface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
