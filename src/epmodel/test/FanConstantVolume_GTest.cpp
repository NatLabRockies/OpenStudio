/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Schedule/ScheduleRuleset.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanConstantVolume_DefaultConstructor) {
  Model model;
  FanConstantVolume fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_ConstantVolume), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
  auto defaultSchedule = fan.availabilitySchedule();
  auto constantSchedule = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(constantSchedule);
  EXPECT_DOUBLE_EQ(1.0, constantSchedule->value());
}

TEST_F(EPModelFixture, FanConstantVolume_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  FanConstantVolume fan(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.4));
  EXPECT_TRUE(fan.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleRuleset rulesetSchedule(model);
  EXPECT_TRUE(fan.setAvailabilitySchedule(rulesetSchedule));
  EXPECT_EQ(rulesetSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(rulesetSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", rulesetSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(22.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(fan.setAvailabilitySchedule(wrongSchedule));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeAcceptsAirLoopSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(fan.addToNode(supplyInletNode));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  FanConstantVolume fan(model);
  EXPECT_TRUE(fan.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}

TEST_F(EPModelFixture, FanConstantVolume_RemoveDetachesFromOutdoorAirSystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  FanConstantVolume fan(model);
  ASSERT_TRUE(fan.addToNode(*outboardOANode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  const auto fanHandle = fan.handle();

  fan.remove();

  EXPECT_LT(oaSystem.oaComponents().size(), 3u);
  EXPECT_FALSE(oaSystem.component(fanHandle));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeRejectsDemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto splitterBranchNode = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranchNode);
  auto branchNode = splitterBranchNode->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  EXPECT_FALSE(fan.addToNode(*branchNode));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeRejectsDemandInletAndOutletNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto demandInletNode = airLoop.demandInletNode();
  auto demandOutletNode = airLoop.demandOutletNode();
  EXPECT_FALSE(fan.addToNode(demandInletNode));
  EXPECT_FALSE(fan.addToNode(demandOutletNode));
}

TEST_F(EPModelFixture, FanConstantVolume_ScalarAccessors_RoundTrip) {
  Model model;
  FanConstantVolume fan(model);

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.81, fan.fanEfficiency());

  EXPECT_TRUE(fan.setFanEfficiency(0.79));
  EXPECT_DOUBLE_EQ(0.79, fan.fanTotalEfficiency());

  EXPECT_TRUE(fan.setPressureRise(620.0));
  EXPECT_DOUBLE_EQ(620.0, fan.pressureRise());

  EXPECT_TRUE(fan.setMaximumFlowRate(1.35));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(1.35, fan.maximumFlowRate().get());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());

  fan.autosizeMaximumFlowRate();
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());

  fan.resetMaximumFlowRate();
  EXPECT_FALSE(fan.maximumFlowRate());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());

  EXPECT_TRUE(fan.setMotorEfficiency(0.88));
  EXPECT_DOUBLE_EQ(0.88, fan.motorEfficiency());

  EXPECT_TRUE(fan.setMotorInAirstreamFraction(0.9));
  EXPECT_DOUBLE_EQ(0.9, fan.motorInAirstreamFraction());

  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
}
