/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include <utilities/idd/AirTerminal_SingleDuct_SeriesPIU_Reheat_FieldEnums.hxx>
#include "../StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.42));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.42, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMaximumPrimaryAirFlowRate(1.05));
  ASSERT_TRUE(terminal.maximumPrimaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.05, terminal.maximumPrimaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumPrimaryAirFlowRateAutosized());
  terminal.autosizeMaximumPrimaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumPrimaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumPrimaryAirFlowFraction(0.39));
  ASSERT_TRUE(terminal.minimumPrimaryAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.39, terminal.minimumPrimaryAirFlowFraction().get());
  EXPECT_FALSE(terminal.isMinimumPrimaryAirFlowFractionAutosized());
  terminal.autosizeMinimumPrimaryAirFlowFraction();
  EXPECT_TRUE(terminal.isMinimumPrimaryAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.004));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.004, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.resetMaximumHotWaterorSteamFlowRate();
  EXPECT_FALSE(terminal.maximumHotWaterorSteamFlowRate());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.0011));
  EXPECT_DOUBLE_EQ(0.0011, terminal.minimumHotWaterorSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.006));
  EXPECT_DOUBLE_EQ(0.006, terminal.convergenceTolerance());

  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  EXPECT_TRUE(terminal.setMinimumFanTurnDownRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, terminal.minimumFanTurnDownRatio());

  EXPECT_EQ("Staged", terminal.heatingControlType());
  EXPECT_TRUE(terminal.setHeatingControlType("Modulated"));
  EXPECT_EQ("Modulated", terminal.heatingControlType());

  EXPECT_TRUE(terminal.setDesignHeatingDischargeAirTemperature(34.0));
  EXPECT_DOUBLE_EQ(34.0, terminal.designHeatingDischargeAirTemperature());

  EXPECT_TRUE(terminal.setHighLimitHeatingDischargeAirTemperature(40.0));
  EXPECT_DOUBLE_EQ(40.0, terminal.highLimitHeatingDischargeAirTemperature());

  const auto fanControlTypeValues = AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues();
  EXPECT_FALSE(fanControlTypeValues.empty());
  EXPECT_TRUE(std::find(fanControlTypeValues.begin(), fanControlTypeValues.end(), "ConstantSpeed") != fanControlTypeValues.end());

  const auto heatingControlTypeValues = AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues();
  EXPECT_FALSE(heatingControlTypeValues.empty());
  EXPECT_TRUE(std::find(heatingControlTypeValues.begin(), heatingControlTypeValues.end(), "Staged") != heatingControlTypeValues.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  EXPECT_FALSE(terminal.availabilitySchedule());

  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());

  FanConstantVolume fan(model);
  CoilHeatingElectric reheatCoil(model);
  Node secondaryNode(model);
  EXPECT_TRUE(terminal.setFan(fan));
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, secondaryNode.handle()));
  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondaryNode.handle(), terminal.secondaryAirInletNode()->handle());

  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());
}
