/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkOccupantVentilationControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkOccupantVentilationControl_DefaultConstructor) {
  Model model;
  AirflowNetworkOccupantVentilationControl occupantVentilationControl(model);
  EXPECT_EQ(AirflowNetworkOccupantVentilationControl::iddObjectType(), occupantVentilationControl.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkOccupantVentilationControl_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkOccupantVentilationControl occupantVentilationControl(model);

  EXPECT_TRUE(occupantVentilationControl.isMinimumOpeningTimeDefaulted());
  EXPECT_TRUE(occupantVentilationControl.setMinimumOpeningTime(123.0));
  EXPECT_DOUBLE_EQ(123.0, occupantVentilationControl.minimumOpeningTime());
  EXPECT_FALSE(occupantVentilationControl.isMinimumOpeningTimeDefaulted());
  occupantVentilationControl.resetMinimumOpeningTime();
  EXPECT_TRUE(occupantVentilationControl.isMinimumOpeningTimeDefaulted());

  EXPECT_TRUE(occupantVentilationControl.setMinimumClosingTime(321.0));
  EXPECT_DOUBLE_EQ(321.0, occupantVentilationControl.minimumClosingTime());
  occupantVentilationControl.resetMinimumClosingTime();
  EXPECT_TRUE(occupantVentilationControl.isMinimumClosingTimeDefaulted());

  EXPECT_TRUE(occupantVentilationControl.setThermalComfortTemperatureBoundaryPoint(20.5));
  EXPECT_DOUBLE_EQ(20.5, occupantVentilationControl.thermalComfortTemperatureBoundaryPoint());
  occupantVentilationControl.resetThermalComfortTemperatureBoundaryPoint();
  EXPECT_TRUE(occupantVentilationControl.isThermalComfortTemperatureBoundaryPointDefaulted());

  EXPECT_TRUE(occupantVentilationControl.setMaximumPredictedPercentageofDissatisfiedThreshold(12.5));
  EXPECT_DOUBLE_EQ(12.5, occupantVentilationControl.maximumPredictedPercentageofDissatisfiedThreshold());
  occupantVentilationControl.resetMaximumPredictedPercentageofDissatisfiedThreshold();
  EXPECT_TRUE(occupantVentilationControl.isMaximumPredictedPercentageofDissatisfiedThresholdDefaulted());

  EXPECT_TRUE(occupantVentilationControl.isOccupancyCheckDefaulted());
  occupantVentilationControl.setOccupancyCheck(true);
  EXPECT_TRUE(occupantVentilationControl.occupancyCheck());
  EXPECT_FALSE(occupantVentilationControl.isOccupancyCheckDefaulted());
  occupantVentilationControl.setOccupancyCheck(false);
  EXPECT_FALSE(occupantVentilationControl.occupancyCheck());
  occupantVentilationControl.resetOccupancyCheck();
  EXPECT_TRUE(occupantVentilationControl.isOccupancyCheckDefaulted());
}
