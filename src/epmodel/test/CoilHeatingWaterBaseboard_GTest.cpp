/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboard_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterBaseboard_IsTransientCompanionView) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingWaterBaseboard_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(baseboard.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingWaterBaseboard_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_FALSE(baseboard.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(
    std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(
    std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == baseboard.handle(); }));

  auto inletNode = heatingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(heatingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.plantLoop());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
}

TEST_F(EPModelFixture, CoilHeatingWaterBaseboard_WriteThroughParentHeatingState) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil().cast<CoilHeatingWaterBaseboard>();

  EXPECT_EQ("HeatingDesignCapacity", heatingCoil.heatingDesignCapacityMethod());
  EXPECT_TRUE(heatingCoil.isHeatingDesignCapacityAutosized());
  EXPECT_FALSE(heatingCoil.autosizedHeatingDesignCapacity());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", heatingCoil.heatingDesignCapacityMethod());
  EXPECT_EQ("CapacityPerFloorArea", baseboard.heatingDesignCapacityMethod());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityPerFloorArea(0.6));
  EXPECT_DOUBLE_EQ(0.6, heatingCoil.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(0.6, baseboard.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(heatingCoil.setFractionofAutosizedHeatingDesignCapacity(0.75));
  EXPECT_DOUBLE_EQ(0.75, heatingCoil.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.75, baseboard.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(heatingCoil.isUFactorTimesAreaValueDefaulted());
  EXPECT_FALSE(heatingCoil.isUFactorTimesAreaValueAutosized());
  EXPECT_TRUE(heatingCoil.setUFactorTimesAreaValue(2.1));
  ASSERT_TRUE(heatingCoil.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2.1, *heatingCoil.uFactorTimesAreaValue());
  ASSERT_TRUE(baseboard.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2.1, *baseboard.uFactorTimesAreaValue());
  heatingCoil.resetUFactorTimesAreaValue();
  EXPECT_TRUE(heatingCoil.isUFactorTimesAreaValueDefaulted());
  EXPECT_FALSE(heatingCoil.uFactorTimesAreaValue());
  EXPECT_FALSE(baseboard.uFactorTimesAreaValue());
  heatingCoil.autosizeUFactorTimesAreaValue();
  EXPECT_TRUE(heatingCoil.isUFactorTimesAreaValueAutosized());
  EXPECT_TRUE(baseboard.isUFactorTimesAreaValueAutosized());
  EXPECT_FALSE(heatingCoil.autosizedUFactorTimesAreaValue());

  EXPECT_TRUE(heatingCoil.isMaximumWaterFlowRateDefaulted());
  EXPECT_FALSE(heatingCoil.isMaximumWaterFlowRateAutosized());
  EXPECT_TRUE(heatingCoil.setMaximumWaterFlowRate(0.012));
  ASSERT_TRUE(heatingCoil.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, *heatingCoil.maximumWaterFlowRate());
  ASSERT_TRUE(baseboard.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, *baseboard.maximumWaterFlowRate());
  heatingCoil.resetMaximumWaterFlowRate();
  EXPECT_TRUE(heatingCoil.isMaximumWaterFlowRateDefaulted());
  EXPECT_FALSE(heatingCoil.maximumWaterFlowRate());
  EXPECT_FALSE(baseboard.maximumWaterFlowRate());
  heatingCoil.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(heatingCoil.isMaximumWaterFlowRateAutosized());
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateAutosized());
  EXPECT_FALSE(heatingCoil.autosizedMaximumWaterFlowRate());

  EXPECT_TRUE(heatingCoil.isConvergenceToleranceDefaulted());
  EXPECT_DOUBLE_EQ(0.001, heatingCoil.convergenceTolerance());
  EXPECT_TRUE(heatingCoil.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, heatingCoil.convergenceTolerance());
  EXPECT_DOUBLE_EQ(0.002, baseboard.convergenceTolerance());
  heatingCoil.resetConvergenceTolerance();
  EXPECT_TRUE(heatingCoil.isConvergenceToleranceDefaulted());
  EXPECT_DOUBLE_EQ(0.001, heatingCoil.convergenceTolerance());
  EXPECT_DOUBLE_EQ(0.001, baseboard.convergenceTolerance());
}
