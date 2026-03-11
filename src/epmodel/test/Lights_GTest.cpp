/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SpaceLoadInstance/Lights.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Lights_DefaultConstructor) {
  Model model;
  Lights object(model);
  EXPECT_EQ(Lights::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, Lights_ScalarAccessors_RoundTrip) {
  Model model;
  Lights object(model);

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

  EXPECT_TRUE(object.setLightingLevel(100.0));
  ASSERT_TRUE(object.lightingLevel());
  EXPECT_DOUBLE_EQ(100.0, object.lightingLevel().get());
  EXPECT_TRUE(object.setMultiplier(2.0));
  ASSERT_TRUE(object.lightingLevel());
  EXPECT_DOUBLE_EQ(200.0, object.lightingLevel().get());

  EXPECT_TRUE(object.setReturnAirFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.returnAirFraction());
  object.resetReturnAirFraction();
  EXPECT_TRUE(object.isReturnAirFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.returnAirFraction());

  EXPECT_TRUE(object.setFractionRadiant(0.1));
  EXPECT_DOUBLE_EQ(0.1, object.fractionRadiant());
  object.resetFractionRadiant();
  EXPECT_TRUE(object.isFractionRadiantDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fractionRadiant());

  EXPECT_TRUE(object.setFractionVisible(0.3));
  EXPECT_DOUBLE_EQ(0.3, object.fractionVisible());
  object.resetFractionVisible();
  EXPECT_TRUE(object.isFractionVisibleDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fractionVisible());

  EXPECT_TRUE(object.setFractionReplaceable(0.4));
  EXPECT_DOUBLE_EQ(0.4, object.fractionReplaceable());
  object.resetFractionReplaceable();
  EXPECT_TRUE(object.isFractionReplaceableDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.fractionReplaceable());

  EXPECT_TRUE(object.setEndUseSubcategory("Process"));
  EXPECT_EQ("Process", object.endUseSubcategory());
  object.resetEndUseSubcategory();
  EXPECT_TRUE(object.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("General", object.endUseSubcategory());

  EXPECT_TRUE(object.setReturnAirFractionCalculatedfromPlenumTemperature(true));
  EXPECT_TRUE(object.returnAirFractionCalculatedfromPlenumTemperature());
  object.resetReturnAirFractionCalculatedfromPlenumTemperature();
  EXPECT_TRUE(object.isReturnAirFractionCalculatedfromPlenumTemperatureDefaulted());

  EXPECT_TRUE(object.setReturnAirFractionFunctionofPlenumTemperatureCoefficient1(0.25));
  EXPECT_DOUBLE_EQ(0.25, object.returnAirFractionFunctionofPlenumTemperatureCoefficient1());
  object.resetReturnAirFractionFunctionofPlenumTemperatureCoefficient1();
  EXPECT_TRUE(object.isReturnAirFractionFunctionofPlenumTemperatureCoefficient1Defaulted());
  EXPECT_DOUBLE_EQ(0.0, object.returnAirFractionFunctionofPlenumTemperatureCoefficient1());

  EXPECT_TRUE(object.setReturnAirFractionFunctionofPlenumTemperatureCoefficient2(0.35));
  EXPECT_DOUBLE_EQ(0.35, object.returnAirFractionFunctionofPlenumTemperatureCoefficient2());
  object.resetReturnAirFractionFunctionofPlenumTemperatureCoefficient2();
  EXPECT_TRUE(object.isReturnAirFractionFunctionofPlenumTemperatureCoefficient2Defaulted());
  EXPECT_DOUBLE_EQ(0.0, object.returnAirFractionFunctionofPlenumTemperatureCoefficient2());
}
