/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfaceConvectionAlgorithmOutsideUserCurve.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmOutsideUserCurve_DefaultConstructor) {
  Model model;
  SurfaceConvectionAlgorithmOutsideUserCurve userCurve(model);
  EXPECT_EQ(SurfaceConvectionAlgorithmOutsideUserCurve::iddObjectType(), userCurve.iddObject().type());
}

TEST_F(EPModelFixture, SurfaceConvectionAlgorithmOutsideUserCurve_ScalarAccessors_RoundTrip) {
  Model model;
  SurfaceConvectionAlgorithmOutsideUserCurve userCurve(model);

  // windSpeedTypeforCurve is a defaulted choice field (default "HeightAdjust", not required)
  // Getter is non-optional (std::string) because it has a default.
  // Initially should be defaulted
  EXPECT_TRUE(userCurve.isWindSpeedTypeforCurveDefaulted());
  EXPECT_EQ("HeightAdjust", userCurve.windSpeedTypeforCurve());

  // Set and roundtrip each valid key
  EXPECT_TRUE(userCurve.setWindSpeedTypeforCurve("WeatherFile"));
  EXPECT_EQ("WeatherFile", userCurve.windSpeedTypeforCurve());
  EXPECT_FALSE(userCurve.isWindSpeedTypeforCurveDefaulted());

  EXPECT_TRUE(userCurve.setWindSpeedTypeforCurve("ParallelComponent"));
  EXPECT_EQ("ParallelComponent", userCurve.windSpeedTypeforCurve());

  EXPECT_TRUE(userCurve.setWindSpeedTypeforCurve("ParallelComponentHeightAdjust"));
  EXPECT_EQ("ParallelComponentHeightAdjust", userCurve.windSpeedTypeforCurve());

  EXPECT_TRUE(userCurve.setWindSpeedTypeforCurve("HeightAdjust"));
  EXPECT_EQ("HeightAdjust", userCurve.windSpeedTypeforCurve());

  // Invalid key should fail
  EXPECT_FALSE(userCurve.setWindSpeedTypeforCurve("InvalidKey"));
  // Value should remain unchanged after failed set
  EXPECT_EQ("HeightAdjust", userCurve.windSpeedTypeforCurve());

  // Set to non-default, then reset -> should return to defaulted state
  EXPECT_TRUE(userCurve.setWindSpeedTypeforCurve("WeatherFile"));
  EXPECT_FALSE(userCurve.isWindSpeedTypeforCurveDefaulted());
  userCurve.resetWindSpeedTypeforCurve();
  EXPECT_TRUE(userCurve.isWindSpeedTypeforCurveDefaulted());
  EXPECT_EQ("HeightAdjust", userCurve.windSpeedTypeforCurve());

  // Values helper
  auto values = SurfaceConvectionAlgorithmOutsideUserCurve::windSpeedTypeforCurveValues();
  EXPECT_EQ(4u, values.size());

  // Name roundtrip (base ModelObject)
  EXPECT_TRUE(userCurve.setName("TestOutsideUserCurve"));
  EXPECT_EQ("TestOutsideUserCurve", userCurve.nameString());
}
