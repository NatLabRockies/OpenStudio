/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONECOOLINGAVERAGE_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONECOOLINGAVERAGE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerMultiZoneCoolingAverage_Impl;
}

class EPMODEL_API SetpointManagerMultiZoneCoolingAverage : public SetpointManager
{
 public:
  explicit SetpointManagerMultiZoneCoolingAverage(const Model& model);

  virtual ~SetpointManagerMultiZoneCoolingAverage() override = default;
  SetpointManagerMultiZoneCoolingAverage(const SetpointManagerMultiZoneCoolingAverage& other) = default;
  SetpointManagerMultiZoneCoolingAverage(SetpointManagerMultiZoneCoolingAverage&& other) = default;
  SetpointManagerMultiZoneCoolingAverage& operator=(const SetpointManagerMultiZoneCoolingAverage&) = default;
  SetpointManagerMultiZoneCoolingAverage& operator=(SetpointManagerMultiZoneCoolingAverage&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: minimumSetpointTemperature and maximumSetpointTemperature map directly to
  //   E+ SetpointManager:MultiZone:Cooling:Average fields.
  // - Field Mapping: controlVariable is preserved as a fixed-value API ("Temperature") even though
  //   the E+ object has no explicit control-variable field.
  // - Field Mapping: Relationship fields HVAC Air Loop Name and Setpoint Node or NodeList Name are
  //   intentionally excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit loop/node linkage in a follow-up pass.
  std::string controlVariable() const;
  double minimumSetpointTemperature() const;
  double maximumSetpointTemperature() const;

  bool setControlVariable(const std::string& controlVariable);
  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);
  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

 protected:
  using ImplType = detail::SetpointManagerMultiZoneCoolingAverage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerMultiZoneCoolingAverage(std::shared_ptr<detail::SetpointManagerMultiZoneCoolingAverage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
