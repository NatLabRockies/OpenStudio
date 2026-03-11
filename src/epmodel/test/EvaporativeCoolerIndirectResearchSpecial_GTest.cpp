/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_DefaultConstructor) {
  Model model;
  EvaporativeCoolerIndirectResearchSpecial evaporativeCooler(model);

  EXPECT_EQ(EvaporativeCoolerIndirectResearchSpecial::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_FALSE(evaporativeCooler.nameString().empty());

  EXPECT_DOUBLE_EQ(0.75, evaporativeCooler.coolerMaximumEffectiveness());
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(30.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());

  ASSERT_TRUE(evaporativeCooler.driftLossFraction());
  EXPECT_DOUBLE_EQ(0.0, evaporativeCooler.driftLossFraction().get());
  EXPECT_FALSE(evaporativeCooler.blowdownConcentrationRatio());

  EXPECT_DOUBLE_EQ(0.1, evaporativeCooler.waterPumpPowerSizingFactor());
  EXPECT_DOUBLE_EQ(1.0, evaporativeCooler.secondaryAirFlowScalingFactor());
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectResearchSpecial_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerIndirectResearchSpecial evaporativeCooler(model);

  EXPECT_TRUE(evaporativeCooler.setCoolerMaximumEffectiveness(0.81));
  EXPECT_DOUBLE_EQ(0.81, evaporativeCooler.coolerMaximumEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(225.0));
  ASSERT_TRUE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());
  EXPECT_DOUBLE_EQ(225.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption().get());
  EXPECT_FALSE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());

  evaporativeCooler.autosizeRecirculatingWaterPumpPowerConsumption();
  EXPECT_TRUE(evaporativeCooler.isRecirculatingWaterPumpPowerConsumptionAutosized());
  EXPECT_FALSE(evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setSecondaryFanFlowRate(1.9));
  ASSERT_TRUE(evaporativeCooler.secondaryFanFlowRate());
  EXPECT_DOUBLE_EQ(1.9, evaporativeCooler.secondaryFanFlowRate().get());
  EXPECT_FALSE(evaporativeCooler.isSecondaryFanFlowRateAutosized());

  evaporativeCooler.resetSecondaryFanFlowRate();
  EXPECT_FALSE(evaporativeCooler.secondaryFanFlowRate());

  evaporativeCooler.autosizeSecondaryFanFlowRate();
  EXPECT_TRUE(evaporativeCooler.isSecondaryFanFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.secondaryFanFlowRate());

  EXPECT_TRUE(evaporativeCooler.setSecondaryFanTotalEfficiency(0.64));
  EXPECT_DOUBLE_EQ(0.64, evaporativeCooler.secondaryFanTotalEfficiency());

  EXPECT_TRUE(evaporativeCooler.setSecondaryFanDeltaPressure(140.0));
  EXPECT_DOUBLE_EQ(140.0, evaporativeCooler.secondaryFanDeltaPressure());

  EXPECT_TRUE(evaporativeCooler.setDewpointEffectivenessFactor(0.87));
  EXPECT_DOUBLE_EQ(0.87, evaporativeCooler.dewpointEffectivenessFactor());

  EXPECT_TRUE(evaporativeCooler.setDriftLossFraction(0.003));
  ASSERT_TRUE(evaporativeCooler.driftLossFraction());
  EXPECT_DOUBLE_EQ(0.003, evaporativeCooler.driftLossFraction().get());
  evaporativeCooler.resetDriftLossFraction();
  ASSERT_TRUE(evaporativeCooler.driftLossFraction());
  EXPECT_DOUBLE_EQ(0.0, evaporativeCooler.driftLossFraction().get());

  EXPECT_TRUE(evaporativeCooler.setBlowdownConcentrationRatio(3.2));
  ASSERT_TRUE(evaporativeCooler.blowdownConcentrationRatio());
  EXPECT_DOUBLE_EQ(3.2, evaporativeCooler.blowdownConcentrationRatio().get());
  evaporativeCooler.resetBlowdownConcentrationRatio();
  EXPECT_FALSE(evaporativeCooler.blowdownConcentrationRatio());

  EXPECT_TRUE(evaporativeCooler.setCoolerDrybulbDesignEffectiveness(0.59));
  ASSERT_TRUE(evaporativeCooler.coolerDrybulbDesignEffectiveness());
  EXPECT_DOUBLE_EQ(0.59, evaporativeCooler.coolerDrybulbDesignEffectiveness().get());
  evaporativeCooler.resetCoolerDrybulbDesignEffectiveness();
  EXPECT_FALSE(evaporativeCooler.coolerDrybulbDesignEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setWaterPumpPowerSizingFactor(0.19));
  EXPECT_DOUBLE_EQ(0.19, evaporativeCooler.waterPumpPowerSizingFactor());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFlowScalingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, evaporativeCooler.secondaryAirFlowScalingFactor());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanDesignPower(560.0));
  ASSERT_TRUE(evaporativeCooler.secondaryAirFanDesignPower());
  EXPECT_DOUBLE_EQ(560.0, evaporativeCooler.secondaryAirFanDesignPower().get());
  EXPECT_FALSE(evaporativeCooler.isSecondaryAirFanDesignPowerAutosized());

  evaporativeCooler.autosizeSecondaryAirFanDesignPower();
  EXPECT_TRUE(evaporativeCooler.isSecondaryAirFanDesignPowerAutosized());
  EXPECT_FALSE(evaporativeCooler.secondaryAirFanDesignPower());

  EXPECT_TRUE(evaporativeCooler.setPrimaryDesignAirFlowRate(1.25));
  ASSERT_TRUE(evaporativeCooler.primaryDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, evaporativeCooler.primaryDesignAirFlowRate().get());
  EXPECT_FALSE(evaporativeCooler.isPrimaryDesignAirFlowRateAutosized());

  evaporativeCooler.resetPrimaryDesignAirFlowRate();
  EXPECT_FALSE(evaporativeCooler.primaryDesignAirFlowRate());

  evaporativeCooler.autosizePrimaryDesignAirFlowRate();
  EXPECT_TRUE(evaporativeCooler.isPrimaryDesignAirFlowRateAutosized());
  EXPECT_FALSE(evaporativeCooler.primaryDesignAirFlowRate());

  EXPECT_FALSE(evaporativeCooler.autosizedRecirculatingWaterPumpPowerConsumption());
  EXPECT_FALSE(evaporativeCooler.autosizedSecondaryFanFlowRate());
  EXPECT_FALSE(evaporativeCooler.autosizedSecondaryAirFanDesignPower());
  EXPECT_FALSE(evaporativeCooler.autosizedPrimaryDesignAirFlowRate());
}
