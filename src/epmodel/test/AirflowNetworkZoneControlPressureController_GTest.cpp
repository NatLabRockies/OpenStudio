/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/AirflowNetworkZoneControlPressureController.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkZoneControlPressureController_DefaultConstructor) {
  Model model;
  AirflowNetworkZoneControlPressureController pressureController(model);
  EXPECT_EQ(AirflowNetworkZoneControlPressureController::iddObjectType(), pressureController.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkZoneControlPressureController_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkZoneControlPressureController pressureController(model);

  const auto values = AirflowNetworkZoneControlPressureController::controlObjectTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(pressureController.setControlObjectType("AirflowNetwork:MultiZone:Component:ZoneExhaustFan"));
  EXPECT_EQ("AirflowNetwork:MultiZone:Component:ZoneExhaustFan", pressureController.controlObjectType());

  EXPECT_TRUE(pressureController.setControlObjectType("AirflowNetwork:Distribution:Component:ReliefAirFlow"));
  EXPECT_EQ("AirflowNetwork:Distribution:Component:ReliefAirFlow", pressureController.controlObjectType());

  EXPECT_FALSE(pressureController.setControlObjectType("InvalidControlObjectType"));
  EXPECT_EQ("AirflowNetwork:Distribution:Component:ReliefAirFlow", pressureController.controlObjectType());
}
