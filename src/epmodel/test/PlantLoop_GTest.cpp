/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Model.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Mixer/Mixer.hpp"
#include "../Splitter/Splitter.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

#include <utilities/idd/PlantLoop_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantLoop_DefaultConstructor) {
  Model model;
  PlantLoop plantLoop(model);
  EXPECT_EQ(PlantLoop::iddObjectType(), plantLoop.iddObject().type());
}

TEST_F(EPModelFixture, PlantLoop_ScalarAccessors_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);

  EXPECT_TRUE(plantLoop.setName("Main Plant Loop"));
  EXPECT_EQ("Main Plant Loop", plantLoop.nameString());

  EXPECT_TRUE(plantLoop.setMaximumLoopTemperature(108.5));
  EXPECT_DOUBLE_EQ(108.5, plantLoop.maximumLoopTemperature());

  EXPECT_TRUE(plantLoop.setMinimumLoopTemperature(30.25));
  EXPECT_DOUBLE_EQ(30.25, plantLoop.minimumLoopTemperature());

  EXPECT_TRUE(plantLoop.setPlantLoopVolume(0.45));
  ASSERT_TRUE(plantLoop.plantLoopVolume());
  EXPECT_DOUBLE_EQ(0.45, plantLoop.plantLoopVolume().get());

  plantLoop.autocalculatePlantLoopVolume();
  EXPECT_TRUE(plantLoop.isPlantLoopVolumeAutocalculated());

  EXPECT_TRUE(plantLoop.setCommonPipeSimulation("CommonPipe"));
  EXPECT_EQ("CommonPipe", plantLoop.commonPipeSimulation());
  EXPECT_FALSE(plantLoop.isCommonPipeSimulationDefaulted());
  plantLoop.resetCommonPipeSimulation();
  EXPECT_TRUE(plantLoop.isCommonPipeSimulationDefaulted());
}

TEST_F(EPModelFixture, PlantLoop_CanonicalTopology) {
  Model model;
  PlantLoop plantLoop(model);

  const auto supply = plantLoop.supplyComponents();
  const auto demand = plantLoop.demandComponents();

  ASSERT_EQ(5u, supply.size());
  ASSERT_EQ(5u, demand.size());

  EXPECT_EQ(plantLoop.supplyInletNode(), supply.front().cast<Node>());
  EXPECT_EQ(plantLoop.supplyOutletNode(), supply.back().cast<Node>());
  EXPECT_EQ(plantLoop.demandInletNode(), demand.front().cast<Node>());
  EXPECT_EQ(plantLoop.demandOutletNode(), demand.back().cast<Node>());
}

TEST_F(EPModelFixture, PlantLoop_AddRemoveSupplyBranchForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop.handle(), pipe.plantLoop()->handle());
  ASSERT_TRUE(pipe.loop());
  EXPECT_EQ(plantLoop.handle(), pipe.loop()->handle());
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  EXPECT_TRUE(plantLoop.removeSupplyBranchWithComponent(pipe));
  EXPECT_FALSE(pipe.plantLoop());
  EXPECT_FALSE(pipe.loop());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
}

TEST_F(EPModelFixture, PlantLoop_AddRemoveDemandBranchForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop.handle(), pipe.plantLoop()->handle());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  EXPECT_TRUE(plantLoop.removeDemandBranchWithComponent(pipe));
  EXPECT_FALSE(pipe.plantLoop());
  EXPECT_FALSE(pipe.loop());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, PlantLoop_AddRemoveDemandBranchForWaterToAirComponent) {
  Model model;
  PlantLoop plantLoop(model);
  CoilHeatingWater coil(model);

  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(coil.plantLoop());
  EXPECT_EQ(plantLoop.handle(), coil.plantLoop()->handle());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  EXPECT_TRUE(plantLoop.removeDemandBranchWithComponent(coil));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, PlantLoop_SupplyComponents_IncludeMultipleEquipmentBranchesInOrder) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic firstPipe(model);
  PipeAdiabatic secondPipe(model);

  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(firstPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(secondPipe));

  const auto supply = plantLoop.supplyComponents();
  ASSERT_EQ(10u, supply.size());

  const auto firstPipeIt = std::find(supply.begin(), supply.end(), firstPipe.cast<ModelObject>());
  const auto secondPipeIt = std::find(supply.begin(), supply.end(), secondPipe.cast<ModelObject>());
  const auto mixerIt = std::find(supply.begin(), supply.end(), plantLoop.supplyMixer().cast<ModelObject>());

  ASSERT_NE(supply.end(), firstPipeIt);
  ASSERT_NE(supply.end(), secondPipeIt);
  ASSERT_NE(supply.end(), mixerIt);

  EXPECT_LT(firstPipeIt, secondPipeIt);
  EXPECT_LT(secondPipeIt, mixerIt);
}

TEST_F(EPModelFixture, PlantLoop_Canonicalize_TwoBranchListsBecomeParallelEquipmentBranches) {
  Model model;
  PlantLoop plantLoop(model);

  auto plantLoopImpl = plantLoop.getImpl<detail::PlantLoop_Impl>();

  auto supplyBranchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  ASSERT_TRUE(supplyBranchList);
  auto supplyBranchListImpl = supplyBranchList->getImpl<detail::BranchList_Impl>();

  auto supplyBranches = supplyBranchList->branches();
  ASSERT_EQ(3u, supplyBranches.size());
  ASSERT_TRUE(supplyBranchListImpl->removeBranch(supplyBranches.front()));
  ASSERT_TRUE(supplyBranchListImpl->removeBranch(supplyBranches.back()));

  Branch secondSupplyEquipmentBranch(model);
  ASSERT_TRUE(secondSupplyEquipmentBranch.setName("Recovered Supply Branch 2"));
  ASSERT_TRUE(supplyBranchListImpl->addBranch(secondSupplyEquipmentBranch));

  auto demandBranchList = plantLoop.getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(demandBranchList);
  auto demandBranchListImpl = demandBranchList->getImpl<detail::BranchList_Impl>();

  auto demandBranches = demandBranchList->branches();
  ASSERT_EQ(3u, demandBranches.size());
  ASSERT_TRUE(demandBranchListImpl->removeBranch(demandBranches.front()));
  ASSERT_TRUE(demandBranchListImpl->removeBranch(demandBranches.back()));

  Branch secondDemandEquipmentBranch(model);
  ASSERT_TRUE(secondDemandEquipmentBranch.setName("Recovered Demand Branch 2"));
  ASSERT_TRUE(demandBranchListImpl->addBranch(secondDemandEquipmentBranch));

  detail::LoadContext context{model, SanitizationPolicy::Repair, SanitizationReport{}, {}};
  plantLoopImpl->canonicalize(context);

  EXPECT_EQ(4u, plantLoopImpl->supplyBranchList().branches().size());
  EXPECT_EQ(2u, plantLoopImpl->supplyEquipmentBranches().size());
  EXPECT_EQ(6u, plantLoop.supplyComponents().size());

  EXPECT_EQ(4u, plantLoopImpl->demandBranchList().branches().size());
  EXPECT_EQ(2u, plantLoopImpl->demandEquipmentBranches().size());
  EXPECT_EQ(6u, plantLoop.demandComponents().size());

  EXPECT_EQ(2u, plantLoop.supplySplitter().outletModelObjects().size());
  EXPECT_EQ(2u, plantLoop.supplyMixer().inletModelObjects().size());
  EXPECT_EQ(2u, plantLoop.demandSplitter().outletModelObjects().size());
  EXPECT_EQ(2u, plantLoop.demandMixer().inletModelObjects().size());
}

TEST_F(EPModelFixture, PlantLoop_AddDemandBranchRejectsTertiaryForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_FALSE(plantLoop.addDemandBranchForComponent(pipe, true));
  EXPECT_FALSE(pipe.plantLoop());
}
