/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_HPP
#define EPMODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RunPeriodControlDaylightSavingTime_Impl;
}

class EPMODEL_API RunPeriodControlDaylightSavingTime : public ModelObject
{
 public:
  explicit RunPeriodControlDaylightSavingTime(const Model& model);

  virtual ~RunPeriodControlDaylightSavingTime() override = default;
  RunPeriodControlDaylightSavingTime(const RunPeriodControlDaylightSavingTime& other) = default;
  RunPeriodControlDaylightSavingTime(RunPeriodControlDaylightSavingTime&& other) = default;
  RunPeriodControlDaylightSavingTime& operator=(const RunPeriodControlDaylightSavingTime&) = default;
  RunPeriodControlDaylightSavingTime& operator=(RunPeriodControlDaylightSavingTime&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::RunPeriodControlDaylightSavingTime scalar accessor names where they map directly.
  // - Field Mapping: startDate()/setStartDate(string) map directly to RunPeriodControl:DaylightSavingTime Start Date.
  // - Field Mapping: endDate()/setEndDate(string) map directly to RunPeriodControl:DaylightSavingTime End Date.
  // - ForwardTranslator evidence: ForwardTranslateRunPeriodControlDaylightSavingTime.cpp reads raw OS StartDate/EndDate strings and
  //   forwards directly to EnergyPlus fields.
  // - TODO(parity): Add non-scalar date-conversion overloads/parsing APIs from model counterpart after scalar saturation.
  std::string startDate() const;
  std::string endDate() const;

  bool setStartDate(const std::string& startDate);
  bool setEndDate(const std::string& endDate);

 protected:
  using ImplType = detail::RunPeriodControlDaylightSavingTime_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RunPeriodControlDaylightSavingTime(std::shared_ptr<detail::RunPeriodControlDaylightSavingTime_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
