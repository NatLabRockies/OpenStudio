/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerFollowGroundTemperature_Impl;
}

class EPMODEL_API SetpointManagerFollowGroundTemperature : public SetpointManager
{
 public:
  explicit SetpointManagerFollowGroundTemperature(const Model& model);

  virtual ~SetpointManagerFollowGroundTemperature() override = default;
  SetpointManagerFollowGroundTemperature(const SetpointManagerFollowGroundTemperature& other) = default;
  SetpointManagerFollowGroundTemperature(SetpointManagerFollowGroundTemperature&& other) = default;
  SetpointManagerFollowGroundTemperature& operator=(const SetpointManagerFollowGroundTemperature&) = default;
  SetpointManagerFollowGroundTemperature& operator=(SetpointManagerFollowGroundTemperature&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();
  static std::vector<std::string> referenceGroundTemperatureObjectTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: referenceGroundTemperatureObjectType, offsetTemperatureDifference, maximumSetpointTemperature, and
  //   minimumSetpointTemperature map directly to E+ SetpointManager:FollowGroundTemperature fields.
  // - Field Mapping: Relationship field Setpoint Node or NodeList Name is intentionally excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit setpoint node linkage in a follow-up pass.
  std::string referenceGroundTemperatureObjectType() const;
  double offsetTemperatureDifference() const;
  double maximumSetpointTemperature() const;
  double minimumSetpointTemperature() const;

  bool setReferenceGroundTemperatureObjectType(const std::string& groundTemperatureObjType);
  bool setOffsetTemperatureDifference(double offsetTemperatureDifference);
  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);
  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

 protected:
  using ImplType = detail::SetpointManagerFollowGroundTemperature_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerFollowGroundTemperature(std::shared_ptr<detail::SetpointManagerFollowGroundTemperature_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
