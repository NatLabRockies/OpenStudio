/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirNodeAirflowNetworkInternalGains.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirNodeAirflowNetworkInternalGains_DefaultConstructor) {
  Model model;
  RoomAirNodeAirflowNetworkInternalGains object(model);
  EXPECT_EQ(RoomAirNodeAirflowNetworkInternalGains::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirNodeAirflowNetworkInternalGains_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirNodeAirflowNetworkInternalGains object(model);

  EXPECT_TRUE(object.setName("InternalGainsNode"));
  EXPECT_EQ("InternalGainsNode", object.nameString());
}
