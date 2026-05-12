/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULE_HPP
#define EPMODEL_SCHEDULERULE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/ScheduleRuleset.hpp"
#include "ScheduleBase/ScheduleDay.hpp"

#include <utilities/time/Date.hpp>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  /** ScheduleRule is a transient wrapper for a rule in a ScheduleRuleset.
   *  It is NOT a ModelObject and is NOT persisted independently in the EnergyPlus IDD.
   *  Rules are stored in-memory in ScheduleRuleset_Impl and compiled to Schedule:Year +
   *  Schedule:Week:Daily objects on each mutation.
   *
   *  Canonical Counterpart: openstudio::model::ScheduleRule.
   *  Documented Delta: No IDD backing; no iddObjectType(); not returned by model queries. */
  class EPMODEL_API ScheduleRule
  {
   public:
    /** Constructs a new rule for the given ruleset with a new empty day schedule.
     *  The rule is inserted at the highest priority (index 0). */
    explicit ScheduleRule(ScheduleRuleset& scheduleRuleset);

    /** Constructs a new rule using the given day schedule.
     *  The rule is inserted at the highest priority (index 0). */
    ScheduleRule(ScheduleRuleset& scheduleRuleset, const ScheduleDay& daySchedule);

    virtual ~ScheduleRule() = default;
    ScheduleRule(const ScheduleRule&) = default;
    ScheduleRule(ScheduleRule&&) = default;
    ScheduleRule& operator=(const ScheduleRule&) = default;
    ScheduleRule& operator=(ScheduleRule&&) = default;

    /** @name Getters */
    //@{

    ScheduleRuleset scheduleRuleset() const;

    /** Returns the priority index (0 = highest priority). */
    int ruleIndex() const;

    ScheduleDay daySchedule() const;

    bool applySunday() const;
    bool applyMonday() const;
    bool applyTuesday() const;
    bool applyWednesday() const;
    bool applyThursday() const;
    bool applyFriday() const;
    bool applySaturday() const;

    bool applyWeekdays() const;
    bool applyWeekends() const;
    bool applyAllDays() const;

    boost::optional<openstudio::Date> startDate() const;
    boost::optional<openstudio::Date> endDate() const;

    //@}
    /** @name Setters */
    //@{

    bool setApplySunday(bool v);
    bool setApplyMonday(bool v);
    bool setApplyTuesday(bool v);
    bool setApplyWednesday(bool v);
    bool setApplyThursday(bool v);
    bool setApplyFriday(bool v);
    bool setApplySaturday(bool v);

    bool setApplyWeekdays(bool v);
    bool setApplyWeekends(bool v);
    bool setApplyAllDays(bool v);

    bool setStartDate(const openstudio::Date& date);
    bool setEndDate(const openstudio::Date& date);

    //@}

   private:
    // Used by ScheduleRuleset::scheduleRules() to wrap an existing rule by index.
    friend class ScheduleRuleset;
    ScheduleRule(const ScheduleRuleset& ruleset, int ruleIndex);

    ScheduleRuleset m_ruleset;
    int m_ruleIndex;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
