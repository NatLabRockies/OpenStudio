/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIRMULTISPEED_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIRMULTISPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl;
}

class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed : public StraightComponent
{
 public:
  explicit AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(const Model& model);

  virtual ~AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed() override = default;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(const AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed& other) = default;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed&& other) = default;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed& operator=(const AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed&) = default;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed& operator=(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyAirFanPlacementValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The multi-speed scalar controls are aligned, but the schedule, fan, coil, node, and zone-link surface is still intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.
  // - Implemented Parity: `supplyAirFanPlacement`, `dXHeatingCoilSizingRatio`, `maximumSupplyAirTemperaturefromSupplementalHeater`, `maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation`, `auxiliaryOnCycleElectricPower`, `auxiliaryOffCycleElectricPower`, `designHeatRecoveryWaterFlowRate`, `maximumTemperatureforHeatRecovery`, `supplyAirFlowRateWhenNoCoolingorHeatingisNeeded`, `numberofSpeedsforHeating`, `numberofSpeedsforCooling`, and the per-speed flow setters preserve the canonical scalar contract.
  // - Documented Delta: Supply fan, schedule, coil, node, and controlling-zone linkage fields are not exposed as public accessors yet.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus multi-speed unitary fields; the forward translator wires the equipment graph separately.
  // - Evidence: `src/model/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.hpp`, `src/model/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.cpp`, and `src/epmodel/test/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted fan, schedule, coil, node, and controlling-zone helpers when relationship parity expands.
  std::string supplyAirFanPlacement() const;
  bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

  double dXHeatingCoilSizingRatio() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

  boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
  bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
  bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
  void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
  bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);

  double auxiliaryOnCycleElectricPower() const;
  bool setAuxiliaryOnCycleElectricPower(double auxiliaryOnCycleElectricPower);

  double auxiliaryOffCycleElectricPower() const;
  bool setAuxiliaryOffCycleElectricPower(double auxiliaryOffCycleElectricPower);

  double designHeatRecoveryWaterFlowRate() const;
  bool setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate);

  double maximumTemperatureforHeatRecovery() const;
  bool setMaximumTemperatureforHeatRecovery(double maximumTemperatureforHeatRecovery);

  boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
  bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
  bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

  int numberofSpeedsforHeating() const;
  bool setNumberofSpeedsforHeating(int numberofSpeedsforHeating);

  int numberofSpeedsforCooling() const;
  bool setNumberofSpeedsforCooling(int numberofSpeedsforCooling);

  boost::optional<double> speed1SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed1SupplyAirFlowRateDuringHeatingOperation(double speed1SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed2SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed2SupplyAirFlowRateDuringHeatingOperation(double speed2SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed3SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed3SupplyAirFlowRateDuringHeatingOperation(double speed3SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed4SupplyAirFlowRateDuringHeatingOperation() const;
  bool isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSpeed4SupplyAirFlowRateDuringHeatingOperation(double speed4SupplyAirFlowRateDuringHeatingOperation);
  void autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> speed1SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed1SupplyAirFlowRateDuringCoolingOperation(double speed1SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> speed2SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed2SupplyAirFlowRateDuringCoolingOperation(double speed2SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> speed3SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed3SupplyAirFlowRateDuringCoolingOperation(double speed3SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> speed4SupplyAirFlowRateDuringCoolingOperation() const;
  bool isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSpeed4SupplyAirFlowRateDuringCoolingOperation(double speed4SupplyAirFlowRateDuringCoolingOperation);
  void autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(
    std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
