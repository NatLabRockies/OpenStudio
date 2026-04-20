/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERRETURNTEMPERATURECHILLEDWATER_HPP
#define EPMODEL_SETPOINTMANAGERRETURNTEMPERATURECHILLEDWATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerReturnTemperatureChilledWater_Impl;
}

class EPMODEL_API SetpointManagerReturnTemperatureChilledWater : public ModelObject
{
 public:
  explicit SetpointManagerReturnTemperatureChilledWater(const Model& model);

  virtual ~SetpointManagerReturnTemperatureChilledWater() override = default;
  SetpointManagerReturnTemperatureChilledWater(const SetpointManagerReturnTemperatureChilledWater& other) = default;
  SetpointManagerReturnTemperatureChilledWater(SetpointManagerReturnTemperatureChilledWater&& other) = default;
  SetpointManagerReturnTemperatureChilledWater& operator=(const SetpointManagerReturnTemperatureChilledWater&) = default;
  SetpointManagerReturnTemperatureChilledWater& operator=(SetpointManagerReturnTemperatureChilledWater&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> returnTemperatureSetpointInputTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to SetpointManager:ReturnTemperature:ChilledWater fields.
  // - Field Mapping: Plant Loop Supply Outlet Node, Plant Loop Supply Inlet Node, and Return
  //   Temperature Setpoint Schedule Name are relationship fields and are excluded from scalar scope.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
  double minimumSupplyTemperatureSetpoint() const;
  bool isMinimumSupplyTemperatureSetpointDefaulted() const;
  bool setMinimumSupplyTemperatureSetpoint(double minimumSupplyTemperatureSetpoint);
  void resetMinimumSupplyTemperatureSetpoint();

  double maximumSupplyTemperatureSetpoint() const;
  bool isMaximumSupplyTemperatureSetpointDefaulted() const;
  bool setMaximumSupplyTemperatureSetpoint(double maximumSupplyTemperatureSetpoint);
  void resetMaximumSupplyTemperatureSetpoint();

  std::string returnTemperatureSetpointInputType() const;
  bool setReturnTemperatureSetpointInputType(const std::string& returnTemperatureSetpointInputType);

  double returnTemperatureSetpointConstantValue() const;
  bool isReturnTemperatureSetpointConstantValueDefaulted() const;
  bool setReturnTemperatureSetpointConstantValue(double returnTemperatureSetpointConstantValue);
  void resetReturnTemperatureSetpointConstantValue();

 protected:
  using ImplType = detail::SetpointManagerReturnTemperatureChilledWater_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerReturnTemperatureChilledWater(std::shared_ptr<detail::SetpointManagerReturnTemperatureChilledWater_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
