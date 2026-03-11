/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "DesignSpecificationOutdoorAir.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "Space.hpp"
#include "Space_Impl.hpp"
#include "ZoneHVACEquipmentConnections.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"
#include "ZoneHVACEquipmentList.hpp"
#include "ZoneHVACEquipmentList_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/Daylighting_Controls_FieldEnums.hxx>
#include <utilities/idd/Daylighting_ReferencePoint_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

namespace {

constexpr unsigned kPrimaryDaylightingReferencePointIndex = 0u;
constexpr unsigned kSecondaryDaylightingReferencePointIndex = 1u;

boost::optional<openstudio::WorkspaceObject> daylightingControlsForZone(const ThermalZone& zone) {
  for (const auto& object : zone.model().getObjectsByType(openstudio::IddObjectType::Daylighting_Controls)) {
    auto zoneOrSpaceName = object.getString(openstudio::Daylighting_ControlsFields::ZoneorSpaceName, true);
    if (zoneOrSpaceName && openstudio::istringEqual(*zoneOrSpaceName, zone.nameString())) {
      return object;
    }
  }
  return boost::none;
}

boost::optional<openstudio::WorkspaceObject> daylightingReferencePointForZone(const ThermalZone& zone, unsigned referencePointIndex) {
  auto daylightingControls = daylightingControlsForZone(zone);
  if (!daylightingControls) {
    return boost::none;
  }

  const auto groups = daylightingControls->extensibleGroups();
  if (referencePointIndex >= groups.size()) {
    return boost::none;
  }

  auto group = groups[referencePointIndex].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!group) {
    return boost::none;
  }

  auto referencePointName = group->getString(openstudio::Daylighting_ControlsExtensibleFields::DaylightingReferencePointName, true);
  if (!referencePointName || referencePointName->empty()) {
    return boost::none;
  }

  return zone.model().getObjectByTypeAndName(openstudio::IddObjectType::Daylighting_ReferencePoint, *referencePointName, true);
}

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

std::string ThermalZone::outdoorAirMethod() const {
  return getImpl<detail::ThermalZone_Impl>()->outdoorAirMethod();
}

bool ThermalZone::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  return getImpl<detail::ThermalZone_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
}

double ThermalZone::outdoorAirFlowperPerson() const {
  return getImpl<detail::ThermalZone_Impl>()->outdoorAirFlowperPerson();
}

bool ThermalZone::setOutdoorAirFlowperPerson(double outdoorAirFlowperPerson) {
  return getImpl<detail::ThermalZone_Impl>()->setOutdoorAirFlowperPerson(outdoorAirFlowperPerson);
}

double ThermalZone::outdoorAirFlowperFloorArea() const {
  return getImpl<detail::ThermalZone_Impl>()->outdoorAirFlowperFloorArea();
}

bool ThermalZone::setOutdoorAirFlowperFloorArea(double outdoorAirFlowperFloorArea) {
  return getImpl<detail::ThermalZone_Impl>()->setOutdoorAirFlowperFloorArea(outdoorAirFlowperFloorArea);
}

double ThermalZone::outdoorAirFlowRate() const {
  return getImpl<detail::ThermalZone_Impl>()->outdoorAirFlowRate();
}

bool ThermalZone::setOutdoorAirFlowRate(double outdoorAirFlowRate) {
  return getImpl<detail::ThermalZone_Impl>()->setOutdoorAirFlowRate(outdoorAirFlowRate);
}

double ThermalZone::outdoorAirFlowAirChangesperHour() const {
  return getImpl<detail::ThermalZone_Impl>()->outdoorAirFlowAirChangesperHour();
}

bool ThermalZone::setOutdoorAirFlowAirChangesperHour(double outdoorAirFlowAirChangesperHour) {
  return getImpl<detail::ThermalZone_Impl>()->setOutdoorAirFlowAirChangesperHour(outdoorAirFlowAirChangesperHour);
}

double ThermalZone::fractionofZoneControlledbyPrimaryDaylightingControl() const {
  return getImpl<detail::ThermalZone_Impl>()->fractionofZoneControlledbyPrimaryDaylightingControl();
}

bool ThermalZone::isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted() const {
  return getImpl<detail::ThermalZone_Impl>()->isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted();
}

bool ThermalZone::setFractionofZoneControlledbyPrimaryDaylightingControl(double fractionofZoneControlledbyPrimaryDaylightingControl) {
  return getImpl<detail::ThermalZone_Impl>()->setFractionofZoneControlledbyPrimaryDaylightingControl(
    fractionofZoneControlledbyPrimaryDaylightingControl);
}

void ThermalZone::resetFractionofZoneControlledbyPrimaryDaylightingControl() {
  getImpl<detail::ThermalZone_Impl>()->resetFractionofZoneControlledbyPrimaryDaylightingControl();
}

double ThermalZone::fractionofZoneControlledbySecondaryDaylightingControl() const {
  return getImpl<detail::ThermalZone_Impl>()->fractionofZoneControlledbySecondaryDaylightingControl();
}

bool ThermalZone::isFractionofZoneControlledbySecondaryDaylightingControlDefaulted() const {
  return getImpl<detail::ThermalZone_Impl>()->isFractionofZoneControlledbySecondaryDaylightingControlDefaulted();
}

bool ThermalZone::setFractionofZoneControlledbySecondaryDaylightingControl(double fractionofZoneControlledbySecondaryDaylightingControl) {
  return getImpl<detail::ThermalZone_Impl>()->setFractionofZoneControlledbySecondaryDaylightingControl(
    fractionofZoneControlledbySecondaryDaylightingControl);
}

void ThermalZone::resetFractionofZoneControlledbySecondaryDaylightingControl() {
  getImpl<detail::ThermalZone_Impl>()->resetFractionofZoneControlledbySecondaryDaylightingControl();
}

double ThermalZone::primaryDaylightingControlXCoordinate() const {
  return getImpl<detail::ThermalZone_Impl>()->primaryDaylightingControlXCoordinate();
}

double ThermalZone::primaryDaylightingControlYCoordinate() const {
  return getImpl<detail::ThermalZone_Impl>()->primaryDaylightingControlYCoordinate();
}

double ThermalZone::primaryDaylightingControlZCoordinate() const {
  return getImpl<detail::ThermalZone_Impl>()->primaryDaylightingControlZCoordinate();
}

bool ThermalZone::setPrimaryDaylightingControlXCoordinate(double primaryDaylightingControlXCoordinate) {
  return getImpl<detail::ThermalZone_Impl>()->setPrimaryDaylightingControlXCoordinate(primaryDaylightingControlXCoordinate);
}

bool ThermalZone::setPrimaryDaylightingControlYCoordinate(double primaryDaylightingControlYCoordinate) {
  return getImpl<detail::ThermalZone_Impl>()->setPrimaryDaylightingControlYCoordinate(primaryDaylightingControlYCoordinate);
}

bool ThermalZone::setPrimaryDaylightingControlZCoordinate(double primaryDaylightingControlZCoordinate) {
  return getImpl<detail::ThermalZone_Impl>()->setPrimaryDaylightingControlZCoordinate(primaryDaylightingControlZCoordinate);
}

double ThermalZone::secondaryDaylightingControlXCoordinate() const {
  return getImpl<detail::ThermalZone_Impl>()->secondaryDaylightingControlXCoordinate();
}

double ThermalZone::secondaryDaylightingControlYCoordinate() const {
  return getImpl<detail::ThermalZone_Impl>()->secondaryDaylightingControlYCoordinate();
}

double ThermalZone::secondaryDaylightingControlZCoordinate() const {
  return getImpl<detail::ThermalZone_Impl>()->secondaryDaylightingControlZCoordinate();
}

bool ThermalZone::setSecondaryDaylightingControlXCoordinate(double secondaryDaylightingControlXCoordinate) {
  return getImpl<detail::ThermalZone_Impl>()->setSecondaryDaylightingControlXCoordinate(secondaryDaylightingControlXCoordinate);
}

bool ThermalZone::setSecondaryDaylightingControlYCoordinate(double secondaryDaylightingControlYCoordinate) {
  return getImpl<detail::ThermalZone_Impl>()->setSecondaryDaylightingControlYCoordinate(secondaryDaylightingControlYCoordinate);
}

bool ThermalZone::setSecondaryDaylightingControlZCoordinate(double secondaryDaylightingControlZCoordinate) {
  return getImpl<detail::ThermalZone_Impl>()->setSecondaryDaylightingControlZCoordinate(secondaryDaylightingControlZCoordinate);
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

std::vector<openstudio::epmodel::Space> ThermalZone_Impl::spaces() const {
  std::vector<openstudio::epmodel::Space> result;
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  for (const auto& space : model().getConcreteModelObjects<openstudio::epmodel::Space>()) {
    if (auto zoneForSpace = space.thermalZone()) {
      if (*zoneForSpace == zone) {
        result.emplace_back(space);
      }
    }
  }
  return result;
}

boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> ThermalZone_Impl::zoneSharedDesignSpecificationOutdoorAir() const {
  boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> result;
  bool foundAnyZoneSpace = false;
  for (const auto& space : spaces()) {
    foundAnyZoneSpace = true;
    auto dsoa = space.designSpecificationOutdoorAir();
    if (!dsoa) {
      return boost::none;
    }
    if (!result) {
      result = dsoa;
      continue;
    }
    if (result->handle() != dsoa->handle()) {
      return boost::none;
    }
  }
  if (!foundAnyZoneSpace) {
    return boost::none;
  }
  return result;
}

boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> ThermalZone_Impl::getOrCreateZoneSharedDesignSpecificationOutdoorAir() {
  auto zoneSpaces = spaces();
  if (zoneSpaces.empty()) {
    return boost::none;
  }

  auto shared = zoneSharedDesignSpecificationOutdoorAir();
  openstudio::epmodel::DesignSpecificationOutdoorAir target = shared ? *shared : openstudio::epmodel::DesignSpecificationOutdoorAir(model());
  if (!shared && !target.name()) {
    target.setName(getObject<openstudio::epmodel::ThermalZone>().nameString() + " DSOA");
  }

  for (auto& space : zoneSpaces) {
    if (!space.setDesignSpecificationOutdoorAir(target)) {
      return boost::none;
    }
  }

  return target;
}

std::string ThermalZone_Impl::outdoorAirMethod() const {
  if (auto dsoa = zoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->outdoorAirMethod();
  }
  return "Sum";
}

bool ThermalZone_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
  if (auto dsoa = getOrCreateZoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->setOutdoorAirMethod(outdoorAirMethod);
  }
  return false;
}

double ThermalZone_Impl::outdoorAirFlowperPerson() const {
  if (auto dsoa = zoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->outdoorAirFlowperPerson();
  }
  return 0.0;
}

bool ThermalZone_Impl::setOutdoorAirFlowperPerson(double outdoorAirFlowperPerson) {
  if (auto dsoa = getOrCreateZoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->setOutdoorAirFlowperPerson(outdoorAirFlowperPerson);
  }
  return false;
}

double ThermalZone_Impl::outdoorAirFlowperFloorArea() const {
  if (auto dsoa = zoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->outdoorAirFlowperFloorArea();
  }
  return 0.0;
}

bool ThermalZone_Impl::setOutdoorAirFlowperFloorArea(double outdoorAirFlowperFloorArea) {
  if (auto dsoa = getOrCreateZoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->setOutdoorAirFlowperFloorArea(outdoorAirFlowperFloorArea);
  }
  return false;
}

double ThermalZone_Impl::outdoorAirFlowRate() const {
  if (auto dsoa = zoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->outdoorAirFlowRate();
  }
  return 0.0;
}

bool ThermalZone_Impl::setOutdoorAirFlowRate(double outdoorAirFlowRate) {
  if (auto dsoa = getOrCreateZoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->setOutdoorAirFlowRate(outdoorAirFlowRate);
  }
  return false;
}

double ThermalZone_Impl::outdoorAirFlowAirChangesperHour() const {
  if (auto dsoa = zoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->outdoorAirFlowAirChangesperHour();
  }
  return 0.0;
}

bool ThermalZone_Impl::setOutdoorAirFlowAirChangesperHour(double outdoorAirFlowAirChangesperHour) {
  if (auto dsoa = getOrCreateZoneSharedDesignSpecificationOutdoorAir()) {
    return dsoa->setOutdoorAirFlowAirChangesperHour(outdoorAirFlowAirChangesperHour);
  }
  return false;
}

boost::optional<double> ThermalZone_Impl::daylightingFraction(unsigned referencePointIndex) const {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  auto daylightingControls = daylightingControlsForZone(zone);
  if (!daylightingControls) {
    return boost::none;
  }

  const auto groups = daylightingControls->extensibleGroups();
  if (referencePointIndex >= groups.size()) {
    return boost::none;
  }

  auto group = groups[referencePointIndex].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!group) {
    return boost::none;
  }

  return group->getDouble(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, false);
}

double ThermalZone_Impl::fractionofZoneControlledbyPrimaryDaylightingControl() const {
  if (auto value = daylightingFraction(kPrimaryDaylightingReferencePointIndex)) {
    return *value;
  }
  return 1.0;
}

bool ThermalZone_Impl::isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted() const {
  return !daylightingFraction(kPrimaryDaylightingReferencePointIndex);
}

bool ThermalZone_Impl::setFractionofZoneControlledbyPrimaryDaylightingControl(double fractionofZoneControlledbyPrimaryDaylightingControl) {
  if ((fractionofZoneControlledbyPrimaryDaylightingControl + fractionofZoneControlledbySecondaryDaylightingControl()) > 1.0) {
    return false;
  }
  return setDaylightingFraction(kPrimaryDaylightingReferencePointIndex, fractionofZoneControlledbyPrimaryDaylightingControl);
}

void ThermalZone_Impl::resetFractionofZoneControlledbyPrimaryDaylightingControl() {
  resetDaylightingFraction(kPrimaryDaylightingReferencePointIndex);
}

double ThermalZone_Impl::fractionofZoneControlledbySecondaryDaylightingControl() const {
  if (auto value = daylightingFraction(kSecondaryDaylightingReferencePointIndex)) {
    return *value;
  }
  return 0.0;
}

bool ThermalZone_Impl::isFractionofZoneControlledbySecondaryDaylightingControlDefaulted() const {
  return !daylightingFraction(kSecondaryDaylightingReferencePointIndex);
}

bool ThermalZone_Impl::setFractionofZoneControlledbySecondaryDaylightingControl(double fractionofZoneControlledbySecondaryDaylightingControl) {
  if ((fractionofZoneControlledbySecondaryDaylightingControl + fractionofZoneControlledbyPrimaryDaylightingControl()) > 1.0) {
    return false;
  }
  return setDaylightingFraction(kSecondaryDaylightingReferencePointIndex, fractionofZoneControlledbySecondaryDaylightingControl);
}

void ThermalZone_Impl::resetFractionofZoneControlledbySecondaryDaylightingControl() {
  resetDaylightingFraction(kSecondaryDaylightingReferencePointIndex);
}

bool ThermalZone_Impl::setDaylightingFraction(unsigned referencePointIndex, double value) {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  auto daylightingControls = daylightingControlsForZone(zone);
  if (!daylightingControls) {
    return false;
  }

  while (daylightingControls->numExtensibleGroups() <= referencePointIndex) {
    daylightingControls->pushExtensibleGroup();
  }

  auto groups = daylightingControls->extensibleGroups();
  if (referencePointIndex >= groups.size()) {
    return false;
  }

  auto group = groups[referencePointIndex].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!group) {
    return false;
  }

  return group->setDouble(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, value);
}

void ThermalZone_Impl::resetDaylightingFraction(unsigned referencePointIndex) {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  auto daylightingControls = daylightingControlsForZone(zone);
  if (!daylightingControls) {
    return;
  }

  const auto groups = daylightingControls->extensibleGroups();
  if (referencePointIndex >= groups.size()) {
    return;
  }

  auto group = groups[referencePointIndex].optionalCast<openstudio::WorkspaceExtensibleGroup>();
  if (!group) {
    return;
  }

  const bool result =
    group->setString(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, "");
  OS_ASSERT(result);
}

double ThermalZone_Impl::daylightingReferencePointCoordinate(unsigned referencePointIndex, unsigned fieldIndex) const {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  auto referencePoint = daylightingReferencePointForZone(zone, referencePointIndex);
  OS_ASSERT(referencePoint);
  auto value = referencePoint->getDouble(fieldIndex, true);
  OS_ASSERT(value);
  return *value;
}

bool ThermalZone_Impl::setDaylightingReferencePointCoordinate(unsigned referencePointIndex, unsigned fieldIndex, double value) {
  const auto zone = getObject<openstudio::epmodel::ThermalZone>();
  auto referencePoint = daylightingReferencePointForZone(zone, referencePointIndex);
  if (!referencePoint) {
    return false;
  }
  return referencePoint->setDouble(fieldIndex, value);
}

double ThermalZone_Impl::primaryDaylightingControlXCoordinate() const {
  return daylightingReferencePointCoordinate(kPrimaryDaylightingReferencePointIndex,
                                             openstudio::Daylighting_ReferencePointFields::XCoordinateofReferencePoint);
}

double ThermalZone_Impl::primaryDaylightingControlYCoordinate() const {
  return daylightingReferencePointCoordinate(kPrimaryDaylightingReferencePointIndex,
                                             openstudio::Daylighting_ReferencePointFields::YCoordinateofReferencePoint);
}

double ThermalZone_Impl::primaryDaylightingControlZCoordinate() const {
  return daylightingReferencePointCoordinate(kPrimaryDaylightingReferencePointIndex,
                                             openstudio::Daylighting_ReferencePointFields::ZCoordinateofReferencePoint);
}

bool ThermalZone_Impl::setPrimaryDaylightingControlXCoordinate(double primaryDaylightingControlXCoordinate) {
  return setDaylightingReferencePointCoordinate(kPrimaryDaylightingReferencePointIndex,
                                                openstudio::Daylighting_ReferencePointFields::XCoordinateofReferencePoint,
                                                primaryDaylightingControlXCoordinate);
}

bool ThermalZone_Impl::setPrimaryDaylightingControlYCoordinate(double primaryDaylightingControlYCoordinate) {
  return setDaylightingReferencePointCoordinate(kPrimaryDaylightingReferencePointIndex,
                                                openstudio::Daylighting_ReferencePointFields::YCoordinateofReferencePoint,
                                                primaryDaylightingControlYCoordinate);
}

bool ThermalZone_Impl::setPrimaryDaylightingControlZCoordinate(double primaryDaylightingControlZCoordinate) {
  return setDaylightingReferencePointCoordinate(kPrimaryDaylightingReferencePointIndex,
                                                openstudio::Daylighting_ReferencePointFields::ZCoordinateofReferencePoint,
                                                primaryDaylightingControlZCoordinate);
}

double ThermalZone_Impl::secondaryDaylightingControlXCoordinate() const {
  return daylightingReferencePointCoordinate(kSecondaryDaylightingReferencePointIndex,
                                             openstudio::Daylighting_ReferencePointFields::XCoordinateofReferencePoint);
}

double ThermalZone_Impl::secondaryDaylightingControlYCoordinate() const {
  return daylightingReferencePointCoordinate(kSecondaryDaylightingReferencePointIndex,
                                             openstudio::Daylighting_ReferencePointFields::YCoordinateofReferencePoint);
}

double ThermalZone_Impl::secondaryDaylightingControlZCoordinate() const {
  return daylightingReferencePointCoordinate(kSecondaryDaylightingReferencePointIndex,
                                             openstudio::Daylighting_ReferencePointFields::ZCoordinateofReferencePoint);
}

bool ThermalZone_Impl::setSecondaryDaylightingControlXCoordinate(double secondaryDaylightingControlXCoordinate) {
  return setDaylightingReferencePointCoordinate(kSecondaryDaylightingReferencePointIndex,
                                                openstudio::Daylighting_ReferencePointFields::XCoordinateofReferencePoint,
                                                secondaryDaylightingControlXCoordinate);
}

bool ThermalZone_Impl::setSecondaryDaylightingControlYCoordinate(double secondaryDaylightingControlYCoordinate) {
  return setDaylightingReferencePointCoordinate(kSecondaryDaylightingReferencePointIndex,
                                                openstudio::Daylighting_ReferencePointFields::YCoordinateofReferencePoint,
                                                secondaryDaylightingControlYCoordinate);
}

bool ThermalZone_Impl::setSecondaryDaylightingControlZCoordinate(double secondaryDaylightingControlZCoordinate) {
  return setDaylightingReferencePointCoordinate(kSecondaryDaylightingReferencePointIndex,
                                                openstudio::Daylighting_ReferencePointFields::ZCoordinateofReferencePoint,
                                                secondaryDaylightingControlZCoordinate);
}

void ThermalZone_Impl::doCanonicalize(LoadContext& context) {
  auto sz = sizingZone();
  sz.getImpl<openstudio::epmodel::detail::SizingZone_Impl>()->canonicalize(context);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
