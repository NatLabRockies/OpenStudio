/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/ScheduleCompact.hpp"
#include "../../model/ScheduleCompact_Impl.hpp"
#include "../../model/ScheduleInterval.hpp"
#include "../../model/ScheduleInterval_Impl.hpp"
#include "../../model/ScheduleFixedInterval.hpp"
#include "../../model/ScheduleFixedInterval_Impl.hpp"
#include "../../model/ScheduleVariableInterval.hpp"
#include "../../model/ScheduleVariableInterval_Impl.hpp"
#include "../../model/YearDescription.hpp"
#include "../../model/YearDescription_Impl.hpp"

#include "../../utilities/data/TimeSeries.hpp"

#include "../../utilities/idf/IdfExtensibleGroup.hpp"

#include <utilities/idd/Schedule_Compact_FieldEnums.hxx>
#include <utilities/idd/OS_Schedule_Compact_FieldEnums.hxx>
#include <utilities/idd/OS_Schedule_FixedInterval_FieldEnums.hxx>
#include <utilities/idd/OS_Schedule_VariableInterval_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

#include "../../utilities/time/Date.hpp"
#include "../../utilities/core/ASCIIStrings.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  OptionalModelObject ReverseTranslator::translateScheduleCompact(const WorkspaceObject& workspaceObject) {
    if (workspaceObject.iddObject().type() != IddObjectType::Schedule_Compact) {
      LOG(Error, "WorkspaceObject is not IddObjectType: Schedule:Compact");
      return boost::none;
    }

    std::vector<DateTime> dateTimes;
    std::vector<double> values;
    
    int day = 1; // temp
    boost::optional<Date> date;
    boost::optional<Time> time;
    for (IdfExtensibleGroup& eg : workspaceObject.extensibleGroups()) {
      for (unsigned i = 0; i < eg.numFields(); ++i) {
        if (boost::optional<std::string> s = eg.getString(i)) {
          std::string lower = openstudio::ascii_to_lower_copy(s.get());
          if (lower.find("through") != std::string::npos) {
            //date = lower;
            date = Date(MonthOfYear(1), day); // temp
            ++day; // temp
          } else if (lower.find("until") != std::string::npos) {
            //time = lower;
            //time = Time("24:00"); // temp
            time = Time(0, 0, 0, 0);
          }
        }
        if (date && time) {
          DateTime datetime(*date, *time);
          dateTimes.push_back(datetime);
          date = boost::none;
          time = boost::none;
        }        
        if (boost::optional<double> value = eg.getDouble(i)) {
          values.push_back(value.get());
        }
      }
    }    

    boost::optional<Time> intervalLength;
    intervalLength = Time(1, 0); // temp
    bool forAllDays = true; // temp

    if (intervalLength && forAllDays) {
      Date startDateNoYear = dateTimes[0].date();
      MonthOfYear monthOfYear = startDateNoYear.monthOfYear();
      int dayOfMonth = startDateNoYear.dayOfMonth();
      OS_ASSERT(dayOfMonth == 1);
      
      model::YearDescription yd = m_model.getUniqueModelObject<model::YearDescription>();
      Date startDate = yd.makeDate(monthOfYear, dayOfMonth);

      TimeSeries timeseries(startDate, *intervalLength, createVector(values), "");
      boost::optional<ScheduleInterval> scheduleInterval = ScheduleInterval::fromTimeSeries(timeseries, m_model);
      OS_ASSERT(scheduleInterval);
      boost::optional<ScheduleFixedInterval> scheduleFixedInterval = scheduleInterval->optionalCast<ScheduleFixedInterval>();
      OS_ASSERT(scheduleFixedInterval);

      OptionalWorkspaceObject target = workspaceObject.getTarget(Schedule_CompactFields::ScheduleTypeLimitsName);
      if (target) {
        OptionalModelObject scheduleTypeLimits = translateAndMapWorkspaceObject(*target);
        if (scheduleTypeLimits) {
          scheduleFixedInterval->setPointer(OS_Schedule_FixedIntervalFields::ScheduleTypeLimitsName, scheduleTypeLimits->handle());
        }
      }

      if (OptionalString os = workspaceObject.name()) {
        scheduleFixedInterval->setName(*os);
      }

      return scheduleFixedInterval.get();
    } else if (forAllDays) {
      TimeSeries timeseries(dateTimes, createVector(values), "");
      boost::optional<ScheduleInterval> scheduleInterval = ScheduleInterval::fromTimeSeries(timeseries, m_model);
      OS_ASSERT(scheduleInterval);
      boost::optional<ScheduleVariableInterval> scheduleVariableInterval = scheduleInterval->optionalCast<ScheduleVariableInterval>();
      OS_ASSERT(scheduleVariableInterval);

      OptionalWorkspaceObject target = workspaceObject.getTarget(Schedule_CompactFields::ScheduleTypeLimitsName);
      if (target) {
        OptionalModelObject scheduleTypeLimits = translateAndMapWorkspaceObject(*target);
        if (scheduleTypeLimits) {
          scheduleVariableInterval->setPointer(OS_Schedule_VariableIntervalFields::ScheduleTypeLimitsName, scheduleTypeLimits->handle());
        }
      }

      if (OptionalString os = workspaceObject.name()) {
        scheduleVariableInterval->setName(*os);
      }

      return scheduleVariableInterval.get();
    } else {
      ScheduleCompact scheduleCompact(m_model);

      OptionalWorkspaceObject target = workspaceObject.getTarget(Schedule_CompactFields::ScheduleTypeLimitsName);
      if (target) {
        OptionalModelObject scheduleTypeLimits = translateAndMapWorkspaceObject(*target);
        if (scheduleTypeLimits) {
          scheduleCompact.setPointer(OS_Schedule_CompactFields::ScheduleTypeLimitsName, scheduleTypeLimits->handle());
        }
      }

      if (OptionalString os = workspaceObject.name()) {
        scheduleCompact.setName(*os);
      }

      for (IdfExtensibleGroup& eg : workspaceObject.extensibleGroups()) {
        for (unsigned i = 0; i < eg.numFields(); ++i) {
          if (auto value = eg.getString(i)) {
            if (istringEqual(value.get(), "Interpolate:Average")) {
              eg.setString(i, "Interpolate:Yes");
            }
          }
        }
        scheduleCompact.pushExtensibleGroup(eg.fields());
      }

      return scheduleCompact;
    }
  }

}  // namespace energyplus

}  // namespace openstudio
