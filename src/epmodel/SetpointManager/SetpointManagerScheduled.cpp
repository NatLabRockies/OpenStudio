/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerScheduled.hpp"
#include "SetpointManager/SetpointManagerScheduled_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/SetpointManager_Scheduled_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

namespace {

boost::optional<openstudio::epmodel::Schedule> resolveScheduleTarget(const openstudio::epmodel::ModelObject& object, unsigned fieldIndex) {
  if (auto schedule = object.getModelObjectTarget<openstudio::epmodel::Schedule>(fieldIndex)) {
    return schedule;
  }

  if (auto scheduleName = object.getString(fieldIndex)) {
    if (!scheduleName->empty()) {
      for (const auto& candidate : object.model().getObjectsByName(*scheduleName, true, true)) {
        if (auto schedule = candidate.optionalCast<openstudio::epmodel::Schedule>()) {
          return schedule;
        }
      }
    }
  }

  return boost::none;
}

}  // namespace

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
  return static_cast<bool>(resolveScheduleTarget(*this, openstudio::SetpointManager_ScheduledFields::ScheduleName));
}

boost::optional<ModelObject> SetpointManagerScheduled::scheduleAsModelObject() const {
  if (auto schedule = resolveScheduleTarget(*this, openstudio::SetpointManager_ScheduledFields::ScheduleName)) {
    return schedule->cast<ModelObject>();
  }
  return boost::none;
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

boost::optional<openstudio::epmodel::Node> SetpointManagerScheduled_Impl::setpointNode() const {
  return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
    openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName);
}

std::string SetpointManagerScheduled_Impl::controlVariable() const {
  if (auto value = getString(openstudio::SetpointManager_ScheduledFields::ControlVariable, true)) {
    return *value;
  }
  return "";
}

bool SetpointManagerScheduled_Impl::setControlVariable(const std::string& value) {
  return setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, value);
}

bool SetpointManagerScheduled_Impl::setSetpointNode(const openstudio::epmodel::Node& node) {
  return getObject<ModelObject>().setPointer(openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName, node.handle());
}

void SetpointManagerScheduled_Impl::doCanonicalize(LoadContext& context) {
  SetpointManager_Impl::doCanonicalize(context);
  canonicalizeSetpointNodeField(context, openstudio::SetpointManager_ScheduledFields::SetpointNodeorNodeListName);

  bool hasControlVariable = false;
  if (auto value = getString(openstudio::SetpointManager_ScheduledFields::ControlVariable, true)) {
    hasControlVariable = !value->empty();
  }

  if (!hasControlVariable) {
    OS_ASSERT(setString(openstudio::SetpointManager_ScheduledFields::ControlVariable, "Temperature"));
    detail::addLoadInfo(context, "Set default Control Variable to 'Temperature' for SetpointManager:Scheduled '"
                                   + getObject<ModelObject>().nameString() + "'.");
  }

  if (auto schedule = resolveScheduleTarget(getObject<ModelObject>(), openstudio::SetpointManager_ScheduledFields::ScheduleName)) {
    OS_ASSERT(setPointer(openstudio::SetpointManager_ScheduledFields::ScheduleName, schedule->handle(), false));
    return;
  }
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
