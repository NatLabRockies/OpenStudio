/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../Curve/CurveQuadLinear_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitCooling_Impl.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"

#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Cooling_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFit_CompanionSharedSourceLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-companion-source-loop-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoadLoop(model);
  PlantLoop coolingLoadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatingHeatPump(model);
  HeatPumpWaterToWaterEquationFitCooling coolingHeatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Removed Equation Fit Companion Source Loop"));
  ASSERT_TRUE(heatingLoadLoop.setName("Equation Fit Heating Load Loop"));
  ASSERT_TRUE(coolingLoadLoop.setName("Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(heatingHeatPump.setName("Companion Equation Fit Heating Heat Pump"));
  ASSERT_TRUE(coolingHeatPump.setName("Companion Equation Fit Cooling Heat Pump"));
  ASSERT_TRUE(heatingHeatPump.setCompanionCoolingHeatPump(coolingHeatPump));
  ASSERT_TRUE(coolingHeatPump.setCompanionHeatingHeatPump(heatingHeatPump));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(heatingLoadLoop.addDemandBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(coolingLoadLoop.addSupplyBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Companion Source Loop");
  auto loadedHeatingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Heating Load Loop");
  auto loadedCoolingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Cooling Load Loop");
  auto loadedHeatingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Companion Equation Fit Heating Heat Pump");
  auto loadedCoolingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Companion Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoadLoop);
  ASSERT_TRUE(loadedCoolingLoadLoop);
  ASSERT_TRUE(loadedHeatingHeatPump);
  ASSERT_TRUE(loadedCoolingHeatPump);
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());
  EXPECT_EQ(*loadedCoolingHeatPump, *loadedHeatingHeatPump->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatingHeatPump, *loadedCoolingHeatPump->companionHeatingHeatPump());
  ASSERT_TRUE(loadedHeatingHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatingHeatPump->secondaryPlantLoop());
  ASSERT_TRUE(loadedCoolingHeatPump->plantLoop());
  ASSERT_TRUE(loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatingHeatPump->plantLoop());
  EXPECT_EQ(*loadedHeatingLoadLoop, *loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedCoolingLoadLoop, *loadedCoolingHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatingHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatingHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatingHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatingHeatPump->demandOutletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != loadedHeatingHeatPump->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != loadedCoolingHeatPump->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  const auto heatingHeatPumpHandle = loadedHeatingHeatPump->handle();
  const auto coolingHeatPumpHandle = loadedCoolingHeatPump->handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(heatingHeatPumpHandle));
  ASSERT_TRUE(loadedModel->getObject(coolingHeatPumpHandle));
  EXPECT_FALSE(loadedHeatingHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatingHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatingHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedHeatingLoadLoop, *loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_TRUE(loadedHeatingHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatingHeatPump->demandOutletModelObject());
  EXPECT_FALSE(loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedCoolingHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedCoolingHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedCoolingHeatPump->plantLoop());
  EXPECT_EQ(*loadedCoolingLoadLoop, *loadedCoolingHeatPump->plantLoop());
  EXPECT_TRUE(loadedCoolingHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());
  EXPECT_EQ(*loadedCoolingHeatPump, *loadedHeatingHeatPump->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatingHeatPump, *loadedCoolingHeatPump->companionHeatingHeatPump());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Equation Fit Companion Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addSupplyBranchForComponent(*loadedHeatingHeatPump));
  ASSERT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedCoolingHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Equation Fit Companion Source Loop");
  auto reloadedHeatingLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Heating Load Loop");
  auto reloadedCoolingLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Cooling Load Loop");
  auto reloadedHeatingHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Companion Equation Fit Heating Heat Pump");
  auto reloadedCoolingHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Companion Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatingLoadLoop);
  ASSERT_TRUE(reloadedCoolingLoadLoop);
  ASSERT_TRUE(reloadedHeatingHeatPump);
  ASSERT_TRUE(reloadedCoolingHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Companion Source Loop"));
  ASSERT_TRUE(reloadedHeatingHeatPump->plantLoop());
  ASSERT_TRUE(reloadedHeatingHeatPump->secondaryPlantLoop());
  ASSERT_TRUE(reloadedCoolingHeatPump->plantLoop());
  ASSERT_TRUE(reloadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatingHeatPump->plantLoop());
  EXPECT_EQ(*reloadedHeatingLoadLoop, *reloadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedCoolingLoadLoop, *reloadedCoolingHeatPump->plantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedCoolingHeatPump->secondaryPlantLoop());
  ASSERT_TRUE(reloadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(reloadedCoolingHeatPump->companionHeatingHeatPump());
  EXPECT_EQ(*reloadedCoolingHeatPump, *reloadedHeatingHeatPump->companionCoolingHeatPump());
  EXPECT_EQ(*reloadedHeatingHeatPump, *reloadedCoolingHeatPump->companionHeatingHeatPump());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFit_CompanionMixedRetentionRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-companion-mixed-retention-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoadLoop(model);
  PlantLoop coolingLoadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatingHeatPump(model);
  HeatPumpWaterToWaterEquationFitCooling coolingHeatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Mixed Retention Removed Source Loop"));
  ASSERT_TRUE(heatingLoadLoop.setName("Mixed Retention Removed Heating Load Loop"));
  ASSERT_TRUE(coolingLoadLoop.setName("Mixed Retention Cooling Load Loop"));
  ASSERT_TRUE(heatingHeatPump.setName("Mixed Retention Deleted Heating Heat Pump"));
  ASSERT_TRUE(coolingHeatPump.setName("Mixed Retention Surviving Cooling Heat Pump"));
  ASSERT_TRUE(heatingHeatPump.setCompanionCoolingHeatPump(coolingHeatPump));
  ASSERT_TRUE(coolingHeatPump.setCompanionHeatingHeatPump(heatingHeatPump));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(heatingLoadLoop.addDemandBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(coolingLoadLoop.addSupplyBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Removed Source Loop");
  auto loadedHeatingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Removed Heating Load Loop");
  auto loadedCoolingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Cooling Load Loop");
  auto loadedHeatingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Mixed Retention Deleted Heating Heat Pump");
  auto loadedCoolingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Mixed Retention Surviving Cooling Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoadLoop);
  ASSERT_TRUE(loadedCoolingLoadLoop);
  ASSERT_TRUE(loadedHeatingHeatPump);
  ASSERT_TRUE(loadedCoolingHeatPump);
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());
  EXPECT_EQ(*loadedCoolingHeatPump, *loadedHeatingHeatPump->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatingHeatPump, *loadedCoolingHeatPump->companionHeatingHeatPump());

  std::vector<openstudio::Handle> heatingLoadTopologyHandles;
  for (const auto& component : loadedHeatingLoadLoop->supplyComponents()) {
    heatingLoadTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedHeatingLoadLoop->demandComponents()) {
    if (component.handle() != loadedHeatingHeatPump->handle()) {
      heatingLoadTopologyHandles.push_back(component.handle());
    }
  }
  const auto heatingLoadLoopHandle = loadedHeatingLoadLoop->handle();
  const auto heatingLoadSizingPlantHandle = loadedHeatingLoadLoop->sizingPlant().handle();
  const auto heatingHeatPumpHandle = loadedHeatingHeatPump->handle();
  const auto coolingHeatPumpHandle = loadedCoolingHeatPump->handle();
  EXPECT_FALSE(loadedHeatingLoadLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(heatingLoadLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(heatingLoadSizingPlantHandle));
  for (const auto& handle : heatingLoadTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(heatingHeatPumpHandle));
  EXPECT_FALSE(loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatingHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatingHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatingHeatPump->plantLoop());
  EXPECT_TRUE(loadedHeatingHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatingHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != heatingHeatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != coolingHeatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedModel->getObject(heatingHeatPumpHandle));
  ASSERT_TRUE(loadedModel->getObject(coolingHeatPumpHandle));
  EXPECT_FALSE(loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedCoolingHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedCoolingHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedCoolingHeatPump->plantLoop());
  EXPECT_EQ(*loadedCoolingLoadLoop, *loadedCoolingHeatPump->plantLoop());
  EXPECT_TRUE(loadedCoolingHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->supplyOutletModelObject());
  EXPECT_FALSE(loadedCoolingHeatPump->companionHeatingHeatPump());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Mixed Retention Replacement Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedCoolingHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Replacement Source Loop");
  auto reloadedCoolingLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Cooling Load Loop");
  auto reloadedCoolingHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Mixed Retention Surviving Cooling Heat Pump");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedCoolingLoadLoop);
  ASSERT_TRUE(reloadedCoolingHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Removed Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Mixed Retention Removed Heating Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Mixed Retention Deleted Heating Heat Pump"));
  ASSERT_TRUE(reloadedCoolingHeatPump->plantLoop());
  ASSERT_TRUE(reloadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedCoolingLoadLoop, *reloadedCoolingHeatPump->plantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(reloadedCoolingHeatPump->companionHeatingHeatPump());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFit_CompanionOppositeMixedRetentionRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-companion-opposite-mixed-retention-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoadLoop(model);
  PlantLoop coolingLoadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatingHeatPump(model);
  HeatPumpWaterToWaterEquationFitCooling coolingHeatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Opposite Mixed Retention Removed Source Loop"));
  ASSERT_TRUE(heatingLoadLoop.setName("Opposite Mixed Retention Heating Load Loop"));
  ASSERT_TRUE(coolingLoadLoop.setName("Opposite Mixed Retention Removed Cooling Load Loop"));
  ASSERT_TRUE(heatingHeatPump.setName("Opposite Mixed Retention Surviving Heating Heat Pump"));
  ASSERT_TRUE(coolingHeatPump.setName("Opposite Mixed Retention Deleted Cooling Heat Pump"));
  ASSERT_TRUE(heatingHeatPump.setCompanionCoolingHeatPump(coolingHeatPump));
  ASSERT_TRUE(coolingHeatPump.setCompanionHeatingHeatPump(heatingHeatPump));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(heatingLoadLoop.addDemandBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(coolingLoadLoop.addSupplyBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Removed Source Loop");
  auto loadedHeatingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Heating Load Loop");
  auto loadedCoolingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Removed Cooling Load Loop");
  auto loadedHeatingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Opposite Mixed Retention Surviving Heating Heat Pump");
  auto loadedCoolingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Opposite Mixed Retention Deleted Cooling Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoadLoop);
  ASSERT_TRUE(loadedCoolingLoadLoop);
  ASSERT_TRUE(loadedHeatingHeatPump);
  ASSERT_TRUE(loadedCoolingHeatPump);
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());
  EXPECT_EQ(*loadedCoolingHeatPump, *loadedHeatingHeatPump->companionCoolingHeatPump());
  EXPECT_EQ(*loadedHeatingHeatPump, *loadedCoolingHeatPump->companionHeatingHeatPump());

  std::vector<openstudio::Handle> coolingLoadTopologyHandles;
  for (const auto& component : loadedCoolingLoadLoop->supplyComponents()) {
    if (component.handle() != loadedCoolingHeatPump->handle()) {
      coolingLoadTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedCoolingLoadLoop->demandComponents()) {
    coolingLoadTopologyHandles.push_back(component.handle());
  }
  const auto coolingLoadLoopHandle = loadedCoolingLoadLoop->handle();
  const auto coolingLoadSizingPlantHandle = loadedCoolingLoadLoop->sizingPlant().handle();
  const auto heatingHeatPumpHandle = loadedHeatingHeatPump->handle();
  const auto coolingHeatPumpHandle = loadedCoolingHeatPump->handle();
  EXPECT_FALSE(loadedCoolingLoadLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(coolingLoadLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingLoadSizingPlantHandle));
  for (const auto& handle : coolingLoadTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  ASSERT_TRUE(loadedModel->getObject(coolingHeatPumpHandle));
  EXPECT_FALSE(loadedCoolingHeatPump->plantLoop());
  EXPECT_FALSE(loadedCoolingHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedCoolingHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_TRUE(loadedCoolingHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedCoolingHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != heatingHeatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != coolingHeatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedModel->getObject(coolingHeatPumpHandle));
  ASSERT_TRUE(loadedModel->getObject(heatingHeatPumpHandle));
  EXPECT_FALSE(loadedHeatingHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatingHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatingHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedHeatingLoadLoop, *loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_TRUE(loadedHeatingHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatingHeatPump->demandOutletModelObject());
  EXPECT_FALSE(loadedHeatingHeatPump->companionCoolingHeatPump());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Opposite Mixed Retention Replacement Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addSupplyBranchForComponent(*loadedHeatingHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Replacement Source Loop");
  auto reloadedHeatingLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Heating Load Loop");
  auto reloadedHeatingHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Opposite Mixed Retention Surviving Heating Heat Pump");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatingLoadLoop);
  ASSERT_TRUE(reloadedHeatingHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Removed Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Opposite Mixed Retention Removed Cooling Load Loop"));
  EXPECT_FALSE(
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Opposite Mixed Retention Deleted Cooling Heat Pump"));
  ASSERT_TRUE(reloadedHeatingHeatPump->plantLoop());
  ASSERT_TRUE(reloadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatingHeatPump->plantLoop());
  EXPECT_EQ(*reloadedHeatingLoadLoop, *reloadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(reloadedHeatingHeatPump->companionCoolingHeatPump());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFit_CompanionPairLastOwnerRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-companion-pair-last-owner-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop heatingLoadLoop(model);
  PlantLoop coolingLoadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatingHeatPump(model);
  HeatPumpWaterToWaterEquationFitCooling coolingHeatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Companion Pair Last Source Loop"));
  ASSERT_TRUE(heatingLoadLoop.setName("Companion Pair Removed Heating Load Loop"));
  ASSERT_TRUE(coolingLoadLoop.setName("Companion Pair Removed Cooling Load Loop"));
  ASSERT_TRUE(heatingHeatPump.setName("Companion Pair Deleted Heating Heat Pump"));
  ASSERT_TRUE(coolingHeatPump.setName("Companion Pair Deleted Cooling Heat Pump"));
  ASSERT_TRUE(heatingHeatPump.setCompanionCoolingHeatPump(coolingHeatPump));
  ASSERT_TRUE(coolingHeatPump.setCompanionHeatingHeatPump(heatingHeatPump));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(heatingLoadLoop.addDemandBranchForComponent(heatingHeatPump));
  ASSERT_TRUE(coolingLoadLoop.addSupplyBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coolingHeatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Companion Pair Last Source Loop");
  auto loadedHeatingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Companion Pair Removed Heating Load Loop");
  auto loadedCoolingLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Companion Pair Removed Cooling Load Loop");
  auto loadedHeatingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Companion Pair Deleted Heating Heat Pump");
  auto loadedCoolingHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Companion Pair Deleted Cooling Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingLoadLoop);
  ASSERT_TRUE(loadedCoolingLoadLoop);
  ASSERT_TRUE(loadedHeatingHeatPump);
  ASSERT_TRUE(loadedCoolingHeatPump);

  const auto removeOwnerLoop = [&](PlantLoop& loop, const openstudio::Handle& retainedComponentHandle) {
    std::vector<openstudio::Handle> topologyHandles;
    for (const auto& component : loop.supplyComponents()) {
      if (component.handle() != retainedComponentHandle) {
        topologyHandles.push_back(component.handle());
      }
    }
    for (const auto& component : loop.demandComponents()) {
      if (component.handle() != retainedComponentHandle) {
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
  const auto heatingHeatPumpHandle = loadedHeatingHeatPump->handle();
  const auto coolingHeatPumpHandle = loadedCoolingHeatPump->handle();
  removeOwnerLoop(*loadedHeatingLoadLoop, heatingHeatPumpHandle);
  removeOwnerLoop(*loadedCoolingLoadLoop, coolingHeatPumpHandle);
  ASSERT_TRUE(loadedModel->getObject(heatingHeatPumpHandle));
  ASSERT_TRUE(loadedModel->getObject(coolingHeatPumpHandle));
  EXPECT_FALSE(loadedHeatingHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatingHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatingHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatingHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatingHeatPump->plantLoop());
  EXPECT_FALSE(loadedCoolingHeatPump->plantLoop());
  EXPECT_FALSE(loadedCoolingHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedCoolingHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedCoolingHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedCoolingHeatPump->secondaryPlantLoop());
  ASSERT_TRUE(loadedHeatingHeatPump->companionCoolingHeatPump());
  ASSERT_TRUE(loadedCoolingHeatPump->companionHeatingHeatPump());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != heatingHeatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != coolingHeatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedModel->getObject(heatingHeatPumpHandle));
  EXPECT_FALSE(loadedModel->getObject(coolingHeatPumpHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Companion Pair Last Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Companion Pair Removed Heating Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Companion Pair Removed Cooling Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Companion Pair Deleted Heating Heat Pump"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Companion Pair Deleted Cooling Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_OppositeSequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-cooling-opposite-last-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  HeatPumpWaterToWaterEquationFitCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Removed Last Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Removed First Equation Fit Cooling Source Loop"));
  ASSERT_TRUE(heatPump.setName("Opposite Deleted Equation Fit Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Cooling Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Cooling Source Loop");
  auto loadedHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Opposite Deleted Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

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
  ASSERT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());

  std::vector<openstudio::Handle> loadTopologyHandles;
  for (const auto& component : loadedLoadLoop->supplyComponents()) {
    if (component.handle() != heatPumpHandle) {
      loadTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedLoadLoop->demandComponents()) {
    loadTopologyHandles.push_back(component.handle());
  }
  const auto loadLoopHandle = loadedLoadLoop->handle();
  const auto loadSizingPlantHandle = loadedLoadLoop->sizingPlant().handle();
  EXPECT_FALSE(loadedLoadLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(loadSizingPlantHandle));
  for (const auto& handle : loadTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedModel->getObject(heatPumpHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Cooling Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Cooling Source Loop"));
  EXPECT_FALSE(
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Opposite Deleted Equation Fit Cooling Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-cooling-last-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  HeatPumpWaterToWaterEquationFitCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Removed First Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Removed Last Equation Fit Cooling Source Loop"));
  ASSERT_TRUE(heatPump.setName("Deleted Equation Fit Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Cooling Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Cooling Source Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Deleted Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

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
  EXPECT_FALSE(loadedHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    sourceTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    if (component.handle() != heatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto sourceLoopHandle = loadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = loadedSourceLoop->sizingPlant().handle();
  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_FALSE(loadedModel->getObject(heatPumpHandle));

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Cooling Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Cooling Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Deleted Equation Fit Cooling Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_SourceDemandOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-cooling-source-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  HeatPumpWaterToWaterEquationFitCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Removed Equation Fit Cooling Source Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Equation Fit Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Cooling Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Cooling Source Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Surviving Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

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
  ASSERT_TRUE(loadedModel->getObject(heatPumpHandle));
  EXPECT_FALSE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Equation Fit Cooling Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Cooling Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Equation Fit Cooling Source Loop");
  auto reloadedHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Surviving Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Cooling Source Loop"));
  ASSERT_TRUE(reloadedHeatPump->plantLoop());
  ASSERT_TRUE(reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->plantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, reloadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandOutletModelObject());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_LoadSupplyOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-cooling-load-owner-removal.idf");

  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  HeatPumpWaterToWaterEquationFitCooling heatPump(model);
  ASSERT_TRUE(loadLoop.setName("Removed Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(sourceLoop.setName("Equation Fit Cooling Source Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Equation Fit Cooling Heat Pump"));
  ASSERT_TRUE(loadLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Cooling Load Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Cooling Source Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Surviving Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

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
  EXPECT_FALSE(loadedHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  PlantLoop replacementLoadLoop(*loadedModel);
  ASSERT_TRUE(replacementLoadLoop.setName("Replacement Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(replacementLoadLoop.addSupplyBranchForComponent(*loadedHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Equation Fit Cooling Load Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Cooling Source Loop");
  auto reloadedHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitCooling>("Surviving Equation Fit Cooling Heat Pump");
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Cooling Load Loop"));
  ASSERT_TRUE(reloadedHeatPump->plantLoop());
  ASSERT_TRUE(reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->plantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, reloadedLoadLoop->supplyComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSourceLoop->demandComponents(HeatPumpWaterToWaterEquationFitCooling::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandOutletModelObject());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterEquationFitCooling::iddObjectType(), hp.iddObject().type());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideInletNodeName, hp.supplyInletPort());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::LoadSideOutletNodeName, hp.supplyOutletPort());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideInletNodeName, hp.demandInletPort());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_CoolingFields::SourceSideOutletNodeName, hp.demandOutletPort());

  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_TRUE(hp.isRatedCoolingCapacityAutosized());
  EXPECT_TRUE(hp.isRatedCoolingPowerConsumptionAutosized());

  EXPECT_FALSE(hp.referenceLoadSideFlowRate());
  EXPECT_FALSE(hp.referenceSourceSideFlowRate());
  EXPECT_FALSE(hp.ratedCoolingCapacity());
  EXPECT_FALSE(hp.ratedCoolingPowerConsumption());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.coolingCapacityCurve().iddObject().type());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.coolingCompressorPowerCurve().iddObject().type());
  EXPECT_FALSE(hp.companionHeatingHeatPump());

  EXPECT_DOUBLE_EQ(8.0, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_CurveConstructorAndSetters) {
  Model model;
  CurveQuadLinear capacityCurve(model);
  CurveQuadLinear powerCurve(model);

  HeatPumpWaterToWaterEquationFitCooling hp(model, capacityCurve, powerCurve);
  EXPECT_EQ(capacityCurve, hp.coolingCapacityCurve());
  EXPECT_EQ(powerCurve, hp.coolingCompressorPowerCurve());

  CurveQuadLinear replacementCapacity(model);
  CurveQuadLinear replacementPower(model);

  EXPECT_TRUE(hp.setCoolingCapacityCurve(replacementCapacity));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCurve(replacementPower));

  EXPECT_EQ(replacementCapacity, hp.coolingCapacityCurve());
  EXPECT_EQ(replacementPower, hp.coolingCompressorPowerCurve());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_CompanionHeatingHeatPumpRoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling cooling(model);
  HeatPumpWaterToWaterEquationFitHeating heating(model);

  EXPECT_FALSE(cooling.companionHeatingHeatPump());
  EXPECT_TRUE(cooling.setCompanionHeatingHeatPump(heating));
  ASSERT_TRUE(cooling.companionHeatingHeatPump());
  EXPECT_EQ(heating, cooling.companionHeatingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_DeprecatedCoefficientAliasesDelegateThroughStoredCurves) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_TRUE(hp.setCoolingCapacityCoefficient1(1.1));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient2(1.2));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient3(1.3));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient4(1.4));
  EXPECT_TRUE(hp.setCoolingCapacityCoefficient5(1.5));
  EXPECT_DOUBLE_EQ(1.1, hp.coolingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(1.2, hp.coolingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(1.3, hp.coolingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(1.4, hp.coolingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(1.5, hp.coolingCapacityCoefficient5());

  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient1(2.1));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient2(2.2));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient3(2.3));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient4(2.4));
  EXPECT_TRUE(hp.setCoolingCompressorPowerCoefficient5(2.5));
  EXPECT_DOUBLE_EQ(2.1, hp.coolingCompressorPowerCoefficient1());
  EXPECT_DOUBLE_EQ(2.2, hp.coolingCompressorPowerCoefficient2());
  EXPECT_DOUBLE_EQ(2.3, hp.coolingCompressorPowerCoefficient3());
  EXPECT_DOUBLE_EQ(2.4, hp.coolingCompressorPowerCoefficient4());
  EXPECT_DOUBLE_EQ(2.5, hp.coolingCompressorPowerCoefficient5());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_TRUE(loadLoop.addSupplyBranchForComponent(hp));
  ASSERT_TRUE(hp.plantLoop());
  EXPECT_EQ(loadLoop.handle(), hp.plantLoop()->handle());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(hp));
  ASSERT_TRUE(hp.secondaryPlantLoop());
  EXPECT_EQ(sourceLoop.handle(), hp.secondaryPlantLoop()->handle());

  ASSERT_TRUE(hp.supplyInletModelObject());
  ASSERT_TRUE(hp.supplyOutletModelObject());
  ASSERT_TRUE(hp.demandInletModelObject());
  ASSERT_TRUE(hp.demandOutletModelObject());

  const auto loadInletNode = hp.supplyInletModelObject()->cast<Node>();
  const auto loadOutletNode = hp.supplyOutletModelObject()->cast<Node>();
  const auto sourceInletNode = hp.demandInletModelObject()->cast<Node>();
  const auto sourceOutletNode = hp.demandOutletModelObject()->cast<Node>();

  ASSERT_TRUE(loadInletNode.plantLoop());
  EXPECT_EQ(loadLoop.handle(), loadInletNode.plantLoop()->handle());
  ASSERT_TRUE(loadOutletNode.plantLoop());
  EXPECT_EQ(loadLoop.handle(), loadOutletNode.plantLoop()->handle());
  ASSERT_TRUE(sourceInletNode.plantLoop());
  EXPECT_EQ(sourceLoop.handle(), sourceInletNode.plantLoop()->handle());
  ASSERT_TRUE(sourceOutletNode.plantLoop());
  EXPECT_EQ(sourceLoop.handle(), sourceOutletNode.plantLoop()->handle());

  EXPECT_NE(loadInletNode, sourceInletNode);
  EXPECT_NE(loadOutletNode, sourceOutletNode);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitCooling_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitCooling hp(model);

  EXPECT_TRUE(hp.setReferenceLoadSideFlowRate(0.101));
  ASSERT_TRUE(hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.101, *hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.101, hp.ratedLoadSideFlowRate());

  EXPECT_TRUE(hp.setRatedLoadSideFlowRate(0.111));
  ASSERT_TRUE(hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.111, *hp.referenceLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(0.111, hp.ratedLoadSideFlowRate());

  hp.autosizeReferenceLoadSideFlowRate();
  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());

  EXPECT_TRUE(hp.setReferenceSourceSideFlowRate(0.202));
  ASSERT_TRUE(hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.202, *hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.202, hp.ratedSourceSideFlowRate());

  EXPECT_TRUE(hp.setRatedSourceSideFlowRate(0.222));
  ASSERT_TRUE(hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.222, *hp.referenceSourceSideFlowRate());
  EXPECT_DOUBLE_EQ(0.222, hp.ratedSourceSideFlowRate());

  hp.autosizeReferenceSourceSideFlowRate();
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());

  EXPECT_TRUE(hp.setRatedCoolingCapacity(12450.0));
  ASSERT_TRUE(hp.ratedCoolingCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.ratedCoolingCapacity());
  hp.autosizeRatedCoolingCapacity();
  EXPECT_TRUE(hp.isRatedCoolingCapacityAutosized());
  EXPECT_FALSE(hp.ratedCoolingCapacity());

  EXPECT_TRUE(hp.setRatedCoolingPowerConsumption(3450.0));
  ASSERT_TRUE(hp.ratedCoolingPowerConsumption());
  EXPECT_DOUBLE_EQ(3450.0, *hp.ratedCoolingPowerConsumption());
  hp.autosizeRatedCoolingPowerConsumption();
  EXPECT_TRUE(hp.isRatedCoolingPowerConsumptionAutosized());
  EXPECT_FALSE(hp.ratedCoolingPowerConsumption());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(7.25));
  EXPECT_DOUBLE_EQ(7.25, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());
}
