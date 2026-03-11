/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPERIODWEATHERFILEDAYS_IMPL_HPP
#define EPMODEL_SIZINGPERIODWEATHERFILEDAYS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SizingPeriodWeatherFileDays_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SizingPeriodWeatherFileDays_Impl() override = default;

  int beginMonth() const;
  bool setBeginMonth(int beginMonth);

  int beginDayofMonth() const;
  bool setBeginDayofMonth(int beginDayofMonth);

  int endMonth() const;
  bool setEndMonth(int endMonth);

  int endDayofMonth() const;
  bool setEndDayofMonth(int endDayofMonth);

  std::string dayofWeekforStartDay() const;
  bool setDayofWeekforStartDay(const std::string& dayofWeekforStartDay);
  bool isDayofWeekforStartDayDefaulted() const;
  void resetDayofWeekforStartDay();

  bool useWeatherFileDaylightSavingPeriod() const;
  bool setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod);
  bool isUseWeatherFileDaylightSavingPeriodDefaulted() const;
  void resetUseWeatherFileDaylightSavingPeriod();

  bool useWeatherFileRainandSnowIndicators() const;
  bool setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators);
  bool isUseWeatherFileRainandSnowIndicatorsDefaulted() const;
  void resetUseWeatherFileRainandSnowIndicators();

  std::vector<std::string> dayofWeekforStartDayValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
