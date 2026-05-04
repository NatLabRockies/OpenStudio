/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/OutsideSurfaceConvectionAlgorithm.hpp"
#include "../ModelObject/OutsideSurfaceConvectionAlgorithm_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutsideSurfaceConvectionAlgorithm_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<OutsideSurfaceConvectionAlgorithm>();
  EXPECT_EQ(OutsideSurfaceConvectionAlgorithm::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, OutsideSurfaceConvectionAlgorithm_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<OutsideSurfaceConvectionAlgorithm>();

  EXPECT_FALSE(object.isAlgorithmDefaulted());
  EXPECT_EQ("DOE-2", object.algorithm());
  EXPECT_TRUE(object.setAlgorithm("TARP"));
  EXPECT_EQ("TARP", object.algorithm());
  EXPECT_FALSE(object.isAlgorithmDefaulted());
  object.resetAlgorithm();
  EXPECT_TRUE(object.isAlgorithmDefaulted());
  EXPECT_EQ("DOE-2", object.algorithm());

  EXPECT_FALSE(object.setAlgorithm("InvalidAlgorithmValue"));

  const auto values = OutsideSurfaceConvectionAlgorithm::validAlgorithmValues();
  EXPECT_GE(values.size(), 1u);
}
