/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Node_DefaultConstructor) {
  Model model;
  Node node = model.getOrCreateTransientByName<Node>("Node 1");
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), node.iddObject().type());
  EXPECT_EQ("Node 1", node.nameString());
}
