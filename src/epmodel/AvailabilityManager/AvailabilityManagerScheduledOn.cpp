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
  auto schedule =
    getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName);
  OS_ASSERT(schedule);
  return *schedule;
}

bool AvailabilityManagerScheduledOn_Impl::setSchedule(openstudio::epmodel::Schedule& schedule) {
  return ModelObject_Impl::setSchedule(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, "AvailabilityManagerScheduledOn",
                                       "Availability Manager Scheduled On", schedule);
}

void AvailabilityManagerScheduledOn_Impl::doCanonicalize(LoadContext& context) {
  auto manager = getObject<openstudio::epmodel::AvailabilityManagerScheduledOn>();
  if (auto schedule =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName)) {
    OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, schedule->handle(), false));
    return;
  }

  if (auto scheduleName = getString(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName)) {
    if (!scheduleName->empty()) {
      for (const auto& candidate : model().getObjectsByName(*scheduleName, true, true)) {
        if (auto schedule = candidate.optionalCast<openstudio::epmodel::Schedule>()) {
          OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, schedule->handle(), false));
          return;
        }
      }
    }
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
