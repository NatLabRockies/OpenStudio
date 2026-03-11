/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/UtilityCostComputation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostComputation_DefaultConstructor) {
  Model model;
  UtilityCostComputation computation(model);

  EXPECT_EQ(UtilityCostComputation::iddObjectType(), computation.iddObject().type());
}

TEST_F(EPModelFixture, UtilityCostComputation_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostComputation computation(model);

  EXPECT_TRUE(computation.setName("Utility Cost Compute"));
  EXPECT_EQ("Utility Cost Compute", computation.nameString());
}
