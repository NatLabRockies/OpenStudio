/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_AirTerminalSingleDuctConstantVolumeNoReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeNoReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AvailabilitySchedule_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.handle(), terminal.availabilitySchedule().handle());
}
