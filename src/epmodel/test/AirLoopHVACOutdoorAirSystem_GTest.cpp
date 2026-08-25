/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../ParentObject/ControllerOutdoorAir.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include "../StraightComponent/Node.hpp"
#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

namespace {

std::vector<ModelObject> nonNodeObjects(const std::vector<ModelObject>& objects) {
  std::vector<ModelObject> result;
  for (const auto& object : objects) {
    if (!object.optionalCast<Node>()) {
      result.push_back(object);
    }
  }
  return result;
}

}  // namespace

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_DefaultConstructor) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  EXPECT_EQ(AirLoopHVACOutdoorAirSystem::iddObjectType(), outdoorAirSystem.iddObject().type());
  EXPECT_FALSE(outdoorAirSystem.nameString().empty());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  const std::string newName = "OA System Scalar Roundtrip";
  EXPECT_TRUE(outdoorAirSystem.setName(newName));
  EXPECT_EQ(newName, outdoorAirSystem.nameString());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_DefaultApiScaffold) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  EXPECT_EQ(openstudio::OutdoorAir_MixerFields::ReturnAirStreamNodeName, outdoorAirSystem.returnAirPort());
  EXPECT_EQ(openstudio::OutdoorAir_MixerFields::OutdoorAirStreamNodeName, outdoorAirSystem.outdoorAirPort());
  EXPECT_EQ(openstudio::OutdoorAir_MixerFields::ReliefAirStreamNodeName, outdoorAirSystem.reliefAirPort());
  EXPECT_EQ(openstudio::OutdoorAir_MixerFields::MixedAirNodeName, outdoorAirSystem.mixedAirPort());

  EXPECT_FALSE(outdoorAirSystem.returnAirModelObject());
  EXPECT_TRUE(outdoorAirSystem.outdoorAirModelObject());
  EXPECT_TRUE(outdoorAirSystem.reliefAirModelObject());
  EXPECT_FALSE(outdoorAirSystem.mixedAirModelObject());
  EXPECT_EQ(1u, outdoorAirSystem.oaComponents().size());
  EXPECT_EQ(1u, outdoorAirSystem.reliefComponents().size());
  EXPECT_EQ(2u, outdoorAirSystem.components().size());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_DefaultCreatesControllerOutdoorAir) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto controllerOutdoorAir = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(ControllerOutdoorAir::iddObjectType(), controllerOutdoorAir.iddObject().type());

  auto linkedSystem = controllerOutdoorAir.airLoopHVACOutdoorAirSystem();
  ASSERT_TRUE(linkedSystem);
  EXPECT_EQ(outdoorAirSystem, *linkedSystem);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_ControllerOutdoorAirRoundTrip) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  ControllerOutdoorAir controllerOutdoorAir(model);

  EXPECT_TRUE(outdoorAirSystem.setControllerOutdoorAir(controllerOutdoorAir));

  auto fetchedController = outdoorAirSystem.getControllerOutdoorAir();
  EXPECT_EQ(controllerOutdoorAir, fetchedController);

  auto fetchedSystem = controllerOutdoorAir.airLoopHVACOutdoorAirSystem();
  ASSERT_TRUE(fetchedSystem);
  EXPECT_EQ(outdoorAirSystem, *fetchedSystem);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_OutboardNodeAccessors) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto outboardOA = outdoorAirSystem.outboardOANode();
  auto outboardRelief = outdoorAirSystem.outboardReliefNode();
  ASSERT_TRUE(outboardOA);
  ASSERT_TRUE(outboardRelief);

  auto outdoorModelObject = outdoorAirSystem.outdoorAirModelObject();
  auto reliefModelObject = outdoorAirSystem.reliefAirModelObject();
  ASSERT_TRUE(outdoorModelObject);
  ASSERT_TRUE(reliefModelObject);

  auto outdoorNode = outdoorModelObject->optionalCast<Node>();
  auto reliefNode = reliefModelObject->optionalCast<Node>();
  ASSERT_TRUE(outdoorNode);
  ASSERT_TRUE(reliefNode);

  EXPECT_EQ(*outboardOA, *outdoorNode);
  EXPECT_EQ(*outboardRelief, *reliefNode);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_SecondSystemDoesNotReuseRenamedSystemNodes) {
  Model model;
  AirLoopHVAC firstLoop(model);
  ASSERT_TRUE(firstLoop.setName("First Air Loop"));
  AirLoopHVACOutdoorAirSystem firstSystem(model);
  auto firstOutboardOA = firstSystem.outboardOANode();
  auto firstOutboardRelief = firstSystem.outboardReliefNode();
  ASSERT_TRUE(firstOutboardOA);
  ASSERT_TRUE(firstOutboardRelief);
  ASSERT_TRUE(firstSystem.setName("First Outdoor Air System"));

  AirLoopHVAC secondLoop(model);
  AirLoopHVACOutdoorAirSystem secondSystem(model);
  auto secondOutboardOA = secondSystem.outboardOANode();
  auto secondOutboardRelief = secondSystem.outboardReliefNode();
  ASSERT_TRUE(secondOutboardOA);
  ASSERT_TRUE(secondOutboardRelief);
  EXPECT_NE(*firstOutboardOA, *secondOutboardOA);
  EXPECT_NE(*firstOutboardRelief, *secondOutboardRelief);

  auto firstSupplyOutlet = firstLoop.supplyOutletNode();
  auto secondSupplyOutlet = secondLoop.supplyOutletNode();
  ASSERT_TRUE(firstSystem.addToNode(firstSupplyOutlet));
  ASSERT_TRUE(secondSystem.addToNode(secondSupplyOutlet));
  ASSERT_TRUE(firstSystem.returnAirModelObject());
  ASSERT_TRUE(firstSystem.mixedAirModelObject());
  ASSERT_TRUE(secondSystem.returnAirModelObject());
  ASSERT_TRUE(secondSystem.mixedAirModelObject());
  EXPECT_NE(*firstSystem.returnAirModelObject(), *secondSystem.returnAirModelObject());
  EXPECT_NE(*firstSystem.mixedAirModelObject(), *secondSystem.mixedAirModelObject());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_DefaultCreatesOutdoorAirNodeList) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto outboardOA = outdoorAirSystem.outboardOANode();
  ASSERT_TRUE(outboardOA);

  bool found = false;
  for (const auto& object : model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
    for (const auto& group : object.extensibleGroups()) {
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      ASSERT_TRUE(workspaceGroup);
      auto nodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
      if (nodeName && openstudio::istringEqual(*nodeName, outboardOA->nameString())) {
        found = true;
      }
    }
  }

  EXPECT_TRUE(found);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToNodeWiresMainPathNodes) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  auto returnAirObject = outdoorAirSystem.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  auto mixedAirObject = outdoorAirSystem.mixedAirModelObject();
  ASSERT_TRUE(mixedAirObject);

  auto supplyComponents = airLoop.supplyComponents();
  ASSERT_EQ(3u, supplyComponents.size());
  EXPECT_EQ(supplyComponents[1], outdoorAirSystem.cast<ModelObject>());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToNodeRejectsNodeNotOnAirLoop) {
  Model model;
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  auto unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected Node");

  EXPECT_FALSE(outdoorAirSystem.addToNode(unconnectedNode));
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToNodeRejectsDemandSideNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(outdoorAirSystem.addToNode(demandInletNode));
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToNodeAllowsOnlyOnePerAirLoop) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem1(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem2(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem1.addToNode(supplyInletNode));
  EXPECT_FALSE(outdoorAirSystem2.addToNode(supplyInletNode));

  auto oaSystems = airLoop.supplyComponents(AirLoopHVACOutdoorAirSystem::iddObjectType());
  ASSERT_EQ(1u, oaSystems.size());
  EXPECT_EQ(outdoorAirSystem1.cast<ModelObject>(), oaSystems.front());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToNodeInsertsBeforeFirstComponentWhenUsingSupplyInlet) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  const auto supplyComponents = airLoop.supplyComponents();
  auto oaPos =
    std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const ModelObject& mo) { return mo == outdoorAirSystem.cast<ModelObject>(); });
  auto fanPos = std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const ModelObject& mo) { return mo == fan.cast<ModelObject>(); });
  ASSERT_NE(supplyComponents.end(), oaPos);
  ASSERT_NE(supplyComponents.end(), fanPos);
  EXPECT_LT(std::distance(supplyComponents.begin(), oaPos), std::distance(supplyComponents.begin(), fanPos));
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToDualDuctSupplyInletBeforeFan) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  FanConstantVolume fan(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyInletNode.airLoopHVAC());
  ASSERT_TRUE(airLoop.supplyComponent(supplyInletNode.handle()));
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  const auto supplyComponents = airLoop.supplyComponents();
  auto oaPos =
    std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const ModelObject& mo) { return mo == outdoorAirSystem.cast<ModelObject>(); });
  auto fanPos = std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const ModelObject& mo) { return mo == fan.cast<ModelObject>(); });
  ASSERT_NE(supplyComponents.end(), oaPos);
  ASSERT_NE(supplyComponents.end(), fanPos);
  EXPECT_LT(std::distance(supplyComponents.begin(), oaPos), std::distance(supplyComponents.begin(), fanPos));

  auto splitterInlet = airLoop.supplySplitterInletNode();
  auto fanOutlet = fan.outletModelObject();
  ASSERT_TRUE(splitterInlet);
  ASSERT_TRUE(fanOutlet);
  EXPECT_EQ(splitterInlet->handle(), fanOutlet->handle());
  const auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());
  for (const auto& deckOutlet : deckOutlets) {
    EXPECT_NE(splitterInlet->handle(), deckOutlet.handle());
  }
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToEmptyDualDuctMainBranch) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  FanConstantVolume fan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(fan.addToNode(supplyInletNode));
  ASSERT_TRUE(outdoorAirSystem.airLoopHVAC());
  EXPECT_EQ(airLoop, *outdoorAirSystem.airLoopHVAC());

  const auto supplyComponents = airLoop.supplyComponents();
  auto fanPos = std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const ModelObject& mo) { return mo == fan.cast<ModelObject>(); });
  auto oaPos =
    std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const ModelObject& mo) { return mo == outdoorAirSystem.cast<ModelObject>(); });
  ASSERT_NE(supplyComponents.end(), fanPos);
  ASSERT_NE(supplyComponents.end(), oaPos);
  EXPECT_LT(std::distance(supplyComponents.begin(), fanPos), std::distance(supplyComponents.begin(), oaPos));

  auto splitterInlet = airLoop.supplySplitterInletNode();
  auto mixedAirObject = outdoorAirSystem.mixedAirModelObject();
  ASSERT_TRUE(splitterInlet);
  ASSERT_TRUE(mixedAirObject);
  EXPECT_EQ(splitterInlet->handle(), mixedAirObject->handle());
  const auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());
  for (const auto& deckOutlet : deckOutlets) {
    EXPECT_NE(splitterInlet->handle(), deckOutlet.handle());
  }
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_RejectsEmptyDualDuctDeckWithoutMutation) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  const auto objectCount = model.objects().size();
  const auto supplyComponents = airLoop.supplyComponents();
  auto splitterInlet = airLoop.supplySplitterInletNode();
  const auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_TRUE(splitterInlet);
  ASSERT_EQ(2u, deckOutlets.size());
  ASSERT_FALSE(outdoorAirSystem.returnAirModelObject());
  ASSERT_FALSE(outdoorAirSystem.mixedAirModelObject());

  auto hotDeckOutlet = deckOutlets.front();
  EXPECT_FALSE(outdoorAirSystem.addToNode(hotDeckOutlet));

  EXPECT_EQ(objectCount, model.objects().size());
  EXPECT_EQ(supplyComponents, airLoop.supplyComponents());
  ASSERT_TRUE(airLoop.supplySplitterInletNode());
  EXPECT_EQ(splitterInlet->handle(), airLoop.supplySplitterInletNode()->handle());
  ASSERT_EQ(deckOutlets.size(), airLoop.supplyOutletNodes().size());
  for (std::size_t i = 0; i < deckOutlets.size(); ++i) {
    EXPECT_EQ(deckOutlets[i].handle(), airLoop.supplyOutletNodes()[i].handle());
  }
  EXPECT_FALSE(outdoorAirSystem.airLoopHVAC());
  EXPECT_FALSE(outdoorAirSystem.returnAirModelObject());
  EXPECT_FALSE(outdoorAirSystem.mixedAirModelObject());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_AddToNodeInsertsAfterLastComponentWhenUsingSupplyOutlet) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanConstantVolume fan(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(fan.addToNode(supplyInletNode));

  auto supplyOutletNode = airLoop.supplyOutletNodes().front();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyOutletNode));

  auto returnAirObject = outdoorAirSystem.returnAirModelObject();
  ASSERT_TRUE(returnAirObject);
  auto mixedAirObject = outdoorAirSystem.mixedAirModelObject();
  ASSERT_TRUE(mixedAirObject);
  EXPECT_EQ(supplyOutletNode.cast<ModelObject>(), *mixedAirObject);
  EXPECT_NE(*returnAirObject, *mixedAirObject);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_StraightComponentInsertionUpdatesMixedAirNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);
  FanConstantVolume fan(model);

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyOutletNode));
  ASSERT_TRUE(fan.addToNode(supplyOutletNode));

  auto fanInlet = fan.inletModelObject();
  auto mixedAirObject = outdoorAirSystem.mixedAirModelObject();
  auto controllerMixedAirObject =
    outdoorAirSystem.getControllerOutdoorAir().getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::MixedAirNodeName);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(mixedAirObject);
  ASSERT_TRUE(controllerMixedAirObject);
  EXPECT_EQ(*fanInlet, *mixedAirObject);
  EXPECT_EQ(*fanInlet, *controllerMixedAirObject);
  EXPECT_NE(supplyOutletNode.cast<ModelObject>(), *mixedAirObject);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_NodeRenamePreservesResolvedLinks) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  auto returnAirObject = outdoorAirSystem.returnAirModelObject();
  auto mixedAirObject = outdoorAirSystem.mixedAirModelObject();
  ASSERT_TRUE(returnAirObject);
  ASSERT_TRUE(mixedAirObject);
  auto returnAirNode = returnAirObject->optionalCast<Node>();
  auto mixedAirNode = mixedAirObject->optionalCast<Node>();
  ASSERT_TRUE(returnAirNode);
  ASSERT_TRUE(mixedAirNode);

  const auto returnRenamed = returnAirNode->nameString() + " Renamed";
  const auto mixedRenamed = mixedAirNode->nameString() + " Renamed";
  ASSERT_TRUE(returnAirNode->setName(returnRenamed));
  ASSERT_TRUE(mixedAirNode->setName(mixedRenamed));

  auto renamedReturnAirObject = outdoorAirSystem.returnAirModelObject();
  auto renamedMixedAirObject = outdoorAirSystem.mixedAirModelObject();
  ASSERT_TRUE(renamedReturnAirObject);
  ASSERT_TRUE(renamedMixedAirObject);
  auto renamedReturnAirNode = renamedReturnAirObject->optionalCast<Node>();
  auto renamedMixedAirNode = renamedMixedAirObject->optionalCast<Node>();
  ASSERT_TRUE(renamedReturnAirNode);
  ASSERT_TRUE(renamedMixedAirNode);
  EXPECT_EQ(*returnAirNode, *renamedReturnAirNode);
  EXPECT_EQ(*mixedAirNode, *renamedMixedAirNode);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_ObjectRenamePreservesLoopResolution) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem outdoorAirSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(outdoorAirSystem.addToNode(supplyInletNode));

  auto beforeLoop = outdoorAirSystem.airLoopHVAC();
  ASSERT_TRUE(beforeLoop);
  EXPECT_EQ(airLoop, *beforeLoop);

  ASSERT_TRUE(outdoorAirSystem.setName(outdoorAirSystem.nameString() + " Renamed"));

  auto afterLoop = outdoorAirSystem.airLoopHVAC();
  ASSERT_TRUE(afterLoop);
  EXPECT_EQ(airLoop, *afterLoop);

  const auto supplyComponents = airLoop.supplyComponents();
  const auto found = std::ranges::any_of(supplyComponents, [&](const ModelObject& object) { return object == outdoorAirSystem.cast<ModelObject>(); });
  EXPECT_TRUE(found);

  EXPECT_TRUE(outdoorAirSystem.returnAirModelObject());
  EXPECT_TRUE(outdoorAirSystem.mixedAirModelObject());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_ReliefSideSingleStreamInsertionAndRemoval) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);
  auto controller = oaSystem.getControllerOutdoorAir();
  auto controllerRelief = controller.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ReliefAirOutletNodeName);
  ASSERT_TRUE(controllerRelief);
  ASSERT_TRUE(oaSystem.reliefAirModelObject());
  EXPECT_EQ(oaSystem.reliefAirModelObject()->handle(), controllerRelief->handle());

  FanConstantVolume reliefFan(model);
  ASSERT_TRUE(reliefFan.addToNode(*outboardReliefNode));

  const auto reliefPath = oaSystem.reliefComponents();
  ASSERT_EQ(3u, reliefPath.size());
  EXPECT_EQ((std::vector<ModelObject>{reliefFan.cast<ModelObject>()}), nonNodeObjects(reliefPath));
  EXPECT_EQ(1u, oaSystem.oaComponents().size());
  controllerRelief = controller.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ReliefAirOutletNodeName);
  ASSERT_TRUE(controllerRelief);
  ASSERT_TRUE(oaSystem.reliefAirModelObject());
  EXPECT_EQ(oaSystem.reliefAirModelObject()->handle(), controllerRelief->handle());
  EXPECT_NE(outboardReliefNode->handle(), controllerRelief->handle());

  reliefFan.remove();

  EXPECT_EQ(1u, oaSystem.reliefComponents().size());
  EXPECT_TRUE(nonNodeObjects(oaSystem.reliefComponents()).empty());
  controllerRelief = controller.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ReliefAirOutletNodeName);
  ASSERT_TRUE(controllerRelief);
  ASSERT_TRUE(oaSystem.reliefAirModelObject());
  EXPECT_EQ(oaSystem.reliefAirModelObject()->handle(), controllerRelief->handle());
  EXPECT_EQ(outboardReliefNode->handle(), controllerRelief->handle());
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_OutdoorStreamInsertionKeepsControllerActuatorOnOutdoorBoundary) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-oa-controller-outdoor-boundary.idf");
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  ASSERT_TRUE(oaSystem.setName("Outdoor Boundary OA System"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  auto controller = oaSystem.getControllerOutdoorAir();
  auto controllerActuator = controller.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  ASSERT_TRUE(controllerActuator);
  ASSERT_TRUE(oaSystem.outdoorAirModelObject());
  EXPECT_EQ(oaSystem.outdoorAirModelObject()->handle(), controllerActuator->handle());
  EXPECT_EQ(outboardOANode->handle(), controllerActuator->handle());

  FanConstantVolume outdoorFan(model);
  ASSERT_TRUE(outdoorFan.addToNode(*outboardOANode));

  controllerActuator = controller.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  ASSERT_TRUE(controllerActuator);
  ASSERT_TRUE(oaSystem.outdoorAirModelObject());
  EXPECT_NE(oaSystem.outdoorAirModelObject()->handle(), controllerActuator->handle());
  EXPECT_EQ(outboardOANode->handle(), controllerActuator->handle());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOASystem = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Outdoor Boundary OA System");
  ASSERT_TRUE(loadedOASystem);
  auto loadedOutboardOANode = loadedOASystem->outboardOANode();
  ASSERT_TRUE(loadedOutboardOANode);
  auto loadedController = loadedOASystem->getControllerOutdoorAir();
  auto loadedActuator = loadedController.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  ASSERT_TRUE(loadedActuator);
  ASSERT_TRUE(loadedOASystem->outdoorAirModelObject());
  EXPECT_EQ(loadedOutboardOANode->handle(), loadedActuator->handle());
  EXPECT_NE(loadedOASystem->outdoorAirModelObject()->handle(), loadedActuator->handle());

  outdoorFan.remove();

  controllerActuator = controller.getModelObjectTarget<Node>(openstudio::Controller_OutdoorAirFields::ActuatorNodeName);
  ASSERT_TRUE(controllerActuator);
  ASSERT_TRUE(oaSystem.outdoorAirModelObject());
  EXPECT_EQ(oaSystem.outdoorAirModelObject()->handle(), controllerActuator->handle());
  EXPECT_EQ(outboardOANode->handle(), controllerActuator->handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_MultipleAirToAirComponentsPreserveExactStreamOrder) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  HeatExchangerAirToAirSensibleAndLatent hx1(model);
  HeatExchangerAirToAirSensibleAndLatent hx2(model);
  ASSERT_TRUE(hx1.addToNode(*outboardOANode));
  ASSERT_TRUE(hx2.addToNode(*outboardOANode));

  EXPECT_EQ((std::vector<ModelObject>{hx2.cast<ModelObject>(), hx1.cast<ModelObject>()}), nonNodeObjects(oaSystem.oaComponents()));
  EXPECT_EQ((std::vector<ModelObject>{hx1.cast<ModelObject>(), hx2.cast<ModelObject>()}), nonNodeObjects(oaSystem.reliefComponents()));
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_MixedChainPreservesExactStreamOrder) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardOANode);
  ASSERT_TRUE(outboardReliefNode);

  FanConstantVolume oaFan(model);
  HeatExchangerAirToAirSensibleAndLatent hx(model);
  FanConstantVolume reliefFan(model);

  ASSERT_TRUE(oaFan.addToNode(*outboardOANode));
  ASSERT_TRUE(hx.addToNode(*outboardOANode));
  ASSERT_TRUE(reliefFan.addToNode(*outboardReliefNode));

  EXPECT_EQ((std::vector<ModelObject>{hx.cast<ModelObject>(), oaFan.cast<ModelObject>()}), nonNodeObjects(oaSystem.oaComponents()));
  EXPECT_EQ((std::vector<ModelObject>{hx.cast<ModelObject>(), reliefFan.cast<ModelObject>()}), nonNodeObjects(oaSystem.reliefComponents()));
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_InternalOutdoorAirNodeInsertionPreservesExactStreamOrder) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  FanConstantVolume oaFan(model);
  ASSERT_TRUE(oaFan.addToNode(*outboardOANode));

  auto internalOANodeObject = oaFan.outletModelObject();
  ASSERT_TRUE(internalOANodeObject);
  auto internalOANode = internalOANodeObject->optionalCast<Node>();
  ASSERT_TRUE(internalOANode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*internalOANode));

  EXPECT_EQ((std::vector<ModelObject>{oaFan.cast<ModelObject>(), hx.cast<ModelObject>()}), nonNodeObjects(oaSystem.oaComponents()));
  EXPECT_EQ((std::vector<ModelObject>{hx.cast<ModelObject>()}), nonNodeObjects(oaSystem.reliefComponents()));
}

TEST_F(EPModelFixture, API_AirLoopHVACOutdoorAirSystem_InternalReliefNodeInsertionPreservesExactStreamOrder) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardReliefNode = oaSystem.outboardReliefNode();
  ASSERT_TRUE(outboardReliefNode);

  FanConstantVolume reliefFan(model);
  ASSERT_TRUE(reliefFan.addToNode(*outboardReliefNode));

  auto internalReliefNodeObject = reliefFan.inletModelObject();
  ASSERT_TRUE(internalReliefNodeObject);
  auto internalReliefNode = internalReliefNodeObject->optionalCast<Node>();
  ASSERT_TRUE(internalReliefNode);

  HeatExchangerAirToAirSensibleAndLatent hx(model);
  ASSERT_TRUE(hx.addToNode(*internalReliefNode));

  EXPECT_EQ((std::vector<ModelObject>{hx.cast<ModelObject>()}), nonNodeObjects(oaSystem.oaComponents()));
  EXPECT_EQ((std::vector<ModelObject>{hx.cast<ModelObject>(), reliefFan.cast<ModelObject>()}), nonNodeObjects(oaSystem.reliefComponents()));
}
