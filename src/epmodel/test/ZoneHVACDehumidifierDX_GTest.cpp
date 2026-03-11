/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACDehumidifierDX.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACDehumidifierDX_DefaultConstructor) {
  Model model;
  ZoneHVACDehumidifierDX dehumidifier(model);
  EXPECT_EQ(ZoneHVACDehumidifierDX::iddObjectType(), dehumidifier.iddObject().type());
  EXPECT_DOUBLE_EQ(50.16, dehumidifier.ratedWaterRemoval());
  EXPECT_DOUBLE_EQ(3.412, dehumidifier.ratedEnergyFactor());
  EXPECT_DOUBLE_EQ(0.12036, dehumidifier.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(10.0, dehumidifier.minimumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(32.0, dehumidifier.maximumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(0.0, dehumidifier.offCycleParasiticElectricLoad());
}

TEST_F(EPModelFixture, ZoneHVACDehumidifierDX_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACDehumidifierDX dehumidifier(model);

  EXPECT_TRUE(dehumidifier.setRatedWaterRemoval(60.5));
  EXPECT_TRUE(dehumidifier.setRatedEnergyFactor(4.001));
  EXPECT_TRUE(dehumidifier.setRatedAirFlowRate(0.150));
  EXPECT_TRUE(dehumidifier.setMinimumDryBulbTemperatureforDehumidifierOperation(12.0));
  EXPECT_TRUE(dehumidifier.setMaximumDryBulbTemperatureforDehumidifierOperation(34.0));
  EXPECT_TRUE(dehumidifier.setOffCycleParasiticElectricLoad(2.5));

  EXPECT_DOUBLE_EQ(60.5, dehumidifier.ratedWaterRemoval());
  EXPECT_DOUBLE_EQ(4.001, dehumidifier.ratedEnergyFactor());
  EXPECT_DOUBLE_EQ(0.150, dehumidifier.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(12.0, dehumidifier.minimumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(34.0, dehumidifier.maximumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(2.5, dehumidifier.offCycleParasiticElectricLoad());
}
