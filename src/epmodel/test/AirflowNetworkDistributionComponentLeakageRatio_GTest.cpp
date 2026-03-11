/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentLeakageRatio.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentLeakageRatio_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentLeakageRatio leakageRatio(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentLeakageRatio::iddObjectType(), leakageRatio.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentLeakageRatio_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentLeakageRatio leakageRatio(model);

  EXPECT_FALSE(leakageRatio.effectiveLeakageRatio());
  EXPECT_TRUE(leakageRatio.setEffectiveLeakageRatio(0.08));
  ASSERT_TRUE(leakageRatio.effectiveLeakageRatio());
  EXPECT_DOUBLE_EQ(0.08, leakageRatio.effectiveLeakageRatio().get());

  leakageRatio.resetEffectiveLeakageRatio();
  EXPECT_FALSE(leakageRatio.effectiveLeakageRatio());

  EXPECT_TRUE(leakageRatio.setMaximumFlowRate(1.2));
  EXPECT_DOUBLE_EQ(1.2, leakageRatio.maximumFlowRate());

  EXPECT_TRUE(leakageRatio.setReferencePressureDifference(250.0));
  EXPECT_DOUBLE_EQ(250.0, leakageRatio.referencePressureDifference());

  EXPECT_TRUE(leakageRatio.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, leakageRatio.airMassFlowExponent());

  EXPECT_TRUE(leakageRatio.setAirMassFlowExponent(0.72));
  EXPECT_DOUBLE_EQ(0.72, leakageRatio.airMassFlowExponent());
  EXPECT_FALSE(leakageRatio.isAirMassFlowExponentDefaulted());

  leakageRatio.resetAirMassFlowExponent();
  EXPECT_TRUE(leakageRatio.isAirMassFlowExponentDefaulted());
  EXPECT_DOUBLE_EQ(0.65, leakageRatio.airMassFlowExponent());
}
