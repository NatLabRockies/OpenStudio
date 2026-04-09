/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Model.hpp"
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
#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    // PTAC only wires a small, explicit set of child families into its owned
    // serial air path: straight air-side components plus water heating coils.
    // Keeping that rule local here is more honest than teaching the shared
    // ZoneHVAC base about every component family that might show up in one
    // compound unit.
    bool isPackagedTerminalAirConditionerAirPathComponent(const HVACComponent& component) {
      return static_cast<bool>(component.optionalCast<StraightComponent>())
             || static_cast<bool>(component.optionalCast<WaterToAirComponent>());
    }

    unsigned packagedTerminalAirConditionerAirInletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->inletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airInletPort();
      }
      return 0u;
    }

    unsigned packagedTerminalAirConditionerAirOutletPort(const HVACComponent& component) {
      if (auto straightComponent = component.optionalCast<StraightComponent>()) {
        return straightComponent->outletPort();
      }
      if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
        return waterToAirComponent->airOutletPort();
      }
      return 0u;
    }

    boost::optional<Node> packagedTerminalAirConditionerAirOutletNode(const HVACComponent& component) {
      const auto outletPort = packagedTerminalAirConditionerAirOutletPort(component);
      if (outletPort == 0u) {
        return boost::none;
      }
      return component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(outletPort);
    }

  }  // namespace

  ZoneHVACPackagedTerminalAirConditioner::ZoneHVACPackagedTerminalAirConditioner(const Model& model)
    : ZoneHVACComponent(ZoneHVACPackagedTerminalAirConditioner::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));
  }

  ZoneHVACPackagedTerminalAirConditioner::ZoneHVACPackagedTerminalAirConditioner(
    std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACPackagedTerminalAirConditioner::iddObjectType() {
    return IddObjectType::ZoneHVAC_PackagedTerminalAirConditioner;
  }

  std::vector<std::string> ZoneHVACPackagedTerminalAirConditioner::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACPackagedTerminalAirConditioner::validFanPlacementValues() {
    return fanPlacementValues();
  }

  Schedule ZoneHVACPackagedTerminalAirConditioner::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
      supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(
      supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
      noLoadSupplyAirFlowRateControlSetToLowSpeed);
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
      outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
      outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  std::string ZoneHVACPackagedTerminalAirConditioner::fanPlacement() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->fanPlacement();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetFanPlacement() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetFanPlacement();
  }

  HVACComponent ZoneHVACPackagedTerminalAirConditioner::supplyAirFan() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFan();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFan(const HVACComponent& fan) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFan(fan);
  }

  Schedule ZoneHVACPackagedTerminalAirConditioner::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  HVACComponent ZoneHVACPackagedTerminalAirConditioner::heatingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->heatingCoil();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setHeatingCoil(heatingCoil);
  }

  HVACComponent ZoneHVACPackagedTerminalAirConditioner::coolingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->coolingCoil();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setCoolingCoil(coolingCoil);
  }

  boost::optional<Node> ZoneHVACPackagedTerminalAirConditioner::fanOutletNode() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACPackagedTerminalAirConditioner::coolingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->coolingCoilOutletNode();
  }

  boost::optional<Node> ZoneHVACPackagedTerminalAirConditioner::heatingCoilOutletNode() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->heatingCoilOutletNode();
  }

  std::vector<ModelObject> ZoneHVACPackagedTerminalAirConditioner::children() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->children();
  }

  namespace detail {

    Schedule ZoneHVACPackagedTerminalAirConditioner_Impl::availabilitySchedule() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityScheduleName,
                                           "ZoneHVACPackagedTerminalAirConditioner", "Availability", schedule);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result =
        supplyAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result =
        supplyAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      auto value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
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

    bool
      ZoneHVACPackagedTerminalAirConditioner_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                    noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No", false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result =
        outdoorAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result =
        outdoorAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    std::string ZoneHVACPackagedTerminalAirConditioner_Impl::fanPlacement() const {
      auto value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
      if (!value) {
        return std::string();
      }
      return value.get();
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, fanPlacement);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetFanPlacement() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, "");
      OS_ASSERT(result);
      maintainContainedAirPath();
    }

    std::vector<ModelObject> ZoneHVACPackagedTerminalAirConditioner_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName)) {
        result.push_back(*heatingCoil);
      }
      if (auto fan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName)) {
        result.push_back(*fan);
      }
      if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName)) {
        result.push_back(*coolingCoil);
      }
      return result;
    }

    unsigned ZoneHVACPackagedTerminalAirConditioner_Impl::inletPort() const {
      return ZoneHVAC_PackagedTerminalAirConditionerFields::AirInletNodeName;
    }

    unsigned ZoneHVACPackagedTerminalAirConditioner_Impl::outletPort() const {
      return ZoneHVAC_PackagedTerminalAirConditionerFields::AirOutletNodeName;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }

      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    HVACComponent ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFan(const HVACComponent& fan) {
      if (fan.model() != model()) {
        return false;
      }

      const auto iddObjectType = fan.iddObject().type();
      if ((iddObjectType == IddObjectType::OS_Fan_ConstantVolume) || (iddObjectType == IddObjectType::OS_Fan_OnOff)
          || (iddObjectType == IddObjectType::OS_Fan_SystemModel) || (iddObjectType == IddObjectType::Fan_ConstantVolume)
          || (iddObjectType == IddObjectType::Fan_OnOff) || (iddObjectType == IddObjectType::Fan_SystemModel)) {
        const bool result = setPointer(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName, fan.handle(), false);
        if (result) {
          maintainContainedAirPath();
        }
        return result;
      }
      return false;
    }

    Schedule ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFanOperatingModeSchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanOperatingModeScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanOperatingModeScheduleName,
                                           "ZoneHVACPackagedTerminalAirConditioner", "Supply Air Fan Operating Mode", schedule);
    }

    HVACComponent ZoneHVACPackagedTerminalAirConditioner_Impl::heatingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if ((heatingCoil.model() != model()) || !isPackagedTerminalAirConditionerAirPathComponent(heatingCoil)) {
        return false;
      }

      const auto iddObjectType = heatingCoil.iddObject().type();
      if ((iddObjectType == IddObjectType::OS_Coil_Heating_Gas) || (iddObjectType == IddObjectType::OS_Coil_Heating_Electric)
          || (iddObjectType == IddObjectType::OS_Coil_Heating_Water) || (iddObjectType == IddObjectType::Coil_Heating_Fuel)
          || (iddObjectType == IddObjectType::Coil_Heating_Electric) || (iddObjectType == IddObjectType::Coil_Heating_Water)) {
        const bool result = setPointer(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName, heatingCoil.handle(), false);
        if (result) {
          maintainContainedAirPath();
        }
        return result;
      }
      return false;
    }

    HVACComponent ZoneHVACPackagedTerminalAirConditioner_Impl::coolingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      if ((coolingCoil.model() != model()) || !coolingCoil.optionalCast<StraightComponent>()) {
        return false;
      }

      const auto iddObjectType = coolingCoil.iddObject().type();
      if ((iddObjectType == IddObjectType::OS_Coil_Cooling_DX_SingleSpeed) || (iddObjectType == IddObjectType::OS_Coil_Cooling_DX_VariableSpeed)
          || (iddObjectType == IddObjectType::OS_CoilSystem_Cooling_DX_HeatExchangerAssisted)
          || (iddObjectType == IddObjectType::OS_Coil_Cooling_DX) || (iddObjectType == IddObjectType::Coil_Cooling_DX_SingleSpeed)
          || (iddObjectType == IddObjectType::Coil_Cooling_DX_VariableSpeed)
          || (iddObjectType == IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted)
          || (iddObjectType == IddObjectType::Coil_Cooling_DX)) {
        if ((packagedTerminalAirConditionerAirInletPort(coolingCoil) == 0u) || (packagedTerminalAirConditionerAirOutletPort(coolingCoil) == 0u)) {
          return false;
        }
        const bool result = setPointer(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName, coolingCoil.handle(), false);
        if (result) {
          maintainContainedAirPath();
        }
        return result;
      }
      return false;
    }

    // PTAC has two valid serial air-path shapes once the outdoor-air mixer
    // boundary is stripped away from the public API:
    //
    // - draw-through: [hidden mixed air or inlet] -> cooling -> heating -> fan -> outlet
    // - blow-through: [hidden mixed air or inlet] -> fan -> cooling -> heating -> outlet
    //
    // The parent owns that serial order. These getters expose the meaningful
    // outlet roles on the compound itself, and those roles may alias the
    // parent outlet when the corresponding component is last in the path.
    boost::optional<Node> ZoneHVACPackagedTerminalAirConditioner_Impl::fanOutletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<Node> ZoneHVACPackagedTerminalAirConditioner_Impl::coolingCoilOutletNode() const {
      auto coolingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName);
      auto cooling = (coolingObject && isPackagedTerminalAirConditionerAirPathComponent(*coolingObject))
                       ? boost::optional<HVACComponent>(*coolingObject)
                       : boost::none;
      if (!cooling) {
        return boost::none;
      }

      return packagedTerminalAirConditionerAirOutletNode(*cooling);
    }

    boost::optional<Node> ZoneHVACPackagedTerminalAirConditioner_Impl::heatingCoilOutletNode() const {
      auto heatingObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName);
      auto heating = (heatingObject && isPackagedTerminalAirConditionerAirPathComponent(*heatingObject))
                       ? boost::optional<HVACComponent>(*heatingObject)
                       : boost::none;
      if (!heating) {
        return boost::none;
      }

      return packagedTerminalAirConditionerAirOutletNode(*heating);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName);
      auto heatingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName);
      auto coolingObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName);

      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto heating = (heatingObject && isPackagedTerminalAirConditionerAirPathComponent(*heatingObject))
                       ? boost::optional<HVACComponent>(*heatingObject)
                       : boost::none;
      auto cooling = (coolingObject && isPackagedTerminalAirConditionerAirPathComponent(*coolingObject))
                       ? boost::optional<HVACComponent>(*coolingObject)
                       : boost::none;

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool value) {
        nodeWiringChanged = nodeWiringChanged || value;
        changed = changed || value;
        return value;
      };

      const auto currentFanType = thisObject.getString(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanObjectType, true);
      const auto expectedFanType = fanObject ? boost::optional<std::string>(fanObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedFanType) {
        if (!currentFanType || !openstudio::istringEqual(*currentFanType, *expectedFanType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanObjectType, *expectedFanType));
          changed = true;
        }
      } else if (currentFanType && !currentFanType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanObjectType, ""));
        changed = true;
      }

      const auto currentHeatingType = thisObject.getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilObjectType, true);
      const auto expectedHeatingType =
        heatingObject ? boost::optional<std::string>(heatingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedHeatingType) {
        if (!currentHeatingType || !openstudio::istringEqual(*currentHeatingType, *expectedHeatingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilObjectType, *expectedHeatingType));
          changed = true;
        }
      } else if (currentHeatingType && !currentHeatingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilObjectType, ""));
        changed = true;
      }

      const auto currentCoolingType = thisObject.getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilObjectType, true);
      const auto expectedCoolingType =
        coolingObject ? boost::optional<std::string>(coolingObject->iddObject().name()) : boost::optional<std::string>();
      if (expectedCoolingType) {
        if (!currentCoolingType || !openstudio::istringEqual(*currentCoolingType, *expectedCoolingType)) {
          OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilObjectType, *expectedCoolingType));
          changed = true;
        }
      } else if (currentCoolingType && !currentCoolingType->empty()) {
        OS_ASSERT(thisObject.setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilObjectType, ""));
        changed = true;
      }

      if (!fan && !heating && !cooling) {
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
        }
        OS_ASSERT(firstComponent);

        if (allowChildNodeRecovery) {
          if (auto candidate = firstComponent->getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(
                packagedTerminalAirConditionerAirInletPort(*firstComponent))) {
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

      if (orderedComponents.empty()) {
        return changed;
      }

      Node upstreamNode = sourceNode ? *sourceNode : inletNode;
      auto& firstComponent = orderedComponents.front();
      trackNodeChange(firstComponent.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalAirConditionerAirInletPort(firstComponent),
                                                                                    upstreamNode.handle(), false));

      for (size_t i = 0; i < orderedComponents.size(); ++i) {
        auto& component = orderedComponents[i];
        const bool hasNext = (i + 1u) < orderedComponents.size();
        if (!hasNext) {
          trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalAirConditionerAirOutletPort(component),
                                                                                   outletNode.handle(), false));
          continue;
        }

        auto& downstream = orderedComponents[i + 1u];
        boost::optional<Node> connectorNode;

        if (auto currentOutlet =
              component.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(packagedTerminalAirConditionerAirOutletPort(component))) {
          if (auto downstreamInlet = downstream.getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(
                packagedTerminalAirConditionerAirInletPort(downstream))) {
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
                packagedTerminalAirConditionerAirInletPort(downstream))) {
            if ((*downstreamInlet != inletNode) && (*downstreamInlet != outletNode) && (!sourceNode || (*downstreamInlet != *sourceNode))) {
              connectorNode = downstreamInlet;
            }
          }
        }

        if (!connectorNode) {
          std::string suggestedName;
          if (component == *fan) {
            suggestedName = baseName + " Fan Outlet Node";
          } else if (cooling && component == *cooling) {
            suggestedName = baseName + " Cooling Coil Outlet Node";
          } else {
            suggestedName = baseName + " Heating Coil Outlet Node";
          }
          connectorNode = model().getOrCreateTransientByName<Node>(suggestedName);
        }

        trackNodeChange(component.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalAirConditionerAirOutletPort(component),
                                                                                 connectorNode->handle(), false));
        trackNodeChange(downstream.getImpl<detail::ModelObject_Impl>()->setPointer(packagedTerminalAirConditionerAirInletPort(downstream),
                                                                                  connectorNode->handle(), false));
      }

      if (nodeWiringChanged && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:PackagedTerminalAirConditioner '" + baseName + "'.");
      }

      return changed;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
