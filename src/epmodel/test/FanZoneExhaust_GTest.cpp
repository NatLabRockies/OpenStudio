/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/FanZoneExhaust.hpp"

#include <utilities/idd/Fan_ZoneExhaust_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanZoneExhaust_DefaultConstructor) {
  Model model;
  FanZoneExhaust fan(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_ZoneExhaust), fan.iddObject().type());
}

TEST_F(EPModelFixture, FanZoneExhaust_ScalarAccessors_RoundTrip) {
  Model model;
  FanZoneExhaust fan(model);

  EXPECT_TRUE(fan.setFanTotalEfficiency(0.72));
  EXPECT_DOUBLE_EQ(0.72, fan.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.72, fan.fanEfficiency());

  EXPECT_TRUE(fan.setFanEfficiency(0.68));
  EXPECT_DOUBLE_EQ(0.68, fan.fanTotalEfficiency());

  EXPECT_TRUE(fan.setPressureRise(320.0));
  EXPECT_DOUBLE_EQ(320.0, fan.pressureRise());

  EXPECT_TRUE(fan.setMaximumFlowRate(0.55));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(0.55, fan.maximumFlowRate().get());
  fan.resetMaximumFlowRate();
  EXPECT_FALSE(fan.maximumFlowRate());

  EXPECT_TRUE(fan.setEndUseSubcategory("Exhaust"));
  EXPECT_EQ("Exhaust", fan.endUseSubcategory());

  const auto couplingModes = FanZoneExhaust::systemAvailabilityManagerCouplingModeValues();
  ASSERT_FALSE(couplingModes.empty());
  EXPECT_TRUE(fan.setSystemAvailabilityManagerCouplingMode(couplingModes.front()));
  EXPECT_EQ(couplingModes.front(), fan.systemAvailabilityManagerCouplingMode());
}

TEST_F(EPModelFixture, FanZoneExhaust_Topology) {
  Model model;
  FanZoneExhaust fan(model);
  ThermalZone zone(model);

  EXPECT_EQ(openstudio::Fan_ZoneExhaustFields::AirInletNodeName, fan.inletPort());
  EXPECT_EQ(openstudio::Fan_ZoneExhaustFields::AirOutletNodeName, fan.outletPort());

  EXPECT_TRUE(fan.addToThermalZone(zone));
  ASSERT_TRUE(fan.thermalZone());
  EXPECT_EQ(zone, fan.thermalZone().get());
  auto inlet = fan.inletNode();
  auto outlet = fan.outletNode();
  ASSERT_TRUE(inlet);
  ASSERT_TRUE(outlet);

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  const auto exhaustNodes = connections->zoneAirExhaustNodes();
  ASSERT_EQ(1u, exhaustNodes.size());
  EXPECT_EQ(*inlet, exhaustNodes.front());

  fan.removeFromThermalZone();
  EXPECT_FALSE(fan.thermalZone());
  EXPECT_FALSE(fan.inletNode());
  EXPECT_FALSE(fan.outletNode());
  EXPECT_TRUE(connections->zoneAirExhaustNodes().empty());
}
