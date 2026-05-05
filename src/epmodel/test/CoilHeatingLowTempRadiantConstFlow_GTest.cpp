/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"

#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantConstFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto heatingCoil = radiant.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingLowTempRadiantConstFlow_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantConstFlow_PlantLoopTraversalProjectsTransientChild) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto heatingCoil = radiant.heatingCoil();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_FALSE(radiant.plantLoop());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(
    std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(
    std::any_of(demandComponents.begin(), demandComponents.end(), [&](const auto& object) { return object.handle() == radiant.handle(); }));

  auto inletNode = heatingCoil.inletModelObject()->cast<Node>();
  ASSERT_TRUE(inletNode.outletModelObject());
  EXPECT_EQ(heatingCoil.handle(), inletNode.outletModelObject()->handle());

  ASSERT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.plantLoop());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
}

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantConstFlow_ScheduleRelationshipsWriteThroughParent) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto heatingCoil = radiant.heatingCoil();

  ScheduleConstant highWater(model);
  ScheduleConstant lowWater(model);
  ScheduleConstant highControl(model);
  ScheduleConstant lowControl(model);
  ASSERT_TRUE(highWater.setValue(45.0));
  ASSERT_TRUE(lowWater.setValue(35.0));
  ASSERT_TRUE(highControl.setValue(22.0));
  ASSERT_TRUE(lowControl.setValue(18.0));

  EXPECT_TRUE(heatingCoil.setHeatingHighWaterTemperatureSchedule(highWater));
  EXPECT_TRUE(heatingCoil.setHeatingLowWaterTemperatureSchedule(lowWater));
  EXPECT_TRUE(heatingCoil.setHeatingHighControlTemperatureSchedule(highControl));
  EXPECT_TRUE(heatingCoil.setHeatingLowControlTemperatureSchedule(lowControl));

  ASSERT_TRUE(heatingCoil.heatingHighWaterTemperatureSchedule());
  ASSERT_TRUE(heatingCoil.heatingLowWaterTemperatureSchedule());
  ASSERT_TRUE(heatingCoil.heatingHighControlTemperatureSchedule());
  ASSERT_TRUE(heatingCoil.heatingLowControlTemperatureSchedule());
  EXPECT_EQ(highWater.handle(), heatingCoil.heatingHighWaterTemperatureSchedule()->handle());
  EXPECT_EQ(lowWater.handle(), heatingCoil.heatingLowWaterTemperatureSchedule()->handle());
  EXPECT_EQ(highControl.handle(), heatingCoil.heatingHighControlTemperatureSchedule()->handle());
  EXPECT_EQ(lowControl.handle(), heatingCoil.heatingLowControlTemperatureSchedule()->handle());

  ASSERT_TRUE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName));
  ASSERT_TRUE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName));
  ASSERT_TRUE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName));
  ASSERT_TRUE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName));
  EXPECT_EQ(
    highWater.handle(),
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName)
      ->handle());
  EXPECT_EQ(
    lowWater.handle(),
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName)
      ->handle());
  EXPECT_EQ(
    highControl.handle(),
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName)
      ->handle());
  EXPECT_EQ(
    lowControl.handle(),
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName)
      ->handle());

  heatingCoil.resetHeatingHighWaterTemperatureSchedule();
  heatingCoil.resetHeatingLowWaterTemperatureSchedule();
  heatingCoil.resetHeatingHighControlTemperatureSchedule();
  heatingCoil.resetHeatingLowControlTemperatureSchedule();

  EXPECT_FALSE(heatingCoil.heatingHighWaterTemperatureSchedule());
  EXPECT_FALSE(heatingCoil.heatingLowWaterTemperatureSchedule());
  EXPECT_FALSE(heatingCoil.heatingHighControlTemperatureSchedule());
  EXPECT_FALSE(heatingCoil.heatingLowControlTemperatureSchedule());
  EXPECT_FALSE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName));
  EXPECT_FALSE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName));
  EXPECT_FALSE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName));
  EXPECT_FALSE(
    radiant.getModelObjectTarget<Schedule>(openstudio::ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName));
}
