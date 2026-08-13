/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Splitter/Splitter.hpp"
#include "../Splitter/Splitter_Impl.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint.hpp"

#include <utilities/idd/AirLoopHVAC_SupplyPlenum_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACSupplyPlenum_DefaultConstructor) {
  Model model;
  AirLoopHVACSupplyPlenum plenum(model);
  EXPECT_EQ(AirLoopHVACSupplyPlenum::iddObjectType(), plenum.iddObject().type());
  EXPECT_TRUE(plenum.optionalCast<Splitter>());
}

TEST_F(EPModelFixture, AirLoopHVACSupplyPlenum_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACSupplyPlenum plenum(model);

  EXPECT_TRUE(plenum.setName("Main Supply Plenum"));
  EXPECT_EQ("Main Supply Plenum", plenum.nameString());
}

TEST_F(EPModelFixture, AirLoopHVACSupplyPlenum_ThermalZoneAndSplitterRelationships) {
  Model model;
  ThermalZone plenumZone(model);
  ThermostatSetpointDualSetpoint thermostat(model);
  AirLoopHVACSupplyPlenum plenum(model);
  Node inlet(model);
  Node firstOutlet(model);
  Node secondOutlet(model);

  ASSERT_TRUE(plenumZone.setThermostatSetpointDualSetpoint(thermostat));
  const auto originalZoneAirNode = plenumZone.zoneAirNode();
  ASSERT_EQ(1u, model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().size());
  ASSERT_EQ(1u, model.getConcreteModelObjects<SizingZone>().size());

  ASSERT_TRUE(plenum.setThermalZone(plenumZone));
  ASSERT_TRUE(plenum.thermalZone());
  EXPECT_EQ(plenumZone, *plenum.thermalZone());
  EXPECT_EQ(originalZoneAirNode, *plenum.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneNodeName));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat).empty());

  AirLoopHVACSupplyPlenum duplicateSupplyPlenum(model);
  EXPECT_FALSE(duplicateSupplyPlenum.setThermalZone(plenumZone));
  AirLoopHVACReturnPlenum duplicateReturnPlenum(model);
  EXPECT_FALSE(duplicateReturnPlenum.setThermalZone(plenumZone));

  ThermalZone returnPlenumZone(model);
  AirLoopHVACReturnPlenum returnPlenum(model);
  ASSERT_TRUE(returnPlenum.setThermalZone(returnPlenumZone));
  AirLoopHVACSupplyPlenum duplicateOfReturnPlenum(model);
  EXPECT_FALSE(duplicateOfReturnPlenum.setThermalZone(returnPlenumZone));

  EXPECT_EQ(openstudio::AirLoopHVAC_SupplyPlenumFields::InletNodeName, plenum.inletPort());
  EXPECT_EQ(plenum.numNonextensibleFields(), plenum.outletPort(0u));
  ASSERT_TRUE(plenum.setInletModelObject(inlet));
  ASSERT_TRUE(plenum.setOutletModelObject(0u, firstOutlet));
  ASSERT_TRUE(plenum.setOutletModelObject(1u, secondOutlet));
  ASSERT_TRUE(plenum.inletModelObject());
  EXPECT_EQ(inlet, plenum.inletModelObject()->cast<Node>());
  ASSERT_EQ(2u, plenum.outletModelObjects().size());
  EXPECT_EQ(firstOutlet, plenum.outletModelObjects()[0].cast<Node>());
  EXPECT_EQ(secondOutlet, plenum.outletModelObjects()[1].cast<Node>());

  plenum.removePortForBranch(0u);
  ASSERT_EQ(1u, plenum.outletModelObjects().size());
  EXPECT_EQ(secondOutlet, plenum.outletModelObjects()[0].cast<Node>());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());

  plenum.resetThermalZone();
  EXPECT_FALSE(plenum.thermalZone());
  EXPECT_FALSE(plenum.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneNodeName));
}

TEST_F(EPModelFixture, AirLoopHVACSupplyPlenum_AddToZoneBranchesRegistersSupplyPath) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);
  AirLoopHVACSupplyPlenum plenum(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  const auto originalSplitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  ASSERT_EQ(2u, originalSplitterOutlets.size());
  auto firstBranchNode = originalSplitterOutlets[0].cast<Node>();
  auto secondBranchNode = originalSplitterOutlets[1].cast<Node>();

  ASSERT_TRUE(plenum.setThermalZone(plenumZone));
  ASSERT_TRUE(plenum.addToNode(firstBranchNode));
  EXPECT_FALSE(plenum.addToNode(firstBranchNode));
  ASSERT_TRUE(plenum.addToNode(secondBranchNode));

  ASSERT_TRUE(plenum.inletModelObject());
  ASSERT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(*plenum.inletModelObject(), airLoop.zoneSplitter().outletModelObjects()[0]);
  ASSERT_EQ(2u, plenum.outletModelObjects().size());
  EXPECT_EQ(firstBranchNode, plenum.outletModelObjects()[0]);
  EXPECT_EQ(secondBranchNode, plenum.outletModelObjects()[1]);

  const auto supplyPaths = model.getConcreteModelObjects<AirLoopHVACSupplyPath>();
  ASSERT_EQ(1u, supplyPaths.size());
  const auto supplyPathComponents = supplyPaths[0].components();
  ASSERT_EQ(2u, supplyPathComponents.size());
  EXPECT_EQ(airLoop.zoneSplitter(), supplyPathComponents[0].cast<AirLoopHVACZoneSplitter>());
  EXPECT_EQ(plenum, supplyPathComponents[1].cast<AirLoopHVACSupplyPlenum>());

  const auto zones = airLoop.thermalZones();
  ASSERT_EQ(2u, zones.size());
  EXPECT_NE(std::ranges::find(zones, firstZone), zones.end());
  EXPECT_NE(std::ranges::find(zones, secondZone), zones.end());
  ASSERT_EQ(1u, airLoop.demandComponents(AirLoopHVACSupplyPlenum::iddObjectType()).size());
  const auto demandComponents = airLoop.demandComponents();
  const auto plenumPosition = std::ranges::find(demandComponents, plenum.cast<ModelObject>());
  ASSERT_NE(plenumPosition, demandComponents.end());
  EXPECT_LT(plenumPosition, std::ranges::find(demandComponents, firstZone.cast<ModelObject>()));
  EXPECT_LT(plenumPosition, std::ranges::find(demandComponents, secondZone.cast<ModelObject>()));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, plenum.outletModelObjects().size());
  EXPECT_EQ(2u, airLoop.thermalZones().size());
}

TEST_F(EPModelFixture, ThermalZone_SetAndRemoveSupplyPlenumPreservesOtherZoneBranches) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(secondZone.setSupplyPlenum(plenumZone));
  EXPECT_TRUE(firstZone.setSupplyPlenum(plenumZone));
  EXPECT_FALSE(firstZone.setSupplyPlenum(secondZone));

  auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  EXPECT_EQ(2u, plenums[0].outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, airLoop.thermalZones().size());

  firstZone.removeSupplyPlenum();
  plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  EXPECT_EQ(1u, plenums[0].outletModelObjects().size());
  EXPECT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, airLoop.thermalZones().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirLoopHVACSupplyPlenum::iddObjectType()).size());

  secondZone.removeSupplyPlenum();
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  EXPECT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, airLoop.thermalZones().size());
  EXPECT_TRUE(airLoop.demandComponents(AirLoopHVACSupplyPlenum::iddObjectType()).empty());

  const auto supplyPaths = model.getConcreteModelObjects<AirLoopHVACSupplyPath>();
  ASSERT_EQ(1u, supplyPaths.size());
  const auto components = supplyPaths[0].components();
  ASSERT_EQ(1u, components.size());
  EXPECT_EQ(airLoop.zoneSplitter(), components[0].cast<AirLoopHVACZoneSplitter>());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(2u, airLoop.thermalZones().size());
}
