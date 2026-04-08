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
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

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

bool isContainedAirPathComponent(const HVACComponent& component) {
  return component.optionalCast<StraightComponent>() || component.optionalCast<WaterToAirComponent>();
}

unsigned containedAirInletPort(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->inletPort();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airInletPort();
  }
  return 0u;
}

unsigned containedAirOutletPort(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->outletPort();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airOutletPort();
  }
  return 0u;
}

boost::optional<ModelObject> containedAirOutletModelObject(const HVACComponent& component) {
  if (auto straightComponent = component.optionalCast<StraightComponent>()) {
    return straightComponent->outletModelObject();
  }
  if (auto waterToAirComponent = component.optionalCast<WaterToAirComponent>()) {
    return waterToAirComponent->airOutletModelObject();
  }
  return boost::none;
}

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
  for (const auto& zone : model().getConcreteModelObjects<ThermalZone>()) {
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

bool ZoneHVACComponent_Impl::addToThermalZone(ThermalZone& thermalZone) {
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

  if (inletPort() != 0u && outletPort() != 0u) {
    const auto objectName = getObject<ModelObject>().nameString();
    auto inlet = model().getOrCreateTransientByName<Node>(objectName + " Air Inlet Node");
    auto outlet = model().getOrCreateTransientByName<Node>(objectName + " Air Outlet Node");

    if (!setPointer(inletPort(), inlet.handle(), false)) {
      return false;
    }
    if (!setPointer(outletPort(), outlet.handle(), false)) {
      return false;
    }
    if (!connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneAirInletNode(outlet)) {
      return false;
    }
    if (!connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneReturnAirNode(inlet)) {
      return false;
    }
  }

  return true;
}

void ZoneHVACComponent_Impl::removeFromThermalZone() {
  auto zone = thermalZone();
  if (!zone) {
    disconnect();
    return;
  }

  auto zoneImpl = zone->getImpl<detail::ThermalZone_Impl>();
  if (auto equipmentList = zoneImpl->zoneHVACEquipmentList()) {
    equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>()->removeEquipment(getObject<ModelObject>());
  }

  if (auto connections = zoneImpl->zoneHVACEquipmentConnections()) {
    if (auto zoneInlet = connections->zoneAirInletNode()) {
      if (auto thisOutlet = outletNode(); thisOutlet && (*zoneInlet == *thisOutlet)) {
        connections->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, Handle());
      }
    }
    if (auto zoneReturn = connections->zoneReturnAirNode()) {
      if (auto thisInlet = inletNode(); thisInlet && (*zoneReturn == *thisInlet)) {
        connections->setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, Handle());
      }
    }
  }

  if (inletPort() != 0u) {
    setPointer(inletPort(), Handle());
  }
  if (outletPort() != 0u) {
    setPointer(outletPort(), Handle());
  }

  disconnect();
}

std::vector<IdfObject> ZoneHVACComponent_Impl::remove() {
  removeFromThermalZone();
  return HVACComponent_Impl::remove();
}

bool ZoneHVACComponent_Impl::addToNode(Node& node) {
  auto airLoop = node.airLoopHVAC();
  if (!airLoop) {
    return false;
  }

  boost::optional<ThermalZone> zone;
  for (const auto& candidateZone : model().getConcreteModelObjects<ThermalZone>()) {
    auto connections = candidateZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
    if (!connections) {
      continue;
    }

    auto inletNode = connections->zoneAirInletNode();
    auto returnNode = connections->zoneReturnAirNode();
    if (inletNode && returnNode && (*inletNode == node) && (*returnNode == node)) {
      zone = candidateZone;
      break;
    }
  }
  if (!zone) {
    return false;
  }

  if (this->thermalZone()) {
    removeFromThermalZone();
  }

  if (!addToThermalZone(*zone)) {
    return false;
  }

  if (inletPort() == 0u || outletPort() == 0u) {
    return true;
  }

  auto outlet = model().getOrCreateTransientByName<Node>(getObject<ModelObject>().nameString() + " Outlet Node");
  if (!setPointer(inletPort(), node.handle(), false)) {
    return false;
  }
  if (!setPointer(outletPort(), outlet.handle(), false)) {
    return false;
  }

  auto connections = zone->getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  if (!connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneAirInletNode(outlet)) {
    return false;
  }
  return connections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneReturnAirNode(node);
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
