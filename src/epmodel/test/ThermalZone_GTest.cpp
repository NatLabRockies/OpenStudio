/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "../StraightComponent/Node.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneControlContaminantController.hpp"
#include "../ModelObject/ZoneControlHumidistat.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../Thermostat/Thermostat.hpp"
#include "../Thermostat/Thermostat_Impl.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint_Impl.hpp"
#include "../ZoneHVACComponent/FanZoneExhaust.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric.hpp"
#include "../ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem.hpp"
#include "../ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include <utilities/idd/Daylighting_Controls_FieldEnums.hxx>
#include <utilities/idd/Daylighting_ReferencePoint_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneControl_Thermostat_FieldEnums.hxx>
#include <utilities/idd/Output_IlluminanceMap_FieldEnums.hxx>
#include <utilities/idd/Zone_FieldEnums.hxx>
#include <boost/none.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ThermalZone_DefaultConstructor) {
  Model model;
  ThermalZone zone(model);
  EXPECT_EQ(ThermalZone::iddObjectType(), zone.iddObject().type());
  EXPECT_FALSE(zone.nameString().empty());
}

TEST_F(EPModelFixture, API_ThermalZone_ModelLookupByTypeAndName) {
  Model model;
  ThermalZone zone(model);

  auto object = model.getObjectByTypeAndName(ThermalZone::iddObjectType(), zone.nameString());
  ASSERT_TRUE(object);
  EXPECT_EQ(zone.cast<ModelObject>(), object->cast<ModelObject>());
}

TEST_F(EPModelFixture, ThermalZone_AddToNode_DemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  EXPECT_TRUE(zone.addToNode(*branchNode));

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(splitterOutlets.size(), mixerInlets.size());
  ASSERT_EQ(1u, splitterOutlets.size());
  EXPECT_NE(splitterOutlets[0], mixerInlets[0]);

  auto updatedNode = splitterOutlets[0].cast<Node>();
  EXPECT_EQ(zone.nameString() + " Demand Branch Node", updatedNode.nameString());
  auto returnNode = mixerInlets[0].cast<Node>();
  EXPECT_EQ(zone.nameString() + " Demand Return Node", returnNode.nameString());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  const auto inletNodes = zoneConnections->zoneAirInletNodes();
  ASSERT_EQ(1u, inletNodes.size());
  const auto returnNodes = zoneConnections->zoneReturnAirNodes();
  ASSERT_EQ(1u, returnNodes.size());
  EXPECT_EQ(updatedNode.cast<ModelObject>(), inletNodes.front().cast<ModelObject>());
  EXPECT_EQ(returnNode.cast<ModelObject>(), returnNodes.front().cast<ModelObject>());

  const auto demandComps = airLoop.demandComponents();
  ASSERT_EQ(7u, demandComps.size());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[0].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter), demandComps[1].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[2].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Zone), demandComps[3].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[4].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneMixer), demandComps[5].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[6].iddObject().type());
}

TEST_F(EPModelFixture, ThermalZone_AddToNode_FailsOnSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_FALSE(zone.addToNode(supplyInletNode));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(zone.addToNode(supplyOutletNode));

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(zone.addToNode(demandInletNode));

  auto demandOutletNode = airLoop.demandOutletNode();
  EXPECT_FALSE(zone.addToNode(demandOutletNode));
}

TEST_F(EPModelFixture, ThermalZone_AddRemoveEquipment_CoordinatesEquipmentListAndConnections) {
  Model model;
  ThermalZone zone(model);
  FanZoneExhaust fan(model);

  ASSERT_TRUE(zone.addEquipment(fan.cast<ModelObject>()));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);

  auto equipmentList = connections->zoneHVACEquipmentList();
  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(fan.cast<ModelObject>(), equipment.front());

  auto fanInlet = fan.inletNode();
  ASSERT_TRUE(fanInlet);
  const auto exhaustNodes = connections->zoneAirExhaustNodes();
  ASSERT_EQ(1u, exhaustNodes.size());
  EXPECT_EQ(*fanInlet, exhaustNodes.front());

  fan.removeFromThermalZone();

  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_TRUE(connections->zoneAirExhaustNodes().empty());
}

TEST_F(EPModelFixture, ThermalZone_AddEquipment_ListOnlyEquipmentDoesNotMutateConnectionNodes) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveElectric baseboard(model);

  ASSERT_TRUE(zone.addEquipment(baseboard.cast<ModelObject>()));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto equipmentList = connections->zoneHVACEquipmentList();
  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(baseboard.cast<ModelObject>(), equipment.front());

  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneAirExhaustNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
}

TEST_F(EPModelFixture, API_ThermalZone_DaylightingFractions_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  openstudio::IdfObject daylightingControls(openstudio::IddObjectType::Daylighting_Controls);
  ASSERT_TRUE(daylightingControls.setName(zone.nameString() + " DaylightingControls"));
  ASSERT_TRUE(daylightingControls.setString(openstudio::Daylighting_ControlsFields::ZoneorSpaceName, zone.nameString()));
  auto primaryGroup = daylightingControls.pushExtensibleGroup();
  ASSERT_TRUE(
    primaryGroup.setString(openstudio::Daylighting_ControlsExtensibleFields::DaylightingReferencePointName, zone.nameString() + " Primary Ref Pt"));
  ASSERT_TRUE(primaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, 0.7));
  ASSERT_TRUE(primaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::IlluminanceSetpointatReferencePoint, 500.0));
  ASSERT_TRUE(model.addObject(daylightingControls));

  EXPECT_FALSE(zone.isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted());
  EXPECT_NEAR(0.7, zone.fractionofZoneControlledbyPrimaryDaylightingControl(), 1e-9);
  EXPECT_TRUE(zone.isFractionofZoneControlledbySecondaryDaylightingControlDefaulted());
  EXPECT_NEAR(0.0, zone.fractionofZoneControlledbySecondaryDaylightingControl(), 1e-9);

  EXPECT_TRUE(zone.setFractionofZoneControlledbySecondaryDaylightingControl(0.2));
  EXPECT_FALSE(zone.isFractionofZoneControlledbySecondaryDaylightingControlDefaulted());
  EXPECT_NEAR(0.2, zone.fractionofZoneControlledbySecondaryDaylightingControl(), 1e-9);

  EXPECT_FALSE(zone.setFractionofZoneControlledbyPrimaryDaylightingControl(0.85));
  EXPECT_NEAR(0.7, zone.fractionofZoneControlledbyPrimaryDaylightingControl(), 1e-9);

  zone.resetFractionofZoneControlledbyPrimaryDaylightingControl();
  EXPECT_TRUE(zone.isFractionofZoneControlledbyPrimaryDaylightingControlDefaulted());
  EXPECT_NEAR(1.0, zone.fractionofZoneControlledbyPrimaryDaylightingControl(), 1e-9);
}

TEST_F(EPModelFixture, API_ThermalZone_DesignSpecificationOutdoorAirScalarAccessors_RoundTrip) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  EXPECT_EQ("Sum", zone.outdoorAirMethod());
  EXPECT_DOUBLE_EQ(0.0, zone.outdoorAirFlowperPerson());
  EXPECT_DOUBLE_EQ(0.0, zone.outdoorAirFlowperFloorArea());
  EXPECT_DOUBLE_EQ(0.0, zone.outdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.0, zone.outdoorAirFlowAirChangesperHour());

  EXPECT_TRUE(zone.setOutdoorAirMethod("Maximum"));
  EXPECT_TRUE(zone.setOutdoorAirFlowperPerson(0.004));
  EXPECT_TRUE(zone.setOutdoorAirFlowperFloorArea(0.0008));
  EXPECT_TRUE(zone.setOutdoorAirFlowRate(0.15));
  EXPECT_TRUE(zone.setOutdoorAirFlowAirChangesperHour(0.25));

  EXPECT_EQ("Maximum", zone.outdoorAirMethod());
  EXPECT_DOUBLE_EQ(0.004, zone.outdoorAirFlowperPerson());
  EXPECT_DOUBLE_EQ(0.0008, zone.outdoorAirFlowperFloorArea());
  EXPECT_DOUBLE_EQ(0.15, zone.outdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.25, zone.outdoorAirFlowAirChangesperHour());

  auto assigned = space.designSpecificationOutdoorAir();
  ASSERT_TRUE(assigned);
  EXPECT_EQ("Maximum", assigned->outdoorAirMethod());
  EXPECT_DOUBLE_EQ(0.004, assigned->outdoorAirFlowperPerson());
  EXPECT_DOUBLE_EQ(0.0008, assigned->outdoorAirFlowperFloorArea());
  EXPECT_DOUBLE_EQ(0.15, assigned->outdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.25, assigned->outdoorAirFlowAirChangesperHour());
}

TEST_F(EPModelFixture, API_ThermalZone_DaylightingReferencePointCoordinates_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  openstudio::IdfObject primaryReferencePoint(openstudio::IddObjectType::Daylighting_ReferencePoint);
  ASSERT_TRUE(primaryReferencePoint.setName(zone.nameString() + " Primary Ref Pt"));
  ASSERT_TRUE(primaryReferencePoint.setString(openstudio::Daylighting_ReferencePointFields::ZoneorSpaceName, zone.nameString()));
  ASSERT_TRUE(primaryReferencePoint.setDouble(openstudio::Daylighting_ReferencePointFields::XCoordinateofReferencePoint, 1.0));
  ASSERT_TRUE(primaryReferencePoint.setDouble(openstudio::Daylighting_ReferencePointFields::YCoordinateofReferencePoint, 2.0));
  ASSERT_TRUE(primaryReferencePoint.setDouble(openstudio::Daylighting_ReferencePointFields::ZCoordinateofReferencePoint, 3.0));
  ASSERT_TRUE(model.addObject(primaryReferencePoint));

  openstudio::IdfObject secondaryReferencePoint(openstudio::IddObjectType::Daylighting_ReferencePoint);
  ASSERT_TRUE(secondaryReferencePoint.setName(zone.nameString() + " Secondary Ref Pt"));
  ASSERT_TRUE(secondaryReferencePoint.setString(openstudio::Daylighting_ReferencePointFields::ZoneorSpaceName, zone.nameString()));
  ASSERT_TRUE(secondaryReferencePoint.setDouble(openstudio::Daylighting_ReferencePointFields::XCoordinateofReferencePoint, 4.0));
  ASSERT_TRUE(secondaryReferencePoint.setDouble(openstudio::Daylighting_ReferencePointFields::YCoordinateofReferencePoint, 5.0));
  ASSERT_TRUE(secondaryReferencePoint.setDouble(openstudio::Daylighting_ReferencePointFields::ZCoordinateofReferencePoint, 6.0));
  ASSERT_TRUE(model.addObject(secondaryReferencePoint));

  openstudio::IdfObject daylightingControls(openstudio::IddObjectType::Daylighting_Controls);
  ASSERT_TRUE(daylightingControls.setName(zone.nameString() + " DaylightingControls"));
  ASSERT_TRUE(daylightingControls.setString(openstudio::Daylighting_ControlsFields::ZoneorSpaceName, zone.nameString()));
  auto primaryGroup = daylightingControls.pushExtensibleGroup();
  ASSERT_TRUE(
    primaryGroup.setString(openstudio::Daylighting_ControlsExtensibleFields::DaylightingReferencePointName, primaryReferencePoint.nameString()));
  ASSERT_TRUE(primaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, 0.6));
  ASSERT_TRUE(primaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::IlluminanceSetpointatReferencePoint, 500.0));

  auto secondaryGroup = daylightingControls.pushExtensibleGroup();
  ASSERT_TRUE(
    secondaryGroup.setString(openstudio::Daylighting_ControlsExtensibleFields::DaylightingReferencePointName, secondaryReferencePoint.nameString()));
  ASSERT_TRUE(secondaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, 0.3));
  ASSERT_TRUE(secondaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::IlluminanceSetpointatReferencePoint, 400.0));
  ASSERT_TRUE(model.addObject(daylightingControls));

  EXPECT_NEAR(1.0, zone.primaryDaylightingControlXCoordinate(), 1e-9);
  EXPECT_NEAR(2.0, zone.primaryDaylightingControlYCoordinate(), 1e-9);
  EXPECT_NEAR(3.0, zone.primaryDaylightingControlZCoordinate(), 1e-9);

  EXPECT_NEAR(4.0, zone.secondaryDaylightingControlXCoordinate(), 1e-9);
  EXPECT_NEAR(5.0, zone.secondaryDaylightingControlYCoordinate(), 1e-9);
  EXPECT_NEAR(6.0, zone.secondaryDaylightingControlZCoordinate(), 1e-9);

  EXPECT_TRUE(zone.setPrimaryDaylightingControlXCoordinate(11.0));
  EXPECT_TRUE(zone.setPrimaryDaylightingControlYCoordinate(12.0));
  EXPECT_TRUE(zone.setPrimaryDaylightingControlZCoordinate(13.0));

  EXPECT_TRUE(zone.setSecondaryDaylightingControlXCoordinate(14.0));
  EXPECT_TRUE(zone.setSecondaryDaylightingControlYCoordinate(15.0));
  EXPECT_TRUE(zone.setSecondaryDaylightingControlZCoordinate(16.0));

  EXPECT_NEAR(11.0, zone.primaryDaylightingControlXCoordinate(), 1e-9);
  EXPECT_NEAR(12.0, zone.primaryDaylightingControlYCoordinate(), 1e-9);
  EXPECT_NEAR(13.0, zone.primaryDaylightingControlZCoordinate(), 1e-9);

  EXPECT_NEAR(14.0, zone.secondaryDaylightingControlXCoordinate(), 1e-9);
  EXPECT_NEAR(15.0, zone.secondaryDaylightingControlYCoordinate(), 1e-9);
  EXPECT_NEAR(16.0, zone.secondaryDaylightingControlZCoordinate(), 1e-9);
}

TEST_F(EPModelFixture, API_ThermalZone_UseIdealAirLoads_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  EXPECT_FALSE(zone.useIdealAirLoads());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACIdealLoadsAirSystem>().empty());

  EXPECT_TRUE(zone.setUseIdealAirLoads(true));
  EXPECT_TRUE(zone.useIdealAirLoads());

  const auto idealLoads = model.getConcreteModelObjects<ZoneHVACIdealLoadsAirSystem>();
  ASSERT_EQ(1u, idealLoads.size());
  ASSERT_TRUE(idealLoads.front().thermalZone());
  EXPECT_EQ(zone, *idealLoads.front().thermalZone());

  EXPECT_TRUE(zone.setUseIdealAirLoads(false));
  EXPECT_FALSE(zone.useIdealAirLoads());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACIdealLoadsAirSystem>().empty());
}

TEST_F(EPModelFixture, API_ThermalZone_ThermostatSetpointDualSetpoint_Relationships) {
  Model model;
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ThermostatSetpointDualSetpoint thermostat(model);
  ASSERT_TRUE(thermostat.setName("Shared Thermostat"));

  EXPECT_FALSE(zone1.thermostatSetpointDualSetpoint());
  EXPECT_TRUE(zone1.setThermostatSetpointDualSetpoint(thermostat));
  ASSERT_TRUE(zone1.thermostat());
  ASSERT_TRUE(zone1.thermostatSetpointDualSetpoint());
  EXPECT_EQ(zone1.thermostatSetpointDualSetpoint().get(), zone1.thermostat().get());
  EXPECT_EQ("Shared Thermostat", zone1.thermostatSetpointDualSetpoint()->nameString());

  EXPECT_TRUE(zone2.setThermostat(thermostat));
  ASSERT_TRUE(zone2.thermostat());
  ASSERT_TRUE(zone2.thermostatSetpointDualSetpoint());
  EXPECT_EQ(zone2.thermostatSetpointDualSetpoint().get(), zone2.thermostat().get());
  EXPECT_NE(zone1.thermostatSetpointDualSetpoint().get(), zone2.thermostatSetpointDualSetpoint().get());

  zone1.resetThermostat();
  EXPECT_FALSE(zone1.thermostat());
  EXPECT_FALSE(zone1.thermostatSetpointDualSetpoint());
  ASSERT_TRUE(zone2.thermostatSetpointDualSetpoint());
}

TEST_F(EPModelFixture, API_ThermalZone_Thermostat_Relationships) {
  Model model;
  ThermalZone zone(model);
  ThermostatSetpointDualSetpoint thermostat(model);
  ASSERT_TRUE(thermostat.setName("Generic Thermostat"));

  EXPECT_FALSE(zone.thermostat());
  EXPECT_TRUE(zone.setThermostat(thermostat));

  auto genericThermostat = zone.thermostat();
  ASSERT_TRUE(genericThermostat);
  EXPECT_EQ("Generic Thermostat", genericThermostat->nameString());
  EXPECT_EQ(ThermostatSetpointDualSetpoint::iddObjectType(), genericThermostat->iddObject().type());
  ASSERT_TRUE(zone.thermostatSetpointDualSetpoint());
  EXPECT_EQ(zone.thermostatSetpointDualSetpoint().get(), genericThermostat.get());
  ASSERT_TRUE(thermostat.thermalZone());
  EXPECT_EQ(zone, *thermostat.thermalZone());

  zone.resetThermostat();
  EXPECT_FALSE(zone.thermostat());
  EXPECT_FALSE(zone.thermostatSetpointDualSetpoint());
  EXPECT_FALSE(thermostat.thermalZone());
}

TEST_F(EPModelFixture, API_ThermalZone_ZoneControlHumidistat_Relationships) {
  Model model;
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ZoneControlHumidistat humidistat(model);
  ASSERT_TRUE(humidistat.setName("Shared Humidistat"));

  EXPECT_FALSE(zone1.zoneControlHumidistat());
  EXPECT_TRUE(zone1.setZoneControlHumidistat(humidistat));
  ASSERT_TRUE(zone1.zoneControlHumidistat());
  EXPECT_EQ("Shared Humidistat", zone1.zoneControlHumidistat()->nameString());

  EXPECT_TRUE(zone2.setZoneControlHumidistat(humidistat));
  ASSERT_TRUE(zone2.zoneControlHumidistat());
  EXPECT_NE(zone1.zoneControlHumidistat().get(), zone2.zoneControlHumidistat().get());

  zone1.resetZoneControlHumidistat();
  EXPECT_FALSE(zone1.zoneControlHumidistat());
  ASSERT_TRUE(zone2.zoneControlHumidistat());
}

TEST_F(EPModelFixture, API_ThermalZone_ZoneControlContaminantController_Relationships) {
  Model model;
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ZoneControlContaminantController controller(model);
  ASSERT_TRUE(controller.setName("Shared Controller"));

  EXPECT_FALSE(zone1.zoneControlContaminantController());
  EXPECT_TRUE(zone1.setZoneControlContaminantController(controller));
  ASSERT_TRUE(zone1.zoneControlContaminantController());
  EXPECT_EQ("Shared Controller", zone1.zoneControlContaminantController()->nameString());

  EXPECT_TRUE(zone2.setZoneControlContaminantController(controller));
  ASSERT_TRUE(zone2.zoneControlContaminantController());
  EXPECT_NE(zone1.zoneControlContaminantController().get(), zone2.zoneControlContaminantController().get());

  zone1.resetZoneControlContaminantController();
  EXPECT_FALSE(zone1.zoneControlContaminantController());
  ASSERT_TRUE(zone2.zoneControlContaminantController());
}

TEST_F(EPModelFixture, API_ThermalZone_EquipmentAndTopologyHelpers_RoundTrip) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveElectric baseboard(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ASSERT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(baseboard.cast<ModelObject>(), zone.equipment().front());
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_TRUE(zone.airLoopHVACTerminals().empty());

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  EXPECT_EQ(zone.nameString() + " Demand Branch Node", zoneAirNode.nameString());

  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_NE(zoneAirNode.cast<ModelObject>(), *returnAirObject);
  auto mixerInletObject = airLoop.zoneMixer().lastInletModelObject();
  ASSERT_TRUE(mixerInletObject);
  EXPECT_EQ(*mixerInletObject, *returnAirObject);

  auto returnAirObjects = zone.returnAirModelObjects();
  ASSERT_EQ(1u, returnAirObjects.size());
  EXPECT_EQ(*returnAirObject, returnAirObjects.front());

  auto airLoopTerminal = zone.airLoopHVACTerminal();
  ASSERT_TRUE(airLoopTerminal);
  EXPECT_EQ(terminal.cast<HVACComponent>(), *airLoopTerminal);

  auto airLoopTerminals = zone.airLoopHVACTerminals();
  ASSERT_EQ(1u, airLoopTerminals.size());
  EXPECT_EQ(terminal.cast<HVACComponent>(), airLoopTerminals.front());
}

TEST_F(EPModelFixture, API_ThermalZone_UseIdealAirLoads_RemovesAirLoopBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  ASSERT_EQ(1u, airLoop.thermalZones().size());

  EXPECT_TRUE(zone.setUseIdealAirLoads(true));
  EXPECT_TRUE(zone.useIdealAirLoads());
  EXPECT_TRUE(airLoop.thermalZones().empty());

  const auto idealLoads = model.getConcreteModelObjects<ZoneHVACIdealLoadsAirSystem>();
  ASSERT_EQ(1u, idealLoads.size());
  ASSERT_TRUE(idealLoads.front().thermalZone());
  EXPECT_EQ(zone, *idealLoads.front().thermalZone());
}

TEST_F(EPModelFixture, API_ThermalZone_OutputIlluminanceMapScalars_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  openstudio::IdfObject illuminanceMapObject(openstudio::IddObjectType::Output_IlluminanceMap);
  ASSERT_TRUE(illuminanceMapObject.setName(zone.nameString() + " IlluminanceMap"));
  ASSERT_TRUE(illuminanceMapObject.setString(openstudio::Output_IlluminanceMapFields::ZoneorSpaceName, zone.nameString()));
  ASSERT_TRUE(illuminanceMapObject.setDouble(openstudio::Output_IlluminanceMapFields::Zheight, 0.75));
  ASSERT_TRUE(illuminanceMapObject.setDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, 1.0));
  ASSERT_TRUE(illuminanceMapObject.setDouble(openstudio::Output_IlluminanceMapFields::XMaximumCoordinate, 11.0));
  ASSERT_TRUE(illuminanceMapObject.setInt(openstudio::Output_IlluminanceMapFields::NumberofXGridPoints, 10));
  ASSERT_TRUE(illuminanceMapObject.setDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, 2.0));
  ASSERT_TRUE(illuminanceMapObject.setDouble(openstudio::Output_IlluminanceMapFields::YMaximumCoordinate, 14.0));
  ASSERT_TRUE(illuminanceMapObject.setInt(openstudio::Output_IlluminanceMapFields::NumberofYGridPoints, 12));
  ASSERT_TRUE(model.addObject(illuminanceMapObject));

  EXPECT_NEAR(1.0, zone.illuminanceMapOriginXCoordinate(), 1e-9);
  EXPECT_NEAR(2.0, zone.illuminanceMapOriginYCoordinate(), 1e-9);
  EXPECT_NEAR(0.75, zone.illuminanceMapOriginZCoordinate(), 1e-9);
  EXPECT_NEAR(10.0, zone.illuminanceMapXLength(), 1e-9);
  EXPECT_EQ(10, zone.illuminanceMapNumberofXGridPoints());
  EXPECT_NEAR(12.0, zone.illuminanceMapYLength(), 1e-9);
  EXPECT_EQ(12, zone.illuminanceMapNumberofYGridPoints());

  EXPECT_TRUE(zone.setIlluminanceMapOriginXCoordinate(3.0));
  EXPECT_TRUE(zone.setIlluminanceMapOriginYCoordinate(5.0));
  EXPECT_TRUE(zone.setIlluminanceMapOriginZCoordinate(1.25));
  EXPECT_TRUE(zone.setIlluminanceMapXLength(8.0));
  EXPECT_TRUE(zone.setIlluminanceMapNumberofXGridPoints(8));
  EXPECT_TRUE(zone.setIlluminanceMapYLength(9.0));
  EXPECT_TRUE(zone.setIlluminanceMapNumberofYGridPoints(9));

  EXPECT_NEAR(3.0, zone.illuminanceMapOriginXCoordinate(), 1e-9);
  EXPECT_NEAR(5.0, zone.illuminanceMapOriginYCoordinate(), 1e-9);
  EXPECT_NEAR(1.25, zone.illuminanceMapOriginZCoordinate(), 1e-9);
  EXPECT_NEAR(8.0, zone.illuminanceMapXLength(), 1e-9);
  EXPECT_EQ(8, zone.illuminanceMapNumberofXGridPoints());
  EXPECT_NEAR(9.0, zone.illuminanceMapYLength(), 1e-9);
  EXPECT_EQ(9, zone.illuminanceMapNumberofYGridPoints());

  const auto outputIlluminanceMaps = model.getObjectsByType(openstudio::IddObjectType::Output_IlluminanceMap);
  ASSERT_EQ(1u, outputIlluminanceMaps.size());
  auto zoneOrSpaceName = outputIlluminanceMaps.front().getString(openstudio::Output_IlluminanceMapFields::ZoneorSpaceName, true);
  ASSERT_TRUE(zoneOrSpaceName);
  EXPECT_EQ(zone.nameString(), *zoneOrSpaceName);
  auto xMin = outputIlluminanceMaps.front().getDouble(openstudio::Output_IlluminanceMapFields::XMinimumCoordinate, true);
  auto xMax = outputIlluminanceMaps.front().getDouble(openstudio::Output_IlluminanceMapFields::XMaximumCoordinate, true);
  auto xPoints = outputIlluminanceMaps.front().getInt(openstudio::Output_IlluminanceMapFields::NumberofXGridPoints, true);
  auto yMin = outputIlluminanceMaps.front().getDouble(openstudio::Output_IlluminanceMapFields::YMinimumCoordinate, true);
  auto yMax = outputIlluminanceMaps.front().getDouble(openstudio::Output_IlluminanceMapFields::YMaximumCoordinate, true);
  auto yPoints = outputIlluminanceMaps.front().getInt(openstudio::Output_IlluminanceMapFields::NumberofYGridPoints, true);
  auto zHeight = outputIlluminanceMaps.front().getDouble(openstudio::Output_IlluminanceMapFields::Zheight, true);
  ASSERT_TRUE(xMin);
  ASSERT_TRUE(xMax);
  ASSERT_TRUE(xPoints);
  ASSERT_TRUE(yMin);
  ASSERT_TRUE(yMax);
  ASSERT_TRUE(yPoints);
  ASSERT_TRUE(zHeight);
  EXPECT_NEAR(3.0, *xMin, 1e-9);
  EXPECT_NEAR(11.0, *xMax, 1e-9);
  EXPECT_EQ(8, *xPoints);
  EXPECT_NEAR(5.0, *yMin, 1e-9);
  EXPECT_NEAR(14.0, *yMax, 1e-9);
  EXPECT_EQ(9, *yPoints);
  EXPECT_NEAR(1.25, *zHeight, 1e-9);
}

TEST_F(EPModelFixture, API_ThermalZone_ZoneScalarAccessors_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  auto zoneIdd = openstudio::IddFactory::instance().getObject(openstudio::IddObjectType::Zone);
  ASSERT_TRUE(zoneIdd);
  auto insideAlgorithms = openstudio::getIddKeyNames(*zoneIdd, openstudio::ZoneFields::ZoneInsideConvectionAlgorithm);
  ASSERT_FALSE(insideAlgorithms.empty());
  auto outsideAlgorithms = openstudio::getIddKeyNames(*zoneIdd, openstudio::ZoneFields::ZoneOutsideConvectionAlgorithm);
  ASSERT_FALSE(outsideAlgorithms.empty());

  EXPECT_EQ(1, zone.multiplier());
  EXPECT_TRUE(zone.setMultiplier(2));
  EXPECT_EQ(2, zone.multiplier());
  EXPECT_FALSE(zone.isMultiplierDefaulted());

  EXPECT_FALSE(zone.ceilingHeight());
  EXPECT_TRUE(zone.isCeilingHeightDefaulted());

  EXPECT_TRUE(zone.setCeilingHeight(3.5));
  ASSERT_TRUE(zone.ceilingHeight());
  EXPECT_DOUBLE_EQ(3.5, zone.ceilingHeight().get());
  EXPECT_FALSE(zone.isCeilingHeightDefaulted());

  zone.autocalculateCeilingHeight();
  EXPECT_FALSE(zone.ceilingHeight());

  zone.resetCeilingHeight();
  EXPECT_TRUE(zone.isCeilingHeightDefaulted());
  EXPECT_FALSE(zone.ceilingHeight());

  EXPECT_FALSE(zone.volume());
  EXPECT_TRUE(zone.isVolumeDefaulted());

  EXPECT_TRUE(zone.setVolume(12.25));
  ASSERT_TRUE(zone.volume());
  EXPECT_DOUBLE_EQ(12.25, zone.volume().get());
  EXPECT_FALSE(zone.isVolumeDefaulted());

  zone.autocalculateVolume();
  EXPECT_FALSE(zone.volume());

  zone.resetVolume();
  EXPECT_TRUE(zone.isVolumeDefaulted());
  EXPECT_FALSE(zone.volume());

  EXPECT_FALSE(zone.zoneInsideConvectionAlgorithm());
  EXPECT_TRUE(zone.setZoneInsideConvectionAlgorithm(insideAlgorithms.front()));
  ASSERT_TRUE(zone.zoneInsideConvectionAlgorithm());
  EXPECT_EQ(insideAlgorithms.front(), zone.zoneInsideConvectionAlgorithm().get());

  EXPECT_FALSE(zone.zoneOutsideConvectionAlgorithm());
  EXPECT_TRUE(zone.setZoneOutsideConvectionAlgorithm(outsideAlgorithms.front()));
  ASSERT_TRUE(zone.zoneOutsideConvectionAlgorithm());
  EXPECT_EQ(outsideAlgorithms.front(), zone.zoneOutsideConvectionAlgorithm().get());
}

TEST_F(EPModelFixture, API_ThermalZone_ThermostatControlObjectTypes_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  EXPECT_TRUE(zone.control1ObjectType().empty());
  EXPECT_FALSE(zone.control2ObjectType());

  EXPECT_TRUE(zone.setControl1ObjectType("ThermostatSetpoint:DualSetpoint"));
  EXPECT_EQ("ThermostatSetpoint:DualSetpoint", zone.control1ObjectType());

  EXPECT_TRUE(zone.setControl2ObjectType("ThermostatSetpoint:SingleHeating"));
  ASSERT_TRUE(zone.control2ObjectType());
  EXPECT_EQ("ThermostatSetpoint:SingleHeating", zone.control2ObjectType().get());

  zone.resetControl2ObjectType();
  EXPECT_FALSE(zone.control2ObjectType());

  auto zoneControlObjects = model.getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat);
  ASSERT_EQ(1u, zoneControlObjects.size());
}

TEST_F(EPModelFixture, API_ThermalZone_ThermostatTemperatureDifference_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  EXPECT_TRUE(zone.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.temperatureDifferenceBetweenCutoutAndSetpoint());

  EXPECT_TRUE(zone.setTemperatureDifferenceBetweenCutoutAndSetpoint(1.5));
  EXPECT_FALSE(zone.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(1.5, zone.temperatureDifferenceBetweenCutoutAndSetpoint());

  zone.resetTemperatureDifferenceBetweenCutoutAndSetpoint();
  EXPECT_TRUE(zone.isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted());
  EXPECT_DOUBLE_EQ(0.0, zone.temperatureDifferenceBetweenCutoutAndSetpoint());
}

TEST_F(EPModelFixture, API_ThermalZone_ZoneVentilationDesignFlowRateScalarAccessors_RoundTrip) {
  Model model;
  ThermalZone zone(model);

  EXPECT_DOUBLE_EQ(0.0, zone.designFlowRate());
  EXPECT_FALSE(zone.setDesignFlowRate(-0.1));
  EXPECT_TRUE(zone.setDesignFlowRate(0.25));
  EXPECT_DOUBLE_EQ(0.25, zone.designFlowRate());
  EXPECT_DOUBLE_EQ(0.0, zone.flowRateperZoneFloorArea());
  EXPECT_DOUBLE_EQ(0.0, zone.flowRateperPerson());
  EXPECT_DOUBLE_EQ(0.0, zone.airChangesperHour());

  EXPECT_FALSE(zone.setFlowRateperZoneFloorArea(-0.1));
  EXPECT_TRUE(zone.setFlowRateperZoneFloorArea(0.0008));
  EXPECT_DOUBLE_EQ(0.0008, zone.flowRateperZoneFloorArea());
  EXPECT_DOUBLE_EQ(0.0, zone.designFlowRate());

  EXPECT_FALSE(zone.setFlowRateperPerson(-0.2));
  EXPECT_TRUE(zone.setFlowRateperPerson(0.0012));
  EXPECT_DOUBLE_EQ(0.0012, zone.flowRateperPerson());
  EXPECT_DOUBLE_EQ(0.0, zone.designFlowRate());

  EXPECT_FALSE(zone.setAirChangesperHour(-0.5));
  EXPECT_TRUE(zone.setAirChangesperHour(2.5));
  EXPECT_DOUBLE_EQ(2.5, zone.airChangesperHour());

  const auto ventilationValues = ThermalZone::ventilationTypeValues();
  ASSERT_FALSE(ventilationValues.empty());
  EXPECT_TRUE(zone.setVentilationType(ventilationValues.front()));
  EXPECT_EQ(ventilationValues.front(), zone.ventilationType());

  EXPECT_FALSE(zone.setVentilationType("InvalidChoice"));
  EXPECT_EQ(ventilationValues.front(), zone.ventilationType());

  EXPECT_TRUE(zone.setFanPressureRise(3.2));
  EXPECT_DOUBLE_EQ(3.2, zone.fanPressureRise());

  EXPECT_TRUE(zone.setFanTotalEfficiency(0.82));
  EXPECT_DOUBLE_EQ(0.82, zone.fanTotalEfficiency());

  EXPECT_TRUE(zone.setConstantTermCoefficient(1.23));
  EXPECT_DOUBLE_EQ(1.23, zone.constantTermCoefficient());

  EXPECT_TRUE(zone.setTemperatureTermCoefficient(0.045));
  EXPECT_DOUBLE_EQ(0.045, zone.temperatureTermCoefficient());

  EXPECT_TRUE(zone.setVelocityTermCoefficient(0.2));
  EXPECT_DOUBLE_EQ(0.2, zone.velocityTermCoefficient());

  EXPECT_TRUE(zone.setVelocitySquaredTermCoefficient(0.05));
  EXPECT_DOUBLE_EQ(0.05, zone.velocitySquaredTermCoefficient());

  EXPECT_TRUE(zone.setMinimumIndoorTemperature(16.0));
  EXPECT_DOUBLE_EQ(16.0, zone.minimumIndoorTemperature());

  EXPECT_TRUE(zone.setMaximumIndoorTemperature(26.0));
  EXPECT_DOUBLE_EQ(26.0, zone.maximumIndoorTemperature());

  EXPECT_TRUE(zone.setDeltaTemperature(4.0));
  EXPECT_DOUBLE_EQ(4.0, zone.deltaTemperature());

  EXPECT_TRUE(zone.setMinimumOutdoorTemperature(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, zone.minimumOutdoorTemperature());

  EXPECT_TRUE(zone.setMaximumOutdoorTemperature(45.0));
  EXPECT_DOUBLE_EQ(45.0, zone.maximumOutdoorTemperature());

  EXPECT_FALSE(zone.setMaximumWindSpeed(-5.0));
  EXPECT_TRUE(zone.setMaximumWindSpeed(38.0));
  EXPECT_DOUBLE_EQ(38.0, zone.maximumWindSpeed());

  const auto densityValues = ThermalZone::densityBasisValues();
  ASSERT_FALSE(densityValues.empty());
  EXPECT_TRUE(zone.setDensityBasis(densityValues.front()));
  EXPECT_EQ(densityValues.front(), zone.densityBasis());
  EXPECT_FALSE(zone.setDensityBasis("InvalidDensity"));
  EXPECT_EQ(densityValues.front(), zone.densityBasis());
}
