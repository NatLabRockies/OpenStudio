/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingBuildingDetailed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingBuildingDetailed_DefaultConstructor) {
  Model model;
  ShadingBuildingDetailed shadingBuildingDetailed(model);
  EXPECT_EQ(ShadingBuildingDetailed::iddObjectType(), shadingBuildingDetailed.iddObject().type());

  EXPECT_FALSE(shadingBuildingDetailed.numberofVertices());
  EXPECT_TRUE(shadingBuildingDetailed.isNumberofVerticesAutocalculated());
}

TEST_F(EPModelFixture, ShadingBuildingDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingBuildingDetailed shadingBuildingDetailed(model);

  EXPECT_TRUE(shadingBuildingDetailed.setNumberofVertices(4));
  ASSERT_TRUE(shadingBuildingDetailed.numberofVertices());
  EXPECT_EQ(4, shadingBuildingDetailed.numberofVertices().get());
  EXPECT_FALSE(shadingBuildingDetailed.isNumberofVerticesAutocalculated());

  EXPECT_FALSE(shadingBuildingDetailed.setNumberofVertices(2));
  ASSERT_TRUE(shadingBuildingDetailed.numberofVertices());
  EXPECT_EQ(4, shadingBuildingDetailed.numberofVertices().get());

  shadingBuildingDetailed.autocalculateNumberofVertices();
  EXPECT_FALSE(shadingBuildingDetailed.numberofVertices());
  EXPECT_TRUE(shadingBuildingDetailed.isNumberofVerticesAutocalculated());

  shadingBuildingDetailed.resetNumberofVertices();
  EXPECT_FALSE(shadingBuildingDetailed.numberofVertices());
  EXPECT_TRUE(shadingBuildingDetailed.isNumberofVerticesAutocalculated());
}
