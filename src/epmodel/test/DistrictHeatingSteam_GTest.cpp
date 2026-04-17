/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/DistrictHeating_Steam_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/DistrictHeatingSteam.hpp"
#include "../StraightComponent/DistrictHeatingSteam_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DistrictHeatingSteam_DefaultConstructor) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);
  EXPECT_EQ(DistrictHeatingSteam::iddObjectType(), districtHeatingSteam.iddObject().type());
  EXPECT_FALSE(districtHeatingSteam.nameString().empty());
  EXPECT_TRUE(districtHeatingSteam.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingSteam.nominalCapacity());
  EXPECT_EQ(model.alwaysOnContinuousSchedule().handle(), districtHeatingSteam.capacityFractionSchedule().handle());

  auto capacityFractionSchedule =
    districtHeatingSteam.getModelObjectTarget<Schedule>(openstudio::DistrictHeating_SteamFields::CapacityFractionScheduleName);
  ASSERT_TRUE(capacityFractionSchedule);
  EXPECT_EQ(districtHeatingSteam.capacityFractionSchedule().handle(), capacityFractionSchedule->handle());
}

TEST_F(EPModelFixture, DistrictHeatingSteam_ScheduleAndScalarAccessors_RoundTrip) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);

  ScheduleConstant capacityFractionSchedule(model);
  ASSERT_TRUE(capacityFractionSchedule.setValue(0.5));
  ScheduleTypeLimits dimensionlessLimits(model);
  ASSERT_TRUE(dimensionlessLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(dimensionlessLimits.setNumericType("Continuous"));
  ASSERT_TRUE(dimensionlessLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(dimensionlessLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(capacityFractionSchedule.setScheduleTypeLimits(dimensionlessLimits));
  EXPECT_TRUE(districtHeatingSteam.setCapacityFractionSchedule(capacityFractionSchedule));
  EXPECT_EQ(capacityFractionSchedule.handle(), districtHeatingSteam.capacityFractionSchedule().handle());

  auto storedSchedule = districtHeatingSteam.getModelObjectTarget<Schedule>(openstudio::DistrictHeating_SteamFields::CapacityFractionScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(capacityFractionSchedule.handle(), storedSchedule->handle());
  ASSERT_TRUE(capacityFractionSchedule.scheduleTypeLimits());
  auto numericType = capacityFractionSchedule.scheduleTypeLimits()->numericType();
  ASSERT_TRUE(numericType);
  EXPECT_EQ("Continuous", *numericType);

  EXPECT_TRUE(districtHeatingSteam.setNominalCapacity(12345.0));
  ASSERT_TRUE(districtHeatingSteam.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtHeatingSteam.nominalCapacity().get());
  EXPECT_FALSE(districtHeatingSteam.isNominalCapacityAutosized());

  auto districtHeatingSteamCloneObject = model.addObject(districtHeatingSteam.idfObject());
  ASSERT_TRUE(districtHeatingSteamCloneObject);
  auto districtHeatingSteamClone = districtHeatingSteamCloneObject->cast<DistrictHeatingSteam>();
  EXPECT_EQ(capacityFractionSchedule.handle(), districtHeatingSteamClone.capacityFractionSchedule().handle());
  ASSERT_TRUE(districtHeatingSteamClone.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, districtHeatingSteamClone.nominalCapacity().get());
  EXPECT_FALSE(districtHeatingSteamClone.isNominalCapacityAutosized());

  districtHeatingSteam.autosizeNominalCapacity();
  EXPECT_TRUE(districtHeatingSteam.isNominalCapacityAutosized());
  EXPECT_FALSE(districtHeatingSteam.nominalCapacity());

  EXPECT_FALSE(districtHeatingSteam.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, DistrictHeatingSteam_ScheduleRelationship_RejectsIncompatibleScheduleTypeLimits) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(22.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));

  const auto originalSchedule = districtHeatingSteam.capacityFractionSchedule();
  EXPECT_FALSE(districtHeatingSteam.setCapacityFractionSchedule(wrongSchedule));
  EXPECT_EQ(originalSchedule.cast<ModelObject>(), districtHeatingSteam.capacityFractionSchedule().cast<ModelObject>());
}

TEST_F(EPModelFixture, DistrictHeatingSteam_ScheduleRelationship_RejectsDiscreteScheduleTypeLimits) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(discreteLimits));

  const auto originalSchedule = districtHeatingSteam.capacityFractionSchedule();
  EXPECT_FALSE(districtHeatingSteam.setCapacityFractionSchedule(wrongSchedule));
  EXPECT_EQ(originalSchedule.cast<ModelObject>(), districtHeatingSteam.capacityFractionSchedule().cast<ModelObject>());
}

TEST_F(EPModelFixture, DistrictHeatingSteam_AddToNode_PlantSupplyOnly) {
  Model model;
  DistrictHeatingSteam districtHeatingSteam(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(districtHeatingSteam.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(districtHeatingSteam.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(districtHeatingSteam.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(districtHeatingSteam.loop());
  ASSERT_TRUE(districtHeatingSteam.inletModelObject());
  ASSERT_TRUE(districtHeatingSteam.outletModelObject());
  EXPECT_TRUE(districtHeatingSteam.isRemovable());

  auto inletNode = districtHeatingSteam.getModelObjectTarget<Node>(openstudio::DistrictHeating_SteamFields::SteamInletNodeName);
  auto outletNode = districtHeatingSteam.getModelObjectTarget<Node>(openstudio::DistrictHeating_SteamFields::SteamOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(districtHeatingSteam.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(districtHeatingSteam.outletModelObject()->handle(), outletNode->handle());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(districtHeatingSteam.addToNode(demandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());

  auto districtHeatingSteamCloneObject = model.addObject(districtHeatingSteam.idfObject());
  ASSERT_TRUE(districtHeatingSteamCloneObject);
  auto districtHeatingSteamClone = districtHeatingSteamCloneObject->cast<DistrictHeatingSteam>();
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(districtHeatingSteamClone.addToNode(supplyOutletNode));
  EXPECT_EQ(9u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(districtHeatingSteamClone.inletModelObject());
  ASSERT_TRUE(districtHeatingSteamClone.outletModelObject());

  districtHeatingSteam.disconnect();
  EXPECT_FALSE(districtHeatingSteam.loop());
  EXPECT_FALSE(districtHeatingSteam.inletModelObject());
  EXPECT_FALSE(districtHeatingSteam.outletModelObject());
  ASSERT_TRUE(districtHeatingSteamClone.loop());
  ASSERT_TRUE(districtHeatingSteamClone.inletModelObject());
  ASSERT_TRUE(districtHeatingSteamClone.outletModelObject());
}
