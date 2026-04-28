/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/OutputMeterCumulative.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputMeterCumulative_DefaultConstructor) {
  Model model;
  OutputMeterCumulative outputMeterCumulative(model);

  EXPECT_EQ(OutputMeterCumulative::iddObjectType(), outputMeterCumulative.iddObject().type());
  EXPECT_EQ("", outputMeterCumulative.keyName());

  EXPECT_TRUE(outputMeterCumulative.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeterCumulative.reportingFrequency()));
}

TEST_F(EPModelFixture, OutputMeterCumulative_ScalarAccessors_RoundTrip) {
  Model model;
  OutputMeterCumulative outputMeterCumulative(model);

  const auto reportingFrequencyValues = OutputMeterCumulative::reportingFrequencyValues();
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Detailed"));
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Hourly"));

  EXPECT_TRUE(outputMeterCumulative.setKeyName("NaturalGas:Facility"));
  EXPECT_EQ("NaturalGas:Facility", outputMeterCumulative.keyName());

  EXPECT_TRUE(outputMeterCumulative.setReportingFrequency("Daily"));
  EXPECT_FALSE(outputMeterCumulative.isReportingFrequencyDefaulted());
  EXPECT_EQ("Daily", outputMeterCumulative.reportingFrequency());

  EXPECT_FALSE(outputMeterCumulative.setReportingFrequency("BadEnum"));
  EXPECT_EQ("Daily", outputMeterCumulative.reportingFrequency());

  outputMeterCumulative.resetReportingFrequency();
  EXPECT_TRUE(outputMeterCumulative.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeterCumulative.reportingFrequency()));
}
