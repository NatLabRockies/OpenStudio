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
      auto schedule = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AvailabilityManagerScheduledOff_Impl::setSchedule(openstudio::epmodel::Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, "AvailabilityManagerScheduledOff",
                                           "Availability Manager Scheduled Off", schedule);
    }

    void AvailabilityManagerScheduledOff_Impl::doCanonicalize(LoadContext& context) {
      auto manager = getObject<openstudio::epmodel::AvailabilityManagerScheduledOff>();
      if (auto schedule = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
            openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName)) {
        OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, schedule->handle(), false));
        return;
      }

      if (auto scheduleName = getString(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName)) {
        if (!scheduleName->empty()) {
          for (const auto& candidate : model().getObjectsByName(*scheduleName, true)) {
            if (auto schedule = candidate.optionalCast<openstudio::epmodel::Schedule>()) {
              OS_ASSERT(setPointer(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, schedule->handle(), false));
              return;
            }
          }
        }
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
