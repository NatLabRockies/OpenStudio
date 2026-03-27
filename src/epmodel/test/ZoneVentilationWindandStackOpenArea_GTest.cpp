/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneVentilationWindandStackOpenArea.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_DefaultConstructor) {
  Model model;
  ZoneVentilationWindandStackOpenArea ventilation(model);

  EXPECT_EQ(ZoneVentilationWindandStackOpenArea::iddObjectType(), ventilation.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, ventilation.openingArea());
  EXPECT_FALSE(ventilation.openingEffectiveness());
  EXPECT_TRUE(ventilation.isOpeningEffectivenessAutocalculated());
  EXPECT_DOUBLE_EQ(0.0, ventilation.effectiveAngle());
  EXPECT_DOUBLE_EQ(0.0, ventilation.heightDifference());
  EXPECT_FALSE(ventilation.dischargeCoefficientforOpening());
  EXPECT_TRUE(ventilation.isDischargeCoefficientforOpeningAutocalculated());
  EXPECT_DOUBLE_EQ(-100.0, ventilation.minimumIndoorTemperature());
  EXPECT_DOUBLE_EQ(100.0, ventilation.maximumIndoorTemperature());
  EXPECT_DOUBLE_EQ(-100.0, ventilation.deltaTemperature());
  EXPECT_DOUBLE_EQ(-100.0, ventilation.minimumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(100.0, ventilation.maximumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(40.0, ventilation.maximumWindSpeed());
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneVentilationWindandStackOpenArea ventilation(model);

  EXPECT_TRUE(ventilation.setOpeningArea(1.5));
  EXPECT_TRUE(ventilation.setOpeningEffectiveness(0.65));
  EXPECT_FALSE(ventilation.isOpeningEffectivenessAutocalculated());
  EXPECT_TRUE(ventilation.setEffectiveAngle(45.0));
  EXPECT_TRUE(ventilation.setHeightDifference(3.25));
  EXPECT_TRUE(ventilation.setDischargeCoefficientforOpening(0.45));
  EXPECT_FALSE(ventilation.isDischargeCoefficientforOpeningAutocalculated());
  EXPECT_TRUE(ventilation.setMinimumIndoorTemperature(-20.0));
  EXPECT_TRUE(ventilation.setMaximumIndoorTemperature(45.0));
  EXPECT_TRUE(ventilation.setDeltaTemperature(12.0));
  EXPECT_TRUE(ventilation.setMinimumOutdoorTemperature(-15.0));
  EXPECT_TRUE(ventilation.setMaximumOutdoorTemperature(35.0));
  EXPECT_TRUE(ventilation.setMaximumWindSpeed(30.0));

  EXPECT_DOUBLE_EQ(1.5, ventilation.openingArea());
  ASSERT_TRUE(ventilation.openingEffectiveness());
  EXPECT_DOUBLE_EQ(0.65, ventilation.openingEffectiveness().value());
  EXPECT_DOUBLE_EQ(45.0, ventilation.effectiveAngle());
  EXPECT_DOUBLE_EQ(3.25, ventilation.heightDifference());
  ASSERT_TRUE(ventilation.dischargeCoefficientforOpening());
  EXPECT_DOUBLE_EQ(0.45, ventilation.dischargeCoefficientforOpening().value());
  EXPECT_DOUBLE_EQ(-20.0, ventilation.minimumIndoorTemperature());
  EXPECT_DOUBLE_EQ(45.0, ventilation.maximumIndoorTemperature());
  EXPECT_DOUBLE_EQ(12.0, ventilation.deltaTemperature());
  EXPECT_DOUBLE_EQ(-15.0, ventilation.minimumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(35.0, ventilation.maximumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(30.0, ventilation.maximumWindSpeed());

  ventilation.autocalculateOpeningEffectiveness();
  EXPECT_TRUE(ventilation.isOpeningEffectivenessAutocalculated());
  EXPECT_FALSE(ventilation.openingEffectiveness());

  ventilation.autocalculateDischargeCoefficientforOpening();
  EXPECT_TRUE(ventilation.isDischargeCoefficientforOpeningAutocalculated());
  EXPECT_FALSE(ventilation.dischargeCoefficientforOpening());
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneVentilationWindandStackOpenArea ventilation(model);

  EXPECT_EQ(0u, ventilation.inletPort());
  EXPECT_EQ(0u, ventilation.outletPort());
  EXPECT_FALSE(ventilation.thermalZone());
  EXPECT_TRUE(ventilation.addToThermalZone(zone));
  ASSERT_TRUE(ventilation.thermalZone());
  EXPECT_EQ(zone, ventilation.thermalZone().get());
  EXPECT_FALSE(ventilation.inletNode());
  EXPECT_FALSE(ventilation.outletNode());

  ventilation.removeFromThermalZone();
  EXPECT_FALSE(ventilation.thermalZone());
  EXPECT_FALSE(ventilation.inletNode());
  EXPECT_FALSE(ventilation.outletNode());
}
