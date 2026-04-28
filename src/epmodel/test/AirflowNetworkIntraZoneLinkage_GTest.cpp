/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/AirflowNetworkIntraZoneLinkage.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkIntraZoneLinkage_DefaultConstructor) {
  Model model;
  AirflowNetworkIntraZoneLinkage linkage(model);
  EXPECT_EQ(AirflowNetworkIntraZoneLinkage::iddObjectType(), linkage.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkIntraZoneLinkage_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkIntraZoneLinkage linkage(model);

  EXPECT_TRUE(linkage.setName("IntraZone Door Linkage"));
  EXPECT_EQ("IntraZone Door Linkage", linkage.nameString());
}
