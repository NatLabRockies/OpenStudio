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

  /** \brief Keeps a loop available according to an availability schedule.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerscheduledon,AvailabilityManager:ScheduledOn}
   *
   * \par Important behavior
   * A newly constructed manager creates a constant schedule with value 1.0.
   * <code>setSchedule()</code> enforces the EnergyPlus Availability schedule
   * type, and loading repairs a missing or unresolved schedule by reconnecting
   * a named schedule or creating a new constant-one schedule.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerScheduledOn</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
