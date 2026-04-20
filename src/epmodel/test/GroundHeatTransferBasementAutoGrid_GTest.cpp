/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferBasementAutoGrid.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementAutoGrid_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementAutoGrid object(model);
  EXPECT_EQ(GroundHeatTransferBasementAutoGrid::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementAutoGrid_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementAutoGrid object(model);

  EXPECT_TRUE(object.setSlabxXdimensionofthebuildingslab(20.0));
  EXPECT_TRUE(object.setSlabyYdimensionofthebuildingslab(25.0));
  EXPECT_DOUBLE_EQ(20.0, object.slabxXdimensionofthebuildingslab());
  EXPECT_DOUBLE_EQ(25.0, object.slabyYdimensionofthebuildingslab());

  EXPECT_TRUE(object.isClearanceDistancefromoutsideofwalltoedgeDefaulted());
  EXPECT_TRUE(object.setClearanceDistancefromoutsideofwalltoedge(12.5));
  EXPECT_DOUBLE_EQ(12.5, object.clearanceDistancefromoutsideofwalltoedge());
  EXPECT_FALSE(object.isClearanceDistancefromoutsideofwalltoedgeDefaulted());
  object.resetClearanceDistancefromoutsideofwalltoedge();
  EXPECT_TRUE(object.isClearanceDistancefromoutsideofwalltoedgeDefaulted());

  EXPECT_TRUE(object.isConcAGHeightHeightofthefoundationwallabovegradeDefaulted());
  EXPECT_TRUE(object.setConcAGHeightHeightofthefoundationwallabovegrade(0.3));
  EXPECT_DOUBLE_EQ(0.3, object.concAGHeightHeightofthefoundationwallabovegrade());
  EXPECT_FALSE(object.isConcAGHeightHeightofthefoundationwallabovegradeDefaulted());
  object.resetConcAGHeightHeightofthefoundationwallabovegrade();
  EXPECT_TRUE(object.isConcAGHeightHeightofthefoundationwallabovegradeDefaulted());

  EXPECT_TRUE(object.isSlabDepthThicknessofthefloorslabDefaulted());
  EXPECT_TRUE(object.setSlabDepthThicknessofthefloorslab(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.slabDepthThicknessofthefloorslab());
  EXPECT_FALSE(object.isSlabDepthThicknessofthefloorslabDefaulted());
  object.resetSlabDepthThicknessofthefloorslab();
  EXPECT_TRUE(object.isSlabDepthThicknessofthefloorslabDefaulted());

  EXPECT_TRUE(object.isBaseDepthDepthofthebasementwallbelowgradeDefaulted());
  EXPECT_TRUE(object.setBaseDepthDepthofthebasementwallbelowgrade(2.7));
  EXPECT_DOUBLE_EQ(2.7, object.baseDepthDepthofthebasementwallbelowgrade());
  EXPECT_FALSE(object.isBaseDepthDepthofthebasementwallbelowgradeDefaulted());
  object.resetBaseDepthDepthofthebasementwallbelowgrade();
  EXPECT_TRUE(object.isBaseDepthDepthofthebasementwallbelowgradeDefaulted());
}
