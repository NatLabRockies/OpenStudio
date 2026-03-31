/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

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

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AddToSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  auto supplyInlet = airLoop.supplyInletNode();
  EXPECT_TRUE(evaporativeCooler.addToNode(supplyInlet));
  EXPECT_TRUE(evaporativeCooler.airLoopHVAC());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AddToDemandBranchRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  EXPECT_FALSE(evaporativeCooler.addToNode(*branchNode));
  EXPECT_FALSE(evaporativeCooler.airLoopHVAC());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectResearchSpecial_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  EvaporativeCoolerDirectResearchSpecial evaporativeCooler(model);
  EXPECT_TRUE(evaporativeCooler.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
