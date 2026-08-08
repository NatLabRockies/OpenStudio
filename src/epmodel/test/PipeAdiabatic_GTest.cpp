/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
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
    SCOPED_TRACE("same-position re-add currently succeeds after detach and reinsert");
    Model model;
    PlantLoop plantLoop(model);
    PipeAdiabatic pipe(model);

    auto node = plantLoop.supplyOutletNode();
    ASSERT_TRUE(pipe.addToNode(node));
    auto outletObject = pipe.outletModelObject();
    ASSERT_TRUE(outletObject);
    auto adjacentNode = outletObject->cast<Node>();

    EXPECT_TRUE(pipe.addToNode(adjacentNode));
    EXPECT_EQ(7u, plantLoop.supplyComponents().size());
    EXPECT_TRUE(pipe.loop());
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
