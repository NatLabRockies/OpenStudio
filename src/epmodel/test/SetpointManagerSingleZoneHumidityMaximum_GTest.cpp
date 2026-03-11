/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneHumidityMaximum.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerSingleZoneHumidityMaximum_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneHumidityMaximum spm(model);
  EXPECT_EQ(SetpointManagerSingleZoneHumidityMaximum::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneHumidityMaximum_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneHumidityMaximum spm(model);

  EXPECT_EQ("MaximumHumidityRatio", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerSingleZoneHumidityMaximum::controlVariableValues();
  ASSERT_EQ(1u, controlVariableValues.size());
  EXPECT_EQ("MaximumHumidityRatio", controlVariableValues.front());

  EXPECT_TRUE(spm.setControlVariable("MaximumHumidityRatio"));
  EXPECT_TRUE(spm.setControlVariable("maximumhumidityratio"));
  EXPECT_FALSE(spm.setControlVariable("Temperature"));
  EXPECT_EQ("MaximumHumidityRatio", spm.controlVariable());
}
