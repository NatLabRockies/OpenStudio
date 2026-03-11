/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ElectricLoadCenterStorageBattery.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterStorageBattery_DefaultConstructor) {
  Model model;
  ElectricLoadCenterStorageBattery battery(model);
  EXPECT_EQ(ElectricLoadCenterStorageBattery::iddObjectType(), battery.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterStorageBattery_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterStorageBattery battery(model);

  EXPECT_TRUE(battery.isRadiativeFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, battery.radiativeFraction());
  EXPECT_TRUE(battery.setRadiativeFraction(0.3));
  EXPECT_DOUBLE_EQ(0.3, battery.radiativeFraction());
  battery.resetRadiativeFraction();
  EXPECT_TRUE(battery.isRadiativeFractionDefaulted());

  EXPECT_TRUE(battery.isNumberofBatteryModulesinParallelDefaulted());
  EXPECT_EQ(1, battery.numberofBatteryModulesinParallel());
  EXPECT_TRUE(battery.setNumberofBatteryModulesinParallel(8));
  EXPECT_EQ(8, battery.numberofBatteryModulesinParallel());

  EXPECT_TRUE(battery.isNumberofBatteryModulesinSeriesDefaulted());
  EXPECT_EQ(1, battery.numberofBatteryModulesinSeries());
  EXPECT_TRUE(battery.setNumberofBatteryModulesinSeries(24));
  EXPECT_EQ(24, battery.numberofBatteryModulesinSeries());

  EXPECT_FALSE(battery.maximumModuleCapacity());
  EXPECT_TRUE(battery.setMaximumModuleCapacity(120.0));
  ASSERT_TRUE(battery.maximumModuleCapacity());
  EXPECT_DOUBLE_EQ(120.0, *battery.maximumModuleCapacity());
  battery.resetMaximumModuleCapacity();
  EXPECT_FALSE(battery.maximumModuleCapacity());

  EXPECT_TRUE(battery.isInitialFractionalStateofChargeDefaulted());
  EXPECT_DOUBLE_EQ(1.0, battery.initialFractionalStateofCharge());
  EXPECT_TRUE(battery.setInitialFractionalStateofCharge(0.75));
  EXPECT_DOUBLE_EQ(0.75, battery.initialFractionalStateofCharge());

  EXPECT_FALSE(battery.fractionofAvailableChargeCapacity());
  EXPECT_TRUE(battery.setFractionofAvailableChargeCapacity(0.82));
  ASSERT_TRUE(battery.fractionofAvailableChargeCapacity());
  EXPECT_DOUBLE_EQ(0.82, *battery.fractionofAvailableChargeCapacity());

  EXPECT_FALSE(battery.changeRatefromBoundChargetoAvailableCharge());
  EXPECT_TRUE(battery.setChangeRatefromBoundChargetoAvailableCharge(0.15));
  ASSERT_TRUE(battery.changeRatefromBoundChargetoAvailableCharge());
  EXPECT_DOUBLE_EQ(0.15, *battery.changeRatefromBoundChargetoAvailableCharge());

  EXPECT_FALSE(battery.fullyChargedModuleOpenCircuitVoltage());
  EXPECT_TRUE(battery.setFullyChargedModuleOpenCircuitVoltage(54.2));
  ASSERT_TRUE(battery.fullyChargedModuleOpenCircuitVoltage());
  EXPECT_DOUBLE_EQ(54.2, *battery.fullyChargedModuleOpenCircuitVoltage());

  EXPECT_FALSE(battery.fullyDischargedModuleOpenCircuitVoltage());
  EXPECT_TRUE(battery.setFullyDischargedModuleOpenCircuitVoltage(42.5));
  ASSERT_TRUE(battery.fullyDischargedModuleOpenCircuitVoltage());
  EXPECT_DOUBLE_EQ(42.5, *battery.fullyDischargedModuleOpenCircuitVoltage());

  EXPECT_FALSE(battery.moduleInternalElectricalResistance());
  EXPECT_TRUE(battery.setModuleInternalElectricalResistance(0.005));
  ASSERT_TRUE(battery.moduleInternalElectricalResistance());
  EXPECT_DOUBLE_EQ(0.005, *battery.moduleInternalElectricalResistance());

  EXPECT_FALSE(battery.maximumModuleDischargingCurrent());
  EXPECT_TRUE(battery.setMaximumModuleDischargingCurrent(120.0));
  ASSERT_TRUE(battery.maximumModuleDischargingCurrent());
  EXPECT_DOUBLE_EQ(120.0, *battery.maximumModuleDischargingCurrent());

  EXPECT_FALSE(battery.moduleCutoffVoltage());
  EXPECT_TRUE(battery.setModuleCutoffVoltage(41.0));
  ASSERT_TRUE(battery.moduleCutoffVoltage());
  EXPECT_DOUBLE_EQ(41.0, *battery.moduleCutoffVoltage());

  EXPECT_TRUE(battery.isModuleChargeRateLimitDefaulted());
  EXPECT_DOUBLE_EQ(1.0, battery.moduleChargeRateLimit());
  EXPECT_TRUE(battery.setModuleChargeRateLimit(0.8));
  EXPECT_DOUBLE_EQ(0.8, battery.moduleChargeRateLimit());

  EXPECT_TRUE(battery.isBatteryLifeCalculationDefaulted());
  EXPECT_FALSE(battery.batteryLifeCalculation());
  EXPECT_TRUE(battery.setBatteryLifeCalculation(true));
  EXPECT_TRUE(battery.batteryLifeCalculation());
  battery.resetBatteryLifeCalculation();
  EXPECT_TRUE(battery.isBatteryLifeCalculationDefaulted());

  EXPECT_TRUE(battery.isNumberofCycleBinsDefaulted());
  EXPECT_EQ(10, battery.numberofCycleBins());
  EXPECT_TRUE(battery.setNumberofCycleBins(25));
  EXPECT_EQ(25, battery.numberofCycleBins());

  battery.resetFractionofAvailableChargeCapacity();
  EXPECT_FALSE(battery.fractionofAvailableChargeCapacity());
  battery.resetChangeRatefromBoundChargetoAvailableCharge();
  EXPECT_FALSE(battery.changeRatefromBoundChargetoAvailableCharge());
  battery.resetFullyChargedModuleOpenCircuitVoltage();
  EXPECT_FALSE(battery.fullyChargedModuleOpenCircuitVoltage());
  battery.resetFullyDischargedModuleOpenCircuitVoltage();
  EXPECT_FALSE(battery.fullyDischargedModuleOpenCircuitVoltage());
  battery.resetModuleInternalElectricalResistance();
  EXPECT_FALSE(battery.moduleInternalElectricalResistance());
  battery.resetMaximumModuleDischargingCurrent();
  EXPECT_FALSE(battery.maximumModuleDischargingCurrent());
  battery.resetModuleCutoffVoltage();
  EXPECT_FALSE(battery.moduleCutoffVoltage());
}
