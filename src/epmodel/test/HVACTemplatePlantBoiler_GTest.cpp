/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HVACTemplatePlantBoiler.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantBoiler_DefaultConstructor) {
  Model model;
  HVACTemplatePlantBoiler object(model);
  EXPECT_EQ(HVACTemplatePlantBoiler::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantBoiler_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantBoiler object(model);

  EXPECT_TRUE(object.setBoilerType("HotWaterBoiler"));
  EXPECT_EQ("HotWaterBoiler", object.boilerType());

  EXPECT_TRUE(object.setCapacity(120000.0));
  ASSERT_TRUE(object.capacity());
  EXPECT_DOUBLE_EQ(120000.0, object.capacity().get());
  EXPECT_FALSE(object.isCapacityAutosized());
  EXPECT_FALSE(object.isCapacityDefaulted());
  object.autosizeCapacity();
  EXPECT_TRUE(object.isCapacityAutosized());
  object.resetCapacity();
  EXPECT_TRUE(object.isCapacityDefaulted());

  EXPECT_TRUE(object.setEfficiency(0.92));
  EXPECT_DOUBLE_EQ(0.92, object.efficiency());
  EXPECT_FALSE(object.isEfficiencyDefaulted());
  object.resetEfficiency();
  EXPECT_TRUE(object.isEfficiencyDefaulted());

  EXPECT_TRUE(object.setFuelType("Diesel"));
  ASSERT_TRUE(object.fuelType());
  EXPECT_EQ("Diesel", object.fuelType().get());
  object.resetFuelType();
  ASSERT_TRUE(object.fuelType());
  EXPECT_NE("Diesel", object.fuelType().get());

  EXPECT_TRUE(object.setPriority("7"));
  ASSERT_TRUE(object.priority());
  EXPECT_EQ("7", object.priority().get());
  object.resetPriority();
  ASSERT_TRUE(object.priority());
  EXPECT_NE("7", object.priority().get());

  EXPECT_TRUE(object.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, object.sizingFactor());
  EXPECT_FALSE(object.isSizingFactorDefaulted());

  EXPECT_TRUE(object.setMinimumPartLoadRatio(0.15));
  EXPECT_DOUBLE_EQ(0.15, object.minimumPartLoadRatio());
  EXPECT_FALSE(object.isMinimumPartLoadRatioDefaulted());

  EXPECT_TRUE(object.setMaximumPartLoadRatio(1.05));
  EXPECT_DOUBLE_EQ(1.05, object.maximumPartLoadRatio());
  EXPECT_FALSE(object.isMaximumPartLoadRatioDefaulted());

  EXPECT_TRUE(object.setOptimumPartLoadRatio(0.85));
  EXPECT_DOUBLE_EQ(0.85, object.optimumPartLoadRatio());
  EXPECT_FALSE(object.isOptimumPartLoadRatioDefaulted());

  EXPECT_TRUE(object.setWaterOutletUpperTemperatureLimit(95.0));
  EXPECT_DOUBLE_EQ(95.0, object.waterOutletUpperTemperatureLimit());
  EXPECT_FALSE(object.isWaterOutletUpperTemperatureLimitDefaulted());
  object.resetWaterOutletUpperTemperatureLimit();
  EXPECT_TRUE(object.isWaterOutletUpperTemperatureLimitDefaulted());

  EXPECT_TRUE(object.setTemplatePlantLoopType("MixedWater"));
  ASSERT_TRUE(object.templatePlantLoopType());
  EXPECT_EQ("MixedWater", object.templatePlantLoopType().get());
  object.resetTemplatePlantLoopType();
  ASSERT_TRUE(object.templatePlantLoopType());
  EXPECT_NE("MixedWater", object.templatePlantLoopType().get());

  EXPECT_FALSE(object.setCapacity(0.0));
  EXPECT_FALSE(object.setEfficiency(-0.1));
  EXPECT_FALSE(object.setEfficiency(1.2));
  EXPECT_FALSE(object.setSizingFactor(0.0));
  EXPECT_FALSE(object.setMinimumPartLoadRatio(-0.1));
  EXPECT_FALSE(object.setMaximumPartLoadRatio(-0.1));
  EXPECT_FALSE(object.setOptimumPartLoadRatio(-0.1));

  EXPECT_GE(HVACTemplatePlantBoiler::boilerTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantBoiler::fuelTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantBoiler::templatePlantLoopTypeValues().size(), 1u);
}
