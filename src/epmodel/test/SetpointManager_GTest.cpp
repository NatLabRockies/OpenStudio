/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../SetpointManager/SetpointManagerMixedAir.hpp"
#include "../SetpointManager/SetpointManagerColdest.hpp"
#include "../SetpointManager/SetpointManagerFollowGroundTemperature.hpp"
#include "../SetpointManager/SetpointManagerFollowOutdoorAirTemperature.hpp"
#include "../SetpointManager/SetpointManagerFollowSystemNodeTemperature.hpp"
#include "../SetpointManager/SetpointManagerScheduled.hpp"
#include "../SetpointManager/SetpointManagerScheduled_Impl.hpp"
#include "../SetpointManager/SetpointManagerScheduledDualSetpoint.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneCooling.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneOneStageCooling.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneOneStageHeating.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneHeating.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneReheat.hpp"
#include "../SetpointManager/SetpointManagerWarmest.hpp"
#include "../SetpointManager/SetpointManagerWarmestTemperatureFlow.hpp"
#include "../HVACComponent/ThermalZone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerScheduled_DefaultConstructor) {
  Model model;
  SetpointManagerScheduled spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Scheduled), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerScheduled spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_FALSE(spm.isControlVariableDefaulted());
  EXPECT_FALSE(spm.hasSchedule());

  const auto controlVariableValues = SetpointManagerScheduled::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  const auto controlVariable = controlVariableValues.back();
  ASSERT_TRUE(spm.setControlVariable(controlVariable));

  EXPECT_EQ(controlVariable, spm.controlVariable());
  EXPECT_FALSE(spm.isControlVariableDefaulted());

  spm.resetControlVariable();
  EXPECT_TRUE(spm.isControlVariableDefaulted());
  EXPECT_EQ("", spm.controlVariable());
}

TEST_F(EPModelFixture, SetpointManagerScheduledDualSetpoint_DefaultConstructor) {
  Model model;
  SetpointManagerScheduledDualSetpoint spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Scheduled_DualSetpoint), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerScheduledDualSetpoint_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerScheduledDualSetpoint spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_TRUE(spm.isAllowedOnPlantLoop());

  const auto controlVariableValues = SetpointManagerScheduledDualSetpoint::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  const auto controlVariable = controlVariableValues.front();
  ASSERT_TRUE(spm.setControlVariable(controlVariable));

  EXPECT_EQ(controlVariable, spm.controlVariable());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneCooling_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneCooling spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_Cooling), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneCooling_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneCooling spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSupplyAirTemperature());

  ASSERT_TRUE(spm.setMinimumSupplyAirTemperature(11.5));
  ASSERT_TRUE(spm.setMaximumSupplyAirTemperature(18.75));

  EXPECT_DOUBLE_EQ(11.5, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(18.75, spm.maximumSupplyAirTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageCooling_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneOneStageCooling spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_OneStageCooling), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageCooling_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneOneStageCooling spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.coolingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.coolingStageOffSupplyAirSetpointTemperature());

  const auto controlVariableValues = SetpointManagerSingleZoneOneStageCooling::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  ASSERT_TRUE(spm.setControlVariable(controlVariableValues.front()));

  ASSERT_TRUE(spm.setCoolingStageOnSupplyAirSetpointTemperature(11.5));
  ASSERT_TRUE(spm.setCoolingStageOffSupplyAirSetpointTemperature(18.75));

  EXPECT_DOUBLE_EQ(11.5, spm.coolingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(18.75, spm.coolingStageOffSupplyAirSetpointTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageHeating_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneOneStageHeating spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_OneStageHeating), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneOneStageHeating_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneOneStageHeating spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(99.0, spm.heatingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(-99.0, spm.heatingStageOffSupplyAirSetpointTemperature());

  const auto controlVariableValues = SetpointManagerSingleZoneOneStageHeating::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  ASSERT_TRUE(spm.setControlVariable(controlVariableValues.front()));

  ASSERT_TRUE(spm.setHeatingStageOnSupplyAirSetpointTemperature(41.25));
  ASSERT_TRUE(spm.setHeatingStageOffSupplyAirSetpointTemperature(17.5));

  EXPECT_DOUBLE_EQ(41.25, spm.heatingStageOnSupplyAirSetpointTemperature());
  EXPECT_DOUBLE_EQ(17.5, spm.heatingStageOffSupplyAirSetpointTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneHeating_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneHeating spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_Heating), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneHeating_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneHeating spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSupplyAirTemperature());

  ASSERT_TRUE(spm.setMinimumSupplyAirTemperature(12.5));
  ASSERT_TRUE(spm.setMaximumSupplyAirTemperature(21.25));

  EXPECT_DOUBLE_EQ(12.5, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(21.25, spm.maximumSupplyAirTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneReheat spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_SingleZone_Reheat), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneReheat spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSupplyAirTemperature());

  const auto controlVariableValues = SetpointManagerSingleZoneReheat::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  ASSERT_TRUE(spm.setControlVariable(controlVariableValues.front()));
  ASSERT_TRUE(spm.setMinimumSupplyAirTemperature(14.25));
  ASSERT_TRUE(spm.setMaximumSupplyAirTemperature(22.75));

  EXPECT_DOUBLE_EQ(14.25, spm.minimumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(22.75, spm.maximumSupplyAirTemperature());
}

TEST_F(EPModelFixture, SetpointManagerColdest_DefaultConstructor) {
  Model model;
  SetpointManagerColdest spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Coldest), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerColdest_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerColdest spm(model);

  EXPECT_DOUBLE_EQ(20.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(50.0, spm.maximumSetpointTemperature());
  EXPECT_EQ("MinimumTemperature", spm.strategy());

  ASSERT_TRUE(spm.setMinimumSetpointTemperature(12.5));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(34.75));

  const auto strategyValues = SetpointManagerColdest::strategyValues();
  ASSERT_FALSE(strategyValues.empty());
  const auto strategy = strategyValues.front();
  ASSERT_TRUE(spm.setStrategy(strategy));

  EXPECT_DOUBLE_EQ(12.5, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(34.75, spm.maximumSetpointTemperature());
  EXPECT_EQ(strategy, spm.strategy());
}

TEST_F(EPModelFixture, SetpointManagerWarmest_DefaultConstructor) {
  Model model;
  SetpointManagerWarmest spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Warmest), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerWarmest_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerWarmest spm(model);

  EXPECT_DOUBLE_EQ(12.2, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(15.6, spm.maximumSetpointTemperature());
  EXPECT_EQ("MaximumTemperature", spm.strategy());

  ASSERT_TRUE(spm.setMinimumSetpointTemperature(13.1));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(17.4));

  const auto strategyValues = SetpointManagerWarmest::strategyValues();
  ASSERT_FALSE(strategyValues.empty());
  const auto strategy = strategyValues.front();
  ASSERT_TRUE(spm.setStrategy(strategy));

  EXPECT_DOUBLE_EQ(13.1, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(17.4, spm.maximumSetpointTemperature());
  EXPECT_EQ(strategy, spm.strategy());
}

TEST_F(EPModelFixture, SetpointManagerWarmestTemperatureFlow_DefaultConstructor) {
  Model model;
  SetpointManagerWarmestTemperatureFlow spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_WarmestTemperatureFlow), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerWarmestTemperatureFlow_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerWarmestTemperatureFlow spm(model);

  EXPECT_DOUBLE_EQ(12.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(18.0, spm.maximumSetpointTemperature());
  EXPECT_EQ("TemperatureFirst", spm.strategy());
  EXPECT_DOUBLE_EQ(0.2, spm.minimumTurndownRatio());

  ASSERT_TRUE(spm.setMinimumSetpointTemperature(13.4));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(19.8));
  ASSERT_TRUE(spm.setMinimumTurndownRatio(0.45));

  const auto strategyValues = SetpointManagerWarmestTemperatureFlow::strategyValues();
  ASSERT_FALSE(strategyValues.empty());
  const auto strategy = strategyValues.front();
  ASSERT_TRUE(spm.setStrategy(strategy));

  EXPECT_DOUBLE_EQ(13.4, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(19.8, spm.maximumSetpointTemperature());
  EXPECT_EQ(strategy, spm.strategy());
  EXPECT_DOUBLE_EQ(0.45, spm.minimumTurndownRatio());
}

TEST_F(EPModelFixture, SetpointManagerFollowGroundTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerFollowGroundTemperature spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_FollowGroundTemperature), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerFollowGroundTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerFollowGroundTemperature spm(model);

  EXPECT_EQ("Site:GroundTemperature:BuildingSurface", spm.referenceGroundTemperatureObjectType());
  EXPECT_DOUBLE_EQ(0.0, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(80.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(10.0, spm.minimumSetpointTemperature());

  const auto referenceValues = SetpointManagerFollowGroundTemperature::referenceGroundTemperatureObjectTypeValues();
  ASSERT_FALSE(referenceValues.empty());
  const auto referenceType = referenceValues.front();

  ASSERT_TRUE(spm.setReferenceGroundTemperatureObjectType(referenceType));
  ASSERT_TRUE(spm.setOffsetTemperatureDifference(1.5));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(65.0));
  ASSERT_TRUE(spm.setMinimumSetpointTemperature(12.0));

  EXPECT_EQ(referenceType, spm.referenceGroundTemperatureObjectType());
  EXPECT_DOUBLE_EQ(1.5, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(65.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(12.0, spm.minimumSetpointTemperature());
}

TEST_F(EPModelFixture, SetpointManagerFollowOutdoorAirTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerFollowOutdoorAirTemperature spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_FollowOutdoorAirTemperature), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerFollowOutdoorAirTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerFollowOutdoorAirTemperature spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_EQ("OutdoorAirWetBulb", spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(1.5, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(80.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(6.0, spm.minimumSetpointTemperature());

  ASSERT_TRUE(spm.setControlVariable("MaximumTemperature"));
  ASSERT_TRUE(spm.setReferenceTemperatureType("OutdoorAirDryBulb"));
  ASSERT_TRUE(spm.setOffsetTemperatureDifference(2.25));
  ASSERT_TRUE(spm.setMaximumSetpointTemperature(62.5));
  ASSERT_TRUE(spm.setMinimumSetpointTemperature(11.5));

  EXPECT_EQ("MaximumTemperature", spm.controlVariable());
  EXPECT_EQ("OutdoorAirDryBulb", spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(2.25, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(62.5, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(11.5, spm.minimumSetpointTemperature());

  EXPECT_FALSE(spm.setReferenceTemperatureType("InvalidValue"));
}

TEST_F(EPModelFixture, SetpointManagerFollowSystemNodeTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerFollowSystemNodeTemperature spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_FollowSystemNodeTemperature), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerFollowSystemNodeTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerFollowSystemNodeTemperature spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_EQ("NodeDryBulb", spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(0.0, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(100.0, spm.maximumLimitSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.0, spm.minimumLimitSetpointTemperature());

  const auto controlVariableValues = SetpointManagerFollowSystemNodeTemperature::controlVariableValues();
  ASSERT_FALSE(controlVariableValues.empty());
  const auto referenceTemperatureTypeValues = SetpointManagerFollowSystemNodeTemperature::referenceTemperatureTypeValues();
  ASSERT_FALSE(referenceTemperatureTypeValues.empty());

  const auto controlVariable = controlVariableValues.front();
  const auto referenceTemperatureType = referenceTemperatureTypeValues.front();
  ASSERT_TRUE(spm.setControlVariable(controlVariable));
  ASSERT_TRUE(spm.setReferenceTemperatureType(referenceTemperatureType));
  ASSERT_TRUE(spm.setOffsetTemperatureDifference(2.5));
  ASSERT_TRUE(spm.setMaximumLimitSetpointTemperature(75.0));
  ASSERT_TRUE(spm.setMinimumLimitSetpointTemperature(5.0));

  EXPECT_EQ(controlVariable, spm.controlVariable());
  EXPECT_EQ(referenceTemperatureType, spm.referenceTemperatureType());
  EXPECT_DOUBLE_EQ(2.5, spm.offsetTemperatureDifference());
  EXPECT_DOUBLE_EQ(75.0, spm.maximumLimitSetpointTemperature());
  EXPECT_DOUBLE_EQ(5.0, spm.minimumLimitSetpointTemperature());

  EXPECT_FALSE(spm.setReferenceTemperatureType("InvalidValue"));
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToNodeReplacesSameControlVariable) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto node = airLoop.supplyOutletNode();

  SetpointManagerScheduled first(model);
  SetpointManagerScheduled second(model);

  ASSERT_TRUE(first.addToNode(node));
  ASSERT_TRUE(second.addToNode(node));

  auto scheduledManagers = model.getConcreteModelObjects<SetpointManagerScheduled>();
  ASSERT_EQ(1u, scheduledManagers.size());
  EXPECT_EQ(second, scheduledManagers.front());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  SetpointManagerScheduled spm(model);
  EXPECT_FALSE(spm.addToNode(*outboardOANode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);
  EXPECT_FALSE(spm.addToNode(*outboardReliefNode));
}

TEST_F(EPModelFixture, SetpointManagerMixedAir_AddToNodeSetsReferenceAndFanNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));

  SetpointManagerMixedAir spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  auto expectedInlet = fan.inletModelObject();
  auto expectedOutlet = fan.outletModelObject();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  auto expectedInletNode = expectedInlet->optionalCast<Node>();
  auto expectedOutletNode = expectedOutlet->optionalCast<Node>();
  ASSERT_TRUE(expectedInletNode);
  ASSERT_TRUE(expectedOutletNode);

  auto spmSetpoint = spm.setpointNode();
  ASSERT_TRUE(spmSetpoint);
  EXPECT_EQ(setpointNode, *spmSetpoint);
  auto referenceNode = spm.referenceSetpointNode();
  ASSERT_TRUE(referenceNode);
  EXPECT_EQ(airLoop.supplyOutletNode(), *referenceNode);
  auto fanInletNode = spm.fanInletNode();
  auto fanOutletNode = spm.fanOutletNode();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  EXPECT_EQ(*expectedInletNode, *fanInletNode);
  EXPECT_EQ(*expectedOutletNode, *fanOutletNode);
}

TEST_F(EPModelFixture, SetpointManagerMixedAir_EagerRefreshAfterSupplyTopologyChange) {
  Model model;
  AirLoopHVAC airLoop(model);

  FanConstantVolume upstreamFan(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(upstreamFan.addToNode(supplyInletNode));

  SetpointManagerMixedAir spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  FanConstantVolume downstreamFan(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(downstreamFan.addToNode(supplyOutletNode));

  auto expectedInlet = downstreamFan.inletModelObject();
  auto expectedOutlet = downstreamFan.outletModelObject();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  auto expectedInletNode = expectedInlet->optionalCast<Node>();
  auto expectedOutletNode = expectedOutlet->optionalCast<Node>();
  ASSERT_TRUE(expectedInletNode);
  ASSERT_TRUE(expectedOutletNode);

  auto fanInletNode = spm.fanInletNode();
  auto fanOutletNode = spm.fanOutletNode();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  EXPECT_EQ(*expectedInletNode, *fanInletNode);
  EXPECT_EQ(*expectedOutletNode, *fanOutletNode);
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_AddToNodeSetsControlZoneFromDemandPath) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto demandBranchNode = splitterOutletObject->optionalCast<openstudio::epmodel::Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));

  SetpointManagerSingleZoneReheat spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  auto controlZone = spm.controlZone();
  ASSERT_TRUE(controlZone);
  EXPECT_EQ(zone, *controlZone);
}
