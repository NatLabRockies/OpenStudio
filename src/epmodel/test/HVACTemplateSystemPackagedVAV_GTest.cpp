/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplateSystemPackagedVAV.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemPackagedVAV_DefaultConstructor) {
  Model model;
  HVACTemplateSystemPackagedVAV object(model);
  EXPECT_EQ(HVACTemplateSystemPackagedVAV::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemPackagedVAV_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemPackagedVAV object(model);

  EXPECT_TRUE(object.setSupplyFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", object.supplyFanPlacement());

  EXPECT_TRUE(object.setSupplyFanMaximumFlowRate(1.2));
  ASSERT_TRUE(object.supplyFanMaximumFlowRate());
  EXPECT_DOUBLE_EQ(1.2, object.supplyFanMaximumFlowRate().get());
  EXPECT_FALSE(object.isSupplyFanMaximumFlowRateAutosized());
  object.autosizeSupplyFanMaximumFlowRate();
  EXPECT_TRUE(object.isSupplyFanMaximumFlowRateAutosized());

  EXPECT_TRUE(object.setCoolingCoilGrossRatedTotalCapacity(5000.0));
  ASSERT_TRUE(object.coolingCoilGrossRatedTotalCapacity());
  EXPECT_DOUBLE_EQ(5000.0, object.coolingCoilGrossRatedTotalCapacity().get());
  object.autosizeCoolingCoilGrossRatedTotalCapacity();
  EXPECT_TRUE(object.isCoolingCoilGrossRatedTotalCapacityAutosized());

  EXPECT_TRUE(object.setEconomizerMaximumLimitDryBulbTemperature(26.0));
  ASSERT_TRUE(object.economizerMaximumLimitDryBulbTemperature());
  EXPECT_DOUBLE_EQ(26.0, object.economizerMaximumLimitDryBulbTemperature().get());
  object.resetEconomizerMaximumLimitDryBulbTemperature();
  EXPECT_FALSE(object.economizerMaximumLimitDryBulbTemperature());

  EXPECT_TRUE(object.setReturnFan(true));
  EXPECT_TRUE(object.returnFan());
  EXPECT_TRUE(object.setReturnFanTotalEfficiency(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.returnFanTotalEfficiency());

  EXPECT_FALSE(object.setSupplyFanPlacement("InvalidChoice"));
  EXPECT_FALSE(object.setSupplyFanTotalEfficiency(0.0));

  EXPECT_GE(HVACTemplateSystemPackagedVAV::economizerTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemPackagedVAV::nightCycleControlValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemPackagedVAV::humidifierTypeValues().size(), 1u);
}
