/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemConstructionIndexVariable.hpp"
#include "EnergyManagementSystemConstructionIndexVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

EnergyManagementSystemConstructionIndexVariable::EnergyManagementSystemConstructionIndexVariable(const Model& model)
  : ModelObject(EnergyManagementSystemConstructionIndexVariable::iddObjectType(), model) {}

EnergyManagementSystemConstructionIndexVariable::EnergyManagementSystemConstructionIndexVariable(
  std::shared_ptr<detail::EnergyManagementSystemConstructionIndexVariable_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType EnergyManagementSystemConstructionIndexVariable::iddObjectType() {
  return IddObjectType::EnergyManagementSystem_ConstructionIndexVariable;
}

}  // namespace epmodel
}  // namespace openstudio
