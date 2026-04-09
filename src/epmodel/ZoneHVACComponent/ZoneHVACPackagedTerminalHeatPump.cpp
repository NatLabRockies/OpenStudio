/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
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
#include <utilities/idd/ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    // PTHP owns a small, explicit set of child families in its serial air
    // path: straight air-side components plus water supplemental heaters.
    // Keeping the type checks here makes the supported child set obvious in the
    // one file that owns the topology instead of extending a shared base helper
    // that would keep growing with every new compound family.
    bool isPackagedTerminalHeatPumpAirPathComponent(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<StraightComponent>())
             || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
    }

    unsigned packagedTerminalHeatPumpAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned packagedTerminalHeatPumpAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> packagedTerminalHeatPumpAirOutletNode(const HVACComponent& component) {
      const auto outletPort = packagedTerminalHeatPumpAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

  }  // namespace

  ZoneHVACPackagedTerminalHeatPump::ZoneHVACPackagedTerminalHeatPump(const Model& model)
    : ZoneHVACComponent(ZoneHVACPackagedTerminalHeatPump::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));
  }

  ZoneHVACPackagedTerminalHeatPump::ZoneHVACPackagedTerminalHeatPump(std::shared_ptr<detail::ZoneHVACPackagedTerminalHeatPump_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACPackagedTerminalHeatPump::iddObjectType() {
    return IddObjectType::ZoneHVAC_PackagedTerminalHeatPump;
  }

  unsigned ZoneHVACPackagedTerminalHeatPump::inletPort() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->inletPort();
  }

  unsigned ZoneHVACPackagedTerminalHeatPump::outletPort() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outletPort();
  }

  std::vector<std::string> ZoneHVACPackagedTerminalHeatPump::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACPackagedTerminalHeatPump::validFanPlacementValues() {
    return fanPlacementValues();
  }

  Schedule ZoneHVACPackagedTerminalHeatPump::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setAvailabilitySchedule(schedule);
  }

  std::vector<ModelObject> ZoneHVACPackagedTerminalHeatPump::children() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->children();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
      supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(
      supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalHeatPump::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
      noLoadSupplyAirFlowRateControlSetToLowSpeed);
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
      outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
      outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool
    ZoneHVACPackagedTerminalHeatPump::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  double ZoneHVACPackagedTerminalHeatPump::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetHeatingConvergenceTolerance() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetHeatingConvergenceTolerance();
  }

  double ZoneHVACPackagedTerminalHeatPump::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  double ZoneHVACPackagedTerminalHeatPump::coolingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->coolingConvergenceTolerance();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isCoolingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isCoolingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetCoolingConvergenceTolerance() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetCoolingConvergenceTolerance();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool
    ZoneHVACPackagedTerminalHeatPump::setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
      maximumSupplyAirTemperaturefromSupplementalHeater);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACPackagedTerminalHeatPump::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACPackagedTerminalHeatPump::fanPlacement() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->fanPlacement();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetFanPlacement() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetFanPlacement();
  }

  HVACComponent ZoneHVACPackagedTerminalHeatPump::supplyAirFan() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFan();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFan(const HVACComponent& supplyAirFan) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFan(supplyAirFan);
  }

  Schedule ZoneHVACPackagedTerminalHeatPump::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  HVACComponent ZoneHVACPackagedTerminalHeatPump::heatingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->heatingCoil();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setHeatingCoil(heatingCoil);
  }

  HVACComponent ZoneHVACPackagedTerminalHeatPump::coolingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->coolingCoil();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setCoolingCoil(coolingCoil);
  }

  HVACComponent ZoneHVACPackagedTerminalHeatPump::supplementalHeatingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplementalHeatingCoil();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplementalHeatingCoil(supplementalHeatingCoil);
  }

  boost::optional<Node> ZoneHVACPackagedTerminalHeatPump::fanOutletNode() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACPackagedTerminalHeatPump::coolingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->coolingCoilOutletNode();
  }

  boost::optional<Node> ZoneHVACPackagedTerminalHeatPump::heatingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->heatingCoilOutletNode();
  }

  double ZoneHVACPackagedTerminalHeatPump::dXHeatingCoilSizingRatio() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->dXHeatingCoilSizingRatio();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
  }

  namespace detail {

    std::vector<ModelObject> ZoneHVACPackagedTerminalHeatPump_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto child = getObject<ModelObject>().getTarget(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName)) {
        if (auto object = child->optionalCast<ModelObject>()) {
          result.push_back(*object);
        }
      }
      if (auto child = getObject<ModelObject>().getTarget(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName)) {
        if (auto object = child->optionalCast<ModelObject>()) {
          result.push_back(*object);
        }
      }
      if (auto child = getObject<ModelObject>().getTarget(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName)) {
        if (auto object = child->optionalCast<ModelObject>()) {
          result.push_back(*object);
        }
      }
      if (auto child = getObject<ModelObject>().getTarget(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilName)) {
        if (auto object = child->optionalCast<ModelObject>()) {
          result.push_back(*object);
        }
      }
      return result;
    }

    unsigned ZoneHVACPackagedTerminalHeatPump_Impl::inletPort() const {
      return ZoneHVAC_PackagedTerminalHeatPumpFields::AirInletNodeName;
    }

    unsigned ZoneHVACPackagedTerminalHeatPump_Impl::outletPort() const {
      return ZoneHVAC_PackagedTerminalHeatPumpFields::AirOutletNodeName;
    }

    Schedule ZoneHVACPackagedTerminalHeatPump_Impl::availabilitySchedule() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_PackagedTerminalHeatPumpFields::AvailabilityScheduleName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_PackagedTerminalHeatPumpFields::AvailabilityScheduleName,
                                           "ZoneHVACPackagedTerminalHeatPump", "Availability", schedule);
    }

    HVACComponent ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFan() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFan(const HVACComponent& supplyAirFan) {
      if ((supplyAirFan.model() != model()) || !supplyAirFan.optionalCast<StraightComponent>()) {
        return false;
      }

      const auto iddObjectType = supplyAirFan.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Fan_ConstantVolume) && (iddObjectType != IddObjectType::OS_Fan_OnOff)
          && (iddObjectType != IddObjectType::OS_Fan_SystemModel) && (iddObjectType != IddObjectType::Fan_ConstantVolume)
          && (iddObjectType != IddObjectType::Fan_OnOff) && (iddObjectType != IddObjectType::Fan_SystemModel)) {
        return false;
      }
      const bool result = setPointer(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName, supplyAirFan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    Schedule ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFanOperatingModeSchedule() const {
      auto child =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanOperatingModeScheduleName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanOperatingModeScheduleName,
                                           "ZoneHVACPackagedTerminalHeatPump", "Supply Air Fan Operating Mode", schedule);
    }

    HVACComponent ZoneHVACPackagedTerminalHeatPump_Impl::heatingCoil() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if ((heatingCoil.model() != model()) || !heatingCoil.optionalCast<StraightComponent>()) {
        return false;
      }

      const auto iddObjectType = heatingCoil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_DX_SingleSpeed) && (iddObjectType != IddObjectType::OS_Coil_Heating_DX_VariableSpeed)
          && (iddObjectType != IddObjectType::Coil_Heating_DX_SingleSpeed)
          && (iddObjectType != IddObjectType::Coil_Heating_DX_VariableSpeed)) {
        return false;
      }
      const bool result = setPointer(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName, heatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent ZoneHVACPackagedTerminalHeatPump_Impl::coolingCoil() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if ((coolingCoil.model() != model()) || !coolingCoil.optionalCast<StraightComponent>()) {
        return false;
      }

      const auto iddObjectType = coolingCoil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Cooling_DX_SingleSpeed)
          && (iddObjectType != IddObjectType::OS_Coil_Cooling_DX_VariableSpeed)
          && (iddObjectType != IddObjectType::OS_CoilSystem_Cooling_DX_HeatExchangerAssisted)
          && (iddObjectType != IddObjectType::OS_Coil_Cooling_DX) && (iddObjectType != IddObjectType::Coil_Cooling_DX_SingleSpeed)
          && (iddObjectType != IddObjectType::Coil_Cooling_DX_VariableSpeed)
          && (iddObjectType != IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted)
          && (iddObjectType != IddObjectType::Coil_Cooling_DX)) {
        return false;
      }
      if ((packagedTerminalHeatPumpAirInletPort(coolingCoil) == 0u) || (packagedTerminalHeatPumpAirOutletPort(coolingCoil) == 0u)) {
        return false;
      }
      const bool result = setPointer(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName, coolingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent ZoneHVACPackagedTerminalHeatPump_Impl::supplementalHeatingCoil() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil) {
      if ((supplementalHeatingCoil.model() != model()) || !isPackagedTerminalHeatPumpAirPathComponent(supplementalHeatingCoil)) {
        return false;
      }

      const auto iddObjectType = supplementalHeatingCoil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_Gas) && (iddObjectType != IddObjectType::OS_Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_Water) && (iddObjectType != IddObjectType::Coil_Heating_Fuel)
          && (iddObjectType != IddObjectType::Coil_Heating_Electric) && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilName, supplementalHeatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    // PTHP has two valid serial air-path shapes once the outdoor-air mixer
    // boundary is stripped away from the public API:
    //
    // - draw-through: [hidden mixed air or inlet] -> cooling -> heating -> fan -> supplemental -> outlet
    // - blow-through: [hidden mixed air or inlet] -> fan -> cooling -> heating -> supplemental -> outlet
    //
    // The parent owns that serial order. These getters expose the meaningful
    // outlet roles on the compound itself, and those roles may alias the
    // parent outlet when the corresponding component is last before the
    // supplemental heater or outlet.
    boost::optional<Node> ZoneHVACPackagedTerminalHeatPump_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> ZoneHVACPackagedTerminalHeatPump_Impl::coolingCoilOutletNode() const {
      auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName);
      auto cooling = (coolingObject && isPackagedTerminalHeatPumpAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject)
                                                                                                   : boost::none;
      if (!cooling) {
        return boost::none;
      }

      return packagedTerminalHeatPumpAirOutletNode(*cooling);
    }

    boost::optional<Node> ZoneHVACPackagedTerminalHeatPump_Impl::heatingCoilOutletNode() const {
      auto heatingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName);
      auto heating = (heatingObject && isPackagedTerminalHeatPumpAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject)
                                                                                                   : boost::none;
      if (!heating) {
        return boost::none;
      }

      return packagedTerminalHeatPumpAirOutletNode(*heating);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result =
        supplyAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result =
        supplyAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result =
        supplyAirFlowRateWhenNoCoolingorHeatingisNeeded
          ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
          : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      auto value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
      if (!value || value->empty()) {
        return false;
      }
      if (openstudio::istringEqual(value.get(), "Yes")) {
        return true;
      }
      if (openstudio::istringEqual(value.get(), "No")) {
        return false;
      }
      return false;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                    noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No", false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result =
        outdoorAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result =
        outdoorAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::heatingConvergenceTolerance() const {
      boost::optional<double> value = getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      bool result = setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, heatingConvergenceTolerance, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetHeatingConvergenceTolerance() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      // Strict EnergyPlus alignment: ZoneHVAC:PackagedTerminalHeatPump does not expose this legacy OS field.
      // Keep API stable while reporting unsupported behavior through the setter/default APIs.
      return 0.0;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
      return true;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double /*minimumOutdoorDryBulbTemperatureforCompressorOperation*/) {
      return false;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
      // No-op: field not present in the EnergyPlus schema for this object.
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::coolingConvergenceTolerance() const {
      boost::optional<double> value = getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isCoolingConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      bool result = setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, coolingConvergenceTolerance, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetCoolingConvergenceTolerance() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, "", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater) {
      const bool result = maximumSupplyAirTemperaturefromSupplementalHeater
                            ? setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                        maximumSupplyAirTemperaturefromSupplementalHeater.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const {
      return {};
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                              maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACPackagedTerminalHeatPump_Impl::fanPlacement() const {
      auto value = getString(ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement);
      if (!value) {
        return std::string();
      }
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setFanPlacement(const std::string& fanPlacement) {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement, fanPlacement, false);
      OS_ASSERT(result);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetFanPlacement() {
      bool result = setString(ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement, "", false);
      OS_ASSERT(result);
      maintainContainedAirPath();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        maintainContainedAirPath();
        return true;
      }
      return false;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName);
      auto supplementalObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilName);

      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto heating = (heatingObject && isPackagedTerminalHeatPumpAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject)
                                                                                                   : boost::none;
      auto cooling = (coolingObject && isPackagedTerminalHeatPumpAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject)
                                                                                                   : boost::none;
      auto supplemental = (supplementalObject && isPackagedTerminalHeatPumpAirPathComponent(*supplementalObject))
                            ? boost::optional<HVACComponent>(*supplementalObject)
                            : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
        return value;
      };

      const auto currentFanType = thisObject.getString(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanObjectType, true);
      const auto expectedFanType = fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedFanType) {
        if (!currentFanType || !openstudio::istringEqual(*currentFanType, *expectedFanType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanObjectType, *expectedFanType));
          changed = true;
        }
      } else if (currentFanType && !currentFanType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanObjectType, ""));
        changed = true;
      }

      const auto currentHeatingType = thisObject.getString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilObjectType, true);
      const auto expectedHeatingType =
        heatingObject ? boost::optional<std::string>(heatingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedHeatingType) {
        if (!currentHeatingType || !openstudio::istringEqual(*currentHeatingType, *expectedHeatingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilObjectType, *expectedHeatingType));
          changed = true;
        }
      } else if (currentHeatingType && !currentHeatingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilObjectType, ""));
        changed = true;
      }

      const auto currentCoolingType = thisObject.getString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilObjectType, true);
      const auto expectedCoolingType =
        coolingObject ? boost::optional<std::string>(coolingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedCoolingType) {
        if (!currentCoolingType || !openstudio::istringEqual(*currentCoolingType, *expectedCoolingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilObjectType, *expectedCoolingType));
          changed = true;
        }
      } else if (currentCoolingType && !currentCoolingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilObjectType, ""));
        changed = true;
      }

      const auto currentSupplementalType =
        thisObject.getString(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilObjectType, true);
      const auto expectedSupplementalType =
        supplementalObject ? boost::optional<std::string>(supplementalObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedSupplementalType) {
        if (!currentSupplementalType || !openstudio::istringEqual(*currentSupplementalType, *expectedSupplementalType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilObjectType, *expectedSupplementalType));
          changed = true;
        }
      } else if (currentSupplementalType && !currentSupplementalType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilObjectType, ""));
        changed = true;
      }

      if (!fan && !heating && !cooling && !supplemental) {
        return changed;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
      trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
      trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));

      const bool blowThrough = openstudio::istringEqual(fanPlacement(), "BlowThrough");
      bool zeroOutdoorAir = false;
      if (auto value = outdoorAirFlowRateDuringCoolingOperation()) {
        zeroOutdoorAir = (*value == 0.0);
      }
      if (auto value = outdoorAirFlowRateDuringHeatingOperation()) {
        zeroOutdoorAir = zeroOutdoorAir && (*value == 0.0);
      }
      if (auto value = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded()) {
        zeroOutdoorAir = zeroOutdoorAir && (*value == 0.0);
      }
      const bool usesHiddenMixedAir = !airLoopHVAC() && !zeroOutdoorAir;

      boost::optional<Node> sourceNode;
      if (usesHiddenMixedAir) {
        const HVACComponent* firstComponent = nullptr;
        if (blowThrough && fan) {
          firstComponent = &(*fan);
        } else if (cooling) {
          firstComponent = &(*cooling);
        } else if (heating) {
          firstComponent = &(*heating);
        } else if (fan) {
          firstComponent = &(*fan);
        } else if (supplemental) {
          firstComponent = &(*supplemental);
        }
        OS_ASSERT(firstComponent);

        if (allowChildNodeRecovery) {
          if (auto candidate = firstComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(
                packagedTerminalHeatPumpAirInletPort(*firstComponent))) {
            if ((*candidate != inletNode) && (*candidate != outletNode)) {
              sourceNode = candidate;
            }
          }
        }

        if (!sourceNode) {
          sourceNode = model().getOrCreateTransientByName<Node>(baseName + " Mixed Air Node");
        }
      }

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

      Node upstreamNode = sourceNode ? *sourceNode : inletNode;
      auto& firstComponent = orderedComponents.front();
      trackNodeChange(firstComponent.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalHeatPumpAirInletPort(firstComponent),
                                                                                    upstreamNode.handle(), false));

      for (size_t i = 0; i < orderedComponents.size(); ++i) {
        auto& component = orderedComponents[i];
        const bool hasNext = (i + 1u) < orderedComponents.size();
        if (!hasNext) {
          trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalHeatPumpAirOutletPort(component),
                                                                                   outletNode.handle(), false));
          continue;
        }

        auto& downstream = orderedComponents[i + 1u];
        boost::optional<Node> connectorNode;

        if (auto currentOutlet =
              component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(packagedTerminalHeatPumpAirOutletPort(component))) {
          if (auto downstreamInlet = downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(
                packagedTerminalHeatPumpAirInletPort(downstream))) {
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
          if (auto downstreamInlet = downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(
                packagedTerminalHeatPumpAirInletPort(downstream))) {
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

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalHeatPumpAirOutletPort(component),
                                                                                 connectorNode->handle(), false));
        trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalHeatPumpAirInletPort(downstream),
                                                                                  connectorNode->handle(), false));
      }

      if (nodeWiringChanged && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:PackagedTerminalHeatPump '" + baseName + "'.");
      }

      return changed;
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::dXHeatingCoilSizingRatio() const {
      boost::optional<double> value = getDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::DXHeatingCoilSizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
      bool result = setDouble(ZoneHVAC_PackagedTerminalHeatPumpFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio, false);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
