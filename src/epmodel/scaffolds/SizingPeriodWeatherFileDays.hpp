/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPERIODWEATHERFILEDAYS_HPP
#define EPMODEL_SIZINGPERIODWEATHERFILEDAYS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SizingPeriodWeatherFileDays_Impl;
  }

  class EPMODEL_API SizingPeriodWeatherFileDays : public ModelObject
  {
   public:
    explicit SizingPeriodWeatherFileDays(const Model& model);

    virtual ~SizingPeriodWeatherFileDays() override = default;
    SizingPeriodWeatherFileDays(const SizingPeriodWeatherFileDays& other) = default;
    SizingPeriodWeatherFileDays(SizingPeriodWeatherFileDays&& other) = default;
    SizingPeriodWeatherFileDays& operator=(const SizingPeriodWeatherFileDays&) = default;
    SizingPeriodWeatherFileDays& operator=(SizingPeriodWeatherFileDays&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> dayofWeekforStartDayValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to E+ SizingPeriod:WeatherFileDays scalar fields.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - TODO(parity): Add any non-scalar/relationship API in a dedicated follow-up pass.
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

   protected:
    using ImplType = detail::SizingPeriodWeatherFileDays_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SizingPeriodWeatherFileDays(std::shared_ptr<detail::SizingPeriodWeatherFileDays_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
