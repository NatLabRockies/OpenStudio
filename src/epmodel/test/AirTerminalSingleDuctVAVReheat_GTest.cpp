/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <utilities/core/Exception.hpp>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/Branch_Impl.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctVAVReheat_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_VAV_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctVAVReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_CanonicalConstructorEstablishesRequiredRelationships) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  CoilHeatingElectric reheatCoil(model);

  AirTerminalSingleDuctVAVReheat terminal(model, availability, reheatCoil);

  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  FanConstantVolume invalidCoil(model);
  EXPECT_THROW({ AirTerminalSingleDuctVAVReheat invalidTerminal(model, availability, invalidCoil); }, openstudio::Exception);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_CanonicalConstructorRenameThenAddMaintainsReheatAirPath) {
  Model model;
  auto availability = model.alwaysOnDiscreteSchedule();
  PlantLoop hotWaterLoop(model);
  CoilHeatingWater reheatCoil(model);
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(reheatCoil));

  AirTerminalSingleDuctVAVReheat terminal(model, availability, reheatCoil);
  const auto initialDamperOutletNode =
    terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  const auto initialCoilAirInletNode = reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  ASSERT_TRUE(initialDamperOutletNode);
  ASSERT_TRUE(initialCoilAirInletNode);
  EXPECT_EQ(*initialDamperOutletNode, *initialCoilAirInletNode);
  ASSERT_TRUE(terminal.setName("Renamed VAV Reheat Terminal"));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  const auto damperOutletNode = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  const auto coilAirInletNode = reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  const auto coilAirOutletNode = reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  const auto terminalOutletNode = terminal.outletModelObject();

  ASSERT_TRUE(damperOutletNode);
  ASSERT_TRUE(coilAirInletNode);
  EXPECT_EQ(*damperOutletNode, *coilAirInletNode);
  EXPECT_EQ("Renamed VAV Reheat Terminal Damper Outlet", damperOutletNode->nameString());

  ASSERT_TRUE(coilAirOutletNode);
  ASSERT_TRUE(terminalOutletNode);
  EXPECT_EQ(terminalOutletNode->cast<Node>(), *coilAirOutletNode);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_SurvivesSaveLoadAndRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-vav-reheat-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.setName("Roundtrip VAV Air Loop"));
  ASSERT_TRUE(plantLoop.setName("Roundtrip VAV Plant Loop"));
  ASSERT_TRUE(zone.setName("Roundtrip VAV Zone"));

  auto availability = model.alwaysOnDiscreteSchedule();
  CoilHeatingWater reheatCoil(model);
  ASSERT_TRUE(reheatCoil.setName("Roundtrip VAV Reheat Coil"));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  AirTerminalSingleDuctVAVReheat terminal(model, availability, reheatCoil);
  ASSERT_TRUE(terminal.setName("Roundtrip VAV Reheat Terminal"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto zoneAirNode = connections->zoneAirNode();
  const auto zoneInletNodes = connections->zoneAirInletNodes();
  ASSERT_EQ(1u, zoneInletNodes.size());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(zoneInletNodes.front().handle(), terminal.outletModelObject()->handle());
  EXPECT_NE(zoneAirNode.handle(), zoneInletNodes.front().handle());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip VAV Air Loop");
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Roundtrip VAV Plant Loop");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip VAV Zone");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctVAVReheat>("Roundtrip VAV Reheat Terminal");
  auto loadedReheatCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Roundtrip VAV Reheat Coil");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedReheatCoil);

  EXPECT_EQ(loadedReheatCoil->handle(), loadedTerminal->reheatCoil().handle());
  ASSERT_TRUE(loadedTerminal->airLoopHVAC());
  EXPECT_EQ(loadedAirLoop->handle(), loadedTerminal->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedReheatCoil->plantLoop());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedReheatCoil->plantLoop()->handle());
  ASSERT_TRUE(loadedZone->airLoopHVACTerminal());
  EXPECT_EQ(loadedTerminal->handle(), loadedZone->airLoopHVACTerminal()->handle());

  auto loadedConnections = loadedZone->getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(loadedConnections);
  const auto loadedZoneAirNode = loadedConnections->zoneAirNode();
  const auto loadedZoneInletNodes = loadedConnections->zoneAirInletNodes();
  ASSERT_EQ(1u, loadedZoneInletNodes.size());
  ASSERT_TRUE(loadedTerminal->outletModelObject());
  EXPECT_EQ(loadedZoneInletNodes.front().handle(), loadedTerminal->outletModelObject()->handle());
  EXPECT_NE(loadedZoneAirNode.handle(), loadedZoneInletNodes.front().handle());

  const auto loadedDamperOutletNode =
    loadedTerminal->getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  const auto loadedCoilAirInletNode = loadedReheatCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  ASSERT_TRUE(loadedDamperOutletNode);
  ASSERT_TRUE(loadedCoilAirInletNode);
  EXPECT_EQ(*loadedDamperOutletNode, *loadedCoilAirInletNode);

  ASSERT_TRUE(loadedTerminal->setName("Reloaded VAV Reheat Terminal"));
  ASSERT_TRUE(loadedTerminal->setReheatCoil(*loadedReheatCoil));
  const auto maintainedDamperOutletNode =
    loadedTerminal->getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  const auto maintainedCoilAirInletNode = loadedReheatCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  ASSERT_TRUE(maintainedDamperOutletNode);
  ASSERT_TRUE(maintainedCoilAirInletNode);
  EXPECT_EQ(*maintainedDamperOutletNode, *maintainedCoilAirInletNode);
  EXPECT_EQ("Reloaded VAV Reheat Terminal Damper Outlet", maintainedDamperOutletNode->nameString());

  const auto terminalHandle = loadedTerminal->handle();
  const auto reheatCoilHandle = loadedReheatCoil->handle();
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(terminalHandle));
  EXPECT_FALSE(loadedModel->getObject(reheatCoilHandle));
  EXPECT_FALSE(loadedZone->airLoopHVACTerminal());
  EXPECT_TRUE(loadedPlantLoop->demandComponents(CoilHeatingWater::iddObjectType()).empty());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Remove_DisconnectedDeletesOwnedReheatCoil) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model, availability, reheatCoil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = reheatCoil.handle();
  const auto damperOutlet = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  ASSERT_TRUE(damperOutlet);
  const auto damperOutletHandle = damperOutlet->handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_FALSE(model.getObject(damperOutletHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Remove_DisconnectedLeavesSharedDamperNode) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model, availability, reheatCoil);
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = reheatCoil.handle();
  const auto damperOutlet = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  ASSERT_TRUE(damperOutlet);
  const auto damperOutletHandle = damperOutlet->handle();

  NodeList foreignNodeList(model);
  auto foreignNodeListImpl = foreignNodeList.getImpl<detail::NodeList_Impl>();
  ASSERT_TRUE(foreignNodeListImpl);
  ASSERT_TRUE(foreignNodeListImpl->addNode(*damperOutlet));
  ASSERT_EQ(1u, foreignNodeList.nodes().size());

  const auto removedObjects = terminal.remove();

  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  ASSERT_TRUE(model.getModelObject<Node>(damperOutletHandle));
  ASSERT_EQ(1u, foreignNodeList.nodes().size());
  EXPECT_EQ(damperOutletHandle, foreignNodeList.nodes().front().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_EQ("Constant", terminal.zoneMinimumAirFlowMethod());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowInputMethod("Scheduled"));
  EXPECT_EQ("Scheduled", terminal.zoneMinimumAirFlowInputMethod());
  EXPECT_TRUE(terminal.setZoneMinimumAirFlowMethod("FixedFlowRate"));
  EXPECT_EQ("FixedFlowRate", terminal.zoneMinimumAirFlowInputMethod());

  EXPECT_TRUE(terminal.setConstantMinimumAirFlowFraction(0.42));
  ASSERT_TRUE(terminal.constantMinimumAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.42, terminal.constantMinimumAirFlowFraction().get());
  terminal.autosizeConstantMinimumAirFlowFraction();
  EXPECT_TRUE(terminal.isConstantMinimumAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setFixedMinimumAirFlowRate(0.5));
  ASSERT_TRUE(terminal.fixedMinimumAirFlowRate());
  EXPECT_DOUBLE_EQ(0.5, terminal.fixedMinimumAirFlowRate().get());
  terminal.autosizeFixedMinimumAirFlowRate();
  EXPECT_TRUE(terminal.isFixedMinimumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.isMaximumHotWaterOrSteamFlowRateAutosized());
  EXPECT_TRUE(terminal.setMaximumHotWaterOrSteamFlowRate(0.005));
  ASSERT_TRUE(terminal.maximumHotWaterOrSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.005, terminal.maximumHotWaterOrSteamFlowRate().get());
  terminal.autosizeMaximumHotWaterOrSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterOrSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterOrStreamFlowRate(0.001));
  EXPECT_DOUBLE_EQ(0.001, terminal.minimumHotWaterOrSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.007));
  EXPECT_DOUBLE_EQ(0.007, terminal.convergenceTolerance());

  EXPECT_EQ("Normal", terminal.damperHeatingAction());
  EXPECT_TRUE(terminal.setDamperHeatingAction("Reverse"));
  EXPECT_EQ("Reverse", terminal.damperHeatingAction());

  EXPECT_TRUE(terminal.isMaximumFlowPerZoneFloorAreaDuringReheatAutosized());
  EXPECT_TRUE(terminal.setMaximumFlowPerZoneFloorAreaDuringReheat(0.25));
  ASSERT_TRUE(terminal.maximumFlowPerZoneFloorAreaDuringReheat());
  EXPECT_DOUBLE_EQ(0.25, terminal.maximumFlowPerZoneFloorAreaDuringReheat().get());
  terminal.autosizeMaximumFlowPerZoneFloorAreaDuringReheat();
  EXPECT_TRUE(terminal.isMaximumFlowPerZoneFloorAreaDuringReheatAutosized());
  terminal.resetMaximumFlowPerZoneFloorAreaDuringReheat();
  EXPECT_FALSE(terminal.maximumFlowPerZoneFloorAreaDuringReheat());

  EXPECT_TRUE(terminal.isMaximumFlowFractionDuringReheatAutosized());
  EXPECT_TRUE(terminal.setMaximumFlowFractionDuringReheat(0.35));
  ASSERT_TRUE(terminal.maximumFlowFractionDuringReheat());
  EXPECT_DOUBLE_EQ(0.35, terminal.maximumFlowFractionDuringReheat().get());
  terminal.autosizeMaximumFlowFractionDuringReheat();
  EXPECT_TRUE(terminal.isMaximumFlowFractionDuringReheatAutosized());
  terminal.resetMaximumFlowFractionDuringReheat();
  EXPECT_FALSE(terminal.maximumFlowFractionDuringReheat());

  EXPECT_TRUE(terminal.setMaximumReheatAirTemperature(41.2));
  EXPECT_DOUBLE_EQ(41.2, terminal.maximumReheatAirTemperature());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  auto defaultSchedule = terminal.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultSchedule);
  EXPECT_DOUBLE_EQ(1.0, defaultSchedule->value());

  ScheduleCompact availability(model);
  ScheduleCompact minimumFraction(model);
  ScheduleCompact turndown(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(minimumFraction.setToConstantValue(0.2));
  ASSERT_TRUE(turndown.setToConstantValue(0.4));

  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  EXPECT_TRUE(terminal.setMinimumAirFlowFractionSchedule(minimumFraction));
  EXPECT_TRUE(terminal.setMinimumAirFlowTurndownSchedule(turndown));
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule().handle());
  ASSERT_TRUE(terminal.minimumAirFlowFractionSchedule());
  EXPECT_EQ(minimumFraction.handle(), terminal.minimumAirFlowFractionSchedule()->handle());
  ASSERT_TRUE(terminal.minimumAirFlowTurndownSchedule());
  EXPECT_EQ(turndown.handle(), terminal.minimumAirFlowTurndownSchedule()->handle());

  CoilHeatingElectric reheatCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());

  terminal.resetMinimumAirFlowFractionSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowFractionSchedule());
  terminal.resetMinimumAirFlowTurndownSchedule();
  EXPECT_FALSE(terminal.minimumAirFlowTurndownSchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_ReheatCoilValidation_GuardsUnsupportedAndForeignObjects) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);

  CoilHeatingElectric electricCoil(model);
  EXPECT_TRUE(terminal.setReheatCoil(electricCoil));
  EXPECT_EQ(electricCoil.handle(), terminal.reheatCoil().handle());

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

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  Node standaloneNode(model);
  Model otherModel;
  Node foreignNode(otherModel);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_ResolvesAirLoopHVACAndADUOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
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
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
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
  EXPECT_NE(zoneAirNode, *outletNode);

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  EXPECT_EQ(connections->zoneAirInletNodes().front(), *outletNode);

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(*outletNode, resolvedOutletNode.get());
  const auto inletHandleBeforeRejectedAdd = terminal.inletModelObject()->handle();
  const auto outletHandleBeforeRejectedAdd = terminal.outletModelObject()->handle();
  const auto aduOutletHandleBeforeRejectedAdd = resolvedOutletNode->handle();

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletHandleBeforeRejectedAdd, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletHandleBeforeRejectedAdd, terminal.outletModelObject()->handle());
  resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(aduOutletHandleBeforeRejectedAdd, resolvedOutletNode->handle());
  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_PopulatesDirectReheatCoilAirPathFields) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);

  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneAirNode = zone.zoneAirNode();
  ASSERT_TRUE(terminal.addToNode(zoneAirNode));

  const std::string damperOutletNodeName = terminal.nameString() + " Damper Outlet";
  EXPECT_EQ(damperOutletNodeName, terminal.getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName, true).get());
  EXPECT_EQ(reheatCoil.iddObject().name(), terminal.getString(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::ReheatCoilObjectType, true).get());
  EXPECT_EQ(damperOutletNodeName, reheatCoil.getString(openstudio::Coil_Heating_WaterFields::AirInletNodeName, true).get());
  ASSERT_TRUE(reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  EXPECT_EQ(connections->zoneAirInletNodes().front(),
            reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName).get());
  EXPECT_NE(zoneAirNode, connections->zoneAirInletNodes().front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_RegistersSecondBranchZoneEquipment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat dummyTerminal(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
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
  EXPECT_NE(zone2.zoneAirNode(), *terminalOutlet);
  auto zone2Connections = zone2.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zone2Connections);
  ASSERT_EQ(1u, zone2Connections->zoneAirInletNodes().size());
  EXPECT_EQ(zone2Connections->zoneAirInletNodes().front(), *terminalOutlet);

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
  EXPECT_EQ(*terminalOutlet, resolvedOutletNode.get());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  const auto zoneInletNode = connections->zoneAirInletNodes().front();

  Node mismatchedMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneInletNode.cast<ModelObject>(), *splitterOutlet);
  EXPECT_NE(zoneAirNode, zoneInletNode);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToZoneAirNodeRejectsAmbiguousFreeInletsWithoutMutation) {
  Model model;
  AirLoopHVAC firstAirLoop(model);
  AirLoopHVAC secondAirLoop(model);
  ThermalZone zone(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  ASSERT_TRUE(firstAirLoop.addBranchForZone(zone));
  ASSERT_TRUE(secondAirLoop.addBranchForZone(zone));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(2u, connections->zoneAirInletNodes().size());
  const auto firstOutlets = firstAirLoop.zoneSplitter().outletModelObjects();
  const auto secondOutlets = secondAirLoop.zoneSplitter().outletModelObjects();
  const auto nodeCount = model.getConcreteModelObjects<Node>().size();

  auto zoneAirNode = zone.zoneAirNode();
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));

  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_EQ(firstOutlets, firstAirLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(secondOutlets, secondAirLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(nodeCount, model.getConcreteModelObjects<Node>().size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_AddToZoneAirNodePreflightDoesNotRepairRawOrDuplicateZoneRelationships) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  ASSERT_TRUE(airLoop.addBranchForZone(zone));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  auto workspaceImpl = connections->getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(connectionsImpl);
  ASSERT_TRUE(workspaceImpl);
  constexpr unsigned inletField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirInletNodeorNodeListName;
  constexpr unsigned zoneAirNodeField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirNodeName;

  auto zoneAirNode = zone.zoneAirNode();
  const auto inletTarget = connections->getTarget(inletField);
  ASSERT_TRUE(inletTarget);
  const auto inletNodeList = inletTarget->optionalCast<NodeList>();
  ASSERT_TRUE(inletNodeList);

  // Intentional raw-only imported A3 relationship. Terminal preflight must
  // reject it without enrolling the NodeList pointer or creating any Node.
  ASSERT_TRUE(connectionsImpl->setPointer(inletField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(inletField, inletNodeList->nameString()));
  const auto inletManagedBefore = connections->getField(inletField, false);
  const auto inletRawBefore = workspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  const auto nodeCountBeforeRaw = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_TRUE(inletManagedBefore == connections->getField(inletField, false));
  EXPECT_TRUE(inletRawBefore == workspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true));
  EXPECT_EQ(nodeCountBeforeRaw, model.getConcreteModelObjects<Node>().size());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());

  ASSERT_TRUE(connectionsImpl->setPointer(inletField, inletNodeList->handle(), false));
  ThermalZone duplicateOwner(model);
  ZoneHVACEquipmentConnections duplicateConnections(duplicateOwner);
  auto duplicateImpl = duplicateConnections.getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(duplicateImpl);
  ASSERT_TRUE(duplicateImpl->setPointer(zoneAirNodeField, zoneAirNode.handle(), false));
  const auto originalZoneAirNodeField = connections->getField(zoneAirNodeField, false);
  const auto duplicateZoneAirNodeField = duplicateConnections.getField(zoneAirNodeField, false);
  const auto nodeCountBeforeDuplicate = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_TRUE(originalZoneAirNodeField == connections->getField(zoneAirNodeField, false));
  EXPECT_TRUE(duplicateZoneAirNodeField == duplicateConnections.getField(zoneAirNodeField, false));
  EXPECT_EQ(nodeCountBeforeDuplicate, model.getConcreteModelObjects<Node>().size());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(zone.equipment().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_TerminalOnlyBranchCanBeClaimedByZoneAndRemoved) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = reheatCoil.handle();

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  ASSERT_TRUE(zone.equipment().empty());

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  ASSERT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone.equipment().front());
  ASSERT_TRUE(terminal.outletModelObject());
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  EXPECT_EQ(terminal.outletModelObject()->handle(), connections->zoneAirInletNodes().front().handle());

  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_TRUE(zone.equipment().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Remove_ReconnectsZoneBranchAndCleansZoneAndPlantReferences) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));
  const auto terminalHandle = terminal.handle();
  const auto coilHandle = waterCoil.handle();
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  const auto zoneAirNode = zone.zoneAirNode();
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto zoneInletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(zoneInletNode);
  EXPECT_NE(zoneAirNode, *zoneInletNode);

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();
  EXPECT_NE(zoneAirNode, *inletNode);

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
  ASSERT_EQ(1u, zone.equipment().size());
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());
  auto plantWaterCoils = plantLoop.demandComponents(CoilHeatingWater::iddObjectType());
  EXPECT_NE(plantWaterCoils.end(), std::ranges::find(plantWaterCoils, waterCoil.cast<ModelObject>()));

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());

  splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneInletNode->cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(airLoop.demandComponents(AirTerminalSingleDuctVAVReheat::iddObjectType()).empty());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_Remove_SelectsItsDemandLoopWhenAnotherLoopServesZones) {
  Model model;
  AirLoopHVAC firstLoop(model);
  AirLoopHVAC secondLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  CoilHeatingElectric firstCoil(model);
  CoilHeatingElectric secondCoil(model);
  AirTerminalSingleDuctVAVReheat firstTerminal(model, availability, firstCoil);
  AirTerminalSingleDuctVAVReheat secondTerminal(model, availability, secondCoil);

  ASSERT_TRUE(firstLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(secondLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_EQ(std::vector<ThermalZone>{firstZone}, firstLoop.thermalZones());
  ASSERT_EQ(std::vector<ThermalZone>{secondZone}, secondLoop.thermalZones());

  const auto firstTerminalHandle = firstTerminal.handle();
  const auto firstCoilHandle = firstCoil.handle();
  EXPECT_FALSE(firstTerminal.remove().empty());

  EXPECT_FALSE(model.getObject(firstTerminalHandle));
  EXPECT_FALSE(model.getObject(firstCoilHandle));
  EXPECT_TRUE(model.getObject(secondTerminal.handle()));
  EXPECT_TRUE(model.getObject(secondCoil.handle()));
  EXPECT_EQ(std::vector<ThermalZone>{firstZone}, firstLoop.thermalZones());
  EXPECT_EQ(std::vector<ThermalZone>{secondZone}, secondLoop.thermalZones());
  ASSERT_TRUE(secondZone.airLoopHVACTerminal());
  EXPECT_EQ(secondTerminal.handle(), secondZone.airLoopHVACTerminal()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansPlantBranchWhenTerminalIsNotAirLoopConnected) {
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  auto plantWaterCoils = plantLoop.demandComponents(CoilHeatingWater::iddObjectType());
  EXPECT_NE(plantWaterCoils.end(), std::ranges::find(plantWaterCoils, waterCoil.cast<ModelObject>()));

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(waterCoil.handle()));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansStaleADUOnlyReference) {
  Model model;
  AirTerminalSingleDuctVAVReheat terminal(model);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(adu.airTerminal());

  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansConnectivityWithoutADU) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  const auto zoneAirNode = zone.zoneAirNode();
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto zoneInletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(zoneInletNode);
  EXPECT_NE(zoneAirNode, *zoneInletNode);
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneInletNode->cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoop_CleansConnectivityWithoutRemovingTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  AirTerminalSingleDuctVAVReheat terminal(model);
  ASSERT_TRUE(terminal.setReheatCoil(waterCoil));
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(waterCoil.plantLoop());
  const auto zoneAirNode = zone.zoneAirNode();
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto zoneInletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(zoneInletNode);
  EXPECT_NE(zoneAirNode, *zoneInletNode);
  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  const auto inletNodeHandle = inletNode->handle();

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneInletNode->cast<ModelObject>(), *splitterOutlet);
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(waterCoil.plantLoop());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoopRejectsMalformedPlantBranchBeforeMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  auto availability = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctVAVReheat terminal(model, availability, waterCoil);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  EXPECT_FALSE(waterCoil.controllerWaterCoil());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(waterCoil.waterInletModelObject());
  ASSERT_TRUE(waterCoil.waterOutletModelObject());

  auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();
  ASSERT_TRUE(plantLoopImpl);
  auto equipmentBranches = plantLoopImpl->demandEquipmentBranches();
  ASSERT_EQ(1u, equipmentBranches.size());
  auto targetBranch = equipmentBranches.front();
  PipeAdiabatic competingPipe(model);
  ASSERT_TRUE(
    targetBranch.getImpl<detail::Branch_Impl>()->appendComponent(competingPipe.cast<ModelObject>(), "Competing Pipe Inlet", "Competing Pipe Outlet"));
  ASSERT_EQ(2u, targetBranch.components().size());

  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }
  const auto splitterBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerBefore = airLoop.zoneMixer().inletModelObjects();
  const auto zoneEquipmentBefore = zone.equipment();
  const auto plantComponentsBefore = plantLoop.demandComponents();
  const auto branchComponentsBefore = targetBranch.components();
  const auto terminalInletHandle = terminal.inletModelObject()->handle();
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();
  const auto waterInletHandle = waterCoil.waterInletModelObject()->handle();
  const auto waterOutletHandle = waterCoil.waterOutletModelObject()->handle();
  const auto damperOutlet = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  const auto coilAirInlet = waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  const auto coilAirOutlet = waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(damperOutlet);
  ASSERT_TRUE(coilAirInlet);
  ASSERT_TRUE(coilAirOutlet);

  EXPECT_FALSE(terminal.removeFromLoop());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(splitterBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  EXPECT_EQ(branchComponentsBefore, targetBranch.components());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  EXPECT_EQ(terminalOutletHandle, terminal.outletModelObject()->handle());
  ASSERT_TRUE(waterCoil.waterInletModelObject());
  ASSERT_TRUE(waterCoil.waterOutletModelObject());
  EXPECT_EQ(waterInletHandle, waterCoil.waterInletModelObject()->handle());
  EXPECT_EQ(waterOutletHandle, waterCoil.waterOutletModelObject()->handle());
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCoil.plantLoop()->handle());
  EXPECT_FALSE(waterCoil.controllerWaterCoil());
  ASSERT_TRUE(adu.airTerminal());
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(terminal.handle(), adu.airTerminal()->handle());
  EXPECT_EQ(terminalOutletHandle, adu.outletNode()->handle());
  ASSERT_TRUE(terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName));
  ASSERT_TRUE(waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName));
  ASSERT_TRUE(waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
  EXPECT_EQ(damperOutlet->handle(),
            terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName)->handle());
  EXPECT_EQ(coilAirInlet->handle(), waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)->handle());
  EXPECT_EQ(coilAirOutlet->handle(), waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemoveFromLoopRejectsMalformedContainedPathBeforeMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  auto availability = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctVAVReheat terminal(model, availability, waterCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(waterCoil.waterInletModelObject());
  ASSERT_TRUE(waterCoil.waterOutletModelObject());
  const auto damperOutlet = terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName);
  const auto coilAirOutlet = waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(damperOutlet);
  ASSERT_TRUE(coilAirOutlet);

  Node foreignCoilInlet(model);
  ASSERT_TRUE(waterCoil.setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, foreignCoilInlet.handle()));

  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }
  const auto splitterBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerBefore = airLoop.zoneMixer().inletModelObjects();
  const auto zoneEquipmentBefore = zone.equipment();
  const auto plantComponentsBefore = plantLoop.demandComponents();
  const auto terminalInletHandle = terminal.inletModelObject()->handle();
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();
  const auto waterInletHandle = waterCoil.waterInletModelObject()->handle();
  const auto waterOutletHandle = waterCoil.waterOutletModelObject()->handle();

  EXPECT_FALSE(terminal.removeFromLoop());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(splitterBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  EXPECT_EQ(terminalOutletHandle, terminal.outletModelObject()->handle());
  ASSERT_TRUE(waterCoil.waterInletModelObject());
  ASSERT_TRUE(waterCoil.waterOutletModelObject());
  EXPECT_EQ(waterInletHandle, waterCoil.waterInletModelObject()->handle());
  EXPECT_EQ(waterOutletHandle, waterCoil.waterOutletModelObject()->handle());
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCoil.plantLoop()->handle());
  ASSERT_TRUE(waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName));
  ASSERT_TRUE(waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
  EXPECT_EQ(foreignCoilInlet.handle(), waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName)->handle());
  EXPECT_EQ(coilAirOutlet->handle(), waterCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName)->handle());
  ASSERT_TRUE(terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName));
  EXPECT_EQ(damperOutlet->handle(),
            terminal.getModelObjectTarget<Node>(openstudio::AirTerminal_SingleDuct_VAV_ReheatFields::DamperAirOutletNodeName)->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctVAVReheat_RemovePreflightDoesNotMaterializeRawPorts) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater waterCoil(model);
  auto availability = model.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctVAVReheat terminal(model, availability, waterCoil);
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(waterCoil));
  auto terminalWorkspaceImpl = terminal.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(terminalWorkspaceImpl);
  const auto inletPort = terminal.inletPort();
  const auto outletPort = terminal.outletPort();
  ASSERT_TRUE(terminalWorkspaceImpl->setPointer(inletPort, openstudio::Handle(), false));
  ASSERT_TRUE(terminalWorkspaceImpl->setPointer(outletPort, openstudio::Handle(), false));
  ASSERT_TRUE(terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(inletPort, "Unresolved VAV Reheat Inlet", false));
  ASSERT_TRUE(terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(outletPort, "Unresolved VAV Reheat Outlet", false));

  const auto rawInletBefore = terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletPort, false, true);
  const auto rawOutletBefore = terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletPort, false, true);
  ASSERT_TRUE(rawInletBefore);
  ASSERT_TRUE(rawOutletBefore);
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }
  const auto splitterBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerBefore = airLoop.zoneMixer().inletModelObjects();
  const auto zoneEquipmentBefore = zone.equipment();
  const auto plantComponentsBefore = plantLoop.demandComponents();
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(terminal.removeFromLoop());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(splitterBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  EXPECT_EQ(*rawInletBefore, terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(inletPort, false, true).value_or(""));
  EXPECT_EQ(*rawOutletBefore, terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(outletPort, false, true).value_or(""));
  ASSERT_TRUE(waterCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), waterCoil.plantLoop()->handle());
  ASSERT_TRUE(adu.airTerminal());
  EXPECT_EQ(terminal.handle(), adu.airTerminal()->handle());
}
