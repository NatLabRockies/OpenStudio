/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WaterUseWell.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterUseWell_DefaultConstructor) {
  Model model;
  WaterUseWell well(model);
  EXPECT_EQ(WaterUseWell::iddObjectType(), well.iddObject().type());
}

TEST_F(EPModelFixture, WaterUseWell_ScalarAccessors_RoundTrip) {
  Model model;
  WaterUseWell well(model);

  EXPECT_TRUE(well.setPumpDepth(55.0));
  ASSERT_TRUE(well.pumpDepth());
  EXPECT_DOUBLE_EQ(55.0, *well.pumpDepth());

  EXPECT_TRUE(well.setPumpRatedFlowRate(0.015));
  ASSERT_TRUE(well.pumpRatedFlowRate());
  EXPECT_DOUBLE_EQ(0.015, *well.pumpRatedFlowRate());

  EXPECT_TRUE(well.setPumpRatedHead(120000.0));
  ASSERT_TRUE(well.pumpRatedHead());
  EXPECT_DOUBLE_EQ(120000.0, *well.pumpRatedHead());

  EXPECT_TRUE(well.setPumpRatedPowerConsumption(3500.0));
  ASSERT_TRUE(well.pumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(3500.0, *well.pumpRatedPowerConsumption());

  EXPECT_TRUE(well.setPumpEfficiency(0.72));
  ASSERT_TRUE(well.pumpEfficiency());
  EXPECT_DOUBLE_EQ(0.72, *well.pumpEfficiency());

  EXPECT_TRUE(well.setWellRecoveryRate(0.0006));
  ASSERT_TRUE(well.wellRecoveryRate());
  EXPECT_DOUBLE_EQ(0.0006, *well.wellRecoveryRate());

  EXPECT_TRUE(well.setNominalWellStorageVolume(12.5));
  ASSERT_TRUE(well.nominalWellStorageVolume());
  EXPECT_DOUBLE_EQ(12.5, *well.nominalWellStorageVolume());

  EXPECT_TRUE(well.setWaterTableDepthMode("Constant"));
  ASSERT_TRUE(well.waterTableDepthMode());
  EXPECT_EQ("Constant", *well.waterTableDepthMode());

  EXPECT_TRUE(well.setWaterTableDepth(7.4));
  ASSERT_TRUE(well.waterTableDepth());
  EXPECT_DOUBLE_EQ(7.4, *well.waterTableDepth());
}
