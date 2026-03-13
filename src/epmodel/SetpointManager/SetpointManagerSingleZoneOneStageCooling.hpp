/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGECOOLING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEONESTAGECOOLING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneOneStageCooling_Impl;
  }

  class EPMODEL_API SetpointManagerSingleZoneOneStageCooling : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneOneStageCooling(const Model& model);

    virtual ~SetpointManagerSingleZoneOneStageCooling() override = default;
    SetpointManagerSingleZoneOneStageCooling(const SetpointManagerSingleZoneOneStageCooling& other) = default;
    SetpointManagerSingleZoneOneStageCooling(SetpointManagerSingleZoneOneStageCooling&& other) = default;
    SetpointManagerSingleZoneOneStageCooling& operator=(const SetpointManagerSingleZoneOneStageCooling&) = default;
    SetpointManagerSingleZoneOneStageCooling& operator=(SetpointManagerSingleZoneOneStageCooling&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: coolingStageOnSupplyAirSetpointTemperature and coolingStageOffSupplyAirSetpointTemperature
    //   map directly to E+ SetpointManager:SingleZone:OneStageCooling scalar fields.
    // - Field Mapping: controlVariable is preserved through inherited SetpointManager API and maps to
    //   fixed legacy semantics ("Temperature") because current E+ SetpointManager:SingleZone:OneStageCooling
    //   has no explicit Control Variable field.
    // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSingleZoneOneStageCooling.cpp maps these same
    //   scalar fields and treats Control Zone Name and Setpoint Node or NodeList Name as relationship mappings.
    // - Field Mapping: Relationship fields Control Zone Name and Setpoint Node or NodeList Name are intentionally
    //   excluded from scalar-only scaffolding.
    // - TODO(parity): Add non-scalar relationship parity for control-zone linkage in a follow-up pass.
    std::string controlVariable() const;
    bool setControlVariable(const std::string& controlVariable);

    double coolingStageOnSupplyAirSetpointTemperature() const;
    bool setCoolingStageOnSupplyAirSetpointTemperature(double coolingStageOnSupplyAirSetpointTemperature);

    double coolingStageOffSupplyAirSetpointTemperature() const;
    bool setCoolingStageOffSupplyAirSetpointTemperature(double coolingStageOffSupplyAirSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneOneStageCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneOneStageCooling(std::shared_ptr<detail::SetpointManagerSingleZoneOneStageCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
