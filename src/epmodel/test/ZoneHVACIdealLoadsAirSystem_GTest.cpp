/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_DefaultConstructor) {
  Model model;
  ZoneHVACIdealLoadsAirSystem system(model);

  EXPECT_DOUBLE_EQ(50.0, system.maximumHeatingSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(13.0, system.minimumCoolingSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(0.0156, system.maximumHeatingSupplyAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0077, system.minimumCoolingSupplyAirHumidityRatio());
  EXPECT_EQ("NoLimit", system.heatingLimit());
  EXPECT_FALSE(system.maximumHeatingAirFlowRate());
  EXPECT_FALSE(system.maximumSensibleHeatingCapacity());
  EXPECT_EQ("NoLimit", system.coolingLimit());
  EXPECT_FALSE(system.maximumCoolingAirFlowRate());
  EXPECT_FALSE(system.maximumTotalCoolingCapacity());
  EXPECT_EQ("ConstantSensibleHeatRatio", system.dehumidificationControlType());
  EXPECT_DOUBLE_EQ(0.7, system.coolingSensibleHeatRatio());
  EXPECT_EQ("None", system.humidificationControlType());
  EXPECT_EQ("None", system.demandControlledVentilationType());
  EXPECT_EQ("NoEconomizer", system.outdoorAirEconomizerType());
  EXPECT_EQ("None", system.heatRecoveryType());
  EXPECT_DOUBLE_EQ(0.7, system.sensibleHeatRecoveryEffectiveness());
  EXPECT_DOUBLE_EQ(0.65, system.latentHeatRecoveryEffectiveness());
  EXPECT_EQ("DistrictHeatingWater", system.heatingFuelType());
  EXPECT_EQ("DistrictCooling", system.coolingFuelType());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACIdealLoadsAirSystem system(model);

  EXPECT_TRUE(system.setMaximumHeatingSupplyAirTemperature(60.0));
  EXPECT_DOUBLE_EQ(60.0, system.maximumHeatingSupplyAirTemperature());
  system.resetMaximumHeatingSupplyAirTemperature();
  EXPECT_DOUBLE_EQ(50.0, system.maximumHeatingSupplyAirTemperature());

  EXPECT_TRUE(system.setMinimumCoolingSupplyAirTemperature(11.0));
  EXPECT_DOUBLE_EQ(11.0, system.minimumCoolingSupplyAirTemperature());
  system.resetMinimumCoolingSupplyAirTemperature();
  EXPECT_DOUBLE_EQ(13.0, system.minimumCoolingSupplyAirTemperature());

  EXPECT_TRUE(system.setMaximumHeatingSupplyAirHumidityRatio(0.02));
  EXPECT_DOUBLE_EQ(0.02, system.maximumHeatingSupplyAirHumidityRatio());
  system.resetMaximumHeatingSupplyAirHumidityRatio();
  EXPECT_DOUBLE_EQ(0.0156, system.maximumHeatingSupplyAirHumidityRatio());

  EXPECT_TRUE(system.setMinimumCoolingSupplyAirHumidityRatio(0.006));
  EXPECT_DOUBLE_EQ(0.006, system.minimumCoolingSupplyAirHumidityRatio());
  system.resetMinimumCoolingSupplyAirHumidityRatio();
  EXPECT_DOUBLE_EQ(0.0077, system.minimumCoolingSupplyAirHumidityRatio());

  EXPECT_TRUE(system.setHeatingLimit("LimitCapacity"));
  EXPECT_EQ("LimitCapacity", system.heatingLimit());
  system.resetHeatingLimit();
  EXPECT_EQ("NoLimit", system.heatingLimit());

  EXPECT_TRUE(system.setMaximumHeatingAirFlowRate(0.75));
  ASSERT_TRUE(system.maximumHeatingAirFlowRate());
  EXPECT_DOUBLE_EQ(0.75, system.maximumHeatingAirFlowRate().get());
  EXPECT_FALSE(system.isMaximumHeatingAirFlowRateAutosized());
  system.autosizeMaximumHeatingAirFlowRate();
  EXPECT_TRUE(system.isMaximumHeatingAirFlowRateAutosized());
  EXPECT_FALSE(system.maximumHeatingAirFlowRate());
  system.resetMaximumHeatingAirFlowRate();
  EXPECT_FALSE(system.maximumHeatingAirFlowRate());

  EXPECT_TRUE(system.setMaximumSensibleHeatingCapacity(8800.0));
  ASSERT_TRUE(system.maximumSensibleHeatingCapacity());
  EXPECT_DOUBLE_EQ(8800.0, system.maximumSensibleHeatingCapacity().get());
  system.autosizeMaximumSensibleHeatingCapacity();
  EXPECT_TRUE(system.isMaximumSensibleHeatingCapacityAutosized());
  system.resetMaximumSensibleHeatingCapacity();
  EXPECT_FALSE(system.maximumSensibleHeatingCapacity());

  EXPECT_TRUE(system.setCoolingLimit("LimitFlowRate"));
  EXPECT_EQ("LimitFlowRate", system.coolingLimit());
  system.resetCoolingLimit();
  EXPECT_EQ("NoLimit", system.coolingLimit());

  EXPECT_TRUE(system.setMaximumCoolingAirFlowRate(0.35));
  ASSERT_TRUE(system.maximumCoolingAirFlowRate());
  EXPECT_DOUBLE_EQ(0.35, system.maximumCoolingAirFlowRate().get());
  system.autosizeMaximumCoolingAirFlowRate();
  EXPECT_TRUE(system.isMaximumCoolingAirFlowRateAutosized());
  system.resetMaximumCoolingAirFlowRate();
  EXPECT_FALSE(system.maximumCoolingAirFlowRate());

  EXPECT_TRUE(system.setMaximumTotalCoolingCapacity(4200.0));
  ASSERT_TRUE(system.maximumTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(4200.0, system.maximumTotalCoolingCapacity().get());
  system.autosizeMaximumTotalCoolingCapacity();
  EXPECT_TRUE(system.isMaximumTotalCoolingCapacityAutosized());
  system.resetMaximumTotalCoolingCapacity();
  EXPECT_FALSE(system.maximumTotalCoolingCapacity());

  EXPECT_TRUE(system.setDehumidificationControlType("Humidistat"));
  EXPECT_EQ("Humidistat", system.dehumidificationControlType());
  system.resetDehumidificationControlType();
  EXPECT_EQ("ConstantSensibleHeatRatio", system.dehumidificationControlType());

  EXPECT_TRUE(system.setCoolingSensibleHeatRatio(0.75));
  EXPECT_DOUBLE_EQ(0.75, system.coolingSensibleHeatRatio());
  system.resetCoolingSensibleHeatRatio();
  EXPECT_DOUBLE_EQ(0.7, system.coolingSensibleHeatRatio());

  EXPECT_TRUE(system.setHumidificationControlType("Humidistat"));
  EXPECT_EQ("Humidistat", system.humidificationControlType());
  system.resetHumidificationControlType();
  EXPECT_EQ("None", system.humidificationControlType());

  EXPECT_TRUE(system.setDemandControlledVentilationType("CO2Setpoint"));
  EXPECT_EQ("CO2Setpoint", system.demandControlledVentilationType());
  system.resetDemandControlledVentilationType();
  EXPECT_EQ("None", system.demandControlledVentilationType());

  EXPECT_TRUE(system.setOutdoorAirEconomizerType("DifferentialDryBulb"));
  EXPECT_EQ("DifferentialDryBulb", system.outdoorAirEconomizerType());
  system.resetOutdoorAirEconomizerType();
  EXPECT_EQ("NoEconomizer", system.outdoorAirEconomizerType());

  EXPECT_TRUE(system.setHeatRecoveryType("Sensible"));
  EXPECT_EQ("Sensible", system.heatRecoveryType());
  system.resetHeatRecoveryType();
  EXPECT_EQ("None", system.heatRecoveryType());

  EXPECT_TRUE(system.setSensibleHeatRecoveryEffectiveness(0.85));
  EXPECT_DOUBLE_EQ(0.85, system.sensibleHeatRecoveryEffectiveness());
  system.resetSensibleHeatRecoveryEffectiveness();
  EXPECT_DOUBLE_EQ(0.7, system.sensibleHeatRecoveryEffectiveness());

  EXPECT_TRUE(system.setLatentHeatRecoveryEffectiveness(0.72));
  EXPECT_DOUBLE_EQ(0.72, system.latentHeatRecoveryEffectiveness());
  system.resetLatentHeatRecoveryEffectiveness();
  EXPECT_DOUBLE_EQ(0.65, system.latentHeatRecoveryEffectiveness());

  EXPECT_TRUE(system.setHeatingFuelType("Electricity"));
  EXPECT_EQ("Electricity", system.heatingFuelType());

  EXPECT_TRUE(system.setCoolingFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", system.coolingFuelType());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACIdealLoadsAirSystem system(model);

  EXPECT_FALSE(system.thermalZone());
  EXPECT_TRUE(system.addToThermalZone(zone));
  ASSERT_TRUE(system.thermalZone());
  EXPECT_EQ(zone, *system.thermalZone());

  system.removeFromThermalZone();
  EXPECT_FALSE(system.thermalZone());
}
