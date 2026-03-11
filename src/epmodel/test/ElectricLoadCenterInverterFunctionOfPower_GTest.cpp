/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ElectricLoadCenterInverterFunctionOfPower.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterInverterFunctionOfPower_DefaultConstructor) {
  Model model;
  ElectricLoadCenterInverterFunctionOfPower inverter(model);
  EXPECT_EQ(ElectricLoadCenterInverterFunctionOfPower::iddObjectType(), inverter.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterInverterFunctionOfPower_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterInverterFunctionOfPower inverter(model);

  EXPECT_TRUE(inverter.setRadiativeFraction(0.2));
  ASSERT_TRUE(inverter.radiativeFraction());
  EXPECT_DOUBLE_EQ(0.2, *inverter.radiativeFraction());

  EXPECT_TRUE(inverter.setRatedMaximumContinuousInputPower(7500.0));
  ASSERT_TRUE(inverter.ratedMaximumContinuousInputPower());
  EXPECT_DOUBLE_EQ(7500.0, *inverter.ratedMaximumContinuousInputPower());

  EXPECT_TRUE(inverter.setMinimumEfficiency(0.91));
  ASSERT_TRUE(inverter.minimumEfficiency());
  EXPECT_DOUBLE_EQ(0.91, *inverter.minimumEfficiency());

  EXPECT_TRUE(inverter.setMaximumEfficiency(0.98));
  ASSERT_TRUE(inverter.maximumEfficiency());
  EXPECT_DOUBLE_EQ(0.98, *inverter.maximumEfficiency());

  EXPECT_TRUE(inverter.setMinimumPowerOutput(300.0));
  ASSERT_TRUE(inverter.minimumPowerOutput());
  EXPECT_DOUBLE_EQ(300.0, *inverter.minimumPowerOutput());

  EXPECT_TRUE(inverter.setMaximumPowerOutput(7000.0));
  ASSERT_TRUE(inverter.maximumPowerOutput());
  EXPECT_DOUBLE_EQ(7000.0, *inverter.maximumPowerOutput());

  EXPECT_TRUE(inverter.setAncillaryPowerConsumedInStandby(10.0));
  ASSERT_TRUE(inverter.ancillaryPowerConsumedInStandby());
  EXPECT_DOUBLE_EQ(10.0, *inverter.ancillaryPowerConsumedInStandby());

  inverter.resetRadiativeFraction();
  EXPECT_FALSE(inverter.radiativeFraction());

  inverter.resetRatedMaximumContinuousInputPower();
  EXPECT_FALSE(inverter.ratedMaximumContinuousInputPower());

  inverter.resetMinimumEfficiency();
  EXPECT_FALSE(inverter.minimumEfficiency());

  inverter.resetMaximumEfficiency();
  EXPECT_FALSE(inverter.maximumEfficiency());

  inverter.resetMinimumPowerOutput();
  EXPECT_FALSE(inverter.minimumPowerOutput());

  inverter.resetMaximumPowerOutput();
  EXPECT_FALSE(inverter.maximumPowerOutput());

  inverter.resetAncillaryPowerConsumedInStandby();
  EXPECT_FALSE(inverter.ancillaryPowerConsumedInStandby());
}
