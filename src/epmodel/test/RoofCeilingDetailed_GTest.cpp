/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoofCeilingDetailed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoofCeilingDetailed_DefaultConstructor) {
  Model model;
  RoofCeilingDetailed roof(model);
  EXPECT_EQ(RoofCeilingDetailed::iddObjectType(), roof.iddObject().type());

  EXPECT_TRUE(roof.isSunExposureDefaulted());
  EXPECT_EQ("SunExposed", roof.sunExposure());
  EXPECT_TRUE(roof.isWindExposureDefaulted());
  EXPECT_EQ("WindExposed", roof.windExposure());

  EXPECT_FALSE(roof.viewFactortoGround());
  EXPECT_TRUE(roof.isViewFactortoGroundAutocalculated());
  EXPECT_FALSE(roof.numberofVertices());
  EXPECT_TRUE(roof.isNumberofVerticesAutocalculated());
}

TEST_F(EPModelFixture, RoofCeilingDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  RoofCeilingDetailed roof(model);

  const auto obcValues = RoofCeilingDetailed::outsideBoundaryConditionValues();
  EXPECT_NE(obcValues.end(), std::find(obcValues.begin(), obcValues.end(), "Outdoors"));
  EXPECT_TRUE(roof.setOutsideBoundaryCondition("Outdoors"));
  EXPECT_EQ("Outdoors", roof.outsideBoundaryCondition());
  EXPECT_FALSE(roof.setOutsideBoundaryCondition("InvalidChoice"));
  EXPECT_EQ("Outdoors", roof.outsideBoundaryCondition());

  EXPECT_TRUE(roof.setSunExposure("NoSun"));
  EXPECT_EQ("NoSun", roof.sunExposure());
  EXPECT_FALSE(roof.isSunExposureDefaulted());
  EXPECT_FALSE(roof.setSunExposure("InvalidChoice"));
  EXPECT_EQ("NoSun", roof.sunExposure());
  roof.resetSunExposure();
  EXPECT_TRUE(roof.isSunExposureDefaulted());
  EXPECT_EQ("SunExposed", roof.sunExposure());

  EXPECT_TRUE(roof.setWindExposure("NoWind"));
  EXPECT_EQ("NoWind", roof.windExposure());
  EXPECT_FALSE(roof.isWindExposureDefaulted());
  EXPECT_FALSE(roof.setWindExposure("InvalidChoice"));
  EXPECT_EQ("NoWind", roof.windExposure());
  roof.resetWindExposure();
  EXPECT_TRUE(roof.isWindExposureDefaulted());
  EXPECT_EQ("WindExposed", roof.windExposure());

  EXPECT_TRUE(roof.setViewFactortoGround(0.4));
  ASSERT_TRUE(roof.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.4, roof.viewFactortoGround().get());
  EXPECT_FALSE(roof.isViewFactortoGroundAutocalculated());
  EXPECT_FALSE(roof.setViewFactortoGround(-0.1));
  EXPECT_FALSE(roof.setViewFactortoGround(1.1));
  ASSERT_TRUE(roof.viewFactortoGround());
  EXPECT_DOUBLE_EQ(0.4, roof.viewFactortoGround().get());
  roof.autocalculateViewFactortoGround();
  EXPECT_FALSE(roof.viewFactortoGround());
  EXPECT_TRUE(roof.isViewFactortoGroundAutocalculated());
  roof.resetViewFactortoGround();
  EXPECT_FALSE(roof.viewFactortoGround());
  EXPECT_TRUE(roof.isViewFactortoGroundAutocalculated());

  EXPECT_TRUE(roof.setNumberofVertices(4));
  ASSERT_TRUE(roof.numberofVertices());
  EXPECT_EQ(4, roof.numberofVertices().get());
  EXPECT_FALSE(roof.isNumberofVerticesAutocalculated());
  EXPECT_FALSE(roof.setNumberofVertices(2));
  ASSERT_TRUE(roof.numberofVertices());
  EXPECT_EQ(4, roof.numberofVertices().get());
  roof.autocalculateNumberofVertices();
  EXPECT_FALSE(roof.numberofVertices());
  EXPECT_TRUE(roof.isNumberofVerticesAutocalculated());
  roof.resetNumberofVertices();
  EXPECT_FALSE(roof.numberofVertices());
  EXPECT_TRUE(roof.isNumberofVerticesAutocalculated());
}
