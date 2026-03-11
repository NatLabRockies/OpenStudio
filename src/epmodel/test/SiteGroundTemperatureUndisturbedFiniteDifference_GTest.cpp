/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureUndisturbedFiniteDifference_DefaultConstructor) {
  Model model;
  SiteGroundTemperatureUndisturbedFiniteDifference object(model);
  EXPECT_EQ(SiteGroundTemperatureUndisturbedFiniteDifference::iddObjectType(), object.iddObject().type());

  EXPECT_DOUBLE_EQ(1.08, object.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(962.0, object.soilDensity());
  EXPECT_DOUBLE_EQ(2576.0, object.soilSpecificHeat());

  EXPECT_TRUE(object.isSoilMoistureContentVolumeFractionDefaulted());
  EXPECT_DOUBLE_EQ(30.0, object.soilMoistureContentVolumeFraction());
  EXPECT_TRUE(object.isSoilMoistureContentVolumeFractionatSaturationDefaulted());
  EXPECT_DOUBLE_EQ(50.0, object.soilMoistureContentVolumeFractionatSaturation());
  EXPECT_TRUE(object.isEvapotranspirationGroundCoverParameterDefaulted());
  EXPECT_DOUBLE_EQ(0.4, object.evapotranspirationGroundCoverParameter());
}

TEST_F(EPModelFixture, SiteGroundTemperatureUndisturbedFiniteDifference_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundTemperatureUndisturbedFiniteDifference object(model);

  EXPECT_TRUE(object.setSoilThermalConductivity(1.25));
  EXPECT_DOUBLE_EQ(1.25, object.soilThermalConductivity());

  EXPECT_TRUE(object.setSoilDensity(1000.0));
  EXPECT_DOUBLE_EQ(1000.0, object.soilDensity());

  EXPECT_TRUE(object.setSoilSpecificHeat(2100.0));
  EXPECT_DOUBLE_EQ(2100.0, object.soilSpecificHeat());

  EXPECT_TRUE(object.setSoilMoistureContentVolumeFraction(22.0));
  EXPECT_DOUBLE_EQ(22.0, object.soilMoistureContentVolumeFraction());
  EXPECT_FALSE(object.isSoilMoistureContentVolumeFractionDefaulted());
  object.resetSoilMoistureContentVolumeFraction();
  EXPECT_TRUE(object.isSoilMoistureContentVolumeFractionDefaulted());
  EXPECT_DOUBLE_EQ(30.0, object.soilMoistureContentVolumeFraction());

  EXPECT_TRUE(object.setSoilMoistureContentVolumeFractionatSaturation(48.0));
  EXPECT_DOUBLE_EQ(48.0, object.soilMoistureContentVolumeFractionatSaturation());
  EXPECT_FALSE(object.isSoilMoistureContentVolumeFractionatSaturationDefaulted());
  object.resetSoilMoistureContentVolumeFractionatSaturation();
  EXPECT_TRUE(object.isSoilMoistureContentVolumeFractionatSaturationDefaulted());
  EXPECT_DOUBLE_EQ(50.0, object.soilMoistureContentVolumeFractionatSaturation());

  EXPECT_TRUE(object.setEvapotranspirationGroundCoverParameter(1.2));
  EXPECT_DOUBLE_EQ(1.2, object.evapotranspirationGroundCoverParameter());
  EXPECT_FALSE(object.isEvapotranspirationGroundCoverParameterDefaulted());
  object.resetEvapotranspirationGroundCoverParameter();
  EXPECT_TRUE(object.isEvapotranspirationGroundCoverParameterDefaulted());
  EXPECT_DOUBLE_EQ(0.4, object.evapotranspirationGroundCoverParameter());
}
