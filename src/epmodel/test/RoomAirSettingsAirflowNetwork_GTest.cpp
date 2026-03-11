/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirSettingsAirflowNetwork.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirSettingsAirflowNetwork_DefaultConstructor) {
  Model model;
  RoomAirSettingsAirflowNetwork roomAirSettings(model);
  EXPECT_EQ(RoomAirSettingsAirflowNetwork::iddObjectType(), roomAirSettings.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirSettingsAirflowNetwork_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirSettingsAirflowNetwork roomAirSettings(model);

  EXPECT_TRUE(roomAirSettings.setName("RoomAir AFN Settings"));
  EXPECT_EQ("RoomAir AFN Settings", roomAirSettings.nameString());
}
