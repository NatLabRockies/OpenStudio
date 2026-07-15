/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemGlobalVariable.hpp"
#include "EnergyManagementSystemGlobalVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/EnergyManagementSystem_GlobalVariable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  EnergyManagementSystemGlobalVariable::EnergyManagementSystemGlobalVariable(const Model& model, const std::string& variableName)
    : ModelObject(EnergyManagementSystemGlobalVariable::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::EnergyManagementSystemGlobalVariable_Impl>());

    auto groups = extensibleGroups();
    if (groups.empty()) {
      pushExtensibleGroup();
      groups = extensibleGroups();
    }
    OS_ASSERT(!groups.empty());
    auto variableGroup = groups.front();

    bool ok = variableGroup.setString(openstudio::EnergyManagementSystem_GlobalVariableExtensibleFields::ErlVariableName, variableName);
    const auto assignedName = variableGroup.getString(openstudio::EnergyManagementSystem_GlobalVariableExtensibleFields::ErlVariableName);
    if ((!ok) || (!assignedName) || (*assignedName != variableName)) {
      remove();
      throw std::runtime_error("Unable to set EnergyManagementSystemGlobalVariable Erl Variable Name to '" + variableName + "'.");
    }
  }

  EnergyManagementSystemGlobalVariable::EnergyManagementSystemGlobalVariable(std::shared_ptr<detail::EnergyManagementSystemGlobalVariable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnergyManagementSystemGlobalVariable::iddObjectType() {
    return IddObjectType::EnergyManagementSystem_GlobalVariable;
  }

}  // namespace epmodel
}  // namespace openstudio
