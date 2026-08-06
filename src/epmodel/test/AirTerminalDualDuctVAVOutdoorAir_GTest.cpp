/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp"
#include "../Mixer/AirTerminalDualDuctVAVOutdoorAir_Impl.hpp"
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
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/AirTerminal_DualDuct_VAV_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_DefaultConstructor) {
  Model model;
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  EXPECT_EQ(AirTerminalDualDuctVAVOutdoorAir::iddObjectType(), terminal.iddObject().type());
  EXPECT_FALSE(terminal.nameString().empty());

  EXPECT_TRUE(terminal.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("CurrentOccupancy", terminal.perPersonVentilationRateMode());

  auto availabilitySchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *availabilitySchedule);
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  EXPECT_TRUE(terminal.setMaximumTerminalAirFlowRate(1.234));
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumTerminalAirFlowRateAutosized());

  terminal.autosizeMaximumTerminalAirFlowRate();
  EXPECT_TRUE(terminal.isMaximumTerminalAirFlowRateAutosized());

  EXPECT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());

  EXPECT_FALSE(terminal.setPerPersonVentilationRateMode("InvalidChoice"));

  const auto values = AirTerminalDualDuctVAVOutdoorAir::perPersonVentilationRateModeValues();
  EXPECT_FALSE(values.empty());
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "CurrentOccupancy"));
  EXPECT_NE(values.end(), std::find(values.begin(), values.end(), "DesignOccupancy"));
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddToDualDuctAirLoop) {
  {
    Model model;
    AirLoopHVAC airLoop(model, true);
    AirTerminalDualDuctVAVOutdoorAir terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    EXPECT_EQ(2u, airLoop.demandInletNodes().size());
    EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());

    ASSERT_TRUE(terminal.outdoorAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(0u));
    EXPECT_EQ(terminal.outdoorAirInletNode()->handle(), terminal.inletModelObject(0u)->handle());

    ASSERT_TRUE(terminal.recirculatedAirInletNode());
    ASSERT_TRUE(terminal.inletModelObject(1u));
    EXPECT_EQ(terminal.recirculatedAirInletNode()->handle(), terminal.inletModelObject(1u)->handle());
  }

  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.outdoorAirInletNode());
  ASSERT_TRUE(terminal.recirculatedAirInletNode());
  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  const auto outletHandle = outletNode->handle();
  ASSERT_TRUE(outletNode->setName("Renamed Dual Duct VAV Outdoor Air Outlet Node"));

  outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(outletHandle, outletNode->handle());
  EXPECT_EQ("Renamed Dual Duct VAV Outdoor Air Outlet Node", outletNode->nameString());
  ASSERT_TRUE(terminal.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), terminal.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());

  terminal.remove();
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  ASSERT_TRUE(zone.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), zone.airLoopHVAC()->handle());
  EXPECT_FALSE(airLoop.addBranchForZone(zone));
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctVAVOutdoorAir terminal2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal2));
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  AirTerminalDualDuctVAVOutdoorAir terminal3(model);
  ASSERT_TRUE(terminal3.setMaximumTerminalAirFlowRate(2.468));
  ASSERT_TRUE(terminal3.setPerPersonVentilationRateMode("DesignOccupancy"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal3));

  ThermalZone zone2(model);
  ASSERT_TRUE(airLoop.addBranchForZone(zone2));
  const auto terminals = airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType());
  ASSERT_EQ(2u, terminals.size());
  auto cloneIt = std::ranges::find_if(terminals, [&](const ModelObject& candidate) { return candidate.handle() != terminal3.handle(); });
  ASSERT_NE(terminals.end(), cloneIt);
  auto clonedTerminal = cloneIt->optionalCast<AirTerminalDualDuctVAVOutdoorAir>();
  ASSERT_TRUE(clonedTerminal);
  ASSERT_TRUE(clonedTerminal->maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(2.468, clonedTerminal->maximumTerminalAirFlowRate().get());
  EXPECT_EQ("DesignOccupancy", clonedTerminal->perPersonVentilationRateMode());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddBranchForZone_ReusesExistingTerminalOnlyBranch) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  ThermalZone zone(model);
  ASSERT_TRUE(terminal.setMaximumTerminalAirFlowRate(1.234));
  ASSERT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  ZoneHVACAirDistributionUnit adu(model);
  ASSERT_TRUE(adu.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setAirTerminal(terminal.cast<ModelObject>()));

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.outletModelObject());
  const auto terminalOutletHandle = terminal.outletModelObject()->handle();

  ASSERT_TRUE(airLoop.addBranchForZone(zone));
  EXPECT_EQ(1u, airLoop.thermalZones().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());

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
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());

  const auto terminalHandle = terminal.handle();
  const auto aduHandle = adu.handle();
  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(aduHandle));
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddBranchForZone_SynchronizesExistingAirDistributionUnit) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  ZoneHVACAirDistributionUnit airDistributionUnit(model);
  Node staleOutletNode(model);
  auto airDistributionUnitImpl = airDistributionUnit.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(airDistributionUnitImpl);
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

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddToNode_RejectsInvalidContextsAndAlreadyConnectedTerminal) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  ASSERT_TRUE(terminal.setMaximumTerminalAirFlowRate(1.234));
  ASSERT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  auto expectedAvailabilitySchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(expectedAvailabilitySchedule);
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
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());
  auto availabilitySchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(expectedAvailabilitySchedule->handle(), availabilitySchedule->handle());

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  const auto originalOutdoorAirInlet = terminal.outdoorAirInletNode();
  const auto originalRecirculatedAirInlet = terminal.recirculatedAirInletNode();
  ASSERT_TRUE(originalOutdoorAirInlet);
  ASSERT_TRUE(originalRecirculatedAirInlet);
  auto connectedZoneAirNode = zone.zoneAirNode();

  EXPECT_FALSE(terminal.addToNode(connectedZoneAirNode));
  ASSERT_TRUE(terminal.outdoorAirInletNode());
  ASSERT_TRUE(terminal.recirculatedAirInletNode());
  EXPECT_EQ(originalOutdoorAirInlet->handle(), terminal.outdoorAirInletNode()->handle());
  EXPECT_EQ(originalRecirculatedAirInlet->handle(), terminal.recirculatedAirInletNode()->handle());
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());
  availabilitySchedule = terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(expectedAvailabilitySchedule->handle(), availabilitySchedule->handle());

  ThermalZone zone2(model);
  EXPECT_FALSE(airLoop.addBranchForZone(zone2, terminal));
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, terminal.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());
  availabilitySchedule = terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(expectedAvailabilitySchedule->handle(), availabilitySchedule->handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddToNode_RejectsMalformedSecondaryDemandPathWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  ASSERT_TRUE(terminal.setMaximumTerminalAirFlowRate(1.234));
  ASSERT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));

  auto demandInletNodeList = airLoop.getModelObjectTarget<NodeList>(openstudio::AirLoopHVACFields::DemandSideInletNodeNames);
  ASSERT_TRUE(demandInletNodeList);
  Node malformedSecondaryDemandInlet(model);
  ASSERT_TRUE(demandInletNodeList->getImpl<detail::NodeList_Impl>()->addNode(malformedSecondaryDemandInlet));
  ASSERT_EQ(2u, airLoop.demandInletNodes().size());

  auto primaryBranchObject = airLoop.zoneSplitter().outletModelObject(0u);
  ASSERT_TRUE(primaryBranchObject);
  auto primaryBranchNode = primaryBranchObject->optionalCast<Node>();
  ASSERT_TRUE(primaryBranchNode);
  const auto transientOutdoorInletName = primaryBranchNode->nameString() + " - " + terminal.nameString() + " Inlet 1";

  EXPECT_FALSE(terminal.addToNode(*primaryBranchNode));
  EXPECT_FALSE(terminal.outdoorAirInletNode());
  EXPECT_FALSE(terminal.recirculatedAirInletNode());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_FALSE(model.getConcreteModelObjectByName<Node>(transientOutdoorInletName));
  ASSERT_TRUE(airLoop.zoneSplitter().outletModelObject(0u));
  EXPECT_EQ(primaryBranchNode->handle(), airLoop.zoneSplitter().outletModelObject(0u)->handle());
  ASSERT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(malformedSecondaryDemandInlet.handle(), airLoop.demandInletNodes()[1].handle());
  ASSERT_TRUE(terminal.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(1.234, *terminal.maximumTerminalAirFlowRate());
  EXPECT_EQ("DesignOccupancy", terminal.perPersonVentilationRateMode());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_AddToNode_DiscardsOnlyProvisionalSecondaryInfrastructure) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  Node existingSecondaryDemandInlet(model);
  ASSERT_TRUE(existingSecondaryDemandInlet.setName(airLoop.nameString() + " Demand Inlet Node 2"));
  AirLoopHVACZoneSplitter existingSecondarySplitter(model);
  auto existingSecondarySplitterImpl = existingSecondarySplitter.getImpl<detail::AirLoopHVACZoneSplitter_Impl>();
  ASSERT_TRUE(existingSecondarySplitterImpl);
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
  EXPECT_FALSE(terminal.outdoorAirInletNode());
  EXPECT_FALSE(terminal.recirculatedAirInletNode());
  EXPECT_FALSE(terminal.outletModelObject());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
  EXPECT_EQ(supplyPathCount, model.getConcreteModelObjects<AirLoopHVACSupplyPath>().size());
  EXPECT_TRUE(model.getObject(existingSecondaryDemandInletHandle));
  EXPECT_TRUE(model.getObject(existingSecondarySplitterHandle));
  EXPECT_TRUE(existingSecondarySplitter.outletModelObjects().empty());
  ASSERT_TRUE(airLoop.zoneSplitter().outletModelObject(0u));
  EXPECT_EQ(primaryBranchNode->handle(), airLoop.zoneSplitter().outletModelObject(0u)->handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_RemoveBranchForZone_WithAttachedTerminalClearsConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

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
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_RemoveDirectDualDuctBranchClearsConnectivity) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
  ASSERT_TRUE(terminal.airLoopHVAC());
  ASSERT_TRUE(terminal.outdoorAirInletNode());
  ASSERT_TRUE(terminal.recirculatedAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());
  const auto outdoorInletHandle = terminal.outdoorAirInletNode()->handle();
  const auto recirculatedInletHandle = terminal.recirculatedAirInletNode()->handle();
  const auto terminalHandle = terminal.handle();

  terminal.remove();
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getModelObject<Node>(outdoorInletHandle));
  EXPECT_FALSE(model.getModelObject<Node>(recirculatedInletHandle));
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_RemoveClearsConnectivityAndSupportsReuse) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);
  ASSERT_TRUE(terminal.setMaximumTerminalAirFlowRate(2.468));
  ASSERT_TRUE(terminal.setPerPersonVentilationRateMode("DesignOccupancy"));
  auto expectedAvailabilitySchedule =
    terminal.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(expectedAvailabilitySchedule);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_EQ(terminal.cast<ModelObject>(), equipmentList.equipment().front());
  ASSERT_TRUE(terminal.outdoorAirInletNode());
  ASSERT_TRUE(terminal.recirculatedAirInletNode());
  ASSERT_TRUE(terminal.outletModelObject());
  ASSERT_EQ(1u, connections->zoneAirInletNodes().size());
  ASSERT_EQ(1u, connections->zoneReturnAirNodes().size());
  const auto outdoorInletHandle = terminal.outdoorAirInletNode()->handle();
  const auto recirculatedInletHandle = terminal.recirculatedAirInletNode()->handle();
  const auto terminalHandle = terminal.handle();
  const auto airDistributionUnits = terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit);
  ASSERT_EQ(1u, airDistributionUnits.size());
  const auto airDistributionUnitHandle = airDistributionUnits.front().handle();

  terminal.remove();
  EXPECT_FALSE(model.getObject(terminalHandle));
  EXPECT_FALSE(model.getObject(airDistributionUnitHandle));
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_FALSE(model.getModelObject<Node>(outdoorInletHandle));
  EXPECT_FALSE(model.getModelObject<Node>(recirculatedInletHandle));
  EXPECT_EQ(0u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ASSERT_TRUE(airLoop.removeBranchForZone(zone));
  EXPECT_TRUE(connections->zoneAirInletNodes().empty());
  EXPECT_TRUE(connections->zoneReturnAirNodes().empty());
  EXPECT_EQ(1u, airLoop.demandInletNodes().size());

  ThermalZone zone2(model);
  AirTerminalDualDuctVAVOutdoorAir terminal2(model);
  ASSERT_TRUE(terminal2.setMaximumTerminalAirFlowRate(2.468));
  ASSERT_TRUE(terminal2.setPerPersonVentilationRateMode("DesignOccupancy"));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal2));
  ASSERT_TRUE(terminal2.airLoopHVAC());
  ASSERT_TRUE(terminal2.outdoorAirInletNode());
  ASSERT_TRUE(terminal2.recirculatedAirInletNode());
  EXPECT_EQ(airLoop.handle(), terminal2.airLoopHVAC()->handle());
  EXPECT_EQ(2u, airLoop.demandInletNodes().size());
  EXPECT_EQ(1u, airLoop.demandComponents(AirTerminalDualDuctVAVOutdoorAir::iddObjectType()).size());
  ASSERT_TRUE(terminal2.maximumTerminalAirFlowRate());
  EXPECT_DOUBLE_EQ(2.468, terminal2.maximumTerminalAirFlowRate().get());
  EXPECT_FALSE(terminal2.isMaximumTerminalAirFlowRateAutosized());
  EXPECT_EQ("DesignOccupancy", terminal2.perPersonVentilationRateMode());
  auto availabilitySchedule =
    terminal2.getModelObjectTarget<Schedule>(openstudio::AirTerminal_DualDuct_VAV_OutdoorAirFields::AvailabilityScheduleName);
  ASSERT_TRUE(availabilitySchedule);
  EXPECT_EQ(expectedAvailabilitySchedule->handle(), availabilitySchedule->handle());
}

TEST_F(EPModelFixture, AirTerminalDualDuctVAVOutdoorAir_RemoveClearsStaleZoneEquipmentWithoutLoop) {
  Model model;
  ThermalZone zone(model);
  AirTerminalDualDuctVAVOutdoorAir terminal(model);

  auto equipmentList = zone.getImpl<detail::ThermalZone_Impl>()->getZoneHVACEquipmentList();
  ASSERT_TRUE(equipmentList.addEquipment(terminal.cast<ModelObject>()));
  ASSERT_EQ(1u, equipmentList.equipment().size());
  EXPECT_FALSE(terminal.airLoopHVAC());
  const auto terminalHandle = terminal.handle();

  terminal.remove();
  EXPECT_TRUE(equipmentList.equipment().empty());
  EXPECT_FALSE(model.getObject(terminalHandle));
}
