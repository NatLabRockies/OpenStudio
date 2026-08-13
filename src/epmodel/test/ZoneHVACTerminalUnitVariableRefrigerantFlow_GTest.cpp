/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/FanOnOff_Impl.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FieldEnums.hxx>
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
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(openstudio::ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNodeName, vrf.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNodeName, vrf.outletPort());

  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.outdoorAirMixer());
  ASSERT_TRUE(vrf.mixedAirNode());
  ASSERT_TRUE(vrf.outdoorAirNode());
  ASSERT_TRUE(vrf.reliefAirNode());

  const auto children = vrf.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(coolingCoil.handle(), children[1].handle());
  EXPECT_EQ(heatingCoil.handle(), children[2].handle());
  EXPECT_EQ(supplementalHeatingCoil.handle(), children[3].handle());
  EXPECT_EQ(vrf.outdoorAirMixer()->handle(), children[4].handle());

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  ASSERT_TRUE(supplementalHeatingCoil.containingHVACComponent());
  EXPECT_EQ(vrf, fan.containingHVACComponent().get());
  EXPECT_EQ(vrf, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(vrf, heatingCoil.containingHVACComponent().get());
  EXPECT_EQ(vrf, supplementalHeatingCoil.containingHVACComponent().get());

  ASSERT_TRUE(vrf.addToThermalZone(zone));
  ASSERT_TRUE(vrf.thermalZone());
  EXPECT_EQ(zone, vrf.thermalZone().get());

  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto supplementalInlet = supplementalHeatingCoil.inletModelObject()->optionalCast<Node>();
  auto supplementalOutlet = supplementalHeatingCoil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(supplementalInlet);
  ASSERT_TRUE(supplementalOutlet);
  auto coolingInlet = coolingCoil.getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  auto coolingOutlet = coolingCoil.getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, true);
  auto heatingInlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  auto heatingOutlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, true);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_EQ(*vrf.inletNode(), *vrf.outdoorAirMixer()->returnAirNode());
  EXPECT_EQ(vrf.mixedAirNode()->nameString(), *coolingInlet);
  EXPECT_EQ(*vrf.mixedAirNode(), *vrf.outdoorAirMixer()->mixedAirNode());
  EXPECT_EQ(*vrf.outdoorAirNode(), *vrf.outdoorAirMixer()->outdoorAirNode());
  EXPECT_EQ(*vrf.reliefAirNode(), *vrf.outdoorAirMixer()->reliefAirNode());
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *coolingOutlet);
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *heatingInlet);
  EXPECT_EQ(vrf.heatingCoilOutletNode()->nameString(), *heatingOutlet);
  EXPECT_EQ(*vrf.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*vrf.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*vrf.fanOutletNode(), *supplementalInlet);
  EXPECT_EQ(*vrf.outletNode(), *supplementalOutlet);

  vrf.removeFromThermalZone();
  EXPECT_FALSE(vrf.thermalZone());
  EXPECT_TRUE(vrf.inletNode());
  EXPECT_TRUE(vrf.outletNode());
  EXPECT_TRUE(vrf.fanOutletNode());
  EXPECT_TRUE(vrf.coolingCoilOutletNode());
  EXPECT_TRUE(vrf.heatingCoilOutletNode());
  EXPECT_TRUE(vrf.outdoorAirMixer());
  EXPECT_TRUE(vrf.mixedAirNode());
  EXPECT_TRUE(vrf.outdoorAirNode());
  EXPECT_TRUE(vrf.reliefAirNode());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_OutdoorAirMixerIsExposedWhenUsed) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.08));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.03));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.01));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.outdoorAirMixer());
  ASSERT_TRUE(vrf.mixedAirNode());
  ASSERT_TRUE(vrf.outdoorAirNode());
  ASSERT_TRUE(vrf.reliefAirNode());
  ASSERT_TRUE(vrf.outdoorAirMixer()->mixedAirNode());
  ASSERT_TRUE(vrf.outdoorAirMixer()->outdoorAirNode());
  ASSERT_TRUE(vrf.outdoorAirMixer()->reliefAirNode());
  const auto children = vrf.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(vrf.outdoorAirMixer()->handle(), children.back().handle());
  EXPECT_EQ(OutdoorAirMixer::iddObjectType(), vrf.outdoorAirMixer()->iddObjectType());
  EXPECT_EQ(*vrf.mixedAirNode(), *vrf.outdoorAirMixer()->mixedAirNode());
  EXPECT_EQ(*vrf.outdoorAirNode(), *vrf.outdoorAirMixer()->outdoorAirNode());
  EXPECT_EQ(*vrf.reliefAirNode(), *vrf.outdoorAirMixer()->reliefAirNode());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ControlRelationships_RoundTrip) {
  Model model;
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);
  ThermalZone zone(model);

  auto defaultAvailability = vrf.terminalUnitAvailabilityschedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = vrf.supplyAirFanOperatingModeSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.3));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(vrf.setTerminalUnitAvailabilityschedule(availability));
  EXPECT_TRUE(vrf.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_TRUE(vrf.setControllingZoneorThermostatLocation(zone));
  EXPECT_EQ(availability.handle(), vrf.terminalUnitAvailabilityschedule().handle());
  EXPECT_EQ(fanMode.handle(), vrf.supplyAirFanOperatingModeSchedule().handle());
  ASSERT_TRUE(vrf.controllingZoneorThermostatLocation());
  EXPECT_EQ(zone.handle(), vrf.controllingZoneorThermostatLocation()->handle());

  vrf.resetControllingZoneorThermostatLocation();
  EXPECT_FALSE(vrf.controllingZoneorThermostatLocation());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFanPlacement("BlowThrough"));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.outletNode());

  auto coolingInlet = coolingCoil.getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  auto heatingInlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(heatingInlet);
  EXPECT_EQ(vrf.fanOutletNode()->nameString(), *coolingInlet);
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *heatingInlet);
  EXPECT_EQ(*vrf.heatingCoilOutletNode(), *supplementalHeatingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*vrf.outletNode(), *supplementalHeatingCoil.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.fanOutletNode()->setName("Custom VRF Fan Outlet"));
  ASSERT_TRUE(vrf.coolingCoilOutletNode()->setName("Custom VRF Cooling Outlet"));
  ASSERT_TRUE(vrf.heatingCoilOutletNode()->setName("Custom VRF Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  EXPECT_EQ("Custom VRF Fan Outlet", vrf.fanOutletNode()->nameString());
  EXPECT_EQ("Custom VRF Cooling Outlet", vrf.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom VRF Heating Outlet", vrf.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  auto originalFanOutlet = vrf.fanOutletNode();
  auto originalCoolingOutlet = vrf.coolingCoilOutletNode();
  auto originalHeatingOutlet = vrf.heatingCoilOutletNode();
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);
  ASSERT_TRUE(originalHeatingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();

  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  coolingCoil.disconnect();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());

  heatingCoil.disconnect();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());

  supplementalHeatingCoil.disconnect();
  EXPECT_FALSE(supplementalHeatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(supplementalHeatingCoil.isRemovable());
  EXPECT_TRUE(supplementalHeatingCoil.remove().empty());

  ASSERT_TRUE(vrf.fanOutletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  EXPECT_EQ(*originalFanOutlet, *vrf.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *vrf.coolingCoilOutletNode());
  EXPECT_EQ(*originalHeatingOutlet, *vrf.heatingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanOnOff fan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow vrf(model);

  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(vrf.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(vrf.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(vrf.setSupplyAirFan(fan));
  ASSERT_TRUE(vrf.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(vrf.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(vrf.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  auto expectedInlet = vrf.inletNode();
  auto expectedOutlet = vrf.outletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);

  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue VRF Cooling Outlet"));
  Node rogueHeatingOutlet(model);
  ASSERT_TRUE(rogueHeatingOutlet.setName("Rogue VRF Heating Outlet"));
  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue VRF Fan Outlet"));

  ASSERT_TRUE(coolingCoil.setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, vrf.inletNode()->handle()));
  ASSERT_TRUE(coolingCoil.setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, rogueHeatingOutlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueHeatingOutlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.inletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.outletPort(), vrf.outletNode()->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(vrf.inletNode());
  ASSERT_TRUE(vrf.outletNode());
  ASSERT_TRUE(vrf.coolingCoilOutletNode());
  ASSERT_TRUE(vrf.heatingCoilOutletNode());
  ASSERT_TRUE(vrf.fanOutletNode());
  EXPECT_EQ(*expectedInlet, *vrf.inletNode());
  EXPECT_EQ(*expectedOutlet, *vrf.outletNode());
  EXPECT_EQ("Rogue VRF Cooling Outlet", vrf.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Rogue VRF Heating Outlet", vrf.heatingCoilOutletNode()->nameString());
  EXPECT_EQ("Rogue VRF Fan Outlet", vrf.fanOutletNode()->nameString());
  auto repairedHeatingInlet = heatingCoil.getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode, true);
  ASSERT_TRUE(repairedHeatingInlet);
  EXPECT_EQ(vrf.coolingCoilOutletNode()->nameString(), *repairedHeatingInlet);
  EXPECT_EQ(*vrf.heatingCoilOutletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*vrf.fanOutletNode(), *supplementalHeatingCoil.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*vrf.outletNode(), *supplementalHeatingCoil.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectAirLoopBranchKeepsTerminalAsPublicComponent) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone controllingZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setName("Direct VRF Terminal"));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.setControllingZoneorThermostatLocation(controllingZone));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));

  const auto supplyComponents = airLoop.supplyComponents();
  ASSERT_EQ(3u, supplyComponents.size());
  EXPECT_EQ(terminal.handle(), supplyComponents[1].handle());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  ASSERT_TRUE(terminal.controllingZoneorThermostatLocation());
  EXPECT_EQ(controllingZone.handle(), terminal.controllingZoneorThermostatLocation()->handle());

  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  ASSERT_TRUE(coolingCoil.outletModelObject());
  ASSERT_TRUE(heatingCoil.inletModelObject());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  ASSERT_TRUE(ownedFan.inletModelObject());
  ASSERT_TRUE(ownedFan.outletModelObject());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
  EXPECT_EQ(coolingCoil.outletModelObject()->handle(), heatingCoil.inletModelObject()->handle());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), ownedFan.inletModelObject()->handle());
  EXPECT_EQ(ownedFan.outletModelObject()->handle(), terminal.outletNode()->handle());

  for (const auto& component : supplyComponents) {
    EXPECT_NE(ownedFan.handle(), component.handle());
    EXPECT_NE(coolingCoil.handle(), component.handle());
    EXPECT_NE(heatingCoil.handle(), component.handle());
  }
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_AdjacentFanInsertionKeepsOwnedPathAligned) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.inletNode());
  auto originalInlet = *terminal.inletNode();

  FanSystemModel branchFan(model);
  ASSERT_TRUE(branchFan.addToNode(originalInlet));
  ASSERT_TRUE(branchFan.outletModelObject());
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(branchFan.outletModelObject()->handle(), terminal.inletNode()->handle());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());

  EXPECT_FALSE(branchFan.remove().empty());
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(originalInlet.handle(), terminal.inletNode()->handle());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectPlacementAcceptsMainBranchOutdoorAirBoundary) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));

  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  const auto supplyComponents = airLoop.supplyComponents();
  const auto oaPosition = std::ranges::find_if(supplyComponents, [&](const auto& component) { return component.handle() == oaSystem.handle(); });
  const auto terminalPosition =
    std::ranges::find_if(supplyComponents, [&](const auto& component) { return component.handle() == terminal.handle(); });
  ASSERT_NE(supplyComponents.end(), oaPosition);
  ASSERT_NE(supplyComponents.end(), terminalPosition);
  EXPECT_LT(oaPosition, terminalPosition);
  EXPECT_TRUE(std::ranges::none_of(supplyComponents, [&](const auto& component) {
    return (component.handle() == ownedFan.handle()) || (component.handle() == coolingCoil.handle()) || (component.handle() == heatingCoil.handle());
  }));
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  ASSERT_TRUE(coolingCoil.inletModelObject());
  EXPECT_EQ(terminal.inletNode()->handle(), coolingCoil.inletModelObject()->handle());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectDetachPreservesTerminalAndAllowsReattach) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone controllingZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.setControllingZoneorThermostatLocation(controllingZone));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.removeFromAirLoopHVAC());

  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletNode());
  EXPECT_FALSE(terminal.outletNode());
  EXPECT_FALSE(ownedFan.inletModelObject());
  EXPECT_FALSE(ownedFan.outletModelObject());
  EXPECT_FALSE(coolingCoil.inletModelObject());
  EXPECT_FALSE(coolingCoil.outletModelObject());
  EXPECT_FALSE(heatingCoil.inletModelObject());
  EXPECT_FALSE(heatingCoil.outletModelObject());
  ASSERT_TRUE(terminal.coolingCoil());
  ASSERT_TRUE(terminal.heatingCoil());
  EXPECT_EQ(ownedFan.handle(), terminal.supplyAirFan().handle());
  EXPECT_EQ(coolingCoil.handle(), terminal.coolingCoil()->handle());
  EXPECT_EQ(heatingCoil.handle(), terminal.heatingCoil()->handle());
  ASSERT_TRUE(terminal.controllingZoneorThermostatLocation());
  EXPECT_EQ(controllingZone.handle(), terminal.controllingZoneorThermostatLocation()->handle());

  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(3u, airLoop.supplyComponents().size());
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectPathSurvivesReloadAndRecursiveRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vrf-terminal-direct-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone controllingZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(airLoop.setName("Roundtrip VRF Air Loop"));
  ASSERT_TRUE(controllingZone.setName("Roundtrip VRF Controlling Zone"));
  ASSERT_TRUE(ownedFan.setName("Roundtrip VRF Owned Fan"));
  ASSERT_TRUE(coolingCoil.setName("Roundtrip VRF Cooling Coil"));
  ASSERT_TRUE(heatingCoil.setName("Roundtrip VRF Heating Coil"));
  ASSERT_TRUE(terminal.setName("Roundtrip VRF Terminal"));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.setControllingZoneorThermostatLocation(controllingZone));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip VRF Air Loop");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip VRF Controlling Zone");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanOnOff>("Roundtrip VRF Owned Fan");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXVariableRefrigerantFlow>("Roundtrip VRF Cooling Coil");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingDXVariableRefrigerantFlow>("Roundtrip VRF Heating Coil");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Roundtrip VRF Terminal");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedHeatingCoil);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedTerminal->airLoopHVAC());
  EXPECT_EQ(loadedAirLoop->handle(), loadedTerminal->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedTerminal->controllingZoneorThermostatLocation());
  EXPECT_EQ(loadedZone->handle(), loadedTerminal->controllingZoneorThermostatLocation()->handle());
  ASSERT_TRUE(loadedTerminal->inletNode());
  ASSERT_TRUE(loadedTerminal->outletNode());
  ASSERT_TRUE(loadedCoolingCoil->inletModelObject());
  ASSERT_TRUE(loadedCoolingCoil->outletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->inletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->outletModelObject());
  ASSERT_TRUE(loadedFan->inletModelObject());
  ASSERT_TRUE(loadedFan->outletModelObject());
  EXPECT_EQ(loadedTerminal->inletNode()->handle(), loadedCoolingCoil->inletModelObject()->handle());
  EXPECT_EQ(loadedCoolingCoil->outletModelObject()->handle(), loadedHeatingCoil->inletModelObject()->handle());
  EXPECT_EQ(loadedHeatingCoil->outletModelObject()->handle(), loadedFan->inletModelObject()->handle());
  EXPECT_EQ(loadedFan->outletModelObject()->handle(), loadedTerminal->outletNode()->handle());

  const auto terminalHandle = loadedTerminal->handle();
  const auto fanHandle = loadedFan->handle();
  const auto coolingHandle = loadedCoolingCoil->handle();
  const auto heatingHandle = loadedHeatingCoil->handle();
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(terminalHandle));
  EXPECT_FALSE(loadedModel->getObject(fanHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingHandle));
  EXPECT_FALSE(loadedModel->getObject(heatingHandle));
  EXPECT_EQ(2u, loadedAirLoop->supplyComponents().size());
  EXPECT_TRUE(loadedModel->getObject(loadedZone->handle()));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACTerminalUnitVariableRefrigerantFlow_DirectPlacementRejectsUnsupportedNodesWithoutMutation) {
  Model model;
  Model foreignModel;
  AirLoopHVAC airLoop(model);
  AirLoopHVAC foreignAirLoop(foreignModel);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  ThermalZone equipmentZone(model);
  FanOnOff ownedFan(model);
  CoilCoolingDXVariableRefrigerantFlow coolingCoil(model);
  CoilHeatingDXVariableRefrigerantFlow heatingCoil(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(terminal.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(terminal.setSupplyAirFan(ownedFan));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  const auto originalInlet = terminal.inletNode()->handle();
  const auto originalOutlet = terminal.outletNode()->handle();

  auto foreignSupplyNode = foreignAirLoop.supplyOutletNode();
  EXPECT_FALSE(terminal.addToNode(foreignSupplyNode));
  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(terminal.addToNode(demandInletNode));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(oaSystem.outboardOANode());
  auto outboardOANode = *oaSystem.outboardOANode();
  EXPECT_FALSE(terminal.addToNode(outboardOANode));

  ASSERT_TRUE(terminal.inletNode());
  ASSERT_TRUE(terminal.outletNode());
  EXPECT_EQ(originalInlet, terminal.inletNode()->handle());
  EXPECT_EQ(originalOutlet, terminal.outletNode()->handle());
  EXPECT_EQ(3u, airLoop.supplyComponents().size());

  ASSERT_TRUE(terminal.addToThermalZone(equipmentZone));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(terminal.addToNode(supplyOutletNode));
  ASSERT_TRUE(terminal.thermalZone());
  EXPECT_EQ(equipmentZone.handle(), terminal.thermalZone()->handle());
}
