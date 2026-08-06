/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirTerminalDualDuctVAV.hpp"
#include "../Mixer/AirTerminalDualDuctVAV_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "../ModelObject/NodeList.hpp"
#include "../ModelObject/NodeList_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/AirTerminal_DualDuct_VAV_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctVAV terminal(model);
  EXPECT_EQ(AirTerminalDualDuctVAV::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_TRUE(terminal.isMaximumDamperAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.3, terminal.zoneMinimumAirFlowFraction());

  EXPECT_FALSE(terminal.getTarget(openstudio::AirTerminal_DualDuct_VAVFields::AvailabilityScheduleName));
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctVAV terminal(model);

  EXPECT_TRUE(terminal.setMaximumDamperAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumDamperAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumDamperAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumDamperAirFlowRateAutosized());

  terminal.autosizeMaximumDamperAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumDamperAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddToDualDuctAirLoop) {
  {
    Model model;
    AirLoopHVAC airLoop(model, true);
    AirTerminalDualDuctVAV terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    EXPECT_EQ(2u, airLoop.demandInletNodes().size());
    EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());

    ASSERT_TRUE(terminal.hotAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(0u));
    EXPECT_EQ(terminal.hotAirInletNode()->handle(), terminal.inletModelObject(0u)->handle());

    ASSERT_TRUE(terminal.coldAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(1u));
    EXPECT_EQ(terminal.coldAirInletNode()->handle(), terminal.inletModelObject(1u)->handle());
  }

  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAV terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());

  terminal.remove();
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  ASSERT_TRUE(zone.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), zone.airLoopHVAC()->handle());
  EXPECT_FALSE(airLoop.addBranchForZone(zone));
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctVAV terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal2));
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctVAV terminal3(model);
  ASSERT_TRUE(terminal3.setMaximumDamperAirFlowRate(2.468));
  ASSERT_TRUE(terminal3.setZoneMinimumAirFlowFraction(0.42));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal3));

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  const auto terminals = airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType());
  ASSERT_EQ(2u, terminals.size());
  auto cloneIt = std::ranges::find_if(terminals, [&](const ModelObject& candidate) { return candidate.handle() != terminal3.handle(); });
  ASSERT_NE(terminals.end(), cloneIt);
  auto clonedTerminal = cloneIt->optionalCast<AirTerminalDualDuctVAV>();
  ASSERT_TRUE(clonedTerminal);
  ASSERT_TRUE(clonedTerminal->maximumDamperAirFlowRate());
  EXPECT_DOUBLE_EQ(2.468, clonedTerminal->maximumDamperAirFlowRate().get());
  EXPECT_DOUBLE_EQ(0.42, clonedTerminal->zoneMinimumAirFlowFraction());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddBranchForZone_ReusesExistingTerminalOnlyBranch) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAV terminal(model);
  ThermalZone zone(model);
  ASSERT_TRUE(terminal.setMaximumDamperAirFlowRate(1.234));
  ASSERT_TRUE(terminal.setZoneMinimumAirFlowFraction(0.42));
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto inletNodes = connections->zoneAirInletNodes();
  const auto returnNodes = connections->zoneReturnAirNodes();
  ASSERT_EQ(1u, inletNodes.size());
  ASSERT_EQ(1u, returnNodes.size());
  EXPECT_NE(inletNodes.front().handle(), returnNodes.front().handle());
  EXPECT_EQ(terminalOutletHandle, inletNodes.front().handle());
  auto mixerInlet = airLoop.zoneMixer().inletModelObject(0u);
  ASSERT_TRUE(mixerInlet);
  EXPECT_EQ(returnNodes.front().handle(), mixerInlet->handle());
  const auto equipment = connections->zoneHVACEquipmentList().equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.handle(), equipment.front().handle());
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(terminalOutletHandle, adu.outletNode()->handle());
  ASSERT_TRUE(terminal.maximumDamperAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumDamperAirFlowRate().get());
  EXPECT_DOUBLE_EQ(0.42, terminal.zoneMinimumAirFlowFraction());

  const auto terminalHandle = terminal.handle();
  const auto aduHandle = adu.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(aduHandle));
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddBranchForZone_SynchronizesExistingAirDistributionUnit) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAV terminal(model);
  ZoneHVACAirDistributionUnit airDistributionUnit(model);
  Node staleOutletNode(model);
  auto airDistributionUnitImpl = airDistributionUnit.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(airDistributionUnitImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(airDistributionUnitImpl->setOutletNode(staleOutletNode));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_TRUE(airDistributionUnit.outletNode());
  EXPECT_EQ(terminal.outletModelObject()->handle(), airDistributionUnit.outletNode()->handle());
  EXPECT_NE(staleOutletNode.handle(), airDistributionUnit.outletNode()->handle());

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto equipment = connections->zoneHVACEquipmentList().equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(terminal.handle(), equipment.front().handle());
  const auto airDistributionUnits = terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit);
  ASSERT_EQ(1u, airDistributionUnits.size());
  EXPECT_EQ(airDistributionUnit.handle(), airDistributionUnits.front().handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddToNode_RejectsInvalidContextsAndAlreadyConnectedTerminal) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAV terminal(model);
  Node standaloneNode(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  auto zoneAirNode = zone.zoneAirNode();

  Model otherModel;
  Node foreignNode(otherModel);

  EXPECT_FALSE(terminal.addToNode(standaloneNode));
  EXPECT_FALSE(terminal.addToNode(foreignNode));
  EXPECT_FALSE(terminal.addToNode(supplyInletNode));
  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  EXPECT_FALSE(terminal.airLoopHVAC());
  EXPECT_FALSE(terminal.inletModelObject(0u));
  EXPECT_FALSE(terminal.inletModelObject(1u));
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  const auto originalHotInlet = terminal.hotAirInletNode();
  const auto originalColdInlet = terminal.coldAirInletNode();
  ASSERT_TRUE(originalHotInlet);
  ASSERT_TRUE(originalColdInlet);
  auto connectedZoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(connectedZoneAirNode));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  EXPECT_EQ(originalHotInlet->handle(), terminal.hotAirInletNode()->handle());
  EXPECT_EQ(originalColdInlet->handle(), terminal.coldAirInletNode()->handle());

  ThermalZone zone2(model);
  EXPECT_FALSE(airLoop.addBranchForZone(zone2, terminal));
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddToNode_RejectsMalformedSecondaryDemandPathWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAV terminal(model);

  auto demandInletNodeList = airLoop.getModelObjectTarget<NodeList>(openstudio::AirLoopHVACFields::DemandSideInletNodeNames);
  ASSERT_TRUE(demandInletNodeList);
  Node malformedSecondaryDemandInlet(model);
  ASSERT_TRUE(demandInletNodeList->getImpl<detail::NodeList_Impl>()->addNode(malformedSecondaryDemandInlet));
  ASSERT_EQ(2u, airLoop.demandInletNodes().size());

  auto primaryBranchObject = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(primaryBranchObject);
  auto primaryBranchNode = primaryBranchObject->optionalCast<Node>();
  ASSERT_TRUE(primaryBranchNode);
  const auto transientInletAName = primaryBranchNode->nameString() + " - " + terminal.nameString() + " Inlet 1";

  EXPECT_FALSE(terminal.addToNode(*primaryBranchNode));
  EXPECT_FALSE(terminal.inletModelObject(0u));
  EXPECT_FALSE(terminal.inletModelObject(1u));
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(transientInletAName));
  ASSERT_TRUE(airLoop.zoneSplitter().outletModelObject(0u));
  EXPECT_EQ(primaryBranchNode->handle(), airLoop.zoneSplitter().outletModelObject(0u)->handle());
  ASSERT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(malformedSecondaryDemandInlet.handle(), airLoop.demandInletNodes()[1].handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_AddToNode_DiscardsOnlyProvisionalSecondaryInfrastructure) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAV terminal(model);

  Node existingSecondaryDemandInlet(model);
  ASSERT_TRUE(existingSecondaryDemandInlet.setName(airLoop.nameString() + " Demand Inlet Node 2"));
  AirLoopHVACZoneSplitter existingSecondarySplitter(model);
  auto existingSecondarySplitterImpl = existingSecondarySplitter.getImpl<detail::AirLoopHVACZoneSplitter_Impl>();
  ASSERT_TRUE(existingSecondarySplitterImpl->setInletNode(existingSecondaryDemandInlet));
  ASSERT_TRUE(existingSecondarySplitterImpl->setString(openstudio::AirLoopHVAC_ZoneSplitterFields::Name, "", false));

  const auto existingSecondaryDemandInletHandle = existingSecondaryDemandInlet.handle();
  const auto existingSecondarySplitterHandle = existingSecondarySplitter.handle();
  const auto supplyPathCount = model.getConcreteModelObjects<AirLoopHVACSupplyPath>().size();
  auto primaryBranchObject = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(primaryBranchObject);
  auto primaryBranchNode = primaryBranchObject->optionalCast<Node>();
  ASSERT_TRUE(primaryBranchNode);

  EXPECT_FALSE(terminal.addToNode(*primaryBranchNode));
  EXPECT_FALSE(terminal.inletModelObject(0u));
  EXPECT_FALSE(terminal.inletModelObject(1u));
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  EXPECT_EQ(supplyPathCount, model.getConcreteModelObjects<AirLoopHVACSupplyPath>().size());
  EXPECT_TRUE(model.getObject(existingSecondaryDemandInletHandle));
  EXPECT_TRUE(model.getObject(existingSecondarySplitterHandle));
  EXPECT_TRUE(existingSecondarySplitter.outletModelObjects().empty());
  ASSERT_TRUE(airLoop.zoneSplitter().outletModelObject(0u));
  EXPECT_EQ(primaryBranchNode->handle(), airLoop.zoneSplitter().outletModelObject(0u)->handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_RemoveBranchForZone_WithAttachedTerminalClearsConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAV terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, equipmentList.equipment().size());
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, connections->zoneReturnAirNodes().size());
  const auto terminalHandle = terminal.handle();

  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_RemoveDirectDualDuctBranchClearsConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAV terminal(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto hotInletHandle = terminal.hotAirInletNode()->handle();
  const auto coldInletHandle = terminal.coldAirInletNode()->handle();
  const auto terminalHandle = terminal.handle();

  terminal.remove();
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getModelObject<Node>(hotInletHandle));
  EXPECT_FALSE(model.getModelObject<Node>(coldInletHandle));
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_RemoveClearsConnectivityAndSupportsReuse) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAV terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipmentList.equipment().front());
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, connections->zoneReturnAirNodes().size());
  const auto hotInletHandle = terminal.hotAirInletNode()->handle();
  const auto coldInletHandle = terminal.coldAirInletNode()->handle();
  const auto terminalHandle = terminal.handle();
  const auto airDistributionUnits = terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit);
  ASSERT_EQ(1u, airDistributionUnits.size());
  const auto airDistributionUnitHandle = airDistributionUnits.front().handle();

  terminal.remove();
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(airDistributionUnitHandle));
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_FALSE(model.getModelObject<Node>(hotInletHandle));
  EXPECT_FALSE(model.getModelObject<Node>(coldInletHandle));
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ThermalZone zone2(model);
  AirTerminalDualDuctVAV terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal2));
  ASSERT_TRUE(terminal2.airLoopHVAC());
  ASSERT_TRUE(terminal2.hotAirInletNode());
  ASSERT_TRUE(terminal2.coldAirInletNode());
  EXPECT_EQ(airLoop.handle(), terminal2.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAV::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAV_RemoveClearsStaleZoneEquipmentWithoutLoop) {
  Model model;
  ThermalZone zone(model);
  AirTerminalDualDuctVAV terminal(model);

  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  ASSERT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_FALSE(terminal.airLoopHVAC());
  const auto terminalHandle = terminal.handle();

  terminal.remove();
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
}
