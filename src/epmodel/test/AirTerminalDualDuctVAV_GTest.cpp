/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirTerminalDualDuctVAV.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctVAV terminal(model);
  EXPECT_EQ(AirTerminalDualDuctVAV::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctVAV terminal(model);

  EXPECT_TRUE(terminal.setMaximumDamperAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumDamperAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumDamperAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumDamperAirFlowRateAutosized());

  terminal.autosizeMaximumDamperAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumDamperAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddToDualDuctAirLoop) {
  {
    Model model;
    AirLoopHVAC airLoop(model, true);
    AirTerminalDualDuctVAV terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    EXPECT_EQ(2u, airLoop.demandInletNodes().size());
    EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());

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
  AirTerminalDualDuctVAV terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());

  terminal.remove();
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  ASSERT_TRUE(zone.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), zone.airLoopHVAC()->handle());
  EXPECT_FALSE(airLoop.addBranchForZone(zone));
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctVAV terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal2));
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctVAV terminal3(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal3));

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  EXPECT_EQ(2u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
}
