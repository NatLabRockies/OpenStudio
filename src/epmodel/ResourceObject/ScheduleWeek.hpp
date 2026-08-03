/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEWEEK_HPP
#define EPMODEL_SCHEDULEWEEK_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class ScheduleDay;

  namespace detail {
    class ScheduleWeek_Impl;
  }

  class EPMODEL_API ScheduleWeek : public ResourceObject
  {
   public:
    explicit ScheduleWeek(const Model& model);

    virtual ~ScheduleWeek() override = default;
    ScheduleWeek(const ScheduleWeek& other) = default;
    ScheduleWeek(ScheduleWeek&& other) = default;
    ScheduleWeek& operator=(const ScheduleWeek&) = default;
    ScheduleWeek& operator=(ScheduleWeek&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - API: Preserves openstudio::model counterpart naming (`ScheduleWeek`).
    // - Canonical Counterpart: openstudio::model::ScheduleWeek.
    // - Implemented Parity: Day schedule relationship methods for all 12 day types.
    // - Field Mapping: Sunday..CustomDay2 schedule day links map to EnergyPlus Schedule:Week:Daily pointer fields.
    // - ForwardTranslator evidence: `ForwardTranslateScheduleWeek.cpp` maps counterpart schedule-day APIs to Schedule_Week_DailyFields::*Schedule_DayName fields.
    // - Field Mapping: Name remains available through inherited ModelObject scalar accessors.
    // - Remaining Parity Work: None for day schedule relationship APIs.

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

    /// Set schedules for all days.
    bool setAllSchedules(const ScheduleDay& schedule);

    /// Set schedules for all weekdays.
    bool setWeekdaySchedule(const ScheduleDay& schedule);

    /// Set schedules for all weekends.
    bool setWeekendSchedule(const ScheduleDay& schedule);

   protected:
    using ImplType = detail::ScheduleWeek_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleWeek(std::shared_ptr<detail::ScheduleWeek_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
