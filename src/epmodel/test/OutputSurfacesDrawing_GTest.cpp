/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../scaffolds/OutputSurfacesDrawing.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputSurfacesDrawing_DefaultConstructor) {
  Model model;
  OutputSurfacesDrawing outputSurfacesDrawing(model);

  EXPECT_EQ(OutputSurfacesDrawing::iddObjectType(), outputSurfacesDrawing.iddObject().type());
  EXPECT_TRUE(outputSurfacesDrawing.isReportSpecifications1Defaulted());
  EXPECT_EQ("Triangulate3DFace", outputSurfacesDrawing.reportSpecifications1());
}

TEST_F(EPModelFixture, OutputSurfacesDrawing_ScalarAccessors_RoundTrip) {
  Model model;
  OutputSurfacesDrawing outputSurfacesDrawing(model);

  const auto reportTypeValues = OutputSurfacesDrawing::reportTypeValues();
  EXPECT_NE(reportTypeValues.end(), std::find(reportTypeValues.begin(), reportTypeValues.end(), "DXF"));
  EXPECT_NE(reportTypeValues.end(), std::find(reportTypeValues.begin(), reportTypeValues.end(), "DXF:WireFrame"));
  EXPECT_NE(reportTypeValues.end(), std::find(reportTypeValues.begin(), reportTypeValues.end(), "VRML"));

  const auto reportSpecifications1Values = OutputSurfacesDrawing::reportSpecifications1Values();
  EXPECT_NE(reportSpecifications1Values.end(), std::find(reportSpecifications1Values.begin(), reportSpecifications1Values.end(), "Triangulate3DFace"));
  EXPECT_NE(reportSpecifications1Values.end(), std::find(reportSpecifications1Values.begin(), reportSpecifications1Values.end(), "ThickPolyline"));
  EXPECT_NE(reportSpecifications1Values.end(), std::find(reportSpecifications1Values.begin(), reportSpecifications1Values.end(), "RegularPolyline"));

  EXPECT_TRUE(outputSurfacesDrawing.setReportType("DXF"));
  EXPECT_EQ("DXF", outputSurfacesDrawing.reportType());

  EXPECT_TRUE(outputSurfacesDrawing.setReportSpecifications1("RegularPolyline"));
  EXPECT_FALSE(outputSurfacesDrawing.isReportSpecifications1Defaulted());
  EXPECT_EQ("RegularPolyline", outputSurfacesDrawing.reportSpecifications1());

  EXPECT_FALSE(outputSurfacesDrawing.setReportType("BadEnum"));
  EXPECT_EQ("DXF", outputSurfacesDrawing.reportType());

  EXPECT_FALSE(outputSurfacesDrawing.setReportSpecifications1("BadEnum"));
  EXPECT_EQ("RegularPolyline", outputSurfacesDrawing.reportSpecifications1());

  outputSurfacesDrawing.resetReportSpecifications1();
  EXPECT_TRUE(outputSurfacesDrawing.isReportSpecifications1Defaulted());
  EXPECT_EQ("Triangulate3DFace", outputSurfacesDrawing.reportSpecifications1());
}
