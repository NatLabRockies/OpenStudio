/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterHeatPumpWrappedCondenser_DefaultConstructor) {
  Model model;
  WaterHeaterHeatPumpWrappedCondenser heatPump(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::OS_WaterHeater_HeatPump_WrappedCondenser), heatPump.iddObject().type());
}

TEST_F(EPModelFixture, WaterHeaterHeatPumpWrappedCondenser_ScalarAccessors_RoundTrip) {
  Model model;
  WaterHeaterHeatPumpWrappedCondenser heatPump(model);

  EXPECT_TRUE(heatPump.setDeadBandTemperatureDifference(6.1));
  EXPECT_DOUBLE_EQ(6.1, heatPump.deadBandTemperatureDifference());
  heatPump.resetDeadBandTemperatureDifference();
  EXPECT_TRUE(heatPump.isDeadBandTemperatureDifferenceDefaulted());

  EXPECT_TRUE(heatPump.setCondenserBottomLocation(1.1));
  EXPECT_DOUBLE_EQ(1.1, heatPump.condenserBottomLocation());
  heatPump.resetCondenserBottomLocation();
  EXPECT_TRUE(heatPump.isCondenserBottomLocationDefaulted());

  EXPECT_TRUE(heatPump.setCondenserTopLocation(2.3));
  EXPECT_DOUBLE_EQ(2.3, heatPump.condenserTopLocation());

  EXPECT_FALSE(heatPump.evaporatorAirFlowRate());
  EXPECT_TRUE(heatPump.setEvaporatorAirFlowRate(0.15));
  ASSERT_TRUE(heatPump.evaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.15, heatPump.evaporatorAirFlowRate().get());
  EXPECT_FALSE(heatPump.isEvaporatorAirFlowRateAutocalculated());
  heatPump.autocalculateEvaporatorAirFlowRate();
  EXPECT_TRUE(heatPump.isEvaporatorAirFlowRateAutocalculated());
  heatPump.resetEvaporatorAirFlowRate();
  EXPECT_FALSE(heatPump.evaporatorAirFlowRate());

  const auto inletOptions = WaterHeaterHeatPumpWrappedCondenser::inletAirConfigurationValues();
  ASSERT_FALSE(inletOptions.empty());
  EXPECT_TRUE(heatPump.setInletAirConfiguration(inletOptions.front()));
  EXPECT_EQ(inletOptions.front(), heatPump.inletAirConfiguration());

  EXPECT_TRUE(heatPump.setMinimumInletAirTemperatureforCompressorOperation(12.4));
  EXPECT_DOUBLE_EQ(12.4, heatPump.minimumInletAirTemperatureforCompressorOperation());
  heatPump.resetMinimumInletAirTemperatureforCompressorOperation();
  EXPECT_TRUE(heatPump.isMinimumInletAirTemperatureforCompressorOperationDefaulted());

  EXPECT_TRUE(heatPump.setMaximumInletAirTemperatureforCompressorOperation(53.2));
  EXPECT_DOUBLE_EQ(53.2, heatPump.maximumInletAirTemperatureforCompressorOperation());
  heatPump.resetMaximumInletAirTemperatureforCompressorOperation();
  EXPECT_TRUE(heatPump.isMaximumInletAirTemperatureforCompressorOperationDefaulted());

  const auto compressorLocations = WaterHeaterHeatPumpWrappedCondenser::compressorLocationValues();
  ASSERT_FALSE(compressorLocations.empty());
  EXPECT_TRUE(heatPump.setCompressorLocation(compressorLocations.back()));
  EXPECT_EQ(compressorLocations.back(), heatPump.compressorLocation());

  const auto fanPlacements = WaterHeaterHeatPumpWrappedCondenser::fanPlacementValues();
  ASSERT_FALSE(fanPlacements.empty());
  EXPECT_TRUE(heatPump.setFanPlacement(fanPlacements.front()));
  EXPECT_EQ(fanPlacements.front(), heatPump.fanPlacement());
  heatPump.resetFanPlacement();
  EXPECT_TRUE(heatPump.isFanPlacementDefaulted());

  EXPECT_TRUE(heatPump.setOnCycleParasiticElectricLoad(5.5));
  EXPECT_DOUBLE_EQ(5.5, heatPump.onCycleParasiticElectricLoad());
  heatPump.resetOnCycleParasiticElectricLoad();
  EXPECT_TRUE(heatPump.isOnCycleParasiticElectricLoadDefaulted());

  EXPECT_TRUE(heatPump.setOffCycleParasiticElectricLoad(2.25));
  EXPECT_DOUBLE_EQ(2.25, heatPump.offCycleParasiticElectricLoad());
  heatPump.resetOffCycleParasiticElectricLoad();
  EXPECT_TRUE(heatPump.isOffCycleParasiticElectricLoadDefaulted());

  const auto parasiticLocations = WaterHeaterHeatPumpWrappedCondenser::parasiticHeatRejectionLocationValues();
  ASSERT_FALSE(parasiticLocations.empty());
  EXPECT_TRUE(heatPump.setParasiticHeatRejectionLocation(parasiticLocations.front()));
  EXPECT_EQ(parasiticLocations.front(), heatPump.parasiticHeatRejectionLocation());
  heatPump.resetParasiticHeatRejectionLocation();
  EXPECT_TRUE(heatPump.isParasiticHeatRejectionLocationDefaulted());

  const auto tankControls = WaterHeaterHeatPumpWrappedCondenser::tankElementControlLogicValues();
  ASSERT_FALSE(tankControls.empty());
  EXPECT_TRUE(heatPump.setTankElementControlLogic(tankControls.front()));
  EXPECT_EQ(tankControls.front(), heatPump.tankElementControlLogic());
  heatPump.resetTankElementControlLogic();
  EXPECT_TRUE(heatPump.isTankElementControlLogicDefaulted());

  EXPECT_TRUE(heatPump.setControlSensor1HeightInStratifiedTank(0.72));
  ASSERT_TRUE(heatPump.controlSensor1HeightInStratifiedTank());
  EXPECT_DOUBLE_EQ(0.72, heatPump.controlSensor1HeightInStratifiedTank().get());
  heatPump.resetControlSensor1HeightInStratifiedTank();
  EXPECT_FALSE(heatPump.controlSensor1HeightInStratifiedTank());

  EXPECT_TRUE(heatPump.setControlSensor1Weight(0.8));
  EXPECT_DOUBLE_EQ(0.8, heatPump.controlSensor1Weight());
  heatPump.resetControlSensor1Weight();
  EXPECT_TRUE(heatPump.isControlSensor1WeightDefaulted());

  EXPECT_TRUE(heatPump.setControlSensor2HeightInStratifiedTank(0.9));
  ASSERT_TRUE(heatPump.controlSensor2HeightInStratifiedTank());
  EXPECT_DOUBLE_EQ(0.9, heatPump.controlSensor2HeightInStratifiedTank().get());
  heatPump.resetControlSensor2HeightInStratifiedTank();
  EXPECT_FALSE(heatPump.controlSensor2HeightInStratifiedTank());
}
