/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERSCHEDULEDOFF_HPP
#define EPMODEL_AVAILABILITYMANAGERSCHEDULEDOFF_HPP

#include "EPModelAPI.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;

namespace detail {
class AvailabilityManagerScheduledOff_Impl;
}

class EPMODEL_API AvailabilityManagerScheduledOff : public AvailabilityManager
{
 public:
  explicit AvailabilityManagerScheduledOff(const Model& model);

  virtual ~AvailabilityManagerScheduledOff() override = default;
  AvailabilityManagerScheduledOff(const AvailabilityManagerScheduledOff& other) = default;
  AvailabilityManagerScheduledOff(AvailabilityManagerScheduledOff&& other) = default;
  AvailabilityManagerScheduledOff& operator=(const AvailabilityManagerScheduledOff&) = default;
  AvailabilityManagerScheduledOff& operator=(AvailabilityManagerScheduledOff&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves model-counterpart class naming for AvailabilityManagerScheduledOff.
  // - Field Mapping: EnergyPlus AvailabilityManager:ScheduledOff exposes only Schedule Name beyond Name.
  // - Implemented Parity: `schedule()` and `setSchedule(...)` now expose the shared schedule relationship surface.
  // - ForwardTranslator evidence: model::ForwardTranslateAvailabilityManagerScheduledOff maps only Schedule Name.
  Schedule schedule() const;
  bool setSchedule(Schedule& schedule);

 protected:
  using ImplType = detail::AvailabilityManagerScheduledOff_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerScheduledOff(std::shared_ptr<detail::AvailabilityManagerScheduledOff_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
