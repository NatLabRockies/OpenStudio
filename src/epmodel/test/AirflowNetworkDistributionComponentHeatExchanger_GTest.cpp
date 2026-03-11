/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentHeatExchanger.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentHeatExchanger_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentHeatExchanger heatExchanger(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentHeatExchanger::iddObjectType(), heatExchanger.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentHeatExchanger_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentHeatExchanger heatExchanger(model);

  EXPECT_TRUE(heatExchanger.setAirPathLength(1.20));
  EXPECT_DOUBLE_EQ(1.20, heatExchanger.airPathLength());
  EXPECT_FALSE(heatExchanger.setAirPathLength(0.0));

  EXPECT_TRUE(heatExchanger.setAirPathHydraulicDiameter(0.35));
  EXPECT_DOUBLE_EQ(0.35, heatExchanger.airPathHydraulicDiameter());
  EXPECT_FALSE(heatExchanger.setAirPathHydraulicDiameter(-0.01));
}
