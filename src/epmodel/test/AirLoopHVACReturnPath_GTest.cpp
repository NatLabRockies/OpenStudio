/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirLoopHVAC.hpp"
#include "../AirLoopHVACReturnPath.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACReturnPath_DefaultConstructor) {
  Model model;
  AirLoopHVACReturnPath path(model);
  EXPECT_EQ(AirLoopHVACReturnPath::iddObjectType(), path.iddObject().type());
  EXPECT_FALSE(path.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACReturnPath_DefaultLocalState) {
  Model model;
  AirLoopHVACReturnPath path(model);

  EXPECT_FALSE(path.airLoopHVAC());
  EXPECT_TRUE(path.components().empty());
}
