/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SetpointManagerReturnTemperatureChilledWater.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerReturnTemperatureChilledWater_DefaultConstructor) {
  Model model;
  SetpointManagerReturnTemperatureChilledWater setpointManager(model);
  EXPECT_EQ(SetpointManagerReturnTemperatureChilledWater::iddObjectType(), setpointManager.iddObject().type());
}

TEST_F(EPModelFixture, SetpointManagerReturnTemperatureChilledWater_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerReturnTemperatureChilledWater setpointManager(model);

  EXPECT_TRUE(setpointManager.setName("Return Temperature Chilled Water"));
  EXPECT_EQ("Return Temperature Chilled Water", setpointManager.nameString());

  const auto returnTemperatureSetpointInputTypeValues = SetpointManagerReturnTemperatureChilledWater::returnTemperatureSetpointInputTypeValues();
  EXPECT_TRUE(std::find(returnTemperatureSetpointInputTypeValues.cbegin(), returnTemperatureSetpointInputTypeValues.cend(), "Constant")
              != returnTemperatureSetpointInputTypeValues.cend());
  EXPECT_TRUE(std::find(returnTemperatureSetpointInputTypeValues.cbegin(), returnTemperatureSetpointInputTypeValues.cend(), "Scheduled")
              != returnTemperatureSetpointInputTypeValues.cend());
  EXPECT_TRUE(std::find(returnTemperatureSetpointInputTypeValues.cbegin(), returnTemperatureSetpointInputTypeValues.cend(),
                        "ReturnTemperatureSetpoint")
              != returnTemperatureSetpointInputTypeValues.cend());

  EXPECT_DOUBLE_EQ(5.0, setpointManager.minimumSupplyTemperatureSetpoint());
  EXPECT_TRUE(setpointManager.isMinimumSupplyTemperatureSetpointDefaulted());
  EXPECT_TRUE(setpointManager.setMinimumSupplyTemperatureSetpoint(6.5));
  EXPECT_DOUBLE_EQ(6.5, setpointManager.minimumSupplyTemperatureSetpoint());
  EXPECT_FALSE(setpointManager.isMinimumSupplyTemperatureSetpointDefaulted());
  setpointManager.resetMinimumSupplyTemperatureSetpoint();
  EXPECT_TRUE(setpointManager.isMinimumSupplyTemperatureSetpointDefaulted());
  EXPECT_DOUBLE_EQ(5.0, setpointManager.minimumSupplyTemperatureSetpoint());

  EXPECT_DOUBLE_EQ(10.0, setpointManager.maximumSupplyTemperatureSetpoint());
  EXPECT_TRUE(setpointManager.isMaximumSupplyTemperatureSetpointDefaulted());
  EXPECT_TRUE(setpointManager.setMaximumSupplyTemperatureSetpoint(11.5));
  EXPECT_DOUBLE_EQ(11.5, setpointManager.maximumSupplyTemperatureSetpoint());
  EXPECT_FALSE(setpointManager.isMaximumSupplyTemperatureSetpointDefaulted());
  setpointManager.resetMaximumSupplyTemperatureSetpoint();
  EXPECT_TRUE(setpointManager.isMaximumSupplyTemperatureSetpointDefaulted());
  EXPECT_DOUBLE_EQ(10.0, setpointManager.maximumSupplyTemperatureSetpoint());

  EXPECT_TRUE(setpointManager.setReturnTemperatureSetpointInputType("Constant"));
  EXPECT_EQ("Constant", setpointManager.returnTemperatureSetpointInputType());
  EXPECT_TRUE(setpointManager.setReturnTemperatureSetpointInputType("Scheduled"));
  EXPECT_EQ("Scheduled", setpointManager.returnTemperatureSetpointInputType());

  EXPECT_DOUBLE_EQ(13.0, setpointManager.returnTemperatureSetpointConstantValue());
  EXPECT_TRUE(setpointManager.isReturnTemperatureSetpointConstantValueDefaulted());
  EXPECT_TRUE(setpointManager.setReturnTemperatureSetpointConstantValue(14.0));
  EXPECT_DOUBLE_EQ(14.0, setpointManager.returnTemperatureSetpointConstantValue());
  EXPECT_FALSE(setpointManager.isReturnTemperatureSetpointConstantValueDefaulted());
  setpointManager.resetReturnTemperatureSetpointConstantValue();
  EXPECT_TRUE(setpointManager.isReturnTemperatureSetpointConstantValueDefaulted());
  EXPECT_DOUBLE_EQ(13.0, setpointManager.returnTemperatureSetpointConstantValue());
}
