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
class HVACComponent;
class ModelObject;
class Schedule;
class ThermalZone;

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
  // - Status: Partial Parity. The multi-speed scalar controls and direct object-link fields are aligned, and the owned internal air path is now maintained through parent-owned epmodel nodes.
  // - Canonical Counterpart: openstudio::model::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.
  // - Implemented Parity: Availability schedule, controlling zone, supply fan, supply-air-fan operating mode schedule, heating coil,
  //   cooling coil, supplemental heating coil, and the scalar airflow/control fields preserve the main canonical wrapper contract. The
  //   owned fan/cooling/heating/supplemental chain now shares a stable parent-maintained air path, with direct access to the meaningful
  //   outlet node roles on the compound.
  // - Documented Delta: `fanOutletNode()`, `coolingCoilOutletNode()`, and `heatingCoilOutletNode()` are additive epmodel conveniences so
  //   callers can inspect and rename the meaningful internal outlet roles owned by the compound. Broader topology convenience beyond the
  //   owned serial air path remains intentionally omitted.
  // - Field/Storage Mapping: Scalar values map directly to EnergyPlus multi-speed unitary fields, while schedule, fan, coil, zone, and
  //   internal-node relationships are explicit parent-owned object links in epmodel.
  // - Evidence: `src/model/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.hpp`, `src/model/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.cpp`, and `src/epmodel/test/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_GTest.cpp`.
  // - Remaining Parity Work: Add any remaining topology conveniences only if the canonical wrapper still exposes them directly.
  boost::optional<Schedule> availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);
  void resetAvailabilitySchedule();

  boost::optional<ThermalZone> controllingZoneorThermostatLocation() const;
  bool setControllingZoneorThermostatLocation(const ThermalZone& thermalZone);
  void resetControllingZoneorThermostatLocation();

  HVACComponent supplyAirFan() const;
  bool setSupplyAirFan(const HVACComponent& fan);

  std::string supplyAirFanPlacement() const;
  bool setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement);

  Schedule supplyAirFanOperatingModeSchedule() const;
  bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

  HVACComponent heatingCoil() const;
  bool setHeatingCoil(const HVACComponent& coil);

  double dXHeatingCoilSizingRatio() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

  HVACComponent coolingCoil() const;
  bool setCoolingCoil(const HVACComponent& coil);

  HVACComponent supplementalHeatingCoil() const;
  bool setSupplementalHeatingCoil(const HVACComponent& coil);

  boost::optional<Node> fanOutletNode() const;
  boost::optional<Node> coolingCoilOutletNode() const;
  boost::optional<Node> heatingCoilOutletNode() const;

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
