/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AvailabilityManager/AvailabilityManagerScheduledOff.hpp"
#include "AvailabilityManager/AvailabilityManagerScheduledOff_Impl.hpp"

#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/AvailabilityManager_ScheduledOff_FieldEnums.hxx>

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

AvailabilityManagerScheduledOff::AvailabilityManagerScheduledOff(const Model& model)
  : AvailabilityManager(AvailabilityManagerScheduledOff::iddObjectType(), model) {
  auto impl = getImpl<detail::AvailabilityManagerScheduledOff_Impl>();
  OS_ASSERT(impl);
  ScheduleConstant schedule(model);
  OS_ASSERT(schedule.setValue(0.0));
  OS_ASSERT(setSchedule(schedule));
}

AvailabilityManagerScheduledOff::AvailabilityManagerScheduledOff(std::shared_ptr<detail::AvailabilityManagerScheduledOff_Impl> impl)
  : AvailabilityManager(std::move(impl)) {}

IddObjectType AvailabilityManagerScheduledOff::iddObjectType() {
  return IddObjectType::AvailabilityManager_ScheduledOff;
}

Schedule AvailabilityManagerScheduledOff::schedule() const {
  return getImpl<detail::AvailabilityManagerScheduledOff_Impl>()->schedule();
}

bool AvailabilityManagerScheduledOff::setSchedule(Schedule& schedule) {
  return getImpl<detail::AvailabilityManagerScheduledOff_Impl>()->setSchedule(schedule);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

openstudio::epmodel::Schedule AvailabilityManagerScheduledOff_Impl::schedule() const {
  auto schedule = resolveScheduleTarget(getObject<ModelObject>(), openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName);
  OS_ASSERT(schedule);
  return *schedule;
}

bool AvailabilityManagerScheduledOff_Impl::setSchedule(openstudio::epmodel::Schedule& schedule) {
  if (schedule.model() != model()) {
    return false;
  }
  return setPointer(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, schedule.handle(), false);
}

void AvailabilityManagerScheduledOff_Impl::doCanonicalize(LoadContext& context) {
  auto manager = getObject<openstudio::epmodel::AvailabilityManagerScheduledOff>();
  if (auto schedule = resolveScheduleTarget(getObject<ModelObject>(), openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName)) {
    OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, schedule->handle(), false));
    return;
  }

  ScheduleConstant schedule(model());
  OS_ASSERT(schedule.setValue(0.0));
  if (!manager.nameString().empty()) {
    schedule.setName(manager.nameString() + " Schedule");
  }

  OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, schedule.handle(), false));
  detail::addLoadInfo(context, "Created default schedule '" + schedule.nameString() + "' for AvailabilityManager:ScheduledOff '"
                                 + manager.nameString() + "'.");
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
