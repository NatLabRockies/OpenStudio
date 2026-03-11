/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerHighTemperatureTurnOn.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerHighTemperatureTurnOn_DefaultConstructor) {
  Model model;
  AvailabilityManagerHighTemperatureTurnOn availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerHighTemperatureTurnOn::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerHighTemperatureTurnOn_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerHighTemperatureTurnOn availabilityManager(model);

  EXPECT_DOUBLE_EQ(30.0, availabilityManager.temperature());
  EXPECT_TRUE(availabilityManager.setTemperature(41.75));
  EXPECT_DOUBLE_EQ(41.75, availabilityManager.temperature());
}
