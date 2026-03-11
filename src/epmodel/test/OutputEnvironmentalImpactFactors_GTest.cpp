/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputEnvironmentalImpactFactors.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputEnvironmentalImpactFactors_DefaultConstructor) {
  Model model;
  OutputEnvironmentalImpactFactors outputEnvironmentalImpactFactors(model);

  EXPECT_EQ(OutputEnvironmentalImpactFactors::iddObjectType(), outputEnvironmentalImpactFactors.iddObject().type());
  EXPECT_EQ("Monthly", outputEnvironmentalImpactFactors.reportingFrequency());
}

TEST_F(EPModelFixture, OutputEnvironmentalImpactFactors_ScalarAccessors_RoundTrip) {
  Model model;
  OutputEnvironmentalImpactFactors outputEnvironmentalImpactFactors(model);

  const auto reportingFrequencyValues = OutputEnvironmentalImpactFactors::reportingFrequencyValues();
  EXPECT_FALSE(reportingFrequencyValues.empty());

  EXPECT_TRUE(outputEnvironmentalImpactFactors.setReportingFrequency("Hourly"));
  EXPECT_EQ("Hourly", outputEnvironmentalImpactFactors.reportingFrequency());

  EXPECT_FALSE(outputEnvironmentalImpactFactors.setReportingFrequency("BadEnum"));
  EXPECT_EQ("Hourly", outputEnvironmentalImpactFactors.reportingFrequency());
}
