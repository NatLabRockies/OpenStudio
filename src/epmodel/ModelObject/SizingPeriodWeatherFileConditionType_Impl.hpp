/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPERIODWEATHERFILECONDITIONTYPE_IMPL_HPP
#define EPMODEL_SIZINGPERIODWEATHERFILECONDITIONTYPE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SizingPeriodWeatherFileConditionType_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SizingPeriodWeatherFileConditionType_Impl() override = default;

      std::vector<std::string> periodSelectionValues() const;
      std::vector<std::string> dayofWeekforStartDayValues() const;

      // PeriodSelection
      std::string periodSelection() const;
      bool setPeriodSelection(const std::string& periodSelection);

      // DayofWeekforStartDay
      std::string dayofWeekforStartDay() const;
      bool setDayofWeekforStartDay(const std::string& dayofWeekforStartDay);
      bool isDayofWeekforStartDayDefaulted() const;
      void resetDayofWeekforStartDay();

      // UseWeatherFileDaylightSavingPeriod
      bool useWeatherFileDaylightSavingPeriod() const;
      bool setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod);
      bool isUseWeatherFileDaylightSavingPeriodDefaulted() const;
      void resetUseWeatherFileDaylightSavingPeriod();

      // UseWeatherFileRainandSnowIndicators
      bool useWeatherFileRainandSnowIndicators() const;
      bool setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators);
      bool isUseWeatherFileRainandSnowIndicatorsDefaulted() const;
      void resetUseWeatherFileRainandSnowIndicators();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
