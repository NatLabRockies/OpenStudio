/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/StraightComponent.hpp"
#include "StraightComponent/StraightComponent_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "BranchList.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/IddFieldProperties.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>

#include <sstream>

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool StraightComponent_Impl::addToOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem, Node& node) {
      auto thisObject = getObject<ModelObject>();
      if (!detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl::isValidOASystemEquipment(thisObject)) {
        LOG_FREE(Warn, "openstudio.epmodel.Model",
                 "Refusing to add " << thisObject.briefDescription() << " to " << oaSystem.briefDescription()
                                    << " because the EnergyPlus IDD does not include type '" << thisObject.iddObject().name()
                                    << "' in validOASysEquipmentTypes");
        return false;
      }

      const auto outboardOANode = oaSystem.outboardOANode();
      const bool onOutdoorAirStream = oaSystem.oaComponent(node.handle()).has_value() || (outboardOANode && (*outboardOANode == node));
      const bool onReliefStream = oaSystem.reliefComponent(node.handle()).has_value();
      if (!onOutdoorAirStream && !onReliefStream) {
        return false;
      }

      auto equipmentListImpl = oaSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()
                                 ->airLoopHVACOutdoorAirSystemEquipmentList()
                                 .getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
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
      auto oaSystemImpl = oaSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>();
      OS_ASSERT(oaSystemImpl);

      if (path.size() == 1u) {
        auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(node.nameString() + " - " + thisObject.nameString() + " Outlet");
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
        auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(node.nameString() + " - " + thisObject.nameString() + " Outlet");

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

      if (!setPointer(inletPort(), inletNode.handle(), false) || !setPointer(outletPort(), outletNode.handle(), false)) {
        return false;
      }

      return oaSystemImpl->rewriteEquipmentListOrder();
    }

    bool StraightComponent_Impl::removeFromOutdoorAirSystem(AirLoopHVACOutdoorAirSystem& oaSystem) {
      auto inletObject = inletModelObject();
      auto outletObject = outletModelObject();
      if (!inletObject || !outletObject) {
        return false;
      }

      auto inletNode = inletObject->optionalCast<openstudio::epmodel::Node>();
      auto outletNode = outletObject->optionalCast<openstudio::epmodel::Node>();
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

      disconnect();
      auto equipmentListImpl =
        oaSystemImpl->airLoopHVACOutdoorAirSystemEquipmentList().getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
      OS_ASSERT(equipmentListImpl);
      equipmentListImpl->removeEquipment(thisObject);
      return oaSystemImpl->rewriteEquipmentListOrder();
    }

    bool StraightComponent_Impl::addToNode(Node& node) {
      if (auto owner = getObject<openstudio::epmodel::HVACComponent>().containingHVACComponent()) {
        LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                 "Refusing to move " << getObject<ModelObject>().briefDescription() << " onto node '" << node.nameString()
                                     << "' because its air-side connectivity is owned by " << owner->briefDescription() << ".");
        return false;
      }

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

      auto thisComponent = getObject<openstudio::epmodel::HVACComponent>();
      if (thisComponent.loop() && !removeFromLoop()) {
        LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                 "Failed to detach " << thisObject.briefDescription()
                                      << " from its existing loop topology before adding it to node '" << node.nameString() << "'.");
        return false;
      }

      if (auto oaSystem = node.airLoopHVACOutdoorAirSystem()) {
        return addToOutdoorAirSystem(*oaSystem, node);
      }

      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoop = node.airLoopHVAC();
      boost::optional<openstudio::epmodel::PlantLoop> plantLoop;
      boost::optional<openstudio::epmodel::Branch> branch;

      if (airLoop) {
        branch = airLoop->getImpl<detail::AirLoopHVAC_Impl>()->branchForSupplyNode(node);
        if (!branch) {
          return false;
        }
      } else {
        plantLoop = node.plantLoop();
        if (!plantLoop) {
          return false;
        }
        auto plantLoopImpl = plantLoop->getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
        branch = plantLoopImpl->branchForNode(node);
        if (!branch) {
          return false;
        }
      }

      auto components = branch->components();
      if (components.empty()) {
        std::string newInletName;
        std::string newOutletName;

        if (airLoop) {
          const auto supplyInlet = airLoop->supplyInletNode();
          const auto supplyOutletNodes = airLoop->supplyOutletNodes();
          const bool isSupplyOutlet = std::find(supplyOutletNodes.begin(), supplyOutletNodes.end(), node) != supplyOutletNodes.end();
          if (!(node == supplyInlet || isSupplyOutlet)) {
            LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                     "Empty branch encountered, but drop node '" << nodeName.get() << "' is not a loop inlet or outlet for AirLoopHVAC '"
                                                                 << airLoop->nameString() << "'.");
            return false;
          }
          if (isSupplyOutlet && airLoop->isDualDuct()) {
            newInletName = *nodeName + " - " + thisName + " Inlet";
            newOutletName = *nodeName;
          } else {
            newInletName = supplyInlet.nameString();
            newOutletName = airLoop->supplyOutletNode().nameString();
          }
        } else {
          auto plantLoopImpl = plantLoop->getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();

          const bool isOutletAnchor = ((*branch == plantLoopImpl->supplyOutletBranch()) && (node == plantLoop->supplyOutletNode()))
                                      || ((*branch == plantLoopImpl->demandOutletBranch()) && (node == plantLoop->demandOutletNode()));
          if (isOutletAnchor) {
            newInletName = *nodeName + " - " + thisName + " Inlet";
            newOutletName = *nodeName;
          } else {
            newInletName = *nodeName;
            newOutletName = *nodeName + " - " + thisName + " Outlet";
          }
        }

        if (!branch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->appendComponent(thisObject, newInletName, newOutletName)) {
          return false;
        }

        auto newInletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newInletName);
        auto newOutletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newOutletName);
        setPointer(inletPort(), newInletNode.handle(), false);
        setPointer(outletPort(), newOutletNode.handle(), false);

        if (airLoop) {
          auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
          airLoopImpl->syncSetpointManagerMixedAirFanNodes();
        }
        return true;
      } else {
        for (std::size_t i = 0; i < components.size(); ++i) {
          auto inletNode = branch->componentInletNode(static_cast<unsigned>(i));
          auto outletNode = branch->componentOutletNode(static_cast<unsigned>(i));

          // We're looking for the branch component whose inlet or outlet node name matches the drop-in node.
          // This identifies the insertion point for the new component on the branch.
          const bool matchesInlet = inletNode && openstudio::istringEqual(inletNode->nameString(), *nodeName);
          const bool matchesOutlet = outletNode && openstudio::istringEqual(outletNode->nameString(), *nodeName);
          if (!matchesInlet && !matchesOutlet) {
            continue;
          }

          // Consistency check: compare branch node names against the component's own inlet/outlet fields.
          if (auto comp = components[i].optionalCast<openstudio::epmodel::StraightComponent>()) {
            if (auto compInlet = comp->inletModelObject()) {
              if (auto compInletName = compInlet->name()) {
                if (inletNode && !openstudio::istringEqual(*compInletName, inletNode->nameString())) {
                  LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                           "Branch inlet node '" << inletNode->nameString() << "' does not match component inlet node '" << *compInletName
                                                 << "' for '" << comp->nameString() << "'.");
                }
              }
            }
            if (auto compOutlet = comp->outletModelObject()) {
              if (auto compOutletName = compOutlet->name()) {
                if (outletNode && !openstudio::istringEqual(*compOutletName, outletNode->nameString())) {
                  LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                           "Branch outlet node '" << outletNode->nameString() << "' does not match component outlet node '" << *compOutletName
                                                  << "' for '" << comp->nameString() << "'.");
                }
              }
            }
          }

          // Generate a new intermediate node name to preserve the existing node position.
          const std::string newNodeName = *nodeName + " - " + thisName + " Outlet";

          // Insert the new component group before the downstream component (if inlet match),
          // otherwise after the upstream component (if outlet match).
          const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1);
          std::string newInletName;
          std::string newOutletName;
          if (matchesOutlet && (i + 1u == components.size())) {
            // Node is the last node in the branch: insert before it so the node remains last.
            newInletName = newNodeName;
            newOutletName = *nodeName;
          } else {
            // Default: insert after the node (component inlet is the node).
            newInletName = *nodeName;
            newOutletName = newNodeName;
          }
          if (!branch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->insertComponent(insertIndex, thisObject, newInletName, newOutletName)) {
            return false;
          }

          auto newInletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newInletName);
          auto newOutletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newOutletName);
          setPointer(inletPort(), newInletNode.handle(), false);
          setPointer(outletPort(), newOutletNode.handle(), false);

          if (matchesInlet) {
            // The downstream component currently uses nodeName as its inlet; reroute it to newNodeName.
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode)) {
              return false;
            }
          } else {
            // The upstream component currently uses nodeName as its outlet; reroute it to newNodeName.
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch->getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode)) {
              return false;
            }
          }

          if (airLoop) {
            auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
            airLoopImpl->syncSetpointManagerMixedAirFanNodes();
          }
          return true;
        }
      }

      return false;
    }

    void StraightComponent_Impl::doCanonicalize(LoadContext& context) {
      auto thisObject = getObject<ModelObject>();

      const auto ensureNodePointer = [&](unsigned port, const char* portLabel) {
        auto nodeName = getString(port);
        if (!(nodeName && !nodeName->empty())) {
          return false;
        }

        // Ports are expected to be Node-typed fields. If a derived class returns an
        // unexpected field index, avoid aborting canonicalization; report and move on.
        if (auto iddField = iddObject().getField(port)) {
          if (iddField->properties().type != openstudio::IddFieldType::NodeType) {
            std::ostringstream oss;
            oss << "StraightComponent canonicalize: expected NodeType for " << portLabel << " port at index " << port << " on object '"
                << thisObject.nameString() << "' (" << thisObject.iddObject().name() << ") but field '" << iddField->name() << "' has type '"
                << iddField->properties().type.valueDescription() << "' with value '" << *nodeName << "'.";
            detail::addLoadError(context, oss.str());
            return false;
          }
        } else {
          std::ostringstream oss;
          oss << "StraightComponent canonicalize: missing IDD field definition for " << portLabel << " port index " << port << " on object '"
              << thisObject.nameString() << "' (" << thisObject.iddObject().name() << ") with value '" << *nodeName << "'.";
          detail::addLoadError(context, oss.str());
          return false;
        }

        auto node = resolvedNodeTarget(port);
        if (!node) {
          std::ostringstream oss;
          oss << "StraightComponent canonicalize: failed to resolve node pointer for " << portLabel << " port index " << port << " on object '"
              << thisObject.nameString() << "' (" << thisObject.iddObject().name() << ") to Node '" << *nodeName << "'.";
          detail::addLoadError(context, oss.str());
          return false;
        }
        return true;
      };

      const auto inlet = inletPort();
      if (inlet != 0) {
        ensureNodePointer(inlet, "inlet");
      }
      const auto outlet = outletPort();
      if (outlet != 0) {
        ensureNodePointer(outlet, "outlet");
      }

      (void)context;
    }

    boost::optional<ModelObject> StraightComponent_Impl::inletModelObject() const {
      const auto port = inletPort();
      if (port == 0) {
        return boost::none;
      }

      if (auto nodeName = getString(port)) {
        if (nodeName->empty()) {
          return boost::none;
        }
        if (auto resolved = resolvedNodeTarget(port)) {
          return resolved->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    boost::optional<ModelObject> StraightComponent_Impl::outletModelObject() const {
      const auto port = outletPort();
      if (port == 0) {
        return boost::none;
      }

      if (auto nodeName = getString(port)) {
        if (nodeName->empty()) {
          return boost::none;
        }
        if (auto resolved = resolvedNodeTarget(port)) {
          return resolved->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    bool StraightComponent_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();

      auto thisComponent = thisObject.optionalCast<openstudio::epmodel::StraightComponent>();
      if (!thisComponent) {
        return false;
      }

      if (auto owner = thisComponent->containingHVACComponent()) {
        LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                 "Refusing to remove " << thisObject.briefDescription() << " from its loop topology because that connectivity is owned by "
                                       << owner->briefDescription() << ".");
        return false;
      }

      const auto inletObject = inletModelObject();
      const auto outletObject = outletModelObject();
      if (!inletObject || !outletObject) {
        return false;
      }

      auto inletNode = inletObject->optionalCast<openstudio::epmodel::Node>();
      auto outletNode = outletObject->optionalCast<openstudio::epmodel::Node>();
      if (!inletNode || !outletNode) {
        return false;
      }

      for (auto oaSystem : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>()) {
        if (oaSystem.component(handle())) {
          return removeFromOutdoorAirSystem(oaSystem);
        }
      }

      if (auto loop = thisComponent->airLoopHVAC()) {
        auto splitter = loop->zoneSplitter();
        auto mixer = loop->zoneMixer();

        const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(inletNode->cast<ModelObject>());
        const auto mixerBranchIndex = mixer.branchIndexForInletModelObject(outletNode->cast<ModelObject>());
        const bool isZoneBranch = (splitterBranchIndex == mixerBranchIndex)
                                  && (splitter.outletModelObject(splitterBranchIndex) == inletNode->cast<ModelObject>())
                                  && (mixer.inletModelObject(mixerBranchIndex) == outletNode->cast<ModelObject>());

        if (isZoneBranch) {
          splitter.setOutletModelObject(splitterBranchIndex, outletNode->cast<ModelObject>());
        } else {
          auto branchList = loop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->branchList();
          const auto branches = branchList.branches();
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
              if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentInletNode(i + 1u, *inletNode)) {
                return false;
              }
            }
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->removeComponent(i)) {
              return false;
            }
            break;
          }
        }

        auto loopImpl = loop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
        loopImpl->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
        loopImpl->syncSetpointManagerMixedAirFanNodes();
        return true;
      }

      auto plantLoop = thisComponent->plantLoop();
      if (!plantLoop) {
        return false;
      }

      auto plantLoopImpl = plantLoop->getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
      auto branch = plantLoopImpl->branchForNode(*inletNode);
      if (!branch) {
        branch = plantLoopImpl->branchForNode(*outletNode);
      }
      if (!branch) {
        return false;
      }

      auto components = branch->components();
      for (unsigned i = 0; i < components.size(); ++i) {
        if (components[i] != thisObject) {
          continue;
        }

        auto branchImpl = branch->getImpl<openstudio::epmodel::detail::Branch_Impl>();
        OS_ASSERT(branchImpl);
        if (i + 1u < components.size()) {
          if (!branchImpl->setComponentInletNode(i + 1u, *inletNode)) {
            return false;
          }
        } else if (i > 0u) {
          if (!branchImpl->setComponentOutletNode(i - 1u, *outletNode)) {
            return false;
          }
        }
        if (!branchImpl->removeComponent(i)) {
          return false;
        }

        // Re-anchor inlet/outlet branches so the surviving component row points back to the loop endpoint node.
        const auto remainingComponents = branch->components();
        if (!remainingComponents.empty()) {
          if ((*branch == plantLoopImpl->supplyInletBranch()) && !branchImpl->setComponentInletNode(0u, plantLoop->supplyInletNode())) {
            return false;
          }
          if ((*branch == plantLoopImpl->demandInletBranch()) && !branchImpl->setComponentInletNode(0u, plantLoop->demandInletNode())) {
            return false;
          }

          const auto lastIndex = static_cast<unsigned>(remainingComponents.size() - 1u);
          if ((*branch == plantLoopImpl->supplyOutletBranch()) && !branchImpl->setComponentOutletNode(lastIndex, plantLoop->supplyOutletNode())) {
            return false;
          }
          if ((*branch == plantLoopImpl->demandOutletBranch()) && !branchImpl->setComponentOutletNode(lastIndex, plantLoop->demandOutletNode())) {
            return false;
          }
        }
        return true;
      }

      return false;
    }

    std::vector<openstudio::IdfObject> StraightComponent_Impl::remove() {
      removeFromLoop();
      return HVACComponent_Impl::remove();
    }

    void StraightComponent_Impl::disconnect() {
      if (auto owner = getObject<openstudio::epmodel::HVACComponent>().containingHVACComponent()) {
        LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                 "Refusing to disconnect " << getObject<ModelObject>().briefDescription() << " because its air-side connectivity is owned by "
                                           << owner->briefDescription() << ".");
        return;
      }

      const auto thisComponent = getObject<openstudio::epmodel::HVACComponent>();
      if (thisComponent.loop() && !removeFromLoop()) {
        LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                 "Failed to detach " << getObject<ModelObject>().briefDescription() << " from its loop topology before clearing node pointers.");
        return;
      }

      setPointer(inletPort(), Handle(), false);
      setPointer(outletPort(), Handle(), false);
    }

  }  // namespace detail

  StraightComponent::StraightComponent(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : HVACComponent(type, model, fastName, isTransient) {}

  StraightComponent::StraightComponent(std::shared_ptr<detail::StraightComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

  bool StraightComponent::removeFromLoop() {
    return getImpl<detail::StraightComponent_Impl>()->removeFromLoop();
  }

  unsigned StraightComponent::inletPort() const {
    return getImpl<detail::StraightComponent_Impl>()->inletPort();
  }

  unsigned StraightComponent::outletPort() const {
    return getImpl<detail::StraightComponent_Impl>()->outletPort();
  }

  boost::optional<ModelObject> StraightComponent::inletModelObject() const {
    return getImpl<detail::StraightComponent_Impl>()->inletModelObject();
  }

  boost::optional<ModelObject> StraightComponent::outletModelObject() const {
    return getImpl<detail::StraightComponent_Impl>()->outletModelObject();
  }

}  // namespace epmodel
}  // namespace openstudio
