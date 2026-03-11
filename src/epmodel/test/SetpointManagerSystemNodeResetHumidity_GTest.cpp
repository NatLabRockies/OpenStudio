/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerSystemNodeResetHumidity.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetHumidity_DefaultConstructor) {
  Model model;
  SetpointManagerSystemNodeResetHumidity spm(model);
  EXPECT_EQ(SetpointManagerSystemNodeResetHumidity::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetHumidity_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSystemNodeResetHumidity spm(model);

  EXPECT_EQ("MaximumHumidityRatio", spm.controlVariable());
  EXPECT_DOUBLE_EQ(0.00924, spm.setpointatLowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.00600, spm.setpointatHighReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.00850, spm.lowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.01000, spm.highReferenceHumidityRatio());

  const auto controlVariableValues = SetpointManagerSystemNodeResetHumidity::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  EXPECT_TRUE(spm.setControlVariable("MinimumHumidityRatio"));
  EXPECT_EQ("MinimumHumidityRatio", spm.controlVariable());

  EXPECT_TRUE(spm.setSetpointatLowReferenceHumidityRatio(0.002));
  EXPECT_TRUE(spm.setSetpointatHighReferenceHumidityRatio(0.001));
  EXPECT_TRUE(spm.setLowReferenceHumidityRatio(0.004));
  EXPECT_TRUE(spm.setHighReferenceHumidityRatio(0.003));

  EXPECT_DOUBLE_EQ(0.002, spm.setpointatLowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.001, spm.setpointatHighReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.004, spm.lowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.003, spm.highReferenceHumidityRatio());
}
