/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneHVACForcedAirUserDefined.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACForcedAirUserDefined_DefaultConstructor) {
  Model model;
  ZoneHVACForcedAirUserDefined forcedAir(model);
  EXPECT_EQ(ZoneHVACForcedAirUserDefined::iddObjectType(), forcedAir.iddObject().type());
}

TEST_F(EPModelFixture, ZoneHVACForcedAirUserDefined_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACForcedAirUserDefined forcedAir(model);

  EXPECT_TRUE(forcedAir.setNumberofPlantLoopConnections(2));
  EXPECT_EQ(2, forcedAir.numberofPlantLoopConnections());
}
