/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEWEEK_IMPL_HPP
#define EPMODEL_SCHEDULEWEEK_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ScheduleDay;

  namespace detail {

    class EPMODEL_API ScheduleWeek_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~ScheduleWeek_Impl() override = default;

      boost::optional<ScheduleDay> sundaySchedule() const;
      bool setSundaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> mondaySchedule() const;
      bool setMondaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> tuesdaySchedule() const;
      bool setTuesdaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> wednesdaySchedule() const;
      bool setWednesdaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> thursdaySchedule() const;
      bool setThursdaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> fridaySchedule() const;
      bool setFridaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> saturdaySchedule() const;
      bool setSaturdaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> holidaySchedule() const;
      bool setHolidaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> summerDesignDaySchedule() const;
      bool setSummerDesignDaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> winterDesignDaySchedule() const;
      bool setWinterDesignDaySchedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> customDay1Schedule() const;
      bool setCustomDay1Schedule(const ScheduleDay& scheduleDay);

      boost::optional<ScheduleDay> customDay2Schedule() const;
      bool setCustomDay2Schedule(const ScheduleDay& scheduleDay);

      bool setAllSchedules(const ScheduleDay& schedule);
      bool setWeekdaySchedule(const ScheduleDay& schedule);
      bool setWeekendSchedule(const ScheduleDay& schedule);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
