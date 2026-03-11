/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include "../SetpointManagerMixedAir.hpp"
#include "../SetpointManagerScheduled.hpp"
#include "../SetpointManagerScheduled_Impl.hpp"
#include "../SetpointManagerSingleZoneReheat.hpp"
#include "../HVACComponent/ThermalZone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SetpointManagerScheduled_DefaultConstructor) {
  Model model;
  SetpointManagerScheduled spm(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::SetpointManager_Scheduled), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToNodeReplacesSameControlVariable) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto node = airLoop.supplyOutletNode();

  SetpointManagerScheduled first(model);
  SetpointManagerScheduled second(model);

  ASSERT_TRUE(first.addToNode(node));
  ASSERT_TRUE(second.addToNode(node));

  auto scheduledManagers = model.getConcreteModelObjects<SetpointManagerScheduled>();
  ASSERT_EQ(1u, scheduledManagers.size());
  EXPECT_EQ(second, scheduledManagers.front());
}

TEST_F(EPModelFixture, SetpointManagerScheduled_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  SetpointManagerScheduled spm(model);
  EXPECT_FALSE(spm.addToNode(*outboardOANode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);
  EXPECT_FALSE(spm.addToNode(*outboardReliefNode));
}

TEST_F(EPModelFixture, SetpointManagerMixedAir_AddToNodeSetsReferenceAndFanNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));

  SetpointManagerMixedAir spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  auto expectedInlet = fan.inletModelObject();
  auto expectedOutlet = fan.outletModelObject();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  auto expectedInletNode = expectedInlet->optionalCast<Node>();
  auto expectedOutletNode = expectedOutlet->optionalCast<Node>();
  ASSERT_TRUE(expectedInletNode);
  ASSERT_TRUE(expectedOutletNode);

  auto spmSetpoint = spm.setpointNode();
  ASSERT_TRUE(spmSetpoint);
  EXPECT_EQ(setpointNode, *spmSetpoint);
  auto referenceNode = spm.referenceSetpointNode();
  ASSERT_TRUE(referenceNode);
  EXPECT_EQ(airLoop.supplyOutletNode(), *referenceNode);
  auto fanInletNode = spm.fanInletNode();
  auto fanOutletNode = spm.fanOutletNode();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  EXPECT_EQ(*expectedInletNode, *fanInletNode);
  EXPECT_EQ(*expectedOutletNode, *fanOutletNode);
}

TEST_F(EPModelFixture, SetpointManagerMixedAir_EagerRefreshAfterSupplyTopologyChange) {
  Model model;
  AirLoopHVAC airLoop(model);

  FanConstantVolume upstreamFan(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(upstreamFan.addToNode(supplyInletNode));

  SetpointManagerMixedAir spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  FanConstantVolume downstreamFan(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(downstreamFan.addToNode(supplyOutletNode));

  auto expectedInlet = downstreamFan.inletModelObject();
  auto expectedOutlet = downstreamFan.outletModelObject();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);
  auto expectedInletNode = expectedInlet->optionalCast<Node>();
  auto expectedOutletNode = expectedOutlet->optionalCast<Node>();
  ASSERT_TRUE(expectedInletNode);
  ASSERT_TRUE(expectedOutletNode);

  auto fanInletNode = spm.fanInletNode();
  auto fanOutletNode = spm.fanOutletNode();
  ASSERT_TRUE(fanInletNode);
  ASSERT_TRUE(fanOutletNode);
  EXPECT_EQ(*expectedInletNode, *fanInletNode);
  EXPECT_EQ(*expectedOutletNode, *fanOutletNode);
}

TEST_F(EPModelFixture, SetpointManagerSingleZoneReheat_AddToNodeSetsControlZoneFromDemandPath) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto splitterOutletObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterOutletObject);
  auto demandBranchNode = splitterOutletObject->optionalCast<openstudio::epmodel::Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));

  SetpointManagerSingleZoneReheat spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));

  auto controlZone = spm.controlZone();
  ASSERT_TRUE(controlZone);
  EXPECT_EQ(zone, *controlZone);
}
