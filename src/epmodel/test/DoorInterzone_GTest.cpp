/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/DoorInterzone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DoorInterzone_DefaultConstructor) {
  Model model;
  DoorInterzone doorInterzone(model);
  EXPECT_EQ(DoorInterzone::iddObjectType(), doorInterzone.iddObject().type());
}

TEST_F(EPModelFixture, DoorInterzone_ScalarAccessors_RoundTrip) {
  Model model;
  DoorInterzone doorInterzone(model);

  EXPECT_TRUE(doorInterzone.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, doorInterzone.multiplier());
  EXPECT_TRUE(doorInterzone.setMultiplier(3.0));
  EXPECT_DOUBLE_EQ(3.0, doorInterzone.multiplier());
  EXPECT_FALSE(doorInterzone.isMultiplierDefaulted());
  doorInterzone.resetMultiplier();
  EXPECT_TRUE(doorInterzone.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, doorInterzone.multiplier());

  EXPECT_FALSE(doorInterzone.startingXCoordinate());
  EXPECT_TRUE(doorInterzone.setStartingXCoordinate(0.65));
  ASSERT_TRUE(doorInterzone.startingXCoordinate());
  EXPECT_DOUBLE_EQ(0.65, *doorInterzone.startingXCoordinate());
  doorInterzone.resetStartingXCoordinate();
  EXPECT_FALSE(doorInterzone.startingXCoordinate());

  EXPECT_FALSE(doorInterzone.startingZCoordinate());
  EXPECT_TRUE(doorInterzone.setStartingZCoordinate(2.0));
  ASSERT_TRUE(doorInterzone.startingZCoordinate());
  EXPECT_DOUBLE_EQ(2.0, *doorInterzone.startingZCoordinate());
  doorInterzone.resetStartingZCoordinate();
  EXPECT_FALSE(doorInterzone.startingZCoordinate());

  EXPECT_FALSE(doorInterzone.length());
  EXPECT_TRUE(doorInterzone.setLength(0.95));
  ASSERT_TRUE(doorInterzone.length());
  EXPECT_DOUBLE_EQ(0.95, *doorInterzone.length());
  doorInterzone.resetLength();
  EXPECT_FALSE(doorInterzone.length());

  EXPECT_FALSE(doorInterzone.height());
  EXPECT_TRUE(doorInterzone.setHeight(2.15));
  ASSERT_TRUE(doorInterzone.height());
  EXPECT_DOUBLE_EQ(2.15, *doorInterzone.height());
  doorInterzone.resetHeight();
  EXPECT_FALSE(doorInterzone.height());
}
