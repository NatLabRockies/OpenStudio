/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class SetpointManagerOutdoorAirReset_Impl;
  }

  class EPMODEL_API SetpointManagerOutdoorAirReset : public SetpointManager
  {
   public:
    explicit SetpointManagerOutdoorAirReset(const Model& model);

    virtual ~SetpointManagerOutdoorAirReset() override = default;
    SetpointManagerOutdoorAirReset(const SetpointManagerOutdoorAirReset& other) = default;
    SetpointManagerOutdoorAirReset(SetpointManagerOutdoorAirReset&& other) = default;
    SetpointManagerOutdoorAirReset& operator=(const SetpointManagerOutdoorAirReset&) = default;
    SetpointManagerOutdoorAirReset& operator=(SetpointManagerOutdoorAirReset&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - Status: Near Parity. Scalar reset rules, the optional rule-selection schedule, and inherited node attachment are aligned.
    // - Canonical Counterpart: openstudio::model::SetpointManagerOutdoorAirReset.
    // - Implemented Parity: Scalar accessors and the optional schedule preserve canonical public signatures. The schedule setter
    //   uses the shared continuous, nonnegative schedule contract.
    // - Field/Storage Mapping: Scalars, Schedule Name, and the setpoint node map directly to EnergyPlus
    //   SetpointManager:OutdoorAirReset fields.
    // - Canonicalization: Construction/load establish scalar defaults and node linkage. A unique persisted schedule name is
    //   reattached during load repair; blank, missing, or ambiguous names are not invented or guessed. Ordinary APIs assume
    //   canonical resolved relationships.
    // - Evidence: `src/model/SetpointManagerOutdoorAirReset.hpp`, `src/model/ScheduleTypeRegistry.cpp`,
    //   `resources/energyplus/ProposedEnergy+.idd`, and `src/epmodel/test/SetpointManagerOutdoorAirReset_GTest.cpp`.
    // - Remaining Parity Work: Object-level clone behavior and broader language/workflow evidence remain demand-driven.

    bool isControlVariableDefaulted() const;
    void resetControlVariable();

    double setpointatOutdoorLowTemperature() const;
    bool setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature);

    double outdoorLowTemperature() const;
    bool setOutdoorLowTemperature(double outdoorLowTemperature);

    double setpointatOutdoorHighTemperature() const;
    bool setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature);

    double outdoorHighTemperature() const;
    bool setOutdoorHighTemperature(double outdoorHighTemperature);

    boost::optional<Schedule> schedule() const;
    bool setSchedule(Schedule& schedule);
    void resetSchedule();

    boost::optional<double> setpointatOutdoorLowTemperature2() const;
    bool setSetpointatOutdoorLowTemperature2(double setpointatOutdoorLowTemperature2);
    void resetSetpointatOutdoorLowTemperature2();

    boost::optional<double> outdoorLowTemperature2() const;
    bool setOutdoorLowTemperature2(double outdoorLowTemperature2);
    void resetOutdoorLowTemperature2();

    boost::optional<double> setpointatOutdoorHighTemperature2() const;
    bool setSetpointatOutdoorHighTemperature2(double setpointatOutdoorHighTemperature2);
    void resetSetpointatOutdoorHighTemperature2();

    boost::optional<double> outdoorHighTemperature2() const;
    bool setOutdoorHighTemperature2(double outdoorHighTemperature2);
    void resetOutdoorHighTemperature2();

   protected:
    using ImplType = detail::SetpointManagerOutdoorAirReset_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerOutdoorAirReset(std::shared_ptr<detail::SetpointManagerOutdoorAirReset_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
