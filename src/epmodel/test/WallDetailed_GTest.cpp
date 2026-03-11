/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WallDetailed.hpp"
#include "../ModelObject/WallDetailed_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WallDetailed_DefaultConstructor) {
  Model model;
  WallDetailed wall(model);
  EXPECT_EQ(WallDetailed::iddObjectType(), wall.iddObject().type());
}

TEST_F(EPModelFixture, WallDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  WallDetailed wall(model);

  EXPECT_FALSE(WallDetailed::outsideBoundaryConditionValues().empty());
  EXPECT_FALSE(WallDetailed::sunExposureValues().empty());
  EXPECT_FALSE(WallDetailed::windExposureValues().empty());

  EXPECT_TRUE(wall.setOutsideBoundaryCondition("Adiabatic"));
  EXPECT_EQ("Adiabatic", wall.outsideBoundaryCondition());

  EXPECT_TRUE(wall.setSunExposure("NoSun"));
  EXPECT_EQ("NoSun", wall.sunExposure());
  EXPECT_FALSE(wall.isSunExposureDefaulted());
  wall.resetSunExposure();
  EXPECT_TRUE(wall.isSunExposureDefaulted());

  EXPECT_TRUE(wall.setWindExposure("NoWind"));
  EXPECT_EQ("NoWind", wall.windExposure());
  EXPECT_FALSE(wall.isWindExposureDefaulted());
  wall.resetWindExposure();
  EXPECT_TRUE(wall.isWindExposureDefaulted());

  EXPECT_TRUE(wall.setViewFactorToGround(0.25));
  ASSERT_TRUE(wall.viewFactorToGround());
  EXPECT_DOUBLE_EQ(0.25, wall.viewFactorToGround().get());
  EXPECT_FALSE(wall.isViewFactorToGroundAutocalculated());
  EXPECT_FALSE(wall.isViewFactorToGroundDefaulted());

  wall.autocalculateViewFactorToGround();
  EXPECT_TRUE(wall.isViewFactorToGroundAutocalculated());
  wall.resetViewFactorToGround();
  EXPECT_TRUE(wall.isViewFactorToGroundDefaulted());
  EXPECT_FALSE(wall.viewFactorToGround());
}
