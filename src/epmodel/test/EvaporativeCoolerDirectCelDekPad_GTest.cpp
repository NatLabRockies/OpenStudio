/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/EvaporativeCoolerDirectCelDekPad.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, EvaporativeCoolerDirectCelDekPad_DefaultConstructor) {
  Model model;
  EvaporativeCoolerDirectCelDekPad evaporativeCooler(model);
  EXPECT_EQ(EvaporativeCoolerDirectCelDekPad::iddObjectType(), evaporativeCooler.iddObject().type());
  EXPECT_TRUE(evaporativeCooler.isDirectPadAreaAutosized());
  EXPECT_TRUE(evaporativeCooler.isDirectPadDepthAutosized());
  EXPECT_FALSE(evaporativeCooler.directPadArea());
  EXPECT_FALSE(evaporativeCooler.directPadDepth());
  EXPECT_FALSE(evaporativeCooler.controlType());
}

TEST_F(EPModelFixture, EvaporativeCoolerDirectCelDekPad_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeCoolerDirectCelDekPad evaporativeCooler(model);

  EXPECT_TRUE(evaporativeCooler.setDirectPadArea(1.25));
  ASSERT_TRUE(evaporativeCooler.directPadArea());
  EXPECT_DOUBLE_EQ(1.25, evaporativeCooler.directPadArea().get());
  EXPECT_FALSE(evaporativeCooler.isDirectPadAreaAutosized());

  EXPECT_TRUE(evaporativeCooler.setDirectPadDepth(0.18));
  ASSERT_TRUE(evaporativeCooler.directPadDepth());
  EXPECT_DOUBLE_EQ(0.18, evaporativeCooler.directPadDepth().get());
  EXPECT_FALSE(evaporativeCooler.isDirectPadDepthAutosized());

  EXPECT_TRUE(evaporativeCooler.setRecirculatingWaterPumpPowerConsumption(245.0));
  EXPECT_DOUBLE_EQ(245.0, evaporativeCooler.recirculatingWaterPumpPowerConsumption());

  EXPECT_TRUE(evaporativeCooler.setControlType("Fixed"));
  ASSERT_TRUE(evaporativeCooler.controlType());
  EXPECT_EQ("Fixed", evaporativeCooler.controlType().get());

  evaporativeCooler.resetDirectPadArea();
  evaporativeCooler.resetDirectPadDepth();
  evaporativeCooler.resetControlType();
  EXPECT_FALSE(evaporativeCooler.directPadArea());
  EXPECT_FALSE(evaporativeCooler.directPadDepth());
  EXPECT_FALSE(evaporativeCooler.controlType());

  evaporativeCooler.autosizeDirectPadArea();
  evaporativeCooler.autosizeDirectPadDepth();
  EXPECT_TRUE(evaporativeCooler.isDirectPadAreaAutosized());
  EXPECT_TRUE(evaporativeCooler.isDirectPadDepthAutosized());
}
