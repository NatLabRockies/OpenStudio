/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/AvailabilityManager_ScheduledOn_FieldEnums.hxx>

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

AvailabilityManagerScheduledOn::AvailabilityManagerScheduledOn(const Model& model)
  : AvailabilityManager(AvailabilityManagerScheduledOn::iddObjectType(), model) {
  auto impl = getImpl<detail::AvailabilityManagerScheduledOn_Impl>();
  OS_ASSERT(impl);
  ScheduleConstant schedule(model);
  OS_ASSERT(schedule.setValue(1.0));
  OS_ASSERT(setSchedule(schedule));
}

AvailabilityManagerScheduledOn::AvailabilityManagerScheduledOn(std::shared_ptr<detail::AvailabilityManagerScheduledOn_Impl> impl)
  : AvailabilityManager(std::move(impl)) {}

IddObjectType AvailabilityManagerScheduledOn::iddObjectType() {
  return IddObjectType::AvailabilityManager_ScheduledOn;
}

Schedule AvailabilityManagerScheduledOn::schedule() const {
  return getImpl<detail::AvailabilityManagerScheduledOn_Impl>()->schedule();
}

bool AvailabilityManagerScheduledOn::setSchedule(Schedule& schedule) {
  return getImpl<detail::AvailabilityManagerScheduledOn_Impl>()->setSchedule(schedule);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

openstudio::epmodel::Schedule AvailabilityManagerScheduledOn_Impl::schedule() const {
  auto schedule = resolveScheduleTarget(getObject<ModelObject>(), openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName);
  OS_ASSERT(schedule);
  return *schedule;
}

bool AvailabilityManagerScheduledOn_Impl::setSchedule(openstudio::epmodel::Schedule& schedule) {
  if (schedule.model() != model()) {
    return false;
  }
  return setPointer(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, schedule.handle(), false);
}

void AvailabilityManagerScheduledOn_Impl::doCanonicalize(LoadContext& context) {
  auto manager = getObject<openstudio::epmodel::AvailabilityManagerScheduledOn>();
  if (auto schedule = resolveScheduleTarget(getObject<ModelObject>(), openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName)) {
    OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, schedule->handle(), false));
    return;
  }

  ScheduleConstant schedule(model());
  OS_ASSERT(schedule.setValue(1.0));
  if (!manager.nameString().empty()) {
    schedule.setName(manager.nameString() + " Schedule");
  }

  OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, schedule.handle(), false));
  detail::addLoadInfo(context, "Created default schedule '" + schedule.nameString() + "' for AvailabilityManager:ScheduledOn '"
                                 + manager.nameString() + "'.");
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
