/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ShadowCalculation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ShadowCalculation_DefaultConstructor) {
  Model model;
  ShadowCalculation shadowCalculation(model);
  EXPECT_EQ(ShadowCalculation::iddObjectType(), shadowCalculation.iddObject().type());
}

TEST_F(EPModelFixture, ShadowCalculation_ScalarAccessors_RoundTrip) {
  Model model;
  ShadowCalculation shadowCalculation(model);

  EXPECT_EQ("PolygonClipping", shadowCalculation.shadingCalculationMethod());
  EXPECT_EQ("Periodic", shadowCalculation.shadingCalculationUpdateFrequencyMethod());
  EXPECT_TRUE(shadowCalculation.isShadingCalculationUpdateFrequencyMethodDefaulted());
  EXPECT_EQ(20, shadowCalculation.shadingCalculationUpdateFrequency());
  EXPECT_FALSE(shadowCalculation.isShadingCalculationUpdateFrequencyDefaulted());
  EXPECT_EQ(15000, shadowCalculation.maximumFiguresInShadowOverlapCalculations());
  EXPECT_FALSE(shadowCalculation.isMaximumFiguresInShadowOverlapCalculationsDefaulted());
  EXPECT_EQ("SutherlandHodgman", shadowCalculation.polygonClippingAlgorithm());
  EXPECT_EQ(512, shadowCalculation.pixelCountingResolution());
  EXPECT_EQ("SimpleSkyDiffuseModeling", shadowCalculation.skyDiffuseModelingAlgorithm());
  EXPECT_FALSE(shadowCalculation.outputExternalShadingCalculationResults());
  EXPECT_FALSE(shadowCalculation.disableSelfShadingWithinShadingZoneGroups());
  EXPECT_FALSE(shadowCalculation.disableSelfShadingFromShadingZoneGroupstoOtherZones());

  EXPECT_TRUE(shadowCalculation.setShadingCalculationMethod("PixelCounting"));
  EXPECT_EQ("PixelCounting", shadowCalculation.shadingCalculationMethod());

  EXPECT_TRUE(shadowCalculation.setShadingCalculationUpdateFrequencyMethod("Timestep"));
  EXPECT_FALSE(shadowCalculation.isShadingCalculationUpdateFrequencyMethodDefaulted());
  EXPECT_EQ("Timestep", shadowCalculation.shadingCalculationUpdateFrequencyMethod());
  shadowCalculation.resetShadingCalculationUpdateFrequencyMethod();
  EXPECT_TRUE(shadowCalculation.isShadingCalculationUpdateFrequencyMethodDefaulted());
  EXPECT_EQ("Periodic", shadowCalculation.shadingCalculationUpdateFrequencyMethod());

  EXPECT_TRUE(shadowCalculation.setShadingCalculationUpdateFrequency(6));
  EXPECT_FALSE(shadowCalculation.isShadingCalculationUpdateFrequencyDefaulted());
  EXPECT_EQ(6, shadowCalculation.shadingCalculationUpdateFrequency());
  shadowCalculation.resetShadingCalculationUpdateFrequency();
  EXPECT_TRUE(shadowCalculation.isShadingCalculationUpdateFrequencyDefaulted());
  EXPECT_EQ(20, shadowCalculation.shadingCalculationUpdateFrequency());

  EXPECT_TRUE(shadowCalculation.setMaximumFiguresInShadowOverlapCalculations(300));
  EXPECT_FALSE(shadowCalculation.isMaximumFiguresInShadowOverlapCalculationsDefaulted());
  EXPECT_EQ(300, shadowCalculation.maximumFiguresInShadowOverlapCalculations());
  shadowCalculation.resetMaximumFiguresInShadowOverlapCalculations();
  EXPECT_TRUE(shadowCalculation.isMaximumFiguresInShadowOverlapCalculationsDefaulted());
  EXPECT_EQ(15000, shadowCalculation.maximumFiguresInShadowOverlapCalculations());

  EXPECT_TRUE(shadowCalculation.setPolygonClippingAlgorithm("ConvexWeilerAtherton"));
  EXPECT_EQ("ConvexWeilerAtherton", shadowCalculation.polygonClippingAlgorithm());
  shadowCalculation.resetPolygonClippingAlgorithm();
  EXPECT_EQ("SutherlandHodgman", shadowCalculation.polygonClippingAlgorithm());

  EXPECT_TRUE(shadowCalculation.setPixelCountingResolution(499));
  EXPECT_EQ(499, shadowCalculation.pixelCountingResolution());
  EXPECT_TRUE(shadowCalculation.setPixelCountingResolution(-3));
  EXPECT_EQ(-3, shadowCalculation.pixelCountingResolution());

  EXPECT_TRUE(shadowCalculation.setSkyDiffuseModelingAlgorithm("DetailedSkyDiffuseModeling"));
  EXPECT_EQ("DetailedSkyDiffuseModeling", shadowCalculation.skyDiffuseModelingAlgorithm());
  shadowCalculation.resetSkyDiffuseModelingAlgorithm();
  EXPECT_EQ("SimpleSkyDiffuseModeling", shadowCalculation.skyDiffuseModelingAlgorithm());

  EXPECT_TRUE(shadowCalculation.setOutputExternalShadingCalculationResults(true));
  EXPECT_TRUE(shadowCalculation.outputExternalShadingCalculationResults());

  EXPECT_TRUE(shadowCalculation.setDisableSelfShadingWithinShadingZoneGroups(true));
  EXPECT_TRUE(shadowCalculation.disableSelfShadingWithinShadingZoneGroups());

  EXPECT_TRUE(shadowCalculation.setDisableSelfShadingFromShadingZoneGroupstoOtherZones(true));
  EXPECT_TRUE(shadowCalculation.disableSelfShadingFromShadingZoneGroupstoOtherZones());

  const auto methodValues = ShadowCalculation::shadingCalculationMethodValues();
  EXPECT_NE(methodValues.end(), std::find(methodValues.begin(), methodValues.end(), "PolygonClipping"));
  EXPECT_NE(methodValues.end(), std::find(methodValues.begin(), methodValues.end(), "PixelCounting"));
}
