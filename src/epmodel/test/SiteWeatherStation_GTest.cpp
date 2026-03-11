/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteWeatherStation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteWeatherStation_DefaultConstructor) {
  Model model;
  SiteWeatherStation object(model);

  EXPECT_EQ(SiteWeatherStation::iddObjectType(), object.iddObject().type());

  EXPECT_TRUE(object.isWindSensorHeightAboveGroundDefaulted());
  EXPECT_DOUBLE_EQ(10.0, object.windSensorHeightAboveGround());

  EXPECT_TRUE(object.isWindSpeedProfileExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.14, object.windSpeedProfileExponent());

  EXPECT_TRUE(object.isWindSpeedProfileBoundaryLayerThicknessDefaulted());
  EXPECT_DOUBLE_EQ(270.0, object.windSpeedProfileBoundaryLayerThickness());

  EXPECT_TRUE(object.isAirTemperatureSensorHeightAboveGroundDefaulted());
  EXPECT_DOUBLE_EQ(1.5, object.airTemperatureSensorHeightAboveGround());
}

TEST_F(EPModelFixture, SiteWeatherStation_ScalarAccessors_RoundTrip) {
  Model model;
  SiteWeatherStation object(model);

  EXPECT_TRUE(object.setWindSensorHeightAboveGround(12.0));
  EXPECT_FALSE(object.isWindSensorHeightAboveGroundDefaulted());
  EXPECT_DOUBLE_EQ(12.0, object.windSensorHeightAboveGround());
  EXPECT_FALSE(object.setWindSensorHeightAboveGround(0.0));
  object.resetWindSensorHeightAboveGround();
  EXPECT_TRUE(object.isWindSensorHeightAboveGroundDefaulted());
  EXPECT_DOUBLE_EQ(10.0, object.windSensorHeightAboveGround());

  EXPECT_TRUE(object.setWindSpeedProfileExponent(0.18));
  EXPECT_FALSE(object.isWindSpeedProfileExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.18, object.windSpeedProfileExponent());
  EXPECT_FALSE(object.setWindSpeedProfileExponent(-0.1));
  object.resetWindSpeedProfileExponent();
  EXPECT_TRUE(object.isWindSpeedProfileExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.14, object.windSpeedProfileExponent());

  EXPECT_TRUE(object.setWindSpeedProfileBoundaryLayerThickness(300.0));
  EXPECT_FALSE(object.isWindSpeedProfileBoundaryLayerThicknessDefaulted());
  EXPECT_DOUBLE_EQ(300.0, object.windSpeedProfileBoundaryLayerThickness());
  EXPECT_FALSE(object.setWindSpeedProfileBoundaryLayerThickness(-1.0));
  object.resetWindSpeedProfileBoundaryLayerThickness();
  EXPECT_TRUE(object.isWindSpeedProfileBoundaryLayerThicknessDefaulted());
  EXPECT_DOUBLE_EQ(270.0, object.windSpeedProfileBoundaryLayerThickness());

  EXPECT_TRUE(object.setAirTemperatureSensorHeightAboveGround(2.0));
  EXPECT_FALSE(object.isAirTemperatureSensorHeightAboveGroundDefaulted());
  EXPECT_DOUBLE_EQ(2.0, object.airTemperatureSensorHeightAboveGround());
  EXPECT_FALSE(object.setAirTemperatureSensorHeightAboveGround(-0.01));
  object.resetAirTemperatureSensorHeightAboveGround();
  EXPECT_TRUE(object.isAirTemperatureSensorHeightAboveGroundDefaulted());
  EXPECT_DOUBLE_EQ(1.5, object.airTemperatureSensorHeightAboveGround());
}
