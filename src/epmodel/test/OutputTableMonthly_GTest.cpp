/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputTableMonthly.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputTableMonthly_DefaultConstructor) {
  Model model;
  OutputTableMonthly outputTableMonthly(model);

  EXPECT_EQ(OutputTableMonthly::iddObjectType(), outputTableMonthly.iddObject().type());
  EXPECT_EQ(2, outputTableMonthly.digitsAfterDecimal());
}

TEST_F(EPModelFixture, OutputTableMonthly_ScalarAccessors_RoundTrip) {
  Model model;
  OutputTableMonthly outputTableMonthly(model);

  EXPECT_TRUE(outputTableMonthly.setDigitsAfterDecimal(4));
  EXPECT_EQ(4, outputTableMonthly.digitsAfterDecimal());
}
