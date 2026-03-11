/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerMultiZoneHumidityMaximum.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerMultiZoneHumidityMaximum_DefaultConstructor) {
  Model model;
  SetpointManagerMultiZoneHumidityMaximum spm(model);
  EXPECT_EQ(SetpointManagerMultiZoneHumidityMaximum::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerMultiZoneHumidityMaximum_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerMultiZoneHumidityMaximum spm(model);

  EXPECT_EQ("MaximumHumidityRatio", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerMultiZoneHumidityMaximum::controlVariableValues();
  ASSERT_EQ(1u, controlVariableValues.size());
  EXPECT_EQ("MaximumHumidityRatio", controlVariableValues.front());
  EXPECT_FALSE(spm.setControlVariable("Temperature"));
  EXPECT_TRUE(spm.setControlVariable("MaximumHumidityRatio"));

  EXPECT_DOUBLE_EQ(0.008, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.015, spm.maximumSetpointHumidityRatio());

  EXPECT_TRUE(spm.setMinimumSetpointHumidityRatio(0.0065));
  EXPECT_TRUE(spm.setMaximumSetpointHumidityRatio(0.01225));

  EXPECT_DOUBLE_EQ(0.0065, spm.minimumSetpointHumidityRatio());
  EXPECT_DOUBLE_EQ(0.01225, spm.maximumSetpointHumidityRatio());
}
