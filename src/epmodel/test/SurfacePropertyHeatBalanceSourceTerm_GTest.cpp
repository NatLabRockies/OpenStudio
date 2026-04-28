/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SurfacePropertyHeatBalanceSourceTerm.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyHeatBalanceSourceTerm_DefaultConstructor) {
  Model model;
  SurfacePropertyHeatBalanceSourceTerm sourceTerm(model);
  EXPECT_EQ(SurfacePropertyHeatBalanceSourceTerm::iddObjectType(), sourceTerm.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyHeatBalanceSourceTerm_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyHeatBalanceSourceTerm sourceTerm(model);

  EXPECT_FALSE(sourceTerm.setName("Heat Balance Source"));
  EXPECT_TRUE(sourceTerm.nameString().empty());
}
