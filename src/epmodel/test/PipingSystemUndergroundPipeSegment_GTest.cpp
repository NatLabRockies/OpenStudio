/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PipingSystemUndergroundPipeSegment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipingSystemUndergroundPipeSegment_DefaultConstructor) {
  Model model;
  PipingSystemUndergroundPipeSegment pipeSegment(model);
  EXPECT_EQ(PipingSystemUndergroundPipeSegment::iddObjectType(), pipeSegment.iddObject().type());
  EXPECT_FALSE(pipeSegment.nameString().empty());

  EXPECT_DOUBLE_EQ(1.0, pipeSegment.xPosition());
  EXPECT_DOUBLE_EQ(1.0, pipeSegment.yPosition());
  EXPECT_EQ("IncreasingZ", pipeSegment.flowDirection());
}

TEST_F(EPModelFixture, PipingSystemUndergroundPipeSegment_ScalarAccessors_RoundTrip) {
  Model model;
  PipingSystemUndergroundPipeSegment pipeSegment(model);

  const auto flowDirectionValues = PipingSystemUndergroundPipeSegment::flowDirectionValues();
  ASSERT_EQ(2u, flowDirectionValues.size());

  EXPECT_TRUE(pipeSegment.setXPosition(3.25));
  EXPECT_TRUE(pipeSegment.setYPosition(2.10));
  EXPECT_TRUE(pipeSegment.setFlowDirection(flowDirectionValues[1]));

  EXPECT_DOUBLE_EQ(3.25, pipeSegment.xPosition());
  EXPECT_DOUBLE_EQ(2.10, pipeSegment.yPosition());
  EXPECT_EQ(flowDirectionValues[1], pipeSegment.flowDirection());

  EXPECT_FALSE(pipeSegment.setXPosition(0.0));
  EXPECT_FALSE(pipeSegment.setYPosition(-1.0));
  EXPECT_FALSE(pipeSegment.setFlowDirection("BadDirection"));
}
