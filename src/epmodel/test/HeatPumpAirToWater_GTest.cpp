/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/HeatPumpAirToWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpAirToWater_DefaultConstructor) {
  Model model;
  HeatPumpAirToWater hp(model);

  EXPECT_EQ(HeatPumpAirToWater::iddObjectType(), hp.iddObject().type());
  EXPECT_FALSE(hp.nameString().empty());

  EXPECT_EQ("Load", hp.operatingModeControlMethod());
  EXPECT_EQ("SingleMode", hp.operatingModeControlOptionforMultipleUnit());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_EQ("None", hp.heatPumpDefrostControl());
  EXPECT_EQ("VariableSpeed", hp.controlType());
}

TEST_F(EPModelFixture, HeatPumpAirToWater_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpAirToWater hp(model);

  EXPECT_TRUE(hp.setOperatingModeControlMethod("EMSControlled"));
  EXPECT_EQ("EMSControlled", hp.operatingModeControlMethod());

  EXPECT_TRUE(hp.setOperatingModeControlOptionforMultipleUnit("Balanced"));
  EXPECT_EQ("Balanced", hp.operatingModeControlOptionforMultipleUnit());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.21));
  EXPECT_DOUBLE_EQ(0.21, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(7.5));
  EXPECT_DOUBLE_EQ(7.5, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());

  EXPECT_TRUE(hp.setHeatPumpDefrostControl("Timed"));
  EXPECT_EQ("Timed", hp.heatPumpDefrostControl());

  EXPECT_TRUE(hp.setHeatPumpDefrostTimePeriodFraction(0.12));
  EXPECT_DOUBLE_EQ(0.12, hp.heatPumpDefrostTimePeriodFraction());

  EXPECT_TRUE(hp.setResistiveDefrostHeaterCapacity(450.0));
  EXPECT_DOUBLE_EQ(450.0, hp.resistiveDefrostHeaterCapacity());

  EXPECT_TRUE(hp.setHeatPumpMultiplier(3));
  EXPECT_EQ(3, hp.heatPumpMultiplier());

  EXPECT_TRUE(hp.setControlType("FixedSpeed"));
  EXPECT_EQ("FixedSpeed", hp.controlType());

  EXPECT_TRUE(hp.setCrankcaseHeaterCapacity(50.0));
  EXPECT_DOUBLE_EQ(50.0, hp.crankcaseHeaterCapacity());

  EXPECT_TRUE(hp.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(8.0));
  EXPECT_DOUBLE_EQ(8.0, hp.maximumAmbientTemperatureforCrankcaseHeaterOperation());

  hp.resetControlType();
  EXPECT_TRUE(hp.isControlTypeDefaulted());
  EXPECT_EQ("VariableSpeed", hp.controlType());
}
