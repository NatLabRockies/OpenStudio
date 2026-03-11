/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerLowTemperatureTurnOff.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerLowTemperatureTurnOff_DefaultConstructor) {
  Model model;
  AvailabilityManagerLowTemperatureTurnOff availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerLowTemperatureTurnOff::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerLowTemperatureTurnOff_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerLowTemperatureTurnOff availabilityManager(model);

  EXPECT_DOUBLE_EQ(30.0, availabilityManager.temperature());
  EXPECT_TRUE(availabilityManager.setTemperature(41.75));
  EXPECT_DOUBLE_EQ(41.75, availabilityManager.temperature());
}
