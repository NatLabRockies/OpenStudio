/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerSingleZoneHumidityMinimum.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerSingleZoneHumidityMinimum_DefaultConstructor) {
  Model model;
  SetpointManagerSingleZoneHumidityMinimum spm(model);
  EXPECT_EQ(SetpointManagerSingleZoneHumidityMinimum::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneHumidityMinimum_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSingleZoneHumidityMinimum spm(model);

  EXPECT_EQ("MinimumHumidityRatio", spm.controlVariable());
  const auto controlVariableValues = SetpointManagerSingleZoneHumidityMinimum::controlVariableValues();
  ASSERT_EQ(1u, controlVariableValues.size());
  EXPECT_EQ("MinimumHumidityRatio", controlVariableValues.front());

  EXPECT_TRUE(spm.setControlVariable("MinimumHumidityRatio"));
  EXPECT_TRUE(spm.setControlVariable("minimumhumidityratio"));
  EXPECT_FALSE(spm.setControlVariable("Temperature"));
  EXPECT_EQ("MinimumHumidityRatio", spm.controlVariable());
}
