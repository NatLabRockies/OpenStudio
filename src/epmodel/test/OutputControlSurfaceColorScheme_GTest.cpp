/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/OutputControlSurfaceColorScheme.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlSurfaceColorScheme_DefaultConstructor) {
  Model model;
  OutputControlSurfaceColorScheme object(model);
  EXPECT_EQ(OutputControlSurfaceColorScheme::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, OutputControlSurfaceColorScheme_ScalarAccessors_RoundTrip) {
  Model model;
  OutputControlSurfaceColorScheme object(model);

  EXPECT_TRUE(object.setName("Custom Surface Colors"));
  EXPECT_EQ("Custom Surface Colors", object.nameString());
}
