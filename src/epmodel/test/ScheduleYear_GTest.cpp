/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleYear.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ScheduleYear_DefaultConstructor) {
  Model model;
  ScheduleYear object(model);
  EXPECT_EQ(ScheduleYear::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ScheduleYear_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleYear object(model);

  EXPECT_TRUE(object.setName("Yearly Schedule"));
  EXPECT_EQ("Yearly Schedule", object.nameString());
}
