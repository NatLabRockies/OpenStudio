/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/OutputTableSummaryReports.hpp"

#include <utilities/idd/Output_Table_SummaryReports_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputTableSummaryReports_DefaultConstructor) {
  Model model;
  OutputTableSummaryReports outputTableSummaryReports(model);
  EXPECT_EQ(OutputTableSummaryReports::iddObjectType(), outputTableSummaryReports.iddObject().type());
}

TEST_F(EPModelFixture, OutputTableSummaryReports_ScalarAccessors_RoundTrip) {
  Model model;
  OutputTableSummaryReports outputTableSummaryReports(model);

  auto eg = outputTableSummaryReports.pushExtensibleGroup();
  ASSERT_TRUE(eg.setString(openstudio::Output_Table_SummaryReportsExtensibleFields::ReportName, "AllSummary"));

  auto summaryReport = eg.getString(openstudio::Output_Table_SummaryReportsExtensibleFields::ReportName, true);
  ASSERT_TRUE(summaryReport);
  EXPECT_EQ("AllSummary", summaryReport.get());
}
