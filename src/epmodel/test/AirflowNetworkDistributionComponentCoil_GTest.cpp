/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentCoil_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentCoil coil(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentCoil::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentCoil_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentCoil coil(model);

  EXPECT_TRUE(coil.setAirPathLength(1.25));
  EXPECT_DOUBLE_EQ(1.25, coil.airPathLength());

  EXPECT_TRUE(coil.setAirPathHydraulicDiameter(0.41));
  EXPECT_DOUBLE_EQ(0.41, coil.airPathHydraulicDiameter());
}
