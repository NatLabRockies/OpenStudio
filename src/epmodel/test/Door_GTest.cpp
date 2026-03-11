/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/Door.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Door_DefaultConstructor) {
  Model model;
  Door door(model);
  EXPECT_EQ(Door::iddObjectType(), door.iddObject().type());
}

TEST_F(EPModelFixture, Door_ScalarAccessors_RoundTrip) {
  Model model;
  Door door(model);

  EXPECT_TRUE(door.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, door.multiplier());
  EXPECT_TRUE(door.setMultiplier(3.0));
  EXPECT_DOUBLE_EQ(3.0, door.multiplier());
  EXPECT_FALSE(door.isMultiplierDefaulted());
  door.resetMultiplier();
  EXPECT_TRUE(door.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, door.multiplier());

  EXPECT_FALSE(door.startingXCoordinate());
  EXPECT_TRUE(door.setStartingXCoordinate(0.75));
  ASSERT_TRUE(door.startingXCoordinate());
  EXPECT_DOUBLE_EQ(0.75, *door.startingXCoordinate());
  door.resetStartingXCoordinate();
  EXPECT_FALSE(door.startingXCoordinate());

  EXPECT_FALSE(door.startingZCoordinate());
  EXPECT_TRUE(door.setStartingZCoordinate(2.1));
  ASSERT_TRUE(door.startingZCoordinate());
  EXPECT_DOUBLE_EQ(2.1, *door.startingZCoordinate());
  door.resetStartingZCoordinate();
  EXPECT_FALSE(door.startingZCoordinate());

  EXPECT_FALSE(door.length());
  EXPECT_TRUE(door.setLength(0.9));
  ASSERT_TRUE(door.length());
  EXPECT_DOUBLE_EQ(0.9, *door.length());
  door.resetLength();
  EXPECT_FALSE(door.length());

  EXPECT_FALSE(door.height());
  EXPECT_TRUE(door.setHeight(2.2));
  ASSERT_TRUE(door.height());
  EXPECT_DOUBLE_EQ(2.2, *door.height());
  door.resetHeight();
  EXPECT_FALSE(door.height());
}
