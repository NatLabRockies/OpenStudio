/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGEHEATING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGEHEATING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneOneStageHeating_Impl;
  }

  class EPMODEL_API SetpointManagerSingleZoneOneStageHeating : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneOneStageHeating(const Model& model);

    virtual ~SetpointManagerSingleZoneOneStageHeating() override = default;
    SetpointManagerSingleZoneOneStageHeating(const SetpointManagerSingleZoneOneStageHeating& other) = default;
    SetpointManagerSingleZoneOneStageHeating(SetpointManagerSingleZoneOneStageHeating&& other) = default;
    SetpointManagerSingleZoneOneStageHeating& operator=(const SetpointManagerSingleZoneOneStageHeating&) = default;
    SetpointManagerSingleZoneOneStageHeating& operator=(SetpointManagerSingleZoneOneStageHeating&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: heatingStageOnSupplyAirSetpointTemperature and heatingStageOffSupplyAirSetpointTemperature
    //   map directly to E+ SetpointManager:SingleZone:OneStageHeating scalar fields.
    // - Field Mapping: controlVariable is preserved through inherited SetpointManager API and maps to
    //   fixed legacy semantics ("Temperature") because current E+ SetpointManager:SingleZone:OneStageHeating
    //   has no explicit Control Variable field.
    // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSingleZoneOneStageHeating.cpp maps these same
    //   scalar fields and treats Control Zone Name and Setpoint Node or NodeList Name as relationship mappings.
    // - Field Mapping: Relationship fields Control Zone Name and Setpoint Node or NodeList Name are intentionally
    //   excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for control-zone linkage in a follow-up pass.
    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double heatingStageOnSupplyAirSetpointTemperature() const;
    bool setHeatingStageOnSupplyAirSetpointTemperature(double heatingStageOnSupplyAirSetpointTemperature);

    double heatingStageOffSupplyAirSetpointTemperature() const;
    bool setHeatingStageOffSupplyAirSetpointTemperature(double heatingStageOffSupplyAirSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneOneStageHeating_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneOneStageHeating(std::shared_ptr<detail::SetpointManagerSingleZoneOneStageHeating_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
