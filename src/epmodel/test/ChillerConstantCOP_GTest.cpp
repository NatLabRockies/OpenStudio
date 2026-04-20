/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ChillerConstantCOP.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerConstantCOP_DefaultConstructor) {
  Model model;
  ChillerConstantCOP chiller(model);
  EXPECT_EQ(ChillerConstantCOP::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerConstantCOP_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerConstantCOP chiller(model);

  EXPECT_TRUE(chiller.setNominalCapacity(700000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(700000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, chiller.nominalCOP());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.024));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.024, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());
  chiller.resetDesignChilledWaterFlowRate();
  EXPECT_FALSE(chiller.designChilledWaterFlowRate());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.031));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.031, chiller.designCondenserWaterFlowRate().get());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());
  chiller.resetDesignCondenserWaterFlowRate();
  EXPECT_FALSE(chiller.designCondenserWaterFlowRate());

  EXPECT_TRUE(chiller.setCondenserType("WaterCooled"));
  EXPECT_EQ("WaterCooled", chiller.condenserType());
  chiller.resetCondenserType();
  EXPECT_TRUE(chiller.isCondenserTypeDefaulted());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());

  EXPECT_TRUE(chiller.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setBasinHeaterCapacity(22.0));
  EXPECT_DOUBLE_EQ(22.0, chiller.basinHeaterCapacity());
  chiller.resetBasinHeaterCapacity();
  EXPECT_TRUE(chiller.isBasinHeaterCapacityDefaulted());
  EXPECT_DOUBLE_EQ(0.0, chiller.basinHeaterCapacity());

  EXPECT_TRUE(chiller.setBasinHeaterSetpointTemperature(6.5));
  EXPECT_DOUBLE_EQ(6.5, chiller.basinHeaterSetpointTemperature());
  chiller.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(chiller.isBasinHeaterSetpointTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(2.0, chiller.basinHeaterSetpointTemperature());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(1.2));
  EXPECT_DOUBLE_EQ(1.2, chiller.thermosiphonMinimumTemperatureDifference());
  chiller.resetThermosiphonMinimumTemperatureDifference();
  EXPECT_TRUE(chiller.isThermosiphonMinimumTemperatureDifferenceDefaulted());
  EXPECT_DOUBLE_EQ(0.0, chiller.thermosiphonMinimumTemperatureDifference());
}
