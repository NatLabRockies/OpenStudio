/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/AirLoopHVACUnitarySystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitarySystem unitary(model);
  EXPECT_EQ(AirLoopHVACUnitarySystem::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitarySystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitarySystem unitary(model);

  EXPECT_TRUE(unitary.setControlType("Load"));
  EXPECT_EQ("Load", unitary.controlType());

  EXPECT_TRUE(unitary.setUseDOASDXCoolingCoil(true));
  EXPECT_TRUE(unitary.useDOASDXCoolingCoil());
  EXPECT_FALSE(unitary.isUseDOASDXCoolingCoilDefaulted());

  EXPECT_TRUE(unitary.setDOASDXCoolingCoilLeavingMinimumAirTemperature(6.2));
  EXPECT_DOUBLE_EQ(6.2, unitary.dOASDXCoolingCoilLeavingMinimumAirTemperature());
  EXPECT_FALSE(unitary.isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized());
  unitary.autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature();
  EXPECT_TRUE(unitary.isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateMethodDuringCoolingOperation("SupplyAirFlowRate"));
  EXPECT_EQ("SupplyAirFlowRate", unitary.supplyAirFlowRateMethodDuringCoolingOperation());
  EXPECT_TRUE(unitary.setSupplyAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.supplyAirFlowRateDuringCoolingOperation().get());
  unitary.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired("SupplyAirFlowRate"));
  EXPECT_TRUE(unitary.setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(0.8));
  ASSERT_TRUE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisRequired());
  EXPECT_DOUBLE_EQ(0.8, unitary.supplyAirFlowRateWhenNoCoolingorHeatingisRequired().get());
  unitary.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized());

  EXPECT_TRUE(unitary.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(false));
  EXPECT_FALSE(unitary.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperature(44.4));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(44.4, unitary.maximumSupplyAirTemperature().get());
  unitary.autosizeMaximumSupplyAirTemperature();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperatureAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.0));
  EXPECT_DOUBLE_EQ(18.0, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());

  EXPECT_TRUE(unitary.setAncilliaryOnCycleElectricPower(9.0));
  EXPECT_DOUBLE_EQ(9.0, unitary.ancilliaryOnCycleElectricPower());
  EXPECT_TRUE(unitary.setAncilliaryOffCycleElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, unitary.ancilliaryOffCycleElectricPower());
}
