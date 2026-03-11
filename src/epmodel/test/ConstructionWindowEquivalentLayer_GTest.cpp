/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ConstructionWindowEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConstructionWindowEquivalentLayer_DefaultConstructor) {
  Model model;
  ConstructionWindowEquivalentLayer object(model);
  EXPECT_EQ(ConstructionWindowEquivalentLayer::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ConstructionWindowEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  ConstructionWindowEquivalentLayer object(model);

  EXPECT_TRUE(object.setName("Equivalent Layer Construction"));
  EXPECT_EQ("Equivalent Layer Construction", object.nameString());
}
