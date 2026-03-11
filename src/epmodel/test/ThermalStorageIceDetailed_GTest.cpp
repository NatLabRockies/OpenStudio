/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/ThermalStorageIceDetailed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageIceDetailed_DefaultConstructor) {
  Model model;
  ThermalStorageIceDetailed storage(model);
  EXPECT_FALSE(ThermalStorageIceDetailed::iddObjectType().valueName().empty());
}

TEST_F(EPModelFixture, ThermalStorageIceDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageIceDetailed storage(model);

  EXPECT_TRUE(storage.setCapacity(2.2));
  EXPECT_DOUBLE_EQ(2.2, storage.capacity());
  EXPECT_FALSE(storage.isCapacityAutosized());
  storage.autosizeCapacity();
  EXPECT_TRUE(storage.isCapacityAutosized());

  auto dischargingValues = ThermalStorageIceDetailed::dischargingCurveVariableSpecificationsValues();
  ASSERT_FALSE(dischargingValues.empty());
  const auto& dischargingValue = dischargingValues.front();
  EXPECT_TRUE(storage.setDischargingCurveVariableSpecifications(dischargingValue));
  EXPECT_EQ(dischargingValue, storage.dischargingCurveVariableSpecifications());

  auto chargingValues = ThermalStorageIceDetailed::chargingCurveVariableSpecificationsValues();
  ASSERT_FALSE(chargingValues.empty());
  const auto& chargingValue = chargingValues.front();
  EXPECT_TRUE(storage.setChargingCurveVariableSpecifications(chargingValue));
  EXPECT_EQ(chargingValue, storage.chargingCurveVariableSpecifications());

  EXPECT_TRUE(storage.setTimestepoftheCurveData(1.25));
  ASSERT_TRUE(storage.timestepoftheCurveData());
  EXPECT_DOUBLE_EQ(1.25, storage.timestepoftheCurveData().get());
  storage.resetTimestepoftheCurveData();
  EXPECT_FALSE(storage.timestepoftheCurveData());

  EXPECT_TRUE(storage.setParasiticElectricLoadDuringDischarging(0.12));
  ASSERT_TRUE(storage.parasiticElectricLoadDuringDischarging());
  EXPECT_DOUBLE_EQ(0.12, storage.parasiticElectricLoadDuringDischarging().get());
  storage.resetParasiticElectricLoadDuringDischarging();
  EXPECT_FALSE(storage.parasiticElectricLoadDuringDischarging());

  EXPECT_TRUE(storage.setParasiticElectricLoadDuringCharging(0.05));
  ASSERT_TRUE(storage.parasiticElectricLoadDuringCharging());
  EXPECT_DOUBLE_EQ(0.05, storage.parasiticElectricLoadDuringCharging().get());
  storage.resetParasiticElectricLoadDuringCharging();
  EXPECT_FALSE(storage.parasiticElectricLoadDuringCharging());

  EXPECT_TRUE(storage.setTankLossCoefficient(0.02));
  ASSERT_TRUE(storage.tankLossCoefficient());
  EXPECT_DOUBLE_EQ(0.02, storage.tankLossCoefficient().get());
  storage.resetTankLossCoefficient();
  EXPECT_FALSE(storage.tankLossCoefficient());

  EXPECT_TRUE(storage.setFreezingTemperatureofStorageMedium(-3.0));
  EXPECT_DOUBLE_EQ(-3.0, storage.freezingTemperatureofStorageMedium());
  storage.resetFreezingTemperatureofStorageMedium();
  EXPECT_TRUE(storage.isFreezingTemperatureofStorageMediumDefaulted());

  auto thawValues = ThermalStorageIceDetailed::thawProcessIndicatorValues();
  ASSERT_FALSE(thawValues.empty());
  const auto& thawValue = thawValues.front();
  EXPECT_TRUE(storage.setThawProcessIndicator(thawValue));
  EXPECT_EQ(thawValue, storage.thawProcessIndicator());
  storage.resetThawProcessIndicator();
  EXPECT_TRUE(storage.isThawProcessIndicatorDefaulted());
}
