/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONECOOLING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONECOOLING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerSingleZoneCooling_Impl;
  }

  class EPMODEL_API SetpointManagerSingleZoneCooling : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneCooling(const Model& model);

    virtual ~SetpointManagerSingleZoneCooling() override = default;
    SetpointManagerSingleZoneCooling(const SetpointManagerSingleZoneCooling& other) = default;
    SetpointManagerSingleZoneCooling(SetpointManagerSingleZoneCooling&& other) = default;
    SetpointManagerSingleZoneCooling& operator=(const SetpointManagerSingleZoneCooling&) = default;
    SetpointManagerSingleZoneCooling& operator=(SetpointManagerSingleZoneCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSupplyAirTemperature and maximumSupplyAirTemperature map directly to
    //   E+ SetpointManager:SingleZone:Cooling scalar fields.
    // - Field Mapping: Relationship fields Control Zone Name, Zone Node Name, Zone Inlet Node Name,
    //   and Setpoint Node or NodeList Name are intentionally excluded from scalar-only scaffolding.
    // - Field Mapping: Control Variable is preserved through inherited SetpointManager API and maps to
    //   E+ SetpointManager:SingleZone:Cooling Control Variable.
    // - TODO(parity): Add non-scalar relationship parity for control-zone and node linkage in a follow-up pass.
    double minimumSupplyAirTemperature() const;
    bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);

    double maximumSupplyAirTemperature() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

   protected:
    using ImplType = detail::SetpointManagerSingleZoneCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneCooling(std::shared_ptr<detail::SetpointManagerSingleZoneCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
