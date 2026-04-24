/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include "../Schedule/ScheduleCompact.hpp"
#include "../StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include <utilities/idd/AirTerminal_SingleDuct_SeriesPIU_Reheat_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.42));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.42, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMaximumPrimaryAirFlowRate(1.05));
  ASSERT_TRUE(terminal.maximumPrimaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.05, terminal.maximumPrimaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumPrimaryAirFlowRateAutosized());
  terminal.autosizeMaximumPrimaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumPrimaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumPrimaryAirFlowFraction(0.39));
  ASSERT_TRUE(terminal.minimumPrimaryAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.39, terminal.minimumPrimaryAirFlowFraction().get());
  EXPECT_FALSE(terminal.isMinimumPrimaryAirFlowFractionAutosized());
  terminal.autosizeMinimumPrimaryAirFlowFraction();
  EXPECT_TRUE(terminal.isMinimumPrimaryAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.004));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.004, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.resetMaximumHotWaterorSteamFlowRate();
  EXPECT_FALSE(terminal.maximumHotWaterorSteamFlowRate());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.0011));
  EXPECT_DOUBLE_EQ(0.0011, terminal.minimumHotWaterorSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.006));
  EXPECT_DOUBLE_EQ(0.006, terminal.convergenceTolerance());

  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  EXPECT_TRUE(terminal.setMinimumFanTurnDownRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, terminal.minimumFanTurnDownRatio());

  EXPECT_EQ("Staged", terminal.heatingControlType());
  EXPECT_TRUE(terminal.setHeatingControlType("Modulated"));
  EXPECT_EQ("Modulated", terminal.heatingControlType());

  EXPECT_TRUE(terminal.setDesignHeatingDischargeAirTemperature(34.0));
  EXPECT_DOUBLE_EQ(34.0, terminal.designHeatingDischargeAirTemperature());

  EXPECT_TRUE(terminal.setHighLimitHeatingDischargeAirTemperature(40.0));
  EXPECT_DOUBLE_EQ(40.0, terminal.highLimitHeatingDischargeAirTemperature());

  const auto fanControlTypeValues = AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues();
  EXPECT_FALSE(fanControlTypeValues.empty());
  EXPECT_TRUE(std::find(fanControlTypeValues.begin(), fanControlTypeValues.end(), "ConstantSpeed") != fanControlTypeValues.end());

  const auto heatingControlTypeValues = AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues();
  EXPECT_FALSE(heatingControlTypeValues.empty());
  EXPECT_TRUE(std::find(heatingControlTypeValues.begin(), heatingControlTypeValues.end(), "Staged") != heatingControlTypeValues.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  EXPECT_FALSE(terminal.availabilitySchedule());

  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());

  FanConstantVolume fan(model);
  CoilHeatingElectric reheatCoil(model);
  Node secondaryNode(model);
  EXPECT_TRUE(terminal.setFan(fan));
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, secondaryNode.handle()));
  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondaryNode.handle(), terminal.secondaryAirInletNode()->handle());

  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_InvalidComponentValidationAndFanControlCompatibility) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  FanVariableVolume variableFan(model);
  EXPECT_TRUE(terminal.setFan(variableFan));
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  FanConstantVolume constantFan(model);
  EXPECT_TRUE(terminal.setFan(constantFan));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_FALSE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());

  Model otherModel;
  FanConstantVolume otherFan(otherModel);
  CoilHeatingElectric otherCoil(otherModel);
  EXPECT_FALSE(terminal.setFan(otherFan));
  EXPECT_FALSE(terminal.setReheatCoil(otherCoil));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_ZoneBranchInsertion_SyncsSecondaryAirAndFanSchedule) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanConstantVolume fan(model, availability);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());

  auto outletNode = terminal.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zone.zoneAirNode(), *outletNode);

  auto inletNode = terminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  EXPECT_NE(*inletNode, *outletNode);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto splitterOutletNode = splitterOutletObject->optionalCast<Node>();
  ASSERT_TRUE(splitterOutletNode);
  EXPECT_EQ(*inletNode, *splitterOutletNode);

  auto mixerInletObject = airLoop.zoneMixer().lastInletModelObject();
  ASSERT_TRUE(mixerInletObject);
  auto mixerInletNode = mixerInletObject->optionalCast<Node>();
  ASSERT_TRUE(mixerInletNode);
  EXPECT_EQ(*outletNode, *mixerInletNode);

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  auto secondaryNode = terminal.secondaryAirInletNode().get();
  EXPECT_NE(secondaryNode, *inletNode);
  EXPECT_NE(secondaryNode, *outletNode);

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.handle(), equipment.front().handle());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  const auto exhaustNodes = zoneConnections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find(exhaustNodes, secondaryNode), exhaustNodes.end());

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zone.zoneAirNode(), resolvedOutletNode.get());
  EXPECT_EQ(airLoop.availabilitySchedule().handle(), fan.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_RejectsMismatchedZoneTopology) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  Node mismatchedMixerNode(model);

  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode));
  EXPECT_FALSE(terminal.addToNode(zone.zoneAirNode()));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutlet->handle());
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  EXPECT_EQ(mismatchedMixerNode.handle(), mixerInlet->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_RejectsAlreadyConnectedTerminal) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto inletNodeHandle = terminal.inletModelObject()->handle();
  const auto outletNodeHandle = terminal.outletModelObject()->handle();
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();

  const auto equipmentBefore = zone.equipment();
  ASSERT_EQ(1u, equipmentBefore.size());

  EXPECT_FALSE(terminal.addToNode(zone.zoneAirNode()));
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletNodeHandle, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletNodeHandle, terminal.outletModelObject()->handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondaryNodeHandle, terminal.secondaryAirInletNode()->handle());
  const auto equipmentAfter = zone.equipment();
  ASSERT_EQ(1u, equipmentAfter.size());
  EXPECT_EQ(terminal.handle(), equipmentAfter.front().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Remove_CleansZoneBranchConnectivity) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();
  ASSERT_TRUE(terminal.inletModelObject());
  const auto inletNodeHandle = terminal.inletModelObject()->handle();
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  const auto exhaustNodesBefore = zoneConnections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find_if(exhaustNodesBefore, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }),
            exhaustNodesBefore.end());

  auto splitterOutletBeforeRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBeforeRemoval);
  EXPECT_EQ(inletNodeHandle, splitterOutletBeforeRemoval->handle());

  const auto containsObject = [](const std::vector<ModelObject>& objects, const ModelObject& object) {
    return std::find(objects.begin(), objects.end(), object) != objects.end();
  };
  EXPECT_TRUE(containsObject(plantLoop.demandComponents(), reheatCoil.cast<ModelObject>()));

  terminal.remove();

  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_FALSE(fan.containingHVACComponent());
  EXPECT_FALSE(reheatCoil.containingHVACComponent());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(containsObject(plantLoop.demandComponents(), reheatCoil.cast<ModelObject>()));

  const auto exhaustNodesAfter = zoneConnections->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
  EXPECT_FALSE(zone.airLoopHVACTerminal());

  auto splitterOutletAfterRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfterRemoval);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutletAfterRemoval->handle());

  auto mixerInletAfterRemoval = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInletAfterRemoval);
  EXPECT_EQ(zone.zoneAirNode().handle(), mixerInletAfterRemoval->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Remove_ClearsPersistedADUFields) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  terminal.remove();

  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  auto persistedADUType = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, true);
  ASSERT_TRUE(persistedADUType);
  EXPECT_TRUE(persistedADUType->empty());
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveFromLoop_CleansSecondaryNodeWithoutZoneRegistrationOrZoneOutlet) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();

  ASSERT_TRUE(zone.removeEquipment(terminal));
  Node detachedOutletNode(model);
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName, detachedOutletNode.handle()));

  ASSERT_TRUE(terminal.removeFromLoop());

  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  const auto exhaustNodesAfter = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveFromLoop_RecoversStaleZoneRegistration) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();
  ASSERT_TRUE(terminal.inletModelObject());
  const auto inletNodeHandle = terminal.inletModelObject()->handle();

  ASSERT_TRUE(zone.removeEquipment(terminal));
  EXPECT_TRUE(zone.equipment().empty());

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutlet->handle());

  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  EXPECT_EQ(zone.zoneAirNode().handle(), mixerInlet->handle());

  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(reheatCoil.plantLoop());
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_FALSE(terminal.airLoopHVAC());

  const auto exhaustNodesAfter = zoneImpl->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
}
