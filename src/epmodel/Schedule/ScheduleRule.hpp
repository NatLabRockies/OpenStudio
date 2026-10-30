/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULE_HPP
#define EPMODEL_SCHEDULERULE_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/time/Date.hpp>

#include <memory>
#include <utility>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ScheduleDay;
  class ScheduleRuleset;

  using ScheduleRuleDateRange = std::pair<openstudio::Date, openstudio::Date>;

  namespace detail {
    class ScheduleRule_Impl;
    class ScheduleRuleset_Impl;
  }

  /**
   * A priority-ordered EnergyPlus Schedule:Week:Rule override for a Schedule:Year:Rules.
   * Date ranges and weekday flags map directly to the EnergyPlus object.
   */
  class EPMODEL_API ScheduleRule : public ParentObject
  {
   public:
    explicit ScheduleRule(ScheduleRuleset& scheduleRuleset);
    ScheduleRule(ScheduleRuleset& scheduleRuleset, const ScheduleDay& daySchedule);

    virtual ~ScheduleRule() override = default;
    ScheduleRule(const ScheduleRule& other) = default;
    ScheduleRule(ScheduleRule&& other) = default;
    ScheduleRule& operator=(const ScheduleRule&) = default;
    ScheduleRule& operator=(ScheduleRule&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> validDateSpecificationTypeValues();

    ScheduleRuleset scheduleRuleset() const;
    int rulePriorityOrder() const;
    bool setRulePriorityOrder(unsigned priorityOrder);
    int ruleIndex() const;
    bool setRuleIndex(unsigned index);

    ScheduleDay daySchedule() const;
    bool setDaySchedule(const ScheduleDay& daySchedule);

    /// Returns an endpoint only when the rule has exactly one date range.
    boost::optional<openstudio::Date> startDate() const;
    /// Returns an endpoint only when the rule has exactly one date range.
    boost::optional<openstudio::Date> endDate() const;
    std::vector<openstudio::Date> specificDates() const;
    std::string dateSpecificationType() const;

    bool applySunday() const;
    bool setApplySunday(bool applySunday);
    void setApplySundayNoFail(bool applySunday);
    bool applyMonday() const;
    bool setApplyMonday(bool applyMonday);
    void setApplyMondayNoFail(bool applyMonday);
    bool applyTuesday() const;
    bool setApplyTuesday(bool applyTuesday);
    void setApplyTuesdayNoFail(bool applyTuesday);
    bool applyWednesday() const;
    bool setApplyWednesday(bool applyWednesday);
    void setApplyWednesdayNoFail(bool applyWednesday);
    bool applyThursday() const;
    bool setApplyThursday(bool applyThursday);
    void setApplyThursdayNoFail(bool applyThursday);
    bool applyFriday() const;
    bool setApplyFriday(bool applyFriday);
    void setApplyFridayNoFail(bool applyFriday);
    bool applySaturday() const;
    bool setApplySaturday(bool applySaturday);
    void setApplySaturdayNoFail(bool applySaturday);

    /// Returns the EnergyPlus date ranges; a single-day range also represents a specific date.
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

   protected:
    using ImplType = detail::ScheduleRule_Impl;

    friend class Model;
    friend class ScheduleRuleset;
    friend class detail::ScheduleRuleset_Impl;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleRule(std::shared_ptr<detail::ScheduleRule_Impl> impl);
    bool setRulePriorityOrderDirect(unsigned priorityOrder);
  };

  using OptionalScheduleRule = boost::optional<ScheduleRule>;
  using ScheduleRuleVector = std::vector<ScheduleRule>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SCHEDULERULE_HPP