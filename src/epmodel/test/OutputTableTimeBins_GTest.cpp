/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputTableTimeBins.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputTableTimeBins_DefaultConstructor) {
  Model model;
  OutputTableTimeBins outputTableTimeBins(model);

  EXPECT_EQ(OutputTableTimeBins::iddObjectType(), outputTableTimeBins.iddObject().type());
  EXPECT_TRUE(outputTableTimeBins.isKeyValueDefaulted());
  EXPECT_EQ("*", outputTableTimeBins.keyValue());
  EXPECT_FALSE(outputTableTimeBins.intervalStart());
  EXPECT_FALSE(outputTableTimeBins.intervalSize());
  EXPECT_FALSE(outputTableTimeBins.intervalCount());
  EXPECT_FALSE(outputTableTimeBins.variableType());

  const auto variableTypeValues = OutputTableTimeBins::variableTypeValues();
  EXPECT_NE(variableTypeValues.end(), std::find(variableTypeValues.begin(), variableTypeValues.end(), "Energy"));
}

TEST_F(EPModelFixture, OutputTableTimeBins_ScalarAccessors_RoundTrip) {
  Model model;
  OutputTableTimeBins outputTableTimeBins(model);

  EXPECT_TRUE(outputTableTimeBins.setKeyValue("Zone 1"));
  EXPECT_FALSE(outputTableTimeBins.isKeyValueDefaulted());
  EXPECT_EQ("Zone 1", outputTableTimeBins.keyValue());

  EXPECT_TRUE(outputTableTimeBins.setVariableName("Zone Mean Air Temperature"));
  EXPECT_EQ("Zone Mean Air Temperature", outputTableTimeBins.variableName());

  EXPECT_TRUE(outputTableTimeBins.setIntervalStart(18.5));
  EXPECT_TRUE(outputTableTimeBins.setIntervalSize(1.0));
  EXPECT_TRUE(outputTableTimeBins.setIntervalCount(5));
  ASSERT_TRUE(outputTableTimeBins.intervalStart());
  ASSERT_TRUE(outputTableTimeBins.intervalSize());
  ASSERT_TRUE(outputTableTimeBins.intervalCount());
  EXPECT_DOUBLE_EQ(18.5, outputTableTimeBins.intervalStart().get());
  EXPECT_DOUBLE_EQ(1.0, outputTableTimeBins.intervalSize().get());
  EXPECT_EQ(5, outputTableTimeBins.intervalCount().get());

  EXPECT_TRUE(outputTableTimeBins.setVariableType("Temperature"));
  ASSERT_TRUE(outputTableTimeBins.variableType());
  EXPECT_EQ("Temperature", outputTableTimeBins.variableType().get());

  EXPECT_FALSE(outputTableTimeBins.setIntervalCount(0));
  ASSERT_TRUE(outputTableTimeBins.intervalCount());
  EXPECT_EQ(5, outputTableTimeBins.intervalCount().get());

  EXPECT_FALSE(outputTableTimeBins.setVariableType("BadEnum"));
  ASSERT_TRUE(outputTableTimeBins.variableType());
  EXPECT_EQ("Temperature", outputTableTimeBins.variableType().get());

  outputTableTimeBins.resetKeyValue();
  outputTableTimeBins.resetIntervalStart();
  outputTableTimeBins.resetIntervalSize();
  outputTableTimeBins.resetIntervalCount();
  outputTableTimeBins.resetVariableType();

  EXPECT_TRUE(outputTableTimeBins.isKeyValueDefaulted());
  EXPECT_EQ("*", outputTableTimeBins.keyValue());
  EXPECT_FALSE(outputTableTimeBins.intervalStart());
  EXPECT_FALSE(outputTableTimeBins.intervalSize());
  EXPECT_FALSE(outputTableTimeBins.intervalCount());
  const auto resetVariableType = outputTableTimeBins.variableType();
  if (resetVariableType) {
    EXPECT_TRUE(*resetVariableType == "Energy" || resetVariableType->empty());
  }
}
