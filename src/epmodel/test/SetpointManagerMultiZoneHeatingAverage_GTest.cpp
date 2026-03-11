/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerMultiZoneHeatingAverage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerMultiZoneHeatingAverage_DefaultConstructor) {
  Model model;
  SetpointManagerMultiZoneHeatingAverage spm(model);
  EXPECT_EQ(SetpointManagerMultiZoneHeatingAverage::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerMultiZoneHeatingAverage_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerMultiZoneHeatingAverage spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerMultiZoneHeatingAverage::controlVariableValues();
  ASSERT_EQ(1u, controlVariableValues.size());
  EXPECT_EQ("Temperature", controlVariableValues.front());
  EXPECT_FALSE(spm.setControlVariable("HumidityRatio"));
  EXPECT_TRUE(spm.setControlVariable("Temperature"));

  EXPECT_DOUBLE_EQ(20.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(50.0, spm.maximumSetpointTemperature());

  EXPECT_TRUE(spm.setMinimumSetpointTemperature(21.5));
  EXPECT_TRUE(spm.setMaximumSetpointTemperature(47.25));

  EXPECT_DOUBLE_EQ(21.5, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(47.25, spm.maximumSetpointTemperature());
}
