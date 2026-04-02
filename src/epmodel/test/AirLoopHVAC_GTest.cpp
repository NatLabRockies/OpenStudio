/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/AirLoopHVACReturnPath.hpp"
#include "../ModelObject/AirLoopHVACReturnPath_Impl.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath.hpp"
#include "../ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "../ModelObject/SizingSystem.hpp"
#include "../ModelObject/SizingSystem_Impl.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "../AvailabilityManager/AvailabilityManagerNightCycle_Impl.hpp"
#include "../Mixer/AirLoopHVACZoneMixer.hpp"
#include "../Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../StraightComponent/FanComponentModel.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanVariableVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../SetpointManager/SetpointManagerMixedAir.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "../ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Sizing_System_FieldEnums.hxx>
#include <algorithm>
#include <set>

using namespace openstudio::epmodel;

namespace {

unsigned demandCount(const AirLoopHVAC& airLoop, openstudio::IddObjectType type) {
  return static_cast<unsigned>(airLoop.demandComponents(type).size());
}

unsigned matchingSupplyPathCount(const Model& model, const AirLoopHVAC& airLoop) {
  unsigned count = 0u;
  for (const auto& supplyPath : model.getConcreteModelObjects<AirLoopHVACSupplyPath>()) {
    auto inletNode = supplyPath.getImpl<detail::AirLoopHVACSupplyPath_Impl>()->supplyAirPathInletNode();
    if (inletNode && *inletNode == airLoop.demandInletNode()) {
      ++count;
    }
  }
  return count;
}

unsigned matchingReturnPathCount(const Model& model, const AirLoopHVAC& airLoop) {
  unsigned count = 0u;
  for (const auto& returnPath : model.getConcreteModelObjects<AirLoopHVACReturnPath>()) {
    auto outletNode = returnPath.getImpl<detail::AirLoopHVACReturnPath_Impl>()->returnAirPathOutletNode();
    if (outletNode && *outletNode == airLoop.demandOutletNode()) {
      ++count;
    }
  }
  return count;
}

unsigned matchingZoneSplitterCount(const Model& model, const AirLoopHVAC& airLoop) {
  unsigned count = 0u;
  for (const auto& zoneSplitter : model.getConcreteModelObjects<AirLoopHVACZoneSplitter>()) {
    auto inletNode = zoneSplitter.getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->inletNode();
    if (inletNode && *inletNode == airLoop.demandInletNode()) {
      ++count;
    }
  }
  return count;
}

unsigned matchingZoneMixerCount(const Model& model, const AirLoopHVAC& airLoop) {
  unsigned count = 0u;
  for (const auto& zoneMixer : model.getConcreteModelObjects<AirLoopHVACZoneMixer>()) {
    auto outletNode = zoneMixer.getImpl<detail::AirLoopHVACZoneMixer_Impl>()->outletNode();
    if (outletNode && *outletNode == airLoop.demandOutletNode()) {
      ++count;
    }
  }
  return count;
}

unsigned matchingSizingSystemCount(const Model& model, const AirLoopHVAC& airLoop) {
  unsigned count = 0u;
  for (const auto& sizingSystem : model.getConcreteModelObjects<SizingSystem>()) {
    auto linkedAirLoop = sizingSystem.getModelObjectTarget<AirLoopHVAC>(openstudio::Sizing_SystemFields::AirLoopName);
    if (linkedAirLoop && *linkedAirLoop == airLoop) {
      ++count;
    }
  }
  return count;
}

void expectDemandBranchParity(const AirLoopHVAC& airLoop) {
  EXPECT_EQ(airLoop.zoneSplitter().outletModelObjects().size(), airLoop.zoneMixer().inletModelObjects().size());
}

std::set<openstudio::Handle> zoneHandles(const AirLoopHVAC& airLoop) {
  std::set<openstudio::Handle> handles;
  for (const auto& zone : airLoop.thermalZones()) {
    handles.insert(zone.handle());
  }
  return handles;
}

}  // namespace

TEST_F(EPModelFixture, AirLoopHVAC_DefaultConstructor) {
  Model model;
  AirLoopHVAC airLoop(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::AirLoopHVAC), airLoop.iddObject().type());
  EXPECT_FALSE(airLoop.nameString().empty());
}

TEST_F(EPModelFixture, AirLoopHVAC_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVAC airLoop(model);

  EXPECT_TRUE(airLoop.setDesignSupplyAirFlowRate(1.25));
  ASSERT_TRUE(airLoop.designSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, airLoop.designSupplyAirFlowRate().get());
  EXPECT_FALSE(airLoop.isDesignSupplyAirFlowRateAutosized());

  airLoop.resetDesignSupplyAirFlowRate();
  ASSERT_TRUE(airLoop.designSupplyAirFlowRate());
  EXPECT_NE(1.25, airLoop.designSupplyAirFlowRate().get());
  EXPECT_FALSE(airLoop.isDesignSupplyAirFlowRateAutosized());

  airLoop.autosizeDesignSupplyAirFlowRate();
  EXPECT_TRUE(airLoop.isDesignSupplyAirFlowRateAutosized());

  EXPECT_TRUE(airLoop.setDesignReturnAirFlowFractionofSupplyAirFlow(0.5));
  EXPECT_DOUBLE_EQ(0.5, airLoop.designReturnAirFlowFractionofSupplyAirFlow());
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
  EXPECT_EQ(fan, components[1]);
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
  EXPECT_EQ(fan, fans[0]);
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
  EXPECT_EQ(fan, *inletDownstream);
  EXPECT_FALSE(inletNode.inletModelObject());

  auto outletUpstream = outletNode.inletModelObject();
  ASSERT_TRUE(outletUpstream);
  EXPECT_EQ(fan, *outletUpstream);
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

TEST_F(EPModelFixture, AirLoopHVAC_AddBranchForHVACComponent_MutatesDemandTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  const auto before = airLoop.demandComponents();
  ASSERT_EQ(5u, before.size());

  EXPECT_TRUE(airLoop.addBranchForHVACComponent(terminal));

  const auto after = airLoop.demandComponents();
  EXPECT_GT(after.size(), before.size());
  auto terminals = airLoop.demandComponents(openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat);
  ASSERT_EQ(1u, terminals.size());
  EXPECT_EQ(terminal, terminals.front());
}

TEST_F(EPModelFixture, AirLoopHVAC_AddAndRemoveBranchForZone_MutatesDemandTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  const auto added = airLoop.demandComponents();
  EXPECT_GE(added.size(), 7u);

  auto zones = airLoop.thermalZones();
  ASSERT_EQ(1u, zones.size());
  EXPECT_EQ(zone, zones.front());

  EXPECT_TRUE(airLoop.removeBranchForZone(zone));
  const auto removed = airLoop.demandComponents();
  EXPECT_EQ(5u, removed.size());
  EXPECT_TRUE(airLoop.thermalZones().empty());
}

TEST_F(EPModelFixture, AirLoopHVAC_AddBranchForZone_MultiZoneExplicitTerminal) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ThermalZone zone3(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal3(model);

  EXPECT_TRUE(airLoop.addBranchForZone(zone1, terminal1));
  EXPECT_FALSE(terminal2.airLoopHVAC());
  EXPECT_FALSE(terminal3.airLoopHVAC());
  EXPECT_TRUE(airLoop.addBranchForZone(zone2, terminal2));
  EXPECT_TRUE(airLoop.addBranchForZone(zone3, terminal3));

  EXPECT_EQ(3u, airLoop.thermalZones().size());
  expectDemandBranchParity(airLoop);
  EXPECT_EQ(3u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(3u, demandCount(airLoop, openstudio::IddObjectType::Zone));
  EXPECT_EQ(3u, demandCount(airLoop, openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat));

  const auto handles = zoneHandles(airLoop);
  EXPECT_TRUE(handles.find(zone1.handle()) != handles.end());
  EXPECT_TRUE(handles.find(zone2.handle()) != handles.end());
  EXPECT_TRUE(handles.find(zone3.handle()) != handles.end());
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveBranchForZone_MultiZoneRemovalOrderMaintainsTopology) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ThermalZone zone3(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal2(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal3(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, terminal1));
  EXPECT_FALSE(terminal2.airLoopHVAC());
  EXPECT_FALSE(terminal3.airLoopHVAC());
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal2));
  ASSERT_TRUE(airLoop.addBranchForZone(zone3, terminal3));
  ASSERT_EQ(3u, airLoop.thermalZones().size());
  expectDemandBranchParity(airLoop);

  EXPECT_TRUE(airLoop.removeBranchForZone(zone3));
  expectDemandBranchParity(airLoop);
  EXPECT_EQ(2u, airLoop.thermalZones().size());

  EXPECT_TRUE(airLoop.removeBranchForZone(zone2));
  expectDemandBranchParity(airLoop);
  EXPECT_EQ(1u, airLoop.thermalZones().size());

  EXPECT_TRUE(airLoop.removeBranchForZone(zone1));
  expectDemandBranchParity(airLoop);
  EXPECT_TRUE(airLoop.thermalZones().empty());
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  const auto outlets = airLoop.zoneSplitter().outletModelObjects();
  const auto inlets = airLoop.zoneMixer().inletModelObjects();
  ASSERT_EQ(1u, outlets.size());
  ASSERT_EQ(1u, inlets.size());
  EXPECT_EQ(outlets.front(), inlets.front());
}

TEST_F(EPModelFixture, AirLoopHVAC_AddBranchForZone_FailurePaths_NoTopologyMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ThermalZone zone3(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal2(model);
  EXPECT_TRUE(airLoop.addBranchForZone(zone1, terminal1));

  const auto baselineDemandSize = airLoop.demandComponents().size();
  const auto baselineBranchCount = airLoop.zoneSplitter().outletModelObjects().size();
  const auto baselineZones = zoneHandles(airLoop);

  auto expectUnchanged = [&]() {
    EXPECT_EQ(baselineDemandSize, airLoop.demandComponents().size());
    EXPECT_EQ(baselineBranchCount, airLoop.zoneSplitter().outletModelObjects().size());
    EXPECT_EQ(baselineBranchCount, airLoop.zoneMixer().inletModelObjects().size());
    EXPECT_EQ(baselineZones, zoneHandles(airLoop));
  };

  EXPECT_FALSE(airLoop.addBranchForZone(zone1, terminal2));
  expectUnchanged();

  EXPECT_FALSE(airLoop.addBranchForZone(zone2, terminal1));
  expectUnchanged();

  Model otherModel;
  ThermalZone foreignZone(otherModel);
  AirTerminalSingleDuctConstantVolumeNoReheat foreignTerminal(otherModel);
  EXPECT_FALSE(airLoop.addBranchForZone(foreignZone, terminal2));
  expectUnchanged();

  EXPECT_FALSE(airLoop.addBranchForZone(zone3, foreignTerminal));
  expectUnchanged();
}

TEST_F(EPModelFixture, AirLoopHVAC_AddBranchForZone_InvalidAirTerminal_RollsBackPartialZoneAttachment) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  FanConstantVolume invalidAirTerminal(model);

  const auto baselineDemand = airLoop.demandComponents();
  const auto baselineZones = zoneHandles(airLoop);
  const auto baselineSplitterOutlets = airLoop.zoneSplitter().outletModelObjects();
  const auto baselineMixerInlets = airLoop.zoneMixer().inletModelObjects();

  EXPECT_FALSE(airLoop.addBranchForZone(zone, invalidAirTerminal));

  EXPECT_EQ(baselineDemand, airLoop.demandComponents());
  EXPECT_EQ(baselineZones, zoneHandles(airLoop));
  EXPECT_EQ(baselineSplitterOutlets, airLoop.zoneSplitter().outletModelObjects());
  EXPECT_EQ(baselineMixerInlets, airLoop.zoneMixer().inletModelObjects());
  EXPECT_TRUE(airLoop.thermalZones().empty());
}

TEST_F(EPModelFixture, AirLoopHVAC_RemoveBranchForZone_FailurePaths_NoTopologyMutation) {
  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone1(model);
  ThermalZone zone2(model);
  ThermalZone zone3(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal2(model);

  ASSERT_TRUE(airLoop.addBranchForZone(zone1, terminal1));
  ASSERT_TRUE(airLoop.addBranchForZone(zone2, terminal2));

  const auto baseDemandSize = airLoop.demandComponents().size();
  const auto baseBranchCount = airLoop.zoneSplitter().outletModelObjects().size();
  const auto baseZones = zoneHandles(airLoop);

  EXPECT_FALSE(airLoop.removeBranchForZone(zone3));
  EXPECT_EQ(baseDemandSize, airLoop.demandComponents().size());
  EXPECT_EQ(baseBranchCount, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(baseZones, zoneHandles(airLoop));

  Model otherModel;
  ThermalZone foreignZone(otherModel);
  EXPECT_FALSE(airLoop.removeBranchForZone(foreignZone));
  EXPECT_EQ(baseDemandSize, airLoop.demandComponents().size());
  EXPECT_EQ(baseBranchCount, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(baseZones, zoneHandles(airLoop));

  ASSERT_TRUE(airLoop.removeBranchForZone(zone2));
  const auto afterFirstRemoveDemandSize = airLoop.demandComponents().size();
  const auto afterFirstRemoveBranchCount = airLoop.zoneSplitter().outletModelObjects().size();
  const auto afterFirstRemoveZones = zoneHandles(airLoop);

  EXPECT_FALSE(airLoop.removeBranchForZone(zone2));
  EXPECT_EQ(afterFirstRemoveDemandSize, airLoop.demandComponents().size());
  EXPECT_EQ(afterFirstRemoveBranchCount, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(afterFirstRemoveZones, zoneHandles(airLoop));
}

TEST_F(EPModelFixture, AirLoopHVAC_AddBranchForHVACComponent_MultiBranchAndFailurePaths) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal1(model);
  AirTerminalSingleDuctConstantVolumeNoReheat terminal2(model);

  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal1));
  EXPECT_FALSE(terminal2.airLoopHVAC());
  ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal2));
  expectDemandBranchParity(airLoop);
  EXPECT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, demandCount(airLoop, openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat));

  const auto baselineDemandSize = airLoop.demandComponents().size();

  Model otherModel;
  AirTerminalSingleDuctConstantVolumeNoReheat foreignTerminal(otherModel);
  EXPECT_FALSE(airLoop.addBranchForHVACComponent(foreignTerminal));
  EXPECT_EQ(baselineDemandSize, airLoop.demandComponents().size());
  expectDemandBranchParity(airLoop);
}

TEST_F(EPModelFixture, AirLoopHVAC_DemandSide_HVACComponentRemove_UpdatesTopology) {
  {
    Model model;
    AirLoopHVAC airLoop(model);
    AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

    ASSERT_TRUE(airLoop.addBranchForHVACComponent(terminal));
    ASSERT_EQ(1u, demandCount(airLoop, openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat));
    terminal.remove();
    EXPECT_EQ(0u, demandCount(airLoop, openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat));
    expectDemandBranchParity(airLoop);
  }

  {
    Model model;
    AirLoopHVAC airLoop(model);
    ThermalZone zone(model);
    AirTerminalSingleDuctConstantVolumeNoReheat terminal(model);

    ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
    ASSERT_EQ(1u, airLoop.thermalZones().size());
    terminal.remove();
    EXPECT_EQ(0u, demandCount(airLoop, openstudio::IddObjectType::AirTerminal_SingleDuct_ConstantVolume_NoReheat));
    expectDemandBranchParity(airLoop);

    EXPECT_TRUE(airLoop.removeBranchForZone(zone));
    EXPECT_TRUE(airLoop.thermalZones().empty());
    EXPECT_EQ(5u, airLoop.demandComponents().size());
  }
}

TEST_F(EPModelFixture, AirLoopHVAC_OutdoorAirConvenienceApis_WithoutOASystem) {
  Model model;
  AirLoopHVAC airLoop(model);

  EXPECT_TRUE(airLoop.oaComponents().empty());
  EXPECT_FALSE(airLoop.outdoorAirNode());
  EXPECT_FALSE(airLoop.reliefAirNode());
  EXPECT_FALSE(airLoop.mixedAirNode());
  EXPECT_FALSE(airLoop.returnAirNode());
  EXPECT_FALSE(airLoop.returnFan());
  EXPECT_FALSE(airLoop.reliefFan());
}

TEST_F(EPModelFixture, AirLoopHVAC_OutdoorAirConvenienceApis_WithOASystem) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outdoorAirNode = airLoop.outdoorAirNode();
  ASSERT_TRUE(outdoorAirNode);
  EXPECT_EQ(*outdoorAirNode, *oaSystem.outboardOANode());

  auto reliefAirNode = airLoop.reliefAirNode();
  ASSERT_TRUE(reliefAirNode);
  EXPECT_EQ(*reliefAirNode, *oaSystem.outboardReliefNode());

  auto mixedAirNode = airLoop.mixedAirNode();
  ASSERT_TRUE(mixedAirNode);
  ASSERT_TRUE(oaSystem.mixedAirModelObject());
  EXPECT_EQ(*mixedAirNode, oaSystem.mixedAirModelObject()->cast<Node>());

  auto returnAirNode = airLoop.returnAirNode();
  ASSERT_TRUE(returnAirNode);
  ASSERT_TRUE(oaSystem.returnAirModelObject());
  EXPECT_EQ(*returnAirNode, oaSystem.returnAirModelObject()->cast<Node>());

  EXPECT_EQ(oaSystem.components(), airLoop.oaComponents());
}

TEST_F(EPModelFixture, AirLoopHVAC_FanHelpers_SelectExpectedFans) {
  {
    Model model;
    AirLoopHVAC airLoop(model);
    AirLoopHVACOutdoorAirSystem oaSystem(model);
    FanConstantVolume returnFan(model);
    FanComponentModel reliefFan(model);

    auto supplyInletNode = airLoop.supplyInletNode();
    ASSERT_TRUE(returnFan.addToNode(supplyInletNode));

    auto returnFanOutletObject = returnFan.outletModelObject();
    ASSERT_TRUE(returnFanOutletObject);
    auto returnFanOutletNode = returnFanOutletObject->optionalCast<Node>();
    ASSERT_TRUE(returnFanOutletNode);
    ASSERT_TRUE(oaSystem.addToNode(*returnFanOutletNode));

    auto reliefNode = oaSystem.outboardReliefNode();
    ASSERT_TRUE(reliefNode);
    ASSERT_TRUE(reliefFan.addToNode(*reliefNode));

    auto selectedReturnFan = airLoop.returnFan();
    ASSERT_TRUE(selectedReturnFan);
    EXPECT_EQ(returnFan.cast<HVACComponent>(), *selectedReturnFan);

    auto selectedReliefFan = airLoop.reliefFan();
    ASSERT_TRUE(selectedReliefFan);
    EXPECT_EQ(reliefFan.cast<HVACComponent>(), *selectedReliefFan);
  }

  {
    Model model;
    AirLoopHVAC airLoop(model);
    FanVariableVolume supplyFan1(model);
    FanSystemModel supplyFan2(model);

    auto supplyInletNode = airLoop.supplyInletNode();
    ASSERT_TRUE(supplyFan1.addToNode(supplyInletNode));

    auto supplyFan1Outlet = supplyFan1.outletModelObject();
    ASSERT_TRUE(supplyFan1Outlet);
    auto supplyFan1OutletNode = supplyFan1Outlet->optionalCast<Node>();
    ASSERT_TRUE(supplyFan1OutletNode);
    ASSERT_TRUE(supplyFan2.addToNode(*supplyFan1OutletNode));

    auto selectedSupplyFan = airLoop.supplyFan();
    ASSERT_TRUE(selectedSupplyFan);
    EXPECT_EQ(supplyFan2.cast<HVACComponent>(), *selectedSupplyFan);
  }
}

TEST_F(EPModelFixture, AirLoopHVAC_SizingSystem_IsLoopOwnedCompanionObject) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto sizingSystem = airLoop.sizingSystem();
  EXPECT_EQ(SizingSystem::iddObjectType(), sizingSystem.iddObject().type());

  const auto sizingSystems = model.getConcreteModelObjects<SizingSystem>();
  ASSERT_EQ(1u, sizingSystems.size());
  EXPECT_EQ(sizingSystem, sizingSystems.front());
}

TEST_F(EPModelFixture, AirLoopHVAC_Canonicalize_DeduplicatesKeyedCompanions) {
  Model model;
  AirLoopHVAC airLoop(model);

  AirLoopHVACSupplyPath duplicateSupplyPath(model);
  duplicateSupplyPath.setName("Duplicate Supply Path");
  ASSERT_TRUE(duplicateSupplyPath.getImpl<detail::AirLoopHVACSupplyPath_Impl>()->setSupplyAirPathInletNode(airLoop.demandInletNode()));

  AirLoopHVACReturnPath duplicateReturnPath(model);
  duplicateReturnPath.setName("Duplicate Return Path");
  ASSERT_TRUE(duplicateReturnPath.getImpl<detail::AirLoopHVACReturnPath_Impl>()->setReturnAirPathOutletNode(airLoop.demandOutletNode()));

  AirLoopHVACZoneSplitter duplicateZoneSplitter(model);
  duplicateZoneSplitter.setName("Duplicate Zone Splitter");
  ASSERT_TRUE(duplicateZoneSplitter.getImpl<detail::AirLoopHVACZoneSplitter_Impl>()->setInletNode(airLoop.demandInletNode()));

  AirLoopHVACZoneMixer duplicateZoneMixer(model);
  duplicateZoneMixer.setName("Duplicate Zone Mixer");
  ASSERT_TRUE(duplicateZoneMixer.getImpl<detail::AirLoopHVACZoneMixer_Impl>()->setOutletNode(airLoop.demandOutletNode()));

  SizingSystem duplicateSizingSystem(model, airLoop);
  duplicateSizingSystem.setName("Duplicate Sizing System");

  EXPECT_EQ(2u, matchingSupplyPathCount(model, airLoop));
  EXPECT_EQ(2u, matchingReturnPathCount(model, airLoop));
  EXPECT_EQ(2u, matchingZoneSplitterCount(model, airLoop));
  EXPECT_EQ(2u, matchingZoneMixerCount(model, airLoop));
  EXPECT_EQ(2u, matchingSizingSystemCount(model, airLoop));

  auto report = model.canonicalize(SanitizationPolicy::Repair);

  EXPECT_EQ(1u, matchingSupplyPathCount(model, airLoop));
  EXPECT_EQ(1u, matchingReturnPathCount(model, airLoop));
  EXPECT_EQ(1u, matchingZoneSplitterCount(model, airLoop));
  EXPECT_EQ(1u, matchingZoneMixerCount(model, airLoop));
  EXPECT_EQ(1u, matchingSizingSystemCount(model, airLoop));
  EXPECT_GT(report.warningCount, 0u);
}

TEST_F(EPModelFixture, AirLoopHVAC_Canonicalize_RepairsDemandBranchCountMismatch) {
  Model model;
  AirLoopHVAC airLoop(model);

  Node extraBranchNode(model);
  extraBranchNode.setName("Mismatched Demand Branch Node");
  ASSERT_TRUE(airLoop.zoneSplitter().setOutletModelObject(1u, extraBranchNode));

  EXPECT_EQ(2u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());

  auto report = model.canonicalize(SanitizationPolicy::Repair);

  EXPECT_EQ(1u, airLoop.zoneSplitter().outletModelObjects().size());
  EXPECT_EQ(1u, airLoop.zoneMixer().inletModelObjects().size());
  EXPECT_EQ(airLoop.zoneSplitter().outletModelObjects().front(), airLoop.zoneMixer().inletModelObjects().front());
  EXPECT_GT(report.warningCount, 0u);
}

TEST_F(EPModelFixture, AirLoopHVAC_NightCycleControlType_UsesAvailabilityManagerNightCycle) {
  Model model;
  AirLoopHVAC airLoop(model);

  EXPECT_EQ("StayOff", airLoop.nightCycleControlType());
  EXPECT_TRUE(airLoop.setNightCycleControlType("CycleOnAny"));
  EXPECT_EQ("CycleOnAny", airLoop.nightCycleControlType());

  bool foundNightCycle = false;
  for (const auto& availabilityManager : airLoop.availabilityManagers()) {
    if (auto nightCycle = availabilityManager.optionalCast<AvailabilityManagerNightCycle>()) {
      foundNightCycle = true;
      EXPECT_EQ("CycleOnAny", nightCycle->controlType());
    }
  }
  EXPECT_TRUE(foundNightCycle);

  EXPECT_FALSE(airLoop.setNightCycleControlType("NotAValidControlType"));
  EXPECT_EQ("CycleOnAny", airLoop.nightCycleControlType());
}

TEST_F(EPModelFixture, AirLoopHVAC_SyncSetpointManagerMixedAirFanNodes_RecognizesVariableVolumeFan) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanVariableVolume fan(model);
  SetpointManagerMixedAir setpointManager(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(setpointManager.addToNode(supplyOutletNode));

  auto fanInletObject = fan.inletModelObject();
  ASSERT_TRUE(fanInletObject);
  auto fanOutletObject = fan.outletModelObject();
  ASSERT_TRUE(fanOutletObject);

  ASSERT_TRUE(setpointManager.fanInletNode());
  ASSERT_TRUE(setpointManager.fanOutletNode());
  EXPECT_EQ(fanInletObject->cast<Node>(), *setpointManager.fanInletNode());
  EXPECT_EQ(fanOutletObject->cast<Node>(), *setpointManager.fanOutletNode());
}
