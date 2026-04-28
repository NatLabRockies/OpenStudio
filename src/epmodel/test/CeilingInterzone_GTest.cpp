/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/CeilingInterzone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CeilingInterzone_DefaultConstructor) {
  Model model;
  CeilingInterzone ceilingInterzone(model);
  EXPECT_EQ(CeilingInterzone::iddObjectType(), ceilingInterzone.iddObject().type());
}

TEST_F(EPModelFixture, CeilingInterzone_ScalarAccessors_RoundTrip) {
  Model model;
  CeilingInterzone ceilingInterzone(model);

  EXPECT_FALSE(ceilingInterzone.azimuthAngle());
  EXPECT_TRUE(ceilingInterzone.setAzimuthAngle(270.0));
  ASSERT_TRUE(ceilingInterzone.azimuthAngle());
  EXPECT_DOUBLE_EQ(270.0, *ceilingInterzone.azimuthAngle());
  ceilingInterzone.resetAzimuthAngle();
  EXPECT_FALSE(ceilingInterzone.azimuthAngle());

  EXPECT_TRUE(ceilingInterzone.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(0.0, ceilingInterzone.tiltAngle());
  EXPECT_TRUE(ceilingInterzone.setTiltAngle(22.0));
  EXPECT_DOUBLE_EQ(22.0, ceilingInterzone.tiltAngle());
  EXPECT_FALSE(ceilingInterzone.isTiltAngleDefaulted());
  ceilingInterzone.resetTiltAngle();
  EXPECT_TRUE(ceilingInterzone.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(0.0, ceilingInterzone.tiltAngle());

  EXPECT_FALSE(ceilingInterzone.startingXCoordinate());
  EXPECT_TRUE(ceilingInterzone.setStartingXCoordinate(1.0));
  ASSERT_TRUE(ceilingInterzone.startingXCoordinate());
  EXPECT_DOUBLE_EQ(1.0, *ceilingInterzone.startingXCoordinate());
  ceilingInterzone.resetStartingXCoordinate();
  EXPECT_FALSE(ceilingInterzone.startingXCoordinate());

  EXPECT_FALSE(ceilingInterzone.startingYCoordinate());
  EXPECT_TRUE(ceilingInterzone.setStartingYCoordinate(2.0));
  ASSERT_TRUE(ceilingInterzone.startingYCoordinate());
  EXPECT_DOUBLE_EQ(2.0, *ceilingInterzone.startingYCoordinate());
  ceilingInterzone.resetStartingYCoordinate();
  EXPECT_FALSE(ceilingInterzone.startingYCoordinate());

  EXPECT_FALSE(ceilingInterzone.startingZCoordinate());
  EXPECT_TRUE(ceilingInterzone.setStartingZCoordinate(3.0));
  ASSERT_TRUE(ceilingInterzone.startingZCoordinate());
  EXPECT_DOUBLE_EQ(3.0, *ceilingInterzone.startingZCoordinate());
  ceilingInterzone.resetStartingZCoordinate();
  EXPECT_FALSE(ceilingInterzone.startingZCoordinate());

  EXPECT_FALSE(ceilingInterzone.length());
  EXPECT_TRUE(ceilingInterzone.setLength(6.0));
  ASSERT_TRUE(ceilingInterzone.length());
  EXPECT_DOUBLE_EQ(6.0, *ceilingInterzone.length());
  ceilingInterzone.resetLength();
  EXPECT_FALSE(ceilingInterzone.length());

  EXPECT_FALSE(ceilingInterzone.width());
  EXPECT_TRUE(ceilingInterzone.setWidth(4.5));
  ASSERT_TRUE(ceilingInterzone.width());
  EXPECT_DOUBLE_EQ(4.5, *ceilingInterzone.width());
  ceilingInterzone.resetWidth();
  EXPECT_FALSE(ceilingInterzone.width());
}
