/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferSlabManualGrid.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferSlabManualGrid_DefaultConstructor) {
  Model model;
  GroundHeatTransferSlabManualGrid object(model);
  EXPECT_EQ(GroundHeatTransferSlabManualGrid::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferSlabManualGrid_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferSlabManualGrid object(model);

  EXPECT_TRUE(object.setNXNumberofcellsintheXdirection(20));
  EXPECT_TRUE(object.setNYNumberofcellsintheYdirection(18));
  EXPECT_TRUE(object.setNZNumberofcellsintheZdirection(12));
  EXPECT_TRUE(object.setIBOXXdirectioncellindicatorofslabedge(7));
  EXPECT_TRUE(object.setJBOXYdirectioncellindicatorofslabedge(6));

  EXPECT_EQ(20, object.nXNumberofcellsintheXdirection());
  EXPECT_EQ(18, object.nYNumberofcellsintheYdirection());
  EXPECT_EQ(12, object.nZNumberofcellsintheZdirection());
  EXPECT_EQ(7, object.iBOXXdirectioncellindicatorofslabedge());
  EXPECT_EQ(6, object.jBOXYdirectioncellindicatorofslabedge());
}
