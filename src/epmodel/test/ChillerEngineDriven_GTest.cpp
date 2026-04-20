/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ChillerEngineDriven.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerEngineDriven_DefaultConstructor) {
  Model model;
  ChillerEngineDriven chiller(model);
  EXPECT_EQ(ChillerEngineDriven::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerEngineDriven_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerEngineDriven chiller(model);

  EXPECT_TRUE(chiller.setNominalCapacity(650000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(650000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalCOP(1.42));
  EXPECT_DOUBLE_EQ(1.42, chiller.nominalCOP());

  EXPECT_TRUE(chiller.setTemperatureRiseCoefficient(2.35));
  EXPECT_DOUBLE_EQ(2.35, chiller.temperatureRiseCoefficient());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.027));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.027, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.033));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.033, chiller.designCondenserWaterFlowRate().get());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.008));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.008, chiller.designHeatRecoveryWaterFlowRate().get());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());
  chiller.resetDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateDefaulted());

  EXPECT_TRUE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", chiller.fuelType());

  EXPECT_TRUE(chiller.setMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode(84.0));
  EXPECT_DOUBLE_EQ(84.0, chiller.maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode());
  chiller.resetMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode();
  EXPECT_TRUE(chiller.isMaximumTemperatureforHeatRecoveryatHeatRecoveryOutletNodeDefaulted());
  EXPECT_DOUBLE_EQ(60.0, chiller.maximumTemperatureforHeatRecoveryatHeatRecoveryOutletNode());

  EXPECT_TRUE(chiller.setSizingFactor(1.08));
  EXPECT_DOUBLE_EQ(1.08, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setBasinHeaterCapacity(20.0));
  EXPECT_DOUBLE_EQ(20.0, chiller.basinHeaterCapacity());

  EXPECT_TRUE(chiller.setBasinHeaterSetpointTemperature(4.0));
  EXPECT_DOUBLE_EQ(4.0, chiller.basinHeaterSetpointTemperature());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.35));
  ASSERT_TRUE(chiller.condenserHeatRecoveryRelativeCapacityFraction());
  EXPECT_DOUBLE_EQ(0.35, chiller.condenserHeatRecoveryRelativeCapacityFraction().get());
}
