/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/EvaporativeCoolerIndirectCelDekPad.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerIndirectCelDekPad_DefaultConstructor) {
  Model model;
  EvaporativeCoolerIndirectCelDekPad evaporativeCooler(model);
  EXPECT_EQ(EvaporativeCoolerIndirectCelDekPad::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_TRUE(evaporativeCooler.isDirectPadAreaAutosized());
  EXPECT_TRUE(evaporativeCooler.isDirectPadDepthAutosized());
  EXPECT_FALSE(evaporativeCooler.directPadArea());
  EXPECT_FALSE(evaporativeCooler.directPadDepth());
  EXPECT_FALSE(evaporativeCooler.secondaryAirFanTotalEfficiency());
  EXPECT_FALSE(evaporativeCooler.controlType());
}

TEST_F(EPModelFixture, EvaporativeCoolerIndirectCelDekPad_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerIndirectCelDekPad evaporativeCooler(model);

  EXPECT_TRUE(evaporativeCooler.setDirectPadArea(1.65));
  ASSERT_TRUE(evaporativeCooler.directPadArea());
  EXPECT_DOUBLE_EQ(1.65, evaporativeCooler.directPadArea().get());
  EXPECT_FALSE(evaporativeCooler.isDirectPadAreaAutosized());

  EXPECT_TRUE(evaporativeCooler.setDirectPadDepth(0.22));
  ASSERT_TRUE(evaporativeCooler.directPadDepth());
  EXPECT_DOUBLE_EQ(0.22, evaporativeCooler.directPadDepth().get());
  EXPECT_FALSE(evaporativeCooler.isDirectPadDepthAutosized());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(315.0));
  EXPECT_DOUBLE_EQ(315.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanFlowRate(2.75));
  EXPECT_DOUBLE_EQ(2.75, evaporativeCooler.secondaryAirFanFlowRate());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanTotalEfficiency(0.62));
  ASSERT_TRUE(evaporativeCooler.secondaryAirFanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.62, evaporativeCooler.secondaryAirFanTotalEfficiency().get());

  EXPECT_TRUE(evaporativeCooler.setSecondaryAirFanDeltaPressure(185.0));
  EXPECT_DOUBLE_EQ(185.0, evaporativeCooler.secondaryAirFanDeltaPressure());

  EXPECT_TRUE(evaporativeCooler.setIndirectHeatExchangerEffectiveness(0.74));
  EXPECT_DOUBLE_EQ(0.74, evaporativeCooler.indirectHeatExchangerEffectiveness());

  EXPECT_TRUE(evaporativeCooler.setControlType("Fixed"));
  ASSERT_TRUE(evaporativeCooler.controlType());
  EXPECT_EQ("Fixed", evaporativeCooler.controlType().get());

  evaporativeCooler.resetDirectPadArea();
  evaporativeCooler.resetDirectPadDepth();
  evaporativeCooler.resetSecondaryAirFanTotalEfficiency();
  evaporativeCooler.resetControlType();
  EXPECT_FALSE(evaporativeCooler.directPadArea());
  EXPECT_FALSE(evaporativeCooler.directPadDepth());
  EXPECT_FALSE(evaporativeCooler.secondaryAirFanTotalEfficiency());
  EXPECT_FALSE(evaporativeCooler.controlType());

  evaporativeCooler.autosizeDirectPadArea();
  evaporativeCooler.autosizeDirectPadDepth();
  EXPECT_TRUE(evaporativeCooler.isDirectPadAreaAutosized());
  EXPECT_TRUE(evaporativeCooler.isDirectPadDepthAutosized());
}
