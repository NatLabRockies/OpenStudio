/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteHeightVariation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteHeightVariation_DefaultConstructor) {
  Model model;
  SiteHeightVariation object(model);

  EXPECT_EQ(SiteHeightVariation::iddObjectType(), object.iddObject().type());
  EXPECT_TRUE(object.isWindSpeedProfileExponentDefaulted());
  EXPECT_TRUE(object.isWindSpeedProfileBoundaryLayerThicknessDefaulted());
  EXPECT_TRUE(object.isAirTemperatureGradientCoefficientDefaulted());
}

TEST_F(EPModelFixture, SiteHeightVariation_ScalarAccessors_RoundTrip) {
  Model model;
  SiteHeightVariation object(model);

  const double defaultWindSpeedProfileExponent = object.windSpeedProfileExponent();
  EXPECT_TRUE(object.setWindSpeedProfileExponent(0.19));
  EXPECT_DOUBLE_EQ(0.19, object.windSpeedProfileExponent());
  EXPECT_FALSE(object.isWindSpeedProfileExponentDefaulted());
  object.resetWindSpeedProfileExponent();
  EXPECT_TRUE(object.isWindSpeedProfileExponentDefaulted());
  EXPECT_DOUBLE_EQ(defaultWindSpeedProfileExponent, object.windSpeedProfileExponent());

  const double defaultWindSpeedProfileBoundaryLayerThickness = object.windSpeedProfileBoundaryLayerThickness();
  EXPECT_TRUE(object.setWindSpeedProfileBoundaryLayerThickness(420.0));
  EXPECT_DOUBLE_EQ(420.0, object.windSpeedProfileBoundaryLayerThickness());
  EXPECT_FALSE(object.isWindSpeedProfileBoundaryLayerThicknessDefaulted());
  object.resetWindSpeedProfileBoundaryLayerThickness();
  EXPECT_TRUE(object.isWindSpeedProfileBoundaryLayerThicknessDefaulted());
  EXPECT_DOUBLE_EQ(defaultWindSpeedProfileBoundaryLayerThickness, object.windSpeedProfileBoundaryLayerThickness());

  const double defaultAirTemperatureGradientCoefficient = object.airTemperatureGradientCoefficient();
  EXPECT_TRUE(object.setAirTemperatureGradientCoefficient(0.0068));
  EXPECT_DOUBLE_EQ(0.0068, object.airTemperatureGradientCoefficient());
  EXPECT_FALSE(object.isAirTemperatureGradientCoefficientDefaulted());
  object.resetAirTemperatureGradientCoefficient();
  EXPECT_TRUE(object.isAirTemperatureGradientCoefficientDefaulted());
  EXPECT_DOUBLE_EQ(defaultAirTemperatureGradientCoefficient, object.airTemperatureGradientCoefficient());
}
