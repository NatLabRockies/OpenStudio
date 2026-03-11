/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneBaseboardOutdoorTemperatureControlled.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneBaseboardOutdoorTemperatureControlled_DefaultConstructor) {
  Model model;
  ZoneBaseboardOutdoorTemperatureControlled object(model);
  EXPECT_EQ(ZoneBaseboardOutdoorTemperatureControlled::iddObjectType(), object.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, object.fractionRadiant());
  EXPECT_EQ("General", object.endUseSubcategory());
}

TEST_F(EPModelFixture, ZoneBaseboardOutdoorTemperatureControlled_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneBaseboardOutdoorTemperatureControlled object(model);

  EXPECT_TRUE(object.setCapacityAtLowTemperature(1500.0));
  EXPECT_TRUE(object.setLowTemperature(-15.0));
  EXPECT_TRUE(object.setCapacityAtHighTemperature(1800.0));
  EXPECT_TRUE(object.setHighTemperature(25.0));
  EXPECT_TRUE(object.setFractionRadiant(0.35));
  EXPECT_TRUE(object.setEndUseSubcategory("Custom"));

  EXPECT_DOUBLE_EQ(1500.0, object.capacityAtLowTemperature());
  EXPECT_DOUBLE_EQ(-15.0, object.lowTemperature());
  EXPECT_DOUBLE_EQ(1800.0, object.capacityAtHighTemperature());
  EXPECT_DOUBLE_EQ(25.0, object.highTemperature());
  EXPECT_DOUBLE_EQ(0.35, object.fractionRadiant());
  EXPECT_EQ("Custom", object.endUseSubcategory());

  object.resetFractionRadiant();
  object.resetEndUseSubcategory();

  EXPECT_TRUE(object.isFractionRadiantDefaulted());
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fractionRadiant());
  EXPECT_EQ("General", object.endUseSubcategory());
}
