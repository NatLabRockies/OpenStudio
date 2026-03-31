/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_DefaultConstructor) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);

  EXPECT_EQ(HeatExchangerDesiccantBalancedFlow::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerDesiccantBalancedFlow object(model);

  EXPECT_TRUE(object.setEconomizerLockout(false));
  EXPECT_FALSE(object.economizerLockout());

  EXPECT_TRUE(object.setEconomizerLockout(true));
  EXPECT_TRUE(object.economizerLockout());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_AddToOANodeBuildsBothStreams) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HeatExchangerDesiccantBalancedFlow object(model);
  ASSERT_TRUE(object.addToNode(*outboardOANode));

  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(object.primaryAirInletModelObject());
  EXPECT_TRUE(object.primaryAirOutletModelObject());
  EXPECT_TRUE(object.secondaryAirInletModelObject());
  EXPECT_TRUE(object.secondaryAirOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_AddToReliefNodeBuildsBothStreams) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HeatExchangerDesiccantBalancedFlow object(model);
  ASSERT_TRUE(object.addToNode(*outboardReliefNode));

  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  EXPECT_EQ(3u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(object.primaryAirInletModelObject());
  EXPECT_TRUE(object.primaryAirOutletModelObject());
  EXPECT_TRUE(object.secondaryAirInletModelObject());
  EXPECT_TRUE(object.secondaryAirOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerDesiccantBalancedFlow_RemoveDetachesFromOutdoorAirSystemWhenAddedFromReliefSide) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  HeatExchangerDesiccantBalancedFlow object(model);
  ASSERT_TRUE(object.addToNode(*outboardReliefNode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  ASSERT_EQ(3u, oaSystem.reliefComponents().size());
  const auto objectHandle = object.handle();

  object.remove();

  EXPECT_EQ(1u, oaSystem.oaComponents().size());
  EXPECT_EQ(1u, oaSystem.reliefComponents().size());
  EXPECT_FALSE(oaSystem.oaComponent(objectHandle));
  EXPECT_FALSE(oaSystem.reliefComponent(objectHandle));
}
