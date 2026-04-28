/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../scaffolds/FloorDetailed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FloorDetailed_DefaultConstructor) {
  Model model;
  FloorDetailed floor(model);
  EXPECT_EQ(FloorDetailed::iddObjectType(), floor.iddObject().type());

  EXPECT_TRUE(floor.isSunExposureDefaulted());
  EXPECT_EQ("SunExposed", floor.sunExposure());
  EXPECT_TRUE(floor.isWindExposureDefaulted());
  EXPECT_EQ("WindExposed", floor.windExposure());

  EXPECT_FALSE(floor.viewFactortoGround());
  EXPECT_TRUE(floor.isViewFactortoGroundAutocalculated());
  EXPECT_FALSE(floor.numberofVertices());
  EXPECT_TRUE(floor.isNumberofVerticesAutocalculated());
}

TEST_F(EPModelFixture, FloorDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  FloorDetailed floor(model);

  const auto obcValues = FloorDetailed::outsideBoundaryConditionValues();
  EXPECT_NE(obcValues.end(), std::find(obcValues.begin(), obcValues.end(), "Outdoors"));
  EXPECT_TRUE(floor.setOutsideBoundaryCondition("Outdoors"));
  EXPECT_EQ("Outdoors", floor.outsideBoundaryCondition());
  EXPECT_FALSE(floor.setOutsideBoundaryCondition("InvalidChoice"));
  EXPECT_EQ("Outdoors", floor.outsideBoundaryCondition());

  EXPECT_TRUE(floor.setSunExposure("NoSun"));
  EXPECT_EQ("NoSun", floor.sunExposure());
  EXPECT_FALSE(floor.isSunExposureDefaulted());
  EXPECT_FALSE(floor.setSunExposure("InvalidChoice"));
  EXPECT_EQ("NoSun", floor.sunExposure());
  floor.resetSunExposure();
  EXPECT_TRUE(floor.isSunExposureDefaulted());
  EXPECT_EQ("SunExposed", floor.sunExposure());

  EXPECT_TRUE(floor.setWindExposure("NoWind"));
  EXPECT_EQ("NoWind", floor.windExposure());
  EXPECT_FALSE(floor.isWindExposureDefaulted());
  EXPECT_FALSE(floor.setWindExposure("InvalidChoice"));
  EXPECT_EQ("NoWind", floor.windExposure());
  floor.resetWindExposure();
  EXPECT_TRUE(floor.isWindExposureDefaulted());
  EXPECT_EQ("WindExposed", floor.windExposure());

  EXPECT_TRUE(floor.setViewFactortoGround(0.4));
  ASSERT_TRUE(floor.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.4, floor.viewFactortoGround().get());
  EXPECT_FALSE(floor.isViewFactortoGroundAutocalculated());
  EXPECT_FALSE(floor.setViewFactortoGround(-0.1));
  EXPECT_FALSE(floor.setViewFactortoGround(1.1));
  ASSERT_TRUE(floor.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.4, floor.viewFactortoGround().get());
  floor.autocalculateViewFactortoGround();
  EXPECT_FALSE(floor.viewFactortoGround());
  EXPECT_TRUE(floor.isViewFactortoGroundAutocalculated());
  floor.resetViewFactortoGround();
  EXPECT_FALSE(floor.viewFactortoGround());
  EXPECT_TRUE(floor.isViewFactortoGroundAutocalculated());

  EXPECT_TRUE(floor.setNumberofVertices(4));
  ASSERT_TRUE(floor.numberofVertices());
  EXPECT_EQ(4, floor.numberofVertices().get());
  EXPECT_FALSE(floor.isNumberofVerticesAutocalculated());
  EXPECT_FALSE(floor.setNumberofVertices(2));
  ASSERT_TRUE(floor.numberofVertices());
  EXPECT_EQ(4, floor.numberofVertices().get());
  floor.autocalculateNumberofVertices();
  EXPECT_FALSE(floor.numberofVertices());
  EXPECT_TRUE(floor.isNumberofVerticesAutocalculated());
  floor.resetNumberofVertices();
  EXPECT_FALSE(floor.numberofVertices());
  EXPECT_TRUE(floor.isNumberofVerticesAutocalculated());
}
