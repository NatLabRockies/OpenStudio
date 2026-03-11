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

class EPMODEL_API RunPeriod : public ParentObject
{
 public:
  explicit RunPeriod(const Model& model);

  virtual ~RunPeriod() override = default;
  RunPeriod(const RunPeriod& other) = default;
  RunPeriod(RunPeriod&& other) = default;
  RunPeriod& operator=(const RunPeriod&) = default;
  RunPeriod& operator=(RunPeriod&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::RunPeriod scalar API names/signatures, including legacy get* naming.
  // - Field Mapping: begin/end date and weather-flag APIs map directly to EnergyPlus RunPeriod scalar fields.
  // - Field Mapping: get/setNumTimePeriodRepeats maps to RunPeriod BeginYear/EndYear because EnergyPlus RunPeriod
  //   has no Number of Times Runperiod to be Repeated field.
  // - ForwardTranslator evidence: BeginYear/EndYear and DayofWeekforStartDay are derived from model::YearDescription
  //   in ForwardTranslateRunPeriod.cpp and intentionally excluded from RunPeriod scalar accessors.
  // - ForwardTranslator evidence: UseWeatherFileHolidays/DaylightSavings are currently hard-set to "No" during
  //   translation; keep preserved RunPeriod APIs mapped to the underlying RunPeriod fields.
  // - TODO(parity): Align translator behavior with preserved RunPeriod weather-flag semantics in parity follow-up.
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

 protected:
  using ImplType = detail::RunPeriod_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RunPeriod(std::shared_ptr<detail::RunPeriod_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
