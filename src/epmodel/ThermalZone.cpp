/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "ZoneHVACEquipmentConnections.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"
#include "ZoneHVACEquipmentList.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

namespace {

bool setZoneSplitterBranchNode(AirLoopHVACZoneSplitter& splitter, unsigned branchIndex, const Node& branchNode) {
  auto groups = splitter.extensibleGroups();
  IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : splitter.pushExtensibleGroup();

  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!workspaceGroup) {
    return false;
  }

  return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ZoneSplitterExtensibleFields::OutletNodeName, branchNode.handle());
}

bool setZoneMixerBranchNode(AirLoopHVACZoneMixer& mixer, unsigned branchIndex, const Node& branchNode) {
  auto groups = mixer.extensibleGroups();
  IdfExtensibleGroup group = (branchIndex < groups.size()) ? groups[branchIndex] : mixer.pushExtensibleGroup();

  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!workspaceGroup) {
    return false;
  }

  return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ZoneMixerExtensibleFields::InletNodeName, branchNode.handle());
}

}  // namespace

ThermalZone::ThermalZone(const Model& model) : ModelObject(ThermalZone::iddObjectType(), model) {
  auto impl = getImpl<detail::ThermalZone_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

ThermalZone::ThermalZone(std::shared_ptr<detail::ThermalZone_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ThermalZone::iddObjectType() {
  return IddObjectType::Zone;
}

bool ThermalZone::addToNode(Node& node) {
  if (node.model() != model()) {
    return false;
  }

  auto loop = node.airLoopHVAC();
  if (!loop) {
    return false;
  }

  auto zoneSplitter = loop->zoneSplitter();
  auto zoneMixer = loop->zoneMixer();
  const auto splitterOutlets = zoneSplitter.outletModelObjects();
  const auto mixerInlets = zoneMixer.inletModelObjects();
  const auto thisNode = node.cast<ModelObject>();

  boost::optional<unsigned> targetBranchIndex;
  const auto sharedCount = std::min(splitterOutlets.size(), mixerInlets.size());
  for (unsigned i = 0; i < sharedCount; ++i) {
    if ((splitterOutlets[i] == thisNode) && (mixerInlets[i] == thisNode)) {
      targetBranchIndex = i;
      break;
    }
  }
  if (!targetBranchIndex) {
    return false;
  }

  const std::string zoneBranchNodeName = nameString() + " Demand Branch Node";
  auto zoneBranchNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(zoneBranchNodeName);

  if ((splitterOutlets[*targetBranchIndex] == zoneBranchNode.cast<ModelObject>())
      && (mixerInlets[*targetBranchIndex] == zoneBranchNode.cast<ModelObject>())) {
    return false;
  }

  if (!setZoneSplitterBranchNode(zoneSplitter, *targetBranchIndex, zoneBranchNode)) {
    return false;
  }

  if (!setZoneMixerBranchNode(zoneMixer, *targetBranchIndex, zoneBranchNode)) {
    return false;
  }

  auto zoneConnections = getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneAirInletNode(zoneBranchNode)) {
    return false;
  }
  if (!zoneConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneReturnAirNode(zoneBranchNode)) {
    return false;
  }

  for (const auto& airLoop : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
    airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
  }

  return true;
}

SizingZone ThermalZone::sizingZone() const {
  return getImpl<detail::ThermalZone_Impl>()->sizingZone();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<openstudio::epmodel::ZoneHVACEquipmentConnections> ThermalZone_Impl::zoneHVACEquipmentConnections() const {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  for (const auto& conn : model().getConcreteModelObjects<openstudio::epmodel::ZoneHVACEquipmentConnections>()) {
    if (auto linkedZone = conn.thermalZone()) {
      if (*linkedZone == zone) {
        return conn;
      }
    }
  }
  return boost::none;
}

openstudio::epmodel::ZoneHVACEquipmentConnections ThermalZone_Impl::getZoneHVACEquipmentConnections() {
  if (auto conn = zoneHVACEquipmentConnections()) {
    return *conn;
  }

  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  openstudio::epmodel::ZoneHVACEquipmentConnections conn(model());
  conn.createName();
  if (!conn.name() || conn.name()->empty()) {
    conn.setName(model().nextName(openstudio::IddObjectType::ZoneHVAC_EquipmentConnections, true));
  }
  if (!conn.getImpl<openstudio::epmodel::detail::ZoneHVACEquipmentConnections_Impl>()->setThermalZone(zone)) {
    OS_ASSERT(false);
  }

  return conn;
}

boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> ThermalZone_Impl::zoneHVACEquipmentList() const {
  auto conn = zoneHVACEquipmentConnections();
  if (!conn) {
    return boost::none;
  }

  const auto equipmentListName =
    conn->getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);
  if (!equipmentListName || equipmentListName->empty()) {
    return boost::none;
  }

  if (auto object = model().getObjectByTypeAndName(openstudio::IddObjectType::ZoneHVAC_EquipmentList, *equipmentListName, true)) {
    return object->optionalCast<openstudio::epmodel::ZoneHVACEquipmentList>();
  }

  return boost::none;
}

boost::optional<openstudio::epmodel::SizingZone> ThermalZone_Impl::optionalSizingZone() const {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  for (const auto& sizingZone : model().getConcreteModelObjects<openstudio::epmodel::SizingZone>()) {
    auto sizingZoneImpl = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>();
    OS_ASSERT(sizingZoneImpl);
    auto sizingZoneThermalZone = sizingZoneImpl->optionalThermalZone();
    if (sizingZoneThermalZone && (*sizingZoneThermalZone == zone)) {
      return sizingZone;
    }
  }
  return boost::none;
}

openstudio::epmodel::SizingZone ThermalZone_Impl::sizingZone() {
  if (auto result = optionalSizingZone()) {
    return *result;
  }

  return openstudio::epmodel::SizingZone(model(), getObject<openstudio::epmodel::ThermalZone>());
}

void ThermalZone_Impl::doCanonicalize(LoadContext& context) {
  auto sz = sizingZone();
  sz.getImpl<openstudio::epmodel::detail::SizingZone_Impl>()->canonicalize(context);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
