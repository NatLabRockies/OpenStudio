/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatExchangerSurface.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerSurface_DefaultConstructor) {
  Model model;
  GroundHeatExchangerSurface ghx(model);
  EXPECT_EQ(GroundHeatExchangerSurface::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_FALSE(ghx.hydronicTubingInsideDiameter());
  EXPECT_FALSE(ghx.numberofTubingCircuits());
  EXPECT_FALSE(ghx.hydronicTubeSpacing());
  EXPECT_FALSE(ghx.surfaceLength());
  EXPECT_FALSE(ghx.surfaceWidth());
  EXPECT_TRUE(ghx.isLowerSurfaceEnvironmentDefaulted());
  EXPECT_EQ("Ground", ghx.lowerSurfaceEnvironment());
}

TEST_F(EPModelFixture, GroundHeatExchangerSurface_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerSurface ghx(model);

  EXPECT_FALSE(GroundHeatExchangerSurface::lowerSurfaceEnvironmentValues().empty());

  EXPECT_TRUE(ghx.setHydronicTubingInsideDiameter(0.025));
  ASSERT_TRUE(ghx.hydronicTubingInsideDiameter());
  EXPECT_DOUBLE_EQ(0.025, ghx.hydronicTubingInsideDiameter().get());
  ghx.resetHydronicTubingInsideDiameter();
  EXPECT_FALSE(ghx.hydronicTubingInsideDiameter());

  EXPECT_TRUE(ghx.setNumberofTubingCircuits(3));
  ASSERT_TRUE(ghx.numberofTubingCircuits());
  EXPECT_EQ(3, ghx.numberofTubingCircuits().get());
  ghx.resetNumberofTubingCircuits();
  EXPECT_FALSE(ghx.numberofTubingCircuits());

  EXPECT_TRUE(ghx.setHydronicTubeSpacing(0.15));
  ASSERT_TRUE(ghx.hydronicTubeSpacing());
  EXPECT_DOUBLE_EQ(0.15, ghx.hydronicTubeSpacing().get());
  ghx.resetHydronicTubeSpacing();
  EXPECT_FALSE(ghx.hydronicTubeSpacing());

  EXPECT_TRUE(ghx.setSurfaceLength(20.0));
  ASSERT_TRUE(ghx.surfaceLength());
  EXPECT_DOUBLE_EQ(20.0, ghx.surfaceLength().get());
  ghx.resetSurfaceLength();
  EXPECT_FALSE(ghx.surfaceLength());

  EXPECT_TRUE(ghx.setSurfaceWidth(10.0));
  ASSERT_TRUE(ghx.surfaceWidth());
  EXPECT_DOUBLE_EQ(10.0, ghx.surfaceWidth().get());
  ghx.resetSurfaceWidth();
  EXPECT_FALSE(ghx.surfaceWidth());

  EXPECT_TRUE(ghx.setLowerSurfaceEnvironment("Exposed"));
  EXPECT_FALSE(ghx.isLowerSurfaceEnvironmentDefaulted());
  EXPECT_EQ("Exposed", ghx.lowerSurfaceEnvironment());
  ghx.resetLowerSurfaceEnvironment();
  EXPECT_TRUE(ghx.isLowerSurfaceEnvironmentDefaulted());
  EXPECT_EQ("Ground", ghx.lowerSurfaceEnvironment());
}
