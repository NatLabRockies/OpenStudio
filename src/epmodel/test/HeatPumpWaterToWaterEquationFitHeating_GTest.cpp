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
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating.hpp"
#include "../WaterToWaterComponent/HeatPumpWaterToWaterEquationFitHeating_Impl.hpp"

#include <utilities/idd/HeatPump_WaterToWater_EquationFit_Heating_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_OppositeSequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-heating-opposite-last-owner-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop loadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Removed Last Equation Fit Heating Source Loop"));
  ASSERT_TRUE(loadLoop.setName("Removed First Equation Fit Heating Load Loop"));
  ASSERT_TRUE(heatPump.setName("Deleted Opposite Equation Fit Heating Heat Pump"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(loadLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Heating Source Loop");
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Heating Load Loop");
  auto loadedHeatPump =
    loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Deleted Opposite Equation Fit Heating Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> loadTopologyHandles;
  for (const auto& component : loadedLoadLoop->supplyComponents()) {
    loadTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedLoadLoop->demandComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      loadTopologyHandles.push_back(component.handle());
    }
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
  EXPECT_FALSE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != heatPumpHandle) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    sourceTopologyHandles.push_back(component.handle());
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
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Heating Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Heating Source Loop"));
  EXPECT_FALSE(
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Deleted Opposite Equation Fit Heating Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_SequentialLastOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-heating-last-owner-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop loadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Removed First Equation Fit Heating Source Loop"));
  ASSERT_TRUE(loadLoop.setName("Removed Last Equation Fit Heating Load Loop"));
  ASSERT_TRUE(heatPump.setName("Deleted Equation Fit Heating Heat Pump"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(loadLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Heating Source Loop");
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Heating Load Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Deleted Equation Fit Heating Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    sourceTopologyHandles.push_back(component.handle());
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
  EXPECT_FALSE(loadedHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> loadTopologyHandles;
  for (const auto& component : loadedLoadLoop->supplyComponents()) {
    loadTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedLoadLoop->demandComponents()) {
    if (component.handle() != heatPumpHandle) {
      loadTopologyHandles.push_back(component.handle());
    }
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
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed First Equation Fit Heating Source Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Last Equation Fit Heating Load Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Deleted Equation Fit Heating Heat Pump"));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_LoadDemandOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-heating-load-owner-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop loadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Equation Fit Heating Source Loop"));
  ASSERT_TRUE(loadLoop.setName("Removed Equation Fit Heating Load Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Equation Fit Heating Heat Pump"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(loadLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Heating Source Loop");
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Heating Load Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Surviving Equation Fit Heating Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> loadTopologyHandles;
  for (const auto& component : loadedLoadLoop->supplyComponents()) {
    loadTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : loadedLoadLoop->demandComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      loadTopologyHandles.push_back(component.handle());
    }
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
  EXPECT_FALSE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_FALSE(loadedHeatPump->demandInletModelObject());
  EXPECT_FALSE(loadedHeatPump->demandOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());

  PlantLoop replacementLoadLoop(*loadedModel);
  ASSERT_TRUE(replacementLoadLoop.setName("Replacement Equation Fit Heating Load Loop"));
  ASSERT_TRUE(replacementLoadLoop.addDemandBranchForComponent(*loadedHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Heating Source Loop");
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Equation Fit Heating Load Loop");
  auto reloadedHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Surviving Equation Fit Heating Heat Pump");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Heating Load Loop"));
  ASSERT_TRUE(reloadedHeatPump->plantLoop());
  ASSERT_TRUE(reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->plantLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, reloadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandOutletModelObject());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_SourceSupplyOwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-equation-fit-heating-source-owner-removal.idf");

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop loadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating heatPump(model);
  ASSERT_TRUE(sourceLoop.setName("Removed Equation Fit Heating Source Loop"));
  ASSERT_TRUE(loadLoop.setName("Equation Fit Heating Load Loop"));
  ASSERT_TRUE(heatPump.setName("Surviving Equation Fit Heating Heat Pump"));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heatPump));
  ASSERT_TRUE(loadLoop.addDemandBranchForComponent(heatPump));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Heating Source Loop");
  auto loadedLoadLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Heating Load Loop");
  auto loadedHeatPump = loadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Surviving Equation Fit Heating Heat Pump");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedLoadLoop);
  ASSERT_TRUE(loadedHeatPump);
  ASSERT_TRUE(loadedHeatPump->plantLoop());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatPump->plantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, loadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(loadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : loadedSourceLoop->supplyComponents()) {
    if (component.handle() != loadedHeatPump->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedSourceLoop->demandComponents()) {
    sourceTopologyHandles.push_back(component.handle());
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
  EXPECT_FALSE(loadedHeatPump->plantLoop());
  EXPECT_FALSE(loadedHeatPump->supplyInletModelObject());
  EXPECT_FALSE(loadedHeatPump->supplyOutletModelObject());
  ASSERT_TRUE(loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*loadedLoadLoop, *loadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, loadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(loadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(loadedHeatPump->demandOutletModelObject());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Equation Fit Heating Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addSupplyBranchForComponent(*loadedHeatPump));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Equation Fit Heating Source Loop");
  auto reloadedLoadLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Equation Fit Heating Load Loop");
  auto reloadedHeatPump =
    reloadedModel->getConcreteModelObjectByName<HeatPumpWaterToWaterEquationFitHeating>("Surviving Equation Fit Heating Heat Pump");
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedLoadLoop);
  ASSERT_TRUE(reloadedHeatPump);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Equation Fit Heating Source Loop"));
  ASSERT_TRUE(reloadedHeatPump->plantLoop());
  ASSERT_TRUE(reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeatPump->plantLoop());
  EXPECT_EQ(*reloadedLoadLoop, *reloadedHeatPump->secondaryPlantLoop());
  EXPECT_EQ(1u, reloadedSourceLoop->supplyComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedLoadLoop->demandComponents(HeatPumpWaterToWaterEquationFitHeating::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeatPump->supplyInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->supplyOutletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandInletModelObject());
  EXPECT_TRUE(reloadedHeatPump->demandOutletModelObject());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_DefaultConstructor) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_EQ(HeatPumpWaterToWaterEquationFitHeating::iddObjectType(), hp.iddObject().type());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideInletNodeName, hp.supplyInletPort());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::SourceSideOutletNodeName, hp.supplyOutletPort());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideInletNodeName, hp.demandInletPort());
  EXPECT_EQ(openstudio::HeatPump_WaterToWater_EquationFit_HeatingFields::LoadSideOutletNodeName, hp.demandOutletPort());

  EXPECT_TRUE(hp.isReferenceLoadSideFlowRateAutosized());
  EXPECT_TRUE(hp.isReferenceSourceSideFlowRateAutosized());
  EXPECT_TRUE(hp.isRatedHeatingCapacityAutosized());
  EXPECT_TRUE(hp.isRatedHeatingPowerConsumptionAutosized());

  EXPECT_FALSE(hp.referenceLoadSideFlowRate());
  EXPECT_FALSE(hp.referenceSourceSideFlowRate());
  EXPECT_FALSE(hp.ratedHeatingCapacity());
  EXPECT_FALSE(hp.ratedHeatingPowerConsumption());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedLoadSideFlowRate());
  EXPECT_DOUBLE_EQ(-999.0, hp.ratedSourceSideFlowRate());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.heatingCapacityCurve().iddObject().type());
  EXPECT_EQ(CurveQuadLinear::iddObjectType(), hp.heatingCompressorPowerCurve().iddObject().type());
  EXPECT_FALSE(hp.companionCoolingHeatPump());

  EXPECT_DOUBLE_EQ(7.5, hp.referenceCoefficientofPerformance());
  EXPECT_DOUBLE_EQ(1.0, hp.sizingFactor());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_CurveConstructorAndSetters) {
  Model model;
  CurveQuadLinear capacityCurve(model);
  CurveQuadLinear powerCurve(model);

  HeatPumpWaterToWaterEquationFitHeating hp(model, capacityCurve, powerCurve);
  EXPECT_EQ(capacityCurve, hp.heatingCapacityCurve());
  EXPECT_EQ(powerCurve, hp.heatingCompressorPowerCurve());

  CurveQuadLinear replacementCapacity(model);
  CurveQuadLinear replacementPower(model);

  EXPECT_TRUE(hp.setHeatingCapacityCurve(replacementCapacity));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCurve(replacementPower));

  EXPECT_EQ(replacementCapacity, hp.heatingCapacityCurve());
  EXPECT_EQ(replacementPower, hp.heatingCompressorPowerCurve());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_CompanionCoolingHeatPumpRoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating heating(model);
  HeatPumpWaterToWaterEquationFitCooling cooling(model);

  EXPECT_FALSE(heating.companionCoolingHeatPump());
  EXPECT_TRUE(heating.setCompanionCoolingHeatPump(cooling));
  ASSERT_TRUE(heating.companionCoolingHeatPump());
  EXPECT_EQ(cooling, heating.companionCoolingHeatPump().get());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_DeprecatedCoefficientAliasesDelegateThroughStoredCurves) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_TRUE(hp.setHeatingCapacityCoefficient1(1.1));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient2(1.2));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient3(1.3));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient4(1.4));
  EXPECT_TRUE(hp.setHeatingCapacityCoefficient5(1.5));
  EXPECT_DOUBLE_EQ(1.1, hp.heatingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(1.2, hp.heatingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(1.3, hp.heatingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(1.4, hp.heatingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(1.5, hp.heatingCapacityCoefficient5());

  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient1(2.1));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient2(2.2));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient3(2.3));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient4(2.4));
  EXPECT_TRUE(hp.setHeatingCompressorPowerCoefficient5(2.5));
  EXPECT_DOUBLE_EQ(2.1, hp.heatingCompressorPowerCoefficient1());
  EXPECT_DOUBLE_EQ(2.2, hp.heatingCompressorPowerCoefficient2());
  EXPECT_DOUBLE_EQ(2.3, hp.heatingCompressorPowerCoefficient3());
  EXPECT_DOUBLE_EQ(2.4, hp.heatingCompressorPowerCoefficient4());
  EXPECT_DOUBLE_EQ(2.5, hp.heatingCompressorPowerCoefficient5());
}

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop loadLoop(model);
  HeatPumpWaterToWaterEquationFitHeating hp(model);

  EXPECT_TRUE(sourceLoop.addSupplyBranchForComponent(hp));
  ASSERT_TRUE(hp.plantLoop());
  EXPECT_EQ(sourceLoop.handle(), hp.plantLoop()->handle());

  EXPECT_TRUE(loadLoop.addDemandBranchForComponent(hp));
  ASSERT_TRUE(hp.secondaryPlantLoop());
  EXPECT_EQ(loadLoop.handle(), hp.secondaryPlantLoop()->handle());

  ASSERT_TRUE(hp.supplyInletModelObject());
  ASSERT_TRUE(hp.supplyOutletModelObject());
  ASSERT_TRUE(hp.demandInletModelObject());
  ASSERT_TRUE(hp.demandOutletModelObject());

  const auto sourceInletNode = hp.supplyInletModelObject()->cast<Node>();
  const auto sourceOutletNode = hp.supplyOutletModelObject()->cast<Node>();
  const auto loadInletNode = hp.demandInletModelObject()->cast<Node>();
  const auto loadOutletNode = hp.demandOutletModelObject()->cast<Node>();

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

TEST_F(EPModelFixture, HeatPumpWaterToWaterEquationFitHeating_ScalarAccessors_RoundTrip) {
  Model model;
  HeatPumpWaterToWaterEquationFitHeating hp(model);

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

  EXPECT_TRUE(hp.setRatedHeatingCapacity(12450.0));
  ASSERT_TRUE(hp.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(12450.0, *hp.ratedHeatingCapacity());
  hp.autosizeRatedHeatingCapacity();
  EXPECT_TRUE(hp.isRatedHeatingCapacityAutosized());
  EXPECT_FALSE(hp.ratedHeatingCapacity());

  EXPECT_TRUE(hp.setRatedHeatingPowerConsumption(3450.0));
  ASSERT_TRUE(hp.ratedHeatingPowerConsumption());
  EXPECT_DOUBLE_EQ(3450.0, *hp.ratedHeatingPowerConsumption());
  hp.autosizeRatedHeatingPowerConsumption();
  EXPECT_TRUE(hp.isRatedHeatingPowerConsumptionAutosized());
  EXPECT_FALSE(hp.ratedHeatingPowerConsumption());

  EXPECT_TRUE(hp.setReferenceCoefficientofPerformance(6.5));
  EXPECT_DOUBLE_EQ(6.5, hp.referenceCoefficientofPerformance());

  EXPECT_TRUE(hp.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, hp.sizingFactor());
}
