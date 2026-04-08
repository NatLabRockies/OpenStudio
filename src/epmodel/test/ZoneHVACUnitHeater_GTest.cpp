/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACUnitHeater.hpp"

#include <utilities/idd/ZoneHVAC_UnitHeater_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACUnitHeater_DefaultConstructor) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);

  EXPECT_EQ(ZoneHVACUnitHeater::iddObjectType(), unitHeater.iddObject().type());
  EXPECT_TRUE(unitHeater.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_EQ("No", unitHeater.fanControlType());
  EXPECT_TRUE(unitHeater.isMaximumHotWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, unitHeater.minimumHotWaterFlowRate());
  EXPECT_FALSE(unitHeater.isMinimumHotWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.001, unitHeater.heatingConvergenceTolerance());
  EXPECT_FALSE(unitHeater.isHeatingConvergenceToleranceDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);

  EXPECT_TRUE(unitHeater.setMaximumSupplyAirFlowRate(0.42));
  EXPECT_FALSE(unitHeater.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_TRUE(unitHeater.setFanControlType("Yes"));
  EXPECT_TRUE(unitHeater.setMaximumHotWaterFlowRate(0.05));
  EXPECT_TRUE(unitHeater.setMinimumHotWaterFlowRate(0.02));
  EXPECT_TRUE(unitHeater.setHeatingConvergenceTolerance(0.01));

  ASSERT_TRUE(unitHeater.maximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.42, unitHeater.maximumSupplyAirFlowRate().value());
  EXPECT_EQ("Yes", unitHeater.fanControlType());
  ASSERT_TRUE(unitHeater.maximumHotWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.05, unitHeater.maximumHotWaterFlowRate().value());
  EXPECT_DOUBLE_EQ(0.02, unitHeater.minimumHotWaterFlowRate());
  EXPECT_FALSE(unitHeater.isMinimumHotWaterFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.01, unitHeater.heatingConvergenceTolerance());
  EXPECT_FALSE(unitHeater.isHeatingConvergenceToleranceDefaulted());

  unitHeater.autosizeMaximumSupplyAirFlowRate();
  EXPECT_TRUE(unitHeater.isMaximumSupplyAirFlowRateAutosized());
  EXPECT_FALSE(unitHeater.maximumSupplyAirFlowRate());

  unitHeater.resetMaximumHotWaterFlowRate();
  EXPECT_FALSE(unitHeater.maximumHotWaterFlowRate());
  unitHeater.autosizeMaximumHotWaterFlowRate();
  EXPECT_TRUE(unitHeater.isMaximumHotWaterFlowRateAutosized());

  unitHeater.resetMinimumHotWaterFlowRate();
  EXPECT_TRUE(unitHeater.isMinimumHotWaterFlowRateDefaulted());

  unitHeater.resetHeatingConvergenceTolerance();
  EXPECT_TRUE(unitHeater.isHeatingConvergenceToleranceDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_TopologyAndChildren) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  EXPECT_EQ(openstudio::ZoneHVAC_UnitHeaterFields::AirInletNodeName, unitHeater.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_UnitHeaterFields::AirOutletNodeName, unitHeater.outletPort());

  EXPECT_TRUE(unitHeater.setSupplyAirFan(fan));
  EXPECT_TRUE(unitHeater.setHeatingCoil(coil));
  EXPECT_TRUE(unitHeater.inletNode());
  EXPECT_TRUE(unitHeater.outletNode());
  EXPECT_TRUE(unitHeater.fanOutletNode());

  EXPECT_TRUE(unitHeater.addToThermalZone(zone));
  EXPECT_TRUE(unitHeater.inletNode());
  EXPECT_TRUE(unitHeater.outletNode());
  EXPECT_TRUE(unitHeater.fanOutletNode());

  unitHeater.removeFromThermalZone();
  EXPECT_TRUE(unitHeater.inletNode());
  EXPECT_TRUE(unitHeater.outletNode());

  const auto children = unitHeater.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(fan, children[0]);
  EXPECT_EQ(coil, children[1]);
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_HvacRelationships_RoundTrip) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);

  auto defaultSchedule = unitHeater.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.4));
  EXPECT_TRUE(unitHeater.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.handle(), unitHeater.availabilitySchedule().handle());

  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);
  EXPECT_TRUE(unitHeater.setSupplyAirFan(fan));
  EXPECT_TRUE(unitHeater.setHeatingCoil(coil));
  EXPECT_EQ(fan.handle(), unitHeater.supplyAirFan().handle());
  EXPECT_EQ(coil.handle(), unitHeater.heatingCoil().handle());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_ContainedNodePath_RoundTrip) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));
  ASSERT_TRUE(unitHeater.setHeatingCoil(coil));

  auto unitHeaterInlet = unitHeater.inletNode();
  auto unitHeaterOutlet = unitHeater.outletNode();
  auto unitHeaterFanOutlet = unitHeater.fanOutletNode();
  auto fanInlet = fan.inletModelObject();
  auto fanOutlet = fan.outletModelObject();
  auto coilInlet = coil.inletModelObject();
  auto coilOutlet = coil.outletModelObject();

  ASSERT_TRUE(unitHeaterInlet);
  ASSERT_TRUE(unitHeaterOutlet);
  ASSERT_TRUE(unitHeaterFanOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(coilInlet);
  ASSERT_TRUE(coilOutlet);

  auto fanInletNode = fanInlet->optionalCast<Node>();
  auto fanOutletNode = fanOutlet->optionalCast<Node>();
  auto coilInletNode = coilInlet->optionalCast<Node>();
  auto coilOutletNode = coilOutlet->optionalCast<Node>();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coilInletNode);
  ASSERT_TRUE(coilOutletNode);

  EXPECT_EQ(*unitHeaterInlet, *fanInletNode);
  EXPECT_EQ(*unitHeaterFanOutlet, *fanOutletNode);
  EXPECT_EQ(*fanOutletNode, *coilInletNode);
  EXPECT_EQ(*coilOutletNode, *unitHeaterOutlet);
  EXPECT_NE(*unitHeaterInlet, *fanOutletNode);
  EXPECT_NE(*fanOutletNode, *unitHeaterOutlet);

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(coil.containingHVACComponent());
  EXPECT_EQ(unitHeater, fan.containingHVACComponent().get());
  EXPECT_EQ(unitHeater, coil.containingHVACComponent().get());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_FanOutletNodeMayAliasOutlet) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);

  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));

  auto fanOutletNode = unitHeater.fanOutletNode();
  auto unitHeaterOutlet = unitHeater.outletNode();
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(unitHeaterOutlet);

  EXPECT_EQ(*fanOutletNode, *fan.outletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*fanOutletNode, *unitHeaterOutlet);
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_FanOutletNode_RenameSurvivesCanonicalize) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));
  ASSERT_TRUE(unitHeater.setHeatingCoil(coil));

  auto internalNode = unitHeater.fanOutletNode();
  ASSERT_TRUE(internalNode);
  ASSERT_TRUE(internalNode->setName("Custom Unit Heater Fan Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  auto renamedNode = unitHeater.fanOutletNode();
  auto fanOutletNode = fan.outletModelObject()->optionalCast<Node>();
  auto coilInletNode = coil.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(renamedNode);
  ASSERT_TRUE(fanOutletNode);
  ASSERT_TRUE(coilInletNode);

  EXPECT_EQ("Custom Unit Heater Fan Outlet", renamedNode->nameString());
  EXPECT_EQ(*renamedNode, *fanOutletNode);
  EXPECT_EQ(*renamedNode, *coilInletNode);
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));
  ASSERT_TRUE(unitHeater.setHeatingCoil(coil));

  auto originalFanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto originalFanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto originalCoilOutlet = coil.outletModelObject()->optionalCast<Node>();
  auto originalUnitHeaterFanOutlet = unitHeater.fanOutletNode();
  ASSERT_TRUE(originalFanInlet);
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoilOutlet);
  ASSERT_TRUE(originalUnitHeaterFanOutlet);

  fan.disconnect();
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  auto currentFanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto currentFanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto currentCoilInlet = coil.inletModelObject()->optionalCast<Node>();
  auto currentCoilOutlet = coil.outletModelObject()->optionalCast<Node>();
  auto currentUnitHeaterFanOutlet = unitHeater.fanOutletNode();
  ASSERT_TRUE(currentFanInlet);
  ASSERT_TRUE(currentFanOutlet);
  ASSERT_TRUE(currentCoilInlet);
  ASSERT_TRUE(currentCoilOutlet);
  ASSERT_TRUE(currentUnitHeaterFanOutlet);

  EXPECT_EQ(*originalFanInlet, *currentFanInlet);
  EXPECT_EQ(*originalFanOutlet, *currentFanOutlet);
  EXPECT_EQ(*currentFanOutlet, *currentCoilInlet);
  EXPECT_EQ(*originalCoilOutlet, *currentCoilOutlet);
  EXPECT_EQ(*originalUnitHeaterFanOutlet, *currentUnitHeaterFanOutlet);

  const auto children = unitHeater.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(fan, children[0]);
  EXPECT_EQ(coil, children[1]);
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_OwnerMutationsRebuildContainedPathWithoutSalvage) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));
  ASSERT_TRUE(unitHeater.setHeatingCoil(coil));

  Node rogueInternalNode(model);
  ASSERT_TRUE(rogueInternalNode.setName("Rogue Unit Heater Internal Node"));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueInternalNode.handle()));
  ASSERT_TRUE(coil.setPointer(coil.inletPort(), rogueInternalNode.handle()));

  FanConstantVolume replacementFan(model);
  ASSERT_TRUE(unitHeater.setSupplyAirFan(replacementFan));
  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));

  auto repairedInternalNode = unitHeater.fanOutletNode();
  ASSERT_TRUE(repairedInternalNode);

  EXPECT_NE("Rogue Unit Heater Internal Node", repairedInternalNode->nameString());
  EXPECT_EQ(*repairedInternalNode, *fan.outletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*repairedInternalNode, *coil.inletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACUnitHeater_CanonicalizeRepairsContainedNodePath) {
  Model model;
  ZoneHVACUnitHeater unitHeater(model);
  FanConstantVolume fan(model);
  CoilHeatingElectric coil(model);

  ASSERT_TRUE(unitHeater.setSupplyAirFan(fan));
  ASSERT_TRUE(unitHeater.setHeatingCoil(coil));

  auto expectedFanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto expectedCoilOutlet = coil.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(expectedFanInlet);
  ASSERT_TRUE(expectedCoilOutlet);

  Node rogueInlet(model);
  ASSERT_TRUE(rogueInlet.setName("Rogue Unit Heater Inlet"));
  Node rogueInternal(model);
  ASSERT_TRUE(rogueInternal.setName("Rogue Unit Heater Internal"));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueInlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueInternal.handle()));
  ASSERT_TRUE(coil.setPointer(coil.inletPort(), rogueInlet.handle()));
  ASSERT_TRUE(coil.setPointer(coil.outletPort(), rogueInternal.handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  auto repairedFanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto repairedFanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto repairedCoilInlet = coil.inletModelObject()->optionalCast<Node>();
  auto repairedCoilOutlet = coil.outletModelObject()->optionalCast<Node>();
  auto repairedUnitHeaterFanOutlet = unitHeater.fanOutletNode();
  ASSERT_TRUE(repairedFanInlet);
  ASSERT_TRUE(repairedFanOutlet);
  ASSERT_TRUE(repairedCoilInlet);
  ASSERT_TRUE(repairedCoilOutlet);
  ASSERT_TRUE(repairedUnitHeaterFanOutlet);

  EXPECT_EQ(*expectedFanInlet, *repairedFanInlet);
  EXPECT_EQ(*repairedFanOutlet, *repairedCoilInlet);
  EXPECT_EQ(*expectedCoilOutlet, *repairedCoilOutlet);
  EXPECT_EQ(*repairedFanOutlet, *repairedUnitHeaterFanOutlet);
  EXPECT_EQ("Rogue Unit Heater Internal", repairedFanOutlet->nameString());
}
