/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ZoneHVACHybridUnitaryHVAC.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACHybridUnitaryHVAC_DefaultConstructor) {
  Model model;
  ZoneHVACHybridUnitaryHVAC hybrid(model);

  EXPECT_EQ(ZoneHVACHybridUnitaryHVAC::iddObjectType(), hybrid.iddObject().type());
  EXPECT_EQ("Automatic", hybrid.methodToChooseControlledInputsAndPartRuntimeFraction());
  EXPECT_FALSE(hybrid.systemMaximumSupplyAirFlowRate());
  EXPECT_FALSE(hybrid.externalStaticPressureAtSystemMaximumSupplyAirFlowRate());
  EXPECT_EQ("No", hybrid.fanHeatIncludedInLookupTables());
  EXPECT_EQ("SupplyAirStream", hybrid.fanHeatGainLocation());
  EXPECT_DOUBLE_EQ(1.0, hybrid.fanHeatInAirStreamFraction());
  EXPECT_DOUBLE_EQ(1.0, hybrid.scalingFactor());
  EXPECT_DOUBLE_EQ(10.0, hybrid.minimumTimeBetweenModeChange());
  EXPECT_EQ("Electricity", hybrid.firstFuelType());
  EXPECT_EQ("None", hybrid.secondFuelType());
  EXPECT_EQ("None", hybrid.thirdFuelType());
  EXPECT_EQ("Electricity Use", hybrid.objectiveFunctionToMinimize());
  EXPECT_DOUBLE_EQ(0.0, hybrid.mode0OutdoorAirFraction());
  EXPECT_DOUBLE_EQ(0.0, hybrid.mode0SupplyAirMassFlowRateRatio());
}

TEST_F(EPModelFixture, ZoneHVACHybridUnitaryHVAC_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACHybridUnitaryHVAC hybrid(model);

  const auto methodValues = ZoneHVACHybridUnitaryHVAC::methodToChooseControlledInputsAndPartRuntimeFractionValues();
  ASSERT_FALSE(methodValues.empty());
  EXPECT_TRUE(hybrid.setMethodToChooseControlledInputsAndPartRuntimeFraction("User Defined"));
  EXPECT_FALSE(hybrid.isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted());
  hybrid.resetMethodToChooseControlledInputsAndPartRuntimeFraction();
  EXPECT_TRUE(hybrid.isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted());

  EXPECT_TRUE(hybrid.setSystemMaximumSupplyAirFlowRate(0.35));
  ASSERT_TRUE(hybrid.systemMaximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.35, hybrid.systemMaximumSupplyAirFlowRate().value());
  hybrid.resetSystemMaximumSupplyAirFlowRate();
  EXPECT_FALSE(hybrid.systemMaximumSupplyAirFlowRate());

  EXPECT_TRUE(hybrid.setExternalStaticPressureAtSystemMaximumSupplyAirFlowRate(65.0));
  ASSERT_TRUE(hybrid.externalStaticPressureAtSystemMaximumSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(65.0, hybrid.externalStaticPressureAtSystemMaximumSupplyAirFlowRate().value());
  hybrid.resetExternalStaticPressureAtSystemMaximumSupplyAirFlowRate();
  EXPECT_FALSE(hybrid.externalStaticPressureAtSystemMaximumSupplyAirFlowRate());

  const auto fanHeatIncludedValues = ZoneHVACHybridUnitaryHVAC::fanHeatIncludedInLookupTablesValues();
  ASSERT_FALSE(fanHeatIncludedValues.empty());
  EXPECT_TRUE(hybrid.setFanHeatIncludedInLookupTables("Yes"));
  EXPECT_FALSE(hybrid.isFanHeatIncludedInLookupTablesDefaulted());
  hybrid.resetFanHeatIncludedInLookupTables();
  EXPECT_TRUE(hybrid.isFanHeatIncludedInLookupTablesDefaulted());

  const auto fanHeatGainValues = ZoneHVACHybridUnitaryHVAC::fanHeatGainLocationValues();
  ASSERT_FALSE(fanHeatGainValues.empty());
  EXPECT_TRUE(hybrid.setFanHeatGainLocation("MixedAirStream"));
  EXPECT_FALSE(hybrid.isFanHeatGainLocationDefaulted());
  hybrid.resetFanHeatGainLocation();
  EXPECT_TRUE(hybrid.isFanHeatGainLocationDefaulted());

  EXPECT_TRUE(hybrid.setFanHeatInAirStreamFraction(0.5));
  EXPECT_FALSE(hybrid.isFanHeatInAirStreamFractionDefaulted());
  hybrid.resetFanHeatInAirStreamFraction();
  EXPECT_TRUE(hybrid.isFanHeatInAirStreamFractionDefaulted());
  EXPECT_DOUBLE_EQ(1.0, hybrid.fanHeatInAirStreamFraction());

  EXPECT_TRUE(hybrid.setScalingFactor(1.5));
  EXPECT_FALSE(hybrid.isScalingFactorDefaulted());
  hybrid.resetScalingFactor();
  EXPECT_TRUE(hybrid.isScalingFactorDefaulted());
  EXPECT_DOUBLE_EQ(1.0, hybrid.scalingFactor());

  EXPECT_TRUE(hybrid.setMinimumTimeBetweenModeChange(15.0));
  EXPECT_FALSE(hybrid.isMinimumTimeBetweenModeChangeDefaulted());
  hybrid.resetMinimumTimeBetweenModeChange();
  EXPECT_TRUE(hybrid.isMinimumTimeBetweenModeChangeDefaulted());
  EXPECT_DOUBLE_EQ(10.0, hybrid.minimumTimeBetweenModeChange());

  EXPECT_TRUE(hybrid.setFirstFuelType("NaturalGas"));
  EXPECT_FALSE(hybrid.isFirstFuelTypeDefaulted());
  hybrid.resetFirstFuelType();
  EXPECT_TRUE(hybrid.isFirstFuelTypeDefaulted());
  EXPECT_EQ("Electricity", hybrid.firstFuelType());

  EXPECT_TRUE(hybrid.setSecondFuelType("FuelOilNo1"));
  EXPECT_FALSE(hybrid.isSecondFuelTypeDefaulted());
  hybrid.resetSecondFuelType();
  EXPECT_TRUE(hybrid.isSecondFuelTypeDefaulted());
  EXPECT_EQ("None", hybrid.secondFuelType());

  EXPECT_TRUE(hybrid.setThirdFuelType("OtherFuel1"));
  EXPECT_FALSE(hybrid.isThirdFuelTypeDefaulted());
  hybrid.resetThirdFuelType();
  EXPECT_TRUE(hybrid.isThirdFuelTypeDefaulted());
  EXPECT_EQ("None", hybrid.thirdFuelType());

  EXPECT_TRUE(hybrid.setObjectiveFunctionToMinimize("Water Use"));
  EXPECT_FALSE(hybrid.isObjectiveFunctionToMinimizeDefaulted());
  hybrid.resetObjectiveFunctionToMinimize();
  EXPECT_TRUE(hybrid.isObjectiveFunctionToMinimizeDefaulted());
  EXPECT_EQ("Electricity Use", hybrid.objectiveFunctionToMinimize());

  EXPECT_TRUE(hybrid.setMode0OutdoorAirFraction(0.25));
  EXPECT_FALSE(hybrid.isMode0OutdoorAirFractionDefaulted());
  hybrid.resetMode0OutdoorAirFraction();
  EXPECT_TRUE(hybrid.isMode0OutdoorAirFractionDefaulted());
  EXPECT_DOUBLE_EQ(0.0, hybrid.mode0OutdoorAirFraction());

  EXPECT_TRUE(hybrid.setMode0SupplyAirMassFlowRateRatio(0.35));
  EXPECT_FALSE(hybrid.isMode0SupplyAirMassFlowRateRatioDefaulted());
  hybrid.resetMode0SupplyAirMassFlowRateRatio();
  EXPECT_TRUE(hybrid.isMode0SupplyAirMassFlowRateRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.0, hybrid.mode0SupplyAirMassFlowRateRatio());
}
