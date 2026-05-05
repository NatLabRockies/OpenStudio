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

  namespace detail {
    class SetpointManagerScheduledDualSetpoint_Impl;
  }

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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model naming for controlVariableValues and inherited
    //   controlVariable()/setControlVariable() from SetpointManager.
    // - Field Mapping: controlVariable delegates to E+ SetpointManager:Scheduled:DualSetpoint Control Variable.
    // - Field Mapping: Relationship fields High Setpoint Schedule Name, Low Setpoint Schedule Name,
    //   and Setpoint Node or NodeList Name are intentionally excluded from scalar-only scaffolding.
    // - Field Mapping: isAllowedOnPlantLoop behavior is preserved via impl override for model parity.
    // - TODO(parity): Add schedule-object parity accessors for high/low setpoint schedules in a follow-up pass.

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
