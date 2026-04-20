/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/ParametricRunControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ParametricRunControl_DefaultConstructor) {
  Model model;
  ParametricRunControl object(model);

  EXPECT_EQ(ParametricRunControl::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ParametricRunControl_ScalarAccessors_RoundTrip) {
  Model model;
  ParametricRunControl object(model);

  EXPECT_TRUE(object.setName("Parametric Run Control"));
  EXPECT_EQ("Parametric Run Control", object.nameString());
}
