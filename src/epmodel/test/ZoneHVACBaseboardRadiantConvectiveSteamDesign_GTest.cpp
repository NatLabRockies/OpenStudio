/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneHVACBaseboardRadiantConvectiveSteamDesign.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveSteamDesign_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveSteamDesign baseboard(model);

  EXPECT_EQ(ZoneHVACBaseboardRadiantConvectiveSteamDesign::iddObjectType(), baseboard.iddObject().type());
  EXPECT_EQ("HeatingDesignCapacity", baseboard.heatingDesignCapacityMethod());
  EXPECT_FALSE(baseboard.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(1.0, baseboard.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_FALSE(baseboard.isFractionofAutosizedHeatingDesignCapacityDefaulted());
  EXPECT_DOUBLE_EQ(0.001, baseboard.convergenceTolerance());
  EXPECT_FALSE(baseboard.isConvergenceToleranceDefaulted());
  EXPECT_DOUBLE_EQ(0.2, baseboard.fractionRadiant());
  ASSERT_TRUE(baseboard.fractionofRadiantEnergyIncidentonPeople());
  EXPECT_DOUBLE_EQ(0.3, baseboard.fractionofRadiantEnergyIncidentonPeople().get());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardRadiantConvectiveSteamDesign_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardRadiantConvectiveSteamDesign baseboard(model);

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", baseboard.heatingDesignCapacityMethod());
  baseboard.resetHeatingDesignCapacityMethod();
  EXPECT_EQ("HeatingDesignCapacity", baseboard.heatingDesignCapacityMethod());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityPerFloorArea(0.5));
  ASSERT_TRUE(baseboard.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(0.5, baseboard.heatingDesignCapacityPerFloorArea().get());
  baseboard.resetHeatingDesignCapacityPerFloorArea();
  EXPECT_FALSE(baseboard.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(baseboard.setFractionofAutosizedHeatingDesignCapacity(0.75));
  EXPECT_DOUBLE_EQ(0.75, baseboard.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_FALSE(baseboard.isFractionofAutosizedHeatingDesignCapacityDefaulted());
  baseboard.resetFractionofAutosizedHeatingDesignCapacity();
  EXPECT_TRUE(baseboard.isFractionofAutosizedHeatingDesignCapacityDefaulted());
  EXPECT_DOUBLE_EQ(1.0, baseboard.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(baseboard.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, baseboard.convergenceTolerance());
  EXPECT_FALSE(baseboard.isConvergenceToleranceDefaulted());
  baseboard.resetConvergenceTolerance();
  EXPECT_TRUE(baseboard.isConvergenceToleranceDefaulted());
  EXPECT_DOUBLE_EQ(0.001, baseboard.convergenceTolerance());

  EXPECT_TRUE(baseboard.setFractionRadiant(0.4));
  EXPECT_DOUBLE_EQ(0.4, baseboard.fractionRadiant());

  EXPECT_TRUE(baseboard.setFractionofRadiantEnergyIncidentonPeople(0.25));
  ASSERT_TRUE(baseboard.fractionofRadiantEnergyIncidentonPeople());
  EXPECT_DOUBLE_EQ(0.25, baseboard.fractionofRadiantEnergyIncidentonPeople().get());
  baseboard.resetFractionofRadiantEnergyIncidentonPeople();
  EXPECT_FALSE(baseboard.fractionofRadiantEnergyIncidentonPeople());
}
