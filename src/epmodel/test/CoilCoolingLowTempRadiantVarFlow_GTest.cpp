/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_VariableFlow_Design_FieldEnums.hxx>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantVarFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  auto coolingCoil = radiant.coolingCoil();
  ASSERT_TRUE(coolingCoil);
  auto typed = coolingCoil->cast<CoilCoolingLowTempRadiantVarFlow>();
  auto coolingImpl = typed.getImpl<openstudio::epmodel::detail::CoilCoolingLowTempRadiantVarFlow_Impl>();

  ASSERT_TRUE(coolingImpl);
  EXPECT_TRUE(coolingImpl->isTransient());
  ASSERT_TRUE(typed.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), typed.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantVarFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  auto coolingCoil = radiant.coolingCoil()->cast<CoilCoolingLowTempRadiantVarFlow>();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coolingCoil.plantLoop()->handle());
  EXPECT_FALSE(radiant.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == coolingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == radiant.handle(); }));

  auto inletNode = coolingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(coolingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(coolingCoil.removeFromLoop());
  EXPECT_FALSE(coolingCoil.plantLoop());
  EXPECT_FALSE(coolingCoil.inletModelObject());
  EXPECT_FALSE(coolingCoil.outletModelObject());
}

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantVarFlow_ScalarsWriteThroughParentAndDesignObject) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  auto coolingCoil = radiant.coolingCoil()->cast<CoilCoolingLowTempRadiantVarFlow>();

  ScheduleConstant controlSchedule(model);
  ASSERT_TRUE(controlSchedule.setValue(15.0));

  EXPECT_TRUE(coolingCoil.setMaximumColdWaterFlow(0.004));
  ASSERT_TRUE(coolingCoil.maximumColdWaterFlow());
  EXPECT_DOUBLE_EQ(0.004, coolingCoil.maximumColdWaterFlow().get());
  ASSERT_TRUE(radiant.maximumColdWaterFlow());
  EXPECT_DOUBLE_EQ(0.004, radiant.maximumColdWaterFlow().get());
  ASSERT_TRUE(radiant.getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, false));
  EXPECT_DOUBLE_EQ(0.004, radiant.getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, false).get());

  EXPECT_TRUE(coolingCoil.setCoolingControlTemperatureSchedule(controlSchedule));
  ASSERT_TRUE(coolingCoil.coolingControlTemperatureSchedule());
  EXPECT_EQ(controlSchedule.handle(), coolingCoil.coolingControlTemperatureSchedule()->handle());

  EXPECT_TRUE(coolingCoil.setCoolingControlThrottlingRange(0.9));
  EXPECT_FALSE(coolingCoil.isCoolingControlThrottlingRangeDefaulted());
  EXPECT_DOUBLE_EQ(0.9, coolingCoil.coolingControlThrottlingRange());

  EXPECT_TRUE(coolingCoil.setCondensationControlType("VariableOff"));
  EXPECT_TRUE(coolingCoil.setCondensationControlDewpointOffset(1.5));
  EXPECT_FALSE(coolingCoil.isCondensationControlTypeDefaulted());
  EXPECT_FALSE(coolingCoil.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_EQ("VariableOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, coolingCoil.condensationControlDewpointOffset());

  EXPECT_TRUE(coolingCoil.setCoolingDesignCapacity(1000.05));
  EXPECT_FALSE(coolingCoil.isCoolingDesignCapacityAutosized());
  ASSERT_TRUE(coolingCoil.coolingDesignCapacity());
  EXPECT_DOUBLE_EQ(1000.05, coolingCoil.coolingDesignCapacity().get());
  ASSERT_TRUE(radiant.coolingDesignCapacity());
  EXPECT_DOUBLE_EQ(1000.05, radiant.coolingDesignCapacity().get());
  ASSERT_TRUE(radiant.getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, false));
  EXPECT_DOUBLE_EQ(1000.05, radiant.getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::CoolingDesignCapacity, false).get());

  EXPECT_EQ("CoolingDesignCapacity", coolingCoil.coolingDesignCapacityMethod());
  EXPECT_TRUE(coolingCoil.setCoolingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", coolingCoil.coolingDesignCapacityMethod());
  EXPECT_TRUE(coolingCoil.setCoolingDesignCapacityPerFloorArea(11.05));
  EXPECT_DOUBLE_EQ(11.05, coolingCoil.coolingDesignCapacityPerFloorArea());
  EXPECT_TRUE(coolingCoil.setFractionofAutosizedCoolingDesignCapacity(0.8));
  EXPECT_DOUBLE_EQ(0.8, coolingCoil.fractionofAutosizedCoolingDesignCapacity());

  auto design = radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::DesignObject);
  ASSERT_TRUE(design);
  ASSERT_TRUE(design->getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName));
  EXPECT_EQ(
    controlSchedule.handle(),
    design->getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName)->handle());
  ASSERT_TRUE(design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange, true));
  EXPECT_DOUBLE_EQ(
    0.9, design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlThrottlingRange, true).get());
  ASSERT_TRUE(design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, true));
  EXPECT_EQ("VariableOff",
            design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlType, true).get());
  ASSERT_TRUE(design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, true));
  EXPECT_DOUBLE_EQ(
    1.5, design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CondensationControlDewpointOffset, true).get());
  ASSERT_TRUE(design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod, true));
  EXPECT_EQ("CapacityPerFloorArea",
            design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityMethod, true).get());
  ASSERT_TRUE(design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityPerFloorArea, true));
  EXPECT_DOUBLE_EQ(
    11.05, design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingDesignCapacityPerFloorArea, true).get());
  ASSERT_TRUE(
    design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedCoolingDesignCapacity, true));
  EXPECT_DOUBLE_EQ(
    0.8,
    design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::FractionofAutosizedCoolingDesignCapacity, true)
      .get());

  coolingCoil.resetMaximumColdWaterFlow();
  EXPECT_TRUE(coolingCoil.isMaximumColdWaterFlowDefaulted());
  EXPECT_FALSE(coolingCoil.maximumColdWaterFlow());
  EXPECT_FALSE(radiant.maximumColdWaterFlow());
  EXPECT_FALSE(radiant.getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlowFields::MaximumColdWaterFlow, false));

  coolingCoil.autosizeMaximumColdWaterFlow();
  EXPECT_TRUE(coolingCoil.isMaximumColdWaterFlowAutosized());
  EXPECT_FALSE(coolingCoil.maximumColdWaterFlow());
  EXPECT_FALSE(coolingCoil.autosizedMaximumColdWaterFlow());

  coolingCoil.resetCoolingControlTemperatureSchedule();
  EXPECT_FALSE(coolingCoil.coolingControlTemperatureSchedule());
  EXPECT_FALSE(
    design->getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_VariableFlow_DesignFields::CoolingControlTemperatureScheduleName));
  coolingCoil.resetCoolingControlThrottlingRange();
  EXPECT_TRUE(coolingCoil.isCoolingControlThrottlingRangeDefaulted());
  EXPECT_DOUBLE_EQ(0.5, coolingCoil.coolingControlThrottlingRange());

  coolingCoil.resetCondensationControlType();
  coolingCoil.resetCondensationControlDewpointOffset();
  EXPECT_TRUE(coolingCoil.isCondensationControlTypeDefaulted());
  EXPECT_TRUE(coolingCoil.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_EQ("SimpleOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.0, coolingCoil.condensationControlDewpointOffset());

  coolingCoil.autosizeCoolingDesignCapacity();
  EXPECT_TRUE(coolingCoil.isCoolingDesignCapacityAutosized());
  EXPECT_FALSE(coolingCoil.coolingDesignCapacity());
  EXPECT_FALSE(coolingCoil.autosizedCoolingDesignCapacity());
}
