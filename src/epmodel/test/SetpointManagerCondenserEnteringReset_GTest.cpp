/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SetpointManagerCondenserEnteringReset.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerCondenserEnteringReset_DefaultConstructor) {
  Model model;
  SetpointManagerCondenserEnteringReset setpointManager(model);
  EXPECT_EQ(SetpointManagerCondenserEnteringReset::iddObjectType(), setpointManager.iddObject().type());
}

TEST_F(EPModelFixture, SetpointManagerCondenserEnteringReset_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerCondenserEnteringReset setpointManager(model);

  EXPECT_TRUE(setpointManager.setName("Condenser Entering Reset"));
  EXPECT_EQ("Condenser Entering Reset", setpointManager.nameString());

  EXPECT_TRUE(setpointManager.setControlVariable("Temperature"));
  EXPECT_EQ("Temperature", setpointManager.controlVariable());
  EXPECT_FALSE(setpointManager.isControlVariableDefaulted());
  setpointManager.resetControlVariable();
  EXPECT_TRUE(setpointManager.isControlVariableDefaulted());

  EXPECT_TRUE(setpointManager.setMinimumLift(7.5));
  EXPECT_DOUBLE_EQ(7.5, setpointManager.minimumLift());
  EXPECT_FALSE(setpointManager.isMinimumLiftDefaulted());
  setpointManager.resetMinimumLift();
  EXPECT_TRUE(setpointManager.isMinimumLiftDefaulted());

  EXPECT_TRUE(setpointManager.setMaximumCondenserEnteringWaterTemperature(29.0));
  EXPECT_DOUBLE_EQ(29.0, setpointManager.maximumCondenserEnteringWaterTemperature());
  EXPECT_FALSE(setpointManager.isMaximumCondenserEnteringWaterTemperatureDefaulted());
  setpointManager.resetMaximumCondenserEnteringWaterTemperature();
  EXPECT_TRUE(setpointManager.isMaximumCondenserEnteringWaterTemperatureDefaulted());

  EXPECT_TRUE(setpointManager.setCoolingTowerDesignInletAirWetBulbTemperature(24.0));
  EXPECT_DOUBLE_EQ(24.0, setpointManager.coolingTowerDesignInletAirWetBulbTemperature());
  EXPECT_FALSE(setpointManager.isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted());
  setpointManager.resetCoolingTowerDesignInletAirWetBulbTemperature();
  EXPECT_TRUE(setpointManager.isCoolingTowerDesignInletAirWetBulbTemperatureDefaulted());
}
