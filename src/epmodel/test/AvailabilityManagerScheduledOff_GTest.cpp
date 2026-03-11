/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOff.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_DefaultConstructor) {
  Model model;
  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);
  EXPECT_EQ(AvailabilityManagerScheduledOff::iddObjectType(), availabilityManagerScheduledOff.iddObject().type());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);

  EXPECT_TRUE(availabilityManagerScheduledOff.setName("AvailabilityManager Scheduled Off 1"));
  EXPECT_EQ("AvailabilityManager Scheduled Off 1", availabilityManagerScheduledOff.nameString());
}
