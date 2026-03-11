/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerHybridVentilation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerHybridVentilation_DefaultConstructor) {
  Model model;
  AvailabilityManagerHybridVentilation availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerHybridVentilation::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerHybridVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerHybridVentilation availabilityManager(model);

  EXPECT_TRUE(availabilityManager.useWeatherFileRainIndicators());
  EXPECT_DOUBLE_EQ(40.0, availabilityManager.maximumWindSpeed());
  EXPECT_DOUBLE_EQ(20.0, availabilityManager.minimumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(30.0, availabilityManager.maximumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(20000.0, availabilityManager.minimumOutdoorEnthalpy());
  EXPECT_DOUBLE_EQ(30000.0, availabilityManager.maximumOutdoorEnthalpy());
  EXPECT_DOUBLE_EQ(15.0, availabilityManager.minimumOutdoorDewpoint());
  EXPECT_DOUBLE_EQ(30.0, availabilityManager.maximumOutdoorDewpoint());
  EXPECT_DOUBLE_EQ(0.0, availabilityManager.minimumHVACOperationTime());
  EXPECT_DOUBLE_EQ(0.0, availabilityManager.minimumVentilationTime());

  EXPECT_TRUE(availabilityManager.setUseWeatherFileRainIndicators(false));
  EXPECT_TRUE(availabilityManager.setMaximumWindSpeed(12.5));
  EXPECT_TRUE(availabilityManager.setMinimumOutdoorTemperature(-5.0));
  EXPECT_TRUE(availabilityManager.setMaximumOutdoorTemperature(35.5));
  EXPECT_TRUE(availabilityManager.setMinimumOutdoorEnthalpy(12500.0));
  EXPECT_TRUE(availabilityManager.setMaximumOutdoorEnthalpy(88000.0));
  EXPECT_TRUE(availabilityManager.setMinimumOutdoorDewpoint(-2.0));
  EXPECT_TRUE(availabilityManager.setMaximumOutdoorDewpoint(18.5));
  EXPECT_TRUE(availabilityManager.setMinimumHVACOperationTime(9.0));
  EXPECT_TRUE(availabilityManager.setMinimumVentilationTime(11.0));

  EXPECT_FALSE(availabilityManager.useWeatherFileRainIndicators());
  EXPECT_DOUBLE_EQ(12.5, availabilityManager.maximumWindSpeed());
  EXPECT_DOUBLE_EQ(-5.0, availabilityManager.minimumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(35.5, availabilityManager.maximumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(12500.0, availabilityManager.minimumOutdoorEnthalpy());
  EXPECT_DOUBLE_EQ(88000.0, availabilityManager.maximumOutdoorEnthalpy());
  EXPECT_DOUBLE_EQ(-2.0, availabilityManager.minimumOutdoorDewpoint());
  EXPECT_DOUBLE_EQ(18.5, availabilityManager.maximumOutdoorDewpoint());
  EXPECT_DOUBLE_EQ(9.0, availabilityManager.minimumHVACOperationTime());
  EXPECT_DOUBLE_EQ(11.0, availabilityManager.minimumVentilationTime());
}
