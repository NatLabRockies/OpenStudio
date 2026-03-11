/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_DefaultConstructor) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  EXPECT_EQ(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(7200.0));
  ASSERT_TRUE(coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(7200.0, coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(0.74));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.74, coil.ratedAirFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setRatedWaterFlowRateAtSelectedNominalSpeedLevel(0.0036));
  ASSERT_TRUE(coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.0036, coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setNominalTimeforCondensatetoBeginLeavingtheCoil(0.4));
  EXPECT_DOUBLE_EQ(0.4, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());

  EXPECT_TRUE(coil.setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(1.8));
  EXPECT_DOUBLE_EQ(1.8, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());

  EXPECT_TRUE(coil.setMaximumCyclingRate(2.7));
  EXPECT_DOUBLE_EQ(2.7, coil.maximumCyclingRate());

  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(60.0));
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());

  EXPECT_TRUE(coil.setFanDelayTime(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.fanDelayTime());

  EXPECT_TRUE(coil.setUseHotGasReheat(true));
  EXPECT_TRUE(coil.useHotGasReheat());

  EXPECT_TRUE(coil.setUseHotGasReheat(false));
  EXPECT_FALSE(coil.useHotGasReheat());
}
