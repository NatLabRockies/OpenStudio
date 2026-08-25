/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRCooling_Impl.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"

#include <limits>
#include <utilities/idd/HeatPump_PlantLoop_EIR_Cooling_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_LoadOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-cooling-heat-pump-load-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Removed Cooling Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Cooling Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Cooling Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Cooling Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Surviving Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  std::vector<openstudio::Handle> loadTopologyHandles;
  for (const auto& component : loadedLoadLoop->supplyComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      loadTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedLoadLoop->demandComponents()) {
    loadTopologyHandles.push_back(component.handle());
  }
  const auto loadLoopHandle = loadedLoadLoop->handle();
  const auto loadSizingPlantHandle = loadedLoadLoop->sizingPlant().handle();
  const auto heatPumpHandle = loadedHeatPump->handle();
  EXPECT_FALSE(loadedLoadLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(loadSizingPlantHandle));
  for (const auto& handle : loadTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->loadSideWaterLoop());
  EXPECT_FALSE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_FALSE(loadedHeatPump->loadSideWaterOutletNode());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  PlantLoop replacementLoadLoop(*loadedModel);
  ASSERT_TRUE(replacementLoadLoop.setName("Replacement Cooling Heat Pump Load Loop"));
  ASSERT_TRUE(replacementLoadLoop.addSupplyBranchForComponent(*loadedHeatPump));
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Cooling Heat Pump Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Source Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Heat Recovery Loop");
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Surviving Cooling Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Cooling Heat Pump Load Loop"));
  ASSERT_TRUE(reloadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, reloadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", reloadedHeatPump->condenserType());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_SourceOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-cooling-heat-pump-source-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Cooling Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Removed Cooling Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Cooling Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Cooling Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Surviving Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    sourceTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  const auto heatPumpHandle = loadedHeatPump->handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->sourceSideWaterLoop());
  EXPECT_FALSE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_FALSE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_EQ("AirSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Cooling Heat Pump Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedHeatPump));
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Cooling Heat Pump Source Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Heat Recovery Loop");
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Surviving Cooling Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Cooling Heat Pump Source Loop"));
  ASSERT_TRUE(reloadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedHeatPump->heatRecoveryLoop());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", reloadedHeatPump->condenserType());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_HeatRecoveryOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-cooling-heat-pump-recovery-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Cooling Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Cooling Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Removed Cooling Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Cooling Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Surviving Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  std::vector<openstudio::Handle> recoveryTopologyHandles;
  for (const auto& component : loadedHeatRecoveryLoop->supplyComponents()) {
    recoveryTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedHeatRecoveryLoop->demandComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      recoveryTopologyHandles.push_back(component.handle());
    }
  }
  const auto recoveryLoopHandle = loadedHeatRecoveryLoop->handle();
  const auto recoverySizingPlantHandle = loadedHeatRecoveryLoop->sizingPlant().handle();
  const auto heatPumpHandle = loadedHeatPump->handle();
  EXPECT_FALSE(loadedHeatRecoveryLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(recoveryLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(recoverySizingPlantHandle));
  for (const auto& handle : recoveryTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_FALSE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_FALSE(loadedHeatPump->heatRecoveryOutletNode());
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  PlantLoop replacementHeatRecoveryLoop(*loadedModel);
  ASSERT_TRUE(replacementHeatRecoveryLoop.setName("Replacement Cooling Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(replacementHeatRecoveryLoop.addDemandBranchForComponent(*loadedHeatPump));
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Cooling Heat Pump Source Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Cooling Heat Pump Heat Recovery Loop");
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Surviving Cooling Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Cooling Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(reloadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedHeatPump->heatRecoveryLoop());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", reloadedHeatPump->condenserType());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-cooling-heat-pump-sequential-last-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Final Cooling Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Second Cooling Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("First Cooling Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Sequential Deleted Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Final Cooling Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Second Cooling Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("First Cooling Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Sequential Deleted Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  const auto heatPumpHandle = loadedHeatPump->handle();
  const auto removeOwnerLoop = [&](PlantLoop& loop) {
    std::vector<openstudio::Handle> topologyHandles;
    for (const auto& component : loop.supplyComponents()) {
      if (component.handle() != heatPumpHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    for (const auto& component : loop.demandComponents()) {
      if (component.handle() != heatPumpHandle) {
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

  removeOwnerLoop(*loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->heatRecoveryLoop());
  EXPECT_FALSE(loadedHeatPump->tertiaryInletModelObject());
  EXPECT_FALSE(loadedHeatPump->tertiaryOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(loadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->sourceSideWaterLoop());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  removeOwnerLoop(*loadedSourceLoop);
  ASSERT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->sourceSideWaterLoop());
  EXPECT_FALSE(loadedHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatPump->demandOutletModelObject());
  EXPECT_FALSE(loadedHeatPump->heatRecoveryLoop());
  ASSERT_TRUE(loadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->loadSideWaterLoop());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_EQ("AirSource", loadedHeatPump->condenserType());

  removeOwnerLoop(*loadedLoadLoop);
  EXPECT_FALSE(loadedModel->getObject(heatPumpHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("First Cooling Heat Pump Heat Recovery Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Second Cooling Heat Pump Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Final Cooling Heat Pump Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRCooling>("Sequential Deleted Cooling Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_DefaultConstructor) {
  Model model;
  HeatPumpPlantLoopEIRCooling hp(model);

  EXPECT_EQ(HeatPumpPlantLoopEIRCooling::iddObjectType(), hp.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.tertiaryInletPort());
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());
  EXPECT_FALSE(hp.autosizedLoadSideReferenceFlowRate());
  EXPECT_FALSE(hp.autosizedSourceSideReferenceFlowRate());
  EXPECT_FALSE(hp.autosizedHeatRecoveryReferenceFlowRate());
  EXPECT_FALSE(hp.autosizedReferenceCapacity());

  EXPECT_FALSE(hp.loadSideReferenceFlowRate());
  EXPECT_FALSE(hp.sourceSideReferenceFlowRate());
  EXPECT_FALSE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_FALSE(hp.referenceCapacity());

  EXPECT_EQ(CurveBiquadratic::iddObjectType(), hp.capacityModifierFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveBiquadratic::iddObjectType(), hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveQuadratic::iddObjectType(), hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve().iddObject().type());
  EXPECT_FALSE(hp.companionHeatingHeatPump());
  EXPECT_FALSE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.thermosiphonCapacityFractionCurve());

  EXPECT_FALSE(hp.loadSideWaterLoop());
  EXPECT_FALSE(hp.sourceSideWaterLoop());
  EXPECT_FALSE(hp.heatRecoveryLoop());
  EXPECT_FALSE(hp.loadSideWaterInletNode());
  EXPECT_FALSE(hp.loadSideWaterOutletNode());
  EXPECT_FALSE(hp.sourceSideWaterInletNode());
  EXPECT_FALSE(hp.sourceSideWaterOutletNode());
  EXPECT_FALSE(hp.heatRecoveryInletNode());
  EXPECT_FALSE(hp.heatRecoveryOutletNode());

  EXPECT_DOUBLE_EQ(7.5, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
  EXPECT_EQ("Load", hp.controlType());
  EXPECT_EQ("ConstantFlow", hp.flowMode());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(-100.0, hp.minimumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(100.0, hp.maximumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(60.0, hp.maximumHeatRecoveryOutletTemperature());
  EXPECT_DOUBLE_EQ(0.0, hp.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_CurveConstructorAndSetters) {
  Model model;
  CurveBiquadratic capacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpPlantLoopEIRCooling hp(model, capacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(capacityCurve, hp.capacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());

  CurveBiquadratic replacementCapacity(model);
  CurveBiquadratic replacementEirFT(model);
  CurveQuadratic replacementEirFPLR(model);
  CurveQuadratic minSupply(model);
  CurveQuadratic maxSupply(model);
  CurveBiquadratic heatRecoveryCapacity(model);
  CurveBiquadratic heatRecoveryEir(model);
  CurveQuadratic thermosiphon(model);

  EXPECT_TRUE(hp.setCapacityModifierFunctionofTemperatureCurve(replacementCapacity));
  EXPECT_TRUE(hp.setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(replacementEirFT));
  EXPECT_TRUE(hp.setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(replacementEirFPLR));
  EXPECT_TRUE(hp.setMinimumSupplyWaterTemperatureCurve(minSupply));
  EXPECT_TRUE(hp.setMaximumSupplyWaterTemperatureCurve(maxSupply));
  EXPECT_TRUE(hp.setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(heatRecoveryCapacity));
  EXPECT_TRUE(hp.setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(heatRecoveryEir));
  EXPECT_TRUE(hp.setThermosiphonCapacityFractionCurve(thermosiphon));

  EXPECT_EQ(replacementCapacity, hp.capacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(replacementEirFT, hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(replacementEirFPLR, hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());
  ASSERT_TRUE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_EQ(minSupply, hp.minimumSupplyWaterTemperatureCurve().get());
  ASSERT_TRUE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_EQ(maxSupply, hp.maximumSupplyWaterTemperatureCurve().get());
  ASSERT_TRUE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(heatRecoveryCapacity, hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve().get());
  ASSERT_TRUE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(heatRecoveryEir, hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve().get());
  ASSERT_TRUE(hp.thermosiphonCapacityFractionCurve());
  EXPECT_EQ(thermosiphon, hp.thermosiphonCapacityFractionCurve().get());

  hp.resetMinimumSupplyWaterTemperatureCurve();
  hp.resetMaximumSupplyWaterTemperatureCurve();
  hp.resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();
  hp.resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();
  hp.resetThermosiphonCapacityFractionCurve();

  EXPECT_FALSE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.thermosiphonCapacityFractionCurve());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_CompanionHeatingHeatPumpRoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRCooling cooling(model);
  HeatPumpPlantLoopEIRHeating heating(model);

  EXPECT_FALSE(cooling.companionHeatingHeatPump());
  EXPECT_TRUE(cooling.setCompanionHeatingHeatPump(heating));
  ASSERT_TRUE(cooling.companionHeatingHeatPump());
  EXPECT_EQ(heating, cooling.companionHeatingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRCooling hp(model);

  const auto condenserTypes = HeatPumpPlantLoopEIRCooling::condenserTypeValues();
  ASSERT_FALSE(condenserTypes.empty());
  EXPECT_TRUE(hp.setCondenserType("AirSource"));
  EXPECT_FALSE(hp.setCondenserType("WaterSource"));
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.setLoadSideReferenceFlowRate(0.101));
  ASSERT_TRUE(hp.loadSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.loadSideReferenceFlowRate());
  hp.autosizeLoadSideReferenceFlowRate();
  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());
  EXPECT_FALSE(hp.autosizedLoadSideReferenceFlowRate());

  EXPECT_TRUE(hp.setSourceSideReferenceFlowRate(0.202));
  ASSERT_TRUE(hp.sourceSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.sourceSideReferenceFlowRate());
  hp.autosizeSourceSideReferenceFlowRate();
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());
  EXPECT_FALSE(hp.autosizedSourceSideReferenceFlowRate());

  EXPECT_TRUE(hp.setHeatRecoveryReferenceFlowRate(0.303));
  ASSERT_TRUE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.303, *hp.heatRecoveryReferenceFlowRate());
  hp.autosizeHeatRecoveryReferenceFlowRate();
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());
  EXPECT_FALSE(hp.autosizedHeatRecoveryReferenceFlowRate());

  EXPECT_TRUE(hp.setReferenceCapacity(12450.0));
  ASSERT_TRUE(hp.referenceCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.referenceCapacity());
  hp.autosizeReferenceCapacity();
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());
  EXPECT_FALSE(hp.autosizedReferenceCapacity());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.9));
  EXPECT_DOUBLE_EQ(6.9, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());

  EXPECT_TRUE(hp.setControlType("Setpoint"));
  EXPECT_EQ("Setpoint", hp.controlType());

  EXPECT_TRUE(hp.setFlowMode("VariableSpeedPumping"));
  EXPECT_EQ("VariableSpeedPumping", hp.flowMode());

  EXPECT_TRUE(hp.setMinimumPartLoadRatio(0.25));
  EXPECT_DOUBLE_EQ(0.25, hp.minimumPartLoadRatio());

  EXPECT_TRUE(hp.setMinimumSourceInletTemperature(-9.0));
  EXPECT_DOUBLE_EQ(-9.0, hp.minimumSourceInletTemperature());

  EXPECT_TRUE(hp.setMaximumSourceInletTemperature(77.0));
  EXPECT_DOUBLE_EQ(77.0, hp.maximumSourceInletTemperature());

  EXPECT_TRUE(hp.setMaximumHeatRecoveryOutletTemperature(51.0));
  EXPECT_DOUBLE_EQ(51.0, hp.maximumHeatRecoveryOutletTemperature());

  EXPECT_TRUE(hp.setThermosiphonMinimumTemperatureDifference(0.9));
  EXPECT_DOUBLE_EQ(0.9, hp.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRCooling_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop sourceLoop2(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRCooling hp(model);

  EXPECT_EQ(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideInletNodeName, hp.supplyInletPort());
  EXPECT_EQ(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::LoadSideOutletNodeName, hp.supplyOutletPort());
  EXPECT_EQ(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideInletNodeName, hp.demandInletPort());
  EXPECT_EQ(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::SourceSideOutletNodeName, hp.demandOutletPort());
  EXPECT_EQ(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryInletNodeName, hp.tertiaryInletPort());
  EXPECT_EQ(openstudio::HeatPump_PlantLoop_EIR_CoolingFields::HeatRecoveryOutletNodeName, hp.tertiaryOutletPort());

  EXPECT_TRUE(loadLoop.addSupplyBranchForComponent(hp));
  ASSERT_TRUE(hp.loadSideWaterLoop());
  EXPECT_EQ(loadLoop, hp.loadSideWaterLoop().get());
  ASSERT_TRUE(hp.loadSideWaterInletNode());
  EXPECT_EQ(hp.supplyInletModelObject()->cast<Node>(), hp.loadSideWaterInletNode().get());
  ASSERT_TRUE(hp.loadSideWaterOutletNode());
  EXPECT_EQ(hp.supplyOutletModelObject()->cast<Node>(), hp.loadSideWaterOutletNode().get());

  EXPECT_FALSE(hp.sourceSideWaterLoop());
  EXPECT_FALSE(hp.heatRecoveryLoop());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(hp));
  ASSERT_TRUE(hp.sourceSideWaterLoop());
  EXPECT_EQ(sourceLoop, hp.sourceSideWaterLoop().get());
  EXPECT_EQ("WaterSource", hp.condenserType());
  EXPECT_FALSE(hp.setCondenserType("AirSource"));
  ASSERT_TRUE(hp.sourceSideWaterInletNode());
  EXPECT_EQ(hp.demandInletModelObject()->cast<Node>(), hp.sourceSideWaterInletNode().get());
  ASSERT_TRUE(hp.sourceSideWaterOutletNode());
  EXPECT_EQ(hp.demandOutletModelObject()->cast<Node>(), hp.sourceSideWaterOutletNode().get());
  EXPECT_FALSE(hp.heatRecoveryLoop());

  boost::optional<Node> heatRecoveryNode;
  for (const auto& component : heatRecoveryLoop.demandComponents()) {
    if (auto node = component.optionalCast<Node>()) {
      heatRecoveryNode = *node;
      break;
    }
  }
  ASSERT_TRUE(heatRecoveryNode);
  EXPECT_TRUE(hp.addToNode(*heatRecoveryNode));
  ASSERT_TRUE(hp.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop, hp.heatRecoveryLoop().get());
  ASSERT_TRUE(hp.heatRecoveryInletNode());
  EXPECT_EQ(hp.tertiaryInletModelObject()->cast<Node>(), hp.heatRecoveryInletNode().get());
  ASSERT_TRUE(hp.heatRecoveryOutletNode());
  EXPECT_EQ(hp.tertiaryOutletModelObject()->cast<Node>(), hp.heatRecoveryOutletNode().get());

  boost::optional<Node> sourceLoop2DemandNode;
  for (const auto& component : sourceLoop2.demandComponents()) {
    if (auto node = component.optionalCast<Node>()) {
      sourceLoop2DemandNode = *node;
      break;
    }
  }
  ASSERT_TRUE(sourceLoop2DemandNode);
  EXPECT_TRUE(hp.addToNode(*sourceLoop2DemandNode));
  ASSERT_TRUE(hp.loadSideWaterLoop());
  EXPECT_EQ(loadLoop, hp.loadSideWaterLoop().get());
  ASSERT_TRUE(hp.sourceSideWaterLoop());
  EXPECT_EQ(sourceLoop2, hp.sourceSideWaterLoop().get());
  ASSERT_TRUE(hp.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop, hp.heatRecoveryLoop().get());

  EXPECT_TRUE(hp.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(hp.heatRecoveryLoop());
  EXPECT_FALSE(hp.heatRecoveryInletNode());
  EXPECT_FALSE(hp.heatRecoveryOutletNode());

  auto loadSupplyOutletNode = loadLoop.supplyOutletNode();
  EXPECT_FALSE(hp.addToTertiaryNode(loadSupplyOutletNode));
  EXPECT_FALSE(hp.heatRecoveryLoop());

  auto heatRecoveryDemandNode = heatRecoveryLoop.demandInletNode();
  EXPECT_TRUE(hp.addToNode(heatRecoveryDemandNode));
  ASSERT_TRUE(hp.loadSideWaterLoop());
  EXPECT_EQ(loadLoop, hp.loadSideWaterLoop().get());
  ASSERT_TRUE(hp.sourceSideWaterLoop());
  EXPECT_EQ(sourceLoop2, hp.sourceSideWaterLoop().get());
  ASSERT_TRUE(hp.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop, hp.heatRecoveryLoop().get());

  EXPECT_TRUE(hp.removeFromSecondaryPlantLoop());
  EXPECT_EQ("AirSource", hp.condenserType());
  EXPECT_FALSE(hp.sourceSideWaterLoop());
  EXPECT_FALSE(hp.setCondenserType("WaterSource"));
}
