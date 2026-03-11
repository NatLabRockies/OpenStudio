/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MaterialPropertyHeatAndMoistureTransferRedistribution.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferRedistribution_DefaultConstructor) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferRedistribution object(model);
  EXPECT_EQ(MaterialPropertyHeatAndMoistureTransferRedistribution::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyHeatAndMoistureTransferRedistribution_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyHeatAndMoistureTransferRedistribution object(model);

  EXPECT_TRUE(object.setNumberofRedistributionpoints(3));
  EXPECT_EQ(3, object.numberofRedistributionpoints());
}
