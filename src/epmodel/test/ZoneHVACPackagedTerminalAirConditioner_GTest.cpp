/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_DefaultConstructor) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_FALSE(ptac.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(ptac.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(ptac.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(ptac.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(ptac.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(ptac.isFanPlacementDefaulted());
  EXPECT_EQ("", ptac.fanPlacement());
}

TEST_F(EPModelFixture, ZoneHVACPackagedTerminalAirConditioner_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACPackagedTerminalAirConditioner ptac(model);

  EXPECT_TRUE(ptac.setSupplyAirFlowRateDuringCoolingOperation(0.5));
  ASSERT_TRUE(ptac.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.5, ptac.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  ptac.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(ptac.supplyAirFlowRateDuringCoolingOperation());

  EXPECT_TRUE(ptac.setSupplyAirFlowRateDuringHeatingOperation(0.55));
  ASSERT_TRUE(ptac.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.55, ptac.supplyAirFlowRateDuringHeatingOperation().get());
  ptac.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(ptac.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.12));
  ASSERT_TRUE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.12, ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  ptac.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(ptac.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  ptac.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(ptac.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(ptac.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(ptac.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateDuringCoolingOperation(0.09));
  ptac.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateDuringHeatingOperation(0.06));
  ptac.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(ptac.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ptac.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(ptac.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  ptac.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(ptac.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(ptac.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", ptac.fanPlacement());
  ptac.resetFanPlacement();
  EXPECT_TRUE(ptac.isFanPlacementDefaulted());
}
