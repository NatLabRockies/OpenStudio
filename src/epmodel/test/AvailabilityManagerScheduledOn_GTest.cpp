/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_DefaultConstructor) {
  Model model;
  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);
  EXPECT_EQ(AvailabilityManagerScheduledOn::iddObjectType(), availabilityManagerScheduledOn.iddObject().type());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);

  EXPECT_TRUE(availabilityManagerScheduledOn.setName("AvailabilityManager Scheduled On 1"));
  EXPECT_EQ("AvailabilityManager Scheduled On 1", availabilityManagerScheduledOn.nameString());
}
