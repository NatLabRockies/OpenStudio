/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/OutputPreprocessorMessage.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputPreprocessorMessage_DefaultConstructor) {
  Model model;
  OutputPreprocessorMessage outputPreprocessorMessage(model);

  EXPECT_EQ(OutputPreprocessorMessage::iddObjectType(), outputPreprocessorMessage.iddObject().type());
  EXPECT_FALSE(outputPreprocessorMessage.preprocessorName());
  EXPECT_FALSE(outputPreprocessorMessage.errorSeverity());
  EXPECT_FALSE(outputPreprocessorMessage.messageLine1());
  EXPECT_FALSE(outputPreprocessorMessage.messageLine10());
}

TEST_F(EPModelFixture, OutputPreprocessorMessage_ScalarAccessors_RoundTrip) {
  Model model;
  OutputPreprocessorMessage outputPreprocessorMessage(model);

  const auto errorSeverityValues = OutputPreprocessorMessage::errorSeverityValues();
  EXPECT_NE(errorSeverityValues.end(), std::find(errorSeverityValues.begin(), errorSeverityValues.end(), "Information"));
  EXPECT_NE(errorSeverityValues.end(), std::find(errorSeverityValues.begin(), errorSeverityValues.end(), "Warning"));
  EXPECT_NE(errorSeverityValues.end(), std::find(errorSeverityValues.begin(), errorSeverityValues.end(), "Severe"));
  EXPECT_NE(errorSeverityValues.end(), std::find(errorSeverityValues.begin(), errorSeverityValues.end(), "Fatal"));

  EXPECT_TRUE(outputPreprocessorMessage.setPreprocessorName("EPXMLPreProc2"));
  ASSERT_TRUE(outputPreprocessorMessage.preprocessorName());
  EXPECT_EQ("EPXMLPreProc2", outputPreprocessorMessage.preprocessorName().get());

  EXPECT_TRUE(outputPreprocessorMessage.setErrorSeverity("Warning"));
  ASSERT_TRUE(outputPreprocessorMessage.errorSeverity());
  EXPECT_EQ("Warning", outputPreprocessorMessage.errorSeverity().get());

  EXPECT_TRUE(outputPreprocessorMessage.setMessageLine1("Line 1"));
  EXPECT_TRUE(outputPreprocessorMessage.setMessageLine2("Line 2"));
  EXPECT_TRUE(outputPreprocessorMessage.setMessageLine10("Line 10"));
  ASSERT_TRUE(outputPreprocessorMessage.messageLine1());
  ASSERT_TRUE(outputPreprocessorMessage.messageLine2());
  ASSERT_TRUE(outputPreprocessorMessage.messageLine10());
  EXPECT_EQ("Line 1", outputPreprocessorMessage.messageLine1().get());
  EXPECT_EQ("Line 2", outputPreprocessorMessage.messageLine2().get());
  EXPECT_EQ("Line 10", outputPreprocessorMessage.messageLine10().get());

  EXPECT_FALSE(outputPreprocessorMessage.setErrorSeverity("InvalidSeverity"));
  ASSERT_TRUE(outputPreprocessorMessage.errorSeverity());
  EXPECT_EQ("Warning", outputPreprocessorMessage.errorSeverity().get());

  outputPreprocessorMessage.resetPreprocessorName();
  outputPreprocessorMessage.resetErrorSeverity();
  outputPreprocessorMessage.resetMessageLine1();
  outputPreprocessorMessage.resetMessageLine2();
  outputPreprocessorMessage.resetMessageLine10();

  ASSERT_TRUE(outputPreprocessorMessage.preprocessorName());
  ASSERT_TRUE(outputPreprocessorMessage.errorSeverity());
  ASSERT_TRUE(outputPreprocessorMessage.messageLine1());
  ASSERT_TRUE(outputPreprocessorMessage.messageLine2());
  ASSERT_TRUE(outputPreprocessorMessage.messageLine10());
  EXPECT_EQ("", outputPreprocessorMessage.preprocessorName().get());
  EXPECT_EQ("", outputPreprocessorMessage.errorSeverity().get());
  EXPECT_EQ("", outputPreprocessorMessage.messageLine1().get());
  EXPECT_EQ("", outputPreprocessorMessage.messageLine2().get());
  EXPECT_EQ("", outputPreprocessorMessage.messageLine10().get());
}
