/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEREHEAT_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;

  namespace detail {
    class SetpointManagerSingleZoneReheat_Impl;
  }

  class EPMODEL_API SetpointManagerSingleZoneReheat : public SetpointManager
  {
   public:
    explicit SetpointManagerSingleZoneReheat(const Model& model);

    virtual ~SetpointManagerSingleZoneReheat() override = default;
    SetpointManagerSingleZoneReheat(const SetpointManagerSingleZoneReheat& other) = default;
    SetpointManagerSingleZoneReheat(SetpointManagerSingleZoneReheat&& other) = default;
    SetpointManagerSingleZoneReheat& operator=(const SetpointManagerSingleZoneReheat&) = default;
    SetpointManagerSingleZoneReheat& operator=(SetpointManagerSingleZoneReheat&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: minimumSupplyAirTemperature and maximumSupplyAirTemperature map directly to
    //   E+ SetpointManager:SingleZone:Reheat scalar fields.
    // - Field Mapping: Relationship fields Control Zone Name, Zone Node Name, Zone Inlet Node Name,
    //   and Setpoint Node or NodeList Name are intentionally excluded from scalar-only scaffolding.
    // - Field Mapping: Control Variable is preserved through inherited SetpointManager API and maps to
    //   E+ SetpointManager:SingleZone:Reheat Control Variable.
    // - TODO(parity): Add non-scalar relationship parity for control-zone and node linkage in a follow-up pass.
    double minimumSupplyAirTemperature() const;
    bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);

    double maximumSupplyAirTemperature() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

    boost::optional<ThermalZone> controlZone() const;

   protected:
    using ImplType = detail::SetpointManagerSingleZoneReheat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSingleZoneReheat(std::shared_ptr<detail::SetpointManagerSingleZoneReheat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
