/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureUndisturbedKusudaAchenbach_DefaultConstructor) {
  Model model;
  SiteGroundTemperatureUndisturbedKusudaAchenbach object(model);
  EXPECT_EQ(SiteGroundTemperatureUndisturbedKusudaAchenbach::iddObjectType(), object.iddObject().type());

  EXPECT_DOUBLE_EQ(1.08, object.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(962.0, object.soilDensity());
  EXPECT_DOUBLE_EQ(2576.0, object.soilSpecificHeat());

  ASSERT_TRUE(object.averageSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(15.5, object.averageSoilSurfaceTemperature().get());
  ASSERT_TRUE(object.averageAmplitudeofSurfaceTemperature());
  EXPECT_DOUBLE_EQ(12.8, object.averageAmplitudeofSurfaceTemperature().get());
  ASSERT_TRUE(object.phaseShiftofMinimumSurfaceTemperature());
  EXPECT_DOUBLE_EQ(17.3, object.phaseShiftofMinimumSurfaceTemperature().get());
}

TEST_F(EPModelFixture, SiteGroundTemperatureUndisturbedKusudaAchenbach_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundTemperatureUndisturbedKusudaAchenbach object(model);

  EXPECT_TRUE(object.setSoilThermalConductivity(1.2));
  EXPECT_DOUBLE_EQ(1.2, object.soilThermalConductivity());

  EXPECT_TRUE(object.setSoilDensity(970.0));
  EXPECT_DOUBLE_EQ(970.0, object.soilDensity());

  EXPECT_TRUE(object.setSoilSpecificHeat(2700.0));
  EXPECT_DOUBLE_EQ(2700.0, object.soilSpecificHeat());

  EXPECT_TRUE(object.setAverageSoilSurfaceTemperature(17.0));
  ASSERT_TRUE(object.averageSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(17.0, object.averageSoilSurfaceTemperature().get());
  object.resetAverageSoilSurfaceTemperature();
  EXPECT_FALSE(object.averageSoilSurfaceTemperature());

  EXPECT_TRUE(object.setAverageAmplitudeofSurfaceTemperature(14.0));
  ASSERT_TRUE(object.averageAmplitudeofSurfaceTemperature());
  EXPECT_DOUBLE_EQ(14.0, object.averageAmplitudeofSurfaceTemperature().get());
  object.resetAverageAmplitudeofSurfaceTemperature();
  EXPECT_FALSE(object.averageAmplitudeofSurfaceTemperature());

  EXPECT_TRUE(object.setPhaseShiftofMinimumSurfaceTemperature(19.0));
  ASSERT_TRUE(object.phaseShiftofMinimumSurfaceTemperature());
  EXPECT_DOUBLE_EQ(19.0, object.phaseShiftofMinimumSurfaceTemperature().get());
  object.resetPhaseShiftofMinimumSurfaceTemperature();
  EXPECT_FALSE(object.phaseShiftofMinimumSurfaceTemperature());
}
