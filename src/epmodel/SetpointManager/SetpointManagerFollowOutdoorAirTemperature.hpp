/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWOUTDOORAIRTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWOUTDOORAIRTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerFollowOutdoorAirTemperature_Impl;
}

class EPMODEL_API SetpointManagerFollowOutdoorAirTemperature : public SetpointManager
{
 public:
  explicit SetpointManagerFollowOutdoorAirTemperature(const Model& model);

  virtual ~SetpointManagerFollowOutdoorAirTemperature() override = default;
  SetpointManagerFollowOutdoorAirTemperature(const SetpointManagerFollowOutdoorAirTemperature& other) = default;
  SetpointManagerFollowOutdoorAirTemperature(SetpointManagerFollowOutdoorAirTemperature&& other) = default;
  SetpointManagerFollowOutdoorAirTemperature& operator=(const SetpointManagerFollowOutdoorAirTemperature&) = default;
  SetpointManagerFollowOutdoorAirTemperature& operator=(SetpointManagerFollowOutdoorAirTemperature&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: referenceTemperatureType, offsetTemperatureDifference, maximumSetpointTemperature, and
  //   minimumSetpointTemperature map directly to E+ SetpointManager:FollowOutdoorAirTemperature fields.
  // - Field Mapping: Relationship field Setpoint Node or NodeList Name is intentionally excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit setpoint node linkage in a follow-up pass.
  std::string referenceTemperatureType() const;
  double offsetTemperatureDifference() const;
  double maximumSetpointTemperature() const;
  double minimumSetpointTemperature() const;

  bool setReferenceTemperatureType(const std::string& value);
  bool setOffsetTemperatureDifference(double value);
  bool setMaximumSetpointTemperature(double value);
  bool setMinimumSetpointTemperature(double value);

 protected:
  using ImplType = detail::SetpointManagerFollowOutdoorAirTemperature_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerFollowOutdoorAirTemperature(std::shared_ptr<detail::SetpointManagerFollowOutdoorAirTemperature_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
