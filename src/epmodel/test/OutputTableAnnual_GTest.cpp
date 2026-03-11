/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputTableAnnual.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputTableAnnual_DefaultConstructor) {
  Model model;
  OutputTableAnnual outputTableAnnual(model);

  EXPECT_EQ(OutputTableAnnual::iddObjectType(), outputTableAnnual.iddObject().type());
  EXPECT_FALSE(outputTableAnnual.filter());
}

TEST_F(EPModelFixture, OutputTableAnnual_ScalarAccessors_RoundTrip) {
  Model model;
  OutputTableAnnual outputTableAnnual(model);

  EXPECT_FALSE(outputTableAnnual.filter());

  EXPECT_TRUE(outputTableAnnual.setFilter("Zone 1"));
  ASSERT_TRUE(outputTableAnnual.filter());
  EXPECT_EQ("Zone 1", outputTableAnnual.filter().get());

  outputTableAnnual.resetFilter();
  EXPECT_FALSE(outputTableAnnual.filter());
}
