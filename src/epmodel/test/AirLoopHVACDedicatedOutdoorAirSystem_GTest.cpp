/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_DefaultConstructor) {
  Model model;
  AirLoopHVACDedicatedOutdoorAirSystem doas(model);
  EXPECT_EQ(AirLoopHVACDedicatedOutdoorAirSystem::iddObjectType(), doas.iddObject().type());
  EXPECT_DOUBLE_EQ(4.5, doas.preheatDesignTemperature());
  EXPECT_DOUBLE_EQ(0.004, doas.preheatDesignHumidityRatio());
  EXPECT_DOUBLE_EQ(17.5, doas.precoolDesignTemperature());
  EXPECT_DOUBLE_EQ(0.012, doas.precoolDesignHumidityRatio());
}

TEST_F(EPModelFixture, AirLoopHVACDedicatedOutdoorAirSystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACDedicatedOutdoorAirSystem doas(model);

  EXPECT_TRUE(doas.setPreheatDesignTemperature(5.2));
  EXPECT_TRUE(doas.setPreheatDesignHumidityRatio(0.0052));
  EXPECT_TRUE(doas.setPrecoolDesignTemperature(18.1));
  EXPECT_TRUE(doas.setPrecoolDesignHumidityRatio(0.0111));

  EXPECT_DOUBLE_EQ(5.2, doas.preheatDesignTemperature());
  EXPECT_DOUBLE_EQ(0.0052, doas.preheatDesignHumidityRatio());
  EXPECT_DOUBLE_EQ(18.1, doas.precoolDesignTemperature());
  EXPECT_DOUBLE_EQ(0.0111, doas.precoolDesignHumidityRatio());
}
