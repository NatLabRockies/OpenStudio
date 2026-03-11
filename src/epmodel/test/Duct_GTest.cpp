/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/Duct.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Duct_DefaultConstructor) {
  Model model;
  Duct duct(model);
  EXPECT_EQ(Duct::iddObjectType(), duct.iddObject().type());
  EXPECT_FALSE(duct.nameString().empty());
}

TEST_F(EPModelFixture, Duct_ScalarAccessors_RoundTrip) {
  Model model;
  Duct duct(model);

  // Duct has no Duct-specific scalar accessors; verify base scalar roundtrip remains intact.
  EXPECT_TRUE(duct.setName("Main Supply Duct"));
  EXPECT_EQ("Main Supply Duct", duct.nameString());
}
