/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/ParametricSetValueForRun.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ParametricSetValueForRun_DefaultConstructor) {
  Model model;
  ParametricSetValueForRun object(model);

  EXPECT_EQ(ParametricSetValueForRun::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ParametricSetValueForRun_ScalarAccessors_RoundTrip) {
  Model model;
  ParametricSetValueForRun object(model);

  EXPECT_TRUE(object.setName("Parametric Set Value For Run"));
  EXPECT_EQ("Parametric Set Value For Run", object.nameString());
}
