/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../SetpointManager/SetpointManagerOutdoorAirPretreat.hpp"
#include "../SetpointManager/SetpointManagerOutdoorAirPretreat_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerOutdoorAirPretreat_DefaultConstructor) {
  Model model;
  SetpointManagerOutdoorAirPretreat spm(model);
  EXPECT_EQ(SetpointManagerOutdoorAirPretreat::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirPretreat_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerOutdoorAirPretreat spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerOutdoorAirPretreat::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.00001, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(1.0, spm.maximumSetpointHumidityRatio());

  EXPECT_TRUE(spm.isMinimumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointHumidityRatioDefaulted());

  EXPECT_TRUE(spm.setControlVariable("HumidityRatio"));
  EXPECT_TRUE(spm.setMinimumSetpointTemperature(-12.5));
  EXPECT_TRUE(spm.setMaximumSetpointTemperature(42.75));
  EXPECT_TRUE(spm.setMinimumSetpointHumidityRatio(0.0015));
  EXPECT_TRUE(spm.setMaximumSetpointHumidityRatio(0.45));

  EXPECT_EQ("HumidityRatio", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-12.5, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(42.75, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.0015, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.45, spm.maximumSetpointHumidityRatio());

  EXPECT_FALSE(spm.isMinimumSetpointTemperatureDefaulted());
  EXPECT_FALSE(spm.isMaximumSetpointTemperatureDefaulted());
  EXPECT_FALSE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_FALSE(spm.isMaximumSetpointHumidityRatioDefaulted());

  spm.resetControlVariable();
  spm.resetMinimumSetpointTemperature();
  spm.resetMaximumSetpointTemperature();
  spm.resetMinimumSetpointHumidityRatio();
  spm.resetMaximumSetpointHumidityRatio();

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.00001, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(1.0, spm.maximumSetpointHumidityRatio());

  EXPECT_TRUE(spm.isMinimumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointHumidityRatioDefaulted());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirPretreat_StreamNodeRelationships) {
  Model model;
  SetpointManagerOutdoorAirPretreat spm(model);
  Node reference(model);
  Node mixed(model);
  Node outdoor(model);
  Node returnAir(model);
  ASSERT_TRUE(reference.setName("Pretreat Reference Node"));
  ASSERT_TRUE(mixed.setName("Pretreat Mixed Air Node"));
  ASSERT_TRUE(outdoor.setName("Pretreat Outdoor Air Node"));
  ASSERT_TRUE(returnAir.setName("Pretreat Return Air Node"));

  EXPECT_FALSE(spm.referenceSetpointNode());
  EXPECT_FALSE(spm.mixedAirStreamNode());
  EXPECT_FALSE(spm.outdoorAirStreamNode());
  EXPECT_FALSE(spm.returnAirStreamNode());
  ASSERT_TRUE(spm.setReferenceSetpointNode(reference));
  ASSERT_TRUE(spm.setMixedAirStreamNode(mixed));
  ASSERT_TRUE(spm.setOutdoorAirStreamNode(outdoor));
  ASSERT_TRUE(spm.setReturnAirStreamNode(returnAir));
  EXPECT_EQ(reference, spm.referenceSetpointNode().get());
  EXPECT_EQ(mixed, spm.mixedAirStreamNode().get());
  EXPECT_EQ(outdoor, spm.outdoorAirStreamNode().get());
  EXPECT_EQ(returnAir, spm.returnAirStreamNode().get());

  Model otherModel;
  Node foreignNode(otherModel);
  EXPECT_FALSE(spm.setReferenceSetpointNode(foreignNode));
  EXPECT_EQ(reference, spm.referenceSetpointNode().get());

  ASSERT_TRUE(reference.setName("Renamed Pretreat Reference Node"));
  ASSERT_TRUE(mixed.setName("Renamed Pretreat Mixed Air Node"));
  ASSERT_TRUE(outdoor.setName("Renamed Pretreat Outdoor Air Node"));
  ASSERT_TRUE(returnAir.setName("Renamed Pretreat Return Air Node"));
  EXPECT_EQ("Renamed Pretreat Reference Node", spm.referenceSetpointNode()->nameString());
  EXPECT_EQ("Renamed Pretreat Mixed Air Node", spm.mixedAirStreamNode()->nameString());
  EXPECT_EQ("Renamed Pretreat Outdoor Air Node", spm.outdoorAirStreamNode()->nameString());
  EXPECT_EQ("Renamed Pretreat Return Air Node", spm.returnAirStreamNode()->nameString());

  spm.resetReferenceSetpointNode();
  spm.resetMixedAirStreamNode();
  spm.resetOutdoorAirStreamNode();
  spm.resetReturnAirStreamNode();
  EXPECT_FALSE(spm.referenceSetpointNode());
  EXPECT_FALSE(spm.mixedAirStreamNode());
  EXPECT_FALSE(spm.outdoorAirStreamNode());
  EXPECT_FALSE(spm.returnAirStreamNode());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirPretreat_OutdoorAirHeatRecoveryRelationshipsSurviveReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-outdoor-air-pretreat-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  HeatExchangerDesiccantBalancedFlow heatExchanger(model);
  SetpointManagerOutdoorAirPretreat spm(model);
  ASSERT_TRUE(oaSystem.setName("Pretreat OA System"));
  ASSERT_TRUE(heatExchanger.setName("Pretreat Heat Exchanger"));
  ASSERT_TRUE(spm.setName("Pretreat Setpoint Manager"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(heatExchanger.addToNode(*outboardOANode));

  auto mixedNode = oaSystem.mixedAirModelObject()->cast<Node>();
  auto outdoorNode = *oaSystem.outboardOANode();
  auto returnNode = oaSystem.returnAirModelObject()->cast<Node>();
  auto heatExchangerOutlet = heatExchanger.primaryAirOutletModelObject()->cast<Node>();
  ASSERT_TRUE(spm.setReferenceSetpointNode(mixedNode));
  ASSERT_TRUE(spm.setMixedAirStreamNode(mixedNode));
  ASSERT_TRUE(spm.setOutdoorAirStreamNode(outdoorNode));
  ASSERT_TRUE(spm.setReturnAirStreamNode(returnNode));
  ASSERT_TRUE(spm.addToNode(heatExchangerOutlet));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Pretreat OA System");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerDesiccantBalancedFlow>("Pretreat Heat Exchanger");
  auto loadedSPM = loadedModel->getConcreteModelObjectByName<SetpointManagerOutdoorAirPretreat>("Pretreat Setpoint Manager");
  ASSERT_TRUE(loadedOA);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedSPM);
  ASSERT_TRUE(loadedSPM->referenceSetpointNode());
  ASSERT_TRUE(loadedSPM->mixedAirStreamNode());
  ASSERT_TRUE(loadedSPM->outdoorAirStreamNode());
  ASSERT_TRUE(loadedSPM->returnAirStreamNode());
  ASSERT_TRUE(loadedSPM->setpointNode());
  EXPECT_EQ(loadedOA->mixedAirModelObject()->cast<Node>(), loadedSPM->referenceSetpointNode().get());
  EXPECT_EQ(loadedOA->mixedAirModelObject()->cast<Node>(), loadedSPM->mixedAirStreamNode().get());
  EXPECT_EQ(*loadedOA->outboardOANode(), loadedSPM->outdoorAirStreamNode().get());
  EXPECT_EQ(loadedOA->returnAirModelObject()->cast<Node>(), loadedSPM->returnAirStreamNode().get());
  EXPECT_EQ(loadedHeatExchanger->primaryAirOutletModelObject()->cast<Node>(), loadedSPM->setpointNode().get());

  openstudio::filesystem::remove(idfPath);
}
