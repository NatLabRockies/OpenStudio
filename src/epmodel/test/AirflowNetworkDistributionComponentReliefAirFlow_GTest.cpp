/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentReliefAirFlow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentReliefAirFlow_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentReliefAirFlow reliefAirFlow(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentReliefAirFlow::iddObjectType(), reliefAirFlow.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentReliefAirFlow_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentReliefAirFlow reliefAirFlow(model);

  EXPECT_TRUE(reliefAirFlow.setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(0.0014));
  EXPECT_DOUBLE_EQ(0.0014, reliefAirFlow.airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions());

  EXPECT_TRUE(reliefAirFlow.isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.65, reliefAirFlow.airMassFlowExponentWhenNoOutdoorAirFlow());

  EXPECT_TRUE(reliefAirFlow.setAirMassFlowExponentWhenNoOutdoorAirFlow(0.71));
  EXPECT_DOUBLE_EQ(0.71, reliefAirFlow.airMassFlowExponentWhenNoOutdoorAirFlow());
  EXPECT_FALSE(reliefAirFlow.isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted());

  reliefAirFlow.resetAirMassFlowExponentWhenNoOutdoorAirFlow();
  EXPECT_TRUE(reliefAirFlow.isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.65, reliefAirFlow.airMassFlowExponentWhenNoOutdoorAirFlow());
}
