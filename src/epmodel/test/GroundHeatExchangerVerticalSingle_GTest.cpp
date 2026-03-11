/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatExchangerVerticalSingle.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerVerticalSingle_DefaultConstructor) {
  Model model;
  GroundHeatExchangerVerticalSingle ghx(model);
  EXPECT_EQ(GroundHeatExchangerVerticalSingle::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_DOUBLE_EQ(0.0, ghx.xLocation());
  EXPECT_DOUBLE_EQ(0.0, ghx.yLocation());
}

TEST_F(EPModelFixture, GroundHeatExchangerVerticalSingle_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerVerticalSingle ghx(model);

  EXPECT_TRUE(ghx.setXLocation(12.5));
  EXPECT_DOUBLE_EQ(12.5, ghx.xLocation());

  EXPECT_TRUE(ghx.setYLocation(-4.25));
  EXPECT_DOUBLE_EQ(-4.25, ghx.yLocation());
}
