/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerOutdoorAirReset.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_DefaultConstructor) {
  Model model;
  SetpointManagerOutdoorAirReset spm(model);
  EXPECT_EQ(SetpointManagerOutdoorAirReset::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerOutdoorAirReset spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_FALSE(spm.isControlVariableDefaulted());
  EXPECT_DOUBLE_EQ(22.0, spm.setpointatOutdoorLowTemperature());
  EXPECT_DOUBLE_EQ(10.0, spm.outdoorLowTemperature());
  EXPECT_DOUBLE_EQ(10.0, spm.setpointatOutdoorHighTemperature());
  EXPECT_DOUBLE_EQ(24.0, spm.outdoorHighTemperature());
  EXPECT_FALSE(spm.setpointatOutdoorLowTemperature2());
  EXPECT_FALSE(spm.outdoorLowTemperature2());
  EXPECT_FALSE(spm.setpointatOutdoorHighTemperature2());
  EXPECT_FALSE(spm.outdoorHighTemperature2());

  const auto controlVariableValues = SetpointManagerOutdoorAirReset::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  EXPECT_TRUE(spm.setSetpointatOutdoorLowTemperature(12.5));
  EXPECT_TRUE(spm.setOutdoorLowTemperature(5.5));
  EXPECT_TRUE(spm.setSetpointatOutdoorHighTemperature(18.25));
  EXPECT_TRUE(spm.setOutdoorHighTemperature(30.75));
  EXPECT_TRUE(spm.setSetpointatOutdoorLowTemperature2(11.1));
  EXPECT_TRUE(spm.setOutdoorLowTemperature2(7.7));
  EXPECT_TRUE(spm.setSetpointatOutdoorHighTemperature2(19.9));
  EXPECT_TRUE(spm.setOutdoorHighTemperature2(27.3));

  EXPECT_DOUBLE_EQ(12.5, spm.setpointatOutdoorLowTemperature());
  EXPECT_DOUBLE_EQ(5.5, spm.outdoorLowTemperature());
  EXPECT_DOUBLE_EQ(18.25, spm.setpointatOutdoorHighTemperature());
  EXPECT_DOUBLE_EQ(30.75, spm.outdoorHighTemperature());
  ASSERT_TRUE(spm.setpointatOutdoorLowTemperature2());
  EXPECT_DOUBLE_EQ(11.1, *spm.setpointatOutdoorLowTemperature2());
  ASSERT_TRUE(spm.outdoorLowTemperature2());
  EXPECT_DOUBLE_EQ(7.7, *spm.outdoorLowTemperature2());
  ASSERT_TRUE(spm.setpointatOutdoorHighTemperature2());
  EXPECT_DOUBLE_EQ(19.9, *spm.setpointatOutdoorHighTemperature2());
  ASSERT_TRUE(spm.outdoorHighTemperature2());
  EXPECT_DOUBLE_EQ(27.3, *spm.outdoorHighTemperature2());

  spm.resetControlVariable();
  spm.resetSetpointatOutdoorLowTemperature2();
  spm.resetOutdoorLowTemperature2();
  spm.resetSetpointatOutdoorHighTemperature2();
  spm.resetOutdoorHighTemperature2();

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_TRUE(spm.isControlVariableDefaulted());
  EXPECT_FALSE(spm.setpointatOutdoorLowTemperature2());
  EXPECT_FALSE(spm.outdoorLowTemperature2());
  EXPECT_FALSE(spm.setpointatOutdoorHighTemperature2());
  EXPECT_FALSE(spm.outdoorHighTemperature2());
}
