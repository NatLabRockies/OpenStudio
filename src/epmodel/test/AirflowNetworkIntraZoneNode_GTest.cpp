/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkIntraZoneNode.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkIntraZoneNode_DefaultConstructor) {
  Model model;
  AirflowNetworkIntraZoneNode node(model);
  EXPECT_EQ(AirflowNetworkIntraZoneNode::iddObjectType(), node.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkIntraZoneNode_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkIntraZoneNode node(model);

  EXPECT_TRUE(node.isNodeHeightDefaulted());
  EXPECT_DOUBLE_EQ(0.0, node.nodeHeight());

  EXPECT_TRUE(node.setNodeHeight(1.35));
  EXPECT_DOUBLE_EQ(1.35, node.nodeHeight());
  EXPECT_FALSE(node.isNodeHeightDefaulted());

  node.resetNodeHeight();
  EXPECT_TRUE(node.isNodeHeightDefaulted());
  EXPECT_DOUBLE_EQ(0.0, node.nodeHeight());
}
