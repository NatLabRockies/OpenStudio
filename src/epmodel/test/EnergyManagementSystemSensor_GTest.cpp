/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EnergyManagementSystemSensor.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EnergyManagementSystemSensor_DefaultConstructor) {
  Model model;
  EnergyManagementSystemSensor sensor(model);
  EXPECT_EQ(EnergyManagementSystemSensor::iddObjectType(), sensor.iddObject().type());
}

TEST_F(EPModelFixture, EnergyManagementSystemSensor_ScalarAccessors_RoundTrip) {
  Model model;
  EnergyManagementSystemSensor sensor(model);

  EXPECT_TRUE(sensor.setKeyName("My Coil"));
  ASSERT_TRUE(sensor.keyName());
  EXPECT_EQ("My Coil", *sensor.keyName());
  sensor.resetKeyName();
  EXPECT_NE("My Coil", sensor.keyName().value_or(""));

  EXPECT_TRUE(sensor.setOutputVariableOrMeterName("Cooling Coil Electric Energy"));
  EXPECT_EQ("Cooling Coil Electric Energy", sensor.outputVariableOrMeterName());
}
