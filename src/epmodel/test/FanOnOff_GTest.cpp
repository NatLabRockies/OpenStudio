/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanOnOff_DefaultConstructor) {
  Model model;
  FanOnOff fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_OnOff), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
  auto defaultSchedule = fan.availabilitySchedule();
  auto constantSchedule = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(constantSchedule);
  EXPECT_DOUBLE_EQ(1.0, constantSchedule->value());
}

TEST_F(EPModelFixture, FanOnOff_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  FanOnOff fan(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.6));
  EXPECT_TRUE(fan.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(18.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(fan.setAvailabilitySchedule(wrongSchedule));
}

TEST_F(EPModelFixture, FanOnOff_ScalarAccessors_RoundTrip) {
  Model model;
  FanOnOff fan(model);

  EXPECT_TRUE(fan.isFanTotalEfficiencyDefaulted());
  EXPECT_TRUE(fan.setFanTotalEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.81, fan.fanEfficiency());
  EXPECT_FALSE(fan.isFanTotalEfficiencyDefaulted());

  EXPECT_TRUE(fan.setFanEfficiency(0.79));
  EXPECT_DOUBLE_EQ(0.79, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.79, fan.fanEfficiency());

  fan.resetFanTotalEfficiency();
  EXPECT_TRUE(fan.isFanTotalEfficiencyDefaulted());
  fan.resetFanEfficiency();
  EXPECT_TRUE(fan.isFanEfficiencyDefaulted());

  EXPECT_TRUE(fan.setPressureRise(620.0));
  EXPECT_DOUBLE_EQ(620.0, fan.pressureRise());

  EXPECT_TRUE(fan.setMaximumFlowRate(1.35));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(1.35, fan.maximumFlowRate().get());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());

  fan.autosizeMaximumFlowRate();
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());

  fan.resetMaximumFlowRate();
  EXPECT_FALSE(fan.maximumFlowRate());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());

  EXPECT_TRUE(fan.isMotorEfficiencyDefaulted());
  EXPECT_TRUE(fan.setMotorEfficiency(0.88));
  EXPECT_DOUBLE_EQ(0.88, fan.motorEfficiency());
  EXPECT_FALSE(fan.isMotorEfficiencyDefaulted());

  fan.resetMotorEfficiency();
  EXPECT_TRUE(fan.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(fan.setMotorInAirstreamFraction(0.9));
  ASSERT_TRUE(fan.motorInAirstreamFraction());
  EXPECT_DOUBLE_EQ(0.9, fan.motorInAirstreamFraction().get());

  fan.resetMotorInAirstreamFraction();
  EXPECT_TRUE(fan.setMotorInAirstreamFraction(0.7));
  ASSERT_TRUE(fan.motorInAirstreamFraction());
  EXPECT_DOUBLE_EQ(0.7, fan.motorInAirstreamFraction().get());

  EXPECT_TRUE(fan.isEndUseSubcategoryDefaulted());
  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
  EXPECT_FALSE(fan.isEndUseSubcategoryDefaulted());

  fan.resetEndUseSubcategory();
  EXPECT_TRUE(fan.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, FanOnOff_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff supplyFan(model);
  FanOnOff demandFan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyFan.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyFan.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyFan.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyFan.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandFan.addToNode(demandInletNode));
  EXPECT_FALSE(demandFan.airLoopHVAC());
}
