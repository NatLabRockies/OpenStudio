/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplatePlantChiller.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplatePlantChiller_DefaultConstructor) {
  Model model;
  HVACTemplatePlantChiller object(model);
  EXPECT_EQ(HVACTemplatePlantChiller::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplatePlantChiller_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplatePlantChiller object(model);

  EXPECT_TRUE(object.setChillerType("ElectricCentrifugalChiller"));
  EXPECT_EQ("ElectricCentrifugalChiller", object.chillerType());

  EXPECT_TRUE(object.setCapacity(150000.0));
  ASSERT_TRUE(object.capacity());
  EXPECT_DOUBLE_EQ(150000.0, object.capacity().get());
  EXPECT_FALSE(object.isCapacityAutosized());
  EXPECT_FALSE(object.isCapacityDefaulted());
  object.autosizeCapacity();
  EXPECT_TRUE(object.isCapacityAutosized());
  object.resetCapacity();
  EXPECT_TRUE(object.isCapacityDefaulted());

  EXPECT_TRUE(object.setNominalCOP(4.5));
  EXPECT_DOUBLE_EQ(4.5, object.nominalCOP());

  EXPECT_TRUE(object.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", object.condenserType());
  EXPECT_FALSE(object.isCondenserTypeDefaulted());
  object.resetCondenserType();
  EXPECT_TRUE(object.isCondenserTypeDefaulted());

  EXPECT_TRUE(object.setPriority("2"));
  ASSERT_TRUE(object.priority());
  EXPECT_EQ("2", object.priority().get());
  object.resetPriority();
  ASSERT_TRUE(object.priority());
  EXPECT_NE("2", object.priority().get());

  EXPECT_TRUE(object.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, object.sizingFactor());
  EXPECT_FALSE(object.isSizingFactorDefaulted());
  object.resetSizingFactor();
  EXPECT_TRUE(object.isSizingFactorDefaulted());

  EXPECT_TRUE(object.setMinimumPartLoadRatio(0.1));
  EXPECT_DOUBLE_EQ(0.1, object.minimumPartLoadRatio());
  EXPECT_TRUE(object.setMaximumPartLoadRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, object.maximumPartLoadRatio());
  EXPECT_TRUE(object.setOptimumPartLoadRatio(0.75));
  EXPECT_DOUBLE_EQ(0.75, object.optimumPartLoadRatio());
  EXPECT_TRUE(object.setMinimumUnloadingRatio(0.3));
  EXPECT_DOUBLE_EQ(0.3, object.minimumUnloadingRatio());

  EXPECT_TRUE(object.setLeavingChilledWaterLowerTemperatureLimit(4.0));
  EXPECT_DOUBLE_EQ(4.0, object.leavingChilledWaterLowerTemperatureLimit());
  EXPECT_FALSE(object.isLeavingChilledWaterLowerTemperatureLimitDefaulted());
  object.resetLeavingChilledWaterLowerTemperatureLimit();
  EXPECT_TRUE(object.isLeavingChilledWaterLowerTemperatureLimitDefaulted());

  EXPECT_FALSE(object.setCapacity(0.0));
  EXPECT_FALSE(object.setNominalCOP(0.0));
  EXPECT_FALSE(object.setSizingFactor(0.0));
  EXPECT_FALSE(object.setMaximumPartLoadRatio(0.0));
  EXPECT_FALSE(object.setOptimumPartLoadRatio(0.0));

  EXPECT_GE(HVACTemplatePlantChiller::chillerTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplatePlantChiller::condenserTypeValues().size(), 1u);
}
