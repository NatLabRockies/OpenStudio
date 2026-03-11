/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WALLDETAILED_HPP
#define EPMODEL_WALLDETAILED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WallDetailed_Impl;
  }

  class EPMODEL_API WallDetailed : public ModelObject
  {
   public:
    explicit WallDetailed(const Model& model);

    virtual ~WallDetailed() override = default;
    WallDetailed(const WallDetailed& other) = default;
    WallDetailed(WallDetailed&& other) = default;
    WallDetailed& operator=(const WallDetailed&) = default;
    WallDetailed& operator=(WallDetailed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> outsideBoundaryConditionValues();
    static std::vector<std::string> sunExposureValues();
    static std::vector<std::string> windExposureValues();

    // Schema Alignment Notes:
    // - API: Wall:Detailed has no openstudio::model counterpart, so the public API mirrors the IDD-derived names.
    // - Field Mapping: OutsideBoundaryCondition, SunExposure, WindExposure, and ViewFactortoGround map to Wall_DetailedFields.
    // - Field Mapping: Construction Name, Zone Name, Space Name, Outside Boundary Condition Object, and vertex data are relationship-link/geometry fields and are intentionally excluded.
    // - ForwardTranslator: GeometryTranslator carries the adjacency/vertex logic for this IDD type; scalar-only work here keeps those relationships untouched.
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

    boost::optional<double> viewFactorToGround() const;
    bool isViewFactorToGroundDefaulted() const;
    bool isViewFactorToGroundAutocalculated() const;
    bool setViewFactorToGround(double viewFactorToGround);
    void resetViewFactorToGround();
    void autocalculateViewFactorToGround();

   protected:
    using ImplType = detail::WallDetailed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WallDetailed(std::shared_ptr<detail::WallDetailed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
