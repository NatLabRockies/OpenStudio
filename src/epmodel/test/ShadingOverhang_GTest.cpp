/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingOverhang.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingOverhang_DefaultConstructor) {
  Model model;
  ShadingOverhang shadingOverhang(model);
  EXPECT_EQ(ShadingOverhang::iddObjectType(), shadingOverhang.iddObject().type());
}

TEST_F(EPModelFixture, ShadingOverhang_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingOverhang shadingOverhang(model);

  EXPECT_FALSE(shadingOverhang.heightaboveWindoworDoor());
  EXPECT_TRUE(shadingOverhang.isTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingOverhang.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhang.leftextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhang.rightextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhang.depth());

  EXPECT_TRUE(shadingOverhang.setHeightaboveWindoworDoor(0.2));
  ASSERT_TRUE(shadingOverhang.heightaboveWindoworDoor());
  EXPECT_DOUBLE_EQ(0.2, shadingOverhang.heightaboveWindoworDoor().get());

  EXPECT_TRUE(shadingOverhang.setTiltAnglefromWindowDoor(60.0));
  EXPECT_FALSE(shadingOverhang.isTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(60.0, shadingOverhang.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhang.setTiltAnglefromWindowDoor(-1.0));
  EXPECT_DOUBLE_EQ(60.0, shadingOverhang.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhang.setTiltAnglefromWindowDoor(181.0));
  EXPECT_DOUBLE_EQ(60.0, shadingOverhang.tiltAnglefromWindowDoor());

  EXPECT_TRUE(shadingOverhang.setLeftextensionfromWindowDoorWidth(0.3));
  ASSERT_TRUE(shadingOverhang.leftextensionfromWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.3, shadingOverhang.leftextensionfromWindowDoorWidth().get());

  EXPECT_TRUE(shadingOverhang.setRightextensionfromWindowDoorWidth(0.4));
  ASSERT_TRUE(shadingOverhang.rightextensionfromWindowDoorWidth());
  EXPECT_DOUBLE_EQ(0.4, shadingOverhang.rightextensionfromWindowDoorWidth().get());

  EXPECT_TRUE(shadingOverhang.setDepth(0.5));
  ASSERT_TRUE(shadingOverhang.depth());
  EXPECT_DOUBLE_EQ(0.5, shadingOverhang.depth().get());
  EXPECT_FALSE(shadingOverhang.setDepth(-0.1));
  ASSERT_TRUE(shadingOverhang.depth());
  EXPECT_DOUBLE_EQ(0.5, shadingOverhang.depth().get());

  shadingOverhang.resetHeightaboveWindoworDoor();
  shadingOverhang.resetTiltAnglefromWindowDoor();
  shadingOverhang.resetLeftextensionfromWindowDoorWidth();
  shadingOverhang.resetRightextensionfromWindowDoorWidth();
  shadingOverhang.resetDepth();

  EXPECT_FALSE(shadingOverhang.heightaboveWindoworDoor());
  EXPECT_TRUE(shadingOverhang.isTiltAnglefromWindowDoorDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingOverhang.tiltAnglefromWindowDoor());
  EXPECT_FALSE(shadingOverhang.leftextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhang.rightextensionfromWindowDoorWidth());
  EXPECT_FALSE(shadingOverhang.depth());
}
