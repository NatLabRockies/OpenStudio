/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWater_DefaultConstructor) {
  Model model;
  CoilCoolingWater coil(model);
  EXPECT_EQ(CoilCoolingWater::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilCoolingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWater coil(model);

  EXPECT_TRUE(coil.setDesignWaterFlowRate(0.0011));
  ASSERT_TRUE(coil.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0011, coil.designWaterFlowRate().get());
  EXPECT_FALSE(coil.isDesignWaterFlowRateAutosized());
  coil.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(coil.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setDesignAirFlowRate(0.87));
  ASSERT_TRUE(coil.designAirFlowRate());
  EXPECT_DOUBLE_EQ(0.87, coil.designAirFlowRate().get());
  EXPECT_FALSE(coil.isDesignAirFlowRateAutosized());
  coil.autosizeDesignAirFlowRate();
  EXPECT_TRUE(coil.isDesignAirFlowRateAutosized());

  EXPECT_TRUE(coil.setDesignInletWaterTemperature(6.8));
  ASSERT_TRUE(coil.designInletWaterTemperature());
  EXPECT_DOUBLE_EQ(6.8, coil.designInletWaterTemperature().get());
  EXPECT_FALSE(coil.isDesignInletWaterTemperatureAutosized());
  coil.autosizeDesignInletWaterTemperature();
  EXPECT_TRUE(coil.isDesignInletWaterTemperatureAutosized());

  EXPECT_TRUE(coil.setDesignInletAirTemperature(26.1));
  ASSERT_TRUE(coil.designInletAirTemperature());
  EXPECT_DOUBLE_EQ(26.1, coil.designInletAirTemperature().get());
  EXPECT_FALSE(coil.isDesignInletAirTemperatureAutosized());
  coil.autosizeDesignInletAirTemperature();
  EXPECT_TRUE(coil.isDesignInletAirTemperatureAutosized());

  EXPECT_TRUE(coil.setDesignOutletAirTemperature(12.4));
  ASSERT_TRUE(coil.designOutletAirTemperature());
  EXPECT_DOUBLE_EQ(12.4, coil.designOutletAirTemperature().get());
  EXPECT_FALSE(coil.isDesignOutletAirTemperatureAutosized());
  coil.autosizeDesignOutletAirTemperature();
  EXPECT_TRUE(coil.isDesignOutletAirTemperatureAutosized());

  EXPECT_TRUE(coil.setDesignInletAirHumidityRatio(0.0105));
  ASSERT_TRUE(coil.designInletAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0105, coil.designInletAirHumidityRatio().get());
  EXPECT_FALSE(coil.isDesignInletAirHumidityRatioAutosized());
  coil.autosizeDesignInletAirHumidityRatio();
  EXPECT_TRUE(coil.isDesignInletAirHumidityRatioAutosized());

  EXPECT_TRUE(coil.setDesignOutletAirHumidityRatio(0.0084));
  ASSERT_TRUE(coil.designOutletAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0084, coil.designOutletAirHumidityRatio().get());
  EXPECT_FALSE(coil.isDesignOutletAirHumidityRatioAutosized());
  coil.autosizeDesignOutletAirHumidityRatio();
  EXPECT_TRUE(coil.isDesignOutletAirHumidityRatioAutosized());

  EXPECT_TRUE(coil.setTypeOfAnalysis("DetailedAnalysis"));
  EXPECT_EQ("DetailedAnalysis", coil.typeOfAnalysis());

  EXPECT_TRUE(coil.setHeatExchangerConfiguration("CounterFlow"));
  EXPECT_EQ("CounterFlow", coil.heatExchangerConfiguration());
}

TEST_F(EPModelFixture, CoilCoolingWater_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingWater coil(model);

  EXPECT_TRUE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(coil.handle(), oaComponents[1].handle());
}

TEST_F(EPModelFixture, CoilCoolingWater_RemoveDetachesFromOutdoorAirSystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingWater coil(model);
  ASSERT_TRUE(coil.addToNode(*outboardOANode));
  ASSERT_EQ(3u, oaSystem.oaComponents().size());
  const auto coilHandle = coil.handle();

  coil.remove();

  EXPECT_LT(oaSystem.oaComponents().size(), 3u);
  EXPECT_FALSE(oaSystem.component(coilHandle));
}
