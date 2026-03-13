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
#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"
#include "ZoneHVACEquipmentConnections.hpp"
#include "ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/AirLoopHVAC_ZoneMixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/Daylighting_Controls_FieldEnums.hxx>
#include <utilities/idd/Daylighting_ReferencePoint_FieldEnums.hxx>
#include <utilities/idd/HVACTemplate_Zone_IdealLoadsAirSystem_FieldEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_IlluminanceMap_FieldEnums.hxx>
#include <utilities/idd/Zone_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneControl_Thermostat_FieldEnums.hxx>
#include <utilities/idd/ZoneList_FieldEnums.hxx>
#include <utilities/idd/OS_ZoneVentilation_DesignFlowRate_FieldEnums.hxx>
#include <utilities/idd/ZoneVentilation_DesignFlowRate_FieldEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  namespace {

    constexpr unsigned kPrimaryDaylightingReferencePointIndex = 0u;
    constexpr unsigned kSecondaryDaylightingReferencePointIndex = 1u;
    const std::vector<std::string>& zoneControlThermostatControlTypeKeys() {
      static const std::vector<std::string> keys{"ThermostatSetpoint:SingleHeating", "ThermostatSetpoint:SingleCooling",
                                                 "ThermostatSetpoint:SingleHeatingOrCooling", "ThermostatSetpoint:DualSetpoint"};
      return keys;
    }

    bool zoneControlThermostatTargetsZone(const ThermalZone& zone, const openstudio::WorkspaceObject& zoneControl) {
      const auto zoneName = zone.nameString();
      if (zoneName.empty()) {
        return false;
      }

      if (auto zoneOrListName = zoneControl.getString(openstudio::ZoneControl_ThermostatFields::ZoneorZoneListName, true)) {
        if (openstudio::istringEqual(*zoneOrListName, zoneName)) {
          return true;
        }

        if (auto zoneListObject = zone.model().getObjectByTypeAndName(openstudio::IddObjectType::ZoneList, *zoneOrListName, true)) {
          auto zoneListGroups = zoneListObject->extensibleGroups();
          for (const auto& group : zoneListGroups) {
            if (auto zoneListEntry = group.getString(openstudio::ZoneListExtensibleFields::ZoneName, true)) {
              if (openstudio::istringEqual(*zoneListEntry, zoneName)) {
                return true;
              }
            }
          }
        }
      }

      return false;
    }

    bool zoneVentilationTargetsZone(const ThermalZone& zone, const openstudio::WorkspaceObject& zoneVentilation) {
      const auto zoneName = zone.nameString();
      if (zoneName.empty()) {
        return false;
      }

      auto zoneOrSpaceName = zoneVentilation.getString(openstudio::ZoneVentilation_DesignFlowRateFields::ZoneorZoneListorSpaceorSpaceListName, true);
      if (!zoneOrSpaceName || zoneOrSpaceName->empty()) {
        return false;
      }

      if (openstudio::istringEqual(*zoneOrSpaceName, zoneName)) {
        return true;
      }

      if (auto zoneListObject = zone.model().getObjectByTypeAndName(openstudio::IddObjectType::ZoneList, *zoneOrSpaceName, true)) {
        auto zoneListGroups = zoneListObject->extensibleGroups();
        for (const auto& group : zoneListGroups) {
          if (auto zoneListEntry = group.getString(openstudio::ZoneListExtensibleFields::ZoneName, true)) {
            if (openstudio::istringEqual(*zoneListEntry, zoneName)) {
              return true;
            }
          }
        }
      }

      if (auto spaceObject = zone.model().getObjectByTypeAndName(openstudio::IddObjectType::Space, *zoneOrSpaceName, true)) {
        if (auto space = spaceObject->optionalCast<openstudio::epmodel::Space>()) {
          if (auto associatedZone = space->thermalZone()) {
            if (*associatedZone == zone) {
              return true;
            }
          }
        }
      }

      return false;
    }

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

    boost::optional<openstudio::WorkspaceObject> outputIlluminanceMapForZone(const ThermalZone& zone) {
      for (const auto& object : zone.model().getObjectsByType(openstudio::IddObjectType::Output_IlluminanceMap)) {
        auto zoneOrSpaceName = object.getString(openstudio::Output_IlluminanceMapFields::ZoneorSpaceName, true);
        if (zoneOrSpaceName && openstudio::istringEqual(*zoneOrSpaceName, zone.nameString())) {
          return object;
        }
      }
      return boost::none;
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

  // Schema Alignment Notes:
  // - API: `addToNode` keeps the EnergyPlus `ZoneHVAC:EquipmentConnections` object aligned with the current demand branch node by
  //   driving the backing `ZoneHVACEquipmentConnections` (inlet/return nodes).
  // - ForwardTranslator Evidence: `ForwardTranslateThermalZone::translateThermalZone` writes the same `ZoneHVAC:EquipmentConnections`
  //   fields (Zone Air Inlet/Exhaust/Node/Return and the Equipment List) so this helper ensures epmodel has the node references the
  //   translator expects to read.
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

  int ThermalZone::multiplier() const {
    return getImpl<detail::ThermalZone_Impl>()->multiplier();
  }

  bool ThermalZone::isMultiplierDefaulted() const {
    return getImpl<detail::ThermalZone_Impl>()->isMultiplierDefaulted();
  }

  bool ThermalZone::setMultiplier(int multiplier) {
    return getImpl<detail::ThermalZone_Impl>()->setMultiplier(multiplier);
  }

  void ThermalZone::resetMultiplier() {
    getImpl<detail::ThermalZone_Impl>()->resetMultiplier();
  }

  boost::optional<double> ThermalZone::ceilingHeight() const {
    return getImpl<detail::ThermalZone_Impl>()->ceilingHeight();
  }

  bool ThermalZone::isCeilingHeightDefaulted() const {
    return getImpl<detail::ThermalZone_Impl>()->isCeilingHeightDefaulted();
  }

  bool ThermalZone::isCeilingHeightAutocalculated() const {
    return getImpl<detail::ThermalZone_Impl>()->isCeilingHeightAutocalculated();
  }

  bool ThermalZone::setCeilingHeight(boost::optional<double> ceilingHeight) {
    return getImpl<detail::ThermalZone_Impl>()->setCeilingHeight(ceilingHeight);
  }

  bool ThermalZone::setCeilingHeight(double ceilingHeight) {
    return getImpl<detail::ThermalZone_Impl>()->setCeilingHeight(ceilingHeight);
  }

  void ThermalZone::resetCeilingHeight() {
    getImpl<detail::ThermalZone_Impl>()->resetCeilingHeight();
  }

  void ThermalZone::autocalculateCeilingHeight() {
    getImpl<detail::ThermalZone_Impl>()->autocalculateCeilingHeight();
  }

  boost::optional<double> ThermalZone::volume() const {
    return getImpl<detail::ThermalZone_Impl>()->volume();
  }

  bool ThermalZone::isVolumeDefaulted() const {
    return getImpl<detail::ThermalZone_Impl>()->isVolumeDefaulted();
  }

  bool ThermalZone::isVolumeAutocalculated() const {
    return getImpl<detail::ThermalZone_Impl>()->isVolumeAutocalculated();
  }

  bool ThermalZone::setVolume(boost::optional<double> volume) {
    return getImpl<detail::ThermalZone_Impl>()->setVolume(volume);
  }

  bool ThermalZone::setVolume(double volume) {
    return getImpl<detail::ThermalZone_Impl>()->setVolume(volume);
  }

  void ThermalZone::resetVolume() {
    getImpl<detail::ThermalZone_Impl>()->resetVolume();
  }

  void ThermalZone::autocalculateVolume() {
    getImpl<detail::ThermalZone_Impl>()->autocalculateVolume();
  }

  boost::optional<std::string> ThermalZone::zoneInsideConvectionAlgorithm() const {
    return getImpl<detail::ThermalZone_Impl>()->zoneInsideConvectionAlgorithm();
  }

  boost::optional<std::string> ThermalZone::zoneOutsideConvectionAlgorithm() const {
    return getImpl<detail::ThermalZone_Impl>()->zoneOutsideConvectionAlgorithm();
  }

  bool ThermalZone::setZoneInsideConvectionAlgorithm(boost::optional<std::string> zoneInsideConvectionAlgorithm) {
    return getImpl<detail::ThermalZone_Impl>()->setZoneInsideConvectionAlgorithm(zoneInsideConvectionAlgorithm);
  }

  bool ThermalZone::setZoneInsideConvectionAlgorithm(const std::string& zoneInsideConvectionAlgorithm) {
    return getImpl<detail::ThermalZone_Impl>()->setZoneInsideConvectionAlgorithm(zoneInsideConvectionAlgorithm);
  }

  void ThermalZone::resetZoneInsideConvectionAlgorithm() {
    getImpl<detail::ThermalZone_Impl>()->resetZoneInsideConvectionAlgorithm();
  }

  bool ThermalZone::setZoneOutsideConvectionAlgorithm(boost::optional<std::string> zoneOutsideConvectionAlgorithm) {
    return getImpl<detail::ThermalZone_Impl>()->setZoneOutsideConvectionAlgorithm(zoneOutsideConvectionAlgorithm);
  }

  bool ThermalZone::setZoneOutsideConvectionAlgorithm(const std::string& zoneOutsideConvectionAlgorithm) {
    return getImpl<detail::ThermalZone_Impl>()->setZoneOutsideConvectionAlgorithm(zoneOutsideConvectionAlgorithm);
  }

  void ThermalZone::resetZoneOutsideConvectionAlgorithm() {
    getImpl<detail::ThermalZone_Impl>()->resetZoneOutsideConvectionAlgorithm();
  }

  bool ThermalZone::useIdealAirLoads() const {
    return getImpl<detail::ThermalZone_Impl>()->useIdealAirLoads();
  }

  bool ThermalZone::setUseIdealAirLoads(bool useIdealAirLoads) {
    return getImpl<detail::ThermalZone_Impl>()->setUseIdealAirLoads(useIdealAirLoads);
  }

  std::vector<std::string> ThermalZone::control1ObjectTypeValues() {
    return detail::ThermalZone_Impl::control1ObjectTypeValues();
  }

  std::string ThermalZone::control1ObjectType() const {
    return getImpl<detail::ThermalZone_Impl>()->control1ObjectType();
  }

  bool ThermalZone::setControl1ObjectType(const std::string& control1ObjectType) {
    return getImpl<detail::ThermalZone_Impl>()->setControl1ObjectType(control1ObjectType);
  }

  std::vector<std::string> ThermalZone::control2ObjectTypeValues() {
    return detail::ThermalZone_Impl::control2ObjectTypeValues();
  }

  boost::optional<std::string> ThermalZone::control2ObjectType() const {
    return getImpl<detail::ThermalZone_Impl>()->control2ObjectType();
  }

  bool ThermalZone::setControl2ObjectType(const std::string& control2ObjectType) {
    return getImpl<detail::ThermalZone_Impl>()->setControl2ObjectType(control2ObjectType);
  }

  void ThermalZone::resetControl2ObjectType() {
    getImpl<detail::ThermalZone_Impl>()->resetControl2ObjectType();
  }

  std::vector<std::string> ThermalZone::control3ObjectTypeValues() {
    return detail::ThermalZone_Impl::control3ObjectTypeValues();
  }

  boost::optional<std::string> ThermalZone::control3ObjectType() const {
    return getImpl<detail::ThermalZone_Impl>()->control3ObjectType();
  }

  bool ThermalZone::setControl3ObjectType(const std::string& control3ObjectType) {
    return getImpl<detail::ThermalZone_Impl>()->setControl3ObjectType(control3ObjectType);
  }

  void ThermalZone::resetControl3ObjectType() {
    getImpl<detail::ThermalZone_Impl>()->resetControl3ObjectType();
  }

  std::vector<std::string> ThermalZone::control4ObjectTypeValues() {
    return detail::ThermalZone_Impl::control4ObjectTypeValues();
  }

  boost::optional<std::string> ThermalZone::control4ObjectType() const {
    return getImpl<detail::ThermalZone_Impl>()->control4ObjectType();
  }

  bool ThermalZone::setControl4ObjectType(const std::string& control4ObjectType) {
    return getImpl<detail::ThermalZone_Impl>()->setControl4ObjectType(control4ObjectType);
  }

  void ThermalZone::resetControl4ObjectType() {
    getImpl<detail::ThermalZone_Impl>()->resetControl4ObjectType();
  }

  double ThermalZone::temperatureDifferenceBetweenCutoutAndSetpoint() const {
    return getImpl<detail::ThermalZone_Impl>()->temperatureDifferenceBetweenCutoutAndSetpoint();
  }

  bool ThermalZone::isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const {
    return getImpl<detail::ThermalZone_Impl>()->isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted();
  }

  bool ThermalZone::setTemperatureDifferenceBetweenCutoutAndSetpoint(double temperatureDifferenceBetweenCutoutAndSetpoint) {
    return getImpl<detail::ThermalZone_Impl>()->setTemperatureDifferenceBetweenCutoutAndSetpoint(temperatureDifferenceBetweenCutoutAndSetpoint);
  }

  void ThermalZone::resetTemperatureDifferenceBetweenCutoutAndSetpoint() {
    getImpl<detail::ThermalZone_Impl>()->resetTemperatureDifferenceBetweenCutoutAndSetpoint();
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

  double ThermalZone::designFlowRate() const {
    return getImpl<detail::ThermalZone_Impl>()->designFlowRate();
  }

  bool ThermalZone::setDesignFlowRate(double designFlowRate) {
    return getImpl<detail::ThermalZone_Impl>()->setDesignFlowRate(designFlowRate);
  }

  double ThermalZone::flowRateperZoneFloorArea() const {
    return getImpl<detail::ThermalZone_Impl>()->flowRateperZoneFloorArea();
  }

  bool ThermalZone::setFlowRateperZoneFloorArea(double flowRateperZoneFloorArea) {
    return getImpl<detail::ThermalZone_Impl>()->setFlowRateperZoneFloorArea(flowRateperZoneFloorArea);
  }

  double ThermalZone::flowRateperPerson() const {
    return getImpl<detail::ThermalZone_Impl>()->flowRateperPerson();
  }

  bool ThermalZone::setFlowRateperPerson(double flowRateperPerson) {
    return getImpl<detail::ThermalZone_Impl>()->setFlowRateperPerson(flowRateperPerson);
  }

  double ThermalZone::airChangesperHour() const {
    return getImpl<detail::ThermalZone_Impl>()->airChangesperHour();
  }

  bool ThermalZone::setAirChangesperHour(double airChangesperHour) {
    return getImpl<detail::ThermalZone_Impl>()->setAirChangesperHour(airChangesperHour);
  }

  std::vector<std::string> ThermalZone::ventilationTypeValues() {
    auto iddObject = openstudio::IddFactory::instance().getObject(IddObjectType::OS_ZoneVentilation_DesignFlowRate);
    OS_ASSERT(iddObject);
    return getIddKeyNames(*iddObject, OS_ZoneVentilation_DesignFlowRateFields::VentilationType);
  }

  std::string ThermalZone::ventilationType() const {
    return getImpl<detail::ThermalZone_Impl>()->ventilationType();
  }

  bool ThermalZone::setVentilationType(const std::string& ventilationType) {
    return getImpl<detail::ThermalZone_Impl>()->setVentilationType(ventilationType);
  }

  double ThermalZone::fanPressureRise() const {
    return getImpl<detail::ThermalZone_Impl>()->fanPressureRise();
  }

  bool ThermalZone::setFanPressureRise(double fanPressureRise) {
    return getImpl<detail::ThermalZone_Impl>()->setFanPressureRise(fanPressureRise);
  }

  double ThermalZone::fanTotalEfficiency() const {
    return getImpl<detail::ThermalZone_Impl>()->fanTotalEfficiency();
  }

  bool ThermalZone::setFanTotalEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::ThermalZone_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  double ThermalZone::constantTermCoefficient() const {
    return getImpl<detail::ThermalZone_Impl>()->constantTermCoefficient();
  }

  bool ThermalZone::setConstantTermCoefficient(double constantTermCoefficient) {
    return getImpl<detail::ThermalZone_Impl>()->setConstantTermCoefficient(constantTermCoefficient);
  }

  double ThermalZone::temperatureTermCoefficient() const {
    return getImpl<detail::ThermalZone_Impl>()->temperatureTermCoefficient();
  }

  bool ThermalZone::setTemperatureTermCoefficient(double temperatureTermCoefficient) {
    return getImpl<detail::ThermalZone_Impl>()->setTemperatureTermCoefficient(temperatureTermCoefficient);
  }

  double ThermalZone::velocityTermCoefficient() const {
    return getImpl<detail::ThermalZone_Impl>()->velocityTermCoefficient();
  }

  bool ThermalZone::setVelocityTermCoefficient(double velocityTermCoefficient) {
    return getImpl<detail::ThermalZone_Impl>()->setVelocityTermCoefficient(velocityTermCoefficient);
  }

  double ThermalZone::velocitySquaredTermCoefficient() const {
    return getImpl<detail::ThermalZone_Impl>()->velocitySquaredTermCoefficient();
  }

  bool ThermalZone::setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient) {
    return getImpl<detail::ThermalZone_Impl>()->setVelocitySquaredTermCoefficient(velocitySquaredTermCoefficient);
  }

  double ThermalZone::minimumIndoorTemperature() const {
    return getImpl<detail::ThermalZone_Impl>()->minimumIndoorTemperature();
  }

  bool ThermalZone::setMinimumIndoorTemperature(double minimumIndoorTemperature) {
    return getImpl<detail::ThermalZone_Impl>()->setMinimumIndoorTemperature(minimumIndoorTemperature);
  }

  double ThermalZone::maximumIndoorTemperature() const {
    return getImpl<detail::ThermalZone_Impl>()->maximumIndoorTemperature();
  }

  bool ThermalZone::setMaximumIndoorTemperature(double maximumIndoorTemperature) {
    return getImpl<detail::ThermalZone_Impl>()->setMaximumIndoorTemperature(maximumIndoorTemperature);
  }

  double ThermalZone::deltaTemperature() const {
    return getImpl<detail::ThermalZone_Impl>()->deltaTemperature();
  }

  bool ThermalZone::setDeltaTemperature(double deltaTemperature) {
    return getImpl<detail::ThermalZone_Impl>()->setDeltaTemperature(deltaTemperature);
  }

  double ThermalZone::minimumOutdoorTemperature() const {
    return getImpl<detail::ThermalZone_Impl>()->minimumOutdoorTemperature();
  }

  bool ThermalZone::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
    return getImpl<detail::ThermalZone_Impl>()->setMinimumOutdoorTemperature(minimumOutdoorTemperature);
  }

  double ThermalZone::maximumOutdoorTemperature() const {
    return getImpl<detail::ThermalZone_Impl>()->maximumOutdoorTemperature();
  }

  bool ThermalZone::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
    return getImpl<detail::ThermalZone_Impl>()->setMaximumOutdoorTemperature(maximumOutdoorTemperature);
  }

  double ThermalZone::maximumWindSpeed() const {
    return getImpl<detail::ThermalZone_Impl>()->maximumWindSpeed();
  }

  bool ThermalZone::setMaximumWindSpeed(double maximumWindSpeed) {
    return getImpl<detail::ThermalZone_Impl>()->setMaximumWindSpeed(maximumWindSpeed);
  }

  std::vector<std::string> ThermalZone::densityBasisValues() {
    auto iddObject = openstudio::IddFactory::instance().getObject(IddObjectType::OS_ZoneVentilation_DesignFlowRate);
    OS_ASSERT(iddObject);
    return getIddKeyNames(*iddObject, OS_ZoneVentilation_DesignFlowRateFields::DensityBasis);
  }

  std::string ThermalZone::densityBasis() const {
    return getImpl<detail::ThermalZone_Impl>()->densityBasis();
  }

  bool ThermalZone::setDensityBasis(const std::string& densityBasis) {
    return getImpl<detail::ThermalZone_Impl>()->setDensityBasis(densityBasis);
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

  double ThermalZone::illuminanceMapOriginXCoordinate() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapOriginXCoordinate();
  }

  bool ThermalZone::setIlluminanceMapOriginXCoordinate(double illuminanceMapOriginXCoordinate) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapOriginXCoordinate(illuminanceMapOriginXCoordinate);
  }

  double ThermalZone::illuminanceMapOriginYCoordinate() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapOriginYCoordinate();
  }

  bool ThermalZone::setIlluminanceMapOriginYCoordinate(double illuminanceMapOriginYCoordinate) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapOriginYCoordinate(illuminanceMapOriginYCoordinate);
  }

  double ThermalZone::illuminanceMapOriginZCoordinate() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapOriginZCoordinate();
  }

  bool ThermalZone::setIlluminanceMapOriginZCoordinate(double illuminanceMapOriginZCoordinate) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapOriginZCoordinate(illuminanceMapOriginZCoordinate);
  }

  double ThermalZone::illuminanceMapXLength() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapXLength();
  }

  bool ThermalZone::setIlluminanceMapXLength(double illuminanceMapXLength) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapXLength(illuminanceMapXLength);
  }

  int ThermalZone::illuminanceMapNumberofXGridPoints() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapNumberofXGridPoints();
  }

  bool ThermalZone::setIlluminanceMapNumberofXGridPoints(int illuminanceMapNumberofXGridPoints) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapNumberofXGridPoints(illuminanceMapNumberofXGridPoints);
  }

  double ThermalZone::illuminanceMapYLength() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapYLength();
  }

  bool ThermalZone::setIlluminanceMapYLength(double illuminanceMapYLength) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapYLength(illuminanceMapYLength);
  }

  int ThermalZone::illuminanceMapNumberofYGridPoints() const {
    return getImpl<detail::ThermalZone_Impl>()->illuminanceMapNumberofYGridPoints();
  }

  bool ThermalZone::setIlluminanceMapNumberofYGridPoints(int illuminanceMapNumberofYGridPoints) {
    return getImpl<detail::ThermalZone_Impl>()->setIlluminanceMapNumberofYGridPoints(illuminanceMapNumberofYGridPoints);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Schema Alignment Notes:
    // - Field Mapping: Returns the `ZoneHVACEquipmentConnections` object that represents the EnergyPlus `ZoneHVAC:EquipmentConnections`
    //   object tied to this zone.
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

      const auto equipmentListName = conn->getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName);
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

    int ThermalZone_Impl::multiplier() const {
      auto value = getInt(openstudio::ZoneFields::Multiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ThermalZone_Impl::isMultiplierDefaulted() const {
      return isEmpty(openstudio::ZoneFields::Multiplier);
    }

    bool ThermalZone_Impl::setMultiplier(int multiplier) {
      return setInt(openstudio::ZoneFields::Multiplier, multiplier);
    }

    void ThermalZone_Impl::resetMultiplier() {
      bool result = setString(openstudio::ZoneFields::Multiplier, "");
      OS_ASSERT(result);
    }

    boost::optional<double> ThermalZone_Impl::ceilingHeight() const {
      return getDouble(openstudio::ZoneFields::CeilingHeight, true);
    }

    bool ThermalZone_Impl::isCeilingHeightDefaulted() const {
      return isEmpty(openstudio::ZoneFields::CeilingHeight);
    }

    bool ThermalZone_Impl::isCeilingHeightAutocalculated() const {
      bool result = false;
      if (auto value = getString(openstudio::ZoneFields::CeilingHeight, true)) {
        result = openstudio::istringEqual(*value, "autocalculate");
      }
      return result;
    }

    bool ThermalZone_Impl::setCeilingHeight(boost::optional<double> ceilingHeight) {
      bool result = false;
      if (ceilingHeight) {
        result = setDouble(openstudio::ZoneFields::CeilingHeight, ceilingHeight.get());
      } else {
        result = setString(openstudio::ZoneFields::CeilingHeight, "");
      }
      OS_ASSERT(result);
      return result;
    }

    bool ThermalZone_Impl::setCeilingHeight(double ceilingHeight) {
      bool result = setDouble(openstudio::ZoneFields::CeilingHeight, ceilingHeight);
      OS_ASSERT(result);
      return result;
    }

    void ThermalZone_Impl::resetCeilingHeight() {
      bool result = setString(openstudio::ZoneFields::CeilingHeight, "");
      OS_ASSERT(result);
    }

    void ThermalZone_Impl::autocalculateCeilingHeight() {
      bool result = setString(openstudio::ZoneFields::CeilingHeight, "autocalculate");
      OS_ASSERT(result);
    }

    boost::optional<double> ThermalZone_Impl::volume() const {
      return getDouble(openstudio::ZoneFields::Volume, true);
    }

    bool ThermalZone_Impl::isVolumeDefaulted() const {
      return isEmpty(openstudio::ZoneFields::Volume);
    }

    bool ThermalZone_Impl::isVolumeAutocalculated() const {
      bool result = false;
      if (auto value = getString(openstudio::ZoneFields::Volume, true)) {
        result = openstudio::istringEqual(*value, "autocalculate");
      }
      return result;
    }

    bool ThermalZone_Impl::setVolume(boost::optional<double> volume) {
      bool result = false;
      if (volume) {
        result = setDouble(openstudio::ZoneFields::Volume, volume.get());
      } else {
        result = setString(openstudio::ZoneFields::Volume, "");
      }
      OS_ASSERT(result);
      return result;
    }

    bool ThermalZone_Impl::setVolume(double volume) {
      bool result = setDouble(openstudio::ZoneFields::Volume, volume);
      OS_ASSERT(result);
      return result;
    }

    void ThermalZone_Impl::resetVolume() {
      bool result = setString(openstudio::ZoneFields::Volume, "");
      OS_ASSERT(result);
    }

    void ThermalZone_Impl::autocalculateVolume() {
      bool result = setString(openstudio::ZoneFields::Volume, "autocalculate");
      OS_ASSERT(result);
    }

    boost::optional<std::string> ThermalZone_Impl::zoneInsideConvectionAlgorithm() const {
      return getString(openstudio::ZoneFields::ZoneInsideConvectionAlgorithm, true);
    }

    boost::optional<std::string> ThermalZone_Impl::zoneOutsideConvectionAlgorithm() const {
      return getString(openstudio::ZoneFields::ZoneOutsideConvectionAlgorithm, true);
    }

    bool ThermalZone_Impl::setZoneInsideConvectionAlgorithm(boost::optional<std::string> zoneInsideConvectionAlgorithm) {
      bool result = false;
      if (zoneInsideConvectionAlgorithm) {
        result = setString(openstudio::ZoneFields::ZoneInsideConvectionAlgorithm, zoneInsideConvectionAlgorithm.get());
      } else {
        result = setString(openstudio::ZoneFields::ZoneInsideConvectionAlgorithm, "");
      }
      return result;
    }

    bool ThermalZone_Impl::setZoneInsideConvectionAlgorithm(const std::string& zoneInsideConvectionAlgorithm) {
      return setString(openstudio::ZoneFields::ZoneInsideConvectionAlgorithm, zoneInsideConvectionAlgorithm);
    }

    void ThermalZone_Impl::resetZoneInsideConvectionAlgorithm() {
      bool result = setString(openstudio::ZoneFields::ZoneInsideConvectionAlgorithm, "");
      OS_ASSERT(result);
    }

    bool ThermalZone_Impl::setZoneOutsideConvectionAlgorithm(boost::optional<std::string> zoneOutsideConvectionAlgorithm) {
      bool result = false;
      if (zoneOutsideConvectionAlgorithm) {
        result = setString(openstudio::ZoneFields::ZoneOutsideConvectionAlgorithm, zoneOutsideConvectionAlgorithm.get());
      } else {
        result = setString(openstudio::ZoneFields::ZoneOutsideConvectionAlgorithm, "");
      }
      return result;
    }

    bool ThermalZone_Impl::setZoneOutsideConvectionAlgorithm(const std::string& zoneOutsideConvectionAlgorithm) {
      return setString(openstudio::ZoneFields::ZoneOutsideConvectionAlgorithm, zoneOutsideConvectionAlgorithm);
    }

    void ThermalZone_Impl::resetZoneOutsideConvectionAlgorithm() {
      bool result = setString(openstudio::ZoneFields::ZoneOutsideConvectionAlgorithm, "");
      OS_ASSERT(result);
    }

    std::vector<openstudio::WorkspaceObject> ThermalZone_Impl::hvacTemplateZoneIdealLoadsAirSystemsForZone() const {
      std::vector<openstudio::WorkspaceObject> result;
      const auto zoneName = getObject<openstudio::epmodel::ThermalZone>().nameString();
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::HVACTemplate_Zone_IdealLoadsAirSystem)) {
        auto mappedZoneName = object.getString(openstudio::HVACTemplate_Zone_IdealLoadsAirSystemFields::ZoneName, true);
        if (mappedZoneName && openstudio::istringEqual(*mappedZoneName, zoneName)) {
          result.emplace_back(object);
        }
      }
      return result;
    }

    bool ThermalZone_Impl::useIdealAirLoads() const {
      return !hvacTemplateZoneIdealLoadsAirSystemsForZone().empty();
    }

    bool ThermalZone_Impl::setUseIdealAirLoads(bool useIdealAirLoads) {
      auto idealLoadsObjects = hvacTemplateZoneIdealLoadsAirSystemsForZone();

      if (useIdealAirLoads) {
        if (!idealLoadsObjects.empty()) {
          return true;
        }
        openstudio::IdfObject object(openstudio::IddObjectType::HVACTemplate_Zone_IdealLoadsAirSystem);
        if (!object.setString(openstudio::HVACTemplate_Zone_IdealLoadsAirSystemFields::ZoneName,
                              getObject<openstudio::epmodel::ThermalZone>().nameString())) {
          return false;
        }
        return model().addObject(object).is_initialized();
      }

      bool result = true;
      for (auto& object : idealLoadsObjects) {
        result = !object.remove().empty() && result;
      }
      return result;
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

    std::vector<std::string> ThermalZone_Impl::control1ObjectTypeValues() {
      return zoneControlThermostatControlTypeKeys();
    }

    std::vector<std::string> ThermalZone_Impl::control2ObjectTypeValues() {
      return zoneControlThermostatControlTypeKeys();
    }

    std::vector<std::string> ThermalZone_Impl::control3ObjectTypeValues() {
      return zoneControlThermostatControlTypeKeys();
    }

    std::vector<std::string> ThermalZone_Impl::control4ObjectTypeValues() {
      return zoneControlThermostatControlTypeKeys();
    }

    std::string ThermalZone_Impl::control1ObjectType() const {
      if (auto object = zoneControlThermostatObject()) {
        if (auto value = object->getString(ZoneControl_ThermostatFields::Control1ObjectType, true)) {
          return *value;
        }
      }
      return std::string();
    }

    boost::optional<std::string> ThermalZone_Impl::control2ObjectType() const {
      if (auto object = zoneControlThermostatObject()) {
        if (auto value = object->getString(ZoneControl_ThermostatFields::Control2ObjectType, false, true)) {
          if (!value->empty()) {
            return value;
          }
        }
      }
      return boost::none;
    }

    boost::optional<std::string> ThermalZone_Impl::control3ObjectType() const {
      if (auto object = zoneControlThermostatObject()) {
        if (auto value = object->getString(ZoneControl_ThermostatFields::Control3ObjectType, false, true)) {
          if (!value->empty()) {
            return value;
          }
        }
      }
      return boost::none;
    }

    boost::optional<std::string> ThermalZone_Impl::control4ObjectType() const {
      if (auto object = zoneControlThermostatObject()) {
        if (auto value = object->getString(ZoneControl_ThermostatFields::Control4ObjectType, false, true)) {
          if (!value->empty()) {
            return value;
          }
        }
      }
      return boost::none;
    }

    bool ThermalZone_Impl::setControl1ObjectType(const std::string& control1ObjectType) {
      auto object = getOrCreateZoneControlThermostatObject();
      return object.setString(ZoneControl_ThermostatFields::Control1ObjectType, control1ObjectType);
    }

    bool ThermalZone_Impl::setControl2ObjectType(const std::string& control2ObjectType) {
      auto object = getOrCreateZoneControlThermostatObject();
      return object.setString(ZoneControl_ThermostatFields::Control2ObjectType, control2ObjectType);
    }

    bool ThermalZone_Impl::setControl3ObjectType(const std::string& control3ObjectType) {
      auto object = getOrCreateZoneControlThermostatObject();
      return object.setString(ZoneControl_ThermostatFields::Control3ObjectType, control3ObjectType);
    }

    bool ThermalZone_Impl::setControl4ObjectType(const std::string& control4ObjectType) {
      auto object = getOrCreateZoneControlThermostatObject();
      return object.setString(ZoneControl_ThermostatFields::Control4ObjectType, control4ObjectType);
    }

    void ThermalZone_Impl::resetControl2ObjectType() {
      if (auto object = zoneControlThermostatObject()) {
        const bool result = object->setString(ZoneControl_ThermostatFields::Control2ObjectType, "");
        OS_ASSERT(result);
      }
    }

    void ThermalZone_Impl::resetControl3ObjectType() {
      if (auto object = zoneControlThermostatObject()) {
        const bool result = object->setString(ZoneControl_ThermostatFields::Control3ObjectType, "");
        OS_ASSERT(result);
      }
    }

    void ThermalZone_Impl::resetControl4ObjectType() {
      if (auto object = zoneControlThermostatObject()) {
        const bool result = object->setString(ZoneControl_ThermostatFields::Control4ObjectType, "");
        OS_ASSERT(result);
      }
    }

    double ThermalZone_Impl::temperatureDifferenceBetweenCutoutAndSetpoint() const {
      if (auto object = zoneControlThermostatObject()) {
        if (auto raw = object->getString(ZoneControl_ThermostatFields::TemperatureDifferenceBetweenCutoutAndSetpoint, false, true)) {
          if (!raw->empty()) {
            if (auto value = object->getDouble(ZoneControl_ThermostatFields::TemperatureDifferenceBetweenCutoutAndSetpoint, true)) {
              return *value;
            }
          }
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const {
      if (auto object = zoneControlThermostatObject()) {
        if (auto raw = object->getString(ZoneControl_ThermostatFields::TemperatureDifferenceBetweenCutoutAndSetpoint, false, true)) {
          return raw->empty();
        }
        return true;
      }
      return true;
    }

    bool ThermalZone_Impl::setTemperatureDifferenceBetweenCutoutAndSetpoint(double temperatureDifferenceBetweenCutoutAndSetpoint) {
      auto object = getOrCreateZoneControlThermostatObject();
      return object.setDouble(ZoneControl_ThermostatFields::TemperatureDifferenceBetweenCutoutAndSetpoint,
                              temperatureDifferenceBetweenCutoutAndSetpoint);
    }

    void ThermalZone_Impl::resetTemperatureDifferenceBetweenCutoutAndSetpoint() {
      if (auto object = zoneControlThermostatObject()) {
        const bool result = object->setString(ZoneControl_ThermostatFields::TemperatureDifferenceBetweenCutoutAndSetpoint, "");
        OS_ASSERT(result);
      }
    }

    boost::optional<openstudio::WorkspaceObject> ThermalZone_Impl::zoneControlThermostatObject() const {
      openstudio::epmodel::ThermalZone zone = getObject<openstudio::epmodel::ThermalZone>();
      const auto zoneObjects = model().getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat, true);
      for (const auto& object : zoneObjects) {
        if (zoneControlThermostatTargetsZone(zone, object)) {
          return object;
        }
      }
      return boost::none;
    }

    openstudio::WorkspaceObject ThermalZone_Impl::getOrCreateZoneControlThermostatObject() {
      if (auto existing = zoneControlThermostatObject()) {
        return *existing;
      }

      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      openstudio::IdfObject object(openstudio::IddObjectType::ZoneControl_Thermostat);
      object.setString(ZoneControl_ThermostatFields::Name, zone.nameString() + " Thermostat");
      object.setString(ZoneControl_ThermostatFields::ZoneorZoneListName, zone.nameString());
      auto added = model().addObject(object);
      OS_ASSERT(added);
      return *added;
    }

    boost::optional<openstudio::WorkspaceObject> ThermalZone_Impl::zoneVentilationObject() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      const auto objects = model().getObjectsByType(openstudio::IddObjectType::ZoneVentilation_DesignFlowRate, true);
      for (const auto& object : objects) {
        if (zoneVentilationTargetsZone(zone, object)) {
          return object;
        }
      }
      return boost::none;
    }

    openstudio::WorkspaceObject ThermalZone_Impl::getOrCreateZoneVentilationObject() {
      if (auto existing = zoneVentilationObject()) {
        return *existing;
      }

      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      openstudio::IdfObject object(openstudio::IddObjectType::ZoneVentilation_DesignFlowRate);
      object.setString(ZoneVentilation_DesignFlowRateFields::Name, zone.nameString() + " Ventilation");
      object.setString(ZoneVentilation_DesignFlowRateFields::ZoneorZoneListorSpaceorSpaceListName, zone.nameString());
      auto added = model().addObject(object);
      OS_ASSERT(added);
      auto workspaceObject = *added;
      applyZoneVentilationDefaults(workspaceObject);
      return workspaceObject;
    }

    void ThermalZone_Impl::applyZoneVentilationDefaults(openstudio::WorkspaceObject& zoneVentilation) {
      bool result = zoneVentilation.setString(ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "AirChanges/Hour");
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::AirChangesperHour, 5.0);
      OS_ASSERT(result);
      result = zoneVentilation.setString(ZoneVentilation_DesignFlowRateFields::VentilationType, "Natural");
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::FanPressureRise, 0.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::FanTotalEfficiency, 1.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::ConstantTermCoefficient, 0.606);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::TemperatureTermCoefficient, 0.03636);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::VelocityTermCoefficient, 0.1177);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::VelocitySquaredTermCoefficient, 0.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperature, 18.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperature, 100.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::DeltaTemperature, 1.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperature, -100.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperature, 100.0);
      OS_ASSERT(result);
      result = zoneVentilation.setDouble(ZoneVentilation_DesignFlowRateFields::MaximumWindSpeed, 40.0);
      OS_ASSERT(result);
      result = zoneVentilation.setString(ZoneVentilation_DesignFlowRateFields::DensityBasis, "Outdoor");
      OS_ASSERT(result);
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

    double ThermalZone_Impl::designFlowRate() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRate, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setDesignFlowRate(double designFlowRate) {
      if (designFlowRate < 0.0) {
        return false;
      }
      auto object = getOrCreateZoneVentilationObject();
      bool result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRate, designFlowRate);
      if (result) {
        result = object.setString(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/Zone");
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::AirChangesperHour, 0.0);
        OS_ASSERT(result);
      }
      return result;
    }

    double ThermalZone_Impl::flowRateperZoneFloorArea() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setFlowRateperZoneFloorArea(double flowRateperZoneFloorArea) {
      if (flowRateperZoneFloorArea < 0.0) {
        return false;
      }
      auto object = getOrCreateZoneVentilationObject();
      bool result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, flowRateperZoneFloorArea);
      if (result) {
        result = object.setString(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/Area");
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRate, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::AirChangesperHour, 0.0);
        OS_ASSERT(result);
      }
      return result;
    }

    double ThermalZone_Impl::flowRateperPerson() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setFlowRateperPerson(double flowRateperPerson) {
      if (flowRateperPerson < 0.0) {
        return false;
      }
      auto object = getOrCreateZoneVentilationObject();
      bool result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, flowRateperPerson);
      if (result) {
        result = object.setString(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "Flow/Person");
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRate, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::AirChangesperHour, 0.0);
        OS_ASSERT(result);
      }
      return result;
    }

    double ThermalZone_Impl::airChangesperHour() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::AirChangesperHour, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setAirChangesperHour(double airChangesperHour) {
      if (airChangesperHour < 0.0) {
        return false;
      }
      auto object = getOrCreateZoneVentilationObject();
      bool result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::AirChangesperHour, airChangesperHour);
      if (result) {
        result = object.setString(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "AirChanges/Hour");
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRate, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, 0.0);
        OS_ASSERT(result);
        result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, 0.0);
        OS_ASSERT(result);
      }
      return result;
    }

    std::string ThermalZone_Impl::ventilationType() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getString(OS_ZoneVentilation_DesignFlowRateFields::VentilationType, true)) {
          return *value;
        }
      }
      return std::string();
    }

    bool ThermalZone_Impl::setVentilationType(const std::string& ventilationType) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setString(OS_ZoneVentilation_DesignFlowRateFields::VentilationType, ventilationType);
    }

    double ThermalZone_Impl::fanPressureRise() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::FanPressureRise, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setFanPressureRise(double fanPressureRise) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FanPressureRise, fanPressureRise);
    }

    double ThermalZone_Impl::fanTotalEfficiency() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::FanTotalEfficiency, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::FanTotalEfficiency, fanTotalEfficiency);
    }

    double ThermalZone_Impl::constantTermCoefficient() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::ConstantTermCoefficient, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setConstantTermCoefficient(double constantTermCoefficient) {
      auto object = getOrCreateZoneVentilationObject();
      bool result = object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::ConstantTermCoefficient, constantTermCoefficient);
      return result;
    }

    double ThermalZone_Impl::temperatureTermCoefficient() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::TemperatureTermCoefficient, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setTemperatureTermCoefficient(double temperatureTermCoefficient) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::TemperatureTermCoefficient, temperatureTermCoefficient);
    }

    double ThermalZone_Impl::velocityTermCoefficient() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::VelocityTermCoefficient, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setVelocityTermCoefficient(double velocityTermCoefficient) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::VelocityTermCoefficient, velocityTermCoefficient);
    }

    double ThermalZone_Impl::velocitySquaredTermCoefficient() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::VelocitySquaredTermCoefficient, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::VelocitySquaredTermCoefficient, velocitySquaredTermCoefficient);
    }

    double ThermalZone_Impl::minimumIndoorTemperature() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperature, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setMinimumIndoorTemperature(double minimumIndoorTemperature) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperature, minimumIndoorTemperature);
    }

    double ThermalZone_Impl::maximumIndoorTemperature() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperature, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setMaximumIndoorTemperature(double maximumIndoorTemperature) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperature, maximumIndoorTemperature);
    }

    double ThermalZone_Impl::deltaTemperature() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::DeltaTemperature, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setDeltaTemperature(double deltaTemperature) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::DeltaTemperature, deltaTemperature);
    }

    double ThermalZone_Impl::minimumOutdoorTemperature() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperature, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setMinimumOutdoorTemperature(double minimumOutdoorTemperature) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperature, minimumOutdoorTemperature);
    }

    double ThermalZone_Impl::maximumOutdoorTemperature() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperature, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setMaximumOutdoorTemperature(double maximumOutdoorTemperature) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperature, maximumOutdoorTemperature);
    }

    double ThermalZone_Impl::maximumWindSpeed() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getDouble(OS_ZoneVentilation_DesignFlowRateFields::MaximumWindSpeed, true)) {
          return *value;
        }
      }
      return 0.0;
    }

    bool ThermalZone_Impl::setMaximumWindSpeed(double maximumWindSpeed) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setDouble(OS_ZoneVentilation_DesignFlowRateFields::MaximumWindSpeed, maximumWindSpeed);
    }

    std::string ThermalZone_Impl::densityBasis() const {
      if (auto object = zoneVentilationObject()) {
        if (auto value = object->getString(OS_ZoneVentilation_DesignFlowRateFields::DensityBasis, true)) {
          return *value;
        }
      }
      return std::string();
    }

    bool ThermalZone_Impl::setDensityBasis(const std::string& densityBasis) {
      auto object = getOrCreateZoneVentilationObject();
      return object.setString(OS_ZoneVentilation_DesignFlowRateFields::DensityBasis, densityBasis);
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

      const bool result = group->setString(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, "");
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

    double ThermalZone_Impl::illuminanceMapOriginXCoordinate() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto value = object->getDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalZone_Impl::setIlluminanceMapOriginXCoordinate(double illuminanceMapOriginXCoordinate) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }

      auto xMin = object->getDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, true);
      auto xMax = object->getDouble(openstudio::Output_IlluminanceMapFields::XMaximumCoordinate, true);
      if (!xMin || !xMax) {
        return false;
      }

      const double xLength = *xMax - *xMin;
      if (!object->setDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, illuminanceMapOriginXCoordinate)) {
        return false;
      }
      return object->setDouble(openstudio::Output_IlluminanceMapFields::XMaximumCoordinate, illuminanceMapOriginXCoordinate + xLength);
    }

    double ThermalZone_Impl::illuminanceMapOriginYCoordinate() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto value = object->getDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalZone_Impl::setIlluminanceMapOriginYCoordinate(double illuminanceMapOriginYCoordinate) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }

      auto yMin = object->getDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, true);
      auto yMax = object->getDouble(openstudio::Output_IlluminanceMapFields::YMaximumCoordinate, true);
      if (!yMin || !yMax) {
        return false;
      }

      const double yLength = *yMax - *yMin;
      if (!object->setDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, illuminanceMapOriginYCoordinate)) {
        return false;
      }
      return object->setDouble(openstudio::Output_IlluminanceMapFields::YMaximumCoordinate, illuminanceMapOriginYCoordinate + yLength);
    }

    double ThermalZone_Impl::illuminanceMapOriginZCoordinate() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto value = object->getDouble(openstudio::Output_IlluminanceMapFields::Zheight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalZone_Impl::setIlluminanceMapOriginZCoordinate(double illuminanceMapOriginZCoordinate) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }
      return object->setDouble(openstudio::Output_IlluminanceMapFields::Zheight, illuminanceMapOriginZCoordinate);
    }

    double ThermalZone_Impl::illuminanceMapXLength() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto xMin = object->getDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, true);
      auto xMax = object->getDouble(openstudio::Output_IlluminanceMapFields::XMaximumCoordinate, true);
      OS_ASSERT(xMin);
      OS_ASSERT(xMax);
      return *xMax - *xMin;
    }

    bool ThermalZone_Impl::setIlluminanceMapXLength(double illuminanceMapXLength) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }
      auto xMin = object->getDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, true);
      if (!xMin) {
        return false;
      }
      return object->setDouble(openstudio::Output_IlluminanceMapFields::XMaximumCoordinate, *xMin + illuminanceMapXLength);
    }

    int ThermalZone_Impl::illuminanceMapNumberofXGridPoints() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto value = object->getInt(openstudio::Output_IlluminanceMapFields::NumberofXGridPoints, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalZone_Impl::setIlluminanceMapNumberofXGridPoints(int illuminanceMapNumberofXGridPoints) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }
      return object->setInt(openstudio::Output_IlluminanceMapFields::NumberofXGridPoints, illuminanceMapNumberofXGridPoints);
    }

    double ThermalZone_Impl::illuminanceMapYLength() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto yMin = object->getDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, true);
      auto yMax = object->getDouble(openstudio::Output_IlluminanceMapFields::YMaximumCoordinate, true);
      OS_ASSERT(yMin);
      OS_ASSERT(yMax);
      return *yMax - *yMin;
    }

    bool ThermalZone_Impl::setIlluminanceMapYLength(double illuminanceMapYLength) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }
      auto yMin = object->getDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, true);
      if (!yMin) {
        return false;
      }
      return object->setDouble(openstudio::Output_IlluminanceMapFields::YMaximumCoordinate, *yMin + illuminanceMapYLength);
    }

    int ThermalZone_Impl::illuminanceMapNumberofYGridPoints() const {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      OS_ASSERT(object);
      auto value = object->getInt(openstudio::Output_IlluminanceMapFields::NumberofYGridPoints, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalZone_Impl::setIlluminanceMapNumberofYGridPoints(int illuminanceMapNumberofYGridPoints) {
      const auto zone = getObject<openstudio::epmodel::ThermalZone>();
      auto object = outputIlluminanceMapForZone(zone);
      if (!object) {
        return false;
      }
      return object->setInt(openstudio::Output_IlluminanceMapFields::NumberofYGridPoints, illuminanceMapNumberofYGridPoints);
    }

    void ThermalZone_Impl::doCanonicalize(LoadContext& context) {
      auto sz = sizingZone();
      sz.getImpl<openstudio::epmodel::detail::SizingZone_Impl>()->canonicalize(context);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
