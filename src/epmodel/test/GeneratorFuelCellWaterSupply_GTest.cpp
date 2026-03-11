/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelCellWaterSupply.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellWaterSupply_DefaultConstructor) {
  Model model;
  GeneratorFuelCellWaterSupply waterSupply(model);
  EXPECT_EQ(GeneratorFuelCellWaterSupply::iddObjectType(), waterSupply.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellWaterSupply_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellWaterSupply waterSupply(model);

  EXPECT_TRUE(waterSupply.setPumpHeatLossFactor(0.38));
  EXPECT_DOUBLE_EQ(0.38, waterSupply.pumpHeatLossFactor());
  waterSupply.resetPumpHeatLossFactor();
  EXPECT_DOUBLE_EQ(0.0, waterSupply.pumpHeatLossFactor());

  const auto modes = GeneratorFuelCellWaterSupply::waterTemperatureModelingModeValues();
  ASSERT_FALSE(modes.empty());
  EXPECT_TRUE(waterSupply.setWaterTemperatureModelingMode(modes.back()));
  EXPECT_EQ(modes.back(), waterSupply.waterTemperatureModelingMode());
  waterSupply.resetWaterTemperatureModelingMode();
  EXPECT_EQ("TemperatureFromSchedule", waterSupply.waterTemperatureModelingMode());
}
