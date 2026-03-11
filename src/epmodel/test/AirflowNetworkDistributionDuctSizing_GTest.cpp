/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionDuctSizing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionDuctSizing_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionDuctSizing ductSizing(model);
  EXPECT_EQ(AirflowNetworkDistributionDuctSizing::iddObjectType(), ductSizing.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionDuctSizing_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionDuctSizing ductSizing(model);

  const auto methodValues = AirflowNetworkDistributionDuctSizing::ductSizingMethodValues();
  EXPECT_FALSE(methodValues.empty());
  EXPECT_TRUE(ductSizing.isDuctSizingMethodDefaulted());
  EXPECT_EQ("MaximumVelocity", ductSizing.ductSizingMethod());

  EXPECT_TRUE(ductSizing.setDuctSizingMethod("PressureLossWithMaximumVelocity"));
  EXPECT_EQ("PressureLossWithMaximumVelocity", ductSizing.ductSizingMethod());
  EXPECT_FALSE(ductSizing.isDuctSizingMethodDefaulted());
  ductSizing.resetDuctSizingMethod();
  EXPECT_TRUE(ductSizing.isDuctSizingMethodDefaulted());
  EXPECT_EQ("MaximumVelocity", ductSizing.ductSizingMethod());

  EXPECT_TRUE(ductSizing.isDuctSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, ductSizing.ductSizingFactor());
  EXPECT_TRUE(ductSizing.setDuctSizingFactor(1.3));
  EXPECT_DOUBLE_EQ(1.3, ductSizing.ductSizingFactor());
  EXPECT_FALSE(ductSizing.isDuctSizingFactorDefaulted());
  ductSizing.resetDuctSizingFactor();
  EXPECT_TRUE(ductSizing.isDuctSizingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, ductSizing.ductSizingFactor());

  EXPECT_TRUE(ductSizing.isMaximumAirflowVelocityDefaulted());
  EXPECT_DOUBLE_EQ(5.0, ductSizing.maximumAirflowVelocity());
  EXPECT_TRUE(ductSizing.setMaximumAirflowVelocity(7.5));
  EXPECT_DOUBLE_EQ(7.5, ductSizing.maximumAirflowVelocity());
  EXPECT_FALSE(ductSizing.isMaximumAirflowVelocityDefaulted());
  ductSizing.resetMaximumAirflowVelocity();
  EXPECT_TRUE(ductSizing.isMaximumAirflowVelocityDefaulted());
  EXPECT_DOUBLE_EQ(5.0, ductSizing.maximumAirflowVelocity());

  EXPECT_FALSE(ductSizing.totalPressureLossAcrossSupplyTrunk());
  EXPECT_TRUE(ductSizing.setTotalPressureLossAcrossSupplyTrunk(210.0));
  ASSERT_TRUE(ductSizing.totalPressureLossAcrossSupplyTrunk());
  EXPECT_DOUBLE_EQ(210.0, *ductSizing.totalPressureLossAcrossSupplyTrunk());
  ductSizing.resetTotalPressureLossAcrossSupplyTrunk();
  EXPECT_FALSE(ductSizing.totalPressureLossAcrossSupplyTrunk());

  EXPECT_FALSE(ductSizing.totalPressureLossAcrossSupplyBranch());
  EXPECT_TRUE(ductSizing.setTotalPressureLossAcrossSupplyBranch(160.0));
  ASSERT_TRUE(ductSizing.totalPressureLossAcrossSupplyBranch());
  EXPECT_DOUBLE_EQ(160.0, *ductSizing.totalPressureLossAcrossSupplyBranch());
  ductSizing.resetTotalPressureLossAcrossSupplyBranch();
  EXPECT_FALSE(ductSizing.totalPressureLossAcrossSupplyBranch());

  EXPECT_FALSE(ductSizing.totalPressureLossAcrossReturnTrunk());
  EXPECT_TRUE(ductSizing.setTotalPressureLossAcrossReturnTrunk(185.0));
  ASSERT_TRUE(ductSizing.totalPressureLossAcrossReturnTrunk());
  EXPECT_DOUBLE_EQ(185.0, *ductSizing.totalPressureLossAcrossReturnTrunk());
  ductSizing.resetTotalPressureLossAcrossReturnTrunk();
  EXPECT_FALSE(ductSizing.totalPressureLossAcrossReturnTrunk());

  EXPECT_FALSE(ductSizing.totalPressureLossAcrossReturnBranch());
  EXPECT_TRUE(ductSizing.setTotalPressureLossAcrossReturnBranch(145.0));
  ASSERT_TRUE(ductSizing.totalPressureLossAcrossReturnBranch());
  EXPECT_DOUBLE_EQ(145.0, *ductSizing.totalPressureLossAcrossReturnBranch());
  ductSizing.resetTotalPressureLossAcrossReturnBranch();
  EXPECT_FALSE(ductSizing.totalPressureLossAcrossReturnBranch());
}
