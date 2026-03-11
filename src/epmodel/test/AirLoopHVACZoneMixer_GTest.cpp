/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirLoopHVACZoneMixer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirLoopHVACZoneMixer_DefaultConstructor) {
  Model model;
  AirLoopHVACZoneMixer mixer(model);
  EXPECT_EQ(AirLoopHVACZoneMixer::iddObjectType(), mixer.iddObject().type());
  EXPECT_FALSE(mixer.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACZoneMixer_DefaultPortsAndInlets) {
  Model model;
  AirLoopHVACZoneMixer mixer(model);

  EXPECT_EQ(0u, mixer.nextBranchIndex());
  EXPECT_FALSE(mixer.lastInletModelObject());
  EXPECT_TRUE(mixer.inletModelObjects().empty());
}
