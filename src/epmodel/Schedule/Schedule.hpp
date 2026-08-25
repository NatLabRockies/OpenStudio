/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULE_HPP
#define EPMODEL_SCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "ScheduleBase/ScheduleBase.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {
    class Schedule_Impl;
  }

  /** \brief Base class for EnergyPlus-backed schedules.
   *
   * \par EnergyPlus object
   * This class has no single EnergyPlus object. It is the base for concrete
   * schedule-family objects such as \epobject{group-schedules.html#schedulecompact,Schedule:Compact},
   * \epobject{group-schedules.html#scheduleconstant,Schedule:Constant}, and \epobject{group-schedules.html#schedulefile,Schedule:File}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::Schedule</code>. No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API Schedule : public ScheduleBase
  {
   public:
    virtual ~Schedule() override = default;
    Schedule(const Schedule& other) = default;
    Schedule(Schedule&& other) = default;
    Schedule& operator=(const Schedule&) = default;
    Schedule& operator=(Schedule&&) = default;

   protected:
    using ImplType = detail::Schedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Schedule(std::shared_ptr<detail::Schedule_Impl> impl);
    Schedule(IddObjectType type, const Model& model);
  };

  using OptionalSchedule = boost::optional<Schedule>;
  using ScheduleVector = std::vector<Schedule>;

}  // namespace epmodel
}  // namespace openstudio

#endif
