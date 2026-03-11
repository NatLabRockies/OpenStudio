/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationCompressor.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCompressor_DefaultConstructor) {
  Model model;
  RefrigerationCompressor compressor(model);

  EXPECT_EQ(RefrigerationCompressor::iddObjectType(), compressor.iddObjectType());
  EXPECT_FALSE(compressor.ratedSuperheat());
  EXPECT_FALSE(compressor.ratedReturnGasTemperature());
  EXPECT_FALSE(compressor.ratedLiquidTemperature());
  EXPECT_FALSE(compressor.ratedSubcooling());
  EXPECT_TRUE(compressor.isEndUseSubcategoryDefaulted());
  EXPECT_TRUE(compressor.isModeofOperationDefaulted());
  EXPECT_EQ("Subcritical", compressor.modeofOperation());
}

TEST_F(EPModelFixture, RefrigerationCompressor_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCompressor compressor(model);

  EXPECT_TRUE(compressor.setRatedSuperheat(4.0));
  ASSERT_TRUE(compressor.ratedSuperheat());
  EXPECT_DOUBLE_EQ(4.0, compressor.ratedSuperheat().get());
  compressor.resetRatedSuperheat();
  EXPECT_FALSE(compressor.ratedSuperheat());

  EXPECT_TRUE(compressor.setRatedReturnGasTemperature(18.0));
  ASSERT_TRUE(compressor.ratedReturnGasTemperature());
  EXPECT_DOUBLE_EQ(18.0, compressor.ratedReturnGasTemperature().get());
  compressor.resetRatedReturnGasTemperature();
  EXPECT_FALSE(compressor.ratedReturnGasTemperature());

  EXPECT_TRUE(compressor.setRatedLiquidTemperature(20.0));
  ASSERT_TRUE(compressor.ratedLiquidTemperature());
  EXPECT_DOUBLE_EQ(20.0, compressor.ratedLiquidTemperature().get());
  compressor.resetRatedLiquidTemperature();
  EXPECT_FALSE(compressor.ratedLiquidTemperature());

  EXPECT_TRUE(compressor.setRatedSubcooling(2.5));
  ASSERT_TRUE(compressor.ratedSubcooling());
  EXPECT_DOUBLE_EQ(2.5, compressor.ratedSubcooling().get());
  compressor.resetRatedSubcooling();
  EXPECT_FALSE(compressor.ratedSubcooling());

  EXPECT_TRUE(compressor.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", compressor.endUseSubcategory());
  EXPECT_FALSE(compressor.isEndUseSubcategoryDefaulted());
  compressor.resetEndUseSubcategory();
  EXPECT_TRUE(compressor.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(compressor.setModeofOperation("Transcritical"));
  EXPECT_EQ("Transcritical", compressor.modeofOperation());
  EXPECT_FALSE(compressor.isModeofOperationDefaulted());
  compressor.resetModeofOperation();
  EXPECT_TRUE(compressor.isModeofOperationDefaulted());
  EXPECT_EQ("Subcritical", compressor.modeofOperation());
}
