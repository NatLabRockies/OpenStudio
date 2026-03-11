/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerDifferentialThermostat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerDifferentialThermostat_DefaultConstructor) {
  Model model;
  AvailabilityManagerDifferentialThermostat availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerDifferentialThermostat::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerDifferentialThermostat_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerDifferentialThermostat availabilityManager(model);

  EXPECT_DOUBLE_EQ(10.0, availabilityManager.temperatureDifferenceOnLimit());
  EXPECT_DOUBLE_EQ(2.0, availabilityManager.temperatureDifferenceOffLimit());

  EXPECT_TRUE(availabilityManager.setTemperatureDifferenceOnLimit(6.5));
  EXPECT_TRUE(availabilityManager.setTemperatureDifferenceOffLimit(1.25));

  EXPECT_DOUBLE_EQ(6.5, availabilityManager.temperatureDifferenceOnLimit());
  EXPECT_DOUBLE_EQ(1.25, availabilityManager.temperatureDifferenceOffLimit());
}
