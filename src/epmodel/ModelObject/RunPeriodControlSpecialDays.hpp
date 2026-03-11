/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLSPECIALDAYS_HPP
#define EPMODEL_RUNPERIODCONTROLSPECIALDAYS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RunPeriodControlSpecialDays_Impl;
}

class EPMODEL_API RunPeriodControlSpecialDays : public ModelObject
{
 public:
  explicit RunPeriodControlSpecialDays(const Model& model);

  virtual ~RunPeriodControlSpecialDays() override = default;
  RunPeriodControlSpecialDays(const RunPeriodControlSpecialDays& other) = default;
  RunPeriodControlSpecialDays(RunPeriodControlSpecialDays&& other) = default;
  RunPeriodControlSpecialDays& operator=(const RunPeriodControlSpecialDays&) = default;
  RunPeriodControlSpecialDays& operator=(RunPeriodControlSpecialDays&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> specialDayTypeValues();
  static std::vector<std::string> validSpecialDayTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::RunPeriodControlSpecialDays scalar accessor names where they map directly.
  // - Field Mapping: startDate/duration/specialDayType map directly to EnergyPlus RunPeriodControl:SpecialDays fields.
  // - ForwardTranslator evidence: ForwardTranslateRunPeriodControlSpecialDays.cpp forwards Start Date/Duration/Special Day Type directly
  //   (with only a "5th" -> "Last" text transform for Start Date).
  // - TODO(parity): Add model-style date conversion overloads/parsing behavior after scalar saturation.
  std::string startDate() const;
  unsigned duration() const;
  std::string specialDayType() const;

  bool setStartDate(const std::string& startDate);
  bool setDuration(unsigned duration);
  bool setSpecialDayType(const std::string& specialDayType);

 protected:
  using ImplType = detail::RunPeriodControlSpecialDays_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RunPeriodControlSpecialDays(std::shared_ptr<detail::RunPeriodControlSpecialDays_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
