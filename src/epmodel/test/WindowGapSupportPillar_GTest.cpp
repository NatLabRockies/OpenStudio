/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowGapSupportPillar.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowGapSupportPillar_DefaultConstructor) {
  Model model;
  WindowGapSupportPillar pillar(model);
  EXPECT_EQ(WindowGapSupportPillar::iddObjectType(), pillar.iddObject().type());
  EXPECT_DOUBLE_EQ(0.04, pillar.spacing());
  EXPECT_TRUE(pillar.isSpacingDefaulted());
  EXPECT_DOUBLE_EQ(0.0004, pillar.radius());
  EXPECT_TRUE(pillar.isRadiusDefaulted());
}

TEST_F(EPModelFixture, WindowGapSupportPillar_ScalarAccessors_RoundTrip) {
  Model model;
  WindowGapSupportPillar pillar(model);

  EXPECT_TRUE(pillar.setSpacing(0.1));
  EXPECT_FALSE(pillar.isSpacingDefaulted());
  EXPECT_DOUBLE_EQ(0.1, pillar.spacing());
  pillar.resetSpacing();
  EXPECT_TRUE(pillar.isSpacingDefaulted());
  EXPECT_DOUBLE_EQ(0.04, pillar.spacing());

  EXPECT_TRUE(pillar.setRadius(0.002));
  EXPECT_FALSE(pillar.isRadiusDefaulted());
  EXPECT_DOUBLE_EQ(0.002, pillar.radius());
  pillar.resetRadius();
  EXPECT_TRUE(pillar.isRadiusDefaulted());
  EXPECT_DOUBLE_EQ(0.0004, pillar.radius());
}
