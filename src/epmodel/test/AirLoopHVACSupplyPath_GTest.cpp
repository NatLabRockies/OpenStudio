/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirLoopHVAC.hpp"
#include "../AirLoopHVACSupplyPath.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACSupplyPath_DefaultConstructor) {
  Model model;
  AirLoopHVACSupplyPath path(model);
  EXPECT_EQ(AirLoopHVACSupplyPath::iddObjectType(), path.iddObject().type());
  EXPECT_FALSE(path.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACSupplyPath_DefaultLocalState) {
  Model model;
  AirLoopHVACSupplyPath path(model);

  EXPECT_FALSE(path.airLoopHVAC());
  EXPECT_TRUE(path.components().empty());
}
