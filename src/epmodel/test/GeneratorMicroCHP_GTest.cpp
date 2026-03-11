/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorMicroCHP.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorMicroCHP_DefaultConstructor) {
  Model model;
  GeneratorMicroCHP generator(model);
  EXPECT_EQ(GeneratorMicroCHP::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorMicroCHP_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorMicroCHP generator(model);

  EXPECT_TRUE(generator.setName("Main Micro CHP Generator"));
  EXPECT_EQ("Main Micro CHP Generator", generator.nameString());
}
