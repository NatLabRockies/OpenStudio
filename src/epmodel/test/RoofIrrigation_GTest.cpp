/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoofIrrigation.hpp"
#include <boost/optional/optional_io.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoofIrrigation_DefaultConstructor) {
  Model model;
  RoofIrrigation irrigation(model);
  EXPECT_EQ(RoofIrrigation::iddObjectType(), irrigation.iddObject().type());
  EXPECT_DOUBLE_EQ(40.0, irrigation.irrigationMaximumSaturationThreshold());
  EXPECT_TRUE(irrigation.isIrrigationMaximumSaturationThresholdDefaulted());
}

TEST_F(EPModelFixture, RoofIrrigation_ScalarAccessors_RoundTrip) {
  Model model;
  RoofIrrigation irrigation(model);

  const std::vector<std::string> expectedValues{"Schedule", "SmartSchedule"};
  EXPECT_EQ(expectedValues, RoofIrrigation::irrigationModelTypeValues());

  const auto initialChoice = irrigation.irrigationModelType();
  EXPECT_TRUE(irrigation.setIrrigationModelType("SmartSchedule"));
  ASSERT_TRUE(irrigation.irrigationModelType());
  EXPECT_EQ("SmartSchedule", *irrigation.irrigationModelType());
  irrigation.resetIrrigationModelType();
  if (irrigation.irrigationModelType()) {
    EXPECT_NE("SmartSchedule", *irrigation.irrigationModelType());
  }

  EXPECT_TRUE(irrigation.isIrrigationMaximumSaturationThresholdDefaulted());
  EXPECT_TRUE(irrigation.setIrrigationMaximumSaturationThreshold(55.0));
  EXPECT_FALSE(irrigation.isIrrigationMaximumSaturationThresholdDefaulted());
  EXPECT_DOUBLE_EQ(55.0, irrigation.irrigationMaximumSaturationThreshold());
  irrigation.resetIrrigationMaximumSaturationThreshold();
  EXPECT_TRUE(irrigation.isIrrigationMaximumSaturationThresholdDefaulted());
  EXPECT_DOUBLE_EQ(40.0, irrigation.irrigationMaximumSaturationThreshold());
}
