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

      if (auto existingZoneAirNode =
            equipmentConnections.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName)) {
        detail::addLoadInfo(context, "Preserved existing zone air node '" + existingZoneAirNode->nameString() + "' on ZoneHVAC:EquipmentConnections '"
                                       + equipmentConnections.nameString() + "'.");
      } else {
        const auto zoneAirNodeName = zone->nameString() + " Demand Branch Node";
        const bool zoneAirNodeAlreadyExisted = static_cast<bool>(model().getObjectByTypeAndName(openstudio::IddObjectType::Node, zoneAirNodeName));
        auto zoneAirNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(zoneAirNodeName);
        if (!equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName, zoneAirNode.handle())) {
          detail::addLoadError(context, "Failed to attach zone air node '" + zoneAirNode.nameString() + "' to ZoneHVAC:EquipmentConnections '"
                                          + equipmentConnections.nameString() + "'.");
          OS_ASSERT(false);
        } else {
          detail::addLoadInfo(context, std::string(zoneAirNodeAlreadyExisted ? "Reused" : "Created") + " zone air node '" + zoneAirNode.nameString()
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
      return addNodeToField(zoneAirExhaustNodes(), node, [this](const auto& nodes) { return setZoneAirExhaustNodes(nodes); });
    }

    bool ZoneHVACEquipmentConnections_Impl::removeZoneAirExhaustNode(const openstudio::epmodel::Node& node) {
      return removeNodeFromField(zoneAirExhaustNodes(), node, [this](const auto& nodes) { return setZoneAirExhaustNodes(nodes); });
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
