/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR.hpp"
#include "../WaterToWaterComponent/ThermalStorageChilledWaterStratified.hpp"

#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/ThermalStorage_ChilledWater_Stratified_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageChilledWaterStratified_DefaultConstructor) {
  Model model;
  ThermalStorageChilledWaterStratified storage(model);
  EXPECT_EQ(ThermalStorageChilledWaterStratified::iddObjectType(), storage.iddObject().type());
  EXPECT_FALSE(storage.nameString().empty());
  EXPECT_EQ(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideInletNodeName, storage.supplyInletPort());
  EXPECT_EQ(openstudio::ThermalStorage_ChilledWater_StratifiedFields::UseSideOutletNodeName, storage.supplyOutletPort());
  EXPECT_EQ(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideInletNodeName, storage.demandInletPort());
  EXPECT_EQ(openstudio::ThermalStorage_ChilledWater_StratifiedFields::SourceSideOutletNodeName, storage.demandOutletPort());
  EXPECT_TRUE(storage.ambientTemperatureSchedule());
  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Cooling), storage.componentType());
  EXPECT_TRUE(storage.coolingFuelTypes().empty());
  EXPECT_TRUE(storage.heatingFuelTypes().empty());
  EXPECT_TRUE(storage.appGHeatingFuelTypes().empty());
  EXPECT_EQ(storage.handle(), storage.waterHeaterSizing().waterHeater().handle());
  ASSERT_EQ(1u, storage.children().size());
  EXPECT_EQ(storage.waterHeaterSizing().handle(), storage.children().front().handle());
  EXPECT_FALSE(storage.autosizedNominalCoolingCapacity());
  EXPECT_FALSE(storage.autosizedUseSideDesignFlowRate());
  EXPECT_FALSE(storage.autosizedSourceSideDesignFlowRate());
}

TEST_F(EPModelFixture, ThermalStorageChilledWaterStratified_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageChilledWaterStratified storage(model);

  EXPECT_TRUE(storage.setTankVolume(100.5));
  EXPECT_DOUBLE_EQ(100.5, storage.tankVolume());

  EXPECT_TRUE(storage.setTankHeight(12.4));
  EXPECT_DOUBLE_EQ(12.4, storage.tankHeight());

  auto tankShapeValues = ThermalStorageChilledWaterStratified::tankShapeValues();
  ASSERT_FALSE(tankShapeValues.empty());
  const auto& tankShapeValue = tankShapeValues.front();
  EXPECT_TRUE(storage.setTankShape(tankShapeValue));
  EXPECT_EQ(tankShapeValue, storage.tankShape());

  EXPECT_TRUE(storage.setTankPerimeter(30.0));
  ASSERT_TRUE(storage.tankPerimeter());
  EXPECT_DOUBLE_EQ(30.0, storage.tankPerimeter().get());
  storage.resetTankPerimeter();
  EXPECT_FALSE(storage.tankPerimeter());

  EXPECT_TRUE(storage.setDeadbandTemperatureDifference(2.0));
  EXPECT_DOUBLE_EQ(2.0, storage.deadbandTemperatureDifference());

  EXPECT_TRUE(storage.setTemperatureSensorHeight(1.5));
  ASSERT_TRUE(storage.temperatureSensorHeight());
  EXPECT_DOUBLE_EQ(1.5, storage.temperatureSensorHeight().get());
  storage.resetTemperatureSensorHeight();
  EXPECT_FALSE(storage.temperatureSensorHeight());

  EXPECT_TRUE(storage.setMinimumTemperatureLimit(4.0));
  ASSERT_TRUE(storage.minimumTemperatureLimit());
  EXPECT_DOUBLE_EQ(4.0, storage.minimumTemperatureLimit().get());
  storage.resetMinimumTemperatureLimit();
  EXPECT_FALSE(storage.minimumTemperatureLimit());

  EXPECT_TRUE(storage.setNominalCoolingCapacity(45000.0));
  ASSERT_TRUE(storage.nominalCoolingCapacity());
  EXPECT_DOUBLE_EQ(45000.0, storage.nominalCoolingCapacity().get());
  EXPECT_FALSE(storage.isNominalCoolingCapacityAutosized());
  storage.autosizeNominalCoolingCapacity();
  EXPECT_TRUE(storage.isNominalCoolingCapacityAutosized());

  auto ambientIndicatorValues = ThermalStorageChilledWaterStratified::ambientTemperatureIndicatorValues();
  ASSERT_FALSE(ambientIndicatorValues.empty());
  const auto& ambientIndicatorValue = ambientIndicatorValues.front();
  EXPECT_TRUE(storage.setAmbientTemperatureIndicator(ambientIndicatorValue));
  EXPECT_EQ(ambientIndicatorValue, storage.ambientTemperatureIndicator());

  EXPECT_TRUE(storage.setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(0.35));
  ASSERT_TRUE(storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature());
  EXPECT_DOUBLE_EQ(0.35, storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature().get());
  storage.resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();
  EXPECT_FALSE(storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature());

  EXPECT_TRUE(storage.setUseSideHeatTransferEffectiveness(0.76));
  EXPECT_DOUBLE_EQ(0.76, storage.useSideHeatTransferEffectiveness());
  storage.resetUseSideHeatTransferEffectiveness();
  EXPECT_TRUE(storage.isUseSideHeatTransferEffectivenessDefaulted());

  EXPECT_TRUE(storage.setUseSideInletHeight(2.6));
  ASSERT_TRUE(storage.useSideInletHeight());
  EXPECT_DOUBLE_EQ(2.6, storage.useSideInletHeight().get());
  storage.autocalculateUseSideInletHeight();
  EXPECT_TRUE(storage.isUseSideInletHeightAutocalculated());

  EXPECT_TRUE(storage.setUseSideOutletHeight(3.2));
  EXPECT_DOUBLE_EQ(3.2, storage.useSideOutletHeight());

  EXPECT_TRUE(storage.setUseSideDesignFlowRate(0.012));
  ASSERT_TRUE(storage.useSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.012, storage.useSideDesignFlowRate().get());
  EXPECT_FALSE(storage.isUseSideDesignFlowRateAutosized());
  storage.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateAutosized());
  storage.resetUseSideDesignFlowRate();
  EXPECT_TRUE(storage.isUseSideDesignFlowRateDefaulted());

  EXPECT_TRUE(storage.setSourceSideHeatTransferEffectiveness(0.88));
  EXPECT_DOUBLE_EQ(0.88, storage.sourceSideHeatTransferEffectiveness());
  storage.resetSourceSideHeatTransferEffectiveness();
  EXPECT_TRUE(storage.isSourceSideHeatTransferEffectivenessDefaulted());

  EXPECT_TRUE(storage.setSourceSideInletHeight(2.2));
  EXPECT_DOUBLE_EQ(2.2, storage.sourceSideInletHeight());

  EXPECT_TRUE(storage.setSourceSideOutletHeight(3.8));
  ASSERT_TRUE(storage.sourceSideOutletHeight());
  EXPECT_DOUBLE_EQ(3.8, storage.sourceSideOutletHeight().get());
  storage.autocalculateSourceSideOutletHeight();
  EXPECT_TRUE(storage.isSourceSideOutletHeightAutocalculated());

  EXPECT_TRUE(storage.setSourceSideDesignFlowRate(0.018));
  ASSERT_TRUE(storage.sourceSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.018, storage.sourceSideDesignFlowRate().get());
  storage.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(storage.isSourceSideDesignFlowRateAutosized());
  storage.resetSourceSideDesignFlowRate();
  EXPECT_TRUE(storage.isSourceSideDesignFlowRateDefaulted());

  EXPECT_TRUE(storage.setTankRecoveryTime(2600.0));
  EXPECT_DOUBLE_EQ(2600.0, storage.tankRecoveryTime());

  auto inletModeValues = ThermalStorageChilledWaterStratified::inletModeValues();
  ASSERT_FALSE(inletModeValues.empty());
  const auto& inletModeValue = inletModeValues.front();
  EXPECT_TRUE(storage.setInletMode(inletModeValue));
  EXPECT_EQ(inletModeValue, storage.inletMode());

  EXPECT_TRUE(storage.setNumberofNodes(10));
  EXPECT_EQ(10, storage.numberofNodes());

  EXPECT_TRUE(storage.setAdditionalDestratificationConductivity(1.25));
  EXPECT_DOUBLE_EQ(1.25, storage.additionalDestratificationConductivity());

  EXPECT_TRUE(storage.setNode1AdditionalLossCoefficient(0.1));
  EXPECT_DOUBLE_EQ(0.1, storage.node1AdditionalLossCoefficient());
  EXPECT_TRUE(storage.setNode10AdditionalLossCoefficient(0.55));
  EXPECT_DOUBLE_EQ(0.55, storage.node10AdditionalLossCoefficient());
}

TEST_F(EPModelFixture, ThermalStorageChilledWaterStratified_RelationshipAccessors_RoundTrip) {
  Model model;
  ThermalStorageChilledWaterStratified storage(model);

  ScheduleConstant setpoint(model);
  ScheduleConstant ambient(model);
  ScheduleConstant useSide(model);
  ScheduleConstant sourceSide(model);
  ThermalZone zone(model);

  ASSERT_TRUE(setpoint.setValue(7.0));
  ASSERT_TRUE(ambient.setValue(21.0));
  ASSERT_TRUE(useSide.setValue(1.0));
  ASSERT_TRUE(sourceSide.setValue(0.0));

  EXPECT_TRUE(storage.setSetpointTemperatureSchedule(setpoint));
  ASSERT_TRUE(storage.setpointTemperatureSchedule());
  EXPECT_EQ(setpoint.handle(), storage.setpointTemperatureSchedule()->handle());
  storage.resetSetpointTemperatureSchedule();
  EXPECT_FALSE(storage.setpointTemperatureSchedule());

  EXPECT_TRUE(storage.setAmbientTemperatureSchedule(ambient));
  ASSERT_TRUE(storage.ambientTemperatureSchedule());
  EXPECT_EQ(ambient.handle(), storage.ambientTemperatureSchedule()->handle());
  storage.resetAmbientTemperatureSchedule();
  EXPECT_FALSE(storage.ambientTemperatureSchedule());

  EXPECT_TRUE(storage.setAmbientTemperatureThermalZone(zone));
  ASSERT_TRUE(storage.ambientTemperatureThermalZone());
  EXPECT_EQ(zone.handle(), storage.ambientTemperatureThermalZone()->handle());
  storage.resetAmbientTemperatureThermalZone();
  EXPECT_FALSE(storage.ambientTemperatureThermalZone());

  EXPECT_TRUE(storage.setAmbientTemperatureOutdoorAirNodeName("Storage Ambient OA Node"));
  ASSERT_TRUE(storage.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ("Storage Ambient OA Node", storage.ambientTemperatureOutdoorAirNodeName().get());
  storage.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_FALSE(storage.ambientTemperatureOutdoorAirNodeName());

  EXPECT_TRUE(storage.setUseSideAvailabilitySchedule(useSide));
  ASSERT_TRUE(storage.useSideAvailabilitySchedule());
  EXPECT_EQ(useSide.handle(), storage.useSideAvailabilitySchedule()->handle());
  storage.resetUseSideAvailabilitySchedule();
  EXPECT_FALSE(storage.useSideAvailabilitySchedule());

  EXPECT_TRUE(storage.setSourceSideAvailabilitySchedule(sourceSide));
  ASSERT_TRUE(storage.sourceSideAvailabilitySchedule());
  EXPECT_EQ(sourceSide.handle(), storage.sourceSideAvailabilitySchedule()->handle());
  storage.resetSourceSideAvailabilitySchedule();
  EXPECT_FALSE(storage.sourceSideAvailabilitySchedule());

  WaterHeaterSizing sizing = storage.waterHeaterSizing();
  EXPECT_EQ(storage.handle(), sizing.waterHeater().handle());
}

TEST_F(EPModelFixture, ThermalStorageChilledWaterStratified_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop useSideLoop(model);
  PlantLoop sourceSideLoop(model);
  PlantLoop loadLoop(model);
  ChillerElectricEIR chiller(model);
  ThermalStorageChilledWaterStratified storage(model);

  EXPECT_TRUE(useSideLoop.addSupplyBranchForComponent(storage));
  ASSERT_TRUE(storage.plantLoop());
  EXPECT_EQ(useSideLoop.handle(), storage.plantLoop()->handle());
  EXPECT_FALSE(storage.secondaryPlantLoop());
  ASSERT_TRUE(storage.supplyInletModelObject());
  ASSERT_TRUE(storage.supplyOutletModelObject());
  EXPECT_FALSE(storage.demandInletModelObject());
  EXPECT_FALSE(storage.demandOutletModelObject());
  EXPECT_EQ(useSideLoop.handle(), storage.supplyInletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(useSideLoop.handle(), storage.supplyOutletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Cooling), storage.componentType());
  EXPECT_TRUE(storage.coolingFuelTypes().empty());
  EXPECT_TRUE(storage.heatingFuelTypes().empty());
  EXPECT_TRUE(storage.appGHeatingFuelTypes().empty());

  EXPECT_TRUE(sourceSideLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(storage.secondaryPlantLoop());
  EXPECT_EQ(sourceSideLoop.handle(), storage.secondaryPlantLoop()->handle());
  ASSERT_TRUE(storage.demandInletModelObject());
  ASSERT_TRUE(storage.demandOutletModelObject());
  EXPECT_EQ(sourceSideLoop.handle(), storage.demandInletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(sourceSideLoop.handle(), storage.demandOutletModelObject()->cast<Node>().plantLoop()->handle());

  EXPECT_TRUE(loadLoop.addSupplyBranchForComponent(chiller));
  EXPECT_TRUE(loadLoop.addDemandBranchForComponent(storage));
  ASSERT_TRUE(storage.plantLoop());
  EXPECT_EQ(useSideLoop.handle(), storage.plantLoop()->handle());
  ASSERT_TRUE(storage.secondaryPlantLoop());
  EXPECT_EQ(loadLoop.handle(), storage.secondaryPlantLoop()->handle());
  EXPECT_EQ(loadLoop.coolingFuelTypes(), storage.coolingFuelTypes());
  EXPECT_TRUE(storage.heatingFuelTypes().empty());
  EXPECT_TRUE(storage.appGHeatingFuelTypes().empty());

  EXPECT_TRUE(storage.removeFromSecondaryPlantLoop());
  EXPECT_FALSE(storage.secondaryPlantLoop());
  EXPECT_FALSE(storage.demandInletModelObject());
  EXPECT_FALSE(storage.demandOutletModelObject());
  EXPECT_TRUE(storage.coolingFuelTypes().empty());
}
