/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/AirLoopHVACReturnPath.hpp"

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

TEST_F(EPModelFixture, AirLoopHVACReturnPath_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACReturnPath path(model);

  EXPECT_TRUE(path.setName("Main Return Path"));
  EXPECT_EQ("Main Return Path", path.nameString());
}
