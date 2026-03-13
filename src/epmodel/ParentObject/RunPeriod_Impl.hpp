/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIOD_IMPL_HPP
#define EPMODEL_RUNPERIOD_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RunPeriod_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RunPeriod_Impl() override = default;

      int getBeginMonth() const;
      bool setBeginMonth(int month);

      int getBeginDayOfMonth() const;
      bool setBeginDayOfMonth(int day);

      int getEndMonth() const;
      bool setEndMonth(int month);

      int getEndDayOfMonth() const;
      bool setEndDayOfMonth(int day);

      bool getUseWeatherFileHolidays() const;
      bool setUseWeatherFileHolidays(bool use);

      bool getUseWeatherFileDaylightSavings() const;
      bool setUseWeatherFileDaylightSavings(bool use);

      bool getApplyWeekendHolidayRule() const;
      bool setApplyWeekendHolidayRule(bool apply);

      bool getUseWeatherFileRainInd() const;
      bool setUseWeatherFileRainInd(bool rainInd);

      bool getUseWeatherFileSnowInd() const;
      bool setUseWeatherFileSnowInd(bool snowInd);

      int getNumTimePeriodRepeats() const;
      bool setNumTimePeriodRepeats(int numRepeats);

      void ensureNoLeapDays();

      bool isAnnual() const;
      bool isPartialYear() const;
      bool isRepeated() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
