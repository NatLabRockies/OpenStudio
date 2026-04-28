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
#include "../StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"

#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design_FieldEnums.hxx>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantConstFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto coolingCoil = radiant.coolingCoil();
  auto coolingImpl = coolingCoil.getImpl<openstudio::epmodel::detail::CoilCoolingLowTempRadiantConstFlow_Impl>();

  ASSERT_TRUE(coolingImpl);
  EXPECT_TRUE(coolingImpl->isTransient());
  ASSERT_TRUE(coolingCoil.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), coolingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantConstFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto coolingCoil = radiant.coolingCoil();

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

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantConstFlow_ScheduleRelationshipsWriteThroughParent) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto coolingCoil = radiant.coolingCoil();

  ScheduleConstant highWater(model);
  ScheduleConstant lowWater(model);
  ScheduleConstant highControl(model);
  ScheduleConstant lowControl(model);
  ASSERT_TRUE(highWater.setValue(18.0));
  ASSERT_TRUE(lowWater.setValue(12.0));
  ASSERT_TRUE(highControl.setValue(26.0));
  ASSERT_TRUE(lowControl.setValue(22.0));

  EXPECT_TRUE(coolingCoil.setCoolingHighWaterTemperatureSchedule(highWater));
  EXPECT_TRUE(coolingCoil.setCoolingLowWaterTemperatureSchedule(lowWater));
  EXPECT_TRUE(coolingCoil.setCoolingHighControlTemperatureSchedule(highControl));
  EXPECT_TRUE(coolingCoil.setCoolingLowControlTemperatureSchedule(lowControl));

  ASSERT_TRUE(coolingCoil.coolingHighWaterTemperatureSchedule());
  ASSERT_TRUE(coolingCoil.coolingLowWaterTemperatureSchedule());
  ASSERT_TRUE(coolingCoil.coolingHighControlTemperatureSchedule());
  ASSERT_TRUE(coolingCoil.coolingLowControlTemperatureSchedule());
  EXPECT_EQ(highWater.handle(), coolingCoil.coolingHighWaterTemperatureSchedule()->handle());
  EXPECT_EQ(lowWater.handle(), coolingCoil.coolingLowWaterTemperatureSchedule()->handle());
  EXPECT_EQ(highControl.handle(), coolingCoil.coolingHighControlTemperatureSchedule()->handle());
  EXPECT_EQ(lowControl.handle(), coolingCoil.coolingLowControlTemperatureSchedule()->handle());

  ASSERT_TRUE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName));
  ASSERT_TRUE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName));
  ASSERT_TRUE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName));
  ASSERT_TRUE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName));
  EXPECT_EQ(highWater.handle(),
            radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName)->handle());
  EXPECT_EQ(lowWater.handle(),
            radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName)->handle());
  EXPECT_EQ(highControl.handle(),
            radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName)->handle());
  EXPECT_EQ(lowControl.handle(),
            radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName)->handle());

  coolingCoil.resetCoolingHighWaterTemperatureSchedule();
  coolingCoil.resetCoolingLowWaterTemperatureSchedule();
  coolingCoil.resetCoolingHighControlTemperatureSchedule();
  coolingCoil.resetCoolingLowControlTemperatureSchedule();

  EXPECT_FALSE(coolingCoil.coolingHighWaterTemperatureSchedule());
  EXPECT_FALSE(coolingCoil.coolingLowWaterTemperatureSchedule());
  EXPECT_FALSE(coolingCoil.coolingHighControlTemperatureSchedule());
  EXPECT_FALSE(coolingCoil.coolingLowControlTemperatureSchedule());
  EXPECT_FALSE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName));
  EXPECT_FALSE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName));
  EXPECT_FALSE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName));
  EXPECT_FALSE(radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName));
}

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantConstFlow_CondensationControlsWriteThroughDesignObject) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto coolingCoil = radiant.coolingCoil();

  EXPECT_TRUE(coolingCoil.isCondensationControlTypeDefaulted());
  EXPECT_TRUE(coolingCoil.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_EQ("SimpleOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.0, coolingCoil.condensationControlDewpointOffset());

  EXPECT_TRUE(coolingCoil.setCondensationControlType("VariableOff"));
  EXPECT_TRUE(coolingCoil.setCondensationControlDewpointOffset(1.5));
  EXPECT_FALSE(coolingCoil.isCondensationControlTypeDefaulted());
  EXPECT_FALSE(coolingCoil.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_EQ("VariableOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, coolingCoil.condensationControlDewpointOffset());

  auto design = radiant.getTarget(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::DesignObject);
  ASSERT_TRUE(design);
  ASSERT_TRUE(design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, true));
  ASSERT_TRUE(design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, true));
  EXPECT_EQ("VariableOff",
            design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, true).get());
  EXPECT_DOUBLE_EQ(
    1.5, design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, true).get());

  coolingCoil.resetCondensationControlType();
  coolingCoil.resetCondensationControlDewpointOffset();
  EXPECT_TRUE(coolingCoil.isCondensationControlTypeDefaulted());
  EXPECT_TRUE(coolingCoil.isCondensationControlDewpointOffsetDefaulted());
  EXPECT_EQ("SimpleOff", coolingCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.0, coolingCoil.condensationControlDewpointOffset());
  ASSERT_TRUE(design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, false));
  EXPECT_TRUE(
    design->getString(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlType, false)->empty());
  EXPECT_FALSE(design->getDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::CondensationControlDewpointOffset, false));
}
