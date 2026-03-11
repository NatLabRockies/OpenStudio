/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SurfacePropertyHeatTransferAlgorithmConstruction.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithmConstruction_DefaultConstructor) {
  Model model;
  SurfacePropertyHeatTransferAlgorithmConstruction heatTransferAlgorithmConstruction(model);
  EXPECT_EQ(SurfacePropertyHeatTransferAlgorithmConstruction::iddObjectType(), heatTransferAlgorithmConstruction.iddObject().type());
}

TEST_F(EPModelFixture, SurfacePropertyHeatTransferAlgorithmConstruction_ScalarAccessors_RoundTrip) {
  Model model;
  SurfacePropertyHeatTransferAlgorithmConstruction heatTransferAlgorithmConstruction(model);

  EXPECT_TRUE(heatTransferAlgorithmConstruction.isAlgorithmDefaulted());
  EXPECT_TRUE(heatTransferAlgorithmConstruction.setAlgorithm("CombinedHeatAndMoistureFiniteElement"));
  EXPECT_EQ("CombinedHeatAndMoistureFiniteElement", heatTransferAlgorithmConstruction.algorithm());
  heatTransferAlgorithmConstruction.resetAlgorithm();
  EXPECT_TRUE(heatTransferAlgorithmConstruction.isAlgorithmDefaulted());
}
