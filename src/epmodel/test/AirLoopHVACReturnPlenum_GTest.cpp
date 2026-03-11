/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_DefaultConstructor) {
  Model model;
  AirLoopHVACReturnPlenum plenum(model);
  EXPECT_EQ(AirLoopHVACReturnPlenum::iddObjectType(), plenum.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACReturnPlenum_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACReturnPlenum plenum(model);

  EXPECT_TRUE(plenum.setName("Main Return Plenum"));
  EXPECT_EQ("Main Return Plenum", plenum.nameString());
}
