/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerScheduled.hpp"
#include "SetpointManager/SetpointManagerScheduled_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_Scheduled_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SetpointManagerScheduled::SetpointManagerScheduled(const Model& model) : SetpointManager(SetpointManagerScheduled::iddObjectType(), model) {
  auto impl = getImpl<detail::SetpointManagerScheduled_Impl>();
  OS_ASSERT(impl);
  OS_ASSERT(setControlVariable("Temperature"));
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

SetpointManagerScheduled::SetpointManagerScheduled(std::shared_ptr<detail::SetpointManagerScheduled_Impl> impl)
  : SetpointManager(std::move(impl)) {}

IddObjectType SetpointManagerScheduled::iddObjectType() {
  return IddObjectType::SetpointManager_Scheduled;
}

std::vector<std::string> SetpointManagerScheduled::controlVariableValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SetpointManager_ScheduledFields::ControlVariable);
}

bool SetpointManagerScheduled::isControlVariableDefaulted() const {
  return getImpl<detail::SetpointManagerScheduled_Impl>()->isControlVariableDefaulted();
}

void SetpointManagerScheduled::resetControlVariable() {
  getImpl<detail::SetpointManagerScheduled_Impl>()->resetControlVariable();
}

bool SetpointManagerScheduled::hasSchedule() const {
  auto scheduleName = getString(openstudio::SetpointManager_ScheduledFields::ScheduleName);
  return scheduleName && !scheduleName->empty();
}

boost::optional<ModelObject> SetpointManagerScheduled::scheduleAsModelObject() const {
  return getModelObjectTarget<ModelObject>(openstudio::SetpointManager_ScheduledFields::ScheduleName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool SetpointManagerScheduled_Impl::isControlVariableDefaulted() const {
  return isEmpty(openstudio::SetpointManager_ScheduledFields::ControlVariable);
}

void SetpointManagerScheduled_Impl::resetControlVariable() {
  OS_ASSERT(setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, ""));
}

unsigned SetpointManagerScheduled_Impl::setpointNodeFieldIndex() const {
  return openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName;
}

unsigned SetpointManagerScheduled_Impl::controlVariableFieldIndex() const {
  return openstudio::SetpointManager_ScheduledFields::ControlVariable;
}

void SetpointManagerScheduled_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);

  if (auto value = getString(openstudio::SetpointManager_ScheduledFields::ControlVariable, true)) {
    if (!value->empty()) {
      return;
    }
  }

  OS_ASSERT(setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, "Temperature"));
  detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Scheduled '"
                                 + getObject<ModelObject>().nameString() + "'.");
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
