/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/ParametricFileNameSuffix.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ParametricFileNameSuffix_DefaultConstructor) {
  Model model;
  ParametricFileNameSuffix object(model);

  EXPECT_EQ(ParametricFileNameSuffix::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ParametricFileNameSuffix_ScalarAccessors_RoundTrip) {
  Model model;
  ParametricFileNameSuffix object(model);

  EXPECT_TRUE(object.setName("Parametric Suffix Set"));
  EXPECT_EQ("Parametric Suffix Set", object.nameString());
}
