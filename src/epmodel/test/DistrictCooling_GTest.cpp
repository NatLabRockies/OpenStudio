/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/DistrictCooling_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/DistrictCooling.hpp"
#include "../StraightComponent/DistrictCooling_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DistrictCooling_DefaultConstructor) {
  Model model;
  DistrictCooling districtCooling(model);
  EXPECT_EQ(DistrictCooling::iddObjectType(), districtCooling.iddObject().type());
  EXPECT_FALSE(districtCooling.nameString().empty());
  EXPECT_TRUE(districtCooling.isNominalCapacityAutosized());
  EXPECT_FALSE(districtCooling.nominalCapacity());
  EXPECT_EQ(model.alwaysOnContinuousSchedule().handle(), districtCooling.capacityFractionSchedule().handle());

  auto capacityFractionSchedule =
    districtCooling.getModelObjectTarget<Schedule>(openstudio::DistrictCoolingFields::CapacityFractionScheduleName);
  ASSERT_TRUE(capacityFractionSchedule);
  EXPECT_EQ(districtCooling.capacityFractionSchedule().handle(), capacityFractionSchedule->handle());
}

TEST_F(EPModelFixture, DistrictCooling_ScheduleAndScalarAccessors_RoundTrip) {
  Model model;
  DistrictCooling districtCooling(model);

  ScheduleConstant capacityFractionSchedule(model);
  ASSERT_TRUE(capacityFractionSchedule.setValue(0.5));
  ScheduleTypeLimits dimensionlessLimits(model);
  ASSERT_TRUE(dimensionlessLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(dimensionlessLimits.setNumericType("Continuous"));
  ASSERT_TRUE(dimensionlessLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(dimensionlessLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(capacityFractionSchedule.setScheduleTypeLimits(dimensionlessLimits));
  EXPECT_TRUE(districtCooling.setCapacityFractionSchedule(capacityFractionSchedule));
  EXPECT_EQ(capacityFractionSchedule.handle(), districtCooling.capacityFractionSchedule().handle());

  auto storedSchedule = districtCooling.getModelObjectTarget<Schedule>(openstudio::DistrictCoolingFields::CapacityFractionScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(capacityFractionSchedule.handle(), storedSchedule->handle());
  ASSERT_TRUE(capacityFractionSchedule.scheduleTypeLimits());
  auto numericType = capacityFractionSchedule.scheduleTypeLimits()->numericType();
  ASSERT_TRUE(numericType);
  EXPECT_EQ("Continuous", *numericType);

  EXPECT_TRUE(districtCooling.setNominalCapacity(12345.0));
  ASSERT_TRUE(districtCooling.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtCooling.nominalCapacity().get());
  EXPECT_FALSE(districtCooling.isNominalCapacityAutosized());

  auto districtCoolingCloneObject = model.addObject(districtCooling.idfObject());
  ASSERT_TRUE(districtCoolingCloneObject);
  auto districtCoolingClone = districtCoolingCloneObject->cast<DistrictCooling>();
  EXPECT_EQ(capacityFractionSchedule.handle(), districtCoolingClone.capacityFractionSchedule().handle());
  ASSERT_TRUE(districtCoolingClone.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtCoolingClone.nominalCapacity().get());
  EXPECT_FALSE(districtCoolingClone.isNominalCapacityAutosized());

  districtCooling.autosizeNominalCapacity();
  EXPECT_TRUE(districtCooling.isNominalCapacityAutosized());
  EXPECT_FALSE(districtCooling.nominalCapacity());

  EXPECT_FALSE(districtCooling.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, DistrictCooling_ScheduleRelationship_RejectsIncompatibleScheduleTypeLimits) {
  Model model;
  DistrictCooling districtCooling(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(22.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));

  const auto originalSchedule = districtCooling.capacityFractionSchedule();
  EXPECT_FALSE(districtCooling.setCapacityFractionSchedule(wrongSchedule));
  EXPECT_EQ(originalSchedule.cast<ModelObject>(), districtCooling.capacityFractionSchedule().cast<ModelObject>());
}

TEST_F(EPModelFixture, DistrictCooling_ScheduleRelationship_RejectsDiscreteScheduleTypeLimits) {
  Model model;
  DistrictCooling districtCooling(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(discreteLimits));

  const auto originalSchedule = districtCooling.capacityFractionSchedule();
  EXPECT_FALSE(districtCooling.setCapacityFractionSchedule(wrongSchedule));
  EXPECT_EQ(originalSchedule.cast<ModelObject>(), districtCooling.capacityFractionSchedule().cast<ModelObject>());
}

TEST_F(EPModelFixture, DistrictCooling_AddToNode_PlantSupplyOnly) {
  Model model;
  DistrictCooling districtCooling(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(districtCooling.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(districtCooling.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(districtCooling.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(districtCooling.loop());
  ASSERT_TRUE(districtCooling.inletModelObject());
  ASSERT_TRUE(districtCooling.outletModelObject());
  EXPECT_TRUE(districtCooling.isRemovable());

  auto inletNode = districtCooling.getModelObjectTarget<Node>(openstudio::DistrictCoolingFields::ChilledWaterInletNodeName);
  auto outletNode = districtCooling.getModelObjectTarget<Node>(openstudio::DistrictCoolingFields::ChilledWaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(districtCooling.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(districtCooling.outletModelObject()->handle(), outletNode->handle());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(districtCooling.addToNode(demandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());

  auto districtCoolingCloneObject = model.addObject(districtCooling.idfObject());
  ASSERT_TRUE(districtCoolingCloneObject);
  auto districtCoolingClone = districtCoolingCloneObject->cast<DistrictCooling>();
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(districtCoolingClone.addToNode(supplyOutletNode));
  EXPECT_EQ(9u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(districtCoolingClone.inletModelObject());
  ASSERT_TRUE(districtCoolingClone.outletModelObject());

  districtCooling.disconnect();
  EXPECT_FALSE(districtCooling.loop());
  EXPECT_FALSE(districtCooling.inletModelObject());
  EXPECT_FALSE(districtCooling.outletModelObject());
  ASSERT_TRUE(districtCoolingClone.loop());
  ASSERT_TRUE(districtCoolingClone.inletModelObject());
  ASSERT_TRUE(districtCoolingClone.outletModelObject());
}
