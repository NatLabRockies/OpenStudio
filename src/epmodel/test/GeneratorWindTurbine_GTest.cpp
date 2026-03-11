/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Generator/GeneratorWindTurbine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GeneratorWindTurbine_DefaultConstructor) {
  Model model;
  GeneratorWindTurbine generator(model);
  EXPECT_EQ(GeneratorWindTurbine::iddObjectType(), generator.iddObject().type());
}

TEST_F(EPModelFixture, GeneratorWindTurbine_ScalarAccessors_RoundTrip) {
  Model model;
  GeneratorWindTurbine generator(model);

  const auto rotorTypes = GeneratorWindTurbine::rotorTypeValues();
  ASSERT_FALSE(rotorTypes.empty());
  const auto powerControls = GeneratorWindTurbine::powerControlValues();
  ASSERT_FALSE(powerControls.empty());

  EXPECT_TRUE(generator.setRotorType("HorizontalAxisWindTurbine"));
  EXPECT_EQ("HorizontalAxisWindTurbine", generator.rotorType());
  EXPECT_TRUE(generator.setPowerControl("VariableSpeedVariablePitch"));
  EXPECT_EQ("VariableSpeedVariablePitch", generator.powerControl());

  EXPECT_TRUE(generator.setRatedRotorSpeed(41.0));
  EXPECT_DOUBLE_EQ(41.0, generator.ratedRotorSpeed());
  EXPECT_TRUE(generator.setRotorDiameter(19.2));
  EXPECT_DOUBLE_EQ(19.2, generator.rotorDiameter());
  EXPECT_TRUE(generator.setOverallHeight(30.5));
  EXPECT_DOUBLE_EQ(30.5, generator.overallHeight());
  EXPECT_TRUE(generator.setNumberofBlades(3));
  EXPECT_EQ(3, generator.numberofBlades());

  EXPECT_TRUE(generator.setRatedPower(55000.0));
  EXPECT_DOUBLE_EQ(55000.0, generator.ratedPower());
  EXPECT_TRUE(generator.setRatedWindSpeed(11.0));
  EXPECT_DOUBLE_EQ(11.0, generator.ratedWindSpeed());
  EXPECT_TRUE(generator.setCutInWindSpeed(3.5));
  EXPECT_DOUBLE_EQ(3.5, generator.cutInWindSpeed());
  EXPECT_TRUE(generator.setCutOutWindSpeed(25.0));
  EXPECT_DOUBLE_EQ(25.0, generator.cutOutWindSpeed());
  EXPECT_TRUE(generator.setFractionSystemEfficiency(0.835));
  EXPECT_DOUBLE_EQ(0.835, generator.fractionSystemEfficiency());
  EXPECT_TRUE(generator.setMaximumTipSpeedRatio(5.0));
  EXPECT_DOUBLE_EQ(5.0, generator.maximumTipSpeedRatio());
  EXPECT_TRUE(generator.setMaximumPowerCoefficient(0.25));
  EXPECT_DOUBLE_EQ(0.25, generator.maximumPowerCoefficient());

  EXPECT_FALSE(generator.annualLocalAverageWindSpeed());
  EXPECT_TRUE(generator.setAnnualLocalAverageWindSpeed(6.4));
  ASSERT_TRUE(generator.annualLocalAverageWindSpeed());
  EXPECT_DOUBLE_EQ(6.4, generator.annualLocalAverageWindSpeed().get());
  generator.resetAnnualLocalAverageWindSpeed();
  EXPECT_FALSE(generator.annualLocalAverageWindSpeed());

  EXPECT_TRUE(generator.setHeightforLocalAverageWindSpeed(50.0));
  EXPECT_DOUBLE_EQ(50.0, generator.heightforLocalAverageWindSpeed());
  EXPECT_TRUE(generator.setBladeChordArea(2.08));
  EXPECT_DOUBLE_EQ(2.08, generator.bladeChordArea());
  EXPECT_TRUE(generator.setBladeDragCoefficient(0.9));
  EXPECT_DOUBLE_EQ(0.9, generator.bladeDragCoefficient());
  EXPECT_TRUE(generator.setBladeLiftCoefficient(0.05));
  EXPECT_DOUBLE_EQ(0.05, generator.bladeLiftCoefficient());

  EXPECT_TRUE(generator.setPowerCoefficientC1(0.5176));
  EXPECT_DOUBLE_EQ(0.5176, generator.powerCoefficientC1());
  EXPECT_TRUE(generator.setPowerCoefficientC2(116.0));
  EXPECT_DOUBLE_EQ(116.0, generator.powerCoefficientC2());
  EXPECT_TRUE(generator.setPowerCoefficientC3(0.4));
  EXPECT_DOUBLE_EQ(0.4, generator.powerCoefficientC3());
  EXPECT_TRUE(generator.setPowerCoefficientC4(0.0));
  EXPECT_DOUBLE_EQ(0.0, generator.powerCoefficientC4());
  EXPECT_TRUE(generator.setPowerCoefficientC5(5.0));
  EXPECT_DOUBLE_EQ(5.0, generator.powerCoefficientC5());
  EXPECT_TRUE(generator.setPowerCoefficientC6(21.0));
  EXPECT_DOUBLE_EQ(21.0, generator.powerCoefficientC6());
}
