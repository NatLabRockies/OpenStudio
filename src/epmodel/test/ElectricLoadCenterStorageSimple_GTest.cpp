/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ElectricalStorage/ElectricLoadCenterStorageSimple.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterStorageSimple_DefaultConstructor) {
  Model model;
  ElectricLoadCenterStorageSimple storage(model);
  EXPECT_EQ(ElectricLoadCenterStorageSimple::iddObjectType(), storage.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterStorageSimple_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterStorageSimple storage(model);

  EXPECT_TRUE(storage.isRadiativeFractionforZoneHeatGainsDefaulted());
  EXPECT_DOUBLE_EQ(0.0, storage.radiativeFractionforZoneHeatGains());
  EXPECT_TRUE(storage.setRadiativeFractionforZoneHeatGains(0.25));
  EXPECT_DOUBLE_EQ(0.25, storage.radiativeFractionforZoneHeatGains());
  storage.resetRadiativeFractionforZoneHeatGains();
  EXPECT_TRUE(storage.isRadiativeFractionforZoneHeatGainsDefaulted());

  EXPECT_FALSE(storage.isNominalEnergeticEfficiencyforChargingDefaulted());
  EXPECT_DOUBLE_EQ(0.8, storage.nominalEnergeticEfficiencyforCharging());
  EXPECT_TRUE(storage.setNominalEnergeticEfficiencyforCharging(0.9));
  EXPECT_DOUBLE_EQ(0.9, storage.nominalEnergeticEfficiencyforCharging());
  storage.resetNominalEnergeticEfficiencyforCharging();
  EXPECT_TRUE(storage.isNominalEnergeticEfficiencyforChargingDefaulted());

  EXPECT_FALSE(storage.isNominalDischargingEnergeticEfficiencyDefaulted());
  EXPECT_DOUBLE_EQ(0.8, storage.nominalDischargingEnergeticEfficiency());
  EXPECT_TRUE(storage.setNominalDischargingEnergeticEfficiency(0.88));
  EXPECT_DOUBLE_EQ(0.88, storage.nominalDischargingEnergeticEfficiency());
  storage.resetNominalDischargingEnergeticEfficiency();
  EXPECT_TRUE(storage.isNominalDischargingEnergeticEfficiencyDefaulted());

  EXPECT_TRUE(storage.setMaximumStorageCapacity(2000000.0));
  EXPECT_DOUBLE_EQ(2000000.0, storage.maximumStorageCapacity());

  EXPECT_TRUE(storage.setMaximumPowerforDischarging(400000.0));
  EXPECT_DOUBLE_EQ(400000.0, storage.maximumPowerforDischarging());

  EXPECT_TRUE(storage.setMaximumPowerforCharging(350000.0));
  EXPECT_DOUBLE_EQ(350000.0, storage.maximumPowerforCharging());

  EXPECT_TRUE(storage.isInitialStateofChargeDefaulted());
  EXPECT_DOUBLE_EQ(1000000.0, storage.initialStateofCharge());
  EXPECT_TRUE(storage.setInitialStateofCharge(750000.0));
  EXPECT_DOUBLE_EQ(750000.0, storage.initialStateofCharge());
  storage.resetInitialStateofCharge();
  EXPECT_TRUE(storage.isInitialStateofChargeDefaulted());
  EXPECT_DOUBLE_EQ(1000000.0, storage.initialStateofCharge());
}
