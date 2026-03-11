/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirflowNetworkLinkage/AirflowNetworkDistributionLinkage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionLinkage_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionLinkage linkage(model);
  EXPECT_EQ(AirflowNetworkDistributionLinkage::iddObjectType(), linkage.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionLinkage_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionLinkage linkage(model);

  EXPECT_TRUE(linkage.setName("Supply Trunk Linkage"));
  EXPECT_EQ("Supply Trunk Linkage", linkage.nameString());
}
