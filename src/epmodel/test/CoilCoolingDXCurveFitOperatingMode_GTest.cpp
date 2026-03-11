/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXCurveFitOperatingMode_DefaultConstructor) {
  Model model;
  CoilCoolingDXCurveFitOperatingMode operatingMode(model);
  EXPECT_EQ(CoilCoolingDXCurveFitOperatingMode::iddObjectType(), operatingMode.iddObject().type());
  EXPECT_FALSE(operatingMode.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitOperatingMode_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXCurveFitOperatingMode operatingMode(model);

  EXPECT_FALSE(operatingMode.ratedGrossTotalCoolingCapacity());
  EXPECT_FALSE(operatingMode.ratedEvaporatorAirFlowRate());
  EXPECT_FALSE(operatingMode.ratedCondenserAirFlowRate());

  EXPECT_TRUE(operatingMode.setRatedGrossTotalCoolingCapacity(1000.0));
  ASSERT_TRUE(operatingMode.ratedGrossTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(1000.0, operatingMode.ratedGrossTotalCoolingCapacity().get());

  EXPECT_TRUE(operatingMode.setRatedEvaporatorAirFlowRate(0.9));
  ASSERT_TRUE(operatingMode.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.9, operatingMode.ratedEvaporatorAirFlowRate().get());

  EXPECT_TRUE(operatingMode.setRatedCondenserAirFlowRate(1.1));
  ASSERT_TRUE(operatingMode.ratedCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(1.1, operatingMode.ratedCondenserAirFlowRate().get());

  EXPECT_TRUE(operatingMode.setMaximumCyclingRate(1.7));
  EXPECT_DOUBLE_EQ(1.7, operatingMode.maximumCyclingRate());

  EXPECT_TRUE(operatingMode.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(0.3));
  EXPECT_DOUBLE_EQ(0.3, operatingMode.ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity());

  EXPECT_TRUE(operatingMode.setLatentCapacityTimeConstant(45.0));
  EXPECT_DOUBLE_EQ(45.0, operatingMode.latentCapacityTimeConstant());

  EXPECT_TRUE(operatingMode.setNominalTimeforCondensateRemovaltoBegin(1000.0));
  EXPECT_DOUBLE_EQ(1000.0, operatingMode.nominalTimeforCondensateRemovaltoBegin());

  EXPECT_TRUE(operatingMode.setApplyLatentDegradationtoSpeedsGreaterthan1(true));
  EXPECT_TRUE(operatingMode.applyLatentDegradationtoSpeedsGreaterthan1());

  EXPECT_TRUE(operatingMode.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", operatingMode.condenserType());

  EXPECT_TRUE(operatingMode.setNominalEvaporativeCondenserPumpPower(12.5));
  ASSERT_TRUE(operatingMode.nominalEvaporativeCondenserPumpPower());
  EXPECT_DOUBLE_EQ(12.5, operatingMode.nominalEvaporativeCondenserPumpPower().get());
  EXPECT_FALSE(operatingMode.isNominalEvaporativeCondenserPumpPowerAutosized());

  EXPECT_TRUE(operatingMode.setNominalSpeedNumber(2));
  EXPECT_EQ(2u, operatingMode.nominalSpeedNumber());
  EXPECT_FALSE(operatingMode.isNominalSpeedNumberDefaulted());

  operatingMode.autosizeRatedGrossTotalCoolingCapacity();
  operatingMode.autosizeRatedEvaporatorAirFlowRate();
  operatingMode.autosizeRatedCondenserAirFlowRate();
  operatingMode.autosizeNominalEvaporativeCondenserPumpPower();
  operatingMode.resetNominalSpeedNumber();

  EXPECT_TRUE(operatingMode.isRatedGrossTotalCoolingCapacityAutosized());
  EXPECT_TRUE(operatingMode.isRatedEvaporatorAirFlowRateAutosized());
  EXPECT_TRUE(operatingMode.isRatedCondenserAirFlowRateAutosized());
  EXPECT_TRUE(operatingMode.isNominalEvaporativeCondenserPumpPowerAutosized());
  EXPECT_TRUE(operatingMode.isNominalSpeedNumberDefaulted());
}
