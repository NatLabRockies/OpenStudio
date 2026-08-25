/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSCHEDULED_HPP
#define EPMODEL_SETPOINTMANAGERSCHEDULED_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Schedule;

  namespace detail {
    class SetpointManagerScheduled_Impl;
  }

  /** \brief Applies a scheduled setpoint at a target node.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerscheduled,SetpointManager:Scheduled}
   *
   * \par Important behavior
   * The schedule setter uses the schedule type expected by the selected control
   * variable; use <code>setControlVariableAndSchedule()</code> when changing both
   * together.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerScheduled</code>.
   *
   * - <b>Changed:</b> OpenStudio Model constructors require a schedule, and
   *   one overload also accepts the control variable. The EPModel constructor
   *   accepts only the model; assign the schedule after construction.
   * - <b>Added:</b> <code>isControlVariableDefaulted()</code>,
   *   <code>resetControlVariable()</code>, and
   *   <code>scheduleAsModelObject()</code>.
   *
   * \par Known limitations
   * The EPModel constructor creates the manager without a schedule; set one with
   * <code>setSchedule</code> or <code>setControlVariableAndSchedule</code> after construction.
   */
  class EPMODEL_API SetpointManagerScheduled : public SetpointManager
  {
   public:
    explicit SetpointManagerScheduled(const Model& model);

    virtual ~SetpointManagerScheduled() override = default;
    SetpointManagerScheduled(const SetpointManagerScheduled& other) = default;
    SetpointManagerScheduled(SetpointManagerScheduled&& other) = default;
    SetpointManagerScheduled& operator=(const SetpointManagerScheduled&) = default;
    SetpointManagerScheduled& operator=(SetpointManagerScheduled&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlVariableValues();

    bool isControlVariableDefaulted() const;
    void resetControlVariable();

    Schedule schedule() const;
    bool hasSchedule() const;
    bool setSchedule(Schedule& schedule);
    bool setControlVariableAndSchedule(const std::string& controlVariable, Schedule& schedule);

    boost::optional<ModelObject> scheduleAsModelObject() const;

   protected:
    using ImplType = detail::SetpointManagerScheduled_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerScheduled(std::shared_ptr<detail::SetpointManagerScheduled_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
