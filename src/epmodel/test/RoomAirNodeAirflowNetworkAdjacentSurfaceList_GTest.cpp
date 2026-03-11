/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirNodeAirflowNetworkAdjacentSurfaceList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirNodeAirflowNetworkAdjacentSurfaceList_DefaultConstructor) {
  Model model;
  RoomAirNodeAirflowNetworkAdjacentSurfaceList object(model);
  EXPECT_EQ(RoomAirNodeAirflowNetworkAdjacentSurfaceList::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirNodeAirflowNetworkAdjacentSurfaceList_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirNodeAirflowNetworkAdjacentSurfaceList object(model);

  EXPECT_TRUE(object.setName("Surface List"));
  EXPECT_EQ("Surface List", object.nameString());
}
