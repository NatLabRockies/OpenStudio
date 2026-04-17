/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/DistrictHeating_Water_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/DistrictHeatingWater.hpp"
#include "../StraightComponent/DistrictHeatingWater_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DistrictHeatingWater_DefaultConstructor) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);
  EXPECT_EQ(DistrictHeatingWater::iddObjectType(), districtHeatingWater.iddObject().type());
  EXPECT_FALSE(districtHeatingWater.nameString().empty());
  EXPECT_TRUE(districtHeatingWater.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingWater.nominalCapacity());
  EXPECT_EQ(model.alwaysOnContinuousSchedule().handle(), districtHeatingWater.capacityFractionSchedule().handle());

  auto capacityFractionSchedule =
    districtHeatingWater.getModelObjectTarget<Schedule>(openstudio::DistrictHeating_WaterFields::CapacityFractionScheduleName);
  ASSERT_TRUE(capacityFractionSchedule);
  EXPECT_EQ(districtHeatingWater.capacityFractionSchedule().handle(), capacityFractionSchedule->handle());
}

TEST_F(EPModelFixture, DistrictHeatingWater_ScheduleAndScalarAccessors_RoundTrip) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);

  ScheduleConstant capacityFractionSchedule(model);
  capacityFractionSchedule.setValue(0.5);
  ScheduleTypeLimits dimensionlessLimits(model);
  ASSERT_TRUE(dimensionlessLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(dimensionlessLimits.setNumericType("Continuous"));
  ASSERT_TRUE(dimensionlessLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(dimensionlessLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(capacityFractionSchedule.setScheduleTypeLimits(dimensionlessLimits));
  EXPECT_TRUE(districtHeatingWater.setCapacityFractionSchedule(capacityFractionSchedule));
  EXPECT_EQ(capacityFractionSchedule.handle(), districtHeatingWater.capacityFractionSchedule().handle());

  auto storedSchedule = districtHeatingWater.getModelObjectTarget<Schedule>(openstudio::DistrictHeating_WaterFields::CapacityFractionScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(capacityFractionSchedule.handle(), storedSchedule->handle());
  ASSERT_TRUE(capacityFractionSchedule.scheduleTypeLimits());
  auto numericType = capacityFractionSchedule.scheduleTypeLimits()->numericType();
  ASSERT_TRUE(numericType);
  EXPECT_EQ("Continuous", *numericType);

  EXPECT_TRUE(districtHeatingWater.setNominalCapacity(12345.0));
  ASSERT_TRUE(districtHeatingWater.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtHeatingWater.nominalCapacity().get());
  EXPECT_FALSE(districtHeatingWater.isNominalCapacityAutosized());

  auto districtHeatingWaterCloneObject = model.addObject(districtHeatingWater.idfObject());
  ASSERT_TRUE(districtHeatingWaterCloneObject);
  auto districtHeatingWaterClone = districtHeatingWaterCloneObject->cast<DistrictHeatingWater>();
  EXPECT_EQ(capacityFractionSchedule.handle(), districtHeatingWaterClone.capacityFractionSchedule().handle());
  ASSERT_TRUE(districtHeatingWaterClone.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtHeatingWaterClone.nominalCapacity().get());
  EXPECT_FALSE(districtHeatingWaterClone.isNominalCapacityAutosized());

  districtHeatingWater.autosizeNominalCapacity();
  EXPECT_TRUE(districtHeatingWater.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingWater.nominalCapacity());

  EXPECT_FALSE(districtHeatingWater.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, DistrictHeatingWater_ScheduleRelationship_RejectsIncompatibleScheduleTypeLimits) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(22.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));

  const auto originalSchedule = districtHeatingWater.capacityFractionSchedule();
  EXPECT_FALSE(districtHeatingWater.setCapacityFractionSchedule(wrongSchedule));
  EXPECT_EQ(originalSchedule.cast<ModelObject>(), districtHeatingWater.capacityFractionSchedule().cast<ModelObject>());
}

TEST_F(EPModelFixture, DistrictHeatingWater_ScheduleRelationship_RejectsDiscreteScheduleTypeLimits) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(discreteLimits));

  const auto originalSchedule = districtHeatingWater.capacityFractionSchedule();
  EXPECT_FALSE(districtHeatingWater.setCapacityFractionSchedule(wrongSchedule));
  EXPECT_EQ(originalSchedule.cast<ModelObject>(), districtHeatingWater.capacityFractionSchedule().cast<ModelObject>());
}

TEST_F(EPModelFixture, DistrictHeatingWater_AddToNode_PlantSupplyOnly) {
  Model model;
  DistrictHeatingWater districtHeatingWater(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(districtHeatingWater.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(districtHeatingWater.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(districtHeatingWater.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(districtHeatingWater.loop());
  ASSERT_TRUE(districtHeatingWater.inletModelObject());
  ASSERT_TRUE(districtHeatingWater.outletModelObject());
  EXPECT_TRUE(districtHeatingWater.isRemovable());

  auto inletNode = districtHeatingWater.getModelObjectTarget<Node>(openstudio::DistrictHeating_WaterFields::HotWaterInletNodeName);
  auto outletNode = districtHeatingWater.getModelObjectTarget<Node>(openstudio::DistrictHeating_WaterFields::HotWaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(districtHeatingWater.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(districtHeatingWater.outletModelObject()->handle(), outletNode->handle());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(districtHeatingWater.addToNode(demandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());

  districtHeatingWater.disconnect();
  EXPECT_FALSE(districtHeatingWater.loop());
  EXPECT_FALSE(districtHeatingWater.inletModelObject());
  EXPECT_FALSE(districtHeatingWater.outletModelObject());

  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(districtHeatingWater.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(districtHeatingWater.inletModelObject());
  ASSERT_TRUE(districtHeatingWater.outletModelObject());
}
