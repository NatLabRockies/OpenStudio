/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoolingTowerVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerVariableSpeed_DefaultConstructor) {
  Model model;
  CoolingTowerVariableSpeed coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_VariableSpeed), coolingTower.iddObject().type());
  EXPECT_FALSE(coolingTower.nameString().empty());
}

TEST_F(EPModelFixture, CoolingTowerVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerVariableSpeed coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_VariableSpeed), coolingTower.iddObject().type());

  coolingTower.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coolingTower.isDesignWaterFlowRateAutosized());
  EXPECT_TRUE(coolingTower.setDesignWaterFlowRate(0.0123));
  ASSERT_TRUE(coolingTower.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0123, *coolingTower.designWaterFlowRate());

  EXPECT_TRUE(coolingTower.setDesignAirFlowRate(4.56));
  ASSERT_TRUE(coolingTower.designAirFlowRate());
  EXPECT_DOUBLE_EQ(4.56, *coolingTower.designAirFlowRate());

  EXPECT_TRUE(coolingTower.setDesignFanPower(7800.0));
  ASSERT_TRUE(coolingTower.designFanPower());
  EXPECT_DOUBLE_EQ(7800.0, *coolingTower.designFanPower());

  EXPECT_TRUE(coolingTower.setMinimumAirFlowRateRatio(0.25));
  ASSERT_TRUE(coolingTower.minimumAirFlowRateRatio());
  EXPECT_DOUBLE_EQ(0.25, *coolingTower.minimumAirFlowRateRatio());

  EXPECT_TRUE(coolingTower.setNumberofCells(2));
  ASSERT_TRUE(coolingTower.numberofCells());
  EXPECT_EQ(2, *coolingTower.numberofCells());
}
