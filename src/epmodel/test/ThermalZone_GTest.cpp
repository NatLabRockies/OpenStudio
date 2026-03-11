/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../DesignSpecificationOutdoorAir.hpp"
#include "../Node.hpp"
#include "../Space.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ZoneHVACEquipmentConnections.hpp"
#include "../ZoneHVACEquipmentConnections_Impl.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include <utilities/idd/Daylighting_Controls_FieldEnums.hxx>
#include <utilities/idd/Daylighting_ReferencePoint_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

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
  EXPECT_EQ(splitterOutlets[0], mixerInlets[0]);

  auto updatedNode = splitterOutlets[0].cast<Node>();
  EXPECT_EQ(zone.nameString() + " Demand Branch Node", updatedNode.nameString());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  auto inletNode = zoneConnections->zoneAirInletNode();
  ASSERT_TRUE(inletNode);
  auto returnNode = zoneConnections->zoneReturnAirNode();
  ASSERT_TRUE(returnNode);
  EXPECT_EQ(updatedNode.cast<ModelObject>(), inletNode->cast<ModelObject>());
  EXPECT_EQ(updatedNode.cast<ModelObject>(), returnNode->cast<ModelObject>());

  const auto demandComps = airLoop.demandComponents();
  ASSERT_EQ(6u, demandComps.size());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[0].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter), demandComps[1].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[2].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Zone), demandComps[3].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneMixer), demandComps[4].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[5].iddObject().type());
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
  ASSERT_TRUE(primaryGroup.setString(openstudio::Daylighting_ControlsExtensibleFields::DaylightingReferencePointName,
                                     primaryReferencePoint.nameString()));
  ASSERT_TRUE(primaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::FractionofLightsControlledbyReferencePoint, 0.6));
  ASSERT_TRUE(primaryGroup.setDouble(openstudio::Daylighting_ControlsExtensibleFields::IlluminanceSetpointatReferencePoint, 500.0));

  auto secondaryGroup = daylightingControls.pushExtensibleGroup();
  ASSERT_TRUE(secondaryGroup.setString(openstudio::Daylighting_ControlsExtensibleFields::DaylightingReferencePointName,
                                       secondaryReferencePoint.nameString()));
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
