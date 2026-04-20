/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneRefrigerationDoorMixing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneRefrigerationDoorMixing_DefaultConstructor) {
  Model model;
  ZoneRefrigerationDoorMixing door(model);

  EXPECT_EQ(ZoneRefrigerationDoorMixing::iddObjectType(), door.iddObject().type());
  EXPECT_DOUBLE_EQ(3.0, door.doorHeight());
  EXPECT_TRUE(door.isDoorHeightDefaulted());
  EXPECT_DOUBLE_EQ(9.0, door.doorArea());
  EXPECT_TRUE(door.isDoorAreaDefaulted());
  EXPECT_EQ("None", door.doorProtectionType());
  EXPECT_TRUE(door.isDoorProtectionTypeDefaulted());
}

TEST_F(EPModelFixture, ZoneRefrigerationDoorMixing_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneRefrigerationDoorMixing door(model);

  const auto values = ZoneRefrigerationDoorMixing::doorProtectionTypeValues();
  EXPECT_NE(values.cend(), std::find(values.cbegin(), values.cend(), "AirCurtain"));

  EXPECT_FALSE(door.setDoorHeight(-0.1));
  EXPECT_FALSE(door.setDoorArea(500.0));

  EXPECT_TRUE(door.setDoorHeight(4.9));
  EXPECT_TRUE(door.setDoorArea(12.25));
  EXPECT_TRUE(door.setDoorProtectionType("AirCurtain"));

  EXPECT_DOUBLE_EQ(4.9, door.doorHeight());
  EXPECT_DOUBLE_EQ(12.25, door.doorArea());
  EXPECT_EQ("AirCurtain", door.doorProtectionType());

  door.resetDoorHeight();
  EXPECT_TRUE(door.isDoorHeightDefaulted());
  EXPECT_DOUBLE_EQ(3.0, door.doorHeight());

  door.resetDoorArea();
  EXPECT_TRUE(door.isDoorAreaDefaulted());
  EXPECT_DOUBLE_EQ(9.0, door.doorArea());

  door.resetDoorProtectionType();
  EXPECT_TRUE(door.isDoorProtectionTypeDefaulted());
  EXPECT_EQ("None", door.doorProtectionType());
}
