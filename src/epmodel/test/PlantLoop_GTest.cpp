/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "../Model.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Mixer/Mixer.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "../Splitter/Splitter.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../ModelObject/SizingPlant_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"

#include <utilities/idd/PlantLoop_FieldEnums.hxx>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantLoop_DefaultConstructor) {
  Model model;
  PlantLoop plantLoop(model);
  EXPECT_EQ(PlantLoop::iddObjectType(), plantLoop.iddObject().type());
}

TEST_F(EPModelFixture, PlantLoop_DefaultConstructor_CreatesCanonicalCompanions) {
  Model model;
  PlantLoop plantLoop(model);

  EXPECT_EQ(plantLoop.supplyOutletNode(), plantLoop.loopTemperatureSetpointNode());

  auto sizingPlant = plantLoop.sizingPlant();
  auto sizingPlantLoop = sizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
  ASSERT_TRUE(sizingPlantLoop);
  EXPECT_EQ(plantLoop, *sizingPlantLoop);

  auto assignmentList = plantLoop.getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
  ASSERT_TRUE(assignmentList);
  EXPECT_TRUE(plantLoop.availabilityManagers().empty());

  auto operationSchemes = plantLoop.getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(operationSchemes);
  EXPECT_FALSE(plantLoop.plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationScheme());
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

TEST_F(EPModelFixture, PlantLoop_AvailabilityManagerMutators_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);
  AvailabilityManagerScheduledOn firstManager(model);
  AvailabilityManagerScheduledOn secondManager(model);
  AvailabilityManagerNightCycle nightCycleManager(model);

  EXPECT_TRUE(plantLoop.addAvailabilityManager(firstManager));
  EXPECT_TRUE(plantLoop.addAvailabilityManager(secondManager));
  EXPECT_FALSE(plantLoop.addAvailabilityManager(nightCycleManager));
  ASSERT_EQ(2u, plantLoop.availabilityManagers().size());
  EXPECT_EQ(1u, plantLoop.availabilityManagerPriority(firstManager));
  EXPECT_EQ(2u, plantLoop.availabilityManagerPriority(secondManager));

  EXPECT_TRUE(plantLoop.setAvailabilityManagerPriority(secondManager, 1u));
  EXPECT_EQ(1u, plantLoop.availabilityManagerPriority(secondManager));
  EXPECT_EQ(2u, plantLoop.availabilityManagerPriority(firstManager));

  EXPECT_TRUE(plantLoop.removeAvailabilityManager(firstManager));
  ASSERT_EQ(1u, plantLoop.availabilityManagers().size());
  EXPECT_EQ(secondManager.cast<ModelObject>(), plantLoop.availabilityManagers().front().cast<ModelObject>());

  plantLoop.resetAvailabilityManagers();
  EXPECT_TRUE(plantLoop.availabilityManagers().empty());
}

TEST_F(EPModelFixture, PlantLoop_OperationSchemes_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);
  PlantEquipmentOperationHeatingLoad heating(model);
  PlantEquipmentOperationCoolingLoad cooling(model);
  PlantEquipmentOperationOutdoorDryBulb primary(model);
  ScheduleConstant heatingSchedule(model);
  ScheduleConstant coolingSchedule(model);
  ScheduleConstant primarySchedule(model);
  ScheduleConstant componentSchedule(model);

  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(heating));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(heatingSchedule));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationCoolingLoad(cooling));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationCoolingLoadSchedule(coolingSchedule));
  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationScheme(primary));
  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  ASSERT_TRUE(plantLoop.setComponentSetpointOperationSchemeSchedule(componentSchedule));

  auto heatingResult = plantLoop.plantEquipmentOperationHeatingLoad();
  ASSERT_TRUE(heatingResult);
  EXPECT_EQ(heating.handle(), heatingResult->handle());

  auto coolingResult = plantLoop.plantEquipmentOperationCoolingLoad();
  ASSERT_TRUE(coolingResult);
  EXPECT_EQ(cooling.handle(), coolingResult->handle());

  auto primaryResult = plantLoop.primaryPlantEquipmentOperationScheme();
  ASSERT_TRUE(primaryResult);
  EXPECT_EQ(primary.handle(), primaryResult->handle());

  auto heatingScheduleResult = plantLoop.plantEquipmentOperationHeatingLoadSchedule();
  ASSERT_TRUE(heatingScheduleResult);
  EXPECT_EQ(heatingSchedule.handle(), heatingScheduleResult->handle());

  auto coolingScheduleResult = plantLoop.plantEquipmentOperationCoolingLoadSchedule();
  ASSERT_TRUE(coolingScheduleResult);
  EXPECT_EQ(coolingSchedule.handle(), coolingScheduleResult->handle());

  auto primaryScheduleResult = plantLoop.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());

  auto componentScheduleResult = plantLoop.componentSetpointOperationSchemeSchedule();
  ASSERT_TRUE(componentScheduleResult);
  EXPECT_EQ(componentSchedule.handle(), componentScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantLoop_HeatingScheduleCanExistWithoutHeatingScheme) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant heatingSchedule(model);

  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(heatingSchedule));
  EXPECT_FALSE(plantLoop.plantEquipmentOperationHeatingLoad());

  auto heatingScheduleResult = plantLoop.plantEquipmentOperationHeatingLoadSchedule();
  ASSERT_TRUE(heatingScheduleResult);
  EXPECT_EQ(heatingSchedule.handle(), heatingScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantLoop_PrimaryScheduleCanExistWithoutPrimaryScheme) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant primarySchedule(model);

  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationScheme());

  auto primaryScheduleResult = plantLoop.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());
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

TEST_F(EPModelFixture, PlantLoop_Canonicalize_RepairsSetpointAndDeduplicatesSizingPlant) {
  Model model;
  PlantLoop plantLoop(model);

  ASSERT_TRUE(plantLoop.setString(openstudio::PlantLoopFields::LoopTemperatureSetpointNodeName, "Missing Setpoint Node"));

  SizingPlant duplicateSizingPlant(model, plantLoop);

  unsigned attachedSizingPlantCount = 0u;
  for (const auto& sizingPlant : model.getConcreteModelObjects<SizingPlant>()) {
    auto sizingPlantLoop = sizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
    if (sizingPlantLoop && (*sizingPlantLoop == plantLoop)) {
      ++attachedSizingPlantCount;
    }
  }
  EXPECT_EQ(2u, attachedSizingPlantCount);

  auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(plantLoop.supplyOutletNode(), plantLoop.loopTemperatureSetpointNode());

  attachedSizingPlantCount = 0u;
  for (const auto& sizingPlant : model.getConcreteModelObjects<SizingPlant>()) {
    auto sizingPlantLoop = sizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName);
    if (sizingPlantLoop && (*sizingPlantLoop == plantLoop)) {
      ++attachedSizingPlantCount;
    }
  }
  EXPECT_EQ(1u, attachedSizingPlantCount);
}

TEST_F(EPModelFixture, PlantLoop_AddDemandBranchRejectsTertiaryForStraightComponent) {
  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);

  EXPECT_FALSE(plantLoop.addDemandBranchForComponent(pipe, true));
  EXPECT_FALSE(pipe.plantLoop());
}
