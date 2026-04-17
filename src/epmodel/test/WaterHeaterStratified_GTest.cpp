/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../WaterToWaterComponent/WaterHeaterStratified.hpp"

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
