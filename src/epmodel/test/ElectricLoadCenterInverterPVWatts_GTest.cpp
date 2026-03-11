/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Inverter/ElectricLoadCenterInverterPVWatts.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ElectricLoadCenterInverterPVWatts_DefaultConstructor) {
  Model model;
  ElectricLoadCenterInverterPVWatts inverter(model);
  EXPECT_EQ(ElectricLoadCenterInverterPVWatts::iddObjectType(), inverter.iddObject().type());
}

TEST_F(EPModelFixture, ElectricLoadCenterInverterPVWatts_ScalarAccessors_RoundTrip) {
  Model model;
  ElectricLoadCenterInverterPVWatts inverter(model);

  EXPECT_TRUE(inverter.isDCToACSizeRatioDefaulted());
  EXPECT_TRUE(inverter.isInverterEfficiencyDefaulted());

  EXPECT_TRUE(inverter.setDCToACSizeRatio(1.2));
  EXPECT_DOUBLE_EQ(1.2, inverter.dcToACSizeRatio());
  EXPECT_FALSE(inverter.isDCToACSizeRatioDefaulted());

  EXPECT_TRUE(inverter.setInverterEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, inverter.inverterEfficiency());
  EXPECT_FALSE(inverter.isInverterEfficiencyDefaulted());

  inverter.resetDCToACSizeRatio();
  EXPECT_TRUE(inverter.isDCToACSizeRatioDefaulted());

  inverter.resetInverterEfficiency();
  EXPECT_TRUE(inverter.isInverterEfficiencyDefaulted());
}
