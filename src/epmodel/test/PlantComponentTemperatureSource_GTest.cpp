/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/PlantComponent_TemperatureSource_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/PlantComponentTemperatureSource.hpp"
#include "../StraightComponent/PlantComponentTemperatureSource_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantComponentTemperatureSource_DefaultConstructor) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  EXPECT_EQ(PlantComponentTemperatureSource::iddObjectType(), plantComponentTemperatureSource.iddObject().type());
  EXPECT_FALSE(plantComponentTemperatureSource.nameString().empty());
  EXPECT_TRUE(plantComponentTemperatureSource.isDesignVolumeFlowRateAutosized());
  EXPECT_FALSE(plantComponentTemperatureSource.designVolumeFlowRate());
  EXPECT_EQ("Constant", plantComponentTemperatureSource.temperatureSpecificationType());
  ASSERT_TRUE(plantComponentTemperatureSource.sourceTemperature());
  EXPECT_DOUBLE_EQ(8.0, plantComponentTemperatureSource.sourceTemperature().get());
  EXPECT_FALSE(plantComponentTemperatureSource.sourceTemperatureSchedule());
}

TEST_F(EPModelFixture, PlantComponentTemperatureSource_ScheduleAndScalarAccessors_RoundTrip) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  EXPECT_TRUE(plantComponentTemperatureSource.setDesignVolumeFlowRate(0.25));
  ASSERT_TRUE(plantComponentTemperatureSource.designVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.25, plantComponentTemperatureSource.designVolumeFlowRate().get());
  EXPECT_FALSE(plantComponentTemperatureSource.isDesignVolumeFlowRateAutosized());

  plantComponentTemperatureSource.autosizeDesignVolumeFlowRate();
  EXPECT_TRUE(plantComponentTemperatureSource.isDesignVolumeFlowRateAutosized());
  EXPECT_FALSE(plantComponentTemperatureSource.designVolumeFlowRate());

  EXPECT_TRUE(plantComponentTemperatureSource.setTemperatureSpecificationType("Scheduled"));
  EXPECT_EQ("Scheduled", plantComponentTemperatureSource.temperatureSpecificationType());

  ScheduleConstant sourceTemperatureSchedule(model);
  ASSERT_TRUE(sourceTemperatureSchedule.setValue(12.5));
  EXPECT_TRUE(plantComponentTemperatureSource.setSourceTemperatureSchedule(sourceTemperatureSchedule));
  ASSERT_TRUE(plantComponentTemperatureSource.sourceTemperatureSchedule());
  EXPECT_EQ(sourceTemperatureSchedule.handle(), plantComponentTemperatureSource.sourceTemperatureSchedule()->handle());

  auto storedSchedule =
    plantComponentTemperatureSource.getModelObjectTarget<Schedule>(openstudio::PlantComponent_TemperatureSourceFields::SourceTemperatureScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(sourceTemperatureSchedule.handle(), storedSchedule->handle());
  ASSERT_TRUE(sourceTemperatureSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", sourceTemperatureSchedule.scheduleTypeLimits()->unitType());

  EXPECT_TRUE(plantComponentTemperatureSource.setSourceTemperature(12.5));
  ASSERT_TRUE(plantComponentTemperatureSource.sourceTemperature());
  EXPECT_DOUBLE_EQ(12.5, plantComponentTemperatureSource.sourceTemperature().get());
  plantComponentTemperatureSource.resetSourceTemperature();
  EXPECT_FALSE(plantComponentTemperatureSource.sourceTemperature());

  auto cloneObject = model.addObject(plantComponentTemperatureSource.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<PlantComponentTemperatureSource>();
  ASSERT_TRUE(clone.sourceTemperatureSchedule());
  EXPECT_EQ(sourceTemperatureSchedule.handle(), clone.sourceTemperatureSchedule()->handle());

  plantComponentTemperatureSource.resetSourceTemperatureSchedule();
  EXPECT_FALSE(plantComponentTemperatureSource.sourceTemperatureSchedule());
  ASSERT_TRUE(clone.sourceTemperatureSchedule());
  EXPECT_EQ(sourceTemperatureSchedule.handle(), clone.sourceTemperatureSchedule()->handle());

  EXPECT_FALSE(plantComponentTemperatureSource.autosizedDesignVolumeFlowRate());
}

TEST_F(EPModelFixture, PlantComponentTemperatureSource_ScheduleRelationship_RejectsIncompatibleUnitType) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(availabilityLimits));

  EXPECT_FALSE(plantComponentTemperatureSource.setSourceTemperatureSchedule(wrongSchedule));
  EXPECT_FALSE(plantComponentTemperatureSource.sourceTemperatureSchedule());
}

TEST_F(EPModelFixture, PlantComponentTemperatureSource_ScheduleRelationship_AcceptsCompatibleTypedTemperatureSchedule) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  ScheduleConstant typedSchedule(model);
  ASSERT_TRUE(typedSchedule.setValue(16.0));
  ScheduleTypeLimits discreteTemperatureLimits(model);
  ASSERT_TRUE(discreteTemperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(discreteTemperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(typedSchedule.setScheduleTypeLimits(discreteTemperatureLimits));

  EXPECT_TRUE(plantComponentTemperatureSource.setSourceTemperatureSchedule(typedSchedule));
  ASSERT_TRUE(plantComponentTemperatureSource.sourceTemperatureSchedule());
  EXPECT_EQ(typedSchedule.handle(), plantComponentTemperatureSource.sourceTemperatureSchedule()->handle());
  ASSERT_TRUE(typedSchedule.scheduleTypeLimits());
  EXPECT_EQ(discreteTemperatureLimits.handle(), typedSchedule.scheduleTypeLimits()->handle());
}

TEST_F(EPModelFixture, PlantComponentTemperatureSource_AddToNode_PlantLoopTopology) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  PlantLoop plantLoop(model);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(plantComponentTemperatureSource.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantComponentTemperatureSource.loop());
  ASSERT_TRUE(plantLoop.supplyComponent(plantComponentTemperatureSource.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(plantComponentTemperatureSource.handle()));
  ASSERT_TRUE(plantComponentTemperatureSource.inletModelObject());
  ASSERT_TRUE(plantComponentTemperatureSource.outletModelObject());
  EXPECT_TRUE(plantComponentTemperatureSource.isRemovable());

  auto inletNode = plantComponentTemperatureSource.getModelObjectTarget<Node>(openstudio::PlantComponent_TemperatureSourceFields::InletNode);
  auto outletNode = plantComponentTemperatureSource.getModelObjectTarget<Node>(openstudio::PlantComponent_TemperatureSourceFields::OutletNode);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(plantComponentTemperatureSource.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(plantComponentTemperatureSource.outletModelObject()->handle(), outletNode->handle());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(plantComponentTemperatureSource.addToNode(demandOutletNode));
  ASSERT_TRUE(plantComponentTemperatureSource.loop());
  EXPECT_EQ(plantLoop.handle(), plantComponentTemperatureSource.loop()->handle());
  EXPECT_FALSE(plantLoop.supplyComponent(plantComponentTemperatureSource.handle()));
  ASSERT_TRUE(plantLoop.demandComponent(plantComponentTemperatureSource.handle()));
  ASSERT_TRUE(plantComponentTemperatureSource.inletModelObject());
  ASSERT_TRUE(plantComponentTemperatureSource.outletModelObject());

  plantComponentTemperatureSource.disconnect();
  EXPECT_FALSE(plantComponentTemperatureSource.loop());
  EXPECT_FALSE(plantComponentTemperatureSource.inletModelObject());
  EXPECT_FALSE(plantComponentTemperatureSource.outletModelObject());
  EXPECT_FALSE(plantLoop.supplyComponent(plantComponentTemperatureSource.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(plantComponentTemperatureSource.handle()));
}
