/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/SurfacePropertyLocalEnvironment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyLocalEnvironment_DefaultConstructor) {
  Model model;
  SurfacePropertyLocalEnvironment localEnv(model);
  EXPECT_EQ(SurfacePropertyLocalEnvironment::iddObjectType(), localEnv.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyLocalEnvironment_NameRoundTrip) {
  Model model;
  SurfacePropertyLocalEnvironment localEnv(model);

  EXPECT_TRUE(localEnv.setName("Ambient Local Environment"));
  EXPECT_EQ("Ambient Local Environment", localEnv.nameString());
}
