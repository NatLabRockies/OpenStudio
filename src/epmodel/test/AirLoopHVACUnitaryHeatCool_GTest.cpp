/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACUnitaryHeatCool.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatCool::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCool_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCool unitary(model);

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperature(48.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(48.0, unitary.maximumSupplyAirTemperature().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperatureAutosized());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperatureDefaulted());
  unitary.resetMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureDefaulted());
  unitary.autosizeMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setCoolingSupplyAirFlowRate(1.1));
  ASSERT_TRUE(unitary.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.1, unitary.coolingSupplyAirFlowRate().get());
  unitary.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(unitary.isCoolingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(unitary.setHeatingSupplyAirFlowRate(1.2));
  ASSERT_TRUE(unitary.heatingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, unitary.heatingSupplyAirFlowRate().get());
  unitary.autosizeHeatingSupplyAirFlowRate();
  EXPECT_TRUE(unitary.isHeatingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(unitary.setNoLoadSupplyAirFlowRate(0.5));
  ASSERT_TRUE(unitary.noLoadSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, unitary.noLoadSupplyAirFlowRate().get());
  unitary.resetNoLoadSupplyAirFlowRate();
  EXPECT_FALSE(unitary.noLoadSupplyAirFlowRate());

  EXPECT_TRUE(unitary.setSupplyFanObjectType("Fan:OnOff"));
  EXPECT_EQ("Fan:OnOff", unitary.supplyFanObjectType());

  EXPECT_TRUE(unitary.setFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.fanPlacement());
  EXPECT_FALSE(unitary.isFanPlacementDefaulted());
  unitary.resetFanPlacement();
  EXPECT_TRUE(unitary.isFanPlacementDefaulted());

  EXPECT_TRUE(unitary.setHeatingCoilObjectType("Coil:Heating:Fuel"));
  EXPECT_EQ("Coil:Heating:Fuel", unitary.heatingCoilObjectType());

  EXPECT_TRUE(unitary.setCoolingCoilObjectType("Coil:Cooling:DX:SingleSpeed"));
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed", unitary.coolingCoilObjectType());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());
  EXPECT_FALSE(unitary.isDehumidificationControlTypeDefaulted());
  unitary.resetDehumidificationControlType();
  EXPECT_TRUE(unitary.isDehumidificationControlTypeDefaulted());

  EXPECT_TRUE(unitary.setReheatCoilObjectType("Coil:Heating:Electric"));
  ASSERT_TRUE(unitary.reheatCoilObjectType());
  EXPECT_EQ("Coil:Heating:Electric", unitary.reheatCoilObjectType().get());
  unitary.resetReheatCoilObjectType();
  ASSERT_TRUE(unitary.reheatCoilObjectType());
  EXPECT_TRUE(unitary.reheatCoilObjectType()->empty());
}
