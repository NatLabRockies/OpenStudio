/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/OutputVariable.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputVariable_DefaultConstructor) {
  Model model;
  OutputVariable outputVariable("Zone Lights Electricity Rate", model);

  EXPECT_EQ(OutputVariable::iddObjectType(), outputVariable.iddObject().type());
  EXPECT_EQ("Zone Lights Electricity Rate", outputVariable.variableName());

  EXPECT_TRUE(outputVariable.isKeyValueDefaulted());
  EXPECT_EQ("*", outputVariable.keyValue());

  EXPECT_TRUE(outputVariable.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputVariable.reportingFrequency()));
}

TEST_F(EPModelFixture, OutputVariable_ScalarAccessors_RoundTrip) {
  Model model;
  OutputVariable outputVariable("Zone Lights Electricity Rate", model);

  const auto reportingFrequencyValues = OutputVariable::reportingFrequencyValues();
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Detailed"));
  EXPECT_NE(reportingFrequencyValues.end(), std::find(reportingFrequencyValues.begin(), reportingFrequencyValues.end(), "Hourly"));

  EXPECT_TRUE(outputVariable.setKeyValue("SPACE1-1"));
  EXPECT_FALSE(outputVariable.isKeyValueDefaulted());
  EXPECT_EQ("SPACE1-1", outputVariable.keyValue());

  EXPECT_TRUE(outputVariable.setReportingFrequency("Daily"));
  EXPECT_FALSE(outputVariable.isReportingFrequencyDefaulted());
  EXPECT_EQ("Daily", outputVariable.reportingFrequency());

  EXPECT_FALSE(outputVariable.setReportingFrequency("BadEnum"));
  EXPECT_EQ("Daily", outputVariable.reportingFrequency());

  outputVariable.resetKeyValue();
  EXPECT_TRUE(outputVariable.isKeyValueDefaulted());
  EXPECT_EQ("*", outputVariable.keyValue());

  outputVariable.resetReportingFrequency();
  EXPECT_TRUE(outputVariable.isReportingFrequencyDefaulted());
  EXPECT_TRUE(openstudio::istringEqual("Hourly", outputVariable.reportingFrequency()));
}
