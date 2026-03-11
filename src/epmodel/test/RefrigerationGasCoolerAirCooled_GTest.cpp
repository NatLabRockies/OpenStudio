/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationGasCoolerAirCooled.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationGasCoolerAirCooled_DefaultConstructor) {
  Model model;
  RefrigerationGasCoolerAirCooled gasCooler(model);
  EXPECT_EQ(RefrigerationGasCoolerAirCooled::iddObjectType(), openstudio::IddObjectType::Refrigeration_GasCooler_AirCooled);
}

TEST_F(EPModelFixture, RefrigerationGasCoolerAirCooled_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationGasCoolerAirCooled gasCooler(model);

  const auto fanSpeedTypes = RefrigerationGasCoolerAirCooled::gasCoolerFanSpeedControlTypeValues();
  ASSERT_FALSE(fanSpeedTypes.empty());
  EXPECT_TRUE(gasCooler.setGasCoolerFanSpeedControlType(fanSpeedTypes.back()));
  EXPECT_EQ(fanSpeedTypes.back(), gasCooler.gasCoolerFanSpeedControlType());
  gasCooler.resetGasCoolerFanSpeedControlType();
  EXPECT_TRUE(gasCooler.isGasCoolerFanSpeedControlTypeDefaulted());

  EXPECT_TRUE(gasCooler.setRatedFanPower(4500.0));
  EXPECT_DOUBLE_EQ(4500.0, gasCooler.ratedFanPower());
  gasCooler.resetRatedFanPower();
  EXPECT_TRUE(gasCooler.isRatedFanPowerDefaulted());

  EXPECT_TRUE(gasCooler.setMinimumFanAirFlowRatio(0.25));
  EXPECT_DOUBLE_EQ(0.25, gasCooler.minimumFanAirFlowRatio());
  gasCooler.resetMinimumFanAirFlowRatio();
  EXPECT_TRUE(gasCooler.isMinimumFanAirFlowRatioDefaulted());

  EXPECT_TRUE(gasCooler.setTransitionTemperature(30.5));
  EXPECT_DOUBLE_EQ(30.5, gasCooler.transitionTemperature());
  gasCooler.resetTransitionTemperature();
  EXPECT_TRUE(gasCooler.isTransitionTemperatureDefaulted());

  EXPECT_TRUE(gasCooler.setTranscriticalApproachTemperature(4.2));
  EXPECT_DOUBLE_EQ(4.2, gasCooler.transcriticalApproachTemperature());
  gasCooler.resetTranscriticalApproachTemperature();
  EXPECT_TRUE(gasCooler.isTranscriticalApproachTemperatureDefaulted());

  EXPECT_TRUE(gasCooler.setSubcriticalTemperatureDifference(12.25));
  EXPECT_DOUBLE_EQ(12.25, gasCooler.subcriticalTemperatureDifference());
  gasCooler.resetSubcriticalTemperatureDifference();
  EXPECT_TRUE(gasCooler.isSubcriticalTemperatureDifferenceDefaulted());

  EXPECT_TRUE(gasCooler.setMinimumCondensingTemperature(9.0));
  EXPECT_DOUBLE_EQ(9.0, gasCooler.minimumCondensingTemperature());
  gasCooler.resetMinimumCondensingTemperature();
  EXPECT_TRUE(gasCooler.isMinimumCondensingTemperatureDefaulted());

  EXPECT_TRUE(gasCooler.setEndUseSubcategory("CustomUsage"));
  EXPECT_EQ("CustomUsage", gasCooler.endUseSubcategory());
  gasCooler.resetEndUseSubcategory();
  EXPECT_TRUE(gasCooler.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(gasCooler.setGasCoolerRefrigerantOperatingChargeInventory(1.5));
  EXPECT_DOUBLE_EQ(1.5, gasCooler.gasCoolerRefrigerantOperatingChargeInventory());
  gasCooler.resetGasCoolerRefrigerantOperatingChargeInventory();
  EXPECT_TRUE(gasCooler.isGasCoolerRefrigerantOperatingChargeInventoryDefaulted());

  EXPECT_TRUE(gasCooler.setGasCoolerReceiverRefrigerantInventory(2.5));
  EXPECT_DOUBLE_EQ(2.5, gasCooler.gasCoolerReceiverRefrigerantInventory());
  gasCooler.resetGasCoolerReceiverRefrigerantInventory();
  EXPECT_TRUE(gasCooler.isGasCoolerReceiverRefrigerantInventoryDefaulted());

  EXPECT_TRUE(gasCooler.setGasCoolerOutletPipingRefrigerantInventory(3.5));
  EXPECT_DOUBLE_EQ(3.5, gasCooler.gasCoolerOutletPipingRefrigerantInventory());
  gasCooler.resetGasCoolerOutletPipingRefrigerantInventory();
  EXPECT_TRUE(gasCooler.isGasCoolerOutletPipingRefrigerantInventoryDefaulted());
}
