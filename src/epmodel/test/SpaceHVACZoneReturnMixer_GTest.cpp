/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SpaceHVACZoneReturnMixer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceHVACZoneReturnMixer_DefaultConstructor) {
  Model model;
  SpaceHVACZoneReturnMixer mixer(model);
  EXPECT_EQ(SpaceHVACZoneReturnMixer::iddObjectType(), mixer.iddObject().type());
}

TEST_F(EPModelFixture, SpaceHVACZoneReturnMixer_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceHVACZoneReturnMixer mixer(model);

  EXPECT_TRUE(mixer.setName("Main Space Return Mixer"));
  EXPECT_EQ("Main Space Return Mixer", mixer.nameString());
}
