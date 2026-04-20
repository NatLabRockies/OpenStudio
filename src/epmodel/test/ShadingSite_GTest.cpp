/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingSite.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingSite_DefaultConstructor) {
  Model model;
  ShadingSite shadingSite(model);
  EXPECT_EQ(ShadingSite::iddObjectType(), shadingSite.iddObject().type());
}

TEST_F(EPModelFixture, ShadingSite_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingSite shadingSite(model);

  EXPECT_FALSE(shadingSite.azimuthAngle());
  EXPECT_TRUE(shadingSite.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingSite.tiltAngle());
  EXPECT_FALSE(shadingSite.startingXCoordinate());
  EXPECT_FALSE(shadingSite.startingYCoordinate());
  EXPECT_FALSE(shadingSite.startingZCoordinate());
  EXPECT_FALSE(shadingSite.length());
  EXPECT_FALSE(shadingSite.height());

  EXPECT_TRUE(shadingSite.setAzimuthAngle(180.0));
  ASSERT_TRUE(shadingSite.azimuthAngle());
  EXPECT_DOUBLE_EQ(180.0, shadingSite.azimuthAngle().get());

  EXPECT_TRUE(shadingSite.setTiltAngle(45.0));
  EXPECT_FALSE(shadingSite.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(45.0, shadingSite.tiltAngle());

  EXPECT_TRUE(shadingSite.setStartingXCoordinate(1.0));
  ASSERT_TRUE(shadingSite.startingXCoordinate());
  EXPECT_DOUBLE_EQ(1.0, shadingSite.startingXCoordinate().get());

  EXPECT_TRUE(shadingSite.setStartingYCoordinate(2.0));
  ASSERT_TRUE(shadingSite.startingYCoordinate());
  EXPECT_DOUBLE_EQ(2.0, shadingSite.startingYCoordinate().get());

  EXPECT_TRUE(shadingSite.setStartingZCoordinate(3.0));
  ASSERT_TRUE(shadingSite.startingZCoordinate());
  EXPECT_DOUBLE_EQ(3.0, shadingSite.startingZCoordinate().get());

  EXPECT_TRUE(shadingSite.setLength(4.0));
  ASSERT_TRUE(shadingSite.length());
  EXPECT_DOUBLE_EQ(4.0, shadingSite.length().get());

  EXPECT_TRUE(shadingSite.setHeight(5.0));
  ASSERT_TRUE(shadingSite.height());
  EXPECT_DOUBLE_EQ(5.0, shadingSite.height().get());

  shadingSite.resetAzimuthAngle();
  EXPECT_FALSE(shadingSite.azimuthAngle());

  shadingSite.resetTiltAngle();
  EXPECT_TRUE(shadingSite.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingSite.tiltAngle());

  shadingSite.resetStartingXCoordinate();
  EXPECT_FALSE(shadingSite.startingXCoordinate());
  shadingSite.resetStartingYCoordinate();
  EXPECT_FALSE(shadingSite.startingYCoordinate());
  shadingSite.resetStartingZCoordinate();
  EXPECT_FALSE(shadingSite.startingZCoordinate());
  shadingSite.resetLength();
  EXPECT_FALSE(shadingSite.length());
  shadingSite.resetHeight();
  EXPECT_FALSE(shadingSite.height());
}
