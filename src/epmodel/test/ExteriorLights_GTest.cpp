/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ExteriorLoadInstance/ExteriorLights.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExteriorLights_DefaultConstructor) {
  Model model;
  ExteriorLights object(model);
  EXPECT_EQ(ExteriorLights::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ExteriorLights_ScalarAccessors_RoundTrip) {
  Model model;
  ExteriorLights object(model);

  EXPECT_FALSE(ExteriorLights::controlOptionValues().empty());
  EXPECT_FALSE(ExteriorLights::validControlOptionValues().empty());

  EXPECT_TRUE(object.setControlOption("AstronomicalClock"));
  EXPECT_EQ("AstronomicalClock", object.controlOption());
  EXPECT_FALSE(object.isControlOptionDefaulted());
  object.resetControlOption();
  EXPECT_TRUE(object.isControlOptionDefaulted());

  EXPECT_TRUE(object.setMultiplier(2.25));
  EXPECT_DOUBLE_EQ(2.25, object.multiplier());
  EXPECT_FALSE(object.isMultiplierDefaulted());
  object.resetMultiplier();
  EXPECT_TRUE(object.isMultiplierDefaulted());

  EXPECT_TRUE(object.setEndUseSubcategory("Exterior Lighting"));
  EXPECT_EQ("Exterior Lighting", object.endUseSubcategory());
  EXPECT_FALSE(object.isEndUseSubcategoryDefaulted());
  object.resetEndUseSubcategory();
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
}
