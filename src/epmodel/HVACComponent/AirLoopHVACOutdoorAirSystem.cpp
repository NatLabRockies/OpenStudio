/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"

#include "AirToAirComponent/AirToAirComponent.hpp"
#include "AirToAirComponent/AirToAirComponent_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/Loop_Impl.hpp"
#include "AirLoopHVACControllerList.hpp"
#include "AirLoopHVACControllerList_Impl.hpp"
#include "AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "Branch.hpp"
#include "Branch_Impl.hpp"
#include "BranchList.hpp"
#include "BranchList_Impl.hpp"
#include "ParentObject/ControllerOutdoorAir.hpp"
#include "ParentObject/ControllerOutdoorAir_Impl.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "ModelObject/OutdoorAirMixer.hpp"
#include "ModelObject/OutdoorAirMixer_Impl.hpp"
#include "StraightComponent/StraightComponent.hpp"
#include "StraightComponent/StraightComponent_Impl.hpp"
#include "WaterToAirComponent/WaterToAirComponent.hpp"
#include "WaterToAirComponent/WaterToAirComponent_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <algorithm>
#include <set>
#include <map>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/AirLoopHVAC_OutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACOutdoorAirSystem::AirLoopHVACOutdoorAirSystem(const Model& model) : HVACComponent(AirLoopHVACOutdoorAirSystem::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACOutdoorAirSystem::AirLoopHVACOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACOutdoorAirSystem_Impl> impl)
    : HVACComponent(std::move(impl)) {}

  IddObjectType AirLoopHVACOutdoorAirSystem::iddObjectType() {
    return IddObjectType::AirLoopHVAC_OutdoorAirSystem;
  }

  unsigned AirLoopHVACOutdoorAirSystem::returnAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->returnAirPort();
  }

  unsigned AirLoopHVACOutdoorAirSystem::outdoorAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outdoorAirPort();
  }

  unsigned AirLoopHVACOutdoorAirSystem::reliefAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefAirPort();
  }

  unsigned AirLoopHVACOutdoorAirSystem::mixedAirPort() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->mixedAirPort();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::returnAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->returnAirModelObject();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::outdoorAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outdoorAirModelObject();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::reliefAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefAirModelObject();
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::mixedAirModelObject() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->mixedAirModelObject();
  }

  std::vector<ModelObject> AirLoopHVACOutdoorAirSystem::oaComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->oaComponents(type);
  }

  std::vector<ModelObject> AirLoopHVACOutdoorAirSystem::reliefComponents(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefComponents(type);
  }

  std::vector<ModelObject> AirLoopHVACOutdoorAirSystem::components(openstudio::IddObjectType type) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->components(type);
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::component(openstudio::Handle handle) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->component(handle);
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::oaComponent(openstudio::Handle handle) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->oaComponent(handle);
  }

  boost::optional<ModelObject> AirLoopHVACOutdoorAirSystem::reliefComponent(openstudio::Handle handle) const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->reliefComponent(handle);
  }

  ControllerOutdoorAir AirLoopHVACOutdoorAirSystem::getControllerOutdoorAir() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->getControllerOutdoorAir();
  }

  bool AirLoopHVACOutdoorAirSystem::setControllerOutdoorAir(const ControllerOutdoorAir& controllerOutdoorAir) {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->setControllerOutdoorAir(controllerOutdoorAir);
  }

  boost::optional<Node> AirLoopHVACOutdoorAirSystem::outboardOANode() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outboardOANode();
  }

  boost::optional<Node> AirLoopHVACOutdoorAirSystem::outboardReliefNode() const {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->outboardReliefNode();
  }

  bool AirLoopHVACOutdoorAirSystem::addToNode(Node& node) {
    return getImpl<detail::AirLoopHVACOutdoorAirSystem_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // These OA helper methods form the shared topology extraction layer for three different
    // responsibilities in this file: stream navigation, stream mutation, and canonicalization.
    // Inlining this logic into every caller would duplicate the same component-family dispatch and
    // stream-walk rules several times, which would make future parity fixes harder to review and
    // easier to drift.

    // Decode the air-side node pair a component presents on one OA stream. This is the place where
    // the EnergyPlus-backed object graph is translated into a uniform "stream inlet node /
    // stream outlet node" view for traversal. Canonicalization uses the same extractor after it
    // has established the owning OA-system invariants needed for traversal, and the runtime callers
    // rely on those same invariants too. This method therefore does not try to repair missing or
    // contradictory relationships on its own.
    boost::optional<std::pair<Node, Node>> AirLoopHVACOutdoorAirSystem_Impl::streamNodesFor(const ModelObject& object, OAStream stream) const {
      if (auto airToAir = object.optionalCast<openstudio::epmodel::AirToAirComponent>()) {
        const auto inlet = (stream == OAStream::OutdoorAir) ? airToAir->primaryAirInletModelObject() : airToAir->secondaryAirInletModelObject();
        const auto outlet = (stream == OAStream::OutdoorAir) ? airToAir->primaryAirOutletModelObject() : airToAir->secondaryAirOutletModelObject();
        if (inlet && outlet) {
          auto inletNode = inlet->optionalCast<Node>();
          auto outletNode = outlet->optionalCast<Node>();
          if (inletNode && outletNode) {
            return std::make_pair(*inletNode, *outletNode);
          }
        }
        return boost::none;
      }

      if (auto straight = object.optionalCast<openstudio::epmodel::StraightComponent>()) {
        auto inlet = straight->inletModelObject();
        auto outlet = straight->outletModelObject();
        if (inlet && outlet) {
          auto inletNode = inlet->optionalCast<Node>();
          auto outletNode = outlet->optionalCast<Node>();
          if (inletNode && outletNode) {
            return std::make_pair(*inletNode, *outletNode);
          }
        }
        return boost::none;
      }

      if (auto waterToAir = object.optionalCast<openstudio::epmodel::WaterToAirComponent>()) {
        auto inlet = waterToAir->airInletModelObject();
        auto outlet = waterToAir->airOutletModelObject();
        if (inlet && outlet) {
          auto inletNode = inlet->optionalCast<Node>();
          auto outletNode = outlet->optionalCast<Node>();
          if (inletNode && outletNode) {
            return std::make_pair(*inletNode, *outletNode);
          }
        }
        return boost::none;
      }

      if (auto zoneHVAC = object.optionalCast<openstudio::epmodel::ZoneHVACComponent>()) {
        auto inlet = zoneHVAC->airInletModelObject();
        auto outlet = zoneHVAC->airOutletModelObject();
        if (inlet && outlet) {
          auto inletNode = inlet->optionalCast<Node>();
          auto outletNode = outlet->optionalCast<Node>();
          if (inletNode && outletNode) {
            return std::make_pair(*inletNode, *outletNode);
          }
        }
        return boost::none;
      }

      return boost::none;
    }

    // Walk the realized OA stream from the mixer-side outdoor-air node outward to the outboard OA
    // node, then reverse that intermediate result so callers see airflow order from outdoors toward
    // the mixer. This walk is intentionally derived from canonicalized node connectivity rather than
    // from equipment-list order alone, because the equipment list is only the persisted membership
    // spine, not the complete executable topology.
    std::vector<ModelObject> AirLoopHVACOutdoorAirSystem_Impl::walkOutdoorAirStream() const {
      auto mixerOutdoor = outdoorAirModelObject();
      if (!mixerOutdoor) {
        return {};
      }
      auto currentNode = mixerOutdoor->optionalCast<Node>();
      if (!currentNode) {
        return {};
      }

      std::vector<ModelObject> candidates;
      for (const auto& equipment : airLoopHVACOutdoorAirSystemEquipmentList().equipment()) {
        if (!equipment.optionalCast<OutdoorAirMixer>()) {
          candidates.push_back(equipment);
        }
      }
      std::vector<ModelObject> reversePath;
      reversePath.push_back(currentNode->cast<ModelObject>());
      std::set<Handle> used;

      while (true) {
        boost::optional<ModelObject> previousComponent;
        boost::optional<Node> previousNode;
        for (const auto& candidate : candidates) {
          if (used.contains(candidate.handle())) {
            continue;
          }
          if (auto streamNodes = streamNodesFor(candidate, OAStream::OutdoorAir)) {
            if (streamNodes->second == *currentNode) {
              previousComponent = candidate;
              previousNode = streamNodes->first;
              break;
            }
          }
        }
        if (!previousComponent || !previousNode) {
          break;
        }
        used.insert(previousComponent->handle());
        reversePath.push_back(*previousComponent);
        reversePath.push_back(previousNode->cast<ModelObject>());
        currentNode = previousNode;
      }

      std::reverse(reversePath.begin(), reversePath.end());
      return reversePath;
    }

    // Walk the realized relief stream in airflow order from the mixer-side relief node out toward
    // the outboard relief node. This mirrors the OA walk above, but the direction already matches
    // the relief airflow convention that the public API exposes.
    std::vector<ModelObject> AirLoopHVACOutdoorAirSystem_Impl::walkReliefAirStream() const {
      auto mixerRelief = reliefAirModelObject();
      if (!mixerRelief) {
        return {};
      }
      auto currentNode = mixerRelief->optionalCast<Node>();
      if (!currentNode) {
        return {};
      }

      std::vector<ModelObject> candidates;
      for (const auto& equipment : airLoopHVACOutdoorAirSystemEquipmentList().equipment()) {
        if (!equipment.optionalCast<OutdoorAirMixer>()) {
          candidates.push_back(equipment);
        }
      }
      std::vector<ModelObject> path;
      path.push_back(currentNode->cast<ModelObject>());
      std::set<Handle> used;

      while (true) {
        boost::optional<ModelObject> nextComponent;
        boost::optional<Node> nextNode;
        for (const auto& candidate : candidates) {
          if (used.contains(candidate.handle())) {
            continue;
          }
          if (auto streamNodes = streamNodesFor(candidate, OAStream::ReliefAir)) {
            if (streamNodes->first == *currentNode) {
              nextComponent = candidate;
              nextNode = streamNodes->second;
              break;
            }
          }
        }
        if (!nextComponent || !nextNode) {
          break;
        }
        used.insert(nextComponent->handle());
        path.push_back(*nextComponent);
        path.push_back(nextNode->cast<ModelObject>());
        currentNode = nextNode;
      }

      return path;
    }

    // Rebuild the persisted OA equipment-list order from the canonicalized node graph. The
    // equipment list remains the persisted serialization spine required by the EnergyPlus schema,
    // but once topology has been canonicalized the node graph is the better source for deriving the
    // stream-ordered projections that users expect. This method is therefore the one place that
    // reconciles those two views back into a stable persisted order.
    bool AirLoopHVACOutdoorAirSystem_Impl::rewriteEquipmentListOrder() {
      return rewriteEquipmentListOrder(static_cast<LoadContext*>(nullptr));
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::rewriteEquipmentListOrder(LoadContext& context) {
      return rewriteEquipmentListOrder(&context);
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::rewriteEquipmentListOrder(LoadContext* context) {
      auto equipmentList = airLoopHVACOutdoorAirSystemEquipmentList();
      auto equipmentListImpl = equipmentList.getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
      OS_ASSERT(equipmentListImpl);

      const auto oaPath = walkOutdoorAirStream();
      const auto reliefPath = walkReliefAirStream();
      auto mixer = outdoorAirMixer().cast<ModelObject>();

      std::vector<ModelObject> ordered;
      ordered.push_back(mixer);

      std::set<Handle> seen;
      seen.insert(mixer.handle());

      for (const auto& object : oaPath) {
        if (object.optionalCast<Node>()) {
          continue;
        }
        if (seen.insert(object.handle()).second) {
          ordered.push_back(object);
        }
      }
      for (const auto& object : reliefPath) {
        if (object.optionalCast<Node>() || object.optionalCast<openstudio::epmodel::AirToAirComponent>()) {
          continue;
        }
        if (seen.insert(object.handle()).second) {
          ordered.push_back(object);
        }
      }

      std::vector<ModelObject> dropped;
      for (const auto& object : equipmentList.equipment()) {
        if (!seen.contains(object.handle())) {
          dropped.push_back(object);
        }
      }

      while (!equipmentList.extensibleGroups().empty()) {
        equipmentList.eraseExtensibleGroup(static_cast<unsigned>(equipmentList.extensibleGroups().size() - 1u));
      }
      for (const auto& object : ordered) {
        if (!equipmentListImpl->addEquipment(object)) {
          return false;
        }
      }

      if (context) {
        for (const auto& object : dropped) {
          detail::addLoadWarning(*context, "Dropped unsalvageable OA equipment '" + object.nameString() + "' (" + object.iddObject().name()
                                             + ") from AirLoopHVAC:OutdoorAirSystem '" + getObject<AirLoopHVACOutdoorAirSystem>().nameString()
                                             + "' because its stream placement could not be resolved.");
        }
      }

      return true;
    }

    // Update one adjacent component's stream-facing node reference after a splice or removal on an
    // OA or relief stream. This stays centralized because the caller already knows which neighbor
    // needs to move, but the port that must be rewritten still depends on the component family and
    // on which stream is being edited.
    bool AirLoopHVACOutdoorAirSystem_Impl::updateAdjacentStreamNode(const ModelObject& object, OAStream stream, bool updateInlet, const Node& node) {
      auto mutableObject = object;
      if (auto airToAir = mutableObject.optionalCast<openstudio::epmodel::AirToAirComponent>()) {
        const auto port = updateInlet ? ((stream == OAStream::OutdoorAir) ? airToAir->primaryAirInletPort() : airToAir->secondaryAirInletPort())
                                      : ((stream == OAStream::OutdoorAir) ? airToAir->primaryAirOutletPort() : airToAir->secondaryAirOutletPort());
        return airToAir->setPointer(port, node.handle());
      }
      if (auto straight = mutableObject.optionalCast<openstudio::epmodel::StraightComponent>()) {
        return straight->setPointer(updateInlet ? straight->inletPort() : straight->outletPort(), node.handle());
      }
      if (auto waterToAir = mutableObject.optionalCast<openstudio::epmodel::WaterToAirComponent>()) {
        const auto port = updateInlet ? waterToAir->airInletPort() : waterToAir->airOutletPort();
        return waterToAir->setPointer(port, node.handle());
      }
      return false;
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::setOutdoorAirStreamNode(const Node& node) {
      return outdoorAirMixer().setPointer(outdoorAirPort(), node.handle());
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::setReliefAirStreamNode(const Node& node) {
      return outdoorAirMixer().setPointer(reliefAirPort(), node.handle());
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::updateOutdoorAirStreamInletNode(const ModelObject& object, const Node& node) {
      return updateAdjacentStreamNode(object, OAStream::OutdoorAir, true, node);
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::updateOutdoorAirStreamOutletNode(const ModelObject& object, const Node& node) {
      return updateAdjacentStreamNode(object, OAStream::OutdoorAir, false, node);
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::updateReliefAirStreamInletNode(const ModelObject& object, const Node& node) {
      return updateAdjacentStreamNode(object, OAStream::ReliefAir, true, node);
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::updateReliefAirStreamOutletNode(const ModelObject& object, const Node& node) {
      return updateAdjacentStreamNode(object, OAStream::ReliefAir, false, node);
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::returnAirPort() const {
      // Schema Alignment Notes:
      // - Field Mapping: AirLoopHVACOutdoorAirSystem node-port APIs map to OutdoorAir:Mixer field enums.
      // - ForwardTranslator evidence: ForwardTranslateAirLoopHVACOutdoorAirSystem.cpp writes these same OutdoorAir:Mixer fields.
      return openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName;
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::outdoorAirPort() const {
      return openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName;
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::reliefAirPort() const {
      return openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName;
    }

    unsigned AirLoopHVACOutdoorAirSystem_Impl::mixedAirPort() const {
      return openstudio::OutdoorAir_MixerFields::MixedAirNodeName;
    }

    openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList AirLoopHVACOutdoorAirSystem_Impl::airLoopHVACOutdoorAirSystemEquipmentList() const {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto equipmentList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);
      OS_ASSERT(equipmentList);
      return *equipmentList;
    }

    openstudio::epmodel::OutdoorAirMixer AirLoopHVACOutdoorAirSystem_Impl::outdoorAirMixer() const {
      const auto mixers = subsetCastVector<openstudio::epmodel::OutdoorAirMixer>(airLoopHVACOutdoorAirSystemEquipmentList().equipment());
      OS_ASSERT(mixers.size() == 1u);
      return mixers.front();
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::returnAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(returnAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::outdoorAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(outdoorAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::reliefAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(reliefAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::mixedAirModelObject() const {
      auto mixer = outdoorAirMixer();

      if (auto node = mixer.getModelObjectTarget<openstudio::epmodel::Node>(mixedAirPort())) {
        return node->cast<openstudio::epmodel::ModelObject>();
      }
      return boost::none;
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::oaComponents(openstudio::IddObjectType type) const {
      auto start = outboardOANode();
      auto target = outdoorAirModelObject();
      if (!start || !target) {
        return {};
      }
      openstudio::epmodel::detail::Loop_Impl::AdjacencyBuilder builder;
      const auto oaPath = walkOutdoorAirStream();
      for (std::size_t i = 1; i < oaPath.size(); ++i) {
        builder.addLink(oaPath[i - 1], oaPath[i]);
      }
      auto path = builder.walkPath(model(), start->cast<ModelObject>(), *target);
      if (type == openstudio::IddObjectType::Catchall) {
        return path;
      }
      std::vector<ModelObject> filtered;
      for (const auto& object : path) {
        if (object.iddObject().type() == type) {
          filtered.push_back(object);
        }
      }
      return filtered;
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::reliefComponents(openstudio::IddObjectType type) const {
      auto start = reliefAirModelObject();
      auto target = outboardReliefNode();
      if (!start || !target) {
        return {};
      }
      openstudio::epmodel::detail::Loop_Impl::AdjacencyBuilder builder;
      const auto reliefPath = walkReliefAirStream();
      for (std::size_t i = 1; i < reliefPath.size(); ++i) {
        builder.addLink(reliefPath[i - 1], reliefPath[i]);
      }
      auto path = builder.walkPath(model(), *start, target->cast<ModelObject>());
      if (type == openstudio::IddObjectType::Catchall) {
        return path;
      }
      std::vector<ModelObject> filtered;
      for (const auto& object : path) {
        if (object.iddObject().type() == type) {
          filtered.push_back(object);
        }
      }
      return filtered;
    }

    std::vector<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::components(openstudio::IddObjectType type) const {
      auto result = oaComponents(type);
      auto relief = reliefComponents(type);
      result.insert(result.end(), relief.begin(), relief.end());
      return result;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::component(openstudio::Handle handle) const {
      if (auto result = oaComponent(handle)) {
        return result;
      }
      return reliefComponent(handle);
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::oaComponent(openstudio::Handle handle) const {
      auto comps = oaComponents(openstudio::IddObjectType::Catchall);
      auto it = std::find_if(comps.begin(), comps.end(), [&](const openstudio::epmodel::ModelObject& comp) { return comp.handle() == handle; });
      if (it != comps.end()) {
        return *it;
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::ModelObject> AirLoopHVACOutdoorAirSystem_Impl::reliefComponent(openstudio::Handle handle) const {
      auto comps = reliefComponents(openstudio::IddObjectType::Catchall);
      auto it = std::ranges::find_if(comps, [&](const openstudio::epmodel::ModelObject& comp) { return comp.handle() == handle; });
      if (it != comps.end()) {
        return *it;
      }
      return boost::none;
    }

    openstudio::epmodel::ControllerOutdoorAir AirLoopHVACOutdoorAirSystem_Impl::getControllerOutdoorAir() const {
      auto controller = airLoopHVACControllerList().optionalControllerOutdoorAir();
      OS_ASSERT(controller);
      return *controller;
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::setControllerOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir) {
      auto controllerList = airLoopHVACControllerList();
      const bool result =
        controllerList.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(controllerOutdoorAir);
      if (result) {
        if (auto airLoop = this->airLoopHVAC()) {
          airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
        }
      }
      return result;
    }

    openstudio::epmodel::AirLoopHVACControllerList AirLoopHVACOutdoorAirSystem_Impl::airLoopHVACControllerList() const {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
      OS_ASSERT(controllerList);
      return *controllerList;
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACOutdoorAirSystem_Impl::outboardOANode() const {
      auto path = walkOutdoorAirStream();
      if (!path.empty()) {
        return path.front().optionalCast<openstudio::epmodel::Node>();
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::Node> AirLoopHVACOutdoorAirSystem_Impl::outboardReliefNode() const {
      auto path = walkReliefAirStream();
      if (!path.empty()) {
        return path.back().optionalCast<openstudio::epmodel::Node>();
      }
      return boost::none;
    }

    void AirLoopHVACOutdoorAirSystem_Impl::doCanonicalize(LoadContext& context) {
      auto oaSystem = getObject<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>();
      auto oaSystemName = oaSystem.nameString();

      // Maintain the non-optional OA controller invariant to match getControllerOutdoorAir().
      auto controllerList = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACControllerList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName);
      if (!controllerList) {
        auto createdControllerList = openstudio::epmodel::AirLoopHVACControllerList(model());
        createdControllerList.setName(oaSystem.nameString() + " Controller List");
        OS_ASSERT(oaSystem.setPointer(openstudio::AirLoopHVAC_OutdoorAirSystemFields::ControllerListName, createdControllerList.handle()));
        controllerList = createdControllerList;
        detail::addLoadInfo(context, "Created missing AirLoopHVAC:ControllerList '" + createdControllerList.nameString()
                                       + "' for AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
      }
      OS_ASSERT(controllerList);
      auto controllerListObject = *controllerList;
      controllerListObject.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>()->canonicalize(context);

      auto oaController = controllerListObject.optionalControllerOutdoorAir();
      if (!oaController) {
        auto createdController = openstudio::epmodel::ControllerOutdoorAir(model());
        createdController.setName(model().nextName(openstudio::IddObjectType::Controller_OutdoorAir, true));
        OS_ASSERT(
          controllerListObject.getImpl<openstudio::epmodel::detail::AirLoopHVACControllerList_Impl>()->setControllerOutdoorAir(createdController));
        oaController = createdController;
        detail::addLoadInfo(context, "Created missing Controller:OutdoorAir '" + createdController.nameString()
                                       + "' for AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
      }
      OS_ASSERT(oaController);
      oaController->getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>()->canonicalize(context);

      auto el = oaSystem.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList>(
        openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName);

      if (!el) {
        el = openstudio::epmodel::AirLoopHVACOutdoorAirSystemEquipmentList(model());
        el->setName(oaSystem.nameString() + " equipment list");
        OS_ASSERT(oaSystem.setPointer(openstudio::AirLoopHVAC_OutdoorAirSystemFields::OutdoorAirEquipmentListName, el->handle()));
        detail::addLoadInfo(context, "Created missing AirLoopHVAC:OutdoorAirSystem:EquipmentList '" + el->nameString()
                                       + "' for AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
      }

      OS_ASSERT(el);
      el->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->canonicalize(context);

      boost::optional<OutdoorAirMixer> mixer;
      const auto mixers = subsetCastVector<openstudio::epmodel::OutdoorAirMixer>(el->equipment());
      if (mixers.empty()) {
        mixer = OutdoorAirMixer(model());
        mixer->setName(oaSystem.nameString() + " mixer");
        OS_ASSERT(el->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->addEquipment(*mixer));
        detail::addLoadInfo(context, "Created missing OutdoorAir:Mixer '" + mixer->nameString() + "' for AirLoopHVAC:OutdoorAirSystem '"
                                       + oaSystem.nameString() + "'.");
      } else {
        mixer = mixers.front();
        // Remove any mixer after the first one
        if (mixers.size() > 1u) {
          auto duplicateMixers = mixers;
          duplicateMixers.erase(duplicateMixers.begin());
          for (const auto& duplicateMixer : duplicateMixers) {
            if (el->getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>()->removeEquipment(duplicateMixer)) {
              detail::addLoadInfo(context, "Removed duplicate OutdoorAir:Mixer '" + duplicateMixer.nameString()
                                             + "' from AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
            }
          }
        }
      }

      OS_ASSERT(mixer);
      auto mixerImpl = mixer->getImpl<openstudio::epmodel::detail::OutdoorAirMixer_Impl>();
      mixerImpl->canonicalize(context);

      if (!mixerImpl->outdoorAirNode()) {
        auto outdoorAirNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(oaSystemName + " Outboard OA Node");
        OS_ASSERT(mixerImpl->setOutdoorAirNode(outdoorAirNode));
      }

      if (!mixerImpl->reliefAirNode()) {
        auto reliefAirNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(oaSystemName + " Relief Node");
        OS_ASSERT(mixerImpl->setReliefAirNode(reliefAirNode));
      }

      if (auto outboardNode = outboardOANode()) {
        const auto outboardNodeName = outboardNode->nameString();
        bool nodeListFound = false;
        for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
          for (const auto& group : object.extensibleGroups()) {
            auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
            if (!workspaceGroup) {
              continue;
            }
            auto nodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
            if (nodeName && openstudio::istringEqual(*nodeName, outboardNodeName)) {
              nodeListFound = true;
              break;
            }
          }
          if (nodeListFound) {
            break;
          }
        }

        if (!nodeListFound) {
          auto oaNodeList = openstudio::epmodel::ModelObject::create(openstudio::IddObjectType::OutdoorAir_NodeList, model());
          auto group = oaNodeList.pushExtensibleGroup();
          auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          OS_ASSERT(workspaceGroup);
          OS_ASSERT(workspaceGroup->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, outboardNodeName));
          detail::addLoadInfo(context, "Created OutdoorAir:NodeList entry for outdoor air node '" + outboardNodeName
                                         + "' on AirLoopHVAC:OutdoorAirSystem '" + oaSystem.nameString() + "'.");
        }
      }

      oaController->getImpl<openstudio::epmodel::detail::ControllerOutdoorAir_Impl>()->canonicalize(context);

      OS_ASSERT(rewriteEquipmentListOrder(context));
    }

    bool AirLoopHVACOutdoorAirSystem_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      if (!airLoop->supplyComponents(openstudio::epmodel::AirLoopHVACOutdoorAirSystem::iddObjectType()).empty()) {
        return false;
      }

      if (!airLoop->supplyComponent(node.handle())) {
        return false;
      }

      const auto nodeName = node.name();
      if (!nodeName || nodeName->empty()) {
        return false;
      }

      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      auto branchList = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->branchList();
      auto branches = branchList.branches();
      if (branches.empty()) {
        return false;
      }
      auto branch = branches.front();

      std::string returnNodeName;
      std::string mixedNodeName;

      const auto components = branch.components();
      if (components.empty()) {
        const auto supplyInlet = airLoop->supplyInletNode();
        const auto supplyOutlet = airLoop->supplyOutletNode();
        if (node != supplyInlet && node != supplyOutlet) {
          return false;
        }
        if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->appendComponent(thisObject, supplyInlet.nameString(),
                                                                                         supplyOutlet.nameString())) {
          return false;
        }
        returnNodeName = supplyInlet.nameString();
        mixedNodeName = supplyOutlet.nameString();
      } else {
        bool inserted = false;
        for (std::size_t i = 0; i < components.size(); ++i) {
          auto inletNode = branch.componentInletNode(static_cast<unsigned>(i));
          auto outletNode = branch.componentOutletNode(static_cast<unsigned>(i));
          const bool matchesInlet = inletNode && openstudio::istringEqual(inletNode->nameString(), *nodeName);
          const bool matchesOutlet = outletNode && openstudio::istringEqual(outletNode->nameString(), *nodeName);
          if (!matchesInlet && !matchesOutlet) {
            continue;
          }

          const std::string newNodeName = *nodeName + " - " + thisObject.nameString() + " Mixed Air";
          const unsigned insertIndex = matchesInlet ? static_cast<unsigned>(i) : static_cast<unsigned>(i + 1);
          if (matchesOutlet && (i + 1u == components.size())) {
            returnNodeName = newNodeName;
            mixedNodeName = *nodeName;
          } else {
            returnNodeName = *nodeName;
            mixedNodeName = newNodeName;
          }
          if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->insertComponent(insertIndex, thisObject, returnNodeName, mixedNodeName)) {
            return false;
          }

          if (matchesInlet) {
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentInletNode(insertIndex + 1u, newNode)) {
              return false;
            }
            if (!updateAdjacentStreamNode(components[i], OAStream::OutdoorAir, true, newNode)) {
              return false;
            }
          } else {
            auto newNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(newNodeName);
            if (!branch.getImpl<openstudio::epmodel::detail::Branch_Impl>()->setComponentOutletNode(insertIndex - 1u, newNode)) {
              return false;
            }
            if (!updateAdjacentStreamNode(components[i], OAStream::OutdoorAir, false, newNode)) {
              return false;
            }
          }

          inserted = true;
          break;
        }

        if (!inserted) {
          return false;
        }
      }

      auto mixerObject = outdoorAirMixer();
      auto returnNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(returnNodeName);
      auto mixedNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(mixedNodeName);
      if (!mixerObject.setPointer(returnAirPort(), returnNode.handle())) {
        return false;
      }
      if (!mixerObject.setPointer(mixedAirPort(), mixedNode.handle())) {
        return false;
      }

      auto controller = getControllerOutdoorAir();
      if (!controller.setPointer(openstudio::Controller_OutdoorAirFields::ReliefAirOutletNodeName,
                                 mixerObject.getImpl<openstudio::epmodel::detail::OutdoorAirMixer_Impl>()->reliefAirNode()->handle())
          || !controller.setPointer(openstudio::Controller_OutdoorAirFields::ReturnAirNodeName, returnNode.handle())
          || !controller.setPointer(openstudio::Controller_OutdoorAirFields::MixedAirNodeName, mixedNode.handle())
          || !controller.setPointer(openstudio::Controller_OutdoorAirFields::ActuatorNodeName,
                                    mixerObject.getImpl<openstudio::epmodel::detail::OutdoorAirMixer_Impl>()->outdoorAirNode()->handle())) {
        return false;
      }

      auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      airLoopImpl->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
