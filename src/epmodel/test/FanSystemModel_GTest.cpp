/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/FanSystemModel.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanSystemModel_DefaultConstructor) {
  Model model;
  FanSystemModel fan(model);
  EXPECT_EQ(FanSystemModel::iddObjectType(), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
  auto defaultSchedule = fan.availabilitySchedule();
  auto constantSchedule = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(constantSchedule);
  EXPECT_DOUBLE_EQ(1.0, constantSchedule->value());
}

TEST_F(EPModelFixture, FanSystemModel_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  FanSystemModel fan(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.7));
  EXPECT_TRUE(fan.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(16.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(fan.setAvailabilitySchedule(wrongSchedule));
}

TEST_F(EPModelFixture, FanSystemModel_ScalarAccessors_RoundTrip) {
  Model model;
  FanSystemModel fan(model);

  EXPECT_TRUE(fan.setDesignMaximumAirFlowRate(1.33));
  ASSERT_TRUE(fan.designMaximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.33, fan.designMaximumAirFlowRate().get());
  EXPECT_FALSE(fan.isDesignMaximumAirFlowRateAutosized());

  fan.autosizeDesignMaximumAirFlowRate();
  EXPECT_TRUE(fan.isDesignMaximumAirFlowRateAutosized());

  const auto speedControlMethods = FanSystemModel::speedControlMethodValues();
  ASSERT_FALSE(speedControlMethods.empty());
  EXPECT_TRUE(fan.setSpeedControlMethod(speedControlMethods.front()));
  EXPECT_EQ(speedControlMethods.front(), fan.speedControlMethod());

  EXPECT_TRUE(fan.setElectricPowerMinimumFlowRateFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, fan.electricPowerMinimumFlowRateFraction());

  EXPECT_TRUE(fan.setDesignPressureRise(640.0));
  EXPECT_DOUBLE_EQ(640.0, fan.designPressureRise());

  EXPECT_TRUE(fan.setMotorEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, fan.motorEfficiency());

  EXPECT_TRUE(fan.setMotorInAirStreamFraction(1.0));
  EXPECT_DOUBLE_EQ(1.0, fan.motorInAirStreamFraction());

  EXPECT_TRUE(fan.setDesignElectricPowerConsumption(520.0));
  ASSERT_TRUE(fan.designElectricPowerConsumption());
  EXPECT_DOUBLE_EQ(520.0, fan.designElectricPowerConsumption().get());
  EXPECT_FALSE(fan.isDesignElectricPowerConsumptionAutosized());

  fan.autosizeDesignElectricPowerConsumption();
  EXPECT_TRUE(fan.isDesignElectricPowerConsumptionAutosized());

  const auto designPowerSizingMethods = FanSystemModel::designPowerSizingMethodValues();
  ASSERT_FALSE(designPowerSizingMethods.empty());
  EXPECT_TRUE(fan.setDesignPowerSizingMethod(designPowerSizingMethods.front()));
  EXPECT_EQ(designPowerSizingMethods.front(), fan.designPowerSizingMethod());

  EXPECT_TRUE(fan.setElectricPowerPerUnitFlowRate(840.0));
  EXPECT_DOUBLE_EQ(840.0, fan.electricPowerPerUnitFlowRate());

  EXPECT_TRUE(fan.setElectricPowerPerUnitFlowRatePerUnitPressure(1.68));
  EXPECT_DOUBLE_EQ(1.68, fan.electricPowerPerUnitFlowRatePerUnitPressure());

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.74));
  EXPECT_DOUBLE_EQ(0.74, fan.fanTotalEfficiency());

  EXPECT_FALSE(fan.nightVentilationModePressureRise());
  EXPECT_TRUE(fan.setNightVentilationModePressureRise(120.0));
  ASSERT_TRUE(fan.nightVentilationModePressureRise());
  EXPECT_DOUBLE_EQ(120.0, fan.nightVentilationModePressureRise().get());
  fan.resetNightVentilationModePressureRise();
  EXPECT_FALSE(fan.nightVentilationModePressureRise());

  EXPECT_FALSE(fan.nightVentilationModeFlowFraction());
  EXPECT_TRUE(fan.setNightVentilationModeFlowFraction(0.55));
  ASSERT_TRUE(fan.nightVentilationModeFlowFraction());
  EXPECT_DOUBLE_EQ(0.55, fan.nightVentilationModeFlowFraction().get());
  fan.resetNightVentilationModeFlowFraction();
  EXPECT_FALSE(fan.nightVentilationModeFlowFraction());

  EXPECT_TRUE(fan.setMotorLossRadiativeFraction(0.0));
  EXPECT_DOUBLE_EQ(0.0, fan.motorLossRadiativeFraction());

  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
}

TEST_F(EPModelFixture, FanSystemModel_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  FanSystemModel fan(model);
  EXPECT_TRUE(fan.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
