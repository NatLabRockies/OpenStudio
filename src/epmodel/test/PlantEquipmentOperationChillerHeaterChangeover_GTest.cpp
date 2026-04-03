/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationChillerHeaterChangeover.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationChillerHeaterChangeover_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationChillerHeaterChangeover changeover(model);
  EXPECT_EQ(PlantEquipmentOperationChillerHeaterChangeover::iddObjectType(), changeover.iddObject().type());
  EXPECT_DOUBLE_EQ(7.0, changeover.primaryCoolingPlantSetpointTemperature());
  EXPECT_DOUBLE_EQ(55.0, changeover.primaryHeatingPlantSetpointatOutdoorHighTemperature());
  EXPECT_DOUBLE_EQ(30.0, changeover.outdoorHighTemperature());
  EXPECT_DOUBLE_EQ(35.0, changeover.primaryHeatingPlantSetpointatOutdoorLowTemperature());
  EXPECT_DOUBLE_EQ(0.0, changeover.outdoorLowTemperature());
  EXPECT_FALSE(changeover.secondaryDistributionCoolingPlantSetpointTemperature());
  EXPECT_FALSE(changeover.secondaryDistributionHeatingPlantSetpointTemperature());
  EXPECT_TRUE(changeover.isBoilerSetpointTemperatureOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.5, changeover.boilerSetpointTemperatureOffset());
  EXPECT_FALSE(changeover.primaryHeatingPlantSetpointatBackupOutdoorLowTemperature());
  EXPECT_FALSE(changeover.backupOutdoorLowTemperature());
}

TEST_F(EPModelFixture, PlantEquipmentOperationChillerHeaterChangeover_ScalarAccessors_RoundTrip) {
  Model model;
  PlantEquipmentOperationChillerHeaterChangeover changeover(model);

  EXPECT_TRUE(changeover.setPrimaryCoolingPlantSetpointTemperature(6.3));
  EXPECT_TRUE(changeover.setSecondaryDistributionCoolingPlantSetpointTemperature(9.5));
  EXPECT_TRUE(changeover.setPrimaryHeatingPlantSetpointatOutdoorHighTemperature(60.1));
  EXPECT_TRUE(changeover.setOutdoorHighTemperature(32.0));
  EXPECT_TRUE(changeover.setPrimaryHeatingPlantSetpointatOutdoorLowTemperature(34.0));
  EXPECT_TRUE(changeover.setOutdoorLowTemperature(-2.5));
  EXPECT_TRUE(changeover.setSecondaryDistributionHeatingPlantSetpointTemperature(42.0));
  EXPECT_TRUE(changeover.setBoilerSetpointTemperatureOffset(1.25));
  EXPECT_FALSE(changeover.isBoilerSetpointTemperatureOffsetDefaulted());
  EXPECT_TRUE(changeover.setPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature(33.2));
  EXPECT_TRUE(changeover.setBackupOutdoorLowTemperature(-4.5));

  EXPECT_DOUBLE_EQ(6.3, changeover.primaryCoolingPlantSetpointTemperature());
  auto secondaryCooling = changeover.secondaryDistributionCoolingPlantSetpointTemperature();
  ASSERT_TRUE(secondaryCooling);
  EXPECT_DOUBLE_EQ(9.5, *secondaryCooling);
  EXPECT_DOUBLE_EQ(60.1, changeover.primaryHeatingPlantSetpointatOutdoorHighTemperature());
  EXPECT_DOUBLE_EQ(32.0, changeover.outdoorHighTemperature());
  EXPECT_DOUBLE_EQ(34.0, changeover.primaryHeatingPlantSetpointatOutdoorLowTemperature());
  EXPECT_DOUBLE_EQ(-2.5, changeover.outdoorLowTemperature());
  auto secondaryHeating = changeover.secondaryDistributionHeatingPlantSetpointTemperature();
  ASSERT_TRUE(secondaryHeating);
  EXPECT_DOUBLE_EQ(42.0, *secondaryHeating);
  EXPECT_DOUBLE_EQ(1.25, changeover.boilerSetpointTemperatureOffset());
  EXPECT_FALSE(changeover.isBoilerSetpointTemperatureOffsetDefaulted());
  auto backupSetpoint = changeover.primaryHeatingPlantSetpointatBackupOutdoorLowTemperature();
  ASSERT_TRUE(backupSetpoint);
  EXPECT_DOUBLE_EQ(33.2, *backupSetpoint);
  auto backupLow = changeover.backupOutdoorLowTemperature();
  ASSERT_TRUE(backupLow);
  EXPECT_DOUBLE_EQ(-4.5, *backupLow);

  changeover.resetSecondaryDistributionCoolingPlantSetpointTemperature();
  EXPECT_FALSE(changeover.secondaryDistributionCoolingPlantSetpointTemperature());
  changeover.resetSecondaryDistributionHeatingPlantSetpointTemperature();
  EXPECT_FALSE(changeover.secondaryDistributionHeatingPlantSetpointTemperature());
  changeover.resetPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature();
  EXPECT_FALSE(changeover.primaryHeatingPlantSetpointatBackupOutdoorLowTemperature());
  changeover.resetBackupOutdoorLowTemperature();
  EXPECT_FALSE(changeover.backupOutdoorLowTemperature());
  changeover.resetBoilerSetpointTemperatureOffset();
  EXPECT_TRUE(changeover.isBoilerSetpointTemperatureOffsetDefaulted());
  EXPECT_DOUBLE_EQ(0.5, changeover.boilerSetpointTemperatureOffset());
}
