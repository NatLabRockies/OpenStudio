/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEMAXIMUMHUMIDITYAVERAGE_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEMAXIMUMHUMIDITYAVERAGE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerMultiZoneMaximumHumidityAverage_Impl;
}

class EPMODEL_API SetpointManagerMultiZoneMaximumHumidityAverage : public SetpointManager
{
 public:
  explicit SetpointManagerMultiZoneMaximumHumidityAverage(const Model& model);

  virtual ~SetpointManagerMultiZoneMaximumHumidityAverage() override = default;
  SetpointManagerMultiZoneMaximumHumidityAverage(const SetpointManagerMultiZoneMaximumHumidityAverage& other) = default;
  SetpointManagerMultiZoneMaximumHumidityAverage(SetpointManagerMultiZoneMaximumHumidityAverage&& other) = default;
  SetpointManagerMultiZoneMaximumHumidityAverage& operator=(const SetpointManagerMultiZoneMaximumHumidityAverage&) = default;
  SetpointManagerMultiZoneMaximumHumidityAverage& operator=(SetpointManagerMultiZoneMaximumHumidityAverage&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: minimumSetpointHumidityRatio and maximumSetpointHumidityRatio map directly to
  //   E+ SetpointManager:MultiZone:MaximumHumidity:Average fields.
  // - Field Mapping: controlVariable is preserved as a fixed-value API ("MaximumHumidityRatio")
  //   even though the E+ object has no explicit control-variable field.
  // - Field Mapping: Relationship fields HVAC Air Loop Name and Setpoint Node or NodeList Name are
  //   intentionally excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit loop/node linkage in a follow-up pass.
  std::string controlVariable() const;
  double minimumSetpointHumidityRatio() const;
  double maximumSetpointHumidityRatio() const;

  bool setControlVariable(const std::string& controlVariable);
  bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
  bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);

 protected:
  using ImplType = detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerMultiZoneMaximumHumidityAverage(std::shared_ptr<detail::SetpointManagerMultiZoneMaximumHumidityAverage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
