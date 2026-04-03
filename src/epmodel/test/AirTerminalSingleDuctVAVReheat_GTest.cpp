/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowMethod());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowInputMethod("Scheduled"));
  EXPECT_EQ("Scheduled", terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowMethod("FixedFlowRate"));
  EXPECT_EQ("FixedFlowRate", terminal.zoneMinimumAirFlowInputMethod());

  EXPECT_TRUE(terminal.setConstantMinimumAirFlowFraction(0.42));
  ASSERT_TRUE(terminal.constantMinimumAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.42, terminal.constantMinimumAirFlowFraction().get());
  terminal.autosizeConstantMinimumAirFlowFraction();
  EXPECT_TRUE(terminal.isConstantMinimumAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setFixedMinimumAirFlowRate(0.5));
  ASSERT_TRUE(terminal.fixedMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, terminal.fixedMinimumAirFlowRate().get());
  terminal.autosizeFixedMinimumAirFlowRate();
  EXPECT_TRUE(terminal.isFixedMinimumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.isMaximumHotWaterOrSteamFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHotWaterOrSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterOrSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterOrSteamFlowRate().get());
  terminal.autosizeMaximumHotWaterOrSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterOrSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterOrStreamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterOrSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.convergenceTolerance());

  EXPECT_EQ("Normal", terminal.damperHeatingAction());
  EXPECT_TRUE(terminal.setDamperHeatingAction("Reverse"));
  EXPECT_EQ("Reverse", terminal.damperHeatingAction());

  EXPECT_TRUE(terminal.isMaximumFlowPerZoneFloorAreaDuringReheatAutosized());
  EXPECT_TRUE(terminal.setMaximumFlowPerZoneFloorAreaDuringReheat(0.25));
  ASSERT_TRUE(terminal.maximumFlowPerZoneFloorAreaDuringReheat());
  EXPECT_DOUBLE_EQ(0.25, terminal.maximumFlowPerZoneFloorAreaDuringReheat().get());
  terminal.autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
  EXPECT_TRUE(terminal.isMaximumFlowPerZoneFloorAreaDuringReheatAutosized());
  terminal.resetMaximumFlowPerZoneFloorAreaDuringReheat();
  EXPECT_FALSE(terminal.maximumFlowPerZoneFloorAreaDuringReheat());

  EXPECT_TRUE(terminal.isMaximumFlowFractionDuringReheatAutosized());
  EXPECT_TRUE(terminal.setMaximumFlowFractionDuringReheat(0.35));
  ASSERT_TRUE(terminal.maximumFlowFractionDuringReheat());
  EXPECT_DOUBLE_EQ(0.35, terminal.maximumFlowFractionDuringReheat().get());
  terminal.autosizeMaximumFlowFractionDuringReheat();
  EXPECT_TRUE(terminal.isMaximumFlowFractionDuringReheatAutosized());
  terminal.resetMaximumFlowFractionDuringReheat();
  EXPECT_FALSE(terminal.maximumFlowFractionDuringReheat());

  EXPECT_TRUE(terminal.setMaximumReheatAirTemperature(41.2));
  EXPECT_DOUBLE_EQ(41.2, terminal.maximumReheatAirTemperature());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact minimumFraction(model);
  ScheduleCompact turndown(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(minimumFraction.setToConstantValue(0.2));
  ASSERT_TRUE(turndown.setToConstantValue(0.4));

  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_TRUE(terminal.setMinimumAirFlowFractionSchedule(minimumFraction));
  EXPECT_TRUE(terminal.setMinimumAirFlowTurndownSchedule(turndown));
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  ASSERT_TRUE(terminal.minimumAirFlowFractionSchedule());
  EXPECT_EQ(minimumFraction.handle(), terminal.minimumAirFlowFractionSchedule()->handle());
  ASSERT_TRUE(terminal.minimumAirFlowTurndownSchedule());
  EXPECT_EQ(turndown.handle(), terminal.minimumAirFlowTurndownSchedule()->handle());

  CoilHeatingElectric reheatCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());

  terminal.resetMinimumAirFlowFractionSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowFractionSchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}
