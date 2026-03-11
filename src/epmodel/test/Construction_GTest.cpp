/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../LayeredConstruction/Construction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Construction_DefaultConstructor) {
  Model model;
  Construction construction(model);
  EXPECT_EQ(Construction::iddObjectType(), construction.iddObject().type());
}

TEST_F(EPModelFixture, Construction_ScalarAccessors_RoundTrip) {
  Model model;
  Construction construction(model);

  // Construction has no class-specific simple scalar fields; base Name scalar is the roundtrip coverage.
  EXPECT_TRUE(construction.setName("EPModel Construction"));
  EXPECT_EQ("EPModel Construction", construction.nameString());
}
