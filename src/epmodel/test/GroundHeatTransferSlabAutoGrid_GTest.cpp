/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferSlabAutoGrid.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabAutoGrid_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabAutoGrid object(model);
  EXPECT_EQ(GroundHeatTransferSlabAutoGrid::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabAutoGrid_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabAutoGrid object(model);

  EXPECT_TRUE(object.setSlabxXdimensionofthebuildingslab(20.0));
  EXPECT_TRUE(object.setSlabyYdimensionofthebuildingslab(25.0));
  EXPECT_DOUBLE_EQ(20.0, object.slabxXdimensionofthebuildingslab());
  EXPECT_DOUBLE_EQ(25.0, object.slabyYdimensionofthebuildingslab());

  EXPECT_TRUE(object.isSlabdepthThicknessofslabongradeDefaulted());
  EXPECT_TRUE(object.setSlabdepthThicknessofslabongrade(0.15));
  EXPECT_DOUBLE_EQ(0.15, object.slabdepthThicknessofslabongrade());
  EXPECT_FALSE(object.isSlabdepthThicknessofslabongradeDefaulted());
  object.resetSlabdepthThicknessofslabongrade();
  EXPECT_TRUE(object.isSlabdepthThicknessofslabongradeDefaulted());

  EXPECT_TRUE(object.isClearanceDistancefromedgeofslabtodomainedgeDefaulted());
  EXPECT_TRUE(object.setClearanceDistancefromedgeofslabtodomainedge(18.0));
  EXPECT_DOUBLE_EQ(18.0, object.clearanceDistancefromedgeofslabtodomainedge());
  EXPECT_FALSE(object.isClearanceDistancefromedgeofslabtodomainedgeDefaulted());
  object.resetClearanceDistancefromedgeofslabtodomainedge();
  EXPECT_TRUE(object.isClearanceDistancefromedgeofslabtodomainedgeDefaulted());

  EXPECT_TRUE(object.isZclearanceDistancefrombottomofslabtodomainbottomDefaulted());
  EXPECT_TRUE(object.setZclearanceDistancefrombottomofslabtodomainbottom(15.0));
  EXPECT_DOUBLE_EQ(15.0, object.zclearanceDistancefrombottomofslabtodomainbottom());
  EXPECT_FALSE(object.isZclearanceDistancefrombottomofslabtodomainbottomDefaulted());
  object.resetZclearanceDistancefrombottomofslabtodomainbottom();
  EXPECT_TRUE(object.isZclearanceDistancefrombottomofslabtodomainbottomDefaulted());
}
