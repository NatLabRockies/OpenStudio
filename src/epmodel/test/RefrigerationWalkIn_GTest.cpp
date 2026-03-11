/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RefrigerationWalkIn.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationWalkIn_DefaultConstructor) {
  Model model;
  RefrigerationWalkIn walkin(model);

  EXPECT_DOUBLE_EQ(4690.0, walkin.ratedCoilCoolingCapacity());
  EXPECT_DOUBLE_EQ(-2.22, walkin.operatingTemperature());
  EXPECT_DOUBLE_EQ(-6.67, walkin.ratedCoolingSourceTemperature());
  EXPECT_DOUBLE_EQ(0.0, walkin.ratedTotalHeatingPower());
  EXPECT_DOUBLE_EQ(735.0, walkin.ratedCoolingCoilFanPower());
  EXPECT_DOUBLE_EQ(0.0, walkin.ratedCirculationFanPower());
  EXPECT_FALSE(walkin.isRatedCirculationFanPowerDefaulted());
  EXPECT_DOUBLE_EQ(120.0, walkin.ratedTotalLightingPower());
  EXPECT_EQ("Electric", walkin.defrostType());
  EXPECT_EQ("TimeSchedule", walkin.defrostControlType());
  ASSERT_TRUE(walkin.defrostPower());
  EXPECT_DOUBLE_EQ(5512.0, walkin.defrostPower().get());
  EXPECT_DOUBLE_EQ(0.0, walkin.averageRefrigerantChargeInventory());
  EXPECT_DOUBLE_EQ(13.0, walkin.insulatedFloorSurfaceArea());
  EXPECT_DOUBLE_EQ(0.207, walkin.insulatedFloorUValue());
}

TEST_F(EPModelFixture, RefrigerationWalkIn_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationWalkIn walkin(model);

  EXPECT_TRUE(walkin.setRatedCoilCoolingCapacity(5000.0));
  EXPECT_TRUE(walkin.setOperatingTemperature(-5.0));
  EXPECT_TRUE(walkin.setRatedCoolingSourceTemperature(-7.0));
  EXPECT_TRUE(walkin.setRatedTotalHeatingPower(1000.0));
  EXPECT_TRUE(walkin.setRatedCoolingCoilFanPower(800.0));
  EXPECT_TRUE(walkin.setRatedCirculationFanPower(150.0));
  EXPECT_TRUE(walkin.setRatedTotalLightingPower(150.0));
  EXPECT_TRUE(walkin.setDefrostType("HotFluid"));
  EXPECT_TRUE(walkin.setDefrostControlType("TemperatureTermination"));
  EXPECT_TRUE(walkin.setDefrostPower(6000.0));
  EXPECT_TRUE(walkin.setTemperatureTerminationDefrostFractiontoIce(0.85));
  EXPECT_TRUE(walkin.setAverageRefrigerantChargeInventory(12.5));
  EXPECT_TRUE(walkin.setInsulatedFloorSurfaceArea(14.0));
  EXPECT_TRUE(walkin.setInsulatedFloorUValue(0.25));

  EXPECT_DOUBLE_EQ(5000.0, walkin.ratedCoilCoolingCapacity());
  EXPECT_DOUBLE_EQ(-5.0, walkin.operatingTemperature());
  EXPECT_DOUBLE_EQ(-7.0, walkin.ratedCoolingSourceTemperature());
  EXPECT_DOUBLE_EQ(1000.0, walkin.ratedTotalHeatingPower());
  EXPECT_DOUBLE_EQ(800.0, walkin.ratedCoolingCoilFanPower());
  EXPECT_DOUBLE_EQ(150.0, walkin.ratedCirculationFanPower());
  EXPECT_DOUBLE_EQ(150.0, walkin.ratedTotalLightingPower());
  EXPECT_EQ("HotFluid", walkin.defrostType());
  EXPECT_EQ("TemperatureTermination", walkin.defrostControlType());
  ASSERT_TRUE(walkin.defrostPower());
  EXPECT_DOUBLE_EQ(6000.0, walkin.defrostPower().get());
  ASSERT_TRUE(walkin.temperatureTerminationDefrostFractiontoIce());
  EXPECT_DOUBLE_EQ(0.85, walkin.temperatureTerminationDefrostFractiontoIce().get());
  EXPECT_DOUBLE_EQ(12.5, walkin.averageRefrigerantChargeInventory());
  EXPECT_DOUBLE_EQ(14.0, walkin.insulatedFloorSurfaceArea());
  EXPECT_DOUBLE_EQ(0.25, walkin.insulatedFloorUValue());
  EXPECT_FALSE(walkin.isInsulatedFloorUValueDefaulted());
}
