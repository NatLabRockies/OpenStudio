/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXVariableSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXVariableSpeed coil(model);
  EXPECT_EQ(CoilCoolingDXVariableSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_DOUBLE_EQ(0.0, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());
  EXPECT_DOUBLE_EQ(0.0, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());
  EXPECT_DOUBLE_EQ(2.5, coil.maximumCyclingRate());
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(60.0, coil.fanDelayTime());
  EXPECT_EQ("AirCooled", coil.condenserType());
  ASSERT_TRUE(coil.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(0.0, coil.evaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(0.0, coil.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, coil.basinHeaterSetpointTemperature());
  EXPECT_DOUBLE_EQ(-25.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXVariableSpeed coil(model);

  ASSERT_FALSE(CoilCoolingDXVariableSpeed::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(4200.0));
  ASSERT_TRUE(coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(4200.0, coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(1.4));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(1.4, coil.ratedAirFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setNominalTimeforCondensatetoBeginLeavingtheCoil(50.0));
  EXPECT_DOUBLE_EQ(50.0, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());
  EXPECT_TRUE(coil.setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(0.3));
  EXPECT_DOUBLE_EQ(0.3, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());
  EXPECT_TRUE(coil.setMaximumCyclingRate(3.0));
  EXPECT_DOUBLE_EQ(3.0, coil.maximumCyclingRate());
  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(70.0));
  EXPECT_DOUBLE_EQ(70.0, coil.latentCapacityTimeConstant());
  EXPECT_TRUE(coil.setFanDelayTime(45.0));
  EXPECT_DOUBLE_EQ(45.0, coil.fanDelayTime());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setEvaporativeCondenserPumpRatedPowerConsumption(120.0));
  ASSERT_TRUE(coil.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(120.0, coil.evaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(80.0));
  EXPECT_DOUBLE_EQ(80.0, coil.crankcaseHeaterCapacity());
  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(8.0));
  EXPECT_DOUBLE_EQ(8.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_TRUE(coil.setBasinHeaterCapacity(25.0));
  EXPECT_DOUBLE_EQ(25.0, coil.basinHeaterCapacity());
  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.0));
  EXPECT_DOUBLE_EQ(3.0, coil.basinHeaterSetpointTemperature());
  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}
