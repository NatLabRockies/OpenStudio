/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerMultiZoneCoolingAverage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerMultiZoneCoolingAverage_DefaultConstructor) {
  Model model;
  SetpointManagerMultiZoneCoolingAverage spm(model);
  EXPECT_EQ(SetpointManagerMultiZoneCoolingAverage::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerMultiZoneCoolingAverage_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerMultiZoneCoolingAverage spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerMultiZoneCoolingAverage::controlVariableValues();
  ASSERT_EQ(1u, controlVariableValues.size());
  EXPECT_EQ("Temperature", controlVariableValues.front());
  EXPECT_FALSE(spm.setControlVariable("HumidityRatio"));
  EXPECT_TRUE(spm.setControlVariable("Temperature"));

  EXPECT_DOUBLE_EQ(12.0, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(18.0, spm.maximumSetpointTemperature());

  EXPECT_TRUE(spm.setMinimumSetpointTemperature(11.25));
  EXPECT_TRUE(spm.setMaximumSetpointTemperature(16.75));

  EXPECT_DOUBLE_EQ(11.25, spm.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(16.75, spm.maximumSetpointTemperature());
}
