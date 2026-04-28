/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowMaterialGap.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialGap_DefaultConstructor) {
  Model model;
  WindowMaterialGap gap(model);
  EXPECT_EQ(WindowMaterialGap::iddObjectType(), gap.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0127, gap.thickness());
  EXPECT_DOUBLE_EQ(101325.0, gap.pressure());
  EXPECT_TRUE(gap.isPressureDefaulted());
}

TEST_F(EPModelFixture, WindowMaterialGap_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialGap gap(model);

  EXPECT_TRUE(gap.setThickness(0.02));
  EXPECT_TRUE(gap.setPressure(100000.0));

  EXPECT_DOUBLE_EQ(0.02, gap.thickness());
  EXPECT_DOUBLE_EQ(100000.0, gap.pressure());
  EXPECT_FALSE(gap.isPressureDefaulted());

  gap.resetPressure();
  EXPECT_TRUE(gap.isPressureDefaulted());
  EXPECT_DOUBLE_EQ(101325.0, gap.pressure());
}
