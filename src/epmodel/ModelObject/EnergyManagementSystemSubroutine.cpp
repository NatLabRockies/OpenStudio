/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "EnergyManagementSystemSubroutine.hpp"
#include "EnergyManagementSystemSubroutine_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  EnergyManagementSystemSubroutine::EnergyManagementSystemSubroutine(const Model& model)
    : ModelObject(EnergyManagementSystemSubroutine::iddObjectType(), model) {}

  EnergyManagementSystemSubroutine::EnergyManagementSystemSubroutine(std::shared_ptr<detail::EnergyManagementSystemSubroutine_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType EnergyManagementSystemSubroutine::iddObjectType() {
    return IddObjectType::EnergyManagementSystem_Subroutine;
  }

}  // namespace epmodel
}  // namespace openstudio
