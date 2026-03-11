/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERCONDENSERENTERINGRESET_HPP
#define EPMODEL_SETPOINTMANAGERCONDENSERENTERINGRESET_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SetpointManagerCondenserEnteringReset_Impl;
}

class EPMODEL_API SetpointManagerCondenserEnteringReset : public ModelObject
{
 public:
  explicit SetpointManagerCondenserEnteringReset(const Model& model);

  virtual ~SetpointManagerCondenserEnteringReset() override = default;
  SetpointManagerCondenserEnteringReset(const SetpointManagerCondenserEnteringReset& other) = default;
  SetpointManagerCondenserEnteringReset(SetpointManagerCondenserEnteringReset&& other) = default;
  SetpointManagerCondenserEnteringReset& operator=(const SetpointManagerCondenserEnteringReset&) = default;
  SetpointManagerCondenserEnteringReset& operator=(SetpointManagerCondenserEnteringReset&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> controlVariableValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to SetpointManager:CondenserEnteringReset fields.
  // - Field Mapping: Default Condenser Entering Water Temperature Schedule Name,
  //   Minimum Design Wetbulb Temperature Curve Name, Minimum Outside Air Wetbulb
  //   Temperature Curve Name, Optimized Cond Entering Water Temperature Curve Name,
  //   and Setpoint Node or NodeList Name are relationship fields and are excluded.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
  std::string controlVariable() const;
  bool isControlVariableDefaulted() const;
  bool setControlVariable(const std::string& controlVariable);
  void resetControlVariable();

  double minimumLift() const;
  bool isMinimumLiftDefaulted() const;
  bool setMinimumLift(double minimumLift);
  void resetMinimumLift();

  double maximumCondenserEnteringWaterTemperature() const;
  bool isMaximumCondenserEnteringWaterTemperatureDefaulted() const;
  bool setMaximumCondenserEnteringWaterTemperature(double maximumCondenserEnteringWaterTemperature);
  void resetMaximumCondenserEnteringWaterTemperature();

  double coolingTowerDesignInletAirWetBulbTemperature() const;
  bool isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted() const;
  bool setCoolingTowerDesignInletAirWetBulbTemperature(double coolingTowerDesignInletAirWetBulbTemperature);
  void resetCoolingTowerDesignInletAirWetBulbTemperature();

 protected:
  using ImplType = detail::SetpointManagerCondenserEnteringReset_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SetpointManagerCondenserEnteringReset(std::shared_ptr<detail::SetpointManagerCondenserEnteringReset_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
