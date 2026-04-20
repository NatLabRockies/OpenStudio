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
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToWaterComponent/WaterHeaterMixed.hpp"

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
  EXPECT_EQ(std::vector<openstudio::AppGFuelType>{openstudio::convertFuelTypeToAppG(openstudio::FuelType::Gas)},
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
