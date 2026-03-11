/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Glazing/ThermochromicGlazing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermochromicGlazing_DefaultConstructor) {
  Model model;
  ThermochromicGlazing glazing(model);

  EXPECT_EQ(ThermochromicGlazing::iddObjectType(), glazing.iddObject().type());
  EXPECT_TRUE(glazing.setName("MyThermochromicGlazing"));
  EXPECT_EQ("MyThermochromicGlazing", glazing.nameString());
}

TEST_F(EPModelFixture, ThermochromicGlazing_MultipleInstances) {
  Model model;
  ThermochromicGlazing first(model);
  ThermochromicGlazing second(model);

  EXPECT_NE(first.handle(), second.handle());
}
