/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/InsideSurfaceConvectionAlgorithm.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, InsideSurfaceConvectionAlgorithm_DefaultConstructor) {
  Model model;
  InsideSurfaceConvectionAlgorithm object(model);
  EXPECT_EQ(InsideSurfaceConvectionAlgorithm::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, InsideSurfaceConvectionAlgorithm_ScalarAccessors_RoundTrip) {
  Model model;
  InsideSurfaceConvectionAlgorithm object(model);

  EXPECT_FALSE(object.isAlgorithmDefaulted());
  EXPECT_EQ("TARP", object.algorithm());
  EXPECT_TRUE(object.setAlgorithm("Simple"));
  EXPECT_EQ("Simple", object.algorithm());
  EXPECT_FALSE(object.isAlgorithmDefaulted());
  object.resetAlgorithm();
  EXPECT_TRUE(object.isAlgorithmDefaulted());
  EXPECT_EQ("TARP", object.algorithm());

  EXPECT_FALSE(object.setAlgorithm("InvalidAlgorithmValue"));

  const auto values = InsideSurfaceConvectionAlgorithm::validAlgorithmValues();
  EXPECT_GE(values.size(), 1u);
}
