/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanConstantVolume_DefaultConstructor) {
  Model model;
  FanConstantVolume fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_ConstantVolume), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeAcceptsAirLoopSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(fan.addToNode(supplyInletNode));
}

TEST_F(EPModelFixture, FanConstantVolume_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  FanConstantVolume fan(model);
  EXPECT_FALSE(fan.addToNode(*outboardOANode));
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
