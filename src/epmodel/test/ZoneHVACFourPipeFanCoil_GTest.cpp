/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../ZoneHVACComponent/ZoneHVACFourPipeFanCoil.hpp"
#include <utilities/idd/ZoneHVAC_FourPipeFanCoil_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_ZoneHVACFourPipeFanCoil_DefaultConstructor) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  EXPECT_EQ(ZoneHVACFourPipeFanCoil::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  const auto capacityMethods = ZoneHVACFourPipeFanCoil::capacityControlMethodValues();
  ASSERT_FALSE(capacityMethods.empty());
  EXPECT_TRUE(coil.setCapacityControlMethod(capacityMethods.front()));
  EXPECT_EQ(capacityMethods.front(), coil.capacityControlMethod());

  EXPECT_TRUE(coil.setMaximumSupplyAirFlowRate(1.2));
  ASSERT_TRUE(coil.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, coil.maximumSupplyAirFlowRate().get());
  coil.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(coil.isMaximumSupplyAirFlowRateAutosized());

  EXPECT_TRUE(coil.setLowSpeedSupplyAirFlowRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, coil.lowSpeedSupplyAirFlowRatio());
  coil.resetLowSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isLowSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMediumSpeedSupplyAirFlowRatio(0.6));
  EXPECT_DOUBLE_EQ(0.6, coil.mediumSpeedSupplyAirFlowRatio());
  coil.resetMediumSpeedSupplyAirFlowRatio();
  EXPECT_TRUE(coil.isMediumSpeedSupplyAirFlowRatioDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorAirFlowRate(0.45));
  coil.autosizeMaximumOutdoorAirFlowRate();
  EXPECT_TRUE(coil.isMaximumOutdoorAirFlowRateAutosized());

  const auto mixerTypes = ZoneHVACFourPipeFanCoil::outdoorAirMixerObjectTypeValues();
  ASSERT_FALSE(mixerTypes.empty());
  EXPECT_TRUE(coil.setOutdoorAirMixerObjectType(mixerTypes.front()));
  EXPECT_EQ(mixerTypes.front(), coil.outdoorAirMixerObjectType());

  EXPECT_TRUE(coil.setMaximumColdWaterFlowRate(0.18));
  coil.autosizeMaximumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumColdWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumColdWaterFlowRate(0.08));
  EXPECT_DOUBLE_EQ(0.08, coil.minimumColdWaterFlowRate());
  coil.resetMinimumColdWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumColdWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setCoolingConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, coil.coolingConvergenceTolerance());
  coil.resetCoolingConvergenceTolerance();
  EXPECT_TRUE(coil.isCoolingConvergenceToleranceDefaulted());

  EXPECT_TRUE(coil.setMaximumHotWaterFlowRate(0.25));
  coil.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMaximumHotWaterFlowRateAutosized());

  EXPECT_TRUE(coil.setMinimumHotWaterFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, coil.minimumHotWaterFlowRate());
  coil.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(coil.isMinimumHotWaterFlowRateDefaulted());

  EXPECT_TRUE(coil.setHeatingConvergenceTolerance(0.003));
  EXPECT_DOUBLE_EQ(0.003, coil.heatingConvergenceTolerance());
  coil.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(coil.isHeatingConvergenceToleranceDefaulted());

  coil.autosizeMinimumSupplyAirTemperatureInCoolingMode();
  EXPECT_TRUE(coil.isMinimumSupplyAirTemperatureInCoolingModeAutosized());

  coil.autosizeMaximumSupplyAirTemperatureInHeatingMode();
  EXPECT_TRUE(coil.isMaximumSupplyAirTemperatureInHeatingModeAutosized());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ChildrenAndZoneTopology) {
  Model model;
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil coil(model);
  ThermalZone zone(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  ASSERT_TRUE(coil.inletNode());
  ASSERT_TRUE(coil.outletNode());
  ASSERT_TRUE(coil.fanOutletNode());
  ASSERT_TRUE(coil.coolingCoilOutletNode());

  const auto children = coil.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(fan, children[0]);
  EXPECT_EQ(coolingCoil, children[1]);
  EXPECT_EQ(heatingCoil, children[2]);

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  EXPECT_EQ(coil, fan.containingHVACComponent().get());
  EXPECT_EQ(coil, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(coil, heatingCoil.containingHVACComponent().get());

  ASSERT_TRUE(coil.addToThermalZone(zone));
  ASSERT_TRUE(coil.thermalZone());
  EXPECT_EQ(zone, coil.thermalZone().get());

  coil.removeFromThermalZone();
  EXPECT_FALSE(coil.thermalZone());
  EXPECT_TRUE(coil.inletNode());
  EXPECT_TRUE(coil.outletNode());
  EXPECT_TRUE(coil.fanOutletNode());
  EXPECT_TRUE(coil.coolingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);

  auto defaultSchedule = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact outdoorAir(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.3));
  ASSERT_TRUE(outdoorAir.setToConstantValue(0.4));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_TRUE(coil.setOutdoorAirSchedule(outdoorAir));
  EXPECT_TRUE(coil.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.outdoorAirSchedule());
  EXPECT_EQ(outdoorAir.handle(), coil.outdoorAirSchedule()->handle());
  ASSERT_TRUE(coil.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode.handle(), coil.supplyAirFanOperatingModeSchedule()->handle());

  coil.resetOutdoorAirSchedule();
  EXPECT_FALSE(coil.outdoorAirSchedule());
  coil.resetSupplyAirFanOperatingModeSchedule();
  EXPECT_FALSE(coil.supplyAirFanOperatingModeSchedule());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_HvacRelationships_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  EXPECT_TRUE(coil.setSupplyAirFan(fan));
  EXPECT_TRUE(coil.setCoolingCoil(coolingCoil));
  EXPECT_TRUE(coil.setHeatingCoil(heatingCoil));
  EXPECT_EQ(fan.handle(), coil.supplyAirFan().handle());
  EXPECT_EQ(coolingCoil.handle(), coil.coolingCoil().handle());
  EXPECT_EQ(heatingCoil.handle(), coil.heatingCoil().handle());

  auto fanType = coil.getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, true);
  auto coolingType = coil.getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, true);
  auto heatingType = coil.getString(openstudio::ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, true);
  ASSERT_TRUE(fanType);
  ASSERT_TRUE(coolingType);
  ASSERT_TRUE(heatingType);
  EXPECT_EQ(fan.iddObject().name(), *fanType);
  EXPECT_EQ(coolingCoil.iddObject().name(), *coolingType);
  EXPECT_EQ(heatingCoil.iddObject().name(), *heatingType);
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ContainedNodePath_RoundTrip) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  auto coilInlet = coil.inletNode();
  auto coilOutlet = coil.outletNode();
  auto fanOutletNode = coil.fanOutletNode();
  auto coolingOutletNode = coil.coolingCoilOutletNode();
  auto fanInlet = fan.inletModelObject();
  auto fanOutlet = fan.outletModelObject();
  auto coolingInlet = coolingCoil.airInletModelObject();
  auto coolingOutlet = coolingCoil.airOutletModelObject();
  auto heatingInlet = heatingCoil.airInletModelObject();
  auto heatingOutlet = heatingCoil.airOutletModelObject();

  ASSERT_TRUE(coilInlet);
  ASSERT_TRUE(coilOutlet);
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coolingOutletNode);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);

  EXPECT_EQ(*coilInlet, *fanInlet->optionalCast<Node>());
  EXPECT_EQ(*fanOutletNode, *fanOutlet->optionalCast<Node>());
  EXPECT_EQ(*fanOutletNode, *coolingInlet->optionalCast<Node>());
  EXPECT_EQ(*coolingOutletNode, *coolingOutlet->optionalCast<Node>());
  EXPECT_EQ(*coolingOutletNode, *heatingInlet->optionalCast<Node>());
  EXPECT_EQ(*coilOutlet, *heatingOutlet->optionalCast<Node>());
  EXPECT_NE(*coilInlet, *fanOutletNode);
  EXPECT_NE(*fanOutletNode, *coolingOutletNode);
  EXPECT_NE(*coolingOutletNode, *coilOutlet);

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  EXPECT_EQ(coil, fan.containingHVACComponent().get());
  EXPECT_EQ(coil, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(coil, heatingCoil.containingHVACComponent().get());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_NodeRolesMayAliasBoundaryNodes) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));

  ASSERT_TRUE(coil.fanOutletNode());
  ASSERT_TRUE(coil.coolingCoilOutletNode());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *coolingCoil.airOutletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *coil.outletNode());

  Model model2;
  ZoneHVACFourPipeFanCoil fanOnlyCoil(model2);
  FanConstantVolume loneFan(model2);
  ASSERT_TRUE(fanOnlyCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanOnlyCoil.setSupplyAirFan(loneFan));
  ASSERT_TRUE(fanOnlyCoil.fanOutletNode());
  EXPECT_EQ(*fanOnlyCoil.inletNode(), *loneFan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*fanOnlyCoil.fanOutletNode(), *fanOnlyCoil.outletNode());
  EXPECT_FALSE(fanOnlyCoil.coolingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  ASSERT_TRUE(coil.fanOutletNode());
  ASSERT_TRUE(coil.coolingCoilOutletNode());
  ASSERT_TRUE(coil.fanOutletNode()->setName("Custom Four Pipe Fan Outlet"));
  ASSERT_TRUE(coil.coolingCoilOutletNode()->setName("Custom Four Pipe Cooling Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  EXPECT_EQ("Custom Four Pipe Fan Outlet", coil.fanOutletNode()->nameString());
  EXPECT_EQ("Custom Four Pipe Cooling Outlet", coil.coolingCoilOutletNode()->nameString());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  auto originalInlet = coil.inletNode();
  auto originalFanOutlet = coil.fanOutletNode();
  auto originalCoolingOutlet = coil.coolingCoilOutletNode();
  ASSERT_TRUE(originalInlet);
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();

  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  coolingCoil.disconnectAirSide();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop, coolingCoil.plantLoop().get());
  coolingCoil.disconnect();
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(plantLoop, coolingCoil.plantLoop().get());

  heatingCoil.disconnectAirSide();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());

  EXPECT_EQ(*originalInlet, *coil.inletNode());
  EXPECT_EQ(*originalFanOutlet, *coil.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *coil.coolingCoilOutletNode());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_PlantAttachedOwnedChildLifecycle) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop hotWaterLoop(model);
  FanConstantVolume fan(model);
  CoilCoolingWater originalCoolingCoil(model);
  CoilCoolingWater replacementCoolingCoil(model);
  CoilHeatingWater heatingCoil(model);
  ZoneHVACFourPipeFanCoil fanCoil(model);

  ASSERT_TRUE(fanCoil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(fanCoil.setSupplyAirFan(fan));
  ASSERT_TRUE(fanCoil.setCoolingCoil(originalCoolingCoil));
  ASSERT_TRUE(fanCoil.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(originalCoolingCoil));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(originalCoolingCoil.plantLoop());
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop, originalCoolingCoil.plantLoop().get());
  EXPECT_EQ(hotWaterLoop, heatingCoil.plantLoop().get());
  EXPECT_FALSE(originalCoolingCoil.isRemovable());
  EXPECT_FALSE(heatingCoil.isRemovable());

  ASSERT_TRUE(fanCoil.setCoolingCoil(replacementCoolingCoil));
  EXPECT_TRUE(originalCoolingCoil.isRemovable());
  ASSERT_TRUE(originalCoolingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop, originalCoolingCoil.plantLoop().get());
  EXPECT_TRUE(chilledWaterLoop.demandComponent(originalCoolingCoil.handle()));
  EXPECT_FALSE(replacementCoolingCoil.isRemovable());

  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(replacementCoolingCoil));
  ASSERT_TRUE(replacementCoolingCoil.plantLoop());
  EXPECT_EQ(chilledWaterLoop, replacementCoolingCoil.plantLoop().get());

  const auto fanCoilHandle = fanCoil.handle();
  const auto fanHandle = fan.handle();
  const auto originalCoolingCoilHandle = originalCoolingCoil.handle();
  const auto replacementCoolingCoilHandle = replacementCoolingCoil.handle();
  const auto heatingCoilHandle = heatingCoil.handle();

  EXPECT_FALSE(fanCoil.remove().empty());
  EXPECT_FALSE(model.getObject(fanCoilHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_TRUE(model.getObject(originalCoolingCoilHandle));
  EXPECT_FALSE(model.getObject(replacementCoolingCoilHandle));
  EXPECT_FALSE(model.getObject(heatingCoilHandle));
  EXPECT_TRUE(chilledWaterLoop.demandComponent(originalCoolingCoilHandle));
  EXPECT_FALSE(chilledWaterLoop.demandComponent(replacementCoolingCoilHandle));
  EXPECT_FALSE(hotWaterLoop.demandComponent(heatingCoilHandle));
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_OwnerMutationsRebuildContainedPathWithoutSalvage) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  Node rogueMixedAir(model);
  ASSERT_TRUE(rogueMixedAir.setName("Rogue Four Pipe Mixed Air"));
  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue Four Pipe Fan Outlet"));
  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue Four Pipe Cooling Outlet"));

  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueMixedAir.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airInletPort(), rogueCoolingOutlet.handle()));

  CoilCoolingWater replacementCoolingCoil(model);
  ASSERT_TRUE(coil.setCoolingCoil(replacementCoolingCoil));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));

  EXPECT_NE("Rogue Four Pipe Mixed Air", coil.inletNode()->nameString());
  EXPECT_NE("Rogue Four Pipe Fan Outlet", coil.fanOutletNode()->nameString());
  EXPECT_NE("Rogue Four Pipe Cooling Outlet", coil.coolingCoilOutletNode()->nameString());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACFourPipeFanCoil_CanonicalizeRepairsContainedNodePath) {
  Model model;
  ZoneHVACFourPipeFanCoil coil(model);
  FanConstantVolume fan(model);
  CoilCoolingWater coolingCoil(model);
  CoilHeatingWater heatingCoil(model);

  ASSERT_TRUE(coil.setCapacityControlMethod("ConstantFanVariableFlow"));
  ASSERT_TRUE(coil.setSupplyAirFan(fan));
  ASSERT_TRUE(coil.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(coil.setHeatingCoil(heatingCoil));

  auto expectedInlet = coil.inletNode();
  auto expectedOutlet = coil.outletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);

  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue Four Pipe Fan Outlet"));
  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue Four Pipe Cooling Outlet"));

  ASSERT_TRUE(fan.setPointer(fan.inletPort(), coil.inletNode()->handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airInletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airOutletPort(), expectedInlet->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  EXPECT_EQ(*expectedInlet, *coil.inletNode());
  EXPECT_EQ("Rogue Four Pipe Fan Outlet", coil.fanOutletNode()->nameString());
  EXPECT_EQ("Rogue Four Pipe Cooling Outlet", coil.coolingCoilOutletNode()->nameString());
  EXPECT_EQ(*coil.inletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*coil.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*expectedOutlet, *heatingCoil.airOutletModelObject()->optionalCast<Node>());
}
