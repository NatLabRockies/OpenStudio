/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/AirLoopHVACUnitarySystem.hpp"
#include "ZoneHVACComponent/AirLoopHVACUnitarySystem_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitarySystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    bool isUnitarySystemAirPathComponent(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<StraightComponent>()) || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
    }

    unsigned unitarySystemAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned unitarySystemAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> unitarySystemAirOutletNode(const HVACComponent& component) {
      const auto outletPort = unitarySystemAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

    bool setComponentAirInletNode(const ModelObject& component, const Node& node) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->setPointer(straightComponent->inletPort(), node.handle());
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->setPointer(waterToAirComponent->airInletPort(), node.handle());
      }
      if (auto zoneComponent = component.optionalCast<ZoneHVACComponent>()) {
        return zoneComponent->setPointer(zoneComponent->inletPort(), node.handle());
      }
      return true;
    }

    bool setComponentAirOutletNode(const ModelObject& component, const Node& node) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->setPointer(straightComponent->outletPort(), node.handle());
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->setPointer(waterToAirComponent->airOutletPort(), node.handle());
      }
      if (auto zoneComponent = component.optionalCast<ZoneHVACComponent>()) {
        return zoneComponent->setPointer(zoneComponent->outletPort(), node.handle());
      }
      return true;
    }

  }  // namespace

  AirLoopHVACUnitarySystem::AirLoopHVACUnitarySystem(const Model& model) : ZoneHVACComponent(AirLoopHVACUnitarySystem::iddObjectType(), model) {
    // Mirror model constructor defaults for scalar fields with strict/non-optional getters.
    OS_ASSERT(setControlType("Load"));
    OS_ASSERT(setDehumidificationControlType("None"));
    OS_ASSERT(setDXHeatingCoilSizingRatio(1.0));
    OS_ASSERT(setUseDOASDXCoolingCoil(false));
    OS_ASSERT(setDOASDXCoolingCoilLeavingMinimumAirTemperature(2.0));
    OS_ASSERT(setLatentLoadControl("SensibleOnlyLoadControl"));
    OS_ASSERT(setSupplyAirFlowRateMethodDuringCoolingOperation("None"));
    OS_ASSERT(setSupplyAirFlowRateMethodDuringHeatingOperation("None"));
    OS_ASSERT(setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired("None"));
    OS_ASSERT(setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
    OS_ASSERT(setMaximumSupplyAirTemperature(80.0));
    OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(21.0));
    OS_ASSERT(setAncilliaryOnCycleElectricPower(0.0));
    OS_ASSERT(setAncilliaryOffCycleElectricPower(0.0));
  }

  AirLoopHVACUnitarySystem::AirLoopHVACUnitarySystem(std::shared_ptr<detail::AirLoopHVACUnitarySystem_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType AirLoopHVACUnitarySystem::iddObjectType() {
    return IddObjectType::AirLoopHVAC_UnitarySystem;
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::controlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitarySystemFields::ControlType);
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType);
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement);
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::latentLoadControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl);
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringCoolingOperationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod);
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringHeatingOperationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod);
  }

  std::vector<std::string> AirLoopHVACUnitarySystem::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod);
  }

  std::string AirLoopHVACUnitarySystem::controlType() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->controlType();
  }

  bool AirLoopHVACUnitarySystem::isControlTypeDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isControlTypeDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setControlType(const std::string& controlType) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setControlType(controlType);
  }

  void AirLoopHVACUnitarySystem::resetControlType() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetControlType();
  }

  boost::optional<ThermalZone> AirLoopHVACUnitarySystem::controllingZoneorThermostatLocation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->controllingZoneorThermostatLocation();
  }

  bool AirLoopHVACUnitarySystem::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setControllingZoneorThermostatLocation(thermalZone);
  }

  void AirLoopHVACUnitarySystem::resetControllingZoneorThermostatLocation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetControllingZoneorThermostatLocation();
  }

  std::string AirLoopHVACUnitarySystem::dehumidificationControlType() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->dehumidificationControlType();
  }

  bool AirLoopHVACUnitarySystem::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  void AirLoopHVACUnitarySystem::resetDehumidificationControlType() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDehumidificationControlType();
  }

  boost::optional<Schedule> AirLoopHVACUnitarySystem::availabilitySchedule() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->availabilitySchedule();
  }

  bool AirLoopHVACUnitarySystem::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirLoopHVACUnitarySystem::resetAvailabilitySchedule() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<HVACComponent> AirLoopHVACUnitarySystem::supplyFan() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyFan();
  }

  bool AirLoopHVACUnitarySystem::setSupplyFan(const HVACComponent& supplyFan) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyFan(supplyFan);
  }

  void AirLoopHVACUnitarySystem::resetSupplyFan() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyFan();
  }

  boost::optional<std::string> AirLoopHVACUnitarySystem::fanPlacement() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fanPlacement();
  }

  bool AirLoopHVACUnitarySystem::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFanPlacement(fanPlacement);
  }

  void AirLoopHVACUnitarySystem::resetFanPlacement() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFanPlacement();
  }

  boost::optional<Schedule> AirLoopHVACUnitarySystem::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  bool AirLoopHVACUnitarySystem::hasHeatingCoil() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->hasHeatingCoil();
  }

  boost::optional<HVACComponent> AirLoopHVACUnitarySystem::heatingCoil() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->heatingCoil();
  }

  bool AirLoopHVACUnitarySystem::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setHeatingCoil(heatingCoil);
  }

  void AirLoopHVACUnitarySystem::resetHeatingCoil() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetHeatingCoil();
  }

  double AirLoopHVACUnitarySystem::dXHeatingCoilSizingRatio() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->dXHeatingCoilSizingRatio();
  }

  bool AirLoopHVACUnitarySystem::isDXHeatingCoilSizingRatioDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDXHeatingCoilSizingRatioDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
  }

  void AirLoopHVACUnitarySystem::resetDXHeatingCoilSizingRatio() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDXHeatingCoilSizingRatio();
  }

  bool AirLoopHVACUnitarySystem::hasCoolingCoil() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->hasCoolingCoil();
  }

  boost::optional<HVACComponent> AirLoopHVACUnitarySystem::coolingCoil() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->coolingCoil();
  }

  bool AirLoopHVACUnitarySystem::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setCoolingCoil(coolingCoil);
  }

  void AirLoopHVACUnitarySystem::resetCoolingCoil() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetCoolingCoil();
  }

  bool AirLoopHVACUnitarySystem::useDOASDXCoolingCoil() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->useDOASDXCoolingCoil();
  }

  bool AirLoopHVACUnitarySystem::isUseDOASDXCoolingCoilDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isUseDOASDXCoolingCoilDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setUseDOASDXCoolingCoil(bool useDOASDXCoolingCoil) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setUseDOASDXCoolingCoil(useDOASDXCoolingCoil);
  }

  void AirLoopHVACUnitarySystem::resetUseDOASDXCoolingCoil() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetUseDOASDXCoolingCoil();
  }

  double AirLoopHVACUnitarySystem::dOASDXCoolingCoilLeavingMinimumAirTemperature() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->dOASDXCoolingCoilLeavingMinimumAirTemperature();
  }

  bool AirLoopHVACUnitarySystem::isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted();
  }

  bool AirLoopHVACUnitarySystem::isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized();
  }

  bool AirLoopHVACUnitarySystem::setDOASDXCoolingCoilLeavingMinimumAirTemperature(double dOASDXCoolingCoilLeavingMinimumAirTemperature) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDOASDXCoolingCoilLeavingMinimumAirTemperature(
      dOASDXCoolingCoilLeavingMinimumAirTemperature);
  }

  void AirLoopHVACUnitarySystem::resetDOASDXCoolingCoilLeavingMinimumAirTemperature() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDOASDXCoolingCoilLeavingMinimumAirTemperature();
  }

  void AirLoopHVACUnitarySystem::autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature();
  }

  std::string AirLoopHVACUnitarySystem::latentLoadControl() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->latentLoadControl();
  }

  bool AirLoopHVACUnitarySystem::isLatentLoadControlDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isLatentLoadControlDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setLatentLoadControl(const std::string& latentLoadControl) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setLatentLoadControl(latentLoadControl);
  }

  void AirLoopHVACUnitarySystem::resetLatentLoadControl() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetLatentLoadControl();
  }

  boost::optional<HVACComponent> AirLoopHVACUnitarySystem::supplementalHeatingCoil() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplementalHeatingCoil();
  }

  bool AirLoopHVACUnitarySystem::setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplementalHeatingCoil(supplementalHeatingCoil);
  }

  void AirLoopHVACUnitarySystem::resetSupplementalHeatingCoil() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplementalHeatingCoil();
  }

  boost::optional<Node> AirLoopHVACUnitarySystem::fanOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fanOutletNode();
  }

  boost::optional<Node> AirLoopHVACUnitarySystem::coolingCoilOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->coolingCoilOutletNode();
  }

  boost::optional<Node> AirLoopHVACUnitarySystem::heatingCoilOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->heatingCoilOutletNode();
  }

  std::string AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateMethodDuringCoolingOperation();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateMethodDuringCoolingOperation(const std::string& supplyAirFlowRateMethodDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateMethodDuringCoolingOperation(
      supplyAirFlowRateMethodDuringCoolingOperation);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateMethodDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateMethodDuringCoolingOperation();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool AirLoopHVACUnitarySystem::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(supplyAirFlowRateDuringCoolingOperation);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateDuringCoolingOperation();
  }

  void AirLoopHVACUnitarySystem::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRatePerFloorAreaDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRatePerFloorAreaDuringCoolingOperation();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(double supplyAirFlowRatePerFloorAreaDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(
      supplyAirFlowRatePerFloorAreaDuringCoolingOperation);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignCoolingSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignCoolingSupplyAirFlowRate();
  }

  bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignCoolingSupplyAirFlowRate(double fractionofAutosizedDesignCoolingSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignCoolingSupplyAirFlowRate(
      fractionofAutosizedDesignCoolingSupplyAirFlowRate);
  }

  void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignCoolingSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignCoolingSupplyAirFlowRate();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation();
  }

  bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(
    double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(
      designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation);
  }

  void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation();
  }

  std::string AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateMethodDuringHeatingOperation();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateMethodDuringHeatingOperation(const std::string& supplyAirFlowRateMethodDuringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateMethodDuringHeatingOperation(
      supplyAirFlowRateMethodDuringHeatingOperation);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateMethodDuringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateMethodDuringHeatingOperation();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool AirLoopHVACUnitarySystem::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(supplyAirFlowRateDuringHeatingOperation);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateDuringHeatingOperation();
  }

  void AirLoopHVACUnitarySystem::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRatePerFloorAreaduringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRatePerFloorAreaduringHeatingOperation();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(double supplyAirFlowRatePerFloorAreaduringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(
      supplyAirFlowRatePerFloorAreaduringHeatingOperation);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignHeatingSupplyAirFlowRate() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignHeatingSupplyAirFlowRate();
  }

  bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignHeatingSupplyAirFlowRate(double fractionofAutosizedDesignHeatingSupplyAirFlowRate) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignHeatingSupplyAirFlowRate(
      fractionofAutosizedDesignHeatingSupplyAirFlowRate);
  }

  void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignHeatingSupplyAirFlowRate() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignHeatingSupplyAirFlowRate();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation();
  }

  bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(
    double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(
      designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation);
  }

  void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation();
  }

  std::string AirLoopHVACUnitarySystem::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(const std::string& noCoolHeatMethod) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(noCoolHeatMethod);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(double supplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
      supplyAirFlowRateWhenNoCoolingorHeatingisRequired);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  void AirLoopHVACUnitarySystem::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(
    double supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(
      supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired);
  }

  void AirLoopHVACUnitarySystem::resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    double fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
      fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
  }

  void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  boost::optional<double> AirLoopHVACUnitarySystem::fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    double fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
      fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
  }

  void AirLoopHVACUnitarySystem::resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  }

  boost::optional<double>
    AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
      ->designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
    double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
      ->setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
        designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired);
  }

  void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
      ->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();
  }

  boost::optional<double>
    AirLoopHVACUnitarySystem::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
      ->designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
    double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
      ->setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
        designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired);
  }

  void AirLoopHVACUnitarySystem::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()
      ->resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();
  }

  bool AirLoopHVACUnitarySystem::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool AirLoopHVACUnitarySystem::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
      noLoadSupplyAirFlowRateControlSetToLowSpeed);
  }

  boost::optional<double> AirLoopHVACUnitarySystem::maximumSupplyAirTemperature() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->maximumSupplyAirTemperature();
  }

  bool AirLoopHVACUnitarySystem::isMaximumSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isMaximumSupplyAirTemperatureDefaulted();
  }

  bool AirLoopHVACUnitarySystem::isMaximumSupplyAirTemperatureAutosized() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isMaximumSupplyAirTemperatureAutosized();
  }

  bool AirLoopHVACUnitarySystem::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setMaximumSupplyAirTemperature(maximumSupplyAirTemperature);
  }

  void AirLoopHVACUnitarySystem::resetMaximumSupplyAirTemperature() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetMaximumSupplyAirTemperature();
  }

  void AirLoopHVACUnitarySystem::autosizeMaximumSupplyAirTemperature() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->autosizeMaximumSupplyAirTemperature();
  }

  double AirLoopHVACUnitarySystem::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool AirLoopHVACUnitarySystem::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void AirLoopHVACUnitarySystem::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  double AirLoopHVACUnitarySystem::ancilliaryOnCycleElectricPower() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->ancilliaryOnCycleElectricPower();
  }

  bool AirLoopHVACUnitarySystem::isAncilliaryOnCycleElectricPowerDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isAncilliaryOnCycleElectricPowerDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setAncilliaryOnCycleElectricPower(double ancilliaryOnCycleElectricPower) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setAncilliaryOnCycleElectricPower(ancilliaryOnCycleElectricPower);
  }

  void AirLoopHVACUnitarySystem::resetAncilliaryOnCycleElectricPower() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetAncilliaryOnCycleElectricPower();
  }

  double AirLoopHVACUnitarySystem::ancilliaryOffCycleElectricPower() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->ancilliaryOffCycleElectricPower();
  }

  bool AirLoopHVACUnitarySystem::isAncilliaryOffCycleElectricPowerDefaulted() const {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->isAncilliaryOffCycleElectricPowerDefaulted();
  }

  bool AirLoopHVACUnitarySystem::setAncilliaryOffCycleElectricPower(double ancilliaryOffCycleElectricPower) {
    return getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->setAncilliaryOffCycleElectricPower(ancilliaryOffCycleElectricPower);
  }

  void AirLoopHVACUnitarySystem::resetAncilliaryOffCycleElectricPower() {
    getImpl<detail::AirLoopHVACUnitarySystem_Impl>()->resetAncilliaryOffCycleElectricPower();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirLoopHVACUnitarySystem_Impl::inletPort() const {
      return openstudio::AirLoopHVAC_UnitarySystemFields::AirInletNodeName;
    }

    unsigned AirLoopHVACUnitarySystem_Impl::outletPort() const {
      return openstudio::AirLoopHVAC_UnitarySystemFields::AirOutletNodeName;
    }

    bool AirLoopHVACUnitarySystem_Impl::addToNode(Node& node) {
      if (node.model() != model() || containingHVACComponent()) {
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop || airLoop->demandComponent(node.handle())) {
        return false;
      }

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      auto branch = airLoopImpl->branchForSupplyNode(node);
      if (!branch) {
        return false;
      }

      const auto nodeName = node.name();
      if (!nodeName) {
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      if (auto currentLoop = airLoopHVAC()) {
        const auto inlet = inletNode();
        const auto outlet = outletNode();
        if ((inlet && (*inlet == node)) || (outlet && (*outlet == node))) {
          return false;
        }
        if (!removeFromAirLoopHVAC()) {
          return false;
        }
        airLoop = node.airLoopHVAC();
        if (!airLoop) {
          return false;
        }
        airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
        branch = airLoopImpl->branchForSupplyNode(node);
        if (!branch) {
          return false;
        }
      }

      const auto thisName = thisObject.nameString();
      const auto components = branch->components();
      std::string inletNodeName;
      std::string outletNodeName;

      if (components.empty()) {
        const auto supplyInlet = airLoop->supplyInletNode();
        const auto supplyOutletNodes = airLoop->supplyOutletNodes();
        const bool isSupplyOutlet = std::find(supplyOutletNodes.begin(), supplyOutletNodes.end(), node) != supplyOutletNodes.end();
        if (!(node == supplyInlet || isSupplyOutlet)) {
          return false;
        }

        if (isSupplyOutlet && airLoop->isDualDuct()) {
          inletNodeName = *nodeName + " - " + thisName + " Inlet";
          outletNodeName = *nodeName;
        } else {
          inletNodeName = supplyInlet.nameString();
          outletNodeName = airLoop->supplyOutletNode().nameString();
        }

        if (!branch->getImpl<detail::Branch_Impl>()->appendComponent(thisObject, inletNodeName, outletNodeName)) {
          return false;
        }
      } else {
        bool inserted = false;
        for (std::size_t i = 0; i < components.size(); ++i) {
          const auto componentInlet = branch->componentInletNode(static_cast<unsigned>(i));
          const auto componentOutlet = branch->componentOutletNode(static_cast<unsigned>(i));
          const bool matchesInlet = componentInlet && openstudio::istringEqual(componentInlet->nameString(), *nodeName);
          const bool matchesOutlet = componentOutlet && openstudio::istringEqual(componentOutlet->nameString(), *nodeName);
          if (!matchesInlet && !matchesOutlet) {
            continue;
          }

          const std::string intermediateNodeName = matchesInlet ? thisName + " Outlet - " + components[i].nameString() + " Inlet"
                                                                : components[i].nameString() + " Outlet - " + thisName + " Inlet";
          const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1u);
          if (matchesOutlet && (i + 1u == components.size())) {
            inletNodeName = intermediateNodeName;
            outletNodeName = *nodeName;
          } else {
            inletNodeName = *nodeName;
            outletNodeName = intermediateNodeName;
          }

          auto branchImpl = branch->getImpl<detail::Branch_Impl>();
          if (!branchImpl->insertComponent(insertIndex, thisObject, inletNodeName, outletNodeName)) {
            return false;
          }

          auto intermediateNode = model().getOrCreateTransientByName<Node>(intermediateNodeName);
          if (matchesInlet) {
            if (!branchImpl->setComponentInletNode(insertIndex + 1u, intermediateNode)
                || !setComponentAirInletNode(components[i], intermediateNode)) {
              return false;
            }
          } else if (!branchImpl->setComponentOutletNode(insertIndex - 1u, intermediateNode)
                     || !setComponentAirOutletNode(components[i], intermediateNode)) {
            return false;
          }
          inserted = true;
          break;
        }
        if (!inserted) {
          return false;
        }
      }

      auto newInletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      auto newOutletNode = model().getOrCreateTransientByName<Node>(outletNodeName);
      if (!setPointer(inletPort(), newInletNode.handle(), false) || !setPointer(outletPort(), newOutletNode.handle(), false)) {
        return false;
      }

      maintainContainedAirPath();
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();
      return true;
    }

    bool AirLoopHVACUnitarySystem_Impl::removeFromAirLoopHVAC() {
      auto airLoop = this->airLoopHVAC();
      auto inlet = inletNode();
      auto outlet = outletNode();
      if (!airLoop || !inlet || !outlet) {
        return false;
      }

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      auto branch = airLoopImpl->branchForSupplyNode(*inlet);
      if (!branch) {
        branch = airLoopImpl->branchForSupplyNode(*outlet);
      }
      if (!branch) {
        return false;
      }

      const auto thisObject = getObject<ModelObject>();
      const auto components = branch->components();
      auto branchImpl = branch->getImpl<detail::Branch_Impl>();
      for (std::size_t i = 0; i < components.size(); ++i) {
        if (components[i] != thisObject) {
          continue;
        }

        if (i + 1u < components.size()) {
          if (!branchImpl->setComponentInletNode(static_cast<unsigned>(i + 1u), *inlet) || !setComponentAirInletNode(components[i + 1u], *inlet)) {
            return false;
          }
        } else if (i > 0u) {
          if (!branchImpl->setComponentOutletNode(static_cast<unsigned>(i - 1u), *outlet)
              || !setComponentAirOutletNode(components[i - 1u], *outlet)) {
            return false;
          }
        }

        if (!branchImpl->removeComponent(static_cast<unsigned>(i))) {
          return false;
        }
        OS_ASSERT(setPointer(inletPort(), Handle(), false));
        OS_ASSERT(setPointer(outletPort(), Handle(), false));
        airLoopImpl->syncSetpointManagerMixedAirFanNodes();
        return true;
      }

      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }
      maintainContainedAirPath();
      return true;
    }

    void AirLoopHVACUnitarySystem_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void AirLoopHVACUnitarySystem_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    std::vector<ModelObject> AirLoopHVACUnitarySystem_Impl::children() const {
      std::vector<ModelObject> result;

      if (auto fan = supplyFan()) {
        result.push_back(*fan);
      }
      if (auto coil = coolingCoil()) {
        result.push_back(*coil);
      }
      if (auto coil = heatingCoil()) {
        result.push_back(*coil);
      }
      if (auto coil = supplementalHeatingCoil()) {
        result.push_back(*coil);
      }

      return result;
    }

    std::vector<IdfObject> AirLoopHVACUnitarySystem_Impl::remove() {
      if (airLoopHVAC() && !removeFromAirLoopHVAC()) {
        return {};
      }

      const auto ownedChildren = children();
      auto removedParent = ZoneHVACComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      // Remove the parent first so the captured children are no longer protected by
      // containingHVACComponent(). Preserve the Model API's children-before-parent
      // ordering in the returned collection.
      std::vector<IdfObject> result;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<HVACComponent>()) {
          auto removed = component->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    std::string AirLoopHVACUnitarySystem_Impl::controlType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isControlTypeDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType);
    }

    bool AirLoopHVACUnitarySystem_Impl::setControlType(const std::string& controlType) {
      return setString(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType, controlType);
    }

    void AirLoopHVACUnitarySystem_Impl::resetControlType() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::ControlType, ""));
    }

    boost::optional<ThermalZone> AirLoopHVACUnitarySystem_Impl::controllingZoneorThermostatLocation() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
        openstudio::AirLoopHVAC_UnitarySystemFields::ControllingZoneorThermostatLocation);
    }

    bool AirLoopHVACUnitarySystem_Impl::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
      return setPointer(openstudio::AirLoopHVAC_UnitarySystemFields::ControllingZoneorThermostatLocation, thermalZone.handle());
    }

    void AirLoopHVACUnitarySystem_Impl::resetControllingZoneorThermostatLocation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::ControllingZoneorThermostatLocation, ""));
    }

    std::string AirLoopHVACUnitarySystem_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType);
    }

    bool AirLoopHVACUnitarySystem_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, dehumidificationControlType);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, ""));
    }

    boost::optional<Schedule> AirLoopHVACUnitarySystem_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirLoopHVAC_UnitarySystemFields::AvailabilityScheduleName);
    }

    bool AirLoopHVACUnitarySystem_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitarySystemFields::AvailabilityScheduleName, "AirLoopHVACUnitarySystem", "Availability", schedule);
    }

    void AirLoopHVACUnitarySystem_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::AvailabilityScheduleName, ""));
    }

    boost::optional<HVACComponent> AirLoopHVACUnitarySystem_Impl::supplyFan() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyFanName);
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyFan(const HVACComponent& supplyFan) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyFanName, supplyFan.handle());
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyFan() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyFanName, ""));
      maintainContainedAirPath();
    }

    boost::optional<std::string> AirLoopHVACUnitarySystem_Impl::fanPlacement() const {
      return getString(openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement, fanPlacement);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void AirLoopHVACUnitarySystem_Impl::resetFanPlacement() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::FanPlacement, ""));
      maintainContainedAirPath();
    }

    boost::optional<Schedule> AirLoopHVACUnitarySystem_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirLoopHVAC_UnitarySystemFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyAirFanOperatingModeScheduleName, "AirLoopHVACUnitarySystem",
                         "Supply Air Fan Operating Mode", schedule);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFanOperatingModeSchedule() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyAirFanOperatingModeScheduleName, ""));
    }

    bool AirLoopHVACUnitarySystem_Impl::hasHeatingCoil() const {
      return !isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingCoilName);
    }

    boost::optional<HVACComponent> AirLoopHVACUnitarySystem_Impl::heatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingCoilName);
    }

    bool AirLoopHVACUnitarySystem_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingCoilName, heatingCoil.handle());
      if (openstudio::istringEqual("None", supplyAirFlowRateMethodDuringHeatingOperation())) {
        autosizeSupplyAirFlowRateDuringHeatingOperation();
        OS_ASSERT(setSupplyAirFlowRateMethodDuringHeatingOperation("SupplyAirFlowRate"));
      }
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void AirLoopHVACUnitarySystem_Impl::resetHeatingCoil() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingCoilName, ""));
      OS_ASSERT(setSupplyAirFlowRateMethodDuringHeatingOperation("None"));
      resetSupplyAirFlowRateDuringHeatingOperation();
      resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation();
      resetFractionofAutosizedDesignHeatingSupplyAirFlowRate();
      resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation();
      if (!hasCoolingCoil()) {
        OS_ASSERT(setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired("None"));
        resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
        resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();
        resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
        resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
        resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();
        resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();
      }
      maintainContainedAirPath();
    }

    double AirLoopHVACUnitarySystem_Impl::dXHeatingCoilSizingRatio() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isDXHeatingCoilSizingRatioDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio);
    }

    bool AirLoopHVACUnitarySystem_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDXHeatingCoilSizingRatio() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, ""));
    }

    bool AirLoopHVACUnitarySystem_Impl::hasCoolingCoil() const {
      return !isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingCoilName);
    }

    boost::optional<HVACComponent> AirLoopHVACUnitarySystem_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingCoilName);
    }

    bool AirLoopHVACUnitarySystem_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingCoilName, coolingCoil.handle());
      if (openstudio::istringEqual("None", supplyAirFlowRateMethodDuringCoolingOperation())) {
        autosizeSupplyAirFlowRateDuringCoolingOperation();
        OS_ASSERT(setSupplyAirFlowRateMethodDuringCoolingOperation("SupplyAirFlowRate"));
      }
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void AirLoopHVACUnitarySystem_Impl::resetCoolingCoil() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingCoilName, ""));
      OS_ASSERT(setSupplyAirFlowRateMethodDuringCoolingOperation("None"));
      resetSupplyAirFlowRateDuringCoolingOperation();
      resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation();
      resetFractionofAutosizedDesignCoolingSupplyAirFlowRate();
      resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation();
      if (!hasHeatingCoil()) {
        OS_ASSERT(setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired("None"));
        resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
        resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();
        resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
        resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
        resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();
        resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();
      }
      maintainContainedAirPath();
    }

    bool AirLoopHVACUnitarySystem_Impl::useDOASDXCoolingCoil() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, true)) {
        return openstudio::istringEqual(*value, "yes");
      }
      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::isUseDOASDXCoolingCoilDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil);
    }

    bool AirLoopHVACUnitarySystem_Impl::setUseDOASDXCoolingCoil(bool useDOASDXCoolingCoil) {
      const bool result = setString(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, useDOASDXCoolingCoil ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void AirLoopHVACUnitarySystem_Impl::resetUseDOASDXCoolingCoil() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, ""));
    }

    double AirLoopHVACUnitarySystem_Impl::dOASDXCoolingCoilLeavingMinimumAirTemperature() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature);
    }

    bool AirLoopHVACUnitarySystem_Impl::isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::setDOASDXCoolingCoilLeavingMinimumAirTemperature(double dOASDXCoolingCoilLeavingMinimumAirTemperature) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, dOASDXCoolingCoilLeavingMinimumAirTemperature);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDOASDXCoolingCoilLeavingMinimumAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, ""));
    }

    void AirLoopHVACUnitarySystem_Impl::autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, "autosize"));
    }

    std::string AirLoopHVACUnitarySystem_Impl::latentLoadControl() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isLatentLoadControlDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl);
    }

    bool AirLoopHVACUnitarySystem_Impl::setLatentLoadControl(const std::string& latentLoadControl) {
      return setString(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl, latentLoadControl);
    }

    void AirLoopHVACUnitarySystem_Impl::resetLatentLoadControl() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::LatentLoadControl, ""));
    }

    boost::optional<HVACComponent> AirLoopHVACUnitarySystem_Impl::supplementalHeatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilName);
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilName, supplementalHeatingCoil.handle());
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplementalHeatingCoil() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilName, ""));
      maintainContainedAirPath();
    }

    boost::optional<Node> AirLoopHVACUnitarySystem_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> AirLoopHVACUnitarySystem_Impl::coolingCoilOutletNode() const {
      auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingCoilName);
      auto cooling =
        (coolingObject && isUnitarySystemAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      if (!cooling) {
        return boost::none;
      }

      return unitarySystemAirOutletNode(*cooling);
    }

    boost::optional<Node> AirLoopHVACUnitarySystem_Impl::heatingCoilOutletNode() const {
      auto heatingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingCoilName);
      auto heating =
        (heatingObject && isUnitarySystemAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      if (!heating) {
        return boost::none;
      }

      return unitarySystemAirOutletNode(*heating);
    }

    std::string AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringCoolingOperation() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateMethodDuringCoolingOperation(
      const std::string& supplyAirFlowRateMethodDuringCoolingOperation) {
      return setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, supplyAirFlowRateMethodDuringCoolingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateMethodDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, ""));
    }

    void AirLoopHVACUnitarySystem_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRatePerFloorAreaDuringCoolingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(
      double supplyAirFlowRatePerFloorAreaDuringCoolingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea,
                       supplyAirFlowRatePerFloorAreaDuringCoolingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignCoolingSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, true);
    }

    bool
      AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignCoolingSupplyAirFlowRate(double fractionofAutosizedDesignCoolingSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate,
                       fractionofAutosizedDesignCoolingSupplyAirFlowRate);
    }

    void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignCoolingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(
      double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity,
                       designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity, ""));
    }

    std::string AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringHeatingOperation() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateMethodDuringHeatingOperation(
      const std::string& supplyAirFlowRateMethodDuringHeatingOperation) {
      return setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, supplyAirFlowRateMethodDuringHeatingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateMethodDuringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateDuringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, ""));
    }

    void AirLoopHVACUnitarySystem_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRatePerFloorAreaduringHeatingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(
      double supplyAirFlowRatePerFloorAreaduringHeatingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea,
                       supplyAirFlowRatePerFloorAreaduringHeatingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignHeatingSupplyAirFlowRate() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, true);
    }

    bool
      AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignHeatingSupplyAirFlowRate(double fractionofAutosizedDesignHeatingSupplyAirFlowRate) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate,
                       fractionofAutosizedDesignHeatingSupplyAirFlowRate);
    }

    void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignHeatingSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(
      double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity,
                       designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity, ""));
    }

    std::string AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(const std::string& noCoolHeatMethod) {
      return setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, noCoolHeatMethod);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool
      AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(double supplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisRequired);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, ""));
    }

    void AirLoopHVACUnitarySystem_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(
      double supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea,
                       supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired);
    }

    void AirLoopHVACUnitarySystem_Impl::resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
      double fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate,
                       fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
    }

    void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate, ""));
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
      double fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate,
                       fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
    }

    void AirLoopHVACUnitarySystem_Impl::resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate, ""));
    }

    boost::optional<double>
      AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
      double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation,
                       designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, ""));
    }

    boost::optional<double>
      AirLoopHVACUnitarySystem_Impl::designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
      double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation,
                       designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired);
    }

    void AirLoopHVACUnitarySystem_Impl::resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, ""));
    }

    bool AirLoopHVACUnitarySystem_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed, true)) {
        return openstudio::istringEqual(*value, "yes");
      }
      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setString(openstudio::AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                    noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> AirLoopHVACUnitarySystem_Impl::maximumSupplyAirTemperature() const {
      return getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, true);
    }

    bool AirLoopHVACUnitarySystem_Impl::isMaximumSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature);
    }

    bool AirLoopHVACUnitarySystem_Impl::isMaximumSupplyAirTemperatureAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitarySystem_Impl::setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, maximumSupplyAirTemperature);
    }

    void AirLoopHVACUnitarySystem_Impl::resetMaximumSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, ""));
    }

    void AirLoopHVACUnitarySystem_Impl::autosizeMaximumSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, "autosize"));
    }

    double AirLoopHVACUnitarySystem_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool AirLoopHVACUnitarySystem_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    void AirLoopHVACUnitarySystem_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, ""));
    }

    double AirLoopHVACUnitarySystem_Impl::ancilliaryOnCycleElectricPower() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isAncilliaryOnCycleElectricPowerDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower);
    }

    bool AirLoopHVACUnitarySystem_Impl::setAncilliaryOnCycleElectricPower(double ancilliaryOnCycleElectricPower) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, ancilliaryOnCycleElectricPower);
    }

    void AirLoopHVACUnitarySystem_Impl::resetAncilliaryOnCycleElectricPower() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, ""));
    }

    double AirLoopHVACUnitarySystem_Impl::ancilliaryOffCycleElectricPower() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitarySystem_Impl::isAncilliaryOffCycleElectricPowerDefaulted() const {
      return isEmpty(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower);
    }

    bool AirLoopHVACUnitarySystem_Impl::setAncilliaryOffCycleElectricPower(double ancilliaryOffCycleElectricPower) {
      return setDouble(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, ancilliaryOffCycleElectricPower);
    }

    void AirLoopHVACUnitarySystem_Impl::resetAncilliaryOffCycleElectricPower() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, ""));
    }

    bool AirLoopHVACUnitarySystem_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool AirLoopHVACUnitarySystem_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirLoopHVACUnitarySystem_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::SupplyFanName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::CoolingCoilName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::HeatingCoilName);
      auto supplementalObject =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilName);

      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto cooling =
        (coolingObject && isUnitarySystemAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      auto heating =
        (heatingObject && isUnitarySystemAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      auto supplemental = (supplementalObject && isUnitarySystemAirPathComponent(*supplementalObject))
                            ? boost::optional<HVACComponent>(*supplementalObject)
                            : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
        return value;
      };

      if (!fan && !cooling && !heating && !supplemental) {
        return changed;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
      trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
      trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));

      const bool blowThrough = fanPlacement() && openstudio::istringEqual(*fanPlacement(), "BlowThrough");

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
        const auto inletPort = unitarySystemAirInletPort(component);
        const auto outletPort = unitarySystemAirOutletPort(component);
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
              const auto downstreamInletPort = unitarySystemAirInletPort(downstream);
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
          const auto downstreamInletPort = unitarySystemAirInletPort(downstream);
          trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(downstreamInletPort, connectorNode->handle(), false));
        }

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(outletPort, downstreamNode.handle(), false));
        upstreamNode = downstreamNode;
      }

      if (nodeWiringChanged && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for AirLoopHVAC:UnitarySystem '" + baseName + "'.");
      }

      return changed;
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::controlTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::controlTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::dehumidificationControlTypeValues();
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::fanPlacementValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::fanPlacementValues();
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::latentLoadControlValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::latentLoadControlValues();
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringCoolingOperationValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringCoolingOperationValues();
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodDuringHeatingOperationValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::supplyAirFlowRateMethodDuringHeatingOperationValues();
    }

    std::vector<std::string> AirLoopHVACUnitarySystem_Impl::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues() const {
      return openstudio::epmodel::AirLoopHVACUnitarySystem::supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
