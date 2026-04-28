/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/WallAdiabatic.hpp"
#include "../scaffolds/WallAdiabatic_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_WallAdiabatic_DefaultConstructor) {
  Model model;
  WallAdiabatic wall(model);
  EXPECT_EQ(WallAdiabatic::iddObjectType(), wall.iddObject().type());
  EXPECT_FALSE(wall.azimuthAngle());
  EXPECT_FALSE(wall.startingXCoordinate());
  EXPECT_FALSE(wall.startingYCoordinate());
  EXPECT_FALSE(wall.startingZCoordinate());
  EXPECT_FALSE(wall.length());
  EXPECT_FALSE(wall.height());
}

TEST_F(EPModelFixture, WallAdiabatic_ScalarAccessors_RoundTrip) {
  Model model;
  WallAdiabatic wall(model);

  EXPECT_TRUE(wall.setAzimuthAngle(123.4));
  ASSERT_TRUE(wall.azimuthAngle());
  EXPECT_DOUBLE_EQ(123.4, wall.azimuthAngle().get());
  wall.resetAzimuthAngle();
  EXPECT_FALSE(wall.azimuthAngle());

  EXPECT_TRUE(wall.setTiltAngle(45.0));
  EXPECT_DOUBLE_EQ(45.0, wall.tiltAngle());
  EXPECT_FALSE(wall.isTiltAngleDefaulted());
  wall.resetTiltAngle();
  EXPECT_TRUE(wall.isTiltAngleDefaulted());

  EXPECT_TRUE(wall.setStartingXCoordinate(1.1));
  ASSERT_TRUE(wall.startingXCoordinate());
  EXPECT_DOUBLE_EQ(1.1, wall.startingXCoordinate().get());
  wall.resetStartingXCoordinate();
  EXPECT_FALSE(wall.startingXCoordinate());

  EXPECT_TRUE(wall.setStartingYCoordinate(2.2));
  ASSERT_TRUE(wall.startingYCoordinate());
  EXPECT_DOUBLE_EQ(2.2, wall.startingYCoordinate().get());
  wall.resetStartingYCoordinate();
  EXPECT_FALSE(wall.startingYCoordinate());

  EXPECT_TRUE(wall.setStartingZCoordinate(3.3));
  ASSERT_TRUE(wall.startingZCoordinate());
  EXPECT_DOUBLE_EQ(3.3, wall.startingZCoordinate().get());
  wall.resetStartingZCoordinate();
  EXPECT_FALSE(wall.startingZCoordinate());

  EXPECT_TRUE(wall.setLength(4.4));
  ASSERT_TRUE(wall.length());
  EXPECT_DOUBLE_EQ(4.4, wall.length().get());
  wall.resetLength();
  EXPECT_FALSE(wall.length());

  EXPECT_TRUE(wall.setHeight(5.5));
  ASSERT_TRUE(wall.height());
  EXPECT_DOUBLE_EQ(5.5, wall.height().get());
  wall.resetHeight();
  EXPECT_FALSE(wall.height());
}
