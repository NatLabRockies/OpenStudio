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
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include "../StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctParallelPIUReheat_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctParallelPIUReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_ConstructorAndRelationshipParity) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));

  FanConstantVolume fan(model, availability);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_EQ(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, terminal.secondaryAirInletPort());

  Node secondary(model);
  EXPECT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, secondary.handle()));
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondary.handle(), terminal.secondaryAirInletNode()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_Remove_DisconnectedDeletesOwnedFanAndReheatCoil) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);
  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto coilHandle = reheatCoil.handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctParallelPIUReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumPrimaryAirFlowRate(1.25));
  ASSERT_TRUE(terminal.maximumPrimaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, terminal.maximumPrimaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumPrimaryAirFlowRateAutosized());
  terminal.autosizeMaximumPrimaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumPrimaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMaximumSecondaryAirFlowRate(1.10));
  ASSERT_TRUE(terminal.maximumSecondaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.10, terminal.maximumSecondaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumSecondaryAirFlowRateAutosized());
  terminal.autosizeMaximumSecondaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumSecondaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumPrimaryAirFlowFraction(0.42));
  ASSERT_TRUE(terminal.minimumPrimaryAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.42, terminal.minimumPrimaryAirFlowFraction().get());
  EXPECT_FALSE(terminal.isMinimumPrimaryAirFlowFractionAutosized());
  terminal.autosizeMinimumPrimaryAirFlowFraction();
  EXPECT_TRUE(terminal.isMinimumPrimaryAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setFanOnFlowFraction(0.58));
  ASSERT_TRUE(terminal.fanOnFlowFraction());
  EXPECT_DOUBLE_EQ(0.58, terminal.fanOnFlowFraction().get());
  EXPECT_FALSE(terminal.isFanOnFlowFractionAutosized());
  terminal.autosizeFanOnFlowFraction();
  EXPECT_TRUE(terminal.isFanOnFlowFractionAutosized());

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
  EXPECT_FALSE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());
  terminal.resetMinimumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.006));
  EXPECT_DOUBLE_EQ(0.006, terminal.convergenceTolerance());
  EXPECT_FALSE(terminal.isConvergenceToleranceDefaulted());
  terminal.resetConvergenceTolerance();
  EXPECT_TRUE(terminal.isConvergenceToleranceDefaulted());

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

  const auto fanControlTypeValues = AirTerminalSingleDuctParallelPIUReheat::fanControlTypeValues();
  EXPECT_FALSE(fanControlTypeValues.empty());
  EXPECT_TRUE(std::find(fanControlTypeValues.begin(), fanControlTypeValues.end(), "ConstantSpeed") != fanControlTypeValues.end());

  const auto heatingControlTypeValues = AirTerminalSingleDuctParallelPIUReheat::heatingControlTypeValues();
  EXPECT_FALSE(heatingControlTypeValues.empty());
  EXPECT_TRUE(std::find(heatingControlTypeValues.begin(), heatingControlTypeValues.end(), "Staged") != heatingControlTypeValues.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctParallelPIUReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());

  FanConstantVolume fan(model);
  CoilHeatingElectric reheatCoil(model);
  Node secondaryNode(model);
  EXPECT_TRUE(terminal.setFan(fan));
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, secondaryNode.handle()));
  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondaryNode.handle(), terminal.secondaryAirInletNode()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_InvalidComponentValidation) {
  Model model;
  AirTerminalSingleDuctParallelPIUReheat terminal(model);

  FanVariableVolume invalidFan(model);
  FanConstantVolume invalidCoil(model);
  EXPECT_FALSE(terminal.setFan(invalidFan));
  EXPECT_FALSE(terminal.setReheatCoil(invalidCoil));

  Model otherModel;
  FanConstantVolume otherFan(otherModel);
  CoilHeatingGas otherCoil(otherModel);
  EXPECT_FALSE(terminal.setFan(otherFan));
  EXPECT_FALSE(terminal.setReheatCoil(otherCoil));

  FanConstantVolume validFan(model);
  CoilHeatingGas validCoil(model);
  EXPECT_TRUE(terminal.setFan(validFan));
  EXPECT_TRUE(terminal.setReheatCoil(validCoil));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingGas reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

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

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_FanControlCompatibility) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanConstantVolume constantVolumeFan(model, availability);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, constantVolumeFan, reheatCoil);

  EXPECT_FALSE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());

  FanSystemModel systemModelFan(model);
  EXPECT_TRUE(terminal.setFan(systemModelFan));
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  EXPECT_TRUE(terminal.setFan(constantVolumeFan));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_FALSE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_AddToNode_ZoneBranchInsertion_NodeListApproximation) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingGas reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  EXPECT_TRUE(airLoop.addBranchForZone(zone, terminal));

  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());

  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
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
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, mixerInletNode->cast<ModelObject>());

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  auto secondaryNode = terminal.secondaryAirInletNode().get();
  EXPECT_NE(secondaryNode, *inletNode);
  EXPECT_NE(secondaryNode, *outletNode);

  auto persistedInlet = terminal.getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName, true);
  ASSERT_TRUE(persistedInlet);
  EXPECT_EQ(inletNode->nameString(), *persistedInlet);

  auto persistedOutlet = terminal.getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName, true);
  ASSERT_TRUE(persistedOutlet);
  EXPECT_EQ(outletNode->nameString(), *persistedOutlet);

  auto persistedSecondary = terminal.getString(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, true);
  ASSERT_TRUE(persistedSecondary);
  EXPECT_EQ(secondaryNode.nameString(), *persistedSecondary);

  auto inletFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName);
  ASSERT_TRUE(inletFieldNode);
  EXPECT_EQ(*inletNode, *inletFieldNode);

  auto outletFieldNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::OutletNodeName);
  ASSERT_TRUE(outletFieldNode);
  EXPECT_EQ(*outletNode, *outletFieldNode);

  auto secondaryFieldNode =
    terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName);
  ASSERT_TRUE(secondaryFieldNode);
  EXPECT_EQ(secondaryNode, *secondaryFieldNode);

  EXPECT_EQ(AirTerminalSingleDuctParallelPIUReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_EQ(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SecondaryAirInletNodeName, terminal.secondaryAirInletPort());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.handle(), equipment.front().handle());

  ASSERT_EQ(1u, zone.airLoopHVACTerminals().size());
  EXPECT_EQ(terminal.handle(), zone.airLoopHVACTerminals().front().handle());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
  auto exhaustTarget = zoneConnections.getTarget(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
  ASSERT_TRUE(exhaustTarget);
  auto exhaustNodeList = exhaustTarget->optionalCast<NodeList>();
  ASSERT_TRUE(exhaustNodeList);
  const auto exhaustNodes = exhaustNodeList->nodes();
  ASSERT_EQ(1u, exhaustNodes.size());
  EXPECT_TRUE(std::find(exhaustNodes.begin(), exhaustNodes.end(), secondaryNode) != exhaustNodes.end());
  EXPECT_EQ(secondaryNode, exhaustNodes.back());

  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  EXPECT_EQ(airLoop.availabilitySchedule().handle(), fan.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_AddToNode_ZoneBranchInsertion_SyncsConstantVolumeFanSchedule) {
  Model model;
  ScheduleCompact terminalAvailability(model);
  ASSERT_TRUE(terminalAvailability.setToConstantValue(0.4));

  FanConstantVolume fan(model, terminalAvailability);
  CoilHeatingGas reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, terminalAvailability, fan, reheatCoil);

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  EXPECT_TRUE(airLoop.addBranchForZone(zone, terminal));
  EXPECT_EQ(airLoop.availabilitySchedule().handle(), fan.availabilitySchedule().handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_ChildrenOwnership) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(reheatCoil.containingHVACComponent());
  EXPECT_EQ(terminal.handle(), fan.containingHVACComponent()->handle());
  EXPECT_EQ(terminal.handle(), reheatCoil.containingHVACComponent()->handle());

  const auto children = terminal.children();
  EXPECT_NE(std::ranges::find(children, fan.cast<ModelObject>()), children.end());
  EXPECT_NE(std::ranges::find(children, reheatCoil.cast<ModelObject>()), children.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_AddToNode_RejectsAlreadyConnectedTerminal) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingGas reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  EXPECT_FALSE(terminal.addToNode(*branchNode));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_Remove_CleansZoneBranchConnectivity) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);
  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto reheatCoilHandle = reheatCoil.handle();
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

  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(reheatCoilHandle));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());

  const auto exhaustNodesAfter = zoneConnections->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
  EXPECT_FALSE(zone.airLoopHVACTerminal());

  auto splitterOutletAfterRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfterRemoval);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutletAfterRemoval->handle());

  auto mixerInletAfterRemoval = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInletAfterRemoval);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(returnAirObject->handle(), mixerInletAfterRemoval->handle());

  FanSystemModel replacementFan(model);
  CoilHeatingWater replacementCoil(model);
  AirTerminalSingleDuctParallelPIUReheat replacement(model, availability, replacementFan, replacementCoil);
  auto replacementZoneNode = zone.zoneAirNode();
  ASSERT_TRUE(replacement.addToNode(replacementZoneNode));
  ASSERT_TRUE(replacement.secondaryAirInletNode());
  ASSERT_EQ(1u, zone.airLoopHVACTerminals().size());
  EXPECT_EQ(replacement.handle(), zone.airLoopHVACTerminals().front().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_RemoveFromLoop_CleansConnectivityAfterStaleZoneEquipmentRemoval) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  ASSERT_TRUE(zone.removeEquipment(terminal));
  EXPECT_TRUE(zone.equipment().empty());

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();
  ASSERT_TRUE(terminal.inletModelObject());
  const auto inletNodeHandle = terminal.inletModelObject()->handle();

  ASSERT_TRUE(terminal.removeFromLoop());

  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(fan.handle()));
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(reheatCoil.plantLoop());
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));
  ASSERT_TRUE(reheatCoil.containingHVACComponent());
  EXPECT_EQ(terminal.handle(), reheatCoil.containingHVACComponent()->handle());
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(zone.airLoopHVACTerminal());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  const auto exhaustNodesAfter = zoneConnections->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);

  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, *mixerInlet);

  EXPECT_FALSE(terminal.removeFromLoop());

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  ASSERT_EQ(1u, zone.airLoopHVACTerminals().size());
  EXPECT_EQ(terminal.handle(), zone.airLoopHVACTerminals().front().handle());
  EXPECT_TRUE(reheatCoil.plantLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_RemoveFromLoop_CleansPlantBranchWhenTerminalIsNotAirLoopConnected) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  ASSERT_TRUE(reheatCoil.plantLoop());

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(reheatCoil.plantLoop());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_AddToNode_RejectsMismatchedZoneBranchTopology) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingGas reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, availability, fan, reheatCoil);

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));

  Node rogueMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, rogueMixerNode.cast<ModelObject>()));

  auto zoneAirNode = zone.zoneAirNode();
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);

  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  EXPECT_EQ(rogueMixerNode.cast<ModelObject>(), *mixerInlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_TerminalOnlyDirectLifecycle) {
  Model model;
  ScheduleCompact terminalSchedule(model);
  ASSERT_TRUE(terminalSchedule.setToConstantValue(0.25));
  FanSystemModel fan(model);
  ASSERT_TRUE(fan.setAvailabilitySchedule(terminalSchedule));
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, terminalSchedule, fan, reheatCoil);
  AirLoopHVAC airLoop(model);

  auto originalBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(originalBranchObject);
  auto originalBranchNode = originalBranchObject->optionalCast<Node>();
  ASSERT_TRUE(originalBranchNode);
  ASSERT_EQ(*originalBranchObject, *airLoop.zoneMixer().lastInletModelObject());

  ASSERT_TRUE(terminal.addToNode(*originalBranchNode));
  ASSERT_TRUE(terminal.inletModelObject());
  const auto firstInletHandle = terminal.inletModelObject()->handle();
  EXPECT_EQ(originalBranchNode->handle(), terminal.outletModelObject()->handle());
  EXPECT_EQ(firstInletHandle, airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().empty());
  EXPECT_EQ(airLoop.availabilitySchedule().handle(), fan.availabilitySchedule().handle());

  ASSERT_TRUE(terminal.removeFromLoop());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(model.getObject(firstInletHandle));
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_TRUE(model.getObject(fan.handle()));
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));

  ASSERT_TRUE(terminal.addToNode(*originalBranchNode));
  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto coilHandle = reheatCoil.handle();
  EXPECT_FALSE(terminal.remove().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_HighLevelTerminalOnlySecondBranchDoesNotInventZoneState) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  const auto zoneEquipmentBefore = zone.equipment();

  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(0.5));
  FanConstantVolume fan(model, schedule);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, schedule, fan, reheatCoil);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminal.inletModelObject()->handle(), airLoop.zoneSplitter().outletModelObject(1u)->handle());
  EXPECT_EQ(terminal.outletModelObject()->handle(), airLoop.zoneMixer().inletModelObject(1u)->handle());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_TRUE(zone.airLoopHVACTerminals().empty());

  ASSERT_TRUE(terminal.removeFromLoop());
  EXPECT_FALSE(reheatCoil.plantLoop());
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));
  auto secondSplitterOutlet = airLoop.zoneSplitter().outletModelObject(1u);
  auto secondMixerInlet = airLoop.zoneMixer().inletModelObject(1u);
  ASSERT_TRUE(secondSplitterOutlet);
  ASSERT_TRUE(secondMixerInlet);
  EXPECT_EQ(*secondSplitterOutlet, *secondMixerInlet);
  EXPECT_TRUE(model.getObject(terminal.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_AddToNodeFailureIsAtomicAndRetryable) {
  Model model;
  ScheduleCompact terminalSchedule(model);
  ASSERT_TRUE(terminalSchedule.setToConstantValue(0.2));
  FanSystemModel fan(model);
  ASSERT_TRUE(fan.setAvailabilitySchedule(terminalSchedule));
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, terminalSchedule, fan, reheatCoil);
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));
  const auto originalADUOutletRaw = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();
  auto zoneConnections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  Node preexistingInletNode(model);
  ASSERT_TRUE(preexistingInletNode.setName(zoneAirNode.nameString() + " - " + terminal.nameString() + " Inlet Node"));
  Node preexistingSecondaryNode(model);
  ASSERT_TRUE(preexistingSecondaryNode.setName(zoneAirNode.nameString() + " - " + terminal.nameString() + " Secondary Air Inlet Node"));
  const auto exhaustNodesBefore = zoneConnections->zoneAirExhaustNodes();
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();
  const auto fanScheduleBefore = fan.availabilitySchedule();

  auto impl = terminal.getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>();
  ASSERT_TRUE(impl);
  EXPECT_FALSE(impl->addToNode(zoneAirNode, detail::AirTerminalSingleDuctParallelPIUReheat_Impl::AddToNodeFailureStage::AfterTopologyPrepared));

  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_EQ(zoneAirNode.handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(exhaustNodesBefore, zoneConnections->zoneAirExhaustNodes());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_TRUE(model.getObject(preexistingInletNode.handle()));
  EXPECT_TRUE(model.getObject(preexistingSecondaryNode.handle()));
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  const auto restoredADUOutletRaw = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
  EXPECT_EQ(static_cast<bool>(originalADUOutletRaw), static_cast<bool>(restoredADUOutletRaw));
  if (originalADUOutletRaw && restoredADUOutletRaw) {
    EXPECT_EQ(*originalADUOutletRaw, *restoredADUOutletRaw);
  }
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(fanScheduleBefore.handle(), fan.availabilitySchedule().handle());

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  EXPECT_TRUE(terminal.secondaryAirInletNode());
  ASSERT_EQ(1u, zone.airLoopHVACTerminals().size());
  EXPECT_EQ(terminal.handle(), zone.airLoopHVACTerminals().front().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_RemoveBranchForZoneDeletesTerminalAndOwnedTopology) {
  Model model;
  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(1.0));
  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, schedule, fan, reheatCoil);
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto coilHandle = reheatCoil.handle();
  const auto secondaryHandle = terminal.secondaryAirInletNode()->handle();

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_FALSE(model.getObject(secondaryHandle));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_TerminalOnlyFailureRemovesCreatedTopology) {
  Model model;
  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(0.3));
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model, schedule, fan, reheatCoil);
  AirLoopHVAC airLoop(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  auto impl = terminal.getImpl<detail::AirTerminalSingleDuctParallelPIUReheat_Impl>();
  ASSERT_TRUE(impl);
  EXPECT_FALSE(impl->addToNode(*branchNode, detail::AirTerminalSingleDuctParallelPIUReheat_Impl::AddToNodeFailureStage::AfterTopologyPrepared));
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(branchNode->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(branchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());

  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_FALSE(terminal.secondaryAirInletNode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctParallelPIUReheat_MissingRequiredChildrenRejectsInsertionWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctParallelPIUReheat terminal(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  const auto originalBranchHandle = branchNode->handle();
  const auto originalNodeCount = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(terminal.addToNode(*branchNode));
  EXPECT_EQ(originalNodeCount, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  FanSystemModel fan(model);
  ASSERT_TRUE(terminal.setFan(fan));
  const auto nodeCountWithFan = model.getConcreteModelObjects<Node>().size();
  EXPECT_FALSE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_EQ(nodeCountWithFan, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));
}
