/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/OutdoorAirMixer.hpp"
#include "ModelObject/OutdoorAirMixer_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"
#include "../utilities/core/StringHelpers.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneHVACTerminalUnitVariableRefrigerantFlow::ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model)
    : ZoneHVACComponent(ZoneHVACTerminalUnitVariableRefrigerantFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>());
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setTerminalUnitAvailabilityschedule(alwaysOn));
    OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));
  }

  ZoneHVACTerminalUnitVariableRefrigerantFlow::ZoneHVACTerminalUnitVariableRefrigerantFlow(
    std::shared_ptr<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACTerminalUnitVariableRefrigerantFlow::iddObjectType() {
    return IddObjectType::ZoneHVAC_TerminalUnit_VariableRefrigerantFlow;
  }

  std::vector<std::string> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
  }

  Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow::terminalUnitAvailabilityschedule() const {
    return getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>()->terminalUnitAvailabilityschedule();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setTerminalUnitAvailabilityschedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>()->setTerminalUnitAvailabilityschedule(schedule);
  }

  namespace {

    const detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl* impl(const ZoneHVACTerminalUnitVariableRefrigerantFlow* object) {
      return object->getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>().get();
    }

    detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl* impl(ZoneHVACTerminalUnitVariableRefrigerantFlow* object) {
      return object->getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>().get();
    }

    // VRF terminals accept a small family of DX coil objects in both the
    // OpenStudio and EnergyPlus IDD spaces. Keeping that check local here
    // makes the setter rules explicit without pushing VRF-specific type
    // knowledge into the shared ZoneHVAC helpers.
    bool isVRFDXCoil(const HVACComponent& component) {
      const auto iddObjectType = component.iddObject().type();
      return (iddObjectType == IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow)
             || (iddObjectType == IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
             || (iddObjectType == IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow)
             || (iddObjectType == IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl)
             || (iddObjectType == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow)
             || (iddObjectType == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
             || (iddObjectType == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow)
             || (iddObjectType == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl);
    }

    // VRF terminal has one straight fan, VRF coils that epmodel now exposes as
    // straight components, and an optional water supplemental heater. Keeping
    // that supported child set local here still matters, but the actual port
    // lookup can now use the shared serial-air bases instead of hard-coding
    // each VRF coil field enum again.
    bool isVRFTerminalAirPathComponent(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<StraightComponent>())
             || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
    }

    unsigned vrfTerminalAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned vrfTerminalAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> vrfTerminalAirOutletNode(const HVACComponent& component) {
      const auto outletPort = vrfTerminalAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

    OutdoorAirMixer getOrCreateOwnedOutdoorAirMixer(ModelObject& owner, unsigned fieldIndex, const std::string& preferredName) {
      if (auto existing = owner.getModelObjectTarget<OutdoorAirMixer>(fieldIndex)) {
        return *existing;
      }

      auto currentName = owner.getString(fieldIndex, true);
      if (currentName && !currentName->empty()) {
        if (auto existing = owner.model().getConcreteModelObjectByName<OutdoorAirMixer>(*currentName)) {
          return *existing;
        }
      }

      if (!preferredName.empty()) {
        if (auto existing = owner.model().getConcreteModelObjectByName<OutdoorAirMixer>(preferredName)) {
          return *existing;
        }
      }

      OutdoorAirMixer created(owner.model());
      if (!preferredName.empty() && !created.setName(preferredName)) {
        OS_ASSERT(created.setName(owner.model().nextName(OutdoorAirMixer::iddObjectType(), true)));
      }
      return created;
    }

    bool clearOwnedOutdoorAirMixer(ModelObject& owner, unsigned fieldIndex) {
      auto current = owner.getModelObjectTarget<OutdoorAirMixer>(fieldIndex);
      bool ownerIsOnlySource = false;
      if (current) {
        ownerIsOnlySource = true;
        for (const auto& source : current->sources()) {
          if (source.handle() != owner.handle()) {
            ownerIsOnlySource = false;
            break;
          }
        }
      }

      bool changed = owner.getImpl<detail::ModelObject_Impl>()->setPointer(fieldIndex, Handle(), false);
      if (current && ownerIsOnlySource && !current->remove().empty()) {
        changed = true;
      }
      return changed;
    }

  }  // namespace

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateDuringCoolingOperation() const {
    return impl(this)->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return impl(this)->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return impl(this)->setSupplyAirFlowRateDuringCoolingOperation(supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    impl(this)->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
    return impl(this)->autosizedSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateWhenNoCoolingisNeeded() const {
    return impl(this)->supplyAirFlowRateWhenNoCoolingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const {
    return impl(this)->isSupplyAirFlowRateWhenNoCoolingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateWhenNoCoolingisNeeded(double supplyAirFlowRateWhenNoCoolingisNeeded) {
    return impl(this)->setSupplyAirFlowRateWhenNoCoolingisNeeded(supplyAirFlowRateWhenNoCoolingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFlowRateWhenNoCoolingisNeeded() {
    impl(this)->resetSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateWhenNoCoolingisNeeded() {
    impl(this)->autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const {
    return impl(this)->autosizedSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateDuringHeatingOperation() const {
    return impl(this)->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return impl(this)->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return impl(this)->setSupplyAirFlowRateDuringHeatingOperation(supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    impl(this)->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
    return impl(this)->autosizedSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateWhenNoHeatingisNeeded() const {
    return impl(this)->supplyAirFlowRateWhenNoHeatingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const {
    return impl(this)->isSupplyAirFlowRateWhenNoHeatingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateWhenNoHeatingisNeeded(double supplyAirFlowRateWhenNoHeatingisNeeded) {
    return impl(this)->setSupplyAirFlowRateWhenNoHeatingisNeeded(supplyAirFlowRateWhenNoHeatingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFlowRateWhenNoHeatingisNeeded() {
    impl(this)->resetSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateWhenNoHeatingisNeeded() {
    impl(this)->autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const {
    return impl(this)->autosizedSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateDuringCoolingOperation() const {
    return impl(this)->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return impl(this)->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return impl(this)->setOutdoorAirFlowRateDuringCoolingOperation(outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    impl(this)->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
    return impl(this)->autosizedOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateDuringHeatingOperation() const {
    return impl(this)->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return impl(this)->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return impl(this)->setOutdoorAirFlowRateDuringHeatingOperation(outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    impl(this)->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
    return impl(this)->autosizedOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return impl(this)->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return impl(this)->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return impl(this)->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    impl(this)->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    impl(this)->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return impl(this)->autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::zoneTerminalUnitOnParasiticElectricEnergyUse() const {
    return impl(this)->zoneTerminalUnitOnParasiticElectricEnergyUse();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setZoneTerminalUnitOnParasiticElectricEnergyUse(
    double zoneTerminalUnitOnParasiticElectricEnergyUse) {
    return impl(this)->setZoneTerminalUnitOnParasiticElectricEnergyUse(zoneTerminalUnitOnParasiticElectricEnergyUse);
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::zoneTerminalUnitOffParasiticElectricEnergyUse() const {
    return impl(this)->zoneTerminalUnitOffParasiticElectricEnergyUse();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setZoneTerminalUnitOffParasiticElectricEnergyUse(
    double zoneTerminalUnitOffParasiticElectricEnergyUse) {
    return impl(this)->setZoneTerminalUnitOffParasiticElectricEnergyUse(zoneTerminalUnitOffParasiticElectricEnergyUse);
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::ratedTotalHeatingCapacitySizingRatio() const {
    return impl(this)->ratedTotalHeatingCapacitySizingRatio();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio) {
    return impl(this)->setRatedTotalHeatingCapacitySizingRatio(ratedTotalHeatingCapacitySizingRatio);
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return impl(this)->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return impl(this)->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setMaximumSupplyAirTemperaturefromSupplementalHeater(
    double maximumSupplyAirTemperaturefromSupplementalHeater) {
    return impl(this)->setMaximumSupplyAirTemperaturefromSupplementalHeater(maximumSupplyAirTemperaturefromSupplementalHeater);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    impl(this)->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return impl(this)->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return impl(this)->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return impl(this)->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    impl(this)->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanPlacement() const {
    return impl(this)->supplyAirFanPlacement();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFanPlacementDefaulted() const {
    return impl(this)->isSupplyAirFanPlacementDefaulted();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
    return impl(this)->setSupplyAirFanPlacement(supplyAirFanPlacement);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFanPlacement() {
    impl(this)->resetSupplyAirFanPlacement();
  }

  HVACComponent ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFan() const {
    return impl(this)->supplyAirFan();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFan(const HVACComponent& fan) {
    return impl(this)->setSupplyAirFan(fan);
  }

  Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanOperatingModeSchedule() const {
    return impl(this)->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return impl(this)->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow::coolingCoil() const {
    return impl(this)->coolingCoil();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setCoolingCoil(const HVACComponent& coil) {
    return impl(this)->setCoolingCoil(coil);
  }

  boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow::heatingCoil() const {
    return impl(this)->heatingCoil();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setHeatingCoil(const HVACComponent& coil) {
    return impl(this)->setHeatingCoil(coil);
  }

  boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplementalHeatingCoil() const {
    return impl(this)->supplementalHeatingCoil();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplementalHeatingCoil(const HVACComponent& coil) {
    return impl(this)->setSupplementalHeatingCoil(coil);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplementalHeatingCoil() {
    impl(this)->resetSupplementalHeatingCoil();
  }

  boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow::fanOutletNode() const {
    return impl(this)->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow::coolingCoilOutletNode() const {
    return impl(this)->coolingCoilOutletNode();
  }

  boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow::heatingCoilOutletNode() const {
    return impl(this)->heatingCoilOutletNode();
  }

  boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow::mixedAirNode() const {
    return impl(this)->mixedAirNode();
  }

  boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirNode() const {
    return impl(this)->outdoorAirNode();
  }

  boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow::reliefAirNode() const {
    return impl(this)->reliefAirNode();
  }

  boost::optional<OutdoorAirMixer> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirMixer() const {
    return impl(this)->outdoorAirMixer();
  }

  boost::optional<ThermalZone> ZoneHVACTerminalUnitVariableRefrigerantFlow::controllingZoneorThermostatLocation() const {
    return impl(this)->controllingZoneorThermostatLocation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
    return impl(this)->setControllingZoneorThermostatLocation(thermalZone);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetControllingZoneorThermostatLocation() {
    impl(this)->resetControllingZoneorThermostatLocation();
  }

  std::vector<ModelObject> ZoneHVACTerminalUnitVariableRefrigerantFlow::children() const {
    return impl(this)->children();
  }

  namespace detail {

    Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::terminalUnitAvailabilityschedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAvailabilitySchedule);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setTerminalUnitAvailabilityschedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAvailabilitySchedule,
                                           "ZoneHVACTerminalUnitVariableRefrigerantFlow", "Terminal Unit Availability", schedule);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result = supplyAirFlowRateDuringCoolingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate,
                                        supplyAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    // epmodel does not currently resolve autosized values from SQL results.
    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateWhenNoCoolingisNeeded() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateWhenNoCoolingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingisNeeded
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoCoolingisNeeded.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFlowRateWhenNoCoolingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateWhenNoCoolingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result = supplyAirFlowRateDuringHeatingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate,
                                        supplyAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateWhenNoHeatingisNeeded() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateWhenNoHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoHeatingisNeeded
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFlowRateWhenNoHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateWhenNoHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result = outdoorAirFlowRateDuringCoolingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate,
                                        outdoorAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result = outdoorAirFlowRateDuringHeatingOperation
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate,
                                        outdoorAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return boost::none;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::zoneTerminalUnitOnParasiticElectricEnergyUse() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setZoneTerminalUnitOnParasiticElectricEnergyUse(
      double zoneTerminalUnitOnParasiticElectricEnergyUse) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse,
                              zoneTerminalUnitOnParasiticElectricEnergyUse, false);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::zoneTerminalUnitOffParasiticElectricEnergyUse() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setZoneTerminalUnitOffParasiticElectricEnergyUse(
      double zoneTerminalUnitOffParasiticElectricEnergyUse) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse,
                              zoneTerminalUnitOffParasiticElectricEnergyUse, false);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::ratedTotalHeatingCapacitySizingRatio() const {
      boost::optional<double> value = getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio) {
      bool result =
        setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, ratedTotalHeatingCapacitySizingRatio, false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, false);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      double maximumSupplyAirTemperaturefromSupplementalHeater) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                              maximumSupplyAirTemperaturefromSupplementalHeater, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result =
        setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = setDouble(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                              maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result =
        setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFanPlacement() const {
      auto value = getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
      if (!value) {
        return {};
      }
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, supplyAirFanPlacement, false);
      OS_ASSERT(result);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFanPlacement() {
      bool result = setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, "", false);
      OS_ASSERT(result);
      maintainContainedAirPath();
    }

    HVACComponent ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFan() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName);
      OS_ASSERT(fan);
      return *fan;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFan(const HVACComponent& fan) {
      if (fan.model() != model()) {
        return false;
      }

      const auto iddObjectType = fan.iddObject().type();
      if (isFluidTemperatureControl()) {
        if ((iddObjectType != IddObjectType::OS_Fan_SystemModel) && (iddObjectType != IddObjectType::OS_Fan_VariableVolume)
            && (iddObjectType != IddObjectType::Fan_SystemModel) && (iddObjectType != IddObjectType::Fan_VariableVolume)) {
          return false;
        }
      } else if ((iddObjectType != IddObjectType::OS_Fan_ConstantVolume) && (iddObjectType != IddObjectType::OS_Fan_OnOff)
                 && (iddObjectType != IddObjectType::OS_Fan_SystemModel) && (iddObjectType != IddObjectType::Fan_ConstantVolume)
                 && (iddObjectType != IddObjectType::Fan_OnOff) && (iddObjectType != IddObjectType::Fan_SystemModel)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName, fan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    Schedule ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFanOperatingModeSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanOperatingModeScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanOperatingModeScheduleName,
                                           "ZoneHVACTerminalUnitVariableRefrigerantFlow", "Supply Air Fan Operating Mode", schedule);
    }

    boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setCoolingCoil(const HVACComponent& coil) {
      if ((coil.model() != model()) || !isVRFDXCoil(coil) || (vrfTerminalAirInletPort(coil) == 0u) || (vrfTerminalAirOutletPort(coil) == 0u)) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow)
          && (iddObjectType != IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
          && (iddObjectType != IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow)
          && (iddObjectType != IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)) {
        return false;
      }

      if (auto heating = heatingCoil()) {
        const auto heatingType = heating->iddObject().type();
        const bool heatingFluidControl =
          (heatingType == IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl)
          || (heatingType == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl);
        const bool coolingFluidControl =
          (iddObjectType == IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
          || (iddObjectType == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl);
        if (heatingFluidControl != coolingFluidControl) {
          return false;
        }
      }

      const bool result = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName, coil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::heatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setHeatingCoil(const HVACComponent& coil) {
      if ((coil.model() != model()) || !isVRFDXCoil(coil) || (vrfTerminalAirInletPort(coil) == 0u) || (vrfTerminalAirOutletPort(coil) == 0u)) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl)
          && (iddObjectType != IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow)
          && (iddObjectType != IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl)) {
        return false;
      }

      if (auto cooling = coolingCoil()) {
        const auto coolingType = cooling->iddObject().type();
        const bool coolingFluidControl =
          (coolingType == IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
          || (coolingType == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl);
        const bool heatingFluidControl =
          (iddObjectType == IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl)
          || (iddObjectType == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl);
        if (coolingFluidControl != heatingFluidControl) {
          return false;
        }
      }

      const bool result = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName, coil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<HVACComponent> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplementalHeatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplementalHeatingCoil(const HVACComponent& coil) {
      if ((coil.model() != model()) || !isVRFTerminalAirPathComponent(coil)) {
        return false;
      }

      const auto iddObjectType = coil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_Gas) && (iddObjectType != IddObjectType::OS_Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_Water) && (iddObjectType != IddObjectType::Coil_Heating_Fuel)
          && (iddObjectType != IddObjectType::Coil_Heating_Electric) && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName, coil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplementalHeatingCoil() {
      bool result = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName, Handle(), false);
      OS_ASSERT(result);
      maintainContainedAirPath();
    }

    boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::coolingCoilOutletNode() const {
      auto cooling = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName);
      if (!cooling) {
        return boost::none;
      }
      return vrfTerminalAirOutletNode(*cooling);
    }

    boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::heatingCoilOutletNode() const {
      auto heating = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName);
      if (!heating) {
        return boost::none;
      }
      return vrfTerminalAirOutletNode(*heating);
    }

    boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::mixedAirNode() const {
      auto mixer = outdoorAirMixer();
      return mixer ? mixer->mixedAirNode() : boost::none;
    }

    boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirNode() const {
      auto mixer = outdoorAirMixer();
      return mixer ? mixer->outdoorAirNode() : boost::none;
    }

    boost::optional<Node> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::reliefAirNode() const {
      auto mixer = outdoorAirMixer();
      return mixer ? mixer->reliefAirNode() : boost::none;
    }

    boost::optional<OutdoorAirMixer> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirMixer() const {
      return getObject<ModelObject>().getModelObjectTarget<OutdoorAirMixer>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectName);
    }

    boost::optional<ThermalZone> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::controllingZoneorThermostatLocation() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
        ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setControllingZoneorThermostatLocation(const ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation, thermalZone.handle(), false);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetControllingZoneorThermostatLocation() {
      OS_ASSERT(setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation, ""));
    }

    std::vector<ModelObject> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::children() const {
      std::vector<ModelObject> result;

      if (auto fan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName)) {
        result.push_back(*fan);
      }
      if (auto coil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName)) {
        result.push_back(*coil);
      }
      if (auto coil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName)) {
        result.push_back(*coil);
      }
      if (auto coil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName)) {
        result.push_back(*coil);
      }
      if (auto mixer = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectName)) {
        result.push_back(*mixer);
      }

      return result;
    }

    unsigned ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::inletPort() const {
      return ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNodeName;
    }

    unsigned ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outletPort() const {
      return ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNodeName;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }
      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isFluidTemperatureControl() const {
      const auto cooling = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName);
      const auto heating = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName);
      const auto isFluidTemp = [](const boost::optional<HVACComponent>& component) {
        if (!component) {
          return false;
        }
        const auto iddObjectType = component->iddObject().type();
        return (iddObjectType == IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
               || (iddObjectType == IddObjectType::OS_Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl)
               || (iddObjectType == IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow_FluidTemperatureControl)
               || (iddObjectType == IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl);
      };
      return isFluidTemp(cooling) || isFluidTemp(heating);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      // Valid VRF terminal air paths follow the same serial shapes as the
      // packaged terminal families:
      // cooling -> heating -> fan -> supplemental (draw-through)
      // fan -> cooling -> heating -> supplemental (blow-through)
      // When the owned local OA mixer is active, the first component sees a mixed
      // air node instead of the parent inlet. Ordinary owner mutations keep
      // that shape intact. Canonicalization may additionally preserve already
      // shared child nodes from imported raw state.
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName);
      auto supplementalObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName);

      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto cooling =
        (coolingObject && isVRFTerminalAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      auto heating =
        (heatingObject && isVRFTerminalAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      auto supplemental = (supplementalObject && isVRFTerminalAirPathComponent(*supplementalObject))
                            ? boost::optional<HVACComponent>(*supplementalObject)
                            : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
        return value;
      };

      const auto syncTypeField = [&](unsigned fieldIndex, const boost::optional<HVACComponent>& component) {
        const auto currentValue = thisObject.getString(fieldIndex, true);
        const auto expectedValue = component ? boost::optional<std::string>(component->iddObject().name()) : boost::optional<std::string>();
        if (expectedValue) {
          if (!currentValue || !openstudio::istringEqual(*currentValue, *expectedValue)) {
            OS_ASSERT(thisObject.setString(fieldIndex, *expectedValue));
            changed = true;
          }
        } else if (currentValue && !currentValue->empty()) {
          OS_ASSERT(thisObject.setString(fieldIndex, ""));
          changed = true;
        }
      };

      syncTypeField(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectType,
                    fanObject ? boost::optional<HVACComponent>(*fanObject) : boost::none);
      syncTypeField(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectType, cooling);
      syncTypeField(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectType, heating);
      syncTypeField(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilObjectType, supplemental);

      // The terminal owns this local OA mixer whenever it owns its own zone-side
      // air path. Zero OA flow still means a valid local mixer topology in
      // EnergyPlus; it should not make the topology object appear and disappear.
      const bool usesHiddenMixedAir = !airLoopHVAC();

      if (!fan && !cooling && !heating && !supplemental) {
        return changed;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
      trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
      trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));

      boost::optional<OutdoorAirMixer> outdoorAirMixer;
      boost::optional<Node> sourceNode;
      if (usesHiddenMixedAir) {
        sourceNode = model().getOrCreateTransientByName<Node>(baseName + " Mixer Outlet Node");
        outdoorAirMixer =
          getOrCreateOwnedOutdoorAirMixer(thisObject, ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectName,
                                          baseName + " OA Mixer");
        changed = setPointer(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectName, outdoorAirMixer->handle()) || changed;

        const auto currentMixerType = thisObject.getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectType, true);
        const std::string expectedMixerType = outdoorAirMixer->iddObject().name();
        if (!currentMixerType || !openstudio::istringEqual(*currentMixerType, expectedMixerType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectType, expectedMixerType));
          changed = true;
        }

        auto outdoorAirNode = model().getOrCreateTransientByName<Node>(baseName + " Outdoor Air Node");
        auto reliefAirNode = model().getOrCreateTransientByName<Node>(baseName + " Relief Air Node");
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::MixedAirNodeName, sourceNode->handle()) || changed;
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::ReturnAirStreamNodeName, inletNode.handle()) || changed;
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::OutdoorAirStreamNodeName, outdoorAirNode.handle()) || changed;
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::ReliefAirStreamNodeName, reliefAirNode.handle()) || changed;
      } else {
        const auto currentMixerType = thisObject.getString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectType, true);
        if (currentMixerType && !currentMixerType->empty()) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectType, ""));
          changed = true;
        }
        changed = clearOwnedOutdoorAirMixer(thisObject, ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectName) || changed;
      }

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

      if (usesHiddenMixedAir) {
        const auto& firstComponent = orderedComponents.front();
        if (allowChildNodeRecovery) {
          // Canonicalization can preserve an existing mixed-air node when the
          // first child already points at one that is not a boundary node.
          if (auto candidate =
                firstComponent.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(vrfTerminalAirInletPort(firstComponent))) {
            if ((*candidate != inletNode) && (*candidate != outletNode)) {
              sourceNode = candidate;
              changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::MixedAirNodeName, sourceNode->handle()) || changed;
            }
          }
        }
      }

      Node upstreamNode = sourceNode ? *sourceNode : inletNode;
      auto& firstComponent = orderedComponents.front();
      trackNodeChange(firstComponent.getImpl<detail::ModelObject_Impl>()->setPointer(vrfTerminalAirInletPort(firstComponent),
                                                                                    upstreamNode.handle(), false));

      for (size_t i = 0; i < orderedComponents.size(); ++i) {
        auto& component = orderedComponents[i];
        const bool hasNext = (i + 1u) < orderedComponents.size();
        if (!hasNext) {
          trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(vrfTerminalAirOutletPort(component),
                                                                                   outletNode.handle(), false));
          continue;
        }

        auto& downstream = orderedComponents[i + 1u];
        boost::optional<Node> connectorNode;

        if (auto currentOutlet =
              component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(vrfTerminalAirOutletPort(component))) {
          if (auto downstreamInlet =
                downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(vrfTerminalAirInletPort(downstream))) {
            if ((*currentOutlet == *downstreamInlet) && (*currentOutlet != inletNode) && (*currentOutlet != outletNode)
                && (!sourceNode || (*currentOutlet != *sourceNode))) {
              connectorNode = currentOutlet;
            }
          } else if (allowChildNodeRecovery && (*currentOutlet != inletNode) && (*currentOutlet != outletNode)
                     && (!sourceNode || (*currentOutlet != *sourceNode))) {
            connectorNode = currentOutlet;
          }
        }

        if (!connectorNode && allowChildNodeRecovery) {
          // Canonicalization keeps an existing shared connector when adjacent
          // children already agree on it and it is not one of the parent-owned
          // boundary or mixed-air nodes.
          if (auto downstreamInlet =
                downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(vrfTerminalAirInletPort(downstream))) {
            if ((*downstreamInlet != inletNode) && (*downstreamInlet != outletNode) && (!sourceNode || (*downstreamInlet != *sourceNode))) {
              connectorNode = downstreamInlet;
            }
          }
        }

        if (!connectorNode) {
          std::string suggestedName;
          if (fan && component == *fan) {
            suggestedName = baseName + " Fan Outlet Node";
          } else if (cooling && component == *cooling) {
            suggestedName = baseName + " Cooling Coil Outlet Node";
          } else {
            suggestedName = baseName + " Heating Coil Outlet Node";
          }
          connectorNode = model().getOrCreateTransientByName<Node>(suggestedName);
        }

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(vrfTerminalAirOutletPort(component),
                                                                                 connectorNode->handle(), false));
        trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(vrfTerminalAirInletPort(downstream),
                                                                                  connectorNode->handle(), false));
      }

      if (nodeWiringChanged && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:TerminalUnit:VariableRefrigerantFlow '" + baseName + "'.");
      }

      return changed;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
