/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl;
}

class EPMODEL_API AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass : public ModelObject
{
 public:
  explicit AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model);

  virtual ~AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass() override = default;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass& other) = default;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass&& other) = default;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass& operator=(const AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass&) = default;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass& operator=(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyAirFanPlacementValues();
  static std::vector<std::string> priorityControlModeValues();
  static std::vector<std::string> dehumidificationControlTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: systemAirFlowRateDuring* and outdoorAirFlowRateDuring* APIs map to E+ Cooling/Heating/NoLoad * Flow Rate fields.
  // - Field Mapping: minimumRuntimeBeforeOperatingModeChange remains mapped directly to E+ field despite historical default nuance in model.
  // - Field Mapping: availability schedule, fan/coil object references, node names, and plenum/mixer linkage fields are relationship-like and excluded.
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
  boost::optional<double> systemAirFlowRateDuringCoolingOperation() const;
  bool isSystemAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSystemAirFlowRateDuringCoolingOperation(double systemAirFlowRateDuringCoolingOperation);
  void autosizeSystemAirFlowRateDuringCoolingOperation();

  boost::optional<double> systemAirFlowRateDuringHeatingOperation() const;
  bool isSystemAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSystemAirFlowRateDuringHeatingOperation(double systemAirFlowRateDuringHeatingOperation);
  void autosizeSystemAirFlowRateDuringHeatingOperation();

  boost::optional<double> systemAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
  bool isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
  bool setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(double systemAirFlowRateWhenNoCoolingorHeatingisNeeded);
  void autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();

  boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;
  bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;
  bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);
  void autosizeOutdoorAirFlowRateDuringCoolingOperation();

  boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;
  bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;
  bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);
  void autosizeOutdoorAirFlowRateDuringHeatingOperation();

  boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
  bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
  bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

  std::string supplyAirFanPlacement() const;
  bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

  std::string priorityControlMode() const;
  bool setPriorityControlMode(const std::string& priorityControlMode);

  double minimumOutletAirTemperatureDuringCoolingOperation() const;
  bool setMinimumOutletAirTemperatureDuringCoolingOperation(double minimumOutletAirTemperatureDuringCoolingOperation);

  double maximumOutletAirTemperatureDuringHeatingOperation() const;
  bool setMaximumOutletAirTemperatureDuringHeatingOperation(double maximumOutletAirTemperatureDuringHeatingOperation);

  std::string dehumidificationControlType() const;
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);

  double minimumRuntimeBeforeOperatingModeChange() const;
  bool setMinimumRuntimeBeforeOperatingModeChange(double runtime);

 protected:
  using ImplType = detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(
    std::shared_ptr<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
