/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputTableReportPeriod.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputTableReportPeriod_DefaultConstructor) {
  Model model;
  OutputTableReportPeriod outputTableReportPeriod(model);

  EXPECT_EQ(OutputTableReportPeriod::iddObjectType(), outputTableReportPeriod.iddObject().type());
  EXPECT_FALSE(outputTableReportPeriod.reportName());
  EXPECT_FALSE(outputTableReportPeriod.beginYear());
  EXPECT_FALSE(outputTableReportPeriod.endYear());

  const auto reportNameValues = OutputTableReportPeriod::reportNameValues();
  EXPECT_FALSE(reportNameValues.empty());
}

TEST_F(EPModelFixture, OutputTableReportPeriod_ScalarAccessors_RoundTrip) {
  Model model;
  OutputTableReportPeriod outputTableReportPeriod(model);

  EXPECT_TRUE(outputTableReportPeriod.setReportName("ThermalResilienceSummary"));
  ASSERT_TRUE(outputTableReportPeriod.reportName());
  EXPECT_EQ("ThermalResilienceSummary", outputTableReportPeriod.reportName().get());

  EXPECT_TRUE(outputTableReportPeriod.setBeginYear(2025));
  ASSERT_TRUE(outputTableReportPeriod.beginYear());
  EXPECT_EQ(2025, outputTableReportPeriod.beginYear().get());

  EXPECT_TRUE(outputTableReportPeriod.setBeginMonth(1));
  EXPECT_TRUE(outputTableReportPeriod.setBeginDayofMonth(15));
  EXPECT_TRUE(outputTableReportPeriod.setBeginHourofDay(4));
  EXPECT_EQ(1, outputTableReportPeriod.beginMonth());
  EXPECT_EQ(15, outputTableReportPeriod.beginDayofMonth());
  EXPECT_EQ(4, outputTableReportPeriod.beginHourofDay());

  EXPECT_TRUE(outputTableReportPeriod.setEndYear(2025));
  ASSERT_TRUE(outputTableReportPeriod.endYear());
  EXPECT_EQ(2025, outputTableReportPeriod.endYear().get());

  EXPECT_TRUE(outputTableReportPeriod.setEndMonth(2));
  EXPECT_TRUE(outputTableReportPeriod.setEndDayofMonth(20));
  EXPECT_TRUE(outputTableReportPeriod.setEndHourofDay(23));
  EXPECT_EQ(2, outputTableReportPeriod.endMonth());
  EXPECT_EQ(20, outputTableReportPeriod.endDayofMonth());
  EXPECT_EQ(23, outputTableReportPeriod.endHourofDay());

  outputTableReportPeriod.resetReportName();
  outputTableReportPeriod.resetBeginYear();
  outputTableReportPeriod.resetEndYear();

  EXPECT_FALSE(outputTableReportPeriod.reportName());
  EXPECT_FALSE(outputTableReportPeriod.beginYear());
  EXPECT_FALSE(outputTableReportPeriod.endYear());
}
