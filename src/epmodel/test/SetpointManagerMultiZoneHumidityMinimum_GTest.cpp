/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerMultiZoneHumidityMinimum.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerMultiZoneHumidityMinimum_DefaultConstructor) {
  Model model;
  SetpointManagerMultiZoneHumidityMinimum spm(model);
  EXPECT_EQ(SetpointManagerMultiZoneHumidityMinimum::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerMultiZoneHumidityMinimum_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerMultiZoneHumidityMinimum spm(model);

  EXPECT_EQ("MinimumHumidityRatio", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerMultiZoneHumidityMinimum::controlVariableValues();
  ASSERT_EQ(1u, controlVariableValues.size());
  EXPECT_EQ("MinimumHumidityRatio", controlVariableValues.front());
  EXPECT_FALSE(spm.setControlVariable("Temperature"));
  EXPECT_TRUE(spm.setControlVariable("MinimumHumidityRatio"));

  EXPECT_TRUE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointHumidityRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.005, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.012, spm.maximumSetpointHumidityRatio());

  EXPECT_TRUE(spm.setMinimumSetpointHumidityRatio(0.007));
  EXPECT_TRUE(spm.setMaximumSetpointHumidityRatio(0.0105));
  EXPECT_FALSE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_FALSE(spm.isMaximumSetpointHumidityRatioDefaulted());

  EXPECT_DOUBLE_EQ(0.007, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0105, spm.maximumSetpointHumidityRatio());

  spm.resetMinimumSetpointHumidityRatio();
  spm.resetMaximumSetpointHumidityRatio();
  EXPECT_TRUE(spm.isMinimumSetpointHumidityRatioDefaulted());
  EXPECT_TRUE(spm.isMaximumSetpointHumidityRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.005, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.012, spm.maximumSetpointHumidityRatio());
}
