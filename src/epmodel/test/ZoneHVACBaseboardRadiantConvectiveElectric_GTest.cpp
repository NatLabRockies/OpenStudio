/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveElectric.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveElectric_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveElectric baseboard(model);
  (void)baseboard;
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveElectric baseboard(model);

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  ASSERT_EQ("CapacityPerFloorArea", baseboard.heatingDesignCapacityMethod());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(2000.0));
  ASSERT_TRUE(baseboard.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(2000.0, baseboard.heatingDesignCapacity().get());
  baseboard.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityPerFloorArea(0.6));
  EXPECT_DOUBLE_EQ(0.6, baseboard.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(baseboard.setFractionofAutosizedHeatingDesignCapacity(0.8));
  EXPECT_DOUBLE_EQ(0.8, baseboard.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(baseboard.setEfficiency(0.88));
  EXPECT_DOUBLE_EQ(0.88, baseboard.efficiency());

  EXPECT_TRUE(baseboard.setFractionRadiant(0.75));
  EXPECT_DOUBLE_EQ(0.75, baseboard.fractionRadiant());

  EXPECT_TRUE(baseboard.setFractionofRadiantEnergyIncidentonPeople(0.35));
  EXPECT_DOUBLE_EQ(0.35, baseboard.fractionofRadiantEnergyIncidentonPeople());

  auto values = ZoneHVACBaseboardRadiantConvectiveElectric::heatingDesignCapacityMethodValues();
  EXPECT_FALSE(values.empty());
  EXPECT_NE(values.cend(), std::find(values.cbegin(), values.cend(), "HeatingDesignCapacity"));
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveElectric_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardRadiantConvectiveElectric baseboard(model);

  EXPECT_EQ(0u, baseboard.inletPort());
  EXPECT_EQ(0u, baseboard.outletPort());
  EXPECT_FALSE(baseboard.inletNode());
  EXPECT_FALSE(baseboard.outletNode());
  EXPECT_FALSE(baseboard.thermalZone());

  EXPECT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_TRUE(baseboard.thermalZone());
  EXPECT_EQ(zone, *baseboard.thermalZone());

  baseboard.removeFromThermalZone();
  EXPECT_FALSE(baseboard.thermalZone());
  EXPECT_FALSE(baseboard.inletNode());
  EXPECT_FALSE(baseboard.outletNode());
}
