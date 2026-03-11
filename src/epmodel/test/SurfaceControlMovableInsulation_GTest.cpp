/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfaceControlMovableInsulation.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfaceControlMovableInsulation_DefaultConstructor) {
  Model model;
  SurfaceControlMovableInsulation movIns(model);
  EXPECT_EQ(SurfaceControlMovableInsulation::iddObjectType(), movIns.iddObject().type());
  EXPECT_EQ("Outside", movIns.insulationType());
}

TEST_F(EPModelFixture, SurfaceControlMovableInsulation_InsulationType_RoundTrip) {
  Model model;
  SurfaceControlMovableInsulation movIns(model);

  EXPECT_TRUE(movIns.setInsulationType("Inside"));
  EXPECT_EQ("Inside", movIns.insulationType());

  EXPECT_TRUE(movIns.setInsulationType("Outside"));
  EXPECT_EQ("Outside", movIns.insulationType());

  // Invalid value should fail
  EXPECT_FALSE(movIns.setInsulationType("InvalidValue"));
  // Value should remain unchanged after failed set
  EXPECT_EQ("Outside", movIns.insulationType());
}

TEST_F(EPModelFixture, SurfaceControlMovableInsulation_InsulationTypeValues) {
  auto values = SurfaceControlMovableInsulation::insulationTypeValues();
  EXPECT_EQ(2u, values.size());
  EXPECT_NE(std::find(values.begin(), values.end(), "Outside"), values.end());
  EXPECT_NE(std::find(values.begin(), values.end(), "Inside"), values.end());
}
