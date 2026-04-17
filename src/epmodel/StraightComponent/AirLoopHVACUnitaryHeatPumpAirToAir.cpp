/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir.hpp"
#include "StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Node.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirLoopHVAC_UnitaryHeatPump_AirToAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

namespace {

bool isUnitaryHeatPumpAirPathComponent(const HVACComponent& component) {
  return static_cast<bool>(component.optionalCast<StraightComponent>()) || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
}

unsigned unitaryHeatPumpAirInletPort(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->inletPort();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airInletPort();
  }
  return 0u;
}

unsigned unitaryHeatPumpAirOutletPort(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->outletPort();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airOutletPort();
  }
  return 0u;
}

boost::optional<Node> unitaryHeatPumpAirOutletNode(const HVACComponent& component) {
  const auto outletPort = unitaryHeatPumpAirOutletPort(component);
  if (outletPort == 0u) {
    return boost::none;
  }
  return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
}

}  // namespace

AirLoopHVACUnitaryHeatPumpAirToAir::AirLoopHVACUnitaryHeatPumpAirToAir(const Model& model)
  : StraightComponent(AirLoopHVACUnitaryHeatPumpAirToAir::iddObjectType(), model) {
  ScheduleConstant alwaysOn(model);
  OS_ASSERT(alwaysOn.setValue(1.0));
  OS_ASSERT(setAvailabilitySchedule(alwaysOn));
  // Mirror model constructor behavior for required scalar initialization.
  OS_ASSERT(setDXHeatingCoilSizingRatio(1.0));
}

AirLoopHVACUnitaryHeatPumpAirToAir::AirLoopHVACUnitaryHeatPumpAirToAir(
  const Model& model, Schedule& availabilitySchedule, HVACComponent& supplyFan, HVACComponent& heatingCoil, HVACComponent& coolingCoil,
  HVACComponent& supplementalHeatingCoil)
  : AirLoopHVACUnitaryHeatPumpAirToAir(model) {
  bool ok = true;
  ok = setAvailabilitySchedule(availabilitySchedule);
  OS_ASSERT(ok);
  ok = setSupplyAirFan(supplyFan);
  OS_ASSERT(ok);
  ok = setHeatingCoil(heatingCoil);
  OS_ASSERT(ok);
  ok = setCoolingCoil(coolingCoil);
  OS_ASSERT(ok);
  ok = setSupplementalHeatingCoil(supplementalHeatingCoil);
  OS_ASSERT(ok);
}

AirLoopHVACUnitaryHeatPumpAirToAir::AirLoopHVACUnitaryHeatPumpAirToAir(
  std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirLoopHVACUnitaryHeatPumpAirToAir::iddObjectType() {
  return IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::addToNode(Node& node) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->addToNode(node);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir::validFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement);
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir::validDehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType);
}

Schedule AirLoopHVACUnitaryHeatPumpAirToAir::availabilitySchedule() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->availabilitySchedule();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setAvailabilitySchedule(schedule);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFlowRateDuringCoolingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFlowRateDuringCoolingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
    supplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeSupplyAirFlowRateDuringCoolingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFlowRateDuringHeatingOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFlowRateDuringHeatingOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFlowRateDuringHeatingOperation(double n2) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(n2);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeSupplyAirFlowRateDuringHeatingOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
}

boost::optional<ThermalZone> AirLoopHVACUnitaryHeatPumpAirToAir::controllingZone() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->controllingZone();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setControllingZone(ThermalZone& zone) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setControllingZone(zone);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetControllingZone() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetControllingZone();
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFan() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFan();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFan(HVACComponent& hvacComponent) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFan(hvacComponent);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir::heatingCoil() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->heatingCoil();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setHeatingCoil(HVACComponent& hvacComponent) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setHeatingCoil(hvacComponent);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir::coolingCoil() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->coolingCoil();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setCoolingCoil(HVACComponent& hvacComponent) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setCoolingCoil(hvacComponent);
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir::supplementalHeatingCoil() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplementalHeatingCoil();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplementalHeatingCoil(HVACComponent& hvacComponent) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplementalHeatingCoil(hvacComponent);
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAir::fanOutletNode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->fanOutletNode();
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAir::coolingCoilOutletNode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->coolingCoilOutletNode();
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAir::heatingCoilOutletNode() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->heatingCoilOutletNode();
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
    maximumSupplyAirTemperaturefromSupplementalHeater);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
}

double AirLoopHVACUnitaryHeatPumpAirToAir::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir::fanPlacement() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->fanPlacement();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isFanPlacementDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isFanPlacementDefaulted();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setFanPlacement(const std::string& fanPlacement) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setFanPlacement(fanPlacement);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetFanPlacement() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetFanPlacement();
}

boost::optional<Schedule> AirLoopHVACUnitaryHeatPumpAirToAir::supplyAirFanOperatingModeSchedule() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->supplyAirFanOperatingModeSchedule();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetSupplyAirFanOperatingModeSchedule() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetSupplyAirFanOperatingModeSchedule();
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir::dehumidificationControlType() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->dehumidificationControlType();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::isDehumidificationControlTypeDefaulted() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->isDehumidificationControlTypeDefaulted();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setDehumidificationControlType(dehumidificationControlType);
}

void AirLoopHVACUnitaryHeatPumpAirToAir::resetDehumidificationControlType() {
  getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->resetDehumidificationControlType();
}

double AirLoopHVACUnitaryHeatPumpAirToAir::dXHeatingCoilSizingRatio() const {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->dXHeatingCoilSizingRatio();
}

bool AirLoopHVACUnitaryHeatPumpAirToAir::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return getImpl<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned AirLoopHVACUnitaryHeatPumpAirToAir_Impl::inletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AirInletNodeName;
}

unsigned AirLoopHVACUnitaryHeatPumpAirToAir_Impl::outletPort() const {
  return openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AirOutletNodeName;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::addToNode(Node& node) {
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

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::doCanonicalize(LoadContext& context) {
  repairContainedAirPath(context);
}

std::vector<ModelObject> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::children() const {
  std::vector<ModelObject> result;

  if (auto supplyFan = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanName)) {
    result.emplace_back(*supplyFan);
  }
  if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingCoilName)) {
    result.emplace_back(*heatingCoil);
  }
  if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingCoilName)) {
    result.emplace_back(*coolingCoil);
  }
  if (auto supplementalHeatingCoil = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
        openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilName)) {
    result.emplace_back(*supplementalHeatingCoil);
  }

  return result;
}

Schedule AirLoopHVACUnitaryHeatPumpAirToAir_Impl::availabilitySchedule() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AvailabilityScheduleName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AvailabilityScheduleName, "AirLoopHVACUnitaryHeatPumpAirToAir",
                     "Availability", schedule);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFlowRateDuringCoolingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFlowRateDuringHeatingOperation() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFlowRateDuringHeatingOperation(double n2) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, n2);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, "autosize"));
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
  double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate,
                   supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, ""));
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, "autosize"));
}

boost::optional<ThermalZone> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::controllingZone() const {
  return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::ControllingZoneorThermostatLocation);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setControllingZone(ThermalZone& zone) {
  return setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::ControllingZoneorThermostatLocation, zone.handle());
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetControllingZone() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::ControllingZoneorThermostatLocation, ""));
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFan() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFan(HVACComponent& hvacComponent) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanName, hvacComponent.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir_Impl::heatingCoil() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingCoilName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setHeatingCoil(HVACComponent& hvacComponent) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingCoilName, hvacComponent.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir_Impl::coolingCoil() const {
  auto value =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingCoilName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setCoolingCoil(HVACComponent& hvacComponent) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingCoilName, hvacComponent.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

HVACComponent AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplementalHeatingCoil() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilName);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplementalHeatingCoil(HVACComponent& hvacComponent) {
  const bool result = setPointer(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilName, hvacComponent.handle());
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::fanOutletNode() const {
  auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanName);
  auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
  if (!fan) {
    return boost::none;
  }

  auto fanOutlet = fan->outletModelObject();
  return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::coolingCoilOutletNode() const {
  auto coolingObject =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingCoilName);
  auto cooling =
    (coolingObject && isUnitaryHeatPumpAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
  if (!cooling) {
    return boost::none;
  }

  return unitaryHeatPumpAirOutletNode(*cooling);
}

boost::optional<Node> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::heatingCoilOutletNode() const {
  auto heatingObject =
    getObject<ModelObject>().getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingCoilName);
  auto heating =
    (heatingObject && isUnitaryHeatPumpAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
  if (!heating) {
    return boost::none;
  }

  return unitaryHeatPumpAirOutletNode(*heating);
}

boost::optional<double> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
  return getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
  if (auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
  double maximumSupplyAirTemperaturefromSupplementalHeater) {
  const bool result = setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                maximumSupplyAirTemperaturefromSupplementalHeater);
  OS_ASSERT(result);
  return result;
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "autosize"));
}

double AirLoopHVACUnitaryHeatPumpAirToAir_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                               true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                   maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
  OS_ASSERT(
    setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, ""));
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir_Impl::fanPlacement() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isFanPlacementDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setFanPlacement(const std::string& fanPlacement) {
  const bool result = setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, fanPlacement);
  if (result) {
    maintainContainedAirPath();
  }
  return result;
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetFanPlacement() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, ""));
  maintainContainedAirPath();
}

boost::optional<Schedule> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::supplyAirFanOperatingModeSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanOperatingModeScheduleName);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
  return setSchedule(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanOperatingModeScheduleName,
                     "AirLoopHVACUnitaryHeatPumpAirToAir", "Supply Air Fan Operating Mode", schedule);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetSupplyAirFanOperatingModeSchedule() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanOperatingModeScheduleName, ""));
}

std::string AirLoopHVACUnitaryHeatPumpAirToAir_Impl::dehumidificationControlType() const {
  const auto value = getString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::isDehumidificationControlTypeDefaulted() const {
  return isEmpty(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
  return setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, dehumidificationControlType);
}

void AirLoopHVACUnitaryHeatPumpAirToAir_Impl::resetDehumidificationControlType() {
  OS_ASSERT(setString(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, ""));
}

double AirLoopHVACUnitaryHeatPumpAirToAir_Impl::dXHeatingCoilSizingRatio() const {
  const auto value = getDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DXHeatingCoilSizingRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
  return setDouble(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::maintainContainedAirPath() {
  return reconcileContainedAirPath(false, nullptr);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::repairContainedAirPath(LoadContext& context) {
  return reconcileContainedAirPath(true, &context);
}

bool AirLoopHVACUnitaryHeatPumpAirToAir_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
  auto thisObject = getObject<ModelObject>();
  if (!thisObject.name()) {
    thisObject.createName();
  }

  auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanName);
  auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingCoilName);
  auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingCoilName);
  auto supplementalObject =
    thisObject.getModelObjectTarget<HVACComponent>(openstudio::AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilName);

  auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
  auto heating =
    (heatingObject && isUnitaryHeatPumpAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
  auto cooling =
    (coolingObject && isUnitaryHeatPumpAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
  auto supplemental = (supplementalObject && isUnitaryHeatPumpAirPathComponent(*supplementalObject))
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

  const bool blowThrough = openstudio::istringEqual(fanPlacement(), "BlowThrough");

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
    const auto inletPort = unitaryHeatPumpAirInletPort(component);
    const auto outletPort = unitaryHeatPumpAirOutletPort(component);
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
          const auto downstreamInletPort = unitaryHeatPumpAirInletPort(downstream);
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
      const auto downstreamInletPort = unitaryHeatPumpAirInletPort(downstream);
      trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(downstreamInletPort, connectorNode->handle(), false));
    }

    trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(outletPort, downstreamNode.handle(), false));
    upstreamNode = downstreamNode;
  }

  if (nodeWiringChanged && context) {
    detail::addLoadInfo(*context, "Reconciled internal node wiring for AirLoopHVAC:UnitaryHeatPump:AirToAir '" + baseName + "'.");
  }

  return changed;
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::validFanPlacementValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpAirToAir::validFanPlacementValues();
}

std::vector<std::string> AirLoopHVACUnitaryHeatPumpAirToAir_Impl::validDehumidificationControlTypeValues() const {
  return openstudio::epmodel::AirLoopHVACUnitaryHeatPumpAirToAir::validDehumidificationControlTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
