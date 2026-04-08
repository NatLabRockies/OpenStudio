/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"

#include "Model.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

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
    return getModelObjectTarget<ThermalZone>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName);
  }

  namespace detail {

    bool ZoneHVACEquipmentConnections_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& zone) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (zone.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName, zone.handle());
    }

  }  // namespace detail

  boost::optional<Node> ZoneHVACEquipmentConnections::zoneAirInletNode() const {
    const auto nodes = zoneAirInletNodes();
    return nodes.empty() ? boost::optional<Node>() : boost::optional<Node>(nodes.front());
  }

  std::vector<Node> ZoneHVACEquipmentConnections::zoneAirInletNodes() const {
    const auto field = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName;
    if (auto target = getTarget(field)) {
      if (auto node = target->optionalCast<Node>()) {
        return {*node};
      }
      if (target->iddObject().type() == openstudio::IddObjectType::NodeList) {
        std::vector<Node> result;
        for (const auto& group : target->extensibleGroups()) {
          auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
          if (!listedNodeName || listedNodeName->empty()) {
            continue;
          }
          if (auto listedNode = model().getObjectByTypeAndName(Node::iddObjectType(), *listedNodeName, true)) {
            if (auto castNode = listedNode->optionalCast<Node>()) {
              result.push_back(*castNode);
            }
          }
        }
        return result;
      }
    }

    if (auto nodeOrListName = getString(field)) {
      if (!nodeOrListName->empty()) {
        if (auto nodeList = model().getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *nodeOrListName, true)) {
          if (!getImpl<detail::ModelObject_Impl>()->setPointer(field, nodeList->handle(), false)) {
            return {};
          }
          std::vector<Node> result;
          for (const auto& group : nodeList->extensibleGroups()) {
            auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
            if (!listedNodeName || listedNodeName->empty()) {
              continue;
            }
            if (auto listedNode = model().getObjectByTypeAndName(Node::iddObjectType(), *listedNodeName, true)) {
              if (auto castNode = listedNode->optionalCast<Node>()) {
                result.push_back(*castNode);
              }
            }
          }
          return result;
        }

        if (auto node = getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(field)) {
          return {*node};
        }
      }
    }

    return {};
  }

  namespace detail {

    bool ZoneHVACEquipmentConnections_Impl::setZoneAirInletNode(const openstudio::epmodel::Node& node) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (node.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, node.handle());
    }

  }  // namespace detail

  boost::optional<Node> ZoneHVACEquipmentConnections::zoneReturnAirNode() const {
    const auto nodes = zoneReturnAirNodes();
    return nodes.empty() ? boost::optional<Node>() : boost::optional<Node>(nodes.front());
  }

  std::vector<Node> ZoneHVACEquipmentConnections::zoneReturnAirNodes() const {
    const auto field = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName;
    if (auto target = getTarget(field)) {
      if (auto node = target->optionalCast<Node>()) {
        return {*node};
      }
      if (target->iddObject().type() == openstudio::IddObjectType::NodeList) {
        std::vector<Node> result;
        for (const auto& group : target->extensibleGroups()) {
          auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
          if (!listedNodeName || listedNodeName->empty()) {
            continue;
          }
          if (auto listedNode = model().getObjectByTypeAndName(Node::iddObjectType(), *listedNodeName, true)) {
            if (auto castNode = listedNode->optionalCast<Node>()) {
              result.push_back(*castNode);
            }
          }
        }
        return result;
      }
    }

    if (auto nodeOrListName = getString(field)) {
      if (!nodeOrListName->empty()) {
        if (auto nodeList = model().getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *nodeOrListName, true)) {
          if (!getImpl<detail::ModelObject_Impl>()->setPointer(field, nodeList->handle(), false)) {
            return {};
          }
          std::vector<Node> result;
          for (const auto& group : nodeList->extensibleGroups()) {
            auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
            if (!listedNodeName || listedNodeName->empty()) {
              continue;
            }
            if (auto listedNode = model().getObjectByTypeAndName(Node::iddObjectType(), *listedNodeName, true)) {
              if (auto castNode = listedNode->optionalCast<Node>()) {
                result.push_back(*castNode);
              }
            }
          }
          return result;
        }

        if (auto node = getImpl<detail::ModelObject_Impl>()->resolvedNodeTarget(field)) {
          return {*node};
        }
      }
    }

    return {};
  }

  namespace detail {

    bool ZoneHVACEquipmentConnections_Impl::setZoneReturnAirNode(const openstudio::epmodel::Node& node) {
      auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
      if (node.model() != equipmentConnections.model()) {
        return false;
      }
      return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName, node.handle());
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
