/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/OutputMeterMeterFileOnly.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputMeterMeterFileOnly_DefaultConstructor) {
  Model model;
  OutputMeterMeterFileOnly outputMeterMeterFileOnly(model);

  EXPECT_EQ(OutputMeterMeterFileOnly::iddObjectType(), outputMeterMeterFileOnly.iddObject().type());
  EXPECT_EQ("", outputMeterMeterFileOnly.keyName());

  EXPECT_TRUE(outputMeterMeterFileOnly.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeterMeterFileOnly.reportingFrequency()));
}

TEST_F(EPModelFixture, OutputMeterMeterFileOnly_ScalarAccessors_RoundTrip) {
  Model model;
  OutputMeterMeterFileOnly outputMeterMeterFileOnly(model);

  const auto reportingFrequencyValues = OutputMeterMeterFileOnly::reportingFrequencyValues();
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Detailed"));
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Hourly"));

  EXPECT_TRUE(outputMeterMeterFileOnly.setKeyName("DistrictHeating:Facility"));
  EXPECT_EQ("DistrictHeating:Facility", outputMeterMeterFileOnly.keyName());

  EXPECT_TRUE(outputMeterMeterFileOnly.setReportingFrequency("Daily"));
  EXPECT_FALSE(outputMeterMeterFileOnly.isReportingFrequencyDefaulted());
  EXPECT_EQ("Daily", outputMeterMeterFileOnly.reportingFrequency());

  EXPECT_FALSE(outputMeterMeterFileOnly.setReportingFrequency("BadEnum"));
  EXPECT_EQ("Daily", outputMeterMeterFileOnly.reportingFrequency());

  outputMeterMeterFileOnly.resetReportingFrequency();
  EXPECT_TRUE(outputMeterMeterFileOnly.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputMeterMeterFileOnly.reportingFrequency()));
}
