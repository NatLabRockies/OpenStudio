/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyHeatTransferAlgorithm.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithm_DefaultConstructor) {
  Model model;
  SurfacePropertyHeatTransferAlgorithm heatTransferAlgorithm(model);
  EXPECT_EQ(SurfacePropertyHeatTransferAlgorithm::iddObjectType(), heatTransferAlgorithm.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithm_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyHeatTransferAlgorithm heatTransferAlgorithm(model);

  EXPECT_TRUE(heatTransferAlgorithm.isAlgorithmDefaulted());
  EXPECT_TRUE(heatTransferAlgorithm.setAlgorithm("MoisturePenetrationDepthConductionTransferFunction"));
  EXPECT_EQ("MoisturePenetrationDepthConductionTransferFunction", heatTransferAlgorithm.algorithm());
  heatTransferAlgorithm.resetAlgorithm();
  EXPECT_TRUE(heatTransferAlgorithm.isAlgorithmDefaulted());
}
