/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWater_DefaultConstructor) {
  Model model;
  CoilHeatingWater coil(model);
  EXPECT_EQ(CoilHeatingWater::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilHeatingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingWater coil(model);

  EXPECT_TRUE(coil.setUFactorTimesAreaValue(512.0));
  ASSERT_TRUE(coil.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(512.0, coil.uFactorTimesAreaValue().get());
  EXPECT_FALSE(coil.isUFactorTimesAreaValueAutosized());
  coil.autosizeUFactorTimesAreaValue();
  EXPECT_TRUE(coil.isUFactorTimesAreaValueAutosized());

  EXPECT_TRUE(coil.setMaximumWaterFlowRate(0.0014));
  ASSERT_TRUE(coil.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0014, coil.maximumWaterFlowRate().get());
  EXPECT_FALSE(coil.isMaximumWaterFlowRateAutosized());
  coil.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setPerformanceInputMethod("NominalCapacity"));
  EXPECT_EQ("NominalCapacity", coil.performanceInputMethod());

  EXPECT_TRUE(coil.setRatedCapacity(10250.0));
  ASSERT_TRUE(coil.ratedCapacity());
  EXPECT_DOUBLE_EQ(10250.0, coil.ratedCapacity().get());
  EXPECT_FALSE(coil.isRatedCapacityAutosized());
  coil.autosizeRatedCapacity();
  EXPECT_TRUE(coil.isRatedCapacityAutosized());

  EXPECT_TRUE(coil.setRatedInletWaterTemperature(60.0));
  EXPECT_DOUBLE_EQ(60.0, coil.ratedInletWaterTemperature());

  EXPECT_TRUE(coil.setRatedInletAirTemperature(16.5));
  EXPECT_DOUBLE_EQ(16.5, coil.ratedInletAirTemperature());

  EXPECT_TRUE(coil.setRatedOutletWaterTemperature(49.0));
  EXPECT_DOUBLE_EQ(49.0, coil.ratedOutletWaterTemperature());

  EXPECT_TRUE(coil.setRatedOutletAirTemperature(31.0));
  EXPECT_DOUBLE_EQ(31.0, coil.ratedOutletAirTemperature());

  EXPECT_TRUE(coil.setRatedRatioForAirAndWaterConvection(0.45));
  EXPECT_DOUBLE_EQ(0.45, coil.ratedRatioForAirAndWaterConvection());
}

TEST_F(EPModelFixture, CoilHeatingWater_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingWater coil(model);

  EXPECT_TRUE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(3u, oaComponents.size());
  EXPECT_EQ(coil.handle(), oaComponents[1].handle());
}
