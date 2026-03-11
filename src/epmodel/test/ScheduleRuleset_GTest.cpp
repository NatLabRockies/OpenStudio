/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleRuleset.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleRuleset_DefaultConstructor) {
  Model model;
  ScheduleRuleset object(model);
  EXPECT_EQ(ScheduleRuleset::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ScheduleRuleset_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleRuleset object(model);

  EXPECT_TRUE(object.setName("Yearly Ruleset"));
  EXPECT_EQ("Yearly Ruleset", object.nameString());
}
