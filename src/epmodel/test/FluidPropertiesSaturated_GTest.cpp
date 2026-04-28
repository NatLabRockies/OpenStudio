/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/FluidPropertiesSaturated.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidPropertiesSaturated_DefaultConstructor) {
  Model model;
  FluidPropertiesSaturated fluidPropertiesSaturated(model);
  EXPECT_EQ(FluidPropertiesSaturated::iddObjectType(), fluidPropertiesSaturated.iddObject().type());
}

TEST_F(EPModelFixture, FluidPropertiesSaturated_ScalarAccessors_RoundTrip) {
  Model model;
  FluidPropertiesSaturated fluidPropertiesSaturated(model);

  const auto fluidPropertyTypeValues = FluidPropertiesSaturated::fluidPropertyTypeValues();
  EXPECT_FALSE(fluidPropertyTypeValues.empty());

  const auto fluidPhaseValues = FluidPropertiesSaturated::fluidPhaseValues();
  EXPECT_FALSE(fluidPhaseValues.empty());

  EXPECT_FALSE(fluidPropertiesSaturated.fluidPropertyType());
  EXPECT_TRUE(fluidPropertiesSaturated.setFluidPropertyType("Enthalpy"));
  ASSERT_TRUE(fluidPropertiesSaturated.fluidPropertyType());
  EXPECT_EQ("Enthalpy", *fluidPropertiesSaturated.fluidPropertyType());
  EXPECT_FALSE(fluidPropertiesSaturated.setFluidPropertyType("NotAValidType"));
  ASSERT_TRUE(fluidPropertiesSaturated.fluidPropertyType());
  EXPECT_EQ("Enthalpy", *fluidPropertiesSaturated.fluidPropertyType());
  fluidPropertiesSaturated.resetFluidPropertyType();
  const auto resetFluidPropertyType = fluidPropertiesSaturated.fluidPropertyType();
  EXPECT_TRUE(!resetFluidPropertyType || resetFluidPropertyType->empty());

  EXPECT_FALSE(fluidPropertiesSaturated.fluidPhase());
  EXPECT_TRUE(fluidPropertiesSaturated.setFluidPhase("FluidGas"));
  ASSERT_TRUE(fluidPropertiesSaturated.fluidPhase());
  EXPECT_EQ("FluidGas", *fluidPropertiesSaturated.fluidPhase());
  EXPECT_FALSE(fluidPropertiesSaturated.setFluidPhase("NotAValidPhase"));
  ASSERT_TRUE(fluidPropertiesSaturated.fluidPhase());
  EXPECT_EQ("FluidGas", *fluidPropertiesSaturated.fluidPhase());
  fluidPropertiesSaturated.resetFluidPhase();
  const auto resetFluidPhase = fluidPropertiesSaturated.fluidPhase();
  EXPECT_TRUE(!resetFluidPhase || resetFluidPhase->empty());
}
