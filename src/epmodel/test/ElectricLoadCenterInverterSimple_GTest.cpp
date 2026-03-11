/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Inverter/ElectricLoadCenterInverterSimple.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterInverterSimple_DefaultConstructor) {
  Model model;
  ElectricLoadCenterInverterSimple inverter(model);
  EXPECT_EQ(ElectricLoadCenterInverterSimple::iddObjectType(), inverter.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterInverterSimple_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterInverterSimple inverter(model);

  EXPECT_TRUE(inverter.setRadiativeFraction(0.2));
  ASSERT_TRUE(inverter.radiativeFraction());
  EXPECT_DOUBLE_EQ(0.2, *inverter.radiativeFraction());

  EXPECT_TRUE(inverter.setInverterEfficiency(0.95));
  ASSERT_TRUE(inverter.inverterEfficiency());
  EXPECT_DOUBLE_EQ(0.95, *inverter.inverterEfficiency());

  inverter.resetRadiativeFraction();
  EXPECT_FALSE(inverter.radiativeFraction());

  inverter.resetInverterEfficiency();
  EXPECT_FALSE(inverter.inverterEfficiency());
}
