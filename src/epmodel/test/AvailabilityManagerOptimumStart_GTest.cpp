/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerOptimumStart.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerOptimumStart_DefaultConstructor) {
  Model model;
  AvailabilityManagerOptimumStart availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerOptimumStart::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerOptimumStart_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerOptimumStart availabilityManager(model);

  EXPECT_EQ("MaximumofZoneList", availabilityManager.controlType());
  EXPECT_DOUBLE_EQ(6.0, availabilityManager.maximumValueforOptimumStartTime());
  EXPECT_EQ("AdaptiveTemperatureGradient", availabilityManager.controlAlgorithm());
  EXPECT_DOUBLE_EQ(3.0, availabilityManager.constantTemperatureGradientduringCooling());
  EXPECT_DOUBLE_EQ(3.0, availabilityManager.constantTemperatureGradientduringHeating());
  EXPECT_DOUBLE_EQ(2.0, availabilityManager.initialTemperatureGradientduringCooling());
  EXPECT_DOUBLE_EQ(2.0, availabilityManager.initialTemperatureGradientduringHeating());
  EXPECT_DOUBLE_EQ(2.0, availabilityManager.constantStartTime());
  EXPECT_EQ(3, availabilityManager.numberofPreviousDays());

  EXPECT_TRUE(availabilityManager.setControlType("ControlZone"));
  EXPECT_TRUE(availabilityManager.setMaximumValueforOptimumStartTime(4.5));
  EXPECT_TRUE(availabilityManager.setControlAlgorithm("ConstantStartTime"));
  EXPECT_TRUE(availabilityManager.setConstantTemperatureGradientduringCooling(1.25));
  EXPECT_TRUE(availabilityManager.setConstantTemperatureGradientduringHeating(1.5));
  EXPECT_TRUE(availabilityManager.setInitialTemperatureGradientduringCooling(0.9));
  EXPECT_TRUE(availabilityManager.setInitialTemperatureGradientduringHeating(1.1));
  EXPECT_TRUE(availabilityManager.setConstantStartTime(1.75));
  EXPECT_TRUE(availabilityManager.setNumberofPreviousDays(5));

  EXPECT_EQ("ControlZone", availabilityManager.controlType());
  EXPECT_DOUBLE_EQ(4.5, availabilityManager.maximumValueforOptimumStartTime());
  EXPECT_EQ("ConstantStartTime", availabilityManager.controlAlgorithm());
  EXPECT_DOUBLE_EQ(1.25, availabilityManager.constantTemperatureGradientduringCooling());
  EXPECT_DOUBLE_EQ(1.5, availabilityManager.constantTemperatureGradientduringHeating());
  EXPECT_DOUBLE_EQ(0.9, availabilityManager.initialTemperatureGradientduringCooling());
  EXPECT_DOUBLE_EQ(1.1, availabilityManager.initialTemperatureGradientduringHeating());
  EXPECT_DOUBLE_EQ(1.75, availabilityManager.constantStartTime());
  EXPECT_EQ(5, availabilityManager.numberofPreviousDays());
}
