/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ZoneHVACLowTempRadiantVarFlowDesign.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantVarFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  auto heatingCoil = radiant.heatingCoil();
  ASSERT_TRUE(heatingCoil);
  auto typed = heatingCoil->cast<CoilHeatingLowTempRadiantVarFlow>();
  auto heatingImpl = typed.getImpl<openstudio::epmodel::detail::CoilHeatingLowTempRadiantVarFlow_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(typed.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), typed.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantVarFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  auto heatingCoil = radiant.heatingCoil()->cast<CoilHeatingLowTempRadiantVarFlow>();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_FALSE(radiant.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == radiant.handle(); }));

  auto inletNode = heatingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(heatingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.plantLoop());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
}

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantVarFlow_WriteThroughParentHeatingState) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  auto heatingCoil = radiant.heatingCoil()->cast<CoilHeatingLowTempRadiantVarFlow>();

  ScheduleConstant heatingControl(model);
  ASSERT_TRUE(heatingControl.setValue(21.5));

  EXPECT_FALSE(heatingCoil.isMaximumHotWaterFlowDefaulted());
  EXPECT_FALSE(heatingCoil.isMaximumHotWaterFlowAutosized());
  EXPECT_TRUE(heatingCoil.setMaximumHotWaterFlow(0.005));
  ASSERT_TRUE(heatingCoil.maximumHotWaterFlow());
  EXPECT_DOUBLE_EQ(0.005, *heatingCoil.maximumHotWaterFlow());
  ASSERT_TRUE(radiant.maximumHotWaterFlow());
  EXPECT_DOUBLE_EQ(0.005, *radiant.maximumHotWaterFlow());

  EXPECT_TRUE(heatingCoil.setHeatingControlTemperatureSchedule(heatingControl));
  ASSERT_TRUE(heatingCoil.heatingControlTemperatureSchedule());
  EXPECT_EQ(heatingControl.handle(), heatingCoil.heatingControlTemperatureSchedule()->handle());
  ASSERT_TRUE(radiant.designObject());
  ASSERT_TRUE(radiant.designObject()->heatingControlTemperatureSchedule());
  EXPECT_EQ(heatingControl.handle(), radiant.designObject()->heatingControlTemperatureSchedule()->handle());

  EXPECT_TRUE(heatingCoil.isHeatingControlThrottlingRangeDefaulted());
  EXPECT_DOUBLE_EQ(0.5, heatingCoil.heatingControlThrottlingRange());
  EXPECT_TRUE(heatingCoil.setHeatingControlThrottlingRange(0.8));
  EXPECT_DOUBLE_EQ(0.8, heatingCoil.heatingControlThrottlingRange());
  EXPECT_DOUBLE_EQ(0.8, radiant.heatingControlThrottlingRange());

  EXPECT_EQ("HeatingDesignCapacity", heatingCoil.heatingDesignCapacityMethod());
  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", heatingCoil.heatingDesignCapacityMethod());
  EXPECT_EQ("CapacityPerFloorArea", radiant.heatingDesignCapacityMethod());
  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityPerFloorArea(42.5));
  EXPECT_DOUBLE_EQ(42.5, heatingCoil.heatingDesignCapacityPerFloorArea());
  ASSERT_TRUE(radiant.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(42.5, *radiant.heatingDesignCapacityPerFloorArea());
  EXPECT_TRUE(heatingCoil.setFractionofAutosizedHeatingDesignCapacity(1.1));
  EXPECT_DOUBLE_EQ(1.1, heatingCoil.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1.1, radiant.fractionofAutosizedHeatingDesignCapacity());

  heatingCoil.resetHeatingControlTemperatureSchedule();
  EXPECT_FALSE(heatingCoil.heatingControlTemperatureSchedule());
  ASSERT_TRUE(radiant.designObject());
  EXPECT_FALSE(radiant.designObject()->heatingControlTemperatureSchedule());

  heatingCoil.resetHeatingControlThrottlingRange();
  EXPECT_TRUE(heatingCoil.isHeatingControlThrottlingRangeDefaulted());
  EXPECT_DOUBLE_EQ(0.5, heatingCoil.heatingControlThrottlingRange());
  EXPECT_DOUBLE_EQ(0.5, radiant.heatingControlThrottlingRange());

  heatingCoil.resetMaximumHotWaterFlow();
  EXPECT_TRUE(heatingCoil.isMaximumHotWaterFlowDefaulted());
  EXPECT_FALSE(heatingCoil.maximumHotWaterFlow());
  EXPECT_FALSE(radiant.maximumHotWaterFlow());
  heatingCoil.autosizeMaximumHotWaterFlow();
  EXPECT_TRUE(heatingCoil.isMaximumHotWaterFlowAutosized());
  EXPECT_TRUE(radiant.isMaximumHotWaterFlowAutosized());
}
