/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "../HVACComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"

#include <utilities/idd/ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  EXPECT_FALSE(vrf.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(vrf.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoCoolingisNeeded());
  EXPECT_FALSE(vrf.isSupplyAirFlowRateWhenNoCoolingisNeededAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(vrf.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoHeatingisNeeded());
  EXPECT_FALSE(vrf.isSupplyAirFlowRateWhenNoHeatingisNeededAutosized());
  EXPECT_FALSE(vrf.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(vrf.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(vrf.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(vrf.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(vrf.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(vrf.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(vrf.isSupplyAirFanPlacementDefaulted());
  EXPECT_EQ("", vrf.supplyAirFanPlacement());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setSupplyAirFlowRateDuringCoolingOperation(0.5));
  ASSERT_TRUE(vrf.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.5, vrf.supplyAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(vrf.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  vrf.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(vrf.supplyAirFlowRateDuringCoolingOperation());

  EXPECT_TRUE(vrf.setSupplyAirFlowRateWhenNoCoolingisNeeded(0.18));
  ASSERT_TRUE(vrf.supplyAirFlowRateWhenNoCoolingisNeeded());
  EXPECT_DOUBLE_EQ(0.18, vrf.supplyAirFlowRateWhenNoCoolingisNeeded().get());
  vrf.resetSupplyAirFlowRateWhenNoCoolingisNeeded();
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoCoolingisNeeded());
  vrf.autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateWhenNoCoolingisNeededAutosized());

  EXPECT_TRUE(vrf.setSupplyAirFlowRateDuringHeatingOperation(0.45));
  ASSERT_TRUE(vrf.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.45, vrf.supplyAirFlowRateDuringHeatingOperation().get());
  vrf.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(vrf.setSupplyAirFlowRateWhenNoHeatingisNeeded(0.22));
  ASSERT_TRUE(vrf.supplyAirFlowRateWhenNoHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.22, vrf.supplyAirFlowRateWhenNoHeatingisNeeded().get());
  vrf.resetSupplyAirFlowRateWhenNoHeatingisNeeded();
  EXPECT_FALSE(vrf.supplyAirFlowRateWhenNoHeatingisNeeded());
  vrf.autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();
  EXPECT_TRUE(vrf.isSupplyAirFlowRateWhenNoHeatingisNeededAutosized());

  EXPECT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.08));
  vrf.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.03));
  vrf.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.01));
  vrf.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(vrf.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  vrf.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(vrf.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(vrf.setZoneTerminalUnitOnParasiticElectricEnergyUse(0.9));
  EXPECT_DOUBLE_EQ(0.9, vrf.zoneTerminalUnitOnParasiticElectricEnergyUse());

  EXPECT_TRUE(vrf.setZoneTerminalUnitOffParasiticElectricEnergyUse(0.6));
  EXPECT_DOUBLE_EQ(0.6, vrf.zoneTerminalUnitOffParasiticElectricEnergyUse());

  EXPECT_TRUE(vrf.setRatedTotalHeatingCapacitySizingRatio(1.05));
  EXPECT_DOUBLE_EQ(1.05, vrf.ratedTotalHeatingCapacitySizingRatio());

  EXPECT_TRUE(vrf.setMaximumSupplyAirTemperaturefromSupplementalHeater(38.2));
  ASSERT_TRUE(vrf.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(38.2, vrf.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  vrf.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(vrf.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(vrf.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(33.3));
  EXPECT_DOUBLE_EQ(33.3, vrf.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  vrf.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(vrf.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(25.0));
  EXPECT_DOUBLE_EQ(25.0, vrf.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());

  EXPECT_TRUE(vrf.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", vrf.supplyAirFanPlacement());
  vrf.resetSupplyAirFanPlacement();
  EXPECT_TRUE(vrf.isSupplyAirFanPlacementDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_TopologyAndChildren) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  EXPECT_EQ(openstudio::ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNodeName, vrf.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNodeName, vrf.outletPort());

  EXPECT_TRUE(vrf.addToThermalZone(zone));
  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  EXPECT_EQ(zone, vrf.thermalZone().get());

  vrf.removeFromThermalZone();
  EXPECT_FALSE(vrf.inletNode());
  EXPECT_FALSE(vrf.outletNode());
  EXPECT_FALSE(vrf.thermalZone());

  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);

  EXPECT_TRUE(vrf.setSupplyAirFan(fan));
  EXPECT_TRUE(vrf.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(vrf.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(fan, vrf.supplyAirFan());
  ASSERT_TRUE(vrf.coolingCoil());
  EXPECT_EQ(coolingCoil, vrf.coolingCoil().get());
  ASSERT_TRUE(vrf.heatingCoil());
  EXPECT_EQ(heatingCoil, vrf.heatingCoil().get());
  ASSERT_TRUE(vrf.supplementalHeatingCoil());
  EXPECT_EQ(supplementalHeatingCoil, vrf.supplementalHeatingCoil().get());

  const auto children = vrf.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(coolingCoil.handle(), children[1].handle());
  EXPECT_EQ(heatingCoil.handle(), children[2].handle());
  EXPECT_EQ(supplementalHeatingCoil.handle(), children[3].handle());
}
