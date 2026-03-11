/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACMixer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACMixer_DefaultConstructor) {
  Model model;
  AirLoopHVACMixer mixer(model);
  EXPECT_EQ(AirLoopHVACMixer::iddObjectType(), mixer.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACMixer_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACMixer mixer(model);

  EXPECT_TRUE(mixer.setName("Main Air Loop Mixer"));
  EXPECT_EQ("Main Air Loop Mixer", mixer.nameString());
}
