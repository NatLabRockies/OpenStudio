/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingSiteDetailed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingSiteDetailed_DefaultConstructor) {
  Model model;
  ShadingSiteDetailed shadingSiteDetailed(model);
  EXPECT_EQ(ShadingSiteDetailed::iddObjectType(), shadingSiteDetailed.iddObject().type());

  EXPECT_FALSE(shadingSiteDetailed.numberofVertices());
  EXPECT_TRUE(shadingSiteDetailed.isNumberofVerticesAutocalculated());
}

TEST_F(EPModelFixture, ShadingSiteDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingSiteDetailed shadingSiteDetailed(model);

  EXPECT_TRUE(shadingSiteDetailed.setNumberofVertices(4));
  ASSERT_TRUE(shadingSiteDetailed.numberofVertices());
  EXPECT_EQ(4, shadingSiteDetailed.numberofVertices().get());
  EXPECT_FALSE(shadingSiteDetailed.isNumberofVerticesAutocalculated());

  EXPECT_FALSE(shadingSiteDetailed.setNumberofVertices(2));
  ASSERT_TRUE(shadingSiteDetailed.numberofVertices());
  EXPECT_EQ(4, shadingSiteDetailed.numberofVertices().get());

  shadingSiteDetailed.autocalculateNumberofVertices();
  EXPECT_FALSE(shadingSiteDetailed.numberofVertices());
  EXPECT_TRUE(shadingSiteDetailed.isNumberofVerticesAutocalculated());

  shadingSiteDetailed.resetNumberofVertices();
  EXPECT_FALSE(shadingSiteDetailed.numberofVertices());
  EXPECT_TRUE(shadingSiteDetailed.isNumberofVerticesAutocalculated());
}
