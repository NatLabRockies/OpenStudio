/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"
#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/core/StringHelpers.hpp>

namespace openstudio {
namespace epmodel {

  ZoneHVACEnergyRecoveryVentilator::ZoneHVACEnergyRecoveryVentilator(const Model& model)
    : ZoneHVACComponent(ZoneHVACEnergyRecoveryVentilator::iddObjectType(), model) {
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

  std::vector<ModelObject> ZoneHVACEnergyRecoveryVentilator::children() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->children();
  }

  namespace detail {

    boost::optional<double> ZoneHVACEnergyRecoveryVentilator_Impl::supplyAirFlowRate() const {
      return getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, true);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setSupplyAirFlowRate(double supplyAirFlowRate) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, supplyAirFlowRate);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::isSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
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
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::autosizeExhaustAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, "autosize"));
    }

    double ZoneHVACEnergyRecoveryVentilator_Impl::ventilationRateperUnitFloorArea() const {
      const auto value = getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, ventilationRateperUnitFloorArea);
    }

    double ZoneHVACEnergyRecoveryVentilator_Impl::ventilationRateperOccupant() const {
      const auto value = getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setVentilationRateperOccupant(double ventilationRateperOccupant) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, ventilationRateperOccupant);
    }

    std::vector<ModelObject> ZoneHVACEnergyRecoveryVentilator_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto intermediate = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName)) {
        result.push_back(intermediate.get());
      }
      if (auto intermediate = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName)) {
        result.push_back(intermediate.get());
      }
      if (auto intermediate = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName)) {
        result.push_back(intermediate.get());
      }
      if (auto intermediate = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName)) {
        result.push_back(intermediate.get());
      }
      return result;
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::inletNode() const {
      if (!thermalZone()) {
        return boost::none;
      }
      auto result = model().getModelObjectByName<Node>(getObject<ModelObject>().nameString() + " Air Inlet Node");
      OS_ASSERT(result);
      return result;
    }

    boost::optional<Node> ZoneHVACEnergyRecoveryVentilator_Impl::outletNode() const {
      if (!thermalZone()) {
        return boost::none;
      }
      auto result = model().getModelObjectByName<Node>(getObject<ModelObject>().nameString() + " Air Outlet Node");
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      removeFromThermalZone();
      thermalZone.setUseIdealAirLoads(false);

      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      auto connections = zoneImpl->getZoneHVACEquipmentConnections();
      auto equipmentList = zoneImpl->zoneHVACEquipmentList();
      if (!equipmentList) {
        ZoneHVACEquipmentList newEquipmentList(model());
        if (!newEquipmentList.name()) {
          newEquipmentList.createName();
        }
        OS_ASSERT(connections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName, newEquipmentList.handle()));
        equipmentList = newEquipmentList;
      }

      if (!equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>()->addEquipment(getObject<ModelObject>())) {
        return false;
      }

      const auto objectName = getObject<ModelObject>().nameString();
      auto inlet = model().getOrCreateTransientByName<Node>(objectName + " Air Inlet Node");
      auto outlet = model().getOrCreateTransientByName<Node>(objectName + " Air Outlet Node");

      if (!connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneAirInletNode(outlet)) {
        return false;
      }
      if (!connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneReturnAirNode(inlet)) {
        return false;
      }

      return true;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::removeFromThermalZone() {
      auto zone = thermalZone();
      if (!zone) {
        disconnect();
        return;
      }

      auto inlet = inletNode();
      auto outlet = outletNode();
      auto zoneImpl = zone->getImpl<detail::ThermalZone_Impl>();
      if (auto equipmentList = zoneImpl->zoneHVACEquipmentList()) {
        equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>()->removeEquipment(getObject<ModelObject>());
      }

      if (auto connections = zoneImpl->zoneHVACEquipmentConnections()) {
        if (auto zoneInlet = connections->zoneAirInletNode()) {
          if (outlet && (*zoneInlet == *outlet)) {
            connections->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, Handle());
          }
        }
        if (auto zoneReturn = connections->zoneReturnAirNode()) {
          if (inlet && (*zoneReturn == *inlet)) {
            connections->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, Handle());
          }
        }
      }

      if (inlet) {
        inlet->remove();
      }
      if (outlet) {
        outlet->remove();
      }

      disconnect();
    }

    unsigned ZoneHVACEnergyRecoveryVentilator_Impl::inletPort() const {
      return OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirInletNodeName;
    }

    unsigned ZoneHVACEnergyRecoveryVentilator_Impl::outletPort() const {
      return OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
