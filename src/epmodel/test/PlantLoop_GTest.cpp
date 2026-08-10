/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../AvailabilityManager/AvailabilityManagerNightCycle.hpp"
#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn_Impl.hpp"
#include "../Model.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Mixer/Mixer.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList.hpp"
#include "../ModelObject/AvailabilityManagerAssignmentList_Impl.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "../Splitter/Splitter.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/BranchList_Impl.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../HVACComponent/ControllerWaterCoil_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../ModelObject/SizingPlant_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"
#include "../StraightComponent/BoilerHotWater_Impl.hpp"
#include "../StraightComponent/PipeAdiabatic.hpp"
#include "../StraightComponent/PipeAdiabatic_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../WaterToWaterComponent/HeatExchangerFluidToFluid.hpp"
#include "../WaterToWaterComponent/HeatExchangerFluidToFluid_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"

#include <utilities/idd/ConnectorList_FieldEnums.hxx>
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

  auto operationSchemes =
    plantLoop.getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(operationSchemes);
  EXPECT_FALSE(plantLoop.plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationScheme());

  auto supplyConnectorList = plantLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName);
  auto demandConnectorList = plantLoop.getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
  ASSERT_TRUE(supplyConnectorList);
  ASSERT_TRUE(demandConnectorList);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::ConnectorList), supplyConnectorList->iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::ConnectorList), demandConnectorList->iddObject().type());
  ASSERT_EQ(2u, supplyConnectorList->extensibleGroups().size());
  ASSERT_EQ(2u, demandConnectorList->extensibleGroups().size());
  EXPECT_EQ("Connector:Splitter",
            supplyConnectorList->extensibleGroups()[0].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
  EXPECT_EQ("Connector:Mixer",
            supplyConnectorList->extensibleGroups()[1].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
  EXPECT_EQ("Connector:Splitter",
            demandConnectorList->extensibleGroups()[0].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
  EXPECT_EQ("Connector:Mixer",
            demandConnectorList->extensibleGroups()[1].getString(openstudio::ConnectorListExtensibleFields::ConnectorObjectType).get());
}

TEST_F(EPModelFixture, PlantLoop_CanonicalRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-canonical-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant availabilitySchedule(model);
  AvailabilityManagerScheduledOn availabilityManager(model);
  PlantEquipmentOperationHeatingLoad operationScheme(model);
  ScheduleConstant operationSchedule(model);

  ASSERT_TRUE(plantLoop.setName("Canonical Removal Plant Loop"));
  ASSERT_TRUE(availabilitySchedule.setName("Canonical Removal Availability Schedule"));
  ASSERT_TRUE(availabilityManager.setName("Canonical Removal Availability Manager"));
  ASSERT_TRUE(operationScheme.setName("Canonical Removal Heating Operation"));
  ASSERT_TRUE(operationSchedule.setName("Canonical Removal Operation Schedule"));
  ASSERT_TRUE(availabilityManager.setSchedule(availabilitySchedule));
  ASSERT_TRUE(plantLoop.addAvailabilityManager(availabilityManager));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(operationScheme));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(operationSchedule));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Canonical Removal Plant Loop");
  auto loadedAvailabilityManager =
    loadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Canonical Removal Availability Manager");
  auto loadedAvailabilitySchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Availability Schedule");
  auto loadedOperationScheme = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Canonical Removal Heating Operation");
  auto loadedOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Operation Schedule");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedAvailabilityManager);
  ASSERT_TRUE(loadedAvailabilitySchedule);
  ASSERT_TRUE(loadedOperationScheme);
  ASSERT_TRUE(loadedOperationSchedule);

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }

  std::vector<openstudio::Handle> canonicalOwnerHandles;
  const auto supplyBranchList = loadedPlantLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::PlantSideBranchListName);
  const auto demandBranchList = loadedPlantLoop->getModelObjectTarget<BranchList>(openstudio::PlantLoopFields::DemandSideBranchListName);
  const auto supplyConnectorList = loadedPlantLoop->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::PlantSideConnectorListName);
  const auto demandConnectorList = loadedPlantLoop->getModelObjectTarget<ModelObject>(openstudio::PlantLoopFields::DemandSideConnectorListName);
  const auto assignmentList =
    loadedPlantLoop->getModelObjectTarget<AvailabilityManagerAssignmentList>(openstudio::PlantLoopFields::AvailabilityManagerListName);
  const auto operationSchemes =
    loadedPlantLoop->getModelObjectTarget<PlantEquipmentOperationSchemes>(openstudio::PlantLoopFields::PlantEquipmentOperationSchemeName);
  ASSERT_TRUE(supplyBranchList);
  ASSERT_TRUE(demandBranchList);
  ASSERT_TRUE(supplyConnectorList);
  ASSERT_TRUE(demandConnectorList);
  ASSERT_TRUE(assignmentList);
  ASSERT_TRUE(operationSchemes);
  canonicalOwnerHandles.push_back(supplyBranchList->handle());
  canonicalOwnerHandles.push_back(demandBranchList->handle());
  canonicalOwnerHandles.push_back(supplyConnectorList->handle());
  canonicalOwnerHandles.push_back(demandConnectorList->handle());
  canonicalOwnerHandles.push_back(assignmentList->handle());
  canonicalOwnerHandles.push_back(operationSchemes->handle());
  for (const auto& branch : supplyBranchList->branches()) {
    canonicalOwnerHandles.push_back(branch.handle());
  }
  for (const auto& branch : demandBranchList->branches()) {
    canonicalOwnerHandles.push_back(branch.handle());
  }

  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto plantLoopHandle = loadedPlantLoop->handle();

  ASSERT_TRUE(loadedAvailabilityManager->loop());
  EXPECT_EQ(plantLoopHandle, loadedAvailabilityManager->loop()->handle());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*loadedOperationScheme, *loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(loadedPlantLoop->remove().empty());

  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  for (const auto& handle : canonicalOwnerHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilityManager->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilitySchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationScheme->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationSchedule->handle()));
  EXPECT_FALSE(loadedAvailabilityManager->loop());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  auto reloadedAvailabilityManager =
    reloadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Canonical Removal Availability Manager");
  EXPECT_TRUE(reloadedAvailabilityManager);
  if (reloadedAvailabilityManager) {
    EXPECT_FALSE(reloadedAvailabilityManager->loop());
  }
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Availability Schedule"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Canonical Removal Heating Operation"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Canonical Removal Operation Schedule"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_StraightComponentRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-straight-component-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic pipe(model);
  ASSERT_TRUE(plantLoop.setName("Straight Component Removal Plant Loop"));
  ASSERT_TRUE(pipe.setName("Owned Supply Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(pipe));
  ASSERT_TRUE(pipe.plantLoop());
  EXPECT_EQ(plantLoop, *pipe.plantLoop());
  EXPECT_TRUE(plantLoop.supplyComponent(pipe.handle()));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Straight Component Removal Plant Loop");
  auto loadedPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedPipe);
  ASSERT_TRUE(loadedPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(loadedPipe->handle()));
  EXPECT_EQ(7u, loadedPlantLoop->supplyComponents().size());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto pipeHandle = loadedPipe->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());

  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(pipeHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Pipe"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SameSideMultipleStraightComponentRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-same-side-multiple-straight-component-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic firstPipe(model);
  PipeAdiabatic secondPipe(model);
  ASSERT_TRUE(plantLoop.setName("Same Side Multiple Straight Component Loop"));
  ASSERT_TRUE(firstPipe.setName("First Same Side Supply Pipe"));
  ASSERT_TRUE(secondPipe.setName("Second Same Side Supply Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(firstPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(secondPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Same Side Multiple Straight Component Loop");
  auto loadedFirstPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("First Same Side Supply Pipe");
  auto loadedSecondPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Second Same Side Supply Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedFirstPipe);
  ASSERT_TRUE(loadedSecondPipe);
  ASSERT_TRUE(loadedFirstPipe->plantLoop());
  ASSERT_TRUE(loadedSecondPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedFirstPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSecondPipe->plantLoop());
  EXPECT_EQ(2u, loadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto firstPipeHandle = loadedFirstPipe->handle();
  const auto secondPipeHandle = loadedSecondPipe->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());

  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(firstPipeHandle));
  EXPECT_FALSE(loadedModel->getObject(secondPipeHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("First Same Side Supply Pipe"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Second Same Side Supply Pipe"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SupplyBranchRemovalPreservesSpecifiedComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-supply-branch-removal-preserves-component.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic removedBranchPipe(model);
  PipeAdiabatic siblingPipe(model);
  ASSERT_TRUE(plantLoop.setName("Supply Branch Removal Plant Loop"));
  ASSERT_TRUE(removedBranchPipe.setName("Detached Supply Branch Pipe"));
  ASSERT_TRUE(siblingPipe.setName("Surviving Sibling Supply Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(removedBranchPipe));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(siblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Supply Branch Removal Plant Loop");
  auto loadedRemovedBranchPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Supply Branch Pipe");
  auto loadedSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Supply Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedRemovedBranchPipe);
  ASSERT_TRUE(loadedSiblingPipe);
  ASSERT_TRUE(loadedRemovedBranchPipe->plantLoop());
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_EQ(2u, loadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  const auto removedBranchPipeHandle = loadedRemovedBranchPipe->handle();
  const auto siblingPipeHandle = loadedSiblingPipe->handle();
  ASSERT_TRUE(loadedPlantLoop->removeSupplyBranchWithComponent(*loadedRemovedBranchPipe));
  EXPECT_TRUE(loadedModel->getObject(removedBranchPipeHandle));
  EXPECT_TRUE(loadedModel->getObject(siblingPipeHandle));
  EXPECT_FALSE(loadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(loadedRemovedBranchPipe->loop());
  EXPECT_FALSE(loadedPlantLoop->supplyComponent(removedBranchPipeHandle));
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(siblingPipeHandle));
  EXPECT_EQ(1u, loadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPlantLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Supply Branch Removal Plant Loop");
  auto reloadedRemovedBranchPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Supply Branch Pipe");
  auto reloadedSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Supply Pipe");
  ASSERT_TRUE(reloadedPlantLoop);
  ASSERT_TRUE(reloadedRemovedBranchPipe);
  ASSERT_TRUE(reloadedSiblingPipe);
  EXPECT_FALSE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(reloadedRemovedBranchPipe->loop());
  EXPECT_FALSE(reloadedPlantLoop->supplyComponent(reloadedRemovedBranchPipe->handle()));
  ASSERT_TRUE(reloadedSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedPlantLoop->supplyComponent(reloadedSiblingPipe->handle()));
  EXPECT_EQ(1u, reloadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(reloadedPlantLoop->addSupplyBranchForComponent(*reloadedRemovedBranchPipe));
  ASSERT_TRUE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(2u, reloadedPlantLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_DemandBranchRemovalPreservesSpecifiedComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-demand-branch-removal-preserves-component.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic removedBranchPipe(model);
  PipeAdiabatic siblingPipe(model);
  ASSERT_TRUE(plantLoop.setName("Demand Branch Removal Plant Loop"));
  ASSERT_TRUE(removedBranchPipe.setName("Detached Demand Branch Pipe"));
  ASSERT_TRUE(siblingPipe.setName("Surviving Sibling Demand Pipe"));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(removedBranchPipe));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(siblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Demand Branch Removal Plant Loop");
  auto loadedRemovedBranchPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Demand Branch Pipe");
  auto loadedSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Demand Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedRemovedBranchPipe);
  ASSERT_TRUE(loadedSiblingPipe);
  ASSERT_TRUE(loadedRemovedBranchPipe->plantLoop());
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_EQ(2u, loadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  const auto removedBranchPipeHandle = loadedRemovedBranchPipe->handle();
  const auto siblingPipeHandle = loadedSiblingPipe->handle();
  ASSERT_TRUE(loadedPlantLoop->removeDemandBranchWithComponent(*loadedRemovedBranchPipe));
  EXPECT_TRUE(loadedModel->getObject(removedBranchPipeHandle));
  EXPECT_TRUE(loadedModel->getObject(siblingPipeHandle));
  EXPECT_FALSE(loadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(loadedRemovedBranchPipe->loop());
  EXPECT_FALSE(loadedPlantLoop->demandComponent(removedBranchPipeHandle));
  ASSERT_TRUE(loadedSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->demandComponent(siblingPipeHandle));
  EXPECT_EQ(1u, loadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPlantLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Demand Branch Removal Plant Loop");
  auto reloadedRemovedBranchPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Detached Demand Branch Pipe");
  auto reloadedSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Surviving Sibling Demand Pipe");
  ASSERT_TRUE(reloadedPlantLoop);
  ASSERT_TRUE(reloadedRemovedBranchPipe);
  ASSERT_TRUE(reloadedSiblingPipe);
  EXPECT_FALSE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_FALSE(reloadedRemovedBranchPipe->loop());
  EXPECT_FALSE(reloadedPlantLoop->demandComponent(reloadedRemovedBranchPipe->handle()));
  ASSERT_TRUE(reloadedSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedPlantLoop->demandComponent(reloadedSiblingPipe->handle()));
  EXPECT_EQ(1u, reloadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(reloadedPlantLoop->addDemandBranchForComponent(*reloadedRemovedBranchPipe));
  ASSERT_TRUE(reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(*reloadedPlantLoop, *reloadedRemovedBranchPipe->plantLoop());
  EXPECT_EQ(2u, reloadedPlantLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_SupplyBranchAddMovesOwnedStraightComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-cross-loop-supply-branch-move.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  PipeAdiabatic targetSiblingPipe(model);
  ASSERT_TRUE(sourceLoop.setName("Source Supply Branch Move Loop"));
  ASSERT_TRUE(targetLoop.setName("Target Supply Branch Move Loop"));
  ASSERT_TRUE(movingPipe.setName("Moved Supply Branch Pipe"));
  ASSERT_TRUE(targetSiblingPipe.setName("Target Sibling Supply Pipe"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(movingPipe));
  ASSERT_TRUE(targetLoop.addSupplyBranchForComponent(targetSiblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Source Supply Branch Move Loop");
  auto loadedTargetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Target Supply Branch Move Loop");
  auto loadedMovingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Supply Branch Pipe");
  auto loadedTargetSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Supply Pipe");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedTargetLoop);
  ASSERT_TRUE(loadedMovingPipe);
  ASSERT_TRUE(loadedTargetSiblingPipe);
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());
  EXPECT_EQ(1u, loadedTargetLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedTargetLoop->addSupplyBranchForComponent(*loadedMovingPipe));
  EXPECT_FALSE(loadedSourceLoop->supplyComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->supplyComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->supplyComponent(loadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedSourceLoop->supplyComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, loadedTargetLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Source Supply Branch Move Loop");
  auto reloadedTargetLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Target Supply Branch Move Loop");
  auto reloadedMovingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Supply Branch Pipe");
  auto reloadedTargetSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Supply Pipe");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedTargetLoop);
  ASSERT_TRUE(reloadedMovingPipe);
  ASSERT_TRUE(reloadedTargetSiblingPipe);
  EXPECT_FALSE(reloadedSourceLoop->supplyComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->supplyComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->supplyComponent(reloadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(reloadedMovingPipe->plantLoop());
  ASSERT_TRUE(reloadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedMovingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedSourceLoop->supplyComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, reloadedTargetLoop->supplyComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_DemandBranchAddMovesOwnedStraightComponentLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-cross-loop-demand-branch-move.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  PipeAdiabatic movingPipe(model);
  PipeAdiabatic targetSiblingPipe(model);
  ASSERT_TRUE(sourceLoop.setName("Source Demand Branch Move Loop"));
  ASSERT_TRUE(targetLoop.setName("Target Demand Branch Move Loop"));
  ASSERT_TRUE(movingPipe.setName("Moved Demand Branch Pipe"));
  ASSERT_TRUE(targetSiblingPipe.setName("Target Sibling Demand Pipe"));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(movingPipe));
  ASSERT_TRUE(targetLoop.addDemandBranchForComponent(targetSiblingPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Source Demand Branch Move Loop");
  auto loadedTargetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Target Demand Branch Move Loop");
  auto loadedMovingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Demand Branch Pipe");
  auto loadedTargetSiblingPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Demand Pipe");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedTargetLoop);
  ASSERT_TRUE(loadedMovingPipe);
  ASSERT_TRUE(loadedTargetSiblingPipe);
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());
  EXPECT_EQ(1u, loadedTargetLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedTargetLoop->addDemandBranchForComponent(*loadedMovingPipe));
  EXPECT_FALSE(loadedSourceLoop->demandComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->demandComponent(loadedMovingPipe->handle()));
  EXPECT_TRUE(loadedTargetLoop->demandComponent(loadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(loadedMovingPipe->plantLoop());
  ASSERT_TRUE(loadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedMovingPipe->plantLoop());
  EXPECT_EQ(*loadedTargetLoop, *loadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(loadedSourceLoop->demandComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, loadedTargetLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Source Demand Branch Move Loop");
  auto reloadedTargetLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Target Demand Branch Move Loop");
  auto reloadedMovingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Moved Demand Branch Pipe");
  auto reloadedTargetSiblingPipe = reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Target Sibling Demand Pipe");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedTargetLoop);
  ASSERT_TRUE(reloadedMovingPipe);
  ASSERT_TRUE(reloadedTargetSiblingPipe);
  EXPECT_FALSE(reloadedSourceLoop->demandComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->demandComponent(reloadedMovingPipe->handle()));
  EXPECT_TRUE(reloadedTargetLoop->demandComponent(reloadedTargetSiblingPipe->handle()));
  ASSERT_TRUE(reloadedMovingPipe->plantLoop());
  ASSERT_TRUE(reloadedTargetSiblingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedMovingPipe->plantLoop());
  EXPECT_EQ(*reloadedTargetLoop, *reloadedTargetSiblingPipe->plantLoop());
  EXPECT_TRUE(reloadedSourceLoop->demandComponents(PipeAdiabatic::iddObjectType()).empty());
  EXPECT_EQ(2u, reloadedTargetLoop->demandComponents(PipeAdiabatic::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_BoilerControlRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-boiler-control-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  BoilerHotWater boiler(model);
  PlantEquipmentOperationHeatingLoad operationScheme(model);
  ScheduleConstant operationSchedule(model);
  ScheduleConstant availabilitySchedule(model);
  AvailabilityManagerScheduledOn availabilityManager(model);
  ASSERT_TRUE(plantLoop.setName("Boiler Control Removal Plant Loop"));
  ASSERT_TRUE(boiler.setName("Removal Lifecycle Boiler"));
  ASSERT_TRUE(operationScheme.setName("Removal Lifecycle Heating Operation"));
  ASSERT_TRUE(operationSchedule.setName("Removal Lifecycle Operation Schedule"));
  ASSERT_TRUE(availabilitySchedule.setName("Removal Lifecycle Availability Schedule"));
  ASSERT_TRUE(availabilityManager.setName("Removal Lifecycle Availability Manager"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(boiler));
  ASSERT_TRUE(operationScheme.addEquipment(boiler));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(operationScheme));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(operationSchedule));
  ASSERT_TRUE(availabilityManager.setSchedule(availabilitySchedule));
  ASSERT_TRUE(plantLoop.addAvailabilityManager(availabilityManager));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Boiler Control Removal Plant Loop");
  auto loadedBoiler = loadedModel->getConcreteModelObjectByName<BoilerHotWater>("Removal Lifecycle Boiler");
  auto loadedOperationScheme = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Removal Lifecycle Heating Operation");
  auto loadedOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Operation Schedule");
  auto loadedAvailabilitySchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Availability Schedule");
  auto loadedAvailabilityManager =
    loadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Removal Lifecycle Availability Manager");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedBoiler);
  ASSERT_TRUE(loadedOperationScheme);
  ASSERT_TRUE(loadedOperationSchedule);
  ASSERT_TRUE(loadedAvailabilitySchedule);
  ASSERT_TRUE(loadedAvailabilityManager);
  ASSERT_TRUE(loadedBoiler->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedBoiler->plantLoop());
  ASSERT_EQ(1u, loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).size());
  EXPECT_EQ(*loadedBoiler, loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).front());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*loadedOperationScheme, *loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(*loadedOperationSchedule, *loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  ASSERT_TRUE(loadedAvailabilityManager->loop());
  EXPECT_EQ(*loadedPlantLoop, *loadedAvailabilityManager->loop());
  EXPECT_EQ(*loadedAvailabilitySchedule, loadedAvailabilityManager->schedule());

  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto boilerHandle = loadedBoiler->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(boilerHandle));
  EXPECT_TRUE(loadedOperationScheme->equipment(loadedOperationScheme->maximumUpperLimit()).empty());
  EXPECT_FALSE(loadedAvailabilityManager->loop());
  EXPECT_TRUE(loadedModel->getObject(loadedOperationScheme->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedOperationSchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilityManager->handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedAvailabilitySchedule->handle()));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<BoilerHotWater>("Removal Lifecycle Boiler"));
  auto reloadedOperationScheme =
    reloadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Removal Lifecycle Heating Operation");
  auto reloadedAvailabilityManager =
    reloadedModel->getConcreteModelObjectByName<AvailabilityManagerScheduledOn>("Removal Lifecycle Availability Manager");
  ASSERT_TRUE(reloadedOperationScheme);
  EXPECT_TRUE(reloadedOperationScheme->equipment(reloadedOperationScheme->maximumUpperLimit()).empty());
  ASSERT_TRUE(reloadedAvailabilityManager);
  EXPECT_FALSE(reloadedAvailabilityManager->loop());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Operation Schedule"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Removal Lifecycle Availability Schedule"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_MultiSideStraightComponentRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-multi-side-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  PipeAdiabatic supplyPipe(model);
  PipeAdiabatic demandPipe(model);
  ASSERT_TRUE(plantLoop.setName("Multi-side Removal Plant Loop"));
  ASSERT_TRUE(supplyPipe.setName("Owned Supply Removal Pipe"));
  ASSERT_TRUE(demandPipe.setName("Owned Demand Removal Pipe"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(supplyPipe));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(demandPipe));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Multi-side Removal Plant Loop");
  auto loadedSupplyPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Removal Pipe");
  auto loadedDemandPipe = loadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Demand Removal Pipe");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedSupplyPipe);
  ASSERT_TRUE(loadedDemandPipe);
  ASSERT_TRUE(loadedSupplyPipe->plantLoop());
  ASSERT_TRUE(loadedDemandPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedSupplyPipe->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedDemandPipe->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(loadedSupplyPipe->handle()));
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedDemandPipe->handle()));
  EXPECT_EQ(7u, loadedPlantLoop->supplyComponents().size());
  EXPECT_EQ(7u, loadedPlantLoop->demandComponents().size());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    topologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto supplyPipeHandle = loadedSupplyPipe->handle();
  const auto demandPipeHandle = loadedDemandPipe->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(supplyPipeHandle));
  EXPECT_FALSE(loadedModel->getObject(demandPipeHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Supply Removal Pipe"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PipeAdiabatic>("Owned Demand Removal Pipe"));

  openstudio::filesystem::remove(idfPath);
}

namespace {
template <typename CoilType>
void runSharedWaterCoilRemovalLifecycle(const openstudio::path& idfPath, const std::string& coilLabel,
                                        const std::string& expectedControllerAction) {
  const auto scheduleName = "Shared " + coilLabel + " Availability Schedule";
  const auto coilName = "Shared " + coilLabel;
  const auto airLoopName = "Surviving " + coilLabel + " Air Loop";
  const auto plantLoopName = "Removed " + coilLabel + " Plant Loop";
  Model model;
  ScheduleConstant availabilitySchedule(model);
  CoilType coil(model, availabilitySchedule);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  ASSERT_TRUE(availabilitySchedule.setName(scheduleName));
  ASSERT_TRUE(coil.setName(coilName));
  ASSERT_TRUE(airLoop.setName(airLoopName));
  ASSERT_TRUE(plantLoop.setName(plantLoopName));
  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>(scheduleName);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilType>(coilName);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>(airLoopName);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>(plantLoopName);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  ASSERT_TRUE(loadedCoil->plantLoop());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedPlantLoop, *loadedCoil->plantLoop());
  EXPECT_TRUE(loadedAirLoop->supplyComponent(loadedCoil->handle()));
  EXPECT_TRUE(loadedPlantLoop->demandComponent(loadedCoil->handle()));
  EXPECT_EQ(1u, loadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());
  EXPECT_EQ(1u, loadedPlantLoop->demandComponents(CoilType::iddObjectType()).size());
  EXPECT_TRUE(loadedCoil->airInletModelObject());
  EXPECT_TRUE(loadedCoil->airOutletModelObject());
  EXPECT_TRUE(loadedCoil->waterInletModelObject());
  EXPECT_TRUE(loadedCoil->waterOutletModelObject());
  auto loadedController = loadedCoil->controllerWaterCoil();
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedController->action());
  EXPECT_EQ(expectedControllerAction, *loadedController->action());

  std::vector<openstudio::Handle> plantTopologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    plantTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    if (component.handle() != loadedCoil->handle()) {
      plantTopologyHandles.push_back(component.handle());
    }
  }
  const auto plantLoopHandle = loadedPlantLoop->handle();
  const auto sizingPlantHandle = loadedPlantLoop->sizingPlant().handle();
  const auto controllerHandle = loadedController->handle();
  const auto coilHandle = loadedCoil->handle();
  const auto airLoopHandle = loadedAirLoop->handle();
  const auto scheduleHandle = loadedSchedule->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(plantLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(controllerHandle));
  for (const auto& handle : plantTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  EXPECT_TRUE(loadedModel->getObject(coilHandle));
  EXPECT_TRUE(loadedModel->getObject(airLoopHandle));
  EXPECT_TRUE(loadedModel->getObject(scheduleHandle));
  EXPECT_FALSE(loadedCoil->plantLoop());
  EXPECT_FALSE(loadedCoil->waterInletModelObject());
  EXPECT_FALSE(loadedCoil->waterOutletModelObject());
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_TRUE(loadedAirLoop->supplyComponent(coilHandle));
  EXPECT_TRUE(loadedCoil->airInletModelObject());
  EXPECT_TRUE(loadedCoil->airOutletModelObject());
  EXPECT_EQ(1u, loadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());

  EXPECT_TRUE(loadedCoil->removeFromAirLoopHVAC());
  EXPECT_FALSE(loadedCoil->airLoopHVAC());
  EXPECT_TRUE(loadedAirLoop->supplyComponents(CoilType::iddObjectType()).empty());
  auto loadedSupplyOutletNode = loadedAirLoop->supplyOutletNode();
  EXPECT_TRUE(loadedCoil->addToNode(loadedSupplyOutletNode));
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(*loadedAirLoop, *loadedCoil->airLoopHVAC());
  EXPECT_EQ(1u, loadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilType>(coilName);
  auto reloadedAirLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>(airLoopName);
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedAirLoop);
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<PlantLoop>().empty());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<ControllerWaterCoil>().empty());
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>(scheduleName));
  EXPECT_FALSE(reloadedCoil->plantLoop());
  EXPECT_FALSE(reloadedCoil->waterInletModelObject());
  EXPECT_FALSE(reloadedCoil->waterOutletModelObject());
  ASSERT_TRUE(reloadedCoil->airLoopHVAC());
  EXPECT_EQ(*reloadedAirLoop, *reloadedCoil->airLoopHVAC());
  EXPECT_TRUE(reloadedAirLoop->supplyComponent(reloadedCoil->handle()));
  EXPECT_EQ(1u, reloadedAirLoop->supplyComponents(CoilType::iddObjectType()).size());

  openstudio::filesystem::remove(idfPath);
}
}  // namespace

TEST_F(EPModelFixture, PlantLoop_SharedWaterCoilRemovalLifecycle) {
  runSharedWaterCoilRemovalLifecycle<CoilHeatingWater>(
    openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-shared-heating-water-coil-removal.idf"), "Heating Water Coil", "Normal");
}

TEST_F(EPModelFixture, PlantLoop_SharedCoolingCoilRemovalLifecycle) {
  runSharedWaterCoilRemovalLifecycle<CoilCoolingWater>(
    openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-shared-cooling-water-coil-removal.idf"), "Cooling Water Coil", "Reverse");
}

TEST_F(EPModelFixture, PlantLoop_DualLoopHeatExchangerRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-dual-loop-heat-exchanger-removal.idf");

  Model model;
  PlantLoop primaryLoop(model);
  PlantLoop secondaryLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  ASSERT_TRUE(primaryLoop.setName("Removed Primary Heat Exchanger Loop"));
  ASSERT_TRUE(secondaryLoop.setName("Removed Secondary Heat Exchanger Loop"));
  ASSERT_TRUE(heatExchanger.setName("Surviving Dual Loop Heat Exchanger"));
  ASSERT_TRUE(primaryLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(secondaryLoop.addDemandBranchForComponent(heatExchanger));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPrimary = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Primary Heat Exchanger Loop");
  auto loadedSecondary = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Secondary Heat Exchanger Loop");
  auto loadedHeatExchanger =
    loadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Surviving Dual Loop Heat Exchanger");
  ASSERT_TRUE(loadedPrimary);
  ASSERT_TRUE(loadedSecondary);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedHeatExchanger->plantLoop());
  ASSERT_TRUE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*loadedPrimary, *loadedHeatExchanger->plantLoop());
  EXPECT_EQ(*loadedSecondary, *loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedPrimary->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSecondary->demandComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->demandInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->demandOutletModelObject());

  std::vector<openstudio::Handle> primaryTopologyHandles;
  for (const auto& component : loadedPrimary->supplyComponents()) {
    if (component.handle() != loadedHeatExchanger->handle()) {
      primaryTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedPrimary->demandComponents()) {
    primaryTopologyHandles.push_back(component.handle());
  }
  const auto primaryHandle = loadedPrimary->handle();
  const auto primarySizingHandle = loadedPrimary->sizingPlant().handle();
  EXPECT_FALSE(loadedPrimary->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(primaryHandle));
  EXPECT_FALSE(loadedModel->getObject(primarySizingHandle));
  for (const auto& handle : primaryTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedHeatExchanger->plantLoop());
  EXPECT_FALSE(loadedHeatExchanger->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatExchanger->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*loadedSecondary, *loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSecondary->demandComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatExchanger->demandInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->demandOutletModelObject());

  PlantLoop replacementPrimary(*loadedModel);
  ASSERT_TRUE(replacementPrimary.setName("Replacement Primary Heat Exchanger Loop"));
  ASSERT_TRUE(replacementPrimary.addSupplyBranchForComponent(*loadedHeatExchanger));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto primaryReattachedModel = Model::load(idfPath);
  ASSERT_TRUE(primaryReattachedModel);
  auto reattachedHeatExchanger =
    primaryReattachedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Surviving Dual Loop Heat Exchanger");
  auto reattachedPrimary = primaryReattachedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Primary Heat Exchanger Loop");
  auto originalSecondary = primaryReattachedModel->getConcreteModelObjectByName<PlantLoop>("Removed Secondary Heat Exchanger Loop");
  ASSERT_TRUE(reattachedHeatExchanger);
  ASSERT_TRUE(reattachedPrimary);
  ASSERT_TRUE(originalSecondary);
  ASSERT_TRUE(reattachedHeatExchanger->plantLoop());
  ASSERT_TRUE(reattachedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*reattachedPrimary, *reattachedHeatExchanger->plantLoop());
  EXPECT_EQ(*originalSecondary, *reattachedHeatExchanger->secondaryPlantLoop());

  std::vector<openstudio::Handle> secondaryTopologyHandles;
  for (const auto& component : originalSecondary->supplyComponents()) {
    secondaryTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : originalSecondary->demandComponents()) {
    if (component.handle() != reattachedHeatExchanger->handle()) {
      secondaryTopologyHandles.push_back(component.handle());
    }
  }
  const auto secondaryHandle = originalSecondary->handle();
  const auto secondarySizingHandle = originalSecondary->sizingPlant().handle();
  EXPECT_FALSE(originalSecondary->remove().empty());
  EXPECT_FALSE(primaryReattachedModel->getObject(secondaryHandle));
  EXPECT_FALSE(primaryReattachedModel->getObject(secondarySizingHandle));
  for (const auto& handle : secondaryTopologyHandles) {
    EXPECT_FALSE(primaryReattachedModel->getObject(handle));
  }
  EXPECT_FALSE(reattachedHeatExchanger->secondaryPlantLoop());
  EXPECT_FALSE(reattachedHeatExchanger->demandInletModelObject());
  EXPECT_FALSE(reattachedHeatExchanger->demandOutletModelObject());
  ASSERT_TRUE(reattachedHeatExchanger->plantLoop());
  EXPECT_EQ(*reattachedPrimary, *reattachedHeatExchanger->plantLoop());
  EXPECT_EQ(1u, reattachedPrimary->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(reattachedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(reattachedHeatExchanger->supplyOutletModelObject());

  PlantLoop replacementSecondary(*primaryReattachedModel);
  ASSERT_TRUE(replacementSecondary.setName("Replacement Secondary Heat Exchanger Loop"));
  ASSERT_TRUE(replacementSecondary.addDemandBranchForComponent(*reattachedHeatExchanger));
  ASSERT_TRUE(primaryReattachedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedHeatExchanger =
    reloadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Surviving Dual Loop Heat Exchanger");
  auto reloadedPrimary = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Primary Heat Exchanger Loop");
  auto reloadedSecondary = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Secondary Heat Exchanger Loop");
  ASSERT_TRUE(reloadedHeatExchanger);
  ASSERT_TRUE(reloadedPrimary);
  ASSERT_TRUE(reloadedSecondary);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Primary Heat Exchanger Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Secondary Heat Exchanger Loop"));
  ASSERT_TRUE(reloadedHeatExchanger->plantLoop());
  ASSERT_TRUE(reloadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(*reloadedPrimary, *reloadedHeatExchanger->plantLoop());
  EXPECT_EQ(*reloadedSecondary, *reloadedHeatExchanger->secondaryPlantLoop());
  EXPECT_EQ(1u, reloadedPrimary->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSecondary->demandComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(reloadedHeatExchanger->supplyOutletModelObject());
  EXPECT_TRUE(reloadedHeatExchanger->demandInletModelObject());
  EXPECT_TRUE(reloadedHeatExchanger->demandOutletModelObject());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, PlantLoop_LastOwnerHeatExchangerRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-loop-last-owner-heat-exchanger-removal.idf");

  Model model;
  PlantLoop plantLoop(model);
  HeatExchangerFluidToFluid heatExchanger(model);
  ASSERT_TRUE(plantLoop.setName("Last Owner Heat Exchanger Loop"));
  ASSERT_TRUE(heatExchanger.setName("Owned Last Owner Heat Exchanger"));
  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(heatExchanger));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Heat Exchanger Loop");
  auto loadedHeatExchanger = loadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Owned Last Owner Heat Exchanger");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedHeatExchanger);
  ASSERT_TRUE(loadedHeatExchanger->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedHeatExchanger->plantLoop());
  EXPECT_FALSE(loadedHeatExchanger->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatExchanger->tertiaryPlantLoop());
  EXPECT_EQ(1u, loadedPlantLoop->supplyComponents(HeatExchangerFluidToFluid::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatExchanger->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatExchanger->supplyOutletModelObject());
  EXPECT_FALSE(loadedHeatExchanger->demandInletModelObject());
  EXPECT_FALSE(loadedHeatExchanger->demandOutletModelObject());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedPlantLoop->supplyComponents()) {
    if (component.handle() != loadedHeatExchanger->handle()) {
      topologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedPlantLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto loopHandle = loadedPlantLoop->handle();
  const auto sizingHandle = loadedPlantLoop->sizingPlant().handle();
  const auto heatExchangerHandle = loadedHeatExchanger->handle();
  EXPECT_FALSE(loadedPlantLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingHandle));
  EXPECT_FALSE(loadedModel->getObject(heatExchangerHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Heat Exchanger Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatExchangerFluidToFluid>("Owned Last Owner Heat Exchanger"));

  openstudio::filesystem::remove(idfPath);
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

TEST_F(EPModelFixture, PlantLoop_PrimaryOperationScheduleResetIsIsolated) {
  Model model;
  PlantLoop plantLoop(model);
  ScheduleConstant coolingSchedule(model);
  ScheduleConstant primarySchedule(model);

  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationCoolingLoadSchedule(coolingSchedule));
  ASSERT_TRUE(plantLoop.setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  ASSERT_TRUE(plantLoop.plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_TRUE(plantLoop.primaryPlantEquipmentOperationSchemeSchedule());

  plantLoop.resetPrimaryPlantEquipmentOperationSchemeSchedule();

  ASSERT_TRUE(plantLoop.plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(coolingSchedule, *plantLoop.plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_FALSE(plantLoop.primaryPlantEquipmentOperationSchemeSchedule());
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
