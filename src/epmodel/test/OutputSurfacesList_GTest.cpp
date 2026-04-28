/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/OutputSurfacesList.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputSurfacesList_DefaultConstructor) {
  Model model;
  OutputSurfacesList outputSurfacesList(model);

  EXPECT_EQ(OutputSurfacesList::iddObjectType(), outputSurfacesList.iddObject().type());
  EXPECT_FALSE(outputSurfacesList.reportSpecifications());
}

TEST_F(EPModelFixture, OutputSurfacesList_ScalarAccessors_RoundTrip) {
  Model model;
  OutputSurfacesList outputSurfacesList(model);

  const auto reportTypeValues = OutputSurfacesList::reportTypeValues();
  EXPECT_NE(reportTypeValues.end(), std::find(reportTypeValues.begin(), reportTypeValues.end(), "Details"));
  EXPECT_NE(reportTypeValues.end(), std::find(reportTypeValues.begin(), reportTypeValues.end(), "Lines"));
  EXPECT_NE(reportTypeValues.end(), std::find(reportTypeValues.begin(), reportTypeValues.end(), "CostInfo"));

  const auto reportSpecificationsValues = OutputSurfacesList::reportSpecificationsValues();
  EXPECT_NE(reportSpecificationsValues.end(), std::find(reportSpecificationsValues.begin(), reportSpecificationsValues.end(), "IDF"));

  EXPECT_TRUE(outputSurfacesList.setReportType("Details"));
  EXPECT_EQ("Details", outputSurfacesList.reportType());

  EXPECT_TRUE(outputSurfacesList.setReportSpecifications("IDF"));
  ASSERT_TRUE(outputSurfacesList.reportSpecifications());
  EXPECT_EQ("IDF", outputSurfacesList.reportSpecifications().get());

  EXPECT_FALSE(outputSurfacesList.setReportType("BadEnum"));
  EXPECT_EQ("Details", outputSurfacesList.reportType());

  EXPECT_FALSE(outputSurfacesList.setReportSpecifications("BadEnum"));
  ASSERT_TRUE(outputSurfacesList.reportSpecifications());
  EXPECT_EQ("IDF", outputSurfacesList.reportSpecifications().get());

  outputSurfacesList.resetReportSpecifications();
  const auto resetReportSpecifications = outputSurfacesList.reportSpecifications();
  if (resetReportSpecifications) {
    EXPECT_TRUE(resetReportSpecifications->empty() || *resetReportSpecifications == "IDF");
  }
}
