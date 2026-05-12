/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ScheduleWeek.hpp"
#include "ResourceObject/ScheduleWeek_Impl.hpp"
#include "ScheduleBase/ScheduleDay.hpp"
#include "ScheduleBase/ScheduleDay_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Schedule_Week_Daily_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ScheduleWeek::ScheduleWeek(const Model& model) : ResourceObject(ScheduleWeek::iddObjectType(), model) {}

  ScheduleWeek::ScheduleWeek(std::shared_ptr<detail::ScheduleWeek_Impl> impl) : ResourceObject(std::move(impl)) {}

  IddObjectType ScheduleWeek::iddObjectType() {
    return IddObjectType::Schedule_Week_Daily;
  }

  boost::optional<ScheduleDay> ScheduleWeek::sundaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->sundaySchedule();
  }
  bool ScheduleWeek::setSundaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setSundaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::mondaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->mondaySchedule();
  }
  bool ScheduleWeek::setMondaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setMondaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::tuesdaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->tuesdaySchedule();
  }
  bool ScheduleWeek::setTuesdaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setTuesdaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::wednesdaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->wednesdaySchedule();
  }
  bool ScheduleWeek::setWednesdaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setWednesdaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::thursdaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->thursdaySchedule();
  }
  bool ScheduleWeek::setThursdaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setThursdaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::fridaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->fridaySchedule();
  }
  bool ScheduleWeek::setFridaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setFridaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::saturdaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->saturdaySchedule();
  }
  bool ScheduleWeek::setSaturdaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setSaturdaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::holidaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->holidaySchedule();
  }
  bool ScheduleWeek::setHolidaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setHolidaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::summerDesignDaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->summerDesignDaySchedule();
  }
  bool ScheduleWeek::setSummerDesignDaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setSummerDesignDaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::winterDesignDaySchedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->winterDesignDaySchedule();
  }
  bool ScheduleWeek::setWinterDesignDaySchedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setWinterDesignDaySchedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::customDay1Schedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->customDay1Schedule();
  }
  bool ScheduleWeek::setCustomDay1Schedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setCustomDay1Schedule(scheduleDay);
  }

  boost::optional<ScheduleDay> ScheduleWeek::customDay2Schedule() const {
    return getImpl<detail::ScheduleWeek_Impl>()->customDay2Schedule();
  }
  bool ScheduleWeek::setCustomDay2Schedule(const ScheduleDay& scheduleDay) {
    return getImpl<detail::ScheduleWeek_Impl>()->setCustomDay2Schedule(scheduleDay);
  }

  bool ScheduleWeek::setAllSchedules(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleWeek_Impl>()->setAllSchedules(schedule);
  }

  bool ScheduleWeek::setWeekdaySchedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleWeek_Impl>()->setWeekdaySchedule(schedule);
  }

  bool ScheduleWeek::setWeekendSchedule(const ScheduleDay& schedule) {
    return getImpl<detail::ScheduleWeek_Impl>()->setWeekendSchedule(schedule);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ScheduleDay> ScheduleWeek_Impl::sundaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::SundaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setSundaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::SundaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::mondaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::MondaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setMondaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::MondaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::tuesdaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::TuesdaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setTuesdaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::TuesdaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::wednesdaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::WednesdaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setWednesdaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::WednesdaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::thursdaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::ThursdaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setThursdaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::ThursdaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::fridaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::FridaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setFridaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::FridaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::saturdaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::SaturdaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setSaturdaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::SaturdaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::holidaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::HolidaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setHolidaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::HolidaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::summerDesignDaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::SummerDesignDaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setSummerDesignDaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::SummerDesignDaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::winterDesignDaySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::WinterDesignDaySchedule_DayName);
    }
    bool ScheduleWeek_Impl::setWinterDesignDaySchedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::WinterDesignDaySchedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::customDay1Schedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::CustomDay1Schedule_DayName);
    }
    bool ScheduleWeek_Impl::setCustomDay1Schedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::CustomDay1Schedule_DayName, scheduleDay.handle());
    }

    boost::optional<ScheduleDay> ScheduleWeek_Impl::customDay2Schedule() const {
      return getObject<ModelObject>().getModelObjectTarget<ScheduleDay>(Schedule_Week_DailyFields::CustomDay2Schedule_DayName);
    }
    bool ScheduleWeek_Impl::setCustomDay2Schedule(const ScheduleDay& scheduleDay) {
      return setPointer(Schedule_Week_DailyFields::CustomDay2Schedule_DayName, scheduleDay.handle());
    }

    bool ScheduleWeek_Impl::setAllSchedules(const ScheduleDay& schedule) {
      bool result = true;

      result = result && setSundaySchedule(schedule);
      result = result && setMondaySchedule(schedule);
      result = result && setTuesdaySchedule(schedule);
      result = result && setWednesdaySchedule(schedule);
      result = result && setThursdaySchedule(schedule);
      result = result && setFridaySchedule(schedule);
      result = result && setSaturdaySchedule(schedule);
      result = result && setHolidaySchedule(schedule);
      result = result && setSummerDesignDaySchedule(schedule);
      result = result && setWinterDesignDaySchedule(schedule);
      result = result && setCustomDay1Schedule(schedule);
      result = result && setCustomDay2Schedule(schedule);

      return result;
    }

    bool ScheduleWeek_Impl::setWeekdaySchedule(const ScheduleDay& schedule) {
      bool result = true;

      result = result && setMondaySchedule(schedule);
      result = result && setTuesdaySchedule(schedule);
      result = result && setWednesdaySchedule(schedule);
      result = result && setThursdaySchedule(schedule);
      result = result && setFridaySchedule(schedule);

      return result;
    }

    bool ScheduleWeek_Impl::setWeekendSchedule(const ScheduleDay& schedule) {
      bool result = true;

      result = result && setSundaySchedule(schedule);
      result = result && setSaturdaySchedule(schedule);

      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
