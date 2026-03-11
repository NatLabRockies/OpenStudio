/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirLoopHVAC.hpp"
#include "../AirLoopHVAC_Impl.hpp"
#include "../AirLoopHVACReturnPath.hpp"
#include "../AirLoopHVACSupplyPath.hpp"
#include "../AirLoopHVACZoneMixer.hpp"
#include "../AirLoopHVACZoneSplitter.hpp"
#include "../AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../FanConstantVolume.hpp"
#include "../Node.hpp"
#include "../ThermalZone.hpp"
#include "../ZoneHVACAirDistributionUnit.hpp"
#include "../ZoneHVACAirDistributionUnit_Impl.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVAC_DefaultConstructor) {
  Model model;
  AirLoopHVAC airLoop(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC), airLoop.iddObject().type());
  EXPECT_FALSE(airLoop.nameString().empty());
}

TEST_F(EPModelFixture, AirLoopHVACSupplyPath_DefaultConstructor) {
  Model model;
  AirLoopHVACSupplyPath supplyPath(model);
  EXPECT_EQ(AirLoopHVACSupplyPath::iddObjectType(), supplyPath.iddObject().type());
  EXPECT_FALSE(supplyPath.nameString().empty());
}

TEST_F(EPModelFixture, AirLoopHVACReturnPath_DefaultConstructor) {
  Model model;
  AirLoopHVACReturnPath returnPath(model);
  EXPECT_EQ(AirLoopHVACReturnPath::iddObjectType(), returnPath.iddObject().type());
  EXPECT_FALSE(returnPath.nameString().empty());
}

TEST_F(EPModelFixture, AirLoopHVACZoneSplitter_DefaultConstructor) {
  Model model;
  AirLoopHVACZoneSplitter zoneSplitter(model);
  EXPECT_EQ(AirLoopHVACZoneSplitter::iddObjectType(), zoneSplitter.iddObject().type());
  EXPECT_FALSE(zoneSplitter.nameString().empty());
}

TEST_F(EPModelFixture, AirLoopHVACZoneMixer_DefaultConstructor) {
  Model model;
  AirLoopHVACZoneMixer zoneMixer(model);
  EXPECT_EQ(AirLoopHVACZoneMixer::iddObjectType(), zoneMixer.iddObject().type());
  EXPECT_FALSE(zoneMixer.nameString().empty());
}

TEST_F(EPModelFixture, AirLoopHVAC_SupplyPathCreatedAndLinkedByDemandInlet) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto impl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(impl);

  auto supplyPath = impl->airLoopHVACSupplyPath();
  EXPECT_EQ(AirLoopHVACSupplyPath::iddObjectType(), supplyPath.iddObject().type());

  auto linkedLoop = supplyPath.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  // Calling again should resolve the same SupplyPath by inlet-node association.
  auto supplyPath2 = impl->airLoopHVACSupplyPath();
  EXPECT_EQ(supplyPath, supplyPath2);
}

TEST_F(EPModelFixture, AirLoopHVAC_ReturnPathCreatedAndLinkedByDemandOutlet) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto impl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(impl);

  auto returnPath = impl->airLoopHVACReturnPath();
  EXPECT_EQ(AirLoopHVACReturnPath::iddObjectType(), returnPath.iddObject().type());

  auto linkedLoop = returnPath.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  // Calling again should resolve the same ReturnPath by outlet-node association.
  auto returnPath2 = impl->airLoopHVACReturnPath();
  EXPECT_EQ(returnPath, returnPath2);
}

TEST_F(EPModelFixture, AirLoopHVAC_ZoneSplitterCreatedAndLinkedByDemandInlet) {
  Model model;
  AirLoopHVAC airLoop(model);

  const auto zoneSplitter = airLoop.zoneSplitter();
  EXPECT_EQ(AirLoopHVACZoneSplitter::iddObjectType(), zoneSplitter.iddObject().type());

  auto linkedLoop = zoneSplitter.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  const auto zoneSplitter2 = airLoop.zoneSplitter();
  EXPECT_EQ(zoneSplitter, zoneSplitter2);
}

TEST_F(EPModelFixture, AirLoopHVAC_ZoneMixerCreatedAndLinkedByDemandOutlet) {
  Model model;
  AirLoopHVAC airLoop(model);

  const auto zoneMixer = airLoop.zoneMixer();
  EXPECT_EQ(AirLoopHVACZoneMixer::iddObjectType(), zoneMixer.iddObject().type());

  auto linkedLoop = zoneMixer.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  const auto zoneMixer2 = airLoop.zoneMixer();
  EXPECT_EQ(zoneMixer, zoneMixer2);
}

TEST_F(EPModelFixture, AirLoopHVAC_SupplyPathAssociationSurvivesDemandInletNodeRename) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto impl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(impl);

  const auto supplyPath = impl->airLoopHVACSupplyPath();
  auto demandInletNode = airLoop.demandInletNode();
  ASSERT_TRUE(demandInletNode.setName("Renamed Demand Inlet Node"));

  // Path should remain associated to the same air loop through pointer-aware rename propagation.
  auto linkedLoop = supplyPath.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  // Resolver should still find the same path, not create a replacement.
  const auto supplyPath2 = impl->airLoopHVACSupplyPath();
  EXPECT_EQ(supplyPath, supplyPath2);
}

TEST_F(EPModelFixture, AirLoopHVAC_ReturnPathAssociationSurvivesDemandOutletNodeRename) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto impl = airLoop.getImpl<detail::AirLoopHVAC_Impl>();
  ASSERT_TRUE(impl);

  const auto returnPath = impl->airLoopHVACReturnPath();
  auto demandOutletNode = airLoop.demandOutletNode();
  ASSERT_TRUE(demandOutletNode.setName("Renamed Demand Outlet Node"));

  // Path should remain associated to the same air loop through pointer-aware rename propagation.
  auto linkedLoop = returnPath.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  // Resolver should still find the same path, not create a replacement.
  const auto returnPath2 = impl->airLoopHVACReturnPath();
  EXPECT_EQ(returnPath, returnPath2);
}

TEST_F(EPModelFixture, AirLoopHVAC_ZoneSplitterAssociationSurvivesDemandInletNodeRename) {
  Model model;
  AirLoopHVAC airLoop(model);

  const auto zoneSplitter = airLoop.zoneSplitter();
  auto demandInletNode = airLoop.demandInletNode();
  ASSERT_TRUE(demandInletNode.setName("Renamed Demand Inlet Node For Zone Splitter"));

  auto linkedLoop = zoneSplitter.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  const auto zoneSplitter2 = airLoop.zoneSplitter();
  EXPECT_EQ(zoneSplitter, zoneSplitter2);
}

TEST_F(EPModelFixture, AirLoopHVAC_ZoneMixerAssociationSurvivesDemandOutletNodeRename) {
  Model model;
  AirLoopHVAC airLoop(model);

  const auto zoneMixer = airLoop.zoneMixer();
  auto demandOutletNode = airLoop.demandOutletNode();
  ASSERT_TRUE(demandOutletNode.setName("Renamed Demand Outlet Node For Zone Mixer"));

  auto linkedLoop = zoneMixer.airLoopHVAC();
  ASSERT_TRUE(linkedLoop);
  EXPECT_EQ(airLoop, linkedLoop.get());

  const auto zoneMixer2 = airLoop.zoneMixer();
  EXPECT_EQ(zoneMixer, zoneMixer2);
}

TEST_F(EPModelFixture, AirLoopHVAC_DemandComponentsIncludesBranchNodeBetweenZoneSplitterAndZoneMixer) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto demandComponents = airLoop.demandComponents();
  ASSERT_GE(demandComponents.size(), 5u);

  EXPECT_EQ(Node::iddObjectType(), demandComponents[0].iddObject().type());
  EXPECT_EQ(AirLoopHVACZoneSplitter::iddObjectType(), demandComponents[1].iddObject().type());
  EXPECT_EQ(Node::iddObjectType(), demandComponents[2].iddObject().type());
  EXPECT_EQ(AirLoopHVACZoneMixer::iddObjectType(), demandComponents[3].iddObject().type());
  EXPECT_EQ(Node::iddObjectType(), demandComponents[4].iddObject().type());

  // Ensure paths are not present in demand topology (OS-style loop topology focus).
  for (const auto& mo : demandComponents) {
    EXPECT_NE(AirLoopHVACSupplyPath::iddObjectType(), mo.iddObject().type());
    EXPECT_NE(AirLoopHVACReturnPath::iddObjectType(), mo.iddObject().type());
  }
}

TEST_F(EPModelFixture, AirLoopHVAC_DemandBranchNodeNameSharedBetweenZoneSplitterAndZoneMixer) {
  Model model;
  AirLoopHVAC airLoop(model);

  // Build demand topology first so the branch link is materialized.
  (void)airLoop.demandComponents();

  const auto zoneSplitter = airLoop.zoneSplitter();
  const auto zoneMixer = airLoop.zoneMixer();

  auto splitterBranchNode = zoneSplitter.lastOutletModelObject();
  ASSERT_TRUE(splitterBranchNode);
  ASSERT_TRUE(splitterBranchNode->optionalCast<Node>());

  auto mixerBranchNode = zoneMixer.lastInletModelObject();
  ASSERT_TRUE(mixerBranchNode);
  ASSERT_TRUE(mixerBranchNode->optionalCast<Node>());

  EXPECT_EQ(splitterBranchNode.get(), mixerBranchNode.get());
}

TEST_F(EPModelFixture, AirLoopHVAC_ThermalZones_UsesDemandTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  const auto thermalZones = airLoop.thermalZones();
  ASSERT_EQ(1u, thermalZones.size());
  EXPECT_EQ(zone, thermalZones.front());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_DemandBranchInsertion) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  terminal.setName("ATU 1");

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  EXPECT_EQ(0u, airLoop.zoneSplitter().branchIndexForOutletModelObject(branchNode->cast<ModelObject>()));
  EXPECT_EQ(0u, airLoop.zoneMixer().branchIndexForInletModelObject(branchNode->cast<ModelObject>()));

  EXPECT_TRUE(terminal.addToNode(*branchNode));

  auto inletObject = terminal.inletModelObject();
  ASSERT_TRUE(inletObject);
  auto inletNode = inletObject->optionalCast<Node>();
  ASSERT_TRUE(inletNode);
  EXPECT_NE(*inletNode, *branchNode);

  auto outletObject = terminal.outletModelObject();
  ASSERT_TRUE(outletObject);
  auto outletNode = outletObject->optionalCast<Node>();
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(*branchNode, *outletNode);

  const auto demandComps = airLoop.demandComponents();
  ASSERT_EQ(7u, demandComps.size());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[0].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneSplitter), demandComps[1].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[2].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat), demandComps[3].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[4].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC_ZoneMixer), demandComps[5].iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), demandComps[6].iddObject().type());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_SynchronizesAirDistributionUnitOutletNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  ZoneHVACAirDistributionUnit airDistributionUnit(model);
  auto airDistributionUnitImpl = airDistributionUnit.getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
  ASSERT_TRUE(airDistributionUnitImpl);
  ASSERT_TRUE(airDistributionUnitImpl->setAirTerminal(terminal.cast<ModelObject>()));

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  ASSERT_TRUE(terminal.addToNode(*branchNode));

  auto airDistributionUnitOutlet = airDistributionUnit.outletNode();
  ASSERT_TRUE(airDistributionUnitOutlet);
  EXPECT_EQ(*branchNode, *airDistributionUnitOutlet);

  ASSERT_TRUE(branchNode->setName(branchNode->nameString() + " Renamed"));
  auto renamedAirDistributionUnitOutlet = airDistributionUnit.outletNode();
  ASSERT_TRUE(renamedAirDistributionUnitOutlet);
  EXPECT_EQ(*branchNode, *renamedAirDistributionUnitOutlet);
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeNoReheat_AddToNode_BranchWithZoneButNoTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);
  terminal.setName("ATU Zone Branch");

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);
  ASSERT_TRUE(zone.addToNode(*branchNode));

  auto zoneBranchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(zoneBranchObject);
  auto zoneBranchNode = zoneBranchObject->optionalCast<Node>();
  ASSERT_TRUE(zoneBranchNode);

  const auto demandBefore = airLoop.demandComponents();
  const auto terminalCountBefore = std::count_if(demandBefore.begin(), demandBefore.end(), [](const ModelObject& mo) {
    return mo.iddObject().type() == openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat;
  });
  EXPECT_EQ(0, terminalCountBefore);

  ASSERT_TRUE(terminal.addToNode(*zoneBranchNode));

  auto terminalInletObject = terminal.inletModelObject();
  ASSERT_TRUE(terminalInletObject);
  auto terminalInletNode = terminalInletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalInletNode);

  auto terminalOutletObject = terminal.outletModelObject();
  ASSERT_TRUE(terminalOutletObject);
  auto terminalOutletNode = terminalOutletObject->optionalCast<Node>();
  ASSERT_TRUE(terminalOutletNode);
  EXPECT_EQ(*zoneBranchNode, *terminalOutletNode);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto splitterOutletNode = splitterOutletObject->optionalCast<Node>();
  ASSERT_TRUE(splitterOutletNode);
  EXPECT_EQ(*terminalInletNode, *splitterOutletNode);

  auto mixerInletObject = airLoop.zoneMixer().lastInletModelObject();
  ASSERT_TRUE(mixerInletObject);
  auto mixerInletNode = mixerInletObject->optionalCast<Node>();
  ASSERT_TRUE(mixerInletNode);
  EXPECT_EQ(*zoneBranchNode, *mixerInletNode);
  EXPECT_NE(*splitterOutletNode, *mixerInletNode);

  const auto demandAfter = airLoop.demandComponents();
  EXPECT_EQ(demandBefore.size() + 2u, demandAfter.size());
  const auto terminalCountAfter = std::count_if(demandAfter.begin(), demandAfter.end(), [](const ModelObject& mo) {
    return mo.iddObject().type() == openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat;
  });
  EXPECT_EQ(1, terminalCountAfter);
}
TEST_F(EPModelFixture, AirLoopHVAC_DefaultConstructorTopology) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto inlet = airLoop.supplyInletNode();
  EXPECT_FALSE(inlet.nameString().empty());

  auto outlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(1u, outlets.size());
  EXPECT_FALSE(outlets[0].nameString().empty());
  EXPECT_NE(inlet.nameString(), outlets[0].nameString());
}

TEST_F(EPModelFixture, AirLoopHVAC_AddToNodeUpdatesSupplyComponents) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  fan.setName("Fan 1");

  auto inletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(fan.addToNode(inletNode));

  auto components = airLoop.supplyComponents(openstudio::IddObjectType::Catchall);
  ASSERT_EQ(3u, components.size());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), components[0].iddObject().type());
  EXPECT_EQ(fan.handle(), components[1].handle());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Node), components[2].iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVAC_SupplyComponentsTypeFilter) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  fan.setName("Fan 1");

  auto inletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(inletNode));

  auto fans = airLoop.supplyComponents(openstudio::IddObjectType::Fan_ConstantVolume);
  ASSERT_EQ(1u, fans.size());
  EXPECT_EQ(fan.handle(), fans[0].handle());
}

TEST_F(EPModelFixture, Node_AdjacentComponentResolution) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  fan.setName("Fan 1");

  auto inletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(inletNode));

  auto outletNode = airLoop.supplyOutletNodes().front();

  auto inletDownstream = inletNode.outletModelObject();
  ASSERT_TRUE(inletDownstream);
  EXPECT_EQ(fan.handle(), inletDownstream->handle());
  EXPECT_FALSE(inletNode.inletModelObject());

  auto outletUpstream = outletNode.inletModelObject();
  ASSERT_TRUE(outletUpstream);
  EXPECT_EQ(fan.handle(), outletUpstream->handle());
  EXPECT_FALSE(outletNode.outletModelObject());
}
TEST_F(EPModelFixture, API_AirLoopHVAC_DefaultConstructor) {
  Model model;
  AirLoopHVAC airLoop(model);
  EXPECT_EQ(AirLoopHVAC::iddObjectType(), airLoop.iddObject().type());
  EXPECT_FALSE(airLoop.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVAC_ModelLookupByTypeAndName) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto object = model.getObjectByTypeAndName(AirLoopHVAC::iddObjectType(), airLoop.nameString());
  ASSERT_TRUE(object);
  EXPECT_EQ(airLoop.cast<ModelObject>(), object->cast<ModelObject>());
}
