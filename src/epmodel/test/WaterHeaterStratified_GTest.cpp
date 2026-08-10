/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../ModelObject/WaterHeaterSizing_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "../WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"

#include <utilities/idd/WaterHeater_Stratified_FieldEnums.hxx>

#include <utilities/data/DataEnums.hpp>

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterStratified_DefaultConstructor) {
  Model model;
  WaterHeaterStratified heater(model);
  EXPECT_EQ(WaterHeaterStratified::iddObjectType(), heater.iddObject().type());
  EXPECT_FALSE(heater.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), heater.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), heater.demandInletPort());
  EXPECT_TRUE(heater.heater1SetpointTemperatureSchedule());
  EXPECT_TRUE(heater.heater2SetpointTemperatureSchedule());
  EXPECT_TRUE(heater.ambientTemperatureSchedule());
  EXPECT_EQ(heater.handle(), heater.waterHeaterSizing().waterHeater().handle());
  ASSERT_EQ(1u, heater.children().size());
  EXPECT_EQ(heater.waterHeaterSizing().handle(), heater.children().front().handle());
}

TEST_F(EPModelFixture, WaterHeaterStratified_CanonicalizeCreatesMissingWaterHeaterSizing) {
  Model model;
  WaterHeaterStratified heater(model);
  heater.waterHeaterSizing().remove();
  ASSERT_EQ(0u, model.getConcreteModelObjects<WaterHeaterSizing>().size());

  auto report = model.canonicalize();

  EXPECT_EQ(0u, report.errorCount);
  ASSERT_EQ(1u, model.getConcreteModelObjects<WaterHeaterSizing>().size());
  auto sizing = heater.waterHeaterSizing();
  EXPECT_EQ(heater.handle(), sizing.waterHeater().handle());
  EXPECT_EQ("PeakDraw", sizing.designMode().get());
  ASSERT_TRUE(sizing.timeStorageCanMeetPeakDraw());
  EXPECT_DOUBLE_EQ(0.538503, sizing.timeStorageCanMeetPeakDraw().get());
  ASSERT_TRUE(sizing.timeforTankRecovery());
  EXPECT_DOUBLE_EQ(0.0, sizing.timeforTankRecovery().get());
  ASSERT_TRUE(sizing.nominalTankVolumeforAutosizingPlantConnections());
  EXPECT_DOUBLE_EQ(1.0, sizing.nominalTankVolumeforAutosizingPlantConnections().get());

  model.canonicalize();
  EXPECT_EQ(1u, model.getConcreteModelObjects<WaterHeaterSizing>().size());
}

TEST_F(EPModelFixture, WaterHeaterStratified_ScalarAccessors_RoundTrip) {
  Model model;
  WaterHeaterStratified heater(model);

  EXPECT_TRUE(heater.setTankVolume(0.65));
  ASSERT_TRUE(heater.tankVolume());
  EXPECT_DOUBLE_EQ(0.65, heater.tankVolume().get());
  heater.autosizeTankVolume();
  EXPECT_TRUE(heater.isTankVolumeAutosized());

  EXPECT_TRUE(heater.setTankHeight(1.2));
  ASSERT_TRUE(heater.tankHeight());
  heater.autosizeTankHeight();
  EXPECT_TRUE(heater.isTankHeightAutosized());

  EXPECT_TRUE(heater.setHeaterFuelType("Electricity"));
  EXPECT_EQ("Electricity", heater.heaterFuelType());

  EXPECT_TRUE(heater.setHeaterThermalEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, heater.heaterThermalEfficiency());

  EXPECT_TRUE(heater.setOffCycleParasiticFuelType("Electricity"));
  EXPECT_TRUE(heater.setOnCycleParasiticFuelType("NaturalGas"));

  EXPECT_TRUE(heater.setAmbientTemperatureIndicator("ThermalZone"));
  EXPECT_EQ("ThermalZone", heater.ambientTemperatureIndicator());

  EXPECT_TRUE(heater.setAmbientTemperatureOutdoorAirNodeName("OutdoorNode"));
  ASSERT_TRUE(heater.ambientTemperatureOutdoorAirNodeName());
  heater.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_FALSE(heater.ambientTemperatureOutdoorAirNodeName());

  EXPECT_TRUE(heater.setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(2.5));
  heater.resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();

  EXPECT_TRUE(heater.setPeakUseFlowRate(0.002));
  heater.resetPeakUseFlowRate();

  EXPECT_TRUE(heater.setUseSideOutletHeight(0.4));
  EXPECT_DOUBLE_EQ(0.4, heater.useSideOutletHeight().get());
  heater.autocalculateUseSideOutletHeight();
  EXPECT_TRUE(heater.isUseSideOutletHeightAutocalculated());

  EXPECT_TRUE(heater.setSourceSideInletHeight(0.25));
  EXPECT_DOUBLE_EQ(0.25, heater.sourceSideInletHeight().get());
  heater.autocalculateSourceSideInletHeight();
  EXPECT_TRUE(heater.isSourceSideInletHeightAutocalculated());

  EXPECT_TRUE(heater.setUseSideDesignFlowRate(0.002));
  heater.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(heater.isUseSideDesignFlowRateAutosized());

  EXPECT_TRUE(heater.setSourceSideDesignFlowRate(0.0015));
  heater.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(heater.isSourceSideDesignFlowRateAutosized());

  EXPECT_TRUE(heater.setNumberofNodes(3));
  EXPECT_TRUE(heater.setNode1AdditionalLossCoefficient(0.1));

  EXPECT_TRUE(heater.setSourceSideFlowControlMode("IndirectHeatPrimarySetpoint"));
  EXPECT_EQ("IndirectHeatPrimarySetpoint", heater.sourceSideFlowControlMode());

  EXPECT_TRUE(heater.setEndUseSubcategory("DomesticHotWater"));
  EXPECT_EQ("DomesticHotWater", heater.endUseSubcategory());
}

TEST_F(EPModelFixture, WaterHeaterStratified_RelationshipAccessors_RoundTrip) {
  Model model;
  WaterHeaterStratified heater(model);

  ScheduleConstant heater1Setpoint(model);
  ScheduleConstant heater2Setpoint(model);
  ScheduleConstant ambient(model);
  ScheduleConstant useFlowFraction(model);
  ScheduleConstant coldWater(model);
  ScheduleConstant indirectAlternate(model);
  ThermalZone thermalZone(model);

  ASSERT_TRUE(heater1Setpoint.setValue(49.0));
  ASSERT_TRUE(heater2Setpoint.setValue(47.0));
  ASSERT_TRUE(ambient.setValue(20.0));
  ASSERT_TRUE(useFlowFraction.setValue(0.75));
  ASSERT_TRUE(coldWater.setValue(13.0));
  ASSERT_TRUE(indirectAlternate.setValue(46.0));

  EXPECT_TRUE(heater.setHeater1SetpointTemperatureSchedule(heater1Setpoint));
  ASSERT_TRUE(heater.heater1SetpointTemperatureSchedule());
  EXPECT_EQ(heater1Setpoint.handle(), heater.heater1SetpointTemperatureSchedule()->handle());
  heater.resetHeater1SetpointTemperatureSchedule();
  EXPECT_FALSE(heater.heater1SetpointTemperatureSchedule());

  EXPECT_TRUE(heater.setHeater2SetpointTemperatureSchedule(heater2Setpoint));
  ASSERT_TRUE(heater.heater2SetpointTemperatureSchedule());
  EXPECT_EQ(heater2Setpoint.handle(), heater.heater2SetpointTemperatureSchedule()->handle());
  heater.resetHeater2SetpointTemperatureSchedule();
  EXPECT_FALSE(heater.heater2SetpointTemperatureSchedule());

  EXPECT_TRUE(heater.setAmbientTemperatureSchedule(ambient));
  ASSERT_TRUE(heater.ambientTemperatureSchedule());
  EXPECT_EQ(ambient.handle(), heater.ambientTemperatureSchedule()->handle());
  heater.resetAmbientTemperatureSchedule();
  EXPECT_FALSE(heater.ambientTemperatureSchedule());

  EXPECT_TRUE(heater.setAmbientTemperatureThermalZone(thermalZone));
  ASSERT_TRUE(heater.ambientTemperatureThermalZone());
  EXPECT_EQ(thermalZone.handle(), heater.ambientTemperatureThermalZone()->handle());
  heater.resetAmbientTemperatureThermalZone();
  EXPECT_FALSE(heater.ambientTemperatureThermalZone());

  EXPECT_TRUE(heater.setAmbientTemperatureOutdoorAirNodeName("Stratified Water Heater OA Node"));
  ASSERT_TRUE(heater.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ("Stratified Water Heater OA Node", heater.ambientTemperatureOutdoorAirNodeName().get());
  heater.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_FALSE(heater.ambientTemperatureOutdoorAirNodeName());

  EXPECT_TRUE(heater.setUseFlowRateFractionSchedule(useFlowFraction));
  ASSERT_TRUE(heater.useFlowRateFractionSchedule());
  EXPECT_EQ(useFlowFraction.handle(), heater.useFlowRateFractionSchedule()->handle());
  heater.resetUseFlowRateFractionSchedule();
  EXPECT_FALSE(heater.useFlowRateFractionSchedule());

  EXPECT_TRUE(heater.setColdWaterSupplyTemperatureSchedule(coldWater));
  ASSERT_TRUE(heater.coldWaterSupplyTemperatureSchedule());
  EXPECT_EQ(coldWater.handle(), heater.coldWaterSupplyTemperatureSchedule()->handle());
  heater.resetColdWaterSupplyTemperatureSchedule();
  EXPECT_FALSE(heater.coldWaterSupplyTemperatureSchedule());

  EXPECT_TRUE(heater.setIndirectAlternateSetpointTemperatureSchedule(indirectAlternate));
  ASSERT_TRUE(heater.indirectAlternateSetpointTemperatureSchedule());
  EXPECT_EQ(indirectAlternate.handle(), heater.indirectAlternateSetpointTemperatureSchedule()->handle());
  heater.resetIndirectAlternateSetpointTemperatureSchedule();
  EXPECT_FALSE(heater.indirectAlternateSetpointTemperatureSchedule());

  WaterHeaterSizing sizing = heater.waterHeaterSizing();
  EXPECT_EQ(heater.handle(), sizing.waterHeater().handle());
}

TEST_F(EPModelFixture, WaterHeaterStratified_CloneReattachesWaterHeaterSizing) {
  Model model;
  WaterHeaterStratified heater(model);

  auto originalSizing = heater.waterHeaterSizing();
  ASSERT_TRUE(originalSizing.setStorageCapacityperPerson(0.16));

  auto cloneObject = heater.clone(model);
  auto heaterClone = cloneObject.cast<WaterHeaterStratified>();
  EXPECT_EQ(2u, model.getConcreteModelObjects<WaterHeaterSizing>().size());
  EXPECT_NE(heater.handle(), heaterClone.handle());

  auto cloneSizing = heaterClone.waterHeaterSizing();
  EXPECT_NE(originalSizing.handle(), cloneSizing.handle());
  EXPECT_EQ(heaterClone.handle(), cloneSizing.waterHeater().handle());
  ASSERT_TRUE(cloneSizing.storageCapacityperPerson());
  EXPECT_DOUBLE_EQ(0.16, cloneSizing.storageCapacityperPerson().get());

  Model otherModel;
  auto crossCloneObject = heater.clone(otherModel);
  auto crossClone = crossCloneObject.cast<WaterHeaterStratified>();
  EXPECT_EQ(1u, otherModel.getConcreteModelObjects<WaterHeaterSizing>().size());

  auto crossCloneSizing = crossClone.waterHeaterSizing();
  EXPECT_EQ(crossClone.handle(), crossCloneSizing.waterHeater().handle());
  EXPECT_NE(originalSizing.handle(), crossCloneSizing.handle());
  ASSERT_TRUE(crossCloneSizing.storageCapacityperPerson());
  EXPECT_DOUBLE_EQ(0.16, crossCloneSizing.storageCapacityperPerson().get());
}

TEST_F(EPModelFixture, WaterHeaterStratified_WaterToWaterTopology) {
  Model model;
  WaterHeaterStratified heater(model);

  EXPECT_EQ(openstudio::WaterHeater_StratifiedFields::UseSideInletNodeName, heater.supplyInletPort());
  EXPECT_EQ(openstudio::WaterHeater_StratifiedFields::UseSideOutletNodeName, heater.supplyOutletPort());
  EXPECT_EQ(openstudio::WaterHeater_StratifiedFields::SourceSideInletNodeName, heater.demandInletPort());
  EXPECT_EQ(openstudio::WaterHeater_StratifiedFields::SourceSideOutletNodeName, heater.demandOutletPort());

  EXPECT_FALSE(heater.tertiaryInletModelObject());
  EXPECT_FALSE(heater.tertiaryOutletModelObject());

  PlantLoop useLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop replacementSourceLoop(model);

  EXPECT_TRUE(useLoop.addSupplyBranchForComponent(heater));

  ASSERT_TRUE(heater.useSidePlantLoop());
  EXPECT_EQ(useLoop.handle(), heater.useSidePlantLoop()->handle());
  EXPECT_FALSE(heater.sourceSidePlantLoop());
  ASSERT_TRUE(heater.useSideInletModelObject());
  ASSERT_TRUE(heater.useSideOutletModelObject());
  EXPECT_FALSE(heater.sourceSideInletModelObject());
  EXPECT_FALSE(heater.sourceSideOutletModelObject());

  EXPECT_TRUE(sourceLoop.addSupplyBranchForComponent(heater));

  ASSERT_TRUE(heater.plantLoop());
  EXPECT_EQ(useLoop.handle(), heater.plantLoop()->handle());
  ASSERT_TRUE(heater.secondaryPlantLoop());
  EXPECT_EQ(sourceLoop.handle(), heater.secondaryPlantLoop()->handle());
  ASSERT_TRUE(heater.useSidePlantLoop());
  EXPECT_EQ(useLoop.handle(), heater.useSidePlantLoop()->handle());
  ASSERT_TRUE(heater.sourceSidePlantLoop());
  EXPECT_EQ(sourceLoop.handle(), heater.sourceSidePlantLoop()->handle());

  ASSERT_TRUE(heater.supplyInletModelObject());
  ASSERT_TRUE(heater.supplyOutletModelObject());
  ASSERT_TRUE(heater.demandInletModelObject());
  ASSERT_TRUE(heater.demandOutletModelObject());
  ASSERT_TRUE(heater.useSideInletModelObject());
  ASSERT_TRUE(heater.useSideOutletModelObject());
  ASSERT_TRUE(heater.sourceSideInletModelObject());
  ASSERT_TRUE(heater.sourceSideOutletModelObject());

  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Heating), heater.componentType());
  EXPECT_EQ(std::vector<openstudio::FuelType>{openstudio::FuelType::Electricity}, heater.heatingFuelTypes());
  EXPECT_EQ(std::vector<openstudio::AppGFuelType>{openstudio::convertFuelTypeToAppG(openstudio::FuelType::Electricity)},
            heater.appGHeatingFuelTypes());
  EXPECT_TRUE(heater.coolingFuelTypes().empty());

  EXPECT_TRUE(heater.removeFromSourceSidePlantLoop());
  EXPECT_FALSE(heater.sourceSidePlantLoop());
  EXPECT_FALSE(heater.sourceSideInletModelObject());
  EXPECT_FALSE(heater.sourceSideOutletModelObject());
  ASSERT_TRUE(heater.useSidePlantLoop());
  EXPECT_EQ(useLoop.handle(), heater.useSidePlantLoop()->handle());

  auto replacementSourceNode = replacementSourceLoop.demandInletNode();
  EXPECT_TRUE(heater.addToSourceSideNode(replacementSourceNode));
  ASSERT_TRUE(heater.sourceSidePlantLoop());
  EXPECT_EQ(replacementSourceLoop.handle(), heater.sourceSidePlantLoop()->handle());
}

TEST_F(EPModelFixture, WaterHeaterStratified_OwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-water-heater-stratified-use-owner-removal.idf");

  Model model;
  PlantLoop useLoop(model);
  PlantLoop sourceLoop(model);
  WaterHeaterStratified heater(model);
  ASSERT_TRUE(useLoop.setName("Removed Stratified Water Heater Use Loop"));
  ASSERT_TRUE(sourceLoop.setName("Surviving Stratified Water Heater Source Loop"));
  ASSERT_TRUE(heater.setName("Surviving Dual Supply Stratified Water Heater"));
  ASSERT_TRUE(useLoop.addSupplyBranchForComponent(heater));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heater));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedUseLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Stratified Water Heater Use Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Stratified Water Heater Source Loop");
  auto loadedHeater = loadedModel->getConcreteModelObjectByName<WaterHeaterStratified>("Surviving Dual Supply Stratified Water Heater");
  ASSERT_TRUE(loadedUseLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeater);
  ASSERT_TRUE(loadedHeater->useSidePlantLoop());
  ASSERT_TRUE(loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(*loadedUseLoop, *loadedHeater->useSidePlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, loadedUseLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_TRUE(loadedHeater->useSideInletModelObject());
  EXPECT_TRUE(loadedHeater->useSideOutletModelObject());
  EXPECT_TRUE(loadedHeater->sourceSideInletModelObject());
  EXPECT_TRUE(loadedHeater->sourceSideOutletModelObject());
  auto loadedWaterHeaterSizing = loadedHeater->waterHeaterSizing();
  EXPECT_EQ(loadedHeater->handle(), loadedWaterHeaterSizing.waterHeater().handle());

  std::vector<openstudio::Handle> useTopologyHandles;
  for (const auto& component : loadedUseLoop->supplyComponents()) {
    if (component.handle() != loadedHeater->handle()) {
      useTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedUseLoop->demandComponents()) {
    useTopologyHandles.push_back(component.handle());
  }
  const auto useLoopHandle = loadedUseLoop->handle();
  const auto sizingPlantHandle = loadedUseLoop->sizingPlant().handle();
  const auto heaterHandle = loadedHeater->handle();
  const auto waterHeaterSizingHandle = loadedWaterHeaterSizing.handle();
  EXPECT_FALSE(loadedUseLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(useLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  for (const auto& handle : useTopologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }
  EXPECT_TRUE(loadedModel->getObject(heaterHandle));
  EXPECT_TRUE(loadedModel->getObject(waterHeaterSizingHandle));
  EXPECT_FALSE(loadedHeater->useSidePlantLoop());
  EXPECT_FALSE(loadedHeater->useSideInletModelObject());
  EXPECT_FALSE(loadedHeater->useSideOutletModelObject());
  ASSERT_TRUE(loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_TRUE(loadedHeater->sourceSideInletModelObject());
  EXPECT_TRUE(loadedHeater->sourceSideOutletModelObject());
  EXPECT_EQ(loadedHeater->handle(), loadedHeater->waterHeaterSizing().waterHeater().handle());

  PlantLoop replacementUseLoop(*loadedModel);
  ASSERT_TRUE(replacementUseLoop.setName("Replacement Stratified Water Heater Use Loop"));
  ASSERT_TRUE(replacementUseLoop.addSupplyBranchForComponent(*loadedHeater));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedUseLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Stratified Water Heater Use Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Stratified Water Heater Source Loop");
  auto reloadedHeater = reloadedModel->getConcreteModelObjectByName<WaterHeaterStratified>("Surviving Dual Supply Stratified Water Heater");
  ASSERT_TRUE(reloadedUseLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeater);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Stratified Water Heater Use Loop"));
  ASSERT_TRUE(reloadedHeater->useSidePlantLoop());
  ASSERT_TRUE(reloadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(*reloadedUseLoop, *reloadedHeater->useSidePlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, reloadedUseLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSourceLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeater->useSideInletModelObject());
  EXPECT_TRUE(reloadedHeater->useSideOutletModelObject());
  EXPECT_TRUE(reloadedHeater->sourceSideInletModelObject());
  EXPECT_TRUE(reloadedHeater->sourceSideOutletModelObject());
  EXPECT_EQ(reloadedHeater->handle(), reloadedHeater->waterHeaterSizing().waterHeater().handle());

  std::vector<openstudio::Handle> sourceTopologyHandles;
  for (const auto& component : reloadedSourceLoop->supplyComponents()) {
    if (component.handle() != reloadedHeater->handle()) {
      sourceTopologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : reloadedSourceLoop->demandComponents()) {
    sourceTopologyHandles.push_back(component.handle());
  }
  const auto sourceLoopHandle = reloadedSourceLoop->handle();
  const auto sourceSizingPlantHandle = reloadedSourceLoop->sizingPlant().handle();
  const auto reloadedHeaterHandle = reloadedHeater->handle();
  const auto reloadedWaterHeaterSizingHandle = reloadedHeater->waterHeaterSizing().handle();
  EXPECT_FALSE(reloadedSourceLoop->remove().empty());
  EXPECT_FALSE(reloadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(reloadedModel->getObject(sourceSizingPlantHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(reloadedModel->getObject(handle));
  }
  EXPECT_TRUE(reloadedModel->getObject(reloadedHeaterHandle));
  EXPECT_TRUE(reloadedModel->getObject(reloadedWaterHeaterSizingHandle));
  EXPECT_FALSE(reloadedHeater->sourceSidePlantLoop());
  EXPECT_FALSE(reloadedHeater->sourceSideInletModelObject());
  EXPECT_FALSE(reloadedHeater->sourceSideOutletModelObject());
  ASSERT_TRUE(reloadedHeater->useSidePlantLoop());
  EXPECT_EQ(*reloadedUseLoop, *reloadedHeater->useSidePlantLoop());
  EXPECT_EQ(1u, reloadedUseLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeater->useSideInletModelObject());
  EXPECT_TRUE(reloadedHeater->useSideOutletModelObject());
  EXPECT_EQ(reloadedHeater->handle(), reloadedHeater->waterHeaterSizing().waterHeater().handle());

  PlantLoop replacementSourceLoop(*reloadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Stratified Water Heater Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addSupplyBranchForComponent(*reloadedHeater));
  ASSERT_TRUE(reloadedModel->save(idfPath, true));

  auto finalModel = Model::load(idfPath);
  ASSERT_TRUE(finalModel);
  auto finalUseLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Replacement Stratified Water Heater Use Loop");
  auto finalSourceLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Replacement Stratified Water Heater Source Loop");
  auto finalHeater = finalModel->getConcreteModelObjectByName<WaterHeaterStratified>("Surviving Dual Supply Stratified Water Heater");
  ASSERT_TRUE(finalUseLoop);
  ASSERT_TRUE(finalSourceLoop);
  ASSERT_TRUE(finalHeater);
  EXPECT_FALSE(finalModel->getConcreteModelObjectByName<PlantLoop>("Surviving Stratified Water Heater Source Loop"));
  ASSERT_TRUE(finalHeater->useSidePlantLoop());
  ASSERT_TRUE(finalHeater->sourceSidePlantLoop());
  EXPECT_EQ(*finalUseLoop, *finalHeater->useSidePlantLoop());
  EXPECT_EQ(*finalSourceLoop, *finalHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, finalUseLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_EQ(1u, finalSourceLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_TRUE(finalHeater->useSideInletModelObject());
  EXPECT_TRUE(finalHeater->useSideOutletModelObject());
  EXPECT_TRUE(finalHeater->sourceSideInletModelObject());
  EXPECT_TRUE(finalHeater->sourceSideOutletModelObject());
  EXPECT_EQ(finalHeater->handle(), finalHeater->waterHeaterSizing().waterHeater().handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, WaterHeaterStratified_LastOwnerUseLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-water-heater-stratified-last-owner-use-removal.idf");

  Model model;
  PlantLoop useLoop(model);
  WaterHeaterStratified heater(model);
  ASSERT_TRUE(useLoop.setName("Last Owner Stratified Water Heater Use Loop"));
  ASSERT_TRUE(heater.setName("Last Owner Stratified Water Heater"));
  ASSERT_TRUE(useLoop.addSupplyBranchForComponent(heater));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedUseLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Stratified Water Heater Use Loop");
  auto loadedHeater = loadedModel->getConcreteModelObjectByName<WaterHeaterStratified>("Last Owner Stratified Water Heater");
  ASSERT_TRUE(loadedUseLoop);
  ASSERT_TRUE(loadedHeater);
  ASSERT_TRUE(loadedHeater->useSidePlantLoop());
  EXPECT_EQ(*loadedUseLoop, *loadedHeater->useSidePlantLoop());
  EXPECT_FALSE(loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, loadedUseLoop->supplyComponents(WaterHeaterStratified::iddObjectType()).size());
  EXPECT_TRUE(loadedHeater->useSideInletModelObject());
  EXPECT_TRUE(loadedHeater->useSideOutletModelObject());
  EXPECT_FALSE(loadedHeater->sourceSideInletModelObject());
  EXPECT_FALSE(loadedHeater->sourceSideOutletModelObject());
  auto loadedWaterHeaterSizing = loadedHeater->waterHeaterSizing();
  EXPECT_EQ(loadedHeater->handle(), loadedWaterHeaterSizing.waterHeater().handle());

  std::vector<openstudio::Handle> topologyHandles;
  for (const auto& component : loadedUseLoop->supplyComponents()) {
    if (component.handle() != loadedHeater->handle()) {
      topologyHandles.push_back(component.handle());
    }
  }
  for (const auto& component : loadedUseLoop->demandComponents()) {
    topologyHandles.push_back(component.handle());
  }
  const auto loopHandle = loadedUseLoop->handle();
  const auto sizingPlantHandle = loadedUseLoop->sizingPlant().handle();
  const auto heaterHandle = loadedHeater->handle();
  const auto waterHeaterSizingHandle = loadedWaterHeaterSizing.handle();
  EXPECT_FALSE(loadedUseLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loopHandle));
  EXPECT_FALSE(loadedModel->getObject(sizingPlantHandle));
  EXPECT_FALSE(loadedModel->getObject(heaterHandle));
  EXPECT_FALSE(loadedModel->getObject(waterHeaterSizingHandle));
  for (const auto& handle : topologyHandles) {
    EXPECT_FALSE(loadedModel->getObject(handle));
  }

  ASSERT_TRUE(loadedModel->save(idfPath, true));
  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Stratified Water Heater Use Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<WaterHeaterStratified>("Last Owner Stratified Water Heater"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<WaterHeaterSizing>().empty());

  openstudio::filesystem::remove(idfPath);
}
