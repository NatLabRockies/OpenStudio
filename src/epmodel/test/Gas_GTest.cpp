/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../GasLayer/Gas.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Gas_DefaultConstructor) {
  Model model;
  Gas gas(model);

  EXPECT_EQ("Air", gas.gasType());
  EXPECT_DOUBLE_EQ(0.003, gas.thickness());
  EXPECT_FALSE(gas.customConductivityCoefficientA());
}

TEST_F(EPModelFixture, Gas_ScalarAccessors_RoundTrip) {
  Model model;
  Gas gas(model);

  EXPECT_TRUE(gas.setGasType("Custom"));
  EXPECT_TRUE(gas.setThickness(0.01));
  EXPECT_TRUE(gas.setCustomConductivity(0.12, 0.23, 0.34));
  EXPECT_TRUE(gas.setCustomViscosity(0.41, 0.52, 0.63));
  EXPECT_TRUE(gas.setCustomSpecificHeat(1.02, 1.13, 1.24));
  EXPECT_TRUE(gas.setCustomMolecularWeight(28.0));
  EXPECT_TRUE(gas.setSpecificHeatRatio(1.41));

  EXPECT_EQ("Custom", gas.gasType());
  EXPECT_DOUBLE_EQ(0.01, gas.thickness());
  ASSERT_TRUE(gas.customConductivityCoefficientC());
  EXPECT_DOUBLE_EQ(0.34, *gas.customConductivityCoefficientC());
  ASSERT_TRUE(gas.customViscosityCoefficientB());
  EXPECT_DOUBLE_EQ(0.52, *gas.customViscosityCoefficientB());
  ASSERT_TRUE(gas.customSpecificHeatCoefficientA());
  EXPECT_DOUBLE_EQ(1.02, *gas.customSpecificHeatCoefficientA());
  ASSERT_TRUE(gas.customMolecularWeight());
  EXPECT_DOUBLE_EQ(28.0, *gas.customMolecularWeight());
  ASSERT_TRUE(gas.specificHeatRatio());
  EXPECT_DOUBLE_EQ(1.41, *gas.specificHeatRatio());

  EXPECT_FALSE(Gas::gasTypeValues().empty());
  EXPECT_FALSE(Gas::validGasTypes().empty());
}
