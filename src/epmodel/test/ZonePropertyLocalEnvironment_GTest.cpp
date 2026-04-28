/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/ZonePropertyLocalEnvironment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZonePropertyLocalEnvironment_DefaultConstructor) {
  Model model;
  ZonePropertyLocalEnvironment environment(model);
  EXPECT_EQ(ZonePropertyLocalEnvironment::iddObjectType(), environment.iddObject().type());
}

TEST_F(EPModelFixture, ZonePropertyLocalEnvironment_ScalarAccessors_RoundTrip) {
  Model model;
  ZonePropertyLocalEnvironment environment(model);

  EXPECT_TRUE(environment.setName("Zone Local Environment"));
  EXPECT_EQ("Zone Local Environment", environment.nameString());
}
