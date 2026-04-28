/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/EvaporativeCoolerIndirectWetCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerIndirectWetCoil_DefaultConstructor) {
  Model model;
  EvaporativeCoolerIndirectWetCoil evaporativeCooler(model);
  EXPECT_EQ(EvaporativeCoolerIndirectWetCoil::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_FALSE(evaporativeCooler.coilFlowRatio());
  EXPECT_FALSE(evaporativeCooler.controlType());
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectWetCoil_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerIndirectWetCoil evaporativeCooler(model);

  EXPECT_TRUE(evaporativeCooler.setCoilMaximumEfficiency(0.8));
  EXPECT_DOUBLE_EQ(0.8, evaporativeCooler.coilMaximumEfficiency());

  EXPECT_TRUE(evaporativeCooler.setCoilFlowRatio(0.35));
  ASSERT_TRUE(evaporativeCooler.coilFlowRatio());
  EXPECT_DOUBLE_EQ(0.35, evaporativeCooler.coilFlowRatio().get());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(310.0));
  EXPECT_DOUBLE_EQ(310.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanFlowRate(2.4));
  EXPECT_DOUBLE_EQ(2.4, evaporativeCooler.secondaryAirFanFlowRate());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanTotalEfficiency(0.62));
  EXPECT_DOUBLE_EQ(0.62, evaporativeCooler.secondaryAirFanTotalEfficiency());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanDeltaPressure(180.0));
  EXPECT_DOUBLE_EQ(180.0, evaporativeCooler.secondaryAirFanDeltaPressure());

  EXPECT_TRUE(evaporativeCooler.setControlType("WetCoil"));
  ASSERT_TRUE(evaporativeCooler.controlType());
  EXPECT_EQ("WetCoil", evaporativeCooler.controlType().get());

  evaporativeCooler.resetCoilFlowRatio();
  EXPECT_FALSE(evaporativeCooler.coilFlowRatio());

  evaporativeCooler.resetControlType();
  EXPECT_FALSE(evaporativeCooler.controlType());
}
