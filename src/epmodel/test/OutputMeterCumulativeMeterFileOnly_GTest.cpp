/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/OutputMeterCumulativeMeterFileOnly.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputMeterCumulativeMeterFileOnly_DefaultConstructor) {
  Model model;
  OutputMeterCumulativeMeterFileOnly outputMeterCumulativeMeterFileOnly(model);

  EXPECT_EQ(OutputMeterCumulativeMeterFileOnly::iddObjectType(), outputMeterCumulativeMeterFileOnly.iddObject().type());
  EXPECT_EQ("", outputMeterCumulativeMeterFileOnly.keyName());

  EXPECT_TRUE(outputMeterCumulativeMeterFileOnly.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeterCumulativeMeterFileOnly.reportingFrequency()));
}

TEST_F(EPModelFixture, OutputMeterCumulativeMeterFileOnly_ScalarAccessors_RoundTrip) {
  Model model;
  OutputMeterCumulativeMeterFileOnly outputMeterCumulativeMeterFileOnly(model);

  const auto reportingFrequencyValues = OutputMeterCumulativeMeterFileOnly::reportingFrequencyValues();
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Detailed"));
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Hourly"));

  EXPECT_TRUE(outputMeterCumulativeMeterFileOnly.setKeyName("DistrictHeating:Facility"));
  EXPECT_EQ("DistrictHeating:Facility", outputMeterCumulativeMeterFileOnly.keyName());

  EXPECT_TRUE(outputMeterCumulativeMeterFileOnly.setReportingFrequency("Daily"));
  EXPECT_FALSE(outputMeterCumulativeMeterFileOnly.isReportingFrequencyDefaulted());
  EXPECT_EQ("Daily", outputMeterCumulativeMeterFileOnly.reportingFrequency());

  EXPECT_FALSE(outputMeterCumulativeMeterFileOnly.setReportingFrequency("BadEnum"));
  EXPECT_EQ("Daily", outputMeterCumulativeMeterFileOnly.reportingFrequency());

  outputMeterCumulativeMeterFileOnly.resetReportingFrequency();
  EXPECT_TRUE(outputMeterCumulativeMeterFileOnly.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeterCumulativeMeterFileOnly.reportingFrequency()));
}
