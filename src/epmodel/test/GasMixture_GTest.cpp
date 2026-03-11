/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../GasLayer/GasMixture.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GasMixture_DefaultConstructor) {
  Model model;
  GasMixture gasMixture(model);

  EXPECT_DOUBLE_EQ(0.003, gasMixture.thickness());
  EXPECT_EQ(4, gasMixture.numberofGasesinMixture());
  EXPECT_EQ("Air", gasMixture.gas1Type());
  EXPECT_DOUBLE_EQ(0.97, gasMixture.gas1Fraction());
  EXPECT_EQ("Argon", gasMixture.gas2Type());
  EXPECT_DOUBLE_EQ(0.01, gasMixture.gas2Fraction());
  EXPECT_EQ("Krypton", gasMixture.gas3Type());
  ASSERT_TRUE(gasMixture.gas3Fraction());
  EXPECT_DOUBLE_EQ(0.01, *gasMixture.gas3Fraction());
  EXPECT_EQ("Xenon", gasMixture.gas4Type());
  ASSERT_TRUE(gasMixture.gas4Fraction());
  EXPECT_DOUBLE_EQ(0.01, *gasMixture.gas4Fraction());
}

TEST_F(EPModelFixture, GasMixture_ScalarAccessors_RoundTrip) {
  Model model;
  GasMixture gasMixture(model);

  EXPECT_TRUE(gasMixture.setThickness(0.005));
  EXPECT_TRUE(gasMixture.setNumberofGasesinMixture(3));
  EXPECT_TRUE(gasMixture.setGas1Type("Krypton"));
  EXPECT_TRUE(gasMixture.setGas1Fraction(0.5));
  EXPECT_TRUE(gasMixture.setGas2Type("Xenon"));
  EXPECT_TRUE(gasMixture.setGas2Fraction(0.3));
  EXPECT_TRUE(gasMixture.setGas3Type("Air"));
  EXPECT_TRUE(gasMixture.setGas3Fraction(0.2));

  EXPECT_DOUBLE_EQ(0.005, gasMixture.thickness());
  EXPECT_EQ(3, gasMixture.numberofGasesinMixture());
  EXPECT_EQ("Krypton", gasMixture.gas1Type());
  EXPECT_DOUBLE_EQ(0.5, gasMixture.gas1Fraction());
  EXPECT_EQ("Xenon", gasMixture.gas2Type());
  EXPECT_DOUBLE_EQ(0.3, gasMixture.gas2Fraction());
  EXPECT_EQ("Air", gasMixture.gas3Type());
  ASSERT_TRUE(gasMixture.gas3Fraction());
  EXPECT_DOUBLE_EQ(0.2, *gasMixture.gas3Fraction());

  gasMixture.resetGas3Type();
  gasMixture.resetGas3Fraction();
  EXPECT_TRUE(gasMixture.gas3Type().empty());
  EXPECT_FALSE(gasMixture.gas3Fraction());
}
