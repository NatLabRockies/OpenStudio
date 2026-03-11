/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSINGLEZONEHEATING_HPP
#define EPMODEL_SETPOINTMANAGERSINGLEZONEHEATING_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerSingleZoneHeating_Impl;
}

class EPMODEL_API SetpointManagerSingleZoneHeating : public SetpointManager
{
 public:
  explicit SetpointManagerSingleZoneHeating(const Model& model);

  virtual ~SetpointManagerSingleZoneHeating() override = default;
  SetpointManagerSingleZoneHeating(const SetpointManagerSingleZoneHeating& other) = default;
  SetpointManagerSingleZoneHeating(SetpointManagerSingleZoneHeating&& other) = default;
  SetpointManagerSingleZoneHeating& operator=(const SetpointManagerSingleZoneHeating&) = default;
  SetpointManagerSingleZoneHeating& operator=(SetpointManagerSingleZoneHeating&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: minimumSupplyAirTemperature and maximumSupplyAirTemperature map directly to
  //   E+ SetpointManager:SingleZone:Heating scalar fields.
  // - Field Mapping: Relationship fields Control Zone Name, Zone Node Name, Zone Inlet Node Name,
  //   and Setpoint Node or NodeList Name are intentionally excluded from scalar-only scaffolding.
  // - Field Mapping: Control Variable is preserved through inherited SetpointManager API and maps to
  //   E+ SetpointManager:SingleZone:Heating Control Variable.
  // - TODO(parity): Add non-scalar relationship parity for control-zone and node linkage in a follow-up pass.
  double minimumSupplyAirTemperature() const;
  double maximumSupplyAirTemperature() const;

  bool setMinimumSupplyAirTemperature(double minimumSupplyAirTemperature);
  bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);

 protected:
  using ImplType = detail::SetpointManagerSingleZoneHeating_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerSingleZoneHeating(std::shared_ptr<detail::SetpointManagerSingleZoneHeating_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
