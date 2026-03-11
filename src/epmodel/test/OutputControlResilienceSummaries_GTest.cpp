/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputControlResilienceSummaries.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputControlResilienceSummaries_DefaultConstructor) {
  Model model;
  OutputControlResilienceSummaries object(model);

  EXPECT_EQ(OutputControlResilienceSummaries::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("Simplified", object.heatIndexAlgorithm());
}

TEST_F(EPModelFixture, OutputControlResilienceSummaries_ScalarAccessors_RoundTrip) {
  Model model;
  OutputControlResilienceSummaries object(model);

  const auto values = OutputControlResilienceSummaries::heatIndexAlgorithmValues();
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "Simplified"));

  const auto validValues = OutputControlResilienceSummaries::validHeatIndexAlgorithmValues();
  EXPECT_EQ(values, validValues);

  EXPECT_FALSE(object.setHeatIndexAlgorithm("bad value"));
  EXPECT_TRUE(object.setHeatIndexAlgorithm("Simplified"));
  EXPECT_EQ("Simplified", object.heatIndexAlgorithm());
}
