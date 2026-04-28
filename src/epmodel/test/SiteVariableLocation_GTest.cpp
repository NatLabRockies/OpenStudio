/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SiteVariableLocation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteVariableLocation_DefaultConstructor) {
  Model model;
  SiteVariableLocation object(model);
  EXPECT_EQ(SiteVariableLocation::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteVariableLocation_ScalarAccessors_RoundTrip) {
  Model model;
  SiteVariableLocation object(model);

  EXPECT_TRUE(object.setName("Variable Vessel Site"));
  EXPECT_EQ("Variable Vessel Site", object.nameString());
}
