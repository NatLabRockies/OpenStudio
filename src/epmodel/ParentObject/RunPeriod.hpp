/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIOD_HPP
#define EPMODEL_RUNPERIOD_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RunPeriod_Impl;
  }

/** \brief Defines the dates and weather-file rules for a simulation run period.
 *
 * \par EnergyPlus object
 * \epobject{group-location-climate-weather-file-access.html#runperiod,RunPeriod}
 *
 * \par Important behavior
 * The begin/end dates, weather holidays, daylight-saving, rain/snow indicators, weekend-holiday rule, and repeat count are stored directly. The convenience predicates isAnnual(), isPartialYear(), and isRepeated() interpret those fields.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::RunPeriod</code>.
 *
 * \par Known limitations
 * The run period does not contain weather data; weather-file availability and weather properties come from the simulation environment.
 */
  class EPMODEL_API RunPeriod : public ParentObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~RunPeriod() override = default;
    RunPeriod(const RunPeriod& other) = default;
    RunPeriod(RunPeriod&& other) = default;
    RunPeriod& operator=(const RunPeriod&) = default;
    RunPeriod& operator=(RunPeriod&&) = default;

    static IddObjectType iddObjectType();


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

   protected:
    explicit RunPeriod(const Model& model);

    using ImplType = detail::RunPeriod_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RunPeriod(std::shared_ptr<detail::RunPeriod_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
