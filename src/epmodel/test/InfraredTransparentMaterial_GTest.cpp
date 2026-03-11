/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelPartitionMaterial/InfraredTransparentMaterial.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, InfraredTransparentMaterial_DefaultConstructor) {
  Model model;
  InfraredTransparentMaterial object(model);
  EXPECT_EQ(InfraredTransparentMaterial::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, InfraredTransparentMaterial_ScalarAccessors_RoundTrip) {
  Model model;
  InfraredTransparentMaterial object(model);

  EXPECT_TRUE(object.setName("IR Transparent Material"));
  EXPECT_EQ("IR Transparent Material", object.nameString());
}
