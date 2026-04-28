/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOLVAVCHANGEOVERBYPASS_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Node;
class HVACComponent;
class Schedule;

namespace detail {
struct LoadContext;

class EPMODEL_API AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  unsigned inletPort() const override;
  unsigned outletPort() const override;
  virtual ~AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl() override = default;

  bool addToNode(Node& node) override;
  void doCanonicalize(LoadContext& context) override;
  std::vector<ModelObject> children() const override;

  boost::optional<Schedule> availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);
  void resetAvailabilitySchedule();

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

  boost::optional<Schedule> outdoorAirFlowRateMultiplierSchedule() const;
  bool setOutdoorAirFlowRateMultiplierSchedule(Schedule& outdoorAirFlowRateMultiplierSchedule);
  void resetOutdoorAirFlowRateMultiplierSchedule();

  HVACComponent supplyAirFan() const;
  bool setSupplyAirFan(const HVACComponent& fansCVandOnOff);

  std::string supplyAirFanPlacement() const;
  bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

  boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
  bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
  void resetSupplyAirFanOperatingModeSchedule();

  HVACComponent coolingCoil() const;
  bool setCoolingCoil(const HVACComponent& coolingCoilName);

  HVACComponent heatingCoil() const;
  bool setHeatingCoil(const HVACComponent& heatingCoilName);

  boost::optional<Node> fanOutletNode() const;
  boost::optional<Node> coolingCoilOutletNode() const;
  boost::optional<Node> heatingCoilOutletNode() const;

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

 private:
  bool maintainContainedAirPath();
  bool repairContainedAirPath(LoadContext& context);
  bool reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context = nullptr);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
