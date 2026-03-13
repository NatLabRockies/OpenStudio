/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_Cooling_DX_SingleSpeed), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_FALSE(coil.addToNode(*outboardOANode));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeRejectsDemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_FALSE(coil.addToNode(*branchNode));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);

  EXPECT_TRUE(coil.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", coil.condenserType());

  EXPECT_TRUE(coil.setRatedCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, coil.ratedCOP());

  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalCoolingCapacity());
  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12000.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, *coil.ratedTotalCoolingCapacity());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());

  coil.autosizeRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_FALSE(coil.ratedSensibleHeatRatio());
  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.73));
  ASSERT_TRUE(coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.73, *coil.ratedSensibleHeatRatio());

  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());
  EXPECT_TRUE(coil.setRatedAirFlowRate(1.25));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, *coil.ratedAirFlowRate());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-20.0));
  EXPECT_DOUBLE_EQ(-20.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}
