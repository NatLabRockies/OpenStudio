/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelCellAirSupply.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelCellAirSupply_DefaultConstructor) {
  Model model;
  GeneratorFuelCellAirSupply airSupply(model);
  EXPECT_EQ(GeneratorFuelCellAirSupply::iddObjectType(), airSupply.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelCellAirSupply_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelCellAirSupply airSupply(model);

  EXPECT_TRUE(airSupply.setBlowerHeatLossFactor(0.92));
  EXPECT_DOUBLE_EQ(0.92, airSupply.blowerHeatLossFactor());
  airSupply.resetBlowerHeatLossFactor();
  EXPECT_DOUBLE_EQ(0.0, airSupply.blowerHeatLossFactor());

  auto asrcModes = GeneratorFuelCellAirSupply::airSupplyRateCalculationModeValues();
  ASSERT_FALSE(asrcModes.empty());
  EXPECT_TRUE(airSupply.setAirSupplyRateCalculationMode(asrcModes.front()));
  EXPECT_EQ(asrcModes.front(), airSupply.airSupplyRateCalculationMode());

  EXPECT_TRUE(airSupply.setStoichiometricRatio(1.25));
  ASSERT_TRUE(airSupply.stoichiometricRatio());
  EXPECT_DOUBLE_EQ(1.25, airSupply.stoichiometricRatio().get());
  airSupply.resetStoichiometricRatio();
  EXPECT_FALSE(airSupply.stoichiometricRatio());

  EXPECT_TRUE(airSupply.setAirRateAirTemperatureCoefficient(0.0031));
  ASSERT_TRUE(airSupply.airRateAirTemperatureCoefficient());
  EXPECT_DOUBLE_EQ(0.0031, airSupply.airRateAirTemperatureCoefficient().get());
  airSupply.resetAirRateAirTemperatureCoefficient();
  ASSERT_TRUE(airSupply.airRateAirTemperatureCoefficient());
  EXPECT_DOUBLE_EQ(0.0, airSupply.airRateAirTemperatureCoefficient().get());

  auto hrModes = GeneratorFuelCellAirSupply::airIntakeHeatRecoveryModeValues();
  ASSERT_FALSE(hrModes.empty());
  EXPECT_TRUE(airSupply.setAirIntakeHeatRecoveryMode(hrModes.front()));
  EXPECT_EQ(hrModes.front(), airSupply.airIntakeHeatRecoveryMode());

  auto constituentModes = GeneratorFuelCellAirSupply::airSupplyConstituentModeValues();
  ASSERT_FALSE(constituentModes.empty());
  EXPECT_TRUE(airSupply.setAirSupplyConstituentMode(constituentModes.front()));
  EXPECT_EQ(constituentModes.front(), airSupply.airSupplyConstituentMode());

  auto numberofConstituents = airSupply.numberofUserDefinedConstituents();
  ASSERT_TRUE(numberofConstituents);
  EXPECT_EQ(0u, numberofConstituents.get());
}
