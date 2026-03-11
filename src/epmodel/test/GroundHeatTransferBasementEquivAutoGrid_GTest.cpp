/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferBasementEquivAutoGrid.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementEquivAutoGrid_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementEquivAutoGrid object(model);
  EXPECT_EQ(GroundHeatTransferBasementEquivAutoGrid::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementEquivAutoGrid_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementEquivAutoGrid object(model);

  EXPECT_TRUE(object.isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted());
  EXPECT_TRUE(object.isSlabDepthThicknessofthefloorslabDefaulted());
  EXPECT_TRUE(object.isBaseDepthDepthofthebasementwallbelowgradeDefaulted());

  EXPECT_TRUE(object.setClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain(12.5));
  EXPECT_DOUBLE_EQ(12.5, object.clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain());
  EXPECT_FALSE(object.isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted());
  object.resetClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain();
  EXPECT_TRUE(object.isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted());

  EXPECT_TRUE(object.setSlabDepthThicknessofthefloorslab(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.slabDepthThicknessofthefloorslab());
  EXPECT_FALSE(object.isSlabDepthThicknessofthefloorslabDefaulted());
  object.resetSlabDepthThicknessofthefloorslab();
  EXPECT_TRUE(object.isSlabDepthThicknessofthefloorslabDefaulted());

  EXPECT_TRUE(object.setBaseDepthDepthofthebasementwallbelowgrade(2.7));
  EXPECT_DOUBLE_EQ(2.7, object.baseDepthDepthofthebasementwallbelowgrade());
  EXPECT_FALSE(object.isBaseDepthDepthofthebasementwallbelowgradeDefaulted());
  object.resetBaseDepthDepthofthebasementwallbelowgrade();
  EXPECT_TRUE(object.isBaseDepthDepthofthebasementwallbelowgradeDefaulted());
}
