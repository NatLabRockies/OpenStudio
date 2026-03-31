/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirToAirComponent/AirToAirComponent.hpp"
#include "AirToAirComponent/AirToAirComponent_Impl.hpp"

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/IddFieldProperties.hpp>

#include <algorithm>
#include <sstream>

namespace openstudio {
namespace epmodel {

AirToAirComponent::AirToAirComponent(IddObjectType type, const Model& model) : HVACComponent(type, model) {}

AirToAirComponent::AirToAirComponent(std::shared_ptr<detail::AirToAirComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

unsigned AirToAirComponent::primaryAirInletPort() const {
  return getImpl<detail::AirToAirComponent_Impl>()->primaryAirInletPort();
}

unsigned AirToAirComponent::primaryAirOutletPort() const {
  return getImpl<detail::AirToAirComponent_Impl>()->primaryAirOutletPort();
}

unsigned AirToAirComponent::secondaryAirInletPort() const {
  return getImpl<detail::AirToAirComponent_Impl>()->secondaryAirInletPort();
}

unsigned AirToAirComponent::secondaryAirOutletPort() const {
  return getImpl<detail::AirToAirComponent_Impl>()->secondaryAirOutletPort();
}

boost::optional<ModelObject> AirToAirComponent::primaryAirInletModelObject() const {
  return getImpl<detail::AirToAirComponent_Impl>()->primaryAirInletModelObject();
}

boost::optional<ModelObject> AirToAirComponent::primaryAirOutletModelObject() const {
  return getImpl<detail::AirToAirComponent_Impl>()->primaryAirOutletModelObject();
}

boost::optional<ModelObject> AirToAirComponent::secondaryAirInletModelObject() const {
  return getImpl<detail::AirToAirComponent_Impl>()->secondaryAirInletModelObject();
}

boost::optional<ModelObject> AirToAirComponent::secondaryAirOutletModelObject() const {
  return getImpl<detail::AirToAirComponent_Impl>()->secondaryAirOutletModelObject();
}

bool AirToAirComponent::addToNode(Node& node) {
  return getImpl<detail::AirToAirComponent_Impl>()->addToNode(node);
}

std::vector<IdfObject> AirToAirComponent::remove() {
  return getImpl<detail::AirToAirComponent_Impl>()->remove();
}

namespace detail {

namespace {

boost::optional<ModelObject> resolveNodeField(const ModelObject& object, unsigned port) {
  if (port == 0u) {
    return boost::none;
  }

  if (auto nodeName = object.getString(port)) {
    if (nodeName->empty()) {
      return boost::none;
    }
    if (auto node = object.getModelObjectTarget<openstudio::epmodel::Node>(port)) {
      return node->cast<ModelObject>();
    }
    try {
      auto resolved = object.model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
      return resolved.cast<ModelObject>();
    } catch (...) {
      return boost::none;
    }
  }

  return boost::none;
}

void canonicalizeNodePort(ModelObject_Impl& impl, unsigned port, const char* label, LoadContext& context) {
  if (port == 0u) {
    return;
  }

  auto nodeName = impl.getString(port);
  if (!(nodeName && !nodeName->empty())) {
    return;
  }

  if (auto iddField = impl.iddObject().getField(port)) {
    if (iddField->properties().type != openstudio::IddFieldType::NodeType) {
      std::ostringstream oss;
      oss << "AirToAirComponent canonicalize: expected NodeType for " << label << " port at index " << port << " on object '"
          << impl.getObject<ModelObject>().nameString() << "' (" << impl.iddObject().name() << ") but field '" << iddField->name()
          << "' has type '" << iddField->properties().type.valueDescription() << "'.";
      detail::addLoadError(context, oss.str());
      return;
    }
  } else {
    std::ostringstream oss;
    oss << "AirToAirComponent canonicalize: missing IDD field definition for " << label << " port index " << port << " on object '"
        << impl.getObject<ModelObject>().nameString() << "' (" << impl.iddObject().name() << ").";
    detail::addLoadError(context, oss.str());
    return;
  }

  auto node = impl.model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
  if (!impl.setPointer(port, node.handle(), false)) {
    std::ostringstream oss;
    oss << "AirToAirComponent canonicalize: failed to set node pointer for " << label << " port index " << port << " on object '"
        << impl.getObject<ModelObject>().nameString() << "' (" << impl.iddObject().name() << ") to transient Node '" << *nodeName << "'.";
    detail::addLoadError(context, oss.str());
  }
}

}  // namespace

unsigned AirToAirComponent_Impl::primaryAirInletPort() const {
  return 0u;
}

unsigned AirToAirComponent_Impl::primaryAirOutletPort() const {
  return 0u;
}

unsigned AirToAirComponent_Impl::secondaryAirInletPort() const {
  return 0u;
}

unsigned AirToAirComponent_Impl::secondaryAirOutletPort() const {
  return 0u;
}

boost::optional<ModelObject> AirToAirComponent_Impl::primaryAirInletModelObject() const {
  return resolveNodeField(getObject<ModelObject>(), primaryAirInletPort());
}

boost::optional<ModelObject> AirToAirComponent_Impl::primaryAirOutletModelObject() const {
  return resolveNodeField(getObject<ModelObject>(), primaryAirOutletPort());
}

boost::optional<ModelObject> AirToAirComponent_Impl::secondaryAirInletModelObject() const {
  return resolveNodeField(getObject<ModelObject>(), secondaryAirInletPort());
}

boost::optional<ModelObject> AirToAirComponent_Impl::secondaryAirOutletModelObject() const {
  return resolveNodeField(getObject<ModelObject>(), secondaryAirOutletPort());
}

bool AirToAirComponent_Impl::addToNode(Node& node) {
  if (auto oaSystem = node.airLoopHVACOutdoorAirSystem()) {
    return addToOutdoorAirSystem(*oaSystem, node);
  }
  return false;
}

void AirToAirComponent_Impl::disconnect() {
  setPointer(primaryAirInletPort(), Handle(), false);
  setPointer(primaryAirOutletPort(), Handle(), false);
  setPointer(secondaryAirInletPort(), Handle(), false);
  setPointer(secondaryAirOutletPort(), Handle(), false);
}

bool AirToAirComponent_Impl::addToOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem, Node& node) {
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

  const auto oaComponents = oaSystem.oaComponents();
  const auto reliefComponents = oaSystem.reliefComponents();
  auto outboardOANode = oaSystem.outboardOANode();
  auto outboardReliefNode = oaSystem.outboardReliefNode();
  if (!outboardOANode || !outboardReliefNode) {
    return false;
  }

  boost::optional<Node> oaNode;
  boost::optional<Node> reliefNode;
  boost::optional<ModelObject> nextSupplyComponent;
  boost::optional<ModelObject> prevSupplyComponent;
  boost::optional<ModelObject> nextReliefComponent;
  boost::optional<ModelObject> prevReliefComponent;

  if (onOutdoorAirStream) {
    oaNode = node;
    int n = -1;
    int bigNPrime = -1;

    auto dropNodeLocation = std::find(oaComponents.begin(), oaComponents.end(), node);
    OS_ASSERT(dropNodeLocation != oaComponents.end());
    for (auto it = dropNodeLocation; it != oaComponents.end(); ++it) {
      ++n;
      if ((nextSupplyComponent = it->optionalCast<AirToAirComponent>())) {
        break;
      }
    }
    if (!nextSupplyComponent) {
      nextSupplyComponent = oaSystem.cast<ModelObject>();
    }

    auto rDropNodeLocation = std::find(oaComponents.rbegin(), oaComponents.rend(), node);
    OS_ASSERT(rDropNodeLocation != oaComponents.rend());
    for (auto it = rDropNodeLocation; it != oaComponents.rend(); ++it) {
      if ((prevSupplyComponent = it->optionalCast<AirToAirComponent>())) {
        break;
      }
    }
    if (!prevSupplyComponent) {
      prevSupplyComponent = outboardOANode->cast<ModelObject>();
    }

    prevReliefComponent = nextSupplyComponent;
    auto prevReliefComponentLocation = (prevReliefComponent.get() != oaSystem.cast<ModelObject>())
                                         ? std::find(reliefComponents.begin(), reliefComponents.end(), prevReliefComponent.get())
                                         : reliefComponents.begin();
    for (auto it = prevReliefComponentLocation; it != reliefComponents.end(); ++it) {
      ++bigNPrime;
      if ((nextReliefComponent = it->optionalCast<AirToAirComponent>())) {
        if (*it != prevReliefComponent.get()) {
          break;
        }
      }
    }
    if (!nextReliefComponent) {
      nextReliefComponent = outboardReliefNode->cast<ModelObject>();
    }

    if (n < bigNPrime) {
      auto mo = *(prevReliefComponentLocation + n);
      reliefNode = mo.optionalCast<Node>();
    } else if (nextReliefComponent.get() == outboardReliefNode->cast<ModelObject>()) {
      reliefNode = outboardReliefNode;
    } else if (auto comp = nextReliefComponent->optionalCast<AirToAirComponent>()) {
      if (auto compInlet = comp->secondaryAirInletModelObject()) {
        reliefNode = compInlet->optionalCast<Node>();
      }
    }
  } else {
    reliefNode = node;
    int n = -1;
    int bigNPrime = -1;

    auto dropNodeLocation = std::find(reliefComponents.begin(), reliefComponents.end(), node);
    OS_ASSERT(dropNodeLocation != reliefComponents.end());
    for (auto it = dropNodeLocation; it != reliefComponents.end(); ++it) {
      ++n;
      if ((nextReliefComponent = it->optionalCast<AirToAirComponent>())) {
        break;
      }
    }
    if (!nextReliefComponent) {
      nextReliefComponent = outboardReliefNode->cast<ModelObject>();
    }

    auto rDropNodeLocation = std::find(reliefComponents.rbegin(), reliefComponents.rend(), node);
    OS_ASSERT(rDropNodeLocation != reliefComponents.rend());
    for (auto it = rDropNodeLocation; it != reliefComponents.rend(); ++it) {
      if ((prevReliefComponent = it->optionalCast<AirToAirComponent>())) {
        break;
      }
    }
    if (!prevReliefComponent) {
      prevReliefComponent = oaSystem.cast<ModelObject>();
    }

    if (nextReliefComponent.get() != outboardReliefNode->cast<ModelObject>()) {
      prevSupplyComponent = nextReliefComponent;
    } else {
      prevSupplyComponent = outboardOANode->cast<ModelObject>();
    }

    auto prevSupplyComponentLocation = std::find(oaComponents.begin(), oaComponents.end(), prevSupplyComponent.get());
    for (auto it = prevSupplyComponentLocation; it != oaComponents.end(); ++it) {
      ++bigNPrime;
      if ((nextSupplyComponent = it->optionalCast<AirToAirComponent>())) {
        break;
      }
    }
    if (!nextSupplyComponent) {
      nextSupplyComponent = oaSystem.cast<ModelObject>();
    }

    if (n < bigNPrime) {
      auto mo = *(prevSupplyComponentLocation + n);
      oaNode = mo.optionalCast<Node>();
    } else if (nextSupplyComponent.get() == oaSystem.cast<ModelObject>()) {
      if (auto compNode = oaSystem.outdoorAirModelObject()) {
        oaNode = compNode->optionalCast<Node>();
      }
    } else if (auto comp = nextSupplyComponent->optionalCast<AirToAirComponent>()) {
      if (auto compInlet = comp->primaryAirInletModelObject()) {
        oaNode = compInlet->optionalCast<Node>();
      }
    }
  }

  if (!oaNode || !reliefNode) {
    return false;
  }

  const auto spliceSingleStream = [&](Node& dropNode, bool outdoorAirStream, unsigned inletPort, unsigned outletPort) -> bool {
    auto path = outdoorAirStream ? oaSystem.oaComponents() : oaSystem.reliefComponents();
    const auto nodeIt = std::find_if(path.begin(), path.end(), [&](const auto& object) { return object.handle() == dropNode.handle(); });
    if (nodeIt == path.end()) {
      return false;
    }

    auto inletNode = dropNode;
    auto outletNode = dropNode;
    if (path.size() == 1u) {
      auto newNode =
        model().getOrCreateTransientByName<Node>(dropNode.nameString() + " - " + thisObject.nameString() + (outdoorAirStream ? " Supply Outlet" : " Exhaust Inlet"));
      if (outdoorAirStream) {
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
      auto newNode =
        model().getOrCreateTransientByName<Node>(dropNode.nameString() + " - " + thisObject.nameString() + (outdoorAirStream ? " Supply Outlet" : " Exhaust Inlet"));

      if (!hasNextComponent && hasPreviousComponent) {
        inletNode = newNode;
        if (outdoorAirStream) {
          if (!oaSystemImpl->updateOutdoorAirStreamOutletNode(path[index - 1u], newNode)) {
            return false;
          }
        } else if (!oaSystemImpl->updateReliefAirStreamOutletNode(path[index - 1u], newNode)) {
          return false;
        }
      } else {
        outletNode = newNode;
        if (hasNextComponent) {
          if (outdoorAirStream) {
            if (!oaSystemImpl->updateOutdoorAirStreamInletNode(path[index + 1u], newNode)) {
              return false;
            }
          } else if (!oaSystemImpl->updateReliefAirStreamInletNode(path[index + 1u], newNode)) {
            return false;
          }
        }
      }
    }

    return setPointer(inletPort, inletNode.handle(), false) && setPointer(outletPort, outletNode.handle(), false);
  };

  if (!spliceSingleStream(*oaNode, true, primaryAirInletPort(), primaryAirOutletPort())) {
    return false;
  }
  if (!spliceSingleStream(*reliefNode, false, secondaryAirInletPort(), secondaryAirOutletPort())) {
    return false;
  }

  return oaSystemImpl->rewriteEquipmentListOrder();
}

bool AirToAirComponent_Impl::removeFromOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem) {
  auto primaryInlet = primaryAirInletModelObject();
  auto primaryOutlet = primaryAirOutletModelObject();
  auto secondaryInlet = secondaryAirInletModelObject();
  auto secondaryOutlet = secondaryAirOutletModelObject();
  if (!primaryInlet || !primaryOutlet || !secondaryInlet || !secondaryOutlet) {
    return false;
  }

  auto primaryInletNode = primaryInlet->optionalCast<Node>();
  auto primaryOutletNode = primaryOutlet->optionalCast<Node>();
  auto secondaryInletNode = secondaryInlet->optionalCast<Node>();
  auto secondaryOutletNode = secondaryOutlet->optionalCast<Node>();
  if (!primaryInletNode || !primaryOutletNode || !secondaryInletNode || !secondaryOutletNode) {
    return false;
  }

  auto oaSystemImpl = oaSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>();
  OS_ASSERT(oaSystemImpl);
  const auto thisObject = getObject<ModelObject>();
  const auto reconnectStream = [&](bool outdoorAirStream) -> bool {
    auto path = outdoorAirStream ? oaSystem.oaComponents() : oaSystem.reliefComponents();
    auto it = std::find_if(path.begin(), path.end(), [&](const auto& object) { return object.handle() == thisObject.handle(); });
    if (it == path.end()) {
      return false;
    }

    const auto index = static_cast<std::size_t>(std::distance(path.begin(), it));
    auto inletNode = outdoorAirStream ? *primaryInletNode : *secondaryInletNode;
    auto outletNode = outdoorAirStream ? *primaryOutletNode : *secondaryOutletNode;

    if (path.size() == 3u) {
      return outdoorAirStream ? oaSystemImpl->setOutdoorAirStreamNode(inletNode) : oaSystemImpl->setReliefAirStreamNode(outletNode);
    }

    if (index < 1u || (index + 1u) >= path.size()) {
      return false;
    }

    auto previousNode = path[index - 1u].optionalCast<Node>();
    auto nextNode = path[index + 1u].optionalCast<Node>();
    if (!previousNode || !nextNode) {
      return false;
    }

    if (index >= 2u) {
      if (outdoorAirStream) {
        if (!oaSystemImpl->updateOutdoorAirStreamOutletNode(path[index - 2u], *previousNode)) {
          return false;
        }
      } else if (!oaSystemImpl->updateReliefAirStreamOutletNode(path[index - 2u], *previousNode)) {
        return false;
      }
    }

    if ((index + 2u) < path.size()) {
      if (outdoorAirStream) {
        return oaSystemImpl->updateOutdoorAirStreamInletNode(path[index + 2u], *previousNode);
      }
      return oaSystemImpl->updateReliefAirStreamInletNode(path[index + 2u], *previousNode);
    }

    return outdoorAirStream ? oaSystemImpl->setOutdoorAirStreamNode(*previousNode) : oaSystemImpl->setReliefAirStreamNode(*previousNode);
  };

  if (!reconnectStream(true) || !reconnectStream(false)) {
    return false;
  }

  disconnect();
  auto equipmentListImpl =
    oaSystemImpl->airLoopHVACOutdoorAirSystemEquipmentList().getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
  OS_ASSERT(equipmentListImpl);
  equipmentListImpl->removeEquipment(thisObject);
  return oaSystemImpl->rewriteEquipmentListOrder();
}

std::vector<IdfObject> AirToAirComponent_Impl::remove() {
  if (!isRemovable()) {
    return {};
  }

  for (auto oaSystem : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
    if (oaSystem.component(handle())) {
      if (removeFromOutdoorAirSystem(oaSystem)) {
        return HVACComponent_Impl::remove();
      }
    }
  }

  disconnect();
  return HVACComponent_Impl::remove();
}

void AirToAirComponent_Impl::doCanonicalize(LoadContext& context) {
  canonicalizeNodePort(*this, primaryAirInletPort(), "primary inlet", context);
  canonicalizeNodePort(*this, primaryAirOutletPort(), "primary outlet", context);
  canonicalizeNodePort(*this, secondaryAirInletPort(), "secondary inlet", context);
  canonicalizeNodePort(*this, secondaryAirOutletPort(), "secondary outlet", context);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
