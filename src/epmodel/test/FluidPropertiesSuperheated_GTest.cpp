/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesSuperheated.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidPropertiesSuperheated_DefaultConstructor) {
  Model model;
  FluidPropertiesSuperheated fluidPropertiesSuperheated(model);
  EXPECT_EQ(FluidPropertiesSuperheated::iddObjectType(), fluidPropertiesSuperheated.iddObject().type());
}

TEST_F(EPModelFixture, FluidPropertiesSuperheated_ScalarAccessors_RoundTrip) {
  Model model;
  FluidPropertiesSuperheated fluidPropertiesSuperheated(model);

  const auto fluidPropertyTypeValues = FluidPropertiesSuperheated::fluidPropertyTypeValues();
  EXPECT_FALSE(fluidPropertyTypeValues.empty());

  EXPECT_FALSE(fluidPropertiesSuperheated.fluidPropertyType());
  EXPECT_TRUE(fluidPropertiesSuperheated.setFluidPropertyType("Density"));
  ASSERT_TRUE(fluidPropertiesSuperheated.fluidPropertyType());
  EXPECT_EQ("Density", *fluidPropertiesSuperheated.fluidPropertyType());
  EXPECT_FALSE(fluidPropertiesSuperheated.setFluidPropertyType("NotAValidType"));
  ASSERT_TRUE(fluidPropertiesSuperheated.fluidPropertyType());
  EXPECT_EQ("Density", *fluidPropertiesSuperheated.fluidPropertyType());
  fluidPropertiesSuperheated.resetFluidPropertyType();
  const auto resetFluidPropertyType = fluidPropertiesSuperheated.fluidPropertyType();
  EXPECT_TRUE(!resetFluidPropertyType || resetFluidPropertyType->empty());

  EXPECT_FALSE(fluidPropertiesSuperheated.pressure());
  EXPECT_TRUE(fluidPropertiesSuperheated.setPressure(101325.0));
  ASSERT_TRUE(fluidPropertiesSuperheated.pressure());
  EXPECT_DOUBLE_EQ(101325.0, *fluidPropertiesSuperheated.pressure());
  EXPECT_FALSE(fluidPropertiesSuperheated.setPressure(-1.0));
  ASSERT_TRUE(fluidPropertiesSuperheated.pressure());
  EXPECT_DOUBLE_EQ(101325.0, *fluidPropertiesSuperheated.pressure());
  fluidPropertiesSuperheated.resetPressure();
  EXPECT_FALSE(fluidPropertiesSuperheated.pressure());
}
