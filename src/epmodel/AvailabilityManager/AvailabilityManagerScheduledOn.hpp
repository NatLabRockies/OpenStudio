/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERSCHEDULEDON_HPP
#define EPMODEL_AVAILABILITYMANAGERSCHEDULEDON_HPP

#include "EPModelAPI.hpp"
#include "AvailabilityManager/AvailabilityManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class AvailabilityManagerScheduledOn_Impl;
  }

  class EPMODEL_API AvailabilityManagerScheduledOn : public AvailabilityManager
  {
   public:
    explicit AvailabilityManagerScheduledOn(const Model& model);

    virtual ~AvailabilityManagerScheduledOn() override = default;
    AvailabilityManagerScheduledOn(const AvailabilityManagerScheduledOn& other) = default;
    AvailabilityManagerScheduledOn(AvailabilityManagerScheduledOn&& other) = default;
    AvailabilityManagerScheduledOn& operator=(const AvailabilityManagerScheduledOn&) = default;
    AvailabilityManagerScheduledOn& operator=(AvailabilityManagerScheduledOn&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves model-counterpart class naming for AvailabilityManagerScheduledOn.
    // - Field Mapping: EnergyPlus AvailabilityManager:ScheduledOn exposes only Schedule Name beyond Name.
    // - Implemented Parity: `schedule()` and `setSchedule(...)` now expose the shared schedule relationship surface.
    // - ForwardTranslator evidence: model::ForwardTranslateAvailabilityManagerScheduledOn maps only Schedule Name.
    Schedule schedule() const;
    bool setSchedule(Schedule& schedule);

   protected:
    using ImplType = detail::AvailabilityManagerScheduledOn_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerScheduledOn(std::shared_ptr<detail::AvailabilityManagerScheduledOn_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
