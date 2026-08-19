/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSCHEDULEDDUALSETPOINT_HPP
#define EPMODEL_SETPOINTMANAGERSCHEDULEDDUALSETPOINT_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class SetpointManagerScheduledDualSetpoint_Impl;
  }

  /** \brief Applies separate scheduled heating and cooling setpoints.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerscheduleddualsetpoint,SetpointManager:Scheduled:DualSetpoint}
   *
   * \par Important behavior
   * The high and low schedule setters require schedules with the appropriate continuous temperature schedule type.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerScheduledDualSetpoint</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerScheduledDualSetpoint : public SetpointManager
  {
   public:
    explicit SetpointManagerScheduledDualSetpoint(const Model& model);

    virtual ~SetpointManagerScheduledDualSetpoint() override = default;
    SetpointManagerScheduledDualSetpoint(const SetpointManagerScheduledDualSetpoint& other) = default;
    SetpointManagerScheduledDualSetpoint(SetpointManagerScheduledDualSetpoint&& other) = default;
    SetpointManagerScheduledDualSetpoint& operator=(const SetpointManagerScheduledDualSetpoint&) = default;
    SetpointManagerScheduledDualSetpoint& operator=(SetpointManagerScheduledDualSetpoint&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();


    boost::optional<Schedule> highSetpointSchedule() const;
    bool setHighSetpointSchedule(Schedule& schedule);
    void resetHighSetpointSchedule();

    boost::optional<Schedule> lowSetpointSchedule() const;
    bool setLowSetpointSchedule(Schedule& schedule);
    void resetLowSetpointSchedule();

   protected:
    using ImplType = detail::SetpointManagerScheduledDualSetpoint_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerScheduledDualSetpoint(std::shared_ptr<detail::SetpointManagerScheduledDualSetpoint_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
