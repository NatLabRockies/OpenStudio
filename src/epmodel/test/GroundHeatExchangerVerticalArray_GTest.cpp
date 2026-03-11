/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatExchangerVerticalArray.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerVerticalArray_DefaultConstructor) {
  Model model;
  GroundHeatExchangerVerticalArray ghx(model);
  EXPECT_EQ(GroundHeatExchangerVerticalArray::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_EQ(10, ghx.numberofBoreholesinXDirection());
  EXPECT_EQ(12, ghx.numberofBoreholesinYDirection());
  EXPECT_DOUBLE_EQ(6.0, ghx.boreholeSpacing());
}

TEST_F(EPModelFixture, GroundHeatExchangerVerticalArray_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerVerticalArray ghx(model);

  EXPECT_TRUE(ghx.setNumberofBoreholesinXDirection(16));
  EXPECT_EQ(16, ghx.numberofBoreholesinXDirection());

  EXPECT_TRUE(ghx.setNumberofBoreholesinYDirection(18));
  EXPECT_EQ(18, ghx.numberofBoreholesinYDirection());

  EXPECT_TRUE(ghx.setBoreholeSpacing(7.5));
  EXPECT_DOUBLE_EQ(7.5, ghx.boreholeSpacing());
}
