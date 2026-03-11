/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneControlHumidistat.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneControlHumidistat_DefaultConstructor) {
  Model model;
  ZoneControlHumidistat humidistat(model);
  EXPECT_EQ(ZoneControlHumidistat::iddObjectType(), humidistat.iddObject().type());
}

TEST_F(EPModelFixture, ZoneControlHumidistat_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlHumidistat humidistat(model);

  EXPECT_TRUE(humidistat.setName("Zone Humidistat"));
  EXPECT_EQ("Zone Humidistat", humidistat.nameString());
}
