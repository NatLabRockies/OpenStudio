/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirSettingsCrossVentilation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirSettingsCrossVentilation_DefaultConstructor) {
  Model model;
  RoomAirSettingsCrossVentilation roomAirSettings(model);
  EXPECT_EQ(RoomAirSettingsCrossVentilation::iddObjectType(), roomAirSettings.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirSettingsCrossVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirSettingsCrossVentilation roomAirSettings(model);

  const auto airflowRegionValues = RoomAirSettingsCrossVentilation::airflowRegionUsedforThermalComfortEvaluationValues();
  EXPECT_FALSE(airflowRegionValues.empty());
  EXPECT_TRUE(std::find(airflowRegionValues.begin(), airflowRegionValues.end(), "Jet") != airflowRegionValues.end());
  EXPECT_TRUE(std::find(airflowRegionValues.begin(), airflowRegionValues.end(), "Recirculation") != airflowRegionValues.end());

  EXPECT_FALSE(roomAirSettings.airflowRegionUsedforThermalComfortEvaluation());
  EXPECT_TRUE(roomAirSettings.setAirflowRegionUsedforThermalComfortEvaluation("Jet"));
  ASSERT_TRUE(roomAirSettings.airflowRegionUsedforThermalComfortEvaluation());
  EXPECT_EQ("Jet", roomAirSettings.airflowRegionUsedforThermalComfortEvaluation().get());

  EXPECT_TRUE(roomAirSettings.setAirflowRegionUsedforThermalComfortEvaluation("Recirculation"));
  ASSERT_TRUE(roomAirSettings.airflowRegionUsedforThermalComfortEvaluation());
  EXPECT_EQ("Recirculation", roomAirSettings.airflowRegionUsedforThermalComfortEvaluation().get());

  roomAirSettings.resetAirflowRegionUsedforThermalComfortEvaluation();
  const auto resetValue = roomAirSettings.airflowRegionUsedforThermalComfortEvaluation();
  EXPECT_TRUE(!resetValue || resetValue->empty());
}
