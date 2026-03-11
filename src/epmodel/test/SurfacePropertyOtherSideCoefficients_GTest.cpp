/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/SurfacePropertyOtherSideCoefficients.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyOtherSideCoefficients_DefaultConstructor) {
  Model model;
  SurfacePropertyOtherSideCoefficients sp(model);
  EXPECT_EQ(SurfacePropertyOtherSideCoefficients::iddObjectType(), sp.iddObject().type());
  EXPECT_FALSE(sp.nameString().empty());
}

TEST_F(EPModelFixture, SurfacePropertyOtherSideCoefficients_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyOtherSideCoefficients sp(model);

  EXPECT_TRUE(sp.setCombinedConvectiveRadiativeFilmCoefficient(1.75));
  ASSERT_TRUE(sp.combinedConvectiveRadiativeFilmCoefficient());
  EXPECT_DOUBLE_EQ(1.75, sp.combinedConvectiveRadiativeFilmCoefficient().get());
  sp.resetCombinedConvectiveRadiativeFilmCoefficient();
  EXPECT_FALSE(sp.combinedConvectiveRadiativeFilmCoefficient());

  EXPECT_TRUE(sp.setConstantTemperature(12.3));
  EXPECT_DOUBLE_EQ(12.3, sp.constantTemperature());
  EXPECT_FALSE(sp.isConstantTemperatureDefaulted());
  sp.resetConstantTemperature();
  EXPECT_TRUE(sp.isConstantTemperatureDefaulted());

  EXPECT_TRUE(sp.setConstantTemperatureCoefficient(0.45));
  EXPECT_DOUBLE_EQ(0.45, sp.constantTemperatureCoefficient());
  EXPECT_FALSE(sp.isConstantTemperatureCoefficientDefaulted());
  sp.resetConstantTemperatureCoefficient();
  EXPECT_TRUE(sp.isConstantTemperatureCoefficientDefaulted());

  EXPECT_TRUE(sp.setExternalDryBulbTemperatureCoefficient(0.85));
  EXPECT_DOUBLE_EQ(0.85, sp.externalDryBulbTemperatureCoefficient());

  EXPECT_TRUE(sp.setGroundTemperatureCoefficient(0.15));
  EXPECT_DOUBLE_EQ(0.15, sp.groundTemperatureCoefficient());

  EXPECT_TRUE(sp.setWindSpeedCoefficient(0.25));
  EXPECT_DOUBLE_EQ(0.25, sp.windSpeedCoefficient());

  EXPECT_TRUE(sp.setZoneAirTemperatureCoefficient(0.35));
  EXPECT_DOUBLE_EQ(0.35, sp.zoneAirTemperatureCoefficient());

  EXPECT_TRUE(sp.setSinusoidalVariationofConstantTemperatureCoefficient(true));
  EXPECT_TRUE(sp.sinusoidalVariationofConstantTemperatureCoefficient());
  EXPECT_FALSE(sp.isSinusoidalVariationofConstantTemperatureCoefficientDefaulted());
  sp.resetSinusoidalVariationofConstantTemperatureCoefficient();
  EXPECT_TRUE(sp.isSinusoidalVariationofConstantTemperatureCoefficientDefaulted());

  EXPECT_TRUE(sp.setPeriodofSinusoidalVariation(3600.0));
  EXPECT_DOUBLE_EQ(3600.0, sp.periodofSinusoidalVariation());
  EXPECT_FALSE(sp.isPeriodofSinusoidalVariationDefaulted());

  EXPECT_TRUE(sp.setPreviousOtherSideTemperatureCoefficient(0.95));
  EXPECT_DOUBLE_EQ(0.95, sp.previousOtherSideTemperatureCoefficient());
  EXPECT_FALSE(sp.isPreviousOtherSideTemperatureCoefficientDefaulted());

  EXPECT_TRUE(sp.setMinimumOtherSideTemperatureLimit(-10.0));
  ASSERT_TRUE(sp.minimumOtherSideTemperatureLimit());
  EXPECT_DOUBLE_EQ(-10.0, sp.minimumOtherSideTemperatureLimit().get());
  sp.resetMinimumOtherSideTemperatureLimit();
  EXPECT_FALSE(sp.minimumOtherSideTemperatureLimit());

  EXPECT_TRUE(sp.setMaximumOtherSideTemperatureLimit(45.0));
  ASSERT_TRUE(sp.maximumOtherSideTemperatureLimit());
  EXPECT_DOUBLE_EQ(45.0, sp.maximumOtherSideTemperatureLimit().get());
  sp.resetMaximumOtherSideTemperatureLimit();
  EXPECT_FALSE(sp.maximumOtherSideTemperatureLimit());
}
