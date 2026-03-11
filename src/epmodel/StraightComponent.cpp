/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent.hpp"
#include "StraightComponent_Impl.hpp"

#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "BranchList.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool StraightComponent_Impl::addToNode(Node& node) {
      // TODO: This only supports single duct, supply side, AirLoopHVAC at the moment
      // TODO: As scope increases for other contexts, this needs to be broken into smaller pieces
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

      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoop = node.airLoopHVAC();

      if (!airLoop) {
        return false;
      }

      const auto branchList = airLoop->getImpl<detail::AirLoopHVAC_Impl>()->branchList();
      auto branch = branchList.branches().front();

      auto components = branch.components();
      if (components.empty()) {
        // If there are no branch components, then this is probably a default constructed loop,
        // therefore the drop node should be either the loop inlet or outlet node
        const auto supplyInlet = airLoop->supplyInletNode();
        const auto supplyOutlet = airLoop->supplyOutletNode();
        if (node == supplyInlet || node == supplyOutlet) {
          if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->appendComponent(thisObject, supplyInlet.nameString(),
                                                                                            supplyOutlet.nameString())) {
            return false;
          }

          setString(inletPort(), supplyInlet.nameString());
          setString(outletPort(), supplyOutlet.nameString());
          setPointer(inletPort(), supplyInlet.handle(), false);
          setPointer(outletPort(), supplyOutlet.handle(), false);
        } else {
          LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                   "Empty branch encountered, but drop node '" << nodeName.get() << "' is not a loop inlet or outlet for AirLoopHVAC '"
                                                               << airLoop->nameString() << "'.");
          return false;
        }

        return true;
      } else {
        for (std::size_t i = 0; i < components.size(); ++i) {
          auto inletNode = branch.componentInletNode(static_cast<unsigned>(i));
          auto outletNode = branch.componentOutletNode(static_cast<unsigned>(i));

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
                                                 << "' for '"
                                                 << comp->nameString() << "'.");
                }
              }
            }
            if (auto compOutlet = comp->outletModelObject()) {
              if (auto compOutletName = compOutlet->name()) {
                if (outletNode && !openstudio::istringEqual(*compOutletName, outletNode->nameString())) {
                  LOG_FREE(Warn, "openstudio.epmodel.StraightComponent",
                           "Branch outlet node '" << outletNode->nameString() << "' does not match component outlet node '" << *compOutletName
                                                  << "' for '"
                                                  << comp->nameString() << "'.");
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
          if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->insertComponent(insertIndex, thisObject, newInletName, newOutletName)) {
            return false;
          }

          setString(inletPort(), newInletName);
          setString(outletPort(), newOutletName);
          auto newInletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newInletName);
          auto newOutletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newOutletName);
          setPointer(inletPort(), newInletNode.handle(), false);
          setPointer(outletPort(), newOutletNode.handle(), false);

          if (matchesInlet) {
            // The downstream component currently uses nodeName as its inlet; reroute it to newNodeName.
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode)) {
              return false;
            }
          } else {
            // The upstream component currently uses nodeName as its outlet; reroute it to newNodeName.
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode)) {
              return false;
            }
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
        auto node = model().getOrCreateTransientByName<openstudio::epmodel::Node>(*nodeName);
        if (!setPointer(port, node.handle(), false)) {
          OS_ASSERT(false);
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
        if (auto node = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(port)) {
          return node->cast<ModelObject>();
        }
        OS_ASSERT(false);
        return boost::none;
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
        if (auto node = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(port)) {
          return node->cast<ModelObject>();
        }
        OS_ASSERT(false);
        return boost::none;
      }
      return boost::none;
    }

  }  // namespace detail

  StraightComponent::StraightComponent(IddObjectType type, const Model& model, bool fastName, bool isTransient)
    : HVACComponent(type, model, fastName, isTransient) {}

  StraightComponent::StraightComponent(std::shared_ptr<detail::StraightComponent_Impl> impl) : HVACComponent(std::move(impl)) {}

  bool StraightComponent::removeFromLoop() {
    return false;
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
