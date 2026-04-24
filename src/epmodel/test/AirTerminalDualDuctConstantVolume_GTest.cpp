/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirTerminalDualDuctConstantVolume.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../Schedule/Schedule.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/AirTerminal_DualDuct_ConstantVolume_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctConstantVolume terminal(model);
  EXPECT_EQ(AirTerminalDualDuctConstantVolume::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  auto availabilitySchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *availabilitySchedule);
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctConstantVolume terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_AddToDualDuctAirLoop) {
  {
    Model model;
    AirLoopHVAC airLoop(model, true);
    AirTerminalDualDuctConstantVolume terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    EXPECT_EQ(2u, airLoop.demandInletNodes().size());
    EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());

    ASSERT_TRUE(terminal.hotAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(0u));
    EXPECT_EQ(terminal.hotAirInletNode()->handle(), terminal.inletModelObject(0u)->handle());

    ASSERT_TRUE(terminal.coldAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(1u));
    EXPECT_EQ(terminal.coldAirInletNode()->handle(), terminal.inletModelObject(1u)->handle());
  }

  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());

  terminal.remove();
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  ASSERT_TRUE(zone.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), zone.airLoopHVAC()->handle());
  EXPECT_FALSE(airLoop.addBranchForZone(zone));
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctConstantVolume terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal2));
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctConstantVolume terminal3(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal3));

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  EXPECT_EQ(2u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_AddBranchForZone_ReusesExistingTerminalOnlyBranch) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto inletNodes = connections->zoneAirInletNodes();
  const auto returnNodes = connections->zoneReturnAirNodes();
  ASSERT_EQ(1u, inletNodes.size());
  ASSERT_EQ(1u, returnNodes.size());
  EXPECT_EQ(inletNodes.front().handle(), returnNodes.front().handle());
  EXPECT_EQ(terminalOutletHandle, inletNodes.front().handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_AddToNode_RejectsInvalidContextsAndAlreadyConnectedTerminal) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  Model otherModel;
  Node foreignNode(otherModel);

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletModelObject(0u));
  EXPECT_FALSE(terminal.inletModelObject(1u));
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  const auto originalHotInlet = terminal.hotAirInletNode();
  const auto originalColdInlet = terminal.coldAirInletNode();
  ASSERT_TRUE(originalHotInlet);
  ASSERT_TRUE(originalColdInlet);

  EXPECT_FALSE(terminal.addToNode(zone.zoneAirNode()));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  EXPECT_EQ(originalHotInlet->handle(), terminal.hotAirInletNode()->handle());
  EXPECT_EQ(originalColdInlet->handle(), terminal.coldAirInletNode()->handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_RemoveDirectDualDuctBranchClearsConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());

  terminal.remove();
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.hotAirInletNode());
  EXPECT_FALSE(terminal.coldAirInletNode());
  EXPECT_FALSE(terminal.inletModelObject(0u));
  EXPECT_FALSE(terminal.inletModelObject(1u));
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_RemoveClearsConnectivityAndSupportsReuse) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipmentList.equipment().front());
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());

  terminal.remove();
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.hotAirInletNode());
  EXPECT_FALSE(terminal.coldAirInletNode());
  EXPECT_FALSE(terminal.inletModelObject(0u));
  EXPECT_FALSE(terminal.inletModelObject(1u));
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_RemoveClearsStaleZoneEquipmentWithoutLoop) {
  Model model;
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  ASSERT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_FALSE(terminal.airLoopHVAC());

  terminal.remove();
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.hotAirInletNode());
  EXPECT_FALSE(terminal.coldAirInletNode());
}
