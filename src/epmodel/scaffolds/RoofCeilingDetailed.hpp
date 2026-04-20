/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOFCEILINGDETAILED_HPP
#define EPMODEL_ROOFCEILINGDETAILED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoofCeilingDetailed_Impl;
  }

  class EPMODEL_API RoofCeilingDetailed : public ModelObject
  {
   public:
    explicit RoofCeilingDetailed(const Model& model);

    virtual ~RoofCeilingDetailed() override = default;
    RoofCeilingDetailed(const RoofCeilingDetailed& other) = default;
    RoofCeilingDetailed(RoofCeilingDetailed&& other) = default;
    RoofCeilingDetailed& operator=(const RoofCeilingDetailed&) = default;
    RoofCeilingDetailed& operator=(RoofCeilingDetailed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outsideBoundaryConditionValues();
    static std::vector<std::string> sunExposureValues();
    static std::vector<std::string> windExposureValues();

    // Schema Alignment Notes:
    // - API: This type has no openstudio::model counterpart, so it keeps the IDD-derived RoofCeiling:Detailed naming.
    // - Field Mapping: Scalar accessors map directly to the EnergyPlus RoofCeiling:Detailed fields
    //   (Outside Boundary Condition, Sun Exposure, Wind Exposure, View Factor to Ground, Number of Vertices).
    // - Field Mapping: Construction Name, Zone Name, Space Name, Outside Boundary Condition Object, and
    //   extensible vertex X/Y/Z coordinate groups are relationship/extensible fields and are intentionally excluded.
    // - ForwardTranslator Evidence: GeometryTranslator routes the RoofCeiling:Detailed scalars straight into BuildingSurface:Detailed.
    // - TODO(parity): Add relationship/extensible vertex APIs after scalar saturation completes.
    std::string outsideBoundaryCondition() const;
    bool setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition);

    std::string sunExposure() const;
    bool setSunExposure(const std::string& sunExposure);
    bool isSunExposureDefaulted() const;
    void resetSunExposure();

    std::string windExposure() const;
    bool setWindExposure(const std::string& windExposure);
    bool isWindExposureDefaulted() const;
    void resetWindExposure();

    boost::optional<double> viewFactortoGround() const;
    bool setViewFactortoGround(double viewFactortoGround);
    bool isViewFactortoGroundAutocalculated() const;
    void autocalculateViewFactortoGround();
    void resetViewFactortoGround();

    boost::optional<int> numberofVertices() const;
    bool setNumberofVertices(int numberofVertices);
    bool isNumberofVerticesAutocalculated() const;
    void autocalculateNumberofVertices();
    void resetNumberofVertices();

   protected:
    using ImplType = detail::RoofCeilingDetailed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoofCeilingDetailed(std::shared_ptr<detail::RoofCeilingDetailed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
