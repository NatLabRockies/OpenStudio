/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"
#include "../WaterToAirComponent/WaterToAirComponent.hpp"
#include "../WaterToWaterComponent/WaterHeaterMixed.hpp"
#include "../WaterToWaterComponent/WaterToWaterComponent.hpp"
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

TEST_F(EPModelFixture, WaterHeaterHeatPump_DefaultChildrenSchedulesAndOwnedNodes) {
  Model model;
  WaterHeaterHeatPump heatPump(model);

  auto availability = heatPump.availabilitySchedule();
  ASSERT_TRUE(availability);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), availability->iddObject().type());

  auto compressorSetpoint = heatPump.compressorSetpointTemperatureSchedule();
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), compressorSetpoint.iddObject().type());

  auto inletMixer = heatPump.inletAirMixerSchedule();
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), inletMixer.iddObject().type());

  auto inletAirTemperature = heatPump.inletAirTemperatureSchedule();
  ASSERT_TRUE(inletAirTemperature);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), inletAirTemperature->iddObject().type());
  auto inletAirHumidity = heatPump.inletAirHumiditySchedule();
  ASSERT_TRUE(inletAirHumidity);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), inletAirHumidity->iddObject().type());
  auto compressorAmbient = heatPump.compressorAmbientTemperatureSchedule();
  ASSERT_TRUE(compressorAmbient);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), compressorAmbient->iddObject().type());

  auto tank = heatPump.tank();
  auto dxCoil = heatPump.dXCoil();
  auto fan = heatPump.fan();
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::WaterHeater_Mixed), tank.iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Pumped), dxCoil.iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_OnOff), fan.iddObject().type());

  const auto children = heatPump.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(tank.handle(), children[0].handle());
  EXPECT_EQ(dxCoil.handle(), children[1].handle());
  EXPECT_EQ(fan.handle(), children[2].handle());

  ASSERT_TRUE(heatPump.condenserWaterInletNode());
  ASSERT_TRUE(heatPump.condenserWaterOutletNode());
  EXPECT_FALSE(heatPump.condenserWaterInletNode()->nameString().empty());
  EXPECT_FALSE(heatPump.condenserWaterOutletNode()->nameString().empty());

  EXPECT_TRUE(fan.containingHVACComponent());
  EXPECT_EQ(heatPump, *fan.containingHVACComponent());
}

TEST_F(EPModelFixture, WaterHeaterHeatPump_OwnedAirPathTracksConfigurationAndRejectsChildDisconnect) {
  Model model;
  WaterHeaterMixed tank(model);
  CoilWaterHeatingAirToWaterHeatPump dxCoil(model);
  FanOnOff fan(model);
  WaterHeaterHeatPump heatPump(model);

  ASSERT_TRUE(heatPump.setTank(tank));
  ASSERT_TRUE(heatPump.setDXCoil(dxCoil));
  ASSERT_TRUE(heatPump.setFan(fan));

  ASSERT_TRUE(heatPump.setInletAirConfiguration("ZoneAndOutdoorAir"));
  ASSERT_TRUE(heatPump.setFanPlacement("BlowThrough"));

  ASSERT_TRUE(heatPump.mixedAirNode());
  ASSERT_TRUE(heatPump.outdoorAirNode());
  ASSERT_TRUE(heatPump.reliefAirNode());
  ASSERT_TRUE(heatPump.fanOutletNode());
  ASSERT_TRUE(heatPump.outletNode());

  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto coilAirInlet = dxCoil.airInletModelObject()->optionalCast<Node>();
  auto coilAirOutlet = dxCoil.airOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coilAirInlet);
  ASSERT_TRUE(coilAirOutlet);

  EXPECT_EQ(*heatPump.mixedAirNode(), *fanInlet);
  EXPECT_EQ(*heatPump.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*heatPump.fanOutletNode(), *coilAirInlet);
  EXPECT_NE(*heatPump.fanOutletNode(), *coilAirOutlet);

  fan.disconnect();
  auto fanInletAfter = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutletAfter = fan.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInletAfter);
  ASSERT_TRUE(fanOutletAfter);
  EXPECT_EQ(*heatPump.mixedAirNode(), *fanInletAfter);
  EXPECT_EQ(*heatPump.fanOutletNode(), *fanOutletAfter);

  dxCoil.disconnectAirSide();
  auto coilAirInletAfter = dxCoil.airInletModelObject()->optionalCast<Node>();
  auto coilAirOutletAfter = dxCoil.airOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(coilAirInletAfter);
  ASSERT_TRUE(coilAirOutletAfter);
  EXPECT_EQ(*coilAirInlet, *coilAirInletAfter);
  EXPECT_EQ(*coilAirOutlet, *coilAirOutletAfter);
}

TEST_F(EPModelFixture, WaterHeaterHeatPump_CanonicalizeRepairsOwnedTopology) {
  Model model;
  WaterHeaterMixed tank(model);
  CoilWaterHeatingAirToWaterHeatPump dxCoil(model);
  FanOnOff fan(model);
  WaterHeaterHeatPump heatPump(model);

  ASSERT_TRUE(heatPump.setTank(tank));
  ASSERT_TRUE(heatPump.setDXCoil(dxCoil));
  ASSERT_TRUE(heatPump.setFan(fan));
  ASSERT_TRUE(heatPump.setInletAirConfiguration("ZoneAirOnly"));
  ASSERT_TRUE(heatPump.setFanPlacement("BlowThrough"));

  auto expectedInlet = heatPump.inletNode();
  auto expectedOutlet = heatPump.outletNode();
  auto expectedFanOutlet = heatPump.fanOutletNode();
  auto expectedCondenserInlet = heatPump.condenserWaterInletNode();
  auto expectedCondenserOutlet = heatPump.condenserWaterOutletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  ASSERT_TRUE(expectedFanOutlet);
  ASSERT_TRUE(expectedCondenserInlet);
  ASSERT_TRUE(expectedCondenserOutlet);

  Node rogueFanInlet(model);
  Node rogueFanOutlet(model);
  Node rogueCoilAirInlet(model);
  Node rogueCoilAirOutlet(model);
  Node rogueCondenserInlet(model);
  Node rogueCondenserOutlet(model);

  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueFanInlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(dxCoil.setPointer(dxCoil.airInletPort(), rogueCoilAirInlet.handle()));
  ASSERT_TRUE(dxCoil.setPointer(dxCoil.airOutletPort(), rogueCoilAirOutlet.handle()));
  ASSERT_TRUE(dxCoil.setPointer(dxCoil.waterInletPort(), rogueCondenserInlet.handle()));
  ASSERT_TRUE(dxCoil.setPointer(dxCoil.waterOutletPort(), rogueCondenserOutlet.handle()));
  ASSERT_TRUE(tank.setPointer(tank.demandOutletPort(), rogueCondenserInlet.handle()));
  ASSERT_TRUE(tank.setPointer(tank.demandInletPort(), rogueCondenserOutlet.handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  auto fanInletAfter = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutletAfter = fan.outletModelObject()->optionalCast<Node>();
  auto coilAirInletAfter = dxCoil.airInletModelObject()->optionalCast<Node>();
  auto coilAirOutletAfter = dxCoil.airOutletModelObject()->optionalCast<Node>();
  auto coilWaterInletAfter = dxCoil.waterInletModelObject()->optionalCast<Node>();
  auto coilWaterOutletAfter = dxCoil.waterOutletModelObject()->optionalCast<Node>();
  auto tankDemandOutletAfter = tank.demandOutletModelObject()->optionalCast<Node>();
  auto tankDemandInletAfter = tank.demandInletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInletAfter);
  ASSERT_TRUE(fanOutletAfter);
  ASSERT_TRUE(coilAirInletAfter);
  ASSERT_TRUE(coilAirOutletAfter);
  ASSERT_TRUE(coilWaterInletAfter);
  ASSERT_TRUE(coilWaterOutletAfter);
  ASSERT_TRUE(tankDemandOutletAfter);
  ASSERT_TRUE(tankDemandInletAfter);

  EXPECT_EQ(*expectedInlet, *fanInletAfter);
  EXPECT_EQ(*fanOutletAfter, *coilAirInletAfter);
  EXPECT_EQ(*expectedOutlet, *coilAirOutletAfter);
  EXPECT_EQ(*expectedCondenserInlet, *coilWaterInletAfter);
  EXPECT_EQ(*expectedCondenserOutlet, *coilWaterOutletAfter);
  EXPECT_EQ(*expectedCondenserInlet, *tankDemandOutletAfter);
  EXPECT_EQ(*expectedCondenserOutlet, *tankDemandInletAfter);
}
