/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl() override = default;

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

  std::vector<std::string> supplyAirFanPlacementValues() const;
  std::vector<std::string> priorityControlModeValues() const;
  std::vector<std::string> dehumidificationControlTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
