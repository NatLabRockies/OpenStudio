/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ComfortViewFactorAngles.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ComfortViewFactorAngles_DefaultConstructor) {
  Model model;
  ComfortViewFactorAngles comfortViewFactorAngles(model);
  EXPECT_EQ(ComfortViewFactorAngles::iddObjectType(), comfortViewFactorAngles.iddObject().type());
}

TEST_F(EPModelFixture, ComfortViewFactorAngles_ScalarAccessors_RoundTrip) {
  Model model;
  ComfortViewFactorAngles comfortViewFactorAngles(model);

  EXPECT_TRUE(comfortViewFactorAngles.setName("Occupant View Angles"));
  EXPECT_EQ("Occupant View Angles", comfortViewFactorAngles.nameString());
}
