/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyIncidentSolarMultiplier.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyIncidentSolarMultiplier_DefaultConstructor) {
  Model model;
  SurfacePropertyIncidentSolarMultiplier multiplier(model);
  EXPECT_EQ(SurfacePropertyIncidentSolarMultiplier::iddObjectType(), multiplier.iddObject().type());
  EXPECT_DOUBLE_EQ(1.0, multiplier.incidentSolarMultiplier());
}

TEST_F(EPModelFixture, SurfacePropertyIncidentSolarMultiplier_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyIncidentSolarMultiplier multiplier(model);

  EXPECT_TRUE(multiplier.setIncidentSolarMultiplier(0.42));
  EXPECT_DOUBLE_EQ(0.42, multiplier.incidentSolarMultiplier());
}
