/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/ElectricLoadCenterDistribution.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterDistribution_DefaultConstructor) {
  Model model;
  ElectricLoadCenterDistribution elcd(model);
  EXPECT_EQ(ElectricLoadCenterDistribution::iddObjectType(), elcd.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterDistribution_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterDistribution elcd(model);

  const auto generatorOperationSchemeValues = ElectricLoadCenterDistribution::generatorOperationSchemeTypeValues();
  ASSERT_FALSE(generatorOperationSchemeValues.empty());
  ASSERT_TRUE(elcd.setGeneratorOperationSchemeType(generatorOperationSchemeValues.front()));
  EXPECT_EQ(generatorOperationSchemeValues.front(), elcd.generatorOperationSchemeType());

  const auto electricalBussTypeValues = ElectricLoadCenterDistribution::electricalBussTypeValues();
  ASSERT_FALSE(electricalBussTypeValues.empty());
  ASSERT_TRUE(elcd.setElectricalBussType(electricalBussTypeValues.front()));
  EXPECT_EQ(electricalBussTypeValues.front(), elcd.electricalBussType());

  const auto storageOperationSchemeValues = ElectricLoadCenterDistribution::storageOperationSchemeValues();
  ASSERT_FALSE(storageOperationSchemeValues.empty());
  ASSERT_TRUE(elcd.setStorageOperationScheme(storageOperationSchemeValues.front()));
  EXPECT_EQ(storageOperationSchemeValues.front(), elcd.storageOperationScheme());

  EXPECT_TRUE(elcd.setDemandLimitSchemePurchasedElectricDemandLimit(5400.0));
  ASSERT_TRUE(elcd.demandLimitSchemePurchasedElectricDemandLimit());
  EXPECT_DOUBLE_EQ(5400.0, *elcd.demandLimitSchemePurchasedElectricDemandLimit());

  EXPECT_TRUE(elcd.setTrackMeterSchemeMeterName("Electricity:Facility"));
  ASSERT_TRUE(elcd.trackMeterSchemeMeterName());
  EXPECT_EQ("Electricity:Facility", *elcd.trackMeterSchemeMeterName());

  EXPECT_TRUE(elcd.setStorageControlTrackMeterName("ElectricityPurchased:Facility"));
  ASSERT_TRUE(elcd.storageControlTrackMeterName());
  EXPECT_EQ("ElectricityPurchased:Facility", *elcd.storageControlTrackMeterName());

  ASSERT_TRUE(elcd.setMaximumStorageStateofChargeFraction(0.95));
  EXPECT_FALSE(elcd.isMaximumStorageStateofChargeFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.95, elcd.maximumStorageStateofChargeFraction());

  ASSERT_TRUE(elcd.setMinimumStorageStateofChargeFraction(0.20));
  EXPECT_FALSE(elcd.isMinimumStorageStateofChargeFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.20, elcd.minimumStorageStateofChargeFraction());

  EXPECT_TRUE(elcd.setDesignStorageControlChargePower(10000.0));
  ASSERT_TRUE(elcd.designStorageControlChargePower());
  EXPECT_DOUBLE_EQ(10000.0, *elcd.designStorageControlChargePower());

  EXPECT_TRUE(elcd.setDesignStorageControlDischargePower(15000.0));
  ASSERT_TRUE(elcd.designStorageControlDischargePower());
  EXPECT_DOUBLE_EQ(15000.0, *elcd.designStorageControlDischargePower());

  EXPECT_TRUE(elcd.setStorageControlUtilityDemandTarget(18000.0));
  ASSERT_TRUE(elcd.storageControlUtilityDemandTarget());
  EXPECT_DOUBLE_EQ(18000.0, *elcd.storageControlUtilityDemandTarget());

  elcd.resetGeneratorOperationSchemeType();
  EXPECT_TRUE(elcd.isGeneratorOperationSchemeTypeDefaulted());

  elcd.resetElectricalBussType();
  EXPECT_TRUE(elcd.isElectricalBussTypeDefaulted());

  elcd.resetStorageOperationScheme();
  EXPECT_TRUE(elcd.isStorageOperationSchemeDefaulted());

  elcd.resetDemandLimitSchemePurchasedElectricDemandLimit();
  EXPECT_FALSE(elcd.demandLimitSchemePurchasedElectricDemandLimit());

  elcd.resetTrackMeterSchemeMeterName();
  EXPECT_FALSE(elcd.trackMeterSchemeMeterName());

  elcd.resetStorageControlTrackMeterName();
  EXPECT_FALSE(elcd.storageControlTrackMeterName());

  elcd.resetMaximumStorageStateofChargeFraction();
  EXPECT_TRUE(elcd.isMaximumStorageStateofChargeFractionDefaulted());

  elcd.resetMinimumStorageStateofChargeFraction();
  EXPECT_TRUE(elcd.isMinimumStorageStateofChargeFractionDefaulted());

  elcd.resetDesignStorageControlChargePower();
  EXPECT_FALSE(elcd.designStorageControlChargePower());

  elcd.resetDesignStorageControlDischargePower();
  EXPECT_FALSE(elcd.designStorageControlDischargePower());

  elcd.resetStorageControlUtilityDemandTarget();
  EXPECT_FALSE(elcd.storageControlUtilityDemandTarget());
}
