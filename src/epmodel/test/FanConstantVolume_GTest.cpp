/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../FanConstantVolume.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanConstantVolume_DefaultConstructor) {
  Model model;
  FanConstantVolume fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_ConstantVolume), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
}
