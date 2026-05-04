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

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model naming for controlVariableValues plus existing schedule presence helpers.
  // - Field Mapping: controlVariable delegates to E+ SetpointManager:Scheduled Control Variable.
  // - Implemented Parity: `schedule`, `setSchedule`, and `setControlVariableAndSchedule` expose the canonical
  //   schedule relationship surface; setpoint-node attachment is inherited from SetpointManager::addToNode.
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

  explicit SetpointManagerScheduled(std::shared_ptr<detail::SetpointManagerScheduled_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
