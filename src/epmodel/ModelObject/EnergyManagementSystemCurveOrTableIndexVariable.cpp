/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemCurveOrTableIndexVariable.hpp"
#include "EnergyManagementSystemCurveOrTableIndexVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  EnergyManagementSystemCurveOrTableIndexVariable::EnergyManagementSystemCurveOrTableIndexVariable(const Model& model)
    : ModelObject(EnergyManagementSystemCurveOrTableIndexVariable::iddObjectType(), model) {}

  EnergyManagementSystemCurveOrTableIndexVariable::EnergyManagementSystemCurveOrTableIndexVariable(
    std::shared_ptr<detail::EnergyManagementSystemCurveOrTableIndexVariable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnergyManagementSystemCurveOrTableIndexVariable::iddObjectType() {
    return IddObjectType::EnergyManagementSystem_CurveOrTableIndexVariable;
  }

}  // namespace epmodel
}  // namespace openstudio
