/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAY_IMPL_HPP
#define EPMODEL_SCHEDULEDAY_IMPL_HPP

#include "ScheduleBase/ScheduleBase_Impl.hpp"

#include <utilities/data/TimeSeries.hpp>
#include <utilities/time/Time.hpp>

#include <boost/optional.hpp>

#include <vector>

namespace openstudio {

namespace epmodel {
  namespace detail {

    class EPMODEL_API ScheduleDay_Impl : public ScheduleBase_Impl
    {
     public:
      using ScheduleBase_Impl::ScheduleBase_Impl;
      virtual ~ScheduleDay_Impl() override = default;

      std::string interpolatetoTimestep() const;
      bool setInterpolatetoTimestep(const std::string& interpolatetoTimestep);
      bool isInterpolatetoTimestepDefaulted() const;
      void resetInterpolatetoTimestep();

      bool addValue(const openstudio::Time& untilTime, double value);
      boost::optional<double> removeValue(const openstudio::Time& time);
      void clearValues();
      std::vector<openstudio::Time> times() const;
      std::vector<double> values() const override;
      double getValue(const openstudio::Time& time) const;

      openstudio::TimeSeries timeSeries() const;

      void ensureNoLeapDays() override;

     protected:
      unsigned scheduleTypeLimitsFieldIndex() const override;
      bool candidateIsCompatibleWithCurrentUse(const ScheduleTypeLimits& candidate) const override;
      bool okToResetScheduleTypeLimits() const override;

     private:
      void clearCachedVariables();

      mutable boost::optional<std::vector<openstudio::Time>> m_cachedTimes;
      mutable boost::optional<std::vector<double>> m_cachedValues;
      mutable boost::optional<openstudio::TimeSeries> m_cachedTimeSeries;

      REGISTER_LOGGER("openstudio.epmodel.ScheduleDay");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
