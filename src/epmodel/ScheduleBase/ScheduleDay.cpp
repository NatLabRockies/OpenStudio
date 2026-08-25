/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ScheduleDay.hpp"
#include "ScheduleDay_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/Timestep.hpp"
#include "ModelObject/Timestep_Impl.hpp"
#include "ResourceObject/ScheduleTypeLimits.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/core/String.hpp>
#include <utilities/data/TimeSeries.hpp>
#include <utilities/data/Vector.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Schedule_Day_Interval_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/time/Time.hpp>

#include <cmath>
#include <set>

namespace openstudio {
namespace epmodel {

  ScheduleDay::ScheduleDay(const Model& model) : ScheduleBase(ScheduleDay::iddObjectType(), model) {}

  ScheduleDay::ScheduleDay(std::shared_ptr<detail::ScheduleDay_Impl> impl) : ScheduleBase(std::move(impl)) {}

  IddObjectType ScheduleDay::iddObjectType() {
    return IddObjectType::Schedule_Day_Interval;
  }

  std::vector<std::string> ScheduleDay::interpolatetoTimestepValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep);
  }

  std::string ScheduleDay::interpolatetoTimestep() const {
    return getImpl<detail::ScheduleDay_Impl>()->interpolatetoTimestep();
  }

  bool ScheduleDay::isInterpolatetoTimestepDefaulted() const {
    return getImpl<detail::ScheduleDay_Impl>()->isInterpolatetoTimestepDefaulted();
  }

  bool ScheduleDay::setInterpolatetoTimestep(const std::string& interpolatetoTimestep) {
    return getImpl<detail::ScheduleDay_Impl>()->setInterpolatetoTimestep(interpolatetoTimestep);
  }

  void ScheduleDay::resetInterpolatetoTimestep() {
    getImpl<detail::ScheduleDay_Impl>()->resetInterpolatetoTimestep();
  }

  bool ScheduleDay::addValue(const openstudio::Time& untilTime, double value) {
    return getImpl<detail::ScheduleDay_Impl>()->addValue(untilTime, value);
  }

  boost::optional<double> ScheduleDay::removeValue(const openstudio::Time& time) {
    return getImpl<detail::ScheduleDay_Impl>()->removeValue(time);
  }

  void ScheduleDay::clearValues() {
    getImpl<detail::ScheduleDay_Impl>()->clearValues();
  }

  std::vector<openstudio::Time> ScheduleDay::times() const {
    return getImpl<detail::ScheduleDay_Impl>()->times();
  }

  std::vector<double> ScheduleDay::values() const {
    return getImpl<detail::ScheduleDay_Impl>()->values();
  }

  double ScheduleDay::getValue(const openstudio::Time& time) const {
    return getImpl<detail::ScheduleDay_Impl>()->getValue(time);
  }

  openstudio::TimeSeries ScheduleDay::timeSeries() const {
    return getImpl<detail::ScheduleDay_Impl>()->timeSeries();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ScheduleDay_Impl::interpolatetoTimestep() const {
      const auto value = getString(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ScheduleDay_Impl::isInterpolatetoTimestepDefaulted() const {
      return isEmpty(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep);
    }

    bool ScheduleDay_Impl::setInterpolatetoTimestep(const std::string& interpolatetoTimestep) {
      m_cachedTimeSeries.reset();
      return setString(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep, interpolatetoTimestep);
    }

    void ScheduleDay_Impl::resetInterpolatetoTimestep() {
      m_cachedTimeSeries.reset();
      const bool result = setString(openstudio::Schedule_Day_IntervalFields::InterpolatetoTimestep, "");
      OS_ASSERT(result);
    }

    unsigned ScheduleDay_Impl::scheduleTypeLimitsFieldIndex() const {
      return openstudio::Schedule_Day_IntervalFields::ScheduleTypeLimitsName;
    }

    void ScheduleDay_Impl::clearCachedVariables() {
      m_cachedTimes.reset();
      m_cachedValues.reset();
      m_cachedTimeSeries.reset();
    }

    std::vector<openstudio::Time> ScheduleDay_Impl::times() const {
      if (!m_cachedTimes) {
        std::vector<openstudio::Time> result;
        for (const IdfExtensibleGroup& group : extensibleGroups()) {
          const auto timeStr = group.getString(openstudio::Schedule_Day_IntervalExtensibleFields::Time, true);
          if (!timeStr) {
            continue;
          }
          try {
            result.push_back(openstudio::Time::fromUntilString(*timeStr));
          } catch (...) {
            LOG(Error, "Could not parse time '" << *timeStr << "' in " << briefDescription());
          }
        }
        m_cachedTimes = std::move(result);
      }
      return *m_cachedTimes;
    }

    std::vector<double> ScheduleDay_Impl::values() const {
      if (!m_cachedValues) {
        std::vector<double> result;
        for (const IdfExtensibleGroup& group : extensibleGroups()) {
          const auto value = group.getDouble(openstudio::Schedule_Day_IntervalExtensibleFields::ValueUntilTime, true);
          if (value) {
            result.push_back(*value);
          } else {
            LOG(Error, "Could not read value " << group.groupIndex() << " in " << briefDescription());
          }
        }
        m_cachedValues = std::move(result);
      }
      return *m_cachedValues;
    }

    bool ScheduleDay_Impl::addValue(const openstudio::Time& untilTime, double value) {
      if (untilTime.totalMinutes() <= 0.5 || untilTime.totalDays() > 1.0) {
        return false;
      }

      // Check validity, cannot be NaN, Inf, etc
      if (std::isinf(value)) {
        LOG(Warn, "Cannot setDouble to Infinity for " << this->briefDescription());
        return false;
      } else if (std::isnan(value)) {
        LOG(Warn, "Cannot setDouble to a NaN for " << this->briefDescription());
        return false;
      }

      std::set<openstudio::Time> timeSet;
      for (const openstudio::Time& t : this->times()) {
        timeSet.insert(t);
      }

      auto [it, inserted] = timeSet.insert(untilTime);
      const auto index = static_cast<unsigned>(std::distance(timeSet.begin(), it));

      bool result;
      if (inserted) {
        // New time: insert extensible group at the sorted position.
        const IdfExtensibleGroup group = insertExtensibleGroup(index, {untilTime.toUntilString(false), toString(value)});
        OS_ASSERT(!group.empty());
        result = !group.empty();
      } else {
        // Existing time: overwrite value only.
        IdfExtensibleGroup group = getExtensibleGroup(index);
        result = group.setDouble(openstudio::Schedule_Day_IntervalExtensibleFields::ValueUntilTime, value);
      }

      clearCachedVariables();
      return result;
    }

    boost::optional<double> ScheduleDay_Impl::removeValue(const openstudio::Time& time) {
      const std::vector<openstudio::Time> existingTimes = this->times();
      boost::optional<unsigned> timeIndex;
      for (unsigned i = 0; i < existingTimes.size(); ++i) {
        if (existingTimes[i] == time) {
          timeIndex = i;
          break;
        }
      }
      if (!timeIndex) {
        return boost::none;
      }

      const std::vector<double> existingValues = this->values();
      OS_ASSERT(existingValues.size() == existingTimes.size());

      const double removedValue = existingValues[*timeIndex];
      clearValues();
      for (unsigned i = 0; i < existingTimes.size(); ++i) {
        if (i != *timeIndex) {
          addValue(existingTimes[i], existingValues[i]);
        }
      }
      return removedValue;
    }

    void ScheduleDay_Impl::clearValues() {
      clearExtensibleGroups();
      addValue(openstudio::Time(1, 0), 0.0);
    }

    double ScheduleDay_Impl::getValue(const openstudio::Time& time) const {
      if (time.totalMinutes() < 0.0 || time.totalDays() > 1.0) {
        return 0.0;
      }

      const TimeSeries ts = this->timeSeries();
      const DateTimeVector dateTimes = ts.dateTimes();
      const Vector values = ts.values();

      const unsigned N = dateTimes.size();
      if (N == 0) {
        return 0.0;
      }

      Vector x(N + 2);
      Vector y(N + 2);

      x[0] = 0.0;
      const std::string interpolation = this->interpolatetoTimestep();
      if (istringEqual("Linear", interpolation)) {
        y[0] = 0.0;
      } else {
        y[0] = values[0];
      }

      for (unsigned i = 0; i < N; ++i) {
        openstudio::Time t = dateTimes[i].time();
        if (t.totalDays() == 0.0) {  // 00:00:00 from the next day
          t = openstudio::Time(0, 24, 0);
        }
        x[i + 1] = t.totalDays();
        y[i + 1] = values[i];
      }

      x[N + 1] = 1.0;
      y[N + 1] = values[N - 1];

      return interp(x, y, time.totalDays(), HoldNextInterp, NoneExtrap);
    }

    openstudio::TimeSeries ScheduleDay_Impl::timeSeries() const {
      if (!m_cachedTimeSeries) {

        const auto timestep = model().getOptionalUniqueModelObject<Timestep>();
        const int numberOfTimestepsPerHour = timestep ? timestep->numberOfTimestepsPerHour() : 6;

        Date startDate(Date(MonthOfYear(MonthOfYear::Jan), 1));  // this is arbitrary
        int minutes = 60 / numberOfTimestepsPerHour;
        DateTime startDateTime(startDate, Time(0, 0, 0));

        DateTimeVector tsDateTimes;
        for (size_t hour = 0; hour < 24; ++hour) {
          for (size_t minute = minutes; minute <= 60; minute += minutes) {
            if (minute == 60) {
              openstudio::Time t(0, hour + 1, 0);
              tsDateTimes.push_back(startDateTime + t);
            } else {
              openstudio::Time t(0, hour, minute);
              tsDateTimes.push_back(startDateTime + t);
            }
          }
        }

        std::vector<double> values = this->values();          // these are already sorted
        std::vector<openstudio::Time> times = this->times();  // these are already sorted

        const unsigned N = times.size();
        OS_ASSERT(values.size() == N);

        TimeSeries result;
        if (N == 0) {
          m_cachedTimeSeries = result;
          return *m_cachedTimeSeries;
        }

        Vector x(N + 2);
        Vector y(N + 2);

        x[0] = -0.000001;
        y[0] = 0.0;

        for (unsigned i = 0; i < N; ++i) {
          x[i + 1] = times[i].totalSeconds();
          y[i + 1] = values[i];
        }

        x[N + 1] = 86400.000001;
        y[N + 1] = 0.0;

        std::string interpolatetoTimestep = this->interpolatetoTimestep();
        Vector tsValues(tsDateTimes.size());
        for (unsigned j = 0; j < tsDateTimes.size(); ++j) {
          openstudio::Time t = tsDateTimes[j].time();
          if (t.totalDays() == 0.0) {  // this is 00:00:00 from the next day
            t = openstudio::Time(0, 24, 0);
          }

          if (istringEqual("No", interpolatetoTimestep)) {
            tsValues[j] = interp(x, y, t.totalSeconds(), HoldNextInterp, NoneExtrap);
          } else if (istringEqual("Average", interpolatetoTimestep)) {
            double minutes = 60.0 / numberOfTimestepsPerHour;
            double ti = minutes * 60.0;  // total seconds of the timestep interval
            tsValues[j] = interp(x, y, t.totalSeconds(), AverageInterp, NoneExtrap, ti);
          } else if (istringEqual("Linear", interpolatetoTimestep)) {
            tsValues[j] = interp(x, y, t.totalSeconds(), LinearInterp, NoneExtrap);
          }
        }

        result = TimeSeries(tsDateTimes, tsValues, "");
        m_cachedTimeSeries = result;
      }

      return *m_cachedTimeSeries;
    }

    void ScheduleDay_Impl::ensureNoLeapDays() {
      // Schedule:Day:Interval has no date fields — nothing to do.
    }

    bool ScheduleDay_Impl::candidateIsCompatibleWithCurrentUse(const ScheduleTypeLimits& /*candidate*/) const {
      // TODO: implement compatibility check
      return true;
    }

    bool ScheduleDay_Impl::okToResetScheduleTypeLimits() const {
      for (const ModelObject& user : getObject<ScheduleDay>().getModelObjectSources<ModelObject>()) {
        // schedules using this ScheduleDay need to also have no limits
        if (user.optionalCast<Schedule>() && user.cast<Schedule>().scheduleTypeLimits()) {
          return false;
        }
        // if (user.optionalCast<ScheduleRule>()) {
        //   // test indirect use through ScheduleRule
        //   if (user.cast<ScheduleRule>().scheduleRuleset().scheduleTypeLimits()) {
        //     return false;
        //   }
        // } else
        if (!user.optionalCast<ScheduleBase>()) {
          // other non-schedule users impose limits
          return false;
        }
      }
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
