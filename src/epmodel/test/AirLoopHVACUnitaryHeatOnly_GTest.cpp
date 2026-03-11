/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACUnitaryHeatOnly.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatOnly_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatOnly unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatOnly::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatOnly_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatOnly unitary(model);

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperature(48.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(48.0, unitary.maximumSupplyAirTemperature().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperatureAutosized());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperatureDefaulted());
  unitary.resetMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureDefaulted());
  unitary.autosizeMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setHeatingSupplyAirFlowRate(1.2));
  ASSERT_TRUE(unitary.heatingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, unitary.heatingSupplyAirFlowRate().get());
  unitary.autosizeHeatingSupplyAirFlowRate();
  EXPECT_TRUE(unitary.isHeatingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(unitary.setSupplyFanObjectType("Fan:OnOff"));
  EXPECT_EQ("Fan:OnOff", unitary.supplyFanObjectType());

  EXPECT_TRUE(unitary.setFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.fanPlacement());
  EXPECT_FALSE(unitary.isFanPlacementDefaulted());
  unitary.resetFanPlacement();
  EXPECT_TRUE(unitary.isFanPlacementDefaulted());

  EXPECT_TRUE(unitary.setHeatingCoilObjectType("Coil:Heating:Fuel"));
  EXPECT_EQ("Coil:Heating:Fuel", unitary.heatingCoilObjectType());
}
