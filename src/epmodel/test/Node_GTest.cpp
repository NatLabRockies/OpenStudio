/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Node.hpp"
#include "../SetpointManagerScheduled.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Node_DefaultConstructor) {
  Model model;
  Node node = model.getOrCreateTransientByName<Node>("Node 1");
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), node.iddObject().type());
  EXPECT_EQ("Node 1", node.nameString());
}

TEST_F(EPModelFixture, Node_SetpointManagers) {
  Model model;
  AirLoopHVAC airLoop(model);
  Node node = airLoop.supplyOutletNode();
  SetpointManagerScheduled spm(model);
  ASSERT_TRUE(spm.addToNode(node));

  const auto spms = node.setpointManagers();
  ASSERT_EQ(1u, spms.size());
  EXPECT_EQ(spm, spms.front());
}

TEST_F(EPModelFixture, Node_AirLoopHVACOutdoorAirSystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  auto resolvedOASystem = outboardOANode->airLoopHVACOutdoorAirSystem();
  ASSERT_TRUE(resolvedOASystem);
  EXPECT_EQ(oaSystem, *resolvedOASystem);

  auto unconnected = model.getOrCreateTransientByName<Node>("Unconnected Node");
  EXPECT_FALSE(unconnected.airLoopHVACOutdoorAirSystem());
}
