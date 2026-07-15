/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_NoReheat_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirTerminalSingleDuctConstantVolumeNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.maximumAirFlowRate());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_ScheduleConstructor_PreservesProvidedAvailabilitySchedule) {
  Model model;
  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));

  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model, compactSchedule);

  EXPECT_EQ(compactSchedule, terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.maximumAirFlowRate());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AutosizedMaximumAirFlowRate_IsDocumentedTypedStub) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.maximumAirFlowRate());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AvailabilitySchedule_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.handle(), terminal.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName));

  const auto repairedSchedule = terminal.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), repairedSchedule);
  const auto storedSchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedSchedule);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_RejectsNonDemandNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  Node standaloneNode(model);
  Model otherModel;
  Node foreignNode(otherModel);
  auto supplyInletNode = airLoop.supplyInletNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_ResolvesAirLoopHVACRegistersZoneEquipmentAndADUOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto terminalInletObject = terminal.inletModelObject();
  ASSERT_TRUE(terminalInletObject);
  auto terminalInletNode = terminalInletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalInletNode);
  EXPECT_NE(zoneAirNode, *terminalInletNode);

  auto terminalOutletObject = terminal.outletModelObject();
  ASSERT_TRUE(terminalOutletObject);
  auto terminalOutletNode = terminalOutletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalOutletNode);
  EXPECT_EQ(zoneAirNode, *terminalOutletNode);

  const auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zoneAirNode, resolvedOutletNode.get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(terminalInletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();

  Node mismatchedMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_Remove_ReconnectsZoneBranchAndCleansZoneReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto zoneAirNode = zone.zoneAirNode();

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  EXPECT_NE(zoneAirNode, *inletNode);

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);

  ASSERT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_EQ(6u, airLoop.demandComponents().size());
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto zoneAirNode = zone.zoneAirNode();
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
}
