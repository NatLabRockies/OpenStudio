#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../HVACComponent/HVACComponent.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeInduction_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

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
  EXPECT_FALSE(terminal.setCoolingCoil(foreignCooling.cast<HVACComponent>()));
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

  EXPECT_EQ(heatingCoil.iddObject().name(),
            terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilObjectType).get());
  EXPECT_EQ(coolingCoil.iddObject().name(),
            terminal.getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::CoolingCoilObjectType).get());
  auto terminalMixer =
    terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName);
  ASSERT_TRUE(terminalMixer);
  ASSERT_EQ(2u, terminalMixer->inletModelObjects().size());

  auto heatingInlet = heatingCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  auto heatingOutlet = heatingCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  auto coolingInlet = coolingCoil.getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName);
  auto coolingOutlet = coolingCoil.getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  EXPECT_EQ(terminal.inducedAirInletNode()->handle(), heatingInlet->handle());
  EXPECT_EQ(heatingOutlet->handle(), coolingInlet->handle());
  EXPECT_EQ(inletNode->cast<ModelObject>(), terminalMixer->inletModelObjects()[0]);
  EXPECT_EQ(coolingOutlet->cast<ModelObject>(), terminalMixer->inletModelObjects()[1]);
  EXPECT_EQ(outletNode->handle(), terminalMixer->getModelObjectTarget<Node>(terminalMixer->outletPort())->handle());

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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_AddToNodeLateFailureIsAtomicAndRetryable) {
  Model model;
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));
  const auto originalADUOutlet = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();
  auto zoneConnections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  Node preexistingInlet(model);
  ASSERT_TRUE(preexistingInlet.setName(zoneAirNode.nameString() + " - " + terminal.nameString() + " Inlet Node"));
  Node preexistingExhaust(model);
  ASSERT_TRUE(preexistingExhaust.setName(zone.nameString() + " Exhaust Node"));
  const auto originalExhaustTarget =
    zoneConnections->getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, false, true);
  const auto originalNodeCount = model.getConcreteModelObjects<Node>().size();
  const auto originalSplitterOutlet = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(originalSplitterOutlet);

  auto impl = terminal.getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl>();
  ASSERT_TRUE(impl);
  EXPECT_FALSE(
    impl->addToNode(zoneAirNode, detail::AirTerminalSingleDuctConstantVolumeFourPipeInduction_Impl::AddToNodeFailureStage::AfterTopologyPrepared));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_EQ(originalSplitterOutlet->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_TRUE(model.getObject(preexistingInlet.handle()));
  EXPECT_TRUE(model.getObject(preexistingExhaust.handle()));
  EXPECT_EQ(originalNodeCount, model.getConcreteModelObjects<Node>().size());
  const auto restoredADUOutlet = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
  EXPECT_EQ(static_cast<bool>(originalADUOutlet), static_cast<bool>(restoredADUOutlet));
  if (originalADUOutlet && restoredADUOutlet) {
    EXPECT_EQ(*originalADUOutlet, *restoredADUOutlet);
  }
  const auto restoredExhaustTarget =
    zoneConnections->getString(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName, false, true);
  EXPECT_EQ(static_cast<bool>(originalExhaustTarget), static_cast<bool>(restoredExhaustTarget));
  if (originalExhaustTarget && restoredExhaustTarget) {
    EXPECT_EQ(*originalExhaustTarget, *restoredExhaustTarget);
  }
  EXPECT_FALSE(heatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName));
  EXPECT_FALSE(coolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName));
  EXPECT_FALSE(terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName));

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  EXPECT_EQ(terminal.cast<ModelObject>(), zone.equipment().front());
  EXPECT_TRUE(terminal.getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName));
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
  EXPECT_FALSE(heatingCoil.controllerWaterCoil());
  EXPECT_FALSE(coolingCoil.controllerWaterCoil());
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

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_ConnectedCoilReplacementAndReloadMaintainAirPath) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-four-pipe-induction-path.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater originalHeatingCoil(model);
  CoilCoolingWater originalCoolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, originalHeatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(originalCoolingCoil));
  ASSERT_TRUE(terminal.setName("Reloaded Four Pipe Induction Terminal"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));

  CoilHeatingElectric unsupportedHeatingCoil(model);
  EXPECT_FALSE(terminal.setHeatingCoil(unsupportedHeatingCoil));
  EXPECT_EQ(originalHeatingCoil.handle(), terminal.heatingCoil().handle());

  CoilHeatingWater replacementHeatingCoil(model);
  CoilCoolingWater replacementCoolingCoil(model);
  ASSERT_TRUE(replacementHeatingCoil.setName("Replacement Induction Heating Coil"));
  ASSERT_TRUE(replacementCoolingCoil.setName("Replacement Induction Cooling Coil"));
  ASSERT_TRUE(terminal.setHeatingCoil(replacementHeatingCoil));
  EXPECT_FALSE(originalHeatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName));
  EXPECT_FALSE(originalHeatingCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
  ASSERT_TRUE(terminal.setCoolingCoil(replacementCoolingCoil));
  EXPECT_FALSE(originalCoolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName));
  EXPECT_FALSE(originalCoolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName));

  auto mixer =
    terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName);
  auto heatingOutlet = replacementHeatingCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  auto coolingInlet = replacementCoolingCoil.getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName);
  auto coolingOutlet = replacementCoolingCoil.getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(mixer);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  EXPECT_EQ(*heatingOutlet, *coolingInlet);
  EXPECT_EQ(coolingOutlet->cast<ModelObject>(), mixer->inletModelObjects()[1]);

  terminal.resetCoolingCoil();
  EXPECT_FALSE(replacementCoolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName));
  EXPECT_FALSE(replacementCoolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName));
  EXPECT_EQ(heatingOutlet->cast<ModelObject>(), mixer->inletModelObjects()[1]);
  ASSERT_TRUE(terminal.setCoolingCoil(replacementCoolingCoil));

  heatingOutlet = replacementHeatingCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  coolingOutlet = replacementCoolingCoil.getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingOutlet->setName("Custom Induction Heating Outlet"));
  ASSERT_TRUE(coolingOutlet->setName("Custom Induction Cooling Outlet"));
  Node extraMixerInlet(model);
  ASSERT_TRUE(extraMixerInlet.setName("Discarded Induction Extra Mixer Inlet"));
  ASSERT_TRUE(mixer->setInletModelObject(2u, extraMixerInlet.cast<ModelObject>()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedTerminal =
    loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeFourPipeInduction>("Reloaded Four Pipe Induction Terminal");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingWater>("Replacement Induction Heating Coil");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingWater>("Replacement Induction Cooling Coil");
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedHeatingCoil);
  ASSERT_TRUE(loadedCoolingCoil);
  auto loadedMixer = loadedTerminal->getModelObjectTarget<AirLoopHVACZoneMixer>(
    openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName);
  auto loadedHeatingInlet = loadedHeatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  auto loadedHeatingOutlet = loadedHeatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  auto loadedCoolingInlet = loadedCoolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName);
  auto loadedCoolingOutlet = loadedCoolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(loadedMixer);
  ASSERT_EQ(2u, loadedMixer->inletModelObjects().size());
  ASSERT_TRUE(loadedHeatingInlet);
  ASSERT_TRUE(loadedHeatingOutlet);
  ASSERT_TRUE(loadedCoolingInlet);
  ASSERT_TRUE(loadedCoolingOutlet);
  EXPECT_EQ("Custom Induction Heating Outlet", loadedHeatingOutlet->nameString());
  EXPECT_EQ("Custom Induction Cooling Outlet", loadedCoolingOutlet->nameString());
  EXPECT_EQ(loadedTerminal->inducedAirInletNode().get(), *loadedHeatingInlet);
  EXPECT_EQ(*loadedHeatingOutlet, *loadedCoolingInlet);
  EXPECT_EQ(loadedTerminal->inletModelObject().get(), loadedMixer->inletModelObjects()[0]);
  EXPECT_EQ(loadedCoolingOutlet->cast<ModelObject>(), loadedMixer->inletModelObjects()[1]);
  EXPECT_EQ(loadedTerminal->outletModelObject()->cast<Node>(), loadedMixer->getModelObjectTarget<Node>(loadedMixer->outletPort()).get());
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Extra Mixer Inlet"));

  Node wrongHeatingInlet(*loadedModel);
  Node wrongHeatingOutlet(*loadedModel);
  Node wrongCoolingInlet(*loadedModel);
  Node wrongCoolingOutlet(*loadedModel);
  Node wrongMixerOutlet(*loadedModel);
  Node wrongMixerInlet(*loadedModel);
  ASSERT_TRUE(wrongHeatingInlet.setName("Discarded Induction Wrong Heating Inlet"));
  ASSERT_TRUE(wrongHeatingOutlet.setName("Discarded Induction Wrong Heating Outlet"));
  ASSERT_TRUE(wrongCoolingInlet.setName("Discarded Induction Wrong Cooling Inlet"));
  ASSERT_TRUE(wrongCoolingOutlet.setName("Discarded Induction Wrong Cooling Outlet"));
  ASSERT_TRUE(wrongMixerOutlet.setName("Discarded Induction Wrong Mixer Outlet"));
  ASSERT_TRUE(wrongMixerInlet.setName("Discarded Induction Wrong Mixer Inlet"));
  auto loadedMixerImpl = loadedMixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
  ASSERT_TRUE(loadedMixerImpl);
  ASSERT_TRUE(loadedHeatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirInletNodeName, wrongHeatingInlet.handle()));
  ASSERT_TRUE(loadedHeatingCoil->setPointer(openstudio::Coil_Heating_WaterFields::AirOutletNodeName, wrongHeatingOutlet.handle()));
  ASSERT_TRUE(loadedCoolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirInletNodeName, wrongCoolingInlet.handle()));
  ASSERT_TRUE(loadedCoolingCoil->setPointer(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName, wrongCoolingOutlet.handle()));
  ASSERT_TRUE(loadedMixerImpl->setOutletNode(wrongMixerOutlet));
  ASSERT_TRUE(loadedMixer->setInletModelObject(1u, wrongMixerInlet.cast<ModelObject>()));
  loadedModel->canonicalize();

  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Wrong Heating Inlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Wrong Heating Outlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Wrong Cooling Inlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Wrong Cooling Outlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Wrong Mixer Outlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Induction Wrong Mixer Inlet"));
  loadedHeatingInlet = loadedHeatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirInletNodeName);
  loadedHeatingOutlet = loadedHeatingCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_WaterFields::AirOutletNodeName);
  loadedCoolingInlet = loadedCoolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirInletNodeName);
  loadedCoolingOutlet = loadedCoolingCoil->getModelObjectTarget<Node>(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName);
  ASSERT_TRUE(loadedHeatingInlet);
  ASSERT_TRUE(loadedHeatingOutlet);
  ASSERT_TRUE(loadedCoolingInlet);
  ASSERT_TRUE(loadedCoolingOutlet);
  EXPECT_EQ(loadedTerminal->inducedAirInletNode().get(), *loadedHeatingInlet);
  EXPECT_EQ(*loadedHeatingOutlet, *loadedCoolingInlet);
  EXPECT_EQ(loadedCoolingOutlet->cast<ModelObject>(), loadedMixer->inletModelObjects()[1]);
  EXPECT_EQ(loadedTerminal->outletModelObject()->cast<Node>(), loadedMixer->getModelObjectTarget<Node>(loadedMixer->outletPort()).get());

  auto loadedTerminalWorkspaceImpl = loadedTerminal->getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(loadedTerminalWorkspaceImpl);
  const auto heatingCoilField = openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName;
  ASSERT_TRUE(loadedTerminalWorkspaceImpl->setPointer(heatingCoilField, openstudio::Handle(), false));
  ASSERT_TRUE(loadedTerminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(heatingCoilField, "Missing Induction Heating Coil", false));
  EXPECT_FALSE(loadedTerminal->getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName));
  loadedModel->canonicalize();
  EXPECT_FALSE(loadedCoolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName));
  EXPECT_FALSE(loadedCoolingCoil->getTarget(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName));
  EXPECT_FALSE(loadedTerminal->getTarget(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::ZoneMixerName));
  EXPECT_TRUE(loadedTerminal->getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName, false, true)
                .value_or("")
                .empty());
  EXPECT_FALSE(loadedTerminal->inletModelObject());
  EXPECT_FALSE(loadedTerminal->inducedAirInletNode());
  EXPECT_FALSE(loadedTerminal->outletModelObject());
  EXPECT_FALSE(loadedTerminal->airLoopHVAC());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_MissingHeatingCoilRepairPreservesPlantBranches) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop hotWaterLoop(model);
  PlantLoop coldWaterLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(coldWaterLoop.addDemandBranchForComponent(coolingCoil));
  ASSERT_TRUE(heatingCoil.waterInletModelObject());
  ASSERT_TRUE(heatingCoil.waterOutletModelObject());
  ASSERT_TRUE(coolingCoil.waterInletModelObject());
  ASSERT_TRUE(coolingCoil.waterOutletModelObject());
  const auto heatingWaterInletHandle = heatingCoil.waterInletModelObject()->handle();
  const auto heatingWaterOutletHandle = heatingCoil.waterOutletModelObject()->handle();
  const auto coolingWaterInletHandle = coolingCoil.waterInletModelObject()->handle();
  const auto coolingWaterOutletHandle = coolingCoil.waterOutletModelObject()->handle();

  auto terminalWorkspaceImpl = terminal.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(terminalWorkspaceImpl);
  const auto heatingCoilField = openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeInductionFields::HeatingCoilName;
  ASSERT_TRUE(terminalWorkspaceImpl->setPointer(heatingCoilField, openstudio::Handle(), false));
  ASSERT_TRUE(terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(heatingCoilField, "Missing Induction Heating Coil", false));
  model.canonicalize();

  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.inducedAirInletNode());
  EXPECT_FALSE(terminal.getTarget(heatingCoilField));
  ASSERT_TRUE(terminal.coolingCoil());
  EXPECT_EQ(coolingCoil.handle(), terminal.coolingCoil()->handle());
  ASSERT_TRUE(heatingCoil.plantLoop());
  ASSERT_TRUE(coolingCoil.plantLoop());
  EXPECT_EQ(hotWaterLoop.handle(), heatingCoil.plantLoop()->handle());
  EXPECT_EQ(coldWaterLoop.handle(), coolingCoil.plantLoop()->handle());
  EXPECT_EQ(heatingWaterInletHandle, heatingCoil.waterInletModelObject()->handle());
  EXPECT_EQ(heatingWaterOutletHandle, heatingCoil.waterOutletModelObject()->handle());
  EXPECT_EQ(coolingWaterInletHandle, coolingCoil.waterInletModelObject()->handle());
  EXPECT_EQ(coolingWaterOutletHandle, coolingCoil.waterOutletModelObject()->handle());
  EXPECT_EQ(1u, hotWaterLoop.demandComponents(CoilHeatingWater::iddObjectType()).size());
  EXPECT_EQ(1u, coldWaterLoop.demandComponents(CoilCoolingWater::iddObjectType()).size());
  EXPECT_FALSE(coolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirInletNodeName));
  EXPECT_FALSE(coolingCoil.getTarget(openstudio::Coil_Cooling_WaterFields::AirOutletNodeName));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeInduction_ContainedWaterCoilsRemoveExistingControllersOnPlantMove) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop hotWaterLoop(model);
  PlantLoop chilledWaterLoop(model);
  ThermalZone zone(model);
  CoilHeatingWater heatingCoil(model);
  CoilCoolingWater coolingCoil(model);
  AirTerminalSingleDuctConstantVolumeFourPipeInduction terminal(model, heatingCoil);
  ASSERT_TRUE(terminal.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(hotWaterLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(chilledWaterLoop.addDemandBranchForComponent(coolingCoil));

  ControllerWaterCoil heatingController(model);
  ASSERT_TRUE(heatingController.setActuatorNode(heatingCoil.waterInletModelObject()->cast<Node>()));
  ASSERT_TRUE(heatingController.setSensorNode(heatingCoil.airOutletModelObject()->cast<Node>()));
  ASSERT_TRUE(heatingCoil.controllerWaterCoil());
  auto hotWaterDemandOutlet = hotWaterLoop.demandOutletNode();
  ASSERT_TRUE(heatingCoil.addToNode(hotWaterDemandOutlet));
  EXPECT_FALSE(heatingCoil.controllerWaterCoil());
  EXPECT_FALSE(model.getObject(heatingController.handle()));

  ControllerWaterCoil coolingController(model);
  ASSERT_TRUE(coolingController.setActuatorNode(coolingCoil.waterInletModelObject()->cast<Node>()));
  ASSERT_TRUE(coolingController.setSensorNode(coolingCoil.airOutletModelObject()->cast<Node>()));
  ASSERT_TRUE(coolingCoil.controllerWaterCoil());
  auto chilledWaterDemandOutlet = chilledWaterLoop.demandOutletNode();
  ASSERT_TRUE(coolingCoil.addToNode(chilledWaterDemandOutlet));
  EXPECT_FALSE(coolingCoil.controllerWaterCoil());
  EXPECT_FALSE(model.getObject(coolingController.handle()));
}
