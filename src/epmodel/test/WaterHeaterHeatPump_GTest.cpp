/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/WaterHeaterHeatPump.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterHeatPump_DefaultConstructor) {
  Model model;
  WaterHeaterHeatPump heatPump(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::WaterHeater_HeatPump_PumpedCondenser), heatPump.iddObject().type());
}

TEST_F(EPModelFixture, WaterHeaterHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  WaterHeaterHeatPump heatPump(model);

  EXPECT_TRUE(heatPump.setDeadBandTemperatureDifference(6.1));
  EXPECT_DOUBLE_EQ(6.1, heatPump.deadBandTemperatureDifference());
  heatPump.resetDeadBandTemperatureDifference();
  EXPECT_TRUE(heatPump.isDeadBandTemperatureDifferenceDefaulted());

  EXPECT_FALSE(heatPump.condenserWaterFlowRate());
  EXPECT_TRUE(heatPump.setCondenserWaterFlowRate(0.02));
  ASSERT_TRUE(heatPump.condenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.02, heatPump.condenserWaterFlowRate().get());
  EXPECT_FALSE(heatPump.isCondenserWaterFlowRateAutosized());
  heatPump.autosizeCondenserWaterFlowRate();
  EXPECT_TRUE(heatPump.isCondenserWaterFlowRateAutosized());
  heatPump.resetCondenserWaterFlowRate();
  EXPECT_FALSE(heatPump.condenserWaterFlowRate());

  EXPECT_FALSE(heatPump.evaporatorAirFlowRate());
  EXPECT_TRUE(heatPump.setEvaporatorAirFlowRate(0.04));
  ASSERT_TRUE(heatPump.evaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.04, heatPump.evaporatorAirFlowRate().get());
  EXPECT_FALSE(heatPump.isEvaporatorAirFlowRateAutosized());
  heatPump.autosizeEvaporatorAirFlowRate();
  EXPECT_TRUE(heatPump.isEvaporatorAirFlowRateAutosized());
  heatPump.resetEvaporatorAirFlowRate();
  EXPECT_FALSE(heatPump.evaporatorAirFlowRate());

  const auto inletOptions = WaterHeaterHeatPump::inletAirConfigurationValues();
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

  const auto compressorLocations = WaterHeaterHeatPump::compressorLocationValues();
  ASSERT_FALSE(compressorLocations.empty());
  EXPECT_TRUE(heatPump.setCompressorLocation(compressorLocations.back()));
  EXPECT_EQ(compressorLocations.back(), heatPump.compressorLocation());

  const auto fanPlacements = WaterHeaterHeatPump::fanPlacementValues();
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

  const auto parasiticLocations = WaterHeaterHeatPump::parasiticHeatRejectionLocationValues();
  ASSERT_FALSE(parasiticLocations.empty());
  EXPECT_TRUE(heatPump.setParasiticHeatRejectionLocation(parasiticLocations.front()));
  EXPECT_EQ(parasiticLocations.front(), heatPump.parasiticHeatRejectionLocation());
  heatPump.resetParasiticHeatRejectionLocation();
  EXPECT_TRUE(heatPump.isParasiticHeatRejectionLocationDefaulted());

  const auto tankControls = WaterHeaterHeatPump::tankElementControlLogicValues();
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
