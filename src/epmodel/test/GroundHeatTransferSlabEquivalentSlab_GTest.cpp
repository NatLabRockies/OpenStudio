/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferSlabEquivalentSlab.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabEquivalentSlab_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabEquivalentSlab object(model);
  EXPECT_EQ(GroundHeatTransferSlabEquivalentSlab::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabEquivalentSlab_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabEquivalentSlab object(model);

  EXPECT_TRUE(object.setApratioTheareatoperimeterratioforthisslab(6.5));
  EXPECT_DOUBLE_EQ(6.5, object.apratioTheareatoperimeterratioforthisslab());

  EXPECT_TRUE(object.isSlabdepthThicknessofslabongradeDefaulted());
  EXPECT_TRUE(object.setSlabdepthThicknessofslabongrade(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.slabdepthThicknessofslabongrade());
  EXPECT_FALSE(object.isSlabdepthThicknessofslabongradeDefaulted());
  object.resetSlabdepthThicknessofslabongrade();
  EXPECT_TRUE(object.isSlabdepthThicknessofslabongradeDefaulted());

  EXPECT_TRUE(object.isClearanceDistancefromedgeofslabtodomainedgeDefaulted());
  EXPECT_TRUE(object.setClearanceDistancefromedgeofslabtodomainedge(10.0));
  EXPECT_DOUBLE_EQ(10.0, object.clearanceDistancefromedgeofslabtodomainedge());
  EXPECT_FALSE(object.isClearanceDistancefromedgeofslabtodomainedgeDefaulted());
  object.resetClearanceDistancefromedgeofslabtodomainedge();
  EXPECT_TRUE(object.isClearanceDistancefromedgeofslabtodomainedgeDefaulted());

  EXPECT_TRUE(object.isZclearanceDistancefrombottomofslabtodomainbottomDefaulted());
  EXPECT_TRUE(object.setZclearanceDistancefrombottomofslabtodomainbottom(12.5));
  EXPECT_DOUBLE_EQ(12.5, object.zclearanceDistancefrombottomofslabtodomainbottom());
  EXPECT_FALSE(object.isZclearanceDistancefrombottomofslabtodomainbottomDefaulted());
  object.resetZclearanceDistancefrombottomofslabtodomainbottom();
  EXPECT_TRUE(object.isZclearanceDistancefrombottomofslabtodomainbottomDefaulted());
}
