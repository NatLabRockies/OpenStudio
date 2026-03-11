/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACEquipmentConnections.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"

#include "Model.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

namespace {

std::vector<Node> resolveNodeOrNodeListByName(const Model& model, const boost::optional<std::string>& nodeOrListName) {
  if (!nodeOrListName || nodeOrListName->empty()) {
    return {};
  }

  if (auto node = model.getObjectByTypeAndName(Node::iddObjectType(), *nodeOrListName, true)) {
    if (auto castNode = node->optionalCast<Node>()) {
      return {*castNode};
    }
  }

  std::vector<Node> result;
  if (auto nodeList = model.getObjectByTypeAndName(openstudio::IddObjectType::NodeList, *nodeOrListName, true)) {
    for (const auto& group : nodeList->extensibleGroups()) {
      auto listedNodeName = group.getString(openstudio::NodeListExtensibleFields::NodeName);
      if (!listedNodeName || listedNodeName->empty()) {
        continue;
      }
      if (auto listedNode = model.getObjectByTypeAndName(Node::iddObjectType(), *listedNodeName, true)) {
        if (auto castNode = listedNode->optionalCast<Node>()) {
          result.push_back(*castNode);
        }
      }
    }
  }

  return result;
}

}  // namespace

ZoneHVACEquipmentConnections::ZoneHVACEquipmentConnections(const Model& model)
  : ModelObject(ZoneHVACEquipmentConnections::iddObjectType(), model) {
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
  if (auto zoneName = getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName)) {
    if (auto zoneObject = model().getObjectByTypeAndName(ThermalZone::iddObjectType(), *zoneName, true)) {
      return zoneObject->optionalCast<ThermalZone>();
    }
  }
  return boost::none;
}

boost::optional<Node> ZoneHVACEquipmentConnections::zoneAirInletNode() const {
  const auto nodes = zoneAirInletNodes();
  if (!nodes.empty()) {
    return nodes.front();
  }
  return boost::none;
}

std::vector<Node> ZoneHVACEquipmentConnections::zoneAirInletNodes() const {
  auto nodeOrListName = getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName);
  return resolveNodeOrNodeListByName(model(), nodeOrListName);
}

boost::optional<Node> ZoneHVACEquipmentConnections::zoneReturnAirNode() const {
  const auto nodes = zoneReturnAirNodes();
  if (!nodes.empty()) {
    return nodes.front();
  }
  return boost::none;
}

std::vector<Node> ZoneHVACEquipmentConnections::zoneReturnAirNodes() const {
  auto nodeOrListName = getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName);
  return resolveNodeOrNodeListByName(model(), nodeOrListName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

bool ZoneHVACEquipmentConnections_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& zone) {
  auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
  if (zone.model() != equipmentConnections.model()) {
    return false;
  }
  return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneName, zone.handle());
}

bool ZoneHVACEquipmentConnections_Impl::setZoneAirInletNode(const openstudio::epmodel::Node& node) {
  auto equipmentConnections = getObject<openstudio::epmodel::ZoneHVACEquipmentConnections>();
  if (node.model() != equipmentConnections.model()) {
    return false;
  }
  return equipmentConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName, node.handle());
}

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
