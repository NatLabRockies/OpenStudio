/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../OutdoorAirMixer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_OutdoorAirMixer_DefaultConstructor) {
  Model model;
  OutdoorAirMixer outdoorAirMixer(model);
  EXPECT_EQ(OutdoorAirMixer::iddObjectType(), outdoorAirMixer.iddObject().type());
  EXPECT_FALSE(outdoorAirMixer.nameString().empty());
}
