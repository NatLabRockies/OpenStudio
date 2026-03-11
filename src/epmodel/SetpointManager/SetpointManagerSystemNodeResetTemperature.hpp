/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerSystemNodeResetTemperature_Impl;
}

class EPMODEL_API SetpointManagerSystemNodeResetTemperature : public SetpointManager
{
 public:
  explicit SetpointManagerSystemNodeResetTemperature(const Model& model);

  virtual ~SetpointManagerSystemNodeResetTemperature() override = default;
  SetpointManagerSystemNodeResetTemperature(const SetpointManagerSystemNodeResetTemperature& other) = default;
  SetpointManagerSystemNodeResetTemperature(SetpointManagerSystemNodeResetTemperature&& other) = default;
  SetpointManagerSystemNodeResetTemperature& operator=(const SetpointManagerSystemNodeResetTemperature&) = default;
  SetpointManagerSystemNodeResetTemperature& operator=(SetpointManagerSystemNodeResetTemperature&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: setpointatLowReferenceTemperature, setpointatHighReferenceTemperature,
  //   lowReferenceTemperature, and highReferenceTemperature map directly to
  //   E+ SetpointManager:SystemNodeReset:Temperature scalar fields.
  // - ForwardTranslator Evidence: ForwardTranslateSetpointManagerSystemNodeResetTemperature writes these exact
  //   scalar fields plus control variable using preserved model API names.
  // - Field Mapping: Relationship fields Reference Node Name and Setpoint Node or NodeList Name are intentionally
  //   excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit reference-node linkage in a follow-up pass.
  double setpointatLowReferenceTemperature() const;
  double setpointatHighReferenceTemperature() const;
  double lowReferenceTemperature() const;
  double highReferenceTemperature() const;

  bool setSetpointatLowReferenceTemperature(double setpointatLowReferenceTemperature);
  bool setSetpointatHighReferenceTemperature(double setpointatHighReferenceTemperature);
  bool setLowReferenceTemperature(double lowReferenceTemperature);
  bool setHighReferenceTemperature(double highReferenceTemperature);

 protected:
  using ImplType = detail::SetpointManagerSystemNodeResetTemperature_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerSystemNodeResetTemperature(std::shared_ptr<detail::SetpointManagerSystemNodeResetTemperature_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
