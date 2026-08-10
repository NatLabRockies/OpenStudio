/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/CentralHeatPumpSystem.hpp"
#include "../WaterToWaterComponent/CentralHeatPumpSystem_Impl.hpp"

#include <utilities/idd/CentralHeatPumpSystem_FieldEnums.hxx>

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CentralHeatPumpSystem_DirectTertiarySupplyEndpointLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-central-heat-pump-tertiary-endpoint.idf");

  Model model;
  PlantLoop coolingLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ASSERT_TRUE(coolingLoop.setName("Endpoint Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(sourceLoop.setName("Endpoint Central Heat Pump Source Loop"));
  ASSERT_TRUE(heatingLoop.setName("Endpoint Central Heat Pump Heating Loop"));
  ASSERT_TRUE(centralHeatPumpSystem.setName("Endpoint Central Heat Pump System"));
  ASSERT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));

  auto heatingOutlet = heatingLoop.supplyOutletNode();
  ASSERT_TRUE(centralHeatPumpSystem.addToTertiaryNode(heatingOutlet));
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop, *centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(1u, heatingLoop.supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  ASSERT_TRUE(centralHeatPumpSystem.tertiaryInletModelObject());
  ASSERT_TRUE(centralHeatPumpSystem.tertiaryOutletModelObject());
  EXPECT_NE(heatingOutlet, centralHeatPumpSystem.tertiaryInletModelObject()->cast<Node>());
  EXPECT_EQ(heatingOutlet, centralHeatPumpSystem.tertiaryOutletModelObject()->cast<Node>());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoolingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Endpoint Central Heat Pump Cooling Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Endpoint Central Heat Pump Source Loop");
  auto loadedHeatingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Endpoint Central Heat Pump Heating Loop");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Endpoint Central Heat Pump System");
  ASSERT_TRUE(loadedCoolingLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoop);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedHeatingLoop, *loadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, loadedCoolingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  ASSERT_TRUE(loadedSystem->tertiaryInletModelObject());
  ASSERT_TRUE(loadedSystem->tertiaryOutletModelObject());
  EXPECT_NE(loadedHeatingLoop->supplyOutletNode(), loadedSystem->tertiaryInletModelObject()->cast<Node>());
  EXPECT_EQ(loadedHeatingLoop->supplyOutletNode(), loadedSystem->tertiaryOutletModelObject()->cast<Node>());

  ASSERT_TRUE(loadedSystem->removeFromTertiaryPlantLoop());
  EXPECT_FALSE(loadedSystem->heatingPlantLoop());
  EXPECT_FALSE(loadedSystem->tertiaryInletModelObject());
  EXPECT_FALSE(loadedSystem->tertiaryOutletModelObject());
  EXPECT_TRUE(loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).empty());
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());

  auto loadedHeatingOutlet = loadedHeatingLoop->supplyOutletNode();
  ASSERT_TRUE(loadedSystem->addToTertiaryNode(loadedHeatingOutlet));
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedHeatingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Endpoint Central Heat Pump Heating Loop");
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Endpoint Central Heat Pump System");
  ASSERT_TRUE(reloadedHeatingLoop);
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedSystem->heatingPlantLoop());
  EXPECT_EQ(*reloadedHeatingLoop, *reloadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, reloadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  ASSERT_TRUE(reloadedSystem->tertiaryInletModelObject());
  ASSERT_TRUE(reloadedSystem->tertiaryOutletModelObject());
  EXPECT_NE(reloadedHeatingLoop->supplyOutletNode(), reloadedSystem->tertiaryInletModelObject()->cast<Node>());
  EXPECT_EQ(reloadedHeatingLoop->supplyOutletNode(), reloadedSystem->tertiaryOutletModelObject()->cast<Node>());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-central-heat-pump-sequential-last-owner-removal.idf");

  Model model;
  PlantLoop coolingLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ScheduleConstant ancillarySchedule(model);
  ASSERT_TRUE(coolingLoop.setName("Final Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(sourceLoop.setName("Second Central Heat Pump Source Loop"));
  ASSERT_TRUE(heatingLoop.setName("First Central Heat Pump Heating Loop"));
  ASSERT_TRUE(centralHeatPumpSystem.setName("Sequential Deleted Central Heat Pump System"));
  ASSERT_TRUE(ancillarySchedule.setName("Surviving Sequential Central Heat Pump Schedule"));
  ASSERT_TRUE(centralHeatPumpSystem.setAncillaryOperationSchedule(ancillarySchedule));
  ASSERT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(heatingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoolingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Final Central Heat Pump Cooling Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Second Central Heat Pump Source Loop");
  auto loadedHeatingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("First Central Heat Pump Heating Loop");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Sequential Deleted Central Heat Pump System");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Surviving Sequential Central Heat Pump Schedule");
  ASSERT_TRUE(loadedCoolingLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoop);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  const auto systemHandle = loadedSystem->handle();
  const auto scheduleHandle = loadedSchedule->handle();
  const auto removeOwnerLoop = [&](PlantLoop& loop) {
    std::vector<openstudio::Handle> topologyHandles;
    for (const auto& component : loop.supplyComponents()) {
      if (component.handle() != systemHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    for (const auto& component : loop.demandComponents()) {
      if (component.handle() != systemHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    const auto loopHandle = loop.handle();
    const auto sizingPlantHandle = loop.sizingPlant().handle();
    EXPECT_FALSE(loop.remove().empty());
    EXPECT_FALSE(loadedModel->getObject(loopHandle));
    EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
    for (const auto& handle : topologyHandles) {
      EXPECT_FALSE(loadedModel->getObject(handle));
    }
  };

  removeOwnerLoop(*loadedHeatingLoop);
  ASSERT_TRUE(loadedModel->getObject(systemHandle));
  EXPECT_FALSE(loadedSystem->heatingPlantLoop());
  EXPECT_FALSE(loadedSystem->tertiaryInletModelObject());
  EXPECT_FALSE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(loadedSystem->demandInletModelObject());
  EXPECT_TRUE(loadedSystem->demandOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  removeOwnerLoop(*loadedSourceLoop);
  ASSERT_TRUE(loadedModel->getObject(systemHandle));
  EXPECT_FALSE(loadedSystem->sourcePlantLoop());
  EXPECT_FALSE(loadedSystem->demandInletModelObject());
  EXPECT_FALSE(loadedSystem->demandOutletModelObject());
  EXPECT_FALSE(loadedSystem->heatingPlantLoop());
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  removeOwnerLoop(*loadedCoolingLoop);
  EXPECT_FALSE(loadedModel->getObject(systemHandle));
  EXPECT_TRUE(loadedModel->getObject(scheduleHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("First Central Heat Pump Heating Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Second Central Heat Pump Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Final Central Heat Pump Cooling Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Sequential Deleted Central Heat Pump System"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Surviving Sequential Central Heat Pump Schedule"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_SourceOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-central-heat-pump-source-owner-removal.idf");

  Model model;
  PlantLoop coolingLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ScheduleConstant ancillarySchedule(model);
  ASSERT_TRUE(coolingLoop.setName("Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(sourceLoop.setName("Removed Central Heat Pump Source Loop"));
  ASSERT_TRUE(heatingLoop.setName("Central Heat Pump Heating Loop"));
  ASSERT_TRUE(centralHeatPumpSystem.setName("Surviving Central Heat Pump System"));
  ASSERT_TRUE(ancillarySchedule.setName("Central Heat Pump Ancillary Schedule"));
  ASSERT_TRUE(centralHeatPumpSystem.setAncillaryOperationSchedule(ancillarySchedule));
  ASSERT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(heatingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoolingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Cooling Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Central Heat Pump Source Loop");
  auto loadedHeatingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Heating Loop");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Surviving Central Heat Pump System");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Central Heat Pump Ancillary Schedule");
  ASSERT_TRUE(loadedCoolingLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoop);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedHeatingLoop, *loadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, loadedCoolingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(loadedSystem->demandInletModelObject());
  EXPECT_TRUE(loadedSystem->demandOutletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    sourceTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != loadedSystem->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  const auto systemHandle = loadedSystem->handle();
  const auto scheduleHandle = loadedSchedule->handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(systemHandle));
  EXPECT_TRUE(loadedModel->getObject(scheduleHandle));
  EXPECT_FALSE(loadedSystem->sourcePlantLoop());
  EXPECT_FALSE(loadedSystem->demandInletModelObject());
  EXPECT_FALSE(loadedSystem->demandOutletModelObject());
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedHeatingLoop, *loadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, loadedCoolingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Central Heat Pump Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedSystem));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoolingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Cooling Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Central Heat Pump Source Loop");
  auto reloadedHeatingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Heating Loop");
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Surviving Central Heat Pump System");
  auto reloadedSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Central Heat Pump Ancillary Schedule");
  ASSERT_TRUE(reloadedCoolingLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatingLoop);
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedSchedule);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Central Heat Pump Source Loop"));
  ASSERT_TRUE(reloadedSystem->coolingPlantLoop());
  ASSERT_TRUE(reloadedSystem->sourcePlantLoop());
  ASSERT_TRUE(reloadedSystem->heatingPlantLoop());
  EXPECT_EQ(*reloadedCoolingLoop, *reloadedSystem->coolingPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedSystem->sourcePlantLoop());
  EXPECT_EQ(*reloadedHeatingLoop, *reloadedSystem->heatingPlantLoop());
  EXPECT_TRUE(reloadedSystem->supplyInletModelObject());
  EXPECT_TRUE(reloadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(reloadedSystem->demandInletModelObject());
  EXPECT_TRUE(reloadedSystem->demandOutletModelObject());
  EXPECT_TRUE(reloadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(reloadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(reloadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*reloadedSchedule, *reloadedSystem->ancillaryOperationSchedule());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_CoolingOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-central-heat-pump-cooling-owner-removal.idf");

  Model model;
  PlantLoop coolingLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ScheduleConstant ancillarySchedule(model);
  ASSERT_TRUE(coolingLoop.setName("Removed Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(sourceLoop.setName("Central Heat Pump Source Loop"));
  ASSERT_TRUE(heatingLoop.setName("Central Heat Pump Heating Loop"));
  ASSERT_TRUE(centralHeatPumpSystem.setName("Surviving Central Heat Pump System"));
  ASSERT_TRUE(ancillarySchedule.setName("Central Heat Pump Ancillary Schedule"));
  ASSERT_TRUE(centralHeatPumpSystem.setAncillaryOperationSchedule(ancillarySchedule));
  ASSERT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(heatingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoolingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Central Heat Pump Cooling Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Source Loop");
  auto loadedHeatingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Heating Loop");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Surviving Central Heat Pump System");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Central Heat Pump Ancillary Schedule");
  ASSERT_TRUE(loadedCoolingLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoop);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedHeatingLoop, *loadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, loadedCoolingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(loadedSystem->demandInletModelObject());
  EXPECT_TRUE(loadedSystem->demandOutletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  std::vector<openstudio::Handle> coolingTopologyHandles;
  for (const auto& component : loadedCoolingLoop->supplyComponents()) {
    if (component.handle() != loadedSystem->handle()) {
      coolingTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedCoolingLoop->demandComponents()) {
    coolingTopologyHandles.push_back(component.handle());
  }
  const auto coolingLoopHandle = loadedCoolingLoop->handle();
  const auto coolingSizingPlantHandle = loadedCoolingLoop->sizingPlant().handle();
  const auto systemHandle = loadedSystem->handle();
  const auto scheduleHandle = loadedSchedule->handle();
  EXPECT_FALSE(loadedCoolingLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(coolingLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingSizingPlantHandle));
  for (const auto& handle : coolingTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(systemHandle));
  EXPECT_TRUE(loadedModel->getObject(scheduleHandle));
  EXPECT_FALSE(loadedSystem->coolingPlantLoop());
  EXPECT_FALSE(loadedSystem->supplyInletModelObject());
  EXPECT_FALSE(loadedSystem->supplyOutletModelObject());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedHeatingLoop, *loadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_TRUE(loadedSystem->demandInletModelObject());
  EXPECT_TRUE(loadedSystem->demandOutletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  PlantLoop replacementCoolingLoop(*loadedModel);
  ASSERT_TRUE(replacementCoolingLoop.setName("Replacement Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(replacementCoolingLoop.addSupplyBranchForComponent(*loadedSystem));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoolingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Central Heat Pump Cooling Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Source Loop");
  auto reloadedHeatingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Heating Loop");
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Surviving Central Heat Pump System");
  auto reloadedSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Central Heat Pump Ancillary Schedule");
  ASSERT_TRUE(reloadedCoolingLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatingLoop);
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedSchedule);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(reloadedSystem->coolingPlantLoop());
  ASSERT_TRUE(reloadedSystem->sourcePlantLoop());
  ASSERT_TRUE(reloadedSystem->heatingPlantLoop());
  EXPECT_EQ(*reloadedCoolingLoop, *reloadedSystem->coolingPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedSystem->sourcePlantLoop());
  EXPECT_EQ(*reloadedHeatingLoop, *reloadedSystem->heatingPlantLoop());
  EXPECT_TRUE(reloadedSystem->supplyInletModelObject());
  EXPECT_TRUE(reloadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(reloadedSystem->demandInletModelObject());
  EXPECT_TRUE(reloadedSystem->demandOutletModelObject());
  EXPECT_TRUE(reloadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(reloadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(reloadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*reloadedSchedule, *reloadedSystem->ancillaryOperationSchedule());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_HeatingOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-central-heat-pump-heating-owner-removal.idf");

  Model model;
  PlantLoop coolingLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ScheduleConstant ancillarySchedule(model);
  ASSERT_TRUE(coolingLoop.setName("Central Heat Pump Cooling Loop"));
  ASSERT_TRUE(sourceLoop.setName("Central Heat Pump Source Loop"));
  ASSERT_TRUE(heatingLoop.setName("Removed Central Heat Pump Heating Loop"));
  ASSERT_TRUE(centralHeatPumpSystem.setName("Surviving Central Heat Pump System"));
  ASSERT_TRUE(ancillarySchedule.setName("Central Heat Pump Ancillary Schedule"));
  ASSERT_TRUE(centralHeatPumpSystem.setAncillaryOperationSchedule(ancillarySchedule));
  ASSERT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(heatingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoolingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Cooling Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Source Loop");
  auto loadedHeatingLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Central Heat Pump Heating Loop");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Surviving Central Heat Pump System");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Central Heat Pump Ancillary Schedule");
  ASSERT_TRUE(loadedCoolingLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoop);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  ASSERT_TRUE(loadedSystem->heatingPlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedHeatingLoop, *loadedSystem->heatingPlantLoop());
  EXPECT_EQ(1u, loadedCoolingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(loadedSystem->demandInletModelObject());
  EXPECT_TRUE(loadedSystem->demandOutletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  std::vector<openstudio::Handle> heatingTopologyHandles;
  for (const auto& component : loadedHeatingLoop->supplyComponents()) {
    if (component.handle() != loadedSystem->handle()) {
      heatingTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedHeatingLoop->demandComponents()) {
    heatingTopologyHandles.push_back(component.handle());
  }
  const auto heatingLoopHandle = loadedHeatingLoop->handle();
  const auto heatingSizingPlantHandle = loadedHeatingLoop->sizingPlant().handle();
  const auto systemHandle = loadedSystem->handle();
  const auto scheduleHandle = loadedSchedule->handle();
  EXPECT_FALSE(loadedHeatingLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(heatingLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(heatingSizingPlantHandle));
  for (const auto& handle : heatingTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(systemHandle));
  EXPECT_TRUE(loadedModel->getObject(scheduleHandle));
  EXPECT_FALSE(loadedSystem->heatingPlantLoop());
  EXPECT_FALSE(loadedSystem->tertiaryInletModelObject());
  EXPECT_FALSE(loadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedSystem->coolingPlantLoop());
  ASSERT_TRUE(loadedSystem->sourcePlantLoop());
  EXPECT_EQ(*loadedCoolingLoop, *loadedSystem->coolingPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedSystem->sourcePlantLoop());
  EXPECT_EQ(1u, loadedCoolingLoop->supplyComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(CentralHeatPumpSystem::iddObjectType()).size());
  EXPECT_TRUE(loadedSystem->supplyInletModelObject());
  EXPECT_TRUE(loadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(loadedSystem->demandInletModelObject());
  EXPECT_TRUE(loadedSystem->demandOutletModelObject());
  ASSERT_TRUE(loadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*loadedSchedule, *loadedSystem->ancillaryOperationSchedule());

  PlantLoop replacementHeatingLoop(*loadedModel);
  ASSERT_TRUE(replacementHeatingLoop.setName("Replacement Central Heat Pump Heating Loop"));
  ASSERT_TRUE(replacementHeatingLoop.addSupplyBranchForComponent(*loadedSystem));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoolingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Cooling Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Central Heat Pump Source Loop");
  auto reloadedHeatingLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Central Heat Pump Heating Loop");
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<CentralHeatPumpSystem>("Surviving Central Heat Pump System");
  auto reloadedSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Central Heat Pump Ancillary Schedule");
  ASSERT_TRUE(reloadedCoolingLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatingLoop);
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedSchedule);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Central Heat Pump Heating Loop"));
  ASSERT_TRUE(reloadedSystem->coolingPlantLoop());
  ASSERT_TRUE(reloadedSystem->sourcePlantLoop());
  ASSERT_TRUE(reloadedSystem->heatingPlantLoop());
  EXPECT_EQ(*reloadedCoolingLoop, *reloadedSystem->coolingPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedSystem->sourcePlantLoop());
  EXPECT_EQ(*reloadedHeatingLoop, *reloadedSystem->heatingPlantLoop());
  EXPECT_TRUE(reloadedSystem->supplyInletModelObject());
  EXPECT_TRUE(reloadedSystem->supplyOutletModelObject());
  EXPECT_TRUE(reloadedSystem->demandInletModelObject());
  EXPECT_TRUE(reloadedSystem->demandOutletModelObject());
  EXPECT_TRUE(reloadedSystem->tertiaryInletModelObject());
  EXPECT_TRUE(reloadedSystem->tertiaryOutletModelObject());
  ASSERT_TRUE(reloadedSystem->ancillaryOperationSchedule());
  EXPECT_EQ(*reloadedSchedule, *reloadedSystem->ancillaryOperationSchedule());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_DefaultConstructor) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  EXPECT_EQ(CentralHeatPumpSystem::iddObjectType(), centralHeatPumpSystem.iddObject().type());
  EXPECT_EQ("SmartMixing", centralHeatPumpSystem.controlMethod());
  EXPECT_DOUBLE_EQ(0.0, centralHeatPumpSystem.ancillaryPower());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::CoolingLoopInletNodeName, centralHeatPumpSystem.supplyInletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::CoolingLoopOutletNodeName, centralHeatPumpSystem.supplyOutletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::SourceLoopInletNodeName, centralHeatPumpSystem.demandInletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::SourceLoopOutletNodeName, centralHeatPumpSystem.demandOutletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::HeatingLoopInletNodeName, centralHeatPumpSystem.tertiaryInletPort());
  EXPECT_EQ(openstudio::CentralHeatPumpSystemFields::HeatingLoopOutletNodeName, centralHeatPumpSystem.tertiaryOutletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), centralHeatPumpSystem.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), centralHeatPumpSystem.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), centralHeatPumpSystem.tertiaryInletPort());
  EXPECT_FALSE(centralHeatPumpSystem.ancillaryOperationSchedule());
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_ScalarAccessors_RoundTrip) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);

  const auto values = CentralHeatPumpSystem::controlMethodValues();
  ASSERT_FALSE(values.empty());
  EXPECT_TRUE(centralHeatPumpSystem.setControlMethod(values.front()));
  EXPECT_EQ(values.front(), centralHeatPumpSystem.controlMethod());

  EXPECT_TRUE(centralHeatPumpSystem.setAncillaryPower(17.25));
  EXPECT_DOUBLE_EQ(17.25, centralHeatPumpSystem.ancillaryPower());
}

TEST_F(EPModelFixture, CentralHeatPumpSystem_RelationshipAndThreeLoopTopology) {
  Model model;
  CentralHeatPumpSystem centralHeatPumpSystem(model);
  ScheduleConstant ancillarySchedule(model);
  PlantLoop coolingLoop(model);
  PlantLoop coolingLoop2(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoop(model);

  ASSERT_TRUE(ancillarySchedule.setValue(1.0));

  EXPECT_TRUE(centralHeatPumpSystem.setAncillaryOperationSchedule(ancillarySchedule));
  ASSERT_TRUE(centralHeatPumpSystem.ancillaryOperationSchedule());
  EXPECT_EQ(ancillarySchedule.handle(), centralHeatPumpSystem.ancillaryOperationSchedule()->handle());
  centralHeatPumpSystem.resetAncillaryOperationSchedule();
  EXPECT_FALSE(centralHeatPumpSystem.ancillaryOperationSchedule());

  EXPECT_TRUE(coolingLoop.addSupplyBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(centralHeatPumpSystem.coolingPlantLoop());
  EXPECT_EQ(coolingLoop.handle(), centralHeatPumpSystem.coolingPlantLoop()->handle());
  EXPECT_FALSE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_FALSE(centralHeatPumpSystem.heatingPlantLoop());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(centralHeatPumpSystem));
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());
  EXPECT_FALSE(centralHeatPumpSystem.heatingPlantLoop());

  auto heatingSupplyOutletNode = heatingLoop.supplyOutletNode();
  EXPECT_TRUE(centralHeatPumpSystem.addToNode(heatingSupplyOutletNode));
  EXPECT_TRUE(centralHeatPumpSystem.tertiaryInletModelObject());
  EXPECT_TRUE(centralHeatPumpSystem.tertiaryOutletModelObject());
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());

  auto sourceDemandInletNode = sourceLoop.demandInletNode();
  EXPECT_FALSE(centralHeatPumpSystem.addToTertiaryNode(sourceDemandInletNode));
  ASSERT_TRUE(centralHeatPumpSystem.coolingPlantLoop());
  EXPECT_EQ(coolingLoop.handle(), centralHeatPumpSystem.coolingPlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());

  auto coolingSupplyOutletNode2 = coolingLoop2.supplyOutletNode();
  EXPECT_TRUE(centralHeatPumpSystem.addToNode(coolingSupplyOutletNode2));

  ASSERT_TRUE(centralHeatPumpSystem.coolingPlantLoop());
  EXPECT_EQ(coolingLoop2.handle(), centralHeatPumpSystem.coolingPlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.sourcePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), centralHeatPumpSystem.sourcePlantLoop()->handle());
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());

  EXPECT_TRUE(centralHeatPumpSystem.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(centralHeatPumpSystem.heatingPlantLoop());

  EXPECT_TRUE(centralHeatPumpSystem.addToTertiaryNode(heatingSupplyOutletNode));
  ASSERT_TRUE(centralHeatPumpSystem.heatingPlantLoop());
  EXPECT_EQ(heatingLoop.handle(), centralHeatPumpSystem.heatingPlantLoop()->handle());
}
