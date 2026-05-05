/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ComplianceBuilding.hpp"
#include "ComplianceBuilding_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Compliance_Building_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ComplianceBuilding::ComplianceBuilding(const Model& model) : ModelObject(ComplianceBuilding::iddObjectType(), model) {}

  ComplianceBuilding::ComplianceBuilding(std::shared_ptr<detail::ComplianceBuilding_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ComplianceBuilding::iddObjectType() {
    return IddObjectType::Compliance_Building;
  }

  double ComplianceBuilding::buildingRotationforAppendixG() const {
    return getImpl<detail::ComplianceBuilding_Impl>()->buildingRotationforAppendixG();
  }

  bool ComplianceBuilding::isBuildingRotationforAppendixGDefaulted() const {
    return getImpl<detail::ComplianceBuilding_Impl>()->isBuildingRotationforAppendixGDefaulted();
  }

  bool ComplianceBuilding::setBuildingRotationforAppendixG(double buildingRotationforAppendixG) {
    return getImpl<detail::ComplianceBuilding_Impl>()->setBuildingRotationforAppendixG(buildingRotationforAppendixG);
  }

  void ComplianceBuilding::resetBuildingRotationforAppendixG() {
    getImpl<detail::ComplianceBuilding_Impl>()->resetBuildingRotationforAppendixG();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double ComplianceBuilding_Impl::buildingRotationforAppendixG() const {
      const auto value = getDouble(openstudio::Compliance_BuildingFields::BuildingRotationforAppendixG, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ComplianceBuilding_Impl::isBuildingRotationforAppendixGDefaulted() const {
      return !getDouble(openstudio::Compliance_BuildingFields::BuildingRotationforAppendixG, false);
    }

    bool ComplianceBuilding_Impl::setBuildingRotationforAppendixG(double buildingRotationforAppendixG) {
      const bool result = setDouble(openstudio::Compliance_BuildingFields::BuildingRotationforAppendixG, buildingRotationforAppendixG);
      OS_ASSERT(result);
      return result;
    }

    void ComplianceBuilding_Impl::resetBuildingRotationforAppendixG() {
      OS_ASSERT(setString(openstudio::Compliance_BuildingFields::BuildingRotationforAppendixG, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
