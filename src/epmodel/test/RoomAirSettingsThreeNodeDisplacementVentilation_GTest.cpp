/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirSettingsThreeNodeDisplacementVentilation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirSettingsThreeNodeDisplacementVentilation_DefaultConstructor) {
  Model model;
  RoomAirSettingsThreeNodeDisplacementVentilation roomAirSettings(model);
  EXPECT_EQ(RoomAirSettingsThreeNodeDisplacementVentilation::iddObjectType(), roomAirSettings.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirSettingsThreeNodeDisplacementVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirSettingsThreeNodeDisplacementVentilation roomAirSettings(model);

  EXPECT_TRUE(roomAirSettings.isNumberofPlumesperOccupantDefaulted());
  EXPECT_TRUE(roomAirSettings.isThermostatHeightDefaulted());
  EXPECT_TRUE(roomAirSettings.isComfortHeightDefaulted());
  EXPECT_TRUE(roomAirSettings.isTemperatureDifferenceThresholdforReportingDefaulted());

  EXPECT_DOUBLE_EQ(1.0, roomAirSettings.numberofPlumesperOccupant());
  EXPECT_DOUBLE_EQ(1.1, roomAirSettings.thermostatHeight());
  EXPECT_DOUBLE_EQ(1.1, roomAirSettings.comfortHeight());
  EXPECT_DOUBLE_EQ(0.4, roomAirSettings.temperatureDifferenceThresholdforReporting());

  EXPECT_TRUE(roomAirSettings.setNumberofPlumesperOccupant(1.8));
  EXPECT_TRUE(roomAirSettings.setThermostatHeight(1.3));
  EXPECT_TRUE(roomAirSettings.setComfortHeight(1.25));
  EXPECT_TRUE(roomAirSettings.setTemperatureDifferenceThresholdforReporting(0.7));

  EXPECT_FALSE(roomAirSettings.isNumberofPlumesperOccupantDefaulted());
  EXPECT_FALSE(roomAirSettings.isThermostatHeightDefaulted());
  EXPECT_FALSE(roomAirSettings.isComfortHeightDefaulted());
  EXPECT_FALSE(roomAirSettings.isTemperatureDifferenceThresholdforReportingDefaulted());

  EXPECT_DOUBLE_EQ(1.8, roomAirSettings.numberofPlumesperOccupant());
  EXPECT_DOUBLE_EQ(1.3, roomAirSettings.thermostatHeight());
  EXPECT_DOUBLE_EQ(1.25, roomAirSettings.comfortHeight());
  EXPECT_DOUBLE_EQ(0.7, roomAirSettings.temperatureDifferenceThresholdforReporting());

  EXPECT_FALSE(roomAirSettings.setNumberofPlumesperOccupant(0.0));
  EXPECT_FALSE(roomAirSettings.setThermostatHeight(0.0));
  EXPECT_FALSE(roomAirSettings.setComfortHeight(0.0));
  EXPECT_FALSE(roomAirSettings.setTemperatureDifferenceThresholdforReporting(-0.1));

  roomAirSettings.resetNumberofPlumesperOccupant();
  roomAirSettings.resetThermostatHeight();
  roomAirSettings.resetComfortHeight();
  roomAirSettings.resetTemperatureDifferenceThresholdforReporting();

  EXPECT_TRUE(roomAirSettings.isNumberofPlumesperOccupantDefaulted());
  EXPECT_TRUE(roomAirSettings.isThermostatHeightDefaulted());
  EXPECT_TRUE(roomAirSettings.isComfortHeightDefaulted());
  EXPECT_TRUE(roomAirSettings.isTemperatureDifferenceThresholdforReportingDefaulted());

  EXPECT_DOUBLE_EQ(1.0, roomAirSettings.numberofPlumesperOccupant());
  EXPECT_DOUBLE_EQ(1.1, roomAirSettings.thermostatHeight());
  EXPECT_DOUBLE_EQ(1.1, roomAirSettings.comfortHeight());
  EXPECT_DOUBLE_EQ(0.4, roomAirSettings.temperatureDifferenceThresholdforReporting());
}
