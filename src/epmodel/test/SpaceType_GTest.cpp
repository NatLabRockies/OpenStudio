/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/SpaceType.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceType_DefaultConstructor) {
  Model model;
  SpaceType spaceType(model);
  EXPECT_EQ(SpaceType::iddObjectType(), spaceType.iddObject().type());
}

TEST_F(EPModelFixture, SpaceType_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceType spaceType(model);

  EXPECT_TRUE(spaceType.setName("My SpaceType"));
  EXPECT_EQ("My SpaceType", spaceType.nameString());
}
