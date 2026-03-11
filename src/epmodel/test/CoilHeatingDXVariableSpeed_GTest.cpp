/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingDXVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableSpeed coil(model);
  EXPECT_EQ(CoilHeatingDXVariableSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(-5.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_FALSE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  EXPECT_DOUBLE_EQ(5.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_DOUBLE_EQ(200.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_NEAR(0.166667, coil.defrostTimePeriodFraction(), 0.000001);
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableSpeed coil(model);

  ASSERT_FALSE(CoilHeatingDXVariableSpeed::defrostStrategyValues().empty());
  ASSERT_FALSE(CoilHeatingDXVariableSpeed::defrostControlValues().empty());

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  coil.autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_TRUE(coil.setRatedHeatingCapacityAtSelectedNominalSpeedLevel(10000.0));
  ASSERT_TRUE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(10000.0, *coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_FALSE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());

  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(1.2));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(1.2, *coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setOutdoorDryBulbTemperaturetoTurnOnCompressor(4.0));
  ASSERT_TRUE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  EXPECT_DOUBLE_EQ(4.0, *coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  coil.resetOutdoorDryBulbTemperaturetoTurnOnCompressor();
  EXPECT_FALSE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforDefrostOperation(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(50.0));
  EXPECT_DOUBLE_EQ(50.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(coil.setDefrostStrategy("ReverseCycle"));
  EXPECT_EQ("ReverseCycle", coil.defrostStrategy());

  EXPECT_TRUE(coil.setDefrostControl("Timed"));
  EXPECT_EQ("Timed", coil.defrostControl());

  EXPECT_TRUE(coil.setDefrostTimePeriodFraction(0.12));
  EXPECT_DOUBLE_EQ(0.12, coil.defrostTimePeriodFraction());

  coil.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_TRUE(coil.setResistiveDefrostHeaterCapacity(500.0));
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(500.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());
}
