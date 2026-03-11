/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneHVACBaseboardRadiantConvectiveSteam.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveSteam_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveSteam baseboard(model);

  EXPECT_EQ(ZoneHVACBaseboardRadiantConvectiveSteam::iddObjectType(), baseboard.iddObject().type());
  EXPECT_FALSE(baseboard.heatingDesignCapacity());
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());
  EXPECT_TRUE(baseboard.degreeofSubCooling());
  EXPECT_DOUBLE_EQ(5.0, baseboard.degreeofSubCooling().get());
  EXPECT_FALSE(baseboard.isDegreeofSubCoolingDefaulted());
  EXPECT_FALSE(baseboard.maximumSteamFlowRate());
  EXPECT_TRUE(baseboard.isMaximumSteamFlowRateAutosized());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveSteam_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveSteam baseboard(model);

  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(3100.0));
  EXPECT_TRUE(baseboard.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(3100.0, baseboard.heatingDesignCapacity().get());
  EXPECT_FALSE(baseboard.isHeatingDesignCapacityAutosized());
  baseboard.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());
  EXPECT_FALSE(baseboard.heatingDesignCapacity());

  EXPECT_TRUE(baseboard.setDegreeofSubCooling(6.9));
  EXPECT_FALSE(baseboard.isDegreeofSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(6.9, baseboard.degreeofSubCooling().get());
  baseboard.resetDegreeofSubCooling();
  EXPECT_TRUE(baseboard.isDegreeofSubCoolingDefaulted());
  EXPECT_DOUBLE_EQ(5.0, baseboard.degreeofSubCooling().get());

  EXPECT_TRUE(baseboard.setMaximumSteamFlowRate(0.0006));
  EXPECT_TRUE(baseboard.maximumSteamFlowRate());
  EXPECT_DOUBLE_EQ(0.0006, baseboard.maximumSteamFlowRate().get());
  EXPECT_FALSE(baseboard.isMaximumSteamFlowRateAutosized());
  baseboard.autosizeMaximumSteamFlowRate();
  EXPECT_TRUE(baseboard.isMaximumSteamFlowRateAutosized());
  EXPECT_FALSE(baseboard.maximumSteamFlowRate());
}
