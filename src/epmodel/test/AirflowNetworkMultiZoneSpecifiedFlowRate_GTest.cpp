/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneSpecifiedFlowRate.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSpecifiedFlowRate_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneSpecifiedFlowRate specifiedFlowRate(model);
  EXPECT_EQ(AirflowNetworkMultiZoneSpecifiedFlowRate::iddObjectType(), specifiedFlowRate.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneSpecifiedFlowRate_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneSpecifiedFlowRate specifiedFlowRate(model);

  EXPECT_TRUE(specifiedFlowRate.setAirFlowValue(5.4));
  EXPECT_DOUBLE_EQ(5.4, specifiedFlowRate.airFlowValue());

  EXPECT_TRUE(specifiedFlowRate.isAirFlowUnitsDefaulted());
  EXPECT_EQ("MassFlow", specifiedFlowRate.airFlowUnits());

  EXPECT_TRUE(specifiedFlowRate.setAirFlowUnits("VolumetricFlow"));
  EXPECT_EQ("VolumetricFlow", specifiedFlowRate.airFlowUnits());
  EXPECT_FALSE(specifiedFlowRate.isAirFlowUnitsDefaulted());

  specifiedFlowRate.resetAirFlowUnits();
  EXPECT_TRUE(specifiedFlowRate.isAirFlowUnitsDefaulted());
  EXPECT_EQ("MassFlow", specifiedFlowRate.airFlowUnits());

  const auto values = AirflowNetworkMultiZoneSpecifiedFlowRate::airFlowUnitsValues();
  EXPECT_EQ(2u, values.size());
  EXPECT_EQ("VolumetricFlow", values[0]);
  EXPECT_EQ("MassFlow", values[1]);
}
