/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/MaterialPropertyHeatAndMoistureTransferDiffusion.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferDiffusion_DefaultConstructor) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferDiffusion object(model);
  EXPECT_EQ(MaterialPropertyHeatAndMoistureTransferDiffusion::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferDiffusion_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferDiffusion object(model);

  EXPECT_TRUE(object.setNumberofDataPairs(3));
  EXPECT_EQ(3, object.numberofDataPairs());
}
