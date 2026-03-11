/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidPropertiesName_DefaultConstructor) {
  Model model;
  FluidPropertiesName fluidPropertiesName(model);
  EXPECT_EQ(FluidPropertiesName::iddObjectType(), fluidPropertiesName.iddObject().type());
}

TEST_F(EPModelFixture, FluidPropertiesName_ScalarAccessors_RoundTrip) {
  Model model;
  FluidPropertiesName fluidPropertiesName(model);

  const auto fluidTypeValues = FluidPropertiesName::fluidTypeValues();
  EXPECT_FALSE(fluidTypeValues.empty());

  EXPECT_TRUE(fluidPropertiesName.setFluidName("MyGlycol_35"));
  EXPECT_EQ("MyGlycol_35", fluidPropertiesName.fluidName());

  EXPECT_TRUE(fluidPropertiesName.setFluidType("Glycol"));
  EXPECT_EQ("Glycol", fluidPropertiesName.fluidType());

  EXPECT_FALSE(fluidPropertiesName.setFluidType("NotAValidFluidType"));
  EXPECT_EQ("Glycol", fluidPropertiesName.fluidType());
}
