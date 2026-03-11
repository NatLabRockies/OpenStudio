/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoolingTowerTwoSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_DefaultConstructor) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_TwoSpeed), coolingTower.iddObject().type());
  EXPECT_FALSE(coolingTower.nameString().empty());
}

TEST_F(EPModelFixture, CoolingTowerTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerTwoSpeed coolingTower(model);

  EXPECT_FALSE(CoolingTowerTwoSpeed::performanceInputMethodValues().empty());
  EXPECT_FALSE(CoolingTowerTwoSpeed::evaporationLossModeValues().empty());
  EXPECT_FALSE(CoolingTowerTwoSpeed::blowdownCalculationModeValues().empty());
  EXPECT_FALSE(CoolingTowerTwoSpeed::cellControlValues().empty());

  coolingTower.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  EXPECT_TRUE(coolingTower.setDesignWaterFlowRate(0.02));
  ASSERT_TRUE(coolingTower.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.02, *coolingTower.designWaterFlowRate());

  EXPECT_TRUE(coolingTower.setHighFanSpeedAirFlowRate(4.2));
  ASSERT_TRUE(coolingTower.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(4.2, *coolingTower.highFanSpeedAirFlowRate());

  EXPECT_TRUE(coolingTower.setHighFanSpeedFanPower(1200.0));
  ASSERT_TRUE(coolingTower.highFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(1200.0, *coolingTower.highFanSpeedFanPower());

  coolingTower.autosizeLowFanSpeedAirFlowRate();
  EXPECT_TRUE(coolingTower.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coolingTower.setPerformanceInputMethod("NominalCapacity"));
  EXPECT_EQ("NominalCapacity", coolingTower.performanceInputMethod());

  EXPECT_TRUE(coolingTower.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", coolingTower.evaporationLossMode());

  EXPECT_TRUE(coolingTower.setBlowdownCalculationMode("ConcentrationRatio"));
  EXPECT_EQ("ConcentrationRatio", coolingTower.blowdownCalculationMode());

  EXPECT_TRUE(coolingTower.setNumberofCells(2));
  EXPECT_EQ(2, coolingTower.numberofCells());

  EXPECT_TRUE(coolingTower.setCellControl("MaximalCell"));
  EXPECT_EQ("MaximalCell", coolingTower.cellControl());

  EXPECT_TRUE(coolingTower.setDesignInletAirDryBulbTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, coolingTower.designInletAirDryBulbTemperature());

  EXPECT_TRUE(coolingTower.setDesignInletAirWetBulbTemperature(25.6));
  EXPECT_DOUBLE_EQ(25.6, coolingTower.designInletAirWetBulbTemperature());

  coolingTower.autosizeDesignApproachTemperature();
  EXPECT_TRUE(coolingTower.isDesignApproachTemperatureAutosized());
  EXPECT_TRUE(coolingTower.setDesignApproachTemperature(5.0));
  ASSERT_TRUE(coolingTower.designApproachTemperature());
  EXPECT_DOUBLE_EQ(5.0, *coolingTower.designApproachTemperature());

  coolingTower.autosizeDesignRangeTemperature();
  EXPECT_TRUE(coolingTower.isDesignRangeTemperatureAutosized());
  EXPECT_TRUE(coolingTower.setDesignRangeTemperature(5.5));
  ASSERT_TRUE(coolingTower.designRangeTemperature());
  EXPECT_DOUBLE_EQ(5.5, *coolingTower.designRangeTemperature());

  EXPECT_TRUE(coolingTower.setEndUseSubcategory("Heat Rejection"));
  EXPECT_EQ("Heat Rejection", coolingTower.endUseSubcategory());
}
