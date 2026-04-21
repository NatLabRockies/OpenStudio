/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"
#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator_Impl.hpp"

#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp"
#include "ParentObject/ZoneHVACEnergyRecoveryVentilatorController_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

#include <algorithm>

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      // This family owns a paired supply and exhaust path: outdoor air through
      // the heat exchanger and supply fan, and zone exhaust through the heat
      // exchanger and exhaust fan.
      bool isEnergyRecoveryVentilatorFan(const HVACComponent& component) {
        const auto type = component.iddObject().type().value();
        return ((type == IddObjectType::Fan_OnOff) || (type == IddObjectType::Fan_SystemModel))
               && component.optionalCast<StraightComponent>().has_value();
      }

      bool isEnergyRecoveryVentilatorHeatExchanger(const HVACComponent& component) {
        return component.optionalCast<HeatExchangerAirToAirSensibleAndLatent>().has_value();
      }

      boost::optional<Node> connectedNode(const boost::optional<ModelObject>& object) {
        return object ? object->optionalCast<Node>() : boost::none;
      }

    }  // namespace

  }  // namespace detail

  ZoneHVACEnergyRecoveryVentilator::ZoneHVACEnergyRecoveryVentilator(const Model& model)
    : ZoneHVACComponent(ZoneHVACEnergyRecoveryVentilator::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));

    HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
    OS_ASSERT(heatExchanger.setSupplyAirOutletTemperatureControl(false));
    FanOnOff supplyAirFan(model);
    FanOnOff exhaustAirFan(model);

    OS_ASSERT(setHeatExchanger(heatExchanger));
    OS_ASSERT(setSupplyAirFan(supplyAirFan));
    OS_ASSERT(setExhaustAirFan(exhaustAirFan));
    autosizeSupplyAirFlowRate();
    autosizeExhaustAirFlowRate();
    OS_ASSERT(setVentilationRateperUnitFloorArea(0.000508));
    OS_ASSERT(setVentilationRateperOccupant(0.00236));
  }

  ZoneHVACEnergyRecoveryVentilator::ZoneHVACEnergyRecoveryVentilator(std::shared_ptr<detail::ZoneHVACEnergyRecoveryVentilator_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACEnergyRecoveryVentilator::iddObjectType() {
    return IddObjectType::ZoneHVAC_EnergyRecoveryVentilator;
  }

  Schedule ZoneHVACEnergyRecoveryVentilator::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent ZoneHVACEnergyRecoveryVentilator::heatExchanger() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->heatExchanger();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setHeatExchanger(const HVACComponent& heatExchanger) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setHeatExchanger(heatExchanger);
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilator::supplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->supplyAirFlowRate();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setSupplyAirFlowRate(double supplyAirFlowRate) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setSupplyAirFlowRate(supplyAirFlowRate);
  }

  bool ZoneHVACEnergyRecoveryVentilator::isSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->isSupplyAirFlowRateAutosized();
  }

  void ZoneHVACEnergyRecoveryVentilator::autosizeSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->autosizeSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilator::exhaustAirFlowRate() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->exhaustAirFlowRate();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setExhaustAirFlowRate(double exhaustAirFlowRate) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setExhaustAirFlowRate(exhaustAirFlowRate);
  }

  bool ZoneHVACEnergyRecoveryVentilator::isExhaustAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->isExhaustAirFlowRateAutosized();
  }

  void ZoneHVACEnergyRecoveryVentilator::autosizeExhaustAirFlowRate() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->autosizeExhaustAirFlowRate();
  }

  HVACComponent ZoneHVACEnergyRecoveryVentilator::supplyAirFan() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->supplyAirFan();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setSupplyAirFan(const HVACComponent& supplyAirFan) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setSupplyAirFan(supplyAirFan);
  }

  HVACComponent ZoneHVACEnergyRecoveryVentilator::exhaustAirFan() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->exhaustAirFan();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setExhaustAirFan(const HVACComponent& exhaustAirFan) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setExhaustAirFan(exhaustAirFan);
  }

  boost::optional<ZoneHVACEnergyRecoveryVentilatorController> ZoneHVACEnergyRecoveryVentilator::controller() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->controller();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setController(const ZoneHVACEnergyRecoveryVentilatorController& controller) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setController(controller);
  }

  void ZoneHVACEnergyRecoveryVentilator::resetController() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->resetController();
  }

  double ZoneHVACEnergyRecoveryVentilator::ventilationRateperUnitFloorArea() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->ventilationRateperUnitFloorArea();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setVentilationRateperUnitFloorArea(ventilationRateperUnitFloorArea);
  }

  double ZoneHVACEnergyRecoveryVentilator::ventilationRateperOccupant() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->ventilationRateperOccupant();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setVentilationRateperOccupant(double ventilationRateperOccupant) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setVentilationRateperOccupant(ventilationRateperOccupant);
  }

  boost::optional<Node> ZoneHVACEnergyRecoveryVentilator::outdoorAirNode() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> ZoneHVACEnergyRecoveryVentilator::supplyAirFanInletNode() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->supplyAirFanInletNode();
  }

  boost::optional<Node> ZoneHVACEnergyRecoveryVentilator::exhaustAirFanInletNode() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->exhaustAirFanInletNode();
  }

  boost::optional<Node> ZoneHVACEnergyRecoveryVentilator::reliefAirNode() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->reliefAirNode();
  }

  std::vector<ModelObject> ZoneHVACEnergyRecoveryVentilator::children() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->children();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    Schedule ZoneHVACEnergyRecoveryVentilator_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_EnergyRecoveryVentilatorFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setAvailabilitySchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_EnergyRecoveryVentilatorFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    HVACComponent ZoneHVACEnergyRecoveryVentilator_Impl::heatExchanger() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setHeatExchanger(const HVACComponent& heatExchanger) {
      if ((heatExchanger.model() != model()) || !isEnergyRecoveryVentilatorHeatExchanger(heatExchanger)) {
        return false;
      }

      if (auto sensibleLatent = heatExchanger.optionalCast<HeatExchangerAirToAirSensibleAndLatent>()) {
        sensibleLatent->setSupplyAirOutletTemperatureControl(false);
      }

      const bool result = setPointer(ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName, heatExchanger.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilator_Impl::supplyAirFlowRate() const {
      return getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, true);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setSupplyAirFlowRate(double supplyAirFlowRate) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, supplyAirFlowRate);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::isSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::autosizeSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilator_Impl::exhaustAirFlowRate() const {
      return getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, true);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setExhaustAirFlowRate(double exhaustAirFlowRate) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, exhaustAirFlowRate);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::isExhaustAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::autosizeExhaustAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, "autosize"));
    }

    HVACComponent ZoneHVACEnergyRecoveryVentilator_Impl::supplyAirFan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setSupplyAirFan(const HVACComponent& supplyAirFan) {
      if ((supplyAirFan.model() != model()) || !isEnergyRecoveryVentilatorFan(supplyAirFan)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName, supplyAirFan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent ZoneHVACEnergyRecoveryVentilator_Impl::exhaustAirFan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setExhaustAirFan(const HVACComponent& exhaustAirFan) {
      if ((exhaustAirFan.model() != model()) || !isEnergyRecoveryVentilatorFan(exhaustAirFan)) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName, exhaustAirFan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<ZoneHVACEnergyRecoveryVentilatorController> ZoneHVACEnergyRecoveryVentilator_Impl::controller() const {
      return getObject<ModelObject>().getModelObjectTarget<ZoneHVACEnergyRecoveryVentilatorController>(
        ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setController(const ZoneHVACEnergyRecoveryVentilatorController& controllerObject) {
      if (controllerObject.model() != model()) {
        return false;
      }
      return setPointer(ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName, controllerObject.handle(), false);
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::resetController() {
      OS_ASSERT(setPointer(ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName, Handle(), false));
    }

    double ZoneHVACEnergyRecoveryVentilator_Impl::ventilationRateperUnitFloorArea() const {
      auto value = getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, ventilationRateperUnitFloorArea);
    }

    double ZoneHVACEnergyRecoveryVentilator_Impl::ventilationRateperOccupant() const {
      auto value = getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setVentilationRateperOccupant(double ventilationRateperOccupant) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, ventilationRateperOccupant);
    }

    std::vector<ModelObject> ZoneHVACEnergyRecoveryVentilator_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto supplyAirFan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName)) {
        result.push_back(*supplyAirFan);
      }
      if (auto exhaustAirFan =
            getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName)) {
        result.push_back(*exhaustAirFan);
      }
      if (auto heatExchanger =
            getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName)) {
        result.push_back(*heatExchanger);
      }
      if (auto controllerObject =
            getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName)) {
        result.push_back(*controllerObject);
      }
      return result;
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::inletNode() const {
      auto heatExchangerObject =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName);
      auto heatExchanger = heatExchangerObject ? heatExchangerObject->optionalCast<HeatExchangerAirToAirSensibleAndLatent>() : boost::none;
      if (!heatExchanger) {
        return boost::none;
      }
      return connectedNode(heatExchanger->secondaryAirInletModelObject());
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::outletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }
      return connectedNode(fan->outletModelObject());
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::outdoorAirNode() const {
      auto heatExchangerObject =
        getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName);
      auto heatExchanger = heatExchangerObject ? heatExchangerObject->optionalCast<HeatExchangerAirToAirSensibleAndLatent>() : boost::none;
      if (!heatExchanger) {
        return boost::none;
      }
      return connectedNode(heatExchanger->primaryAirInletModelObject());
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::supplyAirFanInletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }
      return connectedNode(fan->inletModelObject());
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::exhaustAirFanInletNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }
      return connectedNode(fan->inletModelObject());
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::reliefAirNode() const {
      auto fanObject = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }
      return connectedNode(fan->outletModelObject());
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      removeFromThermalZone();
      thermalZone.setUseIdealAirLoads(false);

      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      auto connections = zoneImpl->getZoneHVACEquipmentConnections();
      const auto objectName = getObject<ModelObject>().nameString();
      auto inlet = model().getOrCreateTransientByName<Node>(objectName + " Air Inlet Node");
      auto outlet = model().getOrCreateTransientByName<Node>(objectName + " Air Outlet Node");

      if (!connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->addEquipment(getObject<ModelObject>(), {outlet}, {}, {inlet})) {
        return false;
      }

      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::removeFromThermalZone() {
      auto zone = thermalZone();
      if (!zone) {
        maintainContainedAirPath();
        return;
      }

      auto inlet = inletNode();
      auto outlet = outletNode();
      auto zoneImpl = zone->getImpl<detail::ThermalZone_Impl>();
      if (auto connections = zoneImpl->zoneHVACEquipmentConnections()) {
        std::vector<Node> inletNodes;
        std::vector<Node> returnNodes;
        if (outlet) {
          inletNodes.push_back(*outlet);
        }
        if (inlet) {
          returnNodes.push_back(*inlet);
        }
        connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->removeEquipment(getObject<ModelObject>(), inletNodes, {}, returnNodes);
      }

      maintainContainedAirPath();
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::doCanonicalize(LoadContext& context) {
      ZoneHVACComponent_Impl::doCanonicalize(context);
      repairContainedAirPath(context);
    }

    unsigned ZoneHVACEnergyRecoveryVentilator_Impl::inletPort() const {
      return OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirInletNodeName;
    }

    unsigned ZoneHVACEnergyRecoveryVentilator_Impl::outletPort() const {
      return OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirOutletNodeName;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      (void)allowChildNodeRecovery;

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto heatExchangerObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName);
      auto supplyAirFanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName);
      auto exhaustAirFanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName);

      auto heatExchanger = heatExchangerObject ? heatExchangerObject->optionalCast<HeatExchangerAirToAirSensibleAndLatent>() : boost::none;
      auto supplyAirFan = supplyAirFanObject ? supplyAirFanObject->optionalCast<StraightComponent>() : boost::none;
      auto exhaustAirFan = exhaustAirFanObject ? exhaustAirFanObject->optionalCast<StraightComponent>() : boost::none;

      if (!heatExchanger || !supplyAirFan || !exhaustAirFan || !isEnergyRecoveryVentilatorHeatExchanger(*heatExchangerObject)
          || !isEnergyRecoveryVentilatorFan(*supplyAirFanObject) || !isEnergyRecoveryVentilatorFan(*exhaustAirFanObject)) {
        if (context) {
          addLoadWarning(*context, "ZoneHVAC:EnergyRecoveryVentilator '" + thisObject.nameString()
                                     + "' could not repair its contained air path because a required child is missing or unsupported.");
        }
        return false;
      }

      bool changed = false;
      bool nodeWiringChanged = false;
      auto trackNodeChange = [&](bool localChanged) {
        changed = localChanged || changed;
        nodeWiringChanged = localChanged || nodeWiringChanged;
      };

      const std::string baseName = thisObject.nameString();
      Node zoneExhaustNode = model().getOrCreateTransientByName<Node>(baseName + " Air Inlet Node");
      Node zoneInletNode = model().getOrCreateTransientByName<Node>(baseName + " Air Outlet Node");
      Node outdoorAirNodeValue = outdoorAirNode().value_or(model().getOrCreateTransientByName<Node>(baseName + " OA Node"));
      Node supplyAirFanInletNodeValue =
        supplyAirFanInletNode().value_or(model().getOrCreateTransientByName<Node>(baseName + " Supply Fan Inlet Node"));
      Node exhaustAirFanInletNodeValue =
        exhaustAirFanInletNode().value_or(model().getOrCreateTransientByName<Node>(baseName + " Exhaust Fan Inlet Node"));
      Node reliefAirNodeValue = reliefAirNode().value_or(model().getOrCreateTransientByName<Node>(baseName + " Exhaust Fan Outlet Node"));

      trackNodeChange(
        heatExchanger->getImpl<ModelObject_Impl>()->setPointer(heatExchanger->primaryAirInletPort(), outdoorAirNodeValue.handle(), false));
      trackNodeChange(
        heatExchanger->getImpl<ModelObject_Impl>()->setPointer(heatExchanger->primaryAirOutletPort(), supplyAirFanInletNodeValue.handle(), false));
      trackNodeChange(
        heatExchanger->getImpl<ModelObject_Impl>()->setPointer(heatExchanger->secondaryAirInletPort(), zoneExhaustNode.handle(), false));
      trackNodeChange(
        heatExchanger->getImpl<ModelObject_Impl>()->setPointer(heatExchanger->secondaryAirOutletPort(), exhaustAirFanInletNodeValue.handle(), false));

      trackNodeChange(supplyAirFan->getImpl<ModelObject_Impl>()->setPointer(supplyAirFan->inletPort(), supplyAirFanInletNodeValue.handle(), false));
      trackNodeChange(supplyAirFan->getImpl<ModelObject_Impl>()->setPointer(supplyAirFan->outletPort(), zoneInletNode.handle(), false));

      trackNodeChange(
        exhaustAirFan->getImpl<ModelObject_Impl>()->setPointer(exhaustAirFan->inletPort(), exhaustAirFanInletNodeValue.handle(), false));
      trackNodeChange(exhaustAirFan->getImpl<ModelObject_Impl>()->setPointer(exhaustAirFan->outletPort(), reliefAirNodeValue.handle(), false));

      if (nodeWiringChanged && context) {
        addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:EnergyRecoveryVentilator '" + baseName + "'.");
      }

      return changed;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
