/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "ModelObject/NodeList.hpp"
#include "ModelObject/NodeList_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
#include <functional>

namespace openstudio {
namespace epmodel {

  ZoneHVACEquipmentConnections::ZoneHVACEquipmentConnections(const ThermalZone& thermalZone)
    : ModelObject(ZoneHVACEquipmentConnections::iddObjectType(), thermalZone.model()) {
    auto impl = getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
    OS_ASSERT(impl);
    OS_ASSERT(impl->setThermalZone(thermalZone));
  }

  ZoneHVACEquipmentConnections::ZoneHVACEquipmentConnections(std::shared_ptr<detail::ZoneHVACEquipmentConnections_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACEquipmentConnections::iddObjectType() {
    return IddObjectType::ZoneHVAC_EquipmentConnections;
  }

  ThermalZone ZoneHVACEquipmentConnections::thermalZone() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->thermalZone();
  }

  ZoneHVACEquipmentList ZoneHVACEquipmentConnections::zoneHVACEquipmentList() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->zoneHVACEquipmentList();
  }

  Node ZoneHVACEquipmentConnections::zoneAirNode() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->zoneAirNode();
  }

  std::vector<Node> ZoneHVACEquipmentConnections::zoneAirInletNodes() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->zoneAirInletNodes();
  }

  std::vector<Node> ZoneHVACEquipmentConnections::zoneAirExhaustNodes() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->zoneAirExhaustNodes();
  }

  std::vector<Node> ZoneHVACEquipmentConnections::zoneReturnAirNodes() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->zoneReturnAirNodes();
  }

  namespace detail {
    namespace {

      std::vector<openstudio::epmodel::Node> resolveNodeOrNodeListField(const openstudio::epmodel::ZoneHVACEquipmentConnections& connections,
                                                                        const unsigned field) {
        if (auto target = connections.getTarget(field)) {
          if (auto node = target->optionalCast<openstudio::epmodel::Node>()) {
            return {*node};
          }
          if (auto nodeList = target->optionalCast<openstudio::epmodel::NodeList>()) {
            return nodeList->nodes();
          }
        }

        if (auto nodeOrListName = connections.getString(field)) {
          if (!nodeOrListName->empty()) {
            if (auto nodeList = connections.model().getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *nodeOrListName)) {
              if (auto castNodeList = nodeList->optionalCast<openstudio::epmodel::NodeList>()) {
                if (!connections.getImpl<openstudio::epmodel::detail::ModelObject_Impl>()->setPointer(field, castNodeList->handle(), false)) {
                  return {};
                }
                return castNodeList->nodes();
              }
            }

            if (auto node = connections.getImpl<openstudio::epmodel::detail::ModelObject_Impl>()->resolvedNodeTarget(field)) {
              return {*node};
            }
          }
        }

        return {};
      }

      boost::optional<openstudio::epmodel::ModelObject> uniqueNamedNodeOrNodeList(const openstudio::epmodel::Model& model, const std::string& name) {
        boost::optional<openstudio::epmodel::ModelObject> result;
        for (const auto& node : model.getConcreteModelObjects<openstudio::epmodel::Node>()) {
          if (!openstudio::istringEqual(node.nameString(), name)) {
            continue;
          }
          if (result) {
            return boost::none;
          }
          result = node;
        }
        for (const auto& nodeList : model.getConcreteModelObjects<openstudio::epmodel::NodeList>()) {
          if (!openstudio::istringEqual(nodeList.nameString(), name)) {
            continue;
          }
          if (result) {
            return boost::none;
          }
          result = nodeList;
        }
        return result;
      }

      boost::optional<openstudio::epmodel::Node> uniqueNamedNode(const openstudio::epmodel::Model& model, const std::string& name) {
        boost::optional<openstudio::epmodel::Node> result;
        for (const auto& node : model.getConcreteModelObjects<openstudio::epmodel::Node>()) {
          if (!openstudio::istringEqual(node.nameString(), name)) {
            continue;
          }
          if (result) {
            return boost::none;
          }
          result = node;
        }
        return result;
      }

      boost::optional<std::string> rawFieldValue(const openstudio::epmodel::ModelObject& owner, const unsigned field) {
        auto workspaceImpl = owner.getImpl<openstudio::detail::WorkspaceObject_Impl>();
        OS_ASSERT(workspaceImpl);
        return workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true);
      }

      bool rawFieldAgrees(const openstudio::epmodel::ModelObject& owner, const unsigned field, const openstudio::epmodel::ModelObject& target) {
        const auto raw = rawFieldValue(owner, field);
        return !raw || raw->empty() || openstudio::toUUID(*raw) == target.handle()
               || (target.name() && openstudio::istringEqual(*raw, *target.name()));
      }

      boost::optional<openstudio::epmodel::ModelObject> readOnlyManagedTarget(const openstudio::epmodel::ModelObject& owner, const unsigned field) {
        const auto managed = owner.getField(field, false);
        if (!managed || managed->empty()) {
          return boost::none;
        }
        const auto handle = openstudio::toUUID(*managed);
        if (handle.isNull()) {
          return boost::none;
        }
        const auto target = owner.model().getObject(handle);
        return target ? target->optionalCast<openstudio::epmodel::ModelObject>() : boost::none;
      }

      struct ReadOnlyNodeField
      {
        bool hasEvidence = false;
        bool valid = true;
        boost::optional<openstudio::epmodel::Node> node;
      };

      ReadOnlyNodeField readOnlyNodeField(const openstudio::epmodel::ModelObject& owner, const unsigned field) {
        ReadOnlyNodeField result;
        const auto managed = readOnlyManagedTarget(owner, field);
        const auto raw = rawFieldValue(owner, field);
        result.hasEvidence = static_cast<bool>(managed) || (raw && !raw->empty());
        if (!result.hasEvidence) {
          return result;
        }

        if (managed) {
          result.node = managed->optionalCast<openstudio::epmodel::Node>();
          const auto uniqueNamedTarget = result.node ? uniqueNamedNode(owner.model(), result.node->nameString()) : boost::none;
          result.valid = result.node && uniqueNamedTarget && *uniqueNamedTarget == *result.node && rawFieldAgrees(owner, field, *managed);
          return result;
        }

        result.node = uniqueNamedNode(owner.model(), *raw);
        result.valid = static_cast<bool>(result.node);
        return result;
      }

      struct ReadOnlyNodeCollectionField
      {
        bool hasEvidence = false;
        bool valid = true;
        std::vector<openstudio::epmodel::Node> nodes;
      };

      ReadOnlyNodeCollectionField readOnlyNodeCollectionField(const openstudio::epmodel::ModelObject& owner, const unsigned field) {
        ReadOnlyNodeCollectionField result;
        const auto managed = readOnlyManagedTarget(owner, field);
        const auto raw = rawFieldValue(owner, field);
        result.hasEvidence = static_cast<bool>(managed) || (raw && !raw->empty());
        if (!result.hasEvidence) {
          return result;
        }

        boost::optional<openstudio::epmodel::ModelObject> target = managed;
        if (managed) {
          const auto uniqueNamedTarget = uniqueNamedNodeOrNodeList(owner.model(), managed->nameString());
          if (!uniqueNamedTarget || *uniqueNamedTarget != *managed || !rawFieldAgrees(owner, field, *managed)) {
            result.valid = false;
            return result;
          }
        } else {
          target = uniqueNamedNodeOrNodeList(owner.model(), *raw);
        }
        if (!target) {
          result.valid = false;
          return result;
        }

        if (auto node = target->optionalCast<openstudio::epmodel::Node>()) {
          result.nodes.push_back(*node);
          return result;
        }
        const auto nodeList = target->optionalCast<openstudio::epmodel::NodeList>();
        if (!nodeList) {
          result.valid = false;
          return result;
        }

        const auto groups = nodeList->extensibleGroups();
        result.nodes.reserve(groups.size());
        for (unsigned row = 0u; row < groups.size(); ++row) {
          const auto nodeField = nodeList->iddObject().index(openstudio::ExtensibleIndex(row, openstudio::NodeListExtensibleFields::NodeName));
          const auto observation = readOnlyNodeField(*nodeList, nodeField);
          if (!observation.valid || !observation.hasEvidence || !observation.node) {
            result.valid = false;
            continue;
          }
          result.nodes.push_back(*observation.node);
        }
        return result;
      }

      bool setNodeListField(openstudio::epmodel::ZoneHVACEquipmentConnections& connections, const unsigned field,
                            const std::vector<openstudio::epmodel::Node>& nodes, const std::string& suffix) {
        for (const auto& node : nodes) {
          if (node.model() != connections.model()) {
            return false;
          }
        }

        boost::optional<openstudio::epmodel::NodeList> existingNodeList;
        if (auto target = connections.getTarget(field)) {
          existingNodeList = target->optionalCast<openstudio::epmodel::NodeList>();
        }

        if (nodes.empty()) {
          if (!connections.setPointer(field, Handle())) {
            return false;
          }
          if (existingNodeList && existingNodeList->sources().empty()) {
            existingNodeList->remove();
          }
          return true;
        }

        auto nodeList = existingNodeList ? *existingNodeList : openstudio::epmodel::NodeList(connections.model());
        if (!existingNodeList) {
          const auto baseName =
            connections.nameString().empty() ? connections.model().nextName(connections.iddObject().type(), true) : connections.nameString();
          if (!nodeList.setName(baseName + suffix)) {
            nodeList.createName();
          }
        }

        auto nodeListImpl = nodeList.getImpl<openstudio::epmodel::detail::NodeList_Impl>();
        OS_ASSERT(nodeListImpl);
        while (!nodeList.extensibleGroups().empty()) {
          nodeList.getImpl<openstudio::epmodel::detail::ModelObject_Impl>()->eraseExtensibleGroup(0, false);
        }
        for (const auto& node : nodes) {
          if (!nodeListImpl->addNode(node)) {
            return false;
          }
        }

        return connections.setPointer(field, nodeList.handle());
      }

      bool addNodeToField(const std::vector<openstudio::epmodel::Node>& currentNodes, const openstudio::epmodel::Node& node,
                          const std::function<bool(const std::vector<openstudio::epmodel::Node>&)>& setter) {
        auto nodes = currentNodes;
        if (std::ranges::find(nodes, node) != nodes.end()) {
          return true;
        }
        nodes.push_back(node);
        return setter(nodes);
      }

      bool removeNodeFromField(const std::vector<openstudio::epmodel::Node>& currentNodes, const openstudio::epmodel::Node& node,
                               const std::function<bool(const std::vector<openstudio::epmodel::Node>&)>& setter) {
        auto nodes = currentNodes;
        const auto originalSize = nodes.size();
        nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
        if (nodes.size() == originalSize) {
          return true;
        }
        return setter(nodes);
      }

    }  // namespace

    void ZoneHVACEquipmentConnections_Impl::doCanonicalize(LoadContext& context) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();

      // This object is authoritative for a ThermalZone's inlet and return
      // boundary-node membership. AirLoopHVAC traversal consumes this
      // relationship rather than inferring zone ownership from direct node
      // continuity.

      if (!equipmentConnections.name() || equipmentConnections.name()->empty()) {
        equipmentConnections.createName();
        if (equipmentConnections.name() && !equipmentConnections.name()->empty()) {
          detail::addLoadInfo(context, "Assigned missing ZoneHVAC:EquipmentConnections name '" + equipmentConnections.nameString() + "'.");
        } else {
          detail::addLoadWarning(context, "ZoneHVAC:EquipmentConnections object has no name and automatic name assignment failed.");
        }
      }

      // `ZoneHVAC:EquipmentConnections` is a zone-owned topology object in epmodel. Raw/imported
      // orphan objects are not meaningful steady-state API objects, so repair canonicalization
      // removes them. Once a zone is attached, canonicalization fills derived required topology.
      auto zone =
        equipmentConnections.getModelObjectTarget<openstudio::epmodel::ThermalZone>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
      if (!zone) {
        detail::addLoadWarning(context, "Removed orphan ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString()
                                          + "' because it does not reference a ThermalZone.");
        equipmentConnections.remove();
        return;
      }

      detail::addLoadInfo(context, "Canonicalizing ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString() + "' for ThermalZone '"
                                     + zone->nameString() + "': ensuring required equipment list and zone air node references are present.");

      if (auto equipmentList = equipmentConnections.getModelObjectTarget<openstudio::epmodel::ZoneHVACEquipmentList>(
            openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName)) {
        detail::addLoadInfo(context, "Preserved existing ZoneHVAC:EquipmentList '" + equipmentList->nameString()
                                       + "' on ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString() + "'.");
      } else {
        openstudio::epmodel::ZoneHVACEquipmentList createdEquipmentList(model());
        if (!equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName,
                                             createdEquipmentList.handle())) {
          detail::addLoadError(context, "Failed to attach created ZoneHVAC:EquipmentList '" + createdEquipmentList.nameString()
                                          + "' to ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString() + "'.");
          OS_ASSERT(false);
        } else {
          detail::addLoadInfo(context, "Created ZoneHVAC:EquipmentList '" + createdEquipmentList.nameString()
                                         + "' for ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString() + "' serving ThermalZone '"
                                         + zone->nameString() + "'.");
        }
      }

      const auto inletObservation =
        readOnlyNodeCollectionField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
      const auto zoneAirNodeObservation = readOnlyNodeField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName);
      if (!inletObservation.valid || !zoneAirNodeObservation.valid) {
        detail::addLoadWarning(context, "Preserved unresolved or ambiguous zone inlet/zone air node evidence on ZoneHVAC:EquipmentConnections '"
                                          + equipmentConnections.nameString() + "'.");
        return;
      }

      const auto& inletNodes = inletObservation.nodes;
      const auto existingZoneAirNode = zoneAirNodeObservation.node;
      const bool zoneAirNodeAliasesInlet = existingZoneAirNode && (std::ranges::find(inletNodes, *existingZoneAirNode) != inletNodes.end());
      if (existingZoneAirNode && !zoneAirNodeAliasesInlet) {
        detail::addLoadInfo(context, "Preserved existing zone air node '" + existingZoneAirNode->nameString() + "' on ZoneHVAC:EquipmentConnections '"
                                       + equipmentConnections.nameString() + "'.");
      } else if (zoneAirNodeAliasesInlet && context.policy != SanitizationPolicy::Repair) {
        detail::addLoadWarning(context, "ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString() + "' uses zone air node '"
                                          + existingZoneAirNode->nameString()
                                          + "' as a zone inlet; repair canonicalization must split these EnergyPlus node roles.");
      } else {
        // EnergyPlus requires the zone sensing node to be distinct from every
        // zone inlet. The first air-loop inlet conventionally uses the
        // "Demand Branch Node" stem, so keep this required node separate.
        const auto zoneAirNodeName = zone->nameString() + " Zone Air Node";
        const bool zoneAirNodeAlreadyExisted = static_cast<bool>(model().getObjectByTypeAndName(openstudio::IddObjectType::Node, zoneAirNodeName));
        auto zoneAirNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(zoneAirNodeName);
        bool reusedZoneAirNode = zoneAirNodeAlreadyExisted;
        if (std::ranges::find(inletNodes, zoneAirNode) != inletNodes.end()) {
          // A malformed import may already use the preferred name for an A3
          // inlet. Keep that inlet intact and give the new sensing node the
          // model's next unique Node name.
          zoneAirNode = openstudio::epmodel::Node(model());
          reusedZoneAirNode = false;
        }
        if (!equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName, zoneAirNode.handle())) {
          detail::addLoadError(context, "Failed to attach zone air node '" + zoneAirNode.nameString() + "' to ZoneHVAC:EquipmentConnections '"
                                          + equipmentConnections.nameString() + "'.");
          OS_ASSERT(false);
        } else {
          detail::addLoadInfo(context, std::string(reusedZoneAirNode ? "Reused" : "Created") + " zone air node '" + zoneAirNode.nameString()
                                         + "' and attached it to ZoneHVAC:EquipmentConnections '" + equipmentConnections.nameString() + "'.");
        }
      }
    }

    openstudio::epmodel::ThermalZone ZoneHVACEquipmentConnections_Impl::thermalZone() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      auto zone =
        equipmentConnections.getModelObjectTarget<openstudio::epmodel::ThermalZone>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
      OS_ASSERT(zone);
      return *zone;
    }

    openstudio::epmodel::ZoneHVACEquipmentList ZoneHVACEquipmentConnections_Impl::zoneHVACEquipmentList() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      auto equipmentList = equipmentConnections.getModelObjectTarget<openstudio::epmodel::ZoneHVACEquipmentList>(
        openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);
      OS_ASSERT(equipmentList);
      return *equipmentList;
    }

    bool ZoneHVACEquipmentConnections_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& zone) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (zone.model() != equipmentConnections.model()) {
        return false;
      }
      if (!equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName, zone.handle())) {
        return false;
      }

      auto currentModel = model();
      LoadContext context{currentModel, SanitizationPolicy::Repair, SanitizationReport{}, {}};
      canonicalize(context);
      return true;
    }

    bool ZoneHVACEquipmentConnections_Impl::setZoneHVACEquipmentList(const openstudio::epmodel::ZoneHVACEquipmentList& equipmentList) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (equipmentList.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName,
                                             equipmentList.handle());
    }

    openstudio::epmodel::Node ZoneHVACEquipmentConnections_Impl::zoneAirNode() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (auto node =
            equipmentConnections.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName)) {
        return *node;
      }
      auto node = resolvedNodeTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName);
      OS_ASSERT(node);
      return *node;
    }

    std::vector<openstudio::epmodel::Node> ZoneHVACEquipmentConnections_Impl::zoneAirInletNodes() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return resolveNodeOrNodeListField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
    }

    bool ZoneHVACEquipmentConnections_Impl::addZoneAirInletNode(const openstudio::epmodel::Node& node) {
      return addNodeToField(zoneAirInletNodes(), node, [this](const auto& nodes) { return setZoneAirInletNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::removeZoneAirInletNode(const openstudio::epmodel::Node& node) {
      return removeNodeFromField(zoneAirInletNodes(), node, [this](const auto& nodes) { return setZoneAirInletNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::setZoneAirInletNodes(const std::vector<openstudio::epmodel::Node>& nodes) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return setNodeListField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, nodes,
                              " Inlet Node List");
    }

    std::vector<openstudio::epmodel::Node> ZoneHVACEquipmentConnections_Impl::zoneAirExhaustNodes() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return resolveNodeOrNodeListField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
    }

    bool ZoneHVACEquipmentConnections_Impl::addZoneAirExhaustNode(const openstudio::epmodel::Node& node) {
      if (!hasExclusiveZoneAirExhaustNodeStorage()) {
        return false;
      }
      return addNodeToField(zoneAirExhaustNodes(), node, [this](const auto& nodes) { return setZoneAirExhaustNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::removeZoneAirExhaustNode(const openstudio::epmodel::Node& node) {
      if (!hasExclusiveZoneAirExhaustNodeStorage()) {
        return false;
      }
      return removeNodeFromField(zoneAirExhaustNodes(), node, [this](const auto& nodes) { return setZoneAirExhaustNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::hasExclusiveZoneAirExhaustNodeStorage() const {
      const auto connections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      constexpr unsigned field = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
      const auto target = connections.getTarget(field);
      if (!target || !target->optionalCast<openstudio::epmodel::NodeList>()) {
        return true;
      }

      std::size_t referenceCount = 0u;
      bool foundExpectedReference = false;
      for (const auto& source : target->sources()) {
        for (const auto sourceField : source.getSourceIndices(target->handle())) {
          ++referenceCount;
          foundExpectedReference = foundExpectedReference || ((source.handle() == connections.handle()) && (sourceField == field));
        }
      }
      return foundExpectedReference && (referenceCount == 1u);
    }

    bool ZoneHVACEquipmentConnections_Impl::setZoneAirExhaustNodes(const std::vector<openstudio::epmodel::Node>& nodes) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return setNodeListField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, nodes,
                              " Exhaust Node List");
    }

    std::vector<openstudio::epmodel::Node> ZoneHVACEquipmentConnections_Impl::zoneReturnAirNodes() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return resolveNodeOrNodeListField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName);
    }

    bool ZoneHVACEquipmentConnections_Impl::addZoneReturnAirNode(const openstudio::epmodel::Node& node) {
      return addNodeToField(zoneReturnAirNodes(), node, [this](const auto& nodes) { return setZoneReturnAirNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::removeZoneReturnAirNode(const openstudio::epmodel::Node& node) {
      return removeNodeFromField(zoneReturnAirNodes(), node, [this](const auto& nodes) { return setZoneReturnAirNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::setZoneReturnAirNodes(const std::vector<openstudio::epmodel::Node>& nodes) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return setNodeListField(equipmentConnections, openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, nodes,
                              " Return Node List");
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
