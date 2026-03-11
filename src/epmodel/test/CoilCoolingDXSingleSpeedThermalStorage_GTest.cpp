/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeedThermalStorage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeedThermalStorage_DefaultConstructor) {
  Model model;
  CoilCoolingDXSingleSpeedThermalStorage coil(model);
  EXPECT_EQ(CoilCoolingDXSingleSpeedThermalStorage::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeedThermalStorage_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeedThermalStorage coil(model);

  ASSERT_FALSE(CoilCoolingDXSingleSpeedThermalStorage::operatingModeControlMethodValues().empty());
  ASSERT_FALSE(CoilCoolingDXSingleSpeedThermalStorage::storageTypeValues().empty());
  ASSERT_FALSE(CoilCoolingDXSingleSpeedThermalStorage::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setOperatingModeControlMethod("ScheduledModes"));
  EXPECT_EQ("ScheduledModes", coil.operatingModeControlMethod());

  EXPECT_TRUE(coil.setStorageType("Ice"));
  EXPECT_EQ("Ice", coil.storageType());

  coil.autosizeRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(1.15));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(1.15, *coil.ratedEvaporatorAirFlowRate());

  EXPECT_TRUE(coil.setCoolingOnlyModeAvailable(true));
  EXPECT_TRUE(coil.coolingOnlyModeAvailable());

  coil.autosizeCoolingAndDischargeModeRatedStorageDischargingCapacity();
  EXPECT_TRUE(coil.isCoolingAndDischargeModeRatedStorageDischargingCapacityAutosized());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setColdWeatherOperationMinimumOutdoorAirTemperature(-7.0));
  ASSERT_TRUE(coil.coldWeatherOperationMinimumOutdoorAirTemperature());
  EXPECT_DOUBLE_EQ(-7.0, *coil.coldWeatherOperationMinimumOutdoorAirTemperature());
  coil.resetColdWeatherOperationMinimumOutdoorAirTemperature();
  EXPECT_FALSE(coil.coldWeatherOperationMinimumOutdoorAirTemperature());
}
