/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../LayeredConstruction/Construction.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PipeOutdoor.hpp"
#include "../StraightComponent/PipeOutdoor_Impl.hpp"
#include <utilities/idd/Pipe_Outdoor_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipeOutdoor_DefaultConstructor) {
  Model model;
  PipeOutdoor pipe(model);
  EXPECT_EQ(PipeOutdoor::iddObjectType(), pipe.iddObject().type());
  EXPECT_FALSE(pipe.nameString().empty());

  EXPECT_EQ(openstudio::Pipe_OutdoorFields::FluidInletNodeName, pipe.inletPort());
  EXPECT_EQ(openstudio::Pipe_OutdoorFields::FluidOutletNodeName, pipe.outletPort());

  EXPECT_DOUBLE_EQ(0.05, pipe.pipeInsideDiameter());
  EXPECT_DOUBLE_EQ(100.0, pipe.pipeLength());
}

TEST_F(EPModelFixture, PipeOutdoor_ScalarAccessors_RoundTrip) {
  Model model;
  PipeOutdoor pipe(model);

  EXPECT_TRUE(pipe.setPipeInsideDiameter(0.125));
  EXPECT_DOUBLE_EQ(0.125, pipe.pipeInsideDiameter());
  EXPECT_FALSE(pipe.setPipeInsideDiameter(-10.0));
  EXPECT_DOUBLE_EQ(0.125, pipe.pipeInsideDiameter());

  EXPECT_TRUE(pipe.setPipeLength(42.0));
  EXPECT_DOUBLE_EQ(42.0, pipe.pipeLength());
  EXPECT_FALSE(pipe.setPipeLength(-10.0));
  EXPECT_DOUBLE_EQ(42.0, pipe.pipeLength());
}

TEST_F(EPModelFixture, PipeOutdoor_RelationshipAccessors_RoundTrip) {
  Model model;
  PipeOutdoor pipe(model);

  Construction construction(model);
  EXPECT_TRUE(pipe.setConstruction(construction));
  ASSERT_TRUE(pipe.construction());
  EXPECT_EQ(construction.handle(), pipe.construction()->handle());
  pipe.resetConstruction();
  EXPECT_FALSE(pipe.construction());

  Node ambientNode(model);
  EXPECT_TRUE(pipe.setAmbientTemperatureOutdoorAirNode(ambientNode));
  ASSERT_TRUE(pipe.ambientTemperatureOutdoorAirNode());
  EXPECT_EQ(ambientNode.handle(), pipe.ambientTemperatureOutdoorAirNode()->handle());
  pipe.resetAmbientTemperatureOutdoorAirNode();
  EXPECT_FALSE(pipe.ambientTemperatureOutdoorAirNode());
}

TEST_F(EPModelFixture, PipeOutdoor_AddToNode_PlantOnlyAndClone) {
  Model model;
  PipeOutdoor pipe(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pipe.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pipe.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pipe.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(pipe.plantLoop());
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());

  auto inletNode = pipe.getModelObjectTarget<Node>(openstudio::Pipe_OutdoorFields::FluidInletNodeName);
  auto outletNode = pipe.getModelObjectTarget<Node>(openstudio::Pipe_OutdoorFields::FluidOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(pipe.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(pipe.outletModelObject()->handle(), outletNode->handle());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pipe.addToNode(demandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(pipe.plantLoop());
  ASSERT_TRUE(pipe.inletModelObject());
  ASSERT_TRUE(pipe.outletModelObject());

  PipeOutdoor pipe2(model);
  EXPECT_TRUE(pipe2.addToNode(demandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());

  PlantLoop plantLoop2(model);
  auto secondLoopDemandOutletNode = plantLoop2.demandOutletNode();
  EXPECT_TRUE(pipe.addToNode(secondLoopDemandOutletNode));
  EXPECT_EQ(7u, plantLoop2.demandComponents().size());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  ASSERT_TRUE(pipe.loop());
  EXPECT_EQ(plantLoop2.handle(), pipe.loop()->handle());

  auto pipeCloneObject = model.addObject(pipe.idfObject());
  ASSERT_TRUE(pipeCloneObject);
  auto pipeClone = pipeCloneObject->cast<PipeOutdoor>();
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pipeClone.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(pipeClone.inletModelObject());
  ASSERT_TRUE(pipeClone.outletModelObject());

  ASSERT_TRUE(pipe.loop());
  ASSERT_TRUE(pipeClone.loop());
  ASSERT_TRUE(pipeClone.inletModelObject());
  ASSERT_TRUE(pipeClone.outletModelObject());

  pipe.disconnect();
  EXPECT_FALSE(pipe.loop());
  EXPECT_FALSE(pipe.inletModelObject());
  EXPECT_FALSE(pipe.outletModelObject());
  EXPECT_EQ(5u, plantLoop2.demandComponents().size());

  pipeClone.disconnect();
  EXPECT_FALSE(pipeClone.loop());
  EXPECT_FALSE(pipeClone.inletModelObject());
  EXPECT_FALSE(pipeClone.outletModelObject());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
}
