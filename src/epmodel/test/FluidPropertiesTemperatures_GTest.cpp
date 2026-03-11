/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FluidPropertiesTemperatures.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FluidPropertiesTemperatures_DefaultConstructor) {
  Model model;
  FluidPropertiesTemperatures fluidPropertiesTemperatures(model);
  EXPECT_EQ(FluidPropertiesTemperatures::iddObjectType(), fluidPropertiesTemperatures.iddObject().type());
}

TEST_F(EPModelFixture, FluidPropertiesTemperatures_ScalarAccessors_RoundTrip) {
  Model model;
  FluidPropertiesTemperatures fluidPropertiesTemperatures(model);

  EXPECT_TRUE(fluidPropertiesTemperatures.setName("FluidTempsProfileA"));
  EXPECT_EQ("FluidTempsProfileA", fluidPropertiesTemperatures.nameString());
}
