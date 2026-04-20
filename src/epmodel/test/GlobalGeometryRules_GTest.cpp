/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GlobalGeometryRules.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GlobalGeometryRules_DefaultConstructor) {
  Model model;
  GlobalGeometryRules globalGeometryRules(model);
  EXPECT_EQ(GlobalGeometryRules::iddObjectType(), globalGeometryRules.iddObject().type());
}

TEST_F(EPModelFixture, GlobalGeometryRules_ScalarAccessors_RoundTrip) {
  Model model;
  GlobalGeometryRules globalGeometryRules(model);

  EXPECT_TRUE(globalGeometryRules.setStartingVertexPosition("UpperLeftCorner"));
  EXPECT_EQ("UpperLeftCorner", globalGeometryRules.startingVertexPosition());

  EXPECT_TRUE(globalGeometryRules.setVertexEntryDirection("Counterclockwise"));
  EXPECT_EQ("Counterclockwise", globalGeometryRules.vertexEntryDirection());

  EXPECT_TRUE(globalGeometryRules.setCoordinateSystem("Relative"));
  EXPECT_EQ("Relative", globalGeometryRules.coordinateSystem());

  EXPECT_TRUE(globalGeometryRules.isDaylightingReferencePointCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.daylightingReferencePointCoordinateSystem());
  EXPECT_TRUE(globalGeometryRules.setDaylightingReferencePointCoordinateSystem("World"));
  EXPECT_EQ("World", globalGeometryRules.daylightingReferencePointCoordinateSystem());
  EXPECT_FALSE(globalGeometryRules.isDaylightingReferencePointCoordinateSystemDefaulted());
  globalGeometryRules.resetDaylightingReferencePointCoordinateSystem();
  EXPECT_TRUE(globalGeometryRules.isDaylightingReferencePointCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.daylightingReferencePointCoordinateSystem());

  EXPECT_TRUE(globalGeometryRules.isRectangularSurfaceCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.rectangularSurfaceCoordinateSystem());
  EXPECT_TRUE(globalGeometryRules.setRectangularSurfaceCoordinateSystem("World"));
  EXPECT_EQ("World", globalGeometryRules.rectangularSurfaceCoordinateSystem());
  EXPECT_FALSE(globalGeometryRules.isRectangularSurfaceCoordinateSystemDefaulted());
  globalGeometryRules.resetRectangularSurfaceCoordinateSystem();
  EXPECT_TRUE(globalGeometryRules.isRectangularSurfaceCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.rectangularSurfaceCoordinateSystem());

  const auto coordinateSystemValues = GlobalGeometryRules::coordinateSystemValues();
  EXPECT_FALSE(coordinateSystemValues.empty());
}
