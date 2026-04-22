/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  EXPECT_EQ(AirTerminalDualDuctVAVOutdoorAir::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());

  EXPECT_TRUE(terminal.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("CurrentOccupancy", terminal.perPersonVentilationRateMode());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  EXPECT_TRUE(terminal.setMaximumTerminalAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumTerminalAirFlowRateAutosized());

  terminal.autosizeMaximumTerminalAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumTerminalAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());

  EXPECT_FALSE(terminal.setPerPersonVentilationRateMode("InvalidChoice"));

  const auto values = AirTerminalDualDuctVAVOutdoorAir::perPersonVentilationRateModeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "CurrentOccupancy"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "DesignOccupancy"));
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddToDualDuctAirLoop) {
  {
    Model model;
    AirLoopHVAC airLoop(model, true);
    AirTerminalDualDuctVAVOutdoorAir terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    EXPECT_EQ(2u, airLoop.demandInletNodes().size());
    EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());

    ASSERT_TRUE(terminal.outdoorAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(0u));
    EXPECT_EQ(terminal.outdoorAirInletNode()->handle(), terminal.inletModelObject(0u)->handle());

    ASSERT_TRUE(terminal.recirculatedAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(1u));
    EXPECT_EQ(terminal.recirculatedAirInletNode()->handle(), terminal.inletModelObject(1u)->handle());
  }

  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.outdoorAirInletNode());
  ASSERT_TRUE(terminal.recirculatedAirInletNode());
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  const auto outletHandle = outletNode->handle();
  ASSERT_TRUE(outletNode->setName("Renamed Dual Duct VAV Outdoor Air Outlet Node"));

  outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(outletHandle, outletNode->handle());
  EXPECT_EQ("Renamed Dual Duct VAV Outdoor Air Outlet Node", outletNode->nameString());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  EXPECT_EQ(2u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
}
