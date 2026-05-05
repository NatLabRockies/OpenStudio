/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACWaterToAirHeatPump.hpp"
#include "ZoneHVACComponent/ZoneHVACWaterToAirHeatPump_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
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

#include <boost/optional.hpp>

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_WaterToAirHeatPump_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    // These two helpers exist only to keep the repeated Yes/No scalar mapping
    // readable in this file.
    bool getBooleanFieldValue(const detail::ModelObject_Impl& impl, int fieldIndex) {
      const auto value = impl.getString(fieldIndex, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool setBooleanFieldValue(detail::ModelObject_Impl& impl, int fieldIndex, bool value) {
      return impl.setString(fieldIndex, value ? "Yes" : "No");
    }

    // Water-to-air heat pump owns a mixed family of internal air-side children:
    // the supply fan is a straight component, while the water-side coils expose
    // dedicated air inlet/outlet fields. Keep that routing logic local here so
    // the supported child set stays explicit in the type that owns the path.
    bool isWaterToAirHeatPumpAirPathComponent(const HVACComponent& component) {
      return component.optionalCast<StraightComponent>() || component.optionalCast<WaterToAirComponent>();
    }

    unsigned waterToAirHeatPumpAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned waterToAirHeatPumpAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> waterToAirHeatPumpAirOutletNode(const HVACComponent& component) {
      const auto outletPort = waterToAirHeatPumpAirOutletPort(component);
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

  ZoneHVACWaterToAirHeatPump::ZoneHVACWaterToAirHeatPump(const Model& model) : ZoneHVACComponent(ZoneHVACWaterToAirHeatPump::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>());
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));
  }

  ZoneHVACWaterToAirHeatPump::ZoneHVACWaterToAirHeatPump(std::shared_ptr<detail::ZoneHVACWaterToAirHeatPump_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACWaterToAirHeatPump::iddObjectType() {
    return IddObjectType::ZoneHVAC_WaterToAirHeatPump;
  }

  std::vector<std::string> ZoneHVACWaterToAirHeatPump::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACWaterToAirHeatPump::heatPumpCoilWaterFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode);
  }

  Schedule ZoneHVACWaterToAirHeatPump::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACWaterToAirHeatPump::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringCoolingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFlowRateDuringCoolingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringHeatingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFlowRateDuringHeatingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACWaterToAirHeatPump::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACWaterToAirHeatPump::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACWaterToAirHeatPump::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(value);
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringCoolingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateDuringCoolingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringHeatingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateDuringHeatingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACWaterToAirHeatPump::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACWaterToAirHeatPump::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumSupplyAirTemperaturefromSupplementalHeater(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumSupplyAirTemperaturefromSupplementalHeater(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACWaterToAirHeatPump::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACWaterToAirHeatPump::fanPlacement() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->fanPlacement();
  }

  bool ZoneHVACWaterToAirHeatPump::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACWaterToAirHeatPump::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACWaterToAirHeatPump::resetFanPlacement() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetFanPlacement();
  }

  std::string ZoneHVACWaterToAirHeatPump::heatPumpCoilWaterFlowMode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->heatPumpCoilWaterFlowMode();
  }

  bool ZoneHVACWaterToAirHeatPump::isHeatPumpCoilWaterFlowModeDefaulted() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isHeatPumpCoilWaterFlowModeDefaulted();
  }

  bool ZoneHVACWaterToAirHeatPump::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setHeatPumpCoilWaterFlowMode(heatPumpCoilWaterFlowMode);
  }

  void ZoneHVACWaterToAirHeatPump::resetHeatPumpCoilWaterFlowMode() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetHeatPumpCoilWaterFlowMode();
  }

  boost::optional<Schedule> ZoneHVACWaterToAirHeatPump::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  HVACComponent ZoneHVACWaterToAirHeatPump::supplyAirFan() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFan();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFan(const HVACComponent& supplyAirFan) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFan(supplyAirFan);
  }

  HVACComponent ZoneHVACWaterToAirHeatPump::heatingCoil() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->heatingCoil();
  }

  bool ZoneHVACWaterToAirHeatPump::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setHeatingCoil(heatingCoil);
  }

  HVACComponent ZoneHVACWaterToAirHeatPump::coolingCoil() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->coolingCoil();
  }

  bool ZoneHVACWaterToAirHeatPump::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setCoolingCoil(coolingCoil);
  }

  HVACComponent ZoneHVACWaterToAirHeatPump::supplementalHeatingCoil() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplementalHeatingCoil();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplementalHeatingCoil(supplementalHeatingCoil);
  }

  boost::optional<Node> ZoneHVACWaterToAirHeatPump::fanOutletNode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACWaterToAirHeatPump::coolingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->coolingCoilOutletNode();
  }

  boost::optional<Node> ZoneHVACWaterToAirHeatPump::heatingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->heatingCoilOutletNode();
  }

  boost::optional<Node> ZoneHVACWaterToAirHeatPump::mixedAirNode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->mixedAirNode();
  }

  boost::optional<Node> ZoneHVACWaterToAirHeatPump::outdoorAirNode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> ZoneHVACWaterToAirHeatPump::reliefAirNode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->reliefAirNode();
  }

  boost::optional<OutdoorAirMixer> ZoneHVACWaterToAirHeatPump::outdoorAirMixer() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirMixer();
  }

  std::vector<ModelObject> ZoneHVACWaterToAirHeatPump::children() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->children();
  }

  double ZoneHVACWaterToAirHeatPump::dXHeatingCoilSizingRatio() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->dXHeatingCoilSizingRatio();
  }

  bool ZoneHVACWaterToAirHeatPump::setDXHeatingCoilSizingRatio(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setDXHeatingCoilSizingRatio(value);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    Schedule ZoneHVACWaterToAirHeatPump_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityScheduleName, "ZoneHVACWaterToAirHeatPump", "Availability",
                                           schedule);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }
      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACWaterToAirHeatPump_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    HVACComponent ZoneHVACWaterToAirHeatPump_Impl::supplyAirFan() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<StraightComponent>(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName);
      OS_ASSERT(fan);
      return fan->cast<HVACComponent>();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFan(const HVACComponent& supplyAirFan) {
      if (supplyAirFan.model() != model()) {
        return false;
      }

      const auto iddObjectType = supplyAirFan.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Fan_ConstantVolume) && (iddObjectType != IddObjectType::OS_Fan_OnOff)
          && (iddObjectType != IddObjectType::OS_Fan_SystemModel) && (iddObjectType != IddObjectType::Fan_ConstantVolume)
          && (iddObjectType != IddObjectType::Fan_OnOff) && (iddObjectType != IddObjectType::Fan_SystemModel)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName, supplyAirFan.handle(), false);
      if (result) {
        OS_ASSERT(setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanObjectType, supplyAirFan.iddObject().name()));
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Schedule> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanOperatingModeScheduleName, "ZoneHVACWaterToAirHeatPump",
                                           "Supply Air Fan Operating Mode", schedule);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFanOperatingModeSchedule() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanOperatingModeScheduleName, "", false);
      OS_ASSERT(result);
    }

    HVACComponent ZoneHVACWaterToAirHeatPump_Impl::heatingCoil() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if (heatingCoil.model() != model()) {
        return false;
      }

      const auto iddObjectType = heatingCoil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_WaterToAirHeatPump_EquationFit)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit)
          && (iddObjectType != IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit)
          && (iddObjectType != IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName, heatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent ZoneHVACWaterToAirHeatPump_Impl::coolingCoil() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if (coolingCoil.model() != model()) {
        return false;
      }

      const auto iddObjectType = coolingCoil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Cooling_WaterToAirHeatPump_EquationFit)
          && (iddObjectType != IddObjectType::OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit)
          && (iddObjectType != IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit)
          && (iddObjectType != IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName, coolingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent ZoneHVACWaterToAirHeatPump_Impl::supplementalHeatingCoil() const {
      auto child = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName);
      OS_ASSERT(child);
      return *child;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil) {
      if ((supplementalHeatingCoil.model() != model()) || !isWaterToAirHeatPumpAirPathComponent(supplementalHeatingCoil)) {
        return false;
      }

      const auto iddObjectType = supplementalHeatingCoil.iddObject().type();
      if ((iddObjectType != IddObjectType::OS_Coil_Heating_Gas) && (iddObjectType != IddObjectType::OS_Coil_Heating_Electric)
          && (iddObjectType != IddObjectType::OS_Coil_Heating_Water) && (iddObjectType != IddObjectType::Coil_Heating_Fuel)
          && (iddObjectType != IddObjectType::Coil_Heating_Electric) && (iddObjectType != IddObjectType::Coil_Heating_Water)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName, supplementalHeatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Node> ZoneHVACWaterToAirHeatPump_Impl::fanOutletNode() const {
      auto fan = getObject<ModelObject>().getModelObjectTarget<StraightComponent>(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName);
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> ZoneHVACWaterToAirHeatPump_Impl::coolingCoilOutletNode() const {
      auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName);
      auto cooling =
        (coolingObject && isWaterToAirHeatPumpAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      if (!cooling) {
        return boost::none;
      }

      return waterToAirHeatPumpAirOutletNode(*cooling);
    }

    boost::optional<Node> ZoneHVACWaterToAirHeatPump_Impl::heatingCoilOutletNode() const {
      auto heatingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName);
      auto heating =
        (heatingObject && isWaterToAirHeatPumpAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      if (!heating) {
        return boost::none;
      }

      return waterToAirHeatPumpAirOutletNode(*heating);
    }

    boost::optional<Node> ZoneHVACWaterToAirHeatPump_Impl::mixedAirNode() const {
      auto mixer = outdoorAirMixer();
      return mixer ? mixer->mixedAirNode() : boost::none;
    }

    boost::optional<Node> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirNode() const {
      auto mixer = outdoorAirMixer();
      return mixer ? mixer->outdoorAirNode() : boost::none;
    }

    boost::optional<Node> ZoneHVACWaterToAirHeatPump_Impl::reliefAirNode() const {
      auto mixer = outdoorAirMixer();
      return mixer ? mixer->reliefAirNode() : boost::none;
    }

    boost::optional<OutdoorAirMixer> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirMixer() const {
      return getObject<ModelObject>().getModelObjectTarget<OutdoorAirMixer>(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName);
    }

    std::vector<ModelObject> ZoneHVACWaterToAirHeatPump_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName)) {
        result.push_back(*child);
      }
      if (auto child = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName)) {
        result.push_back(*child);
      }
      return result;
    }

    unsigned ZoneHVACWaterToAirHeatPump_Impl::inletPort() const {
      return ZoneHVAC_WaterToAirHeatPumpFields::AirInletNodeName;
    }

    unsigned ZoneHVACWaterToAirHeatPump_Impl::outletPort() const {
      return ZoneHVAC_WaterToAirHeatPumpFields::AirOutletNodeName;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      // Valid water-to-air heat-pump air paths follow the same packaged
      // terminal pattern as the other finished compound zone equipment:
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

      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName);
      auto supplementalObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName);

      auto fan = thisObject.getModelObjectTarget<StraightComponent>(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName);
      auto fanObject = fan ? boost::optional<HVACComponent>(fan->cast<HVACComponent>()) : boost::none;
      auto heating =
        (heatingObject && isWaterToAirHeatPumpAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      auto cooling =
        (coolingObject && isWaterToAirHeatPumpAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      auto supplemental = (supplementalObject && isWaterToAirHeatPumpAirPathComponent(*supplementalObject))
                            ? boost::optional<HVACComponent>(*supplementalObject)
                            : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
        return value;
      };

      const auto currentFanType = thisObject.getString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanObjectType, true);
      const auto expectedFanType = fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedFanType) {
        if (!currentFanType || !openstudio::istringEqual(*currentFanType, *expectedFanType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanObjectType, *expectedFanType));
          changed = true;
        }
      } else if (currentFanType && !currentFanType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanObjectType, ""));
        changed = true;
      }

      const auto currentHeatingType = thisObject.getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilObjectType, true);
      const auto expectedHeatingType =
        heatingObject ? boost::optional<std::string>(heatingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedHeatingType) {
        if (!currentHeatingType || !openstudio::istringEqual(*currentHeatingType, *expectedHeatingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilObjectType, *expectedHeatingType));
          changed = true;
        }
      } else if (currentHeatingType && !currentHeatingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilObjectType, ""));
        changed = true;
      }

      const auto currentCoolingType = thisObject.getString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilObjectType, true);
      const auto expectedCoolingType =
        coolingObject ? boost::optional<std::string>(coolingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedCoolingType) {
        if (!currentCoolingType || !openstudio::istringEqual(*currentCoolingType, *expectedCoolingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilObjectType, *expectedCoolingType));
          changed = true;
        }
      } else if (currentCoolingType && !currentCoolingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilObjectType, ""));
        changed = true;
      }

      const auto currentSupplementalType = thisObject.getString(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilObjectType, true);
      const auto expectedSupplementalType =
        supplementalObject ? boost::optional<std::string>(supplementalObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedSupplementalType) {
        if (!currentSupplementalType || !openstudio::istringEqual(*currentSupplementalType, *expectedSupplementalType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilObjectType, *expectedSupplementalType));
          changed = true;
        }
      } else if (currentSupplementalType && !currentSupplementalType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilObjectType, ""));
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
      // The water-to-air heat pump owns this local OA mixer whenever it owns
      // its own zone-side air path. Zero OA flow does not remove the topology
      // object; it only affects the flow through that already-defined path.
      const bool usesHiddenMixedAir = !airLoopHVAC();

      boost::optional<Node> sourceNode;
      boost::optional<OutdoorAirMixer> outdoorAirMixer;
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
          // Canonicalization can preserve an existing mixed-air node when the
          // first child already points at one that is not a boundary node.
          if (auto candidate =
                firstComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(waterToAirHeatPumpAirInletPort(*firstComponent))) {
            if ((*candidate != inletNode) && (*candidate != outletNode)) {
              sourceNode = candidate;
            }
          }
        }

        if (!sourceNode) {
          sourceNode = model().getOrCreateTransientByName<Node>(baseName + " Mixed Air Node");
        }

        outdoorAirMixer = getOrCreateOwnedOutdoorAirMixer(thisObject, ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName, baseName + " OA Mixer");
        changed = setPointer(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName, outdoorAirMixer->handle()) || changed;

        const auto currentMixerType = thisObject.getString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerObjectType, true);
        const std::string expectedMixerType = outdoorAirMixer->iddObject().name();
        if (!currentMixerType || !openstudio::istringEqual(*currentMixerType, expectedMixerType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerObjectType, expectedMixerType));
          changed = true;
        }

        auto outdoorAirNode = model().getOrCreateTransientByName<Node>(baseName + " OA Node");
        auto reliefAirNode = model().getOrCreateTransientByName<Node>(baseName + " Relief Air Node");
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::MixedAirNodeName, sourceNode->handle()) || changed;
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::OutdoorAirStreamNodeName, outdoorAirNode.handle()) || changed;
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::ReliefAirStreamNodeName, reliefAirNode.handle()) || changed;
        changed = outdoorAirMixer->setPointer(OutdoorAir_MixerFields::ReturnAirStreamNodeName, inletNode.handle()) || changed;
      } else {
        const auto currentMixerType = thisObject.getString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerObjectType, true);
        if (currentMixerType && !currentMixerType->empty()) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerObjectType, ""));
          changed = true;
        }
        changed = clearOwnedOutdoorAirMixer(thisObject, ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName) || changed;
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

      Node upstreamNode = sourceNode ? *sourceNode : inletNode;
      for (std::size_t i = 0; i < orderedComponents.size(); ++i) {
        auto component = orderedComponents[i];
        trackNodeChange(
          component.getImpl<detail::ModelObject_Impl>()->setPointer(waterToAirHeatPumpAirInletPort(component), upstreamNode.handle(), false));

        Node downstreamNode = outletNode;
        if ((i + 1u) < orderedComponents.size()) {
          auto downstream = orderedComponents[i + 1u];
          boost::optional<Node> connectorNode;

          if (allowChildNodeRecovery) {
            // Canonicalization keeps an existing shared connector when adjacent
            // children already agree on it and it is not one of the parent-owned
            // boundary or mixed-air nodes.
            if (auto currentOutlet = component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(waterToAirHeatPumpAirOutletPort(component))) {
              if (auto downstreamInlet =
                    downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(waterToAirHeatPumpAirInletPort(downstream))) {
                if ((*currentOutlet == *downstreamInlet) && (*currentOutlet != inletNode) && (*currentOutlet != outletNode)
                    && (!sourceNode || (*currentOutlet != *sourceNode))) {
                  connectorNode = currentOutlet;
                }
              }
            }
          }

          if (!connectorNode) {
            connectorNode = model().getOrCreateTransientByName<Node>(connectorName(component));
          }
          downstreamNode = *connectorNode;
        }

        trackNodeChange(
          component.getImpl<detail::ModelObject_Impl>()->setPointer(waterToAirHeatPumpAirOutletPort(component), downstreamNode.handle(), false));
        upstreamNode = downstreamNode;
      }

      if (context && nodeWiringChanged) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:WaterToAirHeatPump '" + baseName + "'.");
      }

      return changed;
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      bool result = false;
      if (supplyAirFlowRateDuringCoolingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation.get());
        OS_ASSERT(result);
      } else {
        resetSupplyAirFlowRateDuringCoolingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      bool result(false);
      if (supplyAirFlowRateDuringHeatingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation.get());
        OS_ASSERT(result);
      } else {
        resetSupplyAirFlowRateDuringHeatingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      bool result(false);
      if (supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get());
        OS_ASSERT(result);
      } else {
        resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      return getBooleanFieldValue(*this, ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setBooleanFieldValue(*this, ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                               noLoadSupplyAirFlowRateControlSetToLowSpeed);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      bool result(false);
      if (outdoorAirFlowRateDuringCoolingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation.get());
        OS_ASSERT(result);
      } else {
        resetOutdoorAirFlowRateDuringCoolingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      bool result(false);
      if (outdoorAirFlowRateDuringHeatingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation.get());
        OS_ASSERT(result);
      } else {
        resetOutdoorAirFlowRateDuringHeatingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      bool result(false);
      if (outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get());
        OS_ASSERT(result);
      } else {
        resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
        result = true;
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater) {
      bool result = false;
      if (maximumSupplyAirTemperaturefromSupplementalHeater) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                           maximumSupplyAirTemperaturefromSupplementalHeater.get());
        OS_ASSERT(result);
      } else {
        resetMaximumSupplyAirTemperaturefromSupplementalHeater();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      double maximumSupplyAirTemperaturefromSupplementalHeater) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                    maximumSupplyAirTemperaturefromSupplementalHeater);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize");
      OS_ASSERT(result);
    }

    double ZoneHVACWaterToAirHeatPump_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      boost::optional<double> maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = false;
      if (maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                           maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation.get());
        OS_ASSERT(result);
      } else {
        resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                                    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "");
      OS_ASSERT(result);
    }

    std::string ZoneHVACWaterToAirHeatPump_Impl::fanPlacement() const {
      auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, fanPlacement);
      OS_ASSERT(result);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetFanPlacement() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, "");
      OS_ASSERT(result);
      maintainContainedAirPath();
    }

    std::string ZoneHVACWaterToAirHeatPump_Impl::heatPumpCoilWaterFlowMode() const {
      auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isHeatPumpCoilWaterFlowModeDefaulted() const {
      return isEmpty(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
      const bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, heatPumpCoilWaterFlowMode);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetHeatPumpCoilWaterFlowMode() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, "");
      OS_ASSERT(result);
    }

    double ZoneHVACWaterToAirHeatPump_Impl::dXHeatingCoilSizingRatio() const {
      auto value = getDouble(ZoneHVAC_WaterToAirHeatPumpFields::DXHeatingCoilSizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const {
      return {};
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
