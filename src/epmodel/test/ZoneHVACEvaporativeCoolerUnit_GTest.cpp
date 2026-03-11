/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_DefaultConstructor) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);

  EXPECT_EQ(ZoneHVACEvaporativeCoolerUnit::iddObjectType(), cooler.iddObject().type());
  EXPECT_TRUE(cooler.isDesignSupplyAirFlowRateAutosized());
  EXPECT_EQ("BlowThrough", cooler.fanPlacement());
  EXPECT_EQ("ZoneTemperatureDeadbandOnOffCycling", cooler.coolerUnitControlMethod());
  EXPECT_DOUBLE_EQ(1.0, cooler.throttlingRangeTemperatureDifference());
  EXPECT_DOUBLE_EQ(100.0, cooler.coolingLoadControlThresholdHeatTransferRate());
  EXPECT_DOUBLE_EQ(100.0, cooler.shutOffRelativeHumidity());
}

TEST_F(EPModelFixture, ZoneHVACEvaporativeCoolerUnit_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEvaporativeCoolerUnit cooler(model);

  EXPECT_TRUE(cooler.setDesignSupplyAirFlowRate(0.5));
  EXPECT_FALSE(cooler.isDesignSupplyAirFlowRateAutosized());
  EXPECT_TRUE(cooler.setFanPlacement("DrawThrough"));
  EXPECT_TRUE(cooler.setCoolerUnitControlMethod("ZoneCoolingLoadOnOffCycling"));
  EXPECT_TRUE(cooler.setThrottlingRangeTemperatureDifference(2.0));
  EXPECT_TRUE(cooler.setCoolingLoadControlThresholdHeatTransferRate(200.0));
  EXPECT_TRUE(cooler.setShutOffRelativeHumidity(40.0));

  ASSERT_TRUE(cooler.designSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, cooler.designSupplyAirFlowRate().value());
  EXPECT_EQ("DrawThrough", cooler.fanPlacement());
  EXPECT_EQ("ZoneCoolingLoadOnOffCycling", cooler.coolerUnitControlMethod());
  EXPECT_DOUBLE_EQ(2.0, cooler.throttlingRangeTemperatureDifference());
  EXPECT_DOUBLE_EQ(200.0, cooler.coolingLoadControlThresholdHeatTransferRate());
  EXPECT_DOUBLE_EQ(40.0, cooler.shutOffRelativeHumidity());

  cooler.autosizeDesignSupplyAirFlowRate();
  EXPECT_TRUE(cooler.isDesignSupplyAirFlowRateAutosized());
}
