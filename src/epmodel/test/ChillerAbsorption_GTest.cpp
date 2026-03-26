/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/ChillerAbsorption.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerAbsorption_DefaultConstructor) {
  Model model;
  ChillerAbsorption chiller(model);
  EXPECT_EQ(ChillerAbsorption::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());
}

TEST_F(EPModelFixture, ChillerAbsorption_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerAbsorption chiller(model);

  EXPECT_TRUE(chiller.setNominalCapacity(120000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(120000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalPumpingPower(4200.0));
  ASSERT_TRUE(chiller.nominalPumpingPower());
  EXPECT_DOUBLE_EQ(4200.0, chiller.nominalPumpingPower().get());
  EXPECT_FALSE(chiller.isNominalPumpingPowerAutosized());
  chiller.autosizeNominalPumpingPower();
  EXPECT_TRUE(chiller.isNominalPumpingPowerAutosized());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.minimumPartLoadRatio());
  EXPECT_TRUE(chiller.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, chiller.maximumPartLoadRatio());
  EXPECT_TRUE(chiller.setOptimumPartLoadRatio(0.7));
  EXPECT_DOUBLE_EQ(0.7, chiller.optimumPartLoadRatio());

  EXPECT_TRUE(chiller.setDesignCondenserInletTemperature(29.5));
  EXPECT_DOUBLE_EQ(29.5, chiller.designCondenserInletTemperature());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.011));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.011, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, chiller.designCondenserWaterFlowRate().get());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(0.03));
  EXPECT_DOUBLE_EQ(0.03, chiller.coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(0.68));
  EXPECT_DOUBLE_EQ(0.68, chiller.coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(0.29));
  EXPECT_DOUBLE_EQ(0.29, chiller.coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve());

  EXPECT_TRUE(chiller.setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(1.0));
  EXPECT_DOUBLE_EQ(1.0, chiller.coefficient1ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(0.01));
  EXPECT_DOUBLE_EQ(0.01, chiller.coefficient2ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(0.001));
  EXPECT_DOUBLE_EQ(0.001, chiller.coefficient3ofthePumpElectricUsePartLoadRatioCurve());

  EXPECT_TRUE(chiller.setChilledWaterOutletTemperatureLowerLimit(5.5));
  EXPECT_DOUBLE_EQ(5.5, chiller.chilledWaterOutletTemperatureLowerLimit());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  EXPECT_TRUE(chiller.setGeneratorHeatSourceType("HotWater"));
  EXPECT_EQ("HotWater", chiller.generatorHeatSourceType());

  EXPECT_TRUE(chiller.setDesignGeneratorFluidFlowRate(0.007));
  ASSERT_TRUE(chiller.designGeneratorFluidFlowRate());
  EXPECT_DOUBLE_EQ(0.007, chiller.designGeneratorFluidFlowRate().get());
  chiller.autosizeDesignGeneratorFluidFlowRate();
  EXPECT_TRUE(chiller.isDesignGeneratorFluidFlowRateAutosized());

  EXPECT_TRUE(chiller.setDegreeofSubcoolinginSteamGenerator(1.2));
  EXPECT_DOUBLE_EQ(1.2, chiller.degreeofSubcoolinginSteamGenerator());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
}
