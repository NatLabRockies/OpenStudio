/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../SetpointManager/SetpointManagerSystemNodeResetTemperature.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerSystemNodeResetTemperature spm(model);
  EXPECT_EQ(SetpointManagerSystemNodeResetTemperature::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSystemNodeResetTemperature spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(16.7, spm.setpointatLowReferenceTemperature());
  EXPECT_DOUBLE_EQ(12.8, spm.setpointatHighReferenceTemperature());
  EXPECT_DOUBLE_EQ(20.0, spm.lowReferenceTemperature());
  EXPECT_DOUBLE_EQ(23.3, spm.highReferenceTemperature());

  const auto controlVariableValues = SetpointManagerSystemNodeResetTemperature::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  std::string controlVariable = controlVariableValues.front();
  if ((controlVariable == spm.controlVariable()) && (controlVariableValues.size() > 1u)) {
    controlVariable = controlVariableValues.back();
  }
  EXPECT_TRUE(spm.setControlVariable(controlVariable));
  EXPECT_EQ(controlVariable, spm.controlVariable());

  EXPECT_TRUE(spm.setSetpointatLowReferenceTemperature(15.4));
  EXPECT_TRUE(spm.setSetpointatHighReferenceTemperature(11.9));
  EXPECT_TRUE(spm.setLowReferenceTemperature(19.6));
  EXPECT_TRUE(spm.setHighReferenceTemperature(24.2));

  EXPECT_DOUBLE_EQ(15.4, spm.setpointatLowReferenceTemperature());
  EXPECT_DOUBLE_EQ(11.9, spm.setpointatHighReferenceTemperature());
  EXPECT_DOUBLE_EQ(19.6, spm.lowReferenceTemperature());
  EXPECT_DOUBLE_EQ(24.2, spm.highReferenceTemperature());
}
