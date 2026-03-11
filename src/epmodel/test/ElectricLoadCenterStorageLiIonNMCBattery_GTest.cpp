/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ElectricalStorage/ElectricLoadCenterStorageLiIonNMCBattery.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterStorageLiIonNMCBattery_DefaultConstructor) {
  Model model;
  ElectricLoadCenterStorageLiIonNMCBattery battery(model);

  EXPECT_EQ(ElectricLoadCenterStorageLiIonNMCBattery::iddObjectType(), battery.iddObject().type());
  EXPECT_EQ(139, battery.numberofCellsinSeries());
  EXPECT_EQ(25, battery.numberofStringsinParallel());
  EXPECT_DOUBLE_EQ(342.0, battery.batteryMass());
  EXPECT_DOUBLE_EQ(4.26, battery.batterySurfaceArea());
}

TEST_F(EPModelFixture, ElectricLoadCenterStorageLiIonNMCBattery_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterStorageLiIonNMCBattery battery(model, 120, 18, 400.0, 5.1);

  const auto lifetimeValues = ElectricLoadCenterStorageLiIonNMCBattery::lifetimeModelValues();
  EXPECT_FALSE(lifetimeValues.empty());

  EXPECT_EQ(120, battery.numberofCellsinSeries());
  EXPECT_EQ(18, battery.numberofStringsinParallel());
  EXPECT_DOUBLE_EQ(400.0, battery.batteryMass());
  EXPECT_DOUBLE_EQ(5.1, battery.batterySurfaceArea());

  EXPECT_TRUE(battery.setRadiativeFraction(0.33));
  EXPECT_DOUBLE_EQ(0.33, battery.radiativeFraction());

  EXPECT_TRUE(battery.setLifetimeModel(lifetimeValues.front()));
  EXPECT_EQ(lifetimeValues.front(), battery.lifetimeModel());

  EXPECT_TRUE(battery.setInitialFractionalStateofCharge(0.65));
  EXPECT_DOUBLE_EQ(0.65, battery.initialFractionalStateofCharge());

  EXPECT_TRUE(battery.setDCtoDCChargingEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, battery.dctoDCChargingEfficiency());

  EXPECT_TRUE(battery.setBatterySpecificHeatCapacity(1800.0));
  EXPECT_DOUBLE_EQ(1800.0, battery.batterySpecificHeatCapacity());

  EXPECT_TRUE(battery.setHeatTransferCoefficientBetweenBatteryandAmbient(9.0));
  EXPECT_DOUBLE_EQ(9.0, battery.heatTransferCoefficientBetweenBatteryandAmbient());

  EXPECT_TRUE(battery.setFullyChargedCellVoltage(4.1));
  EXPECT_DOUBLE_EQ(4.1, battery.fullyChargedCellVoltage());

  EXPECT_TRUE(battery.setCellVoltageatEndofExponentialZone(3.5));
  EXPECT_DOUBLE_EQ(3.5, battery.cellVoltageatEndofExponentialZone());

  EXPECT_TRUE(battery.setCellVoltageatEndofNominalZone(3.31));
  EXPECT_DOUBLE_EQ(3.31, battery.cellVoltageatEndofNominalZone());

  EXPECT_TRUE(battery.setDefaultNominalCellVoltage(3.29));
  EXPECT_DOUBLE_EQ(3.29, battery.defaultNominalCellVoltage());

  EXPECT_TRUE(battery.setFullyChargedCellCapacity(3.4));
  EXPECT_DOUBLE_EQ(3.4, battery.fullyChargedCellCapacity());

  EXPECT_TRUE(battery.setFractionofCellCapacityRemovedattheEndofExponentialZone(0.81));
  EXPECT_DOUBLE_EQ(0.81, battery.fractionofCellCapacityRemovedattheEndofExponentialZone());

  EXPECT_TRUE(battery.setFractionofCellCapacityRemovedattheEndofNominalZone(0.98));
  EXPECT_DOUBLE_EQ(0.98, battery.fractionofCellCapacityRemovedattheEndofNominalZone());

  EXPECT_TRUE(battery.setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(1.25));
  EXPECT_DOUBLE_EQ(1.25, battery.chargeRateatWhichVoltagevsCapacityCurveWasGenerated());

  EXPECT_TRUE(battery.setBatteryCellInternalElectricalResistance(0.11));
  EXPECT_DOUBLE_EQ(0.11, battery.batteryCellInternalElectricalResistance());
}
