/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/PlantComponentTemperatureSource.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantComponentTemperatureSource_DefaultConstructor) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  EXPECT_EQ(PlantComponentTemperatureSource::iddObjectType(), plantComponentTemperatureSource.iddObject().type());
  EXPECT_FALSE(plantComponentTemperatureSource.nameString().empty());
  EXPECT_TRUE(plantComponentTemperatureSource.isDesignVolumeFlowRateAutosized());
  EXPECT_FALSE(plantComponentTemperatureSource.designVolumeFlowRate());
  EXPECT_EQ("Constant", plantComponentTemperatureSource.temperatureSpecificationType());
  ASSERT_TRUE(plantComponentTemperatureSource.sourceTemperature());
  EXPECT_DOUBLE_EQ(8.0, plantComponentTemperatureSource.sourceTemperature().get());
}

TEST_F(EPModelFixture, PlantComponentTemperatureSource_ScalarAccessors_RoundTrip) {
  Model model;
  PlantComponentTemperatureSource plantComponentTemperatureSource(model);

  EXPECT_TRUE(plantComponentTemperatureSource.setDesignVolumeFlowRate(0.25));
  ASSERT_TRUE(plantComponentTemperatureSource.designVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.25, plantComponentTemperatureSource.designVolumeFlowRate().get());
  EXPECT_FALSE(plantComponentTemperatureSource.isDesignVolumeFlowRateAutosized());

  plantComponentTemperatureSource.autosizeDesignVolumeFlowRate();
  EXPECT_TRUE(plantComponentTemperatureSource.isDesignVolumeFlowRateAutosized());
  EXPECT_FALSE(plantComponentTemperatureSource.designVolumeFlowRate());

  EXPECT_TRUE(plantComponentTemperatureSource.setTemperatureSpecificationType("Scheduled"));
  EXPECT_EQ("Scheduled", plantComponentTemperatureSource.temperatureSpecificationType());

  EXPECT_TRUE(plantComponentTemperatureSource.setSourceTemperature(12.5));
  ASSERT_TRUE(plantComponentTemperatureSource.sourceTemperature());
  EXPECT_DOUBLE_EQ(12.5, plantComponentTemperatureSource.sourceTemperature().get());
  plantComponentTemperatureSource.resetSourceTemperature();
  EXPECT_FALSE(plantComponentTemperatureSource.sourceTemperature());

  EXPECT_FALSE(plantComponentTemperatureSource.autosizedDesignVolumeFlowRate());
}
