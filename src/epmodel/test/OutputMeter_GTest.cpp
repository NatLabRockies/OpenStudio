/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/OutputMeter.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputMeter_DefaultConstructor) {
  Model model;
  OutputMeter outputMeter(model);

  EXPECT_EQ(OutputMeter::iddObjectType(), outputMeter.iddObject().type());
  EXPECT_EQ("", outputMeter.keyName());

  EXPECT_TRUE(outputMeter.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeter.reportingFrequency()));
}

TEST_F(EPModelFixture, OutputMeter_ScalarAccessors_RoundTrip) {
  Model model;
  OutputMeter outputMeter(model);

  const auto reportingFrequencyValues = OutputMeter::reportingFrequencyValues();
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Detailed"));
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Hourly"));

  EXPECT_TRUE(outputMeter.setKeyName("Electricity:Facility"));
  EXPECT_EQ("Electricity:Facility", outputMeter.keyName());

  EXPECT_TRUE(outputMeter.setReportingFrequency("Daily"));
  EXPECT_FALSE(outputMeter.isReportingFrequencyDefaulted());
  EXPECT_EQ("Daily", outputMeter.reportingFrequency());

  EXPECT_FALSE(outputMeter.setReportingFrequency("BadEnum"));
  EXPECT_EQ("Daily", outputMeter.reportingFrequency());

  outputMeter.resetReportingFrequency();
  EXPECT_TRUE(outputMeter.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeter.reportingFrequency()));
}
