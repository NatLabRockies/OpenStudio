/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoolingTowerVariableSpeedMerkel.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoolingTowerVariableSpeedMerkel_DefaultConstructor) {
  Model model;
  CoolingTowerVariableSpeedMerkel coolingTower(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoolingTower_VariableSpeed_Merkel), coolingTower.iddObject().type());
  EXPECT_FALSE(coolingTower.nameString().empty());
}

TEST_F(EPModelFixture, CoolingTowerVariableSpeedMerkel_ScalarAccessors_RoundTrip) {
  Model model;
  CoolingTowerVariableSpeedMerkel coolingTower(model);

  EXPECT_TRUE(coolingTower.setPerformanceInputMethod("NominalCapacity"));
  EXPECT_EQ("NominalCapacity", coolingTower.performanceInputMethod());

  coolingTower.autosizeNominalCapacity();
  EXPECT_TRUE(coolingTower.isNominalCapacityAutosized());
  EXPECT_TRUE(coolingTower.setNominalCapacity(120000.0));
  ASSERT_TRUE(coolingTower.nominalCapacity());
  EXPECT_DOUBLE_EQ(120000.0, *coolingTower.nominalCapacity());

  coolingTower.autocalculateFreeConvectionNominalCapacity();
  EXPECT_TRUE(coolingTower.isFreeConvectionNominalCapacityAutocalculated());
  EXPECT_TRUE(coolingTower.setFreeConvectionNominalCapacity(12000.0));
  ASSERT_TRUE(coolingTower.freeConvectionNominalCapacity());
  EXPECT_DOUBLE_EQ(12000.0, *coolingTower.freeConvectionNominalCapacity());

  EXPECT_TRUE(coolingTower.setDesignWaterFlowRate(0.0123));
  ASSERT_TRUE(coolingTower.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0123, *coolingTower.designWaterFlowRate());

  coolingTower.autocalculateDesignAirFlowRate();
  EXPECT_TRUE(coolingTower.isDesignAirFlowRateAutocalculated());
  EXPECT_TRUE(coolingTower.setDesignAirFlowRate(4.56));
  ASSERT_TRUE(coolingTower.designAirFlowRate());
  EXPECT_DOUBLE_EQ(4.56, *coolingTower.designAirFlowRate());

  coolingTower.autocalculateDesignFanPower();
  EXPECT_TRUE(coolingTower.isDesignFanPowerAutocalculated());
  EXPECT_TRUE(coolingTower.setDesignFanPower(7800.0));
  ASSERT_TRUE(coolingTower.designFanPower());
  EXPECT_DOUBLE_EQ(7800.0, *coolingTower.designFanPower());

  EXPECT_TRUE(coolingTower.setEvaporationLossMode("SaturatedExit"));
  EXPECT_EQ("SaturatedExit", coolingTower.evaporationLossMode());

  EXPECT_TRUE(coolingTower.setNumberofCells(2));
  EXPECT_EQ(2, coolingTower.numberofCells());
}
