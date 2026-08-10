/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../StraightComponent/PipeAdiabatic_Impl.hpp"
#include <utilities/idd/Pipe_Adiabatic_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeAdiabatic_DefaultConstructor) {
  Model model;
  PipeAdiabatic pipe(model);
  EXPECT_EQ(PipeAdiabatic::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());
  EXPECT_EQ(openstudio::Pipe_AdiabaticFields::InletNodeName, pipe.inletPort());
  EXPECT_EQ(openstudio::Pipe_AdiabaticFields::OutletNodeName, pipe.outletPort());
}

TEST_F(EPModelFixture, PipeAdiabatic_ScalarAccessors_RoundTrip) {
  Model model;
  PipeAdiabatic pipe(model);

  // Pipe:Adiabatic has no type-specific scalar accessors; verify base scalar roundtrip remains intact.
  EXPECT_TRUE(pipe.setName("Primary Loop Bypass Pipe"));
  EXPECT_EQ("Primary Loop Bypass Pipe", pipe.nameString());
}

TEST_F(EPModelFixture, PipeAdiabatic_AddToNode_PlantOnly) {
  Model model;
  PipeAdiabatic pipe(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pipe.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pipe.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pipe.addToNode(demandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  PipeAdiabatic pipe2(model);
  EXPECT_TRUE(pipe2.addToNode(demandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, PipeAdiabatic_TopologyCharacterization_CurrentBehavior) {
  // Characterization is evidence, not a declaration that current Model or EPModel
  // behavior is correct. Keep these scenarios aligned with the Model counterpart and
  // review every difference before treating it as a parity requirement or approved delta.

  {
    SCOPED_TRACE("successful move heals the source path");
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    PipeAdiabatic pipe(model);

    auto sourceNode = sourceLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(sourceNode));
    EXPECT_EQ(7u, sourceLoop.supplyComponents().size());

    auto targetNode = targetLoop.demandOutletNode();
    EXPECT_TRUE(pipe.addToNode(targetNode));
    EXPECT_EQ(5u, sourceLoop.supplyComponents().size());
    EXPECT_EQ(7u, targetLoop.demandComponents().size());
    auto actualPlantLoop = pipe.plantLoop();
    ASSERT_TRUE(actualPlantLoop);
    EXPECT_EQ(targetLoop.handle(), actualPlantLoop->handle());
    EXPECT_TRUE(pipe.inletModelObject());
    EXPECT_TRUE(pipe.outletModelObject());
  }

  {
    SCOPED_TRACE("removeFromLoop heals the path but retains EPModel node pointers");
    Model model;
    PlantLoop plantLoop(model);
    PipeAdiabatic pipe(model);

    auto node = plantLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(node));
    EXPECT_TRUE(pipe.removeFromLoop());
    EXPECT_EQ(5u, plantLoop.supplyComponents().size());
    EXPECT_FALSE(pipe.loop());
    EXPECT_TRUE(pipe.inletModelObject());
    EXPECT_TRUE(pipe.outletModelObject());

    EXPECT_TRUE(pipe.addToNode(node));
    EXPECT_EQ(7u, plantLoop.supplyComponents().size());
    EXPECT_TRUE(pipe.loop());
  }

  {
    SCOPED_TRACE("disconnect clears ports and preserves EPModel traversal");
    Model model;
    PlantLoop plantLoop(model);
    PipeAdiabatic pipe(model);

    auto node = plantLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(node));
    pipe.disconnect();
    EXPECT_EQ(5u, plantLoop.supplyComponents().size());
    EXPECT_FALSE(pipe.loop());
    EXPECT_FALSE(pipe.inletModelObject());
    EXPECT_FALSE(pipe.outletModelObject());
  }

  {
    SCOPED_TRACE("same-position re-add is rejected without changing topology");
    Model model;
    PlantLoop plantLoop(model);
    PipeAdiabatic pipe(model);

    auto node = plantLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(node));
    auto outletObject = pipe.outletModelObject();
    ASSERT_TRUE(outletObject);
    auto inletObject = pipe.inletModelObject();
    ASSERT_TRUE(inletObject);
    const auto inletHandle = inletObject->handle();
    const auto outletHandle = outletObject->handle();
    auto adjacentNode = outletObject->cast<Node>();

    EXPECT_FALSE(pipe.addToNode(adjacentNode));
    EXPECT_EQ(7u, plantLoop.supplyComponents().size());
    EXPECT_TRUE(pipe.loop());
    ASSERT_TRUE(pipe.inletModelObject());
    ASSERT_TRUE(pipe.outletModelObject());
    EXPECT_EQ(inletHandle, pipe.inletModelObject()->handle());
    EXPECT_EQ(outletHandle, pipe.outletModelObject()->handle());
  }

  {
    SCOPED_TRACE("foreign-model rejection preserves the EPModel source");
    Model sourceModel;
    PlantLoop sourceLoop(sourceModel);
    PipeAdiabatic pipe(sourceModel);
    auto sourceNode = sourceLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(sourceNode));

    Model targetModel;
    PlantLoop targetLoop(targetModel);
    auto targetNode = targetLoop.supplyOutletNode();

    EXPECT_FALSE(pipe.addToNode(targetNode));
    EXPECT_EQ(7u, sourceLoop.supplyComponents().size());
    EXPECT_EQ(5u, targetLoop.supplyComponents().size());
    EXPECT_TRUE(pipe.loop());
    EXPECT_TRUE(pipe.inletModelObject());
    EXPECT_TRUE(pipe.outletModelObject());
  }

  {
    SCOPED_TRACE("remove heals the path and deletes the component");
    Model model;
    PlantLoop plantLoop(model);
    PipeAdiabatic pipe(model);
    const auto pipeHandle = pipe.handle();

    auto node = plantLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(node));
    EXPECT_FALSE(pipe.remove().empty());
    EXPECT_EQ(5u, plantLoop.supplyComponents().size());
    EXPECT_FALSE(model.getModelObject<PipeAdiabatic>(pipeHandle));
  }
}

TEST_F(EPModelFixture, PipeAdiabatic_PlantTopologySurvivesSaveLoadAndMutation) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-pipe-plant-topology-roundtrip.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.setName("Roundtrip Pipe Plant Loop"));
  ASSERT_TRUE(pipe.setName("Roundtrip Demand Pipe"));
  auto demandOutletNode = plantLoop.demandOutletNode();
  ASSERT_TRUE(pipe.addToNode(demandOutletNode));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Roundtrip Pipe Plant Loop");
  auto loadedPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Roundtrip Demand Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedPipe);

  EXPECT_EQ(5u, loadedPlantLoop->supplyComponents().size());
  EXPECT_EQ(7u, loadedPlantLoop->demandComponents().size());
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedPipe->handle()));
  ASSERT_TRUE(loadedPipe->plantLoop());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedPipe->plantLoop()->handle());
  EXPECT_TRUE(loadedPipe->inletModelObject());
  EXPECT_TRUE(loadedPipe->outletModelObject());

  auto loadedDemandOutletNode = loadedPlantLoop->demandOutletNode();
  ASSERT_TRUE(loadedPipe->removeFromLoop());
  EXPECT_EQ(5u, loadedPlantLoop->demandComponents().size());
  EXPECT_FALSE(loadedPlantLoop->demandComponent(loadedPipe->handle()));
  EXPECT_FALSE(loadedPipe->plantLoop());
  EXPECT_TRUE(loadedPipe->inletModelObject());
  EXPECT_TRUE(loadedPipe->outletModelObject());
  ASSERT_TRUE(loadedPipe->addToNode(loadedDemandOutletNode));
  EXPECT_EQ(7u, loadedPlantLoop->demandComponents().size());
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedPipe->handle()));
  ASSERT_TRUE(loadedPipe->plantLoop());
  EXPECT_EQ(loadedPlantLoop->handle(), loadedPipe->plantLoop()->handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PipeAdiabatic_DemandOrderingAndMovement) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipeA(model);
  PipeAdiabatic pipeB(model);

  auto normalizedDemandOrder = [&]() {
    std::vector<std::string> result;
    for (const auto& component : plantLoop.demandComponents()) {
      if (component.handle() == pipeA.handle()) {
        result.emplace_back("A");
      } else if (component.handle() == pipeB.handle()) {
        result.emplace_back("B");
      } else if (component.optionalCast<Node>()) {
        result.emplace_back("Node");
      } else {
        result.emplace_back("Connector");
      }
    }
    return result;
  };

  auto demandOutletNode = plantLoop.demandOutletNode();
  ASSERT_TRUE(pipeA.addToNode(demandOutletNode));
  ASSERT_TRUE(pipeB.addToNode(demandOutletNode));
  EXPECT_EQ((std::vector<std::string>{"Node", "Connector", "Node", "Connector", "Node", "A", "Node", "B", "Node"}), normalizedDemandOrder());
  ASSERT_TRUE(pipeA.outletModelObject());
  ASSERT_TRUE(pipeB.inletModelObject());
  EXPECT_EQ(pipeA.outletModelObject()->handle(), pipeB.inletModelObject()->handle());

  auto demandInletNode = plantLoop.demandInletNode();
  ASSERT_TRUE(pipeA.addToNode(demandInletNode));
  EXPECT_EQ((std::vector<std::string>{"Node", "A", "Node", "Connector", "Node", "Connector", "Node", "B", "Node"}), normalizedDemandOrder());
  ASSERT_TRUE(pipeA.inletModelObject());
  EXPECT_EQ(demandInletNode.handle(), pipeA.inletModelObject()->handle());

  auto demandComponents = plantLoop.demandComponents();
  ASSERT_GT(demandComponents.size(), 4u);
  auto midPathNode = demandComponents[4].optionalCast<Node>();
  ASSERT_TRUE(midPathNode);
  ASSERT_TRUE(pipeB.addToNode(*midPathNode));
  EXPECT_EQ((std::vector<std::string>{"Node", "A", "Node", "Connector", "Node", "B", "Node", "Connector", "Node"}), normalizedDemandOrder());
  ASSERT_TRUE(pipeB.inletModelObject());
  EXPECT_EQ(midPathNode->handle(), pipeB.inletModelObject()->handle());
}
