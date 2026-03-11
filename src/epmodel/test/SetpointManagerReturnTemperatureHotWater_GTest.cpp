/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SetpointManagerReturnTemperatureHotWater.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerReturnTemperatureHotWater_DefaultConstructor) {
  Model model;
  SetpointManagerReturnTemperatureHotWater setpointManager(model);
  EXPECT_EQ(SetpointManagerReturnTemperatureHotWater::iddObjectType(), setpointManager.iddObject().type());
}

TEST_F(EPModelFixture, SetpointManagerReturnTemperatureHotWater_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerReturnTemperatureHotWater setpointManager(model);

  EXPECT_TRUE(setpointManager.setName("Return Temperature Hot Water"));
  EXPECT_EQ("Return Temperature Hot Water", setpointManager.nameString());

  const auto returnTemperatureSetpointInputTypeValues = SetpointManagerReturnTemperatureHotWater::returnTemperatureSetpointInputTypeValues();
  EXPECT_TRUE(std::find(returnTemperatureSetpointInputTypeValues.cbegin(), returnTemperatureSetpointInputTypeValues.cend(), "Constant")
              != returnTemperatureSetpointInputTypeValues.cend());
  EXPECT_TRUE(std::find(returnTemperatureSetpointInputTypeValues.cbegin(), returnTemperatureSetpointInputTypeValues.cend(), "Scheduled")
              != returnTemperatureSetpointInputTypeValues.cend());
  EXPECT_TRUE(std::find(returnTemperatureSetpointInputTypeValues.cbegin(), returnTemperatureSetpointInputTypeValues.cend(),
                        "ReturnTemperatureSetpoint")
              != returnTemperatureSetpointInputTypeValues.cend());

  EXPECT_DOUBLE_EQ(77.0, setpointManager.minimumSupplyTemperatureSetpoint());
  EXPECT_TRUE(setpointManager.isMinimumSupplyTemperatureSetpointDefaulted());
  EXPECT_TRUE(setpointManager.setMinimumSupplyTemperatureSetpoint(76.0));
  EXPECT_DOUBLE_EQ(76.0, setpointManager.minimumSupplyTemperatureSetpoint());
  EXPECT_FALSE(setpointManager.isMinimumSupplyTemperatureSetpointDefaulted());
  setpointManager.resetMinimumSupplyTemperatureSetpoint();
  EXPECT_TRUE(setpointManager.isMinimumSupplyTemperatureSetpointDefaulted());
  EXPECT_DOUBLE_EQ(77.0, setpointManager.minimumSupplyTemperatureSetpoint());

  EXPECT_DOUBLE_EQ(82.0, setpointManager.maximumSupplyTemperatureSetpoint());
  EXPECT_TRUE(setpointManager.isMaximumSupplyTemperatureSetpointDefaulted());
  EXPECT_TRUE(setpointManager.setMaximumSupplyTemperatureSetpoint(83.5));
  EXPECT_DOUBLE_EQ(83.5, setpointManager.maximumSupplyTemperatureSetpoint());
  EXPECT_FALSE(setpointManager.isMaximumSupplyTemperatureSetpointDefaulted());
  setpointManager.resetMaximumSupplyTemperatureSetpoint();
  EXPECT_TRUE(setpointManager.isMaximumSupplyTemperatureSetpointDefaulted());
  EXPECT_DOUBLE_EQ(82.0, setpointManager.maximumSupplyTemperatureSetpoint());

  EXPECT_TRUE(setpointManager.setReturnTemperatureSetpointInputType("Constant"));
  EXPECT_EQ("Constant", setpointManager.returnTemperatureSetpointInputType());
  EXPECT_TRUE(setpointManager.setReturnTemperatureSetpointInputType("Scheduled"));
  EXPECT_EQ("Scheduled", setpointManager.returnTemperatureSetpointInputType());

  EXPECT_DOUBLE_EQ(71.0, setpointManager.returnTemperatureSetpointConstantValue());
  EXPECT_TRUE(setpointManager.isReturnTemperatureSetpointConstantValueDefaulted());
  EXPECT_TRUE(setpointManager.setReturnTemperatureSetpointConstantValue(72.0));
  EXPECT_DOUBLE_EQ(72.0, setpointManager.returnTemperatureSetpointConstantValue());
  EXPECT_FALSE(setpointManager.isReturnTemperatureSetpointConstantValueDefaulted());
  setpointManager.resetReturnTemperatureSetpointConstantValue();
  EXPECT_TRUE(setpointManager.isReturnTemperatureSetpointConstantValueDefaulted());
  EXPECT_DOUBLE_EQ(71.0, setpointManager.returnTemperatureSetpointConstantValue());
}
