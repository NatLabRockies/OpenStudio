/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_DefaultConstructor) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);
  EXPECT_EQ(CoilHeatingDXSingleSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalHeatingCapacity());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());

  EXPECT_DOUBLE_EQ(5.0, coil.ratedCOP());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedSupplyFanPowerPerVolumeFlowRate());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedSupplyFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedSupplyFanPowerPerVolumeFlowRate2023());

  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("Timed", coil.defrostControl());
  EXPECT_NEAR(0.166667, coil.defrostTimePeriodFraction(), 1e-6);
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(2000.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  EXPECT_TRUE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);

  ASSERT_FALSE(CoilHeatingDXSingleSpeed::validDefrostStrategyValues().empty());
  ASSERT_FALSE(CoilHeatingDXSingleSpeed::validDefrostControlValues().empty());

  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalHeatingCapacity());
  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(15000.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(15000.0, *coil.ratedTotalHeatingCapacity());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedCOP(4.2));
  EXPECT_DOUBLE_EQ(4.2, coil.ratedCOP());

  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());
  EXPECT_TRUE(coil.setRatedAirFlowRate(1.2));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, *coil.ratedAirFlowRate());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedSupplyFanPowerPerVolumeFlowRate(800.0));
  EXPECT_DOUBLE_EQ(800.0, coil.ratedSupplyFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedSupplyFanPowerPerVolumeFlowRate2023(950.0));
  EXPECT_DOUBLE_EQ(950.0, coil.ratedSupplyFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_FALSE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  coil.resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_TRUE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforDefrostOperation(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_FALSE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());
  coil.resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(120.0));
  EXPECT_DOUBLE_EQ(120.0, coil.crankcaseHeaterCapacity());
  EXPECT_FALSE(coil.isCrankcaseHeaterCapacityDefaulted());
  coil.resetCrankcaseHeaterCapacity();
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.5));
  EXPECT_DOUBLE_EQ(9.5, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_FALSE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());
  coil.resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());

  EXPECT_TRUE(coil.setDefrostStrategy("ReverseCycle"));
  EXPECT_EQ("ReverseCycle", coil.defrostStrategy());
  EXPECT_FALSE(coil.isDefrostStrategyDefaulted());
  coil.resetDefrostStrategy();
  EXPECT_TRUE(coil.isDefrostStrategyDefaulted());

  EXPECT_TRUE(coil.setDefrostControl("OnDemand"));
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_FALSE(coil.isDefrostControlDefaulted());
  coil.resetDefrostControl();
  EXPECT_TRUE(coil.isDefrostControlDefaulted());

  EXPECT_TRUE(coil.setDefrostTimePeriodFraction(0.1));
  EXPECT_DOUBLE_EQ(0.1, coil.defrostTimePeriodFraction());
  EXPECT_FALSE(coil.isDefrostTimePeriodFractionDefaulted());
  coil.resetDefrostTimePeriodFraction();
  EXPECT_TRUE(coil.isDefrostTimePeriodFractionDefaulted());

  EXPECT_TRUE(coil.setResistiveDefrostHeaterCapacity(450.0));
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(450.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityDefaulted());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  coil.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());

  coil.resetResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityDefaulted());
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(0.0, *coil.resistiveDefrostHeaterCapacity());
}
