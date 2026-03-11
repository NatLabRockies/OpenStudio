/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../FanConstantVolume.hpp"
#include "../Node.hpp"

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
