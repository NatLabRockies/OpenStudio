/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GlazedDoorInterzone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GlazedDoorInterzone_DefaultConstructor) {
  Model model;
  GlazedDoorInterzone glazedDoorInterzone(model);
  EXPECT_EQ(GlazedDoorInterzone::iddObjectType(), glazedDoorInterzone.iddObject().type());
}

TEST_F(EPModelFixture, GlazedDoorInterzone_ScalarAccessors_RoundTrip) {
  Model model;
  GlazedDoorInterzone glazedDoorInterzone(model);

  EXPECT_TRUE(glazedDoorInterzone.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, glazedDoorInterzone.multiplier());
  EXPECT_TRUE(glazedDoorInterzone.setMultiplier(2.0));
  EXPECT_DOUBLE_EQ(2.0, glazedDoorInterzone.multiplier());
  EXPECT_FALSE(glazedDoorInterzone.isMultiplierDefaulted());
  glazedDoorInterzone.resetMultiplier();
  EXPECT_TRUE(glazedDoorInterzone.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, glazedDoorInterzone.multiplier());

  EXPECT_FALSE(glazedDoorInterzone.startingXCoordinate());
  EXPECT_TRUE(glazedDoorInterzone.setStartingXCoordinate(0.75));
  ASSERT_TRUE(glazedDoorInterzone.startingXCoordinate());
  EXPECT_DOUBLE_EQ(0.75, *glazedDoorInterzone.startingXCoordinate());
  glazedDoorInterzone.resetStartingXCoordinate();
  EXPECT_FALSE(glazedDoorInterzone.startingXCoordinate());

  EXPECT_FALSE(glazedDoorInterzone.startingZCoordinate());
  EXPECT_TRUE(glazedDoorInterzone.setStartingZCoordinate(2.1));
  ASSERT_TRUE(glazedDoorInterzone.startingZCoordinate());
  EXPECT_DOUBLE_EQ(2.1, *glazedDoorInterzone.startingZCoordinate());
  glazedDoorInterzone.resetStartingZCoordinate();
  EXPECT_FALSE(glazedDoorInterzone.startingZCoordinate());

  EXPECT_FALSE(glazedDoorInterzone.length());
  EXPECT_TRUE(glazedDoorInterzone.setLength(0.9));
  ASSERT_TRUE(glazedDoorInterzone.length());
  EXPECT_DOUBLE_EQ(0.9, *glazedDoorInterzone.length());
  glazedDoorInterzone.resetLength();
  EXPECT_FALSE(glazedDoorInterzone.length());

  EXPECT_FALSE(glazedDoorInterzone.height());
  EXPECT_TRUE(glazedDoorInterzone.setHeight(2.2));
  ASSERT_TRUE(glazedDoorInterzone.height());
  EXPECT_DOUBLE_EQ(2.2, *glazedDoorInterzone.height());
  glazedDoorInterzone.resetHeight();
  EXPECT_FALSE(glazedDoorInterzone.height());
}
