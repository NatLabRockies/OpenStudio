/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBicubic.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/ChillerElectricReformulatedEIR.hpp"
#include "../WaterToWaterComponent/ChillerElectricReformulatedEIR_Impl.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_HeatRecoveryOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-reformulated-chiller-recovery-owner-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Reformulated Chiller Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Reformulated Chiller Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Removed Reformulated Chiller Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Surviving Reformulated Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Reformulated Chiller Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Reformulated Chiller Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Reformulated Chiller Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Surviving Reformulated Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedChilledWaterLoop->supplyComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedCondenserWaterLoop->demandComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());

  std::vector<openstudio::Handle> heatRecoveryTopologyHandles;
  for (const auto& component : loadedHeatRecoveryLoop->supplyComponents()) {
    heatRecoveryTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedHeatRecoveryLoop->demandComponents()) {
    if (component.handle() != loadedChiller->handle()) {
      heatRecoveryTopologyHandles.push_back(component.handle());
    }
  }
  const auto heatRecoveryLoopHandle = loadedHeatRecoveryLoop->handle();
  const auto heatRecoverySizingPlantHandle = loadedHeatRecoveryLoop->sizingPlant().handle();
  const auto chillerHandle = loadedChiller->handle();
  EXPECT_FALSE(loadedHeatRecoveryLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(heatRecoveryLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(heatRecoverySizingPlantHandle));
  for (const auto& handle : heatRecoveryTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->heatRecoveryLoop());
  EXPECT_FALSE(loadedChiller->heatRecoveryInletNode());
  EXPECT_FALSE(loadedChiller->heatRecoveryOutletNode());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(1u, loadedChilledWaterLoop->supplyComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedCondenserWaterLoop->demandComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());

  PlantLoop replacementHeatRecoveryLoop(*loadedModel);
  ASSERT_TRUE(replacementHeatRecoveryLoop.setName("Replacement Reformulated Chiller Heat Recovery Loop"));
  ASSERT_TRUE(replacementHeatRecoveryLoop.addDemandBranchForComponent(*loadedChiller));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedChilledWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Reformulated Chiller Chilled Water Loop");
  auto reloadedCondenserWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Reformulated Chiller Condenser Water Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Reformulated Chiller Heat Recovery Loop");
  auto reloadedChiller = reloadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Surviving Reformulated Chiller");
  ASSERT_TRUE(reloadedChilledWaterLoop);
  ASSERT_TRUE(reloadedCondenserWaterLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedChiller);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Reformulated Chiller Heat Recovery Loop"));
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  ASSERT_TRUE(reloadedChiller->condenserWaterLoop());
  ASSERT_TRUE(reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedCondenserWaterLoop, *reloadedChiller->condenserWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedChiller->heatRecoveryLoop());
  EXPECT_TRUE(reloadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(reloadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(reloadedChiller->condenserInletNode());
  EXPECT_TRUE(reloadedChiller->condenserOutletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryOutletNode());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_CondenserOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-reformulated-chiller-condenser-owner-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Condenser Removal Reformulated Chiller Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Removed Reformulated Chiller Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Condenser Removal Reformulated Chiller Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Condenser Removal Surviving Reformulated Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Condenser Removal Reformulated Chiller Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Reformulated Chiller Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Condenser Removal Reformulated Chiller Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Condenser Removal Surviving Reformulated Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());

  std::vector<openstudio::Handle> condenserTopologyHandles;
  for (const auto& component : loadedCondenserWaterLoop->supplyComponents()) {
    condenserTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedCondenserWaterLoop->demandComponents()) {
    if (component.handle() != loadedChiller->handle()) {
      condenserTopologyHandles.push_back(component.handle());
    }
  }
  const auto condenserWaterLoopHandle = loadedCondenserWaterLoop->handle();
  const auto condenserSizingPlantHandle = loadedCondenserWaterLoop->sizingPlant().handle();
  const auto chillerHandle = loadedChiller->handle();
  EXPECT_FALSE(loadedCondenserWaterLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(condenserWaterLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(condenserSizingPlantHandle));
  for (const auto& handle : condenserTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->condenserWaterLoop());
  EXPECT_FALSE(loadedChiller->condenserInletNode());
  EXPECT_FALSE(loadedChiller->condenserOutletNode());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedChilledWaterLoop->supplyComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());

  PlantLoop replacementCondenserWaterLoop(*loadedModel);
  ASSERT_TRUE(replacementCondenserWaterLoop.setName("Replacement Reformulated Chiller Condenser Water Loop"));
  ASSERT_TRUE(replacementCondenserWaterLoop.addDemandBranchForComponent(*loadedChiller));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedChilledWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Condenser Removal Reformulated Chiller Chilled Water Loop");
  auto reloadedCondenserWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Reformulated Chiller Condenser Water Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Condenser Removal Reformulated Chiller Heat Recovery Loop");
  auto reloadedChiller =
    reloadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Condenser Removal Surviving Reformulated Chiller");
  ASSERT_TRUE(reloadedChilledWaterLoop);
  ASSERT_TRUE(reloadedCondenserWaterLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedChiller);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Reformulated Chiller Condenser Water Loop"));
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  ASSERT_TRUE(reloadedChiller->condenserWaterLoop());
  ASSERT_TRUE(reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedCondenserWaterLoop, *reloadedChiller->condenserWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedChiller->heatRecoveryLoop());
  EXPECT_TRUE(reloadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(reloadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(reloadedChiller->condenserInletNode());
  EXPECT_TRUE(reloadedChiller->condenserOutletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryOutletNode());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_ChilledWaterOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-reformulated-chiller-chilled-water-owner-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Removed Reformulated Chiller Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Chilled Removal Reformulated Chiller Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Chilled Removal Reformulated Chiller Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Chilled Removal Surviving Reformulated Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Reformulated Chiller Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Chilled Removal Reformulated Chiller Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Chilled Removal Reformulated Chiller Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Chilled Removal Surviving Reformulated Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());

  std::vector<openstudio::Handle> chilledWaterTopologyHandles;
  for (const auto& component : loadedChilledWaterLoop->supplyComponents()) {
    if (component.handle() != loadedChiller->handle()) {
      chilledWaterTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedChilledWaterLoop->demandComponents()) {
    chilledWaterTopologyHandles.push_back(component.handle());
  }
  const auto chilledWaterLoopHandle = loadedChilledWaterLoop->handle();
  const auto chilledWaterSizingPlantHandle = loadedChilledWaterLoop->sizingPlant().handle();
  const auto chillerHandle = loadedChiller->handle();
  EXPECT_FALSE(loadedChilledWaterLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(chilledWaterLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(chilledWaterSizingPlantHandle));
  for (const auto& handle : chilledWaterTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->chilledWaterLoop());
  EXPECT_FALSE(loadedChiller->chilledWaterInletNode());
  EXPECT_FALSE(loadedChiller->chilledWaterOutletNode());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(1u, loadedCondenserWaterLoop->demandComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_EQ(1u, loadedHeatRecoveryLoop->demandComponents(ChillerElectricReformulatedEIR::iddObjectType()).size());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());

  PlantLoop replacementChilledWaterLoop(*loadedModel);
  ASSERT_TRUE(replacementChilledWaterLoop.setName("Replacement Reformulated Chiller Chilled Water Loop"));
  ASSERT_TRUE(replacementChilledWaterLoop.addSupplyBranchForComponent(*loadedChiller));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedChilledWaterLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Reformulated Chiller Chilled Water Loop");
  auto reloadedCondenserWaterLoop =
    reloadedModel->getConcreteModelObjectByName<PlantLoop>("Chilled Removal Reformulated Chiller Condenser Water Loop");
  auto reloadedHeatRecoveryLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Chilled Removal Reformulated Chiller Heat Recovery Loop");
  auto reloadedChiller =
    reloadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Chilled Removal Surviving Reformulated Chiller");
  ASSERT_TRUE(reloadedChilledWaterLoop);
  ASSERT_TRUE(reloadedCondenserWaterLoop);
  ASSERT_TRUE(reloadedHeatRecoveryLoop);
  ASSERT_TRUE(reloadedChiller);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Reformulated Chiller Chilled Water Loop"));
  ASSERT_TRUE(reloadedChiller->chilledWaterLoop());
  ASSERT_TRUE(reloadedChiller->condenserWaterLoop());
  ASSERT_TRUE(reloadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*reloadedChilledWaterLoop, *reloadedChiller->chilledWaterLoop());
  EXPECT_EQ(*reloadedCondenserWaterLoop, *reloadedChiller->condenserWaterLoop());
  EXPECT_EQ(*reloadedHeatRecoveryLoop, *reloadedChiller->heatRecoveryLoop());
  EXPECT_TRUE(reloadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(reloadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(reloadedChiller->condenserInletNode());
  EXPECT_TRUE(reloadedChiller->condenserOutletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(reloadedChiller->heatRecoveryOutletNode());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-reformulated-chiller-sequential-last-owner-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Sequential Last Reformulated Chiller Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Sequential Second Reformulated Chiller Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Sequential First Reformulated Chiller Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Sequential Deleted Reformulated Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Sequential Last Reformulated Chiller Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Sequential Second Reformulated Chiller Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Sequential First Reformulated Chiller Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Sequential Deleted Reformulated Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());

  const auto chillerHandle = loadedChiller->handle();
  const auto removeOwnerLoop = [&](PlantLoop& loop) {
    std::vector<openstudio::Handle> topologyHandles;
    for (const auto& component : loop.supplyComponents()) {
      if (component.handle() != chillerHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    for (const auto& component : loop.demandComponents()) {
      if (component.handle() != chillerHandle) {
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
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->heatRecoveryLoop());
  EXPECT_FALSE(loadedChiller->heatRecoveryInletNode());
  EXPECT_FALSE(loadedChiller->heatRecoveryOutletNode());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());

  removeOwnerLoop(*loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->condenserWaterLoop());
  EXPECT_FALSE(loadedChiller->condenserInletNode());
  EXPECT_FALSE(loadedChiller->condenserOutletNode());
  EXPECT_FALSE(loadedChiller->heatRecoveryLoop());
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  EXPECT_EQ(*loadedChilledWaterLoop, *loadedChiller->chilledWaterLoop());
  EXPECT_TRUE(loadedChiller->chilledWaterInletNode());
  EXPECT_TRUE(loadedChiller->chilledWaterOutletNode());

  removeOwnerLoop(*loadedChilledWaterLoop);
  EXPECT_FALSE(loadedModel->getObject(chillerHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Sequential First Reformulated Chiller Heat Recovery Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Sequential Second Reformulated Chiller Condenser Water Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Sequential Last Reformulated Chiller Chilled Water Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Sequential Deleted Reformulated Chiller"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_DemandLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-reformulated-chiller-demand-last-owner-removal.idf");

  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);
  ASSERT_TRUE(chilledWaterLoop.setName("First Removed Demand Last Chilled Water Loop"));
  ASSERT_TRUE(condenserWaterLoop.setName("Final Removed Demand Last Condenser Water Loop"));
  ASSERT_TRUE(heatRecoveryLoop.setName("Second Removed Demand Last Heat Recovery Loop"));
  ASSERT_TRUE(chiller.setName("Demand Last Deleted Reformulated Chiller"));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("First Removed Demand Last Chilled Water Loop");
  auto loadedCondenserWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Final Removed Demand Last Condenser Water Loop");
  auto loadedHeatRecoveryLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Second Removed Demand Last Heat Recovery Loop");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Demand Last Deleted Reformulated Chiller");
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserWaterLoop);
  ASSERT_TRUE(loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedChiller->chilledWaterLoop());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());

  const auto chillerHandle = loadedChiller->handle();
  const auto removeOwnerLoop = [&](PlantLoop& loop) {
    std::vector<openstudio::Handle> topologyHandles;
    for (const auto& component : loop.supplyComponents()) {
      if (component.handle() != chillerHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    for (const auto& component : loop.demandComponents()) {
      if (component.handle() != chillerHandle) {
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

  removeOwnerLoop(*loadedChilledWaterLoop);
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->chilledWaterLoop());
  EXPECT_FALSE(loadedChiller->chilledWaterInletNode());
  EXPECT_FALSE(loadedChiller->chilledWaterOutletNode());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  ASSERT_TRUE(loadedChiller->heatRecoveryLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedHeatRecoveryLoop, *loadedChiller->heatRecoveryLoop());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryInletNode());
  EXPECT_TRUE(loadedChiller->heatRecoveryOutletNode());

  removeOwnerLoop(*loadedHeatRecoveryLoop);
  ASSERT_TRUE(loadedModel->getObject(chillerHandle));
  EXPECT_FALSE(loadedChiller->chilledWaterLoop());
  EXPECT_FALSE(loadedChiller->heatRecoveryLoop());
  EXPECT_FALSE(loadedChiller->heatRecoveryInletNode());
  EXPECT_FALSE(loadedChiller->heatRecoveryOutletNode());
  ASSERT_TRUE(loadedChiller->condenserWaterLoop());
  EXPECT_EQ(*loadedCondenserWaterLoop, *loadedChiller->condenserWaterLoop());
  EXPECT_TRUE(loadedChiller->condenserInletNode());
  EXPECT_TRUE(loadedChiller->condenserOutletNode());

  removeOwnerLoop(*loadedCondenserWaterLoop);
  EXPECT_FALSE(loadedModel->getObject(chillerHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("First Removed Demand Last Chilled Water Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Second Removed Demand Last Heat Recovery Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Final Removed Demand Last Condenser Water Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<ChillerElectricReformulatedEIR>("Demand Last Deleted Reformulated Chiller"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_DefaultConstructor) {
  Model model;
  ChillerElectricReformulatedEIR chiller(model);

  EXPECT_EQ(ChillerElectricReformulatedEIR::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());

  EXPECT_EQ(CurveBiquadratic::iddObjectType(), chiller.coolingCapacityFunctionOfTemperature().iddObject().type());
  EXPECT_EQ(CurveBiquadratic::iddObjectType(), chiller.electricInputToCoolingOutputRatioFunctionOfTemperature().iddObject().type());
  EXPECT_EQ(CurveBicubic::iddObjectType(), chiller.electricInputToCoolingOutputRatioFunctionOfPLR().iddObject().type());

  EXPECT_DOUBLE_EQ(3.99, chiller.referenceCOP());
  EXPECT_TRUE(chiller.isReferenceCapacityAutosized());
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(1.0, chiller.condenserHeatRecoveryRelativeCapacityFraction());
  EXPECT_FALSE(chiller.heatRecoveryInletHighTemperatureLimitSchedule());
  EXPECT_FALSE(chiller.heatRecoveryLeavingTemperatureSetpointNode());
  EXPECT_EQ("General", chiller.endUseSubcategory());
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserMinimumFlowFraction());
  EXPECT_DOUBLE_EQ(0.0, chiller.thermosiphonMinimumTemperatureDifference());
  EXPECT_FALSE(chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve());
  EXPECT_FALSE(chiller.temperatureDifferenceAcrossCondenserSchedule());
  EXPECT_FALSE(chiller.thermosiphonCapacityFractionCurve());
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_CurveConstructorAndRelationships) {
  Model model;
  CurveBiquadratic CCFofT(model);
  CurveBiquadratic EIRToCorfOfT(model);
  CurveBicubic EIRToCorfOfPLR(model);
  CurveLinear condenserLoopPLR(model);
  CurveLinear thermosiphonCurve(model);
  ScheduleConstant heatRecoveryLimit(model);
  ScheduleConstant condenserDeltaT(model);
  Node setpointNode(model);

  ChillerElectricReformulatedEIR chiller(model, CCFofT, EIRToCorfOfT, EIRToCorfOfPLR);

  EXPECT_EQ(CCFofT.handle(), chiller.coolingCapacityFunctionOfTemperature().handle());
  EXPECT_EQ(EIRToCorfOfT.handle(), chiller.electricInputToCoolingOutputRatioFunctionOfTemperature().handle());
  EXPECT_EQ(EIRToCorfOfPLR.handle(), chiller.electricInputToCoolingOutputRatioFunctionOfPLR().handle());

  EXPECT_TRUE(chiller.setHeatRecoveryInletHighTemperatureLimitSchedule(heatRecoveryLimit));
  ASSERT_TRUE(chiller.heatRecoveryInletHighTemperatureLimitSchedule());
  EXPECT_EQ(heatRecoveryLimit.handle(), chiller.heatRecoveryInletHighTemperatureLimitSchedule()->handle());
  chiller.resetHeatRecoveryInletHighTemperatureLimitSchedule();
  EXPECT_FALSE(chiller.heatRecoveryInletHighTemperatureLimitSchedule());

  EXPECT_TRUE(chiller.setHeatRecoveryLeavingTemperatureSetpointNode(setpointNode));
  ASSERT_TRUE(chiller.heatRecoveryLeavingTemperatureSetpointNode());
  EXPECT_EQ(setpointNode.handle(), chiller.heatRecoveryLeavingTemperatureSetpointNode()->handle());
  chiller.resetHeatRecoveryLeavingTemperatureSetpointNode();
  EXPECT_FALSE(chiller.heatRecoveryLeavingTemperatureSetpointNode());

  EXPECT_TRUE(chiller.setCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve(condenserLoopPLR));
  ASSERT_TRUE(chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve());
  EXPECT_EQ(condenserLoopPLR.handle(), chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve()->handle());
  chiller.resetCondenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve();
  EXPECT_FALSE(chiller.condenserLoopFlowRateFractionFunctionofLoopPartLoadRatioCurve());

  EXPECT_TRUE(chiller.setTemperatureDifferenceAcrossCondenserSchedule(condenserDeltaT));
  ASSERT_TRUE(chiller.temperatureDifferenceAcrossCondenserSchedule());
  EXPECT_EQ(condenserDeltaT.handle(), chiller.temperatureDifferenceAcrossCondenserSchedule()->handle());
  chiller.resetTemperatureDifferenceAcrossCondenserSchedule();
  EXPECT_FALSE(chiller.temperatureDifferenceAcrossCondenserSchedule());

  EXPECT_TRUE(chiller.setThermosiphonCapacityFractionCurve(thermosiphonCurve));
  ASSERT_TRUE(chiller.thermosiphonCapacityFractionCurve());
  EXPECT_EQ(thermosiphonCurve.handle(), chiller.thermosiphonCapacityFractionCurve()->handle());
  chiller.resetThermosiphonCapacityFractionCurve();
  EXPECT_FALSE(chiller.thermosiphonCapacityFractionCurve());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectricReformulatedEIR chiller(model);

  EXPECT_TRUE(chiller.setReferenceCapacity(700000.0));
  ASSERT_TRUE(chiller.referenceCapacity());
  EXPECT_DOUBLE_EQ(700000.0, *chiller.referenceCapacity());
  EXPECT_FALSE(chiller.isReferenceCapacityAutosized());
  chiller.autosizeReferenceCapacity();
  EXPECT_TRUE(chiller.isReferenceCapacityAutosized());

  EXPECT_TRUE(chiller.setReferenceCOP(4.0));
  EXPECT_DOUBLE_EQ(4.0, chiller.referenceCOP());

  EXPECT_TRUE(chiller.setReferenceLeavingChilledWaterTemperature(6.5));
  EXPECT_DOUBLE_EQ(6.5, chiller.referenceLeavingChilledWaterTemperature());
  chiller.resetReferenceLeavingChilledWaterTemperature();
  EXPECT_TRUE(chiller.isReferenceLeavingChilledWaterTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceLeavingCondenserWaterTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, chiller.referenceLeavingCondenserWaterTemperature());
  chiller.resetReferenceLeavingCondenserWaterTemperature();
  EXPECT_TRUE(chiller.isReferenceLeavingCondenserWaterTemperatureDefaulted());

  EXPECT_TRUE(chiller.setReferenceChilledWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.referenceChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, *chiller.referenceChilledWaterFlowRate());
  chiller.autosizeReferenceChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.setReferenceCondenserWaterFlowRate(0.03));
  ASSERT_TRUE(chiller.referenceCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.03, *chiller.referenceCondenserWaterFlowRate());
  chiller.autosizeReferenceCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.setReferenceCondenserWaterFlowRate(0.04));
  ASSERT_TRUE(chiller.referenceCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.04, *chiller.referenceCondenserWaterFlowRate());
  chiller.resetReferenceCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isReferenceCondenserWaterFlowRateAutosized());

  EXPECT_EQ("LeavingCondenserWaterTemperature", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());
  EXPECT_TRUE(chiller.setElectricInputToCoolingOutputRatioFunctionOfPLRType("Lift"));
  EXPECT_EQ("Lift", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());
  chiller.resetElectricInputToCoolingOutputRatioFunctionOfPLRType();
  EXPECT_EQ("LeavingCondenserWaterTemperature", chiller.electricInputToCoolingOutputRatioFunctionOfPLRType());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.15));
  EXPECT_DOUBLE_EQ(0.15, chiller.minimumPartLoadRatio());
  chiller.resetMinimumPartLoadRatio();
  EXPECT_TRUE(chiller.isMinimumPartLoadRatioDefaulted());

  EXPECT_TRUE(chiller.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, chiller.maximumPartLoadRatio());
  chiller.resetMaximumPartLoadRatio();
  EXPECT_TRUE(chiller.isMaximumPartLoadRatioDefaulted());

  EXPECT_TRUE(chiller.setOptimumPartLoadRatio(0.72));
  EXPECT_DOUBLE_EQ(0.72, chiller.optimumPartLoadRatio());
  chiller.resetOptimumPartLoadRatio();
  EXPECT_TRUE(chiller.isOptimumPartLoadRatioDefaulted());

  EXPECT_TRUE(chiller.setMinimumUnloadingRatio(0.18));
  EXPECT_DOUBLE_EQ(0.18, chiller.minimumUnloadingRatio());
  chiller.resetMinimumUnloadingRatio();
  EXPECT_TRUE(chiller.isMinimumUnloadingRatioDefaulted());

  EXPECT_TRUE(chiller.setFractionofCompressorElectricConsumptionRejectedbyCondenser(0.92));
  EXPECT_DOUBLE_EQ(0.92, chiller.fractionofCompressorElectricConsumptionRejectedbyCondenser());
  chiller.resetFractionofCompressorElectricConsumptionRejectedbyCondenser();
  EXPECT_TRUE(chiller.isFractionofCompressorElectricConsumptionRejectedbyCondenserDefaulted());

  EXPECT_TRUE(chiller.setLeavingChilledWaterLowerTemperatureLimit(3.0));
  EXPECT_DOUBLE_EQ(3.0, chiller.leavingChilledWaterLowerTemperatureLimit());
  chiller.resetLeavingChilledWaterLowerTemperatureLimit();
  EXPECT_TRUE(chiller.isLeavingChilledWaterLowerTemperatureLimitDefaulted());

  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());
  EXPECT_TRUE(chiller.setChillerFlowMode("VariableFlow"));
  EXPECT_EQ("LeavingSetpointModulated", chiller.chillerFlowMode());
  chiller.resetChillerFlowMode();
  EXPECT_TRUE(chiller.isChillerFlowModeDefaulted());
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setDesignHeatRecoveryWaterFlowRate(0.01));
  ASSERT_TRUE(chiller.designHeatRecoveryWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.01, *chiller.designHeatRecoveryWaterFlowRate());
  chiller.autosizeDesignHeatRecoveryWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignHeatRecoveryWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
  chiller.resetSizingFactor();
  EXPECT_TRUE(chiller.isSizingFactorDefaulted());

  EXPECT_TRUE(chiller.setCondenserHeatRecoveryRelativeCapacityFraction(0.25));
  EXPECT_DOUBLE_EQ(0.25, chiller.condenserHeatRecoveryRelativeCapacityFraction());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());

  EXPECT_TRUE(chiller.setCondenserFlowControl("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.condenserFlowControl());

  EXPECT_TRUE(chiller.setCondenserMinimumFlowFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.condenserMinimumFlowFraction());

  EXPECT_TRUE(chiller.setThermosiphonMinimumTemperatureDifference(0.5));
  EXPECT_DOUBLE_EQ(0.5, chiller.thermosiphonMinimumTemperatureDifference());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop heatRecoveryLoop(model);
  ChillerElectricReformulatedEIR chiller(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());

  EXPECT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());

  ASSERT_TRUE(chiller.chilledWaterInletNode());
  ASSERT_TRUE(chiller.chilledWaterOutletNode());
  ASSERT_TRUE(chiller.condenserInletNode());
  ASSERT_TRUE(chiller.condenserOutletNode());
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());

  Node condenserSupplyOutletNode = condenserLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(condenserSupplyOutletNode));

  Node heatRecoveryInletNode = *chiller.heatRecoveryInletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(heatRecoveryInletNode));

  EXPECT_TRUE(chiller.removeFromSecondaryPlantLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.condenserInletNode());
  EXPECT_FALSE(chiller.condenserOutletNode());
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.heatRecoveryInletNode());
  ASSERT_TRUE(chiller.heatRecoveryOutletNode());
}

TEST_F(EPModelFixture, ChillerElectricReformulatedEIR_AddToNodeDemandRoutingParity) {
  Model model;
  ChillerElectricReformulatedEIR chiller(model);

  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop replacementCondenserLoop(model);
  PlantLoop heatRecoveryLoop(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  Node initialHeatRecoveryDemandNode = heatRecoveryLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(initialHeatRecoveryDemandNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  EXPECT_TRUE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());

  Node replacementDemandNode = replacementCondenserLoop.demandOutletNode();
  EXPECT_TRUE(chiller.addToNode(replacementDemandNode));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(replacementCondenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  Node heatRecoverySupplyNode = heatRecoveryLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(heatRecoverySupplyNode));
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  Node heatRecoveryDemandNode = heatRecoveryLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(heatRecoveryDemandNode));
  ASSERT_TRUE(chiller.heatRecoveryLoop());
  EXPECT_EQ(heatRecoveryLoop.handle(), chiller.heatRecoveryLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(replacementCondenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
}
