/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "Splitter/Splitter.hpp"

#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

WaterToAirComponent::WaterToAirComponent(std::shared_ptr<detail::WaterToAirComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

WaterToAirComponent::WaterToAirComponent(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

unsigned WaterToAirComponent::airInletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airInletPort();
}

unsigned WaterToAirComponent::airOutletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airOutletPort();
}

boost::optional<ModelObject> WaterToAirComponent::airInletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airInletModelObject();
}

boost::optional<ModelObject> WaterToAirComponent::airOutletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airOutletModelObject();
}

unsigned WaterToAirComponent::waterInletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterInletPort();
}

unsigned WaterToAirComponent::waterOutletPort() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterOutletPort();
}

boost::optional<ModelObject> WaterToAirComponent::waterInletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterInletModelObject();
}

boost::optional<ModelObject> WaterToAirComponent::waterOutletModelObject() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->waterOutletModelObject();
}

boost::optional<AirLoopHVAC> WaterToAirComponent::airLoopHVAC() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->airLoopHVAC();
}

boost::optional<PlantLoop> WaterToAirComponent::plantLoop() const {
  return getImpl<detail::WaterToAirComponent_Impl>()->plantLoop();
}

bool WaterToAirComponent::addToNode(Node& node) {
  return getImpl<detail::WaterToAirComponent_Impl>()->addToNode(node);
}

bool WaterToAirComponent::addToSplitter(Splitter& splitter) {
  return getImpl<detail::WaterToAirComponent_Impl>()->addToSplitter(splitter);
}

std::vector<IdfObject> WaterToAirComponent::remove() {
  return getImpl<detail::WaterToAirComponent_Impl>()->remove();
}

void WaterToAirComponent::disconnectWaterSide() {
  getImpl<detail::WaterToAirComponent_Impl>()->disconnectWaterSide();
}

void WaterToAirComponent::disconnectAirSide() {
  getImpl<detail::WaterToAirComponent_Impl>()->disconnectAirSide();
}

bool WaterToAirComponent::removeFromAirLoopHVAC() {
  return getImpl<detail::WaterToAirComponent_Impl>()->removeFromAirLoopHVAC();
}

bool WaterToAirComponent::removeFromPlantLoop() {
  return getImpl<detail::WaterToAirComponent_Impl>()->removeFromPlantLoop();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool WaterToAirComponent_Impl::addToOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem, Node& node) {
  auto thisObject = getObject<ModelObject>();
  if (!thisObject.name()) {
    thisObject.createName();
    if (!thisObject.name()) {
      return false;
    }
  }
  if (!detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl::isValidOASystemEquipment(thisObject)) {
    LOG_FREE(Warn, "openstudio.epmodel.Model",
             "Refusing to add " << thisObject.briefDescription() << " to " << oaSystem.briefDescription()
                                << " because the EnergyPlus IDD does not include type '" << thisObject.iddObject().name()
                                << "' in validOASysEquipmentTypes");
    return false;
  }

  const bool onOutdoorAirStream = oaSystem.oaComponent(node.handle()).has_value();
  const bool onReliefStream = oaSystem.reliefComponent(node.handle()).has_value();
  if (!onOutdoorAirStream && !onReliefStream) {
    return false;
  }

  auto oaSystemImpl = oaSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>();
  OS_ASSERT(oaSystemImpl);
  auto equipmentListImpl =
    oaSystemImpl->airLoopHVACOutdoorAirSystemEquipmentList().getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
  OS_ASSERT(equipmentListImpl);
  if (!equipmentListImpl->containsEquipment(thisObject) && !equipmentListImpl->addEquipment(thisObject)) {
    return false;
  }

  auto path = onOutdoorAirStream ? oaSystem.oaComponents() : oaSystem.reliefComponents();
  const auto nodeIt = std::find_if(path.begin(), path.end(), [&](const auto& object) { return object.handle() == node.handle(); });
  if (nodeIt == path.end()) {
    return false;
  }

  auto inletNode = node;
  auto outletNode = node;
  if (path.size() == 1u) {
    auto newNode = model().getOrCreateTransientByName<Node>(node.nameString() + " - " + thisObject.nameString() + " Outlet");
    if (onOutdoorAirStream) {
      outletNode = newNode;
      if (!oaSystemImpl->setOutdoorAirStreamNode(newNode)) {
        return false;
      }
    } else {
      inletNode = newNode;
      if (!oaSystemImpl->setReliefAirStreamNode(newNode)) {
        return false;
      }
    }
  } else {
    const auto index = static_cast<std::size_t>(std::distance(path.begin(), nodeIt));
    const bool hasPreviousComponent = index >= 1u && !path[index - 1u].optionalCast<Node>();
    const bool hasNextComponent = (index + 1u) < path.size() && !path[index + 1u].optionalCast<Node>();
    auto newNode = model().getOrCreateTransientByName<Node>(node.nameString() + " - " + thisObject.nameString() + " Outlet");

    if (!hasNextComponent && hasPreviousComponent) {
      inletNode = newNode;
      if (onOutdoorAirStream) {
        if (!oaSystemImpl->updateOutdoorAirStreamOutletNode(path[index - 1u], newNode)) {
          return false;
        }
      } else if (!oaSystemImpl->updateReliefAirStreamOutletNode(path[index - 1u], newNode)) {
        return false;
      }
    } else {
      outletNode = newNode;
      if (hasNextComponent) {
        if (onOutdoorAirStream) {
          if (!oaSystemImpl->updateOutdoorAirStreamInletNode(path[index + 1u], newNode)) {
            return false;
          }
        } else if (!oaSystemImpl->updateReliefAirStreamInletNode(path[index + 1u], newNode)) {
          return false;
        }
      }
    }
  }

  if (!setPointer(airInletPort(), inletNode.handle(), false) || !setPointer(airOutletPort(), outletNode.handle(), false)) {
    return false;
  }

  return oaSystemImpl->rewriteEquipmentListOrder();
}

bool WaterToAirComponent_Impl::removeFromOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem) {
  auto inletObject = airInletModelObject();
  auto outletObject = airOutletModelObject();
  if (!inletObject || !outletObject) {
    return false;
  }

  auto inletNode = inletObject->optionalCast<Node>();
  auto outletNode = outletObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return false;
  }

  const auto thisObject = getObject<ModelObject>();
  const bool onOutdoorAirStream = oaSystem.oaComponent(handle()).has_value();
  const bool onReliefStream = oaSystem.reliefComponent(handle()).has_value();
  if (!onOutdoorAirStream && !onReliefStream) {
    return false;
  }

  auto path = onOutdoorAirStream ? oaSystem.oaComponents() : oaSystem.reliefComponents();
  auto it = std::find_if(path.begin(), path.end(), [&](const auto& object) { return object.handle() == thisObject.handle(); });
  if (it == path.end()) {
    return false;
  }

  auto oaSystemImpl = oaSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>();
  OS_ASSERT(oaSystemImpl);
  const auto index = static_cast<std::size_t>(std::distance(path.begin(), it));
  if (path.size() == 3u) {
    if (onOutdoorAirStream) {
      if (!oaSystemImpl->setOutdoorAirStreamNode(*inletNode)) {
        return false;
      }
    } else if (!oaSystemImpl->setReliefAirStreamNode(*outletNode)) {
      return false;
    }
  } else if (index >= 1u && (index + 1u) < path.size()) {
    auto previousNode = path[index - 1u].optionalCast<Node>();
    auto nextNode = path[index + 1u].optionalCast<Node>();
    if (!previousNode || !nextNode) {
      return false;
    }

    if (index >= 2u) {
      if (onOutdoorAirStream) {
        if (!oaSystemImpl->updateOutdoorAirStreamOutletNode(path[index - 2u], *previousNode)) {
          return false;
        }
      } else if (!oaSystemImpl->updateReliefAirStreamOutletNode(path[index - 2u], *previousNode)) {
        return false;
      }
    }
    if ((index + 2u) < path.size()) {
      if (onOutdoorAirStream) {
        if (!oaSystemImpl->updateOutdoorAirStreamInletNode(path[index + 2u], *previousNode)) {
          return false;
        }
      } else if (!oaSystemImpl->updateReliefAirStreamInletNode(path[index + 2u], *previousNode)) {
        return false;
      }
    } else if (onOutdoorAirStream) {
      if (!oaSystemImpl->setOutdoorAirStreamNode(*previousNode)) {
        return false;
      }
    } else if (!oaSystemImpl->setReliefAirStreamNode(*previousNode)) {
      return false;
    }
  }

  disconnectAirSide();
  auto equipmentListImpl =
    oaSystemImpl->airLoopHVACOutdoorAirSystemEquipmentList().getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
  OS_ASSERT(equipmentListImpl);
  equipmentListImpl->removeEquipment(thisObject);
  return oaSystemImpl->rewriteEquipmentListOrder();
}

bool WaterToAirComponent_Impl::insertOnBranch(Node& node, const Branch& branch, unsigned inletPort, unsigned outletPort) {
  const auto nodeName = node.name();
  if (!nodeName) {
    return false;
  }

  auto thisObject = getObject<ModelObject>();
  if (!thisObject.name()) {
    thisObject.createName();
    if (!thisObject.name()) {
      return false;
    }
  }

  const auto thisName = thisObject.nameString();
  auto components = branch.components();
  if (components.empty()) {
    const std::string newInletName = *nodeName;
    const std::string newOutletName = *nodeName + " - " + thisName + " Outlet";

    if (!branch.getImpl<detail::Branch_Impl>()->appendComponent(thisObject, newInletName, newOutletName)) {
      return false;
    }

    auto newInletNode = model().getOrCreateTransientByName<Node>(newInletName);
    auto newOutletNode = model().getOrCreateTransientByName<Node>(newOutletName);
    setPointer(inletPort, newInletNode.handle(), false);
    setPointer(outletPort, newOutletNode.handle(), false);
    return true;
  }

  for (std::size_t i = 0; i < components.size(); ++i) {
    auto inletNode = branch.componentInletNode(static_cast<unsigned>(i));
    auto outletNode = branch.componentOutletNode(static_cast<unsigned>(i));

    const bool matchesInlet = inletNode && openstudio::istringEqual(inletNode->nameString(), *nodeName);
    const bool matchesOutlet = outletNode && openstudio::istringEqual(outletNode->nameString(), *nodeName);
    if (!matchesInlet && !matchesOutlet) {
      continue;
    }

    const std::string newNodeName = *nodeName + " - " + thisName + " Outlet";
    const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1u);

    std::string newInletName;
    std::string newOutletName;
    if (matchesOutlet && (i + 1u == components.size())) {
      newInletName = newNodeName;
      newOutletName = *nodeName;
    } else {
      newInletName = *nodeName;
      newOutletName = newNodeName;
    }

    if (!branch.getImpl<detail::Branch_Impl>()->insertComponent(insertIndex, thisObject, newInletName, newOutletName)) {
      return false;
    }

    auto newInletNode = model().getOrCreateTransientByName<Node>(newInletName);
    auto newOutletNode = model().getOrCreateTransientByName<Node>(newOutletName);
    setPointer(inletPort, newInletNode.handle(), false);
    setPointer(outletPort, newOutletNode.handle(), false);

    auto newNode = model().getOrCreateTransientByName<Node>(newNodeName);
    if (matchesInlet) {
      return branch.getImpl<detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode);
    }
    return branch.getImpl<detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode);
  }

  return false;
}

boost::optional<ModelObject> WaterToAirComponent_Impl::airInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(airInletPort());
}

boost::optional<ModelObject> WaterToAirComponent_Impl::airOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(airOutletPort());
}

boost::optional<ModelObject> WaterToAirComponent_Impl::waterInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(waterInletPort());
}

boost::optional<ModelObject> WaterToAirComponent_Impl::waterOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(waterOutletPort());
}

bool WaterToAirComponent_Impl::addToNode(Node& node) {
  const auto nodeObject = node.cast<ModelObject>();
  if (airInletModelObject() == nodeObject || airOutletModelObject() == nodeObject || waterInletModelObject() == nodeObject
      || waterOutletModelObject() == nodeObject) {
    return false;
  }
  if (auto oaSystem = node.airLoopHVACOutdoorAirSystem()) {
    return addToOutdoorAirSystem(*oaSystem, node);
  }

  if (auto airLoop = node.airLoopHVAC()) {
    if (airLoop->demandComponent(node.handle())) {
      return false;
    }

    auto branchList = airLoop->getImpl<detail::AirLoopHVAC_Impl>()->branchList();
    auto branches = branchList.branches();
    if (branches.empty()) {
      return false;
    }

    removeFromAirLoopHVAC();
    if (!insertOnBranch(node, branches.front(), airInletPort(), airOutletPort())) {
      return false;
    }

    airLoop->getImpl<detail::AirLoopHVAC_Impl>()->syncSetpointManagerMixedAirFanNodes();
    return true;
  }

  auto plantLoop = node.plantLoop();
  if (!plantLoop) {
    return false;
  }

  if (!plantLoop->demandComponent(node.handle())) {
    return false;
  }

  auto branch = plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
  if (!branch) {
    return false;
  }

  removeFromPlantLoop();
  return insertOnBranch(node, *branch, waterInletPort(), waterOutletPort());
}

bool WaterToAirComponent_Impl::addToSplitter(Splitter&) {
  return false;
}

std::vector<IdfObject> WaterToAirComponent_Impl::remove() {
  if (!isRemovable()) {
    return {};
  }
  removeFromAirLoopHVAC();
  removeFromPlantLoop();
  return HVACComponent_Impl::remove();
}

void WaterToAirComponent_Impl::disconnectWaterSide() {
  setPointer(waterInletPort(), Handle(), false);
  setPointer(waterOutletPort(), Handle(), false);
}

void WaterToAirComponent_Impl::disconnectAirSide() {
  setPointer(airInletPort(), Handle(), false);
  setPointer(airOutletPort(), Handle(), false);
}

void WaterToAirComponent_Impl::disconnect() {
  disconnectWaterSide();
  disconnectAirSide();
}

bool WaterToAirComponent_Impl::removeFromAirLoopHVAC() {
  auto thisObject = getObject<ModelObject>();
  auto inletObject = airInletModelObject();
  auto outletObject = airOutletModelObject();
  if (!inletObject || !outletObject) {
    return false;
  }

  auto inletNode = inletObject->optionalCast<Node>();
  auto outletNode = outletObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return false;
  }

  for (auto oaSystem : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
    if (oaSystem.component(handle())) {
      return removeFromOutdoorAirSystem(oaSystem);
    }
  }

  auto airLoop = thisObject.cast<WaterToAirComponent>().airLoopHVAC();
  if (!airLoop || !airLoop->supplyComponent(handle())) {
    return false;
  }

  auto branchList = airLoop->getImpl<detail::AirLoopHVAC_Impl>()->branchList();
  auto branches = branchList.branches();
  if (branches.empty()) {
    return false;
  }

  auto branch = branches.front();
  auto components = branch.components();
  for (unsigned i = 0; i < components.size(); ++i) {
    if (components[i] != thisObject) {
      continue;
    }
    if (i + 1u < components.size()) {
      if (!branch.getImpl<detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
        return false;
      }
    }
    if (!branch.getImpl<detail::Branch_Impl>()->removeComponent(i)) {
      return false;
    }
    airLoop->getImpl<detail::AirLoopHVAC_Impl>()->syncSetpointManagerMixedAirFanNodes();
    return true;
  }

  return false;
}

bool WaterToAirComponent_Impl::removeFromPlantLoop() {
  auto thisObject = getObject<ModelObject>();
  auto plantLoop = thisObject.cast<WaterToAirComponent>().plantLoop();
  if (!plantLoop) {
    return false;
  }

  auto inletObject = waterInletModelObject();
  auto outletObject = waterOutletModelObject();
  if (!inletObject || !outletObject) {
    return false;
  }

  auto inletNode = inletObject->optionalCast<Node>();
  auto outletNode = outletObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return false;
  }

  auto branch = plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(*inletNode);
  if (!branch) {
    branch = plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(*outletNode);
  }
  if (!branch) {
    return false;
  }

  auto components = branch->components();
  for (unsigned i = 0; i < components.size(); ++i) {
    if (components[i] != thisObject) {
      continue;
    }
    if (i + 1u < components.size()) {
      if (!branch->getImpl<detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
        return false;
      }
    }
    return branch->getImpl<detail::Branch_Impl>()->removeComponent(i);
  }

  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
