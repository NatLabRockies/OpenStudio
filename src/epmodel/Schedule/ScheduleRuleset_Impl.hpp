/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULESET_IMPL_HPP
#define EPMODEL_SCHEDULERULESET_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class ScheduleDay;
  class ScheduleRule;

  namespace detail {

    class EPMODEL_API ScheduleRuleset_Impl : public Schedule_Impl
    {
     public:
      using Schedule_Impl::Schedule_Impl;
      virtual ~ScheduleRuleset_Impl() override = default;

      std::vector<ScheduleRule> scheduleRules() const;
      bool setScheduleRulePriorityOrder(ScheduleRule& scheduleRule, unsigned priorityOrder);
      std::vector<int> getActiveRuleIndices(const openstudio::Date& startDate, const openstudio::Date& endDate) const;
      std::vector<ScheduleDay> getDaySchedules(const openstudio::Date& startDate, const openstudio::Date& endDate) const;

      ScheduleDay defaultDaySchedule() const;
      bool setDefaultDaySchedule(const ScheduleDay& schedule);

      ScheduleDay summerDesignDaySchedule() const;
      bool isSummerDesignDayScheduleDefaulted() const;
      bool setSummerDesignDaySchedule(const ScheduleDay& schedule);
      void resetSummerDesignDaySchedule();

      ScheduleDay winterDesignDaySchedule() const;
      bool isWinterDesignDayScheduleDefaulted() const;
      bool setWinterDesignDaySchedule(const ScheduleDay& schedule);
      void resetWinterDesignDaySchedule();

      ScheduleDay holidaySchedule() const;
      bool isHolidayScheduleDefaulted() const;
      bool setHolidaySchedule(const ScheduleDay& schedule);
      void resetHolidaySchedule();

      ScheduleDay customDay1Schedule() const;
      bool isCustomDay1ScheduleDefaulted() const;
      bool setCustomDay1Schedule(const ScheduleDay& schedule);
      void resetCustomDay1Schedule();

      ScheduleDay customDay2Schedule() const;
      bool isCustomDay2ScheduleDefaulted() const;
      bool setCustomDay2Schedule(const ScheduleDay& schedule);
      void resetCustomDay2Schedule();

     protected:
      unsigned scheduleTypeLimitsFieldIndex() const override;

     private:
      REGISTER_LOGGER("openstudio.epmodel.ScheduleRuleset");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SCHEDULERULESET_IMPL_HPP