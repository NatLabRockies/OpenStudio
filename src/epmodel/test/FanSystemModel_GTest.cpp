/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ThermalZone.hpp"
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
  EXPECT_TRUE(fan.isDesignMaximumAirFlowRateAutosized());
  EXPECT_EQ("Discrete", fan.speedControlMethod());
  EXPECT_EQ("PowerPerFlowPerPressure", fan.designPowerSizingMethod());
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

TEST_F(EPModelFixture, FanSystemModel_RelationshipAndSpeedAccessors_RoundTrip) {
  Model model;
  FanSystemModel fan(model);

  CurveCubic powerCurve(model);
  EXPECT_TRUE(fan.setElectricPowerFunctionofFlowFractionCurve(powerCurve));
  ASSERT_TRUE(fan.electricPowerFunctionofFlowFractionCurve());
  EXPECT_EQ(powerCurve.cast<ModelObject>(), fan.electricPowerFunctionofFlowFractionCurve()->cast<ModelObject>());

  CurveBiquadratic badCurve(model);
  EXPECT_FALSE(fan.setElectricPowerFunctionofFlowFractionCurve(badCurve));
  ASSERT_TRUE(fan.electricPowerFunctionofFlowFractionCurve());
  EXPECT_EQ(powerCurve.cast<ModelObject>(), fan.electricPowerFunctionofFlowFractionCurve()->cast<ModelObject>());

  fan.resetElectricPowerFunctionofFlowFractionCurve();
  EXPECT_FALSE(fan.electricPowerFunctionofFlowFractionCurve());

  ThermalZone zone(model);
  EXPECT_TRUE(fan.setMotorLossZone(zone));
  ASSERT_TRUE(fan.motorLossZone());
  EXPECT_EQ(zone.cast<ModelObject>(), fan.motorLossZone()->cast<ModelObject>());
  fan.resetMotorLossZone();
  EXPECT_FALSE(fan.motorLossZone());

  EXPECT_EQ(0u, fan.numberofSpeeds());
  EXPECT_TRUE(fan.addSpeed(0.4));
  EXPECT_TRUE(fan.addSpeed(0.8, 0.9));
  EXPECT_EQ(2u, fan.numberofSpeeds());
  auto speeds = fan.speeds();
  ASSERT_EQ(2u, speeds.size());
  EXPECT_DOUBLE_EQ(0.4, speeds[0].flowFraction());
  EXPECT_FALSE(speeds[0].electricPowerFraction());
  EXPECT_DOUBLE_EQ(0.8, speeds[1].flowFraction());
  ASSERT_TRUE(speeds[1].electricPowerFraction());
  EXPECT_DOUBLE_EQ(0.9, *speeds[1].electricPowerFraction());

  auto index = fan.speedIndex(FanSystemModelSpeed(0.8));
  ASSERT_TRUE(index);
  auto speed = fan.getSpeed(*index);
  ASSERT_TRUE(speed);
  EXPECT_DOUBLE_EQ(0.8, speed->flowFraction());

  EXPECT_TRUE(fan.removeSpeed(0u));
  EXPECT_EQ(1u, fan.numberofSpeeds());
  fan.removeAllSpeeds();
  EXPECT_EQ(0u, fan.numberofSpeeds());
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
