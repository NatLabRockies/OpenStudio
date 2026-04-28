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
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include <utilities/idd/AirTerminal_SingleDuct_ParallelPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include "../StraightComponent/AirTerminalSingleDuctParallelPIUReheat.hpp"

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
  EXPECT_EQ(*outletNode, *mixerInletNode);

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

  auto inletFieldNode =
    terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_ParallelPIU_ReheatFields::SupplyAirInletNodeName);
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
  ASSERT_GE(exhaustNodes.size(), 2u);
  EXPECT_TRUE(std::find(exhaustNodes.begin(), exhaustNodes.end(), secondaryNode) != exhaustNodes.end());
  EXPECT_TRUE(std::find_if(exhaustNodes.begin(), exhaustNodes.end(), [&](const auto& nodeInList) { return nodeInList != secondaryNode; })
              != exhaustNodes.end());
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
