/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACExhaustSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_DefaultConstructor) {
  Model model;
  AirLoopHVACExhaustSystem exhaustSystem(model);
  EXPECT_EQ(AirLoopHVACExhaustSystem::iddObjectType(), exhaustSystem.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACExhaustSystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACExhaustSystem exhaustSystem(model);

  EXPECT_TRUE(exhaustSystem.setName("Main Exhaust System"));
  EXPECT_EQ("Main Exhaust System", exhaustSystem.nameString());
}
