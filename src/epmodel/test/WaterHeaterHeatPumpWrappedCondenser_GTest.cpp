/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "../ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterHeatPumpWrappedCondenser_DefaultConstructor) {
  Model model;
  WaterHeaterHeatPumpWrappedCondenser heatPump(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::WaterHeater_HeatPump_WrappedCondenser), heatPump.iddObject().type());
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

TEST_F(EPModelFixture, WaterHeaterHeatPumpWrappedCondenser_DefaultChildrenSchedulesAndNodeHelpers) {
  Model model;
  WaterHeaterHeatPumpWrappedCondenser heatPump(model);

  auto availability = heatPump.availabilitySchedule();
  ASSERT_TRUE(availability);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), availability->iddObject().type());

  auto compressorSetpoint = heatPump.compressorSetpointTemperatureSchedule();
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), compressorSetpoint.iddObject().type());

  auto inletMixer = heatPump.inletAirMixerSchedule();
  ASSERT_TRUE(inletMixer);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Schedule_Constant), inletMixer->iddObject().type());

  auto tank = heatPump.tank();
  auto dxCoil = heatPump.dXCoil();
  auto fan = heatPump.fan();
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::WaterHeater_Stratified), tank.iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_WaterHeating_AirToWaterHeatPump_Wrapped), dxCoil.iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Fan_OnOff), fan.iddObject().type());

  const auto children = heatPump.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(tank.handle(), children[0].handle());
  EXPECT_EQ(dxCoil.handle(), children[1].handle());
  EXPECT_EQ(fan.handle(), children[2].handle());

  EXPECT_FALSE(heatPump.airInletNodeName().empty());
  EXPECT_FALSE(heatPump.airOutletNodeName().empty());
}

TEST_F(EPModelFixture, WaterHeaterHeatPumpWrappedCondenser_OwnedAirPathTracksConfigurationAndRejectsChildDisconnect) {
  Model model;
  WaterHeaterStratified tank(model);
  CoilWaterHeatingAirToWaterHeatPumpWrapped dxCoil(model);
  FanOnOff fan(model);
  WaterHeaterHeatPumpWrappedCondenser heatPump(model);

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
  auto coilInlet = dxCoil.inletModelObject()->optionalCast<Node>();
  auto coilOutlet = dxCoil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coilInlet);
  ASSERT_TRUE(coilOutlet);

  EXPECT_EQ(*heatPump.mixedAirNode(), *fanInlet);
  EXPECT_EQ(*heatPump.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*heatPump.fanOutletNode(), *coilInlet);
  EXPECT_NE(*heatPump.fanOutletNode(), *coilOutlet);

  fan.disconnect();
  auto fanInletAfter = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutletAfter = fan.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInletAfter);
  ASSERT_TRUE(fanOutletAfter);
  EXPECT_EQ(*heatPump.mixedAirNode(), *fanInletAfter);
  EXPECT_EQ(*heatPump.fanOutletNode(), *fanOutletAfter);

  dxCoil.disconnect();
  auto coilInletAfter = dxCoil.inletModelObject()->optionalCast<Node>();
  auto coilOutletAfter = dxCoil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(coilInletAfter);
  ASSERT_TRUE(coilOutletAfter);
  EXPECT_EQ(*coilInlet, *coilInletAfter);
  EXPECT_EQ(*coilOutlet, *coilOutletAfter);

  ASSERT_TRUE(heatPump.setInletAirConfiguration("OutdoorAirOnly"));
  EXPECT_TRUE(heatPump.airInletNodeName().empty());
  EXPECT_TRUE(heatPump.airOutletNodeName().empty());
}

TEST_F(EPModelFixture, WaterHeaterHeatPumpWrappedCondenser_CanonicalizeRepairsOwnedAirPath) {
  Model model;
  WaterHeaterStratified tank(model);
  CoilWaterHeatingAirToWaterHeatPumpWrapped dxCoil(model);
  FanOnOff fan(model);
  WaterHeaterHeatPumpWrappedCondenser heatPump(model);

  ASSERT_TRUE(heatPump.setTank(tank));
  ASSERT_TRUE(heatPump.setDXCoil(dxCoil));
  ASSERT_TRUE(heatPump.setFan(fan));
  ASSERT_TRUE(heatPump.setInletAirConfiguration("ZoneAirOnly"));
  ASSERT_TRUE(heatPump.setFanPlacement("BlowThrough"));

  auto expectedInlet = heatPump.inletNode();
  auto expectedOutlet = heatPump.outletNode();
  auto expectedFanOutlet = heatPump.fanOutletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  ASSERT_TRUE(expectedFanOutlet);

  Node rogueFanInlet(model);
  Node rogueFanOutlet(model);
  Node rogueCoilInlet(model);
  Node rogueCoilOutlet(model);

  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueFanInlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(dxCoil.setPointer(dxCoil.inletPort(), rogueCoilInlet.handle()));
  ASSERT_TRUE(dxCoil.setPointer(dxCoil.outletPort(), rogueCoilOutlet.handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  auto fanInletAfter = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutletAfter = fan.outletModelObject()->optionalCast<Node>();
  auto coilInletAfter = dxCoil.inletModelObject()->optionalCast<Node>();
  auto coilOutletAfter = dxCoil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInletAfter);
  ASSERT_TRUE(fanOutletAfter);
  ASSERT_TRUE(coilInletAfter);
  ASSERT_TRUE(coilOutletAfter);

  EXPECT_EQ(*expectedInlet, *fanInletAfter);
  EXPECT_EQ(*fanOutletAfter, *coilInletAfter);
  EXPECT_EQ(*expectedOutlet, *coilOutletAfter);
}
