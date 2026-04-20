/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WaterUseRainCollector.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterUseRainCollector_DefaultConstructor) {
  Model model;
  WaterUseRainCollector collector(model);
  EXPECT_EQ(WaterUseRainCollector::iddObjectType(), collector.iddObject().type());
}

TEST_F(EPModelFixture, WaterUseRainCollector_ScalarAccessors_RoundTrip) {
  Model model;
  WaterUseRainCollector collector(model);

  EXPECT_TRUE(collector.setLossFactorMode("Scheduled"));
  ASSERT_TRUE(collector.lossFactorMode());
  EXPECT_EQ("Scheduled", *collector.lossFactorMode());

  EXPECT_TRUE(collector.setCollectionLossFactor(0.12));
  ASSERT_TRUE(collector.collectionLossFactor());
  EXPECT_DOUBLE_EQ(0.12, *collector.collectionLossFactor());

  EXPECT_TRUE(collector.setMaximumCollectionRate(0.01));
  ASSERT_TRUE(collector.maximumCollectionRate());
  EXPECT_DOUBLE_EQ(0.01, *collector.maximumCollectionRate());
}
