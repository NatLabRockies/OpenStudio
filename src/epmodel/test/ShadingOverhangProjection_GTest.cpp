/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ShadingOverhangProjection.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingOverhangProjection_DefaultConstructor) {
  Model model;
  ShadingOverhangProjection shadingOverhangProjection(model);
  EXPECT_EQ(ShadingOverhangProjection::iddObjectType(), shadingOverhangProjection.iddObject().type());
}

TEST_F(EPModelFixture, ShadingOverhangProjection_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingOverhangProjection shadingOverhangProjection(model);

  EXPECT_FALSE(shadingOverhangProjection.heightaboveWindoworDoor());
  EXPECT_TRUE(shadingOverhangProjection.isTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingOverhangProjection.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhangProjection.leftextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhangProjection.rightextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhangProjection.depthasFractionofWindowDoorHeight());

  EXPECT_TRUE(shadingOverhangProjection.setHeightaboveWindoworDoor(0.2));
  ASSERT_TRUE(shadingOverhangProjection.heightaboveWindoworDoor());
  EXPECT_DOUBLE_EQ(0.2, shadingOverhangProjection.heightaboveWindoworDoor().get());

  EXPECT_TRUE(shadingOverhangProjection.setTiltAnglefromWindowDoor(60.0));
  EXPECT_FALSE(shadingOverhangProjection.isTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(60.0, shadingOverhangProjection.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhangProjection.setTiltAnglefromWindowDoor(-1.0));
  EXPECT_DOUBLE_EQ(60.0, shadingOverhangProjection.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhangProjection.setTiltAnglefromWindowDoor(181.0));
  EXPECT_DOUBLE_EQ(60.0, shadingOverhangProjection.tiltAnglefromWindowDoor());

  EXPECT_TRUE(shadingOverhangProjection.setLeftextensionfromWindowDoorWidth(0.3));
  ASSERT_TRUE(shadingOverhangProjection.leftextensionfromWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.3, shadingOverhangProjection.leftextensionfromWindowDoorWidth().get());

  EXPECT_TRUE(shadingOverhangProjection.setRightextensionfromWindowDoorWidth(0.4));
  ASSERT_TRUE(shadingOverhangProjection.rightextensionfromWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.4, shadingOverhangProjection.rightextensionfromWindowDoorWidth().get());

  EXPECT_TRUE(shadingOverhangProjection.setDepthasFractionofWindowDoorHeight(0.5));
  ASSERT_TRUE(shadingOverhangProjection.depthasFractionofWindowDoorHeight());
  EXPECT_DOUBLE_EQ(0.5, shadingOverhangProjection.depthasFractionofWindowDoorHeight().get());
  EXPECT_FALSE(shadingOverhangProjection.setDepthasFractionofWindowDoorHeight(-0.1));
  ASSERT_TRUE(shadingOverhangProjection.depthasFractionofWindowDoorHeight());
  EXPECT_DOUBLE_EQ(0.5, shadingOverhangProjection.depthasFractionofWindowDoorHeight().get());

  shadingOverhangProjection.resetHeightaboveWindoworDoor();
  shadingOverhangProjection.resetTiltAnglefromWindowDoor();
  shadingOverhangProjection.resetLeftextensionfromWindowDoorWidth();
  shadingOverhangProjection.resetRightextensionfromWindowDoorWidth();
  shadingOverhangProjection.resetDepthasFractionofWindowDoorHeight();

  EXPECT_FALSE(shadingOverhangProjection.heightaboveWindoworDoor());
  EXPECT_TRUE(shadingOverhangProjection.isTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingOverhangProjection.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhangProjection.leftextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhangProjection.rightextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhangProjection.depthasFractionofWindowDoorHeight());
}
