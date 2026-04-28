/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/AirflowNetworkDistributionComponentLeak.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentLeak_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentLeak leak(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentLeak::iddObjectType(), leak.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentLeak_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentLeak leak(model);

  EXPECT_TRUE(leak.setAirMassFlowCoefficient(0.0014));
  EXPECT_DOUBLE_EQ(0.0014, leak.airMassFlowCoefficient());

  EXPECT_TRUE(leak.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, leak.airMassFlowExponent());

  EXPECT_TRUE(leak.setAirMassFlowExponent(0.71));
  EXPECT_DOUBLE_EQ(0.71, leak.airMassFlowExponent());
  EXPECT_FALSE(leak.isAirMassFlowExponentDefaulted());

  leak.resetAirMassFlowExponent();
  EXPECT_TRUE(leak.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, leak.airMassFlowExponent());
}
