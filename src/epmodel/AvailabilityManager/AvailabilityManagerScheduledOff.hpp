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

  /** \brief Keeps a loop unavailable according to an availability schedule.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerscheduledoff,AvailabilityManager:ScheduledOff}
   *
   * \par Important behavior
   * A newly constructed manager creates a constant schedule with value 0.0.
   * <code>setSchedule()</code> enforces the EnergyPlus Availability schedule
   * type, and loading repairs a missing or unresolved schedule by reconnecting
   * a named schedule or creating a new constant-zero schedule.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerScheduledOff</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
