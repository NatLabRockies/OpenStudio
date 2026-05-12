/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAY_HPP
#define EPMODEL_SCHEDULEDAY_HPP

#include "EPModelAPI.hpp"
#include "ScheduleBase/ScheduleBase.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {

class Time;
class TimeSeries;

namespace epmodel {

  class ScheduleTypeLimits;

  namespace detail {
    class ScheduleDay_Impl;
  }

  class EPMODEL_API ScheduleDay : public ScheduleBase
  {
   public:
    explicit ScheduleDay(const Model& model);

    virtual ~ScheduleDay() override = default;
    ScheduleDay(const ScheduleDay& other) = default;
    ScheduleDay(ScheduleDay&& other) = default;
    ScheduleDay& operator=(const ScheduleDay&) = default;
    ScheduleDay& operator=(ScheduleDay&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> interpolatetoTimestepValues();

    std::string interpolatetoTimestep() const;
    bool setInterpolatetoTimestep(const std::string& interpolatetoTimestep);
    bool isInterpolatetoTimestepDefaulted() const;
    void resetInterpolatetoTimestep();

    /** Returns false if time is less than or equal to 0 days or greater than 1 day. Replaces existing value for same time. */
    bool addValue(const openstudio::Time& untilTime, double value);

    /** Remove a value added by addValue at the exact time.  Returns the removed
     *  value if there was one. */
    boost::optional<double> removeValue(const openstudio::Time& time);

    /** Clear all values from this schedule. */
    void clearValues();

    /** Returns a vector of times marking the end of each value interval, in order. */
    std::vector<openstudio::Time> times() const;

    /** Returns a vector of values in the same order as times(). */
    std::vector<double> values() const;

    /** Returns the value in effect at the given time (0 if time is out of range or no values). */
    double getValue(const openstudio::Time& time) const;

    /// Returns the timeseries corresponding to simulation timestep and chosen interpolation method.
    openstudio::TimeSeries timeSeries() const;

   protected:
    using ImplType = detail::ScheduleDay_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleDay(std::shared_ptr<detail::ScheduleDay_Impl> impl);
  };

  using OptionalScheduleDay = boost::optional<ScheduleDay>;
  using ScheduleDayVector = std::vector<ScheduleDay>;

}  // namespace epmodel
}  // namespace openstudio

#endif
