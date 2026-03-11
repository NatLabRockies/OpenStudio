/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/RefrigerationCondenserWaterCooled.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_DefaultConstructor) {
  Model model;
  RefrigerationCondenserWaterCooled condenser(model);
  EXPECT_EQ(RefrigerationCondenserWaterCooled::iddObjectType(), openstudio::IddObjectType::Refrigeration_Condenser_WaterCooled);
}

TEST_F(EPModelFixture, RefrigerationCondenserWaterCooled_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCondenserWaterCooled condenser(model);

  EXPECT_TRUE(condenser.setRatedEffectiveTotalHeatRejectionRate(12345.0));
  ASSERT_TRUE(condenser.ratedEffectiveTotalHeatRejectionRate());
  EXPECT_DOUBLE_EQ(12345.0, condenser.ratedEffectiveTotalHeatRejectionRate().get());
  condenser.resetRatedEffectiveTotalHeatRejectionRate();
  EXPECT_FALSE(condenser.ratedEffectiveTotalHeatRejectionRate());

  EXPECT_TRUE(condenser.setRatedCondensingTemperature(42.0));
  EXPECT_DOUBLE_EQ(42.0, condenser.ratedCondensingTemperature());

  EXPECT_TRUE(condenser.setRatedSubcoolingTemperatureDifference(2.5));
  EXPECT_FALSE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());
  condenser.resetRatedSubcoolingTemperatureDifference();
  EXPECT_TRUE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());

  EXPECT_TRUE(condenser.setRatedWaterInletTemperature(15.5));
  EXPECT_DOUBLE_EQ(15.5, condenser.ratedWaterInletTemperature());

  const auto flowTypes = RefrigerationCondenserWaterCooled::waterCooledLoopFlowTypeValues();
  ASSERT_FALSE(flowTypes.empty());
  EXPECT_TRUE(condenser.setWaterCooledLoopFlowType(flowTypes.front()));
  EXPECT_EQ(flowTypes.front(), condenser.waterCooledLoopFlowType());
  EXPECT_FALSE(condenser.isWaterCooledLoopFlowTypeDefaulted());
  condenser.resetWaterCooledLoopFlowType();
  EXPECT_TRUE(condenser.isWaterCooledLoopFlowTypeDefaulted());

  EXPECT_TRUE(condenser.setWaterDesignFlowRate(0.005));
  ASSERT_TRUE(condenser.waterDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.005, condenser.waterDesignFlowRate().get());
  condenser.resetWaterDesignFlowRate();
  EXPECT_FALSE(condenser.waterDesignFlowRate());

  EXPECT_TRUE(condenser.setWaterMaximumFlowRate(0.007));
  ASSERT_TRUE(condenser.waterMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.007, condenser.waterMaximumFlowRate().get());
  condenser.resetWaterMaximumFlowRate();
  EXPECT_FALSE(condenser.waterMaximumFlowRate());

  EXPECT_TRUE(condenser.setWaterMaximumWaterOutletTemperature(54.0));
  EXPECT_FALSE(condenser.isWaterMaximumWaterOutletTemperatureDefaulted());
  condenser.resetWaterMaximumWaterOutletTemperature();
  EXPECT_TRUE(condenser.isWaterMaximumWaterOutletTemperatureDefaulted());

  EXPECT_TRUE(condenser.setWaterMinimumWaterInletTemperature(15.0));
  EXPECT_FALSE(condenser.isWaterMinimumWaterInletTemperatureDefaulted());
  condenser.resetWaterMinimumWaterInletTemperature();
  EXPECT_TRUE(condenser.isWaterMinimumWaterInletTemperatureDefaulted());

  EXPECT_TRUE(condenser.setEndUseSubcategory("Condenser"));
  EXPECT_FALSE(condenser.isEndUseSubcategoryDefaulted());
  EXPECT_EQ("Condenser", condenser.endUseSubcategory());
  condenser.resetEndUseSubcategory();
  EXPECT_TRUE(condenser.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(condenser.setCondenserRefrigerantOperatingChargeInventory(1.5));
  ASSERT_TRUE(condenser.condenserRefrigerantOperatingChargeInventory());
  EXPECT_DOUBLE_EQ(1.5, condenser.condenserRefrigerantOperatingChargeInventory().get());
  condenser.resetCondenserRefrigerantOperatingChargeInventory();
  EXPECT_FALSE(condenser.condenserRefrigerantOperatingChargeInventory());

  EXPECT_TRUE(condenser.setCondensateReceiverRefrigerantInventory(0.25));
  ASSERT_TRUE(condenser.condensateReceiverRefrigerantInventory());
  EXPECT_DOUBLE_EQ(0.25, condenser.condensateReceiverRefrigerantInventory().get());
  condenser.resetCondensateReceiverRefrigerantInventory();
  EXPECT_FALSE(condenser.condensateReceiverRefrigerantInventory());

  EXPECT_TRUE(condenser.setCondensatePipingRefrigerantInventory(0.1));
  ASSERT_TRUE(condenser.condensatePipingRefrigerantInventory());
  EXPECT_DOUBLE_EQ(0.1, condenser.condensatePipingRefrigerantInventory().get());
  condenser.resetCondensatePipingRefrigerantInventory();
  EXPECT_FALSE(condenser.condensatePipingRefrigerantInventory());
}
