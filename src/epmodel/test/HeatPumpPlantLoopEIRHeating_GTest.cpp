/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRCooling.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRHeating.hpp"
#include "../WaterToWaterComponent/HeatPumpPlantLoopEIRHeating_Impl.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_LoadOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-heating-heat-pump-load-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRHeating heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Removed Heating Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Heating Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Heating Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Heating Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Heating Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Surviving Heating Heat Pump");
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
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
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
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  PlantLoop replacementLoadLoop(*loadedModel);
  ASSERT_TRUE(replacementLoadLoop.setName("Replacement Heating Heat Pump Load Loop"));
  ASSERT_TRUE(replacementLoadLoop.addSupplyBranchForComponent(*loadedHeatPump));
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Heating Heat Pump Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Source Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Heat Recovery Loop");
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Surviving Heating Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Heating Heat Pump Load Loop"));
  ASSERT_TRUE(reloadedHeatPump->loadSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->sourceSideWaterLoop());
  ASSERT_TRUE(reloadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->loadSideWaterLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->sourceSideWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedHeatPump->heatRecoveryLoop());
  EXPECT_EQ(1u, reloadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(reloadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedHeatPump->heatRecoveryOutletNode());
  EXPECT_EQ("WaterSource", reloadedHeatPump->condenserType());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_SourceOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-heating-heat-pump-source-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRHeating heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Heating Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Removed Heating Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Heating Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Heating Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Heating Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Surviving Heating Heat Pump");
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
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
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
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryInletNode());
  EXPECT_TRUE(loadedHeatPump->heatRecoveryOutletNode());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Heating Heat Pump Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedHeatPump));
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Heating Heat Pump Source Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Heat Recovery Loop");
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Surviving Heating Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Heating Heat Pump Source Loop"));
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

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_HeatRecoveryOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-heating-heat-pump-recovery-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRHeating heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Heating Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Heating Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Removed Heating Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Heating Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Heating Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Surviving Heating Heat Pump");
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
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
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
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpPlantLoopEIRHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->loadSideWaterOutletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterInletNode());
  EXPECT_TRUE(loadedHeatPump->sourceSideWaterOutletNode());
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());

  PlantLoop replacementHeatRecoveryLoop(*loadedModel);
  ASSERT_TRUE(replacementHeatRecoveryLoop.setName("Replacement Heating Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(replacementHeatRecoveryLoop.addDemandBranchForComponent(*loadedHeatPump));
  EXPECT_EQ("WaterSource", loadedHeatPump->condenserType());
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Heating Heat Pump Source Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Heating Heat Pump Heat Recovery Loop");
  auto reloadedHeatPump = reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Surviving Heating Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Heating Heat Pump Heat Recovery Loop"));
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

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-heating-heat-pump-sequential-last-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRHeating heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Final Heating Heat Pump Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Second Heating Heat Pump Source Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("First Heating Heat Pump Heat Recovery Loop"));
  ASSERT_TRUE(heatPump.setName("Sequential Deleted Heating Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(heatPump));
  EXPECT_EQ("WaterSource", heatPump.condenserType());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Final Heating Heat Pump Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Second Heating Heat Pump Source Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("First Heating Heat Pump Heat Recovery Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Sequential Deleted Heating Heat Pump");
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
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("First Heating Heat Pump Heat Recovery Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Second Heating Heat Pump Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Final Heating Heat Pump Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpPlantLoopEIRHeating>("Sequential Deleted Heating Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_DefaultConstructor) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  EXPECT_EQ(HeatPumpPlantLoopEIRHeating::iddObjectType(), hp.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hp.tertiaryInletPort());
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());

  EXPECT_FALSE(hp.loadSideReferenceFlowRate());
  EXPECT_FALSE(hp.sourceSideReferenceFlowRate());
  EXPECT_FALSE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_FALSE(hp.referenceCapacity());

  EXPECT_EQ(CurveBiquadratic::iddObjectType(), hp.capacityModifierFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveBiquadratic::iddObjectType(), hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveQuadratic::iddObjectType(), hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve().iddObject().type());
  EXPECT_FALSE(hp.companionCoolingHeatPump());
  EXPECT_FALSE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.dryOutdoorCorrectionFactorCurve());
  EXPECT_FALSE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostFrequencyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatLoadPenaltyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve());
  EXPECT_FALSE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());

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
  EXPECT_DOUBLE_EQ(1.0, hp.heatingToCoolingCapacitySizingRatio());
  EXPECT_EQ("CoolingCapacity", hp.heatPumpSizingMethod());
  EXPECT_EQ("Load", hp.controlType());
  EXPECT_EQ("ConstantFlow", hp.flowMode());
  EXPECT_DOUBLE_EQ(0.0, hp.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(-100.0, hp.minimumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(100.0, hp.maximumSourceInletTemperature());
  EXPECT_DOUBLE_EQ(10.0, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());
  EXPECT_EQ("None", hp.heatPumpDefrostControl());
  EXPECT_DOUBLE_EQ(0.058333, hp.heatPumpDefrostTimePeriodFraction());
  EXPECT_DOUBLE_EQ(4.5, hp.minimumHeatRecoveryOutletTemperature());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_CurveConstructorAndSetters) {
  Model model;
  CurveBiquadratic capacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpPlantLoopEIRHeating hp(model, capacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(capacityCurve, hp.capacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());

  CurveBiquadratic replacementCapacity(model);
  CurveBiquadratic replacementEirFT(model);
  CurveQuadratic replacementEirFPLR(model);
  CurveQuadratic minSupply(model);
  CurveQuadratic maxSupply(model);
  CurveQuadratic dryOutdoor(model);
  CurveBiquadratic defrostEir(model);
  CurveQuadratic defrostFrequency(model);
  CurveQuadratic defrostPenalty(model);
  CurveQuadratic defrostEnergyFraction(model);
  CurveBiquadratic heatRecoveryCapacity(model);
  CurveBiquadratic heatRecoveryEir(model);

  EXPECT_TRUE(hp.setCapacityModifierFunctionofTemperatureCurve(replacementCapacity));
  EXPECT_TRUE(hp.setElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(replacementEirFT));
  EXPECT_TRUE(hp.setElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve(replacementEirFPLR));
  EXPECT_TRUE(hp.setMinimumSupplyWaterTemperatureCurve(minSupply));
  EXPECT_TRUE(hp.setMaximumSupplyWaterTemperatureCurve(maxSupply));
  EXPECT_TRUE(hp.setDryOutdoorCorrectionFactorCurve(dryOutdoor));
  EXPECT_TRUE(hp.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostEir));
  EXPECT_TRUE(hp.setTimedEmpiricalDefrostFrequencyCurve(defrostFrequency));
  EXPECT_TRUE(hp.setTimedEmpiricalDefrostHeatLoadPenaltyCurve(defrostPenalty));
  EXPECT_TRUE(hp.setTimedEmpiricalDefrostHeatInputEnergyFractionCurve(defrostEnergyFraction));
  EXPECT_TRUE(hp.setHeatRecoveryCapacityModifierFunctionofTemperatureCurve(heatRecoveryCapacity));
  EXPECT_TRUE(hp.setHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve(heatRecoveryEir));

  EXPECT_EQ(replacementCapacity, hp.capacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(replacementEirFT, hp.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(replacementEirFPLR, hp.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());
  ASSERT_TRUE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_EQ(minSupply, hp.minimumSupplyWaterTemperatureCurve().get());
  ASSERT_TRUE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_EQ(maxSupply, hp.maximumSupplyWaterTemperatureCurve().get());
  ASSERT_TRUE(hp.dryOutdoorCorrectionFactorCurve());
  EXPECT_EQ(dryOutdoor, hp.dryOutdoorCorrectionFactorCurve().get());
  ASSERT_TRUE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(defrostEir, hp.defrostEnergyInputRatioFunctionofTemperatureCurve().get());
  ASSERT_TRUE(hp.timedEmpiricalDefrostFrequencyCurve());
  EXPECT_EQ(defrostFrequency, hp.timedEmpiricalDefrostFrequencyCurve().get());
  ASSERT_TRUE(hp.timedEmpiricalDefrostHeatLoadPenaltyCurve());
  EXPECT_EQ(defrostPenalty, hp.timedEmpiricalDefrostHeatLoadPenaltyCurve().get());
  ASSERT_TRUE(hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve());
  EXPECT_EQ(defrostEnergyFraction, hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve().get());
  ASSERT_TRUE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_EQ(heatRecoveryCapacity, hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve().get());
  ASSERT_TRUE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(heatRecoveryEir, hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve().get());

  hp.resetMinimumSupplyWaterTemperatureCurve();
  hp.resetMaximumSupplyWaterTemperatureCurve();
  hp.resetDryOutdoorCorrectionFactorCurve();
  hp.resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  hp.resetTimedEmpiricalDefrostFrequencyCurve();
  hp.resetTimedEmpiricalDefrostHeatLoadPenaltyCurve();
  hp.resetTimedEmpiricalDefrostHeatInputEnergyFractionCurve();
  hp.resetHeatRecoveryCapacityModifierFunctionofTemperatureCurve();
  hp.resetHeatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve();

  EXPECT_FALSE(hp.minimumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.maximumSupplyWaterTemperatureCurve());
  EXPECT_FALSE(hp.dryOutdoorCorrectionFactorCurve());
  EXPECT_FALSE(hp.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostFrequencyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatLoadPenaltyCurve());
  EXPECT_FALSE(hp.timedEmpiricalDefrostHeatInputEnergyFractionCurve());
  EXPECT_FALSE(hp.heatRecoveryCapacityModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(hp.heatRecoveryElectricInputtoOutputRatioModifierFunctionofTemperatureCurve());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_CompanionCoolingHeatPumpRoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRCooling cooling(model);
  HeatPumpPlantLoopEIRHeating heating(model);

  EXPECT_FALSE(heating.companionCoolingHeatPump());
  EXPECT_TRUE(heating.setCompanionCoolingHeatPump(cooling));
  ASSERT_TRUE(heating.companionCoolingHeatPump());
  EXPECT_EQ(cooling, heating.companionCoolingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_Remove) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  const auto initialObjects = model.objects().size();
  EXPECT_FALSE(hp.remove().empty());
  EXPECT_EQ(initialObjects - 1, model.objects().size());
  EXPECT_TRUE(model.getConcreteModelObjects<HeatPumpPlantLoopEIRHeating>().empty());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_Clone) {
  Model model;
  CurveBiquadratic capacityCurve(model);
  CurveBiquadratic eirFT(model);
  CurveQuadratic eirFPLR(model);

  HeatPumpPlantLoopEIRHeating hp(model, capacityCurve, eirFT, eirFPLR);
  EXPECT_EQ(2u, model.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CurveQuadratic>().size());

  {
    auto hpCloneObject = model.addObject(hp.idfObject());
    ASSERT_TRUE(hpCloneObject);
    auto hpClone = hpCloneObject->cast<HeatPumpPlantLoopEIRHeating>();
    EXPECT_EQ(capacityCurve, hpClone.capacityModifierFunctionofTemperatureCurve());
    EXPECT_EQ(eirFT, hpClone.electricInputtoOutputRatioModifierFunctionofTemperatureCurve());
    EXPECT_EQ(eirFPLR, hpClone.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve());
    EXPECT_EQ(2u, model.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1u, model.getConcreteModelObjects<CurveQuadratic>().size());
  }

  {
    Model model2;
    const auto hpIdfObject = hp.idfObject();
    const auto hpCloneObjects = model2.addObjects({capacityCurve.idfObject(), eirFT.idfObject(), eirFPLR.idfObject(), hpIdfObject});
    ASSERT_EQ(4u, hpCloneObjects.size());
    auto hpClones = model2.getConcreteModelObjects<HeatPumpPlantLoopEIRHeating>();
    ASSERT_EQ(1u, hpClones.size());
    auto hpClone = hpClones.front();
    EXPECT_EQ(CurveBiquadratic::iddObjectType(), hpClone.capacityModifierFunctionofTemperatureCurve().iddObject().type());
    EXPECT_EQ(CurveBiquadratic::iddObjectType(), hpClone.electricInputtoOutputRatioModifierFunctionofTemperatureCurve().iddObject().type());
    EXPECT_EQ(CurveQuadratic::iddObjectType(), hpClone.electricInputtoOutputRatioModifierFunctionofPartLoadRatioCurve().iddObject().type());
    EXPECT_EQ(2u, model2.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1u, model2.getConcreteModelObjects<CurveQuadratic>().size());
  }
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpPlantLoopEIRHeating hp(model);

  const auto condenserTypes = HeatPumpPlantLoopEIRHeating::condenserTypeValues();
  ASSERT_FALSE(condenserTypes.empty());
  EXPECT_TRUE(hp.setCondenserType("AirSource"));
  EXPECT_FALSE(hp.setCondenserType("WaterSource"));
  EXPECT_EQ("AirSource", hp.condenserType());

  EXPECT_TRUE(hp.setLoadSideReferenceFlowRate(0.101));
  ASSERT_TRUE(hp.loadSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.loadSideReferenceFlowRate());
  hp.autosizeLoadSideReferenceFlowRate();
  EXPECT_TRUE(hp.isLoadSideReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setSourceSideReferenceFlowRate(0.202));
  ASSERT_TRUE(hp.sourceSideReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.sourceSideReferenceFlowRate());
  hp.autosizeSourceSideReferenceFlowRate();
  EXPECT_TRUE(hp.isSourceSideReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setHeatRecoveryReferenceFlowRate(0.303));
  ASSERT_TRUE(hp.heatRecoveryReferenceFlowRate());
  EXPECT_DOUBLE_EQ(0.303, *hp.heatRecoveryReferenceFlowRate());
  hp.autosizeHeatRecoveryReferenceFlowRate();
  EXPECT_TRUE(hp.isHeatRecoveryReferenceFlowRateAutosized());

  EXPECT_TRUE(hp.setReferenceCapacity(12450.0));
  ASSERT_TRUE(hp.referenceCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.referenceCapacity());
  hp.autosizeReferenceCapacity();
  EXPECT_TRUE(hp.isReferenceCapacityAutosized());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.9));
  EXPECT_DOUBLE_EQ(6.9, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());

  EXPECT_TRUE(hp.setHeatingToCoolingCapacitySizingRatio(1.08));
  EXPECT_DOUBLE_EQ(1.08, hp.heatingToCoolingCapacitySizingRatio());

  EXPECT_TRUE(hp.setHeatPumpSizingMethod("CoolingCapacity"));
  EXPECT_EQ("CoolingCapacity", hp.heatPumpSizingMethod());

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

  EXPECT_TRUE(hp.setMaximumOutdoorDryBulbTemperatureForDefrostOperation(5.0));
  EXPECT_DOUBLE_EQ(5.0, hp.maximumOutdoorDryBulbTemperatureForDefrostOperation());

  EXPECT_TRUE(hp.setHeatPumpDefrostControl("None"));
  EXPECT_EQ("None", hp.heatPumpDefrostControl());

  EXPECT_TRUE(hp.setHeatPumpDefrostTimePeriodFraction(0.08));
  EXPECT_DOUBLE_EQ(0.08, hp.heatPumpDefrostTimePeriodFraction());

  EXPECT_TRUE(hp.setMinimumHeatRecoveryOutletTemperature(6.0));
  EXPECT_DOUBLE_EQ(6.0, hp.minimumHeatRecoveryOutletTemperature());
}

TEST_F(EPModelFixture, HeatPumpPlantLoopEIRHeating_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop heatRecoveryLoop(model);
  HeatPumpPlantLoopEIRHeating hp(model);

  EXPECT_TRUE(loadLoop.addSupplyBranchForComponent(hp));
  ASSERT_TRUE(hp.loadSideWaterLoop());
  EXPECT_EQ(loadLoop.handle(), hp.loadSideWaterLoop()->handle());
  ASSERT_TRUE(hp.loadSideWaterInletNode());
  EXPECT_EQ(hp.supplyInletModelObject()->cast<Node>(), hp.loadSideWaterInletNode().get());
  ASSERT_TRUE(hp.loadSideWaterOutletNode());
  EXPECT_EQ(hp.supplyOutletModelObject()->cast<Node>(), hp.loadSideWaterOutletNode().get());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(hp));
  ASSERT_TRUE(hp.sourceSideWaterLoop());
  EXPECT_EQ(sourceLoop.handle(), hp.sourceSideWaterLoop()->handle());
  EXPECT_EQ("WaterSource", hp.condenserType());
  EXPECT_FALSE(hp.setCondenserType("AirSource"));
  ASSERT_TRUE(hp.sourceSideWaterInletNode());
  EXPECT_EQ(hp.demandInletModelObject()->cast<Node>(), hp.sourceSideWaterInletNode().get());
  ASSERT_TRUE(hp.sourceSideWaterOutletNode());
  EXPECT_EQ(hp.demandOutletModelObject()->cast<Node>(), hp.sourceSideWaterOutletNode().get());

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
  EXPECT_EQ(heatRecoveryLoop.handle(), hp.heatRecoveryLoop()->handle());
  ASSERT_TRUE(hp.heatRecoveryInletNode());
  EXPECT_EQ(hp.tertiaryInletModelObject()->cast<Node>(), hp.heatRecoveryInletNode().get());
  ASSERT_TRUE(hp.heatRecoveryOutletNode());
  EXPECT_EQ(hp.tertiaryOutletModelObject()->cast<Node>(), hp.heatRecoveryOutletNode().get());

  auto loadSupplyOutletNode = loadLoop.supplyOutletNode();
  EXPECT_FALSE(hp.addToTertiaryNode(loadSupplyOutletNode));

  EXPECT_TRUE(hp.removeFromSecondaryPlantLoop());
  EXPECT_EQ("AirSource", hp.condenserType());
  EXPECT_FALSE(hp.sourceSideWaterLoop());
  EXPECT_FALSE(hp.sourceSideWaterInletNode());
  EXPECT_FALSE(hp.sourceSideWaterOutletNode());
  EXPECT_FALSE(hp.demandInletModelObject());
  EXPECT_FALSE(hp.demandOutletModelObject());
  EXPECT_FALSE(hp.setCondenserType("WaterSource"));
}
