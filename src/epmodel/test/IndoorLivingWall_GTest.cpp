/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/IndoorLivingWall.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, IndoorLivingWall_DefaultConstructor) {
  Model model;
  IndoorLivingWall indoorLivingWall(model);
  EXPECT_EQ(IndoorLivingWall::iddObjectType(), indoorLivingWall.iddObject().type());
}

TEST_F(EPModelFixture, IndoorLivingWall_ScalarAccessors_RoundTrip) {
  Model model;
  IndoorLivingWall indoorLivingWall(model);

  EXPECT_TRUE(indoorLivingWall.isEvapotranspirationCalculationMethodDefaulted());
  EXPECT_EQ("Penman-Monteith", indoorLivingWall.evapotranspirationCalculationMethod());
  EXPECT_TRUE(indoorLivingWall.setEvapotranspirationCalculationMethod("Stanghellini"));
  EXPECT_EQ("Stanghellini", indoorLivingWall.evapotranspirationCalculationMethod());
  EXPECT_FALSE(indoorLivingWall.isEvapotranspirationCalculationMethodDefaulted());
  indoorLivingWall.resetEvapotranspirationCalculationMethod();
  EXPECT_TRUE(indoorLivingWall.isEvapotranspirationCalculationMethodDefaulted());

  EXPECT_TRUE(indoorLivingWall.setLightingMethod("Daylight"));
  ASSERT_TRUE(indoorLivingWall.lightingMethod());
  EXPECT_EQ("Daylight", indoorLivingWall.lightingMethod().get());
  indoorLivingWall.resetLightingMethod();
  const auto lightingMethodAfterReset = indoorLivingWall.lightingMethod();
  EXPECT_TRUE(!lightingMethodAfterReset || lightingMethodAfterReset.get() != "Daylight");

  EXPECT_TRUE(indoorLivingWall.setDaylightingControlName("DL Ctrl"));
  ASSERT_TRUE(indoorLivingWall.daylightingControlName());
  EXPECT_EQ("DL Ctrl", indoorLivingWall.daylightingControlName().get());
  indoorLivingWall.resetDaylightingControlName();
  const auto daylightingControlNameAfterReset = indoorLivingWall.daylightingControlName();
  EXPECT_TRUE(!daylightingControlNameAfterReset || daylightingControlNameAfterReset.get().empty());

  EXPECT_FALSE(indoorLivingWall.totalLeafArea());
  EXPECT_TRUE(indoorLivingWall.setTotalLeafArea(6.25));
  ASSERT_TRUE(indoorLivingWall.totalLeafArea());
  EXPECT_DOUBLE_EQ(6.25, indoorLivingWall.totalLeafArea().get());
  indoorLivingWall.resetTotalLeafArea();
  EXPECT_FALSE(indoorLivingWall.totalLeafArea());

  EXPECT_FALSE(indoorLivingWall.lEDNominalIntensity());
  EXPECT_TRUE(indoorLivingWall.setLEDNominalIntensity(180.0));
  ASSERT_TRUE(indoorLivingWall.lEDNominalIntensity());
  EXPECT_DOUBLE_EQ(180.0, indoorLivingWall.lEDNominalIntensity().get());
  indoorLivingWall.resetLEDNominalIntensity();
  EXPECT_FALSE(indoorLivingWall.lEDNominalIntensity());

  EXPECT_FALSE(indoorLivingWall.lEDNominalPower());
  EXPECT_TRUE(indoorLivingWall.setLEDNominalPower(75.0));
  ASSERT_TRUE(indoorLivingWall.lEDNominalPower());
  EXPECT_DOUBLE_EQ(75.0, indoorLivingWall.lEDNominalPower().get());
  indoorLivingWall.resetLEDNominalPower();
  EXPECT_FALSE(indoorLivingWall.lEDNominalPower());

  EXPECT_TRUE(indoorLivingWall.isRadiantFractionofLEDLightsDefaulted());
  EXPECT_DOUBLE_EQ(0.6, indoorLivingWall.radiantFractionofLEDLights());
  EXPECT_TRUE(indoorLivingWall.setRadiantFractionofLEDLights(0.45));
  EXPECT_DOUBLE_EQ(0.45, indoorLivingWall.radiantFractionofLEDLights());
  EXPECT_FALSE(indoorLivingWall.isRadiantFractionofLEDLightsDefaulted());
  indoorLivingWall.resetRadiantFractionofLEDLights();
  EXPECT_TRUE(indoorLivingWall.isRadiantFractionofLEDLightsDefaulted());
}
