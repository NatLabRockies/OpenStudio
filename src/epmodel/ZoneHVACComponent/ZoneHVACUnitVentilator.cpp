/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACUnitVentilator.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitVentilator_Impl.hpp"

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

#include <boost/none.hpp>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_UnitVentilator_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    // Unit ventilator only accepts straight air-side children and water-to-air
    // coils in its owned internal path. Keep that routing rule local here so
    // readers can see the exact supported child families without chasing a
    // shared helper in the ZoneHVAC base.
    bool isUnitVentilatorAirPathComponent(const HVACComponent& component) {
      return component.optionalCast<StraightComponent>() || component.optionalCast<WaterToAirComponent>();
    }

    unsigned unitVentilatorAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned unitVentilatorAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> unitVentilatorAirOutletNode(const HVACComponent& component) {
      const auto outletPort = unitVentilatorAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

  }  // namespace

  ZoneHVACUnitVentilator::ZoneHVACUnitVentilator(const Model& model) : ZoneHVACComponent(ZoneHVACUnitVentilator::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setOutdoorAirControlType("VariablePercent"));
    autosizeMaximumSupplyAirFlowRate();
    autosizeMinimumOutdoorAirFlowRate();
    autosizeMaximumOutdoorAirFlowRate();
    OS_ASSERT(setHeatingConvergenceTolerance(0.001));
    OS_ASSERT(setCoolingConvergenceTolerance(0.001));
  }

  ZoneHVACUnitVentilator::ZoneHVACUnitVentilator(std::shared_ptr<detail::ZoneHVACUnitVentilator_Impl> impl) : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACUnitVentilator::iddObjectType() {
    return IddObjectType::ZoneHVAC_UnitVentilator;
  }

  std::vector<std::string> ZoneHVACUnitVentilator::outdoorAirControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType);
  }

  Schedule ZoneHVACUnitVentilator::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACUnitVentilator::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> ZoneHVACUnitVentilator::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMaximumSupplyAirFlowRate();
  }

  Schedule ZoneHVACUnitVentilator::minimumOutdoorAirSchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->minimumOutdoorAirSchedule();
  }

  bool ZoneHVACUnitVentilator::setMinimumOutdoorAirSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMinimumOutdoorAirSchedule(schedule);
  }

  Schedule ZoneHVACUnitVentilator::maximumOutdoorAirFractionorTemperatureSchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumOutdoorAirFractionorTemperatureSchedule();
  }

  bool ZoneHVACUnitVentilator::setMaximumOutdoorAirFractionorTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumOutdoorAirFractionorTemperatureSchedule(schedule);
  }

  HVACComponent ZoneHVACUnitVentilator::supplyAirFan() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->supplyAirFan();
  }

  bool ZoneHVACUnitVentilator::setSupplyAirFan(const HVACComponent& supplyAirFan) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setSupplyAirFan(supplyAirFan);
  }

  boost::optional<Schedule> ZoneHVACUnitVentilator::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACUnitVentilator::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  void ZoneHVACUnitVentilator::resetSupplyAirFanOperatingModeSchedule() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->resetSupplyAirFanOperatingModeSchedule();
  }

  boost::optional<HVACComponent> ZoneHVACUnitVentilator::heatingCoil() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->heatingCoil();
  }

  bool ZoneHVACUnitVentilator::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setHeatingCoil(heatingCoil);
  }

  void ZoneHVACUnitVentilator::resetHeatingCoil() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->resetHeatingCoil();
  }

  boost::optional<HVACComponent> ZoneHVACUnitVentilator::coolingCoil() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->coolingCoil();
  }

  bool ZoneHVACUnitVentilator::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setCoolingCoil(coolingCoil);
  }

  void ZoneHVACUnitVentilator::resetCoolingCoil() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->resetCoolingCoil();
  }

  boost::optional<Node> ZoneHVACUnitVentilator::mixedAirNode() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->mixedAirNode();
  }

  boost::optional<Node> ZoneHVACUnitVentilator::outdoorAirNode() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> ZoneHVACUnitVentilator::exhaustAirNode() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->exhaustAirNode();
  }

  boost::optional<Node> ZoneHVACUnitVentilator::fanOutletNode() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACUnitVentilator::coolingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->coolingCoilOutletNode();
  }

  std::string ZoneHVACUnitVentilator::outdoorAirControlType() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->outdoorAirControlType();
  }

  bool ZoneHVACUnitVentilator::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setOutdoorAirControlType(outdoorAirControlType);
  }

  boost::optional<double> ZoneHVACUnitVentilator::minimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->minimumOutdoorAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMinimumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMinimumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMinimumOutdoorAirFlowRate(minimumOutdoorAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMinimumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMinimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMaximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMaximumOutdoorAirFlowRate();
  }

  double ZoneHVACUnitVentilator::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACUnitVentilator::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  double ZoneHVACUnitVentilator::coolingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->coolingConvergenceTolerance();
  }

  bool ZoneHVACUnitVentilator::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  std::vector<ModelObject> ZoneHVACUnitVentilator::children() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->children();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<ModelObject> ZoneHVACUnitVentilator_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto supplyFan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName)) {
        result.push_back(*supplyFan);
      }
      if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_UnitVentilatorFields::HeatingCoilName)) {
        result.push_back(*heatingCoil);
      }
      if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_UnitVentilatorFields::CoolingCoilName)) {
        result.push_back(*coolingCoil);
      }
      return result;
    }

    unsigned ZoneHVACUnitVentilator_Impl::inletPort() const {
      return ZoneHVAC_UnitVentilatorFields::AirInletNodeName;
    }

    unsigned ZoneHVACUnitVentilator_Impl::outletPort() const {
      return ZoneHVAC_UnitVentilatorFields::AirOutletNodeName;
    }

    bool ZoneHVACUnitVentilator_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }

      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACUnitVentilator_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACUnitVentilator_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    Schedule ZoneHVACUnitVentilator_Impl::availabilitySchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName, "ZoneHVACUnitVentilator", "Availability",
                                           schedule);
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMaximumSupplyAirFlowRate() const {
      return boost::none;
    }

    Schedule ZoneHVACUnitVentilator_Impl::minimumOutdoorAirSchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setMinimumOutdoorAirSchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName, schedule.handle(), false);
    }

    Schedule ZoneHVACUnitVentilator_Impl::maximumOutdoorAirFractionorTemperatureSchedule() const {
      auto target =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumOutdoorAirFractionorTemperatureSchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName, schedule.handle(), false);
    }

    HVACComponent ZoneHVACUnitVentilator_Impl::supplyAirFan() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitVentilator_Impl::setSupplyAirFan(const HVACComponent& supplyAirFan) {
      if ((supplyAirFan.model() != model()) || !supplyAirFan.optionalCast<StraightComponent>()) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName, supplyAirFan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Schedule> ZoneHVACUnitVentilator_Impl::supplyAirFanOperatingModeSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName);
    }

    bool ZoneHVACUnitVentilator_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, "ZoneHVACUnitVentilator",
                                           "Supply Air Fan Operating Mode", schedule);
    }

    void ZoneHVACUnitVentilator_Impl::resetSupplyAirFanOperatingModeSchedule() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, ""));
    }

    boost::optional<HVACComponent> ZoneHVACUnitVentilator_Impl::heatingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::HeatingCoilName);
    }

    bool ZoneHVACUnitVentilator_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if ((heatingCoil.model() != model()) || !isUnitVentilatorAirPathComponent(heatingCoil)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_UnitVentilatorFields::HeatingCoilName, heatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::resetHeatingCoil() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::HeatingCoilName, ""));
      maintainContainedAirPath();
    }

    boost::optional<HVACComponent> ZoneHVACUnitVentilator_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::CoolingCoilName);
    }

    bool ZoneHVACUnitVentilator_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if ((coolingCoil.model() != model()) || !isUnitVentilatorAirPathComponent(coolingCoil)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_UnitVentilatorFields::CoolingCoilName, coolingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::resetCoolingCoil() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::CoolingCoilName, ""));
      maintainContainedAirPath();
    }

    boost::optional<Node> ZoneHVACUnitVentilator_Impl::mixedAirNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(ZoneHVAC_UnitVentilatorFields::MixedAirNodeName);
    }

    boost::optional<Node> ZoneHVACUnitVentilator_Impl::outdoorAirNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(ZoneHVAC_UnitVentilatorFields::OutdoorAirNodeName);
    }

    boost::optional<Node> ZoneHVACUnitVentilator_Impl::exhaustAirNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(ZoneHVAC_UnitVentilatorFields::ExhaustAirNodeName);
    }

    // Unit ventilators can have a few valid contained air-path shapes:
    //
    // - mixed air -> fan -> outlet
    // - mixed air -> fan -> cooling coil -> outlet
    // - mixed air -> fan -> heating coil -> outlet
    // - mixed air -> fan -> cooling coil -> heating coil -> outlet
    //
    // This getter exposes the fan-outlet role on the parent. That role may
    // alias another parent node such as the unit outlet when there is no
    // downstream coil. The important question is whether the fan exists and
    // has an outlet node, not whether that node is distinct.
    boost::optional<Node> ZoneHVACUnitVentilator_Impl::fanOutletNode() const {
      auto thisObject = getObject<ModelObject>();

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    // This getter exposes the cooling-coil-outlet role on the parent. That
    // role exists whenever a cooling coil exists, even if the outlet node is
    // also the unit outlet because there is no downstream heating coil.
    boost::optional<Node> ZoneHVACUnitVentilator_Impl::coolingCoilOutletNode() const {
      auto thisObject = getObject<ModelObject>();

      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::CoolingCoilName);
      auto cooling =
        (coolingObject && isUnitVentilatorAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;
      if (!cooling) {
        return boost::none;
      }

      return unitVentilatorAirOutletNode(*cooling);
    }

    std::string ZoneHVACUnitVentilator_Impl::outdoorAirControlType() const {
      auto value = getString(ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
      const bool result = setString(ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, outdoorAirControlType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::minimumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMinimumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, minimumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMinimumOutdoorAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMaximumOutdoorAirFlowRate() const {
      return boost::none;
    }

    double ZoneHVACUnitVentilator_Impl::heatingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACUnitVentilator_Impl::coolingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, coolingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACUnitVentilator_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACUnitVentilator_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACUnitVentilator_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::SupplyAirFanName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::HeatingCoilName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitVentilatorFields::CoolingCoilName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto heating =
        (heatingObject && isUnitVentilatorAirPathComponent(*heatingObject)) ? boost::optional<HVACComponent>(*heatingObject) : boost::none;
      auto cooling =
        (coolingObject && isUnitVentilatorAirPathComponent(*coolingObject)) ? boost::optional<HVACComponent>(*coolingObject) : boost::none;

      bool changed = false;

      const auto currentFanType = thisObject.getString(ZoneHVAC_UnitVentilatorFields::SupplyAirFanObjectType, true);
      const auto expectedFanType = fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedFanType) {
        if (!currentFanType || !openstudio::istringEqual(*currentFanType, *expectedFanType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::SupplyAirFanObjectType, *expectedFanType));
          changed = true;
        }
      } else if (currentFanType && !currentFanType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::SupplyAirFanObjectType, ""));
        changed = true;
      }

      const auto currentHeatingType = thisObject.getString(ZoneHVAC_UnitVentilatorFields::HeatingCoilObjectType, true);
      const auto expectedHeatingType =
        heatingObject ? boost::optional<std::string>(heatingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedHeatingType) {
        if (!currentHeatingType || !openstudio::istringEqual(*currentHeatingType, *expectedHeatingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::HeatingCoilObjectType, *expectedHeatingType));
          changed = true;
        }
      } else if (currentHeatingType && !currentHeatingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::HeatingCoilObjectType, ""));
        changed = true;
      }

      const auto currentCoolingType = thisObject.getString(ZoneHVAC_UnitVentilatorFields::CoolingCoilObjectType, true);
      const auto expectedCoolingType =
        coolingObject ? boost::optional<std::string>(coolingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedCoolingType) {
        if (!currentCoolingType || !openstudio::istringEqual(*currentCoolingType, *expectedCoolingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::CoolingCoilObjectType, *expectedCoolingType));
          changed = true;
        }
      } else if (currentCoolingType && !currentCoolingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::CoolingCoilObjectType, ""));
        changed = true;
      }

      std::string expectedCoilOption = "None";
      if (heating && cooling) {
        expectedCoilOption = "HeatingAndCooling";
      } else if (heating) {
        expectedCoilOption = "Heating";
      } else if (cooling) {
        expectedCoilOption = "Cooling";
      }
      const auto currentCoilOption = thisObject.getString(ZoneHVAC_UnitVentilatorFields::CoilOption, true);
      if (!currentCoilOption || !openstudio::istringEqual(*currentCoilOption, expectedCoilOption)) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_UnitVentilatorFields::CoilOption, expectedCoilOption));
        changed = true;
      }

      if (!fan && !heating && !cooling) {
        if (changed && context) {
          detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:UnitVentilator '" + thisObject.nameString() + "'.");
        }
        return changed;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
      auto mixedAir = resolvedOrCreatedNodeTarget(ZoneHVAC_UnitVentilatorFields::MixedAirNodeName, baseName + " Mixed Air Node");
      auto outdoorAir = resolvedOrCreatedNodeTarget(ZoneHVAC_UnitVentilatorFields::OutdoorAirNodeName, baseName + " OA Node");
      auto exhaustAir = resolvedOrCreatedNodeTarget(ZoneHVAC_UnitVentilatorFields::ExhaustAirNodeName, baseName + " Exhaust Air Node");

      changed = setPointer(inletPort(), inletNode.handle(), false) || changed;
      changed = setPointer(outletPort(), outletNode.handle(), false) || changed;
      changed = setPointer(ZoneHVAC_UnitVentilatorFields::MixedAirNodeName, mixedAir.handle(), false) || changed;
      changed = setPointer(ZoneHVAC_UnitVentilatorFields::OutdoorAirNodeName, outdoorAir.handle(), false) || changed;
      changed = setPointer(ZoneHVAC_UnitVentilatorFields::ExhaustAirNodeName, exhaustAir.handle(), false) || changed;

      boost::optional<Node> fanOutlet;
      if (fan && (cooling || heating)) {
        if (!allowChildNodeRecovery) {
          auto currentFanOutlet = fan->outletModelObject() ? fan->outletModelObject()->optionalCast<Node>() : boost::none;
          const boost::optional<HVACComponent> downstream = cooling ? cooling : heating;
          auto currentDownstreamInlet = downstream && unitVentilatorAirInletPort(*downstream) != 0u
                                          ? downstream->getModelObjectTarget<Node>(unitVentilatorAirInletPort(*downstream))
                                          : boost::none;
          if (currentFanOutlet && currentDownstreamInlet && (*currentFanOutlet == *currentDownstreamInlet) && (*currentFanOutlet != mixedAir)
              && (*currentFanOutlet != outletNode)) {
            fanOutlet = currentFanOutlet;
          }
        } else {
          fanOutlet = fanOutletNode();
        }
        if (!fanOutlet && allowChildNodeRecovery) {
          // Canonicalization may recover a named child node link that drifted
          // out of sync, but it should do so through the shared node resolver.
          if (auto candidate = fan->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(fan->outletPort())) {
            if ((*candidate != inletNode) && (*candidate != outletNode) && (*candidate != mixedAir)) {
              fanOutlet = *candidate;
            }
          }
        }
        if (!fanOutlet && allowChildNodeRecovery) {
          const boost::optional<HVACComponent> downstream = cooling ? cooling : heating;
          if (downstream) {
            const auto downstreamInletPort = unitVentilatorAirInletPort(*downstream);
            if (downstreamInletPort != 0u) {
              if (auto candidate = downstream->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(downstreamInletPort)) {
                if ((*candidate != inletNode) && (*candidate != outletNode) && (*candidate != mixedAir)) {
                  fanOutlet = *candidate;
                }
              }
            }
          }
        }
        if (!fanOutlet) {
          fanOutlet = model().getOrCreateTransientByName<Node>(baseName + " Fan Outlet Node");
        }
      }

      boost::optional<Node> coolingOutlet;
      if (cooling && heating) {
        if (!allowChildNodeRecovery) {
          auto currentCoolingOutlet = unitVentilatorAirOutletNode(*cooling);
          const auto heatingAirInlet = unitVentilatorAirInletPort(*heating) != 0u
                                         ? heating->getModelObjectTarget<Node>(unitVentilatorAirInletPort(*heating))
                                         : boost::none;
          if (currentCoolingOutlet && heatingAirInlet && (*currentCoolingOutlet == *heatingAirInlet) && (*currentCoolingOutlet != outletNode)
              && (!fanOutlet || (*currentCoolingOutlet != *fanOutlet))) {
            coolingOutlet = currentCoolingOutlet;
          }
        } else {
          coolingOutlet = coolingCoilOutletNode();
        }
        if (!coolingOutlet && allowChildNodeRecovery) {
          const auto coolingAirOutletPort = unitVentilatorAirOutletPort(*cooling);
          if (coolingAirOutletPort != 0u) {
            if (auto candidate = cooling->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(coolingAirOutletPort)) {
              if ((*candidate != inletNode) && (*candidate != outletNode) && (*candidate != mixedAir) && (!fanOutlet || (*candidate != *fanOutlet))) {
                coolingOutlet = *candidate;
              }
            }
          }
        }
        if (!coolingOutlet && allowChildNodeRecovery) {
          const auto heatingAirInletPort = unitVentilatorAirInletPort(*heating);
          if (heatingAirInletPort != 0u) {
            if (auto candidate = heating->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(heatingAirInletPort)) {
              if ((*candidate != inletNode) && (*candidate != outletNode) && (*candidate != mixedAir) && (!fanOutlet || (*candidate != *fanOutlet))) {
                coolingOutlet = *candidate;
              }
            }
          }
        }
        if (!coolingOutlet) {
          coolingOutlet = model().getOrCreateTransientByName<Node>(baseName + " Cooling Coil Outlet Node");
        }
      }

      if (fan) {
        changed = fan->getImpl<detail::ModelObject_Impl>()->setPointer(fan->inletPort(), mixedAir.handle(), false) || changed;
        if (fanOutlet) {
          changed = fan->getImpl<detail::ModelObject_Impl>()->setPointer(fan->outletPort(), fanOutlet->handle(), false) || changed;
        } else {
          changed = fan->getImpl<detail::ModelObject_Impl>()->setPointer(fan->outletPort(), outletNode.handle(), false) || changed;
        }
      }

      if (cooling) {
        const auto coolingAirInletPort = unitVentilatorAirInletPort(*cooling);
        const auto coolingAirOutletPort = unitVentilatorAirOutletPort(*cooling);
        if (coolingAirInletPort != 0u) {
          if (fanOutlet) {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirInletPort, fanOutlet->handle(), false) || changed;
          } else {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirInletPort, mixedAir.handle(), false) || changed;
          }
        }
        if (coolingAirOutletPort != 0u) {
          if (coolingOutlet) {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirOutletPort, coolingOutlet->handle(), false) || changed;
          } else {
            changed = cooling->getImpl<detail::ModelObject_Impl>()->setPointer(coolingAirOutletPort, outletNode.handle(), false) || changed;
          }
        }
      }

      if (heating) {
        const auto heatingAirInletPort = unitVentilatorAirInletPort(*heating);
        const auto heatingAirOutletPort = unitVentilatorAirOutletPort(*heating);
        if (heatingAirInletPort != 0u) {
          if (coolingOutlet) {
            changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirInletPort, coolingOutlet->handle(), false) || changed;
          } else if (fanOutlet) {
            changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirInletPort, fanOutlet->handle(), false) || changed;
          } else {
            changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirInletPort, mixedAir.handle(), false) || changed;
          }
        }
        if (heatingAirOutletPort != 0u) {
          changed = heating->getImpl<detail::ModelObject_Impl>()->setPointer(heatingAirOutletPort, outletNode.handle(), false) || changed;
        }
      }

      if (changed && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:UnitVentilator '" + baseName + "'.");
      }

      return changed;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
