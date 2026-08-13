/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "../Mixer/Mixer.hpp"
#include "../Mixer/Mixer_Impl.hpp"
#include "../ModelObject/AirLoopHVACReturnPath.hpp"
#include "../ModelObject/AirLoopHVACReturnPath_Impl.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint.hpp"

#include <utilities/idd/AirLoopHVAC_ReturnPlenum_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_DefaultConstructor) {
  Model model;
  AirLoopHVACReturnPlenum plenum(model);
  EXPECT_EQ(AirLoopHVACReturnPlenum::iddObjectType(), plenum.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACReturnPlenum plenum(model);

  EXPECT_TRUE(plenum.setName("Main Return Plenum"));
  EXPECT_EQ("Main Return Plenum", plenum.nameString());
}

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_ImplementsMixerAndThermalZoneRelationships) {
  Model model;
  ThermalZone plenumZone(model);
  ThermostatSetpointDualSetpoint thermostat(model);
  AirLoopHVACReturnPlenum plenum(model);
  Node outlet(model);
  Node firstInlet(model);
  Node secondInlet(model);

  ASSERT_TRUE(plenum.optionalCast<Mixer>());
  EXPECT_EQ(openstudio::AirLoopHVAC_ReturnPlenumFields::OutletNodeName, plenum.outletPort());
  EXPECT_EQ(plenum.numNonextensibleFields(), plenum.inletPort(0u));

  ASSERT_TRUE(plenumZone.setThermostatSetpointDualSetpoint(thermostat));
  const auto originalZoneAirNode = plenumZone.zoneAirNode();
  ASSERT_EQ(1u, model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().size());
  ASSERT_EQ(1u, model.getConcreteModelObjects<SizingZone>().size());
  ASSERT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat).size());

  ASSERT_TRUE(plenum.setThermalZone(plenumZone));
  ASSERT_TRUE(plenum.thermalZone());
  EXPECT_EQ(plenumZone, *plenum.thermalZone());
  EXPECT_EQ(originalZoneAirNode, *plenum.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneNodeName));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat).empty());
  EXPECT_TRUE(model.getObject(thermostat.handle()));
  AirLoopHVACReturnPlenum duplicatePlenum(model);
  EXPECT_FALSE(duplicatePlenum.setThermalZone(plenumZone));

  ASSERT_TRUE(plenum.setOutletModelObject(outlet));
  ASSERT_TRUE(plenum.setInletModelObject(0u, firstInlet));
  ASSERT_TRUE(plenum.setInletModelObject(1u, secondInlet));
  ASSERT_TRUE(plenum.outletModelObject());
  EXPECT_EQ(outlet, plenum.outletModelObject()->cast<Node>());
  ASSERT_EQ(2u, plenum.inletModelObjects().size());
  EXPECT_EQ(firstInlet, plenum.inletModelObjects()[0].cast<Node>());
  EXPECT_EQ(secondInlet, plenum.inletModelObjects()[1].cast<Node>());

  plenum.removePortForBranch(0u);
  ASSERT_EQ(1u, plenum.inletModelObjects().size());
  EXPECT_EQ(secondInlet, plenum.inletModelObjects()[0].cast<Node>());

  plenum.resetThermalZone();
  EXPECT_FALSE(plenum.thermalZone());
  EXPECT_FALSE(plenum.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneNodeName));
}

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_AddToZoneMixerInletRegistersReturnPath) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone plenumZone(model);
  AirLoopHVACReturnPlenum plenum(model);
  ASSERT_TRUE(plenum.setThermalZone(plenumZone));

  auto zoneMixer = airLoop.zoneMixer();
  const auto originalInlets = zoneMixer.inletModelObjects();
  ASSERT_EQ(1u, originalInlets.size());
  auto returnNode = originalInlets[0].cast<Node>();
  ASSERT_TRUE(plenum.addToNode(returnNode));
  EXPECT_FALSE(plenum.addToNode(returnNode));

  ASSERT_TRUE(plenum.outletModelObject());
  ASSERT_EQ(1u, plenum.inletModelObjects().size());
  EXPECT_EQ(returnNode, plenum.inletModelObjects()[0].cast<Node>());
  ASSERT_EQ(1u, zoneMixer.inletModelObjects().size());
  EXPECT_EQ(plenum.outletModelObject()->cast<Node>(), zoneMixer.inletModelObjects()[0].cast<Node>());

  const auto returnPaths = model.getConcreteModelObjects<AirLoopHVACReturnPath>();
  ASSERT_EQ(1u, returnPaths.size());
  const auto components = returnPaths[0].components();
  ASSERT_EQ(2u, components.size());
  EXPECT_EQ(plenum, components[0].cast<AirLoopHVACReturnPlenum>());
  EXPECT_EQ(zoneMixer, components[1].cast<AirLoopHVACZoneMixer>());

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_TRUE(model.getConcreteModelObjects<SizingZone>().empty());
  ASSERT_EQ(2u, returnPaths[0].components().size());
  EXPECT_EQ(plenum, returnPaths[0].components()[0].cast<AirLoopHVACReturnPlenum>());
}

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumSharesOnePlenumAcrossZones) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setReturnPlenum(plenumZone));
  ASSERT_TRUE(secondZone.setReturnPlenum(plenumZone, airLoop));
  EXPECT_TRUE(secondZone.setReturnPlenum(plenumZone));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, plenums.size());
  EXPECT_EQ(2u, plenums[0].inletModelObjects().size());
  EXPECT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());
  ASSERT_TRUE(plenums[0].outletModelObject());
  ASSERT_TRUE(airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_EQ(*plenums[0].outletModelObject(), *airLoop.zoneMixer().inletModelObject(0u));

  const auto zones = airLoop.thermalZones();
  ASSERT_EQ(2u, zones.size());
  EXPECT_NE(std::ranges::find(zones, firstZone), zones.end());
  EXPECT_NE(std::ranges::find(zones, secondZone), zones.end());
  EXPECT_EQ(1u, airLoop.demandComponents(AirLoopHVACReturnPlenum::iddObjectType()).size());
  const auto demandComponents = airLoop.demandComponents();
  const auto plenumPosition = std::ranges::find(demandComponents, plenums[0].cast<ModelObject>());
  ASSERT_NE(plenumPosition, demandComponents.end());
  EXPECT_LT(std::ranges::find(demandComponents, firstZone.cast<ModelObject>()), plenumPosition);
  EXPECT_LT(std::ranges::find(demandComponents, secondZone.cast<ModelObject>()), plenumPosition);

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());
  EXPECT_EQ(2u, airLoop.thermalZones().size());
}

TEST_F(EPModelFixture, ThermalZone_RemoveReturnPlenumRestoresDirectZoneReturns) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  const auto firstReturn = firstZone.returnAirModelObject()->cast<Node>();
  const auto secondReturn = secondZone.returnAirModelObject()->cast<Node>();
  ASSERT_TRUE(firstZone.setReturnPlenum(plenumZone));
  ASSERT_TRUE(secondZone.setReturnPlenum(plenumZone));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, plenums.size());
  const auto plenumHandle = plenums[0].handle();
  ASSERT_TRUE(plenums[0].outletModelObject());
  const auto plenumOutlet = plenums[0].outletModelObject()->cast<Node>();

  firstZone.removeReturnPlenum(airLoop);
  ASSERT_TRUE(model.getObject(plenumHandle));
  ASSERT_EQ(1u, plenums[0].inletModelObjects().size());
  EXPECT_EQ(secondReturn, plenums[0].inletModelObjects()[0]);
  auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(2u, mixerInlets.size());
  EXPECT_NE(std::ranges::find(mixerInlets, firstReturn.cast<ModelObject>()), mixerInlets.end());
  EXPECT_NE(std::ranges::find(mixerInlets, plenumOutlet.cast<ModelObject>()), mixerInlets.end());
  EXPECT_EQ(2u, airLoop.thermalZones().size());

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(1u, plenums[0].inletModelObjects().size());
  EXPECT_EQ(2u, airLoop.thermalZones().size());

  firstZone.removeReturnPlenum();
  secondZone.removeReturnPlenum();
  EXPECT_FALSE(model.getObject(plenumHandle));
  EXPECT_FALSE(model.getObject(plenumOutlet.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().empty());
  mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(2u, mixerInlets.size());
  EXPECT_NE(std::ranges::find(mixerInlets, firstReturn.cast<ModelObject>()), mixerInlets.end());
  EXPECT_NE(std::ranges::find(mixerInlets, secondReturn.cast<ModelObject>()), mixerInlets.end());

  const auto returnPaths = model.getConcreteModelObjects<AirLoopHVACReturnPath>();
  ASSERT_EQ(1u, returnPaths.size());
  ASSERT_EQ(1u, returnPaths[0].components().size());
  EXPECT_EQ(airLoop.zoneMixer(), returnPaths[0].components()[0].cast<AirLoopHVACZoneMixer>());

  report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(2u, airLoop.thermalZones().size());
  EXPECT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());
}

TEST_F(EPModelFixture, ThermalZone_RemoveLastReturnPlenumMovesChangeoverBypassToZoneMixer) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto returnNode = zone.returnAirModelObject()->cast<Node>();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(unitary.addToNode(supplyOutletNode));
  ASSERT_TRUE(zone.setReturnPlenum(plenumZone));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, plenums.size());
  ASSERT_TRUE(unitary.setPlenumorMixer(plenums[0]));
  ASSERT_EQ(2u, plenums[0].inletModelObjects().size());

  zone.removeReturnPlenum();
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().empty());
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(airLoop.zoneMixer(), unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(2u, mixerInlets.size());
  EXPECT_NE(std::ranges::find(mixerInlets, returnNode.cast<ModelObject>()), mixerInlets.end());
  EXPECT_NE(std::ranges::find(mixerInlets, unitary.plenumorMixerNode().cast<ModelObject>()), mixerInlets.end());

  const auto returnPaths = model.getConcreteModelObjects<AirLoopHVACReturnPath>();
  ASSERT_EQ(1u, returnPaths.size());
  ASSERT_EQ(1u, returnPaths[0].components().size());
  EXPECT_EQ(airLoop.zoneMixer(), returnPaths[0].components()[0].cast<AirLoopHVACZoneMixer>());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(1u, airLoop.thermalZones().size());
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(airLoop.zoneMixer(), unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
}
