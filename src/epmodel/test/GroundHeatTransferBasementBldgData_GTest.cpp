/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatTransferBasementBldgData.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementBldgData_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementBldgData object(model);
  EXPECT_EQ(GroundHeatTransferBasementBldgData::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementBldgData_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatTransferBasementBldgData object(model);

  EXPECT_TRUE(object.isDwallWallthicknessDefaulted());
  EXPECT_TRUE(object.isDslabFloorslabthicknessDefaulted());
  EXPECT_TRUE(object.isDgravxyWidthofgravelpitbesidebasementwallDefaulted());
  EXPECT_TRUE(object.isDgravznGraveldepthextendingabovethefloorslabDefaulted());
  EXPECT_TRUE(object.isDgravzpGraveldepthbelowthefloorslabDefaulted());

  EXPECT_TRUE(object.setDwallWallthickness(0.25));
  EXPECT_DOUBLE_EQ(0.25, object.dwallWallthickness());

  EXPECT_TRUE(object.setDslabFloorslabthickness(0.2));
  EXPECT_DOUBLE_EQ(0.2, object.dslabFloorslabthickness());

  EXPECT_TRUE(object.setDgravxyWidthofgravelpitbesidebasementwall(0.5));
  EXPECT_DOUBLE_EQ(0.5, object.dgravxyWidthofgravelpitbesidebasementwall());

  EXPECT_TRUE(object.setDgravznGraveldepthextendingabovethefloorslab(0.35));
  EXPECT_DOUBLE_EQ(0.35, object.dgravznGraveldepthextendingabovethefloorslab());

  EXPECT_TRUE(object.setDgravzpGraveldepthbelowthefloorslab(0.15));
  EXPECT_DOUBLE_EQ(0.15, object.dgravzpGraveldepthbelowthefloorslab());

  EXPECT_TRUE(object.setDwallWallthickness(0.21));
  EXPECT_FALSE(object.isDwallWallthicknessDefaulted());
  object.resetDwallWallthickness();
  EXPECT_TRUE(object.isDwallWallthicknessDefaulted());

  EXPECT_TRUE(object.setDslabFloorslabthickness(0.22));
  EXPECT_FALSE(object.isDslabFloorslabthicknessDefaulted());
  object.resetDslabFloorslabthickness();
  EXPECT_TRUE(object.isDslabFloorslabthicknessDefaulted());

  EXPECT_TRUE(object.setDgravxyWidthofgravelpitbesidebasementwall(0.42));
  EXPECT_FALSE(object.isDgravxyWidthofgravelpitbesidebasementwallDefaulted());
  object.resetDgravxyWidthofgravelpitbesidebasementwall();
  EXPECT_TRUE(object.isDgravxyWidthofgravelpitbesidebasementwallDefaulted());

  EXPECT_TRUE(object.setDgravznGraveldepthextendingabovethefloorslab(0.28));
  EXPECT_FALSE(object.isDgravznGraveldepthextendingabovethefloorslabDefaulted());
  object.resetDgravznGraveldepthextendingabovethefloorslab();
  EXPECT_TRUE(object.isDgravznGraveldepthextendingabovethefloorslabDefaulted());

  EXPECT_TRUE(object.setDgravzpGraveldepthbelowthefloorslab(0.14));
  EXPECT_FALSE(object.isDgravzpGraveldepthbelowthefloorslabDefaulted());
  object.resetDgravzpGraveldepthbelowthefloorslab();
  EXPECT_TRUE(object.isDgravzpGraveldepthbelowthefloorslabDefaulted());
}
