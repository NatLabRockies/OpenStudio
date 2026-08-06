#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../HVACComponent/HVACComponent.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model);

  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_FALSE(terminal.availabilitySchedule());
  EXPECT_TRUE(terminal.isMaximumTotalAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(2.5, terminal.inductionRatio());
  EXPECT_TRUE(terminal.isMaximumHotWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.minimumHotWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001, terminal.heatingConvergenceTolerance());
  EXPECT_FALSE(terminal.coolingCoil());
  EXPECT_TRUE(terminal.isMaximumColdWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.0, terminal.minimumColdWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001, terminal.coolingConvergenceTolerance());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_HeatingCoilConstructor) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);

  EXPECT_EQ(heatingCoil.handle(), terminal.heatingCoil().handle());
  EXPECT_FALSE(terminal.availabilitySchedule());
  EXPECT_FALSE(terminal.coolingCoil());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_Remove_DisconnectedDeletesOwnedCoils) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  const auto terminalHandle = terminal.handle();
  const auto heatingCoilHandle = heatingCoil.handle();
  const auto coolingCoilHandle = coolingCoil.handle();

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(heatingCoilHandle));
  EXPECT_FALSE(model.getObject(coolingCoilHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AvailabilityAndCoils_RoundTripAndValidation) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());
  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());

  CoilCoolingWater coolingCoil(model);
  EXPECT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(terminal.coolingCoil());
  EXPECT_EQ(coolingCoil.handle(), terminal.coolingCoil()->handle());
  terminal.resetCoolingCoil();
  EXPECT_FALSE(terminal.coolingCoil());

  CoilHeatingWater replacementHeating(model);
  EXPECT_TRUE(terminal.setHeatingCoil(replacementHeating));
  EXPECT_EQ(replacementHeating.handle(), terminal.heatingCoil().handle());

  Model foreignModel;
  CoilCoolingWater foreignCooling(foreignModel);
  CoilHeatingWater foreignHeating(foreignModel);
  boost::optional<HVACComponent> foreignCoolingAsComponent = foreignCooling.cast<HVACComponent>();
  EXPECT_FALSE(terminal.setCoolingCoil(foreignCoolingAsComponent));
  EXPECT_FALSE(terminal.setHeatingCoil(foreignHeating.cast<HVACComponent>()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  Node standaloneNode(model);
  Model foreignModel;
  Node foreignNode(foreignModel);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_RequiredHeatingCoilPreflightPreservesTopologyAndRetries) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model);

  const auto originalSplitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto originalMixerInlets = airLoop.zoneMixer().inletModelObjects();
  const auto originalNodeCount = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_EQ(originalSplitterOutlets, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(originalMixerInlets, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(originalNodeCount, model.getConcreteModelObjects<Node>().size());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  CoilHeatingWater heatingCoil(model);
  ASSERT_TRUE(terminal.setHeatingCoil(heatingCoil));
  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_TRUE(terminal.inletModelObject());
  EXPECT_TRUE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNode_ResolvesAirLoopHVACRegistersZoneEquipmentAndExhaustNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  EXPECT_TRUE(terminal.setCoolingCoil(coolingCoil));

  EXPECT_TRUE(airLoop.addBranchForZone(zone, terminal));

  auto linkedAirLoop = terminal.airLoopHVAC();
  ASSERT_TRUE(linkedAirLoop);
  EXPECT_EQ(airLoop, *linkedAirLoop);

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);

  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zone.zoneAirNode(), *outletNode);

  ASSERT_TRUE(terminal.inducedAirInletNode());
  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  auto exhaustNode = zoneConnections->getModelObjectTarget<Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName);
  ASSERT_TRUE(exhaustNode);
  EXPECT_EQ(*exhaustNode, terminal.inducedAirInletNode().get());

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zone.zoneAirNode(), resolvedOutletNode.get());

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipment.front());
  ASSERT_TRUE(zone.airLoopHVACTerminal());
  EXPECT_EQ(terminal.cast<HVACComponent>(), *zone.airLoopHVACTerminal());

  auto zoneAirNode = zone.zoneAirNode();
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(1u, zone.equipment().size());
  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(inletNode->cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNode_RejectsMismatchedSplitterMixerBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();

  Node mismatchedMixerNode(model);
  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode.cast<ModelObject>()));

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zoneAirNode.cast<ModelObject>(), *splitterOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNode_RejectsAlreadyConnectedTerminalOnSecondZone) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, terminal));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto originalInlet = terminal.inletModelObject()->handle();
  const auto originalOutlet = terminal.outletModelObject()->handle();

  auto zone2AirNode = zone2.zoneAirNode();
  EXPECT_FALSE(terminal.addToNode(zone2AirNode));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(originalInlet, terminal.inletModelObject()->handle());
  EXPECT_EQ(originalOutlet, terminal.outletModelObject()->handle());

  ASSERT_EQ(1u, zone1.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), zone1.equipment().front());
  ASSERT_EQ(1u, zone2.equipment().size());
  auto clonedTerminal = zone2.equipment().front().optionalCast<AirTerminalSingleDuctConstantVolumeFourPipeInduction>();
  ASSERT_TRUE(clonedTerminal);
  EXPECT_NE(terminal.handle(), clonedTerminal->handle());
  EXPECT_NE(terminal.heatingCoil().handle(), clonedTerminal->heatingCoil().handle());
  ASSERT_TRUE(terminal.inducedAirInletNode());
  ASSERT_TRUE(clonedTerminal->inducedAirInletNode());
  EXPECT_NE(terminal.inducedAirInletNode()->handle(), clonedTerminal->inducedAirInletNode()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_RemoveFromLoop_CleansStaleADUOnlyReference) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
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
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_FALSE(terminal.removeFromLoop());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_RemoveFromLoop_CleansZoneAndPlantConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));

  PlantLoop hotWaterLoop(model);
  PlantLoop coldWaterLoop(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(coldWaterLoop.addDemandBranchForComponent(coolingCoil));

  const auto containsObject = [](const std::vector<ModelObject>& objects, const ModelObject& object) {
    return std::find(objects.begin(), objects.end(), object) != objects.end();
  };

  EXPECT_TRUE(containsObject(zone.equipment(), terminal.cast<ModelObject>()));
  EXPECT_TRUE(containsObject(hotWaterLoop.demandComponents(), heatingCoil.cast<ModelObject>()));
  EXPECT_TRUE(containsObject(coldWaterLoop.demandComponents(), coolingCoil.cast<ModelObject>()));
  ASSERT_TRUE(terminal.inducedAirInletNode());
  const auto inducedAirInletHandle = terminal.inducedAirInletNode()->handle();
  const auto branchInletNodeHandle = terminal.inletModelObject()->handle();
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  auto splitterOutletBeforeRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBeforeRemoval);
  EXPECT_EQ(branchInletNodeHandle, splitterOutletBeforeRemoval->handle());

  EXPECT_TRUE(terminal.removeFromLoop());

  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_FALSE(containsObject(zone.equipment(), terminal.cast<ModelObject>()));
  EXPECT_FALSE(containsObject(hotWaterLoop.demandComponents(), heatingCoil.cast<ModelObject>()));
  EXPECT_FALSE(containsObject(coldWaterLoop.demandComponents(), coolingCoil.cast<ModelObject>()));

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  EXPECT_FALSE(zoneConnections->getModelObjectTarget<Node>(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName));
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inducedAirInletHandle));
  EXPECT_FALSE(model.getModelObject<Node>(branchInletNodeHandle));
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
  EXPECT_TRUE(model.getObject(coolingCoil.handle()));

  auto splitterOutletAfterRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfterRemoval);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutletAfterRemoval->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_Remove_ConnectedDeletesOwnedCoils) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop hotWaterLoop(model);
  PlantLoop coldWaterLoop(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  const auto terminalHandle = terminal.handle();
  const auto heatingCoilHandle = heatingCoil.handle();
  const auto coolingCoilHandle = coolingCoil.handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(coldWaterLoop.addDemandBranchForComponent(coolingCoil));

  const auto removedObjects = terminal.remove();
  EXPECT_FALSE(removedObjects.empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(heatingCoilHandle));
  EXPECT_FALSE(model.getObject(coolingCoilHandle));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_TRUE(hotWaterLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
  EXPECT_TRUE(coldWaterLoop.demandComponents(CoilCoolingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_RemoveFromLoop_CleansConnectivityWithoutCoolingCoil) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ZoneHVACAirDistributionUnit adu(model);

  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  PlantLoop hotWaterLoop(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));

  const auto containsObject = [](const std::vector<ModelObject>& objects, const ModelObject& object) {
    return std::find(objects.begin(), objects.end(), object) != objects.end();
  };

  ASSERT_TRUE(terminal.inducedAirInletNode());
  const auto inducedAirInletHandle = terminal.inducedAirInletNode()->handle();
  const auto branchInletNodeHandle = terminal.inletModelObject()->handle();

  EXPECT_TRUE(containsObject(zone.equipment(), terminal.cast<ModelObject>()));
  EXPECT_TRUE(containsObject(hotWaterLoop.demandComponents(), heatingCoil.cast<ModelObject>()));
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(zone.zoneAirNode(), adu.outletNode().get());

  EXPECT_TRUE(terminal.removeFromLoop());

  EXPECT_FALSE(terminal.coolingCoil());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_FALSE(containsObject(zone.equipment(), terminal.cast<ModelObject>()));
  EXPECT_FALSE(containsObject(hotWaterLoop.demandComponents(), heatingCoil.cast<ModelObject>()));
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(inducedAirInletHandle));
  EXPECT_FALSE(model.getModelObject<Node>(branchInletNodeHandle));

  auto splitterOutletAfterRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfterRemoval);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutletAfterRemoval->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_Remove_PreflightFailurePreservesAirZoneAndBothPlantSides) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop hotWaterLoop(model);
  PlantLoop coldWaterLoop(model);
  CoilHeatingWater heatingCoil(model);
  CoilHeatingWater neighboringHeatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(coldWaterLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(neighboringHeatingCoil));
  ASSERT_TRUE(coolingCoil.waterInletModelObject());
  ASSERT_TRUE(coolingCoil.waterOutletModelObject());
  const auto coolingInletHandle = coolingCoil.waterInletModelObject()->handle();
  const auto coolingOutletHandle = coolingCoil.waterOutletModelObject()->handle();
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.inducedAirInletNode());
  const auto terminalInletHandle = terminal.inletModelObject()->handle();
  const auto inducedNodeHandle = terminal.inducedAirInletNode()->handle();

  // Make the heating coil span two demand-equipment branches. The valid cold
  // side and all air and zone state must remain untouched when preflight
  // rejects this malformed hot-side topology.
  auto heatingCoilImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingWater_Impl>();
  ASSERT_TRUE(heatingCoilImpl);
  ASSERT_TRUE(neighboringHeatingCoil.waterInletModelObject());
  ASSERT_TRUE(heatingCoilImpl->setPointer(heatingCoil.waterOutletPort(), neighboringHeatingCoil.waterInletModelObject()->handle(), false));
  ASSERT_TRUE(heatingCoil.plantLoop());

  EXPECT_TRUE(terminal.remove().empty());

  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_TRUE(model.getObject(heatingCoil.handle()));
  EXPECT_TRUE(model.getObject(coolingCoil.handle()));
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(terminalInletHandle, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.inducedAirInletNode());
  EXPECT_EQ(inducedNodeHandle, terminal.inducedAirInletNode()->handle());
  ASSERT_TRUE(coolingCoil.waterInletModelObject());
  ASSERT_TRUE(coolingCoil.waterOutletModelObject());
  EXPECT_EQ(coolingInletHandle, coolingCoil.waterInletModelObject()->handle());
  EXPECT_EQ(coolingOutletHandle, coolingCoil.waterOutletModelObject()->handle());
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(coldWaterLoop.handle(), coolingCoil.plantLoop()->handle());
  ASSERT_TRUE(heatingCoil.plantLoop());
  EXPECT_EQ(hotWaterLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_EQ(2u, hotWaterLoop.demandComponents(CoilHeatingWater::iddObjectType()).size());
  EXPECT_EQ(1u, zone.equipment().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalSingleDuctConstantVolumeFourPipeInduction::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_TerminalFirstClaimRemovalPreservesNeighborIdentity) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone claimedZone(model);
  ThermalZone neighborZone(model);
  PlantLoop hotWaterLoop(model);
  PlantLoop coldWaterLoop(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(coldWaterLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(airLoop.addBranchForZone(claimedZone));
  ASSERT_TRUE(airLoop.addBranchForZone(neighborZone));

  ASSERT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());
  const auto neighborSplitterOutlet = airLoop.zoneSplitter().outletModelObject(1u);
  const auto neighborMixerInlet = airLoop.zoneMixer().inletModelObject(1u);
  ASSERT_TRUE(neighborSplitterOutlet);
  ASSERT_TRUE(neighborMixerInlet);
  ASSERT_TRUE(terminal.inducedAirInletNode());
  const auto inducedNodeHandle = terminal.inducedAirInletNode()->handle();
  const auto terminalHandle = terminal.handle();
  const auto heatingCoilHandle = heatingCoil.handle();
  const auto coolingCoilHandle = coolingCoil.handle();
  const auto aduHandle = adu.handle();
  ASSERT_EQ(1u, neighborZone.equipment().size());
  auto neighborTerminal = neighborZone.equipment().front().optionalCast<AirTerminalSingleDuctConstantVolumeFourPipeInduction>();
  ASSERT_TRUE(neighborTerminal);
  const auto neighborTerminalHandle = neighborTerminal->handle();
  const auto neighborHeatingCoilHandle = neighborTerminal->heatingCoil().handle();
  ASSERT_TRUE(neighborTerminal->coolingCoil());
  const auto neighborCoolingCoilHandle = neighborTerminal->coolingCoil()->handle();
  auto claimedConnections = claimedZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(claimedConnections);
  const auto claimedConnectionsHandle = claimedConnections->handle();
  const auto claimedExhaustNodes = claimedConnections->zoneAirExhaustNodes();
  EXPECT_NE(claimedExhaustNodes.end(), std::ranges::find(claimedExhaustNodes, *terminal.inducedAirInletNode()));

  ASSERT_TRUE(airLoop.removeBranchForZone(claimedZone));

  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(heatingCoilHandle));
  EXPECT_FALSE(model.getObject(coolingCoilHandle));
  EXPECT_FALSE(model.getObject(aduHandle));
  EXPECT_FALSE(model.getObject(inducedNodeHandle));
  EXPECT_EQ(1u, hotWaterLoop.demandComponents(CoilHeatingWater::iddObjectType()).size());
  EXPECT_EQ(1u, coldWaterLoop.demandComponents(CoilCoolingWater::iddObjectType()).size());
  EXPECT_TRUE(model.getObject(neighborTerminalHandle));
  EXPECT_TRUE(model.getObject(neighborHeatingCoilHandle));
  EXPECT_TRUE(model.getObject(neighborCoolingCoilHandle));
  EXPECT_TRUE(claimedZone.equipment().empty());
  EXPECT_FALSE(claimedZone.airLoopHVACTerminal());
  if (model.getObject(claimedConnectionsHandle)) {
    auto remainingConnections = claimedZone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
    ASSERT_TRUE(remainingConnections);
    const auto remainingExhaustNodes = remainingConnections->zoneAirExhaustNodes();
    EXPECT_EQ(remainingExhaustNodes.end(),
              std::ranges::find_if(remainingExhaustNodes, [&](const Node& candidate) { return candidate.handle() == inducedNodeHandle; }));
  }

  ASSERT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());
  EXPECT_EQ(neighborSplitterOutlet->handle(), airLoop.zoneSplitter().outletModelObject(0u)->handle());
  EXPECT_EQ(neighborMixerInlet->handle(), airLoop.zoneMixer().inletModelObject(0u)->handle());
  ASSERT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(neighborZone, airLoop.thermalZones().front());
  ASSERT_EQ(1u, neighborZone.equipment().size());
  EXPECT_EQ(neighborTerminalHandle, neighborZone.equipment().front().handle());
}
