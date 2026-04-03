/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/Curve.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanVariableVolume_DefaultConstructor) {
  Model model;
  FanVariableVolume fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_VariableVolume), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
  auto defaultSchedule = fan.availabilitySchedule();
  auto constantSchedule = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(constantSchedule);
  EXPECT_DOUBLE_EQ(1.0, constantSchedule->value());
  EXPECT_DOUBLE_EQ(0.6045, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(1017.592, fan.pressureRise());
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());
}

TEST_F(EPModelFixture, FanVariableVolume_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  FanVariableVolume fan(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(fan.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(20.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(fan.setAvailabilitySchedule(wrongSchedule));
}

TEST_F(EPModelFixture, FanVariableVolume_ScalarAccessors_RoundTrip) {
  Model model;
  FanVariableVolume fan(model);

  EXPECT_FALSE(fan.isFanTotalEfficiencyDefaulted());
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

  const auto inputMethods = FanVariableVolume::fanPowerMinimumFlowRateInputMethodValues();
  ASSERT_FALSE(inputMethods.empty());
  EXPECT_TRUE(fan.setFanPowerMinimumFlowRateInputMethod(inputMethods.front()));
  EXPECT_EQ(inputMethods.front(), fan.fanPowerMinimumFlowRateInputMethod());
  EXPECT_FALSE(fan.isFanPowerMinimumFlowRateInputMethodDefaulted());
  EXPECT_EQ(inputMethods, FanVariableVolume::validFanPowerMinimumFlowRateInputMethodValues());

  fan.resetFanPowerMinimumFlowRateInputMethod();
  EXPECT_TRUE(fan.isFanPowerMinimumFlowRateInputMethodDefaulted());

  EXPECT_TRUE(fan.setFanPowerMinimumFlowFraction(0.12));
  EXPECT_DOUBLE_EQ(0.12, fan.fanPowerMinimumFlowFraction());
  EXPECT_FALSE(fan.isFanPowerMinimumFlowFractionDefaulted());

  fan.resetFanPowerMinimumFlowFraction();
  EXPECT_TRUE(fan.isFanPowerMinimumFlowFractionDefaulted());

  ASSERT_TRUE(fan.fanPowerMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.0, fan.fanPowerMinimumAirFlowRate().get());
  EXPECT_TRUE(fan.setFanPowerMinimumAirFlowRate(0.28));
  ASSERT_TRUE(fan.fanPowerMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.28, fan.fanPowerMinimumAirFlowRate().get());

  fan.resetFanPowerMinimumAirFlowRate();
  EXPECT_FALSE(fan.fanPowerMinimumAirFlowRate());

  EXPECT_FALSE(fan.isMotorEfficiencyDefaulted());
  EXPECT_TRUE(fan.setMotorEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, fan.motorEfficiency());
  EXPECT_FALSE(fan.isMotorEfficiencyDefaulted());

  fan.resetMotorEfficiency();
  EXPECT_TRUE(fan.isMotorEfficiencyDefaulted());

  EXPECT_FALSE(fan.isMotorInAirstreamFractionDefaulted());
  EXPECT_TRUE(fan.setMotorInAirstreamFraction(1.0));
  EXPECT_DOUBLE_EQ(1.0, fan.motorInAirstreamFraction());
  EXPECT_FALSE(fan.isMotorInAirstreamFractionDefaulted());

  fan.resetMotorInAirstreamFraction();
  EXPECT_TRUE(fan.isMotorInAirstreamFractionDefaulted());

  ASSERT_TRUE(fan.fanPowerCoefficient1());
  EXPECT_DOUBLE_EQ(0.0407598940, fan.fanPowerCoefficient1().get());
  EXPECT_TRUE(fan.setFanPowerCoefficient1(0.0015302446));
  ASSERT_TRUE(fan.fanPowerCoefficient1());
  EXPECT_DOUBLE_EQ(0.0015302446, fan.fanPowerCoefficient1().get());
  fan.resetFanPowerCoefficient1();
  EXPECT_FALSE(fan.fanPowerCoefficient1());

  EXPECT_TRUE(fan.setFanPowerCoefficient2(0.0052080574));
  ASSERT_TRUE(fan.fanPowerCoefficient2());
  EXPECT_DOUBLE_EQ(0.0052080574, fan.fanPowerCoefficient2().get());
  fan.resetFanPowerCoefficient2();
  EXPECT_FALSE(fan.fanPowerCoefficient2());

  EXPECT_TRUE(fan.setFanPowerCoefficient3(1.1086242));
  ASSERT_TRUE(fan.fanPowerCoefficient3());
  EXPECT_DOUBLE_EQ(1.1086242, fan.fanPowerCoefficient3().get());
  fan.resetFanPowerCoefficient3();
  EXPECT_FALSE(fan.fanPowerCoefficient3());

  EXPECT_TRUE(fan.setFanPowerCoefficient4(-0.11635563));
  ASSERT_TRUE(fan.fanPowerCoefficient4());
  EXPECT_DOUBLE_EQ(-0.11635563, fan.fanPowerCoefficient4().get());
  fan.resetFanPowerCoefficient4();
  EXPECT_FALSE(fan.fanPowerCoefficient4());

  EXPECT_TRUE(fan.setFanPowerCoefficient5(0.0));
  ASSERT_TRUE(fan.fanPowerCoefficient5());
  EXPECT_DOUBLE_EQ(0.0, fan.fanPowerCoefficient5().get());
  fan.resetFanPowerCoefficient5();
  EXPECT_FALSE(fan.fanPowerCoefficient5());

  EXPECT_TRUE(fan.isEndUseSubcategoryDefaulted());
  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
  EXPECT_FALSE(fan.isEndUseSubcategoryDefaulted());

  fan.resetEndUseSubcategory();
  EXPECT_TRUE(fan.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, FanVariableVolume_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  FanVariableVolume fan(model);
  EXPECT_TRUE(fan.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}

TEST_F(EPModelFixture, FanVariableVolume_ConvertToFanSystemModel) {
  Model model;
  FanVariableVolume fan(model);
  ASSERT_TRUE(fan.setEndUseSubcategory("Fans"));

  FanSystemModel convertedFan = fan.convertToFanSystemModel();
  EXPECT_EQ("Fans", convertedFan.endUseSubcategory());
  EXPECT_DOUBLE_EQ(fan.fanTotalEfficiency(), convertedFan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(fan.pressureRise(), convertedFan.designPressureRise());
  EXPECT_EQ("Continuous", convertedFan.speedControlMethod());
  ASSERT_TRUE(convertedFan.electricPowerFunctionofFlowFractionCurve());
}
