/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ShadingZoneDetailed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingZoneDetailed_DefaultConstructor) {
  Model model;
  ShadingZoneDetailed shadingZoneDetailed(model);
  EXPECT_EQ(ShadingZoneDetailed::iddObjectType(), shadingZoneDetailed.iddObject().type());

  EXPECT_FALSE(shadingZoneDetailed.numberofVertices());
  EXPECT_TRUE(shadingZoneDetailed.isNumberofVerticesAutocalculated());
}

TEST_F(EPModelFixture, ShadingZoneDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingZoneDetailed shadingZoneDetailed(model);

  EXPECT_TRUE(shadingZoneDetailed.setNumberofVertices(4));
  ASSERT_TRUE(shadingZoneDetailed.numberofVertices());
  EXPECT_EQ(4, shadingZoneDetailed.numberofVertices().get());
  EXPECT_FALSE(shadingZoneDetailed.isNumberofVerticesAutocalculated());

  EXPECT_FALSE(shadingZoneDetailed.setNumberofVertices(2));
  ASSERT_TRUE(shadingZoneDetailed.numberofVertices());
  EXPECT_EQ(4, shadingZoneDetailed.numberofVertices().get());

  shadingZoneDetailed.autocalculateNumberofVertices();
  EXPECT_FALSE(shadingZoneDetailed.numberofVertices());
  EXPECT_TRUE(shadingZoneDetailed.isNumberofVerticesAutocalculated());

  shadingZoneDetailed.resetNumberofVertices();
  EXPECT_FALSE(shadingZoneDetailed.numberofVertices());
  EXPECT_TRUE(shadingZoneDetailed.isNumberofVerticesAutocalculated());
}
