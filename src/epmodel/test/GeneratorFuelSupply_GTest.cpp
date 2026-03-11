/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GeneratorFuelSupply.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorFuelSupply_DefaultConstructor) {
  Model model;
  GeneratorFuelSupply fuelSupply(model);
  EXPECT_EQ(GeneratorFuelSupply::iddObjectType(), fuelSupply.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorFuelSupply_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorFuelSupply fuelSupply(model);

  const auto temperatureModes = GeneratorFuelSupply::fuelTemperatureModelingModeValues();
  ASSERT_FALSE(temperatureModes.empty());
  EXPECT_TRUE(fuelSupply.setFuelTemperatureModelingMode(temperatureModes.front()));
  EXPECT_EQ(temperatureModes.front(), fuelSupply.fuelTemperatureModelingMode());
  fuelSupply.resetFuelTemperatureModelingMode();
  EXPECT_EQ("Scheduled", fuelSupply.fuelTemperatureModelingMode());

  EXPECT_TRUE(fuelSupply.setCompressorHeatLossFactor(0.42));
  EXPECT_DOUBLE_EQ(0.42, fuelSupply.compressorHeatLossFactor());
  fuelSupply.resetCompressorHeatLossFactor();
  EXPECT_DOUBLE_EQ(0.0, fuelSupply.compressorHeatLossFactor());

  const auto fuelTypes = GeneratorFuelSupply::fuelTypeValues();
  ASSERT_FALSE(fuelTypes.empty());
  EXPECT_TRUE(fuelSupply.setFuelType(fuelTypes.front()));
  EXPECT_EQ(fuelTypes.front(), fuelSupply.fuelType());
  fuelSupply.resetFuelType();
  EXPECT_EQ("GaseousConstituents", fuelSupply.fuelType());

  EXPECT_TRUE(fuelSupply.setLiquidGenericFuelLowerHeatingValue(35000.0));
  ASSERT_TRUE(fuelSupply.liquidGenericFuelLowerHeatingValue());
  EXPECT_DOUBLE_EQ(35000.0, fuelSupply.liquidGenericFuelLowerHeatingValue().get());
  fuelSupply.resetLiquidGenericFuelLowerHeatingValue();
  EXPECT_FALSE(fuelSupply.liquidGenericFuelLowerHeatingValue());

  EXPECT_TRUE(fuelSupply.setLiquidGenericFuelHigherHeatingValue(40000.0));
  ASSERT_TRUE(fuelSupply.liquidGenericFuelHigherHeatingValue());
  EXPECT_DOUBLE_EQ(40000.0, fuelSupply.liquidGenericFuelHigherHeatingValue().get());
  fuelSupply.resetLiquidGenericFuelHigherHeatingValue();
  EXPECT_FALSE(fuelSupply.liquidGenericFuelHigherHeatingValue());

  EXPECT_TRUE(fuelSupply.setLiquidGenericFuelMolecularWeight(120.0));
  ASSERT_TRUE(fuelSupply.liquidGenericFuelMolecularWeight());
  EXPECT_DOUBLE_EQ(120.0, fuelSupply.liquidGenericFuelMolecularWeight().get());
  fuelSupply.resetLiquidGenericFuelMolecularWeight();
  EXPECT_FALSE(fuelSupply.liquidGenericFuelMolecularWeight());

  EXPECT_TRUE(fuelSupply.setLiquidGenericFuelCO2EmissionFactor(0.06));
  ASSERT_TRUE(fuelSupply.liquidGenericFuelCO2EmissionFactor());
  EXPECT_DOUBLE_EQ(0.06, fuelSupply.liquidGenericFuelCO2EmissionFactor().get());
  fuelSupply.resetLiquidGenericFuelCO2EmissionFactor();
  EXPECT_FALSE(fuelSupply.liquidGenericFuelCO2EmissionFactor());

  auto numberOfConstituents = fuelSupply.numberofConstituentsinGaseousConstituentFuelSupply();
  ASSERT_TRUE(numberOfConstituents);
  EXPECT_EQ(0u, numberOfConstituents.get());
}
