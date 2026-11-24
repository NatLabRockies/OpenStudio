/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULE_IMPL_HPP
#define EPMODEL_SCHEDULERULE_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"
#include "Schedule/ScheduleRule.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ScheduleRule_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~ScheduleRule_Impl() override = default;

      ScheduleRuleset scheduleRuleset() const;
      int rulePriorityOrder() const;
      bool setRulePriorityOrder(unsigned priorityOrder);
      bool setRulePriorityOrderDirect(unsigned priorityOrder);
      std::string dateSpecificationType() const;
      boost::optional<openstudio::Date> startDate() const;
      boost::optional<openstudio::Date> endDate() const;
      std::vector<openstudio::Date> specificDates() const;

      ScheduleDay daySchedule() const;
      bool setDaySchedule(const ScheduleDay& daySchedule);

      bool applySunday() const;
      bool setApplySunday(bool applySunday);
      bool applyMonday() const;
      bool setApplyMonday(bool applyMonday);
      bool applyTuesday() const;
      bool setApplyTuesday(bool applyTuesday);
      bool applyWednesday() const;
      bool setApplyWednesday(bool applyWednesday);
      bool applyThursday() const;
      bool setApplyThursday(bool applyThursday);
      bool applyFriday() const;
      bool setApplyFriday(bool applyFriday);
      bool applySaturday() const;
      bool setApplySaturday(bool applySaturday);

      std::vector<ScheduleRuleDateRange> dateRanges() const;
      bool addDateRange(const openstudio::Date& startDate, const openstudio::Date& endDate);
      bool setStartDate(const openstudio::Date& startDate);
      bool setEndDate(const openstudio::Date& endDate);
      bool addSpecificDate(const openstudio::Date& date);
      void resetDateRanges();
      void ensureNoLeapDays();
      bool containsDate(const openstudio::Date& date) const;
      std::vector<bool> containsDates(const std::vector<openstudio::Date>& dates) const;
      bool applyAllDays() const;
      bool applyWeekdays() const;
      bool applyWeekends() const;
      bool setApplyAllDays(bool applyAllDays);
      bool setApplyWeekdays(bool applyWeekdays);
      bool setApplyWeekends(bool applyWeekends);

     private:
      bool applyDay(unsigned fieldIndex) const;
      bool setApplyDay(unsigned fieldIndex, bool apply);

      REGISTER_LOGGER("openstudio.epmodel.ScheduleRule");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SCHEDULERULE_IMPL_HPP