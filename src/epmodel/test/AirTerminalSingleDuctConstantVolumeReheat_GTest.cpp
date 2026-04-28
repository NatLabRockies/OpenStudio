/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ScheduleAndCoilConstructor_Parity) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();

  CoilHeatingElectric electricCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat electricTerminal(model, alwaysOn, electricCoil);
  EXPECT_EQ(alwaysOn.handle(), electricTerminal.availabilitySchedule().handle());
  EXPECT_EQ(electricCoil.handle(), electricTerminal.reheatCoil().handle());

  CoilHeatingGas gasCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat gasTerminal(model, alwaysOn, gasCoil);
  EXPECT_EQ(gasCoil.handle(), gasTerminal.reheatCoil().handle());

  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat waterTerminal(model, alwaysOn, waterCoil);
  EXPECT_EQ(waterCoil.handle(), waterTerminal.reheatCoil().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterorSteamFlowRate());
  EXPECT_FALSE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());
  terminal.resetMinimumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMinimumHotWaterorSteamFlowRateDefaulted());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.convergenceTolerance());
  EXPECT_FALSE(terminal.isConvergenceToleranceDefaulted());
  terminal.resetConvergenceTolerance();
  EXPECT_TRUE(terminal.isConvergenceToleranceDefaulted());

  EXPECT_TRUE(terminal.setMaximumReheatAirTemperature(41.2));
  EXPECT_DOUBLE_EQ(41.2, terminal.maximumReheatAirTemperature());
  EXPECT_FALSE(terminal.isMaximumReheatAirTemperatureDefaulted());
  terminal.resetMaximumReheatAirTemperature();
  EXPECT_TRUE(terminal.isMaximumReheatAirTemperatureDefaulted());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.7));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.handle(), terminal.availabilitySchedule().handle());

  CoilHeatingElectric reheatCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_ReheatCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, reheatCoil);

  CoilHeatingGas gasCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(gasCoil));
  EXPECT_EQ(gasCoil.handle(), terminal.reheatCoil().handle());

  CoilHeatingWater waterCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(waterCoil));
  EXPECT_EQ(waterCoil.handle(), terminal.reheatCoil().handle());

  FanConstantVolume fan(model);
  EXPECT_FALSE(terminal.setReheatCoil(fan));
  EXPECT_EQ(waterCoil.handle(), terminal.reheatCoil().handle());

  Model otherModel;
  CoilHeatingElectric foreignCoil(otherModel);
  EXPECT_FALSE(terminal.setReheatCoil(foreignCoil));
  EXPECT_EQ(waterCoil.handle(), terminal.reheatCoil().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AvailabilityScheduleGetter_RepairsMissingReference) {
  Model model;
  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, alwaysOn, reheatCoil);

  ASSERT_TRUE(
    terminal.setPointer(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName));

  const auto repairedSchedule = terminal.availabilitySchedule();
  EXPECT_EQ(alwaysOn, repairedSchedule);
  const auto storedSchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
  ASSERT_TRUE(storedSchedule);
  EXPECT_EQ(alwaysOn, *storedSchedule);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_ResolvesAirLoopHVACAndADUOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  EXPECT_NE(zoneAirNode, *inletNode);

  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zoneAirNode, *outletNode);

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zoneAirNode, resolvedOutletNode.get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeReheat_AddToNode_RegistersSecondBranchZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  AirTerminalSingleDuctConstantVolumeReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, dummyTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal));

  const auto splitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  ASSERT_EQ(2u, splitterOutlets.size());
  auto firstBranch = splitterOutlets[0].optionalCast<Node>();
  ASSERT_TRUE(firstBranch);
  auto secondBranch = splitterOutlets[1].optionalCast<Node>();
  ASSERT_TRUE(secondBranch);
  auto dummyInlet = dummyTerminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(dummyInlet);
  EXPECT_EQ(*firstBranch, *dummyInlet);

  auto terminalInlet = terminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalInlet);
  EXPECT_EQ(*secondBranch, *terminalInlet);

  auto terminalOutlet = terminal.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(terminalOutlet);
  EXPECT_EQ(zone2.zoneAirNode(), *terminalOutlet);

  const auto zone1Equipment = zone1.equipment();
  ASSERT_EQ(1u, zone1Equipment.size());
  EXPECT_EQ(dummyTerminal.cast<ModelObject>(), zone1Equipment.front());

  const auto zone2Equipment = zone2.equipment();
  ASSERT_EQ(1u, zone2Equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone2Equipment.front());

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zone2.zoneAirNode(), resolvedOutletNode.get());
}
