/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/CeilingAdiabatic.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CeilingAdiabatic_DefaultConstructor) {
  Model model;
  CeilingAdiabatic ceilingAdiabatic(model);
  EXPECT_EQ(CeilingAdiabatic::iddObjectType(), ceilingAdiabatic.iddObject().type());
}

TEST_F(EPModelFixture, CeilingAdiabatic_ScalarAccessors_RoundTrip) {
  Model model;
  CeilingAdiabatic ceilingAdiabatic(model);

  EXPECT_FALSE(ceilingAdiabatic.azimuthAngle());
  EXPECT_TRUE(ceilingAdiabatic.setAzimuthAngle(180.0));
  ASSERT_TRUE(ceilingAdiabatic.azimuthAngle());
  EXPECT_DOUBLE_EQ(180.0, *ceilingAdiabatic.azimuthAngle());
  ceilingAdiabatic.resetAzimuthAngle();
  EXPECT_FALSE(ceilingAdiabatic.azimuthAngle());

  EXPECT_TRUE(ceilingAdiabatic.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(0.0, ceilingAdiabatic.tiltAngle());
  EXPECT_TRUE(ceilingAdiabatic.setTiltAngle(12.0));
  EXPECT_DOUBLE_EQ(12.0, ceilingAdiabatic.tiltAngle());
  EXPECT_FALSE(ceilingAdiabatic.isTiltAngleDefaulted());
  ceilingAdiabatic.resetTiltAngle();
  EXPECT_TRUE(ceilingAdiabatic.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(0.0, ceilingAdiabatic.tiltAngle());

  EXPECT_FALSE(ceilingAdiabatic.startingXCoordinate());
  EXPECT_TRUE(ceilingAdiabatic.setStartingXCoordinate(1.25));
  ASSERT_TRUE(ceilingAdiabatic.startingXCoordinate());
  EXPECT_DOUBLE_EQ(1.25, *ceilingAdiabatic.startingXCoordinate());
  ceilingAdiabatic.resetStartingXCoordinate();
  EXPECT_FALSE(ceilingAdiabatic.startingXCoordinate());

  EXPECT_FALSE(ceilingAdiabatic.startingYCoordinate());
  EXPECT_TRUE(ceilingAdiabatic.setStartingYCoordinate(2.5));
  ASSERT_TRUE(ceilingAdiabatic.startingYCoordinate());
  EXPECT_DOUBLE_EQ(2.5, *ceilingAdiabatic.startingYCoordinate());
  ceilingAdiabatic.resetStartingYCoordinate();
  EXPECT_FALSE(ceilingAdiabatic.startingYCoordinate());

  EXPECT_FALSE(ceilingAdiabatic.startingZCoordinate());
  EXPECT_TRUE(ceilingAdiabatic.setStartingZCoordinate(3.75));
  ASSERT_TRUE(ceilingAdiabatic.startingZCoordinate());
  EXPECT_DOUBLE_EQ(3.75, *ceilingAdiabatic.startingZCoordinate());
  ceilingAdiabatic.resetStartingZCoordinate();
  EXPECT_FALSE(ceilingAdiabatic.startingZCoordinate());

  EXPECT_FALSE(ceilingAdiabatic.length());
  EXPECT_TRUE(ceilingAdiabatic.setLength(6.4));
  ASSERT_TRUE(ceilingAdiabatic.length());
  EXPECT_DOUBLE_EQ(6.4, *ceilingAdiabatic.length());
  ceilingAdiabatic.resetLength();
  EXPECT_FALSE(ceilingAdiabatic.length());

  EXPECT_FALSE(ceilingAdiabatic.width());
  EXPECT_TRUE(ceilingAdiabatic.setWidth(4.2));
  ASSERT_TRUE(ceilingAdiabatic.width());
  EXPECT_DOUBLE_EQ(4.2, *ceilingAdiabatic.width());
  ceilingAdiabatic.resetWidth();
  EXPECT_FALSE(ceilingAdiabatic.width());
}
