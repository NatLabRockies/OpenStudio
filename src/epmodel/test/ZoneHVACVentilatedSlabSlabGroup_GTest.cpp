/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneHVACVentilatedSlabSlabGroup.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACVentilatedSlabSlabGroup_DefaultConstructor) {
  Model model;
  ZoneHVACVentilatedSlabSlabGroup slabGroup(model);

  EXPECT_EQ(ZoneHVACVentilatedSlabSlabGroup::iddObjectType(), slabGroup.iddObject().type());
}

TEST_F(EPModelFixture, ZoneHVACVentilatedSlabSlabGroup_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACVentilatedSlabSlabGroup slabGroup(model);

  EXPECT_TRUE(slabGroup.setName("SurfaceGroupA"));
  EXPECT_EQ("SurfaceGroupA", slabGroup.nameString());
}
