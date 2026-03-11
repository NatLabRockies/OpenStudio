/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirflowNetworkNode/AirflowNetworkDistributionNode.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionNode_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionNode node(model);
  EXPECT_EQ(AirflowNetworkDistributionNode::iddObjectType(), node.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionNode_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionNode node(model);

  const auto typeValues = AirflowNetworkDistributionNode::componentObjectTypeorNodeTypeValues();
  EXPECT_FALSE(typeValues.empty());
  EXPECT_TRUE(node.isComponentObjectTypeorNodeTypeDefaulted());
  EXPECT_EQ("Other", node.componentObjectTypeorNodeType());

  EXPECT_TRUE(node.setComponentObjectTypeorNodeType("AirLoopHVAC:OutdoorAirSystem"));
  EXPECT_EQ("AirLoopHVAC:OutdoorAirSystem", node.componentObjectTypeorNodeType());
  EXPECT_FALSE(node.isComponentObjectTypeorNodeTypeDefaulted());
  node.resetComponentObjectTypeorNodeType();
  EXPECT_TRUE(node.isComponentObjectTypeorNodeTypeDefaulted());
  EXPECT_EQ("Other", node.componentObjectTypeorNodeType());

  EXPECT_TRUE(node.isNodeHeightDefaulted());
  EXPECT_DOUBLE_EQ(0.0, node.nodeHeight());
  EXPECT_TRUE(node.setNodeHeight(2.25));
  EXPECT_DOUBLE_EQ(2.25, node.nodeHeight());
  EXPECT_FALSE(node.isNodeHeightDefaulted());
  node.resetNodeHeight();
  EXPECT_TRUE(node.isNodeHeightDefaulted());
  EXPECT_DOUBLE_EQ(0.0, node.nodeHeight());
}
