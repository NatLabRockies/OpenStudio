/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemProgram.hpp"
#include "EnergyManagementSystemProgram_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  EnergyManagementSystemProgram::EnergyManagementSystemProgram(const Model& model)
    : ModelObject(EnergyManagementSystemProgram::iddObjectType(), model) {}

  EnergyManagementSystemProgram::EnergyManagementSystemProgram(std::shared_ptr<detail::EnergyManagementSystemProgram_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnergyManagementSystemProgram::iddObjectType() {
    return IddObjectType::EnergyManagementSystem_Program;
  }

}  // namespace epmodel
}  // namespace openstudio
