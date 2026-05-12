/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULESET_HPP
#define EPMODEL_SCHEDULERULESET_HPP

#include "EPModelAPI.hpp"
#include "Schedule/ScheduleYear.hpp"
#include "ScheduleBase/ScheduleDay.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ScheduleRule;

  namespace detail {
    class ScheduleRuleset_Impl;
  }

  class EPMODEL_API ScheduleRuleset : public ScheduleYear
  {
   public:
    /** Constructs a ScheduleRuleset with a default day schedule (no values — value 0 everywhere). */
    explicit ScheduleRuleset(const Model& model);

    /** Constructs a ScheduleRuleset with a constant default day schedule set to the given value. */
    ScheduleRuleset(const Model& model, double value);

    virtual ~ScheduleRuleset() override = default;
    ScheduleRuleset(const ScheduleRuleset& other) = default;
    ScheduleRuleset(ScheduleRuleset&& other) = default;
    ScheduleRuleset& operator=(const ScheduleRuleset&) = default;
    ScheduleRuleset& operator=(ScheduleRuleset&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::ScheduleRuleset.
    // - Implemented Parity: defaultDaySchedule, design day schedules, scheduleRules(), ScheduleRule API.
    // - Documented Delta: No dispatch on load — a Schedule:Year loaded from IDF will not be returned as
    //   a ScheduleRuleset. In-memory rule data is not persisted; only the compiled Schedule:Year +
    //   Schedule:Week:Daily + Schedule:Day:Interval objects are written to IDF.
    // - Field/Storage Mapping: Backed by Schedule:Year. Rules stored in-memory in ScheduleRuleset_Impl;
    //   compiled to Schedule:Year extensible groups + Schedule:Week:Daily on every mutation.
    // - Remaining Parity Work: getActiveRuleIndices, getDaySchedules, setScheduleRuleIndex round-trip,
    //   specificDates on rules, load-time dispatch.

    /** @name Default and design day schedules */
    //@{

    ScheduleDay defaultDaySchedule() const;

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

    //@}
    /** @name Rules */
    //@{

    /** Returns the rules in order from highest priority (index 0) to lowest. */
    std::vector<ScheduleRule> scheduleRules() const;

    /** Sets the priority index of the given rule (0 = highest priority). Returns false if rule
     *  does not belong to this ScheduleRuleset or index is out of range. */
    bool setScheduleRuleIndex(ScheduleRule& rule, unsigned index);

    //@}

   protected:
    using ImplType = detail::ScheduleRuleset_Impl;

    friend class Model;
    friend class ScheduleRule;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleRuleset(std::shared_ptr<detail::ScheduleRuleset_Impl> impl);
  };

  using OptionalScheduleRuleset = boost::optional<ScheduleRuleset>;
  using ScheduleRulesetVector = std::vector<ScheduleRuleset>;

}  // namespace epmodel
}  // namespace openstudio

#endif
