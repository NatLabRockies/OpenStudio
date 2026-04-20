/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../ModelObject/WaterHeaterSizing_Impl.hpp"
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
