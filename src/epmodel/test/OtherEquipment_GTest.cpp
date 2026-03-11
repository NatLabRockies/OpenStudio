/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoadInstance/OtherEquipment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OtherEquipment_DefaultConstructor) {
  Model model;
  OtherEquipment object(model);
  EXPECT_EQ(OtherEquipment::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, OtherEquipment_ScalarAccessors_RoundTrip) {
  Model model;
  OtherEquipment object(model);

  EXPECT_FALSE(OtherEquipment::designLevelCalculationMethodValues().empty());
  EXPECT_FALSE(OtherEquipment::validFuelTypeValues().empty());

  EXPECT_TRUE(object.setDesignLevelCalculationMethod("Watts/Area"));
  EXPECT_EQ("Watts/Area", object.designLevelCalculationMethod());

  EXPECT_TRUE(object.setPowerPerFloorArea(8.3));
  ASSERT_TRUE(object.powerPerFloorArea());
  EXPECT_DOUBLE_EQ(8.3, object.powerPerFloorArea().get());
  object.resetPowerPerFloorArea();
  EXPECT_FALSE(object.powerPerFloorArea());

  EXPECT_TRUE(object.setPowerPerPerson(95.0));
  ASSERT_TRUE(object.powerPerPerson());
  EXPECT_DOUBLE_EQ(95.0, object.powerPerPerson().get());
  object.resetPowerPerPerson();
  EXPECT_FALSE(object.powerPerPerson());

  EXPECT_TRUE(object.setDesignLevel(100.0));
  ASSERT_TRUE(object.designLevel());
  EXPECT_DOUBLE_EQ(100.0, object.designLevel().get());
  EXPECT_TRUE(object.setMultiplier(2.0));
  ASSERT_TRUE(object.designLevel());
  EXPECT_DOUBLE_EQ(200.0, object.designLevel().get());

  EXPECT_TRUE(object.setFractionLatent(0.1));
  EXPECT_DOUBLE_EQ(0.1, object.fractionLatent());
  object.resetFractionLatent();
  EXPECT_TRUE(object.isFractionLatentDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fractionLatent());

  EXPECT_TRUE(object.setFractionRadiant(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.fractionRadiant());
  object.resetFractionRadiant();
  EXPECT_TRUE(object.isFractionRadiantDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fractionRadiant());

  EXPECT_TRUE(object.setFractionLost(0.3));
  EXPECT_DOUBLE_EQ(0.3, object.fractionLost());
  object.resetFractionLost();
  EXPECT_TRUE(object.isFractionLostDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fractionLost());

  EXPECT_TRUE(object.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", object.fuelType());
  EXPECT_TRUE(object.setFuelType("None"));
  EXPECT_EQ("None", object.fuelType());
  EXPECT_FALSE(object.setFuelType("DefinitelyInvalidFuelType"));
  object.resetFuelType();
  EXPECT_TRUE(object.isFuelTypeDefaulted());

  EXPECT_TRUE(object.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", object.endUseSubcategory());
  object.resetEndUseSubcategory();
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("General", object.endUseSubcategory());
}
