/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/RoomAirSettingsOneNodeDisplacementVentilation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirSettingsOneNodeDisplacementVentilation_DefaultConstructor) {
  Model model;
  RoomAirSettingsOneNodeDisplacementVentilation roomAirSettings(model);
  EXPECT_EQ(RoomAirSettingsOneNodeDisplacementVentilation::iddObjectType(), roomAirSettings.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirSettingsOneNodeDisplacementVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirSettingsOneNodeDisplacementVentilation roomAirSettings(model);

  EXPECT_FALSE(roomAirSettings.fractionofConvectiveInternalLoadsAddedtoFloorAir());
  EXPECT_FALSE(roomAirSettings.fractionofInfiltrationInternalLoadsAddedtoFloorAir());

  EXPECT_TRUE(roomAirSettings.setFractionofConvectiveInternalLoadsAddedtoFloorAir(0.6));
  ASSERT_TRUE(roomAirSettings.fractionofConvectiveInternalLoadsAddedtoFloorAir());
  EXPECT_DOUBLE_EQ(0.6, roomAirSettings.fractionofConvectiveInternalLoadsAddedtoFloorAir().get());

  EXPECT_TRUE(roomAirSettings.setFractionofInfiltrationInternalLoadsAddedtoFloorAir(0.25));
  ASSERT_TRUE(roomAirSettings.fractionofInfiltrationInternalLoadsAddedtoFloorAir());
  EXPECT_DOUBLE_EQ(0.25, roomAirSettings.fractionofInfiltrationInternalLoadsAddedtoFloorAir().get());

  EXPECT_FALSE(roomAirSettings.setFractionofConvectiveInternalLoadsAddedtoFloorAir(-0.01));
  EXPECT_FALSE(roomAirSettings.setFractionofInfiltrationInternalLoadsAddedtoFloorAir(1.01));

  roomAirSettings.resetFractionofConvectiveInternalLoadsAddedtoFloorAir();
  roomAirSettings.resetFractionofInfiltrationInternalLoadsAddedtoFloorAir();
  EXPECT_FALSE(roomAirSettings.fractionofConvectiveInternalLoadsAddedtoFloorAir());
  EXPECT_FALSE(roomAirSettings.fractionofInfiltrationInternalLoadsAddedtoFloorAir());
}
