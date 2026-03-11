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
  int getBeginDayOfMonth() const;
  int getEndMonth() const;
  int getEndDayOfMonth() const;
  bool getUseWeatherFileHolidays() const;
  bool getUseWeatherFileDaylightSavings() const;
  bool getApplyWeekendHolidayRule() const;
  bool getUseWeatherFileRainInd() const;
  bool getUseWeatherFileSnowInd() const;
  int getNumTimePeriodRepeats() const;

  bool setBeginMonth(int month);
  bool setBeginDayOfMonth(int day);
  bool setEndMonth(int month);
  bool setEndDayOfMonth(int day);
  bool setUseWeatherFileHolidays(bool use);
  bool setUseWeatherFileDaylightSavings(bool use);
  bool setApplyWeekendHolidayRule(bool apply);
  bool setUseWeatherFileRainInd(bool rainInd);
  bool setUseWeatherFileSnowInd(bool snowInd);
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
