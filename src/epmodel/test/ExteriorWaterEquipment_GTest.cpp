/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ExteriorLoadInstance/ExteriorWaterEquipment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExteriorWaterEquipment_DefaultConstructor) {
  Model model;
  ExteriorWaterEquipment object(model);
  EXPECT_EQ(ExteriorWaterEquipment::iddObjectType(), object.iddObject().type());
  EXPECT_DOUBLE_EQ(1.0, object.multiplier());
  EXPECT_EQ("General", object.endUseSubcategory());
}

TEST_F(EPModelFixture, ExteriorWaterEquipment_ScalarAccessors_RoundTrip) {
  Model model;
  ExteriorWaterEquipment object(model);

  EXPECT_TRUE(object.setMultiplier(2.25));
  EXPECT_DOUBLE_EQ(2.25, object.multiplier());
  EXPECT_FALSE(object.isMultiplierDefaulted());
  object.resetMultiplier();
  EXPECT_TRUE(object.isMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.multiplier());

  EXPECT_TRUE(object.setEndUseSubcategory("Exterior Water"));
  EXPECT_EQ("Exterior Water", object.endUseSubcategory());
  EXPECT_FALSE(object.isEndUseSubcategoryDefaulted());
  object.resetEndUseSubcategory();
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("General", object.endUseSubcategory());
}
