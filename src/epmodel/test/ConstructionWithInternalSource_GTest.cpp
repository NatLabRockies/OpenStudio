/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../LayeredConstruction/ConstructionWithInternalSource.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ConstructionWithInternalSource_DefaultConstructor) {
  Model model;
  ConstructionWithInternalSource construction(model);
  EXPECT_EQ(ConstructionWithInternalSource::iddObjectType(), construction.iddObject().type());
}

TEST_F(EPModelFixture, ConstructionWithInternalSource_ScalarAccessors_RoundTrip) {
  Model model;
  ConstructionWithInternalSource construction(model);

  EXPECT_TRUE(construction.setSourcePresentAfterLayerNumber(1));
  EXPECT_TRUE(construction.setTemperatureCalculationRequestedAfterLayerNumber(1));
  EXPECT_TRUE(construction.setDimensionsForTheCTFCalculation(2));
  EXPECT_TRUE(construction.setTubeSpacing(0.5));

  EXPECT_TRUE(construction.isTwoDimensionalTemperatureCalculationPositionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, construction.twoDimensionalTemperatureCalculationPosition());

  EXPECT_TRUE(construction.setTwoDimensionalTemperatureCalculationPosition(0.75));
  EXPECT_FALSE(construction.isTwoDimensionalTemperatureCalculationPositionDefaulted());

  EXPECT_EQ(1, construction.sourcePresentAfterLayerNumber());
  EXPECT_EQ(1, construction.temperatureCalculationRequestedAfterLayerNumber());
  EXPECT_EQ(2, construction.dimensionsForTheCTFCalculation());
  EXPECT_DOUBLE_EQ(0.5, construction.tubeSpacing());
  EXPECT_DOUBLE_EQ(0.75, construction.twoDimensionalTemperatureCalculationPosition());

  construction.resetTwoDimensionalTemperatureCalculationPosition();
  EXPECT_TRUE(construction.isTwoDimensionalTemperatureCalculationPositionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, construction.twoDimensionalTemperatureCalculationPosition());
}
