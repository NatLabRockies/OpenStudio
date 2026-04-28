/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferBasementManualGrid.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementManualGrid_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementManualGrid object(model);
  EXPECT_EQ(GroundHeatTransferBasementManualGrid::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementManualGrid_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementManualGrid object(model);

  EXPECT_TRUE(object.setNXNumberofcellsintheXdirection20(22));
  EXPECT_TRUE(object.setNYNumberofcellsintheYdirection20(24));
  EXPECT_TRUE(object.setNZAGNumberofcellsintheZdirectionabovegrade4Always(4));
  EXPECT_TRUE(object.setNZBGNumberofcellsinZdirectionbelowgrade1035(16));
  EXPECT_TRUE(object.setIBASEXdirectioncellindicatorofslabedge520(8));
  EXPECT_TRUE(object.setJBASEYdirectioncellindicatorofslabedge520(9));
  EXPECT_TRUE(object.setKBASEZdirectioncellindicatorofthetopofthefloorslab520(7));

  EXPECT_EQ(22, object.nXNumberofcellsintheXdirection20());
  EXPECT_EQ(24, object.nYNumberofcellsintheYdirection20());
  EXPECT_EQ(4, object.nZAGNumberofcellsintheZdirectionabovegrade4Always());
  EXPECT_EQ(16, object.nZBGNumberofcellsinZdirectionbelowgrade1035());
  EXPECT_EQ(8, object.iBASEXdirectioncellindicatorofslabedge520());
  EXPECT_EQ(9, object.jBASEYdirectioncellindicatorofslabedge520());
  EXPECT_EQ(7, object.kBASEZdirectioncellindicatorofthetopofthefloorslab520());
}
