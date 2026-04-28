/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirNode.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirNode_DefaultConstructor) {
  Model model;
  RoomAirNode roomAirNode(model);
  EXPECT_EQ(RoomAirNode::iddObjectType(), roomAirNode.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirNode_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirNode roomAirNode(model);

  EXPECT_TRUE(roomAirNode.setNodeType("Inlet"));
  EXPECT_TRUE(roomAirNode.setHeightOfNodalControlVolumeCenter(1.25));

  EXPECT_EQ("Inlet", roomAirNode.nodeType());
  EXPECT_DOUBLE_EQ(1.25, roomAirNode.heightOfNodalControlVolumeCenter());
}
