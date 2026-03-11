/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputDaylightFactors.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputDaylightFactors_DefaultConstructor) {
  Model model;
  OutputDaylightFactors outputDaylightFactors(model);

  EXPECT_EQ(OutputDaylightFactors::iddObjectType(), outputDaylightFactors.iddObject().type());
}

TEST_F(EPModelFixture, OutputDaylightFactors_ScalarAccessors_RoundTrip) {
  Model model;
  OutputDaylightFactors outputDaylightFactors(model);

  const auto values = OutputDaylightFactors::reportingDaysValues();
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "SizingDays"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "AllShadowCalculationDays"));

  EXPECT_FALSE(outputDaylightFactors.setReportingDays("bad value"));
  EXPECT_TRUE(outputDaylightFactors.setReportingDays("AllShadowCalculationDays"));
  EXPECT_EQ("AllShadowCalculationDays", outputDaylightFactors.reportingDays());

  EXPECT_TRUE(outputDaylightFactors.setReportingDays("SizingDays"));
  EXPECT_EQ("SizingDays", outputDaylightFactors.reportingDays());
}
