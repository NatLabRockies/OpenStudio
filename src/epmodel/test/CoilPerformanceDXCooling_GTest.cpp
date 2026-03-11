/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/CoilPerformanceDXCooling.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilPerformanceDXCooling_DefaultConstructor) {
  Model model;
  CoilPerformanceDXCooling coilPerformance(model);
  EXPECT_EQ(CoilPerformanceDXCooling::iddObjectType(), coilPerformance.iddObject().type());
  EXPECT_FALSE(coilPerformance.nameString().empty());
}

TEST_F(EPModelFixture, CoilPerformanceDXCooling_ScalarAccessors_RoundTrip) {
  Model model;
  CoilPerformanceDXCooling coilPerformance(model);

  EXPECT_TRUE(coilPerformance.setGrossRatedTotalCoolingCapacity(45000.0));
  ASSERT_TRUE(coilPerformance.grossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(45000.0, *coilPerformance.grossRatedTotalCoolingCapacity());
  EXPECT_FALSE(coilPerformance.isGrossRatedTotalCoolingCapacityAutosized());
  coilPerformance.autosizeGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(coilPerformance.isGrossRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coilPerformance.setGrossRatedSensibleHeatRatio(0.74));
  ASSERT_TRUE(coilPerformance.grossRatedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.74, *coilPerformance.grossRatedSensibleHeatRatio());
  EXPECT_FALSE(coilPerformance.isGrossRatedSensibleHeatRatioAutosized());
  coilPerformance.autosizeGrossRatedSensibleHeatRatio();
  EXPECT_TRUE(coilPerformance.isGrossRatedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coilPerformance.setGrossRatedCoolingCOP(3.35));
  EXPECT_DOUBLE_EQ(3.35, coilPerformance.grossRatedCoolingCOP());

  EXPECT_TRUE(coilPerformance.setRatedAirFlowRate(1.6));
  ASSERT_TRUE(coilPerformance.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.6, *coilPerformance.ratedAirFlowRate());
  EXPECT_FALSE(coilPerformance.isRatedAirFlowRateAutosized());
  coilPerformance.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coilPerformance.isRatedAirFlowRateAutosized());

  EXPECT_TRUE(coilPerformance.setFractionofAirFlowBypassedAroundCoil(0.08));
  EXPECT_DOUBLE_EQ(0.08, coilPerformance.fractionofAirFlowBypassedAroundCoil());

  EXPECT_TRUE(coilPerformance.setNominalTimeforCondensateRemovaltoBegin(90.0));
  EXPECT_DOUBLE_EQ(90.0, coilPerformance.nominalTimeforCondensateRemovaltoBegin());

  EXPECT_TRUE(coilPerformance.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(1.5));
  EXPECT_DOUBLE_EQ(1.5, coilPerformance.ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity());

  EXPECT_TRUE(coilPerformance.setMaximumCyclingRate(2.8));
  EXPECT_DOUBLE_EQ(2.8, coilPerformance.maximumCyclingRate());

  EXPECT_TRUE(coilPerformance.setLatentCapacityTimeConstant(45.0));
  EXPECT_DOUBLE_EQ(45.0, coilPerformance.latentCapacityTimeConstant());

  const auto condenserTypeValues = CoilPerformanceDXCooling::condenserTypeValues();
  ASSERT_FALSE(condenserTypeValues.empty());
  EXPECT_TRUE(coilPerformance.setCondenserType(condenserTypeValues.front()));
  EXPECT_EQ(condenserTypeValues.front(), coilPerformance.condenserType());

  EXPECT_TRUE(coilPerformance.setEvaporativeCondenserEffectiveness(0.9));
  EXPECT_DOUBLE_EQ(0.9, coilPerformance.evaporativeCondenserEffectiveness());

  EXPECT_TRUE(coilPerformance.setEvaporativeCondenserAirFlowRate(0.5));
  ASSERT_TRUE(coilPerformance.evaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, *coilPerformance.evaporativeCondenserAirFlowRate());
  EXPECT_FALSE(coilPerformance.isEvaporativeCondenserAirFlowRateAutosized());
  coilPerformance.autosizeEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coilPerformance.isEvaporativeCondenserAirFlowRateAutosized());

  EXPECT_TRUE(coilPerformance.setEvaporativeCondenserPumpRatedPowerConsumption(120.0));
  ASSERT_TRUE(coilPerformance.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(120.0, *coilPerformance.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_FALSE(coilPerformance.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coilPerformance.autosizeEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coilPerformance.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
}
