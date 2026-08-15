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
    // - Status: Near Parity. The high/low temperature schedules and inherited node attachment are aligned.
    // - Canonical Counterpart: openstudio::model::SetpointManagerScheduledDualSetpoint.
    // - Implemented Parity: The high- and low-setpoint schedule APIs preserve the canonical signatures and validate
    //   continuous Temperature schedules through the shared registry. Plant-loop eligibility remains aligned.
    // - Field/Storage Mapping: Both schedules and the setpoint node map directly to EnergyPlus
    //   SetpointManager:Scheduled:DualSetpoint object-list/node fields.
    // - Canonicalization: Construction and load normalize the control variable and setpoint-node relationship. Blank or
    //   unresolved schedule fields are not invented or guessed; ordinary APIs assume canonical resolved relationships.
    // - Evidence: `src/model/SetpointManagerScheduledDualSetpoint.hpp`, `src/model/ScheduleTypeRegistry.cpp`,
    //   `resources/energyplus/ProposedEnergy+.idd`, and `src/epmodel/test/SetpointManager_GTest.cpp`.
    // - Remaining Parity Work: Object-level clone behavior and broader language/workflow evidence remain demand-driven.

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
