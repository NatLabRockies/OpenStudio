/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl.hpp"

#include "HVACComponent.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Mixer/Mixer.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/OutdoorAirMixer.hpp"
#include "ModelObject/OutdoorAirMixer_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    bool isChangeoverBypassAirPathComponent(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<StraightComponent>()) || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
    }

    unsigned changeoverBypassAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned changeoverBypassAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> changeoverBypassAirOutletNode(const HVACComponent& component) {
      const auto outletPort = changeoverBypassAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

  }  // namespace

  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model)
    : StraightComponent(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType(), model) {
    // Renaming an existing unitary does not rename its internal bypass nodes.
    // Advance past that retained default-name prefix before owner maintenance
    // creates another internal path.
    auto internalNodeNameIsTaken = [&model](const std::string& unitaryName) {
      return static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Bypass Duct Mixer Node"))
             || static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Bypass Duct Splitter Node"))
             || static_cast<bool>(model.getConcreteModelObjectByName<Node>(unitaryName + " Mixed Air Node"));
    };
    while (internalNodeNameIsTaken(nameString())) {
      OS_ASSERT(setName(model.nextName(iddObjectType(), false)));
    }

    // Keep required scalar fields populated for strict non-optional getters.
    OS_ASSERT(setSupplyAirFanPlacement("DrawThrough"));
    OS_ASSERT(setPriorityControlMode("ZonePriority"));
    OS_ASSERT(setMinimumOutletAirTemperatureDuringCoolingOperation(8.0));
    OS_ASSERT(setMaximumOutletAirTemperatureDuringHeatingOperation(50.0));
    OS_ASSERT(setDehumidificationControlType("None"));
    OS_ASSERT(setMinimumRuntimeBeforeOperatingModeChange(0.0));

    // Mirror model default constructor autosize behavior for scalar flow-rate fields.
    autosizeSystemAirFlowRateDuringCoolingOperation();
    autosizeSystemAirFlowRateDuringHeatingOperation();
    autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
    autosizeOutdoorAirFlowRateDuringCoolingOperation();
    autosizeOutdoorAirFlowRateDuringHeatingOperation();
    autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(const Model& model, const HVACComponent& fan,
                                                                                               const HVACComponent& coolingCoil,
                                                                                               const HVACComponent& heatingCoil)
    : AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(model) {
    bool ok = true;
    ok = setSupplyAirFan(fan);
    OS_ASSERT(ok);
    ok = setCoolingCoil(coolingCoil);
    OS_ASSERT(ok);
    ok = setHeatingCoil(heatingCoil);
    OS_ASSERT(ok);
  }

  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass(
    std::shared_ptr<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType() {
    return IddObjectType::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass;
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::priorityControlModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode);
  }

  std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType);
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::addToNode(Node& node) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::availabilitySchedule() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->availabilitySchedule();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setAvailabilitySchedule(schedule);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::resetAvailabilitySchedule() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::systemAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->systemAirFlowRateDuringCoolingOperation();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isSystemAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isSystemAirFlowRateDuringCoolingOperationAutosized();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSystemAirFlowRateDuringCoolingOperation(double systemAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSystemAirFlowRateDuringCoolingOperation(
      systemAirFlowRateDuringCoolingOperation);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeSystemAirFlowRateDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeSystemAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::systemAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->systemAirFlowRateDuringHeatingOperation();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isSystemAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isSystemAirFlowRateDuringHeatingOperationAutosized();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSystemAirFlowRateDuringHeatingOperation(double systemAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSystemAirFlowRateDuringHeatingOperation(
      systemAirFlowRateDuringHeatingOperation);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeSystemAirFlowRateDuringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeSystemAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::systemAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->systemAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double systemAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(
      systemAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
      outdoorAirFlowRateDuringCoolingOperation);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
      outdoorAirFlowRateDuringHeatingOperation);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<Schedule> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::outdoorAirFlowRateMultiplierSchedule() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->outdoorAirFlowRateMultiplierSchedule();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setOutdoorAirFlowRateMultiplierSchedule(Schedule& outdoorAirFlowRateMultiplierSchedule) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setOutdoorAirFlowRateMultiplierSchedule(
      outdoorAirFlowRateMultiplierSchedule);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::resetOutdoorAirFlowRateMultiplierSchedule() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->resetOutdoorAirFlowRateMultiplierSchedule();
  }

  HVACComponent AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFan() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->supplyAirFan();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSupplyAirFan(const HVACComponent& fansCVandOnOff) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSupplyAirFan(fansCVandOnOff);
  }

  std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanPlacement() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->supplyAirFanPlacement();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSupplyAirFanPlacement(supplyAirFanPlacement);
  }

  boost::optional<Schedule> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  HVACComponent AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::coolingCoil() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->coolingCoil();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setCoolingCoil(const HVACComponent& coolingCoilName) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setCoolingCoil(coolingCoilName);
  }

  HVACComponent AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::heatingCoil() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->heatingCoil();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setHeatingCoil(const HVACComponent& heatingCoilName) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setHeatingCoil(heatingCoilName);
  }

  boost::optional<Node> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::fanOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->fanOutletNode();
  }

  boost::optional<Node> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::coolingCoilOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->coolingCoilOutletNode();
  }

  boost::optional<Node> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::heatingCoilOutletNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->heatingCoilOutletNode();
  }

  std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::priorityControlMode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->priorityControlMode();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setPriorityControlMode(const std::string& priorityControlMode) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setPriorityControlMode(priorityControlMode);
  }

  double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::minimumOutletAirTemperatureDuringCoolingOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->minimumOutletAirTemperatureDuringCoolingOperation();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setMinimumOutletAirTemperatureDuringCoolingOperation(
    double minimumOutletAirTemperatureDuringCoolingOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setMinimumOutletAirTemperatureDuringCoolingOperation(
      minimumOutletAirTemperatureDuringCoolingOperation);
  }

  double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::maximumOutletAirTemperatureDuringHeatingOperation() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->maximumOutletAirTemperatureDuringHeatingOperation();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setMaximumOutletAirTemperatureDuringHeatingOperation(
    double maximumOutletAirTemperatureDuringHeatingOperation) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setMaximumOutletAirTemperatureDuringHeatingOperation(
      maximumOutletAirTemperatureDuringHeatingOperation);
  }

  std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::dehumidificationControlType() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->dehumidificationControlType();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::minimumRuntimeBeforeOperatingModeChange() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->minimumRuntimeBeforeOperatingModeChange();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setMinimumRuntimeBeforeOperatingModeChange(double runtime) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setMinimumRuntimeBeforeOperatingModeChange(runtime);
  }

  unsigned AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::plenumorMixerAirPort() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->plenumorMixerAirPort();
  }

  Node AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::plenumorMixerNode() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->plenumorMixerNode();
  }

  boost::optional<Mixer> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::plenumorMixer() const {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->plenumorMixer();
  }

  bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::setPlenumorMixer(const Mixer& returnPathComponent) {
    return getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->setPlenumorMixer(returnPathComponent);
  }

  void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::resetPlenumorMixer() {
    getImpl<detail::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl>()->resetPlenumorMixer();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::inletPort() const {
      return openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AirInletNodeName;
    }

    unsigned AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outletPort() const {
      return openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AirOutletNodeName;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::addToNode(Node& node) {
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

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    std::vector<ModelObject> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::children() const {
      std::vector<ModelObject> result;

      if (auto supplyFan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanName)) {
        result.emplace_back(*supplyFan);
      }
      if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilName)) {
        result.emplace_back(*coolingCoil);
      }
      if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
            openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilName)) {
        result.emplace_back(*heatingCoil);
      }

      return result;
    }

    boost::optional<Schedule> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AvailabilityScheduleName);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AvailabilityScheduleName,
                         "AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Availability Schedule", schedule);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AvailabilityScheduleName, ""));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::systemAirFlowRateDuringCoolingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isSystemAirFlowRateDuringCoolingOperationAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool
      AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSystemAirFlowRateDuringCoolingOperation(double systemAirFlowRateDuringCoolingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate,
                       systemAirFlowRateDuringCoolingOperation);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeSystemAirFlowRateDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::systemAirFlowRateDuringHeatingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isSystemAirFlowRateDuringHeatingOperationAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool
      AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSystemAirFlowRateDuringHeatingOperation(double systemAirFlowRateDuringHeatingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate,
                       systemAirFlowRateDuringHeatingOperation);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeSystemAirFlowRateDuringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::systemAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(
      double systemAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate,
                       systemAirFlowRateWhenNoCoolingorHeatingisNeeded);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      double outdoorAirFlowRateDuringCoolingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate,
                       outdoorAirFlowRateDuringCoolingOperation);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      double outdoorAirFlowRateDuringHeatingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate,
                       outdoorAirFlowRateDuringHeatingOperation);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate,
                       outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<Schedule> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::outdoorAirFlowRateMultiplierSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirFlowRateMultiplierScheduleName);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setOutdoorAirFlowRateMultiplierSchedule(Schedule& outdoorAirFlowRateMultiplierSchedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirFlowRateMultiplierScheduleName,
                         "AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Outdoor Air Flow Rate Multiplier Schedule",
                         outdoorAirFlowRateMultiplierSchedule);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::resetOutdoorAirFlowRateMultiplierSchedule() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirFlowRateMultiplierScheduleName, ""));
    }

    HVACComponent AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::supplyAirFan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSupplyAirFan(const HVACComponent& fansCVandOnOff) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanName, fansCVandOnOff.handle());
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::supplyAirFanPlacement() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
      const bool result = setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement, supplyAirFanPlacement);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Schedule> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanOperatingModeScheduleName,
                         "AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass", "Supply Air Fan Operating Mode Schedule", schedule);
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::resetSupplyAirFanOperatingModeSchedule() {
      OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanOperatingModeScheduleName, ""));
    }

    HVACComponent AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::coolingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setCoolingCoil(const HVACComponent& coolingCoilName) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilName, coolingCoilName.handle());
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::heatingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setHeatingCoil(const HVACComponent& heatingCoilName) {
      const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilName, heatingCoilName.handle());
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Node> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::coolingCoilOutletNode() const {
      auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilName);
      auto cooling =
        (coolingObject && isChangeoverBypassAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      if (!cooling) {
        return boost::none;
      }

      return changeoverBypassAirOutletNode(*cooling);
    }

    boost::optional<Node> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::heatingCoilOutletNode() const {
      auto heatingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilName);
      auto heating =
        (heatingObject && isChangeoverBypassAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      if (!heating) {
        return boost::none;
      }

      return changeoverBypassAirOutletNode(*heating);
    }

    std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::priorityControlMode() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setPriorityControlMode(const std::string& priorityControlMode) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode, priorityControlMode);
    }

    double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::minimumOutletAirTemperatureDuringCoolingOperation() const {
      const auto value =
        getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumOutletAirTemperatureDuringCoolingOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setMinimumOutletAirTemperatureDuringCoolingOperation(
      double minimumOutletAirTemperatureDuringCoolingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumOutletAirTemperatureDuringCoolingOperation,
                       minimumOutletAirTemperatureDuringCoolingOperation);
    }

    double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::maximumOutletAirTemperatureDuringHeatingOperation() const {
      const auto value =
        getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MaximumOutletAirTemperatureDuringHeatingOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setMaximumOutletAirTemperatureDuringHeatingOperation(
      double maximumOutletAirTemperatureDuringHeatingOperation) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MaximumOutletAirTemperatureDuringHeatingOperation,
                       maximumOutletAirTemperatureDuringHeatingOperation);
    }

    std::string AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType, dehumidificationControlType);
    }

    double AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::minimumRuntimeBeforeOperatingModeChange() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumRuntimeBeforeOperatingModeChange, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setMinimumRuntimeBeforeOperatingModeChange(double runtime) {
      return setDouble(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumRuntimeBeforeOperatingModeChange, runtime);
    }

    unsigned AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::plenumorMixerAirPort() const {
      return openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PlenumorMixerInletNodeName;
    }

    Node AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::plenumorMixerNode() const {
      if (auto node = resolvedNodeTarget(plenumorMixerAirPort())) {
        return *node;
      }
      return model().getOrCreateTransientByName<Node>(getObject<ModelObject>().nameString() + " Plenum or Mixer Inlet Node");
    }

    boost::optional<Mixer> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::plenumorMixer() const {
      auto node = resolvedNodeTarget(plenumorMixerAirPort());
      if (!node) {
        return boost::none;
      }

      for (const auto& zoneMixer : model().getConcreteModelObjects<AirLoopHVACZoneMixer>()) {
        const auto inlets = zoneMixer.inletModelObjects();
        if (std::ranges::find(inlets, node->cast<ModelObject>()) != inlets.end()) {
          return zoneMixer.cast<Mixer>();
        }
      }
      return boost::none;
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::setPlenumorMixer(const Mixer& returnPathComponent) {
      auto zoneMixer = returnPathComponent.optionalCast<AirLoopHVACZoneMixer>();
      auto thisLoop = getObject<AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass>().airLoopHVAC();
      auto mixerLoop = zoneMixer ? zoneMixer->airLoopHVAC() : boost::none;
      if (!(zoneMixer && thisLoop && mixerLoop && (*thisLoop == *mixerLoop))) {
        return false;
      }

      resetPlenumorMixer();
      auto node = plenumorMixerNode();
      const auto branchIndex = zoneMixer->nextBranchIndex();
      if (!zoneMixer->setInletModelObject(branchIndex, node)) {
        return false;
      }
      if (!setPointer(plenumorMixerAirPort(), node.handle(), false)) {
        zoneMixer->removePortForBranch(branchIndex);
        return false;
      }
      return true;
    }

    void AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::resetPlenumorMixer() {
      auto node = resolvedNodeTarget(plenumorMixerAirPort());
      if (node) {
        for (auto zoneMixer : model().getConcreteModelObjects<AirLoopHVACZoneMixer>()) {
          const auto inlets = zoneMixer.inletModelObjects();
          const auto inlet = std::ranges::find(inlets, node->cast<ModelObject>());
          if (inlet != inlets.end()) {
            zoneMixer.removePortForBranch(static_cast<unsigned>(std::distance(inlets.begin(), inlet)));
            break;
          }
        }
      }
      setPointer(plenumorMixerAirPort(), Handle(), false);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanName);
      auto coolingObject =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilName);
      auto heatingObject =
        thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilName);

      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto cooling =
        (coolingObject && isChangeoverBypassAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      auto heating =
        (heatingObject && isChangeoverBypassAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
        return value;
      };

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
      trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
      trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));

      const auto synchronizeObjectType = [&](unsigned objectTypeField, const boost::optional<HVACComponent>& component) {
        const auto currentType = thisObject.getString(objectTypeField, true);
        const auto expectedType = component ? boost::optional<std::string>(component->iddObject().name()) : boost::optional<std::string>();
        if (expectedType) {
          if (!currentType || !openstudio::istringEqual(*currentType, *expectedType)) {
            OS_ASSERT(thisObject.setString(objectTypeField, *expectedType));
            changed = true;
          }
        } else if (currentType && !currentType->empty()) {
          OS_ASSERT(thisObject.setString(objectTypeField, ""));
          changed = true;
        }
      };
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanObjectType,
                            fan ? boost::optional<HVACComponent>(fan->cast<HVACComponent>()) : boost::none);
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilObjectType,
                            coolingObject ? boost::optional<HVACComponent>(*coolingObject) : boost::none);
      synchronizeObjectType(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilObjectType,
                            heatingObject ? boost::optional<HVACComponent>(*heatingObject) : boost::none);

      auto bypassMixerNode = resolvedOrCreatedNodeTarget(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName,
                                                         baseName + " Bypass Duct Mixer Node");
      auto bypassSplitterNode = resolvedOrCreatedNodeTarget(
        openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctSplitterNodeName, baseName + " Bypass Duct Splitter Node");

      auto outdoorAirMixer =
        thisObject.getModelObjectTarget<OutdoorAirMixer>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName);
      if (!outdoorAirMixer) {
        auto createdMixer = OutdoorAirMixer(model());
        createdMixer.setName(baseName + " Outdoor Air Mixer");
        OS_ASSERT(
          thisObject.setPointer(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName, createdMixer.handle()));
        outdoorAirMixer = createdMixer;
        changed = true;
      }
      OS_ASSERT(outdoorAirMixer);

      const auto currentMixerType =
        thisObject.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerObjectType, true);
      if (!currentMixerType || !openstudio::istringEqual(*currentMixerType, outdoorAirMixer->iddObject().name())) {
        OS_ASSERT(thisObject.setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerObjectType,
                                       outdoorAirMixer->iddObject().name()));
        changed = true;
      }

      auto mixerImpl = outdoorAirMixer->getImpl<detail::OutdoorAirMixer_Impl>();
      auto mixedAirNode = mixerImpl->mixedAirNode();
      if (!mixedAirNode) {
        mixedAirNode = model().getOrCreateTransientByName<Node>(baseName + " Mixed Air Node");
        OS_ASSERT(mixerImpl->setMixedAirNode(*mixedAirNode));
        changed = true;
      }
      auto outdoorAirNode = mixerImpl->outdoorAirNode();
      if (!outdoorAirNode) {
        outdoorAirNode = model().getOrCreateTransientByName<Node>(baseName + " OA Node");
        OS_ASSERT(mixerImpl->setOutdoorAirNode(*outdoorAirNode));
        changed = true;
      }
      auto reliefAirNode = mixerImpl->reliefAirNode();
      if (!reliefAirNode) {
        reliefAirNode = model().getOrCreateTransientByName<Node>(baseName + " Relief Air Node");
        OS_ASSERT(mixerImpl->setReliefAirNode(*reliefAirNode));
        changed = true;
      }
      if (!mixerImpl->returnAirNode() || (*mixerImpl->returnAirNode() != bypassMixerNode)) {
        OS_ASSERT(mixerImpl->setReturnAirNode(bypassMixerNode));
        changed = true;
      }

      bool outdoorAirNodeListed = false;
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
        for (const auto& group : object.extensibleGroups()) {
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }
          auto nodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
          if (nodeName && openstudio::istringEqual(*nodeName, outdoorAirNode->nameString())) {
            outdoorAirNodeListed = true;
            break;
          }
        }
        if (outdoorAirNodeListed) {
          break;
        }
      }
      if (!outdoorAirNodeListed) {
        auto nodeList = ModelObject::create(openstudio::IddObjectType::OutdoorAir_NodeList, model());
        auto group = nodeList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
        OS_ASSERT(group);
        OS_ASSERT(group->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, outdoorAirNode->nameString()));
        changed = true;
      }

      if (!fan && !cooling && !heating) {
        return changed;
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
        return baseName + " Heating Coil Outlet Node";
      };

      Node upstreamNode = *mixedAirNode;
      for (std::size_t i = 0; i < orderedComponents.size(); ++i) {
        auto component = orderedComponents[i];
        const auto inletPort = changeoverBypassAirInletPort(component);
        const auto outletPort = changeoverBypassAirOutletPort(component);
        if ((inletPort == 0u) || (outletPort == 0u)) {
          continue;
        }

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(inletPort, upstreamNode.handle(), false));

        Node downstreamNode = bypassSplitterNode;
        if ((i + 1u) < orderedComponents.size()) {
          auto downstream = orderedComponents[i + 1u];
          boost::optional<Node> connectorNode;

          if (allowChildNodeRecovery) {
            if (auto currentOutlet = component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort)) {
              const auto downstreamInletPort = changeoverBypassAirInletPort(downstream);
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
          const auto downstreamInletPort = changeoverBypassAirInletPort(downstream);
          trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(downstreamInletPort, connectorNode->handle(), false));
        }

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(outletPort, downstreamNode.handle(), false));
        upstreamNode = downstreamNode;
      }

      if (nodeWiringChanged && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass '" + baseName + "'.");
      }

      return changed;
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::supplyAirFanPlacementValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::supplyAirFanPlacementValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::priorityControlModeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::priorityControlModeValues();
    }

    std::vector<std::string> AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::dehumidificationControlTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
