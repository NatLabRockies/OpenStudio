/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_NoReheat_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirTerminalSingleDuctConstantVolumeNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.maximumAirFlowRate());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_ScheduleConstructor_PreservesProvidedAvailabilitySchedule) {
  Model model;
  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));

  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model, compactSchedule);

  EXPECT_EQ(compactSchedule, terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.maximumAirFlowRate());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AutosizedMaximumAirFlowRate_IsDocumentedTypedStub) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_FALSE(terminal.maximumAirFlowRate());
  EXPECT_FALSE(terminal.autosizedMaximumAirFlowRate());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AvailabilitySchedule_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.handle(), terminal.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ASSERT_TRUE(
    terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName));

  const auto repairedSchedule = terminal.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), repairedSchedule);
  const auto storedSchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_NoReheatFields::AvailabilityScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *storedSchedule);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_RejectsNonDemandNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_ResolvesAirLoopHVACAfterZoneInsertion) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto terminalInletObject = terminal.inletModelObject();
  ASSERT_TRUE(terminalInletObject);
  auto terminalInletNode = terminalInletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalInletNode);
  EXPECT_NE(zoneAirNode, *terminalInletNode);

  auto terminalOutletObject = terminal.outletModelObject();
  ASSERT_TRUE(terminalOutletObject);
  auto terminalOutletNode = terminalOutletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalOutletNode);
  EXPECT_EQ(zoneAirNode, *terminalOutletNode);
}
