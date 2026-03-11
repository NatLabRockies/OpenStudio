/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../ModelObject/CoilHeatingSteam.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingSteam_DefaultConstructor) {
  Model model;
  CoilHeatingSteam coil(model);
  EXPECT_EQ(CoilHeatingSteam::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, CoilHeatingSteam_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingSteam coil(model);

  const auto coilControlTypeChoices = CoilHeatingSteam::coilControlTypeValues();
  EXPECT_FALSE(coilControlTypeChoices.empty());
  EXPECT_TRUE(std::find(coilControlTypeChoices.begin(), coilControlTypeChoices.end(), "TemperatureSetpointControl")
              != coilControlTypeChoices.end());
  ASSERT_GE(coilControlTypeChoices.size(), 2u);

  EXPECT_FALSE(coil.maximumSteamFlowRate());
  EXPECT_FALSE(coil.isMaximumSteamFlowRateAutosized());
  EXPECT_TRUE(coil.setMaximumSteamFlowRate(0.55));
  ASSERT_TRUE(coil.maximumSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.55, coil.maximumSteamFlowRate().get());
  EXPECT_FALSE(coil.isMaximumSteamFlowRateAutosized());
  coil.autosizeMaximumSteamFlowRate();
  EXPECT_TRUE(coil.isMaximumSteamFlowRateAutosized());
  coil.resetMaximumSteamFlowRate();
  EXPECT_FALSE(coil.maximumSteamFlowRate());
  EXPECT_FALSE(coil.isMaximumSteamFlowRateAutosized());

  EXPECT_FALSE(coil.degreeofSubCooling());
  EXPECT_TRUE(coil.setDegreeofSubCooling(3.0));
  ASSERT_TRUE(coil.degreeofSubCooling());
  EXPECT_DOUBLE_EQ(3.0, coil.degreeofSubCooling().get());
  coil.resetDegreeofSubCooling();
  EXPECT_FALSE(coil.degreeofSubCooling());

  EXPECT_TRUE(coil.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(20.0, coil.degreeofLoopSubCooling());
  EXPECT_TRUE(coil.setDegreeofLoopSubCooling(15.0));
  EXPECT_DOUBLE_EQ(15.0, coil.degreeofLoopSubCooling());
  EXPECT_FALSE(coil.isDegreeofLoopSubCoolingDefaulted());
  coil.resetDegreeofLoopSubCooling();
  EXPECT_TRUE(coil.isDegreeofLoopSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(20.0, coil.degreeofLoopSubCooling());

  EXPECT_FALSE(coil.coilControlType());
  EXPECT_TRUE(coil.setCoilControlType("TemperatureSetpointControl"));
  ASSERT_TRUE(coil.coilControlType());
  coil.resetCoilControlType();
  ASSERT_TRUE(coil.coilControlType());
  EXPECT_TRUE(coil.coilControlType()->empty());
}
