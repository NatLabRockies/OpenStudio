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

  ZoneHVACEquipmentConnections::ZoneHVACEquipmentConnections(const Model& model) : ModelObject(ZoneHVACEquipmentConnections::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ZoneHVACEquipmentConnections::ZoneHVACEquipmentConnections(std::shared_ptr<detail::ZoneHVACEquipmentConnections_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACEquipmentConnections::iddObjectType() {
    return IddObjectType::ZoneHVAC_EquipmentConnections;
  }

  boost::optional<ThermalZone> ZoneHVACEquipmentConnections::thermalZone() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->thermalZone();
  }

  boost::optional<ZoneHVACEquipmentList> ZoneHVACEquipmentConnections::zoneHVACEquipmentList() const {
    return getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->zoneHVACEquipmentList();
  }

  boost::optional<Node> ZoneHVACEquipmentConnections::zoneAirNode() const {
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
            if (auto nodeList = connections.model().getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *nodeOrListName, true)) {
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

        if (nodes.empty()) {
          return connections.setPointer(field, Handle());
        }

        openstudio::epmodel::NodeList nodeList(connections.model());
        const auto baseName =
          connections.nameString().empty() ? connections.model().nextName(connections.iddObject().type(), true) : connections.nameString();
        if (!nodeList.setName(baseName + suffix)) {
          nodeList.createName();
        }

        auto nodeListImpl = nodeList.getImpl<openstudio::epmodel::detail::NodeList_Impl>();
        OS_ASSERT(nodeListImpl);
        for (const auto& node : nodes) {
          if (!nodeListImpl->addNode(node)) {
            return false;
          }
        }

        return connections.setPointer(field, nodeList.handle());
      }

      boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> getOrCreateEquipmentList(
        openstudio::epmodel::ZoneHVACEquipmentConnections& connections) {
        if (auto equipmentList = connections.getModelObjectTarget<openstudio::epmodel::ZoneHVACEquipmentList>(
              openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName)) {
          return equipmentList;
        }

        openstudio::epmodel::ZoneHVACEquipmentList equipmentList(connections.model());
        if (!equipmentList.name()) {
          equipmentList.createName();
        }
        if (!connections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName, equipmentList.handle())) {
          return boost::none;
        }
        return equipmentList;
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

    boost::optional<openstudio::epmodel::ThermalZone> ZoneHVACEquipmentConnections_Impl::thermalZone() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return equipmentConnections.getModelObjectTarget<openstudio::epmodel::ThermalZone>(
        openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
    }

    boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> ZoneHVACEquipmentConnections_Impl::zoneHVACEquipmentList() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      return equipmentConnections.getModelObjectTarget<openstudio::epmodel::ZoneHVACEquipmentList>(
        openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);
    }

    bool ZoneHVACEquipmentConnections_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& zone) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (zone.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName, zone.handle());
    }

    bool ZoneHVACEquipmentConnections_Impl::setZoneHVACEquipmentList(const openstudio::epmodel::ZoneHVACEquipmentList& equipmentList) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (equipmentList.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName,
                                             equipmentList.handle());
    }

    bool ZoneHVACEquipmentConnections_Impl::setZoneAirNode(const openstudio::epmodel::Node& node) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (node.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName, node.handle());
    }

    bool ZoneHVACEquipmentConnections_Impl::addEquipment(const openstudio::epmodel::ModelObject& equipment,
                                                        const std::vector<openstudio::epmodel::Node>& inletNodes,
                                                        const std::vector<openstudio::epmodel::Node>& exhaustNodes,
                                                        const std::vector<openstudio::epmodel::Node>& returnNodes) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (equipment.model() != equipmentConnections.model()) {
        return false;
      }

      auto equipmentList = getOrCreateEquipmentList(equipmentConnections);
      if (!equipmentList) {
        return false;
      }
      if (!equipmentList->getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentList_Impl>()->addEquipment(equipment)) {
        return false;
      }

      for (const auto& node : inletNodes) {
        if (!addZoneAirInletNode(node)) {
          return false;
        }
      }
      for (const auto& node : exhaustNodes) {
        if (!addZoneAirExhaustNode(node)) {
          return false;
        }
      }
      for (const auto& node : returnNodes) {
        if (!addZoneReturnAirNode(node)) {
          return false;
        }
      }
      return true;
    }

    bool ZoneHVACEquipmentConnections_Impl::removeEquipment(const openstudio::epmodel::ModelObject& equipment,
                                                           const std::vector<openstudio::epmodel::Node>& inletNodes,
                                                           const std::vector<openstudio::epmodel::Node>& exhaustNodes,
                                                           const std::vector<openstudio::epmodel::Node>& returnNodes) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (equipment.model() != equipmentConnections.model()) {
        return false;
      }

      if (auto equipmentList = zoneHVACEquipmentList()) {
        equipmentList->getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentList_Impl>()->removeEquipment(equipment);
      }

      for (const auto& node : inletNodes) {
        if (!removeZoneAirInletNode(node)) {
          return false;
        }
      }
      for (const auto& node : exhaustNodes) {
        if (!removeZoneAirExhaustNode(node)) {
          return false;
        }
      }
      for (const auto& node : returnNodes) {
        if (!removeZoneReturnAirNode(node)) {
          return false;
        }
      }
      return true;
    }

    boost::optional<openstudio::epmodel::Node> ZoneHVACEquipmentConnections_Impl::zoneAirNode() const {
      const auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (auto node = equipmentConnections.getModelObjectTarget<openstudio::epmodel::Node>(
            openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName)) {
        return node;
      }
      return resolvedNodeTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName);
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
