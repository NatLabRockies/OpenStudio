/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <utilities/core/Exception.hpp>

#include "EPModelFixture.hpp"
#include "ScopedTestFailure.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "../Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include "../Schedule/ScheduleCompact.hpp"
#include "../StraightComponent/AirTerminalSingleDuctSeriesPIUReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctSeriesPIUReheat_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingGas_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanSystemModel_Impl.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include <utilities/idd/AirTerminal_SingleDuct_SeriesPIU_Reheat_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/Fan_SystemModel_FieldEnums.hxx>
#include <utilities/idd/ExtensibleIndex.hpp>
#include <utilities/idd/NodeList_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  EXPECT_EQ(AirTerminalSingleDuctSeriesPIUReheat::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_CanonicalConstructorEstablishesRequiredComponents) {
  Model model;
  FanConstantVolume fan(model);
  CoilHeatingElectric reheatCoil(model);

  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  const auto objectCountBeforeInvalidConstruction = model.objects().size();
  EXPECT_THROW({ AirTerminalSingleDuctSeriesPIUReheat invalidTerminal(model, reheatCoil, reheatCoil); }, openstudio::Exception);
  EXPECT_EQ(objectCountBeforeInvalidConstruction, model.objects().size());

  const auto objectCountBeforeInvalidReheatConstruction = model.objects().size();
  EXPECT_THROW({ AirTerminalSingleDuctSeriesPIUReheat invalidTerminal(model, fan, fan); }, openstudio::Exception);
  EXPECT_EQ(objectCountBeforeInvalidReheatConstruction, model.objects().size());
  EXPECT_TRUE(model.getObject(fan.handle()));
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Remove_DisconnectedCascadesOwnedChildren) {
  Model model;
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto reheatCoilHandle = reheatCoil.handle();

  EXPECT_FALSE(terminal.remove().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(reheatCoilHandle));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.42));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.42, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());
  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMaximumPrimaryAirFlowRate(1.05));
  ASSERT_TRUE(terminal.maximumPrimaryAirFlowRate());
  EXPECT_DOUBLE_EQ(1.05, terminal.maximumPrimaryAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumPrimaryAirFlowRateAutosized());
  terminal.autosizeMaximumPrimaryAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumPrimaryAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumPrimaryAirFlowFraction(0.39));
  ASSERT_TRUE(terminal.minimumPrimaryAirFlowFraction());
  EXPECT_DOUBLE_EQ(0.39, terminal.minimumPrimaryAirFlowFraction().get());
  EXPECT_FALSE(terminal.isMinimumPrimaryAirFlowFractionAutosized());
  terminal.autosizeMinimumPrimaryAirFlowFraction();
  EXPECT_TRUE(terminal.isMinimumPrimaryAirFlowFractionAutosized());

  EXPECT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.004));
  ASSERT_TRUE(terminal.maximumHotWaterorSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.004, terminal.maximumHotWaterorSteamFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());
  terminal.resetMaximumHotWaterorSteamFlowRate();
  EXPECT_FALSE(terminal.maximumHotWaterorSteamFlowRate());
  terminal.autosizeMaximumHotWaterorSteamFlowRate();
  EXPECT_TRUE(terminal.isMaximumHotWaterorSteamFlowRateAutosized());

  EXPECT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.0011));
  EXPECT_DOUBLE_EQ(0.0011, terminal.minimumHotWaterorSteamFlowRate());

  EXPECT_TRUE(terminal.setConvergenceTolerance(0.006));
  EXPECT_DOUBLE_EQ(0.006, terminal.convergenceTolerance());

  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  EXPECT_TRUE(terminal.setMinimumFanTurnDownRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, terminal.minimumFanTurnDownRatio());

  EXPECT_EQ("Staged", terminal.heatingControlType());
  EXPECT_TRUE(terminal.setHeatingControlType("Modulated"));
  EXPECT_EQ("Modulated", terminal.heatingControlType());

  EXPECT_TRUE(terminal.setDesignHeatingDischargeAirTemperature(34.0));
  EXPECT_DOUBLE_EQ(34.0, terminal.designHeatingDischargeAirTemperature());

  EXPECT_TRUE(terminal.setHighLimitHeatingDischargeAirTemperature(40.0));
  EXPECT_DOUBLE_EQ(40.0, terminal.highLimitHeatingDischargeAirTemperature());

  const auto fanControlTypeValues = AirTerminalSingleDuctSeriesPIUReheat::fanControlTypeValues();
  EXPECT_FALSE(fanControlTypeValues.empty());
  EXPECT_TRUE(std::find(fanControlTypeValues.begin(), fanControlTypeValues.end(), "ConstantSpeed") != fanControlTypeValues.end());

  const auto heatingControlTypeValues = AirTerminalSingleDuctSeriesPIUReheat::heatingControlTypeValues();
  EXPECT_FALSE(heatingControlTypeValues.empty());
  EXPECT_TRUE(std::find(heatingControlTypeValues.begin(), heatingControlTypeValues.end(), "Staged") != heatingControlTypeValues.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Relationships_RoundTrip) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  EXPECT_FALSE(terminal.availabilitySchedule());

  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(0.5));
  EXPECT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.availabilitySchedule());
  EXPECT_EQ(availability.handle(), terminal.availabilitySchedule()->handle());

  FanConstantVolume fan(model);
  CoilHeatingElectric reheatCoil(model);
  Node secondaryNode(model);
  EXPECT_TRUE(terminal.setFan(fan));
  EXPECT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::SecondaryAirInletNodeName, secondaryNode.handle()));
  EXPECT_EQ(fan.handle(), terminal.fan().handle());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondaryNode.handle(), terminal.secondaryAirInletNode()->handle());

  terminal.resetAvailabilitySchedule();
  EXPECT_FALSE(terminal.availabilitySchedule());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_InvalidComponentValidationAndFanControlCompatibility) {
  Model model;
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);

  FanVariableVolume variableFan(model);
  EXPECT_TRUE(terminal.setFan(variableFan));
  EXPECT_TRUE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("VariableSpeed", terminal.fanControlType());

  FanConstantVolume constantFan(model);
  EXPECT_TRUE(terminal.setFan(constantFan));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());
  EXPECT_FALSE(terminal.setFanControlType("VariableSpeed"));
  EXPECT_EQ("ConstantSpeed", terminal.fanControlType());

  Model otherModel;
  FanConstantVolume otherFan(otherModel);
  CoilHeatingElectric otherCoil(otherModel);
  EXPECT_FALSE(terminal.setFan(otherFan));
  EXPECT_FALSE(terminal.setReheatCoil(otherCoil));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_RejectsInvalidNodesAndContexts) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(terminal.airLoopHVAC());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_ZoneBranchInsertion_SyncsSecondaryAirAndFanSchedule) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanConstantVolume fan(model, availability);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());

  auto outletNode = terminal.outletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(zone.zoneAirNode(), *outletNode);

  auto inletNode = terminal.inletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  EXPECT_NE(*inletNode, *outletNode);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto splitterOutletNode = splitterOutletObject->optionalCast<Node>();
  ASSERT_TRUE(splitterOutletNode);
  EXPECT_EQ(*inletNode, *splitterOutletNode);

  auto mixerInletObject = airLoop.zoneMixer().lastInletModelObject();
  ASSERT_TRUE(mixerInletObject);
  auto mixerInletNode = mixerInletObject->optionalCast<Node>();
  ASSERT_TRUE(mixerInletNode);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(*returnAirObject, mixerInletNode->cast<ModelObject>());

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  auto secondaryNode = terminal.secondaryAirInletNode().get();
  EXPECT_NE(secondaryNode, *inletNode);
  EXPECT_NE(secondaryNode, *outletNode);

  const auto equipment = zone.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.handle(), equipment.front().handle());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  const auto exhaustNodes = zoneConnections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find(exhaustNodes, secondaryNode), exhaustNodes.end());

  auto resolvedOutletNode = adu.outletNode();
  ASSERT_TRUE(resolvedOutletNode);
  EXPECT_EQ(zone.zoneAirNode(), resolvedOutletNode.get());
  EXPECT_EQ(airLoop.availabilitySchedule().handle(), fan.availabilitySchedule().handle());

  EXPECT_EQ(reheatCoil.iddObject().name(), terminal.getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ReheatCoilObjectType).get());
  auto terminalMixer = terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName);
  ASSERT_TRUE(terminalMixer);
  ASSERT_EQ(2u, terminalMixer->inletModelObjects().size());
  EXPECT_EQ(secondaryNode.cast<ModelObject>(), terminalMixer->inletModelObjects()[0]);
  EXPECT_EQ(inletNode->cast<ModelObject>(), terminalMixer->inletModelObjects()[1]);

  auto fanInlet = fan.getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirInletNodeName);
  auto fanOutlet = fan.getModelObjectTarget<Node>(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName);
  auto reheatInlet = reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirInletNodeName);
  auto reheatOutlet = reheatCoil.getModelObjectTarget<Node>(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(reheatInlet);
  ASSERT_TRUE(reheatOutlet);
  EXPECT_EQ(fanInlet->handle(), terminalMixer->getModelObjectTarget<Node>(terminalMixer->outletPort())->handle());
  EXPECT_EQ(fanOutlet->handle(), reheatInlet->handle());
  EXPECT_EQ(outletNode->handle(), reheatOutlet->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_RejectsMismatchedZoneTopology) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  Node mismatchedMixerNode(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));
  auto zoneAirNode = zone.zoneAirNode();

  ASSERT_TRUE(airLoop.zoneMixer().setInletModelObject(0u, mismatchedMixerNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(zone.equipment().empty());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutlet->handle());
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  EXPECT_EQ(mismatchedMixerNode.handle(), mixerInlet->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNode_RejectsAlreadyConnectedTerminal) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  auto zoneAirNode = zone.zoneAirNode();
  const auto inletNodeHandle = terminal.inletModelObject()->handle();
  const auto outletNodeHandle = terminal.outletModelObject()->handle();
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();

  const auto equipmentBefore = zone.equipment();
  ASSERT_EQ(1u, equipmentBefore.size());

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(terminal.inletModelObject());
  EXPECT_EQ(inletNodeHandle, terminal.inletModelObject()->handle());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(outletNodeHandle, terminal.outletModelObject()->handle());
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  EXPECT_EQ(secondaryNodeHandle, terminal.secondaryAirInletNode()->handle());
  const auto equipmentAfter = zone.equipment();
  ASSERT_EQ(1u, equipmentAfter.size());
  EXPECT_EQ(terminal.handle(), equipmentAfter.front().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Remove_CleansZoneBranchConnectivity) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();
  ASSERT_TRUE(terminal.inletModelObject());
  const auto inletNodeHandle = terminal.inletModelObject()->handle();
  const auto fanHandle = fan.handle();
  const auto reheatCoilHandle = reheatCoil.handle();
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  auto zoneConnections = zoneImpl->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  const auto exhaustNodesBefore = zoneConnections->zoneAirExhaustNodes();
  EXPECT_NE(std::ranges::find_if(exhaustNodesBefore, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }),
            exhaustNodesBefore.end());

  auto splitterOutletBeforeRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletBeforeRemoval);
  EXPECT_EQ(inletNodeHandle, splitterOutletBeforeRemoval->handle());

  const auto containsObject = [](const std::vector<ModelObject>& objects, const ModelObject& object) {
    return std::find(objects.begin(), objects.end(), object) != objects.end();
  };
  EXPECT_TRUE(containsObject(plantLoop.demandComponents(), reheatCoil.cast<ModelObject>()));

  EXPECT_FALSE(terminal.remove().empty());

  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(reheatCoilHandle));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(containsObject(plantLoop.demandComponents(), reheatCoil.cast<ModelObject>()));

  const auto exhaustNodesAfter = zoneConnections->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
  EXPECT_FALSE(zone.airLoopHVACTerminal());

  auto splitterOutletAfterRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfterRemoval);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutletAfterRemoval->handle());

  auto mixerInletAfterRemoval = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInletAfterRemoval);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(returnAirObject->handle(), mixerInletAfterRemoval->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_Remove_ClearsPersistedADUFields) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(adu.outletNode());
  ASSERT_TRUE(adu.airTerminal());

  terminal.remove();

  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  EXPECT_FALSE(adu.airTerminal());
  auto persistedADUType = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, true);
  ASSERT_TRUE(persistedADUType);
  EXPECT_TRUE(persistedADUType->empty());
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName));
  EXPECT_FALSE(adu.getTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveFromLoop_CleansSecondaryNodeWithoutZoneRegistrationOrZoneOutlet) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();
  ASSERT_TRUE(terminal.outletModelObject());
  const auto canonicalZoneInletHandle = terminal.outletModelObject()->handle();

  ASSERT_TRUE(zone.removeEquipment(terminal));
  Node detachedOutletNode(model);
  ASSERT_TRUE(terminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName, detachedOutletNode.handle()));

  ASSERT_TRUE(terminal.removeFromLoop());

  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  const auto exhaustNodesAfter = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
  auto splitterOutletAfterRemoval = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutletAfterRemoval);
  EXPECT_EQ(canonicalZoneInletHandle, splitterOutletAfterRemoval->handle());
  EXPECT_NE(detachedOutletNode.handle(), splitterOutletAfterRemoval->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveFromLoop_RecoversStaleZoneRegistration) {
  Model model;
  ScheduleCompact availability(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));

  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  ASSERT_TRUE(terminal.setAvailabilitySchedule(availability));
  ASSERT_TRUE(terminal.setFan(fan));
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));

  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));

  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondaryNodeHandle = terminal.secondaryAirInletNode()->handle();
  ASSERT_TRUE(terminal.inletModelObject());
  const auto inletNodeHandle = terminal.inletModelObject()->handle();

  ASSERT_TRUE(zone.removeEquipment(terminal));
  EXPECT_TRUE(zone.equipment().empty());

  ASSERT_TRUE(terminal.removeFromLoop());

  auto splitterOutlet = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(splitterOutlet);
  EXPECT_EQ(zone.zoneAirNode().handle(), splitterOutlet->handle());

  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  auto returnAirObject = zone.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  EXPECT_EQ(returnAirObject->handle(), mixerInlet->handle());

  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getModelObject<Node>(secondaryNodeHandle));
  EXPECT_FALSE(model.getModelObject<Node>(inletNodeHandle));
  EXPECT_FALSE(adu.outletNode());
  EXPECT_FALSE(adu.airTerminal());
  EXPECT_FALSE(reheatCoil.plantLoop());
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_TRUE(model.getObject(fan.handle()));
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));

  const auto exhaustNodesAfter = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  EXPECT_EQ(std::ranges::find_if(exhaustNodesAfter, [&](const auto& node) { return node.handle() == secondaryNodeHandle; }), exhaustNodesAfter.end());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveFromSharedSupplyPlenumRecoversStaleOutlet) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  FanSystemModel firstFan(model);
  FanSystemModel secondFan(model);
  CoilHeatingElectric firstCoil(model);
  CoilHeatingElectric secondCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat firstTerminal(model, firstFan, firstCoil);
  AirTerminalSingleDuctSeriesPIUReheat secondTerminal(model, secondFan, secondCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(secondZone.setSupplyPlenum(plenumZone));
  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  auto supplyPlenum = plenums.front();
  ASSERT_EQ(2u, supplyPlenum.outletModelObjects().size());
  ASSERT_TRUE(firstTerminal.inletModelObject());
  ASSERT_TRUE(secondTerminal.inletModelObject());
  ASSERT_TRUE(secondTerminal.outletModelObject());
  const auto firstTerminalInletHandle = firstTerminal.inletModelObject()->handle();
  const auto secondTerminalInletHandle = secondTerminal.inletModelObject()->handle();
  const auto canonicalSecondOutletHandle = secondTerminal.outletModelObject()->handle();
  const auto plenumOutletsBefore = supplyPlenum.outletModelObjects();
  const auto secondOutletIt =
    std::ranges::find_if(plenumOutletsBefore, [&](const auto& outlet) { return outlet.handle() == secondTerminalInletHandle; });
  ASSERT_NE(plenumOutletsBefore.end(), secondOutletIt);
  const auto secondPlenumOrdinal = static_cast<unsigned>(std::distance(plenumOutletsBefore.begin(), secondOutletIt));

  ASSERT_TRUE(secondZone.removeEquipment(secondTerminal));
  Node staleOutlet(model);
  ASSERT_TRUE(secondTerminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName, staleOutlet.handle()));

  ASSERT_TRUE(secondTerminal.removeFromLoop());

  ASSERT_EQ(2u, supplyPlenum.outletModelObjects().size());
  ASSERT_TRUE(supplyPlenum.outletModelObject(secondPlenumOrdinal));
  EXPECT_EQ(canonicalSecondOutletHandle, supplyPlenum.outletModelObject(secondPlenumOrdinal)->handle());
  EXPECT_NE(staleOutlet.handle(), supplyPlenum.outletModelObject(secondPlenumOrdinal)->handle());
  const auto plenumOutletsAfter = supplyPlenum.outletModelObjects();
  EXPECT_NE(std::ranges::find_if(plenumOutletsAfter, [&](const auto& outlet) { return outlet.handle() == firstTerminalInletHandle; }),
            plenumOutletsAfter.end());
  EXPECT_TRUE(firstTerminal.inletModelObject());
  EXPECT_EQ(firstTerminalInletHandle, firstTerminal.inletModelObject()->handle());
  EXPECT_FALSE(secondTerminal.inletModelObject());
  EXPECT_FALSE(secondTerminal.outletModelObject());
  EXPECT_FALSE(secondTerminal.secondaryAirInletNode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_SharedSupplyPlenumRejectsOutletFromAnotherZone) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone plenumZone(model);
  FanSystemModel firstFan(model);
  FanSystemModel secondFan(model);
  CoilHeatingElectric firstCoil(model);
  CoilHeatingElectric secondCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat firstTerminal(model, firstFan, firstCoil);
  AirTerminalSingleDuctSeriesPIUReheat secondTerminal(model, secondFan, secondCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(firstZone, firstTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(secondZone, secondTerminal));
  ASSERT_TRUE(firstZone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(secondZone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(firstTerminal.outletModelObject());
  ASSERT_TRUE(secondTerminal.outletModelObject());
  const auto canonicalSecondOutlet = secondTerminal.outletModelObject()->cast<Node>();
  const auto firstZoneOutlet = firstTerminal.outletModelObject()->cast<Node>();
  const auto plenum = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front();
  const auto plenumOutletsBefore = plenum.outletModelObjects();
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto firstZoneEquipmentBefore = firstZone.equipment();
  const auto secondZoneEquipmentBefore = secondZone.equipment();
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  ASSERT_TRUE(secondTerminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName, firstZoneOutlet.handle()));

  EXPECT_FALSE(secondTerminal.isRemovable());
  EXPECT_FALSE(secondTerminal.removeFromLoop());
  EXPECT_FALSE(airLoop.removeBranchForZone(secondZone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_EQ(plenumOutletsBefore, plenum.outletModelObjects());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(firstZoneEquipmentBefore, firstZone.equipment());
  EXPECT_EQ(secondZoneEquipmentBefore, secondZone.equipment());
  ASSERT_TRUE(secondTerminal.outletModelObject());
  EXPECT_EQ(firstZoneOutlet.handle(), secondTerminal.outletModelObject()->handle());

  ASSERT_TRUE(secondTerminal.setPointer(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::OutletNodeName, canonicalSecondOutlet.handle()));
  EXPECT_TRUE(secondTerminal.isRemovable());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_IsRemovableDoesNotAttachRawZoneReturnNodeList) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto returnField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneReturnAirNodeorNodeListName;
  const auto returnTarget = connections->getTarget(returnField);
  ASSERT_TRUE(returnTarget);
  const auto returnNodeList = returnTarget->optionalCast<NodeList>();
  ASSERT_TRUE(returnNodeList);
  const auto returnNodeListName = returnNodeList->nameString();
  const auto returnNodesBefore = returnNodeList->nodes();
  ASSERT_EQ(1u, returnNodesBefore.size());
  const auto returnNode = returnNodesBefore.front();
  ASSERT_EQ(1u, returnNodeList->extensibleGroups().size());
  const auto returnNodeField = returnNodeList->iddObject().index(openstudio::ExtensibleIndex(0u, openstudio::NodeListExtensibleFields::NodeName));
  auto returnNodeListImpl = returnNodeList->getImpl<detail::NodeList_Impl>();
  ASSERT_TRUE(returnNodeListImpl);
  ASSERT_TRUE(returnNodeListImpl->setPointer(returnNodeField, openstudio::Handle(), false));
  ASSERT_TRUE(returnNodeListImpl->openstudio::detail::IdfObject_Impl::setString(returnNodeField, returnNode.nameString(), false));

  auto connectionsImpl = connections->getImpl<detail::ZoneHVACEquipmentConnections_Impl>();
  ASSERT_TRUE(connectionsImpl);
  ASSERT_TRUE(connectionsImpl->setPointer(returnField, openstudio::Handle(), false));
  ASSERT_TRUE(connectionsImpl->openstudio::detail::IdfObject_Impl::setString(returnField, returnNodeListName, false));
  const auto returnListSourcesBefore = returnNodeList->sources();
  EXPECT_EQ(returnListSourcesBefore.end(),
            std::ranges::find_if(returnListSourcesBefore, [&](const auto& source) { return source.handle() == connections->handle(); }));
  const auto rawReturnNameBefore = connectionsImpl->openstudio::detail::IdfObject_Impl::getString(returnField, false, true);
  ASSERT_TRUE(rawReturnNameBefore);
  EXPECT_EQ(returnNodeListName, *rawReturnNameBefore);
  const auto rawReturnNodeNameBefore = returnNodeListImpl->openstudio::detail::IdfObject_Impl::getString(returnNodeField, false, true);
  ASSERT_TRUE(rawReturnNodeNameBefore);
  EXPECT_EQ(returnNode.nameString(), *rawReturnNodeNameBefore);
  const auto returnNodeSourcesBefore = returnNode.sources();
  EXPECT_EQ(returnNodeSourcesBefore.end(),
            std::ranges::find_if(returnNodeSourcesBefore, [&](const auto& source) { return source.handle() == returnNodeList->handle(); }));
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_TRUE(terminal.isRemovable());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  const auto returnListSourcesAfter = returnNodeList->sources();
  EXPECT_EQ(returnListSourcesAfter.end(),
            std::ranges::find_if(returnListSourcesAfter, [&](const auto& source) { return source.handle() == connections->handle(); }));
  const auto rawReturnNameAfter = connectionsImpl->openstudio::detail::IdfObject_Impl::getString(returnField, false, true);
  ASSERT_TRUE(rawReturnNameAfter);
  EXPECT_EQ(returnNodeListName, *rawReturnNameAfter);
  const auto rawReturnNodeNameAfter = returnNodeListImpl->openstudio::detail::IdfObject_Impl::getString(returnNodeField, false, true);
  ASSERT_TRUE(rawReturnNodeNameAfter);
  EXPECT_EQ(returnNode.nameString(), *rawReturnNodeNameAfter);
  const auto returnNodeSourcesAfter = returnNode.sources();
  EXPECT_EQ(returnNodeSourcesAfter.end(),
            std::ranges::find_if(returnNodeSourcesAfter, [&](const auto& source) { return source.handle() == returnNodeList->handle(); }));

  const std::string missingReturnNodeName = "Missing Raw Series PIU Return Node";
  ASSERT_TRUE(returnNodeListImpl->openstudio::detail::IdfObject_Impl::setString(returnNodeField, missingReturnNodeName, false));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingReturnNodeName));
  handlesBefore.clear();
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());

  handlesAfter.clear();
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingReturnNodeName));
  const auto missingReturnNodeNameAfter = returnNodeListImpl->openstudio::detail::IdfObject_Impl::getString(returnNodeField, false, true);
  ASSERT_TRUE(missingReturnNodeNameAfter);
  EXPECT_EQ(missingReturnNodeName, *missingReturnNodeNameAfter);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_IsRemovableDoesNotAttachRawSupplyPlenumOutlet) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(zone.setSupplyPlenum(plenumZone));
  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  auto plenum = plenums.front();
  ASSERT_TRUE(terminal.inletModelObject());
  const auto terminalInlet = terminal.inletModelObject()->cast<Node>();
  const auto outlets = plenum.outletModelObjects();
  const auto outlet = std::ranges::find(outlets, terminalInlet.cast<ModelObject>());
  ASSERT_NE(outlets.end(), outlet);
  const auto outletOrdinal = static_cast<unsigned>(std::distance(outlets.begin(), outlet));
  const auto outletField = plenum.outletPort(outletOrdinal);
  auto plenumImpl = plenum.getImpl<detail::AirLoopHVACSupplyPlenum_Impl>();
  ASSERT_TRUE(plenumImpl);
  ASSERT_TRUE(plenumImpl->setPointer(outletField, openstudio::Handle(), false));
  ASSERT_TRUE(plenumImpl->openstudio::detail::IdfObject_Impl::setString(outletField, terminalInlet.nameString(), false));
  const auto inletSourcesBefore = terminalInlet.sources();
  EXPECT_EQ(inletSourcesBefore.end(),
            std::ranges::find_if(inletSourcesBefore, [&](const auto& source) { return source.handle() == plenum.handle(); }));
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  const auto rawOutletName = plenumImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
  ASSERT_TRUE(rawOutletName);
  EXPECT_EQ(terminalInlet.nameString(), *rawOutletName);
  const auto inletSourcesAfter = terminalInlet.sources();
  EXPECT_EQ(inletSourcesAfter.end(), std::ranges::find_if(inletSourcesAfter, [&](const auto& source) { return source.handle() == plenum.handle(); }));

  const std::string missingOutletName = "Missing Raw Series PIU Supply Plenum Outlet";
  ASSERT_TRUE(plenumImpl->openstudio::detail::IdfObject_Impl::setString(outletField, missingOutletName, false));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingOutletName));
  handlesBefore.clear();
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());

  handlesAfter.clear();
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingOutletName));
  const auto missingOutletNameAfter = plenumImpl->openstudio::detail::IdfObject_Impl::getString(outletField, false, true);
  ASSERT_TRUE(missingOutletNameAfter);
  EXPECT_EQ(missingOutletName, *missingOutletNameAfter);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_IsRemovableDoesNotAttachRawContainedMixerInlet) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto mixer = terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName);
  ASSERT_TRUE(mixer);
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondary = *terminal.secondaryAirInletNode();
  const auto inletField = mixer->inletPort(0u);
  auto mixerImpl = mixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
  ASSERT_TRUE(mixerImpl);
  ASSERT_TRUE(mixerImpl->setPointer(inletField, openstudio::Handle(), false));
  ASSERT_TRUE(mixerImpl->openstudio::detail::IdfObject_Impl::setString(inletField, secondary.nameString(), false));
  const auto secondarySourcesBefore = secondary.sources();
  EXPECT_EQ(secondarySourcesBefore.end(),
            std::ranges::find_if(secondarySourcesBefore, [&](const auto& source) { return source.handle() == mixer->handle(); }));
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  const auto rawInletName = mixerImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  ASSERT_TRUE(rawInletName);
  EXPECT_EQ(secondary.nameString(), *rawInletName);
  const auto secondarySourcesAfter = secondary.sources();
  EXPECT_EQ(secondarySourcesAfter.end(),
            std::ranges::find_if(secondarySourcesAfter, [&](const auto& source) { return source.handle() == mixer->handle(); }));

  const std::string missingInletName = "Missing Raw Series PIU Contained Mixer Inlet";
  ASSERT_TRUE(mixerImpl->openstudio::detail::IdfObject_Impl::setString(inletField, missingInletName, false));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingInletName));
  handlesBefore.clear();
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());

  handlesAfter.clear();
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingInletName));
  const auto missingInletNameAfter = mixerImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  ASSERT_TRUE(missingInletNameAfter);
  EXPECT_EQ(missingInletName, *missingInletNameAfter);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_IsRemovableDoesNotAttachRawTerminalInlet) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone rawZone(model);
  ThermalZone targetZone(model);
  FanSystemModel rawFan(model);
  FanSystemModel targetFan(model);
  CoilHeatingElectric rawCoil(model);
  CoilHeatingElectric targetCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat rawTerminal(model, rawFan, rawCoil);
  AirTerminalSingleDuctSeriesPIUReheat targetTerminal(model, targetFan, targetCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(rawZone, rawTerminal));
  ASSERT_TRUE(airLoop.addBranchForZone(targetZone, targetTerminal));
  ASSERT_TRUE(rawTerminal.inletModelObject());
  const auto terminalInlet = rawTerminal.inletModelObject()->cast<Node>();
  const auto inletField = rawTerminal.inletPort();
  auto terminalImpl = rawTerminal.getImpl<detail::AirTerminalSingleDuctSeriesPIUReheat_Impl>();
  ASSERT_TRUE(terminalImpl);
  ASSERT_TRUE(terminalImpl->setPointer(inletField, openstudio::Handle(), false));
  ASSERT_TRUE(terminalImpl->openstudio::detail::IdfObject_Impl::setString(inletField, terminalInlet.nameString(), false));
  const auto inletSourcesBefore = terminalInlet.sources();
  EXPECT_EQ(inletSourcesBefore.end(),
            std::ranges::find_if(inletSourcesBefore, [&](const auto& source) { return source.handle() == rawTerminal.handle(); }));
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_TRUE(targetTerminal.isRemovable());

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  const auto rawInletName = terminalImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  ASSERT_TRUE(rawInletName);
  EXPECT_EQ(terminalInlet.nameString(), *rawInletName);
  const auto inletSourcesAfter = terminalInlet.sources();
  EXPECT_EQ(inletSourcesAfter.end(),
            std::ranges::find_if(inletSourcesAfter, [&](const auto& source) { return source.handle() == rawTerminal.handle(); }));

  const std::string missingInletName = "Missing Raw Series PIU Terminal Inlet";
  ASSERT_TRUE(terminalImpl->openstudio::detail::IdfObject_Impl::setString(inletField, missingInletName, false));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingInletName));
  handlesBefore.clear();
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_TRUE(targetTerminal.isRemovable());

  handlesAfter.clear();
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(missingInletName));
  const auto missingInletNameAfter = terminalImpl->openstudio::detail::IdfObject_Impl::getString(inletField, false, true);
  ASSERT_TRUE(missingInletNameAfter);
  EXPECT_EQ(missingInletName, *missingInletNameAfter);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveAcceptsDirectZoneExhaustNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.secondaryAirInletNode());
  const auto secondary = *terminal.secondaryAirInletNode();
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto exhaustField = openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneAirExhaustNodeorNodeListName;
  const auto exhaustTarget = connections->getTarget(exhaustField);
  ASSERT_TRUE(exhaustTarget);
  auto exhaustList = exhaustTarget->optionalCast<NodeList>();
  ASSERT_TRUE(exhaustList);
  auto exhaustListImpl = exhaustList->getImpl<detail::NodeList_Impl>();
  ASSERT_TRUE(exhaustListImpl);
  ASSERT_TRUE(exhaustListImpl->removeNode(secondary));
  ASSERT_TRUE(connections->setPointer(exhaustField, secondary.handle()));
  const auto exhaustListHandle = exhaustList->handle();
  exhaustList->remove();
  EXPECT_FALSE(model.getObject(exhaustListHandle));

  EXPECT_TRUE(terminal.isRemovable());
  EXPECT_TRUE(terminal.removeFromLoop());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(connections->getTarget(exhaustField));
  EXPECT_FALSE(model.getObject(secondary.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_MalformedContainedPathPreservesAllTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  ThermalZone plenumZone(model);
  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  ASSERT_TRUE(zone.setSupplyPlenum(plenumZone));
  ASSERT_TRUE(fan.outletModelObject());
  const auto canonicalFanOutlet = fan.outletModelObject()->cast<Node>();
  Node wrongFanOutlet(model);
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), wrongFanOutlet.handle()));

  const auto plenums = model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>();
  ASSERT_EQ(1u, plenums.size());
  const auto plenumHandle = plenums.front().handle();
  const auto plenumInletBefore = plenums.front().inletModelObject();
  const auto plenumOutletsBefore = plenums.front().outletModelObjects();
  const auto splitterOutletsBefore = airLoop.zoneSplitter().outletModelObjects();
  const auto mixerInletsBefore = airLoop.zoneMixer().inletModelObjects();
  const auto zoneEquipmentBefore = zone.equipment();
  const auto plantComponentsBefore = plantLoop.demandComponents();
  const auto exhaustNodesBefore = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes();
  const auto terminalMixerBefore =
    terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName);
  ASSERT_TRUE(plenumInletBefore);
  ASSERT_TRUE(terminalMixerBefore);
  std::set<openstudio::Handle> handlesBefore;
  for (const auto& object : model.objects()) {
    handlesBefore.insert(object.handle());
  }

  EXPECT_FALSE(terminal.isRemovable());
  EXPECT_FALSE(terminal.removeFromLoop());
  EXPECT_FALSE(airLoop.removeBranchForZone(zone));

  std::set<openstudio::Handle> handlesAfter;
  for (const auto& object : model.objects()) {
    handlesAfter.insert(object.handle());
  }
  EXPECT_EQ(handlesBefore, handlesAfter);
  EXPECT_TRUE(model.getObject(plenumHandle));
  ASSERT_EQ(1u, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().size());
  ASSERT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().inletModelObject());
  EXPECT_EQ(plenumInletBefore->handle(), model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().inletModelObject()->handle());
  EXPECT_EQ(plenumOutletsBefore, model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().front().outletModelObjects());
  EXPECT_EQ(splitterOutletsBefore, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(mixerInletsBefore, airLoop.zoneMixer().inletModelObjects());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_EQ(plantComponentsBefore, plantLoop.demandComponents());
  EXPECT_EQ(exhaustNodesBefore, zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections()->zoneAirExhaustNodes());
  const auto terminalMixerAfter =
    terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName);
  ASSERT_TRUE(terminalMixerAfter);
  EXPECT_EQ(terminalMixerBefore->handle(), terminalMixerAfter->handle());
  ASSERT_TRUE(fan.outletModelObject());
  EXPECT_EQ(wrongFanOutlet.handle(), fan.outletModelObject()->handle());
  EXPECT_TRUE(reheatCoil.plantLoop());

  ASSERT_TRUE(fan.setPointer(fan.outletPort(), canonicalFanOutlet.handle()));
  EXPECT_TRUE(terminal.isRemovable());
  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminal.handle()));
  EXPECT_FALSE(model.getObject(reheatCoil.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<AirLoopHVACSupplyPlenum>().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_TerminalOnlyDirectLifecycle) {
  Model model;
  ScheduleCompact terminalSchedule(model);
  ASSERT_TRUE(terminalSchedule.setToConstantValue(0.25));
  FanSystemModel fan(model);
  ASSERT_TRUE(fan.setAvailabilitySchedule(terminalSchedule));
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  AirLoopHVAC airLoop(model);

  auto originalBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(originalBranchObject);
  auto originalBranchNode = originalBranchObject->optionalCast<Node>();
  ASSERT_TRUE(originalBranchNode);
  ASSERT_EQ(*originalBranchObject, *airLoop.zoneMixer().lastInletModelObject());

  ASSERT_TRUE(terminal.addToNode(*originalBranchNode));
  ASSERT_TRUE(terminal.inletModelObject());
  const auto firstInletHandle = terminal.inletModelObject()->handle();
  EXPECT_EQ(originalBranchNode->handle(), terminal.outletModelObject()->handle());
  EXPECT_EQ(firstInletHandle, airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().empty());
  EXPECT_EQ(airLoop.availabilitySchedule().handle(), fan.availabilitySchedule().handle());

  ASSERT_TRUE(terminal.removeFromLoop());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_FALSE(model.getObject(firstInletHandle));
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_TRUE(model.getObject(fan.handle()));
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));

  ASSERT_TRUE(terminal.addToNode(*originalBranchNode));
  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto coilHandle = reheatCoil.handle();
  EXPECT_FALSE(terminal.remove().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_HighLevelTerminalOnlySecondBranchDoesNotInventZoneState) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  const auto zoneEquipmentBefore = zone.equipment();

  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(0.5));
  FanConstantVolume fan(model, schedule);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  ASSERT_EQ(2u, airLoop.zoneMixer().inletModelObjects().size());
  ASSERT_TRUE(terminal.inletModelObject());
  ASSERT_TRUE(terminal.outletModelObject());
  EXPECT_EQ(terminal.inletModelObject()->handle(), airLoop.zoneSplitter().outletModelObject(1u)->handle());
  EXPECT_EQ(terminal.outletModelObject()->handle(), airLoop.zoneMixer().inletModelObject(1u)->handle());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_EQ(zoneEquipmentBefore, zone.equipment());
  EXPECT_TRUE(zone.airLoopHVACTerminals().empty());

  ASSERT_TRUE(terminal.removeFromLoop());
  EXPECT_FALSE(reheatCoil.plantLoop());
  EXPECT_TRUE(model.getObject(reheatCoil.handle()));
  auto secondSplitterOutlet = airLoop.zoneSplitter().outletModelObject(1u);
  auto secondMixerInlet = airLoop.zoneMixer().inletModelObject(1u);
  ASSERT_TRUE(secondSplitterOutlet);
  ASSERT_TRUE(secondMixerInlet);
  EXPECT_EQ(*secondSplitterOutlet, *secondMixerInlet);
  EXPECT_TRUE(model.getObject(terminal.handle()));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNodeFailureIsAtomicAndRetryable) {
  Model model;
  ScheduleCompact terminalSchedule(model);
  ASSERT_TRUE(terminalSchedule.setToConstantValue(0.2));
  FanSystemModel fan(model);
  ASSERT_TRUE(fan.setAvailabilitySchedule(terminalSchedule));
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  const std::string unresolvedFanSchedule = "Persisted Missing Series PIU Fan Schedule";
  auto fanWorkspaceImpl = fan.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(fanWorkspaceImpl);
  ASSERT_TRUE(fanWorkspaceImpl->setPointer(openstudio::Fan_SystemModelFields::AvailabilityScheduleName, openstudio::Handle(), false));
  ASSERT_TRUE(fanWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(
    openstudio::Fan_SystemModelFields::AvailabilityScheduleName, unresolvedFanSchedule, false));
  EXPECT_FALSE(fan.getTarget(openstudio::Fan_SystemModelFields::AvailabilityScheduleName));
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));
  Node originalADUOutlet(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(originalADUOutlet));

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();
  auto zoneConnections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(zoneConnections);
  Node preexistingInletNode(model);
  ASSERT_TRUE(preexistingInletNode.setName(zoneAirNode.nameString() + " - " + terminal.nameString() + " Inlet Node"));
  Node preexistingSecondaryNode(model);
  ASSERT_TRUE(preexistingSecondaryNode.setName(zoneAirNode.nameString() + " - " + terminal.nameString() + " Secondary Air Inlet Node"));
  const auto exhaustNodesBefore = zoneConnections->zoneAirExhaustNodes();
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::SeriesPIUAfterTopologyPrepared);
    EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  }

  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_EQ(zoneAirNode.handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(exhaustNodesBefore, zoneConnections->zoneAirExhaustNodes());
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_TRUE(model.getObject(preexistingInletNode.handle()));
  EXPECT_TRUE(model.getObject(preexistingSecondaryNode.handle()));
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(originalADUOutlet.handle(), adu.outletNode()->handle());
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_FALSE(fan.getTarget(openstudio::Fan_SystemModelFields::AvailabilityScheduleName));
  const auto restoredFanSchedule = fanWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(
    openstudio::Fan_SystemModelFields::AvailabilityScheduleName, false, true);
  ASSERT_TRUE(restoredFanSchedule);
  EXPECT_EQ(unresolvedFanSchedule, *restoredFanSchedule);

  ASSERT_TRUE(terminal.addToNode(zoneAirNode));
  EXPECT_TRUE(terminal.secondaryAirInletNode());
  ASSERT_EQ(1u, zone.airLoopHVACTerminals().size());
  EXPECT_EQ(terminal.handle(), zone.airLoopHVACTerminals().front().handle());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_AddToNodeFailureRestoresUnresolvedADUOutletText) {
  Model model;
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  const std::string staleOutletName = "Persisted Missing PIU Outlet Node";
  ASSERT_TRUE(aduImpl->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, staleOutletName, false));
  const auto originalOutletName = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
  ASSERT_TRUE(originalOutletName);
  EXPECT_EQ(staleOutletName, *originalOutletName);

  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  auto zoneAirNode = zone.zoneAirNode();

  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::SeriesPIUAfterTopologyPrepared);
    EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  }

  const auto restoredOutletName = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, false, true);
  ASSERT_TRUE(restoredOutletName);
  EXPECT_EQ(staleOutletName, *restoredOutletName);
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_TRUE(zone.equipment().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_RemoveBranchForZoneDeletesTerminalAndOwnedTopology) {
  Model model;
  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(1.0));
  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  const auto terminalHandle = terminal.handle();
  const auto fanHandle = fan.handle();
  const auto coilHandle = reheatCoil.handle();
  const auto secondaryHandle = terminal.secondaryAirInletNode()->handle();

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(fanHandle));
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_FALSE(model.getObject(secondaryHandle));
  EXPECT_TRUE(zone.equipment().empty());
  EXPECT_FALSE(zone.airLoopHVACTerminal());
  EXPECT_TRUE(plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_TerminalOnlyFailureRemovesCreatedTopology) {
  Model model;
  ScheduleCompact schedule(model);
  ASSERT_TRUE(schedule.setToConstantValue(0.3));
  FanSystemModel fan(model);
  CoilHeatingElectric reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  AirLoopHVAC airLoop(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  const auto nodeCountBefore = model.getConcreteModelObjects<Node>().size();

  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::SeriesPIUAfterTopologyPrepared);
    EXPECT_FALSE(terminal.addToNode(*branchNode));
  }
  EXPECT_EQ(nodeCountBefore, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(branchNode->handle(), airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(branchNode->handle(), airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());

  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_FALSE(terminal.secondaryAirInletNode());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_MissingRequiredChildrenRejectsInsertionWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model);
  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  const auto originalBranchHandle = branchNode->handle();
  const auto originalNodeCount = model.getConcreteModelObjects<Node>().size();

  EXPECT_FALSE(terminal.addToNode(*branchNode));
  EXPECT_EQ(originalNodeCount, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  FanSystemModel fan(model);
  ASSERT_TRUE(terminal.setFan(fan));
  const auto nodeCountWithFan = model.getConcreteModelObjects<Node>().size();
  EXPECT_FALSE(airLoop.addBranchForHVACComponent(terminal));
  EXPECT_EQ(nodeCountWithFan, model.getConcreteModelObjects<Node>().size());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneSplitter().lastOutletModelObject()->handle());
  EXPECT_EQ(originalBranchHandle, airLoop.zoneMixer().lastInletModelObject()->handle());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());

  CoilHeatingElectric reheatCoil(model);
  ASSERT_TRUE(terminal.setReheatCoil(reheatCoil));
  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_ConnectedChildReplacementAndReloadMaintainAirPath) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-series-piu-path.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  FanConstantVolume originalFan(model);
  CoilHeatingElectric originalCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, originalFan, originalCoil);
  ASSERT_TRUE(terminal.setName("Reloaded Series PIU Terminal"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));

  FanSystemModel replacementFan(model);
  CoilHeatingGas replacementCoil(model);
  ASSERT_TRUE(replacementFan.setName("Replacement Series PIU Fan"));
  ASSERT_TRUE(replacementCoil.setName("Replacement Series PIU Coil"));
  ASSERT_TRUE(terminal.setFan(replacementFan));
  ASSERT_TRUE(terminal.setReheatCoil(replacementCoil));
  EXPECT_FALSE(originalFan.getTarget(openstudio::Fan_ConstantVolumeFields::AirInletNodeName));
  EXPECT_FALSE(originalFan.getTarget(openstudio::Fan_ConstantVolumeFields::AirOutletNodeName));
  EXPECT_FALSE(originalCoil.getTarget(openstudio::Coil_Heating_ElectricFields::AirInletNodeName));
  EXPECT_FALSE(originalCoil.getTarget(openstudio::Coil_Heating_ElectricFields::AirOutletNodeName));

  auto mixer = terminal.getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName);
  auto mixerOutlet = mixer ? mixer->getModelObjectTarget<Node>(mixer->outletPort()) : boost::optional<Node>{};
  auto fanOutlet = replacementFan.getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName);
  ASSERT_TRUE(mixer);
  ASSERT_TRUE(mixerOutlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(mixerOutlet->setName("Custom Series Mixer Outlet"));
  ASSERT_TRUE(fanOutlet->setName("Custom Series Fan Outlet"));
  Node extraMixerInlet(model);
  ASSERT_TRUE(extraMixerInlet.setName("Discarded Series Extra Mixer Inlet"));
  ASSERT_TRUE(mixer->setInletModelObject(2u, extraMixerInlet.cast<ModelObject>()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctSeriesPIUReheat>("Reloaded Series PIU Terminal");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanSystemModel>("Replacement Series PIU Fan");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Replacement Series PIU Coil");
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedFan);
  ASSERT_TRUE(loadedCoil);
  auto loadedMixer =
    loadedTerminal->getModelObjectTarget<AirLoopHVACZoneMixer>(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName);
  auto loadedFanInlet = loadedFan->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName);
  auto loadedFanOutlet = loadedFan->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName);
  auto loadedCoilInlet = loadedCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName);
  auto loadedCoilOutlet = loadedCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName);
  ASSERT_TRUE(loadedMixer);
  ASSERT_EQ(2u, loadedMixer->inletModelObjects().size());
  ASSERT_TRUE(loadedFanInlet);
  ASSERT_TRUE(loadedFanOutlet);
  ASSERT_TRUE(loadedCoilInlet);
  ASSERT_TRUE(loadedCoilOutlet);
  EXPECT_EQ("Custom Series Mixer Outlet", loadedFanInlet->nameString());
  EXPECT_EQ("Custom Series Fan Outlet", loadedFanOutlet->nameString());
  EXPECT_EQ(loadedTerminal->secondaryAirInletNode()->cast<ModelObject>(), loadedMixer->inletModelObjects()[0]);
  EXPECT_EQ(loadedTerminal->inletModelObject().get(), loadedMixer->inletModelObjects()[1]);
  EXPECT_EQ(*loadedFanInlet, loadedMixer->getModelObjectTarget<Node>(loadedMixer->outletPort()).get());
  EXPECT_EQ(*loadedFanOutlet, *loadedCoilInlet);
  EXPECT_EQ(loadedTerminal->outletModelObject()->cast<Node>(), *loadedCoilOutlet);
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Series Extra Mixer Inlet"));

  Node wrongMixerOutlet(*loadedModel);
  Node wrongFanInlet(*loadedModel);
  Node wrongFanOutlet(*loadedModel);
  Node wrongCoilInlet(*loadedModel);
  Node wrongCoilOutlet(*loadedModel);
  ASSERT_TRUE(wrongMixerOutlet.setName("Discarded Series Wrong Mixer Outlet"));
  ASSERT_TRUE(wrongFanInlet.setName("Discarded Series Wrong Fan Inlet"));
  ASSERT_TRUE(wrongFanOutlet.setName("Discarded Series Wrong Fan Outlet"));
  ASSERT_TRUE(wrongCoilInlet.setName("Discarded Series Wrong Coil Inlet"));
  ASSERT_TRUE(wrongCoilOutlet.setName("Discarded Series Wrong Coil Outlet"));
  auto loadedMixerImpl = loadedMixer->getImpl<detail::AirLoopHVACZoneMixer_Impl>();
  ASSERT_TRUE(loadedMixerImpl);
  ASSERT_TRUE(loadedMixerImpl->setOutletNode(wrongMixerOutlet));
  ASSERT_TRUE(loadedFan->setPointer(openstudio::Fan_SystemModelFields::AirInletNodeName, wrongFanInlet.handle()));
  ASSERT_TRUE(loadedFan->setPointer(openstudio::Fan_SystemModelFields::AirOutletNodeName, wrongFanOutlet.handle()));
  ASSERT_TRUE(loadedCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirInletNodeName, wrongCoilInlet.handle()));
  ASSERT_TRUE(loadedCoil->setPointer(openstudio::Coil_Heating_FuelFields::AirOutletNodeName, wrongCoilOutlet.handle()));
  loadedModel->canonicalize();

  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Series Wrong Mixer Outlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Series Wrong Fan Inlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Series Wrong Fan Outlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Series Wrong Coil Inlet"));
  EXPECT_FALSE(loadedModel->getConcreteModelObjectByName<Node>("Discarded Series Wrong Coil Outlet"));
  loadedFanInlet = loadedFan->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirInletNodeName);
  loadedFanOutlet = loadedFan->getModelObjectTarget<Node>(openstudio::Fan_SystemModelFields::AirOutletNodeName);
  loadedCoilInlet = loadedCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirInletNodeName);
  loadedCoilOutlet = loadedCoil->getModelObjectTarget<Node>(openstudio::Coil_Heating_FuelFields::AirOutletNodeName);
  ASSERT_TRUE(loadedFanInlet);
  ASSERT_TRUE(loadedFanOutlet);
  ASSERT_TRUE(loadedCoilInlet);
  ASSERT_TRUE(loadedCoilOutlet);
  EXPECT_EQ(*loadedFanInlet, loadedMixer->getModelObjectTarget<Node>(loadedMixer->outletPort()).get());
  EXPECT_EQ(*loadedFanOutlet, *loadedCoilInlet);
  EXPECT_EQ(loadedTerminal->outletModelObject()->cast<Node>(), *loadedCoilOutlet);

  auto loadedTerminalWorkspaceImpl = loadedTerminal->getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(loadedTerminalWorkspaceImpl);
  const auto fanField = openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName;
  ASSERT_TRUE(loadedTerminalWorkspaceImpl->setPointer(fanField, openstudio::Handle(), false));
  ASSERT_TRUE(loadedTerminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(fanField, "Missing Series PIU Fan", false));
  EXPECT_FALSE(loadedTerminal->getTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName));
  loadedModel->canonicalize();
  EXPECT_FALSE(loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::AirInletNodeName));
  EXPECT_FALSE(loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::AirOutletNodeName));
  EXPECT_FALSE(loadedTerminal->getTarget(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::ZoneMixerName));
  EXPECT_TRUE(loadedTerminal->getString(openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName, false, true).value_or("").empty());
  EXPECT_FALSE(loadedTerminal->inletModelObject());
  EXPECT_FALSE(loadedTerminal->secondaryAirInletNode());
  EXPECT_FALSE(loadedTerminal->outletModelObject());
  EXPECT_FALSE(loadedTerminal->airLoopHVAC());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctSeriesPIUReheat_MissingFanRepairPreservesReheatPlantBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ThermalZone zone(model);
  FanSystemModel fan(model);
  CoilHeatingWater reheatCoil(model);
  AirTerminalSingleDuctSeriesPIUReheat terminal(model, fan, reheatCoil);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(reheatCoil));
  ASSERT_TRUE(reheatCoil.waterInletModelObject());
  ASSERT_TRUE(reheatCoil.waterOutletModelObject());
  const auto waterInletHandle = reheatCoil.waterInletModelObject()->handle();
  const auto waterOutletHandle = reheatCoil.waterOutletModelObject()->handle();

  auto terminalWorkspaceImpl = terminal.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(terminalWorkspaceImpl);
  const auto fanField = openstudio::AirTerminal_SingleDuct_SeriesPIU_ReheatFields::FanName;
  ASSERT_TRUE(terminalWorkspaceImpl->setPointer(fanField, openstudio::Handle(), false));
  ASSERT_TRUE(terminalWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(fanField, "Missing Series PIU Fan", false));
  model.canonicalize();

  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletModelObject());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(terminal.secondaryAirInletNode());
  EXPECT_EQ(reheatCoil.handle(), terminal.reheatCoil().handle());
  ASSERT_TRUE(reheatCoil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), reheatCoil.plantLoop()->handle());
  EXPECT_EQ(waterInletHandle, reheatCoil.waterInletModelObject()->handle());
  EXPECT_EQ(waterOutletHandle, reheatCoil.waterOutletModelObject()->handle());
  EXPECT_EQ(1u, plantLoop.demandComponents(CoilHeatingWater::iddObjectType()).size());
  EXPECT_FALSE(reheatCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirInletNodeName));
  EXPECT_FALSE(reheatCoil.getTarget(openstudio::Coil_Heating_WaterFields::AirOutletNodeName));
}
