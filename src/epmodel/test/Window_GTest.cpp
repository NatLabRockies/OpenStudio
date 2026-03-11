/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/Window.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Window_DefaultConstructor) {
  Model model;
  Window window(model);
  EXPECT_EQ(Window::iddObjectType(), window.iddObject().type());
  EXPECT_DOUBLE_EQ(1.0, window.multiplier());
  EXPECT_TRUE(window.isMultiplierDefaulted());
}

TEST_F(EPModelFixture, Window_ScalarAccessors_RoundTrip) {
  Model model;
  Window window(model);

  EXPECT_TRUE(window.setMultiplier(2.5));
  EXPECT_FALSE(window.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(2.5, window.multiplier());
  window.resetMultiplier();
  EXPECT_TRUE(window.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, window.multiplier());

  EXPECT_TRUE(window.setStartingXCoordinate(0.6));
  ASSERT_TRUE(window.startingXCoordinate());
  EXPECT_DOUBLE_EQ(0.6, *window.startingXCoordinate());
  window.resetStartingXCoordinate();
  EXPECT_FALSE(window.startingXCoordinate());

  EXPECT_TRUE(window.setStartingZCoordinate(1.2));
  ASSERT_TRUE(window.startingZCoordinate());
  EXPECT_DOUBLE_EQ(1.2, *window.startingZCoordinate());
  window.resetStartingZCoordinate();
  EXPECT_FALSE(window.startingZCoordinate());

  EXPECT_TRUE(window.setLength(1.5));
  ASSERT_TRUE(window.length());
  EXPECT_DOUBLE_EQ(1.5, *window.length());
  window.resetLength();
  EXPECT_FALSE(window.length());

  EXPECT_TRUE(window.setHeight(2.0));
  ASSERT_TRUE(window.height());
  EXPECT_DOUBLE_EQ(2.0, *window.height());
  window.resetHeight();
  EXPECT_FALSE(window.height());
}
