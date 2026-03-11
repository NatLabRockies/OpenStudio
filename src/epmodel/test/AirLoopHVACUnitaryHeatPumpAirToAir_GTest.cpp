/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAir.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatPumpAirToAir::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAir_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAir unitary(model);

  EXPECT_TRUE(unitary.setSupplyAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateDuringHeatingOperation(1.2));
  ASSERT_TRUE(unitary.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.2, unitary.supplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.6));
  ASSERT_TRUE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.6, unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  unitary.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperaturefromSupplementalHeater(45.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(45.0, unitary.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  unitary.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  EXPECT_FALSE(unitary.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());
  unitary.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(unitary.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(unitary.setFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.fanPlacement());
  EXPECT_FALSE(unitary.isFanPlacementDefaulted());
  unitary.resetFanPlacement();
  EXPECT_TRUE(unitary.isFanPlacementDefaulted());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());
  EXPECT_FALSE(unitary.isDehumidificationControlTypeDefaulted());
  unitary.resetDehumidificationControlType();
  EXPECT_TRUE(unitary.isDehumidificationControlTypeDefaulted());

  EXPECT_TRUE(unitary.setDXHeatingCoilSizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, unitary.dXHeatingCoilSizingRatio());
}
