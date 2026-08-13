/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <set>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirTerminalDualDuctConstantVolume.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Splitter/Splitter.hpp"
#include "../Splitter/Splitter_Impl.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVHeatAndCoolReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVNoReheat.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <utilities/idd/AirLoopHVAC_SupplyPlenum_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>

using namespace openstudio::epmodel;

namespace {
template <typename TerminalFactory>
void expectCrossedSupplyPlenumBranchRemoval(TerminalFactory makeTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  auto firstTerminal = makeTerminal(model);
  auto secondTerminal = makeTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(secondZone.setSupplyPlenum(plenumZone));
  firstZone.removeSupplyPlenum();

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  ASSERT_EQ(1u, plenums.front().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());
  ASSERT_TRUE(plenums.front().inletModelObject());
  ASSERT_TRUE(secondTerminal.inletModelObject());
  ASSERT_TRUE(secondZone.returnAirModelObject());
  EXPECT_EQ(plenums.front().inletModelObject()->handle(), airLoop.zoneSplitter().outletModelObjects()[0].handle());
  EXPECT_EQ(secondTerminal.inletModelObject()->handle(), plenums.front().outletModelObjects()[0].handle());
  EXPECT_EQ(secondZone.returnAirModelObject()->handle(), airLoop.zoneMixer().inletModelObjects()[1].handle());

  const auto firstTerminalHandle = firstTerminal.handle();
  const auto secondTerminalHandle = secondTerminal.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(secondZone));
  EXPECT_TRUE(model.getObject(firstTerminalHandle));
  EXPECT_FALSE(model.getObject(secondTerminalHandle));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(firstZone, airLoop.thermalZones().front());
  EXPECT_EQ(0u, model.canonicalize().errorCount);
}

template <typename TerminalFactory>
void expectSupplyPlenumRemovalRejectsMalformedWaterBranch(TerminalFactory makeTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  CoilHeatingWater waterCoil(model);
  CoilHeatingWater neighboringCoil(model);
  auto terminal = makeTerminal(model, waterCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(neighboringCoil));
  ASSERT_TRUE(zone.setSupplyPlenum(plenumZone));
  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  const auto plenumHandle = plenums.front().handle();
  const auto plenumInletBefore = plenums.front().inletModelObject();
  ASSERT_TRUE(plenumInletBefore);
  const auto plenumInletHandle = plenumInletBefore->handle();
  const auto plenumOutletsBefore = plenums.front().outletModelObjects();
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto terminalInletBefore = terminal.inletModelObject();
  const auto terminalOutletBefore = terminal.outletModelObject();
  ASSERT_TRUE(terminalInletBefore);
  ASSERT_TRUE(terminalOutletBefore);
  const auto terminalInletHandle = terminalInletBefore->handle();
  const auto terminalOutletHandle = terminalOutletBefore->handle();
  const auto zoneEquipmentBefore = zone.equipment();

  auto waterCoilImpl = waterCoil.getImpl<detail::CoilHeatingWater_Impl>();
  ASSERT_TRUE(waterCoilImpl);
  ASSERT_TRUE(waterCoil.waterOutletModelObject());
  const auto originalWaterOutletHandle = waterCoil.waterOutletModelObject()->handle();
  ASSERT_TRUE(neighboringCoil.waterInletModelObject());
  ASSERT_TRUE(waterCoilImpl->setPointer(waterCoil.waterOutletPort(), neighboringCoil.waterInletModelObject()->handle(), false));
  ASSERT_TRUE(waterCoil.plantLoop());

  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }
  const auto plantComponentsBefore = plantLoop.demandComponents();

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_FALSE(airLoop.removeBranchForZone(zone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  EXPECT_TRUE(model.getObject(plenumHandle));
  const auto remainingPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, remainingPlenums.size());
  ASSERT_TRUE(remainingPlenums.front().inletModelObject());
  EXPECT_EQ(plenumInletHandle, remainingPlenums.front().inletModelObject()->handle());
  EXPECT_EQ(plenumOutletsBefore, remainingPlenums.front().outletModelObjects());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  EXPECT_EQ(terminalOutletHandle, terminal.outletModelObject()->handle());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(waterCoil.handle()));
  ASSERT_TRUE(waterCoil.waterOutletModelObject());
  EXPECT_EQ(neighboringCoil.waterInletModelObject()->handle(), waterCoil.waterOutletModelObject()->handle());
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCoil.plantLoop()->handle());

  ASSERT_TRUE(waterCoilImpl->setPointer(waterCoil.waterOutletPort(), originalWaterOutletHandle, false));
  EXPECT_TRUE(terminal.isRemovable());
  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getObject(waterCoil.handle()));
  EXPECT_TRUE(model.getObject(neighboringCoil.handle()));
}

template <typename TerminalFactory>
void expectSupplyPlenumRemovalRejectsForeignInletReference(TerminalFactory makeTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  auto terminal = makeTerminal(model);
  std::vector<openstudio::Handle> childHandles;
  for (const auto& child : terminal.children()) {
    childHandles.push_back(child.handle());
  }

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(zone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalInletNode = terminal.inletModelObject()->template cast<Node>();
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();

  NodeList foreignNodeList(model);
  auto foreignNodeListImpl = foreignNodeList.getImpl<detail::NodeList_Impl>();
  ASSERT_TRUE(foreignNodeListImpl);
  ASSERT_TRUE(foreignNodeListImpl->addNode(terminalInletNode));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  ASSERT_TRUE(plenums.front().inletModelObject());
  const auto plenumHandle = plenums.front().handle();
  const auto plenumInletHandle = plenums.front().inletModelObject()->handle();
  const auto plenumOutletsBefore = plenums.front().outletModelObjects();
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto zoneEquipmentBefore = zone.equipment();
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_FALSE(airLoop.removeBranchForZone(zone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_TRUE(model.getObject(plenumHandle));
  const auto remainingPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, remainingPlenums.size());
  ASSERT_TRUE(remainingPlenums.front().inletModelObject());
  EXPECT_EQ(plenumInletHandle, remainingPlenums.front().inletModelObject()->handle());
  EXPECT_EQ(plenumOutletsBefore, remainingPlenums.front().outletModelObjects());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminalInletNode.handle(), terminal.inletModelObject()->handle());
  EXPECT_EQ(terminalOutletHandle, terminal.outletModelObject()->handle());
  ASSERT_EQ(1u, foreignNodeList.nodes().size());
  EXPECT_EQ(terminalInletNode.handle(), foreignNodeList.nodes().front().handle());

  ASSERT_TRUE(foreignNodeListImpl->removeNode(terminalInletNode));
  EXPECT_TRUE(terminal.isRemovable());
  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  EXPECT_FALSE(model.getObject(terminal.handle()));
  for (const auto& childHandle : childHandles) {
    EXPECT_FALSE(model.getObject(childHandle));
  }
  EXPECT_TRUE(model.getObject(foreignNodeList.handle()));
}
}  // namespace

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

TEST_F(EPModelFixture, AirLoopHVAC_RemoveBranchForZoneUsesZoneIdentityAcrossSupplyPlenumRows) {
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

  // Moving only the first zone back to the ZoneSplitter deliberately crosses
  // the raw connector order: splitter row 0 now supplies the second zone
  // through the plenum, while mixer row 0 still returns the first zone.
  firstZone.removeSupplyPlenum();
  ASSERT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());

  const auto firstTerminalHandle = firstTerminal.handle();
  const auto secondTerminalHandle = secondTerminal.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(secondZone));

  EXPECT_TRUE(model.getObject(firstTerminalHandle));
  EXPECT_FALSE(model.getObject(secondTerminalHandle));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(firstZone, airLoop.thermalZones().front());
  EXPECT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(firstZone, airLoop.thermalZones().front());
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveCrossedSupplyPlenumBranchWithConstantVolumeReheat) {
  expectCrossedSupplyPlenumBranchRemoval([](Model& model) {
    CoilHeatingElectric reheatCoil(model);
    auto availability = model.alwaysOnDiscreteSchedule();
    return AirTerminalSingleDuctConstantVolumeReheat(model, availability, reheatCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveCrossedSupplyPlenumBranchWithVAVHeatAndCoolReheat) {
  expectCrossedSupplyPlenumBranchRemoval([](Model& model) {
    CoilHeatingElectric reheatCoil(model);
    return AirTerminalSingleDuctVAVHeatAndCoolReheat(model, reheatCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveCrossedSupplyPlenumBranchWithSeriesPIUReheat) {
  expectCrossedSupplyPlenumBranchRemoval([](Model& model) {
    FanSystemModel fan(model);
    CoilHeatingElectric reheatCoil(model);
    return AirTerminalSingleDuctSeriesPIUReheat(model, fan, reheatCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveCrossedSupplyPlenumBranchWithParallelPIUReheat) {
  expectCrossedSupplyPlenumBranchRemoval([](Model& model) {
    FanSystemModel fan(model);
    CoilHeatingElectric reheatCoil(model);
    auto availability = model.alwaysOnDiscreteSchedule();
    return AirTerminalSingleDuctParallelPIUReheat(model, availability, fan, reheatCoil);
  });
}

TEST_F(EPModelFixture, ThermalZone_SetSupplyPlenumSupportsDualDuctLanesIndependently) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  ThermalZone firstPlenumZone(model);
  ThermalZone secondPlenumZone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.inletModelObject(0u));
  ASSERT_TRUE(terminal.inletModelObject(1u));
  const auto firstTerminalInlet = *terminal.inletModelObject(0u);
  const auto secondTerminalInlet = *terminal.inletModelObject(1u);

  const auto splitters = model.getConcreteModelObjects<AirLoopHVACZoneSplitter>();
  ASSERT_EQ(2u, splitters.size());
  boost::optional<AirLoopHVACZoneSplitter> firstSplitter;
  boost::optional<AirLoopHVACZoneSplitter> secondSplitter;
  for (const auto& splitter : splitters) {
    const auto outlets = splitter.outletModelObjects();
    if (std::ranges::find(outlets, firstTerminalInlet) != outlets.end()) {
      firstSplitter = splitter;
    }
    if (std::ranges::find(outlets, secondTerminalInlet) != outlets.end()) {
      secondSplitter = splitter;
    }
  }
  ASSERT_TRUE(firstSplitter);
  ASSERT_TRUE(secondSplitter);
  ASSERT_NE(*firstSplitter, *secondSplitter);
  ASSERT_TRUE(firstSplitter->airLoopHVAC());
  ASSERT_TRUE(secondSplitter->airLoopHVAC());
  EXPECT_EQ(airLoop, *firstSplitter->airLoopHVAC());
  EXPECT_EQ(airLoop, *secondSplitter->airLoopHVAC());

  // Model declares this per-lane API but currently fails lane 1 after leaving
  // an orphan plenum. EPModel preserves the intended public shape while
  // making both independent lane operations transactional.
  ASSERT_TRUE(zone.setSupplyPlenum(firstPlenumZone, 0u));
  ASSERT_TRUE(zone.setSupplyPlenum(secondPlenumZone, 1u));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(2u, plenums.size());
  boost::optional<AirLoopHVACSupplyPlenum> firstPlenum;
  boost::optional<AirLoopHVACSupplyPlenum> secondPlenum;
  for (const auto& plenum : plenums) {
    ASSERT_TRUE(plenum.thermalZone());
    if (*plenum.thermalZone() == firstPlenumZone) {
      firstPlenum = plenum;
    } else if (*plenum.thermalZone() == secondPlenumZone) {
      secondPlenum = plenum;
    }
  }
  ASSERT_TRUE(firstPlenum);
  ASSERT_TRUE(secondPlenum);
  ASSERT_TRUE(firstPlenum->inletModelObject());
  ASSERT_TRUE(secondPlenum->inletModelObject());
  EXPECT_NE(firstPlenum->inletModelObject()->handle(), secondPlenum->inletModelObject()->handle());
  const auto firstPlenumSplitterOutlets = firstSplitter->outletModelObjects();
  const auto secondPlenumSplitterOutlets = secondSplitter->outletModelObjects();
  EXPECT_NE(std::ranges::find(firstPlenumSplitterOutlets, *firstPlenum->inletModelObject()), firstPlenumSplitterOutlets.end());
  EXPECT_NE(std::ranges::find(secondPlenumSplitterOutlets, *secondPlenum->inletModelObject()), secondPlenumSplitterOutlets.end());
  ASSERT_EQ(1u, firstPlenum->outletModelObjects().size());
  ASSERT_EQ(1u, secondPlenum->outletModelObjects().size());
  EXPECT_EQ(firstTerminalInlet, firstPlenum->outletModelObjects().front());
  EXPECT_EQ(secondTerminalInlet, secondPlenum->outletModelObjects().front());
  ASSERT_TRUE(firstPlenum->airLoopHVAC());
  ASSERT_TRUE(secondPlenum->airLoopHVAC());
  EXPECT_EQ(airLoop, *firstPlenum->airLoopHVAC());
  EXPECT_EQ(airLoop, *secondPlenum->airLoopHVAC());

  boost::optional<AirLoopHVACSupplyPath> firstSupplyPath;
  boost::optional<AirLoopHVACSupplyPath> secondSupplyPath;
  for (const auto& supplyPath : model.getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
    const auto components = supplyPath.components();
    if (std::ranges::find(components, firstSplitter->cast<ModelObject>()) != components.end()) {
      firstSupplyPath = supplyPath;
      EXPECT_NE(std::ranges::find(components, firstPlenum->cast<ModelObject>()), components.end());
    }
    if (std::ranges::find(components, secondSplitter->cast<ModelObject>()) != components.end()) {
      secondSupplyPath = supplyPath;
      EXPECT_NE(std::ranges::find(components, secondPlenum->cast<ModelObject>()), components.end());
    }
  }
  ASSERT_TRUE(firstSupplyPath);
  ASSERT_TRUE(secondSupplyPath);
  EXPECT_NE(*firstSupplyPath, *secondSupplyPath);

  const auto firstSplitterOutlets = firstSplitter->outletModelObjects();
  const auto secondSplitterOutlets = secondSplitter->outletModelObjects();
  EXPECT_FALSE(zone.setSupplyPlenum(firstPlenumZone, 1u));
  EXPECT_EQ(firstSplitterOutlets, firstSplitter->outletModelObjects());
  EXPECT_EQ(secondSplitterOutlets, secondSplitter->outletModelObjects());
  EXPECT_EQ(2u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().size());

  zone.removeSupplyPlenum(airLoop, 1u);
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().size());
  EXPECT_EQ(firstPlenumZone, *model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().thermalZone());
  const auto firstLaneAfterSecondRemoval = firstSplitter->outletModelObjects();
  const auto secondLaneAfterSecondRemoval = secondSplitter->outletModelObjects();
  EXPECT_NE(std::ranges::find(firstLaneAfterSecondRemoval, *firstPlenum->inletModelObject()), firstLaneAfterSecondRemoval.end());
  EXPECT_NE(std::ranges::find(secondLaneAfterSecondRemoval, secondTerminalInlet), secondLaneAfterSecondRemoval.end());

  zone.removeSupplyPlenum();
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  const auto firstLaneAfterRemoval = firstSplitter->outletModelObjects();
  const auto secondLaneAfterRemoval = secondSplitter->outletModelObjects();
  EXPECT_NE(std::ranges::find(firstLaneAfterRemoval, firstTerminalInlet), firstLaneAfterRemoval.end());
  EXPECT_NE(std::ranges::find(secondLaneAfterRemoval, secondTerminalInlet), secondLaneAfterRemoval.end());
  EXPECT_EQ(0u, model.canonicalize().errorCount);
}

TEST_F(EPModelFixture, ThermalZone_SetSupplyPlenumRejectsUnknownDualDuctLaneWithoutChangingEitherLane) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto splitters = model.getConcreteModelObjects<AirLoopHVACZoneSplitter>();
  ASSERT_EQ(2u, splitters.size());
  const auto firstLaneBefore = splitters[0].outletModelObjects();
  const auto secondLaneBefore = splitters[1].outletModelObjects();

  EXPECT_FALSE(zone.setSupplyPlenum(plenumZone, 2u));

  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  EXPECT_EQ(firstLaneBefore, splitters[0].outletModelObjects());
  EXPECT_EQ(secondLaneBefore, splitters[1].outletModelObjects());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(zone, airLoop.thermalZones().front());
}

TEST_F(EPModelFixture, ThermalZone_MoveDualDuctSupplyPlenumRejectsMalformedTargetBeforeMutationAndRetries) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone currentPlenumZone(model);
  ThermalZone targetPlenumZone(model);
  AirTerminalDualDuctConstantVolume firstTerminal(model);
  AirTerminalDualDuctConstantVolume secondTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(currentPlenumZone, 0u));
  ASSERT_TRUE(secondZone.setSupplyPlenum(targetPlenumZone, 0u));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(2u, plenums.size());
  auto currentPlenum = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto zone = plenum.thermalZone();
    return zone && (*zone == currentPlenumZone);
  });
  auto targetPlenum = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto zone = plenum.thermalZone();
    return zone && (*zone == targetPlenumZone);
  });
  ASSERT_NE(currentPlenum, plenums.end());
  ASSERT_NE(targetPlenum, plenums.end());

  auto supplyPaths = model.getConcreteModelObjects<AirLoopHVACSupplyPath>();
  ASSERT_EQ(2u, supplyPaths.size());
  auto targetSupplyPath = std::ranges::find_if(supplyPaths, [&](const auto& path) {
    const auto components = path.components();
    return std::ranges::find(components, targetPlenum->cast<ModelObject>()) != components.end();
  });
  ASSERT_NE(targetSupplyPath, supplyPaths.end());
  auto foreignSupplyPath = std::ranges::find_if(supplyPaths, [&](const auto& path) { return path != *targetSupplyPath; });
  ASSERT_NE(foreignSupplyPath, supplyPaths.end());
  auto foreignSupplyPathImpl = foreignSupplyPath->getImpl<detail::AirLoopHVACSupplyPath_Impl>();
  ASSERT_TRUE(foreignSupplyPathImpl);
  ASSERT_TRUE(foreignSupplyPathImpl->addComponent(*targetPlenum));

  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }
  const auto currentOutletsBefore = currentPlenum->outletModelObjects();
  const auto targetOutletsBefore = targetPlenum->outletModelObjects();
  const auto firstLaneBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto supplyPathsBefore = model.getConcreteModelObjects<AirLoopHVACSupplyPath>();
  std::vector<std::vector<ModelObject>> supplyPathComponentsBefore;
  for (const auto& path : supplyPathsBefore) {
    supplyPathComponentsBefore.push_back(path.components());
  }

  EXPECT_FALSE(firstZone.setSupplyPlenum(targetPlenumZone, 0u));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(currentOutletsBefore, currentPlenum->outletModelObjects());
  EXPECT_EQ(targetOutletsBefore, targetPlenum->outletModelObjects());
  EXPECT_EQ(firstLaneBefore, airLoop.zoneSplitter().outletModelObjects());
  const auto supplyPathsAfter = model.getConcreteModelObjects<AirLoopHVACSupplyPath>();
  ASSERT_EQ(supplyPathComponentsBefore.size(), supplyPathsAfter.size());
  for (unsigned i = 0u; i < supplyPathsAfter.size(); ++i) {
    EXPECT_EQ(supplyPathComponentsBefore[i], supplyPathsAfter[i].components());
  }

  ASSERT_TRUE(foreignSupplyPath->removeComponent(*targetPlenum));
  ASSERT_TRUE(firstZone.setSupplyPlenum(targetPlenumZone, 0u));
  const auto remainingPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, remainingPlenums.size());
  ASSERT_TRUE(remainingPlenums.front().thermalZone());
  EXPECT_EQ(targetPlenumZone, *remainingPlenums.front().thermalZone());
  EXPECT_EQ(2u, remainingPlenums.front().outletModelObjects().size());
  EXPECT_EQ(0u, model.canonicalize().errorCount);
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveSupplyPlenumBranchRejectsMalformedPlantBeforeMutation) {
  expectSupplyPlenumRemovalRejectsMalformedWaterBranch([](Model& model, CoilHeatingWater& waterCoil) {
    auto availability = model.alwaysOnDiscreteSchedule();
    return AirTerminalSingleDuctConstantVolumeReheat(model, availability, waterCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveVAVHeatAndCoolSupplyPlenumBranchRejectsMalformedPlantBeforeMutation) {
  expectSupplyPlenumRemovalRejectsMalformedWaterBranch(
    [](Model& model, CoilHeatingWater& waterCoil) { return AirTerminalSingleDuctVAVHeatAndCoolReheat(model, waterCoil); });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveSeriesPIUSupplyPlenumBranchRejectsMalformedPlantBeforeMutation) {
  expectSupplyPlenumRemovalRejectsMalformedWaterBranch([](Model& model, CoilHeatingWater& waterCoil) {
    FanSystemModel fan(model);
    return AirTerminalSingleDuctSeriesPIUReheat(model, fan, waterCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveParallelPIUSupplyPlenumBranchRejectsMalformedPlantBeforeMutation) {
  expectSupplyPlenumRemovalRejectsMalformedWaterBranch([](Model& model, CoilHeatingWater& waterCoil) {
    FanSystemModel fan(model);
    auto availability = model.alwaysOnDiscreteSchedule();
    return AirTerminalSingleDuctParallelPIUReheat(model, availability, fan, waterCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveVAVHeatAndCoolSupplyPlenumBranchRejectsForeignInletReferenceBeforeMutation) {
  expectSupplyPlenumRemovalRejectsForeignInletReference([](Model& model) {
    CoilHeatingElectric reheatCoil(model);
    return AirTerminalSingleDuctVAVHeatAndCoolReheat(model, reheatCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveConstantVolumeSupplyPlenumBranchRejectsForeignInletReferenceBeforeMutation) {
  expectSupplyPlenumRemovalRejectsForeignInletReference([](Model& model) { return AirTerminalSingleDuctConstantVolumeNoReheat(model); });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveVAVSupplyPlenumBranchRejectsForeignInletReferenceBeforeMutation) {
  expectSupplyPlenumRemovalRejectsForeignInletReference([](Model& model) { return AirTerminalSingleDuctVAVNoReheat(model); });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveVAVHeatAndCoolNoReheatSupplyPlenumBranchRejectsForeignInletReferenceBeforeMutation) {
  expectSupplyPlenumRemovalRejectsForeignInletReference([](Model& model) { return AirTerminalSingleDuctVAVHeatAndCoolNoReheat(model); });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveSeriesPIUSupplyPlenumBranchRejectsForeignInletReferenceBeforeMutation) {
  expectSupplyPlenumRemovalRejectsForeignInletReference([](Model& model) {
    FanSystemModel fan(model);
    CoilHeatingElectric reheatCoil(model);
    return AirTerminalSingleDuctSeriesPIUReheat(model, fan, reheatCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveParallelPIUSupplyPlenumBranchRejectsForeignInletReferenceBeforeMutation) {
  expectSupplyPlenumRemovalRejectsForeignInletReference([](Model& model) {
    FanSystemModel fan(model);
    CoilHeatingElectric reheatCoil(model);
    auto availability = model.alwaysOnDiscreteSchedule();
    return AirTerminalSingleDuctParallelPIUReheat(model, availability, fan, reheatCoil);
  });
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveSeriesPIUSharedPlenumBranchRejectsMalformedContainedPathBeforeMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone targetZone(model);
  ThermalZone supplyPlenumZone(model);
  ThermalZone returnPlenumZone(model);
  FanSystemModel firstFan(model);
  FanSystemModel targetFan(model);
  CoilHeatingElectric firstCoil(model);
  CoilHeatingElectric targetCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat firstTerminal(model, firstFan, firstCoil);
  AirTerminalSingleDuctSeriesPIUReheat targetTerminal(model, targetFan, targetCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(targetZone, targetTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(targetZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(firstZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(targetZone.setReturnPlenum(returnPlenumZone));

  const auto supplyPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  const auto returnPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, supplyPlenums.size());
  ASSERT_EQ(1u, returnPlenums.size());
  const auto supplyPlenum = supplyPlenums.front();
  const auto returnPlenum = returnPlenums.front();
  ASSERT_TRUE(supplyPlenum.inletModelObject());
  ASSERT_TRUE(returnPlenum.outletModelObject());
  ASSERT_EQ(2u, supplyPlenum.outletModelObjects().size());
  ASSERT_EQ(2u, returnPlenum.inletModelObjects().size());
  ASSERT_TRUE(firstTerminal.inletModelObject());
  ASSERT_TRUE(firstTerminal.outletModelObject());
  ASSERT_TRUE(firstTerminal.secondaryAirInletNode());
  ASSERT_TRUE(targetTerminal.inletModelObject());
  ASSERT_TRUE(targetTerminal.outletModelObject());
  ASSERT_TRUE(targetTerminal.secondaryAirInletNode());
  ASSERT_TRUE(targetFan.outletModelObject());

  Node wrongFanOutlet(model);
  ASSERT_TRUE(targetFan.setPointer(targetFan.outletPort(), wrongFanOutlet.handle()));

  const auto supplyPlenumInletBefore = supplyPlenum.inletModelObject();
  const auto supplyPlenumOutletsBefore = supplyPlenum.outletModelObjects();
  const auto returnPlenumOutletBefore = returnPlenum.outletModelObject();
  const auto returnPlenumInletsBefore = returnPlenum.inletModelObjects();
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto firstZoneEquipmentBefore = firstZone.equipment();
  const auto targetZoneEquipmentBefore = targetZone.equipment();
  const auto targetExhaustBefore = targetZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  const auto firstTerminalInletBefore = firstTerminal.inletModelObject();
  const auto firstTerminalOutletBefore = firstTerminal.outletModelObject();
  const auto firstSecondaryBefore = firstTerminal.secondaryAirInletNode();
  const auto targetTerminalInletBefore = targetTerminal.inletModelObject();
  const auto targetTerminalOutletBefore = targetTerminal.outletModelObject();
  const auto targetSecondaryBefore = targetTerminal.secondaryAirInletNode();
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(targetTerminal.isRemovable());
  EXPECT_FALSE(targetTerminal.removeFromLoop());
  EXPECT_TRUE(targetTerminal.remove().empty());
  EXPECT_FALSE(airLoop.removeBranchForZone(targetZone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().size());
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().size());
  EXPECT_EQ(supplyPlenum.handle(), model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().handle());
  EXPECT_EQ(returnPlenum.handle(), model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().front().handle());
  ASSERT_TRUE(supplyPlenum.inletModelObject());
  EXPECT_EQ(supplyPlenumInletBefore->handle(), supplyPlenum.inletModelObject()->handle());
  EXPECT_EQ(supplyPlenumOutletsBefore, supplyPlenum.outletModelObjects());
  ASSERT_TRUE(returnPlenum.outletModelObject());
  EXPECT_EQ(returnPlenumOutletBefore->handle(), returnPlenum.outletModelObject()->handle());
  EXPECT_EQ(returnPlenumInletsBefore, returnPlenum.inletModelObjects());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(firstZoneEquipmentBefore, firstZone.equipment());
  EXPECT_EQ(targetZoneEquipmentBefore, targetZone.equipment());
  EXPECT_EQ(targetExhaustBefore, targetZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes());
  ASSERT_TRUE(firstTerminal.inletModelObject());
  ASSERT_TRUE(firstTerminal.outletModelObject());
  ASSERT_TRUE(firstTerminal.secondaryAirInletNode());
  ASSERT_TRUE(targetTerminal.inletModelObject());
  ASSERT_TRUE(targetTerminal.outletModelObject());
  ASSERT_TRUE(targetTerminal.secondaryAirInletNode());
  EXPECT_EQ(firstTerminalInletBefore->handle(), firstTerminal.inletModelObject()->handle());
  EXPECT_EQ(firstTerminalOutletBefore->handle(), firstTerminal.outletModelObject()->handle());
  EXPECT_EQ(firstSecondaryBefore->handle(), firstTerminal.secondaryAirInletNode()->handle());
  EXPECT_EQ(targetTerminalInletBefore->handle(), targetTerminal.inletModelObject()->handle());
  EXPECT_EQ(targetTerminalOutletBefore->handle(), targetTerminal.outletModelObject()->handle());
  EXPECT_EQ(targetSecondaryBefore->handle(), targetTerminal.secondaryAirInletNode()->handle());
  ASSERT_TRUE(targetFan.outletModelObject());
  EXPECT_EQ(wrongFanOutlet.handle(), targetFan.outletModelObject()->handle());
  EXPECT_TRUE(model.getObject(firstFan.handle()));
  EXPECT_TRUE(model.getObject(firstCoil.handle()));
  EXPECT_TRUE(model.getObject(targetFan.handle()));
  EXPECT_TRUE(model.getObject(targetCoil.handle()));
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveParallelPIUSharedPlenumBranchRejectsMalformedContainedPathBeforeMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone targetZone(model);
  ThermalZone supplyPlenumZone(model);
  ThermalZone returnPlenumZone(model);
  FanSystemModel firstFan(model);
  FanSystemModel targetFan(model);
  CoilHeatingElectric firstCoil(model);
  CoilHeatingElectric targetCoil(model);
  auto availability = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctParallelPIUReheat firstTerminal(model, availability, firstFan, firstCoil);
  AirTerminalSingleDuctParallelPIUReheat targetTerminal(model, availability, targetFan, targetCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(targetZone, targetTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(targetZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(firstZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(targetZone.setReturnPlenum(returnPlenumZone));

  const auto supplyPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  const auto returnPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, supplyPlenums.size());
  ASSERT_EQ(1u, returnPlenums.size());
  const auto supplyPlenum = supplyPlenums.front();
  const auto returnPlenum = returnPlenums.front();
  ASSERT_TRUE(supplyPlenum.inletModelObject());
  ASSERT_TRUE(returnPlenum.outletModelObject());
  ASSERT_EQ(2u, supplyPlenum.outletModelObjects().size());
  ASSERT_EQ(2u, returnPlenum.inletModelObjects().size());
  ASSERT_TRUE(targetFan.outletModelObject());

  Node wrongFanOutlet(model);
  ASSERT_TRUE(targetFan.setPointer(targetFan.outletPort(), wrongFanOutlet.handle()));

  const auto supplyPlenumInletBefore = supplyPlenum.inletModelObject();
  const auto supplyPlenumOutletsBefore = supplyPlenum.outletModelObjects();
  const auto returnPlenumOutletBefore = returnPlenum.outletModelObject();
  const auto returnPlenumInletsBefore = returnPlenum.inletModelObjects();
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto firstZoneEquipmentBefore = firstZone.equipment();
  const auto targetZoneEquipmentBefore = targetZone.equipment();
  const auto targetExhaustBefore = targetZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  const auto firstTerminalInletBefore = firstTerminal.inletModelObject();
  const auto firstTerminalOutletBefore = firstTerminal.outletModelObject();
  const auto firstSecondaryBefore = firstTerminal.secondaryAirInletNode();
  const auto targetTerminalInletBefore = targetTerminal.inletModelObject();
  const auto targetTerminalOutletBefore = targetTerminal.outletModelObject();
  const auto targetSecondaryBefore = targetTerminal.secondaryAirInletNode();
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(targetTerminal.isRemovable());
  EXPECT_FALSE(targetTerminal.removeFromLoop());
  EXPECT_TRUE(targetTerminal.remove().empty());
  EXPECT_FALSE(airLoop.removeBranchForZone(targetZone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().size());
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().size());
  EXPECT_EQ(supplyPlenum.handle(), model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().handle());
  EXPECT_EQ(returnPlenum.handle(), model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().front().handle());
  ASSERT_TRUE(supplyPlenum.inletModelObject());
  EXPECT_EQ(supplyPlenumInletBefore->handle(), supplyPlenum.inletModelObject()->handle());
  EXPECT_EQ(supplyPlenumOutletsBefore, supplyPlenum.outletModelObjects());
  ASSERT_TRUE(returnPlenum.outletModelObject());
  EXPECT_EQ(returnPlenumOutletBefore->handle(), returnPlenum.outletModelObject()->handle());
  EXPECT_EQ(returnPlenumInletsBefore, returnPlenum.inletModelObjects());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(firstZoneEquipmentBefore, firstZone.equipment());
  EXPECT_EQ(targetZoneEquipmentBefore, targetZone.equipment());
  EXPECT_EQ(targetExhaustBefore, targetZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes());
  ASSERT_TRUE(firstTerminal.inletModelObject());
  ASSERT_TRUE(firstTerminal.outletModelObject());
  ASSERT_TRUE(firstTerminal.secondaryAirInletNode());
  ASSERT_TRUE(targetTerminal.inletModelObject());
  ASSERT_TRUE(targetTerminal.outletModelObject());
  ASSERT_TRUE(targetTerminal.secondaryAirInletNode());
  EXPECT_EQ(firstTerminalInletBefore->handle(), firstTerminal.inletModelObject()->handle());
  EXPECT_EQ(firstTerminalOutletBefore->handle(), firstTerminal.outletModelObject()->handle());
  EXPECT_EQ(firstSecondaryBefore->handle(), firstTerminal.secondaryAirInletNode()->handle());
  EXPECT_EQ(targetTerminalInletBefore->handle(), targetTerminal.inletModelObject()->handle());
  EXPECT_EQ(targetTerminalOutletBefore->handle(), targetTerminal.outletModelObject()->handle());
  EXPECT_EQ(targetSecondaryBefore->handle(), targetTerminal.secondaryAirInletNode()->handle());
  ASSERT_TRUE(targetFan.outletModelObject());
  EXPECT_EQ(wrongFanOutlet.handle(), targetFan.outletModelObject()->handle());
  EXPECT_TRUE(model.getObject(firstFan.handle()));
  EXPECT_TRUE(model.getObject(firstCoil.handle()));
  EXPECT_TRUE(model.getObject(targetFan.handle()));
  EXPECT_TRUE(model.getObject(targetCoil.handle()));
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveBranchForZonePreservesSharedSupplyAndReturnPlenums) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone supplyPlenumZone(model);
  ThermalZone returnPlenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(secondZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(firstZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(secondZone.setReturnPlenum(returnPlenumZone));

  ASSERT_TRUE(firstTerminal.inletModelObject());
  ASSERT_TRUE(firstTerminal.outletModelObject());
  const auto firstBranchPath =
    airLoop.demandComponents(firstTerminal.inletModelObject()->cast<Node>(), firstTerminal.outletModelObject()->cast<Node>());
  EXPECT_NE(std::ranges::find(firstBranchPath, firstTerminal.cast<ModelObject>()), firstBranchPath.end());
  EXPECT_EQ(std::ranges::find(firstBranchPath, secondTerminal.cast<ModelObject>()), firstBranchPath.end());
  EXPECT_EQ(std::ranges::find(firstBranchPath, secondZone.cast<ModelObject>()), firstBranchPath.end());

  const auto demandInventory = airLoop.demandComponents();
  const auto sharedSupplyPlenum = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().cast<ModelObject>();
  const auto sharedReturnPlenum = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().front().cast<ModelObject>();
  EXPECT_EQ(1u, std::ranges::count(demandInventory, firstTerminal.cast<ModelObject>()));
  EXPECT_EQ(1u, std::ranges::count(demandInventory, secondTerminal.cast<ModelObject>()));
  EXPECT_EQ(1u, std::ranges::count(demandInventory, firstZone.cast<ModelObject>()));
  EXPECT_EQ(1u, std::ranges::count(demandInventory, secondZone.cast<ModelObject>()));
  const auto supplyPlenumPosition = std::ranges::find(demandInventory, sharedSupplyPlenum);
  const auto returnPlenumPosition = std::ranges::find(demandInventory, sharedReturnPlenum);
  ASSERT_NE(supplyPlenumPosition, demandInventory.end());
  ASSERT_NE(returnPlenumPosition, demandInventory.end());
  EXPECT_LT(supplyPlenumPosition, std::ranges::find(demandInventory, firstZone.cast<ModelObject>()));
  EXPECT_LT(supplyPlenumPosition, std::ranges::find(demandInventory, secondZone.cast<ModelObject>()));
  EXPECT_LT(std::ranges::find(demandInventory, firstZone.cast<ModelObject>()), returnPlenumPosition);
  EXPECT_LT(std::ranges::find(demandInventory, secondZone.cast<ModelObject>()), returnPlenumPosition);

  ASSERT_TRUE(secondTerminal.inletModelObject());
  ASSERT_TRUE(secondTerminal.outletModelObject());
  const auto secondTerminalInletHandle = secondTerminal.inletModelObject()->handle();
  const auto secondTerminalOutletHandle = secondTerminal.outletModelObject()->handle();
  auto secondConnections = secondZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(secondConnections);
  ASSERT_EQ(1u, secondConnections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, secondConnections->zoneReturnAirNodes().size());
  const auto secondZoneInletHandle = secondConnections->zoneAirInletNodes().front().handle();
  const auto secondZoneReturnHandle = secondConnections->zoneReturnAirNodes().front().handle();
  auto firstAirDistributionUnit = firstTerminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->zoneHVACAirDistributionUnit();
  auto secondAirDistributionUnit = secondTerminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl>()->zoneHVACAirDistributionUnit();
  ASSERT_TRUE(firstAirDistributionUnit);
  ASSERT_TRUE(secondAirDistributionUnit);
  const auto firstAirDistributionUnitHandle = firstAirDistributionUnit->handle();
  const auto secondAirDistributionUnitHandle = secondAirDistributionUnit->handle();
  ASSERT_TRUE(secondAirDistributionUnit->airTerminal());
  ASSERT_TRUE(secondAirDistributionUnit->outletNode());
  const auto secondAirDistributionUnitTerminalHandle = secondAirDistributionUnit->airTerminal()->handle();
  const auto secondAirDistributionUnitOutletHandle = secondAirDistributionUnit->outletNode()->handle();

  const auto firstTerminalHandle = firstTerminal.handle();
  const auto secondTerminalHandle = secondTerminal.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(firstZone));

  EXPECT_FALSE(model.getObject(firstTerminalHandle));
  EXPECT_FALSE(model.getObject(firstAirDistributionUnitHandle));
  EXPECT_TRUE(model.getObject(secondTerminalHandle));
  EXPECT_TRUE(model.getObject(secondAirDistributionUnitHandle));
  ASSERT_TRUE(secondTerminal.inletModelObject());
  ASSERT_TRUE(secondTerminal.outletModelObject());
  EXPECT_EQ(secondTerminalInletHandle, secondTerminal.inletModelObject()->handle());
  EXPECT_EQ(secondTerminalOutletHandle, secondTerminal.outletModelObject()->handle());
  secondConnections = secondZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(secondConnections);
  ASSERT_EQ(1u, secondConnections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, secondConnections->zoneReturnAirNodes().size());
  EXPECT_EQ(secondZoneInletHandle, secondConnections->zoneAirInletNodes().front().handle());
  EXPECT_EQ(secondZoneReturnHandle, secondConnections->zoneReturnAirNodes().front().handle());
  ASSERT_TRUE(secondAirDistributionUnit->airTerminal());
  ASSERT_TRUE(secondAirDistributionUnit->outletNode());
  EXPECT_EQ(secondAirDistributionUnitTerminalHandle, secondAirDistributionUnit->airTerminal()->handle());
  EXPECT_EQ(secondAirDistributionUnitOutletHandle, secondAirDistributionUnit->outletNode()->handle());
  const auto supplyPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  const auto returnPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, supplyPlenums.size());
  ASSERT_EQ(1u, returnPlenums.size());
  EXPECT_EQ(1u, supplyPlenums.front().outletModelObjects().size());
  EXPECT_EQ(1u, returnPlenums.front().inletModelObjects().size());
  EXPECT_EQ(secondTerminalInletHandle, supplyPlenums.front().outletModelObjects().front().handle());
  EXPECT_EQ(secondZoneReturnHandle, returnPlenums.front().inletModelObjects().front().handle());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(secondZone, airLoop.thermalZones().front());

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(airLoop.removeBranchForZone(secondZone));

  EXPECT_FALSE(model.getObject(secondTerminalHandle));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().empty());
  EXPECT_TRUE(airLoop.thermalZones().empty());
  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(1u, splitterOutlets.size());
  ASSERT_EQ(1u, mixerInlets.size());
  EXPECT_EQ(splitterOutlets.front(), mixerInlets.front());

  report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_TRUE(airLoop.thermalZones().empty());
}

TEST_F(EPModelFixture, AirLoopHVAC_RemovePlenumServedBranchAfterSaveLoad) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-demand-plenum-removal-roundtrip.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone supplyPlenumZone(model);
  ThermalZone returnPlenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);

  ASSERT_TRUE(airLoop.setName("Roundtrip Plenum Air Loop"));
  ASSERT_TRUE(firstZone.setName("Roundtrip First Zone"));
  ASSERT_TRUE(secondZone.setName("Roundtrip Second Zone"));
  ASSERT_TRUE(supplyPlenumZone.setName("Roundtrip Supply Plenum Zone"));
  ASSERT_TRUE(returnPlenumZone.setName("Roundtrip Return Plenum Zone"));
  ASSERT_TRUE(firstTerminal.setName("Roundtrip First Terminal"));
  ASSERT_TRUE(secondTerminal.setName("Roundtrip Second Terminal"));
  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(secondZone.setSupplyPlenum(supplyPlenumZone));
  ASSERT_TRUE(firstZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(secondZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip Plenum Air Loop");
  auto loadedFirstZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip First Zone");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip Second Zone");
  auto loadedFirstTerminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeNoReheat>("Roundtrip First Terminal");
  auto loadedSecondTerminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeNoReheat>("Roundtrip Second Terminal");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedFirstZone);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_TRUE(loadedFirstTerminal);
  ASSERT_TRUE(loadedSecondTerminal);
  ASSERT_TRUE(loadedAirLoop->removeBranchForZone(*loadedSecondZone));

  EXPECT_TRUE(loadedModel->getObject(loadedFirstTerminal->handle()));
  EXPECT_FALSE(loadedModel->getObject(loadedSecondTerminal->handle()));
  ASSERT_EQ(1u, loadedAirLoop->thermalZones().size());
  EXPECT_EQ(*loadedFirstZone, loadedAirLoop->thermalZones().front());
  const auto loadedSupplyPlenums = loadedModel->getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  const auto loadedReturnPlenums = loadedModel->getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, loadedSupplyPlenums.size());
  ASSERT_EQ(1u, loadedReturnPlenums.size());
  EXPECT_EQ(1u, loadedSupplyPlenums.front().outletModelObjects().size());
  EXPECT_EQ(1u, loadedReturnPlenums.front().inletModelObjects().size());
  const auto report = loadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ThermalZone_DualDuctSharedPlenumsPersistAndMutateByLane) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-dual-duct-plenums-roundtrip.idf");
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone firstSupplyPlenumZone(model);
  ThermalZone secondSupplyPlenumZone(model);
  ThermalZone returnPlenumZone(model);
  AirTerminalDualDuctConstantVolume firstTerminal(model);
  AirTerminalDualDuctConstantVolume secondTerminal(model);

  ASSERT_TRUE(airLoop.setName("Dual Duct Plenum Air Loop"));
  ASSERT_TRUE(firstZone.setName("Dual Duct First Zone"));
  ASSERT_TRUE(secondZone.setName("Dual Duct Second Zone"));
  ASSERT_TRUE(firstSupplyPlenumZone.setName("Dual Duct First Supply Plenum Zone"));
  ASSERT_TRUE(secondSupplyPlenumZone.setName("Dual Duct Second Supply Plenum Zone"));
  ASSERT_TRUE(returnPlenumZone.setName("Dual Duct Return Plenum Zone"));
  ASSERT_TRUE(firstTerminal.setName("Dual Duct First Terminal"));
  ASSERT_TRUE(secondTerminal.setName("Dual Duct Second Terminal"));
  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));

  ASSERT_TRUE(firstZone.setSupplyPlenum(firstSupplyPlenumZone, 0u));
  ASSERT_TRUE(secondZone.setSupplyPlenum(firstSupplyPlenumZone, 0u));
  ASSERT_TRUE(firstZone.setSupplyPlenum(secondSupplyPlenumZone, 1u));
  ASSERT_TRUE(secondZone.setSupplyPlenum(secondSupplyPlenumZone, 1u));
  ASSERT_TRUE(firstZone.setReturnPlenum(returnPlenumZone));
  ASSERT_TRUE(secondZone.setReturnPlenum(returnPlenumZone));

  const auto supplyPlenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  const auto returnPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, supplyPlenums.size());
  ASSERT_EQ(1u, returnPlenums.size());
  EXPECT_TRUE(std::ranges::all_of(supplyPlenums, [](const auto& plenum) { return plenum.outletModelObjects().size() == 2u; }));
  EXPECT_EQ(2u, returnPlenums.front().inletModelObjects().size());
  EXPECT_EQ(0u, model.canonicalize().errorCount);
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Dual Duct Plenum Air Loop");
  auto loadedFirstZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Dual Duct First Zone");
  auto loadedSecondZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Dual Duct Second Zone");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedFirstZone);
  ASSERT_TRUE(loadedSecondZone);
  ASSERT_EQ(2u, loadedModel->getConcreteModelObjects<AirLoopHVACSupplyPlenum>().size());
  ASSERT_EQ(1u, loadedModel->getConcreteModelObjects<AirLoopHVACReturnPlenum>().size());

  loadedFirstZone->removeSupplyPlenum(*loadedAirLoop, 1u);
  auto loadedSupplyPlenums = loadedModel->getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(2u, loadedSupplyPlenums.size());
  auto secondDeckPlenum = std::ranges::find_if(loadedSupplyPlenums, [](const auto& plenum) {
    const auto zone = plenum.thermalZone();
    return zone && (zone->nameString() == "Dual Duct Second Supply Plenum Zone");
  });
  ASSERT_NE(secondDeckPlenum, loadedSupplyPlenums.end());
  EXPECT_EQ(1u, secondDeckPlenum->outletModelObjects().size());

  loadedFirstZone->removeSupplyPlenum(*loadedAirLoop, 0u);
  loadedSupplyPlenums = loadedModel->getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(2u, loadedSupplyPlenums.size());
  auto firstDeckPlenum = std::ranges::find_if(loadedSupplyPlenums, [](const auto& plenum) {
    const auto zone = plenum.thermalZone();
    return zone && (zone->nameString() == "Dual Duct First Supply Plenum Zone");
  });
  ASSERT_NE(firstDeckPlenum, loadedSupplyPlenums.end());
  EXPECT_EQ(1u, firstDeckPlenum->outletModelObjects().size());

  loadedFirstZone->removeReturnPlenum(*loadedAirLoop);
  const auto loadedReturnPlenums = loadedModel->getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, loadedReturnPlenums.size());
  EXPECT_EQ(1u, loadedReturnPlenums.front().inletModelObjects().size());
  EXPECT_EQ(0u, loadedModel->canonicalize().errorCount);
  const auto loadedZones = loadedAirLoop->thermalZones();
  ASSERT_EQ(2u, loadedZones.size());
  EXPECT_NE(std::ranges::find(loadedZones, *loadedFirstZone), loadedZones.end());
  EXPECT_NE(std::ranges::find(loadedZones, *loadedSecondZone), loadedZones.end());
  openstudio::filesystem::remove(idfPath);
}
