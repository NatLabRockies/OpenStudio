/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACExhaustSystem.hpp"
#include "AirLoopHVACExhaustSystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

AirLoopHVACExhaustSystem::AirLoopHVACExhaustSystem(const Model& model)
  : ModelObject(AirLoopHVACExhaustSystem::iddObjectType(), model) {}

AirLoopHVACExhaustSystem::AirLoopHVACExhaustSystem(std::shared_ptr<detail::AirLoopHVACExhaustSystem_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirLoopHVACExhaustSystem::iddObjectType() {
  return IddObjectType::AirLoopHVAC_ExhaustSystem;
}

}  // namespace epmodel
}  // namespace openstudio
