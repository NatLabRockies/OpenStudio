/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/Roof.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Roof_DefaultConstructor) {
  Model model;
  Roof roof(model);
  EXPECT_EQ(Roof::iddObjectType(), roof.iddObject().type());
}

TEST_F(EPModelFixture, Roof_ScalarAccessors_RoundTrip) {
  Model model;
  Roof roof(model);

  EXPECT_TRUE(roof.setAzimuthAngle(220.0));
  ASSERT_TRUE(roof.azimuthAngle());
  EXPECT_DOUBLE_EQ(220.0, *roof.azimuthAngle());
  roof.resetAzimuthAngle();
  EXPECT_FALSE(roof.azimuthAngle());

  EXPECT_TRUE(roof.isTiltAngleDefaulted());
  EXPECT_TRUE(roof.setTiltAngle(15.5));
  EXPECT_FALSE(roof.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(15.5, roof.tiltAngle());
  roof.resetTiltAngle();
  EXPECT_TRUE(roof.isTiltAngleDefaulted());

  EXPECT_TRUE(roof.setStartingXCoordinate(1.0));
  EXPECT_TRUE(roof.startingXCoordinate());
  roof.resetStartingXCoordinate();
  EXPECT_FALSE(roof.startingXCoordinate());

  EXPECT_TRUE(roof.setStartingYCoordinate(2.0));
  EXPECT_TRUE(roof.startingYCoordinate());
  roof.resetStartingYCoordinate();
  EXPECT_FALSE(roof.startingYCoordinate());

  EXPECT_TRUE(roof.setStartingZCoordinate(3.0));
  EXPECT_TRUE(roof.startingZCoordinate());
  roof.resetStartingZCoordinate();
  EXPECT_FALSE(roof.startingZCoordinate());

  EXPECT_TRUE(roof.setLength(5.0));
  EXPECT_TRUE(roof.length());
  roof.resetLength();
  EXPECT_FALSE(roof.length());

  EXPECT_TRUE(roof.setWidth(7.5));
  EXPECT_TRUE(roof.width());
  roof.resetWidth();
  EXPECT_FALSE(roof.width());
}
