/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorFuelCell.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCell_DefaultConstructor) {
  Model model;
  GeneratorFuelCell generator(model);
  EXPECT_EQ(GeneratorFuelCell::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCell_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCell generator(model);

  EXPECT_TRUE(generator.setName("Generator FuelCell 1"));
  EXPECT_EQ("Generator FuelCell 1", generator.nameString());
}
