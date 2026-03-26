/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/ChillerAbsorptionIndirect.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_DefaultConstructor) {
  Model model;
  ChillerAbsorptionIndirect chiller(model);
  EXPECT_EQ(ChillerAbsorptionIndirect::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());
}

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerAbsorptionIndirect chiller(model);

  EXPECT_TRUE(chiller.setNominalCapacity(210000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(210000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalPumpingPower(7300.0));
  ASSERT_TRUE(chiller.nominalPumpingPower());
  EXPECT_DOUBLE_EQ(7300.0, chiller.nominalPumpingPower().get());
  EXPECT_FALSE(chiller.isNominalPumpingPowerAutosized());
  chiller.autosizeNominalPumpingPower();
  EXPECT_TRUE(chiller.isNominalPumpingPowerAutosized());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.15));
  EXPECT_DOUBLE_EQ(0.15, chiller.minimumPartLoadRatio());
  EXPECT_TRUE(chiller.setMaximumPartLoadRatio(1.0));
  EXPECT_DOUBLE_EQ(1.0, chiller.maximumPartLoadRatio());
  EXPECT_TRUE(chiller.setOptimumPartLoadRatio(0.65));
  EXPECT_DOUBLE_EQ(0.65, chiller.optimumPartLoadRatio());

  EXPECT_TRUE(chiller.setDesignCondenserInletTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, chiller.designCondenserInletTemperature());
  EXPECT_TRUE(chiller.setCondenserInletTemperatureLowerLimit(10.0));
  EXPECT_DOUBLE_EQ(10.0, chiller.condenserInletTemperatureLowerLimit());
  EXPECT_TRUE(chiller.setChilledWaterOutletTemperatureLowerLimit(5.0));
  EXPECT_DOUBLE_EQ(5.0, chiller.chilledWaterOutletTemperatureLowerLimit());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.013));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.013, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.018));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.018, chiller.designCondenserWaterFlowRate().get());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setChillerFlowMode("NotModulated"));
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setGeneratorHeatSourceType("Steam"));
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());

  EXPECT_TRUE(chiller.setDesignGeneratorFluidFlowRate(0.01));
  ASSERT_TRUE(chiller.designGeneratorFluidFlowRate());
  EXPECT_DOUBLE_EQ(0.01, chiller.designGeneratorFluidFlowRate().get());
  chiller.autosizeDesignGeneratorFluidFlowRate();
  EXPECT_TRUE(chiller.isDesignGeneratorFluidFlowRateAutosized());

  EXPECT_TRUE(chiller.setTemperatureLowerLimitGeneratorInlet(30.0));
  EXPECT_DOUBLE_EQ(30.0, chiller.temperatureLowerLimitGeneratorInlet());
  EXPECT_TRUE(chiller.setDegreeofSubcoolinginSteamGenerator(2.0));
  EXPECT_DOUBLE_EQ(2.0, chiller.degreeofSubcoolinginSteamGenerator());
  EXPECT_TRUE(chiller.setDegreeofSubcoolinginSteamCondensateLoop(12.0));
  EXPECT_DOUBLE_EQ(12.0, chiller.degreeofSubcoolinginSteamCondensateLoop());
  EXPECT_TRUE(chiller.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, chiller.sizingFactor());
}
