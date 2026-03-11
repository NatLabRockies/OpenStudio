/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputDebuggingData.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputDebuggingData_DefaultConstructor) {
  Model model;
  OutputDebuggingData outputDebuggingData(model);

  EXPECT_EQ(OutputDebuggingData::iddObjectType(), outputDebuggingData.iddObject().type());
  EXPECT_FALSE(outputDebuggingData.reportDebuggingData());
  EXPECT_FALSE(outputDebuggingData.reportDuringWarmup());
}

TEST_F(EPModelFixture, OutputDebuggingData_ScalarAccessors_RoundTrip) {
  Model model;
  OutputDebuggingData outputDebuggingData(model);

  EXPECT_TRUE(outputDebuggingData.setReportDebuggingData(true));
  EXPECT_TRUE(outputDebuggingData.reportDebuggingData());
  EXPECT_FALSE(outputDebuggingData.reportDuringWarmup());

  EXPECT_TRUE(outputDebuggingData.setReportDuringWarmup(true));
  EXPECT_TRUE(outputDebuggingData.reportDuringWarmup());

  EXPECT_TRUE(outputDebuggingData.setReportDebuggingData(false));
  EXPECT_FALSE(outputDebuggingData.reportDebuggingData());
  EXPECT_TRUE(outputDebuggingData.reportDuringWarmup());

  EXPECT_TRUE(outputDebuggingData.setReportDuringWarmup(false));
  EXPECT_FALSE(outputDebuggingData.reportDuringWarmup());
}
