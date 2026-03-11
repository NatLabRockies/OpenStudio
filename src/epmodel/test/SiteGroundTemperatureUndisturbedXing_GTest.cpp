/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedXing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureUndisturbedXing_DefaultConstructor) {
  Model model;
  SiteGroundTemperatureUndisturbedXing object(model);
  EXPECT_EQ(SiteGroundTemperatureUndisturbedXing::iddObjectType(), object.iddObject().type());

  EXPECT_DOUBLE_EQ(1.08, object.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(962.0, object.soilDensity());
  EXPECT_DOUBLE_EQ(2576.0, object.soilSpecificHeat());
  EXPECT_DOUBLE_EQ(11.1, object.averageSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(13.4, object.soilSurfaceTemperatureAmplitude1());
  EXPECT_DOUBLE_EQ(0.7, object.soilSurfaceTemperatureAmplitude2());
  EXPECT_DOUBLE_EQ(25.0, object.phaseShiftofTemperatureAmplitude1());
  EXPECT_DOUBLE_EQ(30.0, object.phaseShiftofTemperatureAmplitude2());
}

TEST_F(EPModelFixture, SiteGroundTemperatureUndisturbedXing_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundTemperatureUndisturbedXing object(model);

  EXPECT_TRUE(object.setSoilThermalConductivity(1.3));
  EXPECT_DOUBLE_EQ(1.3, object.soilThermalConductivity());

  EXPECT_TRUE(object.setSoilDensity(971.0));
  EXPECT_DOUBLE_EQ(971.0, object.soilDensity());

  EXPECT_TRUE(object.setSoilSpecificHeat(2701.0));
  EXPECT_DOUBLE_EQ(2701.0, object.soilSpecificHeat());

  EXPECT_TRUE(object.setAverageSoilSurfaceTemperature(11.2));
  EXPECT_DOUBLE_EQ(11.2, object.averageSoilSurfaceTemperature());

  EXPECT_TRUE(object.setSoilSurfaceTemperatureAmplitude1(13.5));
  EXPECT_DOUBLE_EQ(13.5, object.soilSurfaceTemperatureAmplitude1());

  EXPECT_TRUE(object.setSoilSurfaceTemperatureAmplitude2(0.8));
  EXPECT_DOUBLE_EQ(0.8, object.soilSurfaceTemperatureAmplitude2());

  EXPECT_TRUE(object.setPhaseShiftofTemperatureAmplitude1(26.0));
  EXPECT_DOUBLE_EQ(26.0, object.phaseShiftofTemperatureAmplitude1());

  EXPECT_TRUE(object.setPhaseShiftofTemperatureAmplitude2(31.0));
  EXPECT_DOUBLE_EQ(31.0, object.phaseShiftofTemperatureAmplitude2());
}
