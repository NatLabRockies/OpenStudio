/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentOutdoorAirFlow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentOutdoorAirFlow_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentOutdoorAirFlow outdoorAirFlow(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentOutdoorAirFlow::iddObjectType(), outdoorAirFlow.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentOutdoorAirFlow_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentOutdoorAirFlow outdoorAirFlow(model);

  EXPECT_TRUE(outdoorAirFlow.setAirMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions(0.0014));
  EXPECT_DOUBLE_EQ(0.0014, outdoorAirFlow.airMassFlowCoefficientWhenNoOutdoorAirFlowatReferenceConditions());

  EXPECT_TRUE(outdoorAirFlow.isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.65, outdoorAirFlow.airMassFlowExponentWhenNoOutdoorAirFlow());

  EXPECT_TRUE(outdoorAirFlow.setAirMassFlowExponentWhenNoOutdoorAirFlow(0.71));
  EXPECT_DOUBLE_EQ(0.71, outdoorAirFlow.airMassFlowExponentWhenNoOutdoorAirFlow());
  EXPECT_FALSE(outdoorAirFlow.isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted());

  outdoorAirFlow.resetAirMassFlowExponentWhenNoOutdoorAirFlow();
  EXPECT_TRUE(outdoorAirFlow.isAirMassFlowExponentWhenNoOutdoorAirFlowDefaulted());
  EXPECT_DOUBLE_EQ(0.65, outdoorAirFlow.airMassFlowExponentWhenNoOutdoorAirFlow());
}
