/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneGroup.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneGroup_DefaultConstructor) {
  Model model;
  ZoneGroup zoneGroup(model);
  EXPECT_EQ(ZoneGroup::iddObjectType(), zoneGroup.iddObject().type());
  EXPECT_EQ(1, zoneGroup.zoneListMultiplier());
  EXPECT_TRUE(zoneGroup.isZoneListMultiplierDefaulted());
}

TEST_F(EPModelFixture, ZoneGroup_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneGroup zoneGroup(model);

  EXPECT_TRUE(zoneGroup.setZoneListMultiplier(5));
  EXPECT_EQ(5, zoneGroup.zoneListMultiplier());
  EXPECT_FALSE(zoneGroup.isZoneListMultiplierDefaulted());

  EXPECT_FALSE(zoneGroup.setZoneListMultiplier(0));
  EXPECT_EQ(5, zoneGroup.zoneListMultiplier());

  zoneGroup.resetZoneListMultiplier();
  EXPECT_TRUE(zoneGroup.isZoneListMultiplierDefaulted());
  EXPECT_EQ(1, zoneGroup.zoneListMultiplier());
}
