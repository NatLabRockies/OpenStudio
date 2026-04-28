/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"

#include <utilities/idd/Fan_OnOff_FieldEnums.hxx>
#include <utilities/idd/HeatExchanger_AirToAir_SensibleAndLatent_FieldEnums.hxx>
#include <utilities/idd/OS_ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_DefaultConstructor) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);

  EXPECT_EQ(ZoneHVACEnergyRecoveryVentilator::iddObjectType(), ventilator.iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType::Schedule_Constant, ventilator.availabilitySchedule().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::HeatExchanger_AirToAir_SensibleAndLatent, ventilator.heatExchanger().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Fan_OnOff, ventilator.supplyAirFan().iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Fan_OnOff, ventilator.exhaustAirFan().iddObject().type().value());
  EXPECT_EQ(openstudio::OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirInletNodeName, ventilator.inletPort());
  EXPECT_EQ(openstudio::OS_ZoneHVAC_EnergyRecoveryVentilatorFields::AirOutletNodeName, ventilator.outletPort());
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());
  EXPECT_TRUE(ventilator.outdoorAirNode());
  EXPECT_TRUE(ventilator.supplyAirFanInletNode());
  EXPECT_TRUE(ventilator.exhaustAirFanInletNode());
  EXPECT_TRUE(ventilator.reliefAirNode());
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
  auto inlet = ventilator.inletNode();
  auto outlet = ventilator.outletNode();
  ASSERT_TRUE(inlet);
  ASSERT_TRUE(outlet);

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto inletNodes = connections->zoneAirInletNodes();
  ASSERT_EQ(1u, inletNodes.size());
  EXPECT_EQ(*outlet, inletNodes.front());
  EXPECT_TRUE(connections->zoneAirExhaustNodes().empty());
  const auto returnNodes = connections->zoneReturnAirNodes();
  ASSERT_EQ(1u, returnNodes.size());
  EXPECT_EQ(*inlet, returnNodes.front());

  ventilator.removeFromThermalZone();
  EXPECT_FALSE(ventilator.thermalZone());
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_TRUE(ventilator.inletNode());
  EXPECT_TRUE(ventilator.outletNode());
  EXPECT_TRUE(ventilator.outdoorAirNode());
  EXPECT_TRUE(ventilator.supplyAirFanInletNode());
  EXPECT_TRUE(ventilator.exhaustAirFanInletNode());
  EXPECT_TRUE(ventilator.reliefAirNode());
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

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_RelationshipsAndOwnedNodes) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);
  FanOnOff supplyFan(model);
  FanOnOff exhaustFan(model);
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  ZoneHVACEnergyRecoveryVentilatorController controller(model);
  ThermalZone zone(model);

  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setExhaustAirFan(exhaustFan));
  ASSERT_TRUE(ventilator.setHeatExchanger(heatExchanger));
  ASSERT_TRUE(ventilator.setController(controller));
  ASSERT_TRUE(ventilator.addToThermalZone(zone));

  auto zoneExhaustNode = ventilator.inletNode();
  auto zoneInletNode = ventilator.outletNode();
  auto oaNode = ventilator.outdoorAirNode();
  auto supplyFanInletNode = ventilator.supplyAirFanInletNode();
  auto exhaustFanInletNode = ventilator.exhaustAirFanInletNode();
  auto reliefNode = ventilator.reliefAirNode();
  ASSERT_TRUE(zoneExhaustNode);
  ASSERT_TRUE(zoneInletNode);
  ASSERT_TRUE(oaNode);
  ASSERT_TRUE(supplyFanInletNode);
  ASSERT_TRUE(exhaustFanInletNode);
  ASSERT_TRUE(reliefNode);

  EXPECT_EQ(*oaNode, *heatExchanger.primaryAirInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*supplyFanInletNode, *heatExchanger.primaryAirOutletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*zoneExhaustNode, *heatExchanger.secondaryAirInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*exhaustFanInletNode, *heatExchanger.secondaryAirOutletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*supplyFanInletNode, *supplyFan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*zoneInletNode, *supplyFan.outletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*exhaustFanInletNode, *exhaustFan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*reliefNode, *exhaustFan.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilator_ContainedChildTopologyEditsAreRejectedAndCanonicalizationRepairsRawDrift) {
  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);
  HeatExchangerAirToAirSensibleAndLatent heatExchanger(model);
  FanOnOff supplyFan(model);
  FanOnOff exhaustFan(model);
  ThermalZone zone(model);
  ASSERT_TRUE(ventilator.setHeatExchanger(heatExchanger));
  ASSERT_TRUE(ventilator.setSupplyAirFan(supplyFan));
  ASSERT_TRUE(ventilator.setExhaustAirFan(exhaustFan));
  ASSERT_TRUE(ventilator.addToThermalZone(zone));
  Node strayNode(model);

  auto originalZoneInlet = ventilator.outletNode();
  ASSERT_TRUE(originalZoneInlet);

  heatExchanger.disconnect();
  EXPECT_EQ(*originalZoneInlet, *ventilator.outletNode());

  ASSERT_TRUE(heatExchanger.setPointer(openstudio::HeatExchanger_AirToAir_SensibleAndLatentFields::SupplyAirOutletNodeName, strayNode.handle()));
  ASSERT_TRUE(supplyFan.setPointer(openstudio::Fan_OnOffFields::AirOutletNodeName, strayNode.handle()));

  model.canonicalize(SanitizationPolicy::Repair);

  auto repairedSupplyFanInlet = ventilator.supplyAirFanInletNode();
  auto repairedZoneInlet = ventilator.outletNode();
  ASSERT_TRUE(repairedSupplyFanInlet);
  ASSERT_TRUE(repairedZoneInlet);
  EXPECT_EQ(*repairedSupplyFanInlet, *heatExchanger.primaryAirOutletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*repairedZoneInlet, *supplyFan.outletModelObject()->optionalCast<Node>());
}
