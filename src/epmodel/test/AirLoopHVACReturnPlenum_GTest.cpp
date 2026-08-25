/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
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

#include <set>

using namespace openstudio::epmodel;

namespace {

std::set<openstudio::Handle> workspaceHandles(const Model& model) {
  std::set<openstudio::Handle> handles;
  for (const auto& object : model.objects()) {
    handles.insert(object.handle());
  }
  return handles;
}

std::vector<openstudio::Handle> objectHandles(const std::vector<ModelObject>& objects) {
  std::vector<openstudio::Handle> handles;
  handles.reserve(objects.size());
  for (const auto& object : objects) {
    handles.push_back(object.handle());
  }
  return handles;
}

}  // namespace

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

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_AddToNodeRejectsAmbiguousMixerMembershipWithoutMutation) {
  Model model;
  AirLoopHVAC firstAirLoop(model);
  AirLoopHVAC secondAirLoop(model);
  ThermalZone plenumZone(model);
  AirLoopHVACReturnPlenum plenum(model);
  ASSERT_TRUE(plenum.setThermalZone(plenumZone));

  auto sharedNode = firstAirLoop.zoneMixer().inletModelObjects().front().cast<Node>();
  auto secondMixer = secondAirLoop.zoneMixer();
  ASSERT_TRUE(secondMixer.setInletModelObject(0u, sharedNode));
  const auto originalHandles = workspaceHandles(model);
  const auto firstMixerInlets = objectHandles(firstAirLoop.zoneMixer().inletModelObjects());
  const auto secondMixerInlets = objectHandles(secondMixer.inletModelObjects());

  EXPECT_FALSE(plenum.addToNode(sharedNode));
  EXPECT_EQ(originalHandles, workspaceHandles(model));
  EXPECT_EQ(firstMixerInlets, objectHandles(firstAirLoop.zoneMixer().inletModelObjects()));
  EXPECT_EQ(secondMixerInlets, objectHandles(secondMixer.inletModelObjects()));
  EXPECT_FALSE(plenum.outletModelObject());
  EXPECT_TRUE(plenum.inletModelObjects().empty());
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

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumMovesZoneBetweenSharedPlenums) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone movingZone(model);
  ThermalZone oldNeighbor(model);
  ThermalZone targetNeighbor(model);
  ThermalZone oldPlenumZone(model);
  ThermalZone targetPlenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat movingTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat oldNeighborTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat targetNeighborTerminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(movingZone, movingTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(oldNeighbor, oldNeighborTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(targetNeighbor, targetNeighborTerminal));
  const auto movingReturn = movingZone.returnAirModelObject()->cast<Node>();
  const auto oldNeighborReturn = oldNeighbor.returnAirModelObject()->cast<Node>();
  const auto targetNeighborReturn = targetNeighbor.returnAirModelObject()->cast<Node>();
  ASSERT_TRUE(movingZone.setReturnPlenum(oldPlenumZone));
  ASSERT_TRUE(oldNeighbor.setReturnPlenum(oldPlenumZone));
  ASSERT_TRUE(targetNeighbor.setReturnPlenum(targetPlenumZone));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, plenums.size());
  const auto oldPlenumIt = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto zone = plenum.thermalZone();
    return zone && (*zone == oldPlenumZone);
  });
  const auto targetPlenumIt = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto zone = plenum.thermalZone();
    return zone && (*zone == targetPlenumZone);
  });
  ASSERT_NE(plenums.end(), oldPlenumIt);
  ASSERT_NE(plenums.end(), targetPlenumIt);
  auto oldPlenum = *oldPlenumIt;
  auto targetPlenum = *targetPlenumIt;

  const auto handlesBeforeNoOp = workspaceHandles(model);
  const auto mixerBeforeNoOp = objectHandles(airLoop.zoneMixer().inletModelObjects());
  const auto oldInletsBeforeNoOp = objectHandles(oldPlenum.inletModelObjects());
  const auto targetInletsBeforeNoOp = objectHandles(targetPlenum.inletModelObjects());
  ASSERT_TRUE(movingZone.setReturnPlenum(oldPlenumZone));
  EXPECT_EQ(handlesBeforeNoOp, workspaceHandles(model));
  EXPECT_EQ(mixerBeforeNoOp, objectHandles(airLoop.zoneMixer().inletModelObjects()));
  EXPECT_EQ(oldInletsBeforeNoOp, objectHandles(oldPlenum.inletModelObjects()));
  EXPECT_EQ(targetInletsBeforeNoOp, objectHandles(targetPlenum.inletModelObjects()));

  ASSERT_TRUE(movingZone.setReturnPlenum(targetPlenumZone));
  ASSERT_EQ(1u, oldPlenum.inletModelObjects().size());
  EXPECT_EQ(oldNeighborReturn, oldPlenum.inletModelObjects().front());
  const auto targetInlets = targetPlenum.inletModelObjects();
  ASSERT_EQ(2u, targetInlets.size());
  EXPECT_NE(targetInlets.end(), std::ranges::find(targetInlets, movingReturn.cast<ModelObject>()));
  EXPECT_NE(targetInlets.end(), std::ranges::find(targetInlets, targetNeighborReturn.cast<ModelObject>()));
  ASSERT_TRUE(oldPlenum.outletModelObject());
  ASSERT_TRUE(targetPlenum.outletModelObject());
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  EXPECT_NE(mixerInlets.end(), std::ranges::find(mixerInlets, *oldPlenum.outletModelObject()));
  EXPECT_NE(mixerInlets.end(), std::ranges::find(mixerInlets, *targetPlenum.outletModelObject()));
  EXPECT_EQ(3u, airLoop.thermalZones().size());

  const auto oldPlenumHandle = oldPlenum.handle();
  ASSERT_TRUE(oldNeighbor.setReturnPlenum(targetPlenumZone));
  EXPECT_FALSE(model.getObject(oldPlenumHandle));
  const auto finalTargetInlets = targetPlenum.inletModelObjects();
  ASSERT_EQ(3u, finalTargetInlets.size());
  EXPECT_NE(finalTargetInlets.end(), std::ranges::find(finalTargetInlets, movingReturn.cast<ModelObject>()));
  EXPECT_NE(finalTargetInlets.end(), std::ranges::find(finalTargetInlets, oldNeighborReturn.cast<ModelObject>()));
  EXPECT_NE(finalTargetInlets.end(), std::ranges::find(finalTargetInlets, targetNeighborReturn.cast<ModelObject>()));
  ASSERT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());
  EXPECT_EQ(*targetPlenum.outletModelObject(), airLoop.zoneMixer().inletModelObjects().front());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(3u, airLoop.thermalZones().size());
}

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumMovesLastZoneToNewPlenum) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone oldPlenumZone(model);
  ThermalZone targetPlenumZone(model);
  ThermostatSetpointDualSetpoint targetThermostat(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto returnNode = zone.returnAirModelObject()->cast<Node>();
  ASSERT_TRUE(zone.setReturnPlenum(oldPlenumZone));
  ASSERT_TRUE(targetPlenumZone.setThermostatSetpointDualSetpoint(targetThermostat));
  const auto targetSizingHandle = targetPlenumZone.sizingZone().handle();
  const auto oldPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, oldPlenums.size());
  const auto oldPlenumHandle = oldPlenums.front().handle();
  const auto terminalHandle = terminal.handle();

  ASSERT_TRUE(zone.setReturnPlenum(targetPlenumZone));
  EXPECT_FALSE(model.getObject(oldPlenumHandle));
  EXPECT_TRUE(model.getObject(terminalHandle));
  const auto targetPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, targetPlenums.size());
  ASSERT_TRUE(targetPlenums.front().thermalZone());
  EXPECT_EQ(targetPlenumZone, *targetPlenums.front().thermalZone());
  ASSERT_EQ(1u, targetPlenums.front().inletModelObjects().size());
  EXPECT_EQ(returnNode, targetPlenums.front().inletModelObjects().front());
  ASSERT_TRUE(targetPlenums.front().outletModelObject());
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(1u, mixerInlets.size());
  EXPECT_EQ(*targetPlenums.front().outletModelObject(), mixerInlets.front());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(zone, airLoop.thermalZones().front());
  EXPECT_FALSE(targetPlenumZone.thermostatSetpointDualSetpoint());
  EXPECT_FALSE(model.getObject(targetSizingHandle));
  EXPECT_TRUE(model.getObject(targetThermostat.handle()));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(zone, airLoop.thermalZones().front());
}

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumRejectsAmbiguousCurrentPlenumWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone currentPlenumZone(model);
  ThermalZone targetPlenumZone(model);
  ThermostatSetpointDualSetpoint targetThermostat(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto returnNode = zone.returnAirModelObject()->cast<Node>();
  ASSERT_TRUE(zone.setReturnPlenum(currentPlenumZone));
  auto currentPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, currentPlenums.size());
  auto currentPlenum = currentPlenums.front();
  ASSERT_TRUE(currentPlenum.setInletModelObject(currentPlenum.nextBranchIndex(), returnNode));
  ASSERT_EQ(2u, currentPlenum.inletModelObjects().size());
  ASSERT_TRUE(targetPlenumZone.setThermostatSetpointDualSetpoint(targetThermostat));
  ASSERT_TRUE(targetPlenumZone.thermostatSetpointDualSetpoint());

  const auto originalHandles = workspaceHandles(model);
  const auto originalMixer = objectHandles(airLoop.zoneMixer().inletModelObjects());
  const auto originalInlets = objectHandles(currentPlenum.inletModelObjects());
  EXPECT_FALSE(zone.setReturnPlenum(targetPlenumZone));
  EXPECT_EQ(originalHandles, workspaceHandles(model));
  EXPECT_EQ(originalMixer, objectHandles(airLoop.zoneMixer().inletModelObjects()));
  EXPECT_EQ(originalInlets, objectHandles(currentPlenum.inletModelObjects()));
  ASSERT_TRUE(targetPlenumZone.thermostatSetpointDualSetpoint());
  EXPECT_EQ(targetThermostat, *targetPlenumZone.thermostatSetpointDualSetpoint());
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().size());
  EXPECT_EQ(currentPlenum.handle(), model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().front().handle());
}

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumMovesLastPlenumBypassToZoneMixer) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone oldPlenumZone(model);
  ThermalZone targetPlenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto returnNode = zone.returnAirModelObject()->cast<Node>();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(unitary.addToNode(supplyOutletNode));
  ASSERT_TRUE(zone.setReturnPlenum(oldPlenumZone));
  const auto oldPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, oldPlenums.size());
  const auto oldPlenumHandle = oldPlenums.front().handle();
  ASSERT_TRUE(unitary.setPlenumorMixer(oldPlenums.front()));
  const auto bypassNode = unitary.plenumorMixerNode();

  auto zoneMixer = airLoop.zoneMixer();
  ASSERT_TRUE(zoneMixer.setInletModelObject(zoneMixer.nextBranchIndex(), bypassNode));
  const auto malformedHandles = workspaceHandles(model);
  const auto malformedMixerInlets = objectHandles(zoneMixer.inletModelObjects());
  const auto malformedPlenumInlets = objectHandles(oldPlenums.front().inletModelObjects());
  EXPECT_FALSE(zone.setReturnPlenum(targetPlenumZone));
  EXPECT_EQ(malformedHandles, workspaceHandles(model));
  EXPECT_EQ(malformedMixerInlets, objectHandles(zoneMixer.inletModelObjects()));
  EXPECT_EQ(malformedPlenumInlets, objectHandles(oldPlenums.front().inletModelObjects()));
  auto mixerInlets = zoneMixer.inletModelObjects();
  const auto duplicateBypass = std::ranges::find(mixerInlets, bypassNode.cast<ModelObject>());
  ASSERT_NE(mixerInlets.end(), duplicateBypass);
  zoneMixer.removePortForBranch(static_cast<unsigned>(std::distance(mixerInlets.begin(), duplicateBypass)));

  ASSERT_TRUE(zone.setReturnPlenum(targetPlenumZone));
  EXPECT_FALSE(model.getObject(oldPlenumHandle));
  const auto targetPlenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, targetPlenums.size());
  ASSERT_TRUE(targetPlenums.front().thermalZone());
  EXPECT_EQ(targetPlenumZone, *targetPlenums.front().thermalZone());
  ASSERT_EQ(1u, targetPlenums.front().inletModelObjects().size());
  EXPECT_EQ(returnNode, targetPlenums.front().inletModelObjects().front());
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(airLoop.zoneMixer(), unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
  mixerInlets = airLoop.zoneMixer().inletModelObjects();
  EXPECT_NE(mixerInlets.end(), std::ranges::find(mixerInlets, bypassNode.cast<ModelObject>()));
  ASSERT_TRUE(targetPlenums.front().outletModelObject());
  EXPECT_NE(mixerInlets.end(), std::ranges::find(mixerInlets, *targetPlenums.front().outletModelObject()));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(airLoop.zoneMixer(), unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
}

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumUsesTheRequestedAirLoopForMultiLoopZones) {
  Model model;
  AirLoopHVAC firstAirLoop(model);
  AirLoopHVAC secondAirLoop(model);
  AirLoopHVAC foreignAirLoop(model);
  ThermalZone zone(model);
  ThermalZone firstOldPlenumZone(model);
  ThermalZone firstTargetPlenumZone(model);
  ThermalZone secondPlenumZone(model);
  ThermalZone unusedPlenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat firstTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat secondTerminal(model);

  ASSERT_TRUE(firstAirLoop.addBranchForZone(zone, firstTerminal));
  ASSERT_TRUE(secondAirLoop.addBranchForZone(zone, secondTerminal));
  ASSERT_EQ(2u, zone.returnAirModelObjects().size());
  ASSERT_TRUE(zone.setReturnPlenum(firstOldPlenumZone, firstAirLoop));
  ASSERT_TRUE(zone.setReturnPlenum(secondPlenumZone, secondAirLoop));

  auto plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, plenums.size());
  const auto firstOldPlenumIt = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto plenumThermalZone = plenum.thermalZone();
    return plenumThermalZone && (*plenumThermalZone == firstOldPlenumZone);
  });
  const auto secondPlenumIt = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto plenumThermalZone = plenum.thermalZone();
    return plenumThermalZone && (*plenumThermalZone == secondPlenumZone);
  });
  ASSERT_NE(plenums.end(), firstOldPlenumIt);
  ASSERT_NE(plenums.end(), secondPlenumIt);
  auto secondPlenum = *secondPlenumIt;
  const auto firstReturnNode = firstOldPlenumIt->inletModelObjects().front();
  const auto secondReturnNode = secondPlenum.inletModelObjects().front();
  EXPECT_NE(firstReturnNode, secondReturnNode);
  const auto secondPlenumHandle = secondPlenum.handle();
  const auto secondPlenumInlets = objectHandles(secondPlenum.inletModelObjects());
  const auto secondMixerInlets = objectHandles(secondAirLoop.zoneMixer().inletModelObjects());

  ASSERT_TRUE(zone.setReturnPlenum(firstTargetPlenumZone, firstAirLoop));
  plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, plenums.size());
  const auto firstTargetPlenumIt = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto plenumThermalZone = plenum.thermalZone();
    return plenumThermalZone && (*plenumThermalZone == firstTargetPlenumZone);
  });
  ASSERT_NE(plenums.end(), firstTargetPlenumIt);
  ASSERT_EQ(1u, firstTargetPlenumIt->inletModelObjects().size());
  EXPECT_EQ(firstReturnNode, firstTargetPlenumIt->inletModelObjects().front());
  ASSERT_TRUE(model.getObject(secondPlenumHandle));
  EXPECT_EQ(secondPlenumInlets, objectHandles(secondPlenum.inletModelObjects()));
  EXPECT_EQ(secondMixerInlets, objectHandles(secondAirLoop.zoneMixer().inletModelObjects()));

  const auto beforeWrongTarget = workspaceHandles(model);
  const auto firstMixerBeforeWrongTarget = objectHandles(firstAirLoop.zoneMixer().inletModelObjects());
  const auto secondMixerBeforeWrongTarget = objectHandles(secondAirLoop.zoneMixer().inletModelObjects());
  EXPECT_FALSE(zone.setReturnPlenum(secondPlenumZone, firstAirLoop));
  EXPECT_EQ(beforeWrongTarget, workspaceHandles(model));
  EXPECT_EQ(firstMixerBeforeWrongTarget, objectHandles(firstAirLoop.zoneMixer().inletModelObjects()));
  EXPECT_EQ(secondMixerBeforeWrongTarget, objectHandles(secondAirLoop.zoneMixer().inletModelObjects()));

  const auto beforeForeignLoop = workspaceHandles(model);
  EXPECT_FALSE(zone.setReturnPlenum(unusedPlenumZone, foreignAirLoop));
  EXPECT_EQ(beforeForeignLoop, workspaceHandles(model));

  zone.removeReturnPlenum(secondAirLoop);
  EXPECT_FALSE(model.getObject(secondPlenumHandle));
  const auto secondDirectMixerInlets = secondAirLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(1u, secondDirectMixerInlets.size());
  EXPECT_EQ(secondReturnNode, secondDirectMixerInlets.front());
  ASSERT_TRUE(zone.setReturnPlenum(secondPlenumZone, secondAirLoop));
  plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, plenums.size());
  const auto restoredSecondPlenum = std::ranges::find_if(plenums, [&](const auto& plenum) {
    const auto plenumThermalZone = plenum.thermalZone();
    return plenumThermalZone && (*plenumThermalZone == secondPlenumZone);
  });
  ASSERT_NE(plenums.end(), restoredSecondPlenum);
  ASSERT_EQ(1u, restoredSecondPlenum->inletModelObjects().size());
  EXPECT_EQ(secondReturnNode, restoredSecondPlenum->inletModelObjects().front());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(1u, firstAirLoop.thermalZones().size());
  EXPECT_EQ(1u, secondAirLoop.thermalZones().size());
}

TEST_F(EPModelFixture, ThermalZone_SetReturnPlenumReassignsAfterSaveLoad) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-return-plenum-reassignment-roundtrip.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone movingZone(model);
  ThermalZone oldNeighbor(model);
  ThermalZone targetNeighbor(model);
  ThermalZone oldPlenumZone(model);
  ThermalZone targetPlenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat movingTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat oldNeighborTerminal(model);
  AirTerminalSingleDuctConstantVolumeNoReheat targetNeighborTerminal(model);

  ASSERT_TRUE(airLoop.setName("Reassignment Roundtrip Air Loop"));
  ASSERT_TRUE(movingZone.setName("Reassignment Roundtrip Moving Zone"));
  ASSERT_TRUE(oldNeighbor.setName("Reassignment Roundtrip Old Neighbor"));
  ASSERT_TRUE(targetNeighbor.setName("Reassignment Roundtrip Target Neighbor"));
  ASSERT_TRUE(oldPlenumZone.setName("Reassignment Roundtrip Old Plenum Zone"));
  ASSERT_TRUE(targetPlenumZone.setName("Reassignment Roundtrip Target Plenum Zone"));
  ASSERT_TRUE(airLoop.addBranchForZone(movingZone, movingTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(oldNeighbor, oldNeighborTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(targetNeighbor, targetNeighborTerminal));
  ASSERT_TRUE(movingZone.setReturnPlenum(oldPlenumZone));
  ASSERT_TRUE(oldNeighbor.setReturnPlenum(oldPlenumZone));
  ASSERT_TRUE(targetNeighbor.setReturnPlenum(targetPlenumZone));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Reassignment Roundtrip Air Loop");
  auto loadedMovingZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Reassignment Roundtrip Moving Zone");
  auto loadedOldNeighbor = loadedModel->getConcreteModelObjectByName<ThermalZone>("Reassignment Roundtrip Old Neighbor");
  auto loadedTargetNeighbor = loadedModel->getConcreteModelObjectByName<ThermalZone>("Reassignment Roundtrip Target Neighbor");
  auto loadedTargetPlenumZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Reassignment Roundtrip Target Plenum Zone");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedMovingZone);
  ASSERT_TRUE(loadedOldNeighbor);
  ASSERT_TRUE(loadedTargetNeighbor);
  ASSERT_TRUE(loadedTargetPlenumZone);

  ASSERT_TRUE(loadedMovingZone->setReturnPlenum(*loadedTargetPlenumZone, *loadedAirLoop));
  const auto loadedPlenums = loadedModel->getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, loadedPlenums.size());
  const auto loadedOldPlenum = std::ranges::find_if(loadedPlenums, [](const auto& plenum) {
    const auto plenumThermalZone = plenum.thermalZone();
    return plenumThermalZone && (plenumThermalZone->nameString() == "Reassignment Roundtrip Old Plenum Zone");
  });
  const auto loadedTargetPlenum = std::ranges::find_if(loadedPlenums, [](const auto& plenum) {
    const auto plenumThermalZone = plenum.thermalZone();
    return plenumThermalZone && (plenumThermalZone->nameString() == "Reassignment Roundtrip Target Plenum Zone");
  });
  ASSERT_NE(loadedPlenums.end(), loadedOldPlenum);
  ASSERT_NE(loadedPlenums.end(), loadedTargetPlenum);
  EXPECT_EQ(1u, loadedOldPlenum->inletModelObjects().size());
  EXPECT_EQ(2u, loadedTargetPlenum->inletModelObjects().size());
  EXPECT_EQ(3u, loadedAirLoop->thermalZones().size());
  auto report = loadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedAirLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Reassignment Roundtrip Air Loop");
  ASSERT_TRUE(reloadedAirLoop);
  EXPECT_EQ(3u, reloadedAirLoop->thermalZones().size());
  const auto reloadedPlenums = reloadedModel->getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(2u, reloadedPlenums.size());
  EXPECT_EQ(3u, reloadedPlenums[0].inletModelObjects().size() + reloadedPlenums[1].inletModelObjects().size());
  report = reloadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  openstudio::filesystem::remove(idfPath);
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

TEST_F(EPModelFixture, AirLoopHVAC_RemoveBranchForZoneUsesZoneIdentityAcrossReturnPlenumRows) {
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
  ASSERT_TRUE(secondZone.setReturnPlenum(plenumZone));

  // Moving only the first return back to the ZoneMixer deliberately crosses
  // the raw connector order: splitter row 0 supplies the first zone, while
  // mixer row 0 receives the second zone through the plenum.
  firstZone.removeReturnPlenum();
  ASSERT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());

  const auto firstTerminalHandle = firstTerminal.handle();
  const auto secondTerminalHandle = secondTerminal.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(secondZone));

  EXPECT_TRUE(model.getObject(firstTerminalHandle));
  EXPECT_FALSE(model.getObject(secondTerminalHandle));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().empty());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(firstZone, airLoop.thermalZones().front());
  EXPECT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(firstZone, airLoop.thermalZones().front());
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

TEST_F(EPModelFixture, AirLoopHVAC_RemoveLastPlenumServedZonePreservesChangeoverBypassAndDefaultBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(unitary.addToNode(supplyOutletNode));
  ASSERT_TRUE(zone.setReturnPlenum(plenumZone));
  const auto plenums = model.getConcreteModelObjects<AirLoopHVACReturnPlenum>();
  ASSERT_EQ(1u, plenums.size());
  ASSERT_TRUE(unitary.setPlenumorMixer(plenums.front()));
  const auto bypassNode = unitary.plenumorMixerNode();
  const auto terminalHandle = terminal.handle();

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));

  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_TRUE(model.getObject(unitary.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACReturnPlenum>().empty());
  EXPECT_TRUE(airLoop.thermalZones().empty());
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(airLoop.zoneMixer(), unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(1u, splitterOutlets.size());
  ASSERT_EQ(2u, mixerInlets.size());
  EXPECT_NE(std::ranges::find(mixerInlets, bypassNode.cast<ModelObject>()), mixerInlets.end());
  EXPECT_NE(std::ranges::find(mixerInlets, splitterOutlets.front()), mixerInlets.end());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_TRUE(airLoop.thermalZones().empty());
}
