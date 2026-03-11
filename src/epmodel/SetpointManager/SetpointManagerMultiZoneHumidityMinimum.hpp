/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMINIMUM_HPP
#define EPMODEL_SETPOINTMANAGERMULTIZONEHUMIDITYMINIMUM_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerMultiZoneHumidityMinimum_Impl;
}

class EPMODEL_API SetpointManagerMultiZoneHumidityMinimum : public SetpointManager
{
 public:
  explicit SetpointManagerMultiZoneHumidityMinimum(const Model& model);

  virtual ~SetpointManagerMultiZoneHumidityMinimum() override = default;
  SetpointManagerMultiZoneHumidityMinimum(const SetpointManagerMultiZoneHumidityMinimum& other) = default;
  SetpointManagerMultiZoneHumidityMinimum(SetpointManagerMultiZoneHumidityMinimum&& other) = default;
  SetpointManagerMultiZoneHumidityMinimum& operator=(const SetpointManagerMultiZoneHumidityMinimum&) = default;
  SetpointManagerMultiZoneHumidityMinimum& operator=(SetpointManagerMultiZoneHumidityMinimum&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: minimumSetpointHumidityRatio and maximumSetpointHumidityRatio map directly to
  //   E+ SetpointManager:MultiZone:Humidity:Minimum fields.
  // - Field Mapping: controlVariable is preserved as a fixed-value API ("MinimumHumidityRatio")
  //   even though the E+ object has no explicit control-variable field.
  // - Field Mapping: Relationship fields HVAC Air Loop Name and Setpoint Node or NodeList Name are
  //   intentionally excluded from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit loop/node linkage in a follow-up pass.
  std::string controlVariable() const;
  double minimumSetpointHumidityRatio() const;
  bool isMinimumSetpointHumidityRatioDefaulted() const;
  double maximumSetpointHumidityRatio() const;
  bool isMaximumSetpointHumidityRatioDefaulted() const;

  bool setControlVariable(const std::string& controlVariable);
  bool setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio);
  void resetMinimumSetpointHumidityRatio();
  bool setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio);
  void resetMaximumSetpointHumidityRatio();

 protected:
  using ImplType = detail::SetpointManagerMultiZoneHumidityMinimum_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerMultiZoneHumidityMinimum(std::shared_ptr<detail::SetpointManagerMultiZoneHumidityMinimum_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
