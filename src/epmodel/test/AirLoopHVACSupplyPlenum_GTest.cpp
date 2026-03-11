/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACSupplyPlenum_DefaultConstructor) {
  Model model;
  AirLoopHVACSupplyPlenum plenum(model);
  EXPECT_EQ(AirLoopHVACSupplyPlenum::iddObjectType(), plenum.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACSupplyPlenum_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACSupplyPlenum plenum(model);

  EXPECT_TRUE(plenum.setName("Main Supply Plenum"));
  EXPECT_EQ("Main Supply Plenum", plenum.nameString());
}
