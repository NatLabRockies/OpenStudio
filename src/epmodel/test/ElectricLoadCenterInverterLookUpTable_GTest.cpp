/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Inverter/ElectricLoadCenterInverterLookUpTable.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterInverterLookUpTable_DefaultConstructor) {
  Model model;
  ElectricLoadCenterInverterLookUpTable inverter(model);
  EXPECT_EQ(ElectricLoadCenterInverterLookUpTable::iddObjectType(), inverter.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterInverterLookUpTable_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterInverterLookUpTable inverter(model);

  EXPECT_TRUE(inverter.setRadiativeFraction(0.2));
  ASSERT_TRUE(inverter.radiativeFraction());
  EXPECT_DOUBLE_EQ(0.2, *inverter.radiativeFraction());

  EXPECT_TRUE(inverter.setRatedMaximumContinuousOutputPower(7500.0));
  ASSERT_TRUE(inverter.ratedMaximumContinuousOutputPower());
  EXPECT_DOUBLE_EQ(7500.0, *inverter.ratedMaximumContinuousOutputPower());

  EXPECT_TRUE(inverter.setNightTareLossPower(12.0));
  ASSERT_TRUE(inverter.nightTareLossPower());
  EXPECT_DOUBLE_EQ(12.0, *inverter.nightTareLossPower());

  EXPECT_TRUE(inverter.setNominalVoltageInput(480.0));
  ASSERT_TRUE(inverter.nominalVoltageInput());
  EXPECT_DOUBLE_EQ(480.0, *inverter.nominalVoltageInput());

  EXPECT_TRUE(inverter.setEfficiencyAt10PowerAndNominalVoltage(0.91));
  ASSERT_TRUE(inverter.efficiencyAt10PowerAndNominalVoltage());
  EXPECT_DOUBLE_EQ(0.91, *inverter.efficiencyAt10PowerAndNominalVoltage());

  EXPECT_TRUE(inverter.setEfficiencyAt20PowerAndNominalVoltage(0.92));
  ASSERT_TRUE(inverter.efficiencyAt20PowerAndNominalVoltage());
  EXPECT_DOUBLE_EQ(0.92, *inverter.efficiencyAt20PowerAndNominalVoltage());

  EXPECT_TRUE(inverter.setEfficiencyAt30PowerAndNominalVoltage(0.93));
  ASSERT_TRUE(inverter.efficiencyAt30PowerAndNominalVoltage());
  EXPECT_DOUBLE_EQ(0.93, *inverter.efficiencyAt30PowerAndNominalVoltage());

  EXPECT_TRUE(inverter.setEfficiencyAt50PowerAndNominalVoltage(0.95));
  ASSERT_TRUE(inverter.efficiencyAt50PowerAndNominalVoltage());
  EXPECT_DOUBLE_EQ(0.95, *inverter.efficiencyAt50PowerAndNominalVoltage());

  EXPECT_TRUE(inverter.setEfficiencyAt75PowerAndNominalVoltage(0.96));
  ASSERT_TRUE(inverter.efficiencyAt75PowerAndNominalVoltage());
  EXPECT_DOUBLE_EQ(0.96, *inverter.efficiencyAt75PowerAndNominalVoltage());

  EXPECT_TRUE(inverter.setEfficiencyAt100PowerAndNominalVoltage(0.97));
  ASSERT_TRUE(inverter.efficiencyAt100PowerAndNominalVoltage());
  EXPECT_DOUBLE_EQ(0.97, *inverter.efficiencyAt100PowerAndNominalVoltage());

  inverter.resetRadiativeFraction();
  EXPECT_FALSE(inverter.radiativeFraction());

  inverter.resetRatedMaximumContinuousOutputPower();
  EXPECT_FALSE(inverter.ratedMaximumContinuousOutputPower());

  inverter.resetNightTareLossPower();
  EXPECT_FALSE(inverter.nightTareLossPower());

  inverter.resetNominalVoltageInput();
  EXPECT_FALSE(inverter.nominalVoltageInput());

  inverter.resetEfficiencyAt10PowerAndNominalVoltage();
  EXPECT_FALSE(inverter.efficiencyAt10PowerAndNominalVoltage());

  inverter.resetEfficiencyAt20PowerAndNominalVoltage();
  EXPECT_FALSE(inverter.efficiencyAt20PowerAndNominalVoltage());

  inverter.resetEfficiencyAt30PowerAndNominalVoltage();
  EXPECT_FALSE(inverter.efficiencyAt30PowerAndNominalVoltage());

  inverter.resetEfficiencyAt50PowerAndNominalVoltage();
  EXPECT_FALSE(inverter.efficiencyAt50PowerAndNominalVoltage());

  inverter.resetEfficiencyAt75PowerAndNominalVoltage();
  EXPECT_FALSE(inverter.efficiencyAt75PowerAndNominalVoltage());

  inverter.resetEfficiencyAt100PowerAndNominalVoltage();
  EXPECT_FALSE(inverter.efficiencyAt100PowerAndNominalVoltage());
}
