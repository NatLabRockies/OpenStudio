/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilSystemIntegratedHeatPumpAirSource.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_DefaultConstructor) {
  Model model;
  CoilSystemIntegratedHeatPumpAirSource coilSystem(model);
  EXPECT_EQ(CoilSystemIntegratedHeatPumpAirSource::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  EXPECT_DOUBLE_EQ(20.0, coilSystem.indoorTemperatureLimitForSCWHMode());
  EXPECT_DOUBLE_EQ(27.0, coilSystem.ambientTemperatureLimitForSCWHMode());
  EXPECT_DOUBLE_EQ(20.0, coilSystem.indoorTemperatureAboveWhichWHHasHigherPriority());
  EXPECT_DOUBLE_EQ(20.0, coilSystem.ambientTemperatureAboveWhichWHHasHigherPriority());
  EXPECT_EQ(0, coilSystem.flagtoIndicateLoadControlInSCWHMode());
  EXPECT_EQ(1, coilSystem.minimumSpeedLevelForSCWHMode());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode());
  EXPECT_EQ(1, coilSystem.minimumSpeedLevelForSCDWHMode());
  EXPECT_DOUBLE_EQ(360.0, coilSystem.maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode());
  EXPECT_EQ(1, coilSystem.minimumSpeedLevelForSHDWHMode());
}

TEST_F(EPModelFixture, CoilSystemIntegratedHeatPumpAirSource_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemIntegratedHeatPumpAirSource coilSystem(model);

  EXPECT_TRUE(coilSystem.setIndoorTemperatureLimitForSCWHMode(21.5));
  EXPECT_DOUBLE_EQ(21.5, coilSystem.indoorTemperatureLimitForSCWHMode());

  EXPECT_TRUE(coilSystem.setAmbientTemperatureLimitForSCWHMode(28.5));
  EXPECT_DOUBLE_EQ(28.5, coilSystem.ambientTemperatureLimitForSCWHMode());

  EXPECT_TRUE(coilSystem.setIndoorTemperatureAboveWhichWHHasHigherPriority(19.5));
  EXPECT_DOUBLE_EQ(19.5, coilSystem.indoorTemperatureAboveWhichWHHasHigherPriority());

  EXPECT_TRUE(coilSystem.setAmbientTemperatureAboveWhichWHHasHigherPriority(18.5));
  EXPECT_DOUBLE_EQ(18.5, coilSystem.ambientTemperatureAboveWhichWHHasHigherPriority());

  EXPECT_TRUE(coilSystem.setFlagtoIndicateLoadControlInSCWHMode(1));
  EXPECT_EQ(1, coilSystem.flagtoIndicateLoadControlInSCWHMode());

  EXPECT_TRUE(coilSystem.setMinimumSpeedLevelForSCWHMode(2));
  EXPECT_EQ(2, coilSystem.minimumSpeedLevelForSCWHMode());

  EXPECT_TRUE(coilSystem.setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(0.25));
  EXPECT_DOUBLE_EQ(0.25, coilSystem.maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode());

  EXPECT_TRUE(coilSystem.setMinimumSpeedLevelForSCDWHMode(3));
  EXPECT_EQ(3, coilSystem.minimumSpeedLevelForSCDWHMode());

  EXPECT_TRUE(coilSystem.setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(420.0));
  EXPECT_DOUBLE_EQ(420.0, coilSystem.maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode());

  EXPECT_TRUE(coilSystem.setMinimumSpeedLevelForSHDWHMode(4));
  EXPECT_EQ(4, coilSystem.minimumSpeedLevelForSHDWHMode());
}
