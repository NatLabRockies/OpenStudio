/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardConvectiveElectric baseboard(model);
  (void)baseboard;
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardConvectiveElectric baseboard(model);

  EXPECT_TRUE(baseboard.setNominalCapacity(5000.0));
  ASSERT_TRUE(baseboard.nominalCapacity());
  EXPECT_DOUBLE_EQ(5000.0, baseboard.nominalCapacity().get());
  baseboard.autosizeNominalCapacity();
  EXPECT_TRUE(baseboard.isNominalCapacityAutosized());

  EXPECT_TRUE(baseboard.setEfficiency(0.85));
  ASSERT_TRUE(baseboard.efficiency());
  EXPECT_DOUBLE_EQ(0.85, baseboard.efficiency().get());
  baseboard.resetEfficiency();
  EXPECT_TRUE(baseboard.isEfficiencyDefaulted());
  ASSERT_TRUE(baseboard.efficiency());
  EXPECT_DOUBLE_EQ(1.0, baseboard.efficiency().get());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveElectric baseboard(model);

  EXPECT_FALSE(baseboard.thermalZone());
  EXPECT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_TRUE(baseboard.thermalZone());
  EXPECT_EQ(zone, *baseboard.thermalZone());

  baseboard.removeFromThermalZone();
  EXPECT_FALSE(baseboard.thermalZone());
}
