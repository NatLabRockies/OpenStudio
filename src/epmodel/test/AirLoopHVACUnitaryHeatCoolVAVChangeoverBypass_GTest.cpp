/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum.hpp"
#include "../Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypass_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_DefaultConstructor) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);
  EXPECT_EQ(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass::iddObjectType(), unitary.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_SecondUnitaryDoesNotReuseRenamedInternalTopology) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass firstUnitary(model);
  auto firstBypassMixerNode =
    firstUnitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName);
  auto firstBypassSplitterNode =
    firstUnitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctSplitterNodeName);
  auto firstOutdoorAirMixer =
    firstUnitary.getModelObjectTarget<OutdoorAirMixer>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName);
  ASSERT_TRUE(firstBypassMixerNode);
  ASSERT_TRUE(firstBypassSplitterNode);
  ASSERT_TRUE(firstOutdoorAirMixer);
  ASSERT_TRUE(firstUnitary.setName("First Changeover Bypass Unitary"));

  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass secondUnitary(model);
  auto secondBypassMixerNode =
    secondUnitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName);
  auto secondBypassSplitterNode =
    secondUnitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctSplitterNodeName);
  auto secondOutdoorAirMixer =
    secondUnitary.getModelObjectTarget<OutdoorAirMixer>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName);
  ASSERT_TRUE(secondBypassMixerNode);
  ASSERT_TRUE(secondBypassSplitterNode);
  ASSERT_TRUE(secondOutdoorAirMixer);
  EXPECT_NE(*firstBypassMixerNode, *secondBypassMixerNode);
  EXPECT_NE(*firstBypassSplitterNode, *secondBypassSplitterNode);
  EXPECT_NE(*firstOutdoorAirMixer, *secondOutdoorAirMixer);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_RelationshipConstructorAndChildren) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);

  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model, fan, cooling, heating);

  EXPECT_EQ(fan.handle(), unitary.supplyAirFan().handle());
  EXPECT_EQ(cooling.handle(), unitary.coolingCoil().handle());
  EXPECT_EQ(heating.handle(), unitary.heatingCoil().handle());
  EXPECT_EQ(fan.iddObject().name(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanObjectType).get());
  EXPECT_EQ(cooling.iddObject().name(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilObjectType).get());
  EXPECT_EQ(heating.iddObject().name(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilObjectType).get());
  EXPECT_EQ(OutdoorAirMixer::iddObjectType().valueDescription(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerObjectType).get());
  EXPECT_TRUE(unitary.getModelObjectTarget<OutdoorAirMixer>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName));
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).size());

  const auto children = unitary.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan.handle(), children[0].handle());
  EXPECT_EQ(cooling.handle(), children[1].handle());
  EXPECT_EQ(heating.handle(), children[2].handle());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  EXPECT_TRUE(unitary.setSystemAirFlowRateDuringCoolingOperation(1.1));
  ASSERT_TRUE(unitary.systemAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(1.1, unitary.systemAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeSystemAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isSystemAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setSystemAirFlowRateDuringHeatingOperation(1.2));
  ASSERT_TRUE(unitary.systemAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(1.2, unitary.systemAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeSystemAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isSystemAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setSystemAirFlowRateWhenNoCoolingorHeatingisNeeded(0.7));
  ASSERT_TRUE(unitary.systemAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.7, unitary.systemAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeSystemAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isSystemAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateDuringCoolingOperation(0.3));
  ASSERT_TRUE(unitary.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.3, unitary.outdoorAirFlowRateDuringCoolingOperation().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  unitary.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateDuringHeatingOperation(0.35));
  ASSERT_TRUE(unitary.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.35, unitary.outdoorAirFlowRateDuringHeatingOperation().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  unitary.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.2));
  ASSERT_TRUE(unitary.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.2, unitary.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  EXPECT_FALSE(unitary.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  unitary.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(unitary.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  EXPECT_EQ("DrawThrough", unitary.supplyAirFanPlacement());

  EXPECT_TRUE(unitary.setPriorityControlMode("ZonePriority"));
  EXPECT_EQ("ZonePriority", unitary.priorityControlMode());

  EXPECT_TRUE(unitary.setMinimumOutletAirTemperatureDuringCoolingOperation(9.5));
  EXPECT_DOUBLE_EQ(9.5, unitary.minimumOutletAirTemperatureDuringCoolingOperation());

  EXPECT_TRUE(unitary.setMaximumOutletAirTemperatureDuringHeatingOperation(48.0));
  EXPECT_DOUBLE_EQ(48.0, unitary.maximumOutletAirTemperatureDuringHeatingOperation());

  EXPECT_TRUE(unitary.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", unitary.dehumidificationControlType());

  EXPECT_TRUE(unitary.setMinimumRuntimeBeforeOperatingModeChange(0.25));
  EXPECT_DOUBLE_EQ(0.25, unitary.minimumRuntimeBeforeOperatingModeChange());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_RelationshipAccessors_RoundTrip) {
  Model model;
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);
  ScheduleConstant availability(model);
  ScheduleConstant oaMultiplier(model);
  ScheduleConstant fanMode(model);
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);

  ASSERT_TRUE(availability.setValue(0.9));
  ASSERT_TRUE(oaMultiplier.setValue(0.6));
  ASSERT_TRUE(fanMode.setValue(1.0));

  EXPECT_TRUE(unitary.setAvailabilitySchedule(availability));
  ASSERT_TRUE(unitary.availabilitySchedule());
  EXPECT_EQ(availability, unitary.availabilitySchedule().get());
  unitary.resetAvailabilitySchedule();
  EXPECT_FALSE(unitary.availabilitySchedule());

  EXPECT_TRUE(unitary.setOutdoorAirFlowRateMultiplierSchedule(oaMultiplier));
  ASSERT_TRUE(unitary.outdoorAirFlowRateMultiplierSchedule());
  EXPECT_EQ(oaMultiplier, unitary.outdoorAirFlowRateMultiplierSchedule().get());
  unitary.resetOutdoorAirFlowRateMultiplierSchedule();
  EXPECT_FALSE(unitary.outdoorAirFlowRateMultiplierSchedule());

  EXPECT_TRUE(unitary.setSupplyAirFan(fan));
  EXPECT_EQ(fan, unitary.supplyAirFan());

  EXPECT_TRUE(unitary.setSupplyAirFanOperatingModeSchedule(fanMode));
  ASSERT_TRUE(unitary.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode, unitary.supplyAirFanOperatingModeSchedule().get());
  unitary.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(unitary.supplyAirFanOperatingModeSchedule());

  EXPECT_TRUE(unitary.setCoolingCoil(cooling));
  EXPECT_EQ(cooling, unitary.coolingCoil());

  EXPECT_TRUE(unitary.setHeatingCoil(heating));
  EXPECT_EQ(heating, unitary.heatingCoil());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass supplyUnitary(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass demandUnitary(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyUnitary.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyUnitary.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyUnitary.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyUnitary.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandUnitary.addToNode(demandInletNode));
  EXPECT_FALSE(demandUnitary.airLoopHVAC());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_ConnectsBypassReturnToSameLoopZoneMixer) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVAC otherAirLoop(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(unitary.addToNode(supplyOutletNode));
  const auto plenumNode = unitary.plenumorMixerNode();
  EXPECT_FALSE(unitary.getModelObjectTarget<Node>(unitary.plenumorMixerAirPort()));
  EXPECT_FALSE(unitary.plenumorMixer());
  EXPECT_FALSE(unitary.setPlenumorMixer(otherAirLoop.zoneMixer()));

  auto zoneMixer = airLoop.zoneMixer();
  const auto originalInletCount = zoneMixer.inletModelObjects().size();
  ASSERT_TRUE(unitary.setPlenumorMixer(zoneMixer));
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(zoneMixer, unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
  ASSERT_TRUE(unitary.getModelObjectTarget<Node>(unitary.plenumorMixerAirPort()));
  EXPECT_EQ(plenumNode, *unitary.getModelObjectTarget<Node>(unitary.plenumorMixerAirPort()));
  EXPECT_EQ(originalInletCount + 1u, zoneMixer.inletModelObjects().size());
  EXPECT_EQ(plenumNode, zoneMixer.inletModelObjects().back().cast<Node>());

  EXPECT_FALSE(unitary.setPlenumorMixer(otherAirLoop.zoneMixer()));
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(zoneMixer, unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
  EXPECT_EQ(originalInletCount + 1u, zoneMixer.inletModelObjects().size());

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(zoneMixer, unitary.plenumorMixer()->cast<AirLoopHVACZoneMixer>());
  EXPECT_EQ(originalInletCount + 1u, zoneMixer.inletModelObjects().size());

  unitary.resetPlenumorMixer();
  EXPECT_FALSE(unitary.getModelObjectTarget<Node>(unitary.plenumorMixerAirPort()));
  EXPECT_FALSE(unitary.plenumorMixer());
  EXPECT_EQ(originalInletCount, zoneMixer.inletModelObjects().size());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_ConnectsBypassReturnToSameLoopReturnPlenum) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone plenumZone(model);
  AirLoopHVACReturnPlenum returnPlenum(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(unitary.addToNode(supplyOutletNode));
  ASSERT_TRUE(returnPlenum.setThermalZone(plenumZone));

  auto zoneMixer = airLoop.zoneMixer();
  const auto originalMixerInlets = zoneMixer.inletModelObjects();
  ASSERT_EQ(1u, originalMixerInlets.size());
  Node plenumOutlet(model);
  ASSERT_TRUE(returnPlenum.setInletModelObject(0u, originalMixerInlets[0]));
  ASSERT_TRUE(returnPlenum.setOutletModelObject(plenumOutlet));
  ASSERT_TRUE(zoneMixer.setInletModelObject(0u, plenumOutlet));

  ASSERT_TRUE(unitary.setPlenumorMixer(returnPlenum));
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(returnPlenum, unitary.plenumorMixer()->cast<AirLoopHVACReturnPlenum>());
  ASSERT_EQ(2u, returnPlenum.inletModelObjects().size());
  EXPECT_EQ(unitary.plenumorMixerNode(), returnPlenum.inletModelObjects().back().cast<Node>());
  EXPECT_EQ(1u, zoneMixer.inletModelObjects().size());

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(unitary.plenumorMixer());
  EXPECT_EQ(returnPlenum, unitary.plenumorMixer()->cast<AirLoopHVACReturnPlenum>());

  unitary.resetPlenumorMixer();
  EXPECT_FALSE(unitary.plenumorMixer());
  ASSERT_EQ(1u, returnPlenum.inletModelObjects().size());
  EXPECT_EQ(originalMixerInlets[0], returnPlenum.inletModelObjects()[0]);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_TopologyAndInternalNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(unitary.addToNode(supplyInletNode));

  auto unitaryInlet = unitary.inletModelObject()->optionalCast<Node>();
  auto unitaryOutlet = unitary.outletModelObject()->optionalCast<Node>();
  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto coolingInlet = cooling.inletModelObject()->optionalCast<Node>();
  auto coolingOutlet = cooling.outletModelObject()->optionalCast<Node>();
  auto heatingInlet = heating.inletModelObject()->optionalCast<Node>();
  auto heatingOutlet = heating.outletModelObject()->optionalCast<Node>();
  auto bypassMixerNode =
    unitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName);
  auto bypassSplitterNode =
    unitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctSplitterNodeName);
  auto outdoorAirMixer =
    unitary.getModelObjectTarget<OutdoorAirMixer>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName);
  ASSERT_TRUE(unitaryInlet);
  ASSERT_TRUE(unitaryOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(bypassMixerNode);
  ASSERT_TRUE(bypassSplitterNode);
  ASSERT_TRUE(outdoorAirMixer);
  ASSERT_TRUE(outdoorAirMixer->mixedAirNode());
  ASSERT_TRUE(outdoorAirMixer->returnAirNode());
  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());

  EXPECT_EQ(*outdoorAirMixer->mixedAirNode(), *coolingInlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *coolingOutlet);
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heatingInlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *heatingOutlet);
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*unitary.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*bypassMixerNode, *outdoorAirMixer->returnAirNode());
  EXPECT_EQ(*bypassSplitterNode, *fanOutlet);
  EXPECT_NE(*unitaryInlet, *coolingInlet);
  EXPECT_NE(*unitaryOutlet, *fanOutlet);
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("BlowThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.outletModelObject());
  auto bypassSplitterNode =
    unitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctSplitterNodeName);
  ASSERT_TRUE(bypassSplitterNode);

  EXPECT_EQ(*unitary.fanOutletNode(), *cooling.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.coolingCoilOutletNode(), *heating.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*unitary.heatingCoilOutletNode(), *bypassSplitterNode);
  EXPECT_NE(*unitary.heatingCoilOutletNode(), *unitary.outletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode()->setName("Custom Changeover Fan Outlet"));
  ASSERT_TRUE(unitary.coolingCoilOutletNode()->setName("Custom Changeover Cooling Outlet"));
  ASSERT_TRUE(unitary.heatingCoilOutletNode()->setName("Custom Changeover Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.fanOutletNode());
  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  EXPECT_EQ("Custom Changeover Fan Outlet", unitary.fanOutletNode()->nameString());
  EXPECT_EQ("Custom Changeover Cooling Outlet", unitary.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom Changeover Heating Outlet", unitary.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingDXSingleSpeed cooling(model);
  CoilHeatingElectric heating(model);
  AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass unitary(model);

  ASSERT_TRUE(unitary.setSupplyAirFanPlacement("DrawThrough"));
  ASSERT_TRUE(unitary.setSupplyAirFan(fan));
  ASSERT_TRUE(unitary.setCoolingCoil(cooling));
  ASSERT_TRUE(unitary.setHeatingCoil(heating));

  auto expectedCoolingOutlet = unitary.coolingCoilOutletNode();
  auto expectedHeatingOutlet = unitary.heatingCoilOutletNode();
  auto expectedFanOutlet = unitary.fanOutletNode();
  ASSERT_TRUE(expectedCoolingOutlet);
  ASSERT_TRUE(expectedHeatingOutlet);
  ASSERT_TRUE(expectedFanOutlet);

  auto unitaryInlet = unitary.inletModelObject()->optionalCast<Node>();
  auto unitaryOutlet = unitary.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(unitaryInlet);
  ASSERT_TRUE(unitaryOutlet);
  ASSERT_TRUE(cooling.setPointer(cooling.outletPort(), unitaryInlet->handle()));
  ASSERT_TRUE(heating.setPointer(heating.inletPort(), unitaryInlet->handle()));
  ASSERT_TRUE(heating.setPointer(heating.outletPort(), unitaryOutlet->handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), unitaryOutlet->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), unitaryInlet->handle()));
  auto outdoorAirMixer =
    unitary.getModelObjectTarget<OutdoorAirMixer>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName);
  ASSERT_TRUE(outdoorAirMixer);
  ASSERT_TRUE(unitary.setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanObjectType, ""));
  ASSERT_TRUE(unitary.setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilObjectType, ""));
  ASSERT_TRUE(unitary.setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilObjectType, ""));
  ASSERT_TRUE(unitary.setString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName, ""));
  ASSERT_TRUE(outdoorAirMixer->setString(openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName, ""));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(unitary.coolingCoilOutletNode());
  ASSERT_TRUE(unitary.heatingCoilOutletNode());
  ASSERT_TRUE(unitary.fanOutletNode());
  EXPECT_EQ(*expectedCoolingOutlet, *unitary.coolingCoilOutletNode());
  EXPECT_EQ(*expectedHeatingOutlet, *unitary.heatingCoilOutletNode());
  EXPECT_EQ(*expectedFanOutlet, *unitary.fanOutletNode());
  EXPECT_EQ(fan.iddObject().name(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanObjectType).get());
  EXPECT_EQ(cooling.iddObject().name(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilObjectType).get());
  EXPECT_EQ(heating.iddObject().name(),
            unitary.getString(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilObjectType).get());
  auto repairedBypassMixerNode =
    unitary.getModelObjectTarget<Node>(openstudio::AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName);
  ASSERT_TRUE(repairedBypassMixerNode);
  ASSERT_TRUE(outdoorAirMixer->returnAirNode());
  EXPECT_EQ(*repairedBypassMixerNode, *outdoorAirMixer->returnAirNode());
}
