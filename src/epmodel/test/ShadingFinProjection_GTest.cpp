/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingFinProjection.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingFinProjection_DefaultConstructor) {
  Model model;
  ShadingFinProjection shadingFinProjection(model);
  EXPECT_EQ(ShadingFinProjection::iddObjectType(), shadingFinProjection.iddObject().type());
}

TEST_F(EPModelFixture, ShadingFinProjection_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingFinProjection shadingFinProjection(model);

  EXPECT_FALSE(shadingFinProjection.leftExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.leftDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFinProjection.leftDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFinProjection.isLeftTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFinProjection.leftTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.leftDepthasFractionofWindowDoorWidth());
  EXPECT_FALSE(shadingFinProjection.rightExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.rightDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFinProjection.rightDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFinProjection.isRightTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFinProjection.rightTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.rightDepthasFractionofWindowDoorWidth());

  EXPECT_TRUE(shadingFinProjection.setLeftExtensionfromWindowDoor(0.1));
  ASSERT_TRUE(shadingFinProjection.leftExtensionfromWindowDoor());
  EXPECT_DOUBLE_EQ(0.1, shadingFinProjection.leftExtensionfromWindowDoor().get());

  EXPECT_TRUE(shadingFinProjection.setLeftDistanceAboveTopofWindow(0.2));
  ASSERT_TRUE(shadingFinProjection.leftDistanceAboveTopofWindow());
  EXPECT_DOUBLE_EQ(0.2, shadingFinProjection.leftDistanceAboveTopofWindow().get());

  EXPECT_TRUE(shadingFinProjection.setLeftDistanceBelowBottomofWindow(0.3));
  ASSERT_TRUE(shadingFinProjection.leftDistanceBelowBottomofWindow());
  EXPECT_DOUBLE_EQ(0.3, shadingFinProjection.leftDistanceBelowBottomofWindow().get());

  EXPECT_TRUE(shadingFinProjection.setLeftTiltAnglefromWindowDoor(60.0));
  EXPECT_FALSE(shadingFinProjection.isLeftTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(60.0, shadingFinProjection.leftTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.setLeftTiltAnglefromWindowDoor(-1.0));
  EXPECT_DOUBLE_EQ(60.0, shadingFinProjection.leftTiltAnglefromWindowDoor());

  EXPECT_TRUE(shadingFinProjection.setLeftDepthasFractionofWindowDoorWidth(0.4));
  ASSERT_TRUE(shadingFinProjection.leftDepthasFractionofWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.4, shadingFinProjection.leftDepthasFractionofWindowDoorWidth().get());
  EXPECT_FALSE(shadingFinProjection.setLeftDepthasFractionofWindowDoorWidth(-0.1));
  ASSERT_TRUE(shadingFinProjection.leftDepthasFractionofWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.4, shadingFinProjection.leftDepthasFractionofWindowDoorWidth().get());

  EXPECT_TRUE(shadingFinProjection.setRightExtensionfromWindowDoor(0.5));
  ASSERT_TRUE(shadingFinProjection.rightExtensionfromWindowDoor());
  EXPECT_DOUBLE_EQ(0.5, shadingFinProjection.rightExtensionfromWindowDoor().get());

  EXPECT_TRUE(shadingFinProjection.setRightDistanceAboveTopofWindow(0.6));
  ASSERT_TRUE(shadingFinProjection.rightDistanceAboveTopofWindow());
  EXPECT_DOUBLE_EQ(0.6, shadingFinProjection.rightDistanceAboveTopofWindow().get());

  EXPECT_TRUE(shadingFinProjection.setRightDistanceBelowBottomofWindow(0.7));
  ASSERT_TRUE(shadingFinProjection.rightDistanceBelowBottomofWindow());
  EXPECT_DOUBLE_EQ(0.7, shadingFinProjection.rightDistanceBelowBottomofWindow().get());

  EXPECT_TRUE(shadingFinProjection.setRightTiltAnglefromWindowDoor(120.0));
  EXPECT_FALSE(shadingFinProjection.isRightTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(120.0, shadingFinProjection.rightTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.setRightTiltAnglefromWindowDoor(181.0));
  EXPECT_DOUBLE_EQ(120.0, shadingFinProjection.rightTiltAnglefromWindowDoor());

  EXPECT_TRUE(shadingFinProjection.setRightDepthasFractionofWindowDoorWidth(0.8));
  ASSERT_TRUE(shadingFinProjection.rightDepthasFractionofWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.8, shadingFinProjection.rightDepthasFractionofWindowDoorWidth().get());
  EXPECT_FALSE(shadingFinProjection.setRightDepthasFractionofWindowDoorWidth(-0.2));
  ASSERT_TRUE(shadingFinProjection.rightDepthasFractionofWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.8, shadingFinProjection.rightDepthasFractionofWindowDoorWidth().get());

  shadingFinProjection.resetLeftExtensionfromWindowDoor();
  shadingFinProjection.resetLeftDistanceAboveTopofWindow();
  shadingFinProjection.resetLeftDistanceBelowBottomofWindow();
  shadingFinProjection.resetLeftTiltAnglefromWindowDoor();
  shadingFinProjection.resetLeftDepthasFractionofWindowDoorWidth();
  shadingFinProjection.resetRightExtensionfromWindowDoor();
  shadingFinProjection.resetRightDistanceAboveTopofWindow();
  shadingFinProjection.resetRightDistanceBelowBottomofWindow();
  shadingFinProjection.resetRightTiltAnglefromWindowDoor();
  shadingFinProjection.resetRightDepthasFractionofWindowDoorWidth();

  EXPECT_FALSE(shadingFinProjection.leftExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.leftDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFinProjection.leftDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFinProjection.isLeftTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFinProjection.leftTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.leftDepthasFractionofWindowDoorWidth());
  EXPECT_FALSE(shadingFinProjection.rightExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.rightDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFinProjection.rightDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFinProjection.isRightTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFinProjection.rightTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFinProjection.rightDepthasFractionofWindowDoorWidth());
}
