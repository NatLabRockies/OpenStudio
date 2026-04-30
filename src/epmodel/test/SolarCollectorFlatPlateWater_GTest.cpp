/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ModelObject/SolarCollectorPerformanceFlatPlate.hpp"
#include "../ModelObject/SolarCollectorPerformanceFlatPlate_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/SolarCollectorFlatPlateWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorFlatPlateWater_DefaultConstructor) {
  Model model;
  SolarCollectorFlatPlateWater object(model);
  EXPECT_EQ(SolarCollectorFlatPlateWater::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());

  auto performance = object.solarCollectorPerformance();
  EXPECT_EQ(SolarCollectorPerformanceFlatPlate::iddObjectType(), performance.iddObject().type());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlateWater_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorFlatPlateWater object(model);

  EXPECT_FALSE(object.maximumFlowRate());

  EXPECT_TRUE(object.setMaximumFlowRate(0.00123));
  ASSERT_TRUE(object.maximumFlowRate());
  EXPECT_DOUBLE_EQ(0.00123, object.maximumFlowRate().get());

  object.resetMaximumFlowRate();
  EXPECT_FALSE(object.maximumFlowRate());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlateWater_PerformanceLifecycle_RoundTrip) {
  Model model;
  SolarCollectorFlatPlateWater object(model);

  auto originalPerformance = object.solarCollectorPerformance();
  SolarCollectorPerformanceFlatPlate replacement(model);
  ASSERT_NE(originalPerformance.handle(), replacement.handle());

  EXPECT_TRUE(object.setSolarCollectorPerformance(replacement));
  auto assignedPerformance = object.solarCollectorPerformance();
  EXPECT_NE(originalPerformance.handle(), assignedPerformance.handle());
  EXPECT_NE(replacement.handle(), assignedPerformance.handle());
  EXPECT_EQ(1u, object.children().size());
  EXPECT_EQ(assignedPerformance.handle(), object.children()[0].handle());
  EXPECT_EQ(2u, model.getModelObjects<SolarCollectorPerformanceFlatPlate>().size());

  object.resetSolarCollectorPerformance();
  auto resetPerformance = object.solarCollectorPerformance();
  EXPECT_NE(assignedPerformance.handle(), resetPerformance.handle());
  EXPECT_EQ(2u, model.getModelObjects<SolarCollectorPerformanceFlatPlate>().size());

  object.remove();
  EXPECT_EQ(1u, model.getModelObjects<SolarCollectorPerformanceFlatPlate>().size());
}

TEST_F(EPModelFixture, SolarCollectorFlatPlateWater_AddToNode_PlantSupplyOnly) {
  Model model;
  SolarCollectorFlatPlateWater collector(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(collector.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(collector.loop());
  EXPECT_FALSE(collector.inletModelObject());
  EXPECT_FALSE(collector.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto airDemandNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(airDemandNode);
  EXPECT_FALSE(collector.addToNode(*airDemandNode));
  EXPECT_FALSE(collector.loop());

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(collector.addToNode(plantSupplyOutletNode));
  ASSERT_TRUE(collector.loop());
  EXPECT_EQ(plantLoop.handle(), collector.loop()->handle());
  ASSERT_TRUE(collector.inletModelObject());
  ASSERT_TRUE(collector.outletModelObject());

  SolarCollectorFlatPlateWater secondCollector(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondCollector.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(secondCollector.loop());
  EXPECT_FALSE(secondCollector.inletModelObject());
  EXPECT_FALSE(secondCollector.outletModelObject());
}
