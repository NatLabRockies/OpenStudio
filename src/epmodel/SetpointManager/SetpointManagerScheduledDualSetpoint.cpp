/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerScheduledDualSetpoint.hpp"
#include "SetpointManager/SetpointManagerScheduledDualSetpoint_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_Scheduled_DualSetpoint_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerScheduledDualSetpoint::SetpointManagerScheduledDualSetpoint(const Model& model)
  : SetpointManager(SetpointManagerScheduledDualSetpoint::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerScheduledDualSetpoint_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerScheduledDualSetpoint::SetpointManagerScheduledDualSetpoint(
  std::shared_ptr<detail::SetpointManagerScheduledDualSetpoint_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerScheduledDualSetpoint::iddObjectType() {
  return IddObjectType::SetpointManager_Scheduled_DualSetpoint;
}

std::vector<std::string> SetpointManagerScheduledDualSetpoint::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool SetpointManagerScheduledDualSetpoint_Impl::isAllowedOnPlantLoop() const {
  return true;
}

unsigned SetpointManagerScheduledDualSetpoint_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_Scheduled_DualSetpointFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerScheduledDualSetpoint_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable;
}

void SetpointManagerScheduledDualSetpoint_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable, true)) {
    if (!value->empty()) {
      return;
    }
  }

  OS_ASSERT(setString(openstudio::SetpointManager_Scheduled_DualSetpointFields::ControlVariable, "Temperature"));
  detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Scheduled:DualSetpoint '"
                                 + getObject<ModelObject>().nameString() + "'.");
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
