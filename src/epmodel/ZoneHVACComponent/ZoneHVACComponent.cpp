/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACComponent.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include "Mixer/AirLoopHVACReturnPlenum.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_Mixer_FieldEnums.hxx>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  ZoneHVACComponent::ZoneHVACComponent(std::shared_ptr<detail::ZoneHVACComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

  ZoneHVACComponent::ZoneHVACComponent(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

  unsigned ZoneHVACComponent::inletPort() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->inletPort();
  }

  boost::optional<Node> ZoneHVACComponent::inletNode() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->inletNode();
  }

  unsigned ZoneHVACComponent::outletPort() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->outletPort();
  }

  boost::optional<Node> ZoneHVACComponent::outletNode() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->outletNode();
  }

  boost::optional<ThermalZone> ZoneHVACComponent::thermalZone() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->thermalZone();
  }

  bool ZoneHVACComponent::addToThermalZone(ThermalZone& thermalZone) {
    return getImpl<detail::ZoneHVACComponent_Impl>()->addToThermalZone(thermalZone);
  }

  void ZoneHVACComponent::removeFromThermalZone() {
    getImpl<detail::ZoneHVACComponent_Impl>()->removeFromThermalZone();
  }

  bool ZoneHVACComponent::setReturnPlenum(const ThermalZone& plenumZone) {
    return getImpl<detail::ZoneHVACComponent_Impl>()->setReturnPlenum(plenumZone);
  }

  void ZoneHVACComponent::removeReturnPlenum() {
    getImpl<detail::ZoneHVACComponent_Impl>()->removeReturnPlenum();
  }

  boost::optional<AirLoopHVACReturnPlenum> ZoneHVACComponent::returnPlenum() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->returnPlenum();
  }

  bool ZoneHVACComponent::addToNode(Node& node) {
    return getImpl<detail::ZoneHVACComponent_Impl>()->addToNode(node);
  }

  boost::optional<AirLoopHVAC> ZoneHVACComponent::airLoopHVAC() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->airLoopHVAC();
  }

  bool ZoneHVACComponent::removeFromAirLoopHVAC() {
    return getImpl<detail::ZoneHVACComponent_Impl>()->removeFromAirLoopHVAC();
  }

  boost::optional<ModelObject> ZoneHVACComponent::airInletModelObject() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->airInletModelObject();
  }

  boost::optional<ModelObject> ZoneHVACComponent::airOutletModelObject() const {
    return getImpl<detail::ZoneHVACComponent_Impl>()->airOutletModelObject();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned ZoneHVACComponent_Impl::inletPort() const {
      return 0u;
    }

    unsigned ZoneHVACComponent_Impl::outletPort() const {
      return 0u;
    }

    boost::optional<Node> ZoneHVACComponent_Impl::inletNode() const {
      if (inletPort() == 0u) {
        return boost::none;
      }
      return getObject<ModelObject>().getModelObjectTarget<Node>(inletPort());
    }

    boost::optional<Node> ZoneHVACComponent_Impl::outletNode() const {
      if (outletPort() == 0u) {
        return boost::none;
      }
      return getObject<ModelObject>().getModelObjectTarget<Node>(outletPort());
    }

    boost::optional<ThermalZone> ZoneHVACComponent_Impl::thermalZone() const {
      const auto thisObject = getObject<ModelObject>();
      for (const auto& zone : model().getModelObjects<ThermalZone>()) {
        auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentList();
        if (!equipmentList) {
          continue;
        }

        const auto equipment = equipmentList->equipment();
        if (std::ranges::find(equipment, thisObject) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    // Attach this component as ordinary zone HVAC equipment. The component is added to the zone equipment list and, when it
    // exposes inlet/outlet ports, wired in the normal zone-equipment pattern: component inlet from a zone exhaust node and
    // component outlet to a zone inlet node. This is intentionally separate from addToNode, which is only for the inlet-side
    // mixer topology where the ZoneHVAC unit sits downstream of an air terminal.
    bool ZoneHVACComponent_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (thermalZone.model() != model()) {
        return false;
      }

      auto thisComponent = getObject<ZoneHVACComponent>();

      removeFromThermalZone();

      thermalZone.setUseIdealAirLoads(false);

      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      auto equipmentList = zoneImpl->getZoneHVACEquipmentList();
      equipmentList.addEquipment(thisComponent);

      if (inletPort() != 0 && outletPort() != 0) {
        const auto objectName = getObject<ModelObject>().nameString();
        auto inlet = model().getOrCreateTransientByName<Node>(objectName + " Air Inlet Node");
        auto outlet = model().getOrCreateTransientByName<Node>(objectName + " Air Outlet Node");

        OS_ASSERT(setPointer(inletPort(), inlet.handle(), false));
        OS_ASSERT(setPointer(outletPort(), outlet.handle(), false));

        auto connections = zoneImpl->getZoneHVACEquipmentConnections();
        auto connectionsImpl = connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
        OS_ASSERT(connectionsImpl);
        OS_ASSERT(connectionsImpl->addZoneAirInletNode(outlet));
        OS_ASSERT(connectionsImpl->addZoneAirExhaustNode(inlet));
      }

      return true;
    }

    // Unregister this component from whichever zone-topology path attached it. Ordinary zone HVAC is listed on the
    // ZoneHVAC:EquipmentList and wired between a zone exhaust node and a zone inlet node. The addToNode path is different:
    // it inserts this component downstream of an AirTerminal:SingleDuct:Mixer, so removal also has to clear the mixer's
    // secondary air inlet and ZoneHVAC unit fields. Both paths leave the component disconnected from zone nodes and no
    // longer listed as zone equipment.
    void ZoneHVACComponent_Impl::removeFromThermalZone() {
      auto zone = thermalZone();
      if (!zone) {
        disconnect();
        return;
      }

      auto zoneImpl = zone->getImpl<detail::ThermalZone_Impl>();
      boost::optional<AirTerminalSingleDuctInletSideMixer> inletSideMixer;
      if (auto inlet = inletNode()) {
        for (const auto& source : inlet->sources()) {
          auto candidate = source.optionalCast<AirTerminalSingleDuctInletSideMixer>();
          if (!candidate) {
            continue;
          }
          auto terminalOutlet = candidate->outletModelObject();
          if (terminalOutlet && (*terminalOutlet == inlet->cast<ModelObject>())) {
            inletSideMixer = candidate;
            break;
          }
        }
      }

      if (inletSideMixer) {
        // This component was attached through addToNode as the downstream ZoneHVAC unit for an inlet-side mixer. In that
        // topology the component outlet is a zone inlet node, while the mixer's secondary inlet is the zone exhaust node.
        if (auto connections = zoneImpl->zoneHVACEquipmentConnections()) {
          auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
          OS_ASSERT(connectionsImpl);
          if (auto outlet = outletNode()) {
            connectionsImpl->removeZoneAirInletNode(*outlet);
          }
          if (auto secondaryAirInlet = inletSideMixer->secondaryAirInletNode()) {
            connectionsImpl->removeZoneAirExhaustNode(*secondaryAirInlet);
          }
        }

        if (auto equipmentList = zoneImpl->zoneHVACEquipmentList()) {
          equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>()->removeEquipment(getObject<ModelObject>());
        }

        auto terminalImpl = inletSideMixer->getImpl<detail::ModelObject_Impl>();
        terminalImpl->setPointer(inletSideMixer->secondaryAirInletPort(), Handle(), false);
        terminalImpl->setString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectType, "", false);
        terminalImpl->setString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectName, "", false);

        if (inletPort() != 0u) {
          setPointer(inletPort(), Handle(), false);
        }
        if (outletPort() != 0u) {
          setPointer(outletPort(), Handle(), false);
        }

        disconnect();
        return;
      }

      if (auto connections = zoneImpl->zoneHVACEquipmentConnections()) {
        auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
        OS_ASSERT(connectionsImpl);
        if (auto outlet = outletNode()) {
          OS_ASSERT(connectionsImpl->removeZoneAirInletNode(*outlet));
        }
        if (auto inlet = inletNode()) {
          OS_ASSERT(connectionsImpl->removeZoneAirExhaustNode(*inlet));
        }
      }

      if (auto equipmentList = zoneImpl->zoneHVACEquipmentList()) {
        equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>()->removeEquipment(getObject<ModelObject>());
      }

      if (inletPort() != 0u) {
        setPointer(inletPort(), Handle(), false);
      }
      if (outletPort() != 0u) {
        setPointer(outletPort(), Handle(), false);
      }

      disconnect();
    }

    std::vector<IdfObject> ZoneHVACComponent_Impl::remove() {
      removeFromThermalZone();
      return HVACComponent_Impl::remove();
    }

    // This is the inlet-side-mixer integration path for air-based zone HVAC, not the ordinary zone-equipment attach path.
    // Use addToThermalZone for equipment that simply participates between the zone exhaust and zone inlet nodes. Here `node`
    // is the outlet of an AirTerminal:SingleDuct:Mixer that already serves a zone. The mixer outlet becomes this component's
    // inlet, this component's outlet becomes a zone inlet, and a zone exhaust node feeds the mixer's secondary inlet. EnergyPlus
    // also requires the mixer to name the downstream ZoneHVAC unit, so this method keeps the equipment connections object and
    // the mixer's ZoneHVACUnitObjectType/Name fields aligned. Derived classes should override this when that topology is invalid.
    bool ZoneHVACComponent_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      boost::optional<ThermalZone> zone;
      for (const auto& candidateZone : model().getModelObjects<ThermalZone>()) {
        auto connections = candidateZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
        if (!connections) {
          continue;
        }

        const auto inletNodes = connections->zoneAirInletNodes();
        if (std::ranges::find(inletNodes, node) != inletNodes.end()) {
          zone = candidateZone;
          break;
        }
      }
      if (!zone) {
        return false;
      }

      boost::optional<AirTerminalSingleDuctInletSideMixer> inletSideMixer;
      for (const auto& source : node.sources()) {
        auto candidate = source.optionalCast<AirTerminalSingleDuctInletSideMixer>();
        if (!candidate) {
          continue;
        }
        auto terminalOutlet = candidate->outletModelObject();
        if (terminalOutlet && (*terminalOutlet == node.cast<ModelObject>())) {
          inletSideMixer = candidate;
          break;
        }
      }
      if (!inletSideMixer) {
        return false;
      }

      if (inletPort() == 0u || outletPort() == 0u) {
        return false;
      }

      if (this->thermalZone()) {
        removeFromThermalZone();
      }

      if (!zone->setUseIdealAirLoads(false)) {
        return false;
      }

      const auto thisObject = getObject<ModelObject>();
      auto outlet = model().getOrCreateTransientByName<Node>(thisObject.nameString() + " Outlet Node");
      auto exhaust = model().getOrCreateTransientByName<Node>(zone->nameString() + " Exhaust Air Node");
      if (!setPointer(inletPort(), node.handle(), false)) {
        return false;
      }
      if (!setPointer(outletPort(), outlet.handle(), false)) {
        return false;
      }
      auto terminalImpl = inletSideMixer->getImpl<detail::ModelObject_Impl>();
      if (!terminalImpl->setPointer(inletSideMixer->secondaryAirInletPort(), exhaust.handle(), false)) {
        return false;
      }
      if (!terminalImpl->setString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectType, thisObject.iddObject().name(), false)) {
        return false;
      }
      if (!terminalImpl->setString(openstudio::AirTerminal_SingleDuct_MixerFields::ZoneHVACUnitObjectName, thisObject.nameString(), false)) {
        return false;
      }

      auto zoneImpl = zone->getImpl<detail::ThermalZone_Impl>();
      auto connections = zoneImpl->getZoneHVACEquipmentConnections();
      auto connectionsImpl = connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
      OS_ASSERT(connectionsImpl);
      if (!connectionsImpl->addZoneAirInletNode(outlet)) {
        return false;
      }
      if (!connectionsImpl->addZoneAirExhaustNode(exhaust)) {
        return false;
      }

      return zoneImpl->getZoneHVACEquipmentList().addEquipment(thisObject);
    }

    boost::optional<AirLoopHVAC> ZoneHVACComponent_Impl::airLoopHVAC() const {
      if (auto node = inletNode()) {
        return node->airLoopHVAC();
      }
      return boost::none;
    }

    bool ZoneHVACComponent_Impl::removeFromAirLoopHVAC() {
      return false;
    }

    boost::optional<ModelObject> ZoneHVACComponent_Impl::airInletModelObject() const {
      if (auto node = inletNode()) {
        return node->cast<ModelObject>();
      }
      return boost::none;
    }

    boost::optional<ModelObject> ZoneHVACComponent_Impl::airOutletModelObject() const {
      if (auto node = outletNode()) {
        return node->cast<ModelObject>();
      }
      return boost::none;
    }

    bool ZoneHVACComponent_Impl::setReturnPlenum(const ThermalZone&) {
      return false;
    }

    void ZoneHVACComponent_Impl::removeReturnPlenum() {}

    boost::optional<AirLoopHVACReturnPlenum> ZoneHVACComponent_Impl::returnPlenum() const {
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
