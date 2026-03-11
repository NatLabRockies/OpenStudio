/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ZoneHVACEquipmentConnections.hpp"
#include "../ZoneHVACEquipmentConnections_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_DefaultConstructor) {
  Model model;
  ZoneHVACEquipmentConnections equipmentConnections(model);
  EXPECT_EQ(ZoneHVACEquipmentConnections::iddObjectType(), equipmentConnections.iddObject().type());
}

TEST_F(EPModelFixture, API_ZoneHVACEquipmentConnections_SettersAndGetters) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACEquipmentConnections equipmentConnections(model);
  auto zoneNode = model.getOrCreateTransientByName<Node>("Zone Equipment Node");

  ASSERT_TRUE(equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setThermalZone(zone));
  ASSERT_TRUE(equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneAirInletNode(zoneNode));
  ASSERT_TRUE(equipmentConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>()->setZoneReturnAirNode(zoneNode));

  auto linkedZone = equipmentConnections.thermalZone();
  ASSERT_TRUE(linkedZone);
  EXPECT_EQ(zone, linkedZone.get());

  auto zoneAirInletNode = equipmentConnections.zoneAirInletNode();
  ASSERT_TRUE(zoneAirInletNode);
  EXPECT_EQ(zoneNode, zoneAirInletNode.get());
  const auto zoneAirInletNodes = equipmentConnections.zoneAirInletNodes();
  ASSERT_EQ(1u, zoneAirInletNodes.size());
  EXPECT_EQ(zoneNode, zoneAirInletNodes.front());

  auto zoneReturnAirNode = equipmentConnections.zoneReturnAirNode();
  ASSERT_TRUE(zoneReturnAirNode);
  EXPECT_EQ(zoneNode, zoneReturnAirNode.get());
  const auto zoneReturnAirNodes = equipmentConnections.zoneReturnAirNodes();
  ASSERT_EQ(1u, zoneReturnAirNodes.size());
  EXPECT_EQ(zoneNode, zoneReturnAirNodes.front());
}
