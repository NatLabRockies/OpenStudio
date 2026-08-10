/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveCubic.hpp"
#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../ModelObject/WaterHeaterSizing_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToWaterComponent/WaterHeaterMixed.hpp"
#include "../WaterToWaterComponent/WaterHeaterMixed_Impl.hpp"

#include <utilities/idd/WaterHeater_Mixed_FieldEnums.hxx>

#include <utilities/data/DataEnums.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterMixed_DefaultConstructor) {
  Model model;
  WaterHeaterMixed heater(model);
  EXPECT_EQ(WaterHeaterMixed::iddObjectType(), heater.iddObject().type());
  EXPECT_FALSE(heater.nameString().empty());
  EXPECT_TRUE(heater.setpointTemperatureSchedule());
  EXPECT_TRUE(heater.ambientTemperatureSchedule());
  EXPECT_EQ(heater.handle(), heater.waterHeaterSizing().waterHeater().handle());
  ASSERT_EQ(1u, heater.children().size());
  EXPECT_EQ(heater.waterHeaterSizing().handle(), heater.children().front().handle());
}

TEST_F(EPModelFixture, WaterHeaterMixed_CanonicalizeCreatesMissingWaterHeaterSizing) {
  Model model;
  WaterHeaterMixed heater(model);
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

TEST_F(EPModelFixture, WaterHeaterMixed_ScalarAccessors_RoundTrip) {
  Model model;
  WaterHeaterMixed heater(model);

  EXPECT_TRUE(heater.setTankVolume(0.65));
  ASSERT_TRUE(heater.tankVolume());
  EXPECT_DOUBLE_EQ(0.65, heater.tankVolume().get());
  EXPECT_FALSE(heater.isTankVolumeAutosized());
  heater.autosizeTankVolume();
  EXPECT_TRUE(heater.isTankVolumeAutosized());
  heater.resetTankVolume();
  EXPECT_FALSE(heater.tankVolume());
  EXPECT_FALSE(heater.autosizedTankVolume());

  EXPECT_TRUE(heater.setDeadbandTemperatureDifference(0.4));
  EXPECT_DOUBLE_EQ(0.4, heater.deadbandTemperatureDifference());
  heater.resetDeadbandTemperatureDifference();

  EXPECT_TRUE(heater.setMaximumTemperatureLimit(95.0));
  ASSERT_TRUE(heater.maximumTemperatureLimit());
  heater.resetMaximumTemperatureLimit();

  EXPECT_TRUE(heater.setHeaterControlType("Modulate"));
  EXPECT_EQ("Modulate", heater.heaterControlType());

  EXPECT_TRUE(heater.setHeaterMaximumCapacity(180000.0));
  EXPECT_TRUE(heater.isHeaterMaximumCapacityAutosized() == false);
  heater.autosizeHeaterMaximumCapacity();
  EXPECT_TRUE(heater.isHeaterMaximumCapacityAutosized());
  heater.resetHeaterMaximumCapacity();
  EXPECT_FALSE(heater.heaterMaximumCapacity());
  EXPECT_FALSE(heater.autosizedHeaterMaximumCapacity());

  EXPECT_TRUE(heater.setHeaterMinimumCapacity(80000.0));
  ASSERT_TRUE(heater.heaterMinimumCapacity());
  heater.resetHeaterMinimumCapacity();

  EXPECT_TRUE(heater.setHeaterIgnitionMinimumFlowRate(0.002));
  EXPECT_DOUBLE_EQ(0.002, heater.heaterIgnitionMinimumFlowRate());
  heater.resetHeaterIgnitionMinimumFlowRate();

  EXPECT_TRUE(heater.setHeaterIgnitionDelay(3.0));
  EXPECT_DOUBLE_EQ(3.0, heater.heaterIgnitionDelay());
  heater.resetHeaterIgnitionDelay();

  EXPECT_TRUE(heater.setHeaterFuelType("Propane"));
  EXPECT_EQ("Propane", heater.heaterFuelType());

  EXPECT_TRUE(heater.setHeaterThermalEfficiency(0.92));
  ASSERT_TRUE(heater.heaterThermalEfficiency());
  heater.resetHeaterThermalEfficiency();

  CurveCubic partLoadFactorCurve(model);
  EXPECT_TRUE(heater.setPartLoadFactorCurve(partLoadFactorCurve));
  ASSERT_TRUE(heater.partLoadFactorCurve());
  EXPECT_EQ(partLoadFactorCurve.handle(), heater.partLoadFactorCurve()->handle());
  heater.resetPartLoadFactorCurve();
  EXPECT_FALSE(heater.partLoadFactorCurve());

  EXPECT_TRUE(heater.setOffCycleParasiticFuelConsumptionRate(25.0));
  EXPECT_DOUBLE_EQ(25.0, heater.offCycleParasiticFuelConsumptionRate());
  heater.resetOffCycleParasiticFuelConsumptionRate();

  EXPECT_TRUE(heater.setOffCycleParasiticFuelType("Electricity"));
  heater.resetOffCycleParasiticFuelType();

  EXPECT_TRUE(heater.setOffCycleParasiticHeatFractiontoTank(0.6));
  EXPECT_DOUBLE_EQ(0.6, heater.offCycleParasiticHeatFractiontoTank());
  heater.resetOffCycleParasiticHeatFractiontoTank();

  EXPECT_TRUE(heater.setOnCycleParasiticFuelConsumptionRate(45.0));
  EXPECT_DOUBLE_EQ(45.0, heater.onCycleParasiticFuelConsumptionRate());
  heater.resetOnCycleParasiticFuelConsumptionRate();

  EXPECT_TRUE(heater.setOnCycleParasiticFuelType("NaturalGas"));
  heater.resetOnCycleParasiticFuelType();

  EXPECT_TRUE(heater.setOnCycleParasiticHeatFractiontoTank(0.45));
  EXPECT_DOUBLE_EQ(0.45, heater.onCycleParasiticHeatFractiontoTank());
  heater.resetOnCycleParasiticHeatFractiontoTank();

  EXPECT_TRUE(heater.setAmbientTemperatureIndicator("ThermalZone"));
  EXPECT_EQ("ThermalZone", heater.ambientTemperatureIndicator());

  EXPECT_TRUE(heater.setOffCycleLossCoefficienttoAmbientTemperature(6.5));
  heater.resetOffCycleLossCoefficienttoAmbientTemperature();

  EXPECT_TRUE(heater.setOffCycleLossFractiontoThermalZone(0.75));
  heater.resetOffCycleLossFractiontoThermalZone();

  EXPECT_TRUE(heater.setOnCycleLossCoefficienttoAmbientTemperature(4.2));
  heater.resetOnCycleLossCoefficienttoAmbientTemperature();

  EXPECT_TRUE(heater.setOnCycleLossFractiontoThermalZone(0.82));
  heater.resetOnCycleLossFractiontoThermalZone();

  EXPECT_TRUE(heater.setPeakUseFlowRate(0.0015));
  ASSERT_TRUE(heater.peakUseFlowRate());
  heater.resetPeakUseFlowRate();

  EXPECT_TRUE(heater.setUseSideEffectiveness(0.96));
  EXPECT_DOUBLE_EQ(0.96, heater.useSideEffectiveness());
  heater.resetUseSideEffectiveness();

  EXPECT_TRUE(heater.setSourceSideEffectiveness(0.87));
  EXPECT_DOUBLE_EQ(0.87, heater.sourceSideEffectiveness());
  heater.resetSourceSideEffectiveness();

  EXPECT_TRUE(heater.setUseSideDesignFlowRate(0.003));
  ASSERT_TRUE(heater.useSideDesignFlowRate());
  heater.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(heater.isUseSideDesignFlowRateAutosized());
  heater.resetUseSideDesignFlowRate();
  EXPECT_FALSE(heater.useSideDesignFlowRate());

  EXPECT_TRUE(heater.setSourceSideDesignFlowRate(0.0025));
  ASSERT_TRUE(heater.sourceSideDesignFlowRate());
  heater.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(heater.isSourceSideDesignFlowRateAutosized());
  heater.resetSourceSideDesignFlowRate();
  EXPECT_FALSE(heater.sourceSideDesignFlowRate());

  EXPECT_TRUE(heater.setIndirectWaterHeatingRecoveryTime(1.8));
  EXPECT_DOUBLE_EQ(1.8, heater.indirectWaterHeatingRecoveryTime());
  heater.resetIndirectWaterHeatingRecoveryTime();

  EXPECT_TRUE(heater.setSourceSideFlowControlMode("IndirectHeatPrimarySetpoint"));
  EXPECT_EQ("IndirectHeatPrimarySetpoint", heater.sourceSideFlowControlMode());

  EXPECT_TRUE(heater.setEndUseSubcategory("DomesticHotWater"));
  EXPECT_EQ("DomesticHotWater", heater.endUseSubcategory());
}

TEST_F(EPModelFixture, WaterHeaterMixed_RelationshipAccessors_RoundTrip) {
  Model model;
  WaterHeaterMixed heater(model);

  ScheduleConstant setpoint(model);
  ScheduleConstant ambient(model);
  ScheduleConstant useFlowFraction(model);
  ScheduleConstant coldWater(model);
  ScheduleConstant indirectAlternate(model);
  ThermalZone thermalZone(model);
  CurveCubic partLoadFactorCurve(model);

  ASSERT_TRUE(setpoint.setValue(58.0));
  ASSERT_TRUE(ambient.setValue(23.0));
  ASSERT_TRUE(useFlowFraction.setValue(0.5));
  ASSERT_TRUE(coldWater.setValue(14.0));
  ASSERT_TRUE(indirectAlternate.setValue(52.0));

  EXPECT_TRUE(heater.setSetpointTemperatureSchedule(setpoint));
  ASSERT_TRUE(heater.setpointTemperatureSchedule());
  EXPECT_EQ(setpoint.handle(), heater.setpointTemperatureSchedule()->handle());
  heater.resetSetpointTemperatureSchedule();
  EXPECT_FALSE(heater.setpointTemperatureSchedule());

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

  EXPECT_TRUE(heater.setAmbientTemperatureOutdoorAirNodeName("Mixed Water Heater OA Node"));
  ASSERT_TRUE(heater.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ("Mixed Water Heater OA Node", heater.ambientTemperatureOutdoorAirNodeName().get());
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

  EXPECT_TRUE(heater.setPartLoadFactorCurve(partLoadFactorCurve));
  ASSERT_TRUE(heater.partLoadFactorCurve());
  EXPECT_EQ(partLoadFactorCurve.handle(), heater.partLoadFactorCurve()->handle());
  heater.resetPartLoadFactorCurve();
  EXPECT_FALSE(heater.partLoadFactorCurve());

  EXPECT_TRUE(heater.setIndirectAlternateSetpointTemperatureSchedule(indirectAlternate));
  ASSERT_TRUE(heater.indirectAlternateSetpointTemperatureSchedule());
  EXPECT_EQ(indirectAlternate.handle(), heater.indirectAlternateSetpointTemperatureSchedule()->handle());
  EXPECT_EQ("IndirectHeatAlternateSetpoint", heater.sourceSideFlowControlMode());
  heater.resetIndirectAlternateSetpointTemperatureSchedule();
  EXPECT_FALSE(heater.indirectAlternateSetpointTemperatureSchedule());
  EXPECT_EQ("IndirectHeatPrimarySetpoint", heater.sourceSideFlowControlMode());

  WaterHeaterSizing sizing = heater.waterHeaterSizing();
  EXPECT_EQ(heater.handle(), sizing.waterHeater().handle());
}

TEST_F(EPModelFixture, WaterHeaterMixed_SourceSideFlowControlParity) {
  Model model;
  WaterHeaterMixed heater(model);
  ScheduleConstant indirectAlternate(model);

  ASSERT_TRUE(indirectAlternate.setValue(52.0));

  EXPECT_EQ("IndirectHeatPrimarySetpoint", heater.sourceSideFlowControlMode());
  EXPECT_FALSE(heater.indirectAlternateSetpointTemperatureSchedule());
  EXPECT_FALSE(heater.setSourceSideFlowControlMode("IndirectHeatAlternateSetpoint"));

  EXPECT_TRUE(heater.setIndirectAlternateSetpointTemperatureSchedule(indirectAlternate));
  ASSERT_TRUE(heater.indirectAlternateSetpointTemperatureSchedule());
  EXPECT_EQ(indirectAlternate.handle(), heater.indirectAlternateSetpointTemperatureSchedule()->handle());
  EXPECT_EQ("IndirectHeatAlternateSetpoint", heater.sourceSideFlowControlMode());

  EXPECT_TRUE(heater.setSourceSideFlowControlMode("StorageTank"));
  EXPECT_EQ("StorageTank", heater.sourceSideFlowControlMode());
  EXPECT_FALSE(heater.indirectAlternateSetpointTemperatureSchedule());

  EXPECT_TRUE(heater.setIndirectAlternateSetpointTemperatureSchedule(indirectAlternate));
  heater.resetIndirectAlternateSetpointTemperatureSchedule();
  EXPECT_FALSE(heater.indirectAlternateSetpointTemperatureSchedule());
  EXPECT_EQ("IndirectHeatPrimarySetpoint", heater.sourceSideFlowControlMode());
}

TEST_F(EPModelFixture, WaterHeaterMixed_WaterToWaterTopology) {
  Model model;
  WaterHeaterMixed heater(model);

  EXPECT_EQ(openstudio::WaterHeater_MixedFields::UseSideInletNodeName, heater.supplyInletPort());
  EXPECT_EQ(openstudio::WaterHeater_MixedFields::UseSideOutletNodeName, heater.supplyOutletPort());
  EXPECT_EQ(openstudio::WaterHeater_MixedFields::SourceSideInletNodeName, heater.demandInletPort());
  EXPECT_EQ(openstudio::WaterHeater_MixedFields::SourceSideOutletNodeName, heater.demandOutletPort());

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
  EXPECT_EQ(std::vector<openstudio::FuelType>{openstudio::FuelType::Gas}, heater.heatingFuelTypes());
  EXPECT_EQ(std::vector<openstudio::AppGFuelType>{openstudio::convertFuelTypeToAppG(openstudio::FuelType::Gas)}, heater.appGHeatingFuelTypes());
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

TEST_F(EPModelFixture, WaterHeaterMixed_OwnerLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-water-heater-mixed-dual-supply-use-removal.idf");

  Model model;
  PlantLoop useLoop(model);
  PlantLoop sourceLoop(model);
  WaterHeaterMixed heater(model);
  ASSERT_TRUE(useLoop.setName("Removed Water Heater Use Loop"));
  ASSERT_TRUE(sourceLoop.setName("Surviving Water Heater Source Loop"));
  ASSERT_TRUE(heater.setName("Surviving Dual Supply Water Heater"));
  ASSERT_TRUE(useLoop.addSupplyBranchForComponent(heater));
  ASSERT_TRUE(sourceLoop.addSupplyBranchForComponent(heater));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedUseLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Water Heater Use Loop");
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Water Heater Source Loop");
  auto loadedHeater = loadedModel->getConcreteModelObjectByName<WaterHeaterMixed>("Surviving Dual Supply Water Heater");
  ASSERT_TRUE(loadedUseLoop);
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeater);
  ASSERT_TRUE(loadedHeater->useSidePlantLoop());
  ASSERT_TRUE(loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(*loadedUseLoop, *loadedHeater->useSidePlantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, loadedUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
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
  const auto useSizingHandle = loadedUseLoop->sizingPlant().handle();
  const auto heaterHandle = loadedHeater->handle();
  const auto waterHeaterSizingHandle = loadedWaterHeaterSizing.handle();
  EXPECT_FALSE(loadedUseLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(useLoopHandle));
  EXPECT_FALSE(loadedModel->getObject(useSizingHandle));
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
  EXPECT_EQ(1u, loadedSourceLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_TRUE(loadedHeater->sourceSideInletModelObject());
  EXPECT_TRUE(loadedHeater->sourceSideOutletModelObject());
  EXPECT_EQ(loadedHeater->handle(), loadedHeater->waterHeaterSizing().waterHeater().handle());

  PlantLoop replacementUseLoop(*loadedModel);
  ASSERT_TRUE(replacementUseLoop.setName("Replacement Water Heater Use Loop"));
  ASSERT_TRUE(replacementUseLoop.addSupplyBranchForComponent(*loadedHeater));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedUseLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Water Heater Use Loop");
  auto reloadedSourceLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Surviving Water Heater Source Loop");
  auto reloadedHeater = reloadedModel->getConcreteModelObjectByName<WaterHeaterMixed>("Surviving Dual Supply Water Heater");
  ASSERT_TRUE(reloadedUseLoop);
  ASSERT_TRUE(reloadedSourceLoop);
  ASSERT_TRUE(reloadedHeater);
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Removed Water Heater Use Loop"));
  ASSERT_TRUE(reloadedHeater->useSidePlantLoop());
  ASSERT_TRUE(reloadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(*reloadedUseLoop, *reloadedHeater->useSidePlantLoop());
  EXPECT_EQ(*reloadedSourceLoop, *reloadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, reloadedUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_EQ(1u, reloadedSourceLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
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
  const auto sourceSizingHandle = reloadedSourceLoop->sizingPlant().handle();
  const auto reloadedHeaterHandle = reloadedHeater->handle();
  const auto reloadedWaterHeaterSizingHandle = reloadedHeater->waterHeaterSizing().handle();
  EXPECT_FALSE(reloadedSourceLoop->remove().empty());
  EXPECT_FALSE(reloadedModel->getObject(sourceLoopHandle));
  EXPECT_FALSE(reloadedModel->getObject(sourceSizingHandle));
  for (const auto& handle : sourceTopologyHandles) {
    EXPECT_FALSE(reloadedModel->getObject(handle));
  }
  ASSERT_TRUE(reloadedModel->getObject(reloadedHeaterHandle));
  EXPECT_TRUE(reloadedModel->getObject(reloadedWaterHeaterSizingHandle));
  EXPECT_FALSE(reloadedHeater->sourceSidePlantLoop());
  EXPECT_FALSE(reloadedHeater->sourceSideInletModelObject());
  EXPECT_FALSE(reloadedHeater->sourceSideOutletModelObject());
  ASSERT_TRUE(reloadedHeater->useSidePlantLoop());
  EXPECT_EQ(*reloadedUseLoop, *reloadedHeater->useSidePlantLoop());
  EXPECT_EQ(1u, reloadedUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_TRUE(reloadedHeater->useSideInletModelObject());
  EXPECT_TRUE(reloadedHeater->useSideOutletModelObject());
  EXPECT_EQ(reloadedHeater->handle(), reloadedHeater->waterHeaterSizing().waterHeater().handle());

  PlantLoop replacementSourceLoop(*reloadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement Water Heater Source Loop"));
  ASSERT_TRUE(replacementSourceLoop.addSupplyBranchForComponent(*reloadedHeater));
  ASSERT_TRUE(reloadedModel->save(idfPath, true));

  auto finalModel = Model::load(idfPath);
  ASSERT_TRUE(finalModel);
  auto finalUseLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Replacement Water Heater Use Loop");
  auto finalSourceLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Replacement Water Heater Source Loop");
  auto finalHeater = finalModel->getConcreteModelObjectByName<WaterHeaterMixed>("Surviving Dual Supply Water Heater");
  ASSERT_TRUE(finalUseLoop);
  ASSERT_TRUE(finalSourceLoop);
  ASSERT_TRUE(finalHeater);
  EXPECT_FALSE(finalModel->getConcreteModelObjectByName<PlantLoop>("Removed Water Heater Use Loop"));
  EXPECT_FALSE(finalModel->getConcreteModelObjectByName<PlantLoop>("Surviving Water Heater Source Loop"));
  ASSERT_TRUE(finalHeater->useSidePlantLoop());
  ASSERT_TRUE(finalHeater->sourceSidePlantLoop());
  EXPECT_EQ(*finalUseLoop, *finalHeater->useSidePlantLoop());
  EXPECT_EQ(*finalSourceLoop, *finalHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, finalUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_EQ(1u, finalSourceLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_TRUE(finalHeater->useSideInletModelObject());
  EXPECT_TRUE(finalHeater->useSideOutletModelObject());
  EXPECT_TRUE(finalHeater->sourceSideInletModelObject());
  EXPECT_TRUE(finalHeater->sourceSideOutletModelObject());
  EXPECT_EQ(finalHeater->handle(), finalHeater->waterHeaterSizing().waterHeater().handle());

  ASSERT_TRUE(finalHeater->removeFromSourceSidePlantLoop());
  ASSERT_TRUE(finalSourceLoop->setName("Removed Demand Water Heater Source Loop"));
  ASSERT_TRUE(finalSourceLoop->addDemandBranchForComponent(*finalHeater));
  ASSERT_TRUE(finalModel->save(idfPath, true));

  auto demandSourceModel = Model::load(idfPath);
  ASSERT_TRUE(demandSourceModel);
  auto demandSourceUseLoop = demandSourceModel->getConcreteModelObjectByName<PlantLoop>("Replacement Water Heater Use Loop");
  auto removedDemandSourceLoop = demandSourceModel->getConcreteModelObjectByName<PlantLoop>("Removed Demand Water Heater Source Loop");
  auto demandSourceHeater = demandSourceModel->getConcreteModelObjectByName<WaterHeaterMixed>("Surviving Dual Supply Water Heater");
  ASSERT_TRUE(demandSourceUseLoop);
  ASSERT_TRUE(removedDemandSourceLoop);
  ASSERT_TRUE(demandSourceHeater);
  ASSERT_TRUE(demandSourceHeater->useSidePlantLoop());
  ASSERT_TRUE(demandSourceHeater->sourceSidePlantLoop());
  EXPECT_EQ(*demandSourceUseLoop, *demandSourceHeater->useSidePlantLoop());
  EXPECT_EQ(*removedDemandSourceLoop, *demandSourceHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, demandSourceUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_EQ(0u, removedDemandSourceLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_EQ(1u, removedDemandSourceLoop->demandComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_TRUE(demandSourceHeater->useSideInletModelObject());
  EXPECT_TRUE(demandSourceHeater->useSideOutletModelObject());
  EXPECT_TRUE(demandSourceHeater->sourceSideInletModelObject());
  EXPECT_TRUE(demandSourceHeater->sourceSideOutletModelObject());
  EXPECT_EQ(demandSourceHeater->handle(), demandSourceHeater->waterHeaterSizing().waterHeater().handle());

  std::vector<openstudio::Handle> demandSourceTopologyHandles;
  for (const auto& component : removedDemandSourceLoop->supplyComponents()) {
    demandSourceTopologyHandles.push_back(component.handle());
  }
  for (const auto& component : removedDemandSourceLoop->demandComponents()) {
    if (component.handle() != demandSourceHeater->handle()) {
      demandSourceTopologyHandles.push_back(component.handle());
    }
  }
  const auto demandSourceLoopHandle = removedDemandSourceLoop->handle();
  const auto demandSourceSizingHandle = removedDemandSourceLoop->sizingPlant().handle();
  const auto demandSourceHeaterHandle = demandSourceHeater->handle();
  const auto demandSourceWaterHeaterSizingHandle = demandSourceHeater->waterHeaterSizing().handle();
  EXPECT_FALSE(removedDemandSourceLoop->remove().empty());
  EXPECT_FALSE(demandSourceModel->getObject(demandSourceLoopHandle));
  EXPECT_FALSE(demandSourceModel->getObject(demandSourceSizingHandle));
  for (const auto& handle : demandSourceTopologyHandles) {
    EXPECT_FALSE(demandSourceModel->getObject(handle));
  }
  ASSERT_TRUE(demandSourceModel->getObject(demandSourceHeaterHandle));
  EXPECT_TRUE(demandSourceModel->getObject(demandSourceWaterHeaterSizingHandle));
  EXPECT_FALSE(demandSourceHeater->sourceSidePlantLoop());
  EXPECT_FALSE(demandSourceHeater->sourceSideInletModelObject());
  EXPECT_FALSE(demandSourceHeater->sourceSideOutletModelObject());
  ASSERT_TRUE(demandSourceHeater->useSidePlantLoop());
  EXPECT_EQ(*demandSourceUseLoop, *demandSourceHeater->useSidePlantLoop());
  EXPECT_EQ(1u, demandSourceUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_TRUE(demandSourceHeater->useSideInletModelObject());
  EXPECT_TRUE(demandSourceHeater->useSideOutletModelObject());
  EXPECT_EQ(demandSourceHeater->handle(), demandSourceHeater->waterHeaterSizing().waterHeater().handle());

  PlantLoop replacementDemandSourceLoop(*demandSourceModel);
  ASSERT_TRUE(replacementDemandSourceLoop.setName("Replacement Demand Water Heater Source Loop"));
  ASSERT_TRUE(replacementDemandSourceLoop.addDemandBranchForComponent(*demandSourceHeater));
  ASSERT_TRUE(demandSourceModel->save(idfPath, true));

  auto completedModel = Model::load(idfPath);
  ASSERT_TRUE(completedModel);
  auto completedUseLoop = completedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Water Heater Use Loop");
  auto completedSourceLoop = completedModel->getConcreteModelObjectByName<PlantLoop>("Replacement Demand Water Heater Source Loop");
  auto completedHeater = completedModel->getConcreteModelObjectByName<WaterHeaterMixed>("Surviving Dual Supply Water Heater");
  ASSERT_TRUE(completedUseLoop);
  ASSERT_TRUE(completedSourceLoop);
  ASSERT_TRUE(completedHeater);
  EXPECT_FALSE(completedModel->getConcreteModelObjectByName<PlantLoop>("Removed Demand Water Heater Source Loop"));
  ASSERT_TRUE(completedHeater->useSidePlantLoop());
  ASSERT_TRUE(completedHeater->sourceSidePlantLoop());
  EXPECT_EQ(*completedUseLoop, *completedHeater->useSidePlantLoop());
  EXPECT_EQ(*completedSourceLoop, *completedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, completedUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_EQ(1u, completedSourceLoop->demandComponents(WaterHeaterMixed::iddObjectType()).size());
  EXPECT_TRUE(completedHeater->useSideInletModelObject());
  EXPECT_TRUE(completedHeater->useSideOutletModelObject());
  EXPECT_TRUE(completedHeater->sourceSideInletModelObject());
  EXPECT_TRUE(completedHeater->sourceSideOutletModelObject());
  EXPECT_EQ(completedHeater->handle(), completedHeater->waterHeaterSizing().waterHeater().handle());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, WaterHeaterMixed_LastOwnerUseLoopRemovalLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-water-heater-mixed-last-owner-use-removal.idf");

  Model model;
  PlantLoop useLoop(model);
  WaterHeaterMixed heater(model);
  ASSERT_TRUE(useLoop.setName("Last Owner Water Heater Use Loop"));
  ASSERT_TRUE(heater.setName("Last Owner Water Heater"));
  ASSERT_TRUE(useLoop.addSupplyBranchForComponent(heater));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedUseLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Water Heater Use Loop");
  auto loadedHeater = loadedModel->getConcreteModelObjectByName<WaterHeaterMixed>("Last Owner Water Heater");
  ASSERT_TRUE(loadedUseLoop);
  ASSERT_TRUE(loadedHeater);
  ASSERT_TRUE(loadedHeater->useSidePlantLoop());
  EXPECT_EQ(*loadedUseLoop, *loadedHeater->useSidePlantLoop());
  EXPECT_FALSE(loadedHeater->sourceSidePlantLoop());
  EXPECT_EQ(1u, loadedUseLoop->supplyComponents(WaterHeaterMixed::iddObjectType()).size());
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
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<PlantLoop>("Last Owner Water Heater Use Loop"));
  EXPECT_FALSE(reloadedModel->getConcreteModelObjectByName<WaterHeaterMixed>("Last Owner Water Heater"));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<WaterHeaterSizing>().empty());

  openstudio::filesystem::remove(idfPath);
}
