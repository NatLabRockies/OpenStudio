/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/FloorAdiabatic.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FloorAdiabatic_DefaultConstructor) {
  Model model;
  FloorAdiabatic floor(model);
  EXPECT_EQ(FloorAdiabatic::iddObjectType(), floor.iddObject().type());

  EXPECT_FALSE(floor.azimuthAngle());
  EXPECT_TRUE(floor.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(180.0, floor.tiltAngle());
  EXPECT_FALSE(floor.startingXCoordinate());
  EXPECT_FALSE(floor.startingYCoordinate());
  EXPECT_FALSE(floor.startingZCoordinate());
  EXPECT_FALSE(floor.length());
  EXPECT_FALSE(floor.width());
}

TEST_F(EPModelFixture, FloorAdiabatic_ScalarAccessors_RoundTrip) {
  Model model;
  FloorAdiabatic floor(model);

  EXPECT_TRUE(floor.setAzimuthAngle(45.0));
  ASSERT_TRUE(floor.azimuthAngle());
  EXPECT_DOUBLE_EQ(45.0, floor.azimuthAngle().get());
  EXPECT_FALSE(floor.setAzimuthAngle(-0.1));
  EXPECT_FALSE(floor.setAzimuthAngle(360.1));
  ASSERT_TRUE(floor.azimuthAngle());
  EXPECT_DOUBLE_EQ(45.0, floor.azimuthAngle().get());

  EXPECT_TRUE(floor.setTiltAngle(170.0));
  EXPECT_FALSE(floor.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(170.0, floor.tiltAngle());
  EXPECT_FALSE(floor.setTiltAngle(-0.1));
  EXPECT_FALSE(floor.setTiltAngle(180.1));
  EXPECT_DOUBLE_EQ(170.0, floor.tiltAngle());

  EXPECT_TRUE(floor.setStartingXCoordinate(1.2));
  EXPECT_TRUE(floor.setStartingYCoordinate(3.4));
  EXPECT_TRUE(floor.setStartingZCoordinate(5.6));
  EXPECT_TRUE(floor.setLength(7.8));
  EXPECT_TRUE(floor.setWidth(9.1));

  ASSERT_TRUE(floor.startingXCoordinate());
  ASSERT_TRUE(floor.startingYCoordinate());
  ASSERT_TRUE(floor.startingZCoordinate());
  ASSERT_TRUE(floor.length());
  ASSERT_TRUE(floor.width());
  EXPECT_DOUBLE_EQ(1.2, floor.startingXCoordinate().get());
  EXPECT_DOUBLE_EQ(3.4, floor.startingYCoordinate().get());
  EXPECT_DOUBLE_EQ(5.6, floor.startingZCoordinate().get());
  EXPECT_DOUBLE_EQ(7.8, floor.length().get());
  EXPECT_DOUBLE_EQ(9.1, floor.width().get());

  floor.resetAzimuthAngle();
  floor.resetTiltAngle();
  floor.resetStartingXCoordinate();
  floor.resetStartingYCoordinate();
  floor.resetStartingZCoordinate();
  floor.resetLength();
  floor.resetWidth();

  EXPECT_FALSE(floor.azimuthAngle());
  EXPECT_TRUE(floor.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(180.0, floor.tiltAngle());
  EXPECT_FALSE(floor.startingXCoordinate());
  EXPECT_FALSE(floor.startingYCoordinate());
  EXPECT_FALSE(floor.startingZCoordinate());
  EXPECT_FALSE(floor.length());
  EXPECT_FALSE(floor.width());
}
