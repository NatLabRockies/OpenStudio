/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingFin.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingFin_DefaultConstructor) {
  Model model;
  ShadingFin shadingFin(model);
  EXPECT_EQ(ShadingFin::iddObjectType(), shadingFin.iddObject().type());
}

TEST_F(EPModelFixture, ShadingFin_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingFin shadingFin(model);

  EXPECT_FALSE(shadingFin.leftExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFin.leftDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFin.leftDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFin.isLeftTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFin.leftTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFin.leftDepth());
  EXPECT_FALSE(shadingFin.rightExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFin.rightDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFin.rightDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFin.isRightTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFin.rightTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFin.rightDepth());

  EXPECT_TRUE(shadingFin.setLeftExtensionfromWindowDoor(0.1));
  ASSERT_TRUE(shadingFin.leftExtensionfromWindowDoor());
  EXPECT_DOUBLE_EQ(0.1, shadingFin.leftExtensionfromWindowDoor().get());

  EXPECT_TRUE(shadingFin.setLeftDistanceAboveTopofWindow(0.2));
  ASSERT_TRUE(shadingFin.leftDistanceAboveTopofWindow());
  EXPECT_DOUBLE_EQ(0.2, shadingFin.leftDistanceAboveTopofWindow().get());

  EXPECT_TRUE(shadingFin.setLeftDistanceBelowBottomofWindow(0.3));
  ASSERT_TRUE(shadingFin.leftDistanceBelowBottomofWindow());
  EXPECT_DOUBLE_EQ(0.3, shadingFin.leftDistanceBelowBottomofWindow().get());

  EXPECT_TRUE(shadingFin.setLeftTiltAnglefromWindowDoor(60.0));
  EXPECT_FALSE(shadingFin.isLeftTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(60.0, shadingFin.leftTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFin.setLeftTiltAnglefromWindowDoor(-1.0));
  EXPECT_DOUBLE_EQ(60.0, shadingFin.leftTiltAnglefromWindowDoor());

  EXPECT_TRUE(shadingFin.setLeftDepth(0.4));
  ASSERT_TRUE(shadingFin.leftDepth());
  EXPECT_DOUBLE_EQ(0.4, shadingFin.leftDepth().get());
  EXPECT_FALSE(shadingFin.setLeftDepth(-0.1));
  ASSERT_TRUE(shadingFin.leftDepth());
  EXPECT_DOUBLE_EQ(0.4, shadingFin.leftDepth().get());

  EXPECT_TRUE(shadingFin.setRightExtensionfromWindowDoor(0.5));
  ASSERT_TRUE(shadingFin.rightExtensionfromWindowDoor());
  EXPECT_DOUBLE_EQ(0.5, shadingFin.rightExtensionfromWindowDoor().get());

  EXPECT_TRUE(shadingFin.setRightDistanceAboveTopofWindow(0.6));
  ASSERT_TRUE(shadingFin.rightDistanceAboveTopofWindow());
  EXPECT_DOUBLE_EQ(0.6, shadingFin.rightDistanceAboveTopofWindow().get());

  EXPECT_TRUE(shadingFin.setRightDistanceBelowBottomofWindow(0.7));
  ASSERT_TRUE(shadingFin.rightDistanceBelowBottomofWindow());
  EXPECT_DOUBLE_EQ(0.7, shadingFin.rightDistanceBelowBottomofWindow().get());

  EXPECT_TRUE(shadingFin.setRightTiltAnglefromWindowDoor(120.0));
  EXPECT_FALSE(shadingFin.isRightTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(120.0, shadingFin.rightTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFin.setRightTiltAnglefromWindowDoor(181.0));
  EXPECT_DOUBLE_EQ(120.0, shadingFin.rightTiltAnglefromWindowDoor());

  EXPECT_TRUE(shadingFin.setRightDepth(0.8));
  ASSERT_TRUE(shadingFin.rightDepth());
  EXPECT_DOUBLE_EQ(0.8, shadingFin.rightDepth().get());
  EXPECT_FALSE(shadingFin.setRightDepth(-0.2));
  ASSERT_TRUE(shadingFin.rightDepth());
  EXPECT_DOUBLE_EQ(0.8, shadingFin.rightDepth().get());

  shadingFin.resetLeftExtensionfromWindowDoor();
  shadingFin.resetLeftDistanceAboveTopofWindow();
  shadingFin.resetLeftDistanceBelowBottomofWindow();
  shadingFin.resetLeftTiltAnglefromWindowDoor();
  shadingFin.resetLeftDepth();
  shadingFin.resetRightExtensionfromWindowDoor();
  shadingFin.resetRightDistanceAboveTopofWindow();
  shadingFin.resetRightDistanceBelowBottomofWindow();
  shadingFin.resetRightTiltAnglefromWindowDoor();
  shadingFin.resetRightDepth();

  EXPECT_FALSE(shadingFin.leftExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFin.leftDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFin.leftDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFin.isLeftTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFin.leftTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFin.leftDepth());
  EXPECT_FALSE(shadingFin.rightExtensionfromWindowDoor());
  EXPECT_FALSE(shadingFin.rightDistanceAboveTopofWindow());
  EXPECT_FALSE(shadingFin.rightDistanceBelowBottomofWindow());
  EXPECT_TRUE(shadingFin.isRightTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingFin.rightTiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingFin.rightDepth());
}
