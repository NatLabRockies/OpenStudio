/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPLIANCEBUILDING_HPP
#define EPMODEL_COMPLIANCEBUILDING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ComplianceBuilding_Impl;
}

class EPMODEL_API ComplianceBuilding : public ModelObject
{
 public:
  explicit ComplianceBuilding(const Model& model);

  virtual ~ComplianceBuilding() override = default;
  ComplianceBuilding(const ComplianceBuilding& other) = default;
  ComplianceBuilding(ComplianceBuilding&& other) = default;
  ComplianceBuilding& operator=(const ComplianceBuilding&) = default;
  ComplianceBuilding& operator=(ComplianceBuilding&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: buildingRotationforAppendixG maps directly to EnergyPlus
  //   Compliance:Building / Building Rotation for Appendix G.
  // - TODO(parity): Revisit API naming only if a model-counterpart parity target is introduced.
  double buildingRotationforAppendixG() const;
  bool isBuildingRotationforAppendixGDefaulted() const;
  bool setBuildingRotationforAppendixG(double buildingRotationforAppendixG);
  void resetBuildingRotationforAppendixG();

 protected:
  using ImplType = detail::ComplianceBuilding_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ComplianceBuilding(std::shared_ptr<detail::ComplianceBuilding_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
