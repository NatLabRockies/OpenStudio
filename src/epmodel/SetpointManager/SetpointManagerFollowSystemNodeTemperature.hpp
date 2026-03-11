/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerFollowSystemNodeTemperature_Impl;
}

class EPMODEL_API SetpointManagerFollowSystemNodeTemperature : public SetpointManager
{
 public:
  explicit SetpointManagerFollowSystemNodeTemperature(const Model& model);

  virtual ~SetpointManagerFollowSystemNodeTemperature() override = default;
  SetpointManagerFollowSystemNodeTemperature(const SetpointManagerFollowSystemNodeTemperature& other) = default;
  SetpointManagerFollowSystemNodeTemperature(SetpointManagerFollowSystemNodeTemperature&& other) = default;
  SetpointManagerFollowSystemNodeTemperature& operator=(const SetpointManagerFollowSystemNodeTemperature&) = default;
  SetpointManagerFollowSystemNodeTemperature& operator=(SetpointManagerFollowSystemNodeTemperature&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();
  static std::vector<std::string> referenceTemperatureTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: referenceTemperatureType, offsetTemperatureDifference, maximumLimitSetpointTemperature, and
  //   minimumLimitSetpointTemperature map directly to E+ SetpointManager:FollowSystemNodeTemperature fields.
  // - Field Mapping: Relationship fields Reference Node Name and Setpoint Node or NodeList Name are intentionally
  //   excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit reference/setpoint node linkage in a follow-up pass.
  std::string referenceTemperatureType() const;
  double offsetTemperatureDifference() const;
  double maximumLimitSetpointTemperature() const;
  double minimumLimitSetpointTemperature() const;

  bool setReferenceTemperatureType(const std::string& referenceTemperatureType);
  bool setOffsetTemperatureDifference(double offsetTemperatureDifference);
  bool setMaximumLimitSetpointTemperature(double maximumLimitSetpointTemperature);
  bool setMinimumLimitSetpointTemperature(double minimumLimitSetpointTemperature);

 protected:
  using ImplType = detail::SetpointManagerFollowSystemNodeTemperature_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerFollowSystemNodeTemperature(std::shared_ptr<detail::SetpointManagerFollowSystemNodeTemperature_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
