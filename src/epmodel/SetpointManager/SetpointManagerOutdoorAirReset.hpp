/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_HPP
#define EPMODEL_SETPOINTMANAGEROUTDOORAIRRESET_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerOutdoorAirReset_Impl;
}

class EPMODEL_API SetpointManagerOutdoorAirReset : public SetpointManager
{
 public:
  explicit SetpointManagerOutdoorAirReset(const Model& model);

  virtual ~SetpointManagerOutdoorAirReset() override = default;
  SetpointManagerOutdoorAirReset(const SetpointManagerOutdoorAirReset& other) = default;
  SetpointManagerOutdoorAirReset(SetpointManagerOutdoorAirReset&& other) = default;
  SetpointManagerOutdoorAirReset& operator=(const SetpointManagerOutdoorAirReset&) = default;
  SetpointManagerOutdoorAirReset& operator=(SetpointManagerOutdoorAirReset&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
  // - Field Mapping: setpointatOutdoorLowTemperature, outdoorLowTemperature,
  //   setpointatOutdoorHighTemperature, outdoorHighTemperature,
  //   setpointatOutdoorLowTemperature2, outdoorLowTemperature2,
  //   setpointatOutdoorHighTemperature2, and outdoorHighTemperature2 map directly to
  //   E+ SetpointManager:OutdoorAirReset scalar fields.
  // - Field Mapping: Relationship fields Setpoint Node or NodeList Name and Schedule Name are intentionally excluded
  //   from scalar-only scaffolding.
  // - TODO(parity): Add non-scalar relationship parity for explicit schedule and setpoint-node linkage.
  bool isControlVariableDefaulted() const;

  double setpointatOutdoorLowTemperature() const;
  double outdoorLowTemperature() const;
  double setpointatOutdoorHighTemperature() const;
  double outdoorHighTemperature() const;

  boost::optional<double> setpointatOutdoorLowTemperature2() const;
  boost::optional<double> outdoorLowTemperature2() const;
  boost::optional<double> setpointatOutdoorHighTemperature2() const;
  boost::optional<double> outdoorHighTemperature2() const;

  void resetControlVariable();

  bool setSetpointatOutdoorLowTemperature(double setpointatOutdoorLowTemperature);
  bool setOutdoorLowTemperature(double outdoorLowTemperature);
  bool setSetpointatOutdoorHighTemperature(double setpointatOutdoorHighTemperature);
  bool setOutdoorHighTemperature(double outdoorHighTemperature);

  bool setSetpointatOutdoorLowTemperature2(double setpointatOutdoorLowTemperature2);
  void resetSetpointatOutdoorLowTemperature2();
  bool setOutdoorLowTemperature2(double outdoorLowTemperature2);
  void resetOutdoorLowTemperature2();
  bool setSetpointatOutdoorHighTemperature2(double setpointatOutdoorHighTemperature2);
  void resetSetpointatOutdoorHighTemperature2();
  bool setOutdoorHighTemperature2(double outdoorHighTemperature2);
  void resetOutdoorHighTemperature2();

 protected:
  using ImplType = detail::SetpointManagerOutdoorAirReset_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerOutdoorAirReset(std::shared_ptr<detail::SetpointManagerOutdoorAirReset_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
