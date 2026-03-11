/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ExteriorLoadInstance/ExteriorFuelEquipment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExteriorFuelEquipment_DefaultConstructor) {
  Model model;
  ExteriorFuelEquipment object(model);
  EXPECT_EQ(ExteriorFuelEquipment::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("Electricity", object.fuelType());
  EXPECT_DOUBLE_EQ(1.0, object.multiplier());
  EXPECT_EQ("General", object.endUseSubcategory());
}

TEST_F(EPModelFixture, ExteriorFuelEquipment_ScalarAccessors_RoundTrip) {
  Model model;
  ExteriorFuelEquipment object(model);

  EXPECT_FALSE(ExteriorFuelEquipment::validFuelTypeValues().empty());

  EXPECT_TRUE(object.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", object.fuelType());

  EXPECT_TRUE(object.setMultiplier(2.25));
  EXPECT_DOUBLE_EQ(2.25, object.multiplier());
  EXPECT_FALSE(object.isMultiplierDefaulted());
  object.resetMultiplier();
  EXPECT_TRUE(object.isMultiplierDefaulted());

  EXPECT_TRUE(object.setEndUseSubcategory("Exterior Equipment"));
  EXPECT_EQ("Exterior Equipment", object.endUseSubcategory());
  EXPECT_FALSE(object.isEndUseSubcategoryDefaulted());
  object.resetEndUseSubcategory();
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
}
