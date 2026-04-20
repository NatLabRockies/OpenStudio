/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ChillerCombustionTurbine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerCombustionTurbine_DefaultConstructor) {
  Model model;
  ChillerCombustionTurbine chiller(model);
  EXPECT_EQ(ChillerCombustionTurbine::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerCombustionTurbine_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerCombustionTurbine chiller(model);

  EXPECT_TRUE(chiller.setNominalCapacity(550000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(550000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalCOP(1.35));
  EXPECT_DOUBLE_EQ(1.35, chiller.nominalCOP());

  EXPECT_TRUE(chiller.setTemperatureRiseCoefficient(2.25));
  EXPECT_DOUBLE_EQ(2.25, chiller.temperatureRiseCoefficient());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.032));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.032, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.011));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.011, chiller.designHeatRecoveryWaterFlowRate().get());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());
  chiller.resetDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateDefaulted());

  EXPECT_TRUE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  EXPECT_TRUE(chiller.setFuelType("Diesel"));
  EXPECT_EQ("Diesel", chiller.fuelType());

  EXPECT_TRUE(chiller.setHeatRecoveryMaximumTemperature(85.0));
  EXPECT_DOUBLE_EQ(85.0, chiller.heatRecoveryMaximumTemperature());
  chiller.resetHeatRecoveryMaximumTemperature();
  EXPECT_TRUE(chiller.isHeatRecoveryMaximumTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(80.0, chiller.heatRecoveryMaximumTemperature());

  EXPECT_TRUE(chiller.setSizingFactor(1.12));
  EXPECT_DOUBLE_EQ(1.12, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setTurbineEngineEfficiency(0.39));
  EXPECT_DOUBLE_EQ(0.39, chiller.turbineEngineEfficiency());
}
