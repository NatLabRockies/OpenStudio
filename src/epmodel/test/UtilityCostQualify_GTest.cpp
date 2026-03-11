/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "ModelObject/UtilityCostQualify.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, UtilityCostQualify_DefaultConstructor) {
  Model model;
  UtilityCostQualify qualify(model);

  EXPECT_EQ(UtilityCostQualify::iddObjectType(), qualify.iddObject().type());
  EXPECT_FALSE(UtilityCostQualify::qualifyTypeValues().empty());
  EXPECT_FALSE(UtilityCostQualify::seasonValues().empty());
  EXPECT_FALSE(UtilityCostQualify::thresholdTestValues().empty());
  EXPECT_TRUE(qualify.isSeasonDefaulted());
  EXPECT_TRUE(qualify.isNumberOfMonthsDefaulted());
}

TEST_F(EPModelFixture, UtilityCostQualify_ScalarAccessors_RoundTrip) {
  Model model;
  UtilityCostQualify qualify(model);

  EXPECT_TRUE(qualify.setVariableName("totalEnergy"));
  EXPECT_TRUE(qualify.setQualifyType("Minimum"));
  EXPECT_TRUE(qualify.setThresholdValueorVariableName("var"));
  EXPECT_TRUE(qualify.setSeason("Winter"));
  EXPECT_TRUE(qualify.setThresholdTest("Count"));
  EXPECT_TRUE(qualify.setNumberOfMonths(3));

  EXPECT_EQ("totalEnergy", qualify.variableName());
  EXPECT_EQ("Minimum", qualify.qualifyType());
  EXPECT_EQ("var", qualify.thresholdValueorVariableName());
  EXPECT_FALSE(qualify.isSeasonDefaulted());
  EXPECT_EQ("Winter", qualify.season());
  EXPECT_EQ("Count", qualify.thresholdTest());
  EXPECT_FALSE(qualify.isNumberOfMonthsDefaulted());
  EXPECT_EQ(3, qualify.numberOfMonths());

  qualify.resetSeason();
  EXPECT_TRUE(qualify.isSeasonDefaulted());

  qualify.resetNumberOfMonths();
  EXPECT_TRUE(qualify.isNumberOfMonthsDefaulted());
}
