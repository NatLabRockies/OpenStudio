/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULESET_HPP
#define EPMODEL_SCHEDULERULESET_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
class Date;

namespace epmodel {

  class Model;
  class ScheduleDay;
  class ScheduleRule;

  namespace detail {
    class ScheduleRuleset_Impl;
  }

  /** \brief Defines a default day schedule and special-day overrides for a year.
   *
   * \par EnergyPlus object
   * \epobject{group-schedules.html#schedule-year-rules,Schedule:Year:Rules}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ScheduleRuleset</code>. EPModel exposes the
  * default and special-day schedules, as well as ordered Schedule:Week:Rule
  * overrides.
   *
   * \par Known limitations
   * Special-day schedules are object-list references and are not cloned or
   * parented by this wrapper.
   */
  class EPMODEL_API ScheduleRuleset : public Schedule
  {
   public:
    explicit ScheduleRuleset(const Model& model);
    ScheduleRuleset(const Model& model, double value);

    virtual ~ScheduleRuleset() override = default;
    ScheduleRuleset(const ScheduleRuleset& other) = default;
    ScheduleRuleset(ScheduleRuleset&& other) = default;
    ScheduleRuleset& operator=(const ScheduleRuleset&) = default;
    ScheduleRuleset& operator=(ScheduleRuleset&&) = default;

    static IddObjectType iddObjectType();

    std::vector<ScheduleRule> scheduleRules() const;
    bool setScheduleRulePriorityOrder(ScheduleRule& scheduleRule, unsigned priorityOrder);
    bool setScheduleRuleIndex(ScheduleRule& scheduleRule, unsigned index);
    std::vector<int> getActiveRuleIndices(const openstudio::Date& startDate, const openstudio::Date& endDate) const;
    std::vector<ScheduleDay> getDaySchedules(const openstudio::Date& startDate, const openstudio::Date& endDate) const;

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

   protected:
    using ImplType = detail::ScheduleRuleset_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleRuleset(std::shared_ptr<detail::ScheduleRuleset_Impl> impl);
  };

  using OptionalScheduleRuleset = boost::optional<ScheduleRuleset>;
  using ScheduleRulesetVector = std::vector<ScheduleRuleset>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SCHEDULERULESET_HPP