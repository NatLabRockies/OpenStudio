/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesConcentration.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidPropertiesConcentration_DefaultConstructor) {
  Model model;
  FluidPropertiesConcentration fluidPropertiesConcentration(model);
  EXPECT_EQ(FluidPropertiesConcentration::iddObjectType(), fluidPropertiesConcentration.iddObject().type());
}

TEST_F(EPModelFixture, FluidPropertiesConcentration_ScalarAccessors_RoundTrip) {
  Model model;
  FluidPropertiesConcentration fluidPropertiesConcentration(model);

  const auto fluidPropertyTypeValues = FluidPropertiesConcentration::fluidPropertyTypeValues();
  EXPECT_FALSE(fluidPropertyTypeValues.empty());

  EXPECT_FALSE(fluidPropertiesConcentration.fluidPropertyType());
  EXPECT_TRUE(fluidPropertiesConcentration.setFluidPropertyType("SpecificHeat"));
  ASSERT_TRUE(fluidPropertiesConcentration.fluidPropertyType());
  EXPECT_EQ("SpecificHeat", *fluidPropertiesConcentration.fluidPropertyType());
  EXPECT_FALSE(fluidPropertiesConcentration.setFluidPropertyType("NotAValidType"));
  ASSERT_TRUE(fluidPropertiesConcentration.fluidPropertyType());
  EXPECT_EQ("SpecificHeat", *fluidPropertiesConcentration.fluidPropertyType());
  fluidPropertiesConcentration.resetFluidPropertyType();
  const auto resetFluidPropertyType = fluidPropertiesConcentration.fluidPropertyType();
  EXPECT_TRUE(!resetFluidPropertyType || resetFluidPropertyType->empty());

  EXPECT_FALSE(fluidPropertiesConcentration.concentration());
  EXPECT_TRUE(fluidPropertiesConcentration.setConcentration(0.25));
  ASSERT_TRUE(fluidPropertiesConcentration.concentration());
  EXPECT_DOUBLE_EQ(0.25, *fluidPropertiesConcentration.concentration());
  EXPECT_FALSE(fluidPropertiesConcentration.setConcentration(1.5));
  ASSERT_TRUE(fluidPropertiesConcentration.concentration());
  EXPECT_DOUBLE_EQ(0.25, *fluidPropertiesConcentration.concentration());
  fluidPropertiesConcentration.resetConcentration();
  EXPECT_FALSE(fluidPropertiesConcentration.concentration());
}
