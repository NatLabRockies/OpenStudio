/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXTwoStageWithHumidityControlMode.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXTwoStageWithHumidityControlMode_DefaultConstructor) {
  Model model;
  CoilCoolingDXTwoStageWithHumidityControlMode coil(model);
  EXPECT_EQ(CoilCoolingDXTwoStageWithHumidityControlMode::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(2, coil.numberofCapacityStages());
  EXPECT_EQ(1, coil.numberofEnhancedDehumidificationModes());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(0.0, coil.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, coil.basinHeaterSetpointTemperature());
  EXPECT_DOUBLE_EQ(-25.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoStageWithHumidityControlMode_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXTwoStageWithHumidityControlMode coil(model);

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(85.0));
  EXPECT_DOUBLE_EQ(85.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(12.5));
  EXPECT_DOUBLE_EQ(12.5, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(coil.setNumberofCapacityStages(2));
  EXPECT_EQ(2, coil.numberofCapacityStages());

  EXPECT_TRUE(coil.setNumberofEnhancedDehumidificationModes(1));
  EXPECT_EQ(1, coil.numberofEnhancedDehumidificationModes());

  EXPECT_TRUE(coil.setBasinHeaterCapacity(30.0));
  EXPECT_DOUBLE_EQ(30.0, coil.basinHeaterCapacity());

  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, coil.basinHeaterSetpointTemperature());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}
