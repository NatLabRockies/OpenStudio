/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirNodeAirflowNetwork.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirNodeAirflowNetwork_DefaultConstructor) {
  Model model;
  RoomAirNodeAirflowNetwork object(model);
  EXPECT_EQ(RoomAirNodeAirflowNetwork::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirNodeAirflowNetwork_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirNodeAirflowNetwork object(model);

  EXPECT_TRUE(object.isFractionOfZoneAirVolumeDefaulted());
  EXPECT_TRUE(object.setFractionOfZoneAirVolume(0.35));
  ASSERT_TRUE(object.fractionOfZoneAirVolume());
  EXPECT_DOUBLE_EQ(0.35, object.fractionOfZoneAirVolume().get());
  EXPECT_FALSE(object.setFractionOfZoneAirVolume(-0.1));
  EXPECT_FALSE(object.setFractionOfZoneAirVolume(1.1));
  object.resetFractionOfZoneAirVolume();
  EXPECT_TRUE(object.isFractionOfZoneAirVolumeDefaulted());
}
