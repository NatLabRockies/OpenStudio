/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLOORDETAILED_HPP
#define EPMODEL_FLOORDETAILED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FloorDetailed_Impl;
  }

  class EPMODEL_API FloorDetailed : public ModelObject
  {
   public:
    explicit FloorDetailed(const Model& model);

    virtual ~FloorDetailed() override = default;
    FloorDetailed(const FloorDetailed& other) = default;
    FloorDetailed(FloorDetailed&& other) = default;
    FloorDetailed& operator=(const FloorDetailed&) = default;
    FloorDetailed& operator=(FloorDetailed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outsideBoundaryConditionValues();
    static std::vector<std::string> sunExposureValues();
    static std::vector<std::string> windExposureValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar accessors map directly to EnergyPlus Floor:Detailed scalar fields
    //   (Outside Boundary Condition, Sun Exposure, Wind Exposure, View Factor to Ground, Number of Vertices).
    // - Field Mapping: Construction Name, Zone Name, Space Name, and Outside Boundary Condition Object are
    //   relationship-like fields and are intentionally excluded from scalar accessors.
    // - Field Mapping: Extensible Vertex X/Y/Z coordinate groups are non-scalar geometry relationships and are
    //   intentionally excluded from scalar accessors.
    // - ForwardTranslator Evidence: GeometryTranslator maps Floor:Detailed scalar fields (including Outside Boundary
    //   Condition, Sun/Wind Exposure, View Factor to Ground, Number of Vertices) directly into BuildingSurface:Detailed
    //   during geometry translation.
    // - TODO(parity): Add typed relationship/extensible-vertex APIs after scalar scaffold saturation.
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
    bool setViewFactortoGround(double viewFactortoGround);
    void resetViewFactortoGround();
    bool isViewFactortoGroundAutocalculated() const;
    void autocalculateViewFactortoGround();

    boost::optional<int> numberofVertices() const;
    bool setNumberofVertices(int numberofVertices);
    void resetNumberofVertices();
    bool isNumberofVerticesAutocalculated() const;
    void autocalculateNumberofVertices();

   protected:
    using ImplType = detail::FloorDetailed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FloorDetailed(std::shared_ptr<detail::FloorDetailed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
