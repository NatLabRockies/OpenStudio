/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"

#include <utilities/idd/OS_ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_DefaultConstructor) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);

  EXPECT_EQ(ZoneHVACEnergyRecoveryVentilator::iddObjectType(), ventilator.iddObject().type());
  EXPECT_EQ(openstudio::OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirInletNodeName, ventilator.inletPort());
  EXPECT_EQ(openstudio::OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirOutletNodeName, ventilator.outletPort());
  EXPECT_FALSE(ventilator.inletNode());
  EXPECT_FALSE(ventilator.outletNode());
  EXPECT_FALSE(ventilator.thermalZone());
  EXPECT_FALSE(ventilator.supplyAirFlowRate());
  EXPECT_TRUE(ventilator.isSupplyAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.exhaustAirFlowRate());
  EXPECT_TRUE(ventilator.isExhaustAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.000508, ventilator.ventilationRateperUnitFloorArea());
  EXPECT_DOUBLE_EQ(0.00236, ventilator.ventilationRateperOccupant());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_ThermalZoneAttachDetach) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);
  ThermalZone zone(model);

  EXPECT_TRUE(ventilator.addToThermalZone(zone));
  ASSERT_TRUE(ventilator.thermalZone());
  EXPECT_EQ(zone, ventilator.thermalZone().get());
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());

  ventilator.removeFromThermalZone();
  EXPECT_FALSE(ventilator.thermalZone());
  EXPECT_FALSE(ventilator.inletNode());
  EXPECT_FALSE(ventilator.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);

  EXPECT_TRUE(ventilator.setSupplyAirFlowRate(0.45));
  EXPECT_TRUE(ventilator.setExhaustAirFlowRate(0.35));
  EXPECT_TRUE(ventilator.setVentilationRateperUnitFloorArea(0.001));
  EXPECT_TRUE(ventilator.setVentilationRateperOccupant(0.003));

  ASSERT_TRUE(ventilator.supplyAirFlowRate());
  ASSERT_TRUE(ventilator.exhaustAirFlowRate());
  EXPECT_DOUBLE_EQ(0.45, ventilator.supplyAirFlowRate().get());
  EXPECT_DOUBLE_EQ(0.35, ventilator.exhaustAirFlowRate().get());
  EXPECT_DOUBLE_EQ(0.001, ventilator.ventilationRateperUnitFloorArea());
  EXPECT_DOUBLE_EQ(0.003, ventilator.ventilationRateperOccupant());
  EXPECT_FALSE(ventilator.isSupplyAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.isExhaustAirFlowRateAutosized());

  ventilator.autosizeSupplyAirFlowRate();
  ventilator.autosizeExhaustAirFlowRate();

  EXPECT_TRUE(ventilator.isSupplyAirFlowRateAutosized());
  EXPECT_TRUE(ventilator.isExhaustAirFlowRateAutosized());
  EXPECT_FALSE(ventilator.supplyAirFlowRate());
  EXPECT_FALSE(ventilator.exhaustAirFlowRate());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_ChildrenOrderAndContent) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);

  FanOnOff supplyFan(model);
  FanOnOff exhaustFan(model);
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ZoneHVACEnergyRecoveryVentilatorController controller(model);

  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFanName, supplyFan.handle()));
  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFanName, exhaustFan.handle()));
  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_EnergyRecoveryVentilatorFields::HeatExchangerName, heatExchanger.handle()));
  ASSERT_TRUE(ventilator.setPointer(openstudio::ZoneHVAC_EnergyRecoveryVentilatorFields::ControllerName, controller.handle()));

  const auto children = ventilator.children();
  ASSERT_EQ(4u, children.size());
  EXPECT_EQ(supplyFan.handle(), children[0].handle());
  EXPECT_EQ(exhaustFan.handle(), children[1].handle());
  EXPECT_EQ(heatExchanger.handle(), children[2].handle());
  EXPECT_EQ(controller.handle(), children[3].handle());
  EXPECT_EQ(openstudio::IddObjectType::Fan_OnOff, children[0].iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Fan_OnOff, children[1].iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent, children[2].iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::ZoneHVAC_EnergyRecoveryVentilator_Controller, children[3].iddObject().type().value());
}
