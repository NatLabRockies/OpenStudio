/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULERULESET_HPP
#define EPMODEL_SCHEDULERULESET_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ScheduleRuleset_Impl;
}

class EPMODEL_API ScheduleRuleset : public ModelObject
{
 public:
  explicit ScheduleRuleset(const Model& model);

  virtual ~ScheduleRuleset() override = default;
  ScheduleRuleset(const ScheduleRuleset& other) = default;
  ScheduleRuleset(ScheduleRuleset&& other) = default;
  ScheduleRuleset& operator=(const ScheduleRuleset&) = default;
  ScheduleRuleset& operator=(ScheduleRuleset&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model counterpart naming (`ScheduleRuleset`) for EnergyPlus Schedule:Year.
  // - Field Mapping: relationship fields (Schedule Type Limits Name target + extensible WeekSchedule/Start/End groups) are excluded
  //   from scalar scaffold APIs.
  // - ForwardTranslator evidence: ForwardTranslateScheduleRuleset.cpp translates model::ScheduleRuleset to Schedule:Year and
  //   emits week/special-day data via Schedule:Week:Daily objects and Schedule:Year extensible groups.
  // - Field Mapping: Name remains available via inherited ModelObject scalar accessors.
  // - TODO(parity): Add non-scalar week/rule/day relationship APIs incrementally without changing preserved public signatures.

 protected:
  using ImplType = detail::ScheduleRuleset_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ScheduleRuleset(std::shared_ptr<detail::ScheduleRuleset_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
