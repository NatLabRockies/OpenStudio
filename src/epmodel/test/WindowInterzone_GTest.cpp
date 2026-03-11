/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowInterzone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowInterzone_DefaultConstructor) {
  Model model;
  WindowInterzone windowInterzone(model);
  EXPECT_EQ(WindowInterzone::iddObjectType(), windowInterzone.iddObject().type());
  EXPECT_DOUBLE_EQ(1.0, windowInterzone.multiplier());
  EXPECT_TRUE(windowInterzone.isMultiplierDefaulted());
}

TEST_F(EPModelFixture, WindowInterzone_ScalarAccessors_RoundTrip) {
  Model model;
  WindowInterzone windowInterzone(model);

  EXPECT_TRUE(windowInterzone.setMultiplier(2.5));
  EXPECT_FALSE(windowInterzone.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(2.5, windowInterzone.multiplier());
  windowInterzone.resetMultiplier();
  EXPECT_TRUE(windowInterzone.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, windowInterzone.multiplier());

  EXPECT_TRUE(windowInterzone.setStartingXCoordinate(0.7));
  ASSERT_TRUE(windowInterzone.startingXCoordinate());
  EXPECT_DOUBLE_EQ(0.7, *windowInterzone.startingXCoordinate());
  windowInterzone.resetStartingXCoordinate();
  EXPECT_FALSE(windowInterzone.startingXCoordinate());

  EXPECT_TRUE(windowInterzone.setStartingZCoordinate(1.1));
  ASSERT_TRUE(windowInterzone.startingZCoordinate());
  EXPECT_DOUBLE_EQ(1.1, *windowInterzone.startingZCoordinate());
  windowInterzone.resetStartingZCoordinate();
  EXPECT_FALSE(windowInterzone.startingZCoordinate());

  EXPECT_TRUE(windowInterzone.setLength(1.5));
  ASSERT_TRUE(windowInterzone.length());
  EXPECT_DOUBLE_EQ(1.5, *windowInterzone.length());
  windowInterzone.resetLength();
  EXPECT_FALSE(windowInterzone.length());

  EXPECT_TRUE(windowInterzone.setHeight(2.5));
  ASSERT_TRUE(windowInterzone.height());
  EXPECT_DOUBLE_EQ(2.5, *windowInterzone.height());
  windowInterzone.resetHeight();
  EXPECT_FALSE(windowInterzone.height());
}
