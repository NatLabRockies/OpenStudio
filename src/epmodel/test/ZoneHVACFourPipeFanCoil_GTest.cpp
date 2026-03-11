/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACFourPipeFanCoil_DefaultConstructor) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  EXPECT_EQ(ZoneHVACFourPipeFanCoil::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  const auto capacityMethods = ZoneHVACFourPipeFanCoil::capacityControlMethodValues();
  ASSERT_FALSE(capacityMethods.empty());
  EXPECT_TRUE(coil.setCapacityControlMethod(capacityMethods.front()));
  EXPECT_EQ(capacityMethods.front(), coil.capacityControlMethod());

  EXPECT_TRUE(coil.setMaximumSupplyAirFlowRate(1.2));
  ASSERT_TRUE(coil.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, coil.maximumSupplyAirFlowRate().get());
  coil.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(coil.isMaximumSupplyAirFlowRateAutosized());

  EXPECT_TRUE(coil.setLowSpeedSupplyAirFlowRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, coil.lowSpeedSupplyAirFlowRatio());
  coil.resetLowSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isLowSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMediumSpeedSupplyAirFlowRatio(0.6));
  EXPECT_DOUBLE_EQ(0.6, coil.mediumSpeedSupplyAirFlowRatio());
  coil.resetMediumSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isMediumSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorAirFlowRate(0.45));
  coil.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(coil.isMaximumOutdoorAirFlowRateAutosized());

  const auto mixerTypes = ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues();
  ASSERT_FALSE(mixerTypes.empty());
  EXPECT_TRUE(coil.setOutdoorAirMixerObjectType(mixerTypes.front()));
  EXPECT_EQ(mixerTypes.front(), coil.outdoorAirMixerObjectType());

  EXPECT_TRUE(coil.setMaximumColdWaterFlowRate(0.18));
  coil.autosizeMaximumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumColdWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumColdWaterFlowRate(0.08));
  EXPECT_DOUBLE_EQ(0.08, coil.minimumColdWaterFlowRate());
  coil.resetMinimumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumColdWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setCoolingConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, coil.coolingConvergenceTolerance());
  coil.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(coil.isCoolingConvergenceToleranceDefaulted());

  EXPECT_TRUE(coil.setMaximumHotWaterFlowRate(0.25));
  coil.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumHotWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumHotWaterFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, coil.minimumHotWaterFlowRate());
  coil.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumHotWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setHeatingConvergenceTolerance(0.003));
  EXPECT_DOUBLE_EQ(0.003, coil.heatingConvergenceTolerance());
  coil.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(coil.isHeatingConvergenceToleranceDefaulted());

  coil.autosizeMinimumSupplyAirTemperatureInCoolingMode();
  EXPECT_TRUE(coil.isMinimumSupplyAirTemperatureInCoolingModeAutosized());

  coil.autosizeMaximumSupplyAirTemperatureInHeatingMode();
  EXPECT_TRUE(coil.isMaximumSupplyAirTemperatureInHeatingModeAutosized());
}
