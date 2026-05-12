/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULESET_IMPL_HPP
#define EPMODEL_SCHEDULERULESET_IMPL_HPP

#include "EPModelAPI.hpp"
#include "Schedule/ScheduleYear_Impl.hpp"
#include "ScheduleBase/ScheduleDay.hpp"

#include <utilities/time/Date.hpp>

#include <boost/optional.hpp>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ScheduleRuleset_Impl : public ScheduleYear_Impl
    {
     public:
      using ScheduleYear_Impl::ScheduleYear_Impl;
      virtual ~ScheduleRuleset_Impl() override = default;

      // Per-rule data stored in memory (not persisted in IDF fields).
      // Rules are compiled to Schedule:Year extensible groups + Schedule:Week:Daily objects on every mutation.
      struct RuleData
      {
        boost::optional<ScheduleDay> daySchedule;
        bool applySunday{false};
        bool applyMonday{false};
        bool applyTuesday{false};
        bool applyWednesday{false};
        bool applyThursday{false};
        bool applyFriday{false};
        bool applySaturday{false};
        openstudio::Date startDate{openstudio::MonthOfYear::Jan, 1};
        openstudio::Date endDate{openstudio::MonthOfYear::Dec, 31};
      };

      // In-memory schedule state. Set by ScheduleRuleset constructors; empty for plain ScheduleYear wrappers.
      boost::optional<ScheduleDay> m_defaultDaySchedule;
      boost::optional<ScheduleDay> m_summerDesignDaySchedule;
      boost::optional<ScheduleDay> m_winterDesignDaySchedule;
      boost::optional<ScheduleDay> m_holidaySchedule;
      boost::optional<ScheduleDay> m_customDay1Schedule;
      boost::optional<ScheduleDay> m_customDay2Schedule;

      // Rules in priority order: index 0 = highest priority.
      std::vector<RuleData> m_rules;

      /** Rebuilds Schedule:Year extensible groups + owned Schedule:Week:Daily objects from m_rules. */
      void rebuildScheduleYear();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
