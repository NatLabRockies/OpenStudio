/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  EXPECT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.supplyAirFanPlacement());

  EXPECT_TRUE(unitary.setDXHeatingCoilSizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, unitary.dXHeatingCoilSizingRatio());

  EXPECT_TRUE(unitary.setMaximumSupplyAirTemperaturefromSupplementalHeater(44.0));
  ASSERT_TRUE(unitary.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(44.0, unitary.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  EXPECT_FALSE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  unitary.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(unitary.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(unitary.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, unitary.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());

  EXPECT_TRUE(unitary.setAuxiliaryOnCycleElectricPower(12.0));
  EXPECT_DOUBLE_EQ(12.0, unitary.auxiliaryOnCycleElectricPower());

  EXPECT_TRUE(unitary.setAuxiliaryOffCycleElectricPower(8.0));
  EXPECT_DOUBLE_EQ(8.0, unitary.auxiliaryOffCycleElectricPower());

  EXPECT_TRUE(unitary.setDesignHeatRecoveryWaterFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, unitary.designHeatRecoveryWaterFlowRate());

  EXPECT_TRUE(unitary.setMaximumTemperatureforHeatRecovery(75.0));
  EXPECT_DOUBLE_EQ(75.0, unitary.maximumTemperatureforHeatRecovery());

  EXPECT_TRUE(unitary.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.55));
  ASSERT_TRUE(unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.55, unitary.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setNumberofSpeedsforHeating(3));
  EXPECT_EQ(3, unitary.numberofSpeedsforHeating());

  EXPECT_TRUE(unitary.setNumberofSpeedsforCooling(4));
  EXPECT_EQ(4, unitary.numberofSpeedsforCooling());

  EXPECT_TRUE(unitary.setSpeed1SupplyAirFlowRateDuringHeatingOperation(0.7));
  ASSERT_TRUE(unitary.speed1SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.7, unitary.speed1SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed1SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed1SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed2SupplyAirFlowRateDuringHeatingOperation(0.8));
  ASSERT_TRUE(unitary.speed2SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.8, unitary.speed2SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed2SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed2SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed3SupplyAirFlowRateDuringHeatingOperation(0.9));
  ASSERT_TRUE(unitary.speed3SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.9, unitary.speed3SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed3SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed3SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed4SupplyAirFlowRateDuringHeatingOperation(1.0));
  ASSERT_TRUE(unitary.speed4SupplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.0, unitary.speed4SupplyAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSpeed4SupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSpeed4SupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed1SupplyAirFlowRateDuringCoolingOperation(0.75));
  ASSERT_TRUE(unitary.speed1SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.75, unitary.speed1SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed1SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed1SupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed2SupplyAirFlowRateDuringCoolingOperation(0.85));
  ASSERT_TRUE(unitary.speed2SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.85, unitary.speed2SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed2SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed2SupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed3SupplyAirFlowRateDuringCoolingOperation(0.95));
  ASSERT_TRUE(unitary.speed3SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.95, unitary.speed3SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed3SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed3SupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSpeed4SupplyAirFlowRateDuringCoolingOperation(1.05));
  ASSERT_TRUE(unitary.speed4SupplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.05, unitary.speed4SupplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSpeed4SupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSpeed4SupplyAirFlowRateDuringCoolingOperationAutosized());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  auto supplyInlet = airLoop.supplyInletNode();
  EXPECT_TRUE(unitary.addToNode(supplyInlet));

  const auto supplyComponents = airLoop.supplyComponents(openstudio::IddObjectType::AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeed);
  ASSERT_EQ(1u, supplyComponents.size());
  EXPECT_EQ(unitary, supplyComponents.front());

  auto loop = unitary.airLoopHVAC();
  ASSERT_TRUE(loop);
  EXPECT_EQ(airLoop, *loop);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed_AddToNodeRejectsDemand) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed unitary(model);

  auto demandInlet = airLoop.demandInletNode();
  EXPECT_FALSE(unitary.addToNode(demandInlet));
  EXPECT_FALSE(unitary.airLoopHVAC());
}
