/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerOutdoorAirPretreat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerOutdoorAirPretreat_DefaultConstructor) {
  Model model;
  SetpointManagerOutdoorAirPretreat spm(model);
  EXPECT_EQ(SetpointManagerOutdoorAirPretreat::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirPretreat_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerOutdoorAirPretreat spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerOutdoorAirPretreat::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.00001, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(1.0, spm.maximumSetpointHumidityRatio());

  EXPECT_TRUE(spm.isMinimumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointHumidityRatioDefaulted());

  EXPECT_TRUE(spm.setControlVariable("HumidityRatio"));
  EXPECT_TRUE(spm.setMinimumSetpointTemperature(-12.5));
  EXPECT_TRUE(spm.setMaximumSetpointTemperature(42.75));
  EXPECT_TRUE(spm.setMinimumSetpointHumidityRatio(0.0015));
  EXPECT_TRUE(spm.setMaximumSetpointHumidityRatio(0.45));

  EXPECT_EQ("HumidityRatio", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-12.5, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(42.75, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.0015, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.45, spm.maximumSetpointHumidityRatio());

  EXPECT_FALSE(spm.isMinimumSetpointTemperatureDefaulted());
  EXPECT_FALSE(spm.isMaximumSetpointTemperatureDefaulted());
  EXPECT_FALSE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_FALSE(spm.isMaximumSetpointHumidityRatioDefaulted());

  spm.resetControlVariable();
  spm.resetMinimumSetpointTemperature();
  spm.resetMaximumSetpointTemperature();
  spm.resetMinimumSetpointHumidityRatio();
  spm.resetMaximumSetpointHumidityRatio();

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(-99.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(99.0, spm.maximumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.00001, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(1.0, spm.maximumSetpointHumidityRatio());

  EXPECT_TRUE(spm.isMinimumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointTemperatureDefaulted());
  EXPECT_TRUE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointHumidityRatioDefaulted());
}
