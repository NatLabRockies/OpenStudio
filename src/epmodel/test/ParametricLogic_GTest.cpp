/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/ParametricLogic.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ParametricLogic_DefaultConstructor) {
  Model model;
  ParametricLogic object(model);

  EXPECT_EQ(ParametricLogic::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ParametricLogic_ScalarAccessors_RoundTrip) {
  Model model;
  ParametricLogic object(model);

  EXPECT_TRUE(object.setName("Parametric Logic"));
  EXPECT_EQ("Parametric Logic", object.nameString());
}
