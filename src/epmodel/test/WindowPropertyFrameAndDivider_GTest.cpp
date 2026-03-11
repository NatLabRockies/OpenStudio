/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/WindowPropertyFrameAndDivider.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowPropertyFrameAndDivider_DefaultConstructor) {
  Model model;
  WindowPropertyFrameAndDivider frameAndDivider(model);
  EXPECT_EQ(WindowPropertyFrameAndDivider::iddObjectType(), frameAndDivider.iddObject().type());
}

TEST_F(EPModelFixture, WindowPropertyFrameAndDivider_ScalarAccessors_RoundTrip) {
  Model model;
  WindowPropertyFrameAndDivider frameAndDivider(model);

  EXPECT_TRUE(frameAndDivider.setFrameWidth(0.12));
  EXPECT_DOUBLE_EQ(0.12, frameAndDivider.frameWidth());
  frameAndDivider.resetFrameWidth();
  EXPECT_TRUE(frameAndDivider.isFrameWidthDefaulted());

  EXPECT_TRUE(frameAndDivider.setNumberOfHorizontalDividers(3));
  EXPECT_EQ(3, frameAndDivider.numberOfHorizontalDividers());
  frameAndDivider.resetNumberOfHorizontalDividers();
  EXPECT_TRUE(frameAndDivider.isNumberOfHorizontalDividersDefaulted());

  EXPECT_TRUE(frameAndDivider.setOutsideRevealSolarAbsorptance(0.42));
  EXPECT_DOUBLE_EQ(0.42, frameAndDivider.outsideRevealSolarAbsorptance());
  frameAndDivider.resetOutsideRevealSolarAbsorptance();
  EXPECT_TRUE(frameAndDivider.isOutsideRevealSolarAbsorptanceDefaulted());
  EXPECT_TRUE(frameAndDivider.setDividerConductance(1.5));
  EXPECT_DOUBLE_EQ(1.5, frameAndDivider.dividerConductance());
  frameAndDivider.resetDividerConductance();
  EXPECT_TRUE(frameAndDivider.isDividerConductanceDefaulted());
}
