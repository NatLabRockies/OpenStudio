/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/DehumidifierDesiccantNoFans.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DehumidifierDesiccantNoFans_DefaultConstructor) {
  Model model;
  DehumidifierDesiccantNoFans dehumidifier(model);
  EXPECT_EQ(DehumidifierDesiccantNoFans::iddObjectType(), dehumidifier.iddObject().type());
}

TEST_F(EPModelFixture, DehumidifierDesiccantNoFans_ScalarAccessors_RoundTrip) {
  Model model;
  DehumidifierDesiccantNoFans dehumidifier(model);

  EXPECT_TRUE(dehumidifier.setControlType("LeavingMaximumHumidityRatioSetpoint"));
  ASSERT_TRUE(dehumidifier.controlType());
  EXPECT_EQ("LeavingMaximumHumidityRatioSetpoint", dehumidifier.controlType().get());
  dehumidifier.resetControlType();
  EXPECT_TRUE(dehumidifier.controlType());

  EXPECT_TRUE(dehumidifier.setLeavingMaximumHumidityRatioSetpoint(0.009));
  ASSERT_TRUE(dehumidifier.leavingMaximumHumidityRatioSetpoint());
  EXPECT_DOUBLE_EQ(0.009, dehumidifier.leavingMaximumHumidityRatioSetpoint().get());
  dehumidifier.resetLeavingMaximumHumidityRatioSetpoint();
  EXPECT_FALSE(dehumidifier.leavingMaximumHumidityRatioSetpoint());

  EXPECT_TRUE(dehumidifier.setNominalProcessAirFlowRate(1.25));
  ASSERT_TRUE(dehumidifier.nominalProcessAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, dehumidifier.nominalProcessAirFlowRate().get());
  dehumidifier.resetNominalProcessAirFlowRate();
  EXPECT_FALSE(dehumidifier.nominalProcessAirFlowRate());

  EXPECT_TRUE(dehumidifier.setNominalProcessAirVelocity(3.2));
  ASSERT_TRUE(dehumidifier.nominalProcessAirVelocity());
  EXPECT_DOUBLE_EQ(3.2, dehumidifier.nominalProcessAirVelocity().get());
  dehumidifier.resetNominalProcessAirVelocity();
  EXPECT_FALSE(dehumidifier.nominalProcessAirVelocity());

  EXPECT_TRUE(dehumidifier.setRotorPower(500.0));
  ASSERT_TRUE(dehumidifier.rotorPower());
  EXPECT_DOUBLE_EQ(500.0, dehumidifier.rotorPower().get());
  dehumidifier.resetRotorPower();
  EXPECT_FALSE(dehumidifier.rotorPower());

  EXPECT_TRUE(dehumidifier.setRegenerationCoilObjectType("Coil:Heating:Electric"));
  ASSERT_TRUE(dehumidifier.regenerationCoilObjectType());
  EXPECT_EQ("Coil:Heating:Electric", dehumidifier.regenerationCoilObjectType().get());
  dehumidifier.resetRegenerationCoilObjectType();
  EXPECT_TRUE(dehumidifier.regenerationCoilObjectType());

  EXPECT_TRUE(dehumidifier.setRegenerationFanObjectType("Fan:SystemModel"));
  ASSERT_TRUE(dehumidifier.regenerationFanObjectType());
  EXPECT_EQ("Fan:SystemModel", dehumidifier.regenerationFanObjectType().get());
  dehumidifier.resetRegenerationFanObjectType();
  EXPECT_TRUE(dehumidifier.regenerationFanObjectType());

  EXPECT_TRUE(dehumidifier.setPerformanceModelType("Default"));
  ASSERT_TRUE(dehumidifier.performanceModelType());
  EXPECT_EQ("Default", dehumidifier.performanceModelType().get());
  dehumidifier.resetPerformanceModelType();
  EXPECT_TRUE(dehumidifier.performanceModelType());

  EXPECT_TRUE(dehumidifier.setNominalRegenerationTemperature(121.0));
  ASSERT_TRUE(dehumidifier.nominalRegenerationTemperature());
  EXPECT_DOUBLE_EQ(121.0, dehumidifier.nominalRegenerationTemperature().get());
  dehumidifier.resetNominalRegenerationTemperature();
  EXPECT_FALSE(dehumidifier.nominalRegenerationTemperature());
}
