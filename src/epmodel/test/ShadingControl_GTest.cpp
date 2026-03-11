/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/ShadingControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingControl_DefaultConstructor) {
  Model model;
  ShadingControl shadingControl(model);
  EXPECT_EQ(ShadingControl::iddObjectType(), openstudio::IddObjectType::WindowShadingControl);
}

TEST_F(EPModelFixture, ShadingControl_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingControl shadingControl(model);

  EXPECT_TRUE(shadingControl.setShadingType("ExteriorBlind"));
  EXPECT_EQ("ExteriorBlind", shadingControl.shadingType());

  EXPECT_TRUE(shadingControl.setShadingControlType("AlwaysOff"));
  EXPECT_EQ("AlwaysOff", shadingControl.shadingControlType());
  EXPECT_FALSE(shadingControl.isShadingControlTypeDefaulted());
  shadingControl.resetShadingControlType();
  EXPECT_TRUE(shadingControl.isShadingControlTypeDefaulted());

  EXPECT_TRUE(shadingControl.setShadingControlSequenceNumber(3));
  EXPECT_EQ(3, shadingControl.shadingControlSequenceNumber());
  EXPECT_FALSE(shadingControl.isShadingControlSequenceNumberDefaulted());
  shadingControl.resetShadingControlSequenceNumber();
  EXPECT_TRUE(shadingControl.isShadingControlSequenceNumberDefaulted());

  EXPECT_TRUE(shadingControl.setSetpoint(1000.0));
  ASSERT_TRUE(shadingControl.setpoint());
  EXPECT_DOUBLE_EQ(1000.0, shadingControl.setpoint().get());
  shadingControl.resetSetpoint();
  EXPECT_TRUE(shadingControl.isSetpointDefaulted());
  EXPECT_FALSE(shadingControl.setpoint());

  EXPECT_TRUE(shadingControl.setGlareControlIsActive(true));
  EXPECT_TRUE(shadingControl.glareControlIsActive());
  shadingControl.resetGlareControlIsActive();

  EXPECT_TRUE(shadingControl.setTypeofSlatAngleControlforBlinds("ScheduledSlatAngle"));
  EXPECT_EQ("ScheduledSlatAngle", shadingControl.typeofSlatAngleControlforBlinds());
  EXPECT_FALSE(shadingControl.isTypeofSlatAngleControlforBlindsDefaulted());
  shadingControl.resetTypeofSlatAngleControlforBlinds();
  EXPECT_TRUE(shadingControl.isTypeofSlatAngleControlforBlindsDefaulted());

  EXPECT_TRUE(shadingControl.setSetpoint2(250.0));
  ASSERT_TRUE(shadingControl.setpoint2());
  EXPECT_DOUBLE_EQ(250.0, shadingControl.setpoint2().get());

  EXPECT_TRUE(shadingControl.setMultipleSurfaceControlType("Group"));
  EXPECT_EQ("Group", shadingControl.multipleSurfaceControlType());
}
