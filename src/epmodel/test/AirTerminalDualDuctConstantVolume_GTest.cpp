/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Mixer/AirTerminalDualDuctConstantVolume.hpp"
#include "../Mixer/AirTerminalDualDuctConstantVolume_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/AirTerminal_DualDuct_ConstantVolume_FieldEnums.hxx>
#include <utilities/core/Path.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctConstantVolume terminal(model);
  EXPECT_EQ(AirTerminalDualDuctConstantVolume::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());

  auto availabilitySchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_ConstantVolumeFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *availabilitySchedule);
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctConstantVolume terminal(model);

  EXPECT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumAirFlowRateAutosized());

  terminal.autosizeMaximumAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumAirFlowRateAutosized());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_AddToDualDuctAirLoop) {
  {
    Model model;
    AirLoopHVAC airLoop(model, true);
    AirTerminalDualDuctConstantVolume terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    EXPECT_EQ(2u, airLoop.demandInletNodes().size());
    EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());

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
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());

  terminal.remove();
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  ASSERT_TRUE(zone.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), zone.airLoopHVAC()->handle());
  EXPECT_FALSE(airLoop.addBranchForZone(zone));
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctConstantVolume terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal2));
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctConstantVolume terminal3(model);
  ASSERT_TRUE(terminal3.setMaximumAirFlowRate(2.468));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal3));

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  const auto terminals = airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType());
  ASSERT_EQ(2u, terminals.size());
  auto cloneIt = std::ranges::find_if(terminals, [&](const ModelObject& candidate) { return candidate.handle() != terminal3.handle(); });
  ASSERT_NE(terminals.end(), cloneIt);
  auto clonedTerminal = cloneIt->optionalCast<AirTerminalDualDuctConstantVolume>();
  ASSERT_TRUE(clonedTerminal);
  ASSERT_TRUE(clonedTerminal->maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(2.468, clonedTerminal->maximumAirFlowRate().get());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_AddBranchForZone_ReusesExistingTerminalOnlyBranch) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);
  ThermalZone zone(model);
  ASSERT_TRUE(terminal.setMaximumAirFlowRate(1.234));
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());

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
  ASSERT_TRUE(terminal.maximumAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumAirFlowRate().get());

  const auto terminalHandle = terminal.handle();
  const auto aduHandle = adu.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(aduHandle));
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_TerminalFirstZoneAttachmentPreparationFailureRestoresNewState) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(zone.setUseIdealAirLoads(true));
  ASSERT_TRUE(zone.useIdealAirLoads());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalOutlet = terminal.outletModelObject()->cast<Node>();
  ASSERT_TRUE(airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_EQ(terminalOutlet.cast<ModelObject>(), *airLoop.zoneMixer().inletModelObject(0u));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  const auto baselineInletCount = connections->zoneAirInletNodes().size();
  const auto baselineReturnCount = connections->zoneReturnAirNodes().size();
  const auto baselineEquipment = connections->zoneHVACEquipmentList().equipment();
  ASSERT_EQ(1u, baselineEquipment.size());
  const auto idealLoadsHandle = baselineEquipment.front().handle();
  ASSERT_TRUE(model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>().empty());

  const auto returnNodeName = zone.nameString() + " Demand Return Node";
  ASSERT_FALSE(model.getConcreteModelObjectByName<Node>(returnNodeName));

  auto airLoopImpl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(airLoopImpl);
  EXPECT_FALSE(airLoopImpl->addBranchForZone(zone, detail::AirLoopHVAC_Impl::DualDuctZoneAttachmentFailureStage::AfterProvisionalObjectsPrepared));

  EXPECT_TRUE(zone.useIdealAirLoads());
  EXPECT_TRUE(airLoop.thermalZones().empty());
  ASSERT_TRUE(airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_EQ(terminalOutlet.cast<ModelObject>(), *airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_EQ(baselineInletCount, connections->zoneAirInletNodes().size());
  EXPECT_EQ(baselineReturnCount, connections->zoneReturnAirNodes().size());
  const auto equipment = connections->zoneHVACEquipmentList().equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(idealLoadsHandle, equipment.front().handle());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::ZoneHVAC_IdealLoadsAirSystem), equipment.front().iddObject().type());
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(returnNodeName));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>().empty());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_TerminalFirstZoneAttachmentPreparationFailurePreservesExistingState) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalOutlet = terminal.outletModelObject()->cast<Node>();

  Node existingReturnNode(model);
  ASSERT_TRUE(existingReturnNode.setName(zone.nameString() + " Demand Return Node"));
  Node originalADUOutlet(model);
  ZoneHVACAirDistributionUnit adu(model);
  auto aduImpl = adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(aduImpl);
  ASSERT_TRUE(aduImpl->setAirTerminal(terminal.cast<ModelObject>()));
  ASSERT_TRUE(aduImpl->setOutletNode(originalADUOutlet));

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentConnections();
  auto airLoopImpl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(airLoopImpl);
  EXPECT_FALSE(airLoopImpl->addBranchForZone(zone, detail::AirLoopHVAC_Impl::DualDuctZoneAttachmentFailureStage::AfterProvisionalObjectsPrepared));

  EXPECT_TRUE(model.getObject(existingReturnNode.handle()));
  EXPECT_TRUE(model.getObject(adu.handle()));
  ASSERT_TRUE(adu.outletNode());
  EXPECT_EQ(originalADUOutlet.handle(), adu.outletNode()->handle());
  ASSERT_TRUE(airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_EQ(terminalOutlet.cast<ModelObject>(), *airLoop.zoneMixer().inletModelObject(0u));
  EXPECT_TRUE(connections.zoneAirInletNodes().empty());
  EXPECT_TRUE(connections.zoneReturnAirNodes().empty());
  EXPECT_TRUE(connections.zoneHVACEquipmentList().equipment().empty());
  EXPECT_TRUE(airLoop.thermalZones().empty());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_TerminalFirstZoneAttachmentPreparationFailureRemovesNewZoneScaffold) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  ASSERT_FALSE(zoneImpl->zoneHVACEquipmentConnections());
  const auto baselineConnectionCount = model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().size();
  const auto baselineEquipmentListCount = model.getConcreteModelObjects<ZoneHVACEquipmentList>().size();
  const auto zoneAirNodeName = zone.nameString() + " Demand Branch Node";
  const auto returnNodeName = zone.nameString() + " Demand Return Node";
  ASSERT_FALSE(model.getConcreteModelObjectByName<Node>(zoneAirNodeName));
  ASSERT_FALSE(model.getConcreteModelObjectByName<Node>(returnNodeName));

  auto airLoopImpl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(airLoopImpl);
  EXPECT_FALSE(airLoopImpl->addBranchForZone(zone, detail::AirLoopHVAC_Impl::DualDuctZoneAttachmentFailureStage::AfterProvisionalObjectsPrepared));

  EXPECT_FALSE(zoneImpl->zoneHVACEquipmentConnections());
  EXPECT_EQ(baselineConnectionCount, model.getConcreteModelObjects<ZoneHVACEquipmentConnections>().size());
  EXPECT_EQ(baselineEquipmentListCount, model.getConcreteModelObjects<ZoneHVACEquipmentList>().size());
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(zoneAirNodeName));
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(returnNodeName));
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>().empty());
  EXPECT_TRUE(airLoop.thermalZones().empty());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_TerminalFirstZoneAttachmentPreparationFailurePreservesReusedZoneAirNode) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);
  ThermalZone zone(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  Node existingZoneAirNode(model);
  ASSERT_TRUE(existingZoneAirNode.setName(zone.nameString() + " Demand Branch Node"));
  auto zoneImpl = zone.getImpl<detail::ThermalZone_Impl>();
  ASSERT_TRUE(zoneImpl);
  ASSERT_FALSE(zoneImpl->zoneHVACEquipmentConnections());

  auto airLoopImpl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(airLoopImpl);
  EXPECT_FALSE(airLoopImpl->addBranchForZone(zone, detail::AirLoopHVAC_Impl::DualDuctZoneAttachmentFailureStage::AfterProvisionalObjectsPrepared));

  EXPECT_TRUE(model.getObject(existingZoneAirNode.handle()));
  EXPECT_FALSE(zoneImpl->zoneHVACEquipmentConnections());
  EXPECT_TRUE(model.getConcreteModelObjects<ZoneHVACAirDistributionUnit>().empty());
  EXPECT_TRUE(airLoop.thermalZones().empty());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_AddToNode_RejectsInvalidContextsAndAlreadyConnectedTerminal) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);
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

  EXPECT_FALSE(terminal.addToNode(zoneAirNode));
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  EXPECT_EQ(originalHotInlet->handle(), terminal.hotAirInletNode()->handle());
  EXPECT_EQ(originalColdInlet->handle(), terminal.coldAirInletNode()->handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_RemoveDirectDualDuctBranchClearsConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctConstantVolume terminal(model);

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
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_RemoveClearsConnectivityAndSupportsReuse) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipmentList.equipment().front());
  ASSERT_TRUE(terminal.hotAirInletNode());
  ASSERT_TRUE(terminal.coldAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());
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
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ThermalZone zone2(model);
  AirTerminalDualDuctConstantVolume terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal2));
  ASSERT_TRUE(terminal2.airLoopHVAC());
  ASSERT_TRUE(terminal2.hotAirInletNode());
  ASSERT_TRUE(terminal2.coldAirInletNode());
  EXPECT_EQ(airLoop.handle(), terminal2.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctConstantVolume::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_RemoveClearsStaleZoneEquipmentWithoutLoop) {
  Model model;
  ThermalZone zone(model);
  AirTerminalDualDuctConstantVolume terminal(model);

  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  ASSERT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_FALSE(terminal.airLoopHVAC());
  const auto terminalHandle = terminal.handle();

  terminal.remove();
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
}

TEST_F(EPModelFixture, AirTerminalDualDuctConstantVolume_ConnectedTopologySurvivesSaveLoadAndRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-dual-duct-terminal-connected-roundtrip.idf");

  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  AirTerminalDualDuctConstantVolume terminal1(model);
  AirTerminalDualDuctConstantVolume terminal2(model);
  ASSERT_TRUE(airLoop.setName("Roundtrip Dual Duct Air Loop"));
  ASSERT_TRUE(zone1.setName("Roundtrip Dual Duct Zone 1"));
  ASSERT_TRUE(zone2.setName("Roundtrip Dual Duct Zone 2"));
  ASSERT_TRUE(terminal1.setName("Roundtrip Dual Duct Terminal 1"));
  ASSERT_TRUE(terminal2.setName("Roundtrip Dual Duct Terminal 2"));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal1));
  ASSERT_TRUE(airLoop.addBranchForZone(zone1));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal2));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Roundtrip Dual Duct Air Loop");
  auto loadedZone1 = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip Dual Duct Zone 1");
  auto loadedZone2 = loadedModel->getConcreteModelObjectByName<ThermalZone>("Roundtrip Dual Duct Zone 2");
  auto loadedTerminal1 = loadedModel->getConcreteModelObjectByName<AirTerminalDualDuctConstantVolume>("Roundtrip Dual Duct Terminal 1");
  auto loadedTerminal2 = loadedModel->getConcreteModelObjectByName<AirTerminalDualDuctConstantVolume>("Roundtrip Dual Duct Terminal 2");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedZone1);
  ASSERT_TRUE(loadedZone2);
  ASSERT_TRUE(loadedTerminal1);
  ASSERT_TRUE(loadedTerminal2);
  ASSERT_TRUE(loadedTerminal2->hotAirInletNode());
  ASSERT_TRUE(loadedTerminal2->coldAirInletNode());

  const auto terminal1Handle = loadedTerminal1->handle();
  const auto terminal2Handle = loadedTerminal2->handle();
  const auto terminal2HotInletHandle = loadedTerminal2->hotAirInletNode()->handle();
  const auto terminal2ColdInletHandle = loadedTerminal2->coldAirInletNode()->handle();

  ASSERT_TRUE(loadedAirLoop->removeBranchForZone(*loadedZone1));
  EXPECT_FALSE(loadedModel->getObject(terminal1Handle));
  EXPECT_TRUE(loadedModel->getObject(terminal2Handle));
  ASSERT_TRUE(loadedTerminal2->hotAirInletNode());
  ASSERT_TRUE(loadedTerminal2->coldAirInletNode());
  EXPECT_EQ(terminal2HotInletHandle, loadedTerminal2->hotAirInletNode()->handle());
  EXPECT_EQ(terminal2ColdInletHandle, loadedTerminal2->coldAirInletNode()->handle());
  EXPECT_EQ(1u, loadedAirLoop->thermalZones().size());
  EXPECT_EQ(2u, loadedAirLoop->demandInletNodes().size());

  ASSERT_TRUE(loadedAirLoop->removeBranchForZone(*loadedZone2));
  EXPECT_FALSE(loadedModel->getObject(terminal2Handle));
  EXPECT_TRUE(loadedAirLoop->thermalZones().empty());
  EXPECT_EQ(1u, loadedAirLoop->demandInletNodes().size());

  openstudio::filesystem::remove(idfPath);
}
