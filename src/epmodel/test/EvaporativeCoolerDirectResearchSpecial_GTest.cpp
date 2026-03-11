/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_DefaultConstructor) {
  Model model;
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  EXPECT_EQ(EvaporativeCoolerDirectResearchSpecial::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_FALSE(evaporativeCooler.nameString().empty());

  EXPECT_TRUE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());
  EXPECT_TRUE(evaporativeCooler.isPrimaryAirDesignFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_FALSE(evaporativeCooler.primaryAirDesignFlowRate());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  EXPECT_TRUE(evaporativeCooler.setCoolerDesignEffectiveness(0.84));
  EXPECT_DOUBLE_EQ(0.84, evaporativeCooler.coolerDesignEffectiveness());
  EXPECT_DOUBLE_EQ(0.84, evaporativeCooler.coolerEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setCoolerEffectiveness(0.81));
  EXPECT_DOUBLE_EQ(0.81, evaporativeCooler.coolerDesignEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(195.0));
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(195.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());

  evaporativeCooler.autosizeRecirculatingWaterPumpPowerConsumption();
  EXPECT_TRUE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());
  EXPECT_FALSE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setPrimaryAirDesignFlowRate(1.15));
  ASSERT_TRUE(evaporativeCooler.primaryAirDesignFlowRate());
  EXPECT_DOUBLE_EQ(1.15, evaporativeCooler.primaryAirDesignFlowRate().get());
  EXPECT_FALSE(evaporativeCooler.isPrimaryAirDesignFlowRateAutosized());

  evaporativeCooler.autosizePrimaryAirDesignFlowRate();
  EXPECT_TRUE(evaporativeCooler.isPrimaryAirDesignFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.primaryAirDesignFlowRate());

  EXPECT_TRUE(evaporativeCooler.setDriftLossFraction(0.002));
  EXPECT_DOUBLE_EQ(0.002, evaporativeCooler.driftLossFraction());

  EXPECT_TRUE(evaporativeCooler.setBlowdownConcentrationRatio(3.5));
  EXPECT_DOUBLE_EQ(3.5, evaporativeCooler.blowdownConcentrationRatio());

  EXPECT_TRUE(evaporativeCooler.setWaterPumpPowerSizingFactor(85.0));
  EXPECT_DOUBLE_EQ(85.0, evaporativeCooler.waterPumpPowerSizingFactor());

  EXPECT_TRUE(evaporativeCooler.setEvaporativeOperationMinimumDrybulbTemperature(15.0));
  EXPECT_TRUE(evaporativeCooler.setEvaporativeOperationMaximumLimitWetbulbTemperature(24.0));
  EXPECT_TRUE(evaporativeCooler.setEvaporativeOperationMaximumLimitDrybulbTemperature(29.0));

  EXPECT_DOUBLE_EQ(15.0, evaporativeCooler.evaporativeOperationMinimumDrybulbTemperature());
  EXPECT_DOUBLE_EQ(24.0, evaporativeCooler.evaporativeOperationMaximumLimitWetbulbTemperature());
  EXPECT_DOUBLE_EQ(29.0, evaporativeCooler.evaporativeOperationMaximumLimitDrybulbTemperature());

  EXPECT_FALSE(evaporativeCooler.autosizedRecirculatingWaterPumpPowerConsumption());
  EXPECT_FALSE(evaporativeCooler.autosizedPrimaryAirDesignFlowRate());
}
