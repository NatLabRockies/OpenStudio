/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ShadingBuilding.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadingBuilding_DefaultConstructor) {
  Model model;
  ShadingBuilding shadingBuilding(model);
  EXPECT_EQ(ShadingBuilding::iddObjectType(), shadingBuilding.iddObject().type());
}

TEST_F(EPModelFixture, ShadingBuilding_ScalarAccessors_RoundTrip) {
  Model model;
  ShadingBuilding shadingBuilding(model);

  EXPECT_FALSE(shadingBuilding.azimuthAngle());
  EXPECT_TRUE(shadingBuilding.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingBuilding.tiltAngle());
  EXPECT_FALSE(shadingBuilding.startingXCoordinate());
  EXPECT_FALSE(shadingBuilding.startingYCoordinate());
  EXPECT_FALSE(shadingBuilding.startingZCoordinate());
  EXPECT_FALSE(shadingBuilding.length());
  EXPECT_FALSE(shadingBuilding.height());

  EXPECT_TRUE(shadingBuilding.setAzimuthAngle(180.0));
  EXPECT_TRUE(shadingBuilding.azimuthAngle());
  EXPECT_DOUBLE_EQ(180.0, shadingBuilding.azimuthAngle().get());

  EXPECT_TRUE(shadingBuilding.setTiltAngle(45.0));
  EXPECT_FALSE(shadingBuilding.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(45.0, shadingBuilding.tiltAngle());

  EXPECT_TRUE(shadingBuilding.setStartingXCoordinate(1.0));
  EXPECT_TRUE(shadingBuilding.startingXCoordinate());
  EXPECT_DOUBLE_EQ(1.0, shadingBuilding.startingXCoordinate().get());

  EXPECT_TRUE(shadingBuilding.setStartingYCoordinate(2.0));
  EXPECT_TRUE(shadingBuilding.startingYCoordinate());
  EXPECT_DOUBLE_EQ(2.0, shadingBuilding.startingYCoordinate().get());

  EXPECT_TRUE(shadingBuilding.setStartingZCoordinate(3.0));
  EXPECT_TRUE(shadingBuilding.startingZCoordinate());
  EXPECT_DOUBLE_EQ(3.0, shadingBuilding.startingZCoordinate().get());

  EXPECT_TRUE(shadingBuilding.setLength(4.0));
  EXPECT_TRUE(shadingBuilding.length());
  EXPECT_DOUBLE_EQ(4.0, shadingBuilding.length().get());

  EXPECT_TRUE(shadingBuilding.setHeight(5.0));
  EXPECT_TRUE(shadingBuilding.height());
  EXPECT_DOUBLE_EQ(5.0, shadingBuilding.height().get());

  shadingBuilding.resetAzimuthAngle();
  EXPECT_FALSE(shadingBuilding.azimuthAngle());

  shadingBuilding.resetTiltAngle();
  EXPECT_TRUE(shadingBuilding.isTiltAngleDefaulted());
  EXPECT_DOUBLE_EQ(90.0, shadingBuilding.tiltAngle());

  shadingBuilding.resetStartingXCoordinate();
  EXPECT_FALSE(shadingBuilding.startingXCoordinate());
  shadingBuilding.resetStartingYCoordinate();
  EXPECT_FALSE(shadingBuilding.startingYCoordinate());
  shadingBuilding.resetStartingZCoordinate();
  EXPECT_FALSE(shadingBuilding.startingZCoordinate());
  shadingBuilding.resetLength();
  EXPECT_FALSE(shadingBuilding.length());
  shadingBuilding.resetHeight();
  EXPECT_FALSE(shadingBuilding.height());
}
