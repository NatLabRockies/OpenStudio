/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

namespace {

bool isUnitaryHeatPumpMultiSpeedAirPathComponent(const HVACComponent& component) {
  return static_cast<bool>(component.optionalCast<StraightComponent>()) || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
}

unsigned unitaryHeatPumpMultiSpeedAirInletPort(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->inletPort();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airInletPort();
  }
  return 0u;
}

unsigned unitaryHeatPumpMultiSpeedAirOutletPort(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->outletPort();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airOutletPort();
  }
  return 0u;
}

boost::optional<Node> unitaryHeatPumpMultiSpeedAirOutletNode(const HVACComponent& component) {
  const auto outletPort = unitaryHeatPumpMultiSpeedAirOutletPort(component);
  if (outletPort == 0u) {
    return boost::none;
  }
  return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
}

}  // namespace

AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(const Model& model)
  : StraightComponent(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::iddObjectType(), model) {
  ScheduleConstant alwaysOn(model);
  OS_ASSERT(alwaysOn.setValue(1.0));
  OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));

  // Mirror model scalar constructor defaults while excluding relationship fields.
  OS_ASSERT(setSupplyAirFanPlacement("DrawThrough"));
  OS_ASSERT(setDXHeatingCoilSizingRatio(1.0));
  autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(21.0));
  OS_ASSERT(setAuxiliaryOnCycleElectricPower(0.0));
  OS_ASSERT(setAuxiliaryOffCycleElectricPower(0.0));
  OS_ASSERT(setDesignHeatRecoveryWaterFlowRate(0.0));
  OS_ASSERT(setMaximumTemperatureforHeatRecovery(80.0));
  autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  OS_ASSERT(setNumberofSpeedsforHeating(2));
  OS_ASSERT(setNumberofSpeedsforCooling(2));
  autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();
  autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();
  autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();
  autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();
  autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();
}

AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(
  const Model& model, const HVACComponent& supplyAirFan, const HVACComponent& heatingCoil, const HVACComponent& coolingCoil,
  const HVACComponent& supplementalHeatingCoil)
  : AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(model) {
  bool ok = true;
  ok = setSupplyAirFan(supplyAirFan);
  OS_ASSERT(ok);
  ok = setHeatingCoil(heatingCoil);
  OS_ASSERT(ok);
  ok = setCoolingCoil(coolingCoil);
  OS_ASSERT(ok);
  ok = setSupplementalHeatingCoil(supplementalHeatingCoil);
  OS_ASSERT(ok);
}

AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed(
  std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::addToNode(Node& node) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->addToNode(node);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement);
}

boost::optional<Schedule> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::availabilitySchedule() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->availabilitySchedule();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setAvailabilitySchedule(schedule);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::resetAvailabilitySchedule() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->resetAvailabilitySchedule();
}

boost::optional<ThermalZone> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::controllingZoneorThermostatLocation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->controllingZoneorThermostatLocation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setControllingZoneorThermostatLocation(thermalZone);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::resetControllingZoneorThermostatLocation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->resetControllingZoneorThermostatLocation();
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFan() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplyAirFan();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplyAirFan(const HVACComponent& fan) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplyAirFan(fan);
}

std::string AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplyAirFanPlacement();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplyAirFanPlacement(supplyAirFanPlacement);
}

Schedule AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanOperatingModeSchedule() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplyAirFanOperatingModeSchedule();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::heatingCoil() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->heatingCoil();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setHeatingCoil(const HVACComponent& coil) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setHeatingCoil(coil);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::dXHeatingCoilSizingRatio() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->dXHeatingCoilSizingRatio();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::coolingCoil() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->coolingCoil();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setCoolingCoil(const HVACComponent& coil) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setCoolingCoil(coil);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplementalHeatingCoil() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplementalHeatingCoil();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplementalHeatingCoil(const HVACComponent& coil) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplementalHeatingCoil(coil);
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::fanOutletNode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->fanOutletNode();
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::coolingCoilOutletNode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->coolingCoilOutletNode();
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::heatingCoilOutletNode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->heatingCoilOutletNode();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
    maximumSupplyAirTemperaturefromSupplementalHeater);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::auxiliaryOnCycleElectricPower() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->auxiliaryOnCycleElectricPower();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setAuxiliaryOnCycleElectricPower(double auxiliaryOnCycleElectricPower) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setAuxiliaryOnCycleElectricPower(auxiliaryOnCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::auxiliaryOffCycleElectricPower() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->auxiliaryOffCycleElectricPower();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setAuxiliaryOffCycleElectricPower(double auxiliaryOffCycleElectricPower) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setAuxiliaryOffCycleElectricPower(auxiliaryOffCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::designHeatRecoveryWaterFlowRate() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->designHeatRecoveryWaterFlowRate();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setDesignHeatRecoveryWaterFlowRate(designHeatRecoveryWaterFlowRate);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::maximumTemperatureforHeatRecovery() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->maximumTemperatureforHeatRecovery();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setMaximumTemperatureforHeatRecovery(double maximumTemperatureforHeatRecovery) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setMaximumTemperatureforHeatRecovery(maximumTemperatureforHeatRecovery);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::numberofSpeedsforHeating() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->numberofSpeedsforHeating();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setNumberofSpeedsforHeating(int numberofSpeedsforHeating) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setNumberofSpeedsforHeating(numberofSpeedsforHeating);
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::numberofSpeedsforCooling() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->numberofSpeedsforCooling();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setNumberofSpeedsforCooling(int numberofSpeedsforCooling) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setNumberofSpeedsforCooling(numberofSpeedsforCooling);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed1SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed1SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed1SupplyAirFlowRateDuringHeatingOperation(
  double speed1SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed1SupplyAirFlowRateDuringHeatingOperation(
    speed1SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed2SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed2SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed2SupplyAirFlowRateDuringHeatingOperation(
  double speed2SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed2SupplyAirFlowRateDuringHeatingOperation(
    speed2SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed3SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed3SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed3SupplyAirFlowRateDuringHeatingOperation(
  double speed3SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed3SupplyAirFlowRateDuringHeatingOperation(
    speed3SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed4SupplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed4SupplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed4SupplyAirFlowRateDuringHeatingOperation(
  double speed4SupplyAirFlowRateDuringHeatingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed4SupplyAirFlowRateDuringHeatingOperation(
    speed4SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed1SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed1SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed1SupplyAirFlowRateDuringCoolingOperation(
  double speed1SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed1SupplyAirFlowRateDuringCoolingOperation(
    speed1SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed2SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed2SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed2SupplyAirFlowRateDuringCoolingOperation(
  double speed2SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed2SupplyAirFlowRateDuringCoolingOperation(
    speed2SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed3SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed3SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed3SupplyAirFlowRateDuringCoolingOperation(
  double speed3SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed3SupplyAirFlowRateDuringCoolingOperation(
    speed3SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::speed4SupplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->speed4SupplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::setSpeed4SupplyAirFlowRateDuringCoolingOperation(
  double speed4SupplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->setSpeed4SupplyAirFlowRateDuringCoolingOperation(
    speed4SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl>()->autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::inletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirInletNodeName;
}

unsigned AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::outletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirOutletNodeName;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();

  if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
    return false;
  }

  if (!StraightComponent_Impl::addToNode(node)) {
    return false;
  }

  maintainContainedAirPath();
  return true;
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::doCanonicalize(LoadContext& context) {
  repairContainedAirPath(context);
}

std::vector<ModelObject> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::children() const {
  std::vector<ModelObject> result;

  if (auto supplyFan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanName)) {
    result.emplace_back(*supplyFan);
  }
  if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilName)) {
    result.emplace_back(*heatingCoil);
  }
  if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilName)) {
    result.emplace_back(*coolingCoil);
  }
  if (auto supplementalHeatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoilName)) {
    result.emplace_back(*supplementalHeatingCoil);
  }

  return result;
}

boost::optional<Schedule> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::availabilitySchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AvailabilityScheduleName);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AvailabilityScheduleName,
                     "AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed", "Availability Schedule", schedule);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::resetAvailabilitySchedule() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AvailabilityScheduleName, ""));
}

boost::optional<ThermalZone> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::controllingZoneorThermostatLocation() const {
  return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::ControllingZoneorThermostatLocation);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
  return setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::ControllingZoneorThermostatLocation,
                    thermalZone.handle());
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::resetControllingZoneorThermostatLocation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::ControllingZoneorThermostatLocation, ""));
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFan() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplyAirFan(const HVACComponent& fan) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanName, fan.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

std::string AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
  const bool result = setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement, supplyAirFanPlacement);
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

Schedule AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFanOperatingModeSchedule() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanOperatingModeScheduleName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
  return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanOperatingModeScheduleName,
                     "AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed", "Supply Air Fan Operating Mode Schedule", schedule);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::heatingCoil() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setHeatingCoil(const HVACComponent& coil) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilName, coil.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::dXHeatingCoilSizingRatio() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DXHeatingCoilSizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::coolingCoil() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setCoolingCoil(const HVACComponent& coil) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilName, coil.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplementalHeatingCoil() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoilName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplementalHeatingCoil(const HVACComponent& coil) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoilName, coil.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::fanOutletNode() const {
  auto fanObject =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanName);
  auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
  if (!fan) {
    return boost::none;
  }

  auto fanOutlet = fan->outletModelObject();
  return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::coolingCoilOutletNode() const {
  auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilName);
  auto cooling = (coolingObject && isUnitaryHeatPumpMultiSpeedAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject)
                                                                                                 : boost::none;
  if (!cooling) {
    return boost::none;
  }

  return unitaryHeatPumpMultiSpeedAirOutletNode(*cooling);
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::heatingCoilOutletNode() const {
  auto heatingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilName);
  auto heating = (heatingObject && isUnitaryHeatPumpMultiSpeedAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject)
                                                                                                 : boost::none;
  if (!heating) {
    return boost::none;
  }

  return unitaryHeatPumpMultiSpeedAirOutletNode(*heating);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                             true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                   maximumSupplyAirTemperaturefromSupplementalHeater);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  OS_ASSERT(
    setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "autosize"));
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  const auto value =
    getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
              true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::auxiliaryOnCycleElectricPower() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOnCycleElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setAuxiliaryOnCycleElectricPower(double auxiliaryOnCycleElectricPower) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOnCycleElectricPower,
                   auxiliaryOnCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::auxiliaryOffCycleElectricPower() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOffCycleElectricPower, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setAuxiliaryOffCycleElectricPower(double auxiliaryOffCycleElectricPower) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOffCycleElectricPower,
                   auxiliaryOffCycleElectricPower);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::designHeatRecoveryWaterFlowRate() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DesignHeatRecoveryWaterFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setDesignHeatRecoveryWaterFlowRate(double designHeatRecoveryWaterFlowRate) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DesignHeatRecoveryWaterFlowRate,
                   designHeatRecoveryWaterFlowRate);
}

double AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maximumTemperatureforHeatRecovery() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumTemperatureforHeatRecovery, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setMaximumTemperatureforHeatRecovery(double maximumTemperatureforHeatRecovery) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumTemperatureforHeatRecovery,
                   maximumTemperatureforHeatRecovery);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate,
                   supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, "autosize"));
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::numberofSpeedsforHeating() const {
  const auto value = getInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforHeating, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setNumberofSpeedsforHeating(int numberofSpeedsforHeating) {
  return setInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforHeating, numberofSpeedsforHeating);
}

int AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::numberofSpeedsforCooling() const {
  const auto value = getInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforCooling, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setNumberofSpeedsforCooling(int numberofSpeedsforCooling) {
  return setInt(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforCooling, numberofSpeedsforCooling);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed1SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed1SupplyAirFlowRateDuringHeatingOperation(
  double speed1SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate,
                   speed1SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed2SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed2SupplyAirFlowRateDuringHeatingOperation(
  double speed2SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate,
                   speed2SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed3SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed3SupplyAirFlowRateDuringHeatingOperation(
  double speed3SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate,
                   speed3SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed4SupplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed4SupplyAirFlowRateDuringHeatingOperation(
  double speed4SupplyAirFlowRateDuringHeatingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate,
                   speed4SupplyAirFlowRateDuringHeatingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed1SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed1SupplyAirFlowRateDuringCoolingOperation(
  double speed1SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate,
                   speed1SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed2SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed2SupplyAirFlowRateDuringCoolingOperation(
  double speed2SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate,
                   speed2SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed3SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed3SupplyAirFlowRateDuringCoolingOperation(
  double speed3SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate,
                   speed3SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::speed4SupplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::setSpeed4SupplyAirFlowRateDuringCoolingOperation(
  double speed4SupplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate,
                   speed4SupplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, "autosize"));
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::maintainContainedAirPath() {
  return reconcileContainedAirPath(false, nullptr);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::repairContainedAirPath(LoadContext& context) {
  return reconcileContainedAirPath(true, &context);
}

bool AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
  auto thisObject = getObject<ModelObject>();
  if (!thisObject.name()) {
    thisObject.createName();
  }

  auto fanObject =
    thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanName);
  auto heatingObject =
    thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilName);
  auto coolingObject =
    thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilName);
  auto supplementalObject = thisObject.getModelObjectTarget<HVACComponent>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoilName);

  auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
  auto heating = (heatingObject && isUnitaryHeatPumpMultiSpeedAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject)
                                                                                                 : boost::none;
  auto cooling = (coolingObject && isUnitaryHeatPumpMultiSpeedAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject)
                                                                                                 : boost::none;
  auto supplemental = (supplementalObject && isUnitaryHeatPumpMultiSpeedAirPathComponent(*supplementalObject))
                        ? boost::optional<HVACComponent>(*supplementalObject)
                        : boost::none;

  bool changed = false;
  bool nodeWiringChanged = false;
  auto trackNodeChange = [&](bool value) {
    nodeWiringChanged = nodeWiringChanged || value;
    changed = changed || value;
    return value;
  };

  if (!fan && !heating && !cooling && !supplemental) {
    return changed;
  }

  const auto baseName = thisObject.nameString();
  auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
  auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
  trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
  trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));

  const bool blowThrough = openstudio::istringEqual(supplyAirFanPlacement(), "BlowThrough");

  std::vector<HVACComponent> orderedComponents;
  if (blowThrough) {
    if (fan) {
      orderedComponents.push_back(*fan);
    }
    if (cooling) {
      orderedComponents.push_back(*cooling);
    }
    if (heating) {
      orderedComponents.push_back(*heating);
    }
  } else {
    if (cooling) {
      orderedComponents.push_back(*cooling);
    }
    if (heating) {
      orderedComponents.push_back(*heating);
    }
    if (fan) {
      orderedComponents.push_back(*fan);
    }
  }
  if (supplemental) {
    orderedComponents.push_back(*supplemental);
  }

  if (orderedComponents.empty()) {
    return changed;
  }

  auto connectorName = [&](const HVACComponent& component) {
    if (fan && (component.handle() == fan->handle())) {
      return baseName + " Fan Outlet Node";
    }
    if (cooling && (component.handle() == cooling->handle())) {
      return baseName + " Cooling Coil Outlet Node";
    }
    if (heating && (component.handle() == heating->handle())) {
      return baseName + " Heating Coil Outlet Node";
    }
    return component.nameString() + " Outlet Node";
  };

  Node upstreamNode = inletNode;
  for (std::size_t i = 0; i < orderedComponents.size(); ++i) {
    auto component = orderedComponents[i];
    const auto inletPort = unitaryHeatPumpMultiSpeedAirInletPort(component);
    const auto outletPort = unitaryHeatPumpMultiSpeedAirOutletPort(component);
    if ((inletPort == 0u) || (outletPort == 0u)) {
      continue;
    }

    trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(inletPort, upstreamNode.handle(), false));

    Node downstreamNode = outletNode;
    if ((i + 1u) < orderedComponents.size()) {
      auto downstream = orderedComponents[i + 1u];
      boost::optional<Node> connectorNode;

      if (allowChildNodeRecovery) {
        if (auto currentOutlet = component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort)) {
          const auto downstreamInletPort = unitaryHeatPumpMultiSpeedAirInletPort(downstream);
          if (auto downstreamInlet = downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(downstreamInletPort)) {
            if ((*currentOutlet == *downstreamInlet) && (*currentOutlet != inletNode) && (*currentOutlet != outletNode)) {
              connectorNode = currentOutlet;
            }
          }
        }
      }

      if (!connectorNode) {
        connectorNode = model().getOrCreateTransientByName<Node>(connectorName(component));
      }

      downstreamNode = *connectorNode;
      const auto downstreamInletPort = unitaryHeatPumpMultiSpeedAirInletPort(downstream);
      trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(downstreamInletPort, connectorNode->handle(), false));
    }

    trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(outletPort, downstreamNode.handle(), false));
    upstreamNode = downstreamNode;
  }

  if (nodeWiringChanged && context) {
    detail::addLoadInfo(*context, "Reconciled internal node wiring for AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed '" + baseName + "'.");
  }

  return changed;
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_Impl::supplyAirFanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::supplyAirFanPlacementValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
