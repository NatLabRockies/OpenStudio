/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GlazedDoor.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GlazedDoor_DefaultConstructor) {
  Model model;
  GlazedDoor glazedDoor(model);
  EXPECT_EQ(GlazedDoor::iddObjectType(), glazedDoor.iddObject().type());
}

TEST_F(EPModelFixture, GlazedDoor_ScalarAccessors_RoundTrip) {
  Model model;
  GlazedDoor glazedDoor(model);

  EXPECT_TRUE(glazedDoor.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, glazedDoor.multiplier());
  EXPECT_TRUE(glazedDoor.setMultiplier(3.0));
  EXPECT_DOUBLE_EQ(3.0, glazedDoor.multiplier());
  EXPECT_FALSE(glazedDoor.isMultiplierDefaulted());
  glazedDoor.resetMultiplier();
  EXPECT_TRUE(glazedDoor.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, glazedDoor.multiplier());

  EXPECT_FALSE(glazedDoor.startingXCoordinate());
  EXPECT_TRUE(glazedDoor.setStartingXCoordinate(0.85));
  ASSERT_TRUE(glazedDoor.startingXCoordinate());
  EXPECT_DOUBLE_EQ(0.85, *glazedDoor.startingXCoordinate());
  glazedDoor.resetStartingXCoordinate();
  EXPECT_FALSE(glazedDoor.startingXCoordinate());

  EXPECT_FALSE(glazedDoor.startingZCoordinate());
  EXPECT_TRUE(glazedDoor.setStartingZCoordinate(2.05));
  ASSERT_TRUE(glazedDoor.startingZCoordinate());
  EXPECT_DOUBLE_EQ(2.05, *glazedDoor.startingZCoordinate());
  glazedDoor.resetStartingZCoordinate();
  EXPECT_FALSE(glazedDoor.startingZCoordinate());

  EXPECT_FALSE(glazedDoor.length());
  EXPECT_TRUE(glazedDoor.setLength(0.92));
  ASSERT_TRUE(glazedDoor.length());
  EXPECT_DOUBLE_EQ(0.92, *glazedDoor.length());
  glazedDoor.resetLength();
  EXPECT_FALSE(glazedDoor.length());

  EXPECT_FALSE(glazedDoor.height());
  EXPECT_TRUE(glazedDoor.setHeight(2.25));
  ASSERT_TRUE(glazedDoor.height());
  EXPECT_DOUBLE_EQ(2.25, *glazedDoor.height());
  glazedDoor.resetHeight();
  EXPECT_FALSE(glazedDoor.height());
}
