/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/SwimmingPoolIndoor.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SwimmingPoolIndoor_DefaultConstructor) {
  Model model;
  SwimmingPoolIndoor pool(model);
  EXPECT_EQ(SwimmingPoolIndoor::iddObjectType(), pool.iddObject().type());
  EXPECT_FALSE(pool.nameString().empty());
  EXPECT_DOUBLE_EQ(2.0, pool.averageDepth());
  EXPECT_DOUBLE_EQ(0.1, pool.poolHeatingSystemMaximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0, pool.poolMiscellaneousEquipmentPower());
  EXPECT_DOUBLE_EQ(15.0, pool.maximumNumberofPeople());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_ScalarAccessors_RoundTrip) {
  Model model;
  SwimmingPoolIndoor pool(model);

  EXPECT_TRUE(pool.setAverageDepth(1.75));
  EXPECT_DOUBLE_EQ(1.75, pool.averageDepth());

  EXPECT_TRUE(pool.setCoverEvaporationFactor(0.3));
  EXPECT_DOUBLE_EQ(0.3, pool.coverEvaporationFactor());
  EXPECT_FALSE(pool.isCoverEvaporationFactorDefaulted());
  pool.resetCoverEvaporationFactor();
  EXPECT_TRUE(pool.isCoverEvaporationFactorDefaulted());

  EXPECT_TRUE(pool.setCoverConvectionFactor(0.4));
  EXPECT_DOUBLE_EQ(0.4, pool.coverConvectionFactor());
  EXPECT_FALSE(pool.isCoverConvectionFactorDefaulted());
  pool.resetCoverConvectionFactor();
  EXPECT_TRUE(pool.isCoverConvectionFactorDefaulted());

  EXPECT_TRUE(pool.setCoverShortWavelengthRadiationFactor(0.1));
  EXPECT_DOUBLE_EQ(0.1, pool.coverShortWavelengthRadiationFactor());
  EXPECT_FALSE(pool.isCoverShortWavelengthRadiationFactorDefaulted());
  pool.resetCoverShortWavelengthRadiationFactor();
  EXPECT_TRUE(pool.isCoverShortWavelengthRadiationFactorDefaulted());

  EXPECT_TRUE(pool.setCoverLongWavelengthRadiationFactor(0.2));
  EXPECT_DOUBLE_EQ(0.2, pool.coverLongWavelengthRadiationFactor());
  EXPECT_FALSE(pool.isCoverLongWavelengthRadiationFactorDefaulted());
  pool.resetCoverLongWavelengthRadiationFactor();
  EXPECT_TRUE(pool.isCoverLongWavelengthRadiationFactorDefaulted());

  EXPECT_TRUE(pool.setPoolHeatingSystemMaximumWaterFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, pool.poolHeatingSystemMaximumWaterFlowRate());
  EXPECT_FALSE(pool.setPoolHeatingSystemMaximumWaterFlowRate(-10.0));
  EXPECT_DOUBLE_EQ(0.12, pool.poolHeatingSystemMaximumWaterFlowRate());

  EXPECT_TRUE(pool.setPoolMiscellaneousEquipmentPower(123.0));
  EXPECT_DOUBLE_EQ(123.0, pool.poolMiscellaneousEquipmentPower());
  EXPECT_FALSE(pool.setPoolMiscellaneousEquipmentPower(-10.0));
  EXPECT_DOUBLE_EQ(123.0, pool.poolMiscellaneousEquipmentPower());

  EXPECT_TRUE(pool.setMaximumNumberofPeople(25.0));
  EXPECT_DOUBLE_EQ(25.0, pool.maximumNumberofPeople());
  EXPECT_FALSE(pool.setMaximumNumberofPeople(-10.0));
  EXPECT_DOUBLE_EQ(25.0, pool.maximumNumberofPeople());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_AddToNode_PlantDemandOnlyAndDisconnect) {
  Model model;
  SwimmingPoolIndoor pool(model);

  Node orphanNode(model);
  EXPECT_FALSE(pool.addToNode(orphanNode));
  EXPECT_FALSE(pool.loop());
  EXPECT_FALSE(pool.poolWaterInletNode());
  EXPECT_FALSE(pool.poolWaterOutletNode());

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pool.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pool.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(pool.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
  EXPECT_FALSE(pool.loop());
  EXPECT_FALSE(pool.poolWaterInletNode());
  EXPECT_FALSE(pool.poolWaterOutletNode());

  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pool.addToNode(plantDemandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  ASSERT_TRUE(pool.plantLoop());
  EXPECT_EQ(plantLoop.handle(), pool.plantLoop()->handle());
  ASSERT_TRUE(pool.inletModelObject());
  ASSERT_TRUE(pool.outletModelObject());
  ASSERT_TRUE(pool.poolWaterInletNode());
  ASSERT_TRUE(pool.poolWaterOutletNode());
  EXPECT_EQ(pool.inletModelObject()->handle(), pool.poolWaterInletNode()->handle());
  EXPECT_EQ(pool.outletModelObject()->handle(), pool.poolWaterOutletNode()->handle());

  SwimmingPoolIndoor secondPool(model);
  EXPECT_FALSE(secondPool.poolWaterInletNode());
  EXPECT_FALSE(secondPool.poolWaterOutletNode());
  EXPECT_TRUE(secondPool.addToNode(plantDemandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
  ASSERT_TRUE(secondPool.plantLoop());
  EXPECT_EQ(plantLoop.handle(), secondPool.plantLoop()->handle());

  PlantLoop secondPlantLoop(model);
  auto secondDemandInletNode = secondPlantLoop.demandInletNode();
  EXPECT_TRUE(pool.addToNode(secondDemandInletNode));
  ASSERT_TRUE(pool.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), pool.plantLoop()->handle());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(7u, secondPlantLoop.demandComponents().size());
  ASSERT_TRUE(pool.poolWaterInletNode());
  ASSERT_TRUE(pool.poolWaterOutletNode());

  pool.disconnect();
  EXPECT_FALSE(pool.loop());
  EXPECT_FALSE(pool.inletModelObject());
  EXPECT_FALSE(pool.outletModelObject());
  EXPECT_FALSE(pool.poolWaterInletNode());
  EXPECT_FALSE(pool.poolWaterOutletNode());
  EXPECT_EQ(5u, secondPlantLoop.demandComponents().size());

  secondPool.disconnect();
  EXPECT_FALSE(secondPool.loop());
  EXPECT_FALSE(secondPool.inletModelObject());
  EXPECT_FALSE(secondPool.outletModelObject());
  EXPECT_FALSE(secondPool.poolWaterInletNode());
  EXPECT_FALSE(secondPool.poolWaterOutletNode());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}
