/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelCellPowerModule.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellPowerModule_DefaultConstructor) {
  Model model;
  GeneratorFuelCellPowerModule powerModule(model);
  EXPECT_EQ(GeneratorFuelCellPowerModule::iddObjectType(), powerModule.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellPowerModule_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellPowerModule powerModule(model);

  auto efficiencyModes = GeneratorFuelCellPowerModule::efficiencyCurveModeValues();
  ASSERT_FALSE(efficiencyModes.empty());
  EXPECT_TRUE(powerModule.setEfficiencyCurveMode(efficiencyModes.front()));
  EXPECT_EQ(efficiencyModes.front(), powerModule.efficiencyCurveMode());
  powerModule.resetEfficiencyCurveMode();
  EXPECT_EQ("Annex42", powerModule.efficiencyCurveMode());

  EXPECT_TRUE(powerModule.setNominalEfficiency(0.9));
  EXPECT_DOUBLE_EQ(0.9, powerModule.nominalEfficiency());
  powerModule.resetNominalEfficiency();
  EXPECT_DOUBLE_EQ(1.0, powerModule.nominalEfficiency());

  EXPECT_TRUE(powerModule.setNominalElectricalPower(3250.0));
  EXPECT_DOUBLE_EQ(3250.0, powerModule.nominalElectricalPower());
  powerModule.resetNominalElectricalPower();
  EXPECT_DOUBLE_EQ(3400.0, powerModule.nominalElectricalPower());

  EXPECT_TRUE(powerModule.setStartUpFuel(0.4));
  EXPECT_DOUBLE_EQ(0.4, powerModule.startUpFuel());
  powerModule.resetStartUpFuel();
  EXPECT_DOUBLE_EQ(0.0, powerModule.startUpFuel());

  auto skinLossModes = GeneratorFuelCellPowerModule::skinLossCalculationModeValues();
  ASSERT_FALSE(skinLossModes.empty());
  EXPECT_TRUE(powerModule.setSkinLossCalculationMode(skinLossModes.front()));
  EXPECT_EQ(skinLossModes.front(), powerModule.skinLossCalculationMode());
  powerModule.resetSkinLossCalculationMode();
  EXPECT_EQ("ConstantRate", powerModule.skinLossCalculationMode());

  EXPECT_TRUE(powerModule.setSkinLossRadiativeFraction(0.75));
  EXPECT_DOUBLE_EQ(0.75, powerModule.skinLossRadiativeFraction());
  powerModule.resetSkinLossRadiativeFraction();
  EXPECT_DOUBLE_EQ(1.0, powerModule.skinLossRadiativeFraction());

  EXPECT_TRUE(powerModule.setDilutionAirFlowRate(0.007));
  EXPECT_DOUBLE_EQ(0.007, powerModule.dilutionAirFlowRate());
  powerModule.resetDilutionAirFlowRate();
  EXPECT_DOUBLE_EQ(0.0, powerModule.dilutionAirFlowRate());

  EXPECT_TRUE(powerModule.setMinimumOperatingPoint(3000.0));
  EXPECT_DOUBLE_EQ(3000.0, powerModule.minimumOperatingPoint());
  powerModule.resetMinimumOperatingPoint();
  EXPECT_DOUBLE_EQ(0.0, powerModule.minimumOperatingPoint());

  EXPECT_TRUE(powerModule.setMaximumOperatingPoint(3800.0));
  EXPECT_DOUBLE_EQ(3800.0, powerModule.maximumOperatingPoint());
  powerModule.resetMaximumOperatingPoint();
  EXPECT_DOUBLE_EQ(0.0, powerModule.maximumOperatingPoint());
}
